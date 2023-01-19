#include "vmt.h"

// Get pointer to function with index
void* vmt::getFunction(void* vmt, int index) {
	return (*(void***)(vmt))[index];
}

