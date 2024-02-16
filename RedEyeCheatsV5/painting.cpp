#include "painting.h"
#include "interfaces.h"
std::shared_ptr<Paint> paint;
#define PI 3.1415
#define radianstodegrees(x) ((x*180)/PI)
#define degreestoradians(x) ((x*PI)/180)
void Paint::resetFonts() {
	if (bQueFontReset) {
		Glyphs::menu_control.resetFont(true);
		Glyphs::menu_list.resetFont(true);
		Glyphs::menu_splash.resetFont(true);
		Glyphs::feature_esp.resetFont(false);
		Glyphs::menu_main.resetFont(true);
		Glyphs::menu_icons.resetFont(true);
		Glyphs::menu_tab.resetFont(true);
		Glyphs::menu_subtab.resetFont(true);
		Glyphs::menu_grabtext.resetFont(true);
		Glyphs::debug_warning.resetFont(false);
		bQueFontReset = false;
	}
}
void Paint::setupFonts() {



	Glyphs::menu_control.fillData(true);
	Glyphs::menu_list.fillData(true);
	Glyphs::menu_splash.fillData(true);
	Glyphs::feature_esp.fillData(false);
	Glyphs::menu_main.fillData(true);
	Glyphs::menu_icons.fillData(true);
	Glyphs::menu_tab.fillData(true);
	Glyphs::menu_subtab.fillData(true);
	Glyphs::menu_grabtext.fillData(true);
	Glyphs::debug_warning.fillData(false);
	bGlyphsCreated = true;
}
void Paint::outline(int x, int y, int w, int h, color color, RECT clipArea) {
	
	startClip(clipArea.left, clipArea.top, clipArea.right, clipArea.bottom);

	interfaceManager::isurface->DrawSetColor(color);
	interfaceManager::isurface->DrawOutlinedRect(x, y, x + w, y + h);

	
	endClip();
}
void Paint::rectangle(int x, int y, int w, int h, color color, RECT clipArea) {
	
	startClip(clipArea.left, clipArea.top, clipArea.right, clipArea.bottom);

	interfaceManager::isurface->DrawSetColor(color);
	interfaceManager::isurface->DrawFilledRect(x, y, x + w, y + h);

	
	endClip();

}
void Paint::scalineTriangle(int x, int y, int x2, int y2, int x3, int y3, color color, RECT clipArea) {
	
	startClip(clipArea.left, clipArea.top, clipArea.right, clipArea.bottom);

	static int texture = interfaceManager::isurface->CreateNewTextureID(true);
	unsigned char texture_buffer[4] = { 255, 255, 255, 255 };
	interfaceManager::isurface->DrawSetTextureRGBA(texture, texture_buffer, 1, 1);
	interfaceManager::isurface->DrawSetColor(color);
	interfaceManager::isurface->DrawSetTexture(texture);
	Vertex_t vert[3]; vert[0].m_Position.x = x; vert[0].m_Position.y = y; vert[1].m_Position.x = x2; vert[1].m_Position.y = y2; vert[2].m_Position.x = x3; vert[2].m_Position.y = y3;
	interfaceManager::isurface->DrawTexturedPolygon(3, vert);

	
	endClip();



}
void Paint::scalineTriangleOutline(int x, int y, int x2, int y2, int x3, int y3, color color, RECT clipArea) {
	
	startClip(clipArea.left, clipArea.top, clipArea.right, clipArea.bottom);

	interfaceManager::isurface->DrawSetColor(color);
	int xArray[3]; xArray[0] = x; xArray[1] = x2; xArray[2] = x3;
	int yArray[3]; yArray[0] = y; yArray[1] = y2; yArray[2] = y3;
	interfaceManager::isurface->DrawPolyLine(xArray, yArray, 3);

	
	endClip();

}
void Paint::circle(int x, int y, int r, color color, RECT clipArea) {
	
	startClip(clipArea.left, clipArea.top, clipArea.right, clipArea.bottom);

	static int texture = interfaceManager::isurface->CreateNewTextureID(true);
	unsigned char texture_buffer[4] = { 255, 255, 255, 255 };
	interfaceManager::isurface->DrawSetTextureRGBA(texture, texture_buffer, 1, 1);
	interfaceManager::isurface->DrawSetColor(color);
	interfaceManager::isurface->DrawSetTexture(texture);
	const int segments = 30;
	Vertex_t vert[segments];
	for (int i = 0; i < segments; i++) {
		float angle = degreestoradians(i * (360 / segments));
		vert[i].m_Position.x = cos(angle) * r + x;
		vert[i].m_Position.y = sin(angle) * r + y;
	}
	interfaceManager::isurface->DrawTexturedPolygon(segments, vert);

	
	endClip();
}
void Paint::line(int x, int y, int x2, int y2, color color, RECT clipArea) {
	
	startClip(clipArea.left, clipArea.top, clipArea.right, clipArea.bottom);

	interfaceManager::isurface->DrawSetColor(color);
	interfaceManager::isurface->DrawLine(x, y, x2, y2);

	
	endClip();
}
void Paint::circleOutline(int x, int y, int r, color color, RECT clipArea) {
	
	startClip(clipArea.left, clipArea.top, clipArea.right, clipArea.bottom);

	interfaceManager::isurface->DrawSetColor(color);
	interfaceManager::isurface->DrawOutlinedCircle(x, y, r, 10 + r);

	
	endClip();
}
void Paint::corner(int x, int y, int w, int h, color colo, bool outline, RECT clipArea)
{
	if (outline) {
		rectangle(x - 1, y - 1, (w / 5) + 3, 3, color(0, 0, 0, 255), clipArea); //LEFT LEFTSIDE
		rectangle(x - 1, y - 1, 3, (w / 5) + 3, color(0, 0, 0, 255), clipArea); //LEFT LEFTSIDE
	}

	line(x, y, x + (w / 5), y, colo, clipArea); //LEFT TOP
	line(x, y, x, y + (w / 5), colo, clipArea); //LEFT LEFTSIDE		
	if (outline) {
		rectangle(x + w - 1, y, 3, (w / 5) + 2, color(0, 0, 0, 255), clipArea); //LEFT LEFTSIDE
		rectangle(x + w - (w / 5) - 1, y - 1, (w / 5) + 3, 3, color(0, 0, 0, 255), clipArea); //LEFT TOP
	}
	line(x + w, y, x + w, y + (w / 5), colo, clipArea); //LEFT LEFTSIDE
	line(x + w, y, x + w - (w / 5), y, colo, clipArea); //LEFT TOP																																	//BOTTOM LEFT
	if (outline) {
		rectangle(x - 1, (y + h) - 1, (w / 5) + 3, 3, color(0, 0, 0, 255), clipArea); //LEFT TOP
		rectangle(x - 1, (y + (h)) - (w / 5) - 1, 3, (w / 5) + 2, color(0, 0, 0, 255), clipArea); //LEFT TOP
	}
	line(x, y + h, x + (w / 5), y + h, colo, clipArea); //BOTTOM LEFT
	line(x, y + h, x, (y + h) - (w / 5), colo, clipArea); //BOTTOM LEFT																																			  //BOTTOM RIGHT
	if (outline) {
		rectangle(x + w - 1, ((y + h) - (w / 5)) - 1, 3, (w / 5) + 3, color(0, 0, 0,255), clipArea); //VERTICLE BIT
		rectangle(x + w - (w / 5) - 1, y + h - 1, (w / 5) + 2, 3, color(0, 0, 0, 255), clipArea); //BOTTOM BIT
	}
	line(x + w, y + h, x + w, (y + h) - (w / 5), colo, clipArea); //LEFT TOP
	line(x + w, y + h, (x + w) - (w / 5), y + h, colo, clipArea); //LEFT TOP
}
void Paint::threeLine(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3, color col, RECT clipArea) {
	line(x, y, x1, y1, col, clipArea);
	line(x1, y1, x2, y2, col, clipArea);
	line(x2, y2, x3, y3, col, clipArea);
}
void Paint::octagonBox(int x, int y, int w, int h, color col, RECT clipArea)
{
	int SideHeight = h / 6;
	int AddHeight = SideHeight / 2;
	threeLine(x, y + SideHeight + AddHeight, x, y + SideHeight, x + SideHeight, y, x + SideHeight + AddHeight, y, col, clipArea); //topleft
	threeLine(x + w - SideHeight - AddHeight, y, x + w - SideHeight, y, x + w, y + SideHeight, x + w, y + SideHeight + AddHeight, col, clipArea);//Top right
	threeLine(x, y + h - SideHeight - AddHeight, x, y + h - SideHeight, x + SideHeight, y + h, x + SideHeight + AddHeight, y + h, col, clipArea); //Bottom left
	threeLine(x + w, y + h - SideHeight - AddHeight, x + w, y + h - SideHeight, x + w - SideHeight, y + h, x + w - SideHeight - AddHeight, y + h, col, clipArea); // bottom right
}
RECT Paint::textSize(const char* data, font glyph) {
	int wide = 0, tall = 0;
	wchar_t buf[1024];

	if (MultiByteToWideChar(CP_UTF8, 0, data, -1, buf, 1024) > 0) {
		interfaceManager::isurface->GetTextSize(glyph.data, buf, wide, tall);
	}
	return RECT{ 0,0,wide,tall };
}
void Paint::text(int x, int y, const wchar_t data[], font glyph, Anchor pos, color color, RECT clipArea) {


	if (!bGlyphsCreated)
		setupFonts();

	if (glyph.data) {

		
		startClip(clipArea.left, clipArea.top, clipArea.right, clipArea.bottom);
		

		int wide, tall;
		interfaceManager::isurface->GetTextSize(glyph.data, data, wide, tall);
		float posX = x, posY = y;
		Functions::ModifyPosition(posX, posY, wide, tall, pos);
		interfaceManager::isurface->DrawSetTextPos(posX, posY);
		interfaceManager::isurface->DrawSetTextFont(glyph.data);
		interfaceManager::isurface->DrawSetTextColor(color.r(), color.g(), color.b(), color.a());
		interfaceManager::isurface->DrawPrintText(data, wcslen(data));
		
		
		endClip();
	}
}
void Paint::text(int x, int y, const char* data, font glyph, Anchor pos, color color, RECT clipArea) {


	if (!bGlyphsCreated)
		setupFonts();
	if (glyph.data) {

		
		startClip(clipArea.left, clipArea.top, clipArea.right, clipArea.bottom);

		wchar_t buf[1024];

		if (MultiByteToWideChar(CP_UTF8, 0, data, -1, buf, 1024) > 0) {
			int wide, tall;
			interfaceManager::isurface->GetTextSize(glyph.data, buf, wide, tall);
			float posX = x, posY = y;
			Functions::ModifyPosition(posX, posY, wide, tall, pos);
			interfaceManager::isurface->DrawSetTextFont(glyph.data);
			interfaceManager::isurface->DrawSetTextColor(color);
			interfaceManager::isurface->DrawSetTextPos(posX, posY);
			interfaceManager::isurface->DrawPrintText(buf, wcslen(buf));
		}
		/*
		va_list va_alist; char buffer[1024] = { '\0' }; wchar_t string[1024] = { '\0' };
		va_start(va_alist, data);
		vsprintf_s(buffer, data, va_alist);
		va_end(va_alist);
		wsprintfW(string, L"%S", buffer);
		int wide, tall;
		interfaceManager::isurface->GetTextSize(glyph.data, string, wide, tall);
		float posX = x, posY = y;
		Functions::ModifyPosition(posX, posY, wide, tall, pos);
		interfaceManager::isurface->DrawSetTextPos(posX, posY);
		interfaceManager::isurface->DrawSetTextFont(glyph.data);
		interfaceManager::isurface->DrawSetTextColor(color.r(), color.g(), color.b(), color.a());
		interfaceManager::isurface->DrawPrintText(string, wcslen(string));
		*/
		
		endClip();
	}
}
void Paint::image(int x, int y, int w, int h, imageData img, RECT clipArea) {

	if (!img.m_iTexture) return;
	startClip(clipArea.left, clipArea.top, clipArea.right, clipArea.bottom);
	interfaceManager::isurface->DrawSetColor(255,255,255,255);
	interfaceManager::isurface->DrawSetTexture(img.m_iTexture);

	interfaceManager::isurface->DrawTexturedRect(x, y, x + w, y + h);
	endClip();
}
void Paint::imageAlpha(int x, int y, int w, int h, imageData img, float alph, RECT clipArea) {

	if (!img.m_iTexture) return;
	startClip(clipArea.left, clipArea.top, clipArea.right, clipArea.bottom);
	interfaceManager::isurface->DrawSetColor(255, 255, 255, alph);
	interfaceManager::isurface->DrawSetTexture(img.m_iTexture);

	interfaceManager::isurface->DrawTexturedRect(x, y, x + w, y + h);
	endClip();
}
void Paint::startClip(int x_, int y_, int w_, int h_) {
	
	if (x_ == 0 && y_ == 0 && w_ == 0 && h_ == 0) {
		//WE AREN't WANTING TO CLIP THE AREA
		if (x != 0 || y != 0 || x1 != 0 || y1 != 0) {
			// WE PREVIOUSLY HAVE WANTED TO CLIP THE AREA
			bCustomClip = true;
			interfaceManager::isurface->PopMakeCurrent(panelID);
			interfaceManager::isurface->PushMakeCurrent(panelID, false);

			x = 0; y = 0; x1 = 0; y1 = 0;
			bCustomClip = false;
			interfaceManager::isurface->PopMakeCurrent(panelID);
			interfaceManager::isurface->PushMakeCurrent(panelID, false);
		}
		
	}
	else {
		//WE ARE WANTING TO CLIP AN AREA
		if (x_ != x || y_ != y || w_ != x1 || h_ != y1) {
			//ITS A NEW AREA AS ITS DIFFERENT
			if (x == 0 && y == 0 && x1 == 0 && y1 == 0) {
				//OLD ONE WAS 0
				x = x_; y = y_; x1 = x_ + w_; y1 = y_ + h_;
				
				//SET NEW COORDS
			}
			else {
				//OLD ONE WASNT BUT IS STILL DIFFERENT
				bCustomClip = true;
				interfaceManager::isurface->PopMakeCurrent(panelID);
				interfaceManager::isurface->PushMakeCurrent(panelID, false);

				bCustomClip = false;
				x = x_; y = y_; x1 = x_ + w_; y1 = y_ + h_;
			}
		}
	}




	if (x_ == 0 && y_ == 0 && w_ == 0 && h_ == 0) {
		if (x != x_ || y != y_ || x1 != w_ || y1 != h_) {
			bCustomClip = true;
			interfaceManager::isurface->PopMakeCurrent(panelID);
			interfaceManager::isurface->PushMakeCurrent(panelID, false);

			bCustomClip = false;
			interfaceManager::isurface->PopMakeCurrent(panelID);
			interfaceManager::isurface->PushMakeCurrent(panelID, false);
			x = 0; y = 0; x1 = 0; y1 = 0;
		}
	}
	else if (x != x_ || y != y_ || x1 != w_ || y1 != h_) {
		if (!(x == 0 && y == 0 && x1 == 0 && y1 == 0)) {
			bCustomClip = true;
			interfaceManager::isurface->PopMakeCurrent(panelID);
			interfaceManager::isurface->PushMakeCurrent(panelID, false);
			x = x_; y = y_; x1 = w_; y1 = h_;
		}
	}
}
void Paint::endClip() {
	
	//interfaceManager::isurface->SetClipRect(0, 0, Game::m_iWidth, Game::m_iHeight);
	/*bCustomClip = false;
	interfaceManager::isurface->PopMakeCurrent(panelID);
	interfaceManager::isurface->PushMakeCurrent(panelID, false);*/

	//x = 0; y = 0; x1 = Game::m_iWidth; y1 = Game::m_iHeight;
	//int tmX = 0, tmY = 0, tmW = 0, tmH = 0;
	//interfaceManager::ipanel->GetClipRect(panelID, tmX, tmY, tmW, tmH);
}
namespace Glyphs {
	font menu_control = font("Segoe UI", 15, 100, false);
	font feature_esp = font("Tahoma", 12, 600, true);
	font menu_list = font("Segoe UI", 13, 100, false);
	font menu_splash = font("Segoe UI", 13, 100, false);
	font menu_main = font("Segoe UI", 45, 300, false);
	font menu_icons = font("Segoe MDL2 Assets", 45, 600, false);



	font menu_tab = font("Segoe UI", 13, 100, false);
	font menu_subtab = font("Segoe UI", 13, 100, false);
	font  menu_grabtext = font("Segoe UI", 20, 100, false);
	font debug_warning = font("Segoe UI", 50, 100, false);
}
