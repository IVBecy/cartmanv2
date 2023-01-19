#pragma once
#include <stdint.h>

namespace vmt {
    // Get pointer to function with index
    void* getFunction(void* vmt, int index);

	// Call function from pointer with index
	template <typename Return, typename ... Arguments>
	Return callFunction(void* vmt, uint32_t index, Arguments ... args) {
		using Function = Return(__thiscall*)(void*, decltype(args)...);
		return (*(Function**)(vmt))[index](vmt, args...);
	}
}