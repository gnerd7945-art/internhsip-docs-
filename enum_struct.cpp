struct PublishProfile 
{
    std::string name;
    std::string cameraTransport;
    std::string ffmpegRtspTransport;
    std::string protocol;
};
PublishProfile profile{       // initalize: c20 feature , ordering matter 
        .name = "rtmp_tcp",
        .cameraTransport = "tcp",
        .ffmpegRtspTransport = "tcp",
        .protocol = "rtmp",
    };

PublishProfile profile{ // traditional way, ordering matter 
    "rtmp_tcp", 
    "tcp", 
    "tcp", 
    "rtmp"
};

// 1. Create an empty struct (variables default to empty strings)
PublishProfile profile; 

// 2. Assign values one by one (Order does not matter here!)
profile.protocol = "rtmp";
profile.name = "rtmp_tcp";
profile.cameraTransport = "tcp";
profile.ffmpegRtspTransport = "tcp";
---------------------------------------------------------------------------------------------------------------------------------------
enum class DeviceState { IDLE, CONNECTING, ACTIVE, ERROR };

void handleState(DeviceState state) {
    switch (state) {
        using enum DeviceState; // Introduces identifiers locally
        case IDLE:       /* ... */ break;
        case CONNECTING: /* ... */ break;
        case ACTIVE:     /* ... */ break;
        case ERROR:      /* ... */ break;
    }
}
