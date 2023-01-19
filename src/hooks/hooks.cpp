#include "hooks.h"

#include "../../minhook/minhook.h"

#include "../helpers/vmt.h"

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_win32.h"
#include "../../imgui/imgui_impl_dx9.h"

#include "../global/config.h"

#include "../hacks/misc.h"
#include "../hacks/visuals.h"
#include "../hacks/aim.h"
#include "../hacks/esp.h"


void hooks::setup(){
	if (!vars::localPlayer) {
		vars::getLocalPlayer();
	}
	MH_Initialize();

	MH_CreateHook(vmt::getFunction(interfaces::clientMode, 24), &CreateMoveHook, (void**)(&CreateMoveOriginal));
	MH_CreateHook(vmt::getFunction(interfaces::studioRender, 29), &DrawModel, (void**)(&DrawModelOriginal));
	MH_CreateHook(vmt::getFunction(interfaces::baseClient, 37), &FrameStageNotify, (void**)(&FrameStageNotifyOriginal));
	MH_CreateHook(vmt::getFunction(interfaces::panel, 41), &PaintTraverse, (void**)(&PaintTraverseOriginal));
	MH_CreateHook(vmt::getFunction(interfaces::gameEvent, 9), &FireEventClientSide, (void**)(&FireEventClientSideOriginal));
	MH_CreateHook(vmt::getFunction(interfaces::clientMode, 18), &OverrideView, (void**)(&OverrideViewOriginal));
	MH_CreateHook(vmt::getFunction(interfaces::clientMode, 44), &DoPostScreenSpaceEffects, (void**)(&DoPostScreenSpaceEffectsOriginal));
	MH_CreateHook(vmt::getFunction(gui::device, 42), &EndScene, (void**)(&EndSceneOriginal));
	MH_CreateHook(vmt::getFunction(gui::device, 16), &Reset, (void**)(&ResetOriginal));

	MH_EnableHook(MH_ALL_HOOKS);

	gui::destroyDirectX();
}

void hooks::destroy(){
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

long __stdcall hooks::EndScene(IDirect3DDevice9* device) {
	const auto result = EndSceneOriginal(device,device);

	if (!gui::setupDone) {
		gui::setupMenu(device);
	}

	if (gui::show) {
		gui::render();
	}

	return result;
}

HRESULT __stdcall hooks::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) {
	ImGui_ImplDX9_InvalidateDeviceObjects();
	const auto result = ResetOriginal(device,device,params);
	ImGui_ImplDX9_CreateDeviceObjects();
	return result;
}


bool __stdcall hooks::CreateMoveHook(float time, CUserCmd* cmd) {
	vars::getLocalPlayer();

	if (!cmd->commandNumber) {
		return CreateMoveOriginal(interfaces::clientMode, time, cmd);
	}

	if (vars::localPlayer && vars::localPlayer->isAlive() && interfaces::baseEngine->IsInGame()) {
		misc::sniperCross();
		misc::bunnyHop(cmd);
		aim::aimbot(cmd);
		aim::rcs(cmd, _rcs::oldPunch);
		aim::trigger(cmd);
		visual::skyBox();
	}

	return false;
}

void __stdcall hooks::DrawModel(void* results, const ModelRenderInfo& info, CMatrix3x4* bones, float* flexWeight, float* flexDelayedWeight, const CVector& modelOrigin, const int32_t flags) {
	
	vars::getLocalPlayer();

	if (vars::localPlayer && interfaces::baseEngine->IsInGame() && !interfaces::studioRender->IsForcedMaterialOverride()) {
		visual::chams(results, info, bones, flexWeight, flexDelayedWeight, modelOrigin, flags);
		misc::noFlash();

	}
	else {
		DrawModelOriginal(interfaces::studioRender, results, info, bones, flexWeight, flexDelayedWeight, modelOrigin, flags);
	}
}

void __stdcall hooks::FrameStageNotify(ClientFrameStage_t curStage) {
	vars::getLocalPlayer();

	if (vars::localPlayer && interfaces::baseEngine->IsInGame()) {
		if (curStage == ClientFrameStage_t::FRAME_RENDER_START) {
			visual::skyColour();
			misc::nadeTrajectory();
		}
	}

	FrameStageNotifyOriginal(curStage);
}

void __stdcall hooks::PaintTraverse(uintptr_t panel, bool forceRepaint, bool allowForce) {
	vars::getLocalPlayer();

	if (vars::localPlayer && interfaces::baseEngine->IsInGame()) {

		if (panel == interfaces::engineGui->GetPanel(PANEL_TOOLS)) {
			esp::box();
			visual::hitMarker();
		}
	}
	PaintTraverseOriginal(interfaces::panel, panel, forceRepaint, allowForce);
}

bool __stdcall hooks::FireEventClientSide(GameEvent* gameEvent) {
	if (gameEvent && vars::localPlayer && interfaces::baseEngine->IsInGame()) {
		if (strcmp(gameEvent->GetName(),"player_hurt") == 0 && interfaces::baseEngine->GetPlayerForUserID(gameEvent->GetInt("attacker")) == interfaces::baseEngine->GetLocalPlayerIndex()) {
			config::visuals::hitTime = interfaces::globals->currentTime;
		}
	}
	return FireEventClientSideOriginal(interfaces::gameEvent, gameEvent);
}


void __stdcall hooks::OverrideView(CViewSetup* view) {
	OverrideViewOriginal(interfaces::clientMode,view);
}

int __stdcall hooks::DoPostScreenSpaceEffects(CViewSetup* view) {
	return DoPostScreenSpaceEffectsOriginal(interfaces::clientMode, view);
}
