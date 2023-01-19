#include "../valve/cusercmd.h"
#include "../valve/cvector.h"

namespace aim {
	// Cheat functions
	int getAimbotBone(const char* choice);
	void aimbot(CUserCmd* cmd);
	void rcs(CUserCmd* cmd, CVector& oldPunch);
	void trigger(CUserCmd* cmd);

	// Util functions
	CVector normalizeAngles(CVector angles);
	CVector clampAngles(CVector angles);
	void fixMove(CUserCmd* cmd, const CVector& previousViewAngles, const CVector& currentViewAngles, float oldF, float oldS);
	bool gunCheck(int id);
}


// Setup oldPunch
namespace _rcs {
	inline CVector oldPunch{ };
}