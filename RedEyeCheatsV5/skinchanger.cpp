#include "skinchanger.h"
#include "variables.h"
#include "interfaces.h"
#include "cBaseAttributableItem.h"
#include "cBaseCombatWeapon.h"
#include "cBaseWorldModel.h"
Skinchanger skinchanger;
#define SEQUENCE_DEFAULT_DRAW 0
#define SEQUENCE_DEFAULT_IDLE1 1
#define SEQUENCE_DEFAULT_IDLE2 2
#define SEQUENCE_DEFAULT_LIGHT_MISS1 3
#define SEQUENCE_DEFAULT_LIGHT_MISS2 4
#define SEQUENCE_DEFAULT_HEAVY_MISS1 9
#define SEQUENCE_DEFAULT_HEAVY_HIT1 10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB 11
#define SEQUENCE_DEFAULT_LOOKAT01 12
#define SEQUENCE_BUTTERFLY_DRAW 0
#define SEQUENCE_BUTTERFLY_DRAW2 1
#define SEQUENCE_BUTTERFLY_LOOKAT01 13
#define SEQUENCE_BUTTERFLY_LOOKAT03 15
#define SEQUENCE_FALCHION_IDLE1 1
#define SEQUENCE_FALCHION_HEAVY_MISS1 8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP 9
#define SEQUENCE_FALCHION_LOOKAT01 12
#define SEQUENCE_FALCHION_LOOKAT02 13
#define SEQUENCE_DAGGERS_IDLE1 1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 12
#define SEQUENCE_BOWIE_IDLE1 1
int randint(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}
SkinchangerWeapon Skinchanger::WeaponConfigFromIndex(int id)
{
	if (!m_vSkinchangerWeapons.empty()) {
		for (int i = 0; i < m_vSkinchangerWeapons.size(); i++) {
			if (id == m_vSkinchangerWeapons[i].itemdefinition)
				return m_vSkinchangerWeapons[i];
		}
	}
	return SkinchangerWeapon{ -1, -1, 0, -1, -1, "", -1 };
}
float Skinchanger::WearFromIndex(int index)
{
	switch (index) {
	case 0:
		return 0.000000001;
	case 1:
		return 0.08;
	case 2:
		return 0.17;
	case 3:
		return 0.38;
	case 4:
		return 0.54;
	default:
		return 0.0000001;
	}
}
int Skinchanger::SkinFromIndex(int index)
{
	if (!m_vSkins.empty()) {
		return m_vSkins[index].m_iIndex;
	}
	return -1;
}
int Skinchanger::GloveSkinFromIndex(int index)
{
	if (!m_vGloves.empty()) {
		return m_vGloves[index].m_iIndex;

	}
	return -1;
}
void Skinchanger::Sync()
{
	m_vSkinchangerWeapons.clear();
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_DEAGLE, variables::skinchanger::DesertEagleSkin, variables::skinchanger::DesertEagleEnabled, variables::skinchanger::DesertEagleSeed, variables::skinchanger::DesertEagleStatTrack, variables::skinchanger::DesertEagleName.c_str(),variables::skinchanger::DesertEagleWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_ELITE, variables::skinchanger::DualBerettasSkin, variables::skinchanger::DualBerettasEnabled, variables::skinchanger::DualBerettasSeed, variables::skinchanger::DualBerettasStatTrack, variables::skinchanger::DualBerettasName.c_str(),variables::skinchanger::DualBerettasWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_FAMAS, variables::skinchanger::FAMASSkin, variables::skinchanger::FiveSeveNEnabled, variables::skinchanger::FiveSeveNSeed, variables::skinchanger::FiveSeveNStatTrack, variables::skinchanger::FiveSeveNName.c_str(),variables::skinchanger::FiveSeveNWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_AK47, variables::skinchanger::AK47Skin, variables::skinchanger::AK47Enabled, variables::skinchanger::AK47Seed, variables::skinchanger::AK47StatTrack, variables::skinchanger::AK47Name.c_str(),variables::skinchanger::AK47Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_AUG, variables::skinchanger::AUGSkin, variables::skinchanger::AUGEnabled, variables::skinchanger::AUGSeed, variables::skinchanger::AUGStatTrack, variables::skinchanger::AUGName.c_str(),variables::skinchanger::AUGWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_AWP, variables::skinchanger::AWPSkin, variables::skinchanger::AWPEnabled, variables::skinchanger::AWPSeed, variables::skinchanger::AWPStatTrack, variables::skinchanger::AWPName.c_str(),variables::skinchanger::AWPWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_CZ75, variables::skinchanger::CZ75AutoSkin, variables::skinchanger::CZ75AutoEnabled, variables::skinchanger::CZ75AutoSeed, variables::skinchanger::CZ75AutoStatTrack, variables::skinchanger::CZ75AutoName.c_str(),variables::skinchanger::CZ75AutoWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_G3SG1, variables::skinchanger::G3SG1Skin, variables::skinchanger::G3SG1Enabled, variables::skinchanger::G3SG1Seed, variables::skinchanger::G3SG1StatTrack, variables::skinchanger::G3SG1Name.c_str(),variables::skinchanger::G3SG1Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_GALIL, variables::skinchanger::GalilARSkin, variables::skinchanger::GalilAREnabled, variables::skinchanger::GalilARSeed, variables::skinchanger::GalilARStatTrack, variables::skinchanger::GalilARName.c_str(),variables::skinchanger::GalilARWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_GLOCK, variables::skinchanger::Glock18Skin, variables::skinchanger::Glock18Enabled, variables::skinchanger::Glock18Seed, variables::skinchanger::Glock18StatTrack, variables::skinchanger::Glock18Name.c_str(),variables::skinchanger::Glock18Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_M249, variables::skinchanger::M249Skin, variables::skinchanger::M249Enabled, variables::skinchanger::M249Seed, variables::skinchanger::M249StatTrack, variables::skinchanger::M249Name.c_str(),variables::skinchanger::M249Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_M4A1S, variables::skinchanger::M4A1SSkin, variables::skinchanger::M4A1SEnabled, variables::skinchanger::M4A1SSeed, variables::skinchanger::M4A1SStatTrack, variables::skinchanger::M4A1SName.c_str(),variables::skinchanger::M4A1SWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_M4A4, variables::skinchanger::M4A4Skin, variables::skinchanger::M4A4Enabled, variables::skinchanger::M4A4Seed, variables::skinchanger::M4A4StatTrack, variables::skinchanger::M4A4Name.c_str(),variables::skinchanger::M4A4Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_MAC10, variables::skinchanger::MAC10Skin, variables::skinchanger::MAC10Enabled, variables::skinchanger::MAC10Seed, variables::skinchanger::MAC10StatTrack, variables::skinchanger::MAC10Name.c_str(),variables::skinchanger::MAC10Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_MAG7, variables::skinchanger::MAG7Skin, variables::skinchanger::MAG7Enabled, variables::skinchanger::MAG7Seed, variables::skinchanger::MAG7StatTrack, variables::skinchanger::MAG7Name.c_str(),variables::skinchanger::MAG7Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_MP5SD, variables::skinchanger::MP5Skin, variables::skinchanger::MP5Enabled, variables::skinchanger::MP5Seed, variables::skinchanger::MP5StatTrack, variables::skinchanger::MP5Name.c_str(),variables::skinchanger::MP5Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_MP7, variables::skinchanger::MP7Skin, variables::skinchanger::MP7Enabled, variables::skinchanger::MP7Seed, variables::skinchanger::MP7StatTrack, variables::skinchanger::MP7Name.c_str(),variables::skinchanger::MP7Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_MP9, variables::skinchanger::MP9Skin, variables::skinchanger::MP9Enabled, variables::skinchanger::MP9Seed, variables::skinchanger::MP9StatTrack, variables::skinchanger::MP9Name.c_str(),variables::skinchanger::MP9Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_NEGEV, variables::skinchanger::NegevSkin, variables::skinchanger::NegevEnabled, variables::skinchanger::NegevSeed, variables::skinchanger::NegevStatTrack, variables::skinchanger::NegevName.c_str(),variables::skinchanger::NegevWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_NOVA, variables::skinchanger::NovaSkin, variables::skinchanger::NovaEnabled, variables::skinchanger::NovaSeed, variables::skinchanger::NovaStatTrack, variables::skinchanger::NovaName.c_str(),variables::skinchanger::NovaWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_P2000, variables::skinchanger::P2000Skin, variables::skinchanger::P2000Enabled, variables::skinchanger::P2000Seed, variables::skinchanger::P2000StatTrack, variables::skinchanger::P2000Name.c_str(),variables::skinchanger::P2000Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_P250, variables::skinchanger::P250Skin, variables::skinchanger::P250Enabled, variables::skinchanger::P250Seed, variables::skinchanger::P250StatTrack, variables::skinchanger::P250Name.c_str(),variables::skinchanger::P250Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_P90, variables::skinchanger::P90Skin, variables::skinchanger::P90Enabled, variables::skinchanger::P90Seed, variables::skinchanger::P90StatTrack, variables::skinchanger::P90Name.c_str(),variables::skinchanger::P90Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_BIZON, variables::skinchanger::PPBIZONSkin, variables::skinchanger::PPBIZONEnabled, variables::skinchanger::PPBIZONSeed, variables::skinchanger::PPBIZONStatTrack, variables::skinchanger::PPBIZONName.c_str(),variables::skinchanger::PPBIZONWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_REVOLVER, variables::skinchanger::R8RevolverSkin, variables::skinchanger::R8RevolverEnabled, variables::skinchanger::R8RevolverSeed, variables::skinchanger::R8RevolverStatTrack, variables::skinchanger::R8RevolverName.c_str(),variables::skinchanger::R8RevolverWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_SAWEDOFF, variables::skinchanger::SawedOffSkin, variables::skinchanger::SawedOffEnabled, variables::skinchanger::SawedOffSeed, variables::skinchanger::SawedOffStatTrack, variables::skinchanger::SawedOffName.c_str(),variables::skinchanger::SawedOffWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_SCAR20, variables::skinchanger::SCAR20Skin, variables::skinchanger::SCAR20Enabled, variables::skinchanger::SCAR20Seed, variables::skinchanger::SCAR20StatTrack, variables::skinchanger::SCAR20Name.c_str(),variables::skinchanger::SCAR20Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_SSG08, variables::skinchanger::SSG08Skin, variables::skinchanger::SSG08Enabled, variables::skinchanger::SSG08Seed, variables::skinchanger::SSG08StatTrack, variables::skinchanger::SSG08Name.c_str(),variables::skinchanger::SSG08Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_SG553, variables::skinchanger::SG553Skin, variables::skinchanger::SG553Enabled, variables::skinchanger::SG553Seed, variables::skinchanger::SG553StatTrack, variables::skinchanger::SG553Name.c_str(),variables::skinchanger::SG553Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_TEC9, variables::skinchanger::Tec9Skin, variables::skinchanger::Tec9Enabled, variables::skinchanger::Tec9Seed, variables::skinchanger::Tec9StatTrack, variables::skinchanger::Tec9Name.c_str(),variables::skinchanger::Tec9Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_UMP45, variables::skinchanger::UMP45Skin, variables::skinchanger::UMP45Enabled, variables::skinchanger::UMP45Seed, variables::skinchanger::UMP45StatTrack, variables::skinchanger::UMP45Name.c_str(),variables::skinchanger::UMP45Wear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_USPS, variables::skinchanger::USPSSkin, variables::skinchanger::USPSEnabled, variables::skinchanger::USPSSeed, variables::skinchanger::USPSStatTrack, variables::skinchanger::USPSName.c_str(),variables::skinchanger::USPSWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_XM1014, variables::skinchanger::XM1014Skin, variables::skinchanger::XM1014Enabled, variables::skinchanger::XM1014Seed, variables::skinchanger::XM1014StatTrack, variables::skinchanger::XM1014Name.c_str(),variables::skinchanger::XM1014Wear });

	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_CSS, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_T, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_BAYONET, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_FLIP, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_GUT, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_TACTICAL, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_FALCHION, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_BUTTERFLY, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_PUSH, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_CORD, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_CANIS, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_STILETTO, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_URSUS, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_GYPSY_JACKKNIFE, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_OUTDOOR, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_WIDOWMAKER, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });
	m_vSkinchangerWeapons.push_back({ (int)ItemDefinitionIndex::WEAPON_KNIFE_SKELETON, variables::skinchanger::KnifeSkin, variables::skinchanger::KnifeEnabled, variables::skinchanger::KnifeSeed, variables::skinchanger::KnifeStatTrack, variables::skinchanger::KnifeName.c_str(),variables::skinchanger::KnifeWear });


	//Functions::CacheModel("models/weapons/v_knife_default_t.mdl");


}
const char* Skinchanger::ModelConfigFromIndex(int id)
{
	switch (id)
	{
	case (int)ItemDefinitionIndex::WEAPON_KNIFE:
		return xorStr("models/weapons/v_knife_default_ct.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_T:
		return xorStr("models/weapons/v_knife_default_t.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_BAYONET:
		return xorStr("models/weapons/v_knife_bayonet.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_FLIP:
		return xorStr("models/weapons/v_knife_flip.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_GUT:
		return xorStr("models/weapons/v_knife_gut.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT:
		return xorStr("models/weapons/v_knife_karam.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET:
		return xorStr("models/weapons/v_knife_m9_bay.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_TACTICAL:
		return xorStr("models/weapons/v_knife_tactical.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_FALCHION:
		return xorStr("models/weapons/v_knife_falchion_advanced.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_SURVIVAL_BOWIE:
		return xorStr("models/weapons/v_knife_survival_bowie.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_BUTTERFLY:
		return xorStr("models/weapons/v_knife_butterfly.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_PUSH:
		return xorStr("models/weapons/v_knife_push.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_URSUS:
		return xorStr("models/weapons/v_knife_ursus.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_GYPSY_JACKKNIFE:
		return xorStr("models/weapons/v_knife_gypsy_jackknife.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_STILETTO:
		return xorStr("models/weapons/v_knife_stiletto.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_WIDOWMAKER:
		return xorStr("models/weapons/v_knife_widowmaker.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_CORD:
		return xorStr("models/weapons/v_knife_cord.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_CANIS:
		return xorStr("models/weapons/v_knife_canis.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_OUTDOOR:
		return xorStr("models/weapons/v_knife_outdoor.mdl");
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_SKELETON:
		return xorStr("models/weapons/v_knife_skeleton.mdl");
	case (int)ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND:
		return xorStr("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl");
	case (int)ItemDefinitionIndex::GLOVE_T_SIDE:
		return xorStr("models/weapons/v_models/arms/glove_fingerless/v_glove_fingerless.mdl");
	case (int)ItemDefinitionIndex::GLOVE_CT_SIDE:
		return xorStr("models/weapons/v_models/arms/glove_hardknuckle/v_glove_hardknuckle.mdl");
	case (int)ItemDefinitionIndex::GLOVE_SPORTY:
		return xorStr("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl");
	case (int)ItemDefinitionIndex::GLOVE_SLICK:
		return xorStr("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl");
	case (int)ItemDefinitionIndex::GLOVE_LEATHER_WRAP:
		return xorStr("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl");
	case (int)ItemDefinitionIndex::GLOVE_MOTORCYCLE:
		return xorStr("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl");
	case (int)ItemDefinitionIndex::GLOVE_SPECIALIST:
		return xorStr("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl");
	case (int)ItemDefinitionIndex::GLOVE_HYDRA:
		return xorStr("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl");
	default:
		return xorStr("");
	}
	
}
int Skinchanger::CorrectSequence(const char* model, int sequence)
{
	if (model == xorStr("models/weapons/v_knife_butterfly.mdl"))
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_DRAW:
			return randint(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
		case SEQUENCE_DEFAULT_LOOKAT01:
			return randint(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03);
		default:
			return sequence + 1;
		}
	}
	else if (model == xorStr("models/weapons/v_knife_falchion_advanced.mdl"))
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_IDLE2:
			return SEQUENCE_FALCHION_IDLE1;
		case SEQUENCE_DEFAULT_HEAVY_MISS1:
			return randint(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP);
		case SEQUENCE_DEFAULT_LOOKAT01:
			return randint(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02);
		case SEQUENCE_DEFAULT_DRAW:
		case SEQUENCE_DEFAULT_IDLE1:
			return sequence;
		default:
			return sequence - 1;
		}
	}
	else if (model == xorStr("models/weapons/v_knife_push.mdl"))
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_IDLE2:
			return SEQUENCE_DAGGERS_IDLE1;
		case SEQUENCE_DEFAULT_LIGHT_MISS1:
		case SEQUENCE_DEFAULT_LIGHT_MISS2:
			return randint(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5);
		case SEQUENCE_DEFAULT_HEAVY_MISS1:
			return randint(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1);
		case SEQUENCE_DEFAULT_HEAVY_HIT1:
		case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
		case SEQUENCE_DEFAULT_LOOKAT01:
			return sequence + 3;
		case SEQUENCE_DEFAULT_DRAW:
		case SEQUENCE_DEFAULT_IDLE1:
			return sequence;
		default:
			return sequence + 2;
		}
	}
	else if (model == xorStr("models/weapons/v_knife_survival_bowie.mdl"))
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_DRAW:
		case SEQUENCE_DEFAULT_IDLE1:
			return sequence;
		case SEQUENCE_DEFAULT_IDLE2:
			return SEQUENCE_BOWIE_IDLE1;
		default:
			return sequence - 1;
		}
	}
	else if (model == xorStr("models/weapons/v_knife_ursus.mdl"))
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_DRAW:
			return randint(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
		case SEQUENCE_DEFAULT_LOOKAT01:
			return randint(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
		default:
			return sequence + 1;
		}
	}
	else if (model == xorStr("models/weapons/v_knife_stiletto.mdl"))
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_LOOKAT01:
			return randint(12, 13);
		}
	}
	else if (model == xorStr("models/weapons/v_knife_widowmaker.mdl"))
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_LOOKAT01:
			return randint(14, 15);
		}
	}
	else if (model == xorStr("models/weapons/v_knife_cord.mdl"))
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_DRAW:
			return randint(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
		case SEQUENCE_DEFAULT_LOOKAT01:
			return randint(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
		default:
			return sequence + 1;
		}
	}
	else if (model == xorStr("models/weapons/v_knife_canis.mdl"))
	{
	switch (sequence)
	{
		case SEQUENCE_DEFAULT_DRAW:
			return randint(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
		case SEQUENCE_DEFAULT_LOOKAT01:
			return randint(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
		default:
			return sequence + 1;
		}
	}
	else if (model == xorStr("models/weapons/v_knife_outdoor.mdl"))
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_DRAW:
			return randint(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
		case SEQUENCE_DEFAULT_LOOKAT01:
			return randint(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
		default:
			return sequence + 1;
		}
	}
	else if (model == xorStr("models/weapons/v_knife_skeleton.mdl"))
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_DRAW:
			return randint(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
		case SEQUENCE_DEFAULT_LOOKAT01:
			return randint(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
		default:
			return sequence + 1;
		}
	}
	return sequence;
}
ItemDefinitionIndex Skinchanger::KnifeToIndex()
{
	switch (variables::skinchanger::KnifeModel)
	{
	case 1:
		return ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT;
		break;
	case 2:
		return ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET;
		break;
	case 3:
		return  ItemDefinitionIndex::WEAPON_KNIFE_BAYONET;
		break;
	case 4:
		return ItemDefinitionIndex::WEAPON_KNIFE_TACTICAL;
		break;
	case 5:
		return ItemDefinitionIndex::WEAPON_KNIFE_FLIP;
		break;
	case 6:
		return ItemDefinitionIndex::WEAPON_KNIFE_GUT;
		break;
	case 7:
		return ItemDefinitionIndex::WEAPON_KNIFE_FALCHION;
		break;
	case 8:
		return ItemDefinitionIndex::WEAPON_KNIFE_SURVIVAL_BOWIE;
		break;
	case 9:
		return ItemDefinitionIndex::WEAPON_KNIFE_PUSH;
		break;
	case 10:
		return ItemDefinitionIndex::WEAPON_KNIFE_BUTTERFLY;
		break;
	case 11:
		return ItemDefinitionIndex::WEAPON_KNIFE_GYPSY_JACKKNIFE;
		break;
	case 12:
		return ItemDefinitionIndex::WEAPON_KNIFE_STILETTO;
		break;
	case 13:
		return ItemDefinitionIndex::WEAPON_KNIFE_URSUS;
		break;
	case 14:
		return ItemDefinitionIndex::WEAPON_KNIFE_WIDOWMAKER;
		break;
	case 15:
		return ItemDefinitionIndex::WEAPON_KNIFE_CORD;
		break;
	case 16:
		return ItemDefinitionIndex::WEAPON_KNIFE_CANIS;
		break;
	case 17:
		return ItemDefinitionIndex::WEAPON_KNIFE_OUTDOOR;
		break;
	case 18:
		return ItemDefinitionIndex::WEAPON_KNIFE_SKELETON;
		break;
	default:
		return ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT;
		break;
	}

}
ItemDefinitionIndex Skinchanger::GloveToIndex()
{
	switch (variables::skinchanger::GloveModel)
	{
	case 1:
		return ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND;
		break;
	case 2:
		return ItemDefinitionIndex::GLOVE_SLICK;
		break;
	case 3:
		return  ItemDefinitionIndex::GLOVE_LEATHER_WRAP;
		break;
	case 4:
		return ItemDefinitionIndex::GLOVE_MOTORCYCLE;
		break;
	case 5:
		return ItemDefinitionIndex::GLOVE_SPECIALIST;
		break;
	case 6:
		return ItemDefinitionIndex::GLOVE_SPORTY;
		break;
	case 7:
		return ItemDefinitionIndex::GLOVE_HYDRA;
		break;
	default:
		return ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND;
		break;
	}

}
void Skinchanger::CorrectSequences(CRecvProxyData* proxy, cBaseViewModel* model)
{
	if (Functions::is_bad_ptr(Game::local)) return;

	if (Game::local->m_iHealth() <= 0) return;
	cBasePlayer* m_owner = (cBasePlayer*)interfaceManager::ientitylist->getClientEntityFromHandle(model->m_hOwner());
	if (Functions::is_bad_ptr(m_owner)) return;
	if (m_owner != Game::local) return;
	cBaseAttributableItem* m_viewmodel = (cBaseAttributableItem*)interfaceManager::ientitylist->getClientEntityFromHandle(model->m_hWeapon());
	if (Functions::is_bad_ptr(m_viewmodel)) return;
	const char* config = ModelConfigFromIndex((int)m_viewmodel->m_iItemDefinitionIndex());
	if (config == xorStr("")) return;
	long& sequence = proxy->m_Value.m_Int;
	sequence = CorrectSequence(config, sequence);
	
}
bool Skinchanger::IsGlove(int id)
{
	switch (id)
	{
	case (int)ItemDefinitionIndex::GLOVE_CT_SIDE:
	case (int)ItemDefinitionIndex::GLOVE_HYDRA:
	case (int)ItemDefinitionIndex::GLOVE_LEATHER_WRAP:
	case (int)ItemDefinitionIndex::GLOVE_MOTORCYCLE:
	case (int)ItemDefinitionIndex::GLOVE_SLICK:
	case (int)ItemDefinitionIndex::GLOVE_SPECIALIST:
	case (int)ItemDefinitionIndex::GLOVE_SPORTY:
	case (int)ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND:
	case (int)ItemDefinitionIndex::GLOVE_T_SIDE:
		return true;
	}
	return false;
}
bool Skinchanger::IsKnife(int id)
{
	switch (id)
	{
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_BAYONET:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_SURVIVAL_BOWIE:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_BUTTERFLY:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_FALCHION:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_FLIP:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_GUT:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_PUSH:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_T:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_TACTICAL:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_GYPSY_JACKKNIFE:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_STILETTO:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_URSUS:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_WIDOWMAKER:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_CORD:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_CANIS:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_OUTDOOR:
	case (int)ItemDefinitionIndex::WEAPON_KNIFE_SKELETON:
		return true;
	}
	return false;
}
CreateClientClassFn getWearable() {
	ClientClass* m_Classes = interfaceManager::ibaseclient->GetAllClasses();
	while (m_Classes->m_ClassID != classid::CEconWearable)
		m_Classes = m_Classes->m_pNext;
	return m_Classes->m_pCreateFn;
}

cBaseAttributableItem* makeGlove(int entry, int serial) {
	static auto create_wearable_fn = getWearable();
	create_wearable_fn(entry, serial);
	cBaseAttributableItem* glove = (cBaseAttributableItem*)interfaceManager::ientitylist->getClientEntity(entry);
	assert(glove);
	static auto set_abs_origin_addr = Functions::signature(interfaceManager::clientModule, xorStr("55 8B EC 83 E4 F8 51 53 56 57 8B F1"));
	const auto set_abs_origin_fn = reinterpret_cast<void(__thiscall*)(void*, const Vector&)>(set_abs_origin_addr);
	static Vector new_pos = { 10000.f, 10000.f, 10000.f };
	set_abs_origin_fn(glove, new_pos);
	return glove;
}
void Skinchanger::applySkinConfigurations(cBaseAttributableItem* weapon, SkinchangerWeapon configuration, const unsigned xuidLow) {
	
	if (configuration.m_bmenuenabled) {
		if (configuration.m_imenuskin != -1) {
			int m_iSkin = SkinFromIndex(configuration.m_imenuskin);
			if (m_iSkin != -1) {
				ItemDefinitionIndex itemDefinitionIndex = weapon->m_iItemDefinitionIndex();
				weapon->m_nFallbackPaintKit() = m_iSkin;
				if (configuration.m_imenuseed != -1)
					weapon->m_nFallbackSeed() = configuration.m_imenuseed;
				if (configuration.m_imenustattrack != -1)
					weapon->m_nFallbackStatTrak() = configuration.m_imenustattrack;
				if (configuration.m_imenuwear != -1)
					weapon->m_flFallbackWear() = WearFromIndex(configuration.m_imenuwear);
				if (configuration.m_smenuname != "") {
					//char* m_szCustomName = &weapon->m_szCustomName();
					//snprintf(m_szCustomName, 32, "%s", configuration.m_smenuname.c_str());
				}
				ItemDefinitionIndex theoreticalIndex = KnifeToIndex();
				if (IsKnife((int)itemDefinitionIndex) && theoreticalIndex != itemDefinitionIndex) {
					weapon->m_iItemDefinitionIndex() = theoreticalIndex;
					const char* config = ModelConfigFromIndex((int)weapon->m_iItemDefinitionIndex());
					weapon->SetModelIndex(interfaceManager::imodelinfo->GetModelIndex(config));
				}
				weapon->m_iItemIDHigh() = -1;
				weapon->m_iAccountID() = xuidLow;
				weapon->m_OriginalOwnerXuidHigh() = 0;
				weapon->m_OriginalOwnerXuidLow() = 0;
			}
		}
		
	}
}
void Skinchanger::gloveChanger(cBasePlayer* local, uintptr_t xuidLow) {
	cBaseHandle* m_hWearables = (cBaseHandle*)&local->m_hMyWearables();
	static cBaseHandle m_hGloveHandle = 0;
	cBaseAttributableItem* m_Glove = (cBaseAttributableItem*)interfaceManager::ientitylist->getClientEntityFromHandle((PVOID)m_hWearables[0]);
	if (!m_Glove) {
		const auto m_newGlove = (cBaseAttributableItem*)interfaceManager::ientitylist->getClientEntityFromHandle((PVOID)m_hGloveHandle);
		if (m_newGlove) {
			m_hWearables[0] = m_hGloveHandle;
			m_Glove = m_newGlove;
		}
	}
	if (local->m_iHealth() <= 0) {
		if (m_Glove && m_hGloveHandle != 0xFFFFFFFF) {
			m_Glove->GetClientNetworkable()->SetDestroyedOnRecreateEntities();
			m_Glove->GetClientNetworkable()->Release();
		}
		return;
	}

	if (variables::skinchanger::GloveEnabled) {
		if (!m_Glove) {
			const auto newGloveIndex = interfaceManager::ientitylist->getHighestEntityIndex() + 1;
			const int iSerial = randint(0x0, 0xFFF);
			m_Glove = makeGlove(newGloveIndex, iSerial);
			m_hWearables[0] = (newGloveIndex | (iSerial << 16));
			m_hGloveHandle = m_hWearables[0];
		}
		if (m_Glove && variables::skinchanger::GloveModel != 0) {
			ItemDefinitionIndex theoreticalIndex = GloveToIndex();
			if (m_Glove->m_iItemDefinitionIndex() != theoreticalIndex) {
				SkinchangerWeapon configuration = WeaponConfigFromIndex((int)m_Glove->m_iItemDefinitionIndex());
				m_Glove->m_iItemDefinitionIndex() = GloveToIndex();
				m_Glove->m_iItemIDHigh() = -1;
				m_Glove->m_iEntityQuality() = 4;
				m_Glove->m_iAccountID() = xuidLow;
				m_Glove->m_flFallbackWear() = WearFromIndex(variables::skinchanger::GloveWear);
				m_Glove->m_nFallbackSeed() = 0;
				m_Glove->m_nFallbackStatTrak() = -1;
				m_Glove->m_nFallbackPaintKit() = GloveSkinFromIndex(variables::skinchanger::GloveSkin);
				int modelIndex = interfaceManager::imodelinfo->GetModelIndex(ModelConfigFromIndex((int)m_Glove->m_iItemDefinitionIndex()));
				m_Glove->SetModelIndex(modelIndex);
				cBaseViewModel* vModel = (cBaseViewModel*)m_Glove;
				vModel->SetModelIndex(modelIndex);
				if (m_Glove->m_Networkable())
					m_Glove->m_Networkable()->PreDataUpdate(0);
			}
		}

	}
}
void Skinchanger::Loop(cBasePlayer* local)
{
	if (!interfaceManager::iengine->IsConnected() ||
		!interfaceManager::iengine->IsInGame() ||
		!local) return;

	player_info_t local_info;
	if (!interfaceManager::iengine->GetPlayerInfo(interfaceManager::iengine->GetLocalPlayer(), &local_info))
		return;
	Sync();
	gloveChanger(local, local_info.xuid_low);
	cBaseHandle* m_hWeapons = (cBaseHandle*)&local->m_hMyWeapons();
	if (m_hWeapons) {
		for (int i = 0; m_hWeapons[i]; i++) {
			cBaseAttributableItem* m_Weapon = (cBaseAttributableItem*)interfaceManager::ientitylist->getClientEntityFromHandle((PVOID)m_hWeapons[i]);
			if (!m_Weapon) continue;
			SkinchangerWeapon configuration = WeaponConfigFromIndex((int)m_Weapon->m_iItemDefinitionIndex());
			applySkinConfigurations(m_Weapon, configuration, local_info.xuid_low);
		}
	}
	cBaseViewModel* m_LocalView = (cBaseViewModel*)interfaceManager::ientitylist->getClientEntityFromHandle((HANDLE)local->m_hViewModel());
	if (!m_LocalView) return;
	cBaseAttributableItem* m_localViewWeapon = (cBaseAttributableItem*)interfaceManager::ientitylist->getClientEntityFromHandle(m_LocalView->m_hWeapon());
	if (!m_localViewWeapon) return;
	if (IsKnife((int)m_localViewWeapon->m_iItemDefinitionIndex())) {
		const char* modelConfigIndex = ModelConfigFromIndex((int)m_localViewWeapon->m_iItemDefinitionIndex());
		int newModelIndex = interfaceManager::imodelinfo->GetModelIndex(modelConfigIndex);
		m_LocalView->m_nModelIndex() = newModelIndex;
		m_localViewWeapon->m_iViewModelIndex() = newModelIndex;
		cBaseWorldModel* m_WorldModel = (cBaseWorldModel*)interfaceManager::ientitylist->getClientEntityFromHandle(m_localViewWeapon->m_hWeaponWorldModel());
		if (!m_WorldModel) return;
		m_WorldModel->m_nModelIndex() = newModelIndex + 1;
	}


}
/*
void Skinchanger::Loop(cBasePlayer* local)
{
	if (!interfaceManager::iengine->IsConnected() || !interfaceManager::iengine->IsInGame() || Functions::is_bad_ptr(local))
		return;
	Sync();
	player_info_t localinfo;
	if (!interfaceManager::iengine->GetPlayerInfo(interfaceManager::iengine->GetLocalPlayer(), &localinfo)) return;

	HANDLE* weapons = (HANDLE*)local->m_hMyWeapons();
	if (weapons) {
		for (int i = 0; weapons[i]; i++)
		{
			cBaseAttributableItem* weapon = (cBaseAttributableItem*)interfaceManager::ientitylist->getClientEntityFromHandle((HANDLE)weapons[i]);
			if (!weapon) continue;

			SkinchangerWeapon configuration = WeaponConfigFromIndex((int)weapon->m_iItemDefinitionIndex());
			if (configuration.m_bmenuenabled) {
				if (configuration.m_imenuskin != -1) {
					int m_iSkin = SkinFromIndex(configuration.m_imenuskin);
					if (m_iSkin != -1) {
						weapon->m_nFallbackPaintKit() = m_iSkin;

						if (configuration.m_imenuseed != -1)
							weapon->m_nFallbackSeed() = configuration.m_imenuseed;

						if (configuration.m_imenustattrack != -1)
							weapon->m_nFallbackStatTrak() = configuration.m_imenustattrack;

						if (configuration.m_imenuwear != -1)
							weapon->m_flFallbackWear() = WearFromIndex(configuration.m_imenuwear);

						if (configuration.m_smenuname != "") {
							char* m_szCustomName = &weapon->m_szCustomName();
							strcpy_s(m_szCustomName, 128, configuration.m_smenuname.c_str());
						}
						const char* config = ModelConfigFromIndex((int)weapon->m_iItemDefinitionIndex());
						if (IsKnife((int)weapon->m_iItemDefinitionIndex())) {
							weapon->m_iItemDefinitionIndex() = KnifeToIndex();
							weapon->SetModelIndex(interfaceManager::imodelinfo->GetModelIndex(config));
							
						}
						weapon->m_iItemIDHigh() = -1;
						weapon->m_iAccountID() = localinfo.xuid_low;
						weapon->m_OriginalOwnerXuidHigh() = 0;
						weapon->m_OriginalOwnerXuidLow() = 0;
					}
				}
			}
		}
	}

	const auto m_viewModel = (cBaseViewModel*)interfaceManager::ientitylist->getClientEntityFromHandle(local->m_hViewModel());
	if (m_viewModel) {
		const auto weapon = (cBaseCombatWeapon*)interfaceManager::ientitylist->getClientEntityFromHandle(m_viewModel->m_hWeapon());
		if (weapon) {
			if (IsKnife((int)weapon->m_iItemDefinitionIndex())) {
				const char* config = ModelConfigFromIndex((int)weapon->m_iItemDefinitionIndex());
				m_viewModel->m_nModelIndex() = interfaceManager::imodelinfo->GetModelIndex(config);
				m_viewModel->vm_nModelIndex() = interfaceManager::imodelinfo->GetModelIndex(config);;
				cBaseWorldModel* m_hWorldModel = (cBaseWorldModel*)interfaceManager::ientitylist->getClientEntityFromHandle(weapon->m_hWeaponWorldModel());
				if (m_hWorldModel) {
					m_hWorldModel->m_nModelIndex() = interfaceManager::imodelinfo->GetModelIndex(config) + 1;
				}
			}
		}
	}






	static bool glovescreated;
	UINT* Wearables = (UINT*)& local->m_hMyWearables();
	static UINT m_hGlove = 0xFFFFFFFF;
	cBaseAttributableItem* glove = (cBaseAttributableItem*)interfaceManager::ientitylist->getClientEntityFromHandle((UINT*)Wearables[0]);
	if (!glove) {
		cBaseAttributableItem* currentglove = (cBaseAttributableItem*)interfaceManager::ientitylist->getClientEntityFromHandle((UINT*)m_hGlove);
		if (currentglove) {
			Wearables[0] = m_hGlove;
			glove = currentglove;
		}
	}
	if (!local || local->m_iHealth() <= 0) {
		if (glove && m_hGlove != 0xFFFFFFFF) {
			glove->m_Networkable()->SetDestroyedOnRecreateEntities();
			glove->m_Networkable()->Release();
		}
		return;
	}
	if (variables::skinchanger::GloveEnabled) {
		if (!glove) {
			for (ClientClass* Class = interfaceManager::ibaseclient->GetAllClasses(); Class; Class = Class->m_pNext) {
				if (!Class) continue;
				if (Class->m_ClassID == classid::CEconWearable) {
					int iEntry = interfaceManager::ientitylist->getHighestEntityIndex() + 1;
					int iSerial = randint(0x0, 0xFFF);
					if (Class->m_pCreateFn(iEntry, iSerial))
					{
						Wearables[0] = iEntry | (iSerial << 16);
						glove = (cBaseAttributableItem*)interfaceManager::ientitylist->getClientEntityFromHandle((UINT*)Wearables[0]);
						m_hGlove = Wearables[0];
						break;
					}
				}
			}

			glove->m_nFallbackPaintKit() = GloveSkinFromIndex(variables::skinchanger::GloveSkin);
			glove->m_iItemDefinitionIndex() = GloveToIndex();
			glove->SetModelIndex(interfaceManager::imodelinfo->GetModelIndex(ModelConfigFromIndex((int)glove->m_iItemDefinitionIndex())));
			glove->m_flFallbackWear() = WearFromIndex(variables::skinchanger::GloveWear);
			glove->m_iEntityQuality() = 4;
			glove->m_iIndex() = -1;
			glove->m_nFallbackSeed() = -1;
			glove->m_nFallbackStatTrak() = -1;
			glove->m_iItemIDHigh() = -1;
			glove->m_iAccountID() = localinfo.xuid_low;
			glove->m_OriginalOwnerXuidHigh() = 0;
			glove->m_OriginalOwnerXuidLow() = 0;
			if (glove) {
				if (glove->m_Networkable())
					glove->m_Networkable()->PreDataUpdate(0);
			}


		}
	}

	/*if (local->m_iHealth() != 0 && variables::skinchanger::GloveEnabled)
	{
		if (!interfaceManager::entitylist->GetClientEntityFromHandle((UINT*)Wearables[0]))
		{
			for (ClientClass* Class = interfaceManager::ibaseclient->GetAllClasses(); Class; Class = Class->m_pNext)
			{
				if (Class->m_ClassID == classid::CEconWearable)
				{
					int iEntry = interfaceManager::entitylist->GetHighestEntityIndex() + 1;
					int iSerial = randint(0x0, 0xFFF);
					if (Class->m_pCreateFn(iEntry, iSerial))
					{
						Wearables[0] = iEntry | (iSerial << 16);
						glovescreated = true;
						break;
					}
				}
			}

			if (Wearables[0]) {
				CBaseAttributableItem* gloves = (CBaseAttributableItem*)interfaceManager::entitylist->GetClientEntityFromHandle((UINT*)Wearables[0]);
				if (!Help::is_bad_ptr(gloves)) {


					gloves->m_nFallbackPaintKit() = 10008; //SKIN//GloveSkinFromName(m_vGloves[variables::skinchanger::GloveSkin].m_sName);
					gloves->m_iItemDefinitionIndex() = ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND; //GloveToIndex();
					gloves->SetModelIndex(interfaceManager::modelinfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));

					gloves->m_flFallbackWear() = 0.000001;
					gloves->m_iEntityQuality() = 4;
					gloves->m_nFallbackSeed() = -1;
					gloves->m_nFallbackStatTrak() = -1;
					gloves->m_iItemIDHigh() = -1;
					gloves->m_iAccountID() = localinfo.xuid_low;
					gloves->m_OriginalOwnerXuidHigh() = 0;
					gloves->m_OriginalOwnerXuidLow() = 0;

					if (gloves->m_Networkable())
						gloves->m_Networkable()->PreDataUpdate(0);

				}
				/*if (gloves) {
					switch (variables::skinchanger::GloveSkin)
					{
					case 0:
						*m_nFallbackPaintKit = 10008; //SKIN
						break;
					case 1:
						*m_nFallbackPaintKit = 10007; //SKIN
						break;
					case 2:
						*m_nFallbackPaintKit = 10006; //SKIN
						break;
					case 3:
						*m_nFallbackPaintKit = 10039; //SKIN
						break;
					case 4:
						*m_nFallbackPaintKit = 10013; //SKIN
						break;
					case 5:
						*m_nFallbackPaintKit = 10016; //SKIN
						break;
					case 6:
						*m_nFallbackPaintKit = 10040; //SKIN
						break;
					case 7:
						*m_nFallbackPaintKit = 10015; //SKIN
						break;
					case 8:
						*m_nFallbackPaintKit = 10021; //SKIN
						break;
					case 9:
						*m_nFallbackPaintKit = 10010; //SKIN
						break;
					case 10:
						*m_nFallbackPaintKit = 10009; //SKIN
						break;
					case 11:
						*m_nFallbackPaintKit = 10036; //SKIN
						break;
					case 12:
						*m_nFallbackPaintKit = 10026; //SKIN
						break;
					case 13:
						*m_nFallbackPaintKit = 10028; //SKIN
						break;
					case 14:
						*m_nFallbackPaintKit = 10027; //SKIN
						break;
					case 15:
						*m_nFallbackPaintKit = 10024; //SKIN
						break;
					case 16:
						*m_nFallbackPaintKit = 10033; //SKIN
						break;
					case 17:
						*m_nFallbackPaintKit = 10035; //SKIN
						break;
					case 18:
						*m_nFallbackPaintKit = 10034; //SKIN
						break;
					case 19:
						*m_nFallbackPaintKit = 10030; //SKIN
						break;
					case 20:
						*m_nFallbackPaintKit = 10037; //SKIN
						break;
					case 21:
						*m_nFallbackPaintKit = 10018; //SKIN
						break;
					case 22:
						*m_nFallbackPaintKit = 10019; //SKIN
						break;
					case 23:
						*m_nFallbackPaintKit = 10038; //SKIN
						break;
					}

					int IndexH = interfaceManager::modelinfo->GetModelIndex(xorStr("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
					int IndexB = interfaceManager::modelinfo->GetModelIndex(xorStr("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));
					int IndexS = interfaceManager::modelinfo->GetModelIndex(xorStr("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
					int IndexM = interfaceManager::modelinfo->GetModelIndex(xorStr("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
					int IndexT = interfaceManager::modelinfo->GetModelIndex(xorStr("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
					int IndexY = interfaceManager::modelinfo->GetModelIndex(xorStr("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
					int IndexC = interfaceManager::modelinfo->GetModelIndex(xorStr("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));

					switch (variables::skinchanger::GloveModel)
					{
					case 1:
						*m_iItemDefinitionIndex = 5027; //BLOODHOUND
						gloves->SetModelIndex(IndexB);
						break;
					case 2:

						*m_iItemDefinitionIndex = 5031; //BLOODHOUND
						gloves->SetModelIndex(IndexS);
						break;
					case 3:
						*m_iItemDefinitionIndex = 5032; //BLOODHOUND
						gloves->SetModelIndex(IndexH);
						break;
					case 4:
						*m_iItemDefinitionIndex = 5033; //BLOODHOUND
						gloves->SetModelIndex(IndexM);
						break;
					case 5:
						*m_iItemDefinitionIndex = 5034; //BLOODHOUND
						gloves->SetModelIndex(IndexT);
						break;
					case 6:
						*m_iItemDefinitionIndex = 5030; //BLOODHOUND
						gloves->SetModelIndex(IndexY);
						break;
					default:
						break;

					}
					gloves->m_iEntityQuality() = 4;
					gloves->m_nFallbackSeed() = 0;
					gloves->m_nFallbackStatTrak() = -1;
					gloves->m_iItemIDHigh() = -1;
					gloves->m_iAccountID() = localinfo.xuid_low;
					gloves->m_OriginalOwnerXuidHigh() = 0;
					gloves->m_OriginalOwnerXuidLow() = 0;

					if (gloves->m_Networkable())
						gloves->m_Networkable()->PreDataUpdate(0);
				}
			}
		}
	}*/


//}

bool Skinchanger::FindKits()
{
	const auto UCSToUTF8 = static_cast<int(*)(const wchar_t* ucs2, char* utf8, int len)>(Functions::GetProcOfModule(xorStr("vstdlib.dll"), xorStr("V_UCS2ToUTF8")));
	const auto m_ItemSystem = Functions::pattern((PCHAR)xorStr("client.dll"), (PCHAR)xorStr("\xE8\x00\x00\x00\x00\xFF\x76\x0C\x8D\x48\x04\xE8"), (PCHAR)xorStr("x????xxxxxxx"), 0);
	const auto m_ItemSystemOff = *reinterpret_cast<std::int32_t*>(m_ItemSystem + 1);
	const auto m_ItemSystemFn = reinterpret_cast<CCStrike15ItemSystem * (*)()>(m_ItemSystem + 5 + m_ItemSystemOff);
	CCStrike15ItemSchema* m_ItemSchema = reinterpret_cast<CCStrike15ItemSchema*>(std::uintptr_t(m_ItemSystemFn()) + sizeof(void*));
	int32_t m_PaintKitDefinitionOff = *reinterpret_cast<int32_t*>(m_ItemSystem + 12);
	const auto m_PaintKitDefinitionFn = reinterpret_cast<PaintKit * (__thiscall*)(CCStrike15ItemSchema*, int)>(m_ItemSystem + 16 + m_PaintKitDefinitionOff);
	const auto m_StartElement = *reinterpret_cast<std::intptr_t*>(std::uintptr_t(m_PaintKitDefinitionFn) + 10);
	const auto m_HeadOff = m_StartElement - 12;
	const auto m_HeadMap = reinterpret_cast<Head_t<int, PaintKit*>*>(std::uintptr_t(m_ItemSchema) + m_HeadOff);

	for (auto i = 0; i <= m_HeadMap->last_element; ++i)
	{
		const auto m_Kit = m_HeadMap->memory[i].value;
		if (m_Kit->id == 9001) continue;
		const auto wide_name = interfaceManager::ilocalize->Find(m_Kit->item_name.buffer + 1);
		char name[256];
		UCSToUTF8(wide_name, name, sizeof(name));
		int v = 0;
		if (!m_vSkins.empty()) {
			for (int i = 0; i < m_vSkins.size(); i++) {
				if (m_vSkins[i].m_sName.find(name) != std::string::npos)
					v++;
			}
		}

		if (m_Kit->id < 10000) {
			m_vSkins.push_back({ m_Kit->id, name + (v == 0 ? "" : xorStr(" ") + std::to_string(v)) });
		}
		else
			m_vGloves.push_back({ m_Kit->id, name });
	}


	return true;
}
