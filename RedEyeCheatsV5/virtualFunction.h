#pragma once
inline void**& virtualTable(void* inst, size_t offset = 0)
{
	return *reinterpret_cast<void***>((size_t)inst + offset);
}
inline const void** virtualTable(const void* inst, size_t offset = 0)
{
 	return *reinterpret_cast<const void***>((size_t)inst + offset);
}
template< typename Fn >
inline Fn virtualFunction(const void* inst, size_t index, size_t offset = 0)
{
	return reinterpret_cast<Fn>(virtualTable(inst, offset)[index]);
}
