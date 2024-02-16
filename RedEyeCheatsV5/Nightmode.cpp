#include "Nightmode.h"
#include "Interfaces.h"
#include "variables.h"
#include "crashhandler.h"
Nightmode nightmode;

void Nightmode::Peform()
{
	if (!interfaceManager::iengine) return;

	if (!interfaceManager::iengine->IsConnected() || !interfaceManager::iengine->IsInGame())
		ShouldApply = false;

	if (!ShouldApply)
	{

		crashhandler.setDebug("PreBefore");
		if (!Functions::is_bad_ptr(r_drawspecificstaticprop)) {


			r_drawspecificstaticprop->SetValue(1);
			crashhandler.setDebug("Post");
			static auto LoadNamedSky = reinterpret_cast<void(__fastcall*)(const char*)>(Functions::signature(interfaceManager::E, xorStr("55 8B EC 81 EC ? ? ? ? 56 57 8B F9 C7 45")));
			for (auto i = interfaceManager::imaterial->FirstMaterial(); i != interfaceManager::imaterial->InvalidMaterial(); i = interfaceManager::imaterial->NextMaterial(i)) {
				IMaterial* mat = interfaceManager::imaterial->GetMaterial(i);
				if (Functions::is_bad_ptr(mat))
					continue;
				if (mat->IsErrorMaterial())
					continue;
				float newAlph = ((double)variables::misc::asus) / 100.f;
				if (mat->IsTranslucent() && mat->GetAlphaModulation() != newAlph) continue;
				const char* texgroupname = mat->GetTextureGroupName();
				if (variables::misc::nightmode) {

					if (strstr(texgroupname, xorStr("Model"))) {
						mat->ColorModulate(0.6, 0.6, 0.6);
					}
					//World
					if (strstr(texgroupname, xorStr("World textures")) || strstr(texgroupname, xorStr("StaticProp"))) {
						mat->ColorModulate(0.1, 0.1, 0.13);
					}
					if (strstr(texgroupname, xorStr("SkyBox"))) {
						mat->ColorModulate(0.05, 0.05, 0.05);
					}
				}
				else {

					if (strstr(texgroupname, xorStr("Model"))) {
						mat->ColorModulate(1.f, 1.f, 1.f);
					}
					if (strstr(texgroupname, xorStr("World")) || strstr(texgroupname, xorStr("StaticProp"))) {
						mat->ColorModulate(1.f, 1.f, 1.f);
					}
					if (strstr(texgroupname, xorStr("SkyBox"))) {
						mat->ColorModulate(1.f, 1.f, 1.f);
					}
				}


			}
		}
		else {
			r_drawspecificstaticprop = interfaceManager::icvars->FindVar("r_drawspecificstaticprop");
		}
		ShouldApply = true;
	}
	else {
		if (ValueChanged != variables::misc::nightmode) {
			ShouldApply = false;
			ValueChanged = variables::misc::nightmode;
		}
	}

}