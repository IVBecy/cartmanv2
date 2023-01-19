#pragma once
#include "cmatrix.h"
#include "CVector.h"
#include "imaterialsystem.h"
#include "modelrender.h"

#include "../helpers/vmt.h"

class Material;


struct Model {
	void* handle;
	char name[260];
	int	loadFlags;
	int	serverCount;
	int	type;
	int	flags;
	CVector mins, maxs;
};


enum BoneIndex : int
{
	BONE_INVALID = -1,
	BONE_PELVIS,
	BONE_LEAN_ROOT,
	BONE_CAM_DRIVER,
	BONE_SPINE_0,
	BONE_SPINE_1,
	BONE_SPINE_2,
	BONE_SPINE_3,
	BONE_NECK,
	BONE_HEAD,
	BONE_CLAVICLE_L,
	BONE_ARM_UPPER_L,
	BONE_ARM_LOWER_L,
	BONE_HAND_L,
	BONE_FINGER_MIDDLE_META_L,
	BONE_FINGER_MIDDLE_0_L,
	BONE_FINGER_MIDDLE_1_L,
	BONE_FINGER_MIDDLE_2_L,
	BONE_FINGER_PINKY_META_L,
	BONE_FINGER_PINKY_0_L,
	BONE_FINGER_PINKY_1_L,
	BONE_FINGER_PINKY_2_L,
	BONE_FINGER_INDEX_META_L,
	BONE_FINGER_INDEX_0_L,
	BONE_FINGER_INDEX_1_L,
	BONE_FINGER_INDEX_2_L,
	BONE_FINGER_THUMB_0_L,
	BONE_FINGER_THUMB_1_L,
	BONE_FINGER_THUMB_2_L,
	BONE_FINGER_RING_META_L,
	BONE_FINGER_RING_0_L,
	BONE_FINGER_RING_1_L,
	BONE_FINGER_RING_2_L,
	BONE_WEAPON_HAND_L,
	BONE_ARM_LOWER_L_TWIST,
	BONE_ARM_LOWER_L_TWIST1,
	BONE_ARM_UPPER_L_TWIST,
	BONE_ARM_UPPER_L_TWIST1,
	BONE_CLAVICLE_R,
	BONE_ARM_UPPER_R,
	BONE_ARM_LOWER_R,
	BONE_HAND_R,
	BONE_FINGER_MIDDLE_META_R,
	BONE_FINGER_MIDDLE_0_R,
	BONE_FINGER_MIDDLE_1_R,
	BONE_FINGER_MIDDLE_2_R,
	BONE_FINGER_PINKY_META_R,
	BONE_FINGER_PINKY_0_R,
	BONE_FINGER_PINKY_1_R,
	BONE_FINGER_PINKY_2_R,
	BONE_FINGER_INDEX_META_R,
	BONE_FINGER_INDEX_0_R,
	BONE_FINGER_INDEX_1_R,
	BONE_FINGER_INDEX_2_R,
	BONE_FINGER_THUMB_0_R,
	BONE_FINGER_THUMB_1_R,
	BONE_FINGER_THUMB_2_R,
	BONE_FINGER_RING_META_R,
	BONE_FINGER_RING_0_R,
	BONE_FINGER_RING_1_R,
	BONE_FINGER_RING_2_R,
	BONE_WEAPON_HAND_R,
	BONE_ARM_LOWER_R_TWIST,
	BONE_ARM_LOWER_R_TWIST1,
	BONE_ARM_UPPER_R_TWIST,
	BONE_ARM_UPPER_R_TWIST1,
	BONE_LEG_UPPER_L,
	BONE_LEG_LOWER_L,
	BONE_ANKLE_L,
	BONE_BALL_L,
	BONE_LFOOT_LOCK,
	BONE_LEG_UPPER_L_TWIST,
	BONE_LEG_UPPER_L_TWIST1,
	BONE_LEG_UPPER_R,
	BONE_LEG_LOWER_R,
	BONE_ANKLE_R,
	BONE_BALL_R,
	BONE_RFOOT_LOCK,
	BONE_LEG_UPPER_R_TWIST,
	BONE_LEG_UPPER_R_TWIST1,
	BONE_FINGER_PINKY_L_END,
	BONE_FINGER_PINKY_R_END,
	BONE_VALVEBIPED_WEAPON_BONE,
	BONE_LH_IK_DRIVER,
	BONE_PRIMARY_JIGGLE_JNT,
};

