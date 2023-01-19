#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "./hooks/hooks.h"

void mainThread(HMODULE hModule) {

    gui::setup();
    hooks::setup();

    // Panic
    while (!GetAsyncKeyState(VK_END)) {
        Sleep(200);
    }

    hooks::destroy();
    gui::destroyMenu();
    FreeLibraryAndExitThread(hModule, 0);

}

BOOL WINAPI DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        const auto thread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)(mainThread), hModule, 0, nullptr);
        if (thread) {
            CloseHandle(thread);
        }
    }
    return TRUE;
}