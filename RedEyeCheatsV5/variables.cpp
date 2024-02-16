#pragma once
#include "color.h"
#include <Windows.h>
#include <string>
#include "xor.h"
#include "variables.h"
namespace variables
{
	namespace gui
	{

		namespace colors
		{
			int index = 0;
			int lighterBackgroundHuePlus = 15;
			color background = color(18, 18, 18, 255);;
			color primary = color(244, 40, 40, 255);
			color control = color(255, 255, 0, 255);
			color text = color(255, 255, 255, 255);
		}
		int scaleFactor = 1.f;
		int bMenuConstant = 1;
		bool bShowMainGui = true;
		bool bAlwaysTrue = true;
		bool testValue = true;
	}
	namespace aimbot
	{
		int selectedWeapon = 0;
		namespace rifles {
			int selectedTab = 0;
			bool Enabled = true;
			int key = VK_LBUTTON;
			bool enemies = true;
			bool team = false;
			namespace humanization
			{
				int smoothmovefactor = 0;

				bool silent = false;
				int silentfov = 2;
				int silenthitbox = 0;
				bool silentnearest = false;
				int  silenthitchance = 100;
				int silentstartbullet = 0;
				
				float smooth = 70;
				int fovpos = 1;
				int fov = 10;
				int hitbox = 0;
				bool nearest = false;
				bool firstfiredelayenable = false;
				bool firstfiredelayauto = false;
				bool firstfiresilentdelayauto = false;
				bool firstfiredelayoneclick = false;
				int firstfiredelay = 0;
				bool firstfiredelaysilent = false;
				bool targetswitchdelayenable = false;
				int targetswitchdelay = 0;
				bool killstop = false;
				int EndBullet = -1;
				int rcsx = 100;
				int rcsy = 100;
				bool rcs = true;
				int smoothrcs = 0;
				int fovrcs = 0;
				bool hitboxafter1b = false;
				int hitboxrcs = 0;
				bool nearestRCS = false;
				bool rcsstandalone = false;


				bool fastzoom = false;

			}
			namespace triggerbot
			{
				bool enabled = false;
				bool team = false;
				bool enemies = true;
				int delay = 0;
				int key = -1;
				bool head = true;
				bool upperbody = true;
				bool lower = false;
				bool legs = false;
				bool arms = false;
			}
			namespace backtrack
			{
				bool enabled = false;
				int ticks = 16;
			}

		}
		namespace smg {
			int selectedTab = 0;
			bool Enabled = true;
			int key = VK_LBUTTON;
			bool enemies = true;
			bool team = false;
			namespace humanization
			{
				int smoothmovefactor = 0;

				bool silent = false;
				int silentfov = 2;
				int silenthitbox = 0;
				bool silentnearest = false;
				int  silenthitchance = 100;
				int silentstartbullet = 0;
				
				float smooth = 70;
				int fovpos = 1;
				int fov = 10;
				int hitbox = 0;
				bool nearest = false;
				bool firstfiredelayenable = false;
				bool firstfiredelayauto = false;
				bool firstfiresilentdelayauto = false;
				bool firstfiredelayoneclick = false;
				int firstfiredelay = 0;
				bool firstfiredelaysilent = false;
				bool targetswitchdelayenable = false;
				int targetswitchdelay = 0;
				bool killstop = false;
				int EndBullet = -1;
				int rcsx = 100;
				int rcsy = 100;
				bool rcs = true;
				int smoothrcs = 0;
				int fovrcs = 0;
				bool hitboxafter1b = false;
				int hitboxrcs = 0;
				bool nearestRCS = false;
				bool rcsstandalone = false;


				bool fastzoom = false;

			}
			namespace triggerbot
			{
				bool enabled = false;
				bool team = false;
				bool enemies = true;
				int delay = 0;
				int key = -1;
				bool head = true;
				bool upperbody = true;
				bool lower = false;
				bool legs = false;
				bool arms = false;
			}
			namespace backtrack
			{
				bool enabled = false;
				int ticks = 16;
			}

		}
		namespace autosniper {
			int selectedTab = 0;
			bool Enabled = true;
			int key = VK_LBUTTON;
			bool enemies = true;
			bool team = false;
			namespace humanization
			{
				int smoothmovefactor = 0;

