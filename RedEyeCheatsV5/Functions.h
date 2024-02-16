#pragma once
#include <Windows.h>
#include <string>
#include "vector.h"
#include "classes.h"
#include "color.h"
#include "qAngle.h"
#include "matrix3x4.h"

enum class Anchor
{
	TopLeft = 0,
	TopRight,
	BottomLeft,
	BottomRight,
	Center,
	BottomCenter,
	LeftCenter,
	RightCenter,
	TopCenter

};
class cBaseEntity;
class CEconItem;
namespace Functions {
	extern char* stringToChar(std::string nn);
	extern bool CacheModel(const char* path);
	extern void ClampAngles(Vector& v);
	extern void* GetProcOfModule(std::string module, std::string proc);
	extern int safeStoi(std::string& c);
	extern int closestSide(int x, int y, RECT r);
	extern RECT healthPosition(RECT boxArea, RECT txtArea, int lrtb[4], int index);
	extern color coloradd(color a, int ad);
	extern color replaceAlpha(color a, int alpha);
	extern std::uint8_t* signature(void* module, const char* signature);
	extern DWORD manualSignature(DWORD dwAddress, DWORD dwLength, const char* szPattern);
	extern DWORD manualPattern(const char* szModuleName, const char* PatternName, const char* szPattern);
	extern void SetLocalPlayerReady();
	extern bool badPtr(PVOID pPointer);
	extern void ChangeRanks(int rank);
	extern void LoadNamedSky(const char* a, bool check);
	extern void changeClantag(std::string clan);
	extern CEconItem* CreateEconItem();
	extern uintptr_t GetItemSchema();
	template<class T>
	extern inline T* FindHudElement(const char* name);
	extern bool FileExists(const char* _path);
	extern int physicsClip(const Vector& in, const Vector& normal, Vector& out, float overbounce);
	extern float grenadeToTime(ItemDefinitionIndex idx, float id);
	extern void fullupdate();
	extern BSTR stringBSTR_UTF8(const char* szBuff);
	extern DWORD pattern(PCHAR szModule, PCHAR pPattern, PCHAR pszMask, DWORD dwOffset);
	extern int modulesPresent(std::int32_t timeout, const std::initializer_list<std::wstring>& modules);
	extern void ModifyPosition(float& x, float& y, float w, float h, Anchor anchor);
	extern std::string toLower(std::string txt);
	extern bool isDangerZone();
	extern bool invalidMatrix(matrix3x4_t m);
	extern std::string isGrenade(std::string model);
	extern void HSV2RGB(int& r, int& g, int& b, int h, int s, int v);
	extern void RGB2HSV(int r, int g, int b, int& h, int& s, int& v);
	extern void VectorTransform(Vector& in1, matrix3x4_t& in2, Vector& out);
	extern RECT boundArea(RECT inner, RECT outter);
	extern size_t strLen(const char* str);
	extern std::string droppedGrenadeToName(std::string name);
	extern std::string getFileContents(std::ifstream& is);
	extern void  FindReplace(std::string& file_contents, const std::string& morn, const std::string& night);
	extern std::string thrownGrenadeToName(cBaseEntity* ent, std::string name);
	extern std::string gunNameReadable(std::string name);
	extern bool worldToScreen(Vector world, Vector &screen);
	extern bool worldToScreenNoScreenCut(Vector world, Vector& screen);
	extern std::string IDString(ItemDefinitionIndex id);
	extern color removeAlpha(color a);
	extern void Normalize(Vector& vector);
	extern void Normalize(QAngle& angle);
	extern QAngle VectorToAngle(Vector forward);
	extern Vector AngleToVector(const QAngle angles);
	extern float FOV(const QAngle& m_qView, const QAngle& m_qTarget);
	extern auto get_min_sys_addr() -> void*;
	extern auto is_bad_ptr(void* ptr) -> bool;
	template <typename T>
	T clip(const T& n, const T& lower, const T& upper) {
		return n <= lower ? lower : n >= upper ? upper : n;
	}
}