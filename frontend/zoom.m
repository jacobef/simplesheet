#import <Cocoa/Cocoa.h>
#include <raylib.h>
#include <stdbool.h>
#include "zoom.h"

static double zoomDelta = 0.0;
static bool zooming = false;

static NSWindow *FindRaylibWindow(void) {
    if ([[NSApp windows] count] > 0) {
        return [[NSApp windows] objectAtIndex:0];
    }
    return nil;
}

@interface ZoomPollingView : NSView
@end

@implementation ZoomPollingView
- (void)magnifyWithEvent:(NSEvent *)event {
    if (event.phase == NSEventPhaseBegan) {
        zooming = true;
        zoomDelta = 0.0;
    } else if (event.phase == NSEventPhaseEnded || event.phase == NSEventPhaseCancelled) {
        zooming = false;
        zoomDelta = 0.0;
    } else {
        zoomDelta += [event magnification];
    }
}
@end

void SetupTrackpadZoom(void) {
    if (!NSApp) {
        fprintf(stderr, "SetupTrackpadZoom(): NSApplication doesn't exist; did you forget to call InitWindow before this?\n");
        exit(1);
    }

    NSWindow *raylibWin = FindRaylibWindow();
    if (!raylibWin) {
        fprintf(stderr, "SetupTrackpadZoom(): Couldn't find the window; did you forget to call InitWindow before this?\n");
        exit(1);
    }

    // Save the original content view, so Raylib's rendering remains intact
    NSView *oldContent = [raylibWin contentView];
    NSRect frame = [oldContent frame];

    // Create a new custom view that captures magnify events
    ZoomPollingView *zoomView = [[ZoomPollingView alloc] initWithFrame:frame];
    [zoomView setWantsRestingTouches:YES];

    // Put Raylib's original view inside our new zoomView as a subview
    [raylibWin setContentView:zoomView];
    [zoomView addSubview:oldContent];
    [oldContent setFrame:[zoomView bounds]];
}

ZoomInfo PollZoom(void) {
    struct ZoomInfo out = { zoomDelta, zooming };
    zoomDelta = 0.0;
    return out;
}
