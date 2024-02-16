#pragma once
#include "color.h"
#include <vector>
namespace variables
{
	namespace gui
	{
		namespace colors
		{
			extern int lighterBackgroundHuePlus;
			extern int index;
			extern color background;
			extern color primary;
			extern color control;
			extern color text;
		}
		extern int scaleFactor;
		extern bool bShowMainGui;
		extern bool bAlwaysTrue;
		extern bool testValue;
		extern int bMenuConstant;
	}
	namespace aimbot
	{
		extern int selectedWeapon;
		namespace rifles {
			extern int selectedTab;
			extern bool Enabled ;
			extern int key;
			extern bool enemies;
			extern bool team;
			namespace humanization
			{
				extern int smoothmovefactor;

				extern bool silent;
				extern int silentfov;
				extern int silenthitbox;
				extern bool silentnearest;
				extern int  silenthitchance;
				extern int silentstartbullet;
				
				extern float smooth;
				extern int fovpos;
				extern int fov;
				extern int hitbox;
				extern bool nearest;
				extern bool firstfiredelayenable;
				extern bool firstfiredelayauto;
				extern bool firstfiresilentdelayauto;
				extern bool firstfiredelayoneclick;
				extern int firstfiredelay;
				extern bool firstfiredelaysilent;
				extern bool targetswitchdelayenable;
				extern int targetswitchdelay;
				extern bool killstop;
				extern int EndBullet;
				extern int rcsx;
				extern int rcsy;
				extern bool rcs;
				extern int smoothrcs;
				extern int fovrcs;
				extern bool hitboxafter1b;
				extern int hitboxrcs;
				extern bool nearestRCS;
				extern bool rcsstandalone;
				extern bool fastzoom;
				
			}
			namespace triggerbot
			{
				extern bool enabled;
				extern bool team;
				extern bool enemies;
				extern int delay;
				extern int key;
				extern bool head;
				extern bool upperbody;
				extern bool lower;
				extern bool legs;
				extern bool arms;
			}
			namespace backtrack
			{
				extern bool enabled;
				extern int ticks;
			}

		}

		namespace smg {
			extern int selectedTab;
			extern bool Enabled;
			extern int key;
			extern bool enemies;
			extern bool team;
			namespace humanization
			{
				extern int smoothmovefactor;

				extern bool silent;
				extern int silentfov;
				extern int silenthitbox;
				extern bool silentnearest;
				extern int  silenthitchance;
				extern int silentstartbullet;
				
				extern float smooth;
				extern int fovpos;
				extern int fov;
				extern int hitbox;
				extern bool nearest;
				extern bool firstfiredelayenable;
				extern bool firstfiredelayauto;
				extern bool firstfiresilentdelayauto;
				extern bool firstfiredelayoneclick;
				extern int firstfiredelay;
				extern bool firstfiredelaysilent;
				extern bool targetswitchdelayenable;
				extern int targetswitchdelay;
				extern bool killstop;
				extern int EndBullet;
				extern int rcsx;
				extern int rcsy;
				extern bool rcs;
				extern int smoothrcs;
				extern int fovrcs;
				extern bool hitboxafter1b;
				extern int hitboxrcs;
				extern bool nearestRCS;
				extern bool rcsstandalone;
				extern bool fastzoom;

			}
			namespace triggerbot
			{
				extern bool enabled;
				extern bool team;
				extern bool enemies;
				extern int delay;
				extern int key;
				extern bool head;
				extern bool upperbody;
				extern bool lower;
				extern bool legs;
				extern bool arms;
			}
			namespace backtrack
			{
				extern bool enabled;
				extern int ticks;
			}
		}
		namespace autosniper {
			extern int selectedTab;
			extern bool Enabled;
			extern int key;
			extern bool enemies;
			extern bool team;
			namespace humanization
			{
				extern int smoothmovefactor;

				extern bool silent;
				extern int silentfov;
				extern int silenthitbox;
				extern bool silentnearest;
				extern int  silenthitchance;
				extern int silentstartbullet;
				
