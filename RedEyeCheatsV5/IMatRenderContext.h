#pragma once
class ITexture;
#include "CBaseAutoPtr.h"
#include "matrix3x4.h"
#include <stdint.h>
#include "virtualFunction.h"
#include "CTexture.h"
#include <Windows.h>
enum StencilOperation_t
{
#if !defined( _X360 )
	STENCILOPERATION_KEEP = 1,
	STENCILOPERATION_ZERO = 2,
	STENCILOPERATION_REPLACE = 3,
	STENCILOPERATION_INCRSAT = 4,
	STENCILOPERATION_DECRSAT = 5,
	STENCILOPERATION_INVERT = 6,
	STENCILOPERATION_INCR = 7,
	STENCILOPERATION_DECR = 8,
#else
	STENCILOPERATION_KEEP = D3DSTENCILOP_KEEP,
	STENCILOPERATION_ZERO = D3DSTENCILOP_ZERO,
	STENCILOPERATION_REPLACE = D3DSTENCILOP_REPLACE,
	STENCILOPERATION_INCRSAT = D3DSTENCILOP_INCRSAT,
	STENCILOPERATION_DECRSAT = D3DSTENCILOP_DECRSAT,
	STENCILOPERATION_INVERT = D3DSTENCILOP_INVERT,
	STENCILOPERATION_INCR = D3DSTENCILOP_INCR,
	STENCILOPERATION_DECR = D3DSTENCILOP_DECR,
#endif
	STENCILOPERATION_FORCE_DWORD = 0x7fffffff
};
enum MaterialPrimitiveType_t
{
	MATERIAL_POINTS = 0x0,
	MATERIAL_LINES,
	MATERIAL_TRIANGLES,
	MATERIAL_TRIANGLE_STRIP,
	MATERIAL_LINE_STRIP,
	MATERIAL_LINE_LOOP,	// a single line loop
	MATERIAL_POLYGON,	// this is a *single* polygon
	MATERIAL_QUADS,
	MATERIAL_SUBD_QUADS_EXTRA, // Extraordinary sub-d quads
	MATERIAL_SUBD_QUADS_REG,   // Regular sub-d quads
	MATERIAL_INSTANCED_QUADS, // (X360) like MATERIAL_QUADS, but uses vertex instancing

							  // This is used for static meshes that contain multiple types of
							  // primitive types.	When calling draw, you'll need to specify
							  // a primitive type.
							  MATERIAL_HETEROGENOUS
};
enum StencilComparisonFunction_t
{
#if !defined( _X360 )
	STENCILCOMPARISONFUNCTION_NEVER = 1,
	STENCILCOMPARISONFUNCTION_LESS = 2,
	STENCILCOMPARISONFUNCTION_EQUAL = 3,
	STENCILCOMPARISONFUNCTION_LESSEQUAL = 4,
	STENCILCOMPARISONFUNCTION_GREATER = 5,
	STENCILCOMPARISONFUNCTION_NOTEQUAL = 6,
	STENCILCOMPARISONFUNCTION_GREATEREQUAL = 7,
	STENCILCOMPARISONFUNCTION_ALWAYS = 8,
#else
	STENCILCOMPARISONFUNCTION_NEVER = D3DCMP_NEVER,
	STENCILCOMPARISONFUNCTION_LESS = D3DCMP_LESS,
	STENCILCOMPARISONFUNCTION_EQUAL = D3DCMP_EQUAL,
	STENCILCOMPARISONFUNCTION_LESSEQUAL = D3DCMP_LESSEQUAL,
	STENCILCOMPARISONFUNCTION_GREATER = D3DCMP_GREATER,
	STENCILCOMPARISONFUNCTION_NOTEQUAL = D3DCMP_NOTEQUAL,
	STENCILCOMPARISONFUNCTION_GREATEREQUAL = D3DCMP_GREATEREQUAL,
	STENCILCOMPARISONFUNCTION_ALWAYS = D3DCMP_ALWAYS,
#endif

	STENCILCOMPARISONFUNCTION_FORCE_DWORD = 0x7fffffff
};

enum ImageFormat
{
	IMAGE_FORMAT_UNKNOWN = -1,
	IMAGE_FORMAT_RGBA8888 = 0,
	IMAGE_FORMAT_ABGR8888,
	IMAGE_FORMAT_RGB888,
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565,
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,			// Single-channel 32-bit floating point
	IMAGE_FORMAT_RGB323232F,
	IMAGE_FORMAT_RGBA32323232F,

	// Depth-stencil texture formats for shadow depth mapping
	IMAGE_FORMAT_NV_DST16,		// 
	IMAGE_FORMAT_NV_DST24,		//
	IMAGE_FORMAT_NV_INTZ,		// Vendor-specific depth-stencil texture
	IMAGE_FORMAT_NV_RAWZ,		// formats for shadow depth mapping 
	IMAGE_FORMAT_ATI_DST16,		// 
	IMAGE_FORMAT_ATI_DST24,		//
	IMAGE_FORMAT_NV_NULL,		// Dummy format which takes no video memory

	// Compressed normal map formats
	IMAGE_FORMAT_ATI2N,			// One-surface ATI2N / DXN format
	IMAGE_FORMAT_ATI1N,			// Two-surface ATI1N format

#if defined( _X360 )
															// Depth-stencil texture formats
															IMAGE_FORMAT_X360_DST16,
															IMAGE_FORMAT_X360_DST24,
															IMAGE_FORMAT_X360_DST24F,
															// supporting these specific formats as non-tiled for procedural cpu access
															IMAGE_FORMAT_LINEAR_BGRX8888,
															IMAGE_FORMAT_LINEAR_RGBA8888,
															IMAGE_FORMAT_LINEAR_ABGR8888,
															IMAGE_FORMAT_LINEAR_ARGB8888,
															IMAGE_FORMAT_LINEAR_BGRA8888,
															IMAGE_FORMAT_LINEAR_RGB888,
															IMAGE_FORMAT_LINEAR_BGR888,
															IMAGE_FORMAT_LINEAR_BGRX5551,
															IMAGE_FORMAT_LINEAR_I8,
															IMAGE_FORMAT_LINEAR_RGBA16161616,

