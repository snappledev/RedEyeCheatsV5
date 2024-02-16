#include "virtualFunction.h"

#include "cEconItem,h.h"
class cSharedObjectTypeCache
{
public:
	void addObject(void* obj);
	void removeObject(void* obj);
	std::vector<CEconItem*>getEconItems();

};
