#pragma once
#include "modelinfo.h"
#include "cmatrix.h"
#include "imaterialsystem.h"


struct ModelRenderInfo {
	CStudioHdr* studioHdr;
	void* hardwareData;
	int decals;
	int skin;
	int body;
	int hitboxSet;
	IClientRenderable* renderable;
};

enum OverrideType_t : int
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
	OVERRIDE_SSAO_DEPTH_WRITE
};

class ModelRender {
public:
	void ForcedMaterialOverride(IMaterial* newMaterial, OverrideType_t nOverrideType = OVERRIDE_NORMAL) {
		vmt::callFunction<float>(this, 1, newMaterial, nOverrideType);
	}
};