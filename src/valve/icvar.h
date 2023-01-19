#pragma once
#include "../helpers/vmt.h"

#define FCVAR_NONE					0

#define FCVAR_UNREGISTERED			(1<<0)
#define FCVAR_DEVELOPMENTONLY		(1<<1)
#define FCVAR_GAMEDLL				(1<<2)
#define FCVAR_CLIENTDLL				(1<<3)
#define FCVAR_HIDDEN				(1<<4)

#define FCVAR_PROTECTED				(1<<5)
#define FCVAR_SPONLY				(1<<6)
#define FCVAR_ARCHIVE				(1<<7)
#define FCVAR_NOTIFY				(1<<8)
#define FCVAR_USERINFO				(1<<9)
#define FCVAR_CHEAT					(1<<14)

#define FCVAR_PRINTABLEONLY			(1<<10)
#define FCVAR_UNLOGGED				(1<<11)
#define FCVAR_NEVER_AS_STRING		(1<<12)
#define FCVAR_RELEASE				(1<<19)

#define FCVAR_REPLICATED			(1<<13)
#define FCVAR_DEMO					(1<<16)
#define FCVAR_DONTRECORD			(1<<17)

#define FCVAR_NOT_CONNECTED			(1<<22)
#define FCVAR_ARCHIVE_XBOX			(1<<24)
#define FCVAR_SERVER_CAN_EXECUTE	(1<<28)
#define FCVAR_SERVER_CANNOT_QUERY	(1<<29)
#define FCVAR_CLIENTCMD_CAN_EXECUTE	(1<<30)


class ConVar
{
public:
	float GetFloat()
	{
		return vmt::callFunction<float>(this, 12);
	}

	int GetInt()
	{
		return vmt::callFunction<int>(this, 13);
	}

	void SetValue(const char* value)
	{
		vmt::callFunction<const char*>(this, 14,value);
	}

	void SetValue(float value)
	{
		vmt::callFunction<float>(this, 15,value);
	}

	void SetValue(int value)
	{
		vmt::callFunction<int>(this, 16,value);
	}


	char pad_0x0000[0x4]; //0x0000
	ConVar* pNext; //0x0004
	int32_t bRegistered; //0x0008
	char* pszName; //0x000C
	char* pszHelpString; //0x0010
	int32_t nFlags; //0x0014
	char pad_0x0018[0x4]; //0x0018
	ConVar* pParent; //0x001C
	char* pszDefaultValue; //0x0020
	char* strString; //0x0024
	int32_t StringLength; //0x0028
	float fValue; //0x002C
	int32_t nValue; //0x0030
	int32_t bHasMin; //0x0034
	float fMinVal; //0x0038
	int32_t bHasMax; //0x003C
	float fMaxVal; //0x0040
	void* fnChangeCallback; //0x0044
};

class ICvar
{
public:
	ConVar* FindVar(const char *var)
	{
		return vmt::callFunction<ConVar*>(this, 15,var);
	}
};