															IMAGE_FORMAT_LE_BGRX8888,
															IMAGE_FORMAT_LE_BGRA8888,
#endif

															NUM_IMAGE_FORMATS
};
typedef int64_t VertexFormat_t;

struct ShaderStencilState_t
{
	bool m_bEnable;
	StencilOperation_t m_FailOp;
	StencilOperation_t m_ZFailOp;
	StencilOperation_t m_PassOp;
	StencilComparisonFunction_t m_CompareFunc;
	int m_nReferenceValue;
	uint32_t m_nTestMask;
	uint32_t m_nWriteMask;

	ShaderStencilState_t()
	{
		m_bEnable = false;
		m_PassOp = m_FailOp = m_ZFailOp = STENCILOPERATION_KEEP;
		m_CompareFunc = STENCILCOMPARISONFUNCTION_ALWAYS;
		m_nReferenceValue = 0;
		m_nTestMask = m_nWriteMask = 0xFFFFFFFF;
	}
};
enum VertexCompressionType_t
{
	// This indicates an uninitialized VertexCompressionType_t value
	VERTEX_COMPRESSION_INVALID = 0xFFFFFFFF,

	// 'VERTEX_COMPRESSION_NONE' means that no elements of a vertex are compressed
	VERTEX_COMPRESSION_NONE = 0,

	// Currently (more stuff may be added as needed), 'VERTEX_COMPRESSION_ON' means:
	//  - if a vertex contains VERTEX_ELEMENT_NORMAL, this is compressed
	//    (see CVertexBuilder::CompressedNormal3f)
	//  - if a vertex contains VERTEX_ELEMENT_USERDATA4 (and a normal - together defining a tangent
	//    frame, with the binormal reconstructed in the vertex shader), this is compressed
	//    (see CVertexBuilder::CompressedUserData)
	//  - if a vertex contains VERTEX_ELEMENT_BONEWEIGHTSx, this is compressed
	//    (see CVertexBuilder::CompressedBoneWeight3fv)
	VERTEX_COMPRESSION_ON = 1
};
/*
class IMatRenderContext : public IRefCounted
{
public:
	void SetStencilEnable(bool onoff)
	{
		typedef void(__thiscall* OriginalFn)(void*, bool);
		return getvfunc<OriginalFn>(this, 113)(this, onoff);
	}
	void SetStencilFailOperation(StencilOperation_t op)
	{
		typedef void(__thiscall* OriginalFn)(void*, StencilOperation_t);
		return getvfunc<OriginalFn>(this, 114)(this, op);
	}
	void SetStencilZFailOperation(StencilOperation_t op)
	{
		typedef void(__thiscall* OriginalFn)(void*, StencilOperation_t);
		return getvfunc<OriginalFn>(this, 115)(this, op);
	}
	void SetStencilPassOperation(StencilOperation_t op)
	{
		typedef void(__thiscall* OriginalFn)(void*, StencilOperation_t);
		return getvfunc<OriginalFn>(this, 116)(this, op);
	}
	void SetStencilCompareFunction(StencilComparisonFunction_t cmpfn)
	{
		typedef void(__thiscall* OriginalFn)(void*, StencilComparisonFunction_t);
		return getvfunc<OriginalFn>(this, 117)(this, cmpfn);
	}
	void SetStencilReferenceValue(int ref)
	{
		typedef void(__thiscall* OriginalFn)(void*, int);
		return getvfunc<OriginalFn>(this, 118)(this, ref);
	}
	void SetStencilTestMask(uint32_t msk)
	{
		typedef void(__thiscall* OriginalFn)(void*, uint32_t);
		return getvfunc<OriginalFn>(this, 119)(this, msk);
	}
	void SetStencilWriteMask(uint32_t msk)
	{
		typedef void(__thiscall* OriginalFn)(void*, uint32_t);
		return getvfunc<OriginalFn>(this, 120)(this, msk);
	}
	//73
	void ClearStencilBufferRectangle(int xmin, int ymin, int xmax, int ymax, int value)
	{
		typedef void(__thiscall* OriginalFn)(void*, int, int, int, int, int);
		return getvfunc<OriginalFn>(this, 121)(this, xmin, ymin, xmax, ymax, value);
	}
	void DrawScreenSpaceQuad(IMaterial* material)
	{
		typedef void(__thiscall* originalfn)(void*, IMaterial*);
		return getvfunc<originalfn>(this, 73)(this, material);
	}
	void SetStencilState(ShaderStencilState_t stencil)
	{
		SetStencilEnable(stencil.m_bEnable);
		SetStencilFailOperation(stencil.m_FailOp);
		SetStencilZFailOperation(stencil.m_ZFailOp);
		SetStencilPassOperation(stencil.m_PassOp);
		SetStencilCompareFunction(stencil.m_CompareFunc);
		SetStencilReferenceValue(stencil.m_nReferenceValue);
		SetStencilTestMask(stencil.m_nTestMask);
		SetStencilWriteMask(stencil.m_nWriteMask);
	}
};*/
class CPrimList;
struct VertexDesc_t
{
	// These can be set to zero if there are pointers to dummy buffers, when the
	// actual buffer format doesn't contain the data but it needs to be safe to
	// use all the CMeshBuilder functions.
	int	m_VertexSize_Position;
	int m_VertexSize_BoneWeight;
	int m_VertexSize_BoneMatrixIndex;
	int	m_VertexSize_Normal;
	int	m_VertexSize_Color;
	int	m_VertexSize_Specular;
	int m_VertexSize_TexCoord[8];
	int m_VertexSize_TangentS;
	int m_VertexSize_TangentT;
	int m_VertexSize_Wrinkle;

