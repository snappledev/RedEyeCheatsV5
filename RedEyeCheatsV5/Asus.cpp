#include "Asus.h"
#include "Interfaces.h"
#include "variables.h"
#include "crashhandler.h"
Asus asus;
void Asus::Peform()
{
	if (!interfaceManager::iengine) return;

	if (!interfaceManager::iengine->IsConnected() || !interfaceManager::iengine->IsInGame())
		ShouldApply = false;

	if (!ShouldApply)
	{

		crashhandler.setDebug("PreBefore");
		
		crashhandler.setDebug("Post");
		if (!Functions::is_bad_ptr(r_drawspecificstaticprop)) {
			r_drawspecificstaticprop->SetValue(1);
			for (auto i = interfaceManager::imaterial->FirstMaterial(); i != interfaceManager::imaterial->InvalidMaterial(); i = interfaceManager::imaterial->NextMaterial(i)) {
				IMaterial* mat = interfaceManager::imaterial->GetMaterial(i);
				if (Functions::is_bad_ptr(mat))
					continue;
				if (mat->IsErrorMaterial())
					continue;
				const char* texgroupname = mat->GetTextureGroupName();
				if (!strstr(texgroupname, xorStr("SkyBox"))) {
					if (strstr(texgroupname, xorStr("StaticProp"))) {
						mat->AlphaModulate(((double)variables::misc::asus) / 100.f);
						//mat->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, true);
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
		if (ValueChanged != variables::misc::asus) {
			ShouldApply = false;
			ValueChanged = variables::misc::asus;
		}
	}

}