				extern float smooth;
				extern int fovpos;
				extern int fov;
				extern int hitbox;
				extern bool nearest;
				extern bool firstfiredelayenable;
				extern bool firstfiredelayauto;
				extern bool firstfiresilentdelayauto;
				extern bool firstfiredelayoneclick;
				extern int firstfiredelay;
				extern bool firstfiredelaysilent;
				extern bool targetswitchdelayenable;
				extern int targetswitchdelay;
				extern bool killstop;
				extern int EndBullet;
				extern int rcsx;
				extern int rcsy;
				extern bool rcs;
				extern int smoothrcs;
				extern int fovrcs;
				extern bool hitboxafter1b;
				extern int hitboxrcs;
				extern bool nearestRCS;
				extern bool rcsstandalone;
				extern bool fastzoom;

			}
			namespace triggerbot
			{
				extern bool enabled;
				extern bool team;
				extern bool enemies;
				extern int delay;
				extern int key;
				extern bool head;
				extern bool upperbody;
				extern bool lower;
				extern bool legs;
				extern bool arms;
			}
			namespace backtrack
			{
				extern bool enabled;
				extern int ticks;
			}
		}
		namespace awp {
			extern int selectedTab;
			extern bool Enabled;
			extern int key;
			extern bool enemies;
			extern bool team;
			namespace humanization
			{
				extern int smoothmovefactor;

				extern bool silent;
				extern int silentfov;
				extern int silenthitbox;
				extern bool silentnearest;
				extern int  silenthitchance;
				extern int silentstartbullet;
				
				extern float smooth;
				extern int fovpos;
				extern int fov;
				extern int hitbox;
				extern bool nearest;
				extern bool firstfiredelayenable;
				extern bool firstfiredelayauto;
				extern bool firstfiresilentdelayauto;
				extern bool firstfiredelayoneclick;
				extern int firstfiredelay;
				extern bool firstfiredelaysilent;
				extern bool targetswitchdelayenable;
				extern int targetswitchdelay;
				extern bool killstop;
				extern int EndBullet;
				extern bool rcs;
				extern int rcsx;
				extern int rcsy;
				extern int smoothrcs;
				extern int fovrcs;
				extern bool hitboxafter1b;
				extern int hitboxrcs;
				extern bool nearestRCS;
				extern bool rcsstandalone;
				extern bool fastzoom;

			}
			namespace triggerbot
			{
				extern bool enabled;
				extern bool team;
				extern bool enemies;
				extern int delay;
				extern int key;
				extern bool head;
				extern bool upperbody;
				extern bool lower;
				extern bool legs;
				extern bool arms;
			}
			namespace backtrack
			{
				extern bool enabled;
				extern int ticks;
			}
		}
		namespace scout {
			extern int selectedTab;
			extern bool Enabled;
			extern int key;
			extern bool enemies;
			extern bool team;
			namespace humanization
			{
				extern int smoothmovefactor;

				extern bool silent;
				extern int silentfov;
				extern int silenthitbox;
				extern bool silentnearest;
				extern int  silenthitchance;
				extern int silentstartbullet;
				
				extern float smooth;
				extern int fovpos;
				extern int fov;
				extern int hitbox;
				extern bool nearest;
				extern bool firstfiredelayenable;
				extern bool firstfiredelayauto;
				extern bool firstfiresilentdelayauto;
				extern bool firstfiredelayoneclick;
				extern int firstfiredelay;
				extern bool firstfiredelaysilent;
				extern bool targetswitchdelayenable;
				extern int targetswitchdelay;
				extern bool killstop;
				extern int EndBullet;
				extern bool rcs;
				extern int rcsx;
				extern int rcsy;
				extern int smoothrcs;
				extern int fovrcs;
				extern bool hitboxafter1b;
				extern int hitboxrcs;
				extern bool nearestRCS;
				extern bool rcsstandalone;
				extern bool fastzoom;

			}
			namespace triggerbot
			{
				extern bool enabled;
				extern bool team;
				extern bool enemies;
				extern int delay;
				extern int key;
				extern bool head;
				extern bool upperbody;
				extern bool lower;
				extern bool legs;
				extern bool arms;
			}
			namespace backtrack
			{
				extern bool enabled;
				extern int ticks;
			}
		}
		namespace pistols {
			extern int selectedTab;
			extern bool Enabled;
			extern int key;
			extern bool enemies;
			extern bool team;
			namespace humanization
			{
				extern int smoothmovefactor;