	int m_VertexSize_UserData;

	int m_ActualVertexSize;	// Size of the vertices.. Some of the m_VertexSize_ elements above
							// are set to this value and some are set to zero depending on which
							// fields exist in a buffer's vertex format.

							// The type of compression applied to this vertex data
	VertexCompressionType_t m_CompressionType;

	// Number of bone weights per vertex...
	int m_NumBoneWeights;

	// Pointers to our current vertex data
	float* m_pPosition;

	float* m_pBoneWeight;

#ifndef NEW_SKINNING
	unsigned char* m_pBoneMatrixIndex;
#else
	float* m_pBoneMatrixIndex;
#endif

	float* m_pNormal;

	unsigned char* m_pColor;
	unsigned char* m_pSpecular;
	float* m_pTexCoord[8];

	// Tangent space *associated with one particular set of texcoords*
	float* m_pTangentS;
	float* m_pTangentT;

	float* m_pWrinkle;

	// user data
	float* m_pUserData;

	// The first vertex index (used for buffered vertex buffers, or cards that don't support stream offset)
	int	m_nFirstVertex;

	// The offset in bytes of the memory we're writing into 
	// from the start of the D3D buffer (will be 0 for static meshes)
	unsigned int	m_nOffset;

#ifdef DEBUG_WRITE_COMBINE
	int m_nLastWrittenField;
	unsigned char* m_pLastWrittenAddress;
#endif
};

class IVertexBuffer
{
public:
	// NOTE: The following two methods are only valid for static vertex buffers
	// Returns the number of vertices and the format of the vertex buffer
	virtual int VertexCount() const = 0;
	virtual VertexFormat_t GetVertexFormat() const = 0;

	// Is this vertex buffer dynamic?
	virtual bool IsDynamic() const = 0;

	// NOTE: For dynamic vertex buffers only!
	// Casts the memory of the dynamic vertex buffer to the appropriate type
	virtual void BeginCastBuffer(VertexFormat_t format) = 0;
	virtual void EndCastBuffer() = 0;

	// Returns the number of vertices that can still be written into the buffer
	virtual int GetRoomRemaining() const = 0;

	virtual bool Lock(int nVertexCount, bool bAppend, VertexDesc_t& desc) = 0;
	virtual void Unlock(int nVertexCount, VertexDesc_t& desc) = 0;

	// Spews the mesh data
	virtual void Spew(int nVertexCount, const VertexDesc_t& desc) = 0;

	// Call this in debug mode to make sure our data is good.
	virtual void ValidateData(int nVertexCount, const VertexDesc_t& desc) = 0;
};

struct IndexDesc_t
{
	// Pointers to the index data
	unsigned short* m_pIndices;

	// The offset in bytes of the memory we're writing into 
	// from the start of the D3D buffer (will be 0 for static meshes)
	unsigned int	m_nOffset;

	// The first index (used for buffered index buffers, or cards that don't support stream offset)
	unsigned int	m_nFirstIndex;

	// 1 if the device is active, 0 if the device isn't active.
	// Faster than doing if checks for null m_pIndices if someone is
	// trying to write the m_pIndices while the device is inactive.
	unsigned char m_nIndexSize;
};

enum MaterialIndexFormat_t
{
	MATERIAL_INDEX_FORMAT_UNKNOWN = -1,
	MATERIAL_INDEX_FORMAT_16BIT = 0,
	MATERIAL_INDEX_FORMAT_32BIT,
};
class IIndexBuffer
{
public:
	// NOTE: The following two methods are only valid for static index buffers
	// Returns the number of indices and the format of the index buffer
	virtual int IndexCount() const = 0;
	virtual MaterialIndexFormat_t IndexFormat() const = 0;

	// Is this index buffer dynamic?
	virtual bool IsDynamic() const = 0;

	// NOTE: For dynamic index buffers only!
	// Casts the memory of the dynamic index buffer to the appropriate type
	virtual void BeginCastBuffer(MaterialIndexFormat_t format) = 0;
	virtual void EndCastBuffer() = 0;

	// Returns the number of indices that can still be written into the buffer
	virtual int GetRoomRemaining() const = 0;

	// Locks, unlocks the index buffer
	virtual bool Lock(int nMaxIndexCount, bool bAppend, IndexDesc_t& desc) = 0;
	virtual void Unlock(int nWrittenIndexCount, IndexDesc_t& desc) = 0;

	// FIXME: Remove this!!
	// Locks, unlocks the index buffer for modify
	virtual void ModifyBegin(bool bReadOnly, int nFirstIndex, int nIndexCount, IndexDesc_t& desc) = 0;
	virtual void ModifyEnd(IndexDesc_t& desc) = 0;

	// Spews the mesh data
	virtual void Spew(int nIndexCount, const IndexDesc_t& desc) = 0;

	// Ensures the data in the index buffer is valid
	virtual void ValidateData(int nIndexCount, const IndexDesc_t& desc) = 0;
};
struct MeshDesc_t : VertexDesc_t, IndexDesc_t
{
};

//-----------------------------------------------------------------------------
// Interface to the mesh - needs to contain an IVertexBuffer and an IIndexBuffer to emulate old mesh behavior
//-----------------------------------------------------------------------------
class CMeshBuilder;
class IMesh : public IVertexBuffer, public IIndexBuffer
{
public:
	// -----------------------------------

