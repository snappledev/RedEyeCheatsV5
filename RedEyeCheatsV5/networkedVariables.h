#pragma once
#include <string>
#include "recv.h"
#include <vector>
struct networkedTable
{
	std::string               table;
	RecvProp*                 prop;

	uint32_t                  offset;
	std::vector<RecvProp*>    child_props;
	std::vector<networkedTable> child_tables;
};
class networkManager
{
public:
	void findNetworkTables();
	void dumpTablesToFile();
	uint32_t getOffset(const networkedTable& table, const std::string& propName);
	RecvProp* GetNetvarProp(const std::string& tableName, const std::string& propName);
	uint32_t getOffset(const std::string& tableName, const std::string& propName);
private:
	std::vector<networkedTable>  tables;
};