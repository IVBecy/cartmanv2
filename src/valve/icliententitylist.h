#pragma once
#include "../helpers/vmt.h"

#include "CBaseentity.h" 

class IClientEntityList
{
public:
	virtual void* GetClientNetworkable(int entnum) = 0;
	virtual void* GetClientNetworkableFromHandle(unsigned long hEnt) = 0;
	virtual void* GetClientUnknownFromHandle(unsigned long hEnt) = 0;
	virtual void* GetClientEntity(int entnum) = 0;
	virtual void* GetClientEntityFromHandle(unsigned long hEnt) = 0;
	virtual int	NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int	GetHighestEntityIndex(void) = 0;
	virtual void SetMaxEntities(int maxents) = 0;
	virtual int	GetMaxEntities() = 0;

	//Used functions
	CBaseEntity* GetEntityFromIndex(int index) 
	{
		return vmt::callFunction<CBaseEntity*>(this, 3, index);
	}
};