				extern bool silent;
				extern int silentfov;
				extern int silenthitbox;
				extern bool silentnearest;
				extern int  silenthitchance;
				extern int silentstartbullet;
				
				extern float smooth;
				extern int fovpos;
				extern int fov;
				extern int hitbox;
				extern bool nearest;
				extern bool firstfiredelayenable;
				extern bool firstfiredelayauto;
				extern bool firstfiresilentdelayauto;
				extern bool firstfiredelayoneclick;
				extern int firstfiredelay;
				extern bool firstfiredelaysilent;
				extern bool targetswitchdelayenable;
				extern int targetswitchdelay;
				extern bool killstop;
				extern int EndBullet;
				extern bool rcs;
				extern int rcsx;
				extern int rcsy;
				extern int smoothrcs;
				extern int fovrcs;
				extern bool hitboxafter1b;
				extern int hitboxrcs;
				extern bool nearestRCS;
				extern bool rcsstandalone;
				extern bool fastzoom;

			}
			namespace triggerbot
			{
				extern bool enabled;
				extern bool team;
				extern bool enemies;
				extern int delay;
				extern int key;
				extern bool head;
				extern bool upperbody;
				extern bool lower;
				extern bool legs;
				extern bool arms;
			}
			namespace backtrack
			{
				extern bool enabled;
				extern int ticks;
			}
		}
		namespace shotguns {
			extern int selectedTab;
			extern bool Enabled;
			extern int key;
			extern bool enemies;
			extern bool team;
			namespace humanization
			{
				extern int smoothmovefactor;

				extern bool silent;
				extern int silentfov;
				extern int silenthitbox;
				extern bool silentnearest;
				extern int  silenthitchance;
				extern int silentstartbullet;
				
				extern float smooth;
				extern int fovpos;
				extern int fov;
				extern int hitbox;
				extern bool nearest;
				extern bool firstfiredelayenable;
				extern bool firstfiredelayauto;
				extern bool firstfiresilentdelayauto;
				extern bool firstfiredelayoneclick;
				extern int firstfiredelay;
				extern bool firstfiredelaysilent;
				extern bool targetswitchdelayenable;
				extern int targetswitchdelay;
				extern bool killstop;
				extern int EndBullet;
				extern bool rcs;
				extern int rcsx;
				extern int rcsy;
				extern int smoothrcs;
				extern int fovrcs;
				extern bool hitboxafter1b;
				extern int hitboxrcs;
				extern bool nearestRCS;
				extern bool rcsstandalone;
				extern bool fastzoom;

			}
			namespace triggerbot
			{
				extern bool enabled;
				extern bool team;
				extern bool enemies;
				extern int delay;
				extern int key;
				extern bool head;
				extern bool upperbody;
				extern bool lower;
				extern bool legs;
				extern bool arms;
			}
			namespace backtrack
			{
				extern bool enabled;
				extern int ticks;
			}
		}
		namespace extra
		{
			extern int stopspec;
		}

	}
	namespace debug
	{
		extern std::vector<int> fpsData;
		extern bool main1;
		extern bool main2;
		extern bool main3;
		extern bool main4;
		extern bool main5;
		extern bool main6;
		extern bool main7;
		extern bool main8;
		extern bool main9;
		extern bool main10;
		extern bool main11;
		extern bool main12;
		extern bool main13;
		extern bool main14;
		extern bool main15;
		extern bool main16;
		extern bool main17;
		extern bool main18;
		extern bool main19;
		extern bool main20;
		extern bool main21;
		extern bool main22;
		extern bool main23;
		extern bool main24;
		extern bool main25;
		extern bool main26;
		extern bool main27;
		extern bool main28;
		extern bool main29;
		extern bool main30;
		extern bool main31;
		extern bool main32;
	}
	namespace esp
	{
		namespace enemies {
			extern bool enabled;
			extern bool visibleOnly;
			extern int healthbar;
			extern int box;
			extern bool boxOutline;
			extern int name;
			extern int weapon;
			extern int money;
			extern bool skeleton;
			extern int distance;
			extern int ammunition;
			extern int chams;
			extern bool barrel;
			extern bool chamsxqz;
			extern bool radar;
			extern bool cheatradar;
			extern bool backtrack;
			extern bool backtrackChams;
			extern int glow;
			extern bool lines;
			extern bool glowhealth;
			extern bool healthvalue;
			extern bool armorvalue;

