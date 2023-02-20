#pragma once

#include "../global/config.h"
#include "../global/vars.h"

#include "guiConfig.h"


// Styling
ImGuiStyle* guiStyles::setupStyles() {
	ImGuiStyle* style = &ImGui::GetStyle();

	// Frame
	style->FramePadding = ImVec2(8, 6);
	style->FrameRounding = 12;

	// Tabs
	style->Colors[ImGuiCol_Tab] = ImColor(0, 50, 75, 255);
	style->Colors[ImGuiCol_TabActive] = guiVars::lightBlue;
	style->Colors[ImGuiCol_TabHovered] = ImColor(0, 60, 85, 255);
	style->TabRounding = 4;

	// Button Styles
	style->ButtonTextAlign = ImVec2(0, 0.5);
	style->Colors[ImGuiCol_Button] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_ButtonActive] = guiVars::darkBlue;
	style->Colors[ImGuiCol_ButtonHovered] = guiVars::darkBlue;

	style->Colors[ImGuiCol_FrameBg] = guiVars::darkBlue;
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor(0, 35, 62, 255);
	style->Colors[ImGuiCol_CheckMark] = guiVars::lightBlue;

	// Grab and sliders
	style->GrabRounding = 30;
	style->GrabMinSize = 30;
	style->Colors[ImGuiCol_SliderGrabActive] = guiVars::lightBlue;
	style->Colors[ImGuiCol_SeparatorHovered] = guiVars::lightBlue;

	// Scrollbar
	style->ScrollbarRounding = 12;

	// Background
	style->Colors[ImGuiCol_WindowBg] = guiVars::menuBackground;
	style->Colors[ImGuiCol_ChildBg] = guiVars::childBackground;

	return style;
}

// Main menu
void render::Menu() {

	/************************************** SETUP *********************************************/
	ImGuiStyle* styles = guiStyles::setupStyles();
	ImGui::Columns(2, "MAIN");
	ImGui::SetColumnOffset(1, guiVars::menuButton.x + 25);

	/************************************** TITLE *********************************************/
	ImGui::PushFont(fonts::calibriTitle);
	ImGui::SetCursorPosX((guiVars::menuButton.x + 25 - ImGui::CalcTextSize("CARTMAN").x) * 0.5f);
	ImGui::Text("CARTMAN");
	ImGui::PopFont();

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	/************************************** MENU *********************************************/
	ImGui::PushFont(fonts::calibriMenuItem);
	if (ImGui::Button("Visuals", guiVars::menuButton)) {
		gui::tabCounter = 0;
	}
	ImGui::Spacing();
	if (ImGui::Button("ESP", guiVars::menuButton)) {
		gui::tabCounter = 1;
	}
	ImGui::Spacing();
	if(ImGui::Button("Aim", guiVars::menuButton)){
		gui::tabCounter = 2;
	}
	
	ImGui::Spacing();
	if (ImGui::Button("Miscallenous", guiVars::menuButton)) {
		gui::tabCounter = 3;
	}
	ImGui::PopFont();

	ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
	ImGui::Text(vars::_v);

	ImGui::NextColumn();
	/************************************** TABS *********************************************/
	
	switch (gui::tabCounter) {
		case 0:
			render::tabs::Visuals();
			break;
		case 1:
			render::tabs::Esp();
			break;
		case 2:
			render::tabs::Aim();
			break;
		case 3:
			render::tabs::Misc();
			break;
		default:
			render::tabs::Visuals();
			break;
	}

	ImGui::Columns();
}