enum RenderFlags : unsigned int
{
	RENDER_FLAGS_DISABLE_RENDERING = 0x01,
	RENDER_FLAGS_HASCHANGED = 0x02,
	RENDER_FLAGS_ALTERNATE_SORTING = 0x04,
	RENDER_FLAGS_RENDER_WITH_VIEWMODELS = 0x08,
	RENDER_FLAGS_BLOAT_BOUNDS = 0x10,
	RENDER_FLAGS_BOUNDS_VALID = 0x20,
	RENDER_FLAGS_BOUNDS_ALWAYS_RECOMPUTE = 0x40,
	RENDER_FLAGS_IS_SPRITE = 0x80,
	RENDER_FLAGS_FORCE_OPAQUE_PASS = 0x100,
};

enum HitboxIndex : int
{
	HITBOX_INVALID = -1,
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_PELVIS,
	HITBOX_STOMACH,
	HITBOX_THORAX,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};

struct StudioBbox
{
	int bone;
	int group;
	CVector bbMin;
	CVector bbMax;
	int hitboxNameIndex;
	CVector offsetOrientation;
	float capsuleRadius;
	int	unused[4];

	inline const char* GetHitboxName() const
	{
		if (!hitboxNameIndex) return nullptr;
		return (const char*)this + hitboxNameIndex;
	}
};

struct StudioHitboxSet
{
	int nameIndex;
	int numHitboxes;
	int hitboxIndex;

	const char* GetName() noexcept
	{
		return nameIndex ? reinterpret_cast<const char*>(uintptr_t(this) + nameIndex) : nullptr;
	}

	StudioBbox* GetHitbox(int i) noexcept
	{
		return i >= 0 && i < numHitboxes ? reinterpret_cast<StudioBbox*>(uintptr_t(this) + hitboxIndex) + i : nullptr;
	}
};

struct StudioBone
{
	int nameIndex;
	int	parent;
	std::byte pad0[152];
	int flags;
	std::byte pad2[52];

	const char* GetName() const noexcept
	{
		return nameIndex ? reinterpret_cast<const char*>(uintptr_t(this) + nameIndex) : nullptr;
	}
};

struct StudioHdr
{
	int id;
	int version;
	int checksum;
	char name[64];
	int length;
	CVector eyePosition;
	CVector illumPosition;
	CVector hullMin;
	CVector hullMax;
	CVector bbMin;
	CVector bbMax;
	int flags;
	int numBones;
	int boneIndex;
	int numBoneControllers;
	int boneControllerIndex;
	int numHitboxSets;
	int hitboxSetIndex;
	int	localAnimations;
	int	localAnimationIndex;
	int localSequences;
	int localSequenceIndex;

	const StudioBone* GetBone(int i) const noexcept
	{
		return i >= 0 && i < numBones ? reinterpret_cast<StudioBone*>(uintptr_t(this) + boneIndex) + i : nullptr;
	}

	StudioHitboxSet* GetHitboxSet(int i) noexcept
	{
		return i >= 0 && i < numHitboxSets ? reinterpret_cast<StudioHitboxSet*>(uintptr_t(this) + hitboxSetIndex) + i : nullptr;
	}
};

enum RenderableTranslucencyType
{
	RENDERABLE_IS_OPAQUE = 0,
	RENDERABLE_IS_TRANSLUCENT,
	RENDERABLE_IS_TWO_PASS,	// has both translucent and opaque sub-partsa
};

using MDLHandle = unsigned short;

struct Collide;
struct VirtualModel;
struct CombinerModelInput;

class UtlBuffer;

class ModelLoadCallback
{
public:
	virtual void OnModelLoadComplete(const Model * pModel) = 0;

protected:
	// Protected destructor so that nobody tries to delete via this interface.
	// Automatically unregisters if the callback is destroyed while still pending.
	//~ModelLoadCallback();
};

class ModelInfo
{
public:
	char* GetModelName(const Model* model)
	{
		return vmt::callFunction<char*>(this,3,model);
	}
};

class ModelInfoClient : public ModelInfo
{
public:
};
