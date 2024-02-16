#pragma once
#include "vector.h"
#include "matrix3x4.h"
#include "classes.h"
class IHandleEntity;
struct Ray_t;
class CGameTrace;
typedef CGameTrace trace_t;
class ICollideable;
class ITraceListData;
class CPhysCollide;

struct virtualmeshlist_t;
struct cplane_t
{
	Vector normal;
	float dist;
	uint8_t type;   // for fast side tests
	uint8_t signbits;  // signx + (signy<<1) + (signz<<1)
	uint8_t pad[2];

};
enum class TraceType
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(IHandleEntity *pEntity, int contentsMask) = 0;
	virtual TraceType GetTraceType() const = 0;
};


//-----------------------------------------------------------------------------
// Classes are expected to inherit these + implement the ShouldHitEntity method
//-----------------------------------------------------------------------------

// This is the one most normal traces will inherit from
class CTraceFilter : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pEntityHandle, int /*contentsMask*/)
	{
		return !(pEntityHandle == pSkip);
	}
	virtual TraceType GetTraceType() const
	{
		return TraceType::TRACE_EVERYTHING;
	}
	void* pSkip;
};

class CTraceFilterSkipEntity : public ITraceFilter
{
public:
	CTraceFilterSkipEntity(IHandleEntity* pEntityHandle)
	{
		pSkip = pEntityHandle;
	}

	bool ShouldHitEntity(IHandleEntity* pEntityHandle, int /*contentsMask*/)
	{
		return !(pEntityHandle == pSkip);
	}
	virtual TraceType GetTraceType() const
	{
		return TraceType::TRACE_EVERYTHING;
	}
	void* pSkip;
};

class CTraceFilterEntitiesOnly : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pEntityHandle, int /*contentsMask*/)
	{
		return true;
	}
	virtual TraceType GetTraceType() const
	{
		return TraceType::TRACE_ENTITIES_ONLY;
	}
};


//-----------------------------------------------------------------------------
// Classes need not inherit from these
//-----------------------------------------------------------------------------
class CTraceFilterWorldOnly : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* /*pServerEntity*/, int /*contentsMask*/)
	{
		return false;
	}
	virtual TraceType GetTraceType() const
	{
		return TraceType::TRACE_WORLD_ONLY;
	}
};

class CTraceFilterWorldAndPropsOnly : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* /*pServerEntity*/, int /*contentsMask*/)
	{
		return false;
	}
	virtual TraceType GetTraceType() const
	{
		return TraceType::TRACE_EVERYTHING;
	}
};


class CTraceFilterHitAll : public CTraceFilter
{
public:
	virtual bool ShouldHitEntity(IHandleEntity* /*pServerEntity*/, int /*contentsMask*/)
	{
		return true;
	}
};


enum class DebugTraceCounterBehavior_t
{
	kTRACE_COUNTER_SET = 0,
	kTRACE_COUNTER_INC,
};

//-----------------------------------------------------------------------------
// Enumeration interface for EnumerateLinkEntities
//-----------------------------------------------------------------------------
class IEntityEnumerator
{
public:
	// This gets called with each handle
	virtual bool EnumEntity(IHandleEntity *pHandleEntity) = 0;
};


class CPhysCollide;

struct vcollide_t
{
	unsigned short solidCount : 15;
	unsigned short isPacked : 1;
	unsigned short descSize;
	// VPhysicsSolids
	CPhysCollide   **solids;
	char           *pKeyValues;
	void           *pUserData;
};

struct cmodel_t
{
	Vector         mins, maxs;
	Vector         origin;        // for sounds or lights
	int            headnode;
	vcollide_t     vcollisionData;
};

struct csurface_t
{
	const char     *name;
	short          surfaceProps;
	unsigned short flags;         // BUGBUG: These are declared per surface, not per material, but this database is per-material now
};

//-----------------------------------------------------------------------------
// A ray...
//-----------------------------------------------------------------------------
struct Ray_t
{
	VectorAligned  m_Start;  // starting point, centered within the extents
	VectorAligned  m_Delta;  // direction + length of the ray
	VectorAligned  m_StartOffset; // Add this to m_Start to Get the actual ray start
	VectorAligned  m_Extents;     // Describes an axis aligned box extruded along a ray
	const matrix3x4_t *m_pWorldAxisTransform;
	bool m_IsRay;  // are the extents zero?
	bool m_IsSwept;     // is delta != 0?

