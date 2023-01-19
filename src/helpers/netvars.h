#pragma once

#include <cstdint>

#include "../valve/clientclass.h"

namespace netvars {
	// Finding Offsets
	uintptr_t GetOffset(RecvTable* table, const char* tableName, const char* netvarName, const char* propName, int dataOffset);

	// Looping through the linked list to call `GetOffset`
	uintptr_t GetNetvarOffset(const char* tableName, const char* netvarName, ClientClass* clientClass, const char* propName, int dataOffset);
}
