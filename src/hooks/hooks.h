#pragma once

#include "../gui/gui.h"

#include "../valve/istudiorender.h"
#include "../valve/cmatrix.h"
#include "../valve/cvector.h"
#include "../valve/imaterialsystem.h"
#include "../valve/cbaseentity.h"
#include "../valve/cusercmd.h"
#include "../valve/clientframestage_t.h"
#include "../valve/ivpanel.h"
#include "../valve/gameevent.h"
#include "../valve//cviewsetup.h"

#include "../helpers/interface.h"

#include "../global/vars.h"

namespace hooks
{
	void setup();
	void destroy();

	// EndScene
	typedef long (__thiscall* EndScene_t)(void*, IDirect3DDevice9*);
	inline EndScene_t EndSceneOriginal = 0;
	long __stdcall EndScene(IDirect3DDevice9* device);

	// Reset
	typedef HRESULT (__thiscall* Reset_t)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
	inline Reset_t ResetOriginal = 0;
	HRESULT __stdcall Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params);

	// CreateMove
	typedef bool(__thiscall* CreateMove_t)(void*, float, CUserCmd*);
	inline CreateMove_t CreateMoveOriginal = 0;
	bool __stdcall CreateMoveHook(float time, CUserCmd* cmd);

	// DrawModel
	typedef void(__thiscall* DrawModel_t)(void*, void*, const ModelRenderInfo&, CMatrix3x4*, float*, float*, const CVector&, const int32_t);
	inline DrawModel_t DrawModelOriginal = 0;
	void __stdcall DrawModel(void* results, const ModelRenderInfo& info, CMatrix3x4* bones, float* flexWeight, float* flexDelayedWeight , const CVector& modelOrigin, const int32_t flags);

	// FrameStageNotify
	typedef void(__stdcall* FrameStageNotify_t)(ClientFrameStage_t);
	inline FrameStageNotify_t FrameStageNotifyOriginal = 0;
	void __stdcall FrameStageNotify(ClientFrameStage_t curStage);

	// PaintTraverse
	typedef void(__thiscall* PaintTraverse_t)(IVPanel*, uintptr_t, bool, bool);
	inline PaintTraverse_t PaintTraverseOriginal = 0;
	void __stdcall PaintTraverse(uintptr_t panel,bool forceRepaint, bool allowForce);

	// FireEventClientSide
	typedef bool(__thiscall* FireEventClientSide_t)(void*, GameEvent*);
	inline FireEventClientSide_t FireEventClientSideOriginal = 0;
	bool __stdcall FireEventClientSide(GameEvent* gameEvent);

	// OverrideView
	typedef bool(__thiscall* OverrideView_t)(void*, CViewSetup*);
	inline OverrideView_t OverrideViewOriginal = 0;
	void __stdcall OverrideView(CViewSetup* view);

	// DoPostScreenEffects
	typedef int(__thiscall* DoPostScreenSpaceEffects_t)(void*, CViewSetup*);
	inline DoPostScreenSpaceEffects_t DoPostScreenSpaceEffectsOriginal = 0;
	int __stdcall DoPostScreenSpaceEffects(CViewSetup* view);
}