			extern int reloadWarning;
			extern color reloadWarningVisible;
			extern color reloadWarningInvisible;
			extern int scopedWarning;
			extern color scopedWarningVisible;
			extern color scopedWarningInvisible;
			extern int defuseWarning;
			extern color defuseWarningVisible;
			extern color defuseWarningInvisible;
			extern int hostageWarning;
			extern color hostageWarningVisible;
			extern color hostageWarningInvisible;
			extern int helmetESP;
			extern color helmetESPVisible;
			extern color helmetESPInvisible;



			extern color boxVisible;
			extern color boxInvisible;
			extern color nameVisible;
			extern color nameInvisible;


			extern color weaponVisible;
			extern color weaponInvisible;

			extern color healthVisible;
			extern color healthInvisible;


			extern color moneyVisible;
			extern color moneyInvisible;
			extern color ammunitionVisible;
			extern color ammunitionInvisible;
			extern color chamsInvisible;
			extern color chamsVisible;

			extern color distanceInvisible;
			extern color distanceVisible;
			
			extern color barrelInvisible;
			extern color barrelVisible;

			extern color skeletonInvisible;
			extern color skeletonVisible;

			extern color glowVisible;
			extern color glowInvisible;
		}
		namespace team {
			extern bool enabled;
			extern bool visibleOnly;
			extern int healthbar;
			extern bool healthvalue;
			extern bool armorvalue;
			extern int box;
			extern bool boxOutline;
			extern int name;
			extern int weapon;
			extern int money;
			extern int distance;
			extern bool skeleton;
			extern bool lines;
			extern bool barrel;
			extern bool glowhealth;
			extern int ammunition;
			extern int chams;
			extern bool chamsxqz;
			extern bool radar;
			extern bool cheatradar;
			extern bool backtrack;
			extern bool backtrackChams;
			extern int glow;
			extern int reloadWarning;
			extern color reloadWarningVisible;
			extern color reloadWarningInvisible;
			extern int scopedWarning;
			extern color scopedWarningVisible;
			extern color scopedWarningInvisible;
			extern int defuseWarning;
			extern color defuseWarningVisible;
			extern color defuseWarningInvisible;
			extern int hostageWarning;
			extern color hostageWarningVisible;
			extern color hostageWarningInvisible;
			extern int helmetESP;
			extern color helmetESPVisible;
			extern color helmetESPInvisible;


			extern color boxVisible;
			extern color boxInvisible;
			extern color nameVisible;
			extern color nameInvisible;
			extern color weaponVisible;
			extern color weaponInvisible;
			extern color healthVisible;
			extern color healthInvisible;
			extern color moneyVisible;
			extern color moneyInvisible;
			extern color ammunitionVisible;
			extern color ammunitionInvisible;
			extern color chamsInvisible;
			extern color chamsVisible;
			extern color distanceInvisible;
			extern color distanceVisible;
			extern color barrelInvisible;
			extern color barrelVisible;
			extern color skeletonInvisible;
			extern color skeletonVisible;
			extern color glowVisible;
			extern color glowInvisible;
		}
		namespace grenades
		{
			extern bool enabled;
			extern bool dropped;
			extern bool thrown;
			extern int box;
			extern bool boxOutline;
			extern int name;
		}
		namespace weapons
		{
			extern bool enabled;
			extern int box;
			extern bool boxOutline;
			extern int name;
		}
		namespace C4
		{
			extern bool enabled;
			extern int box;
			extern bool boxOutline;
			extern int name;
			extern int chams;;
			extern bool XQZchams;

			extern bool detonationInfo;
			extern bool defuseInfo;
			extern std::string xx ;
		}
		namespace other
		{
			
