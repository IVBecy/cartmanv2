#pragma once
#include <stdint.h>
#include "../helpers/vmt.h"

enum EVGuiPanel
{
	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};

class IEngineVGui
{
public:
	uintptr_t GetPanel(int type)
	{
		return vmt::callFunction<uintptr_t>(this, 1, type);
	}
};