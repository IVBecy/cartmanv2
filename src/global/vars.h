#pragma once

#include <cstdint>

#include "../valve/cbaseentity.h"

namespace vars {
    // Version number
    inline const char* _v = "Version: 1.1.2";

    // Setup local player
    inline CBaseEntity* localPlayer = 0;
    void getLocalPlayer();

    // Other
    inline CVector fakeAngles = { };
}

// Utility Functions
namespace utils{
    struct healthColorurs {
        int r, g;
    };
    healthColorurs GetHealthColorFromDecimal(int health);
}