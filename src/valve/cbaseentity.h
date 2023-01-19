#pragma once
#include <algorithm>

#include "../helpers/vmt.h"
#include "../helpers/netvars.h"

#include "cvector.h"
#include "cmatrix.h"
#include "clientclass.h"
#include "weaponinfo.h"
#include "animState.h"

class CBaseEntity 
{
public:
	enum eFlags : int
	{
		FL_ONGROUND = (1 << 0),
		FL_DUCKING = (1 << 1),
		FL_ANIMDUCKING = (1 << 2),
		FL_WATERJUMP = (1 << 3),
		FL_ONTRAIN = (1 << 4),
		FL_INRAIN = (1 << 5),
		FL_FROZEN = (1 << 6),
		FL_ATCONTROLS = (1 << 7),
		FL_CLIENT = (1 << 8),
		FL_FAKECLIENT = (1 << 9),
		FL_INWATER = (1 << 10),
		FL_FLY = (1 << 11),
		FL_SWIM = (1 << 12),
		FL_CONVEYOR = (1 << 13),
		FL_NPC = (1 << 14),
		FL_GODMODE = (1 << 15),
		FL_NOTARGET = (1 << 16),
		FL_AIMTARGET = (1 << 17),
		FL_PARTIALGROUND = (1 << 18),
		FL_STATICPROP = (1 << 19),
		FL_GRAPHED = (1 << 20),
		FL_GRENADE = (1 << 21),
		FL_STEPMOVEMENT = (1 << 22),
		FL_DONTTOUCH = (1 << 23),
		FL_BASEVELOCITY = (1 << 24),
		FL_WORLDBRUSH = (1 << 25),
		FL_OBJECT = (1 << 26),
		FL_KILLME = (1 << 27),
		FL_ONFIRE = (1 << 28),
		FL_DISSOLVING = (1 << 29),
		FL_TRANSRAGDOLL = (1 << 30),
		FL_UNBLOCKABLE_BY_PLAYER = (1 << 31)
	};


	// Functions
	ClientClass* GetClientClass()
	{
		return vmt::callFunction<ClientClass*>(this + 0x8, 2);
	}

	bool IsDormant()
	{
		return vmt::callFunction<bool>(this + 0x8, 9);
	}

	const CVector& GetAbsOrigin()
	{
		return vmt::callFunction<const CVector&>(this, 10);
	}

	bool SetupBones(CMatrix3x4* out, int32_t max, int32_t mask, float currentTime)
	{
		return vmt::callFunction<bool>(this + 0x4, 13, out, max, mask, currentTime);
	}

	int GetTeam() {
		return vmt::callFunction<int>(this, 88);
	}

	int GetHealth() {
		return vmt::callFunction<int>(this, 122);
	}

	bool isAlive()
	{
		return vmt::callFunction<bool>(this, 156);
	}

	bool IsPlayer()
	{
		return  vmt::callFunction<bool>(this, 158);
	}

	CBaseEntity* GetActiveWeapon() {
		return vmt::callFunction<CBaseEntity*>(this, 268);
	}

	void GetEyePosition(CVector& eyePosition) 
	{
		vmt::callFunction<void>(this, 285, std::ref(eyePosition));
	}

	CBaseEntity* GetObserverTarget() 
	{
		return vmt::callFunction<CBaseEntity*>(this, 295);
	}

	void GetAimPunch(CVector& aimPunch)
	{
		vmt::callFunction<void>(this, 346, std::ref(aimPunch));
	}

	int GetWeaponType() 
	{
		return vmt::callFunction<int>(this, 455);
	}

	WeaponInfo* GetWeaponInfo() 
	{
		return vmt::callFunction<WeaponInfo*>(this, 461);
	}

	// Netvars
	int GetFlags(ClientClass* clientClass)
	{
		return *(int*)(this + netvars::GetNetvarOffset("DT_CSPlayer","m_fFlags",clientClass,"m_fFlags",0));
	}

	short GetWeaponId(ClientClass* clientClass) 
	{
		return *(short*)(this + netvars::GetNetvarOffset("DT_BaseCombatWeapon", "m_iItemDefinitionIndex", clientClass, "m_iItemDefinitionIndex", 0));
	}

	bool IsScoped(ClientClass* clientClass)
	{
		return *(bool*)(this + netvars::GetNetvarOffset("DT_CSPlayer", "m_bIsScoped", clientClass, "m_bIsScoped", 0));
	}

	// Other
	AnimState* GetAnimstate() noexcept
	{
		return *(AnimState**)(this + 0x3900);
	}

	float GetMaxDesyncAngle() noexcept
	{
		const auto animState = GetAnimstate();

		if (!animState)
			return 0.0f;

		float yawModifier = (animState->stopToFullRunningFraction * -0.3f - 0.2f) * std::clamp(animState->footSpeed, 0.0f, 1.0f) + 1.0f;

		if (animState->duckAmount > 0.0f)
			yawModifier += (animState->duckAmount * std::clamp(animState->footSpeed2, 0.0f, 1.0f) * (0.5f - yawModifier));

		return animState->velocitySubtractY * yawModifier;
	}

};



class IClientUnknown
{
public:

	CBaseEntity* GetBaseEntity()
	{
		return vmt::callFunction<CBaseEntity*>(this, 7);
	}
};

class IClientRenderable
{
public:
	IClientUnknown* GetIClientUnknown()
	{
		return vmt::callFunction<IClientUnknown*>(this, 0);
	}

	void DrawModel(int flags, int instance)
	{
		vmt::callFunction<void*>(this, 10, flags, instance);
	}
};
