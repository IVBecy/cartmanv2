/*

Pattern scanning

*/
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

namespace pattern {
	// Structure for pattern data when converting
	struct patternData {
		char bytes[1000]{};
		char mask[1000]{};
	};

	// Generate mask and AOB from IDA styled patterns
	patternData comboConvert(const char* byteArray);

	// Get information from module
	MODULEINFO ModuleInfo(const char* mod);

	// Pattern scan
	DWORD Scan(const char* pattern, const char* mask, int offset, MODULEINFO modInfo);

	// Call all functions and return proper offset
	DWORD scanPattern(const char* sig, const char* mod, int offset, int extra, bool rel);
}
