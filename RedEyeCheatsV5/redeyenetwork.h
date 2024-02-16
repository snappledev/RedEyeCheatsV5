#pragma once
#include "virtualFunction.h"
#include "steamhttp.h"
#include "interfaces.h"
class RedEyeNetwork
{
public:
	/*static auto SteamAPI_RegisterCallResult(VersionCheckCallback* callback, const SteamAPICall_t handle) -> void
	{
		static auto addr = Functions::GetProcOfModule("steam_api.dll", "SteamAPI_RegisterCallResult");
		reinterpret_cast<void(__cdecl*)(VersionCheckCallback*, SteamAPICall_t)>(addr)(callback, handle);
	}
	*/
	static auto GetISteamHTTP(const char* version) -> ISteamHTTP*
	{
		const auto steamclient_addr = Functions::GetProcOfModule("steam_api.dll", "SteamClient");
		const auto gethsteamuser_addr = Functions::GetProcOfModule("steam_api.dll", "SteamAPI_GetHSteamUser");
		const auto gethsteampipe_addr = Functions::GetProcOfModule("steam_api.dll", "SteamAPI_GetHSteamPipe");

		const auto thisptr = reinterpret_cast<void* (__cdecl*)()>(steamclient_addr)();
		const auto steamuser = reinterpret_cast<std::uint32_t(__cdecl*)()>(gethsteamuser_addr)();
		const auto steampipe = reinterpret_cast<std::uint32_t(__cdecl*)()>(gethsteampipe_addr)();

		const auto vfunc = virtualFunction<ISteamHTTP * (__thiscall*)(void*, std::uint32_t, std::uint32_t, const char*)>(thisptr, 23);

		return vfunc(thisptr, steamuser, steampipe, version);
	}
	void SendDataToUrl(std::string url, std::string data) {
		/*steamhhtp = GetISteamHTTP("STEAMHTTP_INTERFACE_VERSION002");

		const auto handle = steamhhtp->CreateHTTPRequest(EHTTPMethod::GET, "http://api.github.com/repos/namazso/nSkinz/commits");

		constexpr static auto build_time = std::integral_constant<time_t, time_t(cx::unix_time())>::value;

		steamhhtp->SetHTTPRequestGetOrPostParameter(handle, "variable", "data");

		SteamAPICall_t api_call;
		steamhttp->SendHTTPRequest(handle, &api_call);

		SteamAPI_RegisterCallResult(&s_check_callback, api_call);*/
	}
private:
	ISteamHTTP* steamhhtp;
};