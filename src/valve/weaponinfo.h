// https://github.com/danielkrupinski/GOESP/blob/master/GOESP/SDK/WeaponInfo.h
// https://github.com/designer1337/csgo-cheat-base/blob/master/source-sdk/structs/weaponinfo.hpp
#pragma once

enum EWeaponType : int
{
    WEAPONTYPE_KNIFE = 0,
    WEAPONTYPE_PISTOL = 1,
    WEAPONTYPE_SUBMACHINEGUN = 2,
    WEAPONTYPE_RIFLE = 3,
    WEAPONTYPE_SHOTGUN = 4,
    WEAPONTYPE_SNIPER = 5,
    WEAPONTYPE_MACHINEGUN = 6,
    WEAPONTYPE_C4 = 7,
    WEAPONTYPE_PLACEHOLDER = 8,
    WEAPONTYPE_GRENADE = 9,
    WEAPONTYPE_HEALTHSHOT = 11,
    WEAPONTYPE_FISTS = 12,
    WEAPONTYPE_BREACHCHARGE = 13,
    WEAPONTYPE_BUMPMINE = 14,
    WEAPONTYPE_TABLET = 15,
    WEAPONTYPE_MELEE = 16
};

enum class WeaponType {
    Knife = 0,
    Pistol,
    SubMachinegun,
    Rifle,
    Shotgun,
    SniperRifle,
    Machinegun,
    C4,
    Placeholder,
    Grenade,
    Unknown,
    StackableItem,
    Fists,
    BreachCharge,
    BumpMine,
    Tablet,
    Melee
};

enum EItemDefinitionIndex {
    weapon_deagle = 1,
    weapon_elite = 2,
    weapon_fiveseven = 3,
    weapon_glock = 4,
    weapon_ak47 = 7,
    weapon_aug = 8,
    weapon_awp = 9,
    weapon_famas = 10,
    weapon_g3sg1 = 11,
    weapon_galilar = 13,
    weapon_m249 = 14,
    weapon_m4a1 = 16,
    weapon_mac10 = 17,
    weapon_p90 = 19,
    weapon_ump = 24,
    weapon_xm1014 = 25,
    weapon_bizon = 26,
    weapon_mag7 = 27,
    weapon_negev = 28,
    weapon_sawedoff = 29,
    weapon_tec9 = 30,
    weapon_taser = 31,
    weapon_hkp2000 = 32,
    weapon_mp7 = 33,
    weapon_mp9 = 34,
    weapon_nova = 35,
    weapon_p250 = 36,
    weapon_scar20 = 38,
    weapon_sg556 = 39,
    weapon_ssg08 = 40,
    weapon_knife = 42,
    weapon_flashbang = 43,
    weapon_hegrenade = 44,
    weapon_smokegrenade = 45,
    weapon_molotov = 46,
    weapon_decoy = 47,
    weapon_incgrenade = 48,
    weapon_c4 = 49,
    weapon_knife_t = 59,
    weapon_m4a1_silencer = 60,
    weapon_usp_silencer = 61,
    weapon_cz75a = 63,
    weapon_revolver = 64,
    weapon_bayonet = 500,
    weapon_knife_flip = 505,
    weapon_knife_gut = 506,
    weapon_knife_karambit = 507,
    weapon_knife_m9_bayonet = 508,
    weapon_knife_tactical = 509,
    weapon_knife_falchion = 512,
    weapon_knife_survival_bowie = 514,
    weapon_knife_butterfly = 515,
    weapon_knife_push = 516
};

