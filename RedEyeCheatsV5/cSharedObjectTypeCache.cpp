#include "cSharedObjectTypeCache.h"
#include "cEconItem,h.h"
void cSharedObjectTypeCache::addObject(void* obj)
{
	typedef void(__thiscall * tOriginal)(void*, void*);
	virtualFunction<tOriginal>(this, 1)(this, obj);
}

void cSharedObjectTypeCache::removeObject(void* obj)
{
	typedef void(__thiscall * tOriginal)(void*, void*);
	virtualFunction<tOriginal>(this, 3)(this, obj);
}

std::vector<CEconItem*> cSharedObjectTypeCache::getEconItems()
{
	std::vector<CEconItem*> ret;
	auto size = *reinterpret_cast<size_t*>(this + 0x18);
	auto data = *reinterpret_cast<uintptr_t * *>(this + 0x4);
	for (size_t i = 0; i < size; i++)
		ret.push_back(reinterpret_cast<CEconItem*>(data[i]));
	return ret;
}