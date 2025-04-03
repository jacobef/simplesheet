typedef struct ZoomInfo {
    double zoom_delta;
    bool zooming;
} ZoomInfo;

void SetupTrackpadZoom(void);
ZoomInfo PollZoom(void);
