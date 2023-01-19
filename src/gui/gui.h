#pragma once

#include "../../imgui/imgui.h"

#include <d3d9.h>

namespace gui
{
	inline int tabCounter = 0;

	inline bool show = true;

	inline bool setupDone = false;

	inline HWND window = nullptr;
	inline WNDCLASSEX wcex = { };
	inline WNDPROC ogWindowProc = nullptr;

	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline LPDIRECT3D9 d3d9 = nullptr;

	bool  makeWindowClass(const char* windowName) noexcept;
	void destroyHWindowClass() noexcept;

	bool setupWindow(const char* name) noexcept;
	void destroyHWindow() noexcept;

	bool setupDirectX() noexcept;
	void destroyDirectX() noexcept;

	void setup();

	void setupMenu(LPDIRECT3DDEVICE9 device) noexcept;
	void destroyMenu() noexcept;

	void render() noexcept;
}