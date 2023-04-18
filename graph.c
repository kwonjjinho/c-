#include <stdio.h>
#include <stdlib.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

void DrawGraph(CGContextRef context)
{
    // 그래프를 그리는 코드 작성
    // CGContext 함수를 사용하여 그래프를 그립니다.
    CGContextSetRGBFillColor(context, 1, 0, 0, 1);
    CGContextFillRect(context, CGRectMake(50, 50, 100, 100));
}

int main(int argc, const char * argv[])
{
    // 윈도우 생성
    CGRect rect = CGRectMake(0, 0, 500, 500);
    CFStringRef title = CFSTR("My Window");
    CFStringRef windowClass = CFSTR("MyWindowClass");
    CFDictionaryRef options = NULL;
    CFStringRef buttonTitle = CFSTR("OK");
    CFUserNotificationDisplayAlert(0, kCFUserNotificationNoteAlertLevel, NULL, NULL, NULL, title, NULL, buttonTitle, NULL, options);

    // 그래픽 콘텍스트 생성
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(NULL, rect.size.width, rect.size.height, 8, 0, colorSpace, kCGImageAlphaPremultipliedLast);
    CGColorSpaceRelease(colorSpace);

    // 그래프 그리기
    DrawGraph(context);

    // 윈도우에 그래프 표시
    CGImageRef image = CGBitmapContextCreateImage(context);
    NSImage *nsimage = [[NSImage alloc] initWithCGImage:image size:NSZeroSize];
    NSImageView *imageView = [[NSImageView alloc] initWithFrame:NSMakeRect(0, 0, rect.size.width, rect.size.height)];
    [imageView setImage:nsimage];
    NSWindow *window = [[NSWindow alloc] initWithContentRect:rect styleMask:NSWindowStyleMaskTitled backing:NSBackingStoreBuffered defer:NO];
    [window setContentView:imageView];
    [window setTitle:(NSString *)title];
    [window makeKeyAndOrderFront:nil];

    // 이벤트 루프 실행
    [[NSApplication sharedApplication] run];

    // 자원 해제
    CGImageRelease(image);
    CGContextRelease(context);

    return 0;
}