				bool silent = false;
				int silentfov = 2;
				int silenthitbox = 0;
				bool silentnearest = false;
				int  silenthitchance = 100;
				int silentstartbullet = 0;
				
				float smooth = 70;
				int fovpos = 1;
				int fov = 10;
				int hitbox = 0;
				bool nearest = false;
				bool firstfiredelayenable = false;
				bool firstfiredelayauto = false;
				bool firstfiresilentdelayauto = false;
				bool firstfiredelayoneclick = false;
				int firstfiredelay = 0;
				bool firstfiredelaysilent = false;
				bool targetswitchdelayenable = false;
				int targetswitchdelay = 0;
				bool killstop = false;
				int EndBullet = -1;
				int rcsx = 100;
				int rcsy = 100;
				bool rcs = true;
				int smoothrcs = 0;
				int fovrcs = 0;
				bool hitboxafter1b = false;
				int hitboxrcs = 0;
				bool nearestRCS = false;
				bool rcsstandalone = false;


				bool fastzoom = false;

			}
			namespace triggerbot
			{
				bool enabled = false;
				bool team = false;
				bool enemies = true;
				int delay = 0;
				int key = -1;
				bool head = true;
				bool upperbody = true;
				bool lower = false;
				bool legs = false;
				bool arms = false;
			}
			namespace backtrack
			{
				bool enabled = false;
				int ticks = 16;
			}

		}
		namespace awp {
			int selectedTab = 0;
			bool Enabled = true;
			int key = VK_LBUTTON;
			bool enemies = true;
			bool team = false;
			namespace humanization
			{
				int smoothmovefactor = 0;

				bool silent = false;
				int silentfov = 2;
				int silenthitbox = 0;
				bool silentnearest = false;
				int  silenthitchance = 100;
				int silentstartbullet = 0;
				
				float smooth = 70;
				int fovpos = 1;
				int fov = 10;
				int hitbox = 0;
				bool nearest = false;
				bool firstfiredelayenable = false;
				bool firstfiredelayauto = false;
				bool firstfiresilentdelayauto = false;
				bool firstfiredelayoneclick = false;
				int firstfiredelay = 0;
				bool firstfiredelaysilent = false;
				bool targetswitchdelayenable = false;
				int targetswitchdelay = 0;
				bool killstop = false;
				int EndBullet = -1;
				int rcsx = 100;
				int rcsy = 100;
				bool rcs = true;
				int smoothrcs = 0;
				int fovrcs = 0;
				bool hitboxafter1b = false;
				int hitboxrcs = 0;
				bool nearestRCS = false;
				bool rcsstandalone = false;


				bool fastzoom = false;

			}
			namespace triggerbot
			{
				bool enabled = false;
				bool team = false;
				bool enemies = true;
				int delay = 0;
				int key = -1;
				bool head = true;
				bool upperbody = true;
				bool lower = false;
				bool legs = false;
				bool arms = false;
			}
			namespace backtrack
			{
				bool enabled = false;
				int ticks = 16;
			}
		}
		namespace scout {
			int selectedTab = 0;
			bool Enabled = true;
			int key = VK_LBUTTON;
			bool enemies = true;
			bool team = false;
			namespace humanization
			{
				int smoothmovefactor = 0;

				bool silent = false;
				int silentfov = 2;
				int silenthitbox = 0;
				bool silentnearest = false;
				int  silenthitchance = 100;
				int silentstartbullet = 0;
				
				float smooth = 70;
				int fovpos = 1;
				int fov = 10;
				int hitbox = 0;
				bool nearest = false;
				bool firstfiredelayenable = false;
				bool firstfiredelayauto = false;
				bool firstfiresilentdelayauto = false;
				bool firstfiredelayoneclick = false;
				int firstfiredelay = 0;
				bool firstfiredelaysilent = false;
				bool targetswitchdelayenable = false;
				int targetswitchdelay = 0;
				bool killstop = false;
				int EndBullet = -1;
				int rcsx = 100;
				int rcsy = 100;
				bool rcs = true;
				int smoothrcs = 0;
				int fovrcs = 0;
				bool hitboxafter1b = false;
				int hitboxrcs = 0;
				bool nearestRCS = false;
				bool rcsstandalone = false;