	// Sets/gets the primitive type
	virtual void SetPrimitiveType(MaterialPrimitiveType_t type) = 0;

	// Draws the mesh
	virtual void Draw(int nFirstIndex = -1, int nIndexCount = 0) = 0;

	virtual void SetColorMesh(IMesh* pColorMesh, int nVertexOffset) = 0;

	// Draw a list of (lists of) primitives. Batching your lists together that use
	// the same lightmap, material, vertex and index buffers with multipass shaders
	// can drastically reduce state-switching overhead.
	// NOTE: this only works with STATIC meshes.
	virtual void Draw(CPrimList* pLists, int nLists) = 0;

	// Copy verts and/or indices to a mesh builder. This only works for temp meshes!
	virtual void CopyToMeshBuilder(
		int iStartVert,		// Which vertices to copy.
		int nVerts,
		int iStartIndex,	// Which indices to copy.
		int nIndices,
		int indexOffset,	// This is added to each index.
		CMeshBuilder& builder) = 0;

	// Spews the mesh data
	virtual void Spew(int nVertexCount, int nIndexCount, const MeshDesc_t& desc) = 0;

	// Call this in debug mode to make sure our data is good.
	virtual void ValidateData(int nVertexCount, int nIndexCount, const MeshDesc_t& desc) = 0;

	// New version
	// Locks/unlocks the mesh, providing space for nVertexCount and nIndexCount.
	// nIndexCount of -1 means don't lock the index buffer...
	virtual void LockMesh(int nVertexCount, int nIndexCount, MeshDesc_t& desc, void* pad = nullptr) = 0;
	virtual void ModifyBegin(int nFirstVertex, int nVertexCount, int nFirstIndex, int nIndexCount, MeshDesc_t& desc) = 0;
	virtual void ModifyEnd(MeshDesc_t& desc) = 0;
	virtual void UnlockMesh(int nVertexCount, int nIndexCount, MeshDesc_t& desc) = 0;

	virtual void ModifyBeginEx(bool bReadOnly, int nFirstVertex, int nVertexCount, int nFirstIndex, int nIndexCount, MeshDesc_t& desc) = 0;

	virtual void SetFlexMesh(IMesh* pMesh, int nVertexOffset) = 0;

	virtual void DisableFlexMesh() = 0;

	virtual void MarkAsDrawn() = 0;

};
class IMatRenderContext;
class CIndexBuilder : IndexDesc_t
{
public:
	CIndexBuilder();
	CIndexBuilder(IIndexBuffer* pIndexBuffer, MaterialIndexFormat_t fmt = MATERIAL_INDEX_FORMAT_UNKNOWN);
	~CIndexBuilder() {}

	// Begins, ends modification of the index buffer (returns true if the lock succeeded)
	// A lock may not succeed if append is set to true and there isn't enough room
	// NOTE: Append is only used with dynamic index buffers; it's ignored for static buffers
	bool Lock(int nMaxIndexCount, int nIndexOffset, bool bAppend = false);
	void Unlock();

	// Spews the current data
	// NOTE: Can only be called during a lock/unlock block
	void SpewData() const;

	// Returns the number of indices we can fit into the buffer without needing to discard
	int GetRoomRemaining() const;

	// Binds this index buffer
	void Bind(IMatRenderContext* pContext) const;

	// Returns the byte offset
	int Offset() const;

	// Begins, ends modification of the index buffer
	// NOTE: IndexOffset is the number to add to all indices written into the buffer;
	// useful when using dynamic vertex buffers.
	void Begin(IIndexBuffer* pIndexBuffer, int nMaxIndexCount, int nIndexOffset = 0);
	void End(bool bSpewData = false);

	// Locks the index buffer to modify existing data
	// Passing nVertexCount == -1 says to lock all the vertices for modification.
	// Pass 0 for nIndexCount to not lock the index buffer.
	void BeginModify(IIndexBuffer* pIndexBuffer, int nFirstIndex = 0, int nIndexCount = 0, int nIndexOffset = 0);
	void EndModify(bool bSpewData = false);

	// returns the number of indices
	int	IndexCount() const;

	// Returns the total number of indices across all Locks()
	int TotalIndexCount() const;

	// Resets the mesh builder so it points to the start of everything again
	void Reset() const;

	// Selects the nth Index 
	void SelectIndex(int nBufferIndex) const;

	// Advances the current index by one
	void AdvanceIndex();
	void AdvanceIndices(int nIndexCount);

	int GetCurrentIndex() const;
	int GetFirstIndex() const;

	unsigned short const* Index() const;

	// Used to define the indices (only used if you aren't using primitives)
	void Index(unsigned short nIndex) const;

	// Fast Index! No need to call advance index, and no random access allowed
	void FastIndex(unsigned short nIndex);

	// NOTE: This version is the one you really want to achieve write-combining;
	// Write combining only works if you write in 4 bytes chunks.
	void FastIndex2(unsigned short nIndex1, unsigned short nIndex2);

	// Generates indices for a particular primitive type
	void GenerateIndices(MaterialPrimitiveType_t primitiveType, int nIndexCount);

	// FIXME: Remove! Backward compat so we can use this from a CMeshBuilder.
	void AttachBegin(IMesh* pMesh, int nMaxIndexCount, const MeshDesc_t& desc);
	void AttachEnd();
	void AttachBeginModify(IMesh* pMesh, int nFirstIndex, int nIndexCount, const MeshDesc_t& desc);
	void AttachEndModify();

private:
	// The mesh we're modifying
	IIndexBuffer* m_pIndexBuffer;

