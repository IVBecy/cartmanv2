#pragma once

#include "vars.h"

#include "../helpers/interface.h"
#include "../helpers/netvars.h"

void vars::getLocalPlayer() {
    int localPlayerIndex = interfaces::baseEngine->GetLocalPlayerIndex();
    localPlayer = interfaces::entityList->GetEntityFromIndex(localPlayerIndex);
}

utils::healthColorurs  utils::GetHealthColorFromDecimal(int health) {
    healthColorurs c{ };
    c.r = (health * -0.01) * 255;
    c.g = (health * 0.01) * 255;
    return c;
}