				bool fastzoom = false;

			}
			namespace triggerbot
			{
				bool enabled = false;
				bool team = false;
				bool enemies = true;
				int delay = 0;
				int key = -1;
				bool head = true;
				bool upperbody = true;
				bool lower = false;
				bool legs = false;
				bool arms = false;
			}
			namespace backtrack
			{
				bool enabled = false;
				int ticks = 16;
			}

		}
		namespace pistols {
			int selectedTab = 0;
			bool Enabled = true;
			int key = VK_LBUTTON;
			bool enemies = true;
			bool team = false;
			namespace humanization
			{
				int smoothmovefactor = 0;

				bool silent = false;
				int silentfov = 2;
				int silenthitbox = 0;
				bool silentnearest = false;
				int  silenthitchance = 100;
				int silentstartbullet = 0;
				
				float smooth = 70;
				int fovpos = 1;
				int fov = 10;
				int hitbox = 0;
				bool nearest = false;
				bool firstfiredelayenable = false;
				bool firstfiredelayauto = false;
				bool firstfiresilentdelayauto = false;
				bool firstfiredelayoneclick = false;
				int firstfiredelay = 0;
				bool firstfiredelaysilent = false;
				bool targetswitchdelayenable = false;
				int targetswitchdelay = 0;
				bool killstop = false;
				int EndBullet = -1;
				int rcsx = 100;
				int rcsy = 100;
				bool rcs = true;
				int smoothrcs = 0;
				int fovrcs = 0;
				bool hitboxafter1b = false;
				int hitboxrcs = 0;
				bool nearestRCS = false;
				bool rcsstandalone = false;
				bool fastzoom = false;
			}
			namespace triggerbot
			{
				bool enabled = false;
				bool team = false;
				bool enemies = true;
				int delay = 0;
				int key = -1;
				bool head = true;
				bool upperbody = true;
				bool lower = false;
				bool legs = false;
				bool arms = false;
			}
			namespace backtrack
			{
				bool enabled = false;
				int ticks = 16;
			}

		}
		namespace shotguns {
			int selectedTab = 0;
			bool Enabled = true;
			int key = VK_LBUTTON;
			bool enemies = true;
			bool team = false;
			namespace humanization
			{
				int smoothmovefactor = 0;

				bool silent = false;
				int silentfov = 2;
				int silenthitbox = 0;
				bool silentnearest = false;
				int  silenthitchance = 100;
				int silentstartbullet = 0;
				
				

				float smooth = 70;
				int fovpos = 1;
				int fov = 10;
				int hitbox = 0;
				bool nearest = false;

				bool firstfiredelayenable = false;
				bool firstfiredelayauto = false;
				bool firstfiresilentdelayauto = false;
				bool firstfiredelayoneclick = false;
				int firstfiredelay = 0;
				bool firstfiredelaysilent = false;

				bool targetswitchdelayenable = false;
				int targetswitchdelay = 0;
				bool killstop = false;
				int EndBullet = -1;
				int rcsx = 100;
				bool rcs = true;
				int rcsy = 100;
				int smoothrcs = 0;
				int fovrcs = 0;
				bool hitboxafter1b = false;
				int hitboxrcs = 0;
				bool nearestRCS = false;
				bool rcsstandalone = false;


