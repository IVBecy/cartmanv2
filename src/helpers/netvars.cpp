/*

This is from: https://github.com/IVBecy/gold_digger

*/

#include "netvars.h"

#include <string.h>

// Finding Offsets
uintptr_t netvars::GetOffset(RecvTable* table, const char* tableName, const char* netvarName, const char* propName, int dataOffset) {
	for (int i = 0; i < table->m_nProps; i++) {
		RecvProp prop = table->m_pProps[i];

		// For: propName == varName
		if (!strcmp(prop.m_pVarName, netvarName)) {
			return prop.m_Offset;
		}
		// For: propName != varName
		else if (!strcmp(propName, prop.m_pVarName)) {
			return dataOffset + prop.m_Offset;
		}
		// If another table in the current one
		if (prop.m_pDataTable) {
			uintptr_t offset = GetOffset(prop.m_pDataTable, tableName, netvarName, propName, dataOffset);

			if (offset) {
				return offset + prop.m_Offset;
			}
		}
	}
	return 0;
}

// Looping through the linked list to call `GetOffset`
uintptr_t netvars::GetNetvarOffset(const char* tableName, const char* netvarName, ClientClass* clientClass, const char* propName, int dataOffset) {
	ClientClass* currentNode = clientClass;

	for (auto currentNode = clientClass; currentNode; currentNode = currentNode->m_pNext) {
		if (strcmp(tableName, currentNode->m_pRecvTable->m_pNetTableName) == 0) {
			return GetOffset(currentNode->m_pRecvTable, tableName, netvarName, propName, dataOffset);
		}
	}
	return 0;
}