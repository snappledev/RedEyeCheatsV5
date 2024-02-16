#include "networkedVariables.h"
#include "ClientClass.h"
#include "interfaces.h"
#include <fstream>
networkedTable loadTable(RecvTable* recvTable)
{
	auto table = networkedTable{};

	table.offset = 0;
	table.table = recvTable->m_pNetTableName;

	for (auto i = 0; i < recvTable->m_nProps; ++i) {
		auto prop = &recvTable->m_pProps[i];

		if (!prop || isdigit(prop->m_pVarName[0]))
			continue;
		if (strcmp("baseclass", prop->m_pVarName) == 0)
			continue;

		if (prop->m_RecvType == DPT_DataTable && prop->m_pDataTable) {
			table.child_tables.emplace_back(loadTable(prop->m_pDataTable));
			table.child_tables.back().offset = prop->m_Offset;
			table.child_tables.back().prop = prop;
		}
		else {
			table.child_props.emplace_back(prop);
		}
	}
	return table;
}
uint32_t networkManager::getOffset(const networkedTable& table, const std::string& propName)
{
	for (const auto& prop : table.child_props) {
		if (strncmp(prop->m_pVarName, propName.data(), propName.size()) == 0) {
			return table.offset + prop->m_Offset;
		}
	}
	for (const auto& child : table.child_tables) {
		auto prop_offset = getOffset(child, propName);
		if (prop_offset != 0)
			return table.offset + prop_offset;
	}
	for (const auto& child : table.child_tables) {
		if (strncmp(child.prop->m_pVarName, propName.data(), propName.size()) == 0) {
			return table.offset + child.offset;
		}
	}
	return 0;
}
RecvProp* networkManager::GetNetvarProp(const std::string& tableName, const std::string& propName)
{
	for (const auto& table : tables) {
		if (table.table == tableName) {
			for (const auto& prop : table.child_props) {
				if (strncmp(prop->m_pVarName, propName.data(), propName.size()) == 0) {
					return prop;
				}
			}
			for (const auto& child : table.child_tables) {
				if (child.prop && child.prop->m_pVarName == propName) {
					return child.prop;
				}
			}
		}
	}
	return nullptr;
}

uint32_t networkManager::getOffset(const std::string& tableName, const std::string& propName)
{
	auto result = 0u;
	for (const auto& table : tables) {
		if (table.table == tableName) {
			result = getOffset(table, propName);
			if (result != 0)
				return result;
		}
	}
	return 0;
}
void networkManager::dumpTablesToFile()
{
	std::fstream file;
	file.open("netvar_dump.txt");
	for (int i = 0; i < tables.size() - 1; i++) {
		networkedTable table = tables.at(i);
		
		file << table.table << "\n";
		for (int x = 0; x < table.child_props.size(); x++) {
			RecvProp* prp = table.child_props.at(x);
			file << "	" << prp->m_pVarName << " - " << prp->m_Offset<<"\n";
		}

	}
}
void networkManager::findNetworkTables() {
	tables.clear();
	for (ClientClass* client = interfaceManager::ibaseclient->GetAllClasses(); client != nullptr; client = client->m_pNext) {
		if (client->m_pRecvTable) {
			tables.emplace_back(loadTable(client->m_pRecvTable));
		}
	}
}
