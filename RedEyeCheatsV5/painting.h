#pragma once
#include "iSurface.h"
#include "color.h"
#include "interfaces.h"
#include <string>
#include "icons.h"
enum fontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

struct font {
	font(std::string n, int s, int w, bool b) : name(n), size(s), weight(w), outlined(b) {}
	void fillData(bool useC) {
		data = interfaceManager::isurface->FontCreate();
		interfaceManager::isurface->SetFontGlyphSet(data, name.c_str(), size * (useC ? Game::menu_scale_factor : 1), weight, 0, 0, outlined ? FONTFLAG_OUTLINE : FONTFLAG_ANTIALIAS);
	}
	void resetFont(bool useC) {
		if (!data)
			fillData(useC);
		else
			interfaceManager::isurface->SetFontGlyphSet(data, name.c_str(), size * (useC ? Game::menu_scale_factor : 1), weight, 0, 0, outlined ? FONTFLAG_OUTLINE : FONTFLAG_ANTIALIAS);
	}
	DWORD data;
	std::string name = "";
	int size = 1;
	int weight = 600;
	bool outlined = false;
};
class Paint {
public:
	void setupFonts();
	void resetFonts();
	void rectangle(int x, int y, int w, int h, color color, RECT clipArea = {0,0,0,0});
	void outline(int x, int y, int w, int h, color color, RECT clipArea = { 0,0,0,0 });

	void circle(int x, int y, int r, color color, RECT clipArea = { 0,0,0,0 });
	void circleOutline(int x, int y, int r, color color, RECT clipArea = { 0,0,0,0 });

	void text(int x, int y, const wchar_t data[], font glyph, Anchor pos, color color, RECT clipArea = { 0,0,0,0 });
	void line(int x, int y, int x2, int y2, color color, RECT clipArea = { 0,0,0,0 });
	void text(int x, int y, const char* data, font glyph, Anchor pos, color color, RECT clipArea = { 0,0,0,0 });
	void scalineTriangle(int x, int y, int x2, int y2, int x3, int y3, color color, RECT clipArea = { 0,0,0,0 });
	void image(int x, int y, int w, int h, imageData img, RECT clipArea = { 0,0,0,0 });
	void imageAlpha(int x, int y, int w, int h, imageData img, float alph, RECT clipArea = { 0,0,0,0 });
	void scalineTriangleOutline(int x, int y, int x2, int y2, int x3, int y3, color color, RECT clipArea = { 0,0,0,0 });
	
	void corner(int x, int y, int w, int h, color color, bool outline, RECT clipArea = {0,0,0,0});
	
	void threeLine(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3, color col, RECT clipArea = {0,0,0,0});
	void octagonBox(int x, int y, int w, int h, color col, RECT clipArea = {0,0,0,0});

	RECT textSize(const char* data, font glyph);
	
	void startClip(int x, int y, int w, int h);
	void endClip();
	bool bCustomClip = false;
	int x, y, x1, y1 = 0;
	int panelID = 0;
	bool bGlyphsCreated = false;
	bool bQueFontReset = false;
};
extern std::shared_ptr<Paint> paint;
namespace Glyphs {
	extern font menu_control;
	extern font menu_list;
	extern font menu_splash;
	extern font menu_main;
	extern font feature_esp;
	extern font menu_icons;


	extern font menu_tab;
	extern font menu_subtab;;
	extern font menu_grabtext;;
	extern font debug_warning;;
}