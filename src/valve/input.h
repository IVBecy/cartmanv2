#pragma once

#include "cvector.h"

class CInput {
public:
    std::byte pad[12];
    bool isTrackIRAvailable;
    bool isMouseInitialized;
    bool isMouseActive;
    std::byte pad1[154];
    bool isCameraInThirdPerson;
    bool cameraMovingWithMouse;
    CVector cameraOffset;
};
