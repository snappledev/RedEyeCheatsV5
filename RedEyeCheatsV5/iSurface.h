#pragma once

#include "color.h"
#include "virtualFunction.h"
#include "Game.h"
#include "vector2D.h"
#include <Windows.h>
#include "xor.h"
struct Vertex_t
{
	Vector2D	m_Position;
	Vector2D	m_TexCoord;
	Vertex_t() {}
	Vertex_t(const Vector2D &pos, const Vector2D &coord = Vector2D(0, 0))
	{
		m_Position = pos;
		m_TexCoord = coord;
	}
	void Init(const Vector2D &pos, const Vector2D &coord = Vector2D(0, 0))
	{
		m_Position = pos;
		m_TexCoord = coord;
	}
};
struct vertex
{
	int x, y;
};
class iSurface {
public:
	OFFSET(bool, m_bClippingEnabled, 0x280);
	void setbClippingEnabled(bool v) {
		*reinterpret_cast<bool*>(uintptr_t(this) + 0x280) = v;
	}
	void PushMakeCurrent(int panel, bool useInsets) {
		typedef void(__thiscall* function)(PVOID, int, bool);
		return virtualFunction<function>(this, 12)(this, panel, useInsets);
	}
	void PopMakeCurrent(int panel) {
		typedef void(__thiscall* function)(PVOID, int);
		return virtualFunction<function>(this, 13)(this, panel);
	}

	void DrawSetColor(color col) {
		typedef void(__thiscall* function)(PVOID, color);
		return virtualFunction<function>(this, 14)(this, col);
	}
	void DrawSetColor(int r, int g, int b, int a) {
		typedef void(__thiscall* function)(PVOID, int, int, int, int);
		virtualFunction<function>(this, 15)(this, r, g, b, a);
	}
	void DrawFilledRect(int x0, int y0, int x1, int y1) {
		typedef void(__thiscall* function)(PVOID, int, int, int, int);
		virtualFunction<function>(this, 16)(this, x0, y0, x1, y1);
	}
	void DrawOutlinedRect(int x0, int y0, int x1, int y1) {
		typedef void(__thiscall* function)(PVOID, int, int, int, int);
		virtualFunction<function>(this, 18)(this, x0, y0, x1, y1);
	}
	void DrawLine(int x0, int y0, int x1, int y1) {
		typedef void(__thiscall* function)(PVOID, int, int, int, int);
		virtualFunction<function>(this, 19)(this, x0, y0, x1, y1);
	}

	void DrawPolyLine(int *x, int *y, int count) {
		typedef void(__thiscall* function)(PVOID, int *, int *, int);
		virtualFunction<function>(this, 20)(this, x, y, count);
	}
	void DrawSetTextFont(unsigned long font) {
		typedef void(__thiscall* function)(PVOID, unsigned long);
		virtualFunction<function>(this, 23)(this, font);
	}
	void DrawSetTextColor(color col) {
		typedef void(__thiscall* function)(PVOID, color);
		return virtualFunction<function>(this, 24)(this, col);
	}
	void DrawSetTextColor(int r, int g, int b, int a) {
		typedef void(__thiscall* function)(PVOID, int, int, int, int);
		virtualFunction<function>(this, 25)(this, r, g, b, a);
	}
	void DrawSetTextPos(int x, int y) {
		typedef void(__thiscall* function)(PVOID, int, int);
		virtualFunction<function>(this, 26)(this, x, y);
	}
	void DrawPrintText(const wchar_t* text, int textLen) {
		typedef void(__thiscall* function)(PVOID, const wchar_t*, int, int);
		virtualFunction<function>(this, 28)(this, text, textLen, 0);
	}
	void DrawSetTexture(int textureID) {
		typedef void(__thiscall* function)(PVOID, int);
		return virtualFunction<function>(this, 38)(this, textureID);
	}
	void DrawSetTextureRGBA(int textureID, const unsigned char* colors, uint32_t w, uint32_t h) {
		typedef void(__thiscall* function)(PVOID, int, unsigned char  const*, uint32_t, uint32_t);
		return virtualFunction<function>(this, 37)(this, textureID, colors, w, h);
	}
	inline void DrawTexturedRect(int x, int y, int w, int h) {
		typedef void(__thiscall *function)(void *, int, int, int, int);
		virtualFunction<function>(this, 41)(this, x, y, w, h);
	}
	bool IsTextureIDValid(int textureID) {
		typedef bool(__thiscall* function)(PVOID, int);
		return virtualFunction<function>(this, 42)(this, textureID);
	}
	int CreateNewTextureID(bool procedural) {
		typedef int(__thiscall* function)(PVOID, bool);
		return virtualFunction<function>(this, 43)(this, procedural);
	}
	void SurfaceGetCursorPos(int &x, int &y) {
		typedef void(__thiscall* function)(PVOID, int&, int&);
		return virtualFunction<function>(this, 66)(this, x, y);
	}

	unsigned long FontCreate() {
		typedef unsigned int(__thiscall* function)(PVOID);
		return virtualFunction<function>(this, 71)(this);
	}
	void SetFontGlyphSet(unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags) {
		typedef void(__thiscall* function)(PVOID, unsigned long, const char*, int, int, int, int, int, int, int);
		virtualFunction<function>(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}
	void GetTextSize(unsigned long font, const wchar_t* text, int& wide, int& tall) {
		typedef void(__thiscall* function)(PVOID, unsigned long, const wchar_t*, int&, int&);
		virtualFunction<function>(this, 79)(this, font, text, wide, tall);
	}
	void DrawOutlinedCircle(int x, int y, int r, int seg) {
		typedef void(__thiscall* function)(PVOID, int, int, int, int);
		return virtualFunction<function>(this, 103)(this, x, y, r, seg);
	}
	void DrawTexturedPolygon(int vtxCount, Vertex_t *vtx, bool bClipVertices = true) {
		typedef void(__thiscall* function)(PVOID, int, Vertex_t*, bool);
		return virtualFunction<function>(this, 106)(this, vtxCount, vtx, bClipVertices);
	}
	void GetClipRect(int& x, int& y, int& x2, int& y2) {
		typedef void(__thiscall* function)(PVOID, int&, int&, int&, int&);
		return virtualFunction<function>(this, 146)(this, x, y, x2, y2);
	}
	void SetClipRect(int x, int y, int x2, int y2) {
		typedef void(__thiscall* function)(PVOID, int&, int&, int&, int&);
		return virtualFunction<function>(this, 147)(this, x, y, x2, y2);
	}
	void DisableClipping(bool c) {
		typedef void(__thiscall * function)(PVOID, bool);
		return virtualFunction<function>(this, 159)(this, c);
	}
	void UnlockCursor() {
		typedef void(__thiscall * UnlockCursor)(void*);
		virtualFunction<UnlockCursor>(this, 66)(this);
	}
};