	// Max number of indices
	int				m_nMaxIndexCount;

	// Number of indices
	int				m_nIndexCount;

	// Offset to add to each index as it's written into the buffer
	int				m_nIndexOffset;

	// The current index
	mutable int		m_nCurrentIndex;

	// Total number of indices appended
	int				m_nTotalIndexCount;

	// First index buffer offset + first index
	unsigned int	m_nBufferOffset;
	unsigned int	m_nBufferFirstIndex;

	// Used to make sure Begin/End calls and BeginModify/EndModify calls match.
	bool			m_bModify;
};

class CVertexBuilder : VertexDesc_t
{
public:
	CVertexBuilder();
	CVertexBuilder(IVertexBuffer* pVertexBuffer, VertexFormat_t fmt = 0);
	~CVertexBuilder();

	// Begins, ends modification of the index buffer (returns true if the lock succeeded)
	// A lock may not succeed if append is set to true and there isn't enough room
	// NOTE: Append is only used with dynamic index buffers; it's ignored for static buffers
	bool Lock(int nMaxIndexCount, bool bAppend = false);
	void Unlock();

	// Spews the current data
	// NOTE: Can only be called during a lock/unlock block
	void SpewData() const;

	// Returns the number of indices we can fit into the buffer without needing to discard
	int GetRoomRemaining() const;

	// Binds this vertex buffer
	void Bind(IMatRenderContext* pContext, int nStreamID, VertexFormat_t usage = 0) const;

	// Returns the byte offset
	int Offset() const;

	// This must be called before Begin, if a vertex buffer with a compressed format is to be used
	void SetCompressionType(VertexCompressionType_t compressionType);
	static void ValidateCompressionType();

	void Begin(IVertexBuffer* pVertexBuffer, int nVertexCount, int* nFirstVertex);
	void Begin(IVertexBuffer* pVertexBuffer, int nVertexCount);

	// Use this when you're done writing
	// Set bDraw to true to call m_pMesh->Draw automatically.
	void End(bool bSpewData = false);

	// Locks the vertex buffer to modify existing data
	// Passing nVertexCount == -1 says to lock all the vertices for modification.
	void BeginModify(IVertexBuffer* pVertexBuffer, int nFirstVertex = 0, int nVertexCount = -1);
	void EndModify(bool bSpewData = false);

	// returns the number of vertices
	int VertexCount() const;

	// Returns the total number of vertices across all Locks()
	int TotalVertexCount() const;

	// Resets the mesh builder so it points to the start of everything again
	void Reset();

	// Returns the size of the vertex
	int VertexSize() { return m_ActualVertexSize; }

	// returns the data size of a given texture coordinate
	int TextureCoordinateSize(int nTexCoordNumber) { return m_VertexSize_TexCoord[nTexCoordNumber]; }

	// Returns the base vertex memory pointer
	void* BaseVertexData() const;

	// Selects the nth Vertex and Index 
	void SelectVertex(int idx);

	// Advances the current vertex and index by one
	void AdvanceVertex();
	void AdvanceVertices(int nVerts);

	int GetCurrentVertex() const;
	int GetFirstVertex() const;

	// Data retrieval...
	const float* Position() const;

	const float* Normal() const;

	unsigned int Color() const;

	unsigned char* Specular() const;

	const float* TexCoord(int stage) const;

	const float* TangentS() const;
	const float* TangentT() const;

	const float* BoneWeight() const;
	float Wrinkle() const;

	int NumBoneWeights() const;
#ifndef NEW_SKINNING
	unsigned char* BoneMatrix() const;
#else
	float* BoneMatrix() const;
#endif

	// position setting
	void Position3f(float x, float y, float z) const;
	void Position3fv(const float* v) const;

	// normal setting
	void Normal3f(float nx, float ny, float nz) const;
	void Normal3fv(const float* n) const;
	void NormalDelta3fv(const float* n) const;
	void NormalDelta3f(float nx, float ny, float nz) const;
	// normal setting (templatized for code which needs to support compressed vertices)
	template <VertexCompressionType_t T> void CompressedNormal3f(float nx, float ny, float nz) const;
	template <VertexCompressionType_t T> void CompressedNormal3fv(const float* n) const;

	// color setting
	void Color3f(float r, float g, float b) const;
	void Color3fv(const float* rgb) const;
	void Color4f(float r, float g, float b, float a) const;
	void Color4fv(const float* rgba) const;

