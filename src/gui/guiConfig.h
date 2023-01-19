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
	inline ImColor lightBlue = ImColor(0, 175, 215, 170);
	inline ImColor darkBlue = ImColor(0, 0, 0, 170);
	inline ImColor black = ImColor(0, 0, 0, 255);

	inline ImColor hover = ImColor(25, 25, 25, 170);

	// Sizes
	inline ImVec2 menuButton = ImVec2(150, 40);
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