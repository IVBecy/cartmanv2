#pragma once
#include "../helpers/vmt.h"

typedef unsigned short MaterialHandle_t;
class RenderContext;
class CKeyValues { };

class IMaterial
{
public:
	enum EMaterialVarFlag : int32_t
	{
		IGNOREZ = 1 << 15,
		WIREFRAME = 1 << 28,
		MATERIAL_VAR_NO_DRAW = 1 << 2,
	};

	const char* GetTextureGroupName() 
	{
		return vmt::callFunction<const char*>(this, 1);
	}

	 void ColorModulate(float r, float g, float b) 
	 {
		 vmt::callFunction<float>(this, 28, r, g, b);
	 }

	 void ColorModulate(float colours[3]) 
	 {
		 vmt::callFunction<float>(this, 28, colours[0], colours[1], colours[2]);
	 }

	 void SetMaterialVarFlag(const int32_t flag, const bool on) noexcept
	 {
		 vmt::callFunction<void>(this, 29, flag, on);
	 }

	 bool IsPrecached() 
	 {
		 return vmt::callFunction<bool>(this, 70);
	 }
};


class IMaterialSystem
{
public:
	  IMaterial* CreateMaterial(const char* name, CKeyValues* kv) noexcept
	{
		return vmt::callFunction<IMaterial*>(this, 83, name, kv);
	}

	  IMaterial* FindMaterial(const char* name) noexcept
	{
		return vmt::callFunction<IMaterial*>(this, 84, name, nullptr, true, nullptr);
	}

	 MaterialHandle_t FirstMaterial() noexcept
	{
		return vmt::callFunction<MaterialHandle_t>(this, 86);
	}

	 MaterialHandle_t NextMaterial(MaterialHandle_t handle) noexcept
	{
		return vmt::callFunction<MaterialHandle_t>(this, 87,handle);
	}

	 MaterialHandle_t InvalidMaterial() noexcept
	 {
		 return vmt::callFunction<MaterialHandle_t>(this, 88);
	 }

	 IMaterial* GetMaterial(MaterialHandle_t handle) noexcept
	 {
		 return vmt::callFunction<IMaterial*>(this, 89, handle);
	 }

	 RenderContext* GetRenderContext()
	 {
		 return vmt::callFunction<RenderContext*>(this, 115);
	 }
};