	// Faster versions of color
	void Color3ub(unsigned char r, unsigned char g, unsigned char b) const;
	void Color3ubv(unsigned char const* rgb) const;
	void Color4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a) const;
	void Color4ubv(unsigned char const* rgba) const;

	// specular color setting
	void Specular3f(float r, float g, float b) const;
	void Specular3fv(const float* rgb) const;
	void Specular4f(float r, float g, float b, float a) const;
	void Specular4fv(const float* rgba) const;

	// Faster version of specular
	void Specular3ub(unsigned char r, unsigned char g, unsigned char b) const;
	void Specular3ubv(unsigned char const* c) const;
	void Specular4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a) const;
	void Specular4ubv(unsigned char const* c) const;

	// texture coordinate setting
	void TexCoord1f(int stage, float s) const;
	void TexCoord2f(int stage, float s, float t) const;
	void TexCoord2fv(int stage, const float* st) const;
	void TexCoord3f(int stage, float s, float t, float u) const;
	void TexCoord3fv(int stage, const float* stu) const;
	void TexCoord4f(int stage, float s, float t, float u, float w) const;
	void TexCoord4fv(int stage, const float* stuv) const;

	void TexCoordSubRect2f(int stage, float s, float t, float offsetS, float offsetT, float scaleS, float scaleT) const;
	void TexCoordSubRect2fv(int stage, const float* st, const float* offset, const float* scale) const;

	// tangent space 
	void TangentS3f(float sx, float sy, float sz) const;
	void TangentS3fv(const float* s) const;

	void TangentT3f(float tx, float ty, float tz) const;
	void TangentT3fv(const float* t) const;

	// Wrinkle
	void Wrinkle1f(float flWrinkle) const;

	// bone weights
	void BoneWeight(int idx, float weight) const;
	// bone weights (templatized for code which needs to support compressed vertices)
	template <VertexCompressionType_t T> void CompressedBoneWeight3fv(const float* pWeights) const;

	// bone matrix index
	void BoneMatrix(int idx, int matrixIndex) const;

	// Generic per-vertex data
	void UserData(const float* pData) const;
	// Generic per-vertex data (templatized for code which needs to support compressed vertices)
	template <VertexCompressionType_t T> void CompressedUserData(const float* pData) const;

	// Fast Vertex! No need to call advance vertex, and no random access allowed. 
	// WARNING - these are low level functions that are intended only for use
	// in the software vertex skinner.
	void FastVertex(/*ModelVertexDX7_t*/ const int& vertex);
	void FastVertexSSE(/*ModelVertexDX7_t*/ const int& vertex);

	// store 4 dx7 vertices fast. for special sse dx7 pipeline
	void Fast4VerticesSSE(
		/*ModelVertexDX7_t*/ const int* vtx_a,
		/*ModelVertexDX7_t*/ const int* vtx_b,
		/*ModelVertexDX7_t*/ const int* vtx_c,
		/*ModelVertexDX7_t*/ const int* vtx_d);

	void FastVertex(/*ModelVertexDX8_t*/ const float& vertex);
	void FastVertexSSE(/*ModelVertexDX8_t*/ const float& vertex);

	// Add number of verts and current vert since FastVertex routines do not update.
	void FastAdvanceNVertices(int n);

#if defined( _X360 )
	void VertexDX8ToX360(const ModelVertexDX8_t& vertex);
#endif

	// FIXME: Remove! Backward compat so we can use this from a CMeshBuilder.
	void AttachBegin(IMesh* pMesh, int nMaxVertexCount, const MeshDesc_t& desc);
	void AttachEnd();
	void AttachBeginModify(IMesh* pMesh, int nFirstVertex, int nVertexCount, const MeshDesc_t& desc);
	void AttachEndModify();

private:
	// The vertex buffer we're modifying
	IVertexBuffer* m_pVertexBuffer;

	// Used to make sure Begin/End calls and BeginModify/EndModify calls match.
	bool m_bModify;

	// Max number of indices and vertices
	int m_nMaxVertexCount;

	// Number of indices and vertices
	int m_nVertexCount;

	// The current vertex and index
	mutable int m_nCurrentVertex;

	// Optimization: Pointer to the current pos, norm, texcoord, and color
	mutable float* m_pCurrPosition;
	mutable float* m_pCurrNormal;
	mutable float* m_pCurrTexCoord[8];
	mutable unsigned char* m_pCurrColor;

	// Total number of vertices appended
	int m_nTotalVertexCount;

	// First vertex buffer offset + index
	unsigned int m_nBufferOffset;
	unsigned int m_nBufferFirstVertex;

#if ( COMPRESSED_NORMALS_TYPE == COMPRESSED_NORMALS_COMBINEDTANGENTS_UBYTE4 )
	// Debug checks to make sure we write userdata4/tangents AFTER normals
	bool m_bWrittenNormal : 1;
	bool m_bWrittenUserData : 1;
#endif

	friend class CMeshBuilder;
};
class IMorph;
struct  MorphWeight_t;
class CMeshBuilder : public MeshDesc_t
{
public:
	CMeshBuilder();
	~CMeshBuilder() { /*if(m_pMesh) throw std::exception("CMeshBuilder: Begin() without an End()");*/ }		// if this fires you did a Begin() without an End()

																											// This must be called before Begin, if a vertex buffer with a compressed format is to be used
	void SetCompressionType(VertexCompressionType_t compressionType);

	// Locks the vertex buffer
	// (*cannot* use the Index() call below)
	void Begin(IMesh* pMesh, MaterialPrimitiveType_t type, int numPrimitives);

	// Locks the vertex buffer, can specify arbitrary index lists
	// (must use the Index() call below)
	void Begin(IMesh* pMesh, MaterialPrimitiveType_t type, int nVertexCount, int nIndexCount, int* nFirstVertex);
	void Begin(IMesh* pMesh, MaterialPrimitiveType_t type, int nVertexCount, int nIndexCount);

	// forward compat
	static void Begin(IVertexBuffer* pVertexBuffer, MaterialPrimitiveType_t type, int numPrimitives);
	static void Begin(IVertexBuffer* pVertexBuffer, IIndexBuffer* pIndexBuffer, MaterialPrimitiveType_t type, int nVertexCount, int nIndexCount, int* nFirstVertex);
	static void Begin(IVertexBuffer* pVertexBuffer, IIndexBuffer* pIndexBuffer, MaterialPrimitiveType_t type, int nVertexCount, int nIndexCount);

	// Use this when you're done writing
	// Set bDraw to true to call m_pMesh->Draw automatically.
	void End(bool bSpewData = false, bool bDraw = false);

	// Locks the vertex buffer to modify existing data
	// Passing nVertexCount == -1 says to lock all the vertices for modification.
	// Pass 0 for nIndexCount to not lock the index buffer.
	void BeginModify(IMesh* pMesh, int nFirstVertex = 0, int nVertexCount = -1, int nFirstIndex = 0, int nIndexCount = 0);
	void EndModify(bool bSpewData = false);