				bool fastzoom = false;

			}
			namespace triggerbot
			{
				bool enabled = false;
				bool team = false;
				bool enemies = true;
				int delay = 0;
				int key = -1;
				bool head = true;
				bool upperbody = true;
				bool lower = false;
				bool legs = false;
				bool arms = false;
			}
			namespace backtrack
			{
				bool enabled = false;
				int ticks = 16;
			}

		}
		namespace extra
		{
			int stopspec = 0;
		}
	}
	namespace debug
	{
		std::vector<int> fpsData;
		bool main1 = true;
		bool main2 = true;
		bool main3 = true;
		bool main4 = true;
		bool main5 = true;
		bool main6 = true;
		bool main7 = true;
		bool main8 = true;
		bool main9 = true;
		bool main10 = true;
		bool main11 = true;
		bool main12 = true;
		bool main13 = true;
		bool main14 = true;
		bool main15 = true;
		bool main16 = true;
		bool main17 = true;
		bool main18 = true;
		bool main19 = true;
		bool main20 = true;
		bool main21 = true;
		bool main22 = true;
		bool main23 = true;
		bool main24 = true;
		bool main25 = true;
		bool main26 = true;
		bool main27 = true;
		bool main28 = true;
		bool main29 = true;
		bool main30 = true;
		bool main31 = true;
		bool main32 = true;
	}
	namespace esp
	{
		namespace enemies {
			bool enabled = true;
			bool visibleOnly = false;
			int healthbar = false;
			int box = 1;
			bool boxOutline = true;
			int name = 1;
			int weapon = 1;
			bool skeleton = false;
			bool barrel = false;
			int money = 1;
			bool lines = false;
			bool glowhealth = true;
			int distance = 2;
			int ammunition = 1;
			int chams = false;
			bool chamsxqz = false;
			bool radar = false;
			bool cheatradar = false;
			bool backtrack = false;
			bool backtrackChams = false;
			int glow = 0;
			bool healthvalue = false;
			bool armorvalue = false;
			int reloadWarning = 1;
			color reloadWarningVisible = color(240, 176, 0, 255);;;
			color reloadWarningInvisible = color(240, 176, 0, 255);;;
			int scopedWarning = 1;
			color scopedWarningVisible = color(240, 176, 0, 255);;;
			color scopedWarningInvisible = color(240, 176, 0, 255);;;
			int defuseWarning = 1;
			color defuseWarningVisible = color(240, 176, 0, 255);;;
			color defuseWarningInvisible = color(240, 176, 0, 255);;;
			int hostageWarning = 1;
			color hostageWarningVisible = color(240, 176, 0, 255);;;
			color hostageWarningInvisible = color(240, 176, 0, 255);;;
			int helmetESP = 1;
			color helmetESPVisible = color(240, 176, 0, 255);;;
			color helmetESPInvisible = color(240, 176, 0, 255);;;
			color boxVisible = color(34, 177, 76, 255);;
			color boxInvisible = color(255, 127, 39, 255);;
			color nameVisible = color(255, 255, 255, 255);
			color nameInvisible = color(255, 255, 255, 255);
			color weaponVisible = color(255, 255, 255, 255);
			color weaponInvisible = color(255, 255, 255, 255);
			color healthVisible = color(0, 255, 0, 255);
			color healthInvisible = color(0, 255, 0, 255);
			color moneyVisible = color(0, 200, 0, 255);
			color moneyInvisible = color(0, 150, 0, 255);
			color ammunitionVisible = color(255, 255, 255, 255);
			color ammunitionInvisible = color(100, 100, 255, 255);

			color chamsVisible = color(255, 127, 39, 255);
			color chamsInvisible = color(133, 0, 213, 255);

			color distanceVisible = color(255, 255, 255, 255);
			color distanceInvisible = color(100, 100, 255, 255);

			color barrelVisible = color(255, 255, 255, 255);
			color barrelInvisible = color(100, 100, 255, 255);

