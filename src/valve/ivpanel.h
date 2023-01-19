#pragma once
#include "../helpers/vmt.h"

class IVPanel
{
public:
	const char* GetName(int panel)
	{
		return vmt::callFunction<const char*>(this, 36, panel);
	}
};