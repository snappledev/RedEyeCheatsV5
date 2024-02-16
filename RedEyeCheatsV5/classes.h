#pragma once
#include <Windows.h>
enum class ItemDefinitionIndex : short
{
	WEAPON_NONE = 0,
	WEAPON_DEAGLE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALIL = 13,
	WEAPON_M249,
	WEAPON_M4A4 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_ZEUS,
	WEAPON_P2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SHIELD,
	WEAPON_SCAR20,
	WEAPON_SG553,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INC,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1S,
	WEAPON_USPS,
	WEAPON_CZ75 = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	WEAPON_SNOWBALL,
	WEAPON_BUMPMINE,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_CSS = 503,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH,
	WEAPON_KNIFE_CORD,
	WEAPON_KNIFE_CANIS,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE,
	WEAPON_KNIFE_OUTDOOR,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER,
	WEAPON_KNIFE_SKELETON = 525,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_HYDRA = 5035
};
class CSWeaponInfo{
public:
	char	pad0[4];
	char* m_szWeaponName;
	char	pad1[12];
	int		m_iMaxAmmoR;
	int		m_iMaxReserveAmmoR;
	int		default_clip1;
	int		default_clip2;
	int		m_iMaxAmmo;
	int		m_iMaxReserveAmmo;
	char* world_model;
	char* m_szWeaponModelPat;
	char* m_szDroppedWeaponModelPath;
	char	pad2[80];
	char* hud_name;
	char* weapon_name;
	char	pad3[2];
	bool	is_melee_weapon;
	char	pad4[9];
	float	weapon_weight;
	char	pad5[40];
	int		m_iWeaponType;
	char	pad6[4];
	int		m_iWeaponPrice;;
	int		m_iWeaponReward;
	char	pad7[4];
	float	cycle_time;
	float	cycle_time_alt;
	char	pad8[8];
	bool	m_nFullAuto;
	char	pad9[3];
	int		m_iDamage;
	float	 m_flArmorRatio;
	int		 m_iAmmo;
	float	 m_flPenetration;
	char	pad10[8];
	float m_flRange; //0x0108 
	float m_flRangeModifier; //0x010C 
	float	throw_velocity;
	char	pad11[12];
	bool	m_nSilencer;
	char	pad12[11];
	char* bullet_type;
	float	m_flMaxSpeed;
	float	m_flMaxSpeedAlt;
	char	pad13[4];
	float	spread;
	float	spread_alt;
	float	inaccuracy_crouch;
	float	inaccuracy_crouch_alt;
	float	inaccuracy_stand;
	float	inaccuracy_stand_alt;
	float	inaccuracy_jump_initial;
	float	inaccuracy_jump_apex;
	float	inaccuracy_jump;
	float	inaccuracy_jump_alt;
	float	inaccuracy_land;
	float	inaccuracy_land_alt;
	float	inaccuracy_ladder;
	float	inaccuracy_ladder_alt;
	float	inaccuracy_fire;
	float	inaccuracy_fire_alt;
	float	inaccuracy_move;
	float	inaccuracy_move_alt;
	float	inaccuracy_reload;
	int		recoil_seed;
	float	recoil_angle;
	float	recoil_angle_alt;
	float	recoil_angle_variance;
	float	recoil_angle_variance_alt;
	float	recoil_magnitude;
	float	recoil_magnitude_alt;
	float	recoil_magnitude_variance;
	float	recoil_magnitude_variance_alt;
};



#define MAX_QPATH  260
#define BONE_CALCULATE_MASK             0x1F
#define BONE_PHYSICALLY_SIMULATED       0x01    // bone is physically simulated when physics are active
#define BONE_PHYSICS_PROCEDURAL         0x02    // procedural when physics is active
#define BONE_ALWAYS_PROCEDURAL          0x04    // bone is always procedurally animated
#define BONE_SCREEN_ALIGN_SPHERE        0x08    // bone aligns to the screen, not constrained in motion.
#define BONE_SCREEN_ALIGN_CYLINDER      0x10    // bone aligns to the screen, constrained by it's own axis.
#define BONE_USED_MASK                  0x0007FF00
#define BONE_USED_BY_ANYTHING           0x0007FF00
#define BONE_USED_BY_HITBOX             0x00000100    // bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT         0x00000200    // bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK        0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0        0x00000400    // bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1        0x00000800    
#define BONE_USED_BY_VERTEX_LOD2        0x00001000  
#define BONE_USED_BY_VERTEX_LOD3        0x00002000
#define BONE_USED_BY_VERTEX_LOD4        0x00004000
#define BONE_USED_BY_VERTEX_LOD5        0x00008000
#define BONE_USED_BY_VERTEX_LOD6        0x00010000
#define BONE_USED_BY_VERTEX_LOD7        0x00020000
#define BONE_USED_BY_BONE_MERGE         0x00040000    // bone is available for bone merge to occur against it
#define BONE_USED_BY_VERTEX_AT_LOD(lod) ( BONE_USED_BY_VERTEX_LOD0 << (lod) )
#define BONE_USED_BY_ANYTHING_AT_LOD(lod) ( ( BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK ) | BONE_USED_BY_VERTEX_AT_LOD(lod) )
#define MAX_NUM_LODS 8
#define MAXSTUDIOBONES		128		// total bones actually used
#define BONE_TYPE_MASK                  0x00F00000
#define BONE_FIXED_ALIGNMENT            0x00100000    // bone can't spin 360 degrees, all interpolation is normalized around a fixed orientation
#define BONE_HAS_SAVEFRAME_POS          0x00200000    // Vector48
#define BONE_HAS_SAVEFRAME_ROT64        0x00400000    // Quaternion64
#define BONE_HAS_SAVEFRAME_ROT32        0x00800000    // Quaternion32