	// A helper method since this seems to be done a whole bunch.
	void DrawQuad(IMesh* pMesh, const float* v1, const float* v2,
		const float* v3, const float* v4, unsigned char const* pColor, bool wireframe = false);

	// returns the number of indices and vertices
	int VertexCount() const;
	int	IndexCount() const;

	// Resets the mesh builder so it points to the start of everything again
	void Reset();

	// Returns the size of the vertex
	int VertexSize() { return m_ActualVertexSize; }

	// returns the data size of a given texture coordinate
	int TextureCoordinateSize(int nTexCoordNumber) { return m_VertexSize_TexCoord[nTexCoordNumber]; }

	// Returns the base vertex memory pointer
	void* BaseVertexData() const;

	// Selects the nth Vertex and Index 
	void SelectVertex(int idx);
	void SelectIndex(int idx) const;

	// Given an index, point to the associated vertex
	void SelectVertexFromIndex(int idx);

	// Advances the current vertex and index by one
	void AdvanceVertex();
	void AdvanceVertices(int nVerts);
	void AdvanceIndex();
	void AdvanceIndices(int nIndices);

	int GetCurrentVertex() const;
	int GetCurrentIndex() const;

	// Data retrieval...
	const float* Position() const;

	const float* Normal() const;

	unsigned int Color() const;

	unsigned char* Specular() const;

	const float* TexCoord(int stage) const;

	const float* TangentS() const;
	const float* TangentT() const;

	const float* BoneWeight() const;
	float Wrinkle() const;

	int NumBoneWeights() const;
#ifndef NEW_SKINNING
	unsigned char* BoneMatrix() const;
#else
	float* BoneMatrix() const;
#endif
	unsigned short const* Index() const;

	// position setting
	void Position3f(float x, float y, float z) const;
	void Position3fv(const float* v) const;

	// normal setting
	void Normal3f(float nx, float ny, float nz) const;
	void Normal3fv(const float* n) const;
	void NormalDelta3fv(const float* n) const;
	void NormalDelta3f(float nx, float ny, float nz) const;

	// normal setting (templatized for code which needs to support compressed vertices)
	template <VertexCompressionType_t T> void CompressedNormal3f(float nx, float ny, float nz) const;
	template <VertexCompressionType_t T> void CompressedNormal3fv(const float* n) const;

	// color setting
	void Color3f(float r, float g, float b) const;
	void Color3fv(const float* rgb) const;
	void Color4f(float r, float g, float b, float a) const;
	void Color4fv(const float* rgba) const;

	// Faster versions of color
	void Color3ub(unsigned char r, unsigned char g, unsigned char b) const;
	void Color3ubv(unsigned char const* rgb) const;
	void Color4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a) const;
	void Color4ubv(unsigned char const* rgba) const;

	// specular color setting
	void Specular3f(float r, float g, float b) const;
	void Specular3fv(const float* rgb) const;
	void Specular4f(float r, float g, float b, float a) const;
	void Specular4fv(const float* rgba) const;

	// Faster version of specular
	void Specular3ub(unsigned char r, unsigned char g, unsigned char b) const;
	void Specular3ubv(unsigned char const* c) const;
	void Specular4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a) const;
	void Specular4ubv(unsigned char const* c) const;

	// texture coordinate setting
	void TexCoord1f(int stage, float s) const;
	void TexCoord2f(int stage, float s, float t) const;
	void TexCoord2fv(int stage, const float* st) const;
	void TexCoord3f(int stage, float s, float t, float u) const;
	void TexCoord3fv(int stage, const float* stu) const;
	void TexCoord4f(int stage, float s, float t, float u, float w) const;
	void TexCoord4fv(int stage, const float* stuv) const;

	void TexCoordSubRect2f(int stage, float s, float t, float offsetS, float offsetT, float scaleS, float scaleT) const;
	void TexCoordSubRect2fv(int stage, const float* st, const float* offset, const float* scale) const;

	// tangent space 
	void TangentS3f(float sx, float sy, float sz) const;
	void TangentS3fv(const float* s) const;

	void TangentT3f(float tx, float ty, float tz) const;
	void TangentT3fv(const float* t) const;

	// Wrinkle
	void Wrinkle1f(float flWrinkle) const;

	// bone weights
	void BoneWeight(int idx, float weight) const;
	// bone weights (templatized for code which needs to support compressed vertices)
	template <VertexCompressionType_t T> void CompressedBoneWeight3fv(const float* pWeights) const;

	// bone matrix index
	void BoneMatrix(int idx, int matrixIndex) const;

	// Generic per-vertex data
	void UserData(const float* pData) const;
	// Generic per-vertex data (templatized for code which needs to support compressed vertices)
	template <VertexCompressionType_t T> void CompressedUserData(const float* pData) const;

	// Used to define the indices (only used if you aren't using primitives)
	void Index(unsigned short index) const;

	// NOTE: Use this one to get write combining! Much faster than the other version of FastIndex
	// Fast Index! No need to call advance index, and no random access allowed
	void FastIndex2(unsigned short nIndex1, unsigned short nIndex2);

	// Fast Index! No need to call advance index, and no random access allowed
	void FastIndex(unsigned short index);

	// Fast Vertex! No need to call advance vertex, and no random access allowed. 
	// WARNING - these are low level functions that are intended only for use
	// in the software vertex skinner.
	void FastVertex(/*ModelVertexDX7_t*/ const int& vertex);
	void FastVertexSSE(/*ModelVertexDX7_t*/ const int& vertex);

	// store 4 dx7 vertices fast. for special sse dx7 pipeline
	void Fast4VerticesSSE(
		/*ModelVertexDX7_t*/ const int* vtx_a,
		/*ModelVertexDX7_t*/ const int* vtx_b,
		/*ModelVertexDX7_t*/ const int* vtx_c,
		/*ModelVertexDX7_t*/ const int* vtx_d);

	void FastVertex(/*ModelVertexDX8_t*/ const float& vertex);
	void FastVertexSSE(/*ModelVertexDX8_t*/ const float& vertex);

	// Add number of verts and current vert since FastVertexxx routines do not update.
	void FastAdvanceNVertices(int n);