			color skeletonVisible = color(255, 255, 255, 255);
			color skeletonInvisible = color(230, 230, 230, 255);
			color glowVisible = color(55, 235, 52);
			color glowInvisible = color(235, 128, 52, 255);
		}
		namespace team {
			bool enabled = false;
			bool visibleOnly = false;
			int healthbar = 1;
			int box = true;
			bool boxOutline = true;
			int name = 1;
			int weapon = 1;
			int money = 1;
			int distance = 2;
			bool barrel = false;
			bool glowhealth = true;
			int ammunition = 1;
			bool skeleton = false;
			int chams = false;
			bool chamsxqz = false;
			int glow = 0;
			bool radar = false;
			bool cheatradar = false;
			bool backtrack = false;
			bool backtrackChams = false;
			bool healthvalue = false;
			bool armorvalue = false;
			bool lines = false;
			int reloadWarning = 1;
			color reloadWarningVisible = color(240, 176, 0, 255);;;
			color reloadWarningInvisible = color(240, 176, 0, 255);;;
			int scopedWarning = 1;
			color scopedWarningVisible = color(240, 176, 0, 255);;;
			color scopedWarningInvisible = color(240, 176, 0, 255);;;
			int defuseWarning = 1;
			color defuseWarningVisible = color(240, 176, 0, 255);;;
			color defuseWarningInvisible = color(240, 176, 0, 255);;;
			int hostageWarning = 1;
			color hostageWarningVisible = color(240, 176, 0, 255);;;
			color hostageWarningInvisible = color(240, 176, 0, 255);;;
			int helmetESP = 1;
			color helmetESPVisible = color(240, 176, 0, 255);;;
			color helmetESPInvisible = color(240, 176, 0, 255);;;


			color boxVisible = color(153, 217, 234, 255);;
			color boxInvisible = color(133, 0, 213, 255);;

			color nameVisible = color(255, 255, 255, 255);
			color nameInvisible = color(255, 255, 255, 255);

			color weaponVisible = color(255, 255, 255, 255);
			color weaponInvisible = color(255, 255, 255, 255);

			color healthVisible = color(0, 255, 0, 255);
			color healthInvisible = color(0, 255, 0, 255);

			color moneyVisible = color(0, 100, 0, 255);
			color moneyInvisible = color(0, 150, 0, 255);

			color ammunitionVisible = color(205, 205, 205, 255);
			color ammunitionInvisible = color(50, 50, 255, 255);

			color chamsVisible = color(133, 0, 213, 255);
			color chamsInvisible = color(255, 127, 39, 255);

			color distanceVisible = color(205, 205, 205, 255);
			color distanceInvisible = color(50, 50, 255, 255);

			color barrelVisible = color(205, 205, 205, 255);
			color barrelInvisible = color(50, 50, 255, 255);

			color skeletonVisible = color(255, 255, 255, 255);
			color skeletonInvisible = color(230, 230, 230, 255);
			color glowVisible = color(52, 86, 235, 255);
			color glowInvisible = color(235, 52, 52, 255);
		}
		namespace grenades
		{
			bool enabled = false;
			int box = 1;
			bool thrown = true;
			bool dropped = true;
			bool boxOutline = true;
			int name = 1;
		}
		namespace weapons
		{
			bool enabled = true;
			int box = 1;
			bool boxOutline = true;
			int name = 1;
		}
		namespace C4
		{
			bool enabled = true;
			int box = true;
			bool boxOutline = true;
			int name = true;
			int chams = false;
			bool XQZchams = false;

			bool detonationInfo = true;
			bool defuseInfo = true;
			std::string xx = "";
		}
		namespace other {
			int crosshairs = 0;
			bool spectators = true;
			bool damage = false;
			bool whocansee = false;
			int hitmarkers = 0;
			bool DeathFlags = false;
			bool drawsilentfov = false;
			bool drawfov = false;
			bool bombHealth = true;
		}
	
	}
	namespace misc {
		bool floating = false;
		int bhop_probability = 100;
		bool bhop_humanisation = false;
		bool autoStrafe = false;
		bool bhop = false;
		bool leftHandedKnife = false;
		bool revealranks = false;
		bool nightmode = false;
		int gamefov = 0;
		int viewfov = 0;
		bool autoPistol = false;
		int asus = 100.f;
		bool grenade = false;
		int trailParticles = 0;
		int rateOfParticle = 5;
		int mirrorview = -1;
		int mapheight = -1;
		int freemove = -1;
		std::string clantag = "";
		namespace statistics {
			int iHeadshots = 0;
			int iKills = 0;
			int iDeaths = 0;
		}
	}
	namespace updates {
		int update = 0;
	}
	namespace skinchanger
	{
		int selectedWeapon = 0;
		bool Glock18Enabled = true;
		int Glock18Skin = 18;
		int Glock18Wear = 0;
		int Glock18Seed = -1;
		int Glock18StatTrack = -1;
		std::string Glock18Name = xorStr("");


