#include "visuals.h"

#include "../global/config.h"
#include "../global/vars.h"

#include "../helpers/interface.h"

#include "../hooks/hooks.h"

// Chams
void visual::chams(void* results, const ModelRenderInfo& info, CMatrix3x4* bones, float* flexWeight, float* flexDelayedWeight, const CVector& modelOrigin, const int32_t flags) {

	if (vars::localPlayer && info.renderable) {
		CBaseEntity* entity = info.renderable->GetIClientUnknown()->GetBaseEntity();

		// Enemy
		if (entity && entity->IsPlayer() && entity->GetTeam() != vars::localPlayer->GetTeam() && entity != vars::localPlayer) {

			IMaterial* mat = interfaces::materialSystem->FindMaterial("debug/debugambientcube");

			interfaces::studioRender->SetAlphaModulation(1.f);

			if (config::visuals::chams::__hiddenColoursEnemy) {
				mat->SetMaterialVarFlag(IMaterial::IGNOREZ, true);
				interfaces::studioRender->SetColorModulation(config::visuals::chams::hiddenColoursEnemy);
				interfaces::studioRender->ForcedMaterialOverride(mat);
				hooks::DrawModelOriginal(interfaces::studioRender, results, info, bones, flexWeight, flexDelayedWeight, modelOrigin, flags);
			}

			if (config::visuals::chams::__visibleColoursEnemy) {
				mat->SetMaterialVarFlag(IMaterial::IGNOREZ, false);
				interfaces::studioRender->SetColorModulation(config::visuals::chams::visibleColoursEnemy);
				interfaces::studioRender->ForcedMaterialOverride(mat);
				hooks::DrawModelOriginal(interfaces::studioRender, results, info, bones, flexWeight, flexDelayedWeight, modelOrigin, flags);
			}
			hooks::DrawModelOriginal(interfaces::studioRender, results, info, bones, flexWeight, flexDelayedWeight, modelOrigin, flags);
			return interfaces::studioRender->ForcedMaterialOverride(nullptr);
		}

		// Team
		else if (entity && entity->IsPlayer() && entity->GetTeam() == vars::localPlayer->GetTeam() && entity != vars::localPlayer) {

			IMaterial* mat = interfaces::materialSystem->FindMaterial("debug/debugambientcube");

			interfaces::studioRender->SetAlphaModulation(1.f);

			if (config::visuals::chams::__hiddenColoursTeam) {
				mat->SetMaterialVarFlag(IMaterial::IGNOREZ, true);
				interfaces::studioRender->SetColorModulation(config::visuals::chams::hiddenColoursTeam);
				interfaces::studioRender->ForcedMaterialOverride(mat);
				hooks::DrawModelOriginal(interfaces::studioRender, results, info, bones, flexWeight, flexDelayedWeight, modelOrigin, flags);
			}

			if (config::visuals::chams::__visibleColoursTeam) {
				mat->SetMaterialVarFlag(IMaterial::IGNOREZ, false);
				interfaces::studioRender->SetColorModulation(config::visuals::chams::visibleColoursTeam);
				interfaces::studioRender->ForcedMaterialOverride(mat);
				hooks::DrawModelOriginal(interfaces::studioRender, results, info, bones, flexWeight, flexDelayedWeight, modelOrigin, flags);
			}
			hooks::DrawModelOriginal(interfaces::studioRender, results, info, bones, flexWeight, flexDelayedWeight, modelOrigin, flags);
			return interfaces::studioRender->ForcedMaterialOverride(nullptr);
		}

	}
	hooks::DrawModelOriginal(interfaces::studioRender, results, info, bones, flexWeight, flexDelayedWeight, modelOrigin, flags);
}

// Sky colour
void visual::skyColour() {
	if (!config::visuals::skyColour) {
		return;
	}

	for (MaterialHandle_t h = interfaces::materialSystem->FirstMaterial(); h != interfaces::materialSystem->InvalidMaterial(); h = interfaces::materialSystem->NextMaterial(h)) {
		const auto mat = interfaces::materialSystem->GetMaterial(h);
		if (strcmp(mat->GetTextureGroupName(), "SkyBox textures") == 0) {
			mat->ColorModulate(config::visuals::skyColours[0], config::visuals::skyColours[1], config::visuals::skyColours[2]);
		}
	}
}

// Sky Box
void visual::skyBox() {
	if (strcmp(config::visuals::skyName, interfaces::cVar->FindVar("sv_skyname")->strString) != 0) {
		config::visuals::skyName = interfaces::cVar->FindVar("sv_skyname")->strString;
	}
	if (!config::visuals::skyEnable) {
		interfaces::cVar->FindVar("sv_skyname")->SetValue(config::visuals::skyName);
	}
	else {
		interfaces::cVar->FindVar("sv_skyname")->SetValue(config::visuals::skyBoxes[config::visuals::skyNew]);
	}
}

void visual::hitMarker(){

	if (!config::visuals::hitMarkerToggle) {
		return;
	}

	if (config::visuals::hitTime + 0.25 >= interfaces::globals->currentTime) {
		const auto [width, height] = interfaces::surface->GetScreenSize();
		const auto width_mid = width / 2;
		const auto height_mid = height / 2;
		interfaces::surface->DrawSetColor(255, 255, 255);
		interfaces::surface->DrawLine(width_mid +config::visuals::hitMarkerSize ,height_mid +config::visuals::hitMarkerSize, width_mid + 4, height_mid + 4);
		interfaces::surface->DrawLine(width_mid -config::visuals::hitMarkerSize, height_mid +config::visuals::hitMarkerSize, width_mid - 4, height_mid + 4);
		interfaces::surface->DrawLine(width_mid +config::visuals::hitMarkerSize, height_mid -config::visuals::hitMarkerSize, width_mid + 4, height_mid - 4);
		interfaces::surface->DrawLine(width_mid -config::visuals::hitMarkerSize, height_mid -config::visuals::hitMarkerSize, width_mid - 4, height_mid - 4);
	}
}

// Material setter
void visual::setMaterial(IMaterial* mat, bool state, float colours[3]) {
	mat->SetMaterialVarFlag(IMaterial::IGNOREZ, state);
	interfaces::studioRender->SetColorModulation(colours);
	interfaces::studioRender->ForcedMaterialOverride(mat);
}