#pragma once
#include "gui.h"

#include "../../imgui/imgui.h"

// Fonts
namespace fonts {
	inline ImFont* calibriTitle;
	inline ImFont* calibriMenuItem;
	inline ImFont* calibri;
}

// Vars for elements
namespace guiVars {
	// Background colors
	inline ImColor menuBackground = ImColor(25, 25, 25, 200);
	inline ImColor childBackground = ImColor(25, 25, 25, 170);

	// Normal Colours
	inline ImColor lightBlue = ImColor(58, 169, 255, 255);
	inline ImColor darkBlue = ImColor(24, 31, 42, 255);
	inline ImColor midBlue = ImColor(32, 44, 60, 255);

	// Sizes
	inline ImVec2 menuButton = ImVec2(150, 60);
	inline float childSize = 200.f;
}

// Styling
namespace guiStyles{
	ImGuiStyle* setupStyles();
}

// Rendered views
namespace render {
	// Menu items
	void Menu();

	// Tabs
	namespace tabs {
		void Visuals();
		void Esp();
		void Aim();
		void Misc();
	}
}