		bool P250Enabled = true;
		int P250Skin = 64;
		int P250Wear = 0;
		int P250Seed = -1;
		int P250StatTrack = -1;
		std::string P250Name = xorStr("");

		bool DesertEagleEnabled = true;
		int DesertEagleSkin = 27;
		int DesertEagleWear = 0;
		int DesertEagleSeed = -1;
		int DesertEagleStatTrack = -1;
		std::string DesertEagleName = xorStr("");

		bool DualBerettasEnabled = true;
		int DualBerettasSkin = 575;
		int DualBerettasWear = 0;
		int DualBerettasSeed = -1;
		int DualBerettasStatTrack = -1;
		std::string DualBerettasName = xorStr("");

		bool Tec9Enabled = true;
		int Tec9Skin = 510;
		int Tec9Wear = 0;
		int Tec9Seed = -1;
		int Tec9StatTrack = -1;
		std::string Tec9Name = xorStr("");

		bool CZ75AutoEnabled = true;
		int CZ75AutoSkin = 593;
		int CZ75AutoWear = 0;
		int CZ75AutoSeed = -1;
		int CZ75AutoStatTrack = -1;
		std::string CZ75AutoName = xorStr("");

		bool R8RevolverEnabled = true;
		int R8RevolverSkin = 701;
		int R8RevolverWear = 0;
		int R8RevolverSeed = -1;
		int R8RevolverStatTrack = -1;
		std::string R8RevolverName = xorStr("");

		bool P2000Enabled = true;
		int P2000Skin = 546;
		int P2000Wear = 0;
		int P2000Seed = -1;
		int P2000StatTrack = -1;
		std::string  P2000Name = xorStr("");


		bool  USPSEnabled = true;
		int USPSSkin = 421;
		int USPSWear = 0;
		int USPSSeed = -1;
		int USPSStatTrack = -1;
		std::string  USPSName = xorStr("");

		bool  FiveSeveNEnabled = true;
		int FiveSeveNSkin = 695;
		int FiveSeveNWear = 0;
		int FiveSeveNSeed = -1;
		int FiveSeveNStatTrack = -1;
		std::string  FiveSeveNName = xorStr("");

		bool  NovaEnabled = true;
		int NovaSkin = 209;
		int NovaWear = 0;
		int NovaSeed = -1;
		int NovaStatTrack = -1;
		std::string  NovaName = xorStr("");

		bool  XM1014Enabled = true;
		int XM1014Skin = 708;
		int XM1014Wear = 0;
		int XM1014Seed = -1;
		int XM1014StatTrack = -1;
		std::string  XM1014Name = xorStr("");

		bool  SawedOffEnabled = true;
		int SawedOffSkin = 731;
		int SawedOffWear = 0;
		int SawedOffSeed = -1;
		int SawedOffStatTrack = -1;
		std::string  SawedOffName = xorStr("");

		bool  MAG7Enabled = true;
		int MAG7Skin = 29;
		int MAG7Wear = 0;
		int MAG7Seed = -1;
		int MAG7StatTrack = -1;
		std::string  MAG7Name = xorStr("");

		bool  MAC10Enabled = true;
		int MAC10Skin = 351;
		int MAC10Wear = 0;
		int MAC10Seed = -1;
		int MAC10StatTrack = -1;
		std::string  MAC10Name = xorStr("");


		bool  MP7Enabled = true;
		int MP7Skin = 567;
		int MP7Wear = 0;
		int MP7Seed = -1;
		int MP7StatTrack = -1;
		std::string  MP7Name = xorStr("");



		bool  MP5Enabled = true;
		int MP5Skin = 685;
		int MP5Wear = 0;
		int MP5Seed = -1;
		int MP5StatTrack = -1;
		std::string  MP5Name = xorStr("");

		bool  UMP45Enabled = true;
		int UMP45Skin = 730;
		int UMP45Wear = 0;
		int UMP45Seed = -1;
		int UMP45StatTrack = -1;
		std::string UMP45Name = xorStr("");


		bool PPBIZONEnabled = true;
		int PPBIZONSkin = 626;
		int PPBIZONWear = 0;
		int PPBIZONSeed = -1;
		int PPBIZONStatTrack = -1;
		std::string PPBIZONName = xorStr("");


