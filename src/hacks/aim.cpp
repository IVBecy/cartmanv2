#include "aim.h"

#include "../valve/cvector.h"
#include "../valve/cmatrix.h"
#include "../valve/cbaseentity.h"
#include "../valve/ienginetrace.h"
#include "../valve/weaponinfo.h"

#include "../helpers/interface.h"

#include "../global/vars.h"
#include "../global/config.h"

int aim::getAimbotBone(const char* choice) {
	if (strcmp(choice,"Head") == 0) {
		return 8;
	}
	else if (strcmp(choice, "Chest") == 0) {
		return 6;
	}
	else if (strcmp(choice, "Neck") == 0) {
		return 7;
	}
	else if (strcmp(choice, "Core") == 0) {
		return 5;
	}
}

void aim::aimbot(CUserCmd* cmd) {
	
	if(!config::aim::aimbot){
		return;
	}

	if (!config::aim::autoLock) {
		if (!(cmd->buttons & CUserCmd::IN_ATTACK)) {
			return;
		}
	}

	CVector newAngle{ };
	float bestFov = config::aim::fov ;

	for (int i = 1; i < interfaces::globals->maxClients; i++) {
		CBaseEntity* entity = interfaces::entityList->GetEntityFromIndex(i);

		if (!entity) {
			continue;
		}

		if(entity->IsDormant() || !entity->isAlive() || entity->GetTeam() == vars::localPlayer->GetTeam()){
			continue;
		}

		if (!gunCheck(vars::localPlayer->GetActiveWeapon()->GetWeaponType())) {
			return;
		}
		
		CMatrix3x4 bones[128];
		if (!entity->SetupBones(bones,128,256,interfaces::globals->currentTime)) {
			continue;
		}

		CVector eyePos;
		vars::localPlayer->GetEyePosition(eyePos);

		CVector aimPunch;
		vars::localPlayer->GetAimPunch(aimPunch);

		int id = getAimbotBone(config::aim::hitboxes[config::aim::hitBoxChoice]);
		// Trace ray
		CTrace trace;
		interfaces::engineTrace->TraceRay(CRay{ eyePos,bones[id].Origin() },MASK_SHOT,CTraceFilter{ vars::localPlayer },trace);
		if (!trace.entity) {
			return;
		}

		CVector enemyAngle{(bones[id].Origin() - eyePos).ToAngle() - (cmd->viewAngles + aimPunch)};

		float fov = std::hypot(enemyAngle.x, enemyAngle.y);
		if (fov < bestFov) {
			bestFov = fov;
			newAngle = enemyAngle;
		}
	}

	CVector testAngles;

	if (config::aim::smooth > 0.f) {
		testAngles.x = cmd->viewAngles.x + newAngle.x / config::aim::smooth;
		testAngles.y = cmd->viewAngles.y + newAngle.y / config::aim::smooth;

	}
	else {
		testAngles = cmd->viewAngles + newAngle;
	}

	cmd->viewAngles = clampAngles(normalizeAngles(testAngles));

	if (!config::aim::silent) {
		interfaces::baseEngine->SetViewAngles(cmd->viewAngles);
	}

}


// Recoil compensation
void aim::rcs(CUserCmd* cmd, CVector& oldPunch) {

	if (!config::aim::rcs) {
		return;
	}

	CVector aimPunch;
	vars::localPlayer->GetAimPunch(aimPunch);

	CVector newRecoil{
		cmd->viewAngles.x + oldPunch.x - aimPunch.x,
		cmd->viewAngles.y + oldPunch.y - aimPunch.y,
		0
	};

	cmd->viewAngles = clampAngles(normalizeAngles(newRecoil));

	interfaces::baseEngine->SetViewAngles(cmd->viewAngles);

	oldPunch.x = aimPunch.x;
	oldPunch.y = aimPunch.y;

}

void aim::trigger(CUserCmd* cmd) {

	if (!config::aim::trigger) {
		return;
	}

	if (!gunCheck(vars::localPlayer->GetActiveWeapon()->GetWeaponType())) {
		return;
	}

	CVector eyePos;
	vars::localPlayer->GetEyePosition(eyePos);

	CVector aimPunch;
	vars::localPlayer->GetAimPunch(aimPunch);

	const CVector distance{ 
		std::cos(Deg2Rad(cmd->viewAngles.x + aimPunch.x)) * std::cos(Deg2Rad(cmd->viewAngles.y + aimPunch.y)) * 8192.f,
		std::cos(Deg2Rad(cmd->viewAngles.x + aimPunch.x)) * std::sin(Deg2Rad(cmd->viewAngles.y + aimPunch.y)) * 8192.f,
		-std::sin(Deg2Rad(cmd->viewAngles.x + aimPunch.x)) * 8192.f 
	};

	CTrace trace;
	interfaces::engineTrace->TraceRay(CRay{ eyePos, distance + eyePos}, 0x46004009, CTraceFilter{ vars::localPlayer }, trace);
	
	if (!trace.entity || !trace.entity->IsPlayer()) {
		return;
	}

	if (!trace.entity->isAlive() || trace.entity->GetTeam() == vars::localPlayer->GetTeam()) {
		return;
	}

	cmd->buttons |= CUserCmd::IN_ATTACK;
}


// Normalize angles
CVector aim::normalizeAngles(CVector angles) {
	if (angles.x > 180)
	{
		angles.x -= 360.0f;
	}

	if (angles.x < 180)
	{
		angles.x += 360.0f;
	}

	return angles;
};

// Clamp angles
CVector aim::clampAngles(CVector angles) {
	if (angles.x > 89.0f && angles.x <= 180.0f)
	{
		angles.x = 89.0f;
	}

	if (angles.x > 180.0f)
	{
		angles.x = angles.x - 360.0f;
	}

	if (angles.x < -89.0f)
	{
		angles.x = -89.0f;
	}

	if (angles.y > 180.0f)
	{
		angles.y = angles.y - 360.0f;
	}

	if (angles.y < -180.0f)
	{
		angles.y = angles.y + 360.0f;
	}

	angles.z = 0;

	return angles;
};

// Gun check
bool aim::gunCheck(int type) {
	switch (type) {

	case EWeaponType::WEAPONTYPE_GRENADE:
	case EWeaponType::WEAPONTYPE_C4:
	case EWeaponType::WEAPONTYPE_KNIFE:
	{
		return false;
	}
	case EWeaponType::WEAPONTYPE_SNIPER:
	{
		if (!vars::localPlayer->IsScoped(interfaces::clientClass)) {
			return false;
		}
		return true;
		break;
	}
	default:
		return true;
		break;
	}
}

void aim::fixMove(CUserCmd* cmd,const CVector& previousViewAngles, const CVector& currentViewAngles, float oldF, float oldS) {

	float deltaView = cmd->viewAngles.y - currentViewAngles.y;
	float f1;
	float f2;

	if (currentViewAngles.y < 0.f)
		f1 = 360.0f + currentViewAngles.y;
	else
		f1 = currentViewAngles.y;

	if (cmd->viewAngles.y < 0.0f)
		f2 = 360.0f + cmd->viewAngles.y;
	else
		f2 = cmd->viewAngles.y;

	if (f2 < f1)
		deltaView = abs(f2 - f1);
	else
		deltaView = 360.0f - abs(f1 - f2);
	deltaView = 360.0f - deltaView;

	cmd->forwardMove = cos(Deg2Rad(deltaView)) * oldF + cos(Deg2Rad(deltaView + 90.f)) * oldS;
	cmd->sideMove = sin(Deg2Rad(deltaView)) * oldF + sin(Deg2Rad(deltaView + 90.f)) * oldS;
}
