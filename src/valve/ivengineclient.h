#pragma once

#include "../helpers/vmt.h"

#include "cvector.h"
#include "networkchannel.h"

struct PlayerInfo {
    std::uint64_t version;
    union {
        std::uint64_t xuid;
        struct {
            std::uint32_t xuidLow;
            std::uint32_t xuidHigh;
        };
    };
    char name[128];
    int userId;
    char guid[33];
    std::uint32_t friendsId;
    char friendsName[128];
    bool fakeplayer;
    bool hltv;
    int customfiles[4];
    unsigned char filesdownloaded;
    int entityIndex;
};

class IVEngineClient {
public:
    void GetScreenSize(int& width, int& height)
    {
        vmt::callFunction<void, int&, int&>(this, 5, width, height);
    }

    bool GetPlayerInfo(int entityIndex, PlayerInfo& playerInfo) 
    {
        return vmt::callFunction<bool, int, PlayerInfo&>(this, 8, entityIndex, playerInfo);
    }
    
    int GetPlayerForUserID(int uid)
    {
        return vmt::callFunction<int>(this, 9, uid);
    }
	
    int GetLocalPlayerIndex() 
	{
		return vmt::callFunction<int>(this,12);
	}

    void GetViewAngles(CVector& angles)
    {
        vmt::callFunction<void, CVector&>(this, 18, angles);
    }

    void SetViewAngles(const CVector& viewAngles)
    {
        vmt::callFunction<void, const CVector&>(this, 19, viewAngles);
    }

	bool IsInGame()
	{
		return vmt::callFunction<bool>(this, 26);
	}

    NetworkChannel* GetNetworkChannel()
    {
        return vmt::callFunction<NetworkChannel*>(this, 78);
    }
};