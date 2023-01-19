#include "misc.h"

#include "../global/vars.h"
#include "../global/config.h"

#include "aim.h"

// Bunny Hop
void misc::bunnyHop(CUserCmd* cmd) {
	if(!config::misc::bunnyHop){
		return;
	}

	if (!(vars::localPlayer->GetFlags(interfaces::clientClass) & CBaseEntity::FL_ONGROUND)) {
		cmd->buttons &= ~CUserCmd::IN_JUMP;

		if (config::misc::autostrafe) {
			if (cmd->mouseDeltaX > 0) {
				cmd->sideMove = 450.0f;
			}

			if (cmd->mouseDeltaX < 0){
				cmd->sideMove = -450.0f;
			}
		}
	}
}


// No flash
void misc::noFlash() {
	IMaterial* Flash = interfaces::materialSystem->FindMaterial("effects\\flashbang");
	IMaterial* FlashWhite = interfaces::materialSystem->FindMaterial("effects\\flashbang_white");
	
	if (config::misc::noFlash) {

		Flash->SetMaterialVarFlag(IMaterial::MATERIAL_VAR_NO_DRAW, true);
		FlashWhite->SetMaterialVarFlag(IMaterial::MATERIAL_VAR_NO_DRAW, true);
	}
	else {
		Flash->SetMaterialVarFlag(IMaterial::MATERIAL_VAR_NO_DRAW, false);
		FlashWhite->SetMaterialVarFlag(IMaterial::MATERIAL_VAR_NO_DRAW, false);
	}

	interfaces::studioRender->ForcedMaterialOverride(Flash);
	interfaces::studioRender->ForcedMaterialOverride(FlashWhite);
	interfaces::studioRender->ForcedMaterialOverride(NULL);
}


// Grenade trajectory
void misc::nadeTrajectory() {
	if (config::misc::nadeTraject) {
		interfaces::cVar->FindVar("cl_grenadepreview")->SetValue(1);
	}
	else {
		interfaces::cVar->FindVar("cl_grenadepreview")->SetValue(0);
	}
}

// Sniper crosshair
void misc::sniperCross() {
	if (config::misc::showSniperCrosshair) {
		interfaces::cVar->FindVar("weapon_debug_spread_show")->SetValue(3);
	}
	else {
		interfaces::cVar->FindVar("weapon_debug_spread_show")->SetValue(0);
	}
}