inline const char* GetWeaponNameFromId(short id) {
    switch (id) {
    case weapon_deagle:         return "Desert Eagle";
    case weapon_elite:          return "Dual-Elites";
    case weapon_fiveseven:      return "Five-Seven";
    case weapon_glock:          return "Glock";
    case weapon_ak47:           return "AK-47";
    case weapon_aug:            return "AUG";
    case weapon_awp:            return "AWP";
    case weapon_famas:          return "Famas";
    case weapon_g3sg1:          return "G3SG1";
    case weapon_galilar:        return "Galil";
    case weapon_m249:           return "M249";
    case weapon_m4a1:           return "M4A4";
    case weapon_mac10:          return "MAC-10";
    case weapon_p90:            return "P90";
    case weapon_ump:            return "UMP";
    case weapon_xm1014:         return "XM1014";
    case weapon_bizon:          return "PP-Bizon";
    case weapon_mag7:           return "Mag7";
    case weapon_negev:          return "Negev";
    case weapon_sawedoff:       return "Sawed-off";
    case weapon_tec9:           return "Tec9";
    case weapon_taser:          return "Zeus";
    case weapon_hkp2000:        return "P2000";
    case weapon_mp7:            return "MP7";
    case weapon_mp9:            return "MP9";
    case weapon_nova:           return "Nova";
    case weapon_p250:           return "P-250";
    case weapon_scar20:         return "Scar20";
    case weapon_sg556:          return "SG556";
    case weapon_ssg08:          return "SSG-08";
    case weapon_flashbang:      return "Flashbang";
    case weapon_hegrenade:      return "HE Granade";
    case weapon_smokegrenade:   return "Smoke";
    case weapon_molotov:        return "Molotov";
    case weapon_decoy:          return "Decoy";
    case weapon_incgrenade:     return "Incendiary";
    case weapon_c4:             return "C4";
    case weapon_m4a1_silencer:  return "M4A1-S";
    case weapon_usp_silencer:   return "USP-S";
    case weapon_cz75a:          return "CZ-75a";
    case weapon_revolver:       return "Revolver";
    case weapon_bayonet:
    case weapon_knife:
    case weapon_knife_t:
    case weapon_knife_flip:
    case weapon_knife_gut:
    case weapon_knife_karambit:
    case weapon_knife_m9_bayonet:
    case weapon_knife_tactical:
    case weapon_knife_falchion:
    case weapon_knife_survival_bowie:
    case weapon_knife_butterfly:
    case weapon_knife_push:
        return "Knife";
    default:
        return "Unknown";
    }
}

class WeaponInfo {
public:
	char		u0[0x4];
	char* weapon_name;
	char		u1[0xC];
	__int32		weapon_max_clip;
	char		u2[0xC];
	__int32		weapon_max_reserved_ammo;
	char		u3[0x4];
	char* weapon_model_path;
	char* weapon_model_path_alt;
	char* weapon_dropped_model_path;
	char* weapon_default_clip;
	char		u4[0x44];
	char* weapon_bullet_type;
	char		u5[0x4];
	char* weapon_hud_name;
	char* weapon_name_alt;
	char		u6[0x38];
	__int32		weapon_type;
	__int32		weapon_type_alt;
	__int32		weapon_price;
	__int32		weapon_reward;
	char* weapon_type_name;
	float		weapon_unknown_float;
	char		u7[0xC];
	unsigned char	weapon_full_auto;
	char		u8[0x3];
	__int32		weapon_damage;
	float		weapon_armor_ratio;
	__int32		weapon_bullets;
	float		weapon_penetration;
	char		u9[0x8];
	float		weapon_range;
	float		weapon_range_mod;
	float		weapon_throw_velocity;
	char		u10[0xC];
	unsigned char	weapon_has_silencer;
	char		u11[0xF];
	float		weapon_max_speed;
	float		weapon_max_speed_alt;
	float		weapon_attack_move_factor;
	float		weapon_spread;
	float		weapon_spread_alt;
	float		weapon_inaccuracy_crouch;
	float		weapon_inaccuracy_crouch_alt;
	float		weapon_inaccuracy_stand;
	float		weapon_inaccuracy_stand_alt;
	float		weapon_inaccuracy_jump;
	float		weapon_inaccuracy_jump_alt;
	char		u12[0x28];
	__int32		weapon_recoil_seed;
	char		u13[0x68];
	char* weapon_traces_type;
};