#include "cBaseEntity.h"
#pragma region MASKS

#define   DISPSURF_FLAG_SURFACE           (1<<0)
#define   DISPSURF_FLAG_WALKABLE          (1<<1)
#define   DISPSURF_FLAG_BUILDABLE         (1<<2)
#define   DISPSURF_FLAG_SURFPROP1         (1<<3)
#define   DISPSURF_FLAG_SURFPROP2         (1<<4)

#define   CONTENTS_EMPTY                0

#define   CONTENTS_SOLID                0x1       
#define   CONTENTS_WINDOW               0x2
#define   CONTENTS_AUX                  0x4
#define   CONTENTS_GRATE                0x8
#define   CONTENTS_SLIME                0x10
#define   CONTENTS_WATER                0x20
#define   CONTENTS_BLOCKLOS             0x40 
#define   CONTENTS_OPAQUE               0x80 
#define   LAST_VISIBLE_CONTENTS         CONTENTS_OPAQUE

#define   ALL_VISIBLE_CONTENTS            (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define   CONTENTS_TESTFOGVOLUME        0x100
#define   CONTENTS_UNUSED               0x200     
#define   CONTENTS_BLOCKLIGHT           0x400
#define   CONTENTS_TEAM1                0x800 
#define   CONTENTS_TEAM2                0x1000 
#define   CONTENTS_IGNORE_NODRAW_OPAQUE 0x2000
#define   CONTENTS_MOVEABLE             0x4000
#define   CONTENTS_AREAPORTAL           0x8000
#define   CONTENTS_PLAYERCLIP           0x10000
#define   CONTENTS_MONSTERCLIP          0x20000
#define   CONTENTS_CURRENT_0            0x40000
#define   CONTENTS_CURRENT_90           0x80000
#define   CONTENTS_CURRENT_180          0x100000
#define   CONTENTS_CURRENT_270          0x200000
#define   CONTENTS_CURRENT_UP           0x400000
#define   CONTENTS_CURRENT_DOWN         0x800000

#define   CONTENTS_ORIGIN               0x1000000 

#define   CONTENTS_MONSTER              0x2000000 
#define   CONTENTS_DEBRIS               0x4000000
#define   CONTENTS_DETAIL               0x8000000 
#define   CONTENTS_TRANSLUCENT          0x10000000
#define   CONTENTS_LADDER               0x20000000
#define   CONTENTS_HITBOX               0x40000000

#define   SURF_LIGHT                    0x0001 
#define   SURF_SKY2D                    0x0002 
#define   SURF_SKY                      0x0004 
#define   SURF_WARP                     0x0008 
#define   SURF_TRANS                    0x0010
#define   SURF_NOPORTAL                 0x0020 
#define   SURF_TRIGGER                  0x0040 
#define   SURF_NODRAW                   0x0080 

#define   SURF_HINT                     0x0100 

#define   SURF_SKIP                     0x0200   
#define   SURF_NOLIGHT                  0x0400   
#define   SURF_BUMPLIGHT                0x0800   
#define   SURF_NOSHADOWS                0x1000   
#define   SURF_NODECALS                 0x2000   
#define   SURF_NOPAINT                  SURF_NODECALS
#define   SURF_NOCHOP                   0x4000   
#define   SURF_HITBOX                   0x8000   

// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define   MASK_ALL                      (0xFFFFFFFF)
#define   MASK_SOLID                    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_PLAYERSOLID              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_NPCSOLID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_NPCFLUID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define   MASK_WATER                    (CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
#define   MASK_OPAQUE                   (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
#define   MASK_OPAQUE_AND_NPCS          (MASK_OPAQUE|CONTENTS_MONSTER)
#define   MASK_BLOCKLOS                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
#define   MASK_BLOCKLOS_AND_NPCS        (MASK_BLOCKLOS|CONTENTS_MONSTER)
#define   MASK_VISIBLE                  (MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define   MASK_VISIBLE_AND_NPCS         (MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define   MASK_SHOT                     (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define   MASK_SHOT_BRUSHONLY           (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
#define   MASK_SHOT_HULL                (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
#define   MASK_SHOT_PORTAL              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define   MASK_SOLID_BRUSHONLY          (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
#define   MASK_PLAYERSOLID_BRUSHONLY    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
#define   MASK_NPCSOLID_BRUSHONLY       (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define   MASK_NPCWORLDSTATIC           (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define   MASK_NPCWORLDSTATIC_FLUID     (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
#define   MASK_SPLITAREAPORTAL          (CONTENTS_WATER|CONTENTS_SLIME)
#define   MASK_CURRENT                  (CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
#define   MASK_DEADSOLID                (CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)
#pragma endregion

enum class HITBOX
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_PELVIS,
	HITBOX_BELLY,
	HITBOX_THORAX,
	HITBOX_LOWER_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};