// Tabs
void render::tabs::Visuals() {
	ImVec2 avail = ImGui::GetContentRegionAvail();
	// Chams
	ImGui::BeginChild("Chams", ImVec2(avail.y, guiVars::childSize + 50), true);
	ImGui::Text("Enemy Chams");
	ImGui::Separator();
	ImGui::Combo("Enemy material", &config::visuals::chams::enemymaterial, config::visuals::chams::material, 5);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Visible layer", &config::visuals::chams::__visibleColoursEnemy);
	ImGui::SameLine();
	ImGui::ColorEdit3("Visible colours", (float*)&config::visuals::chams::visibleColoursEnemy, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Hidden layer", &config::visuals::chams::__hiddenColoursEnemy);
	ImGui::SameLine();
	ImGui::ColorEdit3("Hidden colours", (float*)&config::visuals::chams::hiddenColoursEnemy, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
	ImGui::EndChild();

	// Sky colour
	ImGui::BeginChild("Sky settings", ImVec2(avail.y, guiVars::childSize), true);
	ImGui::Text("Sky");
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Sky colour", &config::visuals::skyColour);
	ImGui::SameLine();
	ImGui::ColorEdit3("Colour", (float*)&config::visuals::skyColours, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Enable sky boxes", &config::visuals::skyEnable);
	ImGui::Spacing();
	ImGui::Combo("Sky boxes", &config::visuals::skyNew, config::visuals::skyBoxes, 24);
	ImGui::EndChild();
}

// ESP
void render::tabs::Esp() {
	ImVec2 avail = ImGui::GetContentRegionAvail();
	ImGui::BeginChild("Box ESP", ImVec2(avail.y, guiVars::childSize + 150), true);
	ImGui::Text("Box ESP");
	ImGui::Separator();
	ImGui::Checkbox("Enabled", &config::esp::enable);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Box", &config::esp::Box);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Health bar", &config::esp::BoxHealth);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Show names", &config::esp::showName);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Reveal gun", &config::esp::showGun);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Snap lines", &config::esp::snapLines);
	ImGui::EndChild();
	ImGui::EndTabItem();
}

// AIM
void render::tabs::Aim() {
	ImVec2 avail = ImGui::GetContentRegionAvail();
	ImGui::BeginChild("AimBot", ImVec2(avail.y, guiVars::childSize + 150), true);
	ImGui::Text("Aimbot");
	ImGui::Separator();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("When RCS is selected (see misc)\nsilent aimbot won't work!");
	}
	ImGui::Checkbox("Enabled", &config::aim::aimbot);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::SliderFloat("FOV", &config::aim::fov, 0.5f, 89.f);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Combo("Hit box", &config::aim::hitBoxChoice, config::aim::hitboxes, 4);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Silent", &config::aim::silent);
	ImGui::Spacing();
	ImGui::Spacing();
	if (!config::aim::silent) {
		ImGui::SliderFloat("Smoothing", &config::aim::smooth, 0.f, 10.f);
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Checkbox("Auto-lock", &config::aim::autoLock);
	}
	ImGui::EndChild();

	ImGui::BeginChild("Other aim", ImVec2(avail.y, guiVars::childSize - 25), true);
	ImGui::Text("Other aim");
	ImGui::Separator();
	ImGui::Checkbox("Recoil compensation", &config::aim::rcs);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Trigger bot", &config::aim::trigger);
	ImGui::EndChild();
}

// MISC
void render::tabs::Misc() {
	ImVec2 avail = ImGui::GetContentRegionAvail();
	ImGui::BeginChild("Weapon related", ImVec2(avail.y, guiVars::childSize), true);
	ImGui::Text("Weapon related");
	ImGui::Separator();
	ImGui::Checkbox("No flash", &config::misc::noFlash);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Grenade path", &config::misc::nadeTraject);
	ImGui::EndChild();

	ImGui::BeginChild("Other", ImVec2(avail.y, guiVars::childSize + 100), true);
	ImGui::Text("Other");
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Checkbox("Bunny hop", &config::misc::bunnyHop);
	ImGui::Spacing();
	ImGui::Checkbox("Auto strafe", &config::misc::autostrafe);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Sniper crosshair", &config::misc::showSniperCrosshair);
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Checkbox("Hit marker", &config::visuals::hitMarkerToggle);
	ImGui::EndTabItem();
	ImGui::EndChild();
}