		bool P90Enabled = true;
		int P90Skin = 726;
		int P90Wear = 0;
		int P90Seed = -1;
		int P90StatTrack = -1;
		std::string P90Name = xorStr("");


		bool MP9Enabled = true;
		int MP9Skin = 185;
		int MP9Wear = 0;
		int MP9Seed = -1;
		int MP9StatTrack = -1;
		std::string MP9Name = xorStr("");


		bool GalilAREnabled = true;
		int GalilARSkin = 318;
		int GalilARWear = 0;
		int GalilARSeed = -1;
		int GalilARStatTrack = -1;
		std::string GalilARName = xorStr("");


		bool FAMASEnabled = true;
		int FAMASSkin = 733;
		int FAMASWear = 0;
		int FAMASSeed = -1;
		int FAMASStatTrack = -1;
		std::string FAMASName = xorStr("");

		bool AK47Enabled = true;
		int AK47Skin = 34;
		int AK47Wear = 0;
		int AK47Seed = 3148;
		int AK47StatTrack = -1;
		std::string  AK47Name = xorStr("");

		bool M4A4Enabled = true;
		int M4A4Skin = 231;
		int M4A4Wear = 0;
		int M4A4Seed = -1;
		int M4A4StatTrack = -1;
		std::string  M4A4Name = xorStr("");

		bool SSG08Enabled = true;
		int SSG08Skin = 146;
		int SSG08Wear = 0;
		int SSG08Seed = -1;
		int SSG08StatTrack = -1;
		std::string  SSG08Name = xorStr("");


		bool M4A1SEnabled = true;
		int M4A1SSkin = 414;
		int M4A1SWear = 0;
		int M4A1SSeed = -1;
		int M4A1SStatTrack = -1;
		std::string  M4A1SName = xorStr("");


		bool SG553Enabled = true;
		int SG553Skin = 482;
		int SG553Wear = 0;
		int SG553Seed = -1;
		int SG553StatTrack = -1;
		std::string   SG553Name = xorStr("");


		bool AUGEnabled = true;
		int AUGSkin = 373;
		int AUGWear = 0;
		int AUGSeed = -1;
		int AUGStatTrack = -1;
		std::string   AUGName = xorStr("");

		bool AWPEnabled = true;
		int AWPSkin = 264;
		int AWPWear = 0;
		int AWPSeed = -1;
		int AWPStatTrack = -1;
		std::string   AWPName = xorStr("");

		bool G3SG1Enabled = true;
		int G3SG1Skin = 681;
		int G3SG1Wear = 0;
		int G3SG1Seed = -1;
		int G3SG1StatTrack = -1;
		std::string   G3SG1Name = xorStr("");

		bool SCAR20Enabled = true;
		int SCAR20Skin = 90;
		int SCAR20Wear = 0;
		int SCAR20Seed = -1;
		int SCAR20StatTrack = -1;
		std::string   SCAR20Name = xorStr("");

		bool M249Enabled = true;
		int M249Skin = 413;
		int M249Wear = 0;
		int M249Seed = -1;
		int M249StatTrack = -1;
		std::string   M249Name = xorStr("");

		bool NegevEnabled = true;
		int NegevSkin = 430;
		int NegevWear = 0;
		int NegevSeed = -1;
		int NegevStatTrack = -1;
		std::string   NegevName = xorStr("");

		bool C4Enabled = true;
		int C4Skin = 0;
		int C4Wear = 0;
		int C4Seed = -1;
		int C4StatTrack = -1;
		std::string   C4Name = xorStr("");


		bool KnifeEnabled = true;
		int KnifeSkin = 34;
		int KnifeWear = 0;
		int KnifeSeed = 902;
		int KnifeModel = 1;
		int KnifeStatTrack = -1;
		std::string   KnifeName = xorStr("");

		bool GloveEnabled = true;
		int GloveSkin = 7;
		int GloveWear = 0;
		int GloveSeed = -1;
		int GloveStatTrack = -1;

		int GloveModel = 2;
	}
}