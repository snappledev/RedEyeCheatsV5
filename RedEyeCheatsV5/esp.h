#pragma once
#include "interfaces.h"
#include "Functions.h"
#include "cBaseEntity.h"
#include "painting.h"
#include "cCSPlayer.h"
#include "cBasePlayer.h"
#include "CCSBomb.h"
#include "vector.h"
struct strcol
{
	std::string txt;
	color col;
};
class Box
{
public:
	int x, y, w, h;
	Box() {
		leftPad = 0;
		rightPad = 0;
		topPad = 0;
		bottomPad = 0;
	}
	void UpdatePosition(int x_, int y_, int w_, int h_) {
		x = x_; y = y_; w = w_; h = h_;
	}
	void AddText(int pos, int hp, std::string txt, color col) {
		//xorStr("off"), xorStr("left"), xorStr("right"), xorStr("top"), xorStr("bottom")
		if (txt == "") return;
		RECT area = paint->textSize(txt.c_str(), Glyphs::feature_esp);
		if (pos == 1) {
			paint->text(x - area.right - (hp == 1 ? 6 : 1), y + leftPad, txt.c_str(), Glyphs::feature_esp, Anchor::TopLeft, col);
			leftPad += area.bottom;
		}
		else if (pos == 2) {
			paint->text(x + w + (hp == 2 ? 7 : 3), y + rightPad, txt.c_str(), Glyphs::feature_esp, Anchor::TopLeft, col);
			rightPad += area.bottom;
		}
		else if (pos == 3) {
			paint->text(x + (w / 2) - (area.right / 2), y - topPad - area.bottom - (hp == 3 ? 4 : 1), txt.c_str(), Glyphs::feature_esp, Anchor::TopLeft, col);
			topPad += area.bottom + 1;
		}
		else if (pos == 4) {
			paint->text(x + (w / 2) - (area.right / 2), y + h + bottomPad + (hp == 4 ? 5 : 1), txt.c_str(), Glyphs::feature_esp, Anchor::TopLeft, col);
			bottomPad += area.bottom;
		}
	}
	void Draw(int boxtype, bool outline, color col, int top_buffer, int bottom_buffer, int left_buffer, int right_buffer)
	{
		if (boxtype == 1) {
			if (outline) {
				paint->outline(x - 1, y - 1, w + 2, h + 2, color(0, 0, 0, 255));
				paint->outline(x + 1, y + 1, w - 2, h - 2, color(0, 0, 0, 255));
			}
			paint->outline(x, y, w, h, col);
		}
		else if (boxtype == 2) {
			paint->corner(x, y, w, h, col, outline);
		}
		else if (boxtype == 3) {
			paint->octagonBox(x, y, w, h, col);
		}
		else if (boxtype == 4) {

			//flb, brt, blb, frt, frb, brb, blt, flt };
			//          blt     brt
			//      flt        frt



			//          blb   brb
			///     flb      frb

			paint->line(screenPoints[6].x, screenPoints[6].y, screenPoints[1].x, screenPoints[1].y, col);
			paint->line(screenPoints[6].x, screenPoints[6].y, screenPoints[7].x, screenPoints[7].y, col);
			paint->line(screenPoints[7].x, screenPoints[7].y, screenPoints[3].x, screenPoints[3].y, col);
			paint->line(screenPoints[3].x, screenPoints[3].y, screenPoints[1].x, screenPoints[1].y, col);


			paint->line(screenPoints[2].x, screenPoints[2].y, screenPoints[0].x, screenPoints[0].y, col);
			paint->line(screenPoints[0].x, screenPoints[0].y, screenPoints[4].x, screenPoints[4].y, col);
			paint->line(screenPoints[4].x, screenPoints[4].y, screenPoints[5].x, screenPoints[5].y, col);
			paint->line(screenPoints[5].x, screenPoints[5].y, screenPoints[2].x, screenPoints[2].y, col);


			paint->line(screenPoints[7].x, screenPoints[7].y, screenPoints[0].x, screenPoints[0].y, col);
			paint->line(screenPoints[3].x, screenPoints[3].y, screenPoints[4].x, screenPoints[4].y, col);
			paint->line(screenPoints[6].x, screenPoints[6].y, screenPoints[2].x, screenPoints[2].y, col);
			paint->line(screenPoints[1].x, screenPoints[1].y, screenPoints[5].x, screenPoints[5].y, col);

		}

	}
	void updatePoints(Vector p[8]) {
		for (int i = 0; i < 8; i++)
			screenPoints[i] = p[i];
	}
	
private:
	int leftPad = 0;
	int rightPad = 0;
	int topPad = 0;
	int bottomPad = 0;
	Vector screenPoints[8] = {};
	
};

class espFeature {
public:
	void loop();
	void bombDamage(cBasePlayer* local, CCSBomb* bomb);
	void players(cBasePlayer* player);
	void team(cCSPlayer* player, cBaseEntity* local);
	color healthCol(cBasePlayer* player);
	color armorCol(cCSPlayer* player);
	void lines(cBasePlayer* player, Box box);
	std::string healthValueESP(cBasePlayer* player);
	std::string armourValueESP(cCSPlayer* player);
	void testSizeESP(cBasePlayer* player);
	std::string reloadWarning(cBasePlayer* player);
	std::string scopedWarning(cCSPlayer* player);
	std::string defuseWarning(cCSPlayer* player);
	std::string hostageWarning(cCSPlayer* player);
	std::string helmetESP(cCSPlayer* player);
	void drawHitboxes(cCSPlayer* player, cBaseEntity* local);
	void enemies(cCSPlayer* player, cBaseEntity* local);
	bool findBounds(bool D3D, Box& box, cBaseEntity* entity, int hz, float divide);
	void drawToBox(std::string data, Box& box, Anchor alignment);
	void drawBacktrack(cBasePlayer* player);
	std::string distance(cCSPlayer* entity, cCSPlayer* local);
	std::string money(cCSPlayer* entity);
	void skeleton(cCSPlayer* entity, color c);
	void tracelines(cCSPlayer* entity, color c);
	void crosshair(cBasePlayer* local);
	color grenadeToColor(std::string model);
	void c4Infomation(CCSBomb* c4, int time, const char* time_text);
	std::string ammunition(cCSPlayer* entity);
	std::string weapon(cCSPlayer* entity);
	std::string name(int i);
	void radar(cCSPlayer* player);
	void healthBar(int hb, Box box, cBasePlayer* entity, color healthcolor);
	void playerColor(bool visible, cBasePlayer* entity, cBasePlayer* local, color& boxcolor, color& namecolor, color& weaponcolor, color& healthcolor, color& moneycolor, color& ammunitioncolor, color& distancecolor, color& barrelcolor, color& skeletoncolor, color& reloadWarningcolor, color& scopedWarningcolor, color& defuseWarningcolor, color& hostageWarningcolor, color& helmetESPcolor);
	
};