	Ray_t() : m_pWorldAxisTransform(NULL) {}

	void Init(Vector const& start, Vector const& end)
	{
		m_Delta = end - start;

		m_IsSwept = (m_Delta.Length() != 0);

		m_Extents.Init();

		m_pWorldAxisTransform = NULL;
		m_IsRay = true;

		// Offset m_Start to be in the center of the box...
		m_StartOffset.Init();
		m_Start = start;
	}

	void Init(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs)
	{
		m_Delta = end - start;

		m_pWorldAxisTransform = NULL;
		m_IsSwept = (m_Delta.Length() != 0);

		m_Extents = maxs - mins;
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.Length() < 1e-6);

		// Offset m_Start to be in the center of the box...
		m_StartOffset = maxs + mins;
		m_StartOffset *= 0.5f;
		m_Start = start + m_StartOffset;
		m_StartOffset *= -1.0f;
	}
	Vector InvDelta() const
	{
		Vector vecInvDelta;
		std::size_t x = 0;


		if (m_Delta.x != 0.0f) {
			vecInvDelta.x = 1.0f / m_Delta.x;
		}
		else {
			vecInvDelta.x = FLT_MAX;
		}
		if (m_Delta.y != 0.0f) {
			vecInvDelta.y = 1.0f / m_Delta.y;
		}
		else {
			vecInvDelta.y = FLT_MAX;
		}
		if (m_Delta.z != 0.0f) {
			vecInvDelta.z = 1.0f / m_Delta.z;
		}
		else {
			vecInvDelta.z = FLT_MAX;
		}
		return vecInvDelta;
	}

private:
};

class CBaseTrace
{
public:
	bool IsDispSurface(void) { return ((dispFlags & DISPSURF_FLAG_SURFACE) != 0); }
	bool IsDispSurfaceWalkable(void) { return ((dispFlags & DISPSURF_FLAG_WALKABLE) != 0); }
	bool IsDispSurfaceBuildable(void) { return ((dispFlags & DISPSURF_FLAG_BUILDABLE) != 0); }
	bool IsDispSurfaceProp1(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP1) != 0); }
	bool IsDispSurfaceProp2(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP2) != 0); }

public:

	// these members are aligned!!
	Vector         startpos;            // start position
	Vector         endpos;              // final position
	cplane_t       plane;               // surface normal at impact

	float          fraction;            // time completed, 1.0 = didn't hit anything

	int            contents;            // contents on other side of surface hit
	unsigned short dispFlags;           // displacement flags for marking surfaces with data

	bool           allsolid;            // if true, plane is not valid
	bool           startsolid;          // if true, the initial point was in a solid area

	CBaseTrace() {}

};
class CBaseEntity;


struct CGameTrace : public CBaseTrace {
	Vector start;
	Vector end;
	cplane_t plane;
	float flFraction;
	int contents;
	unsigned short dispFlags;
	bool allsolid;
	bool startSolid;
	float fractionLeftSolid;
	csurface_t surface;
	int hitgroup;
	short physicsBone;
	cBaseEntity* hit_entity;
	int hitbox;

	bool did_hit() const {
		return flFraction < 1.f;
	}

	bool did_hit_world() const {
		return false;
	}

	bool did_hit_non_world_entity() const {
		return hit_entity != NULL && !did_hit_world();
	}
};





class iEngineTrace
{
public:
	virtual int   GetPointContents(const Vector &vecAbsPosition, int contentsMask = MASK_ALL, IHandleEntity** ppEntity = nullptr) = 0;
	virtual int   GetPointContents_WorldOnly(const Vector &vecAbsPosition, int contentsMask = MASK_ALL) = 0;
	virtual int   GetPointContents_Collideable(ICollideable *pCollide, const Vector &vecAbsPosition) = 0;
	virtual void  ClipRayToEntity(const Ray_t &ray, unsigned int fMask, IHandleEntity *pEnt, CGameTrace* pTrace) = 0;
	virtual void  ClipRayToCollideable(const Ray_t &ray, unsigned int fMask, ICollideable *pCollide, CGameTrace* pTrace) = 0;
	virtual void  TraceRay(const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, CGameTrace* pTrace) = 0;
};