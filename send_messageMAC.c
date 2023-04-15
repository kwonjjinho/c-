#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#define BUFFER_SIZE 4096

unsigned short in_cksum(unsigned short *ptr, int nbytes) {
    register long sum;
    u_short oddbyte;
    register u_short answer;

    sum = 0;
    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }
    if (nbytes == 1) {
        oddbyte = 0;
        *((u_char *)&oddbyte) = *(u_char *)ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = (u_short)~sum;

    return (answer);
}

unsigned char *get_mac_address(const char *if_name) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return NULL;
    }

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, if_name, IFNAMSIZ - 1);

    if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) {
        perror("ioctl");
        close(sock);
        return NULL;
    }

    unsigned char *mac_address = (unsigned char *)malloc(6);
    memcpy(mac_address, ifr.ifr_hwaddr.sa_data, 6);
    close(sock);

    return mac_address;
}

char *get_ip_address(const char *if_name) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return NULL;
    }

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, if_name, IFNAMSIZ - 1);

    if (ioctl(sock, SIOCGIFADDR, &ifr) < 0) {
        perror("ioctl");
        close(sock);
        return NULL;
    }

    char *ip_address = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
    close(sock);

    return ip_address;
}

unsigned char *get_arp_mac_address(const char *ip_address, const char *if_name) {
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sock < 0) {
        perror("socket");
        return NULL;
    }

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, if_name, IFNAMSIZ - 1);

    if (ioctl(sock, SIOCGIFINDEX, &ifr) < 0) {
        perror("ioctl");
        close(sock);
        return NULL;
    }

    unsigned char *mac_address = get_mac_address(if_name);
    if (mac_address == NULL) {
        close(sock);
        return NULL;
    }

    unsigned char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    struct ethhdr *eth = (struct ethhdr *)buffer;
    memcpy(eth->h_dest, "\xff\xff\xff\xff\xff\xff", ETH_ALEN);
    memcpy(eth->h_source, mac_address, ETH_ALEN);
    eth->h_proto = htons(ETH_P_ARP);

    struct arphdr *arp = (struct arphdr *)(buffer + sizeof(struct ethhdr));
    arp->ar_hrd = htons(ARPHRD_ETHER);
    arp->ar_pro = htons(ETH_P_IP);
    arp->ar_hln = ETH_ALEN;
    arp->ar_pln = sizeof(in_addr_t);
    arp->ar_op = htons(ARPOP_REQUEST);
    memcpy(&arp->ar_sha, mac_address, ETH_ALEN);
    inet_pton(AF_INET, get_ip_address(if_name), &arp->ar_sip);
    memcpy(&arp->ar_tha, "\x00\x00\x00\x00\x00\x00", ETH_ALEN);
    inet_pton(AF_INET, ip_address, &arp->ar_tip);

    struct sockaddr_ll addr;
    memset(&addr, 0, sizeof(struct sockaddr_ll));
    addr.sll_family = AF_PACKET;
    addr.sll_ifindex = ifr.ifr_ifindex;
    addr.sll_halen = ETH_ALEN;
    memcpy(addr.sll_addr, mac_address, ETH_ALEN);

    if (sendto(sock, buffer, sizeof(struct ethhdr) + sizeof(struct arphdr), 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_ll)) < 0) {
        perror("sendto");
        free(mac_address);
        close(sock);
        return NULL;
    }

    unsigned char *arp_mac_address = NULL;
    while (arp_mac_address == NULL) {
        unsigned char recv_buffer[BUFFER_SIZE];
        memset(recv_buffer, 0, BUFFER_SIZE);
        ssize_t length = recv(sock, recv_buffer, BUFFER_SIZE, 0);
        if (length < 0) {
            perror("recv");
            free(mac_address);
            close(sock);
            return NULL;
        }

        struct ethhdr *recv_eth = (struct ethhdr *)recv_buffer;
        if (ntohs(recv_eth->h_proto) == ETH_P_ARP) {
            struct arphdr *recv_arp = (struct arphdr *)(recv_buffer + sizeof(struct ethhdr));
            if (ntohs(recv_arp->ar_op) == ARPOP_REPLY && memcmp(&recv_arp->ar_tip, &arp->ar_sip, sizeof(in_addr_t)) == 0) {
                arp_mac_address = (unsigned char *)malloc(ETH_ALEN);
                memcpy(arp_mac_address, &recv_arp->ar_sha, ETH_ALEN);
            }
        }
    }

    char *compliment = "You are doing a great job!";
    unsigned char *packet = (unsigned char *)malloc(sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct icmphdr) + strlen(compliment));
    memset(packet, 0, sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct icmphdr) + strlen(compliment));

    memcpy(packet, eth, sizeof(struct ethhdr));

    struct iphdr *ip = (struct iphdr *)(packet + sizeof(struct ethhdr));
    ip->version = 4;
    ip->ihl = 5;
    ip->tos = 0;
    ip->tot_len = htons(sizeof(struct iphdr) + sizeof(struct icmphdr)
    ip->id = htons(0);
    ip->frag_off = htons(0);
    ip->ttl = 64;
    ip->protocol = IPPROTO_ICMP;
    ip->check = 0;
    inet_pton(AF_INET, get_ip_address(if_name), &ip->saddr);
    inet_pton(AF_INET, ip_address, &ip->daddr);
    ip->check = csum((unsigned short *)ip, sizeof(struct iphdr));

    struct icmphdr *icmp = (struct icmphdr *)(packet + sizeof(struct ethhdr) + sizeof(struct iphdr));
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->checksum = 0;
    icmp->un.echo.id = htons(getpid());
    icmp->un.echo.sequence = htons(1);
    memcpy(packet + sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct icmphdr), compliment, strlen(compliment));

    icmp->checksum = csum((unsigned short *)(packet + sizeof(struct ethhdr) + sizeof(struct iphdr)), sizeof(struct icmphdr) + strlen(compliment));

    struct sockaddr_ll addr2;
    memset(&addr2, 0, sizeof(struct sockaddr_ll));
    addr2.sll_family = AF_PACKET;
    addr2.sll_ifindex = ifr.ifr_ifindex;
    addr2.sll_halen = ETH_ALEN;
    memcpy(addr2.sll_addr, arp_mac_address, ETH_ALEN);

    if (sendto(sock, packet, sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct icmphdr) + strlen(compliment), 0, (struct sockaddr *)&addr2, sizeof(struct sockaddr_ll)) < 0) {
        perror("sendto");
        free(mac_address);
        free(packet);
        close(sock);
        return NULL;
    }

    free(mac_address);
    free(packet);
    close(sock);

    return arp_mac_address;
}