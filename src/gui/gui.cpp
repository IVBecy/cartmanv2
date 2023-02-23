
#include "gui.h"

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_win32.h"
#include "../../imgui/imgui_impl_dx9.h"

#include "guiConfig.h"

// Window process handler
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


bool gui::makeWindowClass(const char* windowName) noexcept{
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = DefWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = windowName;
	wcex.hIconSm = NULL;

	if (!RegisterClassEx(&wcex)) {
		return false;
	}

	return true;
}

void gui::destroyHWindowClass() noexcept{
	UnregisterClass(wcex.lpszClassName, wcex.hInstance);
}

bool gui::setupWindow(const char* name) noexcept {
	window = CreateWindow(wcex.lpszClassName, name, WS_OVERLAPPEDWINDOW, 100, 100, 300, 250, 0, 0, wcex.hInstance, 0);

	if (!window) {
		return false;
	}

	return true;
}

void gui::destroyHWindow() noexcept{
	if (window) {
		DestroyWindow(window);
	}
}

bool gui::setupDirectX() noexcept{
	const HMODULE handle = GetModuleHandle("d3d9.dll");

	using createFunction = LPDIRECT3D9(__stdcall*)(UINT);
	if (!handle) {
		return false;
	}
	const auto create = (createFunction)(GetProcAddress(handle, "Direct3DCreate9"));

	d3d9 = create(D3D_SDK_VERSION);

	if (!create || !d3d9) {
		return false;
	}	

	D3DPRESENT_PARAMETERS params = { };
	params.BackBufferWidth = 0;
	params.BackBufferHeight = 0;
	params.BackBufferFormat =  D3DFMT_UNKNOWN;
	params.BackBufferCount = 0;
	params.MultiSampleType = D3DMULTISAMPLE_NONE;
	params.MultiSampleQuality = NULL;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.hDeviceWindow = window;
	params.Windowed = 1;
	params.EnableAutoDepthStencil = 0;
	params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
	params.Flags = NULL;
	params.FullScreen_RefreshRateInHz = 0;
	params.PresentationInterval = 0;

	if (d3d9->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_NULLREF,window,D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &params, &device) < 0) {
		return false;
	}

	return true;
}

void gui::destroyDirectX() noexcept{
	if (device) {
		device->Release();
		device = NULL;
	}
	if (d3d9) {
		d3d9->Release();
		d3d9 = NULL;
	}
}

void gui::setup(){
	makeWindowClass("CartmanClass");
	setupWindow("Cartman");
	setupDirectX();

	destroyHWindow();
	destroyHWindowClass();
}

void gui::setupMenu(LPDIRECT3DDEVICE9 device) noexcept{
	auto params = D3DDEVICE_CREATION_PARAMETERS{ };
	device->GetCreationParameters(&params);

	// Game window
	window = params.hFocusWindow;
	ogWindowProc = (WNDPROC)(SetWindowLongPtr(window,GWLP_WNDPROC,(LONG_PTR)(WndProc)));

	// IMGUI
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
	io.IniFilename = NULL;

	// Fonts
	fonts::calibri = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\calibri.ttf", 15.5f);
	fonts::calibriTitle = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\calibri.ttf", 25.f);
	fonts::calibriMenuItem = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\calibri.ttf", 17.5f);


	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);

	setupDone = true;
}

void gui::destroyMenu() noexcept{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	SetWindowLongPtr(window,GWLP_WNDPROC, (LONG_PTR)(ogWindowProc));
	destroyDirectX();
}

void gui::render() noexcept{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(300,300), ImGuiCond_Once | ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(650, 500));

	ImGui::PushFont(fonts::calibri);
	ImGui::Begin("Cartman", &show, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	render::Menu();
	
	ImGui::End();
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	// Toggle the imgui menu
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		gui::show = !gui::show;
	}

	// Window process when menu is open
	if (gui::show && ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) {
		return 1L;
	}	

	// Call our window
	return CallWindowProc(gui::ogWindowProc, hWnd, message, wParam, lParam);
}
