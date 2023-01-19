#pragma once
#include "cbaseentity.h"
#include "cvector.h"
#include "cutlvector.h"

class GlowObject {
public:
	CBaseEntity* entity;
	CVector glowColor;
	float   alpha;
	std::byte pad[4];
	float   m_flSomeFloat;
	float   bloomAmount;
	float   m_flAnotherFloat;
	bool    renderWhenOccluded;
	bool    renderWhenUnoccluded;
	bool    fullBloomRender;
	std::byte pad1;
	int fullBloomStencilTestValue;
	int glowStyle;
	int splitScreenSlot;
	int nextFreeSlot;

	bool IsUnused() {
		return nextFreeSlot != ENTRY_IN_USE;
	}

	static constexpr int END_OF_FREE_LIST = -1;
	static constexpr int ENTRY_IN_USE = -2;

};
class GlowObjectManager {
public:
		CUtlVector<GlowObject> glowObjects;
};


