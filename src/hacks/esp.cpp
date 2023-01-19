#include "esp.h"

#include "../helpers/interface.h"

#include "../global/vars.h"
#include "../global/config.h"

#include "../helpers/netvars.h"

void esp::box() {

	if (!config::esp::Box) {
		return;
	}

	if (vars::localPlayer && interfaces::baseEngine->IsInGame()) {

		if (!esp::tahoma) {
			esp::tahoma = interfaces::surface->FontCreate();
			interfaces::surface->SetFontGlyphSet(esp::tahoma, "Tahoma", 13, 550, 0, 0, FONTFLAG_ANTIALIAS);
		}

		for (int i = 1; i < interfaces::globals->maxClients; i++) {

			CBaseEntity* entity = interfaces::entityList->GetEntityFromIndex(i);

			if (!entity) {
				continue;
			}

			if (entity->IsDormant() || !entity->isAlive() || entity->GetTeam() == vars::localPlayer->GetTeam()) {
				continue;
			}

			CMatrix3x4 bones[128];
			if (!entity->SetupBones(bones, 128, 0x7FF00, interfaces::globals->currentTime)) {
				continue;
			}

			CVector head;
			if (interfaces::debugOverlay->ScreenPosition(bones[8].Origin() + CVector{ 0.f,0.f,11.f }, head)) {
				continue;
			}

			CVector feet;
			if (interfaces::debugOverlay->ScreenPosition(entity->GetAbsOrigin() - CVector{ 0.f,0.f,9.f }, feet)) {
				continue;
			}

			float height = feet.y - head.y;
			float width = height * 0.25f;
			float right = head.x + width;
			float left = head.x - width;

			interfaces::surface->DrawSetColor(0, 0, 0);
			interfaces::surface->DrawOutlinedRect((int)left - 0.5, (int)head.y - 0.5, (int)right - 0.5, (int)feet.y - 0.5);
			interfaces::surface->DrawOutlinedRect((int)left + 0.5, (int)head.y + 0.5, (int)right + 0.5, (int)feet.y + 0.5);
			
			interfaces::surface->DrawSetColor(255, 255, 255);
			interfaces::surface->DrawOutlinedRect((int)left, (int)head.y, (int)right, (int)feet.y);

			if (config::esp::BoxHealth) {
				int health = entity->GetHealth();
				utils::healthColorurs  healthcolours = utils::GetHealthColorFromDecimal(health);
				interfaces::surface->DrawSetColor(healthcolours.r, healthcolours.g, 0);
				interfaces::surface->DrawFilledRect((int)left - 7, (int)feet.y - (int)(height * health * 0.01f), (int)left - 5, (int)feet.y);
			}

			if (config::esp::showName) {
				PlayerInfo playerinfo;
				interfaces::baseEngine->GetPlayerInfo(i, playerinfo);
				
				wchar_t buffer[256];
				MultiByteToWideChar(CP_UTF8, 0, playerinfo.name, -1, buffer, 128);

				interfaces::surface->DrawSetTextFont(tahoma);
				interfaces::surface->SetTextColor(255, 255, 255);
				interfaces::surface->DrawSetTextPos((int)head.x - 25, (int)head.y - 15);
				interfaces::surface->DrawPrintText(buffer, wcslen(buffer));
			}

			if (config::esp::showGun) {

				short weaponID = entity->GetActiveWeapon()->GetWeaponId(interfaces::clientClass);
				const char* name = GetWeaponNameFromId(weaponID);

				wchar_t buffer2[256];
				MultiByteToWideChar(CP_UTF8, 0, name, -1, buffer2, 128);

				// Draw
				interfaces::surface->DrawSetTextFont(tahoma);
				interfaces::surface->SetTextColor(255, 255, 255);
				interfaces::surface->DrawSetTextPos((int)(head.x - width), (int)(head.y + height));
				interfaces::surface->DrawPrintText(buffer2, wcslen(buffer2));
			}

			if (config::esp::snapLines) {
				int w, h;
				interfaces::baseEngine->GetScreenSize(w,h);
				interfaces::surface->DrawSetColor(255, 255, 255);
				interfaces::surface->DrawLine(w / 2, h, (int)feet.x, (int)feet.y);
			}
		}
	}
}