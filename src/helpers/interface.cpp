#include <windows.h>
#include "interface.h"

void* GetInterface(const char* interfaceName, const char* dll) {
	tCreateInterface CreateInterface = (tCreateInterface)GetProcAddress(GetModuleHandle(dll), "CreateInterface");
	int retCode = 0;
	void* interFace = CreateInterface(interfaceName, &retCode);
	return interFace;
}
