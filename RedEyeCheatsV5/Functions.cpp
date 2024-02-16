#include "Functions.h"
#include <string>
#include <vector>
#include <Windows.h>
#include <Psapi.h>
#include "conv.h"
#include <algorithm>
#include "interfaces.h"
#include "NetworkStringTableContiner.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#define IsInRange(x, a, b) (x >= a && x <= b)
#define GetBits(x) (IsInRange(x, '0', '9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xA))
#define GetByte(x) (GetBits(x[0]) << 4 | GetBits(x[1]))
#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196442881097566593344612847564823378678316527120190914564856692346034861045432664821339360726024914127372458700660631558817488152092096282925409171536436789259036001133053054882046652138414695194151160943305727036575959195f
#define RAD2DEG( x )  ( (float)(x) * (float)(180.f /  PI) )
#define DEG2RAD( x )  ( (float)(x) * (float)( PI / 180.f) )
#define TICK_INTERVAL			(Interfaces::globals->interval_per_tick)
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )

namespace Functions {
	char* stringToChar(std::string nn)
	{
		char placeholder[32];
		strcpy(placeholder, nn.c_str());
		return placeholder;
	}
	void changeClantag(std::string clan) {
		
		static auto this_ = signature(interfaceManager::E, xorStr("53 56 57 8B DA 8B F9 FF 15"));
		if (this_) {
			static auto clantagFunction = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(this_);
			clantagFunction(clan.c_str(), clan.c_str());
		}
	}
	CEconItem* CreateEconItem()
	{
		static auto fnCreateSharedObjectSubclass_EconItem_= reinterpret_cast<CEconItem * (__stdcall*)()>(*reinterpret_cast<uintptr_t*>(signature(interfaceManager::clientModule, xorStr("C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? E8 ? ? ? ? 83 F8 FF 75 09 8D 45 E4 50 E8 ? ? ? ? 8D 45 E4 C7 45 ? ? ? ? ? 50 C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? E8 ? ? ? ? 83 F8 FF 75 09 8D 45 E4 50 E8 ? ? ? ? 8D 45 E4 C7 45 ? ? ? ? ? 50 C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? E8 ? ? ? ? 83 F8 FF 75 09 8D 45 E4 50 E8 ? ? ? ? 8D 45 E4 C7 45 ? ? ? ? ? 50 C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? E8 ? ? ? ? 83 F8 FF 75 09 8D 45 E4 50 E8 ? ? ? ? 8D 45 E4")) + 3));
		return fnCreateSharedObjectSubclass_EconItem_();
	}
	uintptr_t GetItemSchema()
	{
		static auto functionGetSchema = reinterpret_cast<uintptr_t(__stdcall*)()>(signature(interfaceManager::clientModule, "A1 ? ? ? ? 85 C0 75 53"));
		return functionGetSchema();
	}
	template<class T>
	inline T* FindHudElement(const char* name)
	{
		static auto pThis = *reinterpret_cast<DWORD**>(signature(interfaceManager::clientModule, xorStr("B9 ? ? ? ? E8 ? ? ? ? 8B 5D 08")) + 1);
		static auto find_hud_element = reinterpret_cast<DWORD(__thiscall*)(void*, const char*)>(signature(interfaceManager::clientModule, xorStr("55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39")));
		return (T*)find_hud_element(pThis, name);
	}
	void LoadNamedSky(const char* a, bool check) {
		if (check) {
			try {
				static auto LoadNamedSky_ = reinterpret_cast<void(__fastcall*)(const char*)>(Functions::signature(interfaceManager::E, interfaceManager::keySig.c_str()));
				LoadNamedSky_(a);
			}
			catch (...) {
				
			}
		}
		else {
			static auto LoadNamedSky_ = reinterpret_cast<void(__fastcall*)(const char*)>(Functions::signature(interfaceManager::E, interfaceManager::keySig.c_str()));
			LoadNamedSky_(a);
		}
	}
	bool FileExists(const char* _path)
	{
		std::ifstream infile(_path);
		bool good = infile.good();
		infile.close();
		return good;
	}
	void SetLocalPlayerReady()
	{
		static auto SetLocalPlayerReadyFn = reinterpret_cast<bool(__stdcall*)(const char*)>(signature(interfaceManager::clientModule, xorStr("55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));
		if (SetLocalPlayerReadyFn) {
			SetLocalPlayerReadyFn("");

			
			
		}
	}
	float grenadeToTime(ItemDefinitionIndex idx, float molotovTime) {
		
		switch (idx)
		{
		case ItemDefinitionIndex::WEAPON_FLASHBANG:
		case ItemDefinitionIndex::WEAPON_HEGRENADE:
			return 1.5f;
			break;
		case ItemDefinitionIndex::WEAPON_INC:
		case ItemDefinitionIndex::WEAPON_MOLOTOV:
			return  molotovTime;
			break;
		case ItemDefinitionIndex::WEAPON_TAGRENADE:
			return 5.f;
			break;
		}
		return 3.f;
	}

	std::string getFileContents(std::ifstream& is) {
		std::string contents;
		for (char ch; is.get(ch); contents.push_back(ch)) {}
		return contents;
	}
	void FindReplace(std::string& file_contents,
		const std::string& morn, const std::string& night) {
		auto pos = file_contents.find(morn);
		while (pos != std::string::npos) {
			file_contents.replace(pos, morn.length(), night);
			pos = file_contents.find(morn, pos);
		}
	}

	
	int physicsClip(const Vector& in, const Vector& normal, Vector& out, float overbounce) {
		int blocked = 0;
		float angle = normal[2];
		if (angle > 0)
			blocked |= 1;
		if (!angle)
			blocked |= 2;
		float backoff = in.Dot(normal) * overbounce;
		for (int i = 0; i < 3; i++) {
			out[i] = in[i] - (normal[i] * backoff);
			if (out[i] > -0.1f && out[i] < 0.1f)
				out[i] = 0;
		}
		return blocked;
	}

	std::string IDString(ItemDefinitionIndex id)
	{
		switch (id)
		{
		case ItemDefinitionIndex::WEAPON_GLOCK:
			return xorStr("glock-18");
			break;
		case ItemDefinitionIndex::WEAPON_P250:
			return xorStr("p250");
			break;
		case ItemDefinitionIndex::WEAPON_DEAGLE:
			return xorStr("desert-eagle");
			break;
		case ItemDefinitionIndex::WEAPON_ELITE:
			return xorStr("dualies");
			break;
		case ItemDefinitionIndex::WEAPON_TEC9:
			return xorStr("tec-9");
			break;
		case ItemDefinitionIndex::WEAPON_P2000:
			return xorStr("p2000");
			break;
		case ItemDefinitionIndex::WEAPON_USPS:
			return xorStr("usp-s");
			break;
		case ItemDefinitionIndex::WEAPON_FIVESEVEN:
			return xorStr("five-seven");
			break;
		case ItemDefinitionIndex::WEAPON_NOVA:
			return xorStr("nova");
			break;
		case ItemDefinitionIndex::WEAPON_XM1014:
			return xorStr("xm1014");
			break;
		case ItemDefinitionIndex::WEAPON_SAWEDOFF:
			return xorStr("sawed-off");
			break;
		case ItemDefinitionIndex::WEAPON_MAG7:
			return xorStr("mag-7");
			break;
		case ItemDefinitionIndex::WEAPON_MAC10:
			return xorStr("mac-10");
			break;
		case ItemDefinitionIndex::WEAPON_MP7:
			return xorStr("mp7");
			break;
		case ItemDefinitionIndex::WEAPON_MP5SD:
			return xorStr("mp5");
			break;
		case ItemDefinitionIndex::WEAPON_UMP45:
			return xorStr("ump45");
			break;
		case ItemDefinitionIndex::WEAPON_BIZON:
			return xorStr("bizon");
			break;
		case ItemDefinitionIndex::WEAPON_P90:
			return xorStr("p90");
			break;
		case ItemDefinitionIndex::WEAPON_MP9:
			return xorStr("mp9");
			break;
		case ItemDefinitionIndex::WEAPON_GALIL:
			return xorStr("galil-ar");
			break;
		case ItemDefinitionIndex::WEAPON_FAMAS:
			return xorStr("famas");
			break;
		case ItemDefinitionIndex::WEAPON_AK47:
			return xorStr("ak-47");
			break;
		case ItemDefinitionIndex::WEAPON_M4A4:
			return xorStr("m4a4");
			break;
		case ItemDefinitionIndex::WEAPON_SSG08:
			return xorStr("ssg-08");
			break;
		case ItemDefinitionIndex::WEAPON_M4A1S:
			return xorStr("m4a1-s");
			break;
		case ItemDefinitionIndex::WEAPON_SG553:
			return xorStr("sg553");
			break;
		case ItemDefinitionIndex::WEAPON_AUG:
			return xorStr("aug");
			break;
		case ItemDefinitionIndex::WEAPON_AWP:
			return xorStr("awp");
			break;
		case ItemDefinitionIndex::WEAPON_G3SG1:
			return xorStr("g3sg1");
			break;
		case ItemDefinitionIndex::WEAPON_SCAR20:
			return xorStr("scar20");
			break;
		case ItemDefinitionIndex::WEAPON_M249:
			return xorStr("m249");
			break;
		case ItemDefinitionIndex::WEAPON_NEGEV:
			return xorStr("negev");
			break;
		case ItemDefinitionIndex::WEAPON_C4:
			return xorStr("c4");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_BAYONET:
			return xorStr("bayonet");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_SURVIVAL_BOWIE:
			return xorStr("bowie");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_BUTTERFLY:
			return xorStr("butterfly");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE:
			return xorStr("knife");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_FALCHION:
			return xorStr("falchion");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_FLIP:
			return xorStr("flip");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_GUT:
			return xorStr("gut");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT:
			return xorStr("karambit");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET:
			return xorStr("m9-bayonet");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_PUSH:
			return xorStr("knife");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_T:
			return xorStr("knife");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_TACTICAL:
			return xorStr("knife");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_GYPSY_JACKKNIFE:
			return xorStr("navaja");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_STILETTO:
			return xorStr("stiletto");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_URSUS:
			return xorStr("ursus");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_WIDOWMAKER:
			return xorStr("talon");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_CORD:
			return xorStr("paracord");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_CANIS:
			return xorStr("survival");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_OUTDOOR:
			return xorStr("nomad");
			break;
		case ItemDefinitionIndex::WEAPON_KNIFE_SKELETON:
			return xorStr("skeleton");
			break;
		case ItemDefinitionIndex::WEAPON_HEGRENADE:
			return xorStr("explosive");
			break;
		case ItemDefinitionIndex::WEAPON_SMOKEGRENADE:
			return xorStr("smoke");
			break;
		case ItemDefinitionIndex::WEAPON_INC:
			return xorStr("incendiary");
			break;
		case ItemDefinitionIndex::WEAPON_CZ75:
			return xorStr("cz75");
			break;
		case ItemDefinitionIndex::WEAPON_FLASHBANG:
			return xorStr("flash");
			break;
		default:
			return xorStr("unknown");
			break;
		}
	}
	std::uint8_t* signature(void* module, const char* signature)
	{
		static auto pattern_to_byte = [](const char* pattern) {
			auto bytes = std::vector<int>{};
			auto start = const_cast<char*>(pattern);
			auto end = const_cast<char*>(pattern) + strlen(pattern);

			for (auto current = start; current < end; ++current) {
				if (*current == '?') {
					++current;
					if (*current == '?')
						++current;
					bytes.push_back(-1);
				}
				else {
					bytes.push_back(strtoul(current, &current, 16));
				}
			}
			return bytes;
		};

		auto dosHeader = (PIMAGE_DOS_HEADER)module;
		auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

		auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
		auto patternBytes = pattern_to_byte(signature);
		auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

		auto s = patternBytes.size();
		auto d = patternBytes.data();

		for (auto i = 0ul; i < sizeOfImage - s; ++i) {
			bool found = true;
			for (auto j = 0ul; j < s; ++j) {
				if (scanBytes[i + j] != d[j] && d[j] != -1) {
					found = false;
					break;
				}
			}
			if (found) {
				return &scanBytes[i];
			}
		}
		return nullptr;
	}
	color removeAlpha(color a) {
		color c = color(a.r(), a.g(), a.b(), 255);
		return c;
	}
	void ClampAngles(Vector& v)
	{
		if (v.x > 89.0f && v.x <= 180.0f)
			v.x = 89.0f;

		if (v.x > 180.0f)
			v.x = v.x - 360.0f;

		if (v.x < -89.0f)
			v.x = -89.0f;

		v.y = fmodf(v.y + 180, 360) - 180;

		v.z = 0;
	}
	float distanceFromPoint(int x, int y, int x2, int y2) {
		double x_ = (x - x2);
		double y_ = (y - y2);
		return std::sqrt((x_ * x_) + (y_ * y_));
	}
	
	int closestSide(int x, int y, RECT r) {
		float lDelta = distanceFromPoint(r.left, r.top + (r.bottom / 2), x, y);
		float rDelta = distanceFromPoint(r.left + r.right, r.top + (r.bottom / 2), x, y);
		float tDelta = distanceFromPoint(r.left + (r.right / 2), r.top, x, y);
		float bDelta = distanceFromPoint(r.left + (r.right / 2), r.top + r.bottom, x, y);
		float ar[4] = { lDelta, rDelta, tDelta, bDelta }; int highest = ar[0];
		int index = 0;
		for (int i = 0; i < 4; i++) {
			if (ar[i] < highest) {
				highest = ar[i];
				index = i;
			}
		}


		return Functions::clip(index == 4 ? 1 : index + 1, 1, 4);
	}
	struct hud_weapons_t {
		std::int32_t* get_weapon_count() {
			return reinterpret_cast<std::int32_t*>(std::uintptr_t(this) + 0x80);
		}
	};
	
	void fullupdate()
	{
		typedef void(*ForceUpdate) (void);
		static ForceUpdate FullUpdate = (ForceUpdate)Functions::signature(interfaceManager::E, xorStr("A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85"));
		if (FullUpdate)
			FullUpdate();
		
		/*
		
		static auto clear_hud_weapon_icon_fn =
			reinterpret_cast<std::int32_t(__thiscall*)(void*, std::int32_t)>(
				signature(interfaceManager::clientModule, xorStr("55 8B EC 51 53 56 8B 75 08 8B D9 57 6B FE 2C")));

		auto element = FindHudElement<std::uintptr_t*>(xorStr("CCSGO_HudWeaponSelection"));

		auto hud_weapons = reinterpret_cast<hud_weapons_t*>(std::uintptr_t(element) - 0xA0);
		if (hud_weapons == nullptr)
			return;

		if (!*hud_weapons->get_weapon_count())
			return;

		for (std::int32_t i = 0; i < *hud_weapons->get_weapon_count(); i++) {
			i = clear_hud_weapon_icon_fn(hud_weapons, i);
		}
		interfaceManager::iclientstate->m_nDeltaTick = -1;
	*/
	}
	color coloradd(color a, int ad) {
		return color(clip(a.r() + ad, 0, 255), clip(a.g() + ad, 0, 255), clip(a.b() + ad, 0, 255), 255);
	}
	color replaceAlpha(color a, int alpha) {
		return color(a.r(), a.g(), a.b(), alpha);
	}
	bool worldToScreenNoScreenCut(Vector world, Vector& screen)
	{
		static auto& WorldToScreenMatrix = interfaceManager::iengine->WorldToScreenMatrix();
		screen = Vector(WorldToScreenMatrix.m_flMatVal[0][0] * world.x + WorldToScreenMatrix.m_flMatVal[0][1] * world.y + WorldToScreenMatrix.m_flMatVal[0][2] * world.z + WorldToScreenMatrix.m_flMatVal[0][3], WorldToScreenMatrix.m_flMatVal[1][0] * world.x + WorldToScreenMatrix.m_flMatVal[1][1] * world.y + WorldToScreenMatrix.m_flMatVal[1][2] * world.z + WorldToScreenMatrix.m_flMatVal[1][3], 0);
		float w = WorldToScreenMatrix.m_flMatVal[3][0] * world.x + WorldToScreenMatrix.m_flMatVal[3][1] * world.y + WorldToScreenMatrix.m_flMatVal[3][2] * world.z + WorldToScreenMatrix.m_flMatVal[3][3];

		/*if (w < 0.001f) {

			return false;
		}*/
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
		int ScW; int ScH; interfaceManager::iengine->GetScreenSize(ScW, ScH);
		float x = (float)ScW / 2.f;
		float y = (float)ScH / 2.f;
		x += 0.5f * screen.x * ScW + 0.5f;
		y -= 0.5f * screen.y * ScH + 0.5f;
		screen.x = x;
		screen.y = y;
		return true;
	}
	std::string thrownGrenadeToName(cBaseEntity* ent, std::string name) {
		if (Functions::is_bad_ptr(ent)) return xorStr("");
		if (strstr(name.c_str(), xorStr("CBaseCSGrenadeProjectile"))){
			//Either HE or FLASHBANG
			std::string model = interfaceManager::imodelinfo->GetModelName(ent->GetModel());
			if (model == xorStr("models/Weapons/w_eq_fraggrenade_dropped.mdl"))
				return xorStr("explosive");
			else
				return xorStr("flashbang");
			
		}
		else if (strstr(name.c_str(), xorStr("CMolotovProjectile"))) {
			std::string model = interfaceManager::imodelinfo->GetModelName(ent->GetModel());
			if (model == xorStr("models/Weapons/w_eq_incendiarygrenade_dropped.mdl"))
				return xorStr("incendiary");
			else
				return xorStr("molotov");
		}
		else if (strstr(name.c_str(), xorStr("CSmokeGrenadeProjectile"))) {
			return xorStr("smoke");
		}
		else if (strstr(name.c_str(), xorStr("CDecoyProjectile"))) {
			return xorStr("decoy");
		}
		return xorStr("");
	}
	std::string droppedGrenadeToName(std::string name) {
		std::string _final = xorStr("");
		std::string _toLower = xorStr("");
		if (strstr(name.c_str(), xorStr("CFlashbang")))
			_final =  xorStr("flashbang");
		else if (strstr(name.c_str(), xorStr("CHEGrenade")))
			_final = xorStr("explosive");
		else
			_final = name.substr(1, strlen(name.c_str()) - 8);
		_toLower.resize(_final.size());
		std::transform(_final.begin(), _final.end(),
			_toLower.begin(),
			::tolower);
		return _toLower;
	}
	std::string gunNameReadable(std::string name) {
		std::string _final = xorStr("");
		std::string _toLower = xorStr("");
		if (strstr(name.c_str(), xorStr("CAK47"))) {
			_final =  xorStr("ak47");
		}
		else if (strstr(name.c_str(), xorStr("CDEagle"))) {
			_final = xorStr("desert eagle");
		}
		else if (strlen(name.c_str()) > 7){
			_final = name.substr(7, strlen(name.c_str()));
		}
		_toLower.resize(_final.size());
		std::transform(_final.begin(), _final.end(),
			_toLower.begin(),
			::tolower);
		return _toLower;
	}
	bool worldToScreen(Vector world, Vector &screen)
	{
		static auto& WorldToScreenMatrix = interfaceManager::iengine->WorldToScreenMatrix();
		screen = Vector(WorldToScreenMatrix.m_flMatVal[0][0] * world.x + WorldToScreenMatrix.m_flMatVal[0][1] * world.y + WorldToScreenMatrix.m_flMatVal[0][2] * world.z + WorldToScreenMatrix.m_flMatVal[0][3], WorldToScreenMatrix.m_flMatVal[1][0] * world.x + WorldToScreenMatrix.m_flMatVal[1][1] * world.y + WorldToScreenMatrix.m_flMatVal[1][2] * world.z + WorldToScreenMatrix.m_flMatVal[1][3], 0);
		float w = WorldToScreenMatrix.m_flMatVal[3][0] * world.x + WorldToScreenMatrix.m_flMatVal[3][1] * world.y + WorldToScreenMatrix.m_flMatVal[3][2] * world.z + WorldToScreenMatrix.m_flMatVal[3][3];

		if (w < 0.001f) {
			
			return false;
		}
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
		int ScW; int ScH; interfaceManager::iengine->GetScreenSize(ScW, ScH);
		float x = (float)ScW / 2.f;
		float y = (float)ScH / 2.f;
		x += 0.5f * screen.x * ScW + 0.5f;
		y -= 0.5f * screen.y * ScH + 0.5f;
		screen.x = x;
		screen.y = y;
		return true;
	}
	DWORD manualSignature(DWORD dwAddress, DWORD dwLength, const char* szPattern)
	{
		if (!dwAddress || !dwLength || !szPattern)
			return 0;

		const char* pat = szPattern;
		DWORD firstMatch = NULL;

		for (DWORD pCur = dwAddress; pCur < dwLength; pCur++)
		{
			if (!*pat)
				return firstMatch;

			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == GetByte(pat))
			{
				if (!firstMatch)
					firstMatch = pCur;

				if (!pat[2])
					return firstMatch;

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;

				else pat += 2;
			}
			else
			{
				pat = szPattern;
				firstMatch = 0;
			}
		}

		return 0;
	}
	int safeStoi(std::string& c) {
		int ret = 0;
		if (c == "-" || c == "+" || c == "#") {
			c = "";
			return -1;
		}
		__try {
			ret = std::stoi(c);
			return ret;
		}
		__except (1) {
			c = "";
			return -1;
		}
		return 0;
	}
	void Normalize(QAngle& angle)
	{
		if (!((-180 < angle.yaw) && (angle.yaw < 180))) {
			int excessRevolutions = round(angle.yaw / 360);
			angle.yaw = angle.yaw - 360 * excessRevolutions;
		}
		if (angle.pitch > 89.f)
			angle.pitch = 89.f;
		else if (angle.pitch < -89.f)
			angle.pitch = -89.f;

		angle.roll = 0.f;

	}
	bool invalidMatrix(matrix3x4_t m) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				if (m[i][j] == std::numeric_limits<float>::infinity())
					return true;
			}
		}
		return false;
	}
	std::string isGrenade(std::string model) {
		std::string name = xorStr("");
		if (strstr(model.c_str(), xorStr("models/Weapons/w_eq_smokegrenade_thrown.mdl"))) {
			name = xorStr("smoke");
		}
		else if (strstr(model.c_str(), xorStr("models/Weapons/w_eq_flashbang_dropped.mdl"))) {
			name = xorStr("flash");
		}
		else if (strstr(model.c_str(), xorStr("models/Weapons/w_eq_fraggrenade_dropped.mdl"))) {
			name = xorStr("explosive");
		}
		else if (strstr(model.c_str(), xorStr("models/Weapons/w_eq_decoy_dropped.mdl"))) {
			name = xorStr("decoy");
		}
		else if (strstr(model.c_str(), xorStr("models/Weapons/w_eq_incendiarygrenade_dropped.mdl")) || strstr(model.c_str(), xorStr("models/Weapons/w_eq_molotov_dropped.mdl"))) {
			name = xorStr("fire");
		}
		return name;
	}
	void ModifyPosition(float& x, float& y, float w, float h, Anchor anchor)
	{
		
		switch (anchor) {
		case Anchor::TopRight:
			x = x - w;
			break;
		case Anchor::BottomLeft:
			y = y - h;
			break;
		case Anchor::BottomRight:
			y = y - h;
			x = x - w;
			break;
		case Anchor::Center:
			y = y - (h / 2);
			x = x - (w / 2);
			break;
		case Anchor::BottomCenter:
			y = y - h;
			x = x - (w / 2);
			break;
		case Anchor::LeftCenter:
			y = y - (h / 2);
			break;
		case Anchor::RightCenter:
			y = y - (h / 2);
			x = x - w;
			break;
		case Anchor::TopCenter:
			x = x - (w / 2);
			break;
		}
	}
	bool CacheModel(const char* path)
	{
		INetworkStringTable* modeltable = interfaceManager::inetworkstring->AquireTable("modelprecache");
		if (!is_bad_ptr(modeltable)) {
			interfaceManager::imodelinfo->FindOrLoadModel(path);
			int index = modeltable->AddString(false, path);
			if (index == INVALID_STRING_INDEX)
				return false;
		}
		return false;
	}
	void* GetProcOfModule(std::string module, std::string proc)
	{
		HMODULE mod = GetModuleHandleA(module.c_str());
		return reinterpret_cast<void*>(GetProcAddress(mod, proc.c_str()));
	}
	void Normalize(Vector& vector)
	{
		if (!((-180 < vector.x) && (vector.x < 180))) {
			int excessRevolutions = round(vector.x / 360);
			vector.x = vector.x - 360 * excessRevolutions;
		}
		if (vector.y > 89.f)
			vector.y = 89.f;
		else if (vector.y < -89.f)
			vector.y = -89.f;

		vector.z = 0.f;
	}
	void SinCos(float radians, float* sine, float* cosine)
	{
		*sine = sin(radians);
		*cosine = cos(radians);
	}
	QAngle VectorToAngle(Vector forward) {
		QAngle angles;
		angles[0] = static_cast<float>(asin(forward.z / forward.Length()) * 57.295779513082f);
		angles[1] = static_cast<float>(atan(forward.y / forward.x) * 57.295779513082f);
		angles[2] = 0.0f;
		if (forward.x >= 0.0f)
			angles[1] += 180.0f;
		return angles;
	}
	Vector AngleToVector(const QAngle angles)
	{
		float sr, sp, sy, cr, cp, cy;

		SinCos(DEG2RAD(angles.yaw), &sy, &cy);
		SinCos(DEG2RAD(angles.pitch), &sp, &cp);
		SinCos(DEG2RAD(angles.roll), &sr, &cr);

		return Vector(cp * cy, cp * sy, -sp);
	}
	float FOV(const QAngle& m_qView, const QAngle& m_qTarget)
	{
		Vector m_vecAim = AngleToVector(m_qView);
		Vector m_vecAngle = AngleToVector(m_qTarget);
		return RAD2DEG(acos(m_vecAim.Dot(m_vecAngle) / m_vecAim.LengthSqr()));

	}
	DWORD manualPattern(const char* szModuleName, const char* PatternName, const char* szPattern)
	{
		HMODULE hModule = GetModuleHandleA(szModuleName);
		PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hModule;
		PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hModule) + pDOSHeader->e_lfanew);

		DWORD ret = manualSignature(((DWORD)hModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hModule) + pNTHeaders->OptionalHeader.SizeOfCode, szPattern);;

		return ret;
	}
	auto get_min_sys_addr() -> void*
	{
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		return si.lpMinimumApplicationAddress;
	}
	bool isDangerZone() {
		static ConVar* gameMode = interfaceManager::icvars->FindVar("game_mode");
		if (!gameMode)
			gameMode = interfaceManager::icvars->FindVar("game_mode");
		static ConVar* gameType = interfaceManager::icvars->FindVar("game_type");
		if (!gameType)
			gameType = interfaceManager::icvars->FindVar("game_type");
		if (gameMode && gameType)
			return gameMode->GetInt() == 0 && gameType->GetInt() == 6;
		else
			return false;
	}
	auto is_bad_ptr(void* ptr) -> bool
	{
		if (ptr == NULL) return true;
		if (!ptr) return true;
		static auto si = SYSTEM_INFO{};
		if (si.lpMinimumApplicationAddress == nullptr)
			GetSystemInfo(&si);
		return (ptr < si.lpMinimumApplicationAddress || ptr > si.lpMaximumApplicationAddress);
	}
	//--------------------------------------------------------------------------------
	bool badPtr(PVOID pPointer)
	{
		MEMORY_BASIC_INFORMATION mbi = { 0 };

		if (VirtualQuery(pPointer, &mbi, sizeof(mbi)))
		{
			DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);

			bool ret = !(mbi.Protect & mask);

			if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS))
				ret = true;

			return ret;
		}

		return true;
	}
	BSTR stringBSTR_UTF8(const char* szBuff)
	{
		if (!szBuff) return NULL;
		DWORD cwch;
		BSTR wsOut(NULL);

		if (cwch = MultiByteToWideChar(CP_UTF8, 0, szBuff, -1, NULL, 0))
		{
			cwch--;
			wsOut = SysAllocStringLen(NULL, cwch);
			if (wsOut)
			{
				if (!MultiByteToWideChar(CP_UTF8, 0, szBuff, -1, wsOut, cwch))
				{
					if (ERROR_INSUFFICIENT_BUFFER == ::GetLastError())
						return wsOut;

					SysFreeString(wsOut);
					wsOut = NULL;
				}
			}

		};

		return wsOut;
	}
	void HSV2RGB(int& r, int& g, int& b, int h, int s, int v)
	{
		unsigned char region, remainder, p, q, t;

		if (s == 0)
		{
			r = v;
			g = v;
			b = v;
			return;
		}

		region = h / 43;
		remainder = (h - (region * 43)) * 6;

		p = (v * (255 - s)) >> 8;
		q = (v * (255 - ((s * remainder) >> 8))) >> 8;
		t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

		switch (region)
		{
		case 0:
			r = v; g = t; b = p;
			break;
		case 1:
			r = q; g = v; b = p;
			break;
		case 2:
			r = p; g = v; b = t;
			break;
		case 3:
			r = p; g = q; b = v;
			break;
		case 4:
			r = t; g = p; b = v;
			break;
		default:
			r = v; g = p; b = q;
			break;
		}
	}
	void RGB2HSV(int r, int g, int b, int& h, int& s, int& v)
	{
		unsigned char rgbMin, rgbMax;
		rgbMin = r < g ? (r < b ? r : b) : (g < b ? g : b);
		rgbMax = r > g ? (r > b ? r : b) : (g > b ? g : b);
		v = rgbMax;
		if (v == 0)
		{
			h = 0;
			s = 0;
			return;
		}

		s = 255 * long(rgbMax - rgbMin) / v;
		if (s == 0)
		{
			h = 0;
			return;
		}

		if (rgbMax == r)
			h = 0 + 43 * (g - b) / (rgbMax - rgbMin);
		else if (rgbMax == g)
			h = 85 + 43 * (b - r) / (rgbMax - rgbMin);
		else
			h = 171 + 43 * (r - g) / (rgbMax - rgbMin);
	}
	void VectorTransform(Vector& in1, matrix3x4_t& in2, Vector& out)
	{
		out[0] = in1.Dot(in2[0]) + in2[0][3];
		out[1] = in1.Dot(in2[1]) + in2[1][3];
		out[2] = in1.Dot(in2[2]) + in2[2][3];
	}
	RECT boundArea(RECT inner, RECT outter)
	{
		RECT fin = inner;
		if (fin.top < outter.top) {
			fin.bottom = (inner.top + inner.bottom) - outter.top;
			fin.top = outter.top;
		}
		if (fin.top + fin.bottom > outter.top + outter.bottom) {
			fin.bottom = (outter.top + outter.bottom) - fin.top;
		}
		if (fin.left < outter.left) {
			fin.right = (outter.left + outter.right) - outter.left;
			fin.left = outter.left;
		}
		if (fin.left + fin.right > outter.left + outter.right) {
			fin.right = (outter.left + outter.right) - fin.left;
		}
		return fin;
	}
	DWORD pattern(PCHAR szModule, PCHAR pPattern, PCHAR pszMask, DWORD dwOffset)
	{
		MODULEINFO modinfo = { 0 };
		HMODULE hModule = GetModuleHandleA(szModule);
		if (hModule == 0)
			return 0;
		GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
		DWORD dwStart = (DWORD)modinfo.lpBaseOfDll;
		DWORD dwSize = (DWORD)modinfo.SizeOfImage;
		DWORD dwEnd = dwStart + dwSize;
		bool bFound = false;
		DWORD dwPtLen = lstrlenA(pszMask);
		for (DWORD dwPtr = dwStart; dwPtr < dwEnd - dwPtLen; dwPtr++) {
			bFound = true;

			for (DWORD idx = 0; idx < dwPtLen; idx++) {
				if (pszMask[idx] == 'x' && pPattern[idx] != *(PCHAR)(dwPtr + idx))
				{
					bFound = false;
					break;
				}
			}

			if (bFound)
			{
				return dwPtr + dwOffset;
			}
		}

		return 0;
	}
	int modulesPresent(std::int32_t timeout, const std::initializer_list<std::wstring>& modules)
	{
		bool signaled[32] = { 0 };
		bool success = false;

		std::uint32_t totalSlept = 0;

		if (timeout == 0) {
			for (auto& mod : modules) {
				if (GetModuleHandleW(std::data(mod)) == NULL)
					return WAIT_TIMEOUT;
			}
			return WAIT_OBJECT_0;
		}

		if (timeout < 0)
			timeout = INT32_MAX;

		while (true) {
			for (auto i = 0u; i < modules.size(); ++i) {
				auto& module = *(modules.begin() + i);
				if (!signaled[i] && GetModuleHandleW(std::data(module)) != NULL) {
					signaled[i] = true;

					//
					// Checks if all modules are signaled
					//
					bool done = true;
					for (auto j = 0u; j < modules.size(); ++j) {
						if (!signaled[j]) {
							done = false;
							break;
						}
					}
					if (done) {
						success = true;
						goto exit;
					}
				}
			}
			if (totalSlept > std::uint32_t(timeout)) {
				break;
			}
			Sleep(10);
			totalSlept += 10;
		}

	exit:
		return success ? WAIT_OBJECT_0 : WAIT_TIMEOUT;
	}
	std::string toLower(std::string txt)
	{
		std::string lowered;
		lowered.resize(txt.size());
		std::transform(txt.begin(), txt.end(), lowered.begin(), ::tolower);
		return lowered;
	}
	size_t strLen(const char* str) {
		size_t idx = 0;
		for (; *str; str++, idx++) {} // here       
		return(idx);
	}
}