#if defined( _X360 )
	void VertexDX8ToX360(const ModelVertexDX8_t& vertex);
#endif

private:
	// Computes number of verts and indices 
	static void ComputeNumVertsAndIndices(int* pMaxVertices, int* pMaxIndices,
		MaterialPrimitiveType_t type, int nPrimitiveCount);
	static int IndicesFromVertices(MaterialPrimitiveType_t type, int nVertexCount);

	// The mesh we're modifying
	IMesh* m_pMesh;

	MaterialPrimitiveType_t m_Type;

	// Generate indices?
	bool m_bGenerateIndices;

	CIndexBuilder	m_IndexBuilder;
	CVertexBuilder	m_VertexBuilder;
};
struct MaterialLightingState_t;
struct MaterialMatrixMode_t;
enum MaterialCullMode_t
{
	MATERIAL_CULLMODE_CCW,	// this culls polygons with counterclockwise winding
	MATERIAL_CULLMODE_CW	// this culls polygons with clockwise winding
};
enum MaterialHeightClipMode_t
{
	MATERIAL_HEIGHTCLIPMODE_DISABLE,
	MATERIAL_HEIGHTCLIPMODE_RENDER_ABOVE_HEIGHT,
	MATERIAL_HEIGHTCLIPMODE_RENDER_BELOW_HEIGHT
};
struct LightDesc_t;
class Vector4D;
enum MaterialFogMode_t
{
	MATERIAL_FOG_NONE,
	MATERIAL_FOG_LINEAR,
	MATERIAL_FOG_LINEAR_BELOW_FOG_Z,
};
struct OcclusionQueryObjectHandle_t;
struct MorphFormat_t;
struct Rect_t;
struct FlashlightState_t;
class ICallQueue;
struct ColorCorrectionHandle_t;
struct MaterialNonInteractiveMode_t;
struct DeformationBase_t;
class IMaterial;
class IMatRenderContext : public IRefCounted
{
public:
	virtual void add_ref() = 0;
	virtual void release() = 0;

	void ClearBuffers(bool clear_color, bool clear_depth, bool clear_stencil = false)
	{
		typedef void(__thiscall * org_fn)(PVOID, bool, bool, bool);
		virtualFunction<org_fn>(this, 12)(this, clear_color, clear_depth, clear_stencil);
	}

	// virtual void	ClearColor4ub( unsigned char r, unsigned char g, unsigned char b, unsigned char a ) = 0;
	void SetClearColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		typedef void(__thiscall * org_fn)(PVOID, unsigned char, unsigned char, unsigned char, unsigned char);
		virtualFunction<org_fn>(this, 79)(this, r, g, b, a);
	}

	void PushRenderTargetAndViewport()
	{
		typedef void(__thiscall * org_fn)(PVOID);
		virtualFunction<org_fn>(this, 118)(this);
	}

	void PopRenderTargetAndViewport()
	{
		typedef void(__thiscall * org_fn)(PVOID);
		virtualFunction<org_fn>(this, 119)(this);
	}

	void SetRenderTarget(VTexture* target)
	{
		typedef void(__thiscall * org_fn)(PVOID, VTexture*);
		virtualFunction<org_fn>(this, 6)(this, target);
	}

};
template<class T> class CUtlReference
{
public:
	FORCEINLINE CUtlReference(void)
	{
		m_pNext = m_pPrev = NULL;
		m_pObject = NULL;
	}

	FORCEINLINE CUtlReference(T* pObj)
	{
		m_pNext = m_pPrev = NULL;
		AddRef(pObj);
	}

	FORCEINLINE ~CUtlReference(void)
	{
		KillRef();
	}

	FORCEINLINE void Set(T* pObj)
	{
		if (m_pObject != pObj)
		{
			KillRef();
			AddRef(pObj);
		}
	}

	FORCEINLINE T* operator()(void) const
	{
		return m_pObject;
	}

	FORCEINLINE operator T* ()
	{
		return m_pObject;
	}

	FORCEINLINE operator const T* () const
	{
		return m_pObject;
	}

	FORCEINLINE T* operator->()
	{
		return m_pObject;
	}

	FORCEINLINE const T* operator->() const
	{
		return m_pObject;
	}

	FORCEINLINE CUtlReference& operator=(const CUtlReference& otherRef)
	{
		Set(otherRef.m_pObject);
		return *this;
	}

	FORCEINLINE CUtlReference& operator=(T* pObj)
	{
		Set(pObj);
		return *this;
	}


	FORCEINLINE bool operator==(const CUtlReference& o) const
	{
		return (o.m_pObject == m_pObject);
	}

public:
	CUtlReference* m_pNext;
	CUtlReference* m_pPrev;

	T* m_pObject;

	FORCEINLINE void AddRef(T* pObj)
	{
		m_pObject = pObj;
		if (pObj)
		{
			pObj->m_References.AddToHead(this);
		}
	}

	FORCEINLINE void KillRef(void)
	{
		if (m_pObject)
		{
			m_pObject->m_References.RemoveNode(this);
			m_pObject = NULL;
		}
	}

};


