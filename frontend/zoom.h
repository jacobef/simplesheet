#ifndef ZOOM_H
#define ZOOM_H
#include <stdbool.h>

typedef struct ZoomInfo {
    double zoom_delta;
    bool zooming;
} ZoomInfo;

void SetupTrackpadZoom(void);
ZoomInfo PollZoom(void);

#endif