			extern int crosshairs;
			extern bool spectators;
			extern bool damage;
			extern bool whocansee;
			extern int hitmarkers;
			extern bool DeathFlags;
			extern bool drawsilentfov;
			extern bool drawfov;
			extern bool bombHealth;
		}
	}
	namespace misc {
		extern bool floating;
		extern int bhop_probability;
		extern bool bhop_humanisation;
		extern bool autoStrafe;
		extern bool bhop;
		extern bool leftHandedKnife;
		extern bool revealranks;
		extern bool nightmode;
		extern int gamefov;
		extern int viewfov;
		extern bool autoPistol;
		extern int asus;
		extern std::string clantag;
		extern bool grenade;
		extern int trailParticles;
		extern int rateOfParticle;
		extern int mirrorview;
		extern int mapheight;
		extern int freemove;
		namespace statistics {
			extern int iHeadshots;
			extern int iKills;
			extern int iDeaths;
		}
	}
	namespace updates {
		extern int update;
	}
	namespace skinchanger
	{
		extern int selectedWeapon;
		extern bool Glock18Enabled;
		extern int Glock18Skin;
		extern int Glock18Wear;
		extern int Glock18Seed;
		extern int Glock18StatTrack;
		extern std::string Glock18Name;


		extern bool P250Enabled;
		extern int P250Skin;
		extern int P250Wear;
		extern int P250Seed;
		extern int P250StatTrack;
		extern std::string P250Name;

		extern bool DesertEagleEnabled;
		extern int DesertEagleSkin;
		extern int DesertEagleWear;
		extern int DesertEagleSeed;
		extern int DesertEagleStatTrack;
		extern std::string DesertEagleName;

		extern bool DualBerettasEnabled;
		extern int DualBerettasSkin;
		extern int DualBerettasWear;
		extern int DualBerettasSeed;
		extern int DualBerettasStatTrack;
		extern std::string DualBerettasName;

		extern bool Tec9Enabled;
		extern int Tec9Skin;
		extern int Tec9Wear;
		extern int Tec9Seed;
		extern int Tec9StatTrack;
		extern std::string Tec9Name;


		extern bool CZ75AutoEnabled;
		extern int CZ75AutoSkin;
		extern int CZ75AutoWear;
		extern int CZ75AutoSeed;
		extern int CZ75AutoStatTrack;
		extern std::string CZ75AutoName;


		extern bool R8RevolverEnabled;
		extern int R8RevolverSkin;
		extern int R8RevolverWear;
		extern int R8RevolverSeed;
		extern int R8RevolverStatTrack;
		extern std::string R8RevolverName;


		extern bool P2000Enabled;
		extern int P2000Skin;
		extern int P2000Wear;
		extern int P2000Seed;
		extern int P2000StatTrack;
		extern std::string P2000Name;

		extern bool USPSEnabled;
		extern int USPSSkin;
		extern int USPSWear;
		extern int USPSSeed;
		extern int USPSStatTrack;
		extern std::string USPSName;

		extern bool FiveSeveNEnabled;
		extern int FiveSeveNSkin;
		extern int FiveSeveNWear;
		extern int FiveSeveNSeed;
		extern int FiveSeveNStatTrack;
		extern std::string FiveSeveNName;

		extern bool NovaEnabled;
		extern int NovaSkin;
		extern int NovaWear;
		extern int NovaSeed;
		extern int NovaStatTrack;
		extern std::string NovaName;

		extern bool XM1014Enabled;
		extern int XM1014Skin;
		extern int XM1014Wear;
		extern int XM1014Seed;
		extern int XM1014StatTrack;
		extern std::string XM1014Name;

		extern bool SawedOffEnabled;
		extern int SawedOffSkin;
		extern int SawedOffWear;
		extern int SawedOffSeed;
		extern int SawedOffStatTrack;
		extern std::string SawedOffName;

		extern bool MAG7Enabled;
		extern int MAG7Skin;
		extern int MAG7Wear;
		extern int MAG7Seed;
		extern int MAG7StatTrack;
		extern std::string MAG7Name;

		extern bool MAC10Enabled;
		extern int MAC10Skin;
		extern int MAC10Wear;
		extern int MAC10Seed;
		extern int MAC10StatTrack;
		extern std::string MAC10Name;

		extern bool MP7Enabled;
		extern int MP7Skin;
		extern int MP7Wear;
		extern int MP7Seed;
		extern int MP7StatTrack;
		extern std::string MP7Name;



