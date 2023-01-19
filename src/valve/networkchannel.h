#pragma once

#include <cstddef>

#include "../helpers/vmt.h"

class NetworkChannel {
public:

    float GetLatency(int flow) 
    {
        return vmt::callFunction<float>(this, 9, flow);
    }

    float GetAvgLatency(int flow)
    {
        return vmt::callFunction<float>(this, 10, flow);
    }

    std::byte pad[44];
    int chokedPackets;
};