		extern bool MP5Enabled;
		extern int MP5Skin;
		extern int MP5Wear;
		extern int MP5Seed;
		extern int MP5StatTrack;
		extern std::string MP5Name;


		extern bool UMP45Enabled;
		extern int UMP45Skin;
		extern int UMP45Wear;
		extern int UMP45Seed;
		extern int UMP45StatTrack;
		extern std::string UMP45Name;


		extern bool PPBIZONEnabled;
		extern int PPBIZONSkin;
		extern int PPBIZONWear;
		extern int PPBIZONSeed;
		extern int PPBIZONStatTrack;
		extern std::string PPBIZONName;

		extern bool P90Enabled;
		extern int P90Skin;
		extern int P90Wear;
		extern int P90Seed;
		extern int P90StatTrack;
		extern std::string P90Name;

		extern bool MP9Enabled;
		extern int MP9Skin;
		extern int MP9Wear;
		extern int MP9Seed;
		extern int MP9StatTrack;
		extern std::string MP9Name;

		extern bool GalilAREnabled;
		extern int GalilARSkin;
		extern int GalilARWear;
		extern int GalilARSeed;
		extern int GalilARStatTrack;
		extern std::string GalilARName;


		extern bool FAMASEnabled;
		extern int FAMASSkin;
		extern int FAMASWear;
		extern int FAMASSeed;
		extern int FAMASStatTrack;
		extern std::string FAMASName;

		extern bool AK47Enabled;
		extern int AK47Skin;
		extern int AK47Wear;
		extern int AK47Seed;
		extern int AK47StatTrack;
		extern std::string AK47Name;


		extern bool M4A4Enabled;
		extern int M4A4Skin;
		extern int M4A4Wear;
		extern int M4A4Seed;
		extern int M4A4StatTrack;
		extern std::string M4A4Name;

		extern bool SSG08Enabled;
		extern int SSG08Skin;
		extern int SSG08Wear;
		extern int SSG08Seed;
		extern int SSG08StatTrack;
		extern std::string SSG08Name;


		extern bool M4A1SEnabled;
		extern int M4A1SSkin;
		extern int M4A1SWear;
		extern int M4A1SSeed;
		extern int M4A1SStatTrack;
		extern std::string M4A1SName;

		extern bool SG553Enabled;
		extern int SG553Skin;
		extern int SG553Wear;
		extern int SG553Seed;
		extern int SG553StatTrack;
		extern std::string SG553Name;

		extern bool AUGEnabled;
		extern int AUGSkin;
		extern int AUGWear;
		extern int AUGSeed;
		extern int AUGStatTrack;
		extern std::string AUGName;

		extern bool AWPEnabled;
		extern int AWPSkin;
		extern int AWPWear;
		extern int AWPSeed;
		extern int AWPStatTrack;
		extern std::string AWPName;


		extern bool G3SG1Enabled;
		extern int G3SG1Skin;
		extern int G3SG1Wear;
		extern int G3SG1Seed;
		extern int G3SG1StatTrack;
		extern std::string G3SG1Name;

		extern bool SCAR20Enabled;
		extern int SCAR20Skin;
		extern int SCAR20Wear;
		extern int SCAR20Seed;
		extern int SCAR20StatTrack;
		extern std::string SCAR20Name;


		extern bool M249Enabled;
		extern int M249Skin;
		extern int M249Wear;
		extern int M249Seed;
		extern int M249StatTrack;
		extern std::string M249Name;


		extern bool NegevEnabled;
		extern int NegevSkin;
		extern int NegevWear;
		extern int NegevSeed;
		extern int NegevStatTrack;
		extern std::string NegevName;


		extern bool C4Enabled;
		extern int C4Skin;
		extern int C4Wear;
		extern int C4Seed;
		extern int C4StatTrack;
		extern std::string C4Name;

		extern bool KnifeEnabled;
		extern int KnifeSkin;
		extern int KnifeWear;
		extern int KnifeSeed;
		extern int KnifeStatTrack;
		extern std::string KnifeName;

		extern bool GloveEnabled;
		extern int GloveSkin;
		extern int GloveWear;
		extern int GloveSeed;
		extern int GloveStatTrack;

		extern int KnifeModel;
		extern int GloveModel;
	}

}