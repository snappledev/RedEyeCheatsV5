#pragma once
#include <Windows.h>
#include <vector>
#include "xor.h"
#include "color.h"
#include "Functions.h"
#include "inputManager.h"
#include "painting.h"
#include "variables.h"
#include "Que.h"
#include "skinchanger.h"
#include "icons.h"
#include "log.h"
#include "esp.h"
//#define USEMENUV1 1

#define boxMenuWidth 175
struct AREA {
	float x, y, w, h;
};
class edgeGroupBacking
{
public:
	edgeGroupBacking(int x_, int y_, int w_, int h_, std::string na) {
		x = x_; y = y_; w = w_; h = h_; name = na;
	}
	int x = 0, y = 0, w = 0, h = 0;
	std::string name = xorStr("");

};
class edgeControl {
public:
	virtual void paintControl(int x_, int y_) = 0;
	virtual void updateControl(int x_, int y_, bool& dropdownOpen) = 0;
	virtual void thinkControl() = 0;
	virtual bool saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page) = 0;
	virtual bool loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page) = 0;
	int x, y;
	std::string name;
	int* allowedVisible;
	int  allowedVisibleComparitor;
	int uniqueID;
	int id = 0;
	bool useOp = false;
};
class SearchItem
{
public:
	std::string name;
	int tab;
	int group;
	int yvalue = 0;
};
class edgeLabel : public edgeControl
{
public:
	edgeLabel(std::string n, int x_, int y_, int* a, int allowed) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = allowed; uniqueID = -1;
	}
	bool saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page) {

		return false;
	}
	bool loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page) {

		return true;
	}

	void paintControl(int x_, int y_) {
		if (*allowedVisible != allowedVisibleComparitor) return;
		paint->text(x_ + x, y_ + y, name.c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text);

	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {

	}
};
class edgeLabelValue : public edgeControl
{
public:
	edgeLabelValue(std::string n, int x_, int y_, int* value_, int* a, int allowed) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = allowed; uniqueID = -1;
		value = value_;
	}
	bool saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page) {

		return false;
	}
	bool loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page) {

		return true;
	}

	void paintControl(int x_, int y_) {
		if (*allowedVisible != allowedVisibleComparitor) return;
		std::string text = name + ": " + std::to_string(*value);
		paint->text(x_ + x, y_ + y, text.c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text);

	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {

	}
	int* value;
};
class edgePortableTextbox
{
public:
	edgePortableTextbox() {

	}

	const char* bindkeys[254] = { xorStr(""), xorStr("Left Click"), xorStr("Right Click"), xorStr("Cancel"), xorStr("Middle Click"), xorStr("X1 Click"), xorStr("X2 Click"),
xorStr(""), xorStr("Backspace"), xorStr("Tab"), xorStr(""), xorStr("Clear"), xorStr("Enter"),xorStr(""), xorStr("Shift"), xorStr("Control"), xorStr("Alt"), xorStr("Pause"), xorStr("Caps-Lock"),
xorStr("Hanguel"), xorStr("Caps-Lock"), xorStr(""), xorStr("Junja"), xorStr("Final"), xorStr("Hanja"), xorStr("Kanji"), xorStr(""), xorStr("Escape"), xorStr("Convert"), xorStr("Non-Convert"), xorStr("Accept"), xorStr("Mode-Change"),
xorStr("Spacebar"), xorStr("Page Up"), xorStr("Page Down"), xorStr("End"), xorStr("Home"),xorStr("Left Arrow"), xorStr("Up Arrow"), xorStr("Right Arrow"), xorStr("Down Arrow"), xorStr("Select"), xorStr("Print"), xorStr("Execute"), xorStr("Print Screen"), xorStr("Insert"),
xorStr("Delete"), xorStr("Help"), xorStr("0"), xorStr("1"), xorStr("2"), xorStr("3"), xorStr("4"), xorStr("5"), xorStr("6"), xorStr("7"), xorStr("8"), xorStr("9"), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""),
xorStr(""), xorStr("A"), xorStr("B"), xorStr("C"), xorStr("D"), xorStr("E"), xorStr("F"), xorStr("G"), xorStr("H"), xorStr("I"), xorStr("J"), xorStr("K"), xorStr("L"), xorStr("M"), xorStr("N"), xorStr("O"), xorStr("P"), xorStr("Q"), xorStr("R"), xorStr("S"), xorStr("T"), xorStr("U"), xorStr("V"), xorStr("W"), xorStr("X"),
xorStr("Y"), xorStr("Z"), xorStr("Left Windows"), xorStr("Right Windows"), xorStr("Page"), xorStr(""), xorStr("Sleep"), xorStr("Numpad 0"),xorStr("Numpad 0"),xorStr("Numpad 2"), xorStr("Numpad 3"), xorStr("Numpad 4"), xorStr("Numpad 5"), xorStr("Numpad 9"),
xorStr("Numpad 7"), xorStr("Numpad 8"), xorStr("Numpad 9"), xorStr("Multiply"), xorStr("Add"), xorStr("Seperator"), xorStr("Subtract"), xorStr("Decimal"),xorStr("Divide"), xorStr("F1"), xorStr("F2"), xorStr("F3"), xorStr("F4"), xorStr("F5"), xorStr("F6"), xorStr("F7"), xorStr("F8"), xorStr("F9"), xorStr("F10"), xorStr("F11"), xorStr("F12"),
xorStr("F13"), xorStr("F14"), xorStr("F15"), xorStr("F16"), xorStr("F17"), xorStr("F18"), xorStr("F19"), xorStr("F20"), xorStr("F21"), xorStr("F22"), xorStr("F23"), xorStr("F24"), xorStr(""), xorStr("Number Lock"), xorStr("Scroll Lock"), xorStr(""), xorStr(""),
xorStr("Shift"), xorStr("Shift"), xorStr("Control"), xorStr("Number Lock"), xorStr("Scroll Lock"), xorStr("Right Media"), xorStr("Browser"), xorStr("Brower"), xorStr("Browser"), xorStr("Browser"), xorStr("Browser"), xorStr("Browser"), xorStr("Browser"), xorStr("Mute"),
xorStr("Volume Down"), xorStr("Volume Up"), xorStr("Next Track"), xorStr("Previous Track"), xorStr("Stop Media"), xorStr("Shift"), xorStr("Mail"), xorStr("Control"), xorStr("Control"), xorStr("Alt"), xorStr(""), xorStr(""), xorStr("+"), xorStr(","),
xorStr("-"), xorStr("."), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""),
xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""),
xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""),
xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""),
xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""),
xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr("") };
	struct highlite
	{
		int characternumber;
		float x, y, w, h;
	};
	void paintControl(std::string* output, int x_, int y_, int w_ = 175) {

		AREA ActivationArea = { x_,y_, w_, h };
		color outlinecolor = Functions::coloradd(variables::gui::colors::background, 20);
		if (AcceptingInput) {
			outlinecolor = Functions::coloradd(variables::gui::colors::background, 40);
		}
		else {
			if (inputmanager.inArea(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h))
				outlinecolor = Functions::coloradd(variables::gui::colors::background, -20);
		}

		paint->rectangle(ActivationArea.x + (ActivationArea.h / 2), ActivationArea.y, ActivationArea.w - ActivationArea.h, ActivationArea.h, outlinecolor);
		paint->circle(ActivationArea.x + (ActivationArea.h / 2), ActivationArea.y + (ActivationArea.h / 2), ActivationArea.h / 2, outlinecolor);
		paint->circle(ActivationArea.x + ActivationArea.w - (ActivationArea.h / 2), ActivationArea.y + (ActivationArea.h / 2), ActivationArea.h / 2, outlinecolor);
		if (AcceptingInput) {
			RECT textarea = paint->textSize(temptext.c_str(), Glyphs::menu_control);
			paint->text(ActivationArea.x + 15, ActivationArea.y + (ActivationArea.h / 2) - (textarea.bottom / 2), temptext.c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::primary);
			paint->line(ActivationArea.x + 19 + textarea.right, ActivationArea.y + (ActivationArea.h / 2) - (textarea.bottom / 2), ActivationArea.x + 19 + textarea.right, ActivationArea.y + (ActivationArea.h / 2) - (textarea.bottom / 2) + textarea.bottom, variables::gui::colors::primary);

		}
		else {
			std::string out = *output;
			RECT textarea = paint->textSize(out.c_str(), Glyphs::menu_control);
			paint->text(ActivationArea.x + 15, ActivationArea.y + (ActivationArea.h / 2) - (textarea.bottom / 2), out.length() <= 0 ? "Enter search" : out.c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text);
		}
		if (!DeleteCharacters.empty() && m_iHighlightW != 0) {
			for (int i = 0; i < DeleteCharacters.size(); i++) {
				paint->rectangle(DeleteCharacters[i].x, DeleteCharacters[i].y, DeleteCharacters[i].w, DeleteCharacters[i].h, color(variables::gui::colors::primary.r(), variables::gui::colors::primary.g(), variables::gui::colors::primary.b(), 75));
			}
		}
	}
	void thinkControl() {

	}
	void updateControl(std::string* output, int x_, int y_, int w_ = 175) {

		AREA ActivationArea = { x_,y_, w_, h };
		if (inputmanager.inArea(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h) && inputmanager.click(VK_LBUTTON))
			AcceptingInput = true;

		if (inputmanager.click(VK_ESCAPE)) {
			AcceptingInput = false;
			temptext = *output;
		}

		if (AcceptingInput) {
			for (int i = 0; i <= 254; i++) {
				const char* heldkey = inputmanager.KeyToName(i, inputmanager.hold(VK_SHIFT));
				if (i != VK_SPACE && heldkey == nullptr) continue;
				if (inputmanager.click(i)) {
					RECT textarea = paint->textSize(temptext.c_str(), Glyphs::menu_control);
					if (textarea.right + 20 < ActivationArea.w) {
						if (i == VK_SPACE)
							temptext.append(" ");
						else
							temptext.append(heldkey);
					}
				}
			}
			if (inputmanager.click(VK_BACK) && !temptext.empty())
				temptext.erase(temptext.size() - 1);
		}
		if (!inputmanager.inArea(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h) && inputmanager.click(VK_LBUTTON)) {

			*output = temptext;

			AcceptingInput = false;
		}
		if (inputmanager.click(VK_RETURN) && DeleteCharacters.empty()) {
			*output = temptext;

			AcceptingInput = false;
		}
		if (inputmanager.click(VK_LBUTTON) && inputmanager.inArea(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h)) {
			m_bHighlighting = true;
		}
		if (m_bHighlighting)
		{
			if (!inputmanager.hold(VK_LBUTTON))
				m_bHighlighting = false;
			else {

				m_iStartHighlightX = m_iStartHighlightXT;
				m_iHighlightW = m_iStartHighlightXT - inputmanager.cursor.x;
			}
		}
		else {
			m_iStartHighlightXT = inputmanager.cursor.x;
		}
		DeleteCharacters.clear();
		if (m_iHighlightW != 0) {
			AREA HighlightArea = { m_iStartHighlightX, ActivationArea.y, -m_iHighlightW, ActivationArea.h };
			if (m_iHighlightW > 0) {
				HighlightArea = { (float)m_iStartHighlightX - (float)m_iHighlightW, ActivationArea.y, (float)m_iHighlightW, ActivationArea.h };
			}
			int xoff = 0;
			std::string outstr = *output;
			const char* arrayofstr = outstr.c_str();
			for (int i = 0; i < outstr.length(); i++)
			{
				std::string str(1, arrayofstr[i]);
				RECT area = paint->textSize(str.c_str(), Glyphs::menu_control);
				if ((ActivationArea.x + 15 + xoff > HighlightArea.x) && (ActivationArea.x + 15 + xoff < HighlightArea.x + HighlightArea.w))
					DeleteCharacters.push_back({ i, ActivationArea.x + 15 + xoff, ActivationArea.y, (float)area.right, ActivationArea.h });
				xoff += area.right;
			}
		}
		if (inputmanager.click(VK_BACK) && !DeleteCharacters.empty() && m_iHighlightW != 0) {
			std::string tmp = *output;
			tmp.erase(DeleteCharacters[0].characternumber, DeleteCharacters.size());
			*output = tmp;
			temptext = tmp;
			m_iHighlightW = 0;
			DeleteCharacters.empty();
		}
	}
	int m_iStartHighlightXT = 0, m_iStartHighlightX;
	bool m_bHighlighting;
	int m_iHighlightW = 0;
	bool AcceptingInput = false;
	int w = 175 * Game::menu_scale_factor, h = 30 * Game::menu_scale_factor;
	std::vector<highlite> DeleteCharacters;
	std::string temptext;
};

class edgeTextbox : public edgeControl
{
public:
	edgeTextbox(std::string n, int x_, int y_, std::string* v, int* a, int allowed, int controlIncrementer) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = allowed; output = v; temptext = *v; uniqueID = controlIncrementer;

	}
	bool saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page) {
		std::string m_cValue = *output;
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		if (WritePrivateProfileString(ConfigName.c_str(), m_nName.c_str(), m_cValue.c_str(), filepath))
			return true;
		return false;
	}
	bool loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page) {
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		CHAR m_cReturn[128];
		if (!GetPrivateProfileString(ConfigName.c_str(), m_nName.c_str(), "", m_cReturn, 128, filepath))
			return false;
		temptext = m_cReturn;
		*output = m_cReturn;
		return true;
	}
	struct highlite
	{
		int characternumber;
		float x, y, w, h;
	};
	void paintControl(int x_, int y_) {
		AREA ActivationArea = { x_ + x,y_ + y, w, h };
		paint->rectangle(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h, Functions::coloradd(variables::gui::colors::background, 30));
		if (AcceptingInput) {
			RECT textarea = paint->textSize(temptext.c_str(), Glyphs::menu_control);
			paint->text(ActivationArea.x + 15, ActivationArea.y + (ActivationArea.h / 2) - (textarea.bottom / 2), temptext.c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text);
			paint->line(ActivationArea.x + 19 + textarea.right, ActivationArea.y + (ActivationArea.h / 2) - (textarea.bottom / 2), ActivationArea.x + 19 + textarea.right, ActivationArea.y + (ActivationArea.h / 2) - (textarea.bottom / 2) + textarea.bottom, variables::gui::colors::primary);

		}
		else {
			std::string out = *output;
			RECT textarea = paint->textSize(out.c_str(), Glyphs::menu_control);
			paint->text(ActivationArea.x + 15, ActivationArea.y + (ActivationArea.h / 2) - (textarea.bottom / 2), out.c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text);
		}
		if (!DeleteCharacters.empty() && m_iHighlightW != 0) {
			for (int i = 0; i < DeleteCharacters.size(); i++) {
				paint->rectangle(DeleteCharacters[i].x, DeleteCharacters[i].y, DeleteCharacters[i].w, DeleteCharacters[i].h, color(variables::gui::colors::primary.r(), variables::gui::colors::primary.g(), variables::gui::colors::primary.b(), 75));
			}
		}
	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		AREA ActivationArea = { x_ + x,y_ + y, w, h };
		if (inputmanager.inArea(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h) && inputmanager.click(VK_LBUTTON))
			AcceptingInput = true;

		if (inputmanager.click(VK_ESCAPE)) {
			AcceptingInput = false;
			temptext = *output;
		}
		if (AcceptingInput) {
			bool keyWasPressed = false;
			for (int i = 0; i <= 254; i++) {
				//if (i == previousInt) continue;
				const char* heldkey = inputmanager.KeyToName(i, inputmanager.hold(VK_SHIFT));
				if (i != VK_SPACE && heldkey == nullptr) continue;
				if (!inputmanager.click(i)) continue;


				RECT textarea = paint->textSize(temptext.c_str(), Glyphs::menu_control);
				if (textarea.right + 20 < ActivationArea.w) {
					if (i == VK_SPACE) {
						temptext.append(" ");

					}
					else {
						temptext.append(heldkey);
					}
					previousInt = i;
					keyWasPressed = true;
				}


			}
			/*
			if (!keyWasPressed) {
				previousInt = -1;
			}*/


			if (inputmanager.click(VK_BACK) && !temptext.empty())
				temptext.erase(temptext.size() - 1);
		}
		if (!inputmanager.inArea(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h) && inputmanager.click(VK_LBUTTON)) {
			*output = temptext;
			AcceptingInput = false;
		}
		if (inputmanager.click(VK_RETURN) && DeleteCharacters.empty()) {
			*output = temptext;
			AcceptingInput = false;
		}
		if (inputmanager.click(VK_LBUTTON) && inputmanager.inArea(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h)) {
			m_bHighlighting = true;
		}
		if (m_bHighlighting)
		{
			if (!inputmanager.hold(VK_LBUTTON))
				m_bHighlighting = false;
			else {

				m_iStartHighlightX = m_iStartHighlightXT;
				m_iHighlightW = m_iStartHighlightXT - inputmanager.cursor.x;
			}
		}
		else {
			m_iStartHighlightXT = inputmanager.cursor.x;
		}
		DeleteCharacters.clear();
		if (m_iHighlightW != 0) {
			AREA HighlightArea = { m_iStartHighlightX, ActivationArea.y, -m_iHighlightW, ActivationArea.h };
			if (m_iHighlightW > 0) {
				HighlightArea = { (float)m_iStartHighlightX - (float)m_iHighlightW, ActivationArea.y, (float)m_iHighlightW, ActivationArea.h };
			}
			int xoff = 0;
			std::string outstr = *output;
			const char* arrayofstr = outstr.c_str();
			for (int i = 0; i < outstr.length(); i++)
			{
				std::string str(1, arrayofstr[i]);
				RECT area = paint->textSize(str.c_str(), Glyphs::menu_control);
				if ((ActivationArea.x + 15 + xoff > HighlightArea.x) && (ActivationArea.x + 15 + xoff < HighlightArea.x + HighlightArea.w))
					DeleteCharacters.push_back({ i, ActivationArea.x + 15 + xoff, ActivationArea.y, (float)area.right, ActivationArea.h });
				xoff += area.right;
			}
		}
		if (inputmanager.click(VK_BACK) && !DeleteCharacters.empty() && m_iHighlightW != 0) {
			std::string tmp = *output;
			tmp.erase(DeleteCharacters[0].characternumber, DeleteCharacters.size());
			*output = tmp;
			temptext = tmp;
			m_iHighlightW = 0;
			DeleteCharacters.empty();
		}
	}
	int m_iStartHighlightXT = 0, m_iStartHighlightX;
	bool m_bHighlighting = false;
	int m_iHighlightW = 0;
	bool AcceptingInput = false;
	int w = boxMenuWidth * Game::menu_scale_factor, h = 30 * Game::menu_scale_factor;
	int previousInt = -1;
	std::vector<highlite> DeleteCharacters;
	std::string temptext;
	std::string* output;
};

class edgeNumberTextbox : public edgeControl
{
public:
	edgeNumberTextbox(std::string n, int x_, int y_, int* v, int* a, int allowed, int controlIncrementer) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = allowed; output = v; temptext = std::to_string(*v); uniqueID = controlIncrementer;

	}
	bool saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page) {
		std::string m_cValue = std::to_string(*output);
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		if (WritePrivateProfileString(ConfigName.c_str(), m_nName.c_str(), m_cValue.c_str(), filepath))
			return true;
		return false;
	}
	bool loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page) {
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		CHAR m_cReturn[128];
		if (!GetPrivateProfileString(ConfigName.c_str(), m_nName.c_str(), "", m_cReturn, 128, filepath))
			return false;
		temptext = m_cReturn;
		std::string conversionBuffer = m_cReturn;
		*output = Functions::safeStoi(conversionBuffer);
		return true;
	}
	struct highlite
	{
		int characternumber;
		float x, y, w, h;
	};
	void paintControl(int x_, int y_) {
		AREA ActivationArea = { x_ + x,y_ + y, w, h };
		paint->rectangle(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h, Functions::coloradd(variables::gui::colors::background, 30));
		if (AcceptingInput) {
			RECT textarea = paint->textSize(temptext.c_str(), Glyphs::menu_control);
			paint->text(ActivationArea.x + 15, ActivationArea.y + (ActivationArea.h / 2) - (textarea.bottom / 2), temptext.c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text);
			paint->line(ActivationArea.x + 19 + textarea.right, ActivationArea.y + (ActivationArea.h / 2) - (textarea.bottom / 2), ActivationArea.x + 19 + textarea.right, ActivationArea.y + (ActivationArea.h / 2) - (textarea.bottom / 2) + textarea.bottom, variables::gui::colors::primary);

		}
		else {
			std::string out = std::to_string(*output);
			RECT textarea = paint->textSize(out.c_str(), Glyphs::menu_control);
			paint->text(ActivationArea.x + 15, ActivationArea.y + (ActivationArea.h / 2) - (textarea.bottom / 2), out.c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text);
		}
		if (!DeleteCharacters.empty() && m_iHighlightW != 0) {
			for (int i = 0; i < DeleteCharacters.size(); i++) {
				paint->rectangle(DeleteCharacters[i].x, DeleteCharacters[i].y, DeleteCharacters[i].w, DeleteCharacters[i].h, color(variables::gui::colors::primary.r(), variables::gui::colors::primary.g(), variables::gui::colors::primary.b(), 75));
			}
		}
	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		AREA ActivationArea = { x_ + x,y_ + y, w, h };
		if (inputmanager.inArea(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h) && inputmanager.click(VK_LBUTTON))
			AcceptingInput = true;
		if (temptext == "ÿ") return;
		if (inputmanager.click(VK_ESCAPE)) {
			AcceptingInput = false;
			temptext = *output;
		}
		if (AcceptingInput) {
			bool keyWasPressed = false;
			for (int i = 0; i <= 254; i++) {
				//if (i == previousInt) continue;
				if (!inputmanager.click(i)) continue;
				const char* heldkey = inputmanager.KeyToNumber(i);
				if ((!(i == 0xBD && temptext.size() == 0)) && heldkey == nullptr) continue;
				RECT textarea = paint->textSize(temptext.c_str(), Glyphs::menu_control);
				if (textarea.right + 20 < ActivationArea.w) {
					temptext.append(i == 0xBD ? "-" : heldkey);
					previousInt = i;
					keyWasPressed = true;
				}


			}
			/*
			if (!keyWasPressed) {
				previousInt = -1;
			}*/


			if (inputmanager.click(VK_BACK) && !temptext.empty())
				temptext.erase(temptext.size() - 1);
		}
		if (!inputmanager.inArea(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h) && inputmanager.click(VK_LBUTTON)) {
			if (temptext == "")
				*output = -1;
			else {
				*output = Functions::safeStoi(temptext);
			}
			

			AcceptingInput = false;
		}
		if (inputmanager.click(VK_RETURN) && DeleteCharacters.empty()) {
			if (temptext == "")
				*output = -1;
			else
				*output = Functions::safeStoi(temptext);
			AcceptingInput = false;
		}
		if (inputmanager.click(VK_LBUTTON) && inputmanager.inArea(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h)) {
			m_bHighlighting = true;
		}
		if (m_bHighlighting)
		{
			if (!inputmanager.hold(VK_LBUTTON))
				m_bHighlighting = false;
			else {

				m_iStartHighlightX = m_iStartHighlightXT;
				m_iHighlightW = m_iStartHighlightXT - inputmanager.cursor.x;
			}
		}
		else {
			m_iStartHighlightXT = inputmanager.cursor.x;
		}
		DeleteCharacters.clear();
		if (m_iHighlightW != 0) {
			AREA HighlightArea = { m_iStartHighlightX, ActivationArea.y, -m_iHighlightW, ActivationArea.h };
			if (m_iHighlightW > 0) {
				HighlightArea = { (float)m_iStartHighlightX - (float)m_iHighlightW, ActivationArea.y, (float)m_iHighlightW, ActivationArea.h };
			}
			int xoff = 0;
			std::string outstr = std::to_string(*output);
			const char* arrayofstr = outstr.c_str();
			for (int i = 0; i < outstr.length(); i++)
			{
				std::string str(1, arrayofstr[i]);
				RECT area = paint->textSize(str.c_str(), Glyphs::menu_control);
				if ((ActivationArea.x + 15 + xoff > HighlightArea.x) && (ActivationArea.x + 15 + xoff < HighlightArea.x + HighlightArea.w))
					DeleteCharacters.push_back({ i, ActivationArea.x + 15 + xoff, ActivationArea.y, (float)area.right, ActivationArea.h });
				xoff += area.right;
			}
		}
		if (inputmanager.click(VK_BACK) && !DeleteCharacters.empty() && m_iHighlightW != 0) {
			std::string tmp = std::to_string(*output);
			tmp.erase(DeleteCharacters[0].characternumber, DeleteCharacters.size());
			if (tmp == "")
				* output = -1;
			else
				*output = stoi(temptext);
			temptext = tmp;
			m_iHighlightW = 0;
			DeleteCharacters.empty();
		}
	}
	int m_iStartHighlightXT = 0, m_iStartHighlightX;
	bool m_bHighlighting = false;
	int m_iHighlightW = 0;
	bool AcceptingInput = false;
	int w = boxMenuWidth * Game::menu_scale_factor, h = 30 * Game::menu_scale_factor;
	int previousInt = -1;
	std::vector<highlite> DeleteCharacters;
	std::string temptext = "";
	int* output;
};

class edgeTabSelector : public edgeControl
{
public:
	edgeTabSelector(int x_, int y_, int* w_, int* h_, std::vector<std::string> items, int* v, int* a, int allowed) {
		name = ""; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = allowed; value = v; uniqueID = -1;
		w = w_; h = h_; stringList = items; alphaList.resize(items.size());

	}
	bool saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page) {

		return false;
	}
	bool loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page) {
		return true;
	}

	void paintControl(int x_, int y_) {
		RECT ActivationArea = { x_ + x,y_ + y, *w, (*h) * 0.75 };
		float subTabWidth = (float)ActivationArea.right / (float)stringList.size();
		for (int i = 0; i < stringList.size(); i++) {
			RECT area = { ActivationArea.left + (i * subTabWidth),  ActivationArea.top, subTabWidth,  ActivationArea.bottom };
			color edgeColor = Functions::coloradd(variables::gui::colors::background, variables::gui::colors::lighterBackgroundHuePlus);
			color greyAlph = color(160, 160, 160, variables::gui::colors::primary.a());
			if (*value == i) {
				edgeColor = variables::gui::colors::primary;
			}
			if (inputmanager.inArea(area.left, area.top, area.right, area.bottom)) {
				alphaList[i] = Functions::clip(alphaList[i] + 10, 0, 255);
			}
			else {
				alphaList[i] = Functions::clip(alphaList[i] - 10, 0, 255);
			}
			paint->rectangle(area.left, area.top, area.right, area.bottom, edgeColor);
			paint->rectangle(area.left, area.top, area.right, area.bottom,Functions::replaceAlpha(variables::gui::colors::primary, alphaList[i]) );
			paint->text(area.left + (area.right / 2), area.top + (area.bottom / 2), stringList[i].c_str(), Glyphs::menu_subtab, Anchor::Center, variables::gui::colors::text);

		}
	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		RECT ActivationArea = { x_ + x,y_ + y, *w, (*h) * 0.75 };

		int subTabWidth = ActivationArea.right / stringList.size();
		for (int i = 0; i < stringList.size(); i++) {
			if (*value != i) {
				RECT area = { ActivationArea.left + (i * subTabWidth), ActivationArea.top, subTabWidth, ActivationArea.bottom };
				if (inputmanager.inArea(area.left, area.top, area.right, area.bottom) && inputmanager.click(VK_LBUTTON)) {
					*value = i;
				}
			}
		}


	}
	int* w, * h;
	std::vector<std::string> stringList;
	std::vector<int> alphaList;
	int* value;
};
class edgeColorPicker : public edgeControl
{
public:
	edgeColorPicker(std::string n, int x_, int y_, color* v, int* a, int allowed, int controlIncrementer) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = allowed; color_ = v; uniqueID = controlIncrementer;
		int H = 0, S = 0, V = 0; Functions::RGB2HSV(v->r(), v->g(), v->b(), H, S, V);
		m_iPickX = (H / 255.f) * w;
		m_iPickY = (1.f - (S / 255.f)) * h;
		m_iPickV = (1.f - (V / 255.f)) * h;
	}
	bool saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page) {
		std::string m_cValue = std::to_string(color_->r()) + "," + std::to_string(color_->g()) + "," + std::to_string(color_->b()) + "," + std::to_string(color_->a());
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		if (WritePrivateProfileString(ConfigName.c_str(), m_nName.c_str(), m_cValue.c_str(), filepath))
			return true;
		return false;
	}
	bool loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page) {
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		CHAR m_cReturn[128];
		if (!GetPrivateProfileString(ConfigName.c_str(), m_nName.c_str(), "", m_cReturn, 128, filepath))
			return false;
		int previousIndex = 0;
		std::string data(m_cReturn);
		std::vector<std::string> strings = {};
		for (int i = 0; i < data.length(); i++) {
			if (data[i] == ',' || i == (data.length() - 1)) {
				strings.push_back(data.substr(previousIndex, i - previousIndex + (i == (data.length() - 1) ? 1 : 0)));
				previousIndex = i + 1;
			}
		}
		color_->Setcolor(Functions::safeStoi(strings[0]), Functions::safeStoi(strings[1]), Functions::safeStoi(strings[2]), Functions::safeStoi(strings[3]));
		int H = 0, S = 0, V = 0; Functions::RGB2HSV(color_->r(), color_->g(), color_->b(), H, S, V);
		m_iPickX = (H / 255.f) * w;
		m_iPickY = (1.f - (S / 255.f)) * h;
		m_iPickV = (1.f - (V / 255.f)) * h;
		return true;
	}

	void paintControl(int x_, int y_) {
		AREA m_ActivationArea = { x_ + x,y_ + y, w, h };
		paint->image(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h, images::colorpicker);
		paint->outline(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h, variables::gui::colors::primary);
		paint->circle(m_ActivationArea.x + m_iPickX - 2, m_ActivationArea.y + m_iPickY - 2, 5, *color_);
		paint->circleOutline(m_ActivationArea.x + m_iPickX - 2, m_ActivationArea.y + m_iPickY - 2, 5, color(0, 0, 0, 255));
		int m_iWidth = (0.04519774011 * m_ActivationArea.w);


		int H = ((float)m_iPickX / (float)m_ActivationArea.w) * 255.f;
		int S = (1.f - ((float)m_iPickY / (float)m_ActivationArea.h)) * 255.f;
		int r = 0, g = 0, b = 0;
		Functions::HSV2RGB(r, g, b, H, S, 255);

		paint->rectangle(m_ActivationArea.x + m_ActivationArea.w + m_iWidth, m_ActivationArea.y, m_iWidth, m_ActivationArea.h, color(r, g, b, 255));
		paint->image(m_ActivationArea.x + m_ActivationArea.w + m_iWidth, m_ActivationArea.y, m_iWidth, m_ActivationArea.h, images::colorgradient);
		paint->scalineTriangle(m_ActivationArea.x + m_ActivationArea.w + (m_iWidth * 2), m_ActivationArea.y + m_iPickV, m_ActivationArea.x + m_ActivationArea.w + (m_iWidth * 2) + (m_iWidth / 2), m_ActivationArea.y + m_iPickV - (m_iWidth / 2), m_ActivationArea.x + m_ActivationArea.w + (m_iWidth * 2) + (m_iWidth / 2), m_ActivationArea.y + m_iPickV + (m_iWidth / 2), variables::gui::colors::primary);
		paint->outline(m_ActivationArea.x + m_ActivationArea.w + m_iWidth, m_ActivationArea.y, m_iWidth, m_ActivationArea.h, variables::gui::colors::primary);
		paint->rectangle(m_ActivationArea.x + m_ActivationArea.w + (m_iWidth * 3), m_ActivationArea.y, m_iWidth, m_ActivationArea.h, *color_);
		paint->outline(m_ActivationArea.x + m_ActivationArea.w + (m_iWidth * 3), m_ActivationArea.y, m_iWidth, m_ActivationArea.h, variables::gui::colors::primary);

	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		AREA m_ActivationArea = { x_ + x,y_ + y , w, h };
		if (inputmanager.inArea(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h) && inputmanager.click(VK_LBUTTON)) {
			m_bHoldingColor = true;
		}
		if (m_bHoldingColor) {
			if (!inputmanager.hold(VK_LBUTTON))
				m_bHoldingColor = false;
			else {
				m_iPickX = inputmanager.cursor.x - m_ActivationArea.x;
				m_iPickY = inputmanager.cursor.y - m_ActivationArea.y;
			}
		}

		if (inputmanager.inArea(m_ActivationArea.x + m_ActivationArea.w + (0.04519774011 * m_ActivationArea.w), m_ActivationArea.y, (0.04519774011 * m_ActivationArea.w), m_ActivationArea.h) && inputmanager.click(VK_LBUTTON)) {
			m_bHoldingV = true;
		}
		if (m_bHoldingV) {
			if (!inputmanager.hold(VK_LBUTTON))
				m_bHoldingV = false;
			else {
				m_iPickV = inputmanager.cursor.y - m_ActivationArea.y;
			}
		}
		m_iPickX = Functions::clip(m_iPickX, 1, (int)m_ActivationArea.w);
		m_iPickY = Functions::clip(m_iPickY, 1, (int)m_ActivationArea.h);
		m_iPickV = Functions::clip(m_iPickV, 1, (int)m_ActivationArea.h);
		int H = ((float)m_iPickX / (float)m_ActivationArea.w) * 255.f;
		int S = (1.f - ((float)m_iPickY / (float)m_ActivationArea.h)) * 255.f;
		int V = (1.f - ((float)m_iPickV / (float)m_ActivationArea.h)) * 255.f;
		int r = 0, g = 0, b = 0;
		Functions::HSV2RGB(r, g, b, H, S, V);

		r = Functions::clip(r, 1, 254);
		g = Functions::clip(g, 1, 254);
		b = Functions::clip(b, 1, 254);
		*color_ = color(r, g, b, 255);

	}
	int w = (boxMenuWidth * 1.5) * Game::menu_scale_factor, h = (boxMenuWidth * 1.5) * Game::menu_scale_factor;
	int m_iPickX = 0, m_iPickY = 0, m_iPickV = 0;
	bool m_bHoldingColor = false, m_bHoldingV = false;
	color* color_;
};

class edgeKeybinder : public edgeControl
{
public:
	edgeKeybinder(std::string n, int x_, int y_, int* v, int* a, int allowed, int controlIncrementer, bool b) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = allowed;  value = v; uniqueID = controlIncrementer;
		if (*value == -1)
			m_sKeybindText = xorStr("Always Activated");
		else
			m_sKeybindText = bindkeys[*value];
		bChangeMessage = b;
		if (bChangeMessage)
			w *= 0.45;
	}
	bool  loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		int m_cReturn = GetPrivateProfileInt(ConfigName.c_str(), m_nName.c_str(), 0, filepath);
		*value = m_cReturn;
		return true;
	}
	bool  saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		int m_cValue = *value;
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		if (WritePrivateProfileString(ConfigName.c_str(), m_nName.c_str(), std::to_string(m_cValue).c_str(), filepath))
			return true;
		return false;
	}
	const char* bindkeys[254] = { xorStr(""), xorStr("Left Click"), xorStr("Right Click"), xorStr("Cancel"), xorStr("Middle Click"), xorStr("X1 Click"), xorStr("X2 Click"),
xorStr(""), xorStr("Backspace"), xorStr("Tab"), xorStr(""), xorStr("Clear"), xorStr("Enter"),xorStr(""), xorStr("Shift"), xorStr("Control"), xorStr("Alt"), xorStr("Pause"), xorStr("Caps-Lock"),
xorStr("Hanguel"), xorStr("Caps-Lock"), xorStr(""), xorStr("Junja"), xorStr("Final"), xorStr("Hanja"), xorStr("Kanji"), xorStr(""), xorStr("Escape"), xorStr("Convert"), xorStr("Non-Convert"), xorStr("Accept"), xorStr("Mode-Change"),
xorStr("Spacebar"), xorStr("Page Up"), xorStr("Page Down"), xorStr("End"), xorStr("Home"),xorStr("Left Arrow"), xorStr("Up Arrow"), xorStr("Right Arrow"), xorStr("Down Arrow"), xorStr("Select"), xorStr("Print"), xorStr("Execute"), xorStr("Print Screen"), xorStr("Insert"),
xorStr("Delete"), xorStr("Help"), xorStr("0"), xorStr("1"), xorStr("2"), xorStr("3"), xorStr("4"), xorStr("5"), xorStr("6"), xorStr("7"), xorStr("8"), xorStr("9"), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""),
xorStr(""), xorStr("A"), xorStr("B"), xorStr("C"), xorStr("D"), xorStr("E"), xorStr("F"), xorStr("G"), xorStr("H"), xorStr("I"), xorStr("J"), xorStr("K"), xorStr("L"), xorStr("M"), xorStr("N"), xorStr("O"), xorStr("P"), xorStr("Q"), xorStr("R"), xorStr("S"), xorStr("T"), xorStr("U"), xorStr("V"), xorStr("W"), xorStr("X"),
xorStr("Y"), xorStr("Z"), xorStr("Left Windows"), xorStr("Right Windows"), xorStr("Page"), xorStr(""), xorStr("Sleep"), xorStr("Numpad 0"),xorStr("Numpad 0"),xorStr("Numpad 2"), xorStr("Numpad 3"), xorStr("Numpad 4"), xorStr("Numpad 5"), xorStr("Numpad 9"),
xorStr("Numpad 7"), xorStr("Numpad 8"), xorStr("Numpad 9"), xorStr("Multiply"), xorStr("Add"), xorStr("Seperator"), xorStr("Subtract"), xorStr("Decimal"),xorStr("Divide"), xorStr("F1"), xorStr("F2"), xorStr("F3"), xorStr("F4"), xorStr("F5"), xorStr("F6"), xorStr("F7"), xorStr("F8"), xorStr("F9"), xorStr("F10"), xorStr("F11"), xorStr("F12"),
xorStr("F13"), xorStr("F14"), xorStr("F15"), xorStr("F16"), xorStr("F17"), xorStr("F18"), xorStr("F19"), xorStr("F20"), xorStr("F21"), xorStr("F22"), xorStr("F23"), xorStr("F24"), xorStr(""), xorStr("Number Lock"), xorStr("Scroll Lock"), xorStr(""), xorStr(""),
xorStr("Shift"), xorStr("Shift"), xorStr("Control"), xorStr("Number Lock"), xorStr("Scroll Lock"), xorStr("Right Media"), xorStr("Browser"), xorStr("Brower"), xorStr("Browser"), xorStr("Browser"), xorStr("Browser"), xorStr("Browser"), xorStr("Browser"), xorStr("Mute"),
xorStr("Volume Down"), xorStr("Volume Up"), xorStr("Next Track"), xorStr("Previous Track"), xorStr("Stop Media"), xorStr("Shift"), xorStr("Mail"), xorStr("Control"), xorStr("Control"), xorStr("Alt"), xorStr(""), xorStr(""), xorStr("+"), xorStr(","),
xorStr("-"), xorStr("."), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""),
xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""),
xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""),
xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""),
xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""),
xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr(""), xorStr("") };

	void paintControl(int x_, int y_) {
		AREA ActivationArea = { x_ + x,y_ + y , w, h };
		color outlinecolor = Functions::coloradd(variables::gui::colors::background, 30);
		if (AcceptingKeys) {
			outlinecolor = Functions::coloradd(variables::gui::colors::primary, 5);
		}
		else {
			if (inputmanager.inArea(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h))
				outlinecolor = Functions::coloradd(variables::gui::colors::background, 40);
		}
		paint->rectangle(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h, outlinecolor);

		if (!AcceptingKeys) {
			if (*value == -1)
				m_sKeybindText = xorStr(bChangeMessage ? "Disabled" : "Always Activated");
			else
				m_sKeybindText = bindkeys[*value];
		}
		else
			m_sKeybindText = xorStr("Press to bind");

		RECT textarea = paint->textSize(m_sKeybindText.c_str(), Glyphs::menu_control);
		paint->text(ActivationArea.x + 15, ActivationArea.y + (ActivationArea.h / 2) - (textarea.bottom / 2), m_sKeybindText.c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text);
	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		AREA ActivationArea = { x_ + x,y_ + y, w, h };
		if (inputmanager.inArea(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h) && inputmanager.click(VK_LBUTTON)) {

			if (AcceptingKeys)
				AcceptingKeys = false;
			else
				AcceptingKeys = true;
			return;
		}

		if (AcceptingKeys && inputmanager.click(VK_ESCAPE)) {
			*value = -1; AcceptingKeys = false;
		}
		if (AcceptingKeys) {
			for (int i = 0; i <= 254; i++) {
				const char* heldkey = bindkeys[i];
				if (heldkey == xorStr("") || i == VK_ESCAPE) continue;
				if (inputmanager.click(i)) {
					*value = i;
					AcceptingKeys = false;
				}
			}
		}
	}
	bool AcceptingKeys = false;
	int w = boxMenuWidth * Game::menu_scale_factor, h = 30 * Game::menu_scale_factor;
	std::string m_sKeybindText = xorStr("Press to bind");
	int* value;
	bool bChangeMessage = false;
};
class edgeButton : public edgeControl
{
public:
	typedef void(*fn)(void);
	edgeButton(std::string n, int x_, int y_, int we, fn& v_, int* a, int allowed, int controlIncrementer) {
		name = n; buttontext = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = allowed; function = v_; id = 1;
		if (we == -1) {
			w = we;
		}
		else {
			w = we * Game::menu_scale_factor;
		}


		uniqueID = -1;
	}
	bool  loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		return true;
	}
	bool  saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		return false;
	}
	void paintControl(int x_, int y_) {
		RECT txtArea = paint->textSize(buttontext.c_str(), Glyphs::menu_control);
		AREA ActivationArea = { x + x_, y + y_, w == -1 ? ((txtArea.right * 1.5) * Game::menu_scale_factor) : w, txtArea.bottom * 2 };
		color OutlineColor = variables::gui::colors::primary; color BackColor = Functions::coloradd(variables::gui::colors::background, -50);
		if (inputmanager.inArea(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h)) {
			if (inputmanager.hold(VK_LBUTTON)) {
				OutlineColor = BackColor = Functions::coloradd(variables::gui::colors::primary, -25);
			}
			else {
				OutlineColor = variables::gui::colors::primary;
				BackColor = Functions::coloradd(variables::gui::colors::background, 30);
			}

		}
		else {
			OutlineColor = BackColor = Functions::coloradd(variables::gui::colors::background, 30);
		}


		paint->rectangle(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h, BackColor);
		paint->outline(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h, OutlineColor);
		paint->outline(ActivationArea.x + 1, ActivationArea.y + 1, ActivationArea.w - 2, ActivationArea.h - 2, OutlineColor);
		paint->text(ActivationArea.x + (ActivationArea.w / 2), ActivationArea.y + (ActivationArea.h / 2), buttontext.c_str(), Glyphs::menu_control, Anchor::Center, variables::gui::colors::text);
	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {
		RECT txtArea = paint->textSize(buttontext.c_str(), Glyphs::menu_control);
		AREA ActivationArea = { x + x_, y + y_, w == -1 ? ((txtArea.right * 1.5) * Game::menu_scale_factor) : w, txtArea.bottom * 2 };
		if (inputmanager.click(VK_LBUTTON) && inputmanager.inArea(ActivationArea.x, ActivationArea.y, ActivationArea.w, ActivationArea.h)) {
			function();
		}
	}
	void SetFunction(fn func) {
		function = func;
	}
	std::string buttontext;
	fn function;
	int h = 60 * Game::menu_scale_factor, w = 30;
	bool* value;
};
class edgeCheckbox : public edgeControl
{
public:
	edgeCheckbox(std::string n, int x_, int y_, bool* v, int allowed, int* a, int controlIncrementer) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = allowed; value = v; id = 1;
		uniqueID = controlIncrementer;
		m_iBallX = ((*value) == true) ? w - h : 0.f;
	}
	bool  loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		int m_cReturn = GetPrivateProfileInt(ConfigName.c_str(), m_nName.c_str(), 0, filepath);
		*value = m_cReturn;
		return true;
	}
	bool  saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		int m_cValue = *value;
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		if (WritePrivateProfileString(ConfigName.c_str(), m_nName.c_str(), std::to_string(m_cValue).c_str(), filepath))
			return true;
		return false;
	}
	void paintControl(int x_, int y_) {
		color m_cBackground = variables::gui::colors::primary;
		AREA m_ActivationArea = { x_ + x , y_ + y, w, h };
		AREA m_BallArea = { m_ActivationArea.x + m_iBallX + (m_ActivationArea.h / 4), m_ActivationArea.y + (m_ActivationArea.h / 4), m_ActivationArea.h / 2, m_ActivationArea.h / 2 };
		if (*value) {
			if (inputmanager.inArea(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h)) {
				m_cBackground = Functions::coloradd(variables::gui::colors::primary, 20);
			}
		}
		else {
			if (inputmanager.inArea(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h)) {
				m_cBackground = Functions::coloradd(variables::gui::colors::background, 40);
			}
			else {
				m_cBackground = Functions::coloradd(variables::gui::colors::background, 20);
			}
		}

		paint->circle(x_ + x + (h / 2), y_ + y + (h / 2), (h / 2), m_cBackground);
		paint->circle(x_ + x + w - (h / 2), y_ + y + (h / 2), (h / 2), m_cBackground);
		paint->rectangle(x_ + x + (h / 2), y_ + y, w - h, h, m_cBackground);
		paint->circle(m_BallArea.x + (m_BallArea.h / 2), m_BallArea.y + (m_BallArea.h / 2), m_BallArea.h / 2, variables::gui::colors::background);
	}
	void thinkControl() {
		int m_iValue = *value;
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		if (!m_bHolding) {
			m_iVelocity = m_iValue == 1 ? 1 : -1;
			m_iBallX += m_iVelocity;
		}
		m_iBallX = Functions::clip(m_iBallX, 0.f, (float)w - (float)h);
		*value = Functions::clip(m_iValue, 0, 1);
	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {
		int m_iValue = *value;
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		AREA m_ActivationArea = { x_ + x , y_ + y, w, h };
		AREA m_BallArea = { m_ActivationArea.x + m_iBallX + (m_ActivationArea.h / 4), m_ActivationArea.y + (m_ActivationArea.h / 4), m_ActivationArea.h / 2, m_ActivationArea.h / 2 };
		if (inputmanager.click(VK_LBUTTON)) {
			if (inputmanager.inArea(m_BallArea.x, m_BallArea.y, m_BallArea.w, m_BallArea.h))
				m_bHolding = true;
			else if (inputmanager.inArea(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h)) {
				m_iValue = (m_iValue == 1 ? 0 : 1);
			}
		}


		if (m_bHolding) {
			if (!inputmanager.hold(VK_LBUTTON)) {
				m_bHolding = false;
				m_iValue = (m_iBallX + (m_BallArea.w / 2)) < m_ActivationArea.w / 2 ? 0 : 1;
			}
			else
				m_iBallX = inputmanager.cursor.x - m_ActivationArea.x - m_iBallXRemainder;
		}
		else {
			m_iBallXRemainder = inputmanager.cursor.x - m_BallArea.x;
		}


		m_iBallX = Functions::clip(m_iBallX, 0.f, m_ActivationArea.w - m_ActivationArea.h);
		*value = Functions::clip(m_iValue, 0, 1);
	}
	int w = 60 * Game::menu_scale_factor, h = 20 * Game::menu_scale_factor;
	float m_iBallX = w - h;
	float m_iBallXSpacing = 0.15;
	bool m_bHolding = false;
	float m_iBallXRemainder = 0;
	int m_iVelocity = 1;
	bool* value;
};
class edgeSelectionCheckbox : public edgeControl
{
public:
	edgeSelectionCheckbox(std::string n, int x_, int y_, int* v, int allowed, int* a, int controlIncrementer) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = allowed; value = v; id = 1;
		uniqueID = controlIncrementer;
		if (*v == 0)
			previousI = 1;
		else
			previousI = *v;;

		m_iBallX = ((*value) > 0) ? w - h : 0.f;
	}
	bool  loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		int m_cReturn = GetPrivateProfileInt(ConfigName.c_str(), m_nName.c_str(), 0, filepath);
		*value = m_cReturn;
		return true;
	}
	bool  saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		int m_cValue = *value;
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		if (WritePrivateProfileString(ConfigName.c_str(), m_nName.c_str(), std::to_string(m_cValue).c_str(), filepath))
			return true;
		return false;
	}
	void paintControl(int x_, int y_) {
		color m_cBackground = variables::gui::colors::primary;
		AREA m_ActivationArea = { x_ + x , y_ + y, w, h };
		AREA m_BallArea = { m_ActivationArea.x + m_iBallX + (m_ActivationArea.h / 4), m_ActivationArea.y + (m_ActivationArea.h / 4), m_ActivationArea.h / 2, m_ActivationArea.h / 2 };
		if (*value) {
			if (inputmanager.inArea(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h)) {
				m_cBackground = Functions::coloradd(variables::gui::colors::primary, 20);
			}
		}
		else {
			if (inputmanager.inArea(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h)) {
				m_cBackground = Functions::coloradd(variables::gui::colors::background, 40);
			}
			else {
				m_cBackground = Functions::coloradd(variables::gui::colors::background, 20);
			}
		}

		paint->circle(x_ + x + (h / 2), y_ + y + (h / 2), (h / 2), m_cBackground);
		paint->circle(x_ + x + w - (h / 2), y_ + y + (h / 2), (h / 2), m_cBackground);
		paint->rectangle(x_ + x + (h / 2), y_ + y, w - h, h, m_cBackground);
		paint->circle(m_BallArea.x + (m_BallArea.h / 2), m_BallArea.y + (m_BallArea.h / 2), m_BallArea.h / 2, variables::gui::colors::background);
	}
	void thinkControl() {
		int m_iValue = *value;
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		if (!m_bHolding) {
			m_iVelocity = (m_iValue > 0) ? 1 : -1;
			m_iBallX += m_iVelocity;
		}
		m_iBallX = Functions::clip(m_iBallX, 0.f, (float)w - (float)h);
		*value = Functions::clip(m_iValue, 0, 4);
	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {
		int m_iValue = *value;
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		AREA m_ActivationArea = { x_ + x , y_ + y, w, h };
		AREA m_BallArea = { m_ActivationArea.x + m_iBallX + (m_ActivationArea.h / 4), m_ActivationArea.y + (m_ActivationArea.h / 4), m_ActivationArea.h / 2, m_ActivationArea.h / 2 };
		if (inputmanager.click(VK_LBUTTON)) {
			if (inputmanager.inArea(m_BallArea.x, m_BallArea.y, m_BallArea.w, m_BallArea.h))
				m_bHolding = true;
			else if (inputmanager.inArea(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h)) {
				if (m_iValue > 0) {
					m_iValue = 0;
					previousI = *value;
				}
				else {
					m_iValue = previousI;
				}
			}
		}


		if (m_bHolding) {
			if (!inputmanager.hold(VK_LBUTTON)) {
				m_bHolding = false;
				m_iValue = (m_iBallX + (m_BallArea.w / 2)) < m_ActivationArea.w / 2 ? 0 : previousI;
			}
			else
				m_iBallX = inputmanager.cursor.x - m_ActivationArea.x - m_iBallXRemainder;
		}
		else {
			m_iBallXRemainder = inputmanager.cursor.x - m_BallArea.x;
		}


		m_iBallX = Functions::clip(m_iBallX, 0.f, m_ActivationArea.w - m_ActivationArea.h);
		*value = Functions::clip(m_iValue, 0, 4);
	}
	int w = 60 * Game::menu_scale_factor, h = 20 * Game::menu_scale_factor;
	float m_iBallX = w - h;
	float m_iBallXSpacing = 0.15;
	bool m_bHolding = false;
	float m_iBallXRemainder = 0;
	int m_iVelocity = 1;
	int* value;
	int previousI = 0;

};
class edgeHorizontalScrollbar
{
public:
	void updateScrollBar(int& value, int x, int y, int w, int h, int max, int view, bool bFocus) {
		float barWidth = (double)((float)view / (float)max) * w;
		int scrollbarX = x + scrollValue;
		if (inputmanager.click(VK_LBUTTON) && inputmanager.inArea(scrollbarX, y, barWidth, h) && bFocus)
			bHolding = true;
		if (bHolding) {
			if (inputmanager.hold(VK_LBUTTON)) {
				scrollValue = inputmanager.cursor.x - disX - x;
			}
			else {
				bHolding = false;
			}
		}
		else {
			disX = inputmanager.cursor.x - scrollbarX;
		}

		scrollValue = Functions::clip(scrollValue, 0, (int)(w - barWidth));
		value = (float)((float)scrollValue / (float)w) * max;
	}
	void drawScrollBar(int& value, int x, int y, int w, int h, int max, int view, color bar, color back) {
		float barWidth = (double)((float)view / (float)max) * w;

		int scrollbarX = x + scrollValue;
		paint->rectangle(x, y, w, h, back);
		paint->rectangle(scrollbarX, y, barWidth, h, bar);
	}
	int scrollValue = 0;
	int disX = 0;
	bool bHolding = false;
};
class edgeVerticleScrollbar
{
public:
	void updateScrollBar(int& value, int x, int y, int w, int h, int max, int view, bool bFocus) {
		float barHeight = (double)((float)view / (float)max) * h;
		int yPos = (((float)value / (float)max) * h);

		if (inputmanager.click(VK_LBUTTON) && inputmanager.inArea(x, y + yPos, w, barHeight) && bFocus)
			bHolding = true;
		if (bHolding) {
			if (inputmanager.hold(VK_LBUTTON)) {
				yPos = Functions::clip((int)(inputmanager.cursor.y - y - disY), 0, (int)(h - barHeight));
				value = (float)((float)(yPos) / (float)h) * max;
			}
			else {
				bHolding = false;
			}
		}
		else {
			disY = inputmanager.cursor.y - yPos - y;
		}
		yPos = Functions::clip((int)(yPos), 0, (int)(h - barHeight));
	}
	void handleScrolling(int& value, int x, int y, int w, int h, int max, int view) {
		float barHeight = (double)((float)view / (float)max) * h;
		int yPos = (((float)value / (float)max) * h);
		if (inputmanager.inArea(x, y, w, h)) {
			if (inputmanager.bMouseDown && (y + yPos < y + h - barHeight)) {
				value += 5;
			}
			else if (inputmanager.bMouseUp && value > 0) {
				value -= 5;
			}
		}

		value = Functions::clip(value, 0, max);
	}
	void drawScrollBar(int& value, int x, int y, int w, int h, int max, int view) {
		float barHeight = (double)((float)view / (float)max) * h;
		int yPos = y + (((float)value / (float)max) * h);

		//paint->rectangle(x, y, w, h, color(50, 50, 50, 255));
		paint->circle(x + (w / 2), yPos + (w / 2), (w / 2), color(200, 200, 200, 200));
		paint->circle(x + (w / 2), yPos + barHeight - (w / 2), (w / 2), color(200, 200, 200, 200));
		paint->rectangle(x, yPos + (w / 2), w, barHeight - w, color(200, 200, 200, 200));
	}
	int scrollValue = 0;
	int disY = 0;
	bool bHolding = false;
};
class edgeSlider : public edgeControl
{
public:
	edgeSlider(std::string n, int x_, int y_, float we, int* a, int allowed, int* v, int ma, int mi, int controlIncrementer) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = allowed; value = v; m_iMax = ma; m_iMin = mi;
		if (we != -1)
			w = we;
		if (m_iMin < 0) {
			float add = 0;
			if (*value > 0)
				add = 0.5;
			m_iBarX = (((float)(*value) / (float)((float)-m_iMin + (float)m_iMax)) + add) * (float)w;
		}
		else {
			m_iBarX = ((float)(*value) / (float)(m_iMax - m_iMin)) * (float)w;
		}
		uniqueID = controlIncrementer;
	}
	bool  loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		int oldValue = *value;
		int m_cReturn = GetPrivateProfileInt(ConfigName.c_str(), m_nName.c_str(), oldValue, filepath);
		*value = m_cReturn;
		if (m_iMin < 0) {
			float add = 0;
			if (*value > 0)
				add = 0.5;
			m_iBarX = (((float)(*value) / (float)((float)-m_iMin + (float)m_iMax)) + add) * (float)w;
		}
		else {
			m_iBarX = ((float)(*value) / (float)(m_iMax - m_iMin)) * (float)w;
		}
		return true;
	}
	bool  saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		int m_cValue = *value;
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		if (WritePrivateProfileString(ConfigName.c_str(), m_nName.c_str(), std::to_string(m_cValue).c_str(), filepath))
			return true;
		return false;
	}
	void paintControl(int x_, int y_) {

		AREA m_ActivationArea = { x + x_,y + y_,w,h };
		AREA m_ScrollArea = { m_ActivationArea.x + m_iBarX + (m_ActivationArea.h / 2), y, h, h };
		color m_cLeft = variables::gui::colors::primary, m_cBar = color(0, 0, 0, 0), m_cRight = Functions::coloradd(variables::gui::colors::background, 20);;
		if (inputmanager.inArea(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h) || m_bHolding) {
			m_cBar = Functions::coloradd(variables::gui::colors::primary, 10);
		}
		else {
			m_cBar = variables::gui::colors::primary;
		}

		paint->circle(m_ActivationArea.x + (m_ActivationArea.h / 2), m_ActivationArea.y + (m_ActivationArea.h / 2), (m_ActivationArea.h) / 2, *value == 0 ? m_cRight : m_cBar);
		paint->circle(m_ActivationArea.x + m_ActivationArea.w - (m_ActivationArea.h / 2), m_ActivationArea.y + (m_ActivationArea.h / 2), (m_ActivationArea.h) / 2, m_cRight);
		paint->rectangle(m_ActivationArea.x + (m_ActivationArea.h / 2), m_ActivationArea.y, m_ActivationArea.w - m_ActivationArea.h, m_ActivationArea.h, m_cRight);


		paint->circle(m_ScrollArea.x, m_ActivationArea.y + (m_ActivationArea.h / 2), m_ActivationArea.h / 2, m_cBar);
		paint->rectangle(m_ActivationArea.x + (m_ActivationArea.h / 2), m_ActivationArea.y, m_ScrollArea.x - m_ActivationArea.x - (m_ActivationArea.h / 2), m_ActivationArea.h, m_cBar);


		//display.RoundedRect(m_ScrollArea.x, m_ScrollArea.y, m_ScrollArea.w, m_ScrollArea.h, (m_ScrollArea.w / 2), m_cBar, RECTANGLE(ClipArea.left, ClipArea.top, ClipArea.right, ClipArea.bottom));
		if (m_iAlpha > 0) {
			RECT stringArea = paint->textSize(std::to_string(*value).c_str(), Glyphs::menu_control);
			AREA BoxArea = { m_ScrollArea.x - (m_ScrollArea.h / 2) - (stringArea.right / 2) - 1, m_ActivationArea.y + m_ActivationArea.h + 5, m_ScrollArea.h + stringArea.right + 2, m_ScrollArea.h + stringArea.bottom + 2 };

			paint->rectangle(BoxArea.x, BoxArea.y, BoxArea.w, BoxArea.h, Functions::replaceAlpha(variables::gui::colors::background, m_iAlpha));
			paint->outline(BoxArea.x, BoxArea.y, BoxArea.w, BoxArea.h, Functions::coloradd(Functions::replaceAlpha(variables::gui::colors::background, m_iAlpha), -31));

			paint->text(BoxArea.x + (BoxArea.w / 2), BoxArea.y + (BoxArea.h / 2), std::to_string(*value).c_str(), Glyphs::menu_control, Anchor::Center, Functions::replaceAlpha(variables::gui::colors::text, m_iAlpha));
		}
	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		AREA m_ActivationArea = { x + x_,y + y_,w,h };
		AREA m_ScrollArea = { m_ActivationArea.x + m_iBarX, y, w * 0.02857142857, h };
		int m_iValue = *value;
		if (inputmanager.click(VK_LBUTTON)) {
			if (inputmanager.inArea(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h))
				m_bHolding = true;
		}

		if (m_bHolding) {
			m_iAlpha += m_iAlphaVelocity;
			if (!inputmanager.hold(VK_LBUTTON))
				m_bHolding = false;
			else
				m_iBarX = inputmanager.cursor.x - m_ActivationArea.x - (m_ScrollArea.w / 2);
		}
		else {
			m_iAlpha -= m_iAlphaVelocity;

		}

		m_iAlpha = Functions::clip(m_iAlpha, 0, 255);

		m_iBarX = Functions::clip(m_iBarX, 0.f, m_ActivationArea.w - m_ScrollArea.w - (m_ActivationArea.h / 2));
		double m_iStep = m_iBarX / (m_ActivationArea.w - m_ScrollArea.w - (m_ActivationArea.h / 2));
		m_iValue = m_iStep * (m_iMax - m_iMin);
		*value = Functions::clip(m_iValue + m_iMin, m_iMin, m_iMax);
	}
	int m_iMax, m_iMin, m_iAlphaVelocity = 10, m_iAlpha = 0, m_iBarRemainder;
	float m_iBarX = 0;
	int w = boxMenuWidth * Game::menu_scale_factor, h = 12 * Game::menu_scale_factor;
	bool m_bHolding = false;
	int* value;

};
class edgeSliderFloat : public edgeControl
{
public:
	edgeSliderFloat(std::string n, int x_, int y_, float we, int* a, int allowed, float* v, float ma, float mi, int controlIncrementer) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = allowed; value = v; m_iMax = ma; m_iMin = mi;
		if (we != -1)
			w = we;
		if (m_iMin < 0) {
			float add = 0;
			if (*value > 0)
				add = 0.5;
			m_iBarX = (((float)(*value) / (float)((float)-m_iMin + (float)m_iMax)) + add) * (float)w;
		}
		else {
			m_iBarX = ((float)(*value) / (float)(m_iMax - m_iMin)) * (float)w;
		}
		uniqueID = controlIncrementer;
	}
	bool  loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		
		CHAR m_cReturn[128];
		if (!GetPrivateProfileString(ConfigName.c_str(), m_nName.c_str(), "", m_cReturn, 128, filepath))
			return false;

		*value = std::stof((const char*)m_cReturn);
		if (m_iMin < 0) {
			float add = 0;
			if (*value > 0)
				add = 0.5;
			m_iBarX = (((float)(*value) / (float)((float)-m_iMin + (float)m_iMax)) + add) * (float)w;
		}
		else {
			m_iBarX = ((float)(*value) / (float)(m_iMax - m_iMin)) * (float)w;
		}
		return true;
	}
	bool  saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		float m_cValue = *value;
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		if (WritePrivateProfileString(ConfigName.c_str(), m_nName.c_str(), std::to_string(m_cValue).c_str(), filepath))
			return true;
		return false;
	}
	void paintControl(int x_, int y_) {

		AREA m_ActivationArea = { x + x_,y + y_,w,h };
		AREA m_ScrollArea = { m_ActivationArea.x + m_iBarX + (m_ActivationArea.h / 2), y, h, h };
		color m_cLeft = variables::gui::colors::primary, m_cBar = color(0, 0, 0, 0), m_cRight = Functions::coloradd(variables::gui::colors::background, 20);;
		if (inputmanager.inArea(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h) || m_bHolding) {
			m_cBar = Functions::coloradd(variables::gui::colors::primary, 10);
		}
		else {
			m_cBar = variables::gui::colors::primary;
		}

		paint->circle(m_ActivationArea.x + (m_ActivationArea.h / 2), m_ActivationArea.y + (m_ActivationArea.h / 2), (m_ActivationArea.h) / 2, *value == 0 ? m_cRight : m_cBar);
		paint->circle(m_ActivationArea.x + m_ActivationArea.w - (m_ActivationArea.h / 2), m_ActivationArea.y + (m_ActivationArea.h / 2), (m_ActivationArea.h) / 2, m_cRight);
		paint->rectangle(m_ActivationArea.x + (m_ActivationArea.h / 2), m_ActivationArea.y, m_ActivationArea.w - m_ActivationArea.h, m_ActivationArea.h, m_cRight);


		paint->circle(m_ScrollArea.x, m_ActivationArea.y + (m_ActivationArea.h / 2), m_ActivationArea.h / 2, m_cBar);
		paint->rectangle(m_ActivationArea.x + (m_ActivationArea.h / 2), m_ActivationArea.y, m_ScrollArea.x - m_ActivationArea.x - (m_ActivationArea.h / 2), m_ActivationArea.h, m_cBar);


		//display.RoundedRect(m_ScrollArea.x, m_ScrollArea.y, m_ScrollArea.w, m_ScrollArea.h, (m_ScrollArea.w / 2), m_cBar, RECTANGLE(ClipArea.left, ClipArea.top, ClipArea.right, ClipArea.bottom));
		if (m_iAlpha > 0) {
			std::string pureStringValue = std::to_string(*value);
			std::string clippedStringValue = pureStringValue.substr(0, pureStringValue.size() - 4);
			RECT stringArea = paint->textSize(clippedStringValue.c_str(), Glyphs::menu_control);
			AREA BoxArea = { m_ScrollArea.x - (m_ScrollArea.h / 2) - (stringArea.right / 2) - 1, m_ActivationArea.y + m_ActivationArea.h + 5, m_ScrollArea.h + stringArea.right + 2, m_ScrollArea.h + stringArea.bottom + 2 };

			paint->rectangle(BoxArea.x, BoxArea.y, BoxArea.w, BoxArea.h, Functions::replaceAlpha(variables::gui::colors::background, m_iAlpha));
			paint->outline(BoxArea.x, BoxArea.y, BoxArea.w, BoxArea.h, Functions::coloradd(Functions::replaceAlpha(variables::gui::colors::background, m_iAlpha), -31));
			paint->text(BoxArea.x + (BoxArea.w / 2), BoxArea.y + (BoxArea.h / 2), clippedStringValue.c_str(), Glyphs::menu_control, Anchor::Center, Functions::replaceAlpha(variables::gui::colors::text, m_iAlpha));
		}
	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		AREA m_ActivationArea = { x + x_,y + y_,w,h };
		AREA m_ScrollArea = { m_ActivationArea.x + m_iBarX, y, w * 0.02857142857, h };
		float m_iValue = *value;
		if (inputmanager.click(VK_LBUTTON)) {
			if (inputmanager.inArea(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h))
				m_bHolding = true;
		}

		if (m_bHolding) {
			m_iAlpha += m_iAlphaVelocity;
			if (!inputmanager.hold(VK_LBUTTON))
				m_bHolding = false;
			else
				m_iBarX = inputmanager.cursor.x - m_ActivationArea.x - (m_ScrollArea.w / 2);
		}
		else {
			m_iAlpha -= m_iAlphaVelocity;

		}

		m_iAlpha = Functions::clip(m_iAlpha, 0.f, 255.f);

		m_iBarX = Functions::clip(m_iBarX, 0.f, m_ActivationArea.w - m_ScrollArea.w - (m_ActivationArea.h / 2));
		double m_iStep = (double)m_iBarX / ((double)m_ActivationArea.w - (double)m_ScrollArea.w - ((double)m_ActivationArea.h / 2));
		m_iValue = m_iStep * (m_iMax - m_iMin);
		*value = Functions::clip(m_iValue + m_iMin, m_iMin, m_iMax);
	}
	float m_iMax, m_iMin, m_iAlphaVelocity = 10, m_iAlpha = 0, m_iBarRemainder;
	float m_iBarX = 0;
	int w = boxMenuWidth * Game::menu_scale_factor, h = 10 * Game::menu_scale_factor;
	bool m_bHolding = false;
	float* value;

};
class popupMessage {
public:
	popupMessage(std::string name, std::vector<std::string> messageList) {
		title = name;
		msges = messageList;
		width = Game::m_iWidth / 4;
		height = Game::m_iHeight / 4;
		x = (Game::m_iWidth / 2) - (width / 2);
		y = (Game::m_iHeight / 2) - (height / 2);
	}
	void paintMessage() {
		if (!open) return;
		AREA mainWindow = { x, y, width, height };
		RECT area = paint->textSize(title.c_str(), Glyphs::menu_main);

		paint->rectangle(mainWindow.x, mainWindow.y, mainWindow.w, 8 + area.bottom,  Functions::coloradd(variables::gui::colors::background, 10));
		paint->rectangle(mainWindow.x, mainWindow.y + 8 + area.bottom, mainWindow.w, mainWindow.h - (8 + area.bottom), Functions::coloradd(variables::gui::colors::background, 20));

		paint->text(mainWindow.x + 8, mainWindow.y + 5, title.c_str(), Glyphs::menu_main, Anchor::TopLeft, variables::gui::colors::text);
		paint->rectangle(mainWindow.x + 3, mainWindow.y + 8 + area.bottom, width - 6, 2, variables::gui::colors::primary);
		int yPlus = (area.bottom / 3);
		for (int i = 0; i < msges.size(); i++) {
			RECT area1 = paint->textSize(msges[i].c_str(), Glyphs::menu_control);
			if (msges[i] != "") {
				paint->circle(mainWindow.x + (area.bottom / 3), mainWindow.y + 8 + area.bottom + yPlus + (area1.bottom / 2), 3, variables::gui::colors::text);
				paint->text(mainWindow.x + (area.bottom / 3) + 6, mainWindow.y + 8 + area.bottom + yPlus, msges[i].c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text);
			}
			yPlus += (area1.bottom + 3);
		}

		RECT buttonArea = { mainWindow.x + mainWindow.w - (width / 4) - 10, mainWindow.y + mainWindow.h - (height / 5) - 10, width / 4, height / 5 };
		
		paint->rectangle(buttonArea.left, buttonArea.top, buttonArea.right, buttonArea.bottom, Functions::coloradd(variables::gui::colors::background, 30 + buttonAlpha));
		paint->text(buttonArea.left + (buttonArea.right / 2), buttonArea.top + (buttonArea.bottom / 2), xorStr("Ok"), Glyphs::menu_grabtext, Anchor::Center, Functions::coloradd(variables::gui::colors::text, buttonAlpha));
		
	}
	void updateMessage() {
		AREA mainWindow = { x, y, width, height };
		RECT buttonArea = { mainWindow.x + mainWindow.w - (width / 4) - 10, mainWindow.y + mainWindow.h - (height / 5) - 10, width / 4, height / 5 };

		if (inputmanager.inArea(buttonArea.left, buttonArea.top, buttonArea.right, buttonArea.bottom)) {
			if (buttonAlpha < 20)
				buttonAlpha += 2;
			if (inputmanager.click(VK_LBUTTON))
				open = false;
		}
		else if (buttonAlpha > 0){
			buttonAlpha -= 2;
		}
		buttonAlpha = Functions::clip(buttonAlpha, 0, 20);
		RECT area = paint->textSize(title.c_str(), Glyphs::menu_main);
		if (!holding) {
			rx = inputmanager.cursor.x - mainWindow.x;
			ry = inputmanager.cursor.y - mainWindow.y;
		}
		if (inputmanager.click(VK_LBUTTON) && (inputmanager.inArea(mainWindow.x, mainWindow.y, width, 8 + area.bottom))) {
			holding = true;
		}
		if (holding) {
			if (inputmanager.hold(VK_LBUTTON)) {
				x = inputmanager.cursor.x - rx;
				y = inputmanager.cursor.y - ry;
			}
			else
				holding = false;
		}
		
	}
	int buttonAlpha = 0;
	bool holding = false;
	int x = 0, y = 0, rx = 0, ry = 0;
	int width = 0, height = 0;
	bool open = true;;
	std::string title = "";
	std::vector<std::string> msges;
};
class edgeListbox : public edgeControl
{
public:
	edgeListbox(std::string n, int x_, int y_, int he, std::vector<std::string> list, int* v, int* a, int ee, int controlIncrementer) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = ee; value = v; Items = list; h = he;

		uniqueID = controlIncrementer;
	}
	bool  loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		int m_cReturn = GetPrivateProfileInt(ConfigName.c_str(), m_nName.c_str(), 0, filepath);
		*value = m_cReturn;
		return true;
	}
	bool  saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		int m_cValue = *value;
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		if (WritePrivateProfileString(ConfigName.c_str(), m_nName.c_str(), std::to_string(m_cValue).c_str(), filepath))
			return true;
		return false;
	}
	void paintControl(int x_, int y_) {
		AREA m_ActivationArea = { x_ + x,y_ + y, w, h };
		int m_iValue = *value;
		std::vector<std::string> m_vItems = Items;
		paint->rectangle(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h, variables::gui::colors::background);
		paint->outline(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h, color(0, 0, 0, 255));

		float m_fSpacing = (0.0179 * m_ActivationArea.w);
		RECT InsideClip = RECT{ (LONG)m_ActivationArea.x,(LONG)m_ActivationArea.y + (LONG)m_fSpacing, (LONG)m_ActivationArea.w, (LONG)(m_ActivationArea.h - (m_fSpacing * 2)) };

		for (int i = 0; i < m_vItems.size(); i++) {
			AREA m_Area = { m_ActivationArea.x + m_fSpacing, m_ActivationArea.y - scrollY + (m_iSize * i) + m_fSpacing, m_ActivationArea.w - (/*SCROLL W*/5) - (m_fSpacing * 2), m_iSize - (m_fSpacing / 2) };
			if (m_Area.y + m_Area.h < m_ActivationArea.y) continue;
			if (m_Area.y > m_ActivationArea.y + m_ActivationArea.h) continue;
			color m_cBack = variables::gui::colors::primary;
			if (i == m_iValue) {
				if (inputmanager.inArea(m_Area.x, m_Area.y, m_Area.w, m_Area.h))
					m_cBack = Functions::coloradd(variables::gui::colors::primary, 20);
			}
			else {
				if (inputmanager.inArea(m_Area.x, m_Area.y, m_Area.w, m_Area.h))
					m_cBack = Functions::coloradd(variables::gui::colors::primary, -30);
				else
					m_cBack = Functions::coloradd(variables::gui::colors::background, -10);
			}

			paint->rectangle(m_Area.x, m_Area.y, m_Area.w, m_Area.h, m_cBack, InsideClip);
			RECT m_TextArea = paint->textSize(m_vItems[i].c_str(), Glyphs::menu_control);
			paint->text(m_Area.x + ((m_Area.w + /*scroll W*/5) * 0.04285714285), m_Area.y + (m_Area.h / 2) - (m_TextArea.bottom / 2), m_vItems[i].c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text, InsideClip);
		}
		if (m_vItems.size() * m_iSize > m_ActivationArea.h)
			scroll.drawScrollBar(scrollY, m_ActivationArea.x + m_ActivationArea.w - 5, m_ActivationArea.y, 5, m_ActivationArea.h, (m_vItems.size() + 2) * m_iSize, m_ActivationArea.h + m_fSpacing);

	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		AREA m_ActivationArea = { x_ + x,y_ + y, w, h };
		float m_fSpacing = (0.0179 * m_ActivationArea.w);
		int m_iValue = *value;
		std::vector<std::string> m_vItems = Items;
		if (m_vItems.size() * m_iSize > m_ActivationArea.h) {
			RECT InsideClip = RECT{ (LONG)m_ActivationArea.x,(LONG)m_ActivationArea.y + (LONG)m_fSpacing, (LONG)m_ActivationArea.w, (LONG)(m_ActivationArea.h - (m_fSpacing * 2)) };
			scroll.updateScrollBar(scrollY, m_ActivationArea.x + m_ActivationArea.w - 5, m_ActivationArea.y, 5, m_ActivationArea.h, (m_vItems.size() + 2) * m_iSize, m_ActivationArea.h + m_fSpacing, true);
		}
		else {
			scrollY = 0;
		}
		scroll.handleScrolling(scrollY, m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h, (m_vItems.size() + 2) * m_iSize, m_ActivationArea.h + m_fSpacing);

		for (int i = 0; i < m_vItems.size(); i++) {
			AREA m_Area = { m_ActivationArea.x + m_fSpacing, m_ActivationArea.y - scrollY + (m_iSize * i) + m_fSpacing, m_ActivationArea.w - (/*SCROLL W*/ 5) - (m_fSpacing * 2), m_iSize - (m_fSpacing / 2) };
			if (m_Area.y + m_Area.h < m_ActivationArea.y) continue;
			if (m_Area.y > m_ActivationArea.y + m_ActivationArea.h) continue;
			if (i == m_iValue) continue;
			if (inputmanager.inArea(m_Area.x, m_Area.y, m_Area.w, m_Area.h) && inputmanager.click(VK_LBUTTON)) {
				m_iValue = i;
			}
		}
		*value = Functions::clip(m_iValue, 0, (int)(m_vItems.size() - 1));
	}
	int m_iSize = 32;
	std::vector<std::string> Items;
	int w = 200 * Game::menu_scale_factor, h = 800 * Game::menu_scale_factor;
	edgeVerticleScrollbar scroll;
	int* value;
	int scrollY = 0;
};
class edgeGraph : public edgeControl
{
public:
	edgeGraph(std::string n, int x_, int y_, std::vector<int>* data, int* a, int ee, int controlIncrementer) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = ee; graphData = data;

		uniqueID = controlIncrementer;
	}
	bool  loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{

		return true;
	}
	bool  saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		return false;
	}
	void paintControl(int x_, int y_) {
		AREA m_ActivationArea = { x_ + x,y_ + y, w, h };
		paint->rectangle(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h, Functions::coloradd(variables::gui::colors::background, variables::gui::colors::lighterBackgroundHuePlus));

		if (graphData->empty()) {
			paint->text(m_ActivationArea.x + (m_ActivationArea.w / 2), m_ActivationArea.y + (m_ActivationArea.h / 2), xorStr("No data"), Glyphs::menu_control, Anchor::Center, variables::gui::colors::text);
		}
		else {
			int maxValue = 0, minValue = 9999;
			for (int i = 0; i < graphData->size(); i++) {
				if (graphData->at(i) > maxValue)
					maxValue = graphData->at(i);
				if (graphData->at(i) < minValue)
					minValue = graphData->at(i);
			}
			if (inputmanager.inArea(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h)) {
				paint->line(inputmanager.cursor.x, m_ActivationArea.y, inputmanager.cursor.x, m_ActivationArea.y + m_ActivationArea.h, Functions::replaceAlpha(variables::gui::colors::text, 30));
				paint->line(m_ActivationArea.x, inputmanager.cursor.y, m_ActivationArea.x + m_ActivationArea.w, inputmanager.cursor.y, Functions::replaceAlpha(variables::gui::colors::text, 30));
			}
			for (int i = 0; i < graphData->size() - 1; i++) {
				int current_y = ((float)((float)(graphData->at(i) - minValue) / (float)(maxValue - minValue)) * m_ActivationArea.h);
				int current_x = (float)((float)(i) / (float)graphData->size()) * m_ActivationArea.w;
				int future_y = ((float)((float)(graphData->at(i + 1) - minValue) / (float)(maxValue - minValue)) * m_ActivationArea.h);
				int future_x = (float)((float)(i + 1) / (float)graphData->size()) * m_ActivationArea.w;
				float FPSDrop = graphData->at(i) - graphData->at(i + 1);
				paint->line(m_ActivationArea.x + current_x, m_ActivationArea.y + m_ActivationArea.h - current_y, m_ActivationArea.x + future_x, m_ActivationArea.y + m_ActivationArea.h - future_y, FPSDrop > 20 ? variables::gui::colors::primary : variables::gui::colors::text);
				paint->text(m_ActivationArea.x + current_x, m_ActivationArea.y + m_ActivationArea.h, std::to_string(i).c_str(), Glyphs::menu_control, Anchor::TopCenter, variables::gui::colors::text);
			}
			for (int i = maxValue; i > minValue; i -= 15)
				paint->text(m_ActivationArea.x, m_ActivationArea.y + m_ActivationArea.h - (((float)(i - minValue) / (float)(maxValue - minValue)) * m_ActivationArea.h), std::to_string(i).c_str(), Glyphs::menu_control, Anchor::RightCenter, variables::gui::colors::text);
		}
	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		AREA m_ActivationArea = { x_ + x,y_ + y, w, h };

	}
	std::vector<int>* graphData;
	int w = (boxMenuWidth * 2) * Game::menu_scale_factor, h = (boxMenuWidth * 1.5) * Game::menu_scale_factor;
};
class edgeSearchableListbox : public edgeControl
{
public:
	edgeSearchableListbox(std::string n, int x_, int y_, int he, std::vector<std::string> list, int* v, int* a, int ee, int controlIncrementer) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = ee; value = v; Items = list; h = he;
		visualData = Items[*v];
		uniqueID = controlIncrementer;
	}
	bool  loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		int m_cReturn = GetPrivateProfileInt(ConfigName.c_str(), m_nName.c_str(), 0, filepath);
		*value = m_cReturn;
		visualData = Items[*value];
		m_vItems.clear();
		searchboxoutput = "";
		searchbox.AcceptingInput = false;
		searchbox.temptext = "";
		return true;
	}
	bool  saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		int m_cValue = *value;
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		if (WritePrivateProfileString(ConfigName.c_str(), m_nName.c_str(), std::to_string(m_cValue).c_str(), filepath))
			return true;
		return false;
	}
	void paintControl(int x_, int y_) {
		AREA m_ActivationArea = { x_ + x,y_ + y, w, h };
		paint->rectangle(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h, variables::gui::colors::background);
		paint->outline(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h, color(0, 0, 0, 255));

		float m_fSpacing = (0.0179 * m_ActivationArea.w);
		RECT InsideClip = RECT{ (LONG)m_ActivationArea.x,(LONG)m_ActivationArea.y + (LONG)m_fSpacing, (LONG)m_ActivationArea.w, (LONG)(m_ActivationArea.h - (m_fSpacing * 2)) };

		for (int i = 0; i < m_vItems.size(); i++) {
			std::string name = m_vItems[i];
			AREA m_Area = { m_ActivationArea.x + m_fSpacing, m_ActivationArea.y - scrollY + (m_iSize * i) + m_fSpacing, m_ActivationArea.w - (/*SCROLL W*/5) - (m_fSpacing * 2), m_iSize - (m_fSpacing / 2) };
			if (m_Area.y + m_Area.h < m_ActivationArea.y) continue;
			if (m_Area.y > m_ActivationArea.y + m_ActivationArea.h) continue;
			color m_cBack = variables::gui::colors::primary;
			if (name == visualData) {
				if (inputmanager.inArea(m_Area.x, m_Area.y, m_Area.w, m_Area.h))
					m_cBack = Functions::coloradd(variables::gui::colors::primary, 20);
			}
			else {
				if (inputmanager.inArea(m_Area.x, m_Area.y, m_Area.w, m_Area.h))
					m_cBack = Functions::coloradd(variables::gui::colors::primary, -50);
				else
					m_cBack = Functions::coloradd(variables::gui::colors::background, -10);
			}

			paint->rectangle(m_Area.x, m_Area.y, m_Area.w, m_Area.h, m_cBack, InsideClip);
			RECT m_TextArea = paint->textSize(m_vItems[i].c_str(), Glyphs::menu_control);
			paint->text(m_Area.x + ((m_Area.w + /*scroll W*/5) * 0.04285714285), m_Area.y + (m_Area.h / 2) - (m_TextArea.bottom / 2), m_vItems[i].c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text, InsideClip);
		}
		if (m_vItems.size() * m_iSize > m_ActivationArea.h)
			scroll.drawScrollBar(scrollY, m_ActivationArea.x + m_ActivationArea.w - 5, m_ActivationArea.y, 5, m_ActivationArea.h, (m_vItems.size() + 2) * m_iSize, m_ActivationArea.h + m_fSpacing);
		searchbox.paintControl(&searchboxoutput, m_ActivationArea.x, m_ActivationArea.y + m_ActivationArea.h + 3, m_ActivationArea.w);


	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		AREA m_ActivationArea = { x_ + x,y_ + y, w, h };
		float m_fSpacing = (0.0179 * m_ActivationArea.w);

		searchbox.updateControl(&searchboxoutput, m_ActivationArea.x, m_ActivationArea.y + m_ActivationArea.h + 3, m_ActivationArea.w);
		if (m_vItems.size() == 0 && searchboxoutput == xorStr("")) {
			m_vItems = Items;
		}
		if (searchboxoutput != previousearchboxoutput) {
			m_vItems.clear();
			std::string loweredSearch = Functions::toLower(searchboxoutput);
			for (int i = 0; i < Items.size(); i++) {
				std::string loweredItem = Functions::toLower(Items[i]);
				if (loweredItem.find(loweredSearch) != std::string::npos)
					m_vItems.push_back(Items[i]);
			}
			previousearchboxoutput = searchboxoutput;
		}


		if (m_vItems.size() * m_iSize > m_ActivationArea.h) {
			RECT InsideClip = RECT{ (LONG)m_ActivationArea.x,(LONG)m_ActivationArea.y + (LONG)m_fSpacing, (LONG)m_ActivationArea.w, (LONG)(m_ActivationArea.h - (m_fSpacing * 2)) };
			scroll.updateScrollBar(scrollY, m_ActivationArea.x + m_ActivationArea.w - 5, m_ActivationArea.y, 5, m_ActivationArea.h, (m_vItems.size() + 2) * m_iSize, m_ActivationArea.h + m_fSpacing, true);
		}
		else {
			scrollY = 0;
		}

		scroll.handleScrolling(scrollY, m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h, (m_vItems.size()) * m_iSize, m_ActivationArea.h + m_fSpacing);


		for (int i = 0; i < m_vItems.size(); i++) {
			std::string name = m_vItems[i];
			AREA m_Area = { m_ActivationArea.x + m_fSpacing, m_ActivationArea.y - scrollY + (m_iSize * i) + m_fSpacing, m_ActivationArea.w - (/*SCROLL W*/ 5) - (m_fSpacing * 2), m_iSize - (m_fSpacing / 2) };
			if (m_Area.y + m_Area.h < m_ActivationArea.y) continue;
			if (m_Area.y > m_ActivationArea.y + m_ActivationArea.h) continue;
			if (name == visualData) continue;
			if (inputmanager.inArea(m_Area.x, m_Area.y, m_Area.w, m_Area.h) && inputmanager.click(VK_LBUTTON)) {
				visualData = name;
			}
		}
		bool selectedFound = false;
		if (m_vItems.size() > 0) {
			for (int i = 0; i < Items.size(); i++) {
				if (selectedFound) break;
				if (visualData == Items[i]) {
					*value = Functions::clip(i, 0, (int)(Items.size() - 1));
					selectedFound = true;
				}
			}
		}
		if (!selectedFound) {
			*value = 1;
			visualData = xorStr("");
		}
	}
	int m_iSize = 32;
	std::vector<std::string> Items;
	std::vector<std::string> m_vItems;
	int w = 200 * Game::menu_scale_factor, h = 800 * Game::menu_scale_factor;
	edgeVerticleScrollbar scroll;
	edgePortableTextbox searchbox;
	std::string searchboxoutput = "";
	std::string previousearchboxoutput = "";
	int* value;
	std::string visualData = "";
	int scrollY = 0;
};

class edgeListboxAdjustable : public edgeControl
{
public:
	edgeListboxAdjustable(std::string n, int x_, int y_, int he, std::vector<std::string>* list, int* v, int* a, int ee, int controlIncrementer) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = ee; value = v; Items = list; h = he;
		uniqueID = controlIncrementer;
	}
	bool  loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		int m_cReturn = GetPrivateProfileInt(ConfigName.c_str(), m_nName.c_str(), 0, filepath);
		*value = m_cReturn;
		return true;
	}
	bool  saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		int m_cValue = *value;
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		if (WritePrivateProfileString(ConfigName.c_str(), m_nName.c_str(), std::to_string(m_cValue).c_str(), filepath))
			return true;
		return false;
	}
	void paintControl(int x_, int y_) {
		AREA m_ActivationArea = { x_ + x,y_ + y, w, h };
		int m_iValue = *value;
		std::vector<std::string> m_vItems = *Items;
		paint->rectangle(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h, variables::gui::colors::background);
		paint->outline(m_ActivationArea.x, m_ActivationArea.y, m_ActivationArea.w, m_ActivationArea.h, color(0, 0, 0, 255));

		float m_fSpacing = (0.0179 * m_ActivationArea.w);
		RECT InsideClip = RECT{ (LONG)m_ActivationArea.x,(LONG)m_ActivationArea.y + (LONG)m_fSpacing, (LONG)m_ActivationArea.w, (LONG)(m_ActivationArea.h - (m_fSpacing * 2)) };

		for (int i = 0; i < m_vItems.size(); i++) {
			AREA m_Area = { m_ActivationArea.x + m_fSpacing, m_ActivationArea.y - scrollY + (m_iSize * i) + m_fSpacing, m_ActivationArea.w - (/*SCROLL W*/5) - (m_fSpacing * 2), m_iSize - (m_fSpacing / 2) };
			if (m_Area.y + m_Area.h < m_ActivationArea.y) continue;
			if (m_Area.y > m_ActivationArea.y + m_ActivationArea.h) continue;
			color m_cBack = variables::gui::colors::primary;
			if (i == m_iValue) {
				if (inputmanager.inArea(m_Area.x, m_Area.y, m_Area.w, m_Area.h))
					m_cBack = Functions::replaceAlpha(Functions::coloradd(variables::gui::colors::primary, -22), 20);
			}
			else {
				if (inputmanager.inArea(m_Area.x, m_Area.y, m_Area.w, m_Area.h))
					m_cBack = Functions::coloradd(variables::gui::colors::background, -37);
				else
					m_cBack = Functions::coloradd(variables::gui::colors::background, -13);
			}

			paint->rectangle(m_Area.x, m_Area.y, m_Area.w, m_Area.h, m_cBack, InsideClip);
			RECT m_TextArea = paint->textSize(m_vItems[i].c_str(), Glyphs::menu_control);
			paint->text(m_Area.x + ((m_Area.w + /*scroll W*/5) * 0.04285714285), m_Area.y + (m_Area.h / 2) - (m_TextArea.bottom / 2), m_vItems[i].c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text, InsideClip);
		}
		if (m_vItems.size() * m_iSize > m_ActivationArea.h)
			scroll.drawScrollBar(scrollY, m_ActivationArea.x + m_ActivationArea.w - 5, m_ActivationArea.y, 5, m_ActivationArea.h, (m_vItems.size() + 2) * m_iSize, m_ActivationArea.h + m_fSpacing);

	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen) {
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		AREA m_ActivationArea = { x_ + x,y_ + y, w, h };
		float m_fSpacing = (0.0179 * m_ActivationArea.w);
		int m_iValue = *value;
		std::vector<std::string> m_vItems = *Items;
		if (m_vItems.size() * m_iSize > m_ActivationArea.h) {
			RECT InsideClip = RECT{ (LONG)m_ActivationArea.x,(LONG)m_ActivationArea.y + (LONG)m_fSpacing, (LONG)m_ActivationArea.w, (LONG)(m_ActivationArea.h - (m_fSpacing * 2)) };
			scroll.updateScrollBar(scrollY, m_ActivationArea.x + m_ActivationArea.w - 5, m_ActivationArea.y, 5, m_ActivationArea.h, (m_vItems.size() + 2) * m_iSize, m_ActivationArea.h + m_fSpacing, true);
		}
		else {
			scrollY = 0;
		}

		for (int i = 0; i < m_vItems.size(); i++) {
			AREA m_Area = { m_ActivationArea.x + m_fSpacing, m_ActivationArea.y - scrollY + (m_iSize * i) + m_fSpacing, m_ActivationArea.w - (/*SCROLL W*/ 5) - (m_fSpacing * 2), m_iSize - (m_fSpacing / 2) };
			if (m_Area.y + m_Area.h < m_ActivationArea.y) continue;
			if (m_Area.y > m_ActivationArea.y + m_ActivationArea.h) continue;
			if (i == m_iValue) continue;
			if (inputmanager.inArea(m_Area.x, m_Area.y, m_Area.w, m_Area.h) && inputmanager.click(VK_LBUTTON)) {
				m_iValue = i;
			}
		}
		*value = Functions::clip(m_iValue, 0, (int)(m_vItems.size() - 1));
	}
	int m_iSize = 32 * Game::menu_scale_factor;
	std::vector<std::string>* Items;
	int w = 300 * Game::menu_scale_factor, h = 800 * Game::menu_scale_factor;
	edgeVerticleScrollbar scroll;
	int* value;
	int scrollY = 0;
};
class moveable
{
public:
	moveable() {};
	moveable(int* position_, std::string tx, color co) {
		position = position_; txt = tx; col = co;
	}
	int* position = 0;
	int dy= 0, dx = 0;
	bool dragging = false;

	std::string txt = "";
	color col = color(255,255,255,255);
};

class edgeESPSelector : public edgeControl
{

public:
	edgeESPSelector(std::string n, int x_, int y_, int* a, int allow, int controlIncrementer, bool t, bool* enable_, bool* visibleOnly_, int* health_, int* box_, bool* boxoutline_, int* name_, int* weapon_, int* money_, bool* skeleton_, int* distance_, int* ammunition_, int* chams_, bool* barrel_, bool* xqz_, int* glow_, int* reloadwarning_, int* scopedWarning_, int* defuseWarning_, int* hostageWarning_, int* HelmetESP_) 
	{
		name = n; x = x_; y = y_; allowedVisibleComparitor = allow;  allowedVisible = a;
		
		enable = enable_;
		isTerrorist = t;
		h = 1.7 * w;
		health = health_;
		box = box_;
		boxoutline = boxoutline_;
		skeleton = skeleton_;
		chams = chams_;
		barrel = barrel_;
		xqz = xqz_;
		glow = glow_;



		moveables[0] = moveable(name_, "Alan", color(255, 255, 255, 255) );
		moveables[1] = moveable(weapon_, isTerrorist ? "glock-18" : "usp-s", color(255, 255, 255, 255));
		moveables[2] = moveable(money_, "$690", color(55, 255, 55, 255));
		moveables[3] = moveable(distance_, "16m", color(0, 255, 255, 255));
		moveables[4] = moveable(ammunition_, "(24/32)", color(0, 255, 255, 255));;
		moveables[5] = moveable(reloadwarning_, "*reload*", color(255, 0, 255, 255));;
		moveables[6] = moveable(scopedWarning_, "*scoped*", color(255, 0, 255, 255));;
		moveables[7] = moveable(defuseWarning_, "*defuse*", color(255, 0, 255, 255));;
		moveables[8] = moveable(hostageWarning_, "*hostage*", color(255, 0, 255, 255));;
		moveables[9] = moveable(HelmetESP_, "*H*", color(255, 0, 255, 255));;
		if (isTerrorist) {
			switch (*chams) {
			case 0:
				currentImage = images::csgoCTDefault;
				break;
			case 1:
			case 2:
				currentImage = images::csgoCTChams;
				break;
			case 3:
				currentImage = images::csgoCTWireframe;
				break;
			case 4:
				currentImage = images::csgoCTGold;
				break;
			case 5:
				currentImage = images::csgoCTPlastic;
				break;
			default:
				currentImage = images::csgoCTplatinum;
				break;
			}
		}
		else {
			switch (*chams) {
			case 0:
				currentImage = images::csgoTDefault;
				break;
			case 1:
			case 2:
				currentImage = images::csgoTChams;
				break;
			case 3:
				currentImage = images::csgoTWireframe;
				break;
			case 4:
				currentImage = images::csgoTGold;
				break;
			case 5:
				currentImage = images::csgoTPlastic;
				break;
			default:
				currentImage = images::csgoTplatinum;
				break;
			}
		}
		uniqueID = controlIncrementer;
	}
	bool  loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		CHAR m_cReturn[128];
		if (!GetPrivateProfileString(ConfigName.c_str(), m_nName.c_str(), "", m_cReturn, 128, filepath))
			return false;
		for (int i = 0; i < 5; i++) {
			if (m_cReturn[i] != '0' &&
				m_cReturn[i] != '1')
				return false;
		}
		
		return true;
	}
	bool  saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{

		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		//std::string m_cValue = std::to_string(*head) + std::to_string(*upper) + std::to_string(*lower) + std::to_string(*arms) + std::to_string(*legs);
		//if (WritePrivateProfileString(ConfigName.c_str(), m_nName.c_str(), m_cValue.c_str(), filepath))
		//	return true;
		return false;
	}
	
	void paintControl(int x_, int y_) {

		RECT m_ActivationArea = { x_ + x , y_ + y, w, h };
		paint->rectangle(m_ActivationArea.left, m_ActivationArea.top, m_ActivationArea.right, m_ActivationArea.bottom, Functions::coloradd(variables::gui::colors::background, 30));
		paint->outline(m_ActivationArea.left, m_ActivationArea.top, m_ActivationArea.right, m_ActivationArea.bottom, !*enable ? color(0, 0, 0, 125) : color(0, 0, 0, 255));


		paint->text(m_ActivationArea.left + (m_ActivationArea.right / 2), m_ActivationArea.top + 3, xorStr("Drag to customise"), Glyphs::menu_control, Anchor::TopCenter, Functions::replaceAlpha(variables::gui::colors::text, noteAlpha));
		RECT boxArea = { m_ActivationArea.left + (m_ActivationArea.right / 4), m_ActivationArea.top + (m_ActivationArea.bottom / 2) - ((((m_ActivationArea.right / 2) * (isTerrorist ? 1.96 : 2.6)))  / 2), m_ActivationArea.right / 2, ((m_ActivationArea.right / 2) * (isTerrorist ? 1.96 : 2.6)) };
		imageData imag = images::csgocharacter;
		if (isTerrorist) {
			switch (*chams) {
			case 0:
				imag = images::csgoCTDefault;
				break;
			case 1:
			case 2:
				imag = images::csgoCTChams;
				break;
			case 3:
				imag = images::csgoCTWireframe;
				break;
			case 4:
				imag = images::csgoCTGold;
				break;
			case 5:
				imag = images::csgoCTPlastic;
				break;
			default:
				imag = images::csgoCTplatinum;
				break;
			}
		}
		else {
			switch (*chams) {
			case 0:
				imag = images::csgoTDefault;
				break;
			case 1:
			case 2:
				imag = images::csgoTChams;
				break;
			case 3:
				imag = images::csgoTWireframe;
				break;
			case 4:
				imag = images::csgoTGold;
				break;
			case 5:
				imag = images::csgoTPlastic;
				break;
			default:
				imag = images::csgoTplatinum;
				break;
			}
		}
		if (currentImage.m_iTexture != imag.m_iTexture) {
			if (imageAlpha > 1) {
				imageAlpha = Functions::clip((float)imageAlpha - 5, 0.0f, 255.f);
			}
			else {
				currentImage = imag;
			}
		}
		else if (currentImage.m_iTexture == imag.m_iTexture) {
			if (imageAlpha < 254) {
				imageAlpha = Functions::clip((float)imageAlpha + 5, 0.0f, 255.f);
			}
		}
		paint->imageAlpha(boxArea.left, boxArea.top, boxArea.right, boxArea.bottom, currentImage, imageAlpha);

		bbox.UpdatePosition(boxArea.left, boxArea.top, boxArea.right, boxArea.bottom);
		Vector p[8] = { Vector(boxArea.left + (0.076 * boxArea.right) ,  boxArea.top + (0.951 * boxArea.bottom), 0),
						Vector(boxArea.left + (0.9 * boxArea.right), boxArea.top + (0.037 * boxArea.bottom), 0),
						Vector(boxArea.left + (0.394 * boxArea.right), boxArea.top + (0.810 * boxArea.bottom), 0),
						Vector(boxArea.left + (0.6842 * boxArea.right), boxArea.top + (0.1620 * boxArea.bottom), 0),
						Vector(boxArea.left + (0.694 * boxArea.right), boxArea.top + (0.9551 * boxArea.bottom), 0),
						Vector(boxArea.left + (0.884 * boxArea.right), boxArea.top + (0.813 * boxArea.bottom), 0),
						Vector(boxArea.left + (0.3947 * boxArea.right), boxArea.top + (0.037 * boxArea.bottom), 0),
						Vector(boxArea.left + (0.0789 * boxArea.right), boxArea.top + (0.1551 * boxArea.bottom), 0) };
		bbox.updatePoints(p);
	
		bbox.Draw(*box, *boxoutline, color(255, 0, 255, 255), *health == 3 ? 5 : 1, *health == 4 ? 5 : 1, *health == 1 ? 5 : 0, *health == 2 ? 5 : 0);
		if (*health != 0) {
			if (holdingHealth) {
				int side = Functions::closestSide(inputmanager.cursor.x, inputmanager.cursor.y, boxArea);
				switch (side) {
				case 1:
					paint->outline(boxArea.left - 5, boxArea.top, 3, boxArea.bottom, color(0, 255, 0, 255));
					boxArea.left -= 3; boxArea.right += 3;
					break;
				case 2:
					paint->outline(boxArea.left + boxArea.right + 2, boxArea.top, 3, boxArea.bottom, color(0, 255, 0, 255));
					boxArea.right += 3;
					break;
				case 3:
					paint->outline(boxArea.left, boxArea.top - 4, boxArea.right, 3, color(0, 255, 0, 255));
					boxArea.top -= 3;
					break;
				case 4:
					paint->outline(boxArea.left, boxArea.top + boxArea.bottom + 2, boxArea.right, 3, color(0, 255, 0, 255));
					boxArea.top += 3;
					break;
				}
			}
			else {
				switch (*health) {
				case 1:
					paint->rectangle(boxArea.left - 5, boxArea.top, 3, boxArea.bottom, color(0, 0, 0, 255));
					paint->rectangle(boxArea.left - 4, boxArea.top + 1, 1, boxArea.bottom - 2, color(0, 255, 0, 255));
					boxArea.left -= 5;
					break;
				case 2:
					paint->rectangle(boxArea.left + boxArea.right + 2, boxArea.top, 3, boxArea.bottom, color(0, 0, 0, 255));
					paint->rectangle(boxArea.left + boxArea.right + 3, boxArea.top, 1, boxArea.bottom - 2, color(0, 255, 0, 255));
					boxArea.left += 5;
					break;
				case 3:
					paint->rectangle(boxArea.left, boxArea.top - 4, boxArea.right, 3, color(0, 0, 0, 255));
					paint->rectangle(boxArea.left + 1, boxArea.top - 3, boxArea.right - 2, 1, color(0, 255, 0, 255));
					boxArea.top -= 3;
					break;
				case 4:
					paint->rectangle(boxArea.left, boxArea.top + boxArea.bottom + 2, boxArea.right, 3, color(0, 0, 0, 255));
					paint->rectangle(boxArea.left + 1, boxArea.top + boxArea.bottom + 3, boxArea.right - 2, 1, color(0, 255, 0, 255));
					boxArea.top += 5;
					break;
				}
			}
		}
		
		if (*skeleton) {
			Vector arms[7] = { Vector(boxArea.left + (0.18 * boxArea.right), boxArea.top + (0.2769 * boxArea.bottom),0) ,
							   Vector(boxArea.left + (0.345 * boxArea.right), boxArea.top + (0.246 * boxArea.bottom) ,0) ,
							   Vector(boxArea.left + (0.43 * boxArea.right), boxArea.top + (0.171 * boxArea.bottom) ,0) ,
							   Vector(boxArea.left + (0.595 * boxArea.right), boxArea.top + (0.159 * boxArea.bottom) ,0),
							   Vector(boxArea.left + (0.875 * boxArea.right), boxArea.top + (0.169 * boxArea.bottom) ,0),
							   Vector(boxArea.left + (0.715 * boxArea.right), boxArea.top + (0.284 * boxArea.bottom) ,0),
							   Vector(boxArea.left + (0.22 * boxArea.right), boxArea.top + (0.286 * boxArea.bottom) ,0) };



			Vector spine[3] = { Vector(boxArea.left + (0.57 * boxArea.right), boxArea.top + (0.073 * boxArea.bottom),0) ,
								Vector(boxArea.left + (0.595 * boxArea.right), boxArea.top + (0.159 * boxArea.bottom),0) ,
					            Vector(boxArea.left + (0.68 * boxArea.right), boxArea.top + (0.413 * boxArea.bottom),0) };

			Vector legs[9] = { Vector(boxArea.left + (0.45 * boxArea.right), boxArea.top + (0.76 * boxArea.bottom), 0) ,
							   Vector(boxArea.left + (0.655 * boxArea.right), boxArea.top + (0.763 * boxArea.bottom) , 0),
							   Vector(boxArea.left + (0.45 * boxArea.right), boxArea.top + (0.607 * boxArea.bottom) , 0) ,
						       Vector(boxArea.left + (0.58 * boxArea.right), boxArea.top + (0.425 * boxArea.bottom), 0),
						       Vector(boxArea.left + (0.68 * boxArea.right), boxArea.top + (0.413 * boxArea.bottom), 0),
						       Vector(boxArea.left + (0.865 * boxArea.right), boxArea.top + (0.4346 * boxArea.bottom), 0),
						       Vector(boxArea.left + (0.55 * boxArea.right), boxArea.top + (0.6538 * boxArea.bottom), 0),
						       Vector(boxArea.left + (0.655 * boxArea.right), boxArea.top + (0.91 * boxArea.bottom), 0),
							   Vector(boxArea.left + (0.465 * boxArea.right), boxArea.top + (0.967 * boxArea.bottom), 0) };
			for (int i = 0; i < 6; i++) {
				paint->line(arms[i].x, arms[i].y, arms[i + 1].x, arms[i + 1].y, color(255, 255, 255, 255));
			}
			for (int i = 0; i < 2; i++) {
				paint->line(spine[i].x, spine[i].y, spine[i + 1].x, spine[i + 1].y, color(255, 255, 255, 255));
			}
			for (int i = 0; i < 8; i++) {

				paint->line(legs[i].x, legs[i].y, legs[i + 1].x, legs[i + 1].y, color(255, 255, 255, 255));
			}
			
		}

		int lrtb[4] = { 0,0,1,0 };
		for (int i = 0; i < 10; i++) {
			moveable mov = moveables[i];
			if (*mov.position == 0) continue;
			RECT txtArea = paint->textSize(mov.txt.c_str(), Glyphs::feature_esp);
			if (mov.dragging) {

				paint->text(inputmanager.cursor.x + mov.dx, inputmanager.cursor.y + mov.dy, mov.txt.c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text, m_ActivationArea);
				int side = Functions::closestSide(inputmanager.cursor.x, inputmanager.cursor.y, boxArea);
				switch (side) {
				case 1:
					paint->outline(boxArea.left - txtArea.right - 1, boxArea.top + lrtb[0] + txtArea.bottom + 2, txtArea.right, txtArea.bottom, color(255, 255, 255, 255));
					lrtb[0] += txtArea.bottom;
					break;
				case 2:
					paint->outline(boxArea.left + boxArea.right + 1, boxArea.top + txtArea.bottom+ lrtb[1] + 2, txtArea.right, txtArea.bottom, color(255, 255, 255, 255));
					lrtb[1] += txtArea.bottom;
					break;
				case 3:
					paint->outline(boxArea.left + (boxArea.right / 2) - (txtArea.right / 2), boxArea.top - txtArea.bottom - lrtb[2] - 2, txtArea.right, txtArea.bottom, color(255, 255, 255, 255));
					lrtb[2] += txtArea.bottom;
					break;
				case 4:
					paint->outline(boxArea.left + (boxArea.right / 2) - (txtArea.right / 2), boxArea.top + boxArea.bottom + txtArea.bottom + lrtb[3] - 2, txtArea.right, txtArea.bottom, color(255, 255, 255, 255));
					lrtb[3] += txtArea.bottom;
					break;
				}
	
			}
			else {
				
				switch (*mov.position) {
				case 1:
					
					paint->text(boxArea.left - txtArea.right - 1, boxArea.top + lrtb[0] + 2, mov.txt.c_str(), Glyphs::feature_esp, Anchor::TopLeft, variables::gui::colors::text, m_ActivationArea);
					lrtb[0] += txtArea.bottom;
					break;
				case 2:
					paint->text(boxArea.left + boxArea.right + 1, boxArea.top + lrtb[1] + 2, mov.txt.c_str(), Glyphs::feature_esp, Anchor::TopLeft, variables::gui::colors::text, m_ActivationArea);
					lrtb[1] += txtArea.bottom;
					break;
				case 3:
					paint->text(boxArea.left + (boxArea.right / 2) - (txtArea.right / 2), boxArea.top - txtArea.bottom - lrtb[2] - 2, mov.txt.c_str(), Glyphs::feature_esp, Anchor::TopLeft, variables::gui::colors::text, m_ActivationArea);
					lrtb[2] += txtArea.bottom;
					break;
				case 4:
					paint->text(boxArea.left + (boxArea.right / 2) - (txtArea.right / 2), boxArea.top + boxArea.bottom + lrtb[3] + 2, mov.txt.c_str(), Glyphs::feature_esp, Anchor::TopLeft, variables::gui::colors::text, m_ActivationArea);
					lrtb[3] += txtArea.bottom;
					break;
				}
			}
		}

		
	}


	void thinkControl() {

	}
	
	void updateControl(int x_, int y_, bool& dropdownOpen)
	{
		if (!*enable) return;
		RECT m_ActivationArea = { x_ + x , y_ + y, w, h };
		RECT boxArea = { m_ActivationArea.left + (m_ActivationArea.right / 4), m_ActivationArea.top + (m_ActivationArea.bottom / 2) - ((((m_ActivationArea.right / 2) * (isTerrorist ? 1.96 : 2.6))) / 2), m_ActivationArea.right / 2, ((m_ActivationArea.right / 2) * (isTerrorist ? 1.96 : 2.6)) };
		if (*health != 0) {
			RECT healthArea = boxArea;
			switch (*health) {
			case 1:
				healthArea = RECT{ boxArea.left - 5, boxArea.top, 5, boxArea.bottom };
				boxArea.left -= 5;
				break;
			case 2:
				healthArea = RECT{ boxArea.left + boxArea.right + 0, boxArea.top, 5, boxArea.bottom };
				boxArea.left += 5;
				break;
			case 3:
				healthArea = RECT{ boxArea.left, boxArea.top - 4, boxArea.right, 5 };
				boxArea.top -= 3;
				break;
			case 4:
				healthArea = RECT{ boxArea.left, boxArea.top + boxArea.bottom, boxArea.right, 5 };
				boxArea.bottom += 5;
				break;
			}
			if (inputmanager.inArea(healthArea.left, healthArea.top, healthArea.right, healthArea.bottom) && inputmanager.click(VK_LBUTTON)) {
				holdingHealth = true;
			}
			if (holdingHealth && !inputmanager.hold(VK_LBUTTON)) {
				holdingHealth = false;
				int side = Functions::closestSide(inputmanager.cursor.x, inputmanager.cursor.y, boxArea);
				*health = side;
			}
		}
		int lrtb[4] = { 0,0,1,0 };
		for (int i = 0; i < 10; i++) {
			moveable mov = moveables[i];
			if (*mov.position == 0) continue;
			RECT txtArea = paint->textSize(mov.txt.c_str(), Glyphs::feature_esp);
			RECT clickArea = txtArea;
			switch (*mov.position) {
			case 1:

				clickArea = RECT{ boxArea.left - txtArea.right - 1, boxArea.top + lrtb[0] + 2, txtArea.right, txtArea.bottom };
				lrtb[0] += txtArea.bottom;
				break;
			case 2:
				clickArea = RECT{ boxArea.left + boxArea.right + 1, boxArea.top + lrtb[1] + 2, txtArea.right, txtArea.bottom };
				lrtb[1] += txtArea.bottom;
				break;
			case 3:
				clickArea = RECT{ boxArea.left + (boxArea.right / 2) - (txtArea.right / 2), boxArea.top - txtArea.bottom - lrtb[2] - 2, txtArea.right, txtArea.bottom };
				lrtb[2] += txtArea.bottom;
				break;
			case 4:

				clickArea = RECT{ boxArea.left + (boxArea.right / 2) - (txtArea.right / 2), boxArea.top + boxArea.bottom + lrtb[3] + 2, txtArea.right, txtArea.bottom };
				lrtb[3] += txtArea.bottom;
				break;
			}
			if (inputmanager.inArea(clickArea.left, clickArea.top, clickArea.right, clickArea.bottom) && inputmanager.click(VK_LBUTTON)) {
				moveables[i].dx = inputmanager.cursor.x - clickArea.left;
				moveables[i].dy = inputmanager.cursor.x - clickArea.top;
				moveables[i].dragging = true;
			}
			if (mov.dragging) {
				if (!inputmanager.hold(VK_LBUTTON)) {
					moveables[i].dx = moveables[i].dy = 0;
					moveables[i].dragging = false;
					int side = Functions::closestSide(inputmanager.cursor.x, inputmanager.cursor.y, boxArea);
					*moveables[i].position = side;
				}
				else if (!inputmanager.inArea(m_ActivationArea.left, m_ActivationArea.top, m_ActivationArea.right, m_ActivationArea.bottom)) {
					moveables[i].dx = moveables[i].dy = 0;
					moveables[i].dragging = false;

				}
			}
		}
		if (inputmanager.inArea(m_ActivationArea.left, m_ActivationArea.top, m_ActivationArea.right, m_ActivationArea.bottom) && noteAlpha < 254)
			noteAlpha = Functions::clip((float)noteAlpha + 5, 0.0f, 255.f);
		else if (noteAlpha > 1)
			noteAlpha = Functions::clip((float)noteAlpha - 5, 0.0f, 255.f);
	}
	int x, y, w = 200 * Game::menu_scale_factor, h = 216 * Game::menu_scale_factor;
	bool* enable;
	bool isTerrorist;
	bool* visibleOnly;
	bool* skeleton;
	int* chams;
	bool* barrel;
	bool* xqz;
	int* glow;
	int* health;
	int* box;
	bool* boxoutline;
	bool holdingHealth = false;
	float imageAlpha = 255;
	float noteAlpha = 0;
	imageData currentImage = imageData(0,0);
	Box bbox;
	moveable moveables[10] ;
};
class edgeHitboxSelector : public edgeControl
{
public:
	edgeHitboxSelector(std::string n, int x_, int y_, bool* h, bool* u, bool* l, bool* le, bool* ar, int* a, int allow, int controlIncrementer) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = allow; head = h; upper = u; lower = l; legs = le; arms = ar;
		uniqueID = controlIncrementer;
	}
	bool  loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		CHAR m_cReturn[128];
		if (!GetPrivateProfileString(ConfigName.c_str(), m_nName.c_str(), "", m_cReturn, 128, filepath))
			return false;
		for (int i = 0; i < 5; i++) {
			if (m_cReturn[i] != '0' &&
				m_cReturn[i] != '1')
				return false;
		}
		*head = (m_cReturn[0] == '1') ? true : false;
		*upper = (m_cReturn[1] == '1') ? true : false;
		*lower = (m_cReturn[2] == '1') ? true : false;
		*arms = (m_cReturn[3] == '1') ? true : false;
		*legs = (m_cReturn[4] == '1') ? true : false;
		return true;
	}
	bool  saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{

		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		std::string m_cValue = std::to_string(*head) + std::to_string(*upper) + std::to_string(*lower) + std::to_string(*arms) + std::to_string(*legs);
		if (WritePrivateProfileString(ConfigName.c_str(), m_nName.c_str(), m_cValue.c_str(), filepath))
			return true;
		return false;
	}
	void paintControl(int x_, int y_) {

		RECT m_ActivationArea = { x_ + x , y_ + y, w, h };
		paint->rectangle(m_ActivationArea.left, m_ActivationArea.top, m_ActivationArea.right, m_ActivationArea.bottom, Functions::coloradd(variables::gui::colors::background, 30));
		paint->outline(m_ActivationArea.left, m_ActivationArea.top, m_ActivationArea.right, m_ActivationArea.bottom, color(0, 0, 0, 255));


		RECT m_HeadArea = { m_ActivationArea.left + (m_ActivationArea.right * 0.344), m_ActivationArea.top + (m_ActivationArea.bottom * 0.0571), (m_ActivationArea.right * 0.288),(m_ActivationArea.bottom * 0.157) };
		RECT m_UpperArea = { m_ActivationArea.left + (m_ActivationArea.right * 0.3), m_ActivationArea.top + (m_ActivationArea.bottom * 0.214), (m_ActivationArea.right * 0.4166),(m_ActivationArea.bottom * 0.162) };
		RECT m_LowerArea = { m_ActivationArea.left + (m_ActivationArea.right * 0.3), m_ActivationArea.top + (m_ActivationArea.bottom * 0.374), (m_ActivationArea.right * 0.4166),(m_ActivationArea.bottom * 0.214) };
		RECT m_LeftArmArea = { m_ActivationArea.left + (m_ActivationArea.right * 0.211), m_ActivationArea.top + (m_ActivationArea.bottom * 0.2314), (m_ActivationArea.right * 0.0944),(m_ActivationArea.bottom * 0.4228) };
		RECT m_RightArmArea = { m_ActivationArea.left + (m_ActivationArea.right * 0.7166), m_ActivationArea.top + (m_ActivationArea.bottom * 0.2485), (m_ActivationArea.right * 0.0944),(m_ActivationArea.bottom * 0.3457) };
		RECT m_LeftLegArea = { m_ActivationArea.left + (m_ActivationArea.right * 0.3055), m_ActivationArea.top + (m_ActivationArea.bottom * 0.588), (m_ActivationArea.right * 0.205),(m_ActivationArea.bottom * 0.357) };
		RECT m_RightLegArea = { m_ActivationArea.left + (m_ActivationArea.right * 0.55), m_ActivationArea.top + (m_ActivationArea.bottom * 0.5914), (m_ActivationArea.right * 0.21666),(m_ActivationArea.bottom * 0.371) };


		paint->image(m_ActivationArea.left, m_ActivationArea.top, m_ActivationArea.right, m_ActivationArea.bottom, images::csgocharacter);
		if (inputmanager.inArea(m_HeadArea.left, m_HeadArea.top, m_HeadArea.right, m_HeadArea.bottom) || *head)
			paint->rectangle(m_HeadArea.left, m_HeadArea.top, m_HeadArea.right, m_HeadArea.bottom, color(0, 255, 0, *head ? 25 : 15));

		if (inputmanager.inArea(m_UpperArea.left, m_UpperArea.top, m_UpperArea.right, m_UpperArea.bottom) || *upper)
			paint->rectangle(m_UpperArea.left, m_UpperArea.top, m_UpperArea.right, m_UpperArea.bottom, color(0, 255, 0, *upper ? 25 : 15));

		if (inputmanager.inArea(m_LowerArea.left, m_LowerArea.top, m_LowerArea.right, m_LowerArea.bottom) || *lower)
			paint->rectangle(m_LowerArea.left, m_LowerArea.top, m_LowerArea.right, m_LowerArea.bottom, color(0, 255, 0, *lower ? 25 : 15));

		if (inputmanager.inArea(m_LeftArmArea.left, m_LeftArmArea.top, m_LeftArmArea.right, m_LeftArmArea.bottom) || inputmanager.inArea(m_RightArmArea.left, m_RightArmArea.top, m_RightArmArea.right, m_RightArmArea.bottom) || *arms) {
			paint->rectangle(m_LeftArmArea.left, m_LeftArmArea.top, m_LeftArmArea.right, m_LeftArmArea.bottom, color(0, 255, 0, *arms ? 25 : 15));
			paint->rectangle(m_RightArmArea.left, m_RightArmArea.top, m_RightArmArea.right, m_RightArmArea.bottom, color(0, 255, 0, *arms ? 25 : 15));
		}


		if (inputmanager.inArea(m_LeftLegArea.left, m_LeftLegArea.top, m_LeftLegArea.right, m_LeftLegArea.bottom) || inputmanager.inArea(m_RightLegArea.left, m_RightLegArea.top, m_RightLegArea.right, m_RightLegArea.bottom) || *legs) {
			paint->rectangle(m_LeftLegArea.left, m_LeftLegArea.top, m_LeftLegArea.right, m_LeftLegArea.bottom, color(0, 255, 0, *legs ? 25 : 15));
			paint->rectangle(m_RightLegArea.left, m_RightLegArea.top, m_RightLegArea.right, m_RightLegArea.bottom, color(0, 255, 0, *legs ? 25 : 15));
		}
	}


	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen)
	{
		RECT m_ActivationArea = { x_ + x , y_ + y, w, h };
		RECT m_HeadArea = { m_ActivationArea.left + (m_ActivationArea.right * 0.344), m_ActivationArea.top + (m_ActivationArea.bottom * 0.0571), (m_ActivationArea.right * 0.288),(m_ActivationArea.bottom * 0.157) };
		RECT m_UpperArea = { m_ActivationArea.left + (m_ActivationArea.right * 0.3), m_ActivationArea.top + (m_ActivationArea.bottom * 0.214), (m_ActivationArea.right * 0.4166),(m_ActivationArea.bottom * 0.162) };
		RECT m_LowerArea = { m_ActivationArea.left + (m_ActivationArea.right * 0.3), m_ActivationArea.top + (m_ActivationArea.bottom * 0.374), (m_ActivationArea.right * 0.4166),(m_ActivationArea.bottom * 0.214) };
		RECT m_LeftArmArea = { m_ActivationArea.left + (m_ActivationArea.right * 0.211), m_ActivationArea.top + (m_ActivationArea.bottom * 0.2314), (m_ActivationArea.right * 0.0944),(m_ActivationArea.bottom * 0.4228) };
		RECT m_RightArmArea = { m_ActivationArea.left + (m_ActivationArea.right * 0.7166), m_ActivationArea.top + (m_ActivationArea.bottom * 0.2485), (m_ActivationArea.right * 0.0944),(m_ActivationArea.bottom * 0.3457) };
		RECT m_LeftLegArea = { m_ActivationArea.left + (m_ActivationArea.right * 0.3055), m_ActivationArea.top + (m_ActivationArea.bottom * 0.588), (m_ActivationArea.right * 0.205),(m_ActivationArea.bottom * 0.357) };
		RECT m_RightLegArea = { m_ActivationArea.left + (m_ActivationArea.right * 0.55), m_ActivationArea.top + (m_ActivationArea.bottom * 0.5914), (m_ActivationArea.right * 0.21666),(m_ActivationArea.bottom * 0.371) };


		paint->image(m_ActivationArea.left, m_ActivationArea.top, m_ActivationArea.right, m_ActivationArea.bottom, images::csgocharacter);
		if (inputmanager.inArea(m_HeadArea.left, m_HeadArea.top, m_HeadArea.right, m_HeadArea.bottom) && inputmanager.click(VK_LBUTTON))
			* head = !*head;

		if (inputmanager.inArea(m_UpperArea.left, m_UpperArea.top, m_UpperArea.right, m_UpperArea.bottom) && inputmanager.click(VK_LBUTTON))
			* upper = !*upper;

		if (inputmanager.inArea(m_LowerArea.left, m_LowerArea.top, m_LowerArea.right, m_LowerArea.bottom) && inputmanager.click(VK_LBUTTON))
			* lower = !*lower;

		if (inputmanager.inArea(m_LeftArmArea.left, m_LeftArmArea.top, m_LeftArmArea.right, m_LeftArmArea.bottom) && inputmanager.click(VK_LBUTTON))
			* arms = !*arms;

		if (inputmanager.inArea(m_RightArmArea.left, m_RightArmArea.top, m_RightArmArea.right, m_RightArmArea.bottom) && inputmanager.click(VK_LBUTTON))
			* arms = !*arms;

		if (inputmanager.inArea(m_LeftLegArea.left, m_LeftLegArea.top, m_LeftLegArea.right, m_LeftLegArea.bottom) && inputmanager.click(VK_LBUTTON))
			* legs = !*legs;

		if (inputmanager.inArea(m_RightLegArea.left, m_RightLegArea.top, m_RightLegArea.right, m_RightLegArea.bottom) && inputmanager.click(VK_LBUTTON))
			* legs = !*legs;


	}
	int x, y, w = 180 * Game::menu_scale_factor, h = 330 * Game::menu_scale_factor;
	bool* head;
	bool* upper;
	bool* lower;
	bool* arms;
	bool* legs;
};

class edgeSelectionBox : public edgeControl
{
public:
	edgeSelectionBox(std::string n, int x_, int y_, std::vector<std::string> items_, int* a, int allow, int* v, int controlIncrementer) {
		name = n; x = x_; y = y_; allowedVisible = a; allowedVisibleComparitor = allow; value = v; items = items_; id = 2;
		uniqueID = controlIncrementer;
	}
	bool  loadValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		int m_cReturn = GetPrivateProfileInt(ConfigName.c_str(), m_nName.c_str(), 0, filepath);
		*value = m_cReturn;
		return true;
	}
	bool  saveValue(const char* filepath, std::string ConfigName, std::string window, std::string cluster, std::string page)
	{
		int m_cValue = *value;
		std::string m_nName = window + xorStr("->") + cluster + xorStr("->") + page + xorStr("->") + name + xorStr("->") + std::to_string(allowedVisibleComparitor);
		if (WritePrivateProfileString(ConfigName.c_str(), m_nName.c_str(), std::to_string(m_cValue).c_str(), filepath))
			return true;
		return false;
	}
	void paintControl(int x_, int y_) {

		RECT m_ActivationArea = { x_ + x , y_ + y, w, h };
		int m_iValue = *value;
		paint->rectangle(m_ActivationArea.left, m_ActivationArea.top, m_ActivationArea.right, m_ActivationArea.bottom, Functions::coloradd(variables::gui::colors::background, 30));
		float m_TextSpacing = w * 0.04285714285;
		RECT m_TextValueArea = paint->textSize(items[m_iValue].c_str(), Glyphs::menu_control);
		paint->text(m_ActivationArea.left + m_TextSpacing, m_ActivationArea.top + (m_ActivationArea.bottom / 2) - (m_TextValueArea.bottom / 2), items[m_iValue].c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text);

		if (m_bOpen) {
			RECT m_OpenArea = { m_ActivationArea.left, m_ActivationArea.top + m_ActivationArea.bottom, m_ActivationArea.right, min(items.size(), m_iMaximumOpen) * m_ActivationArea.bottom + (m_ActivationArea.bottom / 2) };
			for (int i = 0; i < items.size(); i++) {
				RECT m_Area = { m_OpenArea.left, m_OpenArea.top - scrollY + (m_ActivationArea.bottom * i), m_OpenArea.right/*scroll.w*/, m_ActivationArea.bottom };
				if (m_Area.top + m_Area.bottom < m_OpenArea.top) continue;
				if (m_Area.top > m_OpenArea.top + m_OpenArea.bottom) continue;

				color m_cBack = variables::gui::colors::primary;
				if (i == m_iValue) {
					if (inputmanager.inArea(m_Area.left, m_Area.top, m_Area.right, m_Area.bottom))
						m_cBack = Functions::coloradd(variables::gui::colors::primary, 5);
				}
				else {
					if (inputmanager.inArea(m_Area.left, m_Area.top, m_Area.right, m_Area.bottom))
						m_cBack = Functions::coloradd(variables::gui::colors::primary, -10);
					else
						m_cBack = Functions::coloradd(variables::gui::colors::primary, -20);
				}
				RECT m_Clip = Functions::boundArea(RECT{ (LONG)m_Area.left,(LONG)m_Area.top , (LONG)m_Area.right, (LONG)m_Area.bottom }, RECT{ (LONG)m_OpenArea.left,(LONG)m_OpenArea.top, (LONG)m_OpenArea.right, (LONG)m_OpenArea.bottom });
				RECT m_ClipText = RECT{ (LONG)m_OpenArea.left,(LONG)m_OpenArea.top, (LONG)m_OpenArea.right, (LONG)m_OpenArea.bottom };
				paint->rectangle(m_Clip.left, m_Clip.top, m_Clip.right, m_Clip.bottom, m_cBack);
				RECT m_TextArea = paint->textSize(items[i].c_str(), Glyphs::menu_control);
				paint->text(m_Area.left + m_TextSpacing, m_Area.top + (m_Area.bottom / 2) - (m_TextArea.bottom / 2), items[i].c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text, m_ClipText);
			}
			if (items.size() * m_ActivationArea.bottom > m_OpenArea.bottom)
				scroll.drawScrollBar(scrollY, m_OpenArea.left + m_OpenArea.right - 5, m_OpenArea.top, 5, m_OpenArea.bottom, items.size() * m_ActivationArea.bottom + (m_ActivationArea.bottom / 2), m_OpenArea.bottom);
		}
		RECT textSize = paint->textSize(name.c_str(), Glyphs::menu_control);
		paint->text(x_ + x, y_ + y - textSize.bottom - 3, name.c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text);


	}
	void thinkControl() {

	}
	void updateControl(int x_, int y_, bool& dropdownOpen)
	{
		RECT m_ActivationArea = { x_ + x , y_ + y, w, h };
		int m_iValue = *value;
		if (inputmanager.click(VK_LBUTTON)) {

			if (inputmanager.inArea(m_ActivationArea.left, m_ActivationArea.top, m_ActivationArea.right, m_ActivationArea.bottom)) {
				m_bOpen = !m_bOpen;
				dropdownOpen = m_bOpen;
			}
			else if (!inputmanager.inArea(m_ActivationArea.left, m_ActivationArea.top, m_ActivationArea.right, m_ActivationArea.bottom * (items.size() + 1))) {
				dropdownOpen = false;
				m_bOpen = false;
			}
		}

		if (m_bOpen) {
			RECT m_OpenArea = { m_ActivationArea.left, m_ActivationArea.top + m_ActivationArea.bottom + 1, m_ActivationArea.right, min(items.size(), m_iMaximumOpen) * m_ActivationArea.bottom + (m_ActivationArea.bottom / 2) };
			if (items.size() * m_ActivationArea.bottom > m_OpenArea.bottom) {
				scroll.updateScrollBar(scrollY, m_OpenArea.left + m_OpenArea.right - 5, m_OpenArea.top, 5, m_OpenArea.bottom, items.size() * m_ActivationArea.bottom + (m_ActivationArea.bottom / 2), m_OpenArea.bottom, true);
			}
			for (int i = 0; i < items.size(); i++) {
				RECT m_Area = { m_OpenArea.left, m_OpenArea.top - scrollY + (m_ActivationArea.bottom * i) + (m_ActivationArea.bottom / 4), m_OpenArea.right - 10 /*scroll.w*/ - 2, m_ActivationArea.bottom };
				RECT m_Clip = Functions::boundArea(RECT{ (LONG)m_Area.left,(LONG)m_Area.top, (LONG)m_Area.right, (LONG)m_Area.bottom }, RECT{ (LONG)m_OpenArea.left,(LONG)m_OpenArea.top, (LONG)m_OpenArea.right, (LONG)m_OpenArea.bottom });
				if (m_Area.top + m_Area.bottom < m_OpenArea.top) continue;
				if (m_Area.top > m_OpenArea.top + m_OpenArea.bottom) continue;
				if (i == m_iValue) continue;
				if (inputmanager.inArea(m_Clip.left, m_Clip.top, m_Clip.right - 5, m_Clip.bottom) && inputmanager.click(VK_LBUTTON)) {
					m_iValue = i;
					m_bOpen = false;
				}
			}
			if (!inputmanager.inArea(m_OpenArea.left, m_OpenArea.top, m_OpenArea.right, m_OpenArea.bottom) && !inputmanager.inArea(m_ActivationArea.left, m_ActivationArea.top, m_ActivationArea.right, m_ActivationArea.bottom) && inputmanager.click(VK_LBUTTON)) {
				m_bOpen = false;
			}
		}
		*value = Functions::clip(m_iValue, 0, (int)(items.size() - 1));
	}
	int x, y, w = boxMenuWidth * Game::menu_scale_factor, h = 30 * Game::menu_scale_factor;
	float m_iMaximumOpen = 9;
	std::string name;
	int* value;
	std::vector<std::string> items;
	bool m_bOpen = false;
	edgeVerticleScrollbar scroll;
	int scrollY = 0;
};
class edgePage
{
public:
	edgePage(std::string n, color c, int textx, int texty, int* x_, int* y_, int* w_, int* h_, float y_add, imageData* img, bool extra, bool  skip) {
		x = x_; y = y_; w = w_; h = h_;
		name = n;
		pageColor = c;
		extraLarge = extra;
		textX = textx;
		textY = texty;
		shouldBeSkipped = skip;
		image = img;
		yPadScale = y_add;
	}
	void loop() {


	}
	void paintPage() {

		if (lockedPage) return;
		std::vector<int> dropBoxes = {};

		for (int j = 0; j < controls.size(); j++) {
			std::shared_ptr <edgeControl> ctrl = controls[j];
			if (*ctrl->allowedVisible != ctrl->allowedVisibleComparitor) continue;

			if (ctrl->id == 2) {
				std::shared_ptr<edgeSelectionBox> box = std::dynamic_pointer_cast<edgeSelectionBox>(ctrl);
				if (box->m_bOpen) {
					dropBoxes.push_back(j);
					continue;
				}
			}

			if (ctrl->uniqueID != -1)
				paint->text(ctrl->x + *x, ctrl->y + *y + (yPadScale * (*h)), controls[j]->name.c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text);
			RECT textSize = paint->textSize(controls[j]->name.c_str(), Glyphs::menu_control);
			ctrl->paintControl(*x, *y + (yPadScale * (*h)) + (ctrl->uniqueID != -1 ? textSize.bottom + 3 : 0));

		}

		for (int i = 0; i < dropBoxes.size(); i++) {
			std::shared_ptr <edgeControl> ctrl = controls[dropBoxes[i]];
			if (!ctrl) continue;
			if (*ctrl->allowedVisible != ctrl->allowedVisibleComparitor) continue;
			if (ctrl->uniqueID != -1)
				paint->text(ctrl->x + (*x), ctrl->y + (*y) + (yPadScale * (*h)), ctrl->name.c_str(), Glyphs::menu_control, Anchor::TopLeft, variables::gui::colors::text);
			RECT textSize = paint->textSize(ctrl->name.c_str(), Glyphs::menu_control);
			ctrl->paintControl(*x, *y + (yPadScale * (*h)) + (ctrl->uniqueID != -1 ? textSize.bottom + 3 : 0));

		}
		if (dropBoxes.size() <= 0 && dropdownOpen) {
			dropdownOpen = false;
		}

	}
	void updatePage() {
		if (lockedPage) return;
		for (int i = 0; i < controls.size(); i++) {
			std::shared_ptr <edgeControl> control = controls[i];
			if (!control) continue;
			if (*control->allowedVisible != control->allowedVisibleComparitor) continue;
			if (control->id == 2) {
				std::shared_ptr<edgeSelectionBox> box = std::dynamic_pointer_cast<edgeSelectionBox>(control);
				if (dropdownOpen && !box->m_bOpen) continue;
			}
			else {
				if (dropdownOpen) continue;
			}

			RECT textSize = paint->textSize(control->name.c_str(), Glyphs::menu_control);
			control->updateControl(*x, *y + (yPadScale * (*h)) + (control->uniqueID != -1 ? textSize.bottom + 3 : 0), dropdownOpen);
		}

	}
	int* x = 0, *y = 0, *w = 0, *h = 0;
	float yPadScale = 1;
	int textX = 0;
	int textY = 0;
	int imageWidth = 40 * Game::menu_scale_factor;
	int groupTextPadX = 10 * Game::menu_scale_factor;
	bool extraLarge = false;
	std::string name;
	std::string inheritGroupName = "";
	bool shouldBeSkipped = false;
	int pageColorAlpha = 0;
	bool lockedPage = false;
	color pageColor = color(100, 100, 100, 255);
	std::vector<std::shared_ptr<edgeControl>> controls;
	bool dropdownOpen = false;
	imageData* image;
};

class edgeCluster
{
public:
	edgeCluster(std::string name_, bool* vis) {
		name = name_;
		allowedVisible = vis;
	}
	std::string name;
	bool* allowedVisible;
	int selectedPage = 0;
	std::vector<std::shared_ptr<edgePage>> pages;
	int width = 245 * Game::menu_scale_factor;
	int maxPerWidth = 2;
};
class edgeWindow
{
public:
	edgeWindow(std::string name_, bool* vis) {
		name = name_;
		allowedVisible = vis;
	}
	void updateWindow() {

		if (focusedCluster < 0 || focusedCluster >= clusters.size())
			focusedCluster = 0;


		RECT tabArea = { x + width - (0.2 * grabHeight) - (width * 0.45), y + (grabHeight / 2) - (grabHeight * 0.3), (width * 0.45), grabHeight * 0.6 };
		int tabWidth = tabArea.right / clusters.size();

		for (int i = 0; i < clusters.size(); i++) {
			std::shared_ptr <edgeCluster> cluster = clusters[i];
			if (!cluster) continue;
			RECT area = { tabArea.left + (i * tabWidth), tabArea.top, tabWidth, tabArea.bottom };
			if (inputmanager.inArea(area.left, area.top, area.right, area.bottom) && inputmanager.click(VK_LBUTTON)) {
				focusedCluster = i;
			}
		}


		RECT subTabArea = { x, y + grabHeight + grabBarPad + pageTabsPad, width, pageTabsHeight };
		float subTabWidth = (float)subTabArea.right / (float)clusters[focusedCluster]->pages.size();
		for (int i = 0; i < clusters[focusedCluster]->pages.size(); i++) {
			/*Tab*/
			if (clusters[focusedCluster]->selectedPage != i) {
				std::shared_ptr <edgePage> page = clusters[focusedCluster]->pages[i];
				RECT area = { subTabArea.left + (i * subTabWidth), subTabArea.top, subTabWidth + 1, subTabArea.bottom };
				if (inputmanager.inArea(area.left, area.top, area.right, area.bottom) && inputmanager.click(VK_LBUTTON))
					clusters[focusedCluster]->selectedPage = i;
			}
			if (clusters[focusedCluster]->pages[clusters[focusedCluster]->selectedPage] && i == clusters[focusedCluster]->selectedPage) {
				clusters[focusedCluster]->pages[clusters[focusedCluster]->selectedPage]->updatePage();

			}
			/*Page*/
		}
	}
	void paintWindow() {
		if (focusedCluster < 0 || focusedCluster >= clusters.size())
			focusedCluster = 0;

		paint->rectangle(x, y, width, height - pageBottomHeight, variables::gui::colors::background); // Main Body 
		RECT redArea = paint->textSize(xorStr("RED "), Glyphs::menu_grabtext);
		paint->text(x + ((grabHeight - redArea.top) / 2), y + (grabHeight / 2) - (redArea.bottom / 2), xorStr("RED "), Glyphs::menu_grabtext, Anchor::TopLeft, variables::gui::colors::primary);
		paint->text(x + ((grabHeight - redArea.top) / 2) + redArea.right, y + (grabHeight / 2) - (redArea.bottom / 2), xorStr("EYE CHEATS V5"), Glyphs::menu_grabtext, Anchor::TopLeft, variables::gui::colors::text);
		paint->rectangle(x, y + grabHeight, width, grabBarPad, Functions::coloradd(variables::gui::colors::background, variables::gui::colors::lighterBackgroundHuePlus)); //Padded bit
		paint->rectangle(x, y + grabHeight, width, grabBarPad, Functions::coloradd(variables::gui::colors::background, variables::gui::colors::lighterBackgroundHuePlus)); // Footer



		RECT tabArea = { x + width - (0.2 * grabHeight) - (width * 0.45), y + (grabHeight / 2) - (grabHeight * 0.3), (width * 0.45), grabHeight * 0.6 };
		int tabWidth = tabArea.right / clusters.size();

		for (int i = 0; i < clusters.size(); i++) {
			std::shared_ptr <edgeCluster> cluster = clusters[i];
			if (!cluster) continue;
			RECT area = { tabArea.left + (i * tabWidth), tabArea.top, tabWidth, tabArea.bottom };
			paint->rectangle(area.left, area.top, area.right, area.bottom, Functions::coloradd(variables::gui::colors::background, variables::gui::colors::lighterBackgroundHuePlus));
			paint->text(area.left + (area.right / 2), area.top + (area.bottom / 2), cluster->name.c_str(), Glyphs::menu_tab, Anchor::Center, variables::gui::colors::text);
			color edgeColor = Functions::coloradd(variables::gui::colors::background, variables::gui::colors::lighterBackgroundHuePlus);
			if (inputmanager.inArea(area.left, area.top, area.right, area.bottom) && i != focusedCluster) {
				paint->line(area.left, area.top - 1, area.left + area.right, area.top - 1, Functions::replaceAlpha(variables::gui::colors::primary, 20));
			}
			else if (i == focusedCluster)
				paint->line(area.left, area.top - 1, area.left + area.right, area.top - 1, variables::gui::colors::primary);
		}


		
		RECT subTabArea = { x, y + grabHeight + grabBarPad + pageTabsPad, width, pageTabsHeight };
		
		float subTabWidth = (float)subTabArea.right / (float)clusters[focusedCluster]->pages.size();
		for (int i = 0; i < clusters[focusedCluster]->pages.size(); i++) {
			std::shared_ptr <edgePage> page = clusters[focusedCluster]->pages[i];
			if (!page) continue;
			RECT area = { subTabArea.left + (i * subTabWidth), subTabArea.top, subTabWidth + 1, subTabArea.bottom };
			color edgeColor = Functions::coloradd(variables::gui::colors::background, variables::gui::colors::lighterBackgroundHuePlus);
			if (i == clusters[focusedCluster]->selectedPage) {
				edgeColor = variables::gui::colors::primary;
				page->paintPage();
			}
			if (inputmanager.inArea(area.left, area.top, area.right, area.bottom)) {
				page->pageColorAlpha = Functions::clip(page->pageColorAlpha + 10, 0, 255);
			}
			else {
				page->pageColorAlpha = Functions::clip(page->pageColorAlpha - 10, 0, 255);
			}
			paint->rectangle(area.left, area.top, area.right, area.bottom, edgeColor);
			paint->rectangle(area.left, area.top, area.right, area.bottom, Functions::replaceAlpha(variables::gui::colors::primary, page->pageColorAlpha));
			paint->text(area.left + (area.right / 2), area.top + (area.bottom / 2), page->name.c_str(), Glyphs::menu_subtab, Anchor::Center, variables::gui::colors::text);

			/*Page*/
		}
		

	}


	int width = 750 * Game::menu_scale_factor, height = 550 * Game::menu_scale_factor, x = (Game::m_iWidth / 2) - (width / 2), y = (Game::m_iHeight / 2) - (height / 2), disX = 0, disY = 0, grabHeight = 70 * Game::menu_scale_factor;
	int grabBarPad = 7 * Game::menu_scale_factor;
	int pageTabsPad = 10 * Game::menu_scale_factor;
	int pageTabsHeight = 42 * Game::menu_scale_factor;
	int pageBottomHeight = 20 * Game::menu_scale_factor;
	int pageHorizontalScroll = 0;
	edgeHorizontalScrollbar horizontalSplashBar;
	edgePortableTextbox searchbox;
	std::string searchboxresult = "";
	std::string previoussearchboxresult = "";
	int pageVerticleScroll = 0;
	std::vector<edgeCluster*> pageList;
	std::vector<edgeCluster*> sortedPageList;
	int listXPad = 24 * Game::menu_scale_factor, listYPad = 80, listWidth = 270 * Game::menu_scale_factor, itemPad = 45 * Game::menu_scale_factor, listSize = 37 * Game::menu_scale_factor;
	edgeVerticleScrollbar verticleSplashBar;

	bool bHolding = false, bFocused = false;;
	std::string name = xorStr("");
	std::string version = xorStr("Build version: Public build v4");
	bool* allowedVisible;
	int focusedCluster = 0;
	std::vector< std::shared_ptr<edgeCluster>> clusters;


	std::vector<edgePage*> specialPages;
	int specialPagePad = 3;
};
namespace FU {
	extern void FullUpdate();
	extern void null();
}
namespace MENU {
	extern void updateScaleFactor();
}
namespace DEBUG {
	extern void activate();
}
namespace SETTINGS {

	extern std::string path;
	extern std::vector <std::string> Configurations;
	extern std::string m_sName;
	extern std::string m_sDefaultName;
	extern int m_iSelectedIndex;
	extern bool FileExists(const char* _path);
	extern void setupPath();
	extern void SaveSetting();
	extern std::vector<std::string> get_all_files_names_within_folder(std::string folder);
	extern bool ConfigurationFileAlreadyExists(std::string name);
	extern void RefreshSettings();
	extern void  NewConfiguration();
	extern void LoadSetting();
	extern void RenameConfig();
	extern void DeleteConfiguration(std::string name);
	extern void DeleteConfiguration();

	extern void LoadConfiguration(std::string name);
	extern void LoadConfigurationz();
	extern void SetDefault();
	extern void SaveConfiguration(std::string name);
	extern void SaveConfigurationz();
}
class edgeGUI
{
public:
	~edgeGUI() {

	}
	bool runUpdateMessage() {

		std::vector<std::string> list = {xorStr("Fixed crashing upon injection") , xorStr("Enjoy :)"), xorStr("VAC protection updated v2"), xorStr(""),xorStr("IF YOU ARE CRASHING PLEASE VISIT THE LINK:"), xorStr("redeyecheats.com/threads/cheat-crash-feedback.31560/")};
		std::shared_ptr<popupMessage> newMessage = std::make_unique<popupMessage>(xorStr("What's New?"), list);
		alertMessages.push_back(newMessage);
		return true;
	}
	bool runUpdateCheck() {
		if (SETTINGS::path == "") {
			char* appdata = getenv(xorStr("APPDATA"));
			std::string dir = appdata; dir += xorStr("\\VPXA_3432\\");
			SETTINGS::path = dir;
		}
		std::string m_sConfiguration = SETTINGS::path + xorStr("x37nawdui.ini");
		if (!SETTINGS::FileExists(m_sConfiguration.c_str())) {
			std::ofstream a(m_sConfiguration);
			a.close();
			if (!WritePrivateProfileString(xorStr("data"), xorStr("version"), std::to_string(currentVersion).c_str(), m_sConfiguration.c_str()))
				return false;
			runUpdateMessage();
			return true;
		}
		CHAR m_cReturn[128];
		if (!GetPrivateProfileString(xorStr("data"), xorStr("version"), "", m_cReturn, 128, m_sConfiguration.c_str()))
			return false;
		
		double retrivedVersion = std::stof(m_cReturn);\
		if (currentVersion > retrivedVersion) {
			runUpdateMessage();
			if (!WritePrivateProfileString(xorStr("data"), xorStr("version"), std::to_string(currentVersion).c_str(), m_sConfiguration.c_str()))
				return false;
		}
		return true;
	}
	void loop() {
		
		if (!bSetup)
			setup();
		if (inputmanager.click(VK_INSERT)) {
			variables::gui::bShowMainGui = !variables::gui::bShowMainGui;
			interfaceManager::inputsys->EnableInput(!variables::gui::bShowMainGui);
		}
		
		updateGUI();
		paintGUI();
		for (int i = 0; i < alertMessages.size(); i++) {
			alertMessages[i]->updateMessage();
			alertMessages[i]->paintMessage();
		}
		for (int i = 0; i < alertMessages.size(); i++) {
			if (!alertMessages[i]->open)
				alertMessages.erase(alertMessages.begin() + i);
		}
	}
	bool createWindow(std::string name, bool* showPointer) {
		temporaryWindow = std::make_unique<edgeWindow>(name, showPointer);
		return true;
	}
	bool finalizeWindow() {

		const char* letterMap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		int letterIndex = 0;
		while (letterIndex < 27) {
			std::string name(1, letterMap[letterIndex]);
			edgeCluster* tempCluster = new edgeCluster(name, temporaryWindow->allowedVisible);
			for (int i = 0; i < temporaryWindow->clusters.size(); i++) {
				for (int j = 0; j < temporaryWindow->clusters[i]->pages.size(); j++) {
					std::shared_ptr<edgePage> page = temporaryWindow->clusters[i]->pages[j];
					if (page->name == "") continue;
					if (toupper(page->name[0]) == letterMap[letterIndex])
						tempCluster->pages.push_back(page);
				}
			}
			if (tempCluster->pages.size() > 0)
				temporaryWindow->pageList.push_back(tempCluster);
			letterIndex++;
		}
		Windows.push_back(temporaryWindow);
		return true;
	}
	bool createCluster(std::string name, bool* v) {
		tempoaryCluster = std::make_shared<edgeCluster>(name, v);
		return true;
	}
	bool finalizeCluster() {
		temporaryWindow->clusters.push_back(tempoaryCluster);


		return true;
	}
	bool createPage(std::string name, color c, int textX, int textY, imageData* image = NULL, std::string additional = "", bool extraLarge = false) {
		float yAdd = (float)(temporaryWindow->grabHeight + temporaryWindow->grabBarPad + temporaryWindow->pageTabsPad + temporaryWindow->pageTabsHeight) / (float)temporaryWindow->height;
		tempoaryPage = std::make_unique<edgePage>(name, c, textX, textY, &temporaryWindow->x, &temporaryWindow->y, &temporaryWindow->width, &temporaryWindow->height, yAdd, image, extraLarge, false);
		tempoaryPage->inheritGroupName = tempoaryCluster->name;
		

		return true;
	}
	bool finalizePage() {
		tempoaryCluster->pages.push_back(tempoaryPage);
		return true;
	}
	bool addCheckbox(std::string name, int x, int y, bool* value, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeCheckbox>(name, x, y, value, allowed, a, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	bool addCheckbox(std::string name, int x, int y, bool* value, bool* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeCheckbox>(name, x, y, value, allowed, (int*)a, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	bool addSlider(std::string name, int x, int y, int w, int* value, int min, int max, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeSlider>(name, x, y, w, a, allowed, value, max, min, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	bool addSlider(std::string name, int x, int y, int* value, int min, int max, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeSlider>(name, x, y, -1, a, allowed, value, max, min, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	bool addSliderFloat(std::string name, int x, int y, float width, float* value, float min, float max, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeSliderFloat>(name, x, y, width, a, allowed, value, max, min, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	bool addSliderFloat(std::string name, int x, int y, float* value, float min, float max, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeSliderFloat>(name, x, y,-1,  a, allowed, value, max, min, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	bool addKeybinder(std::string name, int x, int y, int* value, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeKeybinder>(name, x, y, value, a, allowed, controlIncrementer, false));
		controlIncrementer++;
		return true;
	}
	bool addKeybinderB(std::string name, int x, int y, int* value, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeKeybinder>(name, x, y, value, a, allowed, controlIncrementer, true));
		controlIncrementer++;
		return true;
	}
	bool addTextbox(std::string name, int x, int y, std::string* value, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeTextbox>(name, x, y, value, a, allowed, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	bool addNumberTextbox(std::string name, int x, int y, int* value, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeNumberTextbox>(name, x, y, value, a, allowed, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	bool addHitboxSelector(std::string name, int x, int y, bool* head, bool* upper, bool* lower, bool* legs, bool* arms, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeHitboxSelector>(name, x, y, head, upper, lower, legs, arms, a, allowed, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	bool addESPSelector(std::string name, int x, int y, bool t, bool* enable_, bool* visibleOnly_, int* health_, int* box_, bool* boxoutline_, int* name_, int* weapon_, int* money_, bool* skeleton_, int* distance_, int* ammunition_, int* chams_, bool* barrel_, bool* xqz_, int* glow_, int* reloadwarning_, int* scopedWarning_, int* defuseWarning_, int* hostageWarning_, int* HelmetESP_, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeESPSelector>(name, x, y, a, allowed, controlIncrementer, t, enable_, visibleOnly_, health_, box_, boxoutline_, name_, weapon_, money_, skeleton_, distance_, ammunition_, chams_, barrel_, xqz_, glow_, reloadwarning_, scopedWarning_, defuseWarning_, hostageWarning_, HelmetESP_));
		controlIncrementer++;
		return true;
	}
	bool addSearchableListbox(std::string name, int x, int y, int height, std::vector<std::string> items, int* output, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeSearchableListbox>(name, x, y, height, items, output, a, allowed, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	bool addListbox(std::string name, int x, int y, int height, std::vector<std::string> items, int* output, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeListbox>(name, x, y, height, items, output, a, allowed, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	bool addListboxAdjustable(std::string name, int x, int y, int height, std::vector<std::string>* items, int* output, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeListboxAdjustable>(name, x, y, height, items, output, a, allowed, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	// edgeColorPicker
	bool addColorPicker(std::string name, int x, int y, color* output, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared <edgeColorPicker>(name, x, y, output, a, allowed, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	bool addTabSelector(int x, int y, int* w, int* h, std::vector<std::string> v, int* output, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeTabSelector>(x, y, w, h, v, output, a, allowed));
		return true;
	}
	bool addLabel(std::string name, int x, int y, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeLabel>(name, x, y, a, allowed));
		return true;
	}
	bool addLabelValue(std::string name, int x, int y, int* value, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeLabelValue>(name, x, y, value, a, allowed));
		return true;
	}
	bool addGraph(std::string name, int x, int y, std::vector<int>* data, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeGraph>(name, x, y, data, a, allowed, controlIncrementer));
		return true;
	}
	bool addButton(std::string name, int x, int y, int w, edgeButton::fn function, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared <edgeButton>(name, x, y, w, function, a, allowed, controlIncrementer));
		controlIncrementer++;
		return true;
	}

	bool addSelectionBox(std::string name, int x, int y, std::vector<std::string> i, int* value, bool* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared <edgeSelectionBox>(name, x, y, i, (int*)a, allowed, value, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	bool addSelectionCheck(std::string name, int x, int y, int* value, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeSelectionCheckbox>(name, x, y, value, allowed, a, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	bool addSelectionBox(std::string name, int x, int y, std::vector<std::string> i, int* value, int* a, int allowed = 1) {
		tempoaryPage->controls.push_back(std::make_shared<edgeSelectionBox>(name, x, y, i, a, allowed, value, controlIncrementer));
		controlIncrementer++;
		return true;
	}
	void updateGUI() {
		if (Windows.size() <= 0) return;
		if (inputmanager.click(VK_LBUTTON)) {
			int win = -1;
			for (int i = (Windows.size() - 1); i >= 0; i--) {
				std::shared_ptr <edgeWindow> window = Windows[i];
				if (!window) continue;
				if (!*window->allowedVisible) continue;
				if (inputmanager.inArea(window->x, window->y, window->width, window->height))
					win = i;
			}
			if (win != -1)
				std::rotate(Windows.begin(), Windows.begin() + win, Windows.end());
		}

		for (int i = 0; i < Windows.size(); i++) {
			std::shared_ptr <edgeWindow> window = Windows[i];
			if (!window) return;
			if (!*window->allowedVisible) continue;
			if (!window->bHolding) {
				window->disX = inputmanager.cursor.x - window->x;
				window->disY = inputmanager.cursor.y - window->y;
			}

			if (i == 0) {
				window->bFocused = true;
				if (inputmanager.click(VK_LBUTTON) && (inputmanager.inArea(window->x, window->y, window->width, window->grabHeight))) {
					window->bHolding = true;
				}
				if (window->bHolding) {
					if (inputmanager.hold(VK_LBUTTON)) {
						window->x = inputmanager.cursor.x - window->disX;
						window->y = inputmanager.cursor.y - window->disY;
					}
					else
						window->bHolding = false;
				}
			}
			else {
				window->bFocused = false;
			}
			for (int j = 0; j < window->clusters.size(); j++) {
				std::shared_ptr<edgeCluster> cluster = window->clusters[j];
				if (!cluster) continue;
				for (int k = 0; k < cluster->pages.size(); k++) {
					std::shared_ptr< edgePage>page = cluster->pages[k];
					if (!page) continue;
					for (int ee = 0; ee < page->controls.size(); ee++) {
						std::shared_ptr <edgeControl> ctrl = page->controls[ee];
						if (!ctrl) continue;
						ctrl->thinkControl();
					}
				}
			}
			window->updateWindow();
		}
	}
	void paintGUI() {
		for (int i = (Windows.size() - 1); i >= 0; i--) {
			std::shared_ptr < edgeWindow> window = Windows[i];
			if (!window) return;
			if (!*window->allowedVisible) continue;
			window->paintWindow();
			if (i != 0)
				paint->rectangle(window->x, window->y, window->width, window->height, color(255, 255, 255, 25));

		}
	}
	int XfromIndex(float index) {
		int bufferPad = ((float)temporaryWindow->width * 0.05);
		int xPosition = (bufferPad + (((boxMenuWidth / 2) + bufferPad) * index)) * Game::menu_scale_factor;

		return xPosition;
	}
	int YEnableSpacePos() {


		return (-temporaryWindow->pageTabsHeight - (temporaryWindow->pageTabsPad) * 0.75);
	}

	int YfromIndex(float index) {

		int h = temporaryWindow->height - temporaryWindow->grabHeight - temporaryWindow->grabBarPad - temporaryWindow->pageTabsPad - temporaryWindow->pageTabsHeight - temporaryWindow->pageBottomHeight;
		float yBuffer = (temporaryWindow->width * 0.05);
		float ySpacing = (h / 8);

		return ((float)(temporaryWindow->width * 0.05) + (index * (float)(h / 8)));
	}
	int MaximumWidth() {
		float yBuffer = (temporaryWindow->width * 0.05);
		return temporaryWindow->width - (2 * yBuffer);
	}
	void setup() {
		SETTINGS::setupPath();
		runUpdateCheck();
		createWindow(xorStr("Red Eye Cheats V5"), &variables::gui::bShowMainGui); {
			createCluster(xorStr("Aimbot"), &variables::gui::bAlwaysTrue); {

				createPage(xorStr("Rifles"), color(237, 41, 57), XfromIndex(0), YfromIndex(0), NULL, "", true);
				{
					float buffer = 0.3;
					addTabSelector(0, 0, &temporaryWindow->width, &temporaryWindow->pageTabsHeight, {
						xorStr("General"),
						xorStr("Recoil Control"),
						xorStr("Silent"),
						/*xorStr("Triggerbot")*/ }, &variables::aimbot::rifles::selectedTab, &variables::gui::bMenuConstant);




					/*=======================GENERAL==================================*/
					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::rifles::Enabled, &variables::aimbot::rifles::selectedTab, 0);
					addCheckbox(xorStr("Nearest Hitbox"), XfromIndex(1), YfromIndex(0 + buffer), &variables::aimbot::rifles::humanization::nearest, &variables::aimbot::rifles::selectedTab, 0);
					addCheckbox(xorStr("Enemies"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::rifles::enemies, &variables::aimbot::rifles::selectedTab, 0);
					addCheckbox(xorStr("Team"), XfromIndex(1), YfromIndex(1.5 + buffer), &variables::aimbot::rifles::team, &variables::aimbot::rifles::selectedTab, 0);
					addCheckbox(xorStr("Backtrack"), XfromIndex(1), YfromIndex(3 + buffer), &variables::aimbot::rifles::backtrack::enabled, &variables::aimbot::rifles::selectedTab, 0);
					addCheckbox(xorStr("Auto-Zoom"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::rifles::humanization::fastzoom, &variables::aimbot::rifles::selectedTab, 0);

					addKeybinder(xorStr("Key"), XfromIndex(2), YfromIndex(0 + buffer), &variables::aimbot::rifles::key, &variables::aimbot::rifles::selectedTab, 0);
					addSelectionBox(xorStr("Hitbox"), XfromIndex(4), YfromIndex(0 + buffer), { xorStr("Head") , xorStr("Neck"), xorStr("Low Neck"), xorStr("Body"), xorStr("Thorax"), xorStr("Chest"), xorStr("Upper Chest") }, &variables::aimbot::rifles::humanization::hitbox, &variables::aimbot::rifles::selectedTab, 0);
					addSelectionBox(xorStr("Smooth Mode"), XfromIndex(2), YfromIndex(1.5 + buffer), { xorStr("Deceleration"), xorStr("Constant") }, &variables::aimbot::rifles::humanization::smoothmovefactor, &variables::aimbot::rifles::selectedTab, 0);
					addSelectionBox(xorStr("FOV-Position"), XfromIndex(4), YfromIndex(1.5 + buffer), { xorStr("Center Screen"), xorStr("Recoil"), xorStr("On Player") }, &variables::aimbot::rifles::humanization::fovpos, &variables::aimbot::rifles::selectedTab, 0);
					addSlider(xorStr("Ticks"), XfromIndex(4), YfromIndex(3 + buffer), &variables::aimbot::rifles::backtrack::ticks, 0, 12, &variables::aimbot::rifles::selectedTab, 0);



					addSliderFloat(xorStr("Smooth"), XfromIndex(0), YfromIndex(5), MaximumWidth(), &variables::aimbot::rifles::humanization::smooth, 0, 100, &variables::aimbot::rifles::selectedTab, 0);
					addSlider(xorStr("FOV"), XfromIndex(0), YfromIndex(6), MaximumWidth(),  &variables::aimbot::rifles::humanization::fov, 0, 300, &variables::aimbot::rifles::selectedTab, 0);

					

					/*=======================Recoil==================================*/
					addCheckbox(xorStr("RCS Enabled"), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::rifles::humanization::rcs, &variables::aimbot::rifles::selectedTab, 1);
					addCheckbox(xorStr("RCS Standalone"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::rifles::humanization::rcsstandalone, &variables::aimbot::rifles::selectedTab, 1);
					addSlider(xorStr("RCS-X"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::rifles::humanization::rcsx, 0, 150, &variables::aimbot::rifles::selectedTab, 1);
					addSlider(xorStr("RCS-Y"), XfromIndex(0), YfromIndex(4.5 + buffer), &variables::aimbot::rifles::humanization::rcsy, 0, 150, &variables::aimbot::rifles::selectedTab, 1);

					/*=======================Silent==================================*/
					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::rifles::humanization::silent, &variables::aimbot::rifles::selectedTab, 2);
					addCheckbox(xorStr("Silent Nearest"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::rifles::humanization::silentnearest, &variables::aimbot::rifles::selectedTab, 2);
					addSelectionBox(xorStr("Silent Hitbox"), XfromIndex(0), YfromIndex(3 + buffer), { xorStr("Head") , xorStr("Neck"), xorStr("Low Neck"), xorStr("Body"), xorStr("Thorax"), xorStr("Chest"), xorStr("Upper Chest") }, &variables::aimbot::rifles::humanization::silenthitbox, &variables::aimbot::rifles::selectedTab, 2);



					addSlider(xorStr("Silent FOV"), XfromIndex(4), YfromIndex(0 + buffer), &variables::aimbot::rifles::humanization::silentfov, 0, 30, &variables::aimbot::rifles::selectedTab, 2);
					addSlider(xorStr("Silent Start Bullet"), XfromIndex(4), YfromIndex(1.5 + buffer), &variables::aimbot::rifles::humanization::silentstartbullet, 0, 100, &variables::aimbot::rifles::selectedTab, 2);
					addSlider(xorStr("Silent Hitchance"), XfromIndex(4), YfromIndex(3 + buffer), &variables::aimbot::rifles::humanization::silenthitchance, 0, 100, &variables::aimbot::rifles::selectedTab, 2);


					/*=======================Triggerbot==================================*/
				/*	addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::rifles::triggerbot::enabled, &variables::aimbot::rifles::selectedTab, 3);
					addKeybinder(xorStr("Key"), XfromIndex(1), YfromIndex(0 + buffer), &variables::aimbot::rifles::triggerbot::key, &variables::aimbot::rifles::selectedTab, 3);
					addCheckbox(xorStr("Enemies"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::rifles::triggerbot::enemies, &variables::aimbot::rifles::selectedTab, 3);
					addCheckbox(xorStr("Team"), XfromIndex(1), YfromIndex(1.5 + buffer), &variables::aimbot::rifles::triggerbot::team, &variables::aimbot::rifles::selectedTab, 3);
					//addSlider(xorStr("Delay MS"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::rifles::triggerbot::delay, 0, 100, &variables::aimbot::rifles::selectedTab, 3);
					addHitboxSelector(xorStr(""), XfromIndex(4), YfromIndex(0), &variables::aimbot::rifles::triggerbot::head, &variables::aimbot::rifles::triggerbot::upperbody, &variables::aimbot::rifles::triggerbot::lower, &variables::aimbot::rifles::triggerbot::legs, &variables::aimbot::rifles::triggerbot::arms, &variables::aimbot::rifles::selectedTab, 3);

					*/
					finalizePage();
				}
				createPage(xorStr("Smgs"), color(237, 41, 57), XfromIndex(0), YfromIndex(0), NULL, "", true);
				{
					float buffer = 0.3;
					addTabSelector(0, 0, &temporaryWindow->width, &temporaryWindow->pageTabsHeight, {
						xorStr("General"),
						xorStr("Recoil Control"),
						xorStr("Silent"),
						/*xorStr("Triggerbot")*/ }, &variables::aimbot::smg::selectedTab, &variables::gui::bMenuConstant);




					/*=======================GENERAL==================================*/
					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::smg::Enabled, &variables::aimbot::smg::selectedTab, 0);
					addCheckbox(xorStr("Nearest Hitbox"), XfromIndex(1), YfromIndex(0 + buffer), &variables::aimbot::smg::humanization::nearest, &variables::aimbot::smg::selectedTab, 0);
					addCheckbox(xorStr("Enemies"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::smg::enemies, &variables::aimbot::smg::selectedTab, 0);
					addCheckbox(xorStr("Team"), XfromIndex(1), YfromIndex(1.5 + buffer), &variables::aimbot::smg::team, &variables::aimbot::smg::selectedTab, 0);
					addCheckbox(xorStr("Backtrack"), XfromIndex(1), YfromIndex(3 + buffer), &variables::aimbot::smg::backtrack::enabled, &variables::aimbot::smg::selectedTab, 0);
					addCheckbox(xorStr("Auto-Zoom"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::smg::humanization::fastzoom, &variables::aimbot::smg::selectedTab, 0);

					addKeybinder(xorStr("Key"), XfromIndex(2), YfromIndex(0 + buffer), &variables::aimbot::smg::key, &variables::aimbot::smg::selectedTab, 0);
					addSelectionBox(xorStr("Hitbox"), XfromIndex(4), YfromIndex(0 + buffer), { xorStr("Head") , xorStr("Neck"), xorStr("Low Neck"), xorStr("Body"), xorStr("Thorax"), xorStr("Chest"), xorStr("Upper Chest") }, &variables::aimbot::smg::humanization::hitbox, &variables::aimbot::smg::selectedTab, 0);
					addSelectionBox(xorStr("Smooth Mode"), XfromIndex(2), YfromIndex(1.5 + buffer), { xorStr("Deceleration"), xorStr("Constant") }, &variables::aimbot::smg::humanization::smoothmovefactor, &variables::aimbot::smg::selectedTab, 0);
					addSelectionBox(xorStr("FOV-Position"), XfromIndex(4), YfromIndex(1.5 + buffer), { xorStr("Center Screen"), xorStr("Recoil"), xorStr("On Player") }, &variables::aimbot::smg::humanization::fovpos, &variables::aimbot::smg::selectedTab, 0);
					addSlider(xorStr("Ticks"), XfromIndex(4), YfromIndex(3 + buffer), &variables::aimbot::smg::backtrack::ticks, 0, 12, &variables::aimbot::smg::selectedTab, 0);



					addSliderFloat(xorStr("Smooth"), XfromIndex(0), YfromIndex(5), MaximumWidth(), &variables::aimbot::smg::humanization::smooth, 0, 100, &variables::aimbot::smg::selectedTab, 0);
					addSlider(xorStr("FOV"), XfromIndex(0), YfromIndex(6), MaximumWidth(), &variables::aimbot::smg::humanization::fov, 0, 300, &variables::aimbot::smg::selectedTab, 0);




					/*=======================Recoil==================================*/
					addCheckbox(xorStr("RCS Enabled"), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::smg::humanization::rcs, &variables::aimbot::smg::selectedTab, 1);
					addCheckbox(xorStr("RCS Standalone"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::smg::humanization::rcsstandalone, &variables::aimbot::smg::selectedTab, 1);
					addSlider(xorStr("RCS-X"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::smg::humanization::rcsx, 0, 150, &variables::aimbot::smg::selectedTab, 1);
					addSlider(xorStr("RCS-Y"), XfromIndex(0), YfromIndex(4.5 + buffer), &variables::aimbot::smg::humanization::rcsy, 0, 150, &variables::aimbot::smg::selectedTab, 1);
					//addSlider(xorStr("RCS-Smooth"), XfromIndex(0), YfromIndex(6 + buffer), &variables::aimbot::smg::humanization::smoothrcs, 0, 100, &variables::aimbot::smg::selectedTab, 1);




					/*=======================Silent==================================*/
					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::smg::humanization::silent, &variables::aimbot::smg::selectedTab, 2);
					addCheckbox(xorStr("Silent Nearest"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::smg::humanization::silentnearest, &variables::aimbot::smg::selectedTab, 2);
					addSelectionBox(xorStr("Silent Hitbox"), XfromIndex(0), YfromIndex(3 + buffer), { xorStr("Head") , xorStr("Neck"), xorStr("Low Neck"), xorStr("Body"), xorStr("Thorax"), xorStr("Chest"), xorStr("Upper Chest") }, &variables::aimbot::smg::humanization::silenthitbox, &variables::aimbot::smg::selectedTab, 2);



					addSlider(xorStr("Silent FOV"), XfromIndex(4), YfromIndex(0 + buffer), &variables::aimbot::smg::humanization::silentfov, 0, 30, &variables::aimbot::smg::selectedTab, 2);
					addSlider(xorStr("Silent Start Bullet"), XfromIndex(4), YfromIndex(1.5 + buffer), &variables::aimbot::smg::humanization::silentstartbullet, 0, 100, &variables::aimbot::smg::selectedTab, 2);
					addSlider(xorStr("Silent Hitchance"), XfromIndex(4), YfromIndex(3 + buffer), &variables::aimbot::smg::humanization::silenthitchance, 0, 100, &variables::aimbot::smg::selectedTab, 2);

				
					/*=======================Triggerbot==================================*/
					/*addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::smg::triggerbot::enabled, &variables::aimbot::smg::selectedTab, 3);
					addKeybinder(xorStr("Key"), XfromIndex(1), YfromIndex(0 + buffer), &variables::aimbot::smg::triggerbot::key, &variables::aimbot::smg::selectedTab, 3);
					addCheckbox(xorStr("Enemies"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::smg::triggerbot::enemies, &variables::aimbot::smg::selectedTab, 3);
					addCheckbox(xorStr("Team"), XfromIndex(1), YfromIndex(1.5 + buffer), &variables::aimbot::smg::triggerbot::team, &variables::aimbot::smg::selectedTab, 3);
					//addSlider(xorStr("Delay MS"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::smg::triggerbot::delay, 0, 100, &variables::aimbot::smg::selectedTab, 3);
					addHitboxSelector(xorStr(""), XfromIndex(4), YfromIndex(0), &variables::aimbot::smg::triggerbot::head, &variables::aimbot::smg::triggerbot::upperbody, &variables::aimbot::smg::triggerbot::lower, &variables::aimbot::smg::triggerbot::legs, &variables::aimbot::smg::triggerbot::arms, &variables::aimbot::smg::selectedTab, 3);
					*/

					finalizePage();
				}
				createPage(xorStr("Pistols"), color(237, 41, 57), XfromIndex(0), YfromIndex(0), NULL, "", true);
				{
					float buffer = 0.3;
					addTabSelector(0, 0, &temporaryWindow->width, &temporaryWindow->pageTabsHeight, {
						xorStr("General"),
						xorStr("Recoil Control"),
						xorStr("Silent"),
						/*xorStr("Triggerbot")*/  }, &variables::aimbot::pistols::selectedTab, &variables::gui::bMenuConstant);



					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::pistols::Enabled, &variables::aimbot::pistols::selectedTab, 0);
					addCheckbox(xorStr("Nearest Hitbox"), XfromIndex(1), YfromIndex(0 + buffer), &variables::aimbot::pistols::humanization::nearest, &variables::aimbot::pistols::selectedTab, 0);
					addCheckbox(xorStr("Enemies"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::pistols::enemies, &variables::aimbot::pistols::selectedTab, 0);
					addCheckbox(xorStr("Team"), XfromIndex(1), YfromIndex(1.5 + buffer), &variables::aimbot::pistols::team, &variables::aimbot::pistols::selectedTab, 0);
					addCheckbox(xorStr("Backtrack"), XfromIndex(1), YfromIndex(3 + buffer), &variables::aimbot::pistols::backtrack::enabled, &variables::aimbot::pistols::selectedTab, 0);
					addCheckbox(xorStr("Auto-Zoom"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::pistols::humanization::fastzoom, &variables::aimbot::pistols::selectedTab, 0);

					addKeybinder(xorStr("Key"), XfromIndex(2), YfromIndex(0 + buffer), &variables::aimbot::pistols::key, &variables::aimbot::pistols::selectedTab, 0);
					addSelectionBox(xorStr("Hitbox"), XfromIndex(4), YfromIndex(0 + buffer), { xorStr("Head") , xorStr("Neck"), xorStr("Low Neck"), xorStr("Body"), xorStr("Thorax"), xorStr("Chest"), xorStr("Upper Chest") }, & variables::aimbot::pistols::humanization::hitbox, & variables::aimbot::pistols::selectedTab, 0);
					addSelectionBox(xorStr("Smooth Mode"), XfromIndex(2), YfromIndex(1.5 + buffer), { xorStr("Deceleration"), xorStr("Constant") }, & variables::aimbot::pistols::humanization::smoothmovefactor, & variables::aimbot::pistols::selectedTab, 0);
					addSelectionBox(xorStr("FOV-Position"), XfromIndex(4), YfromIndex(1.5 + buffer), { xorStr("Center Screen"), xorStr("Recoil"), xorStr("On Player") }, & variables::aimbot::pistols::humanization::fovpos, & variables::aimbot::pistols::selectedTab, 0);
					addSlider(xorStr("Ticks"), XfromIndex(4), YfromIndex(3 + buffer), &variables::aimbot::pistols::backtrack::ticks, 0, 12, &variables::aimbot::pistols::selectedTab, 0);



					addSliderFloat(xorStr("Smooth"), XfromIndex(0), YfromIndex(5), MaximumWidth(), &variables::aimbot::pistols::humanization::smooth, 0, 100, &variables::aimbot::pistols::selectedTab, 0);
					addSlider(xorStr("FOV"), XfromIndex(0), YfromIndex(6), MaximumWidth(), &variables::aimbot::pistols::humanization::fov, 0, 300, &variables::aimbot::pistols::selectedTab, 0);



					/*=======================Recoil==================================*/
					addCheckbox(xorStr("RCS Enabled"), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::pistols::humanization::rcs, &variables::aimbot::pistols::selectedTab, 1);
					addCheckbox(xorStr("RCS Standalone"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::pistols::humanization::rcsstandalone, &variables::aimbot::pistols::selectedTab, 1);
					addSlider(xorStr("RCS-X"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::pistols::humanization::rcsx, 0, 150, &variables::aimbot::pistols::selectedTab, 1);
					addSlider(xorStr("RCS-Y"), XfromIndex(0), YfromIndex(4.5 + buffer), &variables::aimbot::pistols::humanization::rcsy, 0, 150, &variables::aimbot::pistols::selectedTab, 1);
					//addSlider(xorStr("RCS-Smooth"), XfromIndex(0), YfromIndex(6 + buffer), &variables::aimbot::pistols::humanization::smoothrcs, 0, 100, &variables::aimbot::pistols::selectedTab, 1);




					/*=======================Silent==================================*/
					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::pistols::humanization::silent, &variables::aimbot::pistols::selectedTab, 2);
					addCheckbox(xorStr("Silent Nearest"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::pistols::humanization::silentnearest, &variables::aimbot::pistols::selectedTab, 2);
					addSelectionBox(xorStr("Silent Hitbox"), XfromIndex(0), YfromIndex(3 + buffer), { xorStr("Head") , xorStr("Neck"), xorStr("Low Neck"), xorStr("Body"), xorStr("Thorax"), xorStr("Chest"), xorStr("Upper Chest") }, &variables::aimbot::pistols::humanization::silenthitbox, &variables::aimbot::pistols::selectedTab, 2);



					addSlider(xorStr("Silent FOV"), XfromIndex(4), YfromIndex(0 + buffer), &variables::aimbot::pistols::humanization::silentfov, 0, 30, &variables::aimbot::pistols::selectedTab, 2);
					addSlider(xorStr("Silent Start Bullet"), XfromIndex(4), YfromIndex(1.5 + buffer), &variables::aimbot::pistols::humanization::silentstartbullet, 0, 100, &variables::aimbot::pistols::selectedTab, 2);
					addSlider(xorStr("Silent Hitchance"), XfromIndex(4), YfromIndex(3 + buffer), &variables::aimbot::pistols::humanization::silenthitchance, 0, 100, &variables::aimbot::pistols::selectedTab, 2);


					/*=======================Triggerbot==================================*/
					/*addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::pistols::triggerbot::enabled, &variables::aimbot::pistols::selectedTab, 3);
					addKeybinder(xorStr("Key"), XfromIndex(1), YfromIndex(0 + buffer), &variables::aimbot::pistols::triggerbot::key, &variables::aimbot::pistols::selectedTab, 3);
					addCheckbox(xorStr("Enemies"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::pistols::triggerbot::enemies, &variables::aimbot::pistols::selectedTab, 3);
					addCheckbox(xorStr("Team"), XfromIndex(1), YfromIndex(1.5 + buffer), &variables::aimbot::pistols::triggerbot::team, &variables::aimbot::pistols::selectedTab, 3);
					addHitboxSelector(xorStr(""), XfromIndex(4), YfromIndex(0), &variables::aimbot::pistols::triggerbot::head, &variables::aimbot::pistols::triggerbot::upperbody, &variables::aimbot::pistols::triggerbot::lower, &variables::aimbot::pistols::triggerbot::legs, &variables::aimbot::pistols::triggerbot::arms, &variables::aimbot::pistols::selectedTab, 3);
					*/
					finalizePage();
				}
				createPage(xorStr("AWP"), color(237, 41, 57), XfromIndex(0), YfromIndex(0), NULL, "", true);
				{
					float buffer = 0.3;
					addTabSelector(0, 0, &temporaryWindow->width, &temporaryWindow->pageTabsHeight, {
						xorStr("General"),
						xorStr("Recoil Control"),
						xorStr("Silent"),
						/*xorStr("Triggerbot")*/ }, &variables::aimbot::awp::selectedTab, &variables::gui::bMenuConstant);




					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::awp::Enabled, &variables::aimbot::awp::selectedTab, 0);
					addCheckbox(xorStr("Nearest Hitbox"), XfromIndex(1), YfromIndex(0 + buffer), &variables::aimbot::awp::humanization::nearest, &variables::aimbot::awp::selectedTab, 0);
					addCheckbox(xorStr("Enemies"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::awp::enemies, &variables::aimbot::awp::selectedTab, 0);
					addCheckbox(xorStr("Team"), XfromIndex(1), YfromIndex(1.5 + buffer), &variables::aimbot::awp::team, &variables::aimbot::awp::selectedTab, 0);
					addCheckbox(xorStr("Backtrack"), XfromIndex(1), YfromIndex(3 + buffer), &variables::aimbot::awp::backtrack::enabled, &variables::aimbot::awp::selectedTab, 0);
					addCheckbox(xorStr("Auto-Zoom"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::awp::humanization::fastzoom, &variables::aimbot::awp::selectedTab, 0);

					addKeybinder(xorStr("Key"), XfromIndex(2), YfromIndex(0 + buffer), &variables::aimbot::awp::key, &variables::aimbot::awp::selectedTab, 0);
					addSelectionBox(xorStr("Hitbox"), XfromIndex(4), YfromIndex(0 + buffer), { xorStr("Head") , xorStr("Neck"), xorStr("Low Neck"), xorStr("Body"), xorStr("Thorax"), xorStr("Chest"), xorStr("Upper Chest") }, & variables::aimbot::awp::humanization::hitbox, & variables::aimbot::awp::selectedTab, 0);
					addSelectionBox(xorStr("Smooth Mode"), XfromIndex(2), YfromIndex(1.5 + buffer), { xorStr("Deceleration"), xorStr("Constant") }, & variables::aimbot::awp::humanization::smoothmovefactor, & variables::aimbot::awp::selectedTab, 0);
					addSelectionBox(xorStr("FOV-Position"), XfromIndex(4), YfromIndex(1.5 + buffer), { xorStr("Center Screen"), xorStr("Recoil"), xorStr("On Player") }, & variables::aimbot::awp::humanization::fovpos, & variables::aimbot::awp::selectedTab, 0);
					addSlider(xorStr("Ticks"), XfromIndex(4), YfromIndex(3 + buffer), &variables::aimbot::awp::backtrack::ticks, 0, 12, &variables::aimbot::awp::selectedTab, 0);



					addSliderFloat(xorStr("Smooth"), XfromIndex(0), YfromIndex(5), MaximumWidth(), &variables::aimbot::awp::humanization::smooth, 0, 100, &variables::aimbot::awp::selectedTab, 0);
					addSlider(xorStr("FOV"), XfromIndex(0), YfromIndex(6), MaximumWidth(), &variables::aimbot::awp::humanization::fov, 0, 300, &variables::aimbot::awp::selectedTab, 0);



					/*=======================Recoil==================================*/
					addCheckbox(xorStr("RCS Enabled"), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::awp::humanization::rcs, &variables::aimbot::awp::selectedTab, 1);
					addCheckbox(xorStr("RCS Standalone"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::awp::humanization::rcsstandalone, &variables::aimbot::awp::selectedTab, 1);
					addSlider(xorStr("RCS-X"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::awp::humanization::rcsx, 0, 150, &variables::aimbot::awp::selectedTab, 1);
					addSlider(xorStr("RCS-Y"), XfromIndex(0), YfromIndex(4.5 + buffer), &variables::aimbot::awp::humanization::rcsy, 0, 150, &variables::aimbot::awp::selectedTab, 1);
					//addSlider(xorStr("RCS-Smooth"), XfromIndex(0), YfromIndex(6 + buffer), &variables::aimbot::awp::humanization::smoothrcs, 0, 100, &variables::aimbot::awp::selectedTab, 1);




					/*=======================Silent==================================*/
					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::awp::humanization::silent, &variables::aimbot::awp::selectedTab, 2);
					addCheckbox(xorStr("Silent Nearest"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::awp::humanization::silentnearest, &variables::aimbot::awp::selectedTab, 2);
					addSelectionBox(xorStr("Silent Hitbox"), XfromIndex(0), YfromIndex(3 + buffer), { xorStr("Head") , xorStr("Neck"), xorStr("Low Neck"), xorStr("Body"), xorStr("Thorax"), xorStr("Chest"), xorStr("Upper Chest") }, &variables::aimbot::awp::humanization::silenthitbox, &variables::aimbot::awp::selectedTab, 2);



					addSlider(xorStr("Silent FOV"), XfromIndex(4), YfromIndex(0 + buffer), &variables::aimbot::awp::humanization::silentfov, 0, 30, &variables::aimbot::awp::selectedTab, 2);
					addSlider(xorStr("Silent Start Bullet"), XfromIndex(4), YfromIndex(1.5 + buffer), &variables::aimbot::awp::humanization::silentstartbullet, 0, 100, &variables::aimbot::awp::selectedTab, 2);
					addSlider(xorStr("Silent Hitchance"), XfromIndex(4), YfromIndex(3 + buffer), &variables::aimbot::awp::humanization::silenthitchance, 0, 100, &variables::aimbot::awp::selectedTab, 2);


					/*=======================Triggerbot==================================*/
					/*addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::awp::triggerbot::enabled, &variables::aimbot::awp::selectedTab, 3);
					addKeybinder(xorStr("Key"), XfromIndex(1), YfromIndex(0 + buffer), &variables::aimbot::awp::triggerbot::key, &variables::aimbot::awp::selectedTab, 3);
					addCheckbox(xorStr("Enemies"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::awp::triggerbot::enemies, &variables::aimbot::awp::selectedTab, 3);
					addCheckbox(xorStr("Team"), XfromIndex(1), YfromIndex(1.5 + buffer), &variables::aimbot::awp::triggerbot::team, &variables::aimbot::awp::selectedTab, 3);
					//addSlider(xorStr("Delay MS"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::awp::triggerbot::delay, 0, 100, &variables::aimbot::awp::selectedTab, 3);
					addHitboxSelector(xorStr(""), XfromIndex(4), YfromIndex(0), &variables::aimbot::awp::triggerbot::head, &variables::aimbot::awp::triggerbot::upperbody, &variables::aimbot::awp::triggerbot::lower, &variables::aimbot::awp::triggerbot::legs, &variables::aimbot::awp::triggerbot::arms, &variables::aimbot::awp::selectedTab, 3);

					*/
					finalizePage();
				}
				createPage(xorStr("Scout"), color(237, 41, 57), XfromIndex(0), YfromIndex(0), NULL, "", true);
				{
					float buffer = 0.3;
					addTabSelector(0, 0, &temporaryWindow->width, &temporaryWindow->pageTabsHeight, {
						xorStr("General"),
						xorStr("Recoil Control"),
						xorStr("Silent"),
						/*xorStr("Triggerbot")*/ }, &variables::aimbot::scout::selectedTab, &variables::gui::bMenuConstant);




					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::scout::Enabled, &variables::aimbot::scout::selectedTab, 0);
					addCheckbox(xorStr("Nearest Hitbox"), XfromIndex(1), YfromIndex(0 + buffer), &variables::aimbot::scout::humanization::nearest, &variables::aimbot::scout::selectedTab, 0);
					addCheckbox(xorStr("Enemies"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::scout::enemies, &variables::aimbot::scout::selectedTab, 0);
					addCheckbox(xorStr("Team"), XfromIndex(1), YfromIndex(1.5 + buffer), &variables::aimbot::scout::team, &variables::aimbot::scout::selectedTab, 0);
					addCheckbox(xorStr("Backtrack"), XfromIndex(1), YfromIndex(3 + buffer), &variables::aimbot::scout::backtrack::enabled, &variables::aimbot::scout::selectedTab, 0);
					addCheckbox(xorStr("Auto-Zoom"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::scout::humanization::fastzoom, &variables::aimbot::scout::selectedTab, 0);

					addKeybinder(xorStr("Key"), XfromIndex(2), YfromIndex(0 + buffer), &variables::aimbot::scout::key, &variables::aimbot::scout::selectedTab, 0);
					addSelectionBox(xorStr("Hitbox"), XfromIndex(4), YfromIndex(0 + buffer), { xorStr("Head") , xorStr("Neck"), xorStr("Low Neck"), xorStr("Body"), xorStr("Thorax"), xorStr("Chest"), xorStr("Upper Chest") }, & variables::aimbot::scout::humanization::hitbox, & variables::aimbot::scout::selectedTab, 0);
					addSelectionBox(xorStr("Smooth Mode"), XfromIndex(2), YfromIndex(1.5 + buffer), { xorStr("Deceleration"), xorStr("Constant") }, & variables::aimbot::scout::humanization::smoothmovefactor, & variables::aimbot::scout::selectedTab, 0);
					addSelectionBox(xorStr("FOV-Position"), XfromIndex(4), YfromIndex(1.5 + buffer), { xorStr("Center Screen"), xorStr("Recoil"), xorStr("On Player") }, & variables::aimbot::scout::humanization::fovpos, & variables::aimbot::scout::selectedTab, 0);
					addSlider(xorStr("Ticks"), XfromIndex(4), YfromIndex(3 + buffer), &variables::aimbot::scout::backtrack::ticks, 0, 12, &variables::aimbot::scout::selectedTab, 0);



					addSliderFloat(xorStr("Smooth"), XfromIndex(0), YfromIndex(5), MaximumWidth(), &variables::aimbot::scout::humanization::smooth, 0, 100, &variables::aimbot::scout::selectedTab, 0);
					addSlider(xorStr("FOV"), XfromIndex(0), YfromIndex(6), MaximumWidth(), &variables::aimbot::scout::humanization::fov, 0, 300, &variables::aimbot::scout::selectedTab, 0);


					/*=======================Recoil==================================*/
					addCheckbox(xorStr("RCS Enabled"), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::scout::humanization::rcs, &variables::aimbot::scout::selectedTab, 1);
					addCheckbox(xorStr("RCS Standalone"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::scout::humanization::rcsstandalone, &variables::aimbot::scout::selectedTab, 1);
					addSlider(xorStr("RCS-X"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::scout::humanization::rcsx, 0, 150, &variables::aimbot::scout::selectedTab, 1);
					addSlider(xorStr("RCS-Y"), XfromIndex(0), YfromIndex(4.5 + buffer), &variables::aimbot::scout::humanization::rcsy, 0, 150, &variables::aimbot::scout::selectedTab, 1);
					//addSlider(xorStr("RCS-Smooth"), XfromIndex(0), YfromIndex(6 + buffer), &variables::aimbot::scout::humanization::smoothrcs, 0, 100, &variables::aimbot::scout::selectedTab, 1);




					/*=======================Silent==================================*/
					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::scout::humanization::silent, &variables::aimbot::scout::selectedTab, 2);
					addCheckbox(xorStr("Silent Nearest"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::scout::humanization::silentnearest, &variables::aimbot::scout::selectedTab, 2);
					addSelectionBox(xorStr("Silent Hitbox"), XfromIndex(0), YfromIndex(3 + buffer), { xorStr("Head") , xorStr("Neck"), xorStr("Low Neck"), xorStr("Body"), xorStr("Thorax"), xorStr("Chest"), xorStr("Upper Chest") }, &variables::aimbot::scout::humanization::silenthitbox, &variables::aimbot::scout::selectedTab, 2);



					addSlider(xorStr("Silent FOV"), XfromIndex(4), YfromIndex(0 + buffer), &variables::aimbot::scout::humanization::silentfov, 0, 30, &variables::aimbot::scout::selectedTab, 2);
					addSlider(xorStr("Silent Start Bullet"), XfromIndex(4), YfromIndex(1.5 + buffer), &variables::aimbot::scout::humanization::silentstartbullet, 0, 100, &variables::aimbot::scout::selectedTab, 2);
					addSlider(xorStr("Silent Hitchance"), XfromIndex(4), YfromIndex(3 + buffer), &variables::aimbot::scout::humanization::silenthitchance, 0, 100, &variables::aimbot::scout::selectedTab, 2);


					/*=======================Triggerbot==================================*/
					/*addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::scout::triggerbot::enabled, &variables::aimbot::scout::selectedTab, 3);
					addKeybinder(xorStr("Key"), XfromIndex(1), YfromIndex(0 + buffer), &variables::aimbot::scout::triggerbot::key, &variables::aimbot::scout::selectedTab, 3);
					addCheckbox(xorStr("Enemies"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::scout::triggerbot::enemies, &variables::aimbot::scout::selectedTab, 3);
					addCheckbox(xorStr("Team"), XfromIndex(1), YfromIndex(1.5 + buffer), &variables::aimbot::scout::triggerbot::team, &variables::aimbot::scout::selectedTab, 3);
					//addSlider(xorStr("Delay MS"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::scout::triggerbot::delay, 0, 100, &variables::aimbot::scout::selectedTab, 3);
					addHitboxSelector(xorStr(""), XfromIndex(4), YfromIndex(0), &variables::aimbot::scout::triggerbot::head, &variables::aimbot::scout::triggerbot::upperbody, &variables::aimbot::scout::triggerbot::lower, &variables::aimbot::scout::triggerbot::legs, &variables::aimbot::scout::triggerbot::arms, &variables::aimbot::scout::selectedTab, 3);

					*/

					finalizePage();
				}
				createPage(xorStr("Autosniper"), color(237, 41, 57), XfromIndex(0), YfromIndex(0), NULL, "", true);
				{
					float buffer = 0.3;
					addTabSelector(0, 0, &temporaryWindow->width, &temporaryWindow->pageTabsHeight, {
						xorStr("General"),
						xorStr("Recoil Control"),
						xorStr("Silent"),
						/*xorStr("Triggerbot")*/ }, &variables::aimbot::autosniper::selectedTab, &variables::gui::bMenuConstant);




					/*=======================GENERAL==================================*/
					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::autosniper::Enabled, &variables::aimbot::autosniper::selectedTab, 0);
					addCheckbox(xorStr("Nearest Hitbox"), XfromIndex(1), YfromIndex(0 + buffer), &variables::aimbot::autosniper::humanization::nearest, &variables::aimbot::autosniper::selectedTab, 0);
					addCheckbox(xorStr("Enemies"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::autosniper::enemies, &variables::aimbot::autosniper::selectedTab, 0);
					addCheckbox(xorStr("Team"), XfromIndex(1), YfromIndex(1.5 + buffer), &variables::aimbot::autosniper::team, &variables::aimbot::autosniper::selectedTab, 0);
					addCheckbox(xorStr("Backtrack"), XfromIndex(1), YfromIndex(3 + buffer), &variables::aimbot::autosniper::backtrack::enabled, &variables::aimbot::autosniper::selectedTab, 0);
					addCheckbox(xorStr("Auto-Zoom"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::autosniper::humanization::fastzoom, &variables::aimbot::autosniper::selectedTab, 0);

					addKeybinder(xorStr("Key"), XfromIndex(2), YfromIndex(0 + buffer), &variables::aimbot::autosniper::key, &variables::aimbot::autosniper::selectedTab, 0);
					addSelectionBox(xorStr("Hitbox"), XfromIndex(4), YfromIndex(0 + buffer), { xorStr("Head") , xorStr("Neck"), xorStr("Low Neck"), xorStr("Body"), xorStr("Thorax"), xorStr("Chest"), xorStr("Upper Chest") }, & variables::aimbot::autosniper::humanization::hitbox, & variables::aimbot::autosniper::selectedTab, 0);
					addSelectionBox(xorStr("Smooth Mode"), XfromIndex(2), YfromIndex(1.5 + buffer), { xorStr("Deceleration"), xorStr("Constant") }, & variables::aimbot::autosniper::humanization::smoothmovefactor, & variables::aimbot::autosniper::selectedTab, 0);
					addSelectionBox(xorStr("FOV-Position"), XfromIndex(4), YfromIndex(1.5 + buffer), { xorStr("Center Screen"), xorStr("Recoil"), xorStr("On Player") }, & variables::aimbot::autosniper::humanization::fovpos, & variables::aimbot::autosniper::selectedTab, 0);
					addSlider(xorStr("Ticks"), XfromIndex(4), YfromIndex(3 + buffer), &variables::aimbot::autosniper::backtrack::ticks, 0, 12, &variables::aimbot::autosniper::selectedTab, 0);



					addSliderFloat(xorStr("Smooth"), XfromIndex(0), YfromIndex(5), MaximumWidth(), &variables::aimbot::autosniper::humanization::smooth, 0, 100, &variables::aimbot::autosniper::selectedTab, 0);
					addSlider(xorStr("FOV"), XfromIndex(0), YfromIndex(6), MaximumWidth(), &variables::aimbot::autosniper::humanization::fov, 0, 300, &variables::aimbot::autosniper::selectedTab, 0);




					/*=======================Recoil==================================*/
					addCheckbox(xorStr("RCS Enabled"), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::autosniper::humanization::rcs, &variables::aimbot::autosniper::selectedTab, 1);
					addCheckbox(xorStr("RCS Standalone"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::autosniper::humanization::rcsstandalone, &variables::aimbot::autosniper::selectedTab, 1);
					addSlider(xorStr("RCS-X"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::autosniper::humanization::rcsx, 0, 150, &variables::aimbot::autosniper::selectedTab, 1);
					addSlider(xorStr("RCS-Y"), XfromIndex(0), YfromIndex(4.5 + buffer), &variables::aimbot::autosniper::humanization::rcsy, 0, 150, &variables::aimbot::autosniper::selectedTab, 1);
					//addSlider(xorStr("RCS-Smooth"), XfromIndex(0), YfromIndex(6 + buffer), &variables::aimbot::autosniper::humanization::smoothrcs, 0, 100, &variables::aimbot::autosniper::selectedTab, 1);




					/*=======================Silent==================================*/
					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::autosniper::humanization::silent, &variables::aimbot::autosniper::selectedTab, 2);
					addCheckbox(xorStr("Silent Nearest"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::autosniper::humanization::silentnearest, &variables::aimbot::autosniper::selectedTab, 2);
					addSelectionBox(xorStr("Silent Hitbox"), XfromIndex(0), YfromIndex(3 + buffer), { xorStr("Head") , xorStr("Neck"), xorStr("Low Neck"), xorStr("Body"), xorStr("Thorax"), xorStr("Chest"), xorStr("Upper Chest") }, &variables::aimbot::autosniper::humanization::silenthitbox, &variables::aimbot::autosniper::selectedTab, 2);



					addSlider(xorStr("Silent FOV"), XfromIndex(4), YfromIndex(0 + buffer), &variables::aimbot::autosniper::humanization::silentfov, 0, 30, &variables::aimbot::autosniper::selectedTab, 2);
					addSlider(xorStr("Silent Start Bullet"), XfromIndex(4), YfromIndex(1.5 + buffer), &variables::aimbot::autosniper::humanization::silentstartbullet, 0, 100, &variables::aimbot::autosniper::selectedTab, 2);
					addSlider(xorStr("Silent Hitchance"), XfromIndex(4), YfromIndex(3 + buffer), &variables::aimbot::autosniper::humanization::silenthitchance, 0, 100, &variables::aimbot::autosniper::selectedTab, 2);



					/*=======================Triggerbot==================================*/
					/*addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::autosniper::triggerbot::enabled, &variables::aimbot::autosniper::selectedTab, 3);
					addKeybinder(xorStr("Key"), XfromIndex(1), YfromIndex(0 + buffer), &variables::aimbot::autosniper::triggerbot::key, &variables::aimbot::autosniper::selectedTab, 3);
					addCheckbox(xorStr("Enemies"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::autosniper::triggerbot::enemies, &variables::aimbot::autosniper::selectedTab, 3);
					addCheckbox(xorStr("Team"), XfromIndex(1), YfromIndex(1.5 + buffer), &variables::aimbot::autosniper::triggerbot::team, &variables::aimbot::autosniper::selectedTab, 3);
					//addSlider(xorStr("Delay MS"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::autosniper::triggerbot::delay, 0, 100, &variables::aimbot::autosniper::selectedTab, 3);
					addHitboxSelector(xorStr(""), XfromIndex(4), YfromIndex(0), &variables::aimbot::autosniper::triggerbot::head, &variables::aimbot::autosniper::triggerbot::upperbody, &variables::aimbot::autosniper::triggerbot::lower, &variables::aimbot::autosniper::triggerbot::legs, &variables::aimbot::autosniper::triggerbot::arms, &variables::aimbot::autosniper::selectedTab, 3);
					*/
					finalizePage();
				}
				createPage(xorStr("Shotguns"), color(237, 41, 57), XfromIndex(0), YfromIndex(0), NULL, "", true);
				{
					float buffer = 0.3;
					addTabSelector(0, 0, &temporaryWindow->width, &temporaryWindow->pageTabsHeight, {
						xorStr("General"),
						xorStr("Recoil Control"),
						xorStr("Silent"),
						/*xorStr("Triggerbot")*/ }, &variables::aimbot::shotguns::selectedTab, &variables::gui::bMenuConstant);




					/*=======================GENERAL==================================*/
					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::shotguns::Enabled, &variables::aimbot::shotguns::selectedTab, 0);
					addCheckbox(xorStr("Nearest Hitbox"), XfromIndex(1), YfromIndex(0 + buffer), &variables::aimbot::shotguns::humanization::nearest, &variables::aimbot::shotguns::selectedTab, 0);
					addCheckbox(xorStr("Enemies"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::shotguns::enemies, &variables::aimbot::shotguns::selectedTab, 0);
					addCheckbox(xorStr("Team"), XfromIndex(1), YfromIndex(1.5 + buffer), &variables::aimbot::shotguns::team, &variables::aimbot::shotguns::selectedTab, 0);
					addCheckbox(xorStr("Backtrack"), XfromIndex(1), YfromIndex(3 + buffer), &variables::aimbot::shotguns::backtrack::enabled, &variables::aimbot::shotguns::selectedTab, 0);
					addCheckbox(xorStr("Auto-Zoom"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::shotguns::humanization::fastzoom, &variables::aimbot::shotguns::selectedTab, 0);

					addKeybinder(xorStr("Key"), XfromIndex(2), YfromIndex(0 + buffer), &variables::aimbot::shotguns::key, &variables::aimbot::shotguns::selectedTab, 0);
					addSelectionBox(xorStr("Hitbox"), XfromIndex(4), YfromIndex(0 + buffer), { xorStr("Head") , xorStr("Neck"), xorStr("Low Neck"), xorStr("Body"), xorStr("Thorax"), xorStr("Chest"), xorStr("Upper Chest") }, & variables::aimbot::shotguns::humanization::hitbox, & variables::aimbot::shotguns::selectedTab, 0);
					addSelectionBox(xorStr("Smooth Mode"), XfromIndex(2), YfromIndex(1.5 + buffer), { xorStr("Deceleration"), xorStr("Constant") }, & variables::aimbot::shotguns::humanization::smoothmovefactor, & variables::aimbot::shotguns::selectedTab, 0);
					addSelectionBox(xorStr("FOV-Position"), XfromIndex(4), YfromIndex(1.5 + buffer), { xorStr("Center Screen"), xorStr("Recoil"), xorStr("On Player") }, & variables::aimbot::shotguns::humanization::fovpos, & variables::aimbot::shotguns::selectedTab, 0);
					addSlider(xorStr("Ticks"), XfromIndex(4), YfromIndex(3 + buffer), &variables::aimbot::shotguns::backtrack::ticks, 0, 12, &variables::aimbot::shotguns::selectedTab, 0);



					addSliderFloat(xorStr("Smooth"), XfromIndex(0), YfromIndex(5), MaximumWidth(), &variables::aimbot::shotguns::humanization::smooth, 0, 100, &variables::aimbot::shotguns::selectedTab, 0);
					addSlider(xorStr("FOV"), XfromIndex(0), YfromIndex(6), MaximumWidth(), &variables::aimbot::shotguns::humanization::fov, 0, 300, &variables::aimbot::shotguns::selectedTab, 0);




					/*=======================Recoil==================================*/
					addCheckbox(xorStr("RCS Enabled"), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::shotguns::humanization::rcs, &variables::aimbot::shotguns::selectedTab, 1);
					addCheckbox(xorStr("RCS Standalone"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::shotguns::humanization::rcsstandalone, &variables::aimbot::shotguns::selectedTab, 1);
					addSlider(xorStr("RCS-X"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::shotguns::humanization::rcsx, 0, 150, &variables::aimbot::shotguns::selectedTab, 1);
					addSlider(xorStr("RCS-Y"), XfromIndex(0), YfromIndex(4.5 + buffer), &variables::aimbot::shotguns::humanization::rcsy, 0, 150, &variables::aimbot::shotguns::selectedTab, 1);
					//addSlider(xorStr("RCS-Smooth"), XfromIndex(0), YfromIndex(6 + buffer), &variables::aimbot::shotguns::humanization::smoothrcs, 0, 100, &variables::aimbot::shotguns::selectedTab, 1);




					/*=======================Silent==================================*/
					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::shotguns::humanization::silent, &variables::aimbot::shotguns::selectedTab, 2);
					addCheckbox(xorStr("Silent Nearest"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::shotguns::humanization::silentnearest, &variables::aimbot::shotguns::selectedTab, 2);
					addSelectionBox(xorStr("Silent Hitbox"), XfromIndex(0), YfromIndex(3 + buffer), { xorStr("Head") , xorStr("Neck"), xorStr("Low Neck"), xorStr("Body"), xorStr("Thorax"), xorStr("Chest"), xorStr("Upper Chest") }, &variables::aimbot::shotguns::humanization::silenthitbox, &variables::aimbot::shotguns::selectedTab, 2);



					addSlider(xorStr("Silent FOV"), XfromIndex(4), YfromIndex(0 + buffer), &variables::aimbot::shotguns::humanization::silentfov, 0, 30, &variables::aimbot::shotguns::selectedTab, 2);
					addSlider(xorStr("Silent Start Bullet"), XfromIndex(4), YfromIndex(1.5 + buffer), &variables::aimbot::shotguns::humanization::silentstartbullet, 0, 100, &variables::aimbot::shotguns::selectedTab, 2);
					addSlider(xorStr("Silent Hitchance"), XfromIndex(4), YfromIndex(3 + buffer), &variables::aimbot::shotguns::humanization::silenthitchance, 0, 100, &variables::aimbot::shotguns::selectedTab, 2);



					/*=======================Triggerbot==================================*/
					/*addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0 + buffer), &variables::aimbot::shotguns::triggerbot::enabled, &variables::aimbot::shotguns::selectedTab, 3);
					addKeybinder(xorStr("Key"), XfromIndex(1), YfromIndex(0 + buffer), &variables::aimbot::shotguns::triggerbot::key, &variables::aimbot::shotguns::selectedTab, 3);
					addCheckbox(xorStr("Enemies"), XfromIndex(0), YfromIndex(1.5 + buffer), &variables::aimbot::shotguns::triggerbot::enemies, &variables::aimbot::shotguns::selectedTab, 3);
					addCheckbox(xorStr("Team"), XfromIndex(1), YfromIndex(1.5 + buffer), &variables::aimbot::shotguns::triggerbot::team, &variables::aimbot::shotguns::selectedTab, 3);
					//addSlider(xorStr("Delay MS"), XfromIndex(0), YfromIndex(3 + buffer), &variables::aimbot::shotguns::triggerbot::delay, 0, 100, &variables::aimbot::shotguns::selectedTab, 3);
					addHitboxSelector(xorStr(""), XfromIndex(4), YfromIndex(0), &variables::aimbot::shotguns::triggerbot::head, &variables::aimbot::shotguns::triggerbot::upperbody, &variables::aimbot::shotguns::triggerbot::lower, &variables::aimbot::shotguns::triggerbot::legs, &variables::aimbot::shotguns::triggerbot::arms, &variables::aimbot::shotguns::selectedTab, 3);

					*/

					finalizePage();
				}
				finalizeCluster();
			}
			createCluster(xorStr("ESP"), &variables::gui::bAlwaysTrue); {

				createPage(xorStr("Enemies"), color(191, 10, 48), XfromIndex(0), YfromIndex(0), NULL, xorStr("Frequently Used"), true);
				{
					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0), &variables::esp::enemies::enabled, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Visible only"), XfromIndex(0), YfromIndex(1), &variables::esp::enemies::visibleOnly, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Ingame-Radar"), XfromIndex(0), YfromIndex(2), &variables::esp::enemies::radar, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Custom-Radar"), XfromIndex(0), YfromIndex(3), &variables::esp::enemies::cheatradar, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Skeleton (lowfps)"), XfromIndex(0), YfromIndex(4), &variables::esp::enemies::skeleton, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Has Helmet"), XfromIndex(0), YfromIndex(5), &variables::esp::enemies::helmetESP, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Is Defusing"), XfromIndex(0), YfromIndex(6), &variables::esp::enemies::defuseWarning, &variables::gui::bMenuConstant);


					addSelectionCheck(xorStr("Name"), XfromIndex(0.8), YfromIndex(0), &variables::esp::enemies::name, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Health"), XfromIndex(0.8), YfromIndex(1), &variables::esp::enemies::healthbar, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Money"), XfromIndex(0.8), YfromIndex(2), &variables::esp::enemies::money, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Weapon"), XfromIndex(0.8), YfromIndex(3), &variables::esp::enemies::weapon, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Ammunition"), XfromIndex(0.8), YfromIndex(4), &variables::esp::enemies::ammunition, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Distance"), XfromIndex(0.8), YfromIndex(5), &variables::esp::enemies::distance, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Barrel"), XfromIndex(0.8), YfromIndex(6), &variables::esp::enemies::barrel, &variables::gui::bMenuConstant);
					

					addCheckbox(xorStr("Box Outline"), XfromIndex(1.6), YfromIndex(0), &variables::esp::enemies::boxOutline, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Chams XQZ"), XfromIndex(1.6), YfromIndex(1), &variables::esp::enemies::chamsxqz, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Backtrack Point"), XfromIndex(1.6), YfromIndex(2), &variables::esp::enemies::backtrack, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Backtrack Chams"), XfromIndex(1.6), YfromIndex(3), &variables::esp::enemies::backtrackChams, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Is Scoped"), XfromIndex(1.6), YfromIndex(4), &variables::esp::enemies::scopedWarning, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Hostage Warning"), XfromIndex(1.6), YfromIndex(5), &variables::esp::enemies::hostageWarning, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Reload Warning"), XfromIndex(1.6), YfromIndex(6), &variables::esp::enemies::reloadWarning, &variables::gui::bMenuConstant);


					

					addSelectionBox(xorStr("Box"), XfromIndex(2.4), YfromIndex(0), { xorStr("off"),  xorStr("Bounding"), xorStr("Edges"),xorStr("Octagon"), xorStr("3D") }, & variables::esp::enemies::box, & variables::gui::bMenuConstant);
					addSelectionBox(xorStr("Chams"), XfromIndex(2.4), YfromIndex(1.2), { xorStr("off"),  xorStr("plain"), xorStr("flat"),xorStr("wireframe"),xorStr("gold"),xorStr("plastic"),xorStr("platinum") }, & variables::esp::enemies::chams, & variables::gui::bMenuConstant);
					addSelectionBox(xorStr("Glow"), XfromIndex(2.4), YfromIndex(2.4), { xorStr("off"), xorStr("outline"), xorStr("full") }, & variables::esp::enemies::glow, & variables::gui::bMenuConstant);
					addCheckbox(xorStr("Glow health color"), XfromIndex(2.4), YfromIndex(6.0), &variables::esp::enemies::glowhealth, &variables::gui::bMenuConstant);

					addCheckbox(xorStr("Health Value"), XfromIndex(2.4), YfromIndex(3.6), &variables::esp::enemies::healthvalue, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Armour Value"), XfromIndex(2.4), YfromIndex(4.4), &variables::esp::enemies::armorvalue, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Lines"), XfromIndex(2.4), YfromIndex(5.2), &variables::esp::enemies::lines, &variables::gui::bMenuConstant);


					addESPSelector(xorStr(""), XfromIndex(3.8), YfromIndex(0), false, &variables::esp::enemies::enabled, &variables::esp::enemies::visibleOnly, &variables::esp::enemies::healthbar, &variables::esp::enemies::box, &variables::esp::enemies::boxOutline,
						&variables::esp::enemies::name, &variables::esp::enemies::weapon, &variables::esp::enemies::money, &variables::esp::enemies::skeleton, &variables::esp::enemies::distance, &variables::esp::enemies::ammunition, &variables::esp::enemies::chams,
						&variables::esp::enemies::barrel, &variables::esp::enemies::chamsxqz, &variables::esp::enemies::glow, &variables::esp::enemies::reloadWarning, &variables::esp::enemies::scopedWarning, &variables::esp::enemies::defuseWarning, &variables::esp::enemies::hostageWarning, &variables::esp::enemies::helmetESP, &variables::gui::bMenuConstant);
					finalizePage();
				}

				createPage(xorStr("Team"), color(184, 15, 10), XfromIndex(0), YfromIndex(0), NULL);
				{

					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0), &variables::esp::team::enabled, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Visible only"), XfromIndex(0), YfromIndex(1), &variables::esp::team::visibleOnly, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Ingame-Radar"), XfromIndex(0), YfromIndex(2), &variables::esp::team::radar, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Custom-Radar"), XfromIndex(0), YfromIndex(3), &variables::esp::team::cheatradar, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Skeleton (lowfps)"), XfromIndex(0), YfromIndex(4), &variables::esp::team::skeleton, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Has Helmet"), XfromIndex(0), YfromIndex(5), &variables::esp::team::helmetESP, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Is Defusing"), XfromIndex(0), YfromIndex(6), &variables::esp::team::defuseWarning, &variables::gui::bMenuConstant);


					addSelectionCheck(xorStr("Name"), XfromIndex(0.8), YfromIndex(0), &variables::esp::team::name, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Health"), XfromIndex(0.8), YfromIndex(1), &variables::esp::team::healthbar, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Money"), XfromIndex(0.8), YfromIndex(2), &variables::esp::team::money, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Weapon"), XfromIndex(0.8), YfromIndex(3), &variables::esp::team::weapon, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Ammunition"), XfromIndex(0.8), YfromIndex(4), &variables::esp::team::ammunition, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Distance"), XfromIndex(0.8), YfromIndex(5), &variables::esp::team::distance, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Barrel"), XfromIndex(0.8), YfromIndex(6), &variables::esp::team::barrel, &variables::gui::bMenuConstant);


					addCheckbox(xorStr("Box Outline"), XfromIndex(1.6), YfromIndex(0), &variables::esp::team::boxOutline, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Chams XQZ"), XfromIndex(1.6), YfromIndex(1), &variables::esp::team::chamsxqz, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Backtrack Point"), XfromIndex(1.6), YfromIndex(2), &variables::esp::team::backtrack, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Backtrack Chams"), XfromIndex(1.6), YfromIndex(3), &variables::esp::team::backtrackChams, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Is Scoped"), XfromIndex(1.6), YfromIndex(4), &variables::esp::team::scopedWarning, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Hostage Warning"), XfromIndex(1.6), YfromIndex(5), &variables::esp::team::hostageWarning, &variables::gui::bMenuConstant);
					addSelectionCheck(xorStr("Reload Warning"), XfromIndex(1.6), YfromIndex(6), &variables::esp::team::reloadWarning, &variables::gui::bMenuConstant);




					addSelectionBox(xorStr("Box"), XfromIndex(2.4), YfromIndex(0), { xorStr("off"),  xorStr("Bounding"), xorStr("Edges"),xorStr("Octagon"), xorStr("3D") }, & variables::esp::team::box, & variables::gui::bMenuConstant);
					addSelectionBox(xorStr("Chams"), XfromIndex(2.4), YfromIndex(1.2), { xorStr("off"),  xorStr("plain"), xorStr("flat"),xorStr("wireframe"),xorStr("gold"),xorStr("plastic"),xorStr("platinum") }, & variables::esp::team::chams, & variables::gui::bMenuConstant);
					addSelectionBox(xorStr("Glow"), XfromIndex(2.4), YfromIndex(2.4), { xorStr("off"), xorStr("outline"), xorStr("full") }, & variables::esp::team::glow, & variables::gui::bMenuConstant);
					addCheckbox(xorStr("Glow health color"), XfromIndex(2.4), YfromIndex(6.0), &variables::esp::team::glowhealth, &variables::gui::bMenuConstant);

					addCheckbox(xorStr("Health Value"), XfromIndex(2.4), YfromIndex(3.6), &variables::esp::team::healthvalue, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Armour Value"), XfromIndex(2.4), YfromIndex(4.4), &variables::esp::team::armorvalue, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Lines"), XfromIndex(2.4), YfromIndex(5.2), &variables::esp::team::lines, &variables::gui::bMenuConstant);
					

					addESPSelector(xorStr(""), XfromIndex(3.8), YfromIndex(0), false, &variables::esp::team::enabled, &variables::esp::team::visibleOnly, &variables::esp::team::healthbar, &variables::esp::team::box, &variables::esp::team::boxOutline,
						&variables::esp::team::name, &variables::esp::team::weapon, &variables::esp::team::money, &variables::esp::team::skeleton, &variables::esp::team::distance, &variables::esp::team::ammunition, &variables::esp::team::chams,
						&variables::esp::team::barrel, &variables::esp::team::chamsxqz, &variables::esp::team::glow, &variables::esp::team::reloadWarning, &variables::esp::team::scopedWarning, &variables::esp::team::defuseWarning, &variables::esp::team::hostageWarning, &variables::esp::team::helmetESP, &variables::gui::bMenuConstant);
					finalizePage();
				}
				createPage(xorStr("Grenades"), color(126, 25, 27), XfromIndex(0), YfromIndex(0), NULL);
				{


					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0), &variables::esp::grenades::enabled, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Box Outline"), XfromIndex(0), YfromIndex(1.5), &variables::esp::grenades::boxOutline, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Thrown Grenades"), XfromIndex(0), YfromIndex(3), &variables::esp::grenades::thrown, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Dropped Grenades"), XfromIndex(0), YfromIndex(4.5), &variables::esp::grenades::dropped, &variables::gui::bMenuConstant);


					addSelectionBox(xorStr("Box"), XfromIndex(4), YfromIndex(0), { xorStr("off"),  xorStr("Bounding"), xorStr("Edges"),xorStr("Octagon"), xorStr("3D") }, & variables::esp::grenades::box, & variables::gui::bMenuConstant);
					addSelectionBox(xorStr("Name"), XfromIndex(4), YfromIndex(1.5), { xorStr("off"), xorStr("left"), xorStr("right"), xorStr("top"), xorStr("bottom") }, & variables::esp::grenades::name, & variables::gui::bMenuConstant);
					finalizePage();
				}
				createPage(xorStr("Weapons"), color(126, 25, 27), XfromIndex(0), YfromIndex(0), NULL);
				{


					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0), &variables::esp::weapons::enabled, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Box Outline"), XfromIndex(0), YfromIndex(1.5), &variables::esp::weapons::boxOutline, &variables::gui::bMenuConstant);


					addSelectionBox(xorStr("Box"), XfromIndex(4), YfromIndex(0), { xorStr("off"),  xorStr("Bounding"), xorStr("Edges"),xorStr("Octagon"), xorStr("3D") }, &variables::esp::weapons::box, &variables::gui::bMenuConstant);
					addSelectionBox(xorStr("Name"), XfromIndex(4), YfromIndex(1.5), { xorStr("off"), xorStr("left"), xorStr("right"), xorStr("top"), xorStr("bottom") }, &variables::esp::weapons::name, &variables::gui::bMenuConstant);
					finalizePage();
				}
				createPage(xorStr("C4"), color(150, 0, 24), XfromIndex(0), YfromIndex(0), NULL);
				{
					addCheckbox(xorStr(xorStr("Enabled")), XfromIndex(0), YfromIndex(0), &variables::esp::C4::enabled, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Chams XQZ"), XfromIndex(0), YfromIndex(1.5), &variables::esp::C4::XQZchams, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Box Outline"), XfromIndex(0), YfromIndex(3), &variables::esp::C4::boxOutline, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Detonation Timer"), XfromIndex(0), YfromIndex(4.5), &variables::esp::C4::detonationInfo, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Defuse Timer"), XfromIndex(0), YfromIndex(6), &variables::esp::C4::defuseInfo, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Bomb Damage"), XfromIndex(2), YfromIndex(0), &variables::esp::other::bombHealth, &variables::gui::bMenuConstant);



					addSelectionBox(xorStr("Box"), XfromIndex(4), YfromIndex(0), { xorStr("off"),  xorStr("Bounding"), xorStr("Edges"),xorStr("Octagon"), xorStr("3D") }, &variables::esp::C4::box, &variables::gui::bMenuConstant);
					addSelectionBox(xorStr("Name"), XfromIndex(4), YfromIndex(1.5), { xorStr("off"), xorStr("left"), xorStr("right"), xorStr("top"), xorStr("bottom") }, &variables::esp::C4::name, &variables::gui::bMenuConstant);
					addSelectionBox(xorStr("Chams"), XfromIndex(4), YfromIndex(3), { xorStr("off"),  xorStr("plain"), xorStr("flat"),xorStr("wireframe"),xorStr("gold"),xorStr("crystal"),xorStr("platinum") }, &variables::esp::C4::chams, &variables::gui::bMenuConstant);


					finalizePage();

				}
				createPage(xorStr("Other"), color(178, 34, 34), XfromIndex(0), YfromIndex(0));
				{
					addCheckbox(xorStr("Display Damage"), XfromIndex(0), YfromIndex(0), &variables::esp::other::damage, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Display Spectators"), XfromIndex(0), YfromIndex(1.5), &variables::esp::other::spectators, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Death Notices"), XfromIndex(0), YfromIndex(3), &variables::esp::other::DeathFlags, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Draw Aimbot FOV"), XfromIndex(0), YfromIndex(4.5), &variables::esp::other::drawfov, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Draw Aimbot Silent FOV"), XfromIndex(0), YfromIndex(6), &variables::esp::other::drawsilentfov, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Who can see warning"), XfromIndex(1), YfromIndex(0), &variables::esp::other::whocansee, &variables::gui::bMenuConstant);
				
					addSelectionBox(xorStr("Crosshairs"), XfromIndex(4), YfromIndex(0), { xorStr("off"), xorStr("+hair"), xorStr("xhair"), xorStr("-hair") }, &variables::esp::other::crosshairs, &variables::gui::bMenuConstant);

					finalizePage();
				}
				finalizeCluster();
			}
			createCluster(xorStr("Misc"), &variables::gui::bAlwaysTrue); {


				createPage(xorStr("Skinchanger"), color(141, 2, 31), XfromIndex(0), YfromIndex(0), NULL, xorStr("Frequently Used"), true); {

					std::vector<std::string> skins = {};
					for (int skin = 0; skin < skinchanger.m_vSkins.size(); skin++) {
						skins.push_back(skinchanger.m_vSkins[skin].m_sName);
					}
					addListbox(xorStr("Weapons"), XfromIndex(0), YfromIndex(0), 0.61 * temporaryWindow->height,
						{ xorStr("Glock-18"),
						xorStr("P250"),
						xorStr("Desert Eagle"),
						xorStr("Dual Berettas"),
						xorStr("Tec-9"),
						xorStr("CZ75"),
						xorStr("R8 Revolver"),
						xorStr("P2000"),
						xorStr("USP-S"),
						xorStr("Five SeveN"),
						xorStr("Nova"),
						xorStr("XM1014"),
						xorStr("Sawed Off"),
						xorStr("Mag-7"),
						xorStr("MAC-10"),
						xorStr("MP5"),
						xorStr("MP7"),
						xorStr("UMP-45"),
						xorStr("PP-Bizon"),
						xorStr("P90"),
						xorStr("MP9"),
						xorStr("Galil AR"),
						xorStr("Famas"),
						xorStr("AK47"),
						xorStr("M4A4"),
						xorStr("SSG08"),
						xorStr("M4A1-S"),
						xorStr("SG 553"),
						xorStr("AUG"),
						xorStr("AWP"),
						xorStr("G3SG1"),
						xorStr("SCAR-20"),
						xorStr("M249"),
						xorStr("Negev"),
						xorStr("C4"),
						xorStr("Knife"),
						xorStr("Glove") }, &variables::skinchanger::selectedWeapon, &variables::gui::bMenuConstant);




					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::Glock18Skin, &variables::skinchanger::selectedWeapon, 0);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::Glock18Enabled, &variables::skinchanger::selectedWeapon, 0);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::Glock18StatTrack, &variables::skinchanger::selectedWeapon, 0);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::Glock18Seed, &variables::skinchanger::selectedWeapon, 0);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::Glock18Wear, &variables::skinchanger::selectedWeapon, 0);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::Glock18Name, &variables::skinchanger::selectedWeapon, 0);



					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::P250Skin, &variables::skinchanger::selectedWeapon, 1);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::P250Enabled, &variables::skinchanger::selectedWeapon, 1);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::P250StatTrack, &variables::skinchanger::selectedWeapon, 1);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::P250Seed, &variables::skinchanger::selectedWeapon, 1);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::P250Wear, &variables::skinchanger::selectedWeapon, 1);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::P250Name, &variables::skinchanger::selectedWeapon, 1);



					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::DesertEagleSkin, &variables::skinchanger::selectedWeapon, 2);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::DesertEagleEnabled, &variables::skinchanger::selectedWeapon, 2);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::DesertEagleStatTrack, &variables::skinchanger::selectedWeapon, 2);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::DesertEagleSeed, &variables::skinchanger::selectedWeapon, 2);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::DesertEagleWear, &variables::skinchanger::selectedWeapon, 2);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::DesertEagleName, &variables::skinchanger::selectedWeapon, 2);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::DualBerettasSkin, &variables::skinchanger::selectedWeapon, 3);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::DualBerettasEnabled, &variables::skinchanger::selectedWeapon, 3);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::DualBerettasStatTrack, &variables::skinchanger::selectedWeapon, 3);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::DualBerettasSeed, &variables::skinchanger::selectedWeapon, 3);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::DualBerettasWear, &variables::skinchanger::selectedWeapon, 3);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::DualBerettasName, &variables::skinchanger::selectedWeapon, 3);



					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::Tec9Skin, &variables::skinchanger::selectedWeapon, 4);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::Tec9Enabled, &variables::skinchanger::selectedWeapon, 4);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::Tec9StatTrack, &variables::skinchanger::selectedWeapon, 4);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::Tec9Seed, &variables::skinchanger::selectedWeapon, 4);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::Tec9Wear, &variables::skinchanger::selectedWeapon, 4);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::Tec9Name, &variables::skinchanger::selectedWeapon, 4);



					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::CZ75AutoSkin, &variables::skinchanger::selectedWeapon, 5);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::CZ75AutoEnabled, &variables::skinchanger::selectedWeapon, 5);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::CZ75AutoStatTrack, &variables::skinchanger::selectedWeapon, 5);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::CZ75AutoSeed, &variables::skinchanger::selectedWeapon, 5);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::CZ75AutoWear, &variables::skinchanger::selectedWeapon, 5);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::CZ75AutoName, &variables::skinchanger::selectedWeapon, 5);



					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::R8RevolverSkin, &variables::skinchanger::selectedWeapon, 6);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::R8RevolverEnabled, &variables::skinchanger::selectedWeapon, 6);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::R8RevolverStatTrack, &variables::skinchanger::selectedWeapon, 6);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::R8RevolverSeed, &variables::skinchanger::selectedWeapon, 6);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::R8RevolverWear, &variables::skinchanger::selectedWeapon, 6);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::R8RevolverName, &variables::skinchanger::selectedWeapon, 6);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::P2000Skin, &variables::skinchanger::selectedWeapon, 7);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::P2000Enabled, &variables::skinchanger::selectedWeapon, 7);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::P2000StatTrack, &variables::skinchanger::selectedWeapon, 7);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::P2000Seed, &variables::skinchanger::selectedWeapon, 7);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::P2000Wear, &variables::skinchanger::selectedWeapon, 7);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::P2000Name, &variables::skinchanger::selectedWeapon, 7);




					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::USPSSkin, &variables::skinchanger::selectedWeapon, 8);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::USPSEnabled, &variables::skinchanger::selectedWeapon, 8);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::USPSStatTrack, &variables::skinchanger::selectedWeapon, 8);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::USPSSeed, &variables::skinchanger::selectedWeapon, 8);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::USPSWear, &variables::skinchanger::selectedWeapon, 8);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::USPSName, &variables::skinchanger::selectedWeapon, 8);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::FiveSeveNSkin, &variables::skinchanger::selectedWeapon, 9);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::FiveSeveNEnabled, &variables::skinchanger::selectedWeapon, 9);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::FiveSeveNStatTrack, &variables::skinchanger::selectedWeapon, 9);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::FiveSeveNSeed, &variables::skinchanger::selectedWeapon, 9);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::FiveSeveNWear, &variables::skinchanger::selectedWeapon, 9);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::FiveSeveNName, &variables::skinchanger::selectedWeapon, 9);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::NovaSkin, &variables::skinchanger::selectedWeapon, 10);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::NovaEnabled, &variables::skinchanger::selectedWeapon, 10);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::NovaStatTrack, &variables::skinchanger::selectedWeapon, 10);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::NovaSeed, &variables::skinchanger::selectedWeapon, 10);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::NovaWear, &variables::skinchanger::selectedWeapon, 10);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::NovaName, &variables::skinchanger::selectedWeapon, 10);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::XM1014Skin, &variables::skinchanger::selectedWeapon, 11);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::XM1014Enabled, &variables::skinchanger::selectedWeapon, 11);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::XM1014StatTrack, &variables::skinchanger::selectedWeapon, 11);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::XM1014Seed, &variables::skinchanger::selectedWeapon, 11);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::XM1014Wear, &variables::skinchanger::selectedWeapon, 11);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::XM1014Name, &variables::skinchanger::selectedWeapon, 11);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::SawedOffSkin, &variables::skinchanger::selectedWeapon, 12);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::SawedOffEnabled, &variables::skinchanger::selectedWeapon, 12);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::SawedOffStatTrack, &variables::skinchanger::selectedWeapon, 12);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::SawedOffSeed, &variables::skinchanger::selectedWeapon, 12);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::SawedOffWear, &variables::skinchanger::selectedWeapon, 12);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::SawedOffName, &variables::skinchanger::selectedWeapon, 12);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::MAG7Skin, &variables::skinchanger::selectedWeapon, 13);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::MAG7Enabled, &variables::skinchanger::selectedWeapon, 13);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::MAG7StatTrack, &variables::skinchanger::selectedWeapon, 13);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::MAG7Seed, &variables::skinchanger::selectedWeapon, 13);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::MAG7Wear, &variables::skinchanger::selectedWeapon, 13);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::MAG7Name, &variables::skinchanger::selectedWeapon, 13);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::MAC10Skin, &variables::skinchanger::selectedWeapon, 14);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::MAC10Enabled, &variables::skinchanger::selectedWeapon, 14);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::MAC10StatTrack, &variables::skinchanger::selectedWeapon, 14);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::MAC10Seed, &variables::skinchanger::selectedWeapon, 14);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::MAC10Wear, &variables::skinchanger::selectedWeapon, 14);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::MAC10Name, &variables::skinchanger::selectedWeapon, 14);

					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::MP5Skin, &variables::skinchanger::selectedWeapon, 15);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::MP5Enabled, &variables::skinchanger::selectedWeapon, 15);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::MP5StatTrack, &variables::skinchanger::selectedWeapon, 15);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::MP5Seed, &variables::skinchanger::selectedWeapon, 15);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::MP5Wear, &variables::skinchanger::selectedWeapon, 15);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::MP5Name, &variables::skinchanger::selectedWeapon, 15);



					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::MP7Skin, &variables::skinchanger::selectedWeapon, 16);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::MP7Enabled, &variables::skinchanger::selectedWeapon, 16);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::MP7StatTrack, &variables::skinchanger::selectedWeapon, 16);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::MP7Seed, &variables::skinchanger::selectedWeapon, 16);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::MP7Wear, &variables::skinchanger::selectedWeapon, 16);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::MP7Name, &variables::skinchanger::selectedWeapon, 16);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::UMP45Skin, &variables::skinchanger::selectedWeapon, 17);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::UMP45Enabled, &variables::skinchanger::selectedWeapon, 17);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::UMP45StatTrack, &variables::skinchanger::selectedWeapon, 17);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::UMP45Seed, &variables::skinchanger::selectedWeapon, 17);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::UMP45Wear, &variables::skinchanger::selectedWeapon, 17);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::UMP45Name, &variables::skinchanger::selectedWeapon, 17);



					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::PPBIZONSkin, &variables::skinchanger::selectedWeapon, 18);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::PPBIZONEnabled, &variables::skinchanger::selectedWeapon, 18);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::PPBIZONStatTrack, &variables::skinchanger::selectedWeapon, 18);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::PPBIZONSeed, &variables::skinchanger::selectedWeapon, 18);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::PPBIZONWear, &variables::skinchanger::selectedWeapon, 18);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::PPBIZONName, &variables::skinchanger::selectedWeapon, 18);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::P90Skin, &variables::skinchanger::selectedWeapon, 19);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::P90Enabled, &variables::skinchanger::selectedWeapon, 19);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::P90StatTrack, &variables::skinchanger::selectedWeapon, 19);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::P90Seed, &variables::skinchanger::selectedWeapon, 19);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::P90Wear, &variables::skinchanger::selectedWeapon, 19);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::P90Name, &variables::skinchanger::selectedWeapon, 19);



					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::MP9Skin, &variables::skinchanger::selectedWeapon, 20);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::MP9Enabled, &variables::skinchanger::selectedWeapon, 20);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::MP9StatTrack, &variables::skinchanger::selectedWeapon, 20);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::MP9Seed, &variables::skinchanger::selectedWeapon, 20);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::MP9Wear, &variables::skinchanger::selectedWeapon, 20);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::MP9Name, &variables::skinchanger::selectedWeapon, 20);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::GalilARSkin, &variables::skinchanger::selectedWeapon, 21);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::GalilAREnabled, &variables::skinchanger::selectedWeapon, 21);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::GalilARStatTrack, &variables::skinchanger::selectedWeapon, 21);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::GalilARSeed, &variables::skinchanger::selectedWeapon, 21);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::GalilARWear, &variables::skinchanger::selectedWeapon, 21);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::GalilARName, &variables::skinchanger::selectedWeapon, 21);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::FAMASSkin, &variables::skinchanger::selectedWeapon, 22);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::FAMASEnabled, &variables::skinchanger::selectedWeapon, 22);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::FAMASStatTrack, &variables::skinchanger::selectedWeapon, 22);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::FAMASSeed, &variables::skinchanger::selectedWeapon, 22);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::FAMASWear, &variables::skinchanger::selectedWeapon, 22);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::FAMASName, &variables::skinchanger::selectedWeapon, 22);



					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::AK47Skin, &variables::skinchanger::selectedWeapon, 23);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::AK47Enabled, &variables::skinchanger::selectedWeapon, 23);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::AK47StatTrack, &variables::skinchanger::selectedWeapon, 23);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::AK47Seed, &variables::skinchanger::selectedWeapon, 23);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::AK47Wear, &variables::skinchanger::selectedWeapon, 23);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::AK47Name, &variables::skinchanger::selectedWeapon, 23);




					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::M4A4Skin, &variables::skinchanger::selectedWeapon, 24);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::M4A4Enabled, &variables::skinchanger::selectedWeapon, 24);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::M4A4StatTrack, &variables::skinchanger::selectedWeapon, 24);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::M4A4Seed, &variables::skinchanger::selectedWeapon, 24);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::M4A4Wear, &variables::skinchanger::selectedWeapon, 24);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::M4A4Name, &variables::skinchanger::selectedWeapon, 24);



					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::SSG08Skin, &variables::skinchanger::selectedWeapon, 25);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::SSG08Enabled, &variables::skinchanger::selectedWeapon, 25);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::SSG08StatTrack, &variables::skinchanger::selectedWeapon, 25);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::SSG08Seed, &variables::skinchanger::selectedWeapon, 25);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::SSG08Wear, &variables::skinchanger::selectedWeapon, 25);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::SSG08Name, &variables::skinchanger::selectedWeapon, 25);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::M4A1SSkin, &variables::skinchanger::selectedWeapon, 26);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::M4A1SEnabled, &variables::skinchanger::selectedWeapon, 26);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::M4A1SStatTrack, &variables::skinchanger::selectedWeapon, 26);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::M4A1SSeed, &variables::skinchanger::selectedWeapon, 26);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::M4A1SWear, &variables::skinchanger::selectedWeapon, 26);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::M4A1SName, &variables::skinchanger::selectedWeapon, 26);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::SG553Skin, &variables::skinchanger::selectedWeapon, 27);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::SG553Enabled, &variables::skinchanger::selectedWeapon, 27);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::SG553StatTrack, &variables::skinchanger::selectedWeapon, 27);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::SG553Seed, &variables::skinchanger::selectedWeapon, 27);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::SG553Wear, &variables::skinchanger::selectedWeapon, 27);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::SG553Name, &variables::skinchanger::selectedWeapon, 27);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::AUGSkin, &variables::skinchanger::selectedWeapon, 28);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::AUGEnabled, &variables::skinchanger::selectedWeapon, 28);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::AUGStatTrack, &variables::skinchanger::selectedWeapon, 28);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::AUGSeed, &variables::skinchanger::selectedWeapon, 28);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::AUGWear, &variables::skinchanger::selectedWeapon, 28);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::AUGName, &variables::skinchanger::selectedWeapon, 28);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::AWPSkin, &variables::skinchanger::selectedWeapon, 29);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::AWPEnabled, &variables::skinchanger::selectedWeapon, 29);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::AWPStatTrack, &variables::skinchanger::selectedWeapon, 29);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::AWPSeed, &variables::skinchanger::selectedWeapon, 29);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::AWPWear, &variables::skinchanger::selectedWeapon, 29);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::AWPName, &variables::skinchanger::selectedWeapon, 29);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::G3SG1Skin, &variables::skinchanger::selectedWeapon, 30);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::G3SG1Enabled, &variables::skinchanger::selectedWeapon, 30);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::G3SG1StatTrack, &variables::skinchanger::selectedWeapon, 30);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::G3SG1Seed, &variables::skinchanger::selectedWeapon, 30);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::G3SG1Wear, &variables::skinchanger::selectedWeapon, 30);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::G3SG1Name, &variables::skinchanger::selectedWeapon, 30);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::SCAR20Skin, &variables::skinchanger::selectedWeapon, 31);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::SCAR20Enabled, &variables::skinchanger::selectedWeapon, 31);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::SCAR20StatTrack, &variables::skinchanger::selectedWeapon, 31);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::SCAR20Seed, &variables::skinchanger::selectedWeapon, 31);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::SCAR20Wear, &variables::skinchanger::selectedWeapon, 31);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::SCAR20Name, &variables::skinchanger::selectedWeapon, 31);


					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::M249Skin, &variables::skinchanger::selectedWeapon, 32);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::M249Enabled, &variables::skinchanger::selectedWeapon, 32);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::M249StatTrack, &variables::skinchanger::selectedWeapon, 32);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::M249Seed, &variables::skinchanger::selectedWeapon, 32);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::M249Wear, &variables::skinchanger::selectedWeapon, 32);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::M249Name, &variables::skinchanger::selectedWeapon, 32);




					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::NegevSkin, &variables::skinchanger::selectedWeapon, 33);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::NegevEnabled, &variables::skinchanger::selectedWeapon, 33);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::NegevStatTrack, &variables::skinchanger::selectedWeapon, 33);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::NegevSeed, &variables::skinchanger::selectedWeapon, 33);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::NegevWear, &variables::skinchanger::selectedWeapon, 33);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::NegevName, &variables::skinchanger::selectedWeapon, 33);

					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::C4Skin, &variables::skinchanger::selectedWeapon, 34);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::C4Enabled, &variables::skinchanger::selectedWeapon, 34);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::C4StatTrack, &variables::skinchanger::selectedWeapon, 34);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::C4Seed, &variables::skinchanger::selectedWeapon, 34);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::C4Wear, &variables::skinchanger::selectedWeapon, 34);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.3), &variables::skinchanger::C4Name, &variables::skinchanger::selectedWeapon, 34);



					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, skins, &variables::skinchanger::KnifeSkin, &variables::skinchanger::selectedWeapon, 35);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::KnifeEnabled, &variables::skinchanger::selectedWeapon, 35);
					addNumberTextbox(xorStr("Stat-Track"), XfromIndex(4), YfromIndex(1), &variables::skinchanger::KnifeStatTrack, &variables::skinchanger::selectedWeapon, 35);
					addNumberTextbox(xorStr("Seed"), XfromIndex(4), YfromIndex(2), &variables::skinchanger::KnifeSeed, &variables::skinchanger::selectedWeapon, 35);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(3), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::KnifeWear, &variables::skinchanger::selectedWeapon, 35);
					addSelectionBox(xorStr("Model"), XfromIndex(4), YfromIndex(5.3), { xorStr("Default"), xorStr("Karambit"), xorStr("M9 Bayonet"), xorStr("Bayonet"), xorStr("Huntsman"), xorStr("Flip"), xorStr("Gut"), xorStr("Falchion"), xorStr("Bowie"),xorStr("Shadow Daggers"), xorStr("Butterfly"), xorStr("Navaja Knife"), xorStr("Stiletto Knife"),  xorStr("Ursus Knife") , xorStr("Talon Knife"), xorStr("Paracord Knife"),xorStr("Survival Knife"), xorStr("Nomad Knife"), xorStr("Skeleton Knife") }, &variables::skinchanger::KnifeModel, &variables::skinchanger::selectedWeapon, 35);
					addTextbox(xorStr("Name"), XfromIndex(4), YfromIndex(4.1), &variables::skinchanger::KnifeName, &variables::skinchanger::selectedWeapon, 35);



					std::vector<std::string> gloveskins = {};
					for (int glove = 0; glove < skinchanger.m_vGloves.size(); glove++) {
						gloveskins.push_back(skinchanger.m_vGloves[glove].m_sName);
					}
					addSearchableListbox(xorStr("Skins"), XfromIndex(2), YfromIndex(0), temporaryWindow->height * 0.55, gloveskins, &variables::skinchanger::GloveSkin, &variables::skinchanger::selectedWeapon, 36);
					addCheckbox(xorStr("Enabled"), XfromIndex(4), YfromIndex(0), &variables::skinchanger::GloveEnabled, &variables::skinchanger::selectedWeapon, 36);
					addSelectionBox(xorStr("Wear"), XfromIndex(4), YfromIndex(2), { xorStr("Factory New"), xorStr("Minimal Wear"), xorStr("Field Tested"), xorStr("Well Worn"), xorStr("Battle Scarred") }, &variables::skinchanger::GloveWear, &variables::skinchanger::selectedWeapon, 36);
					addSelectionBox(xorStr("Model"), XfromIndex(4), YfromIndex(1), { "Default", "Bloodhound", "Driver", "HandWraps", "Moto", "Specialist", "Sport", "Hydra" }, &variables::skinchanger::GloveModel, &variables::skinchanger::selectedWeapon, 36);


					addButton(xorStr("Update Skins"), XfromIndex(4), YfromIndex(6.5), -1, &FU::FullUpdate, &variables::gui::bMenuConstant, 1);
					finalizePage();
				}
				createPage(xorStr("Hacks"), color(124, 10, 2), XfromIndex(0), YfromIndex(0), NULL, xorStr("Frequently Used")); {

					//addCheckbox(xorStr("Bhop Humanisation"), XfromIndex(1), YfromIndex(2), &variables::misc::bhop_humanisation, &variables::gui::bMenuConstant);

					addCheckbox(xorStr("Left handed knife"), XfromIndex(0), YfromIndex(0), &variables::misc::leftHandedKnife, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Reveal Ranks"), XfromIndex(1), YfromIndex(0), &variables::misc::revealranks, &variables::gui::bMenuConstant);


					addCheckbox(xorStr("Nightmode"), XfromIndex(0), YfromIndex(1.5), &variables::misc::nightmode, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Autopistol"), XfromIndex(1), YfromIndex(1.5), &variables::misc::autoPistol, &variables::gui::bMenuConstant);

					addCheckbox(xorStr("AutoStrafe"), XfromIndex(0), YfromIndex(3), &variables::misc::autoStrafe, &variables::gui::bMenuConstant);
					addCheckbox(xorStr("Bhop"), XfromIndex(1), YfromIndex(3), &variables::misc::bhop, &variables::gui::bMenuConstant);
					//addCheckbox(xorStr("Floating Ragdolls"), XfromIndex(0), YfromIndex(4.5), &variables::misc::floating , & variables::gui::bMenuConstant);
					addKeybinderB(xorStr("Mirror Cam"), XfromIndex(0), YfromIndex(4.5), &variables::misc::mirrorview, &variables::gui::bMenuConstant);
					addKeybinderB(xorStr("Height Advantage"), XfromIndex(1), YfromIndex(4.5), &variables::misc::mapheight, &variables::gui::bMenuConstant);
					addKeybinderB(xorStr("Freecam"), XfromIndex(0), YfromIndex(6), &variables::misc::freemove, &variables::gui::bMenuConstant);
					addTextbox(xorStr("Clantag"), XfromIndex(1), YfromIndex(6), &variables::misc::clantag, &variables::gui::bMenuConstant);
					addSlider(xorStr("Asus Walls"), XfromIndex(3), YfromIndex(0), &variables::misc::asus, 0, 100, &variables::gui::bMenuConstant);
					addSlider(xorStr("FOV-Game"), XfromIndex(3), YfromIndex(1), &variables::misc::gamefov, 0, 64, &variables::gui::bMenuConstant);
					//addSlider(xorStr("Bhop Missing Probablity (1/X)"), XfromIndex(3), YfromIndex(2), &variables::misc::bhop_probability, 0, 100, &variables::gui::bMenuConstant);

					//addSlider(xorStr("VIEW-Game"), XfromIndex(3), YfromIndex(2), &variables::misc::viewfov, 0, 150, &variables::gui::bMenuConstant);

					addCheckbox(xorStr("Grenade Helper"), XfromIndex(3), YfromIndex(3), &variables::misc::grenade, &variables::gui::bMenuConstant);
					addSelectionBox(xorStr("Particle Trail"), XfromIndex(3), YfromIndex(4.5), {xorStr("Off"), xorStr("Energy"), xorStr("Muzzle"),  xorStr("Smoke"),  xorStr("Sparks") }, &variables::misc::trailParticles, & variables::gui::bMenuConstant);
					addSlider(xorStr("Particle Rate"), XfromIndex(3), YfromIndex(6), &variables::misc::rateOfParticle, 0, 10, &variables::gui::bMenuConstant);

					
					finalizePage();
				}
				createPage(xorStr("Statistics"), color(124, 10, 2), XfromIndex(0), YfromIndex(0), NULL, xorStr("Frequently Used")); {

					addLabelValue(xorStr("Headshots"), XfromIndex(0), YfromIndex(0), &variables::misc::statistics::iHeadshots, &variables::gui::bMenuConstant);
					addLabelValue(xorStr("Kills"), XfromIndex(0), YfromIndex(0.75), &variables::misc::statistics::iKills, &variables::gui::bMenuConstant);
					addLabelValue(xorStr("Deaths"), XfromIndex(0), YfromIndex(1.5), &variables::misc::statistics::iDeaths, &variables::gui::bMenuConstant);
					addLabel(xorStr("More to come..."), XfromIndex(0), YfromIndex(2.25),  &variables::gui::bMenuConstant);

					finalizePage();
				}
				finalizeCluster();
				createCluster(xorStr("Settings"), &variables::gui::bAlwaysTrue); {
					createPage(xorStr("Configurations"), color(94, 25, 20), XfromIndex(0), YfromIndex(0), NULL, xorStr("Frequently Used"), true); {


						addListboxAdjustable(xorStr("Configurations"), XfromIndex(0), YfromIndex(0), 0.61 * temporaryWindow->height, &SETTINGS::Configurations, &SETTINGS::m_iSelectedIndex, &variables::gui::bMenuConstant);

						addTextbox(xorStr(xorStr("Name")), XfromIndex(3), YfromIndex(0), &SETTINGS::m_sName, &variables::gui::bMenuConstant);
						float pad = (YfromIndex(2.5) - YfromIndex(1.5)) / 4;
						addButton(xorStr("Save"), XfromIndex(3), YfromIndex(1.5), (boxMenuWidth / 2) - pad, SETTINGS::SaveConfigurationz, &variables::gui::bMenuConstant);
						addButton(xorStr("Load"), XfromIndex(3) + (boxMenuWidth / 2) + pad, YfromIndex(1.5), (boxMenuWidth / 2) - pad, SETTINGS::LoadConfigurationz, &variables::gui::bMenuConstant);

						addButton(xorStr("Default"), XfromIndex(3), YfromIndex(2.5), (boxMenuWidth / 2) - pad, SETTINGS::SetDefault, &variables::gui::bMenuConstant);
						addButton(xorStr("Refresh"), XfromIndex(3) + (boxMenuWidth / 2) + pad, YfromIndex(2.5), (boxMenuWidth / 2) - pad, SETTINGS::RefreshSettings, &variables::gui::bMenuConstant);

						addButton(xorStr("Add"), XfromIndex(3), YfromIndex(3.5), (boxMenuWidth / 2) - pad, SETTINGS::NewConfiguration, &variables::gui::bMenuConstant);
						addButton(xorStr("Delete"), XfromIndex(3) + (boxMenuWidth / 2) + pad, YfromIndex(3.5), (boxMenuWidth / 2) - pad, SETTINGS::DeleteConfiguration, &variables::gui::bMenuConstant);

						//addButton(xorStr("Rename"), XfromIndex(3), YfromIndex(4.5), boxMenuWidth, SETTINGS::RenameConfig, &variables::gui::bMenuConstant);

						finalizePage();
					}
					/*createPage(xorStr("Debug"), color(125, 125, 125), XfromIndex(0), YfromIndex(0), NULL);
					{
						addLabel(xorStr("This tab is intended for debugging if you are experiencing"), XfromIndex(3), YfromIndex(0.5), &variables::gui::bMenuConstant);
						addLabel(xorStr("issues with the cheat, such as low FPS."), XfromIndex(3), YfromIndex(1), &variables::gui::bMenuConstant);
						addLabel(xorStr("Step 1) Go ingame, try to trigger low FPS"), XfromIndex(3), YfromIndex(1.5), &variables::gui::bMenuConstant);
						addLabel(xorStr("Step 2) Run the debug test"), XfromIndex(3), YfromIndex(2), &variables::gui::bMenuConstant);
						addLabel(xorStr("Step 3) Post a screenshot of the data on the forum"), XfromIndex(3), YfromIndex(2.5), &variables::gui::bMenuConstant);
						


						addButton(xorStr("Run Debug Test"), XfromIndex(3), YfromIndex(3), -1, &DEBUG::activate, &variables::gui::bMenuConstant);
						addGraph(xorStr("Debug data"), XfromIndex(0), YfromIndex(0), &variables::debug::fpsData, &variables::gui::bMenuConstant);

						finalizePage();
					}*/
						/*
					createPage(xorStr("Updates"), color(125, 125, 125), XfromIndex(0), YfromIndex(0), NULL);
					{
						addListbox(xorStr("Updates"), XfromIndex(0), YfromIndex(0), 0.61 * temporaryWindow->height,
							{ xorStr("29/10/19"),
							  xorStr("30/10/19"),
							  xorStr("04/11/19"),
							  xorStr("06/11/19"),
							 xorStr("08/11/19"),
							 xorStr("10/11/19"),
							 xorStr("17/11/19"),
							xorStr("18/11/19"),
							xorStr("19/11/19"),
							xorStr("26/11/19"),
							xorStr("28/11/19"),
							xorStr("30/11/19"),
							xorStr("01/12/19"),
							xorStr("06/12/19"), 
							xorStr("15/12/19"),
							xorStr("07/01/20"),
							xorStr("03/02/20"),
							xorStr("08/02/20"),
							xorStr("11/02/20"),
							xorStr("26/02/20"),
							xorStr("03/03/20"),
							xorStr("04/03/20"),
							xorStr("12/03/20"),
							xorStr("28/03/20"),
							xorStr("24/04/20"),
							xorStr("04/08/20") }, &variables::updates::update, &variables::gui::bMenuConstant);

						addLabel(xorStr("- Chams will now not show through smoke"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 0);
						addLabel(xorStr("- Scrolling added to listboxes"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 0);
						addLabel(xorStr("- Added update log"), XfromIndex(2.3), YfromIndex(1.5), &variables::updates::update, 0);
						addLabel(xorStr("- Added skeleton"), XfromIndex(2.3), YfromIndex(2), &variables::updates::update, 0);
						addLabel(xorStr("- Added barrel"), XfromIndex(2.3), YfromIndex(2.5), &variables::updates::update, 0);
						addLabel(xorStr("- Fixed colors not loading"), XfromIndex(2.3), YfromIndex(3), &variables::updates::update, 0);
						addLabel(xorStr("- Added triggerbot"), XfromIndex(2.3), YfromIndex(3.5), &variables::updates::update, 0);
						addLabel(xorStr("- Updated debug tab"), XfromIndex(2.3), YfromIndex(4), &variables::updates::update, 0);


						addLabel(xorStr("- FPS improvements"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 1);
						addLabel(xorStr("- Debug options changed"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 1);
						addLabel(xorStr("- Added distance ESP"), XfromIndex(2.3), YfromIndex(1.5), &variables::updates::update, 1);


						addLabel(xorStr("- Fixed Aimbot glitch"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 2);
						addLabel(xorStr("- Added custom radar"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 2);


						addLabel(xorStr("- Additional Stabalisation"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 3);
						addLabel(xorStr("- Bhop readded"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 3);

						addLabel(xorStr("- Added barrel colour"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 4);
						addLabel(xorStr("- Added skeleton colour"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 4);
						addLabel(xorStr("- Added distance colour"), XfromIndex(2.3), YfromIndex(1.5), &variables::updates::update, 4);
						addLabel(xorStr("- Menu scaling changed to be uniform"), XfromIndex(2.3), YfromIndex(2), &variables::updates::update, 4);
						addLabel(xorStr("- Bug fixes"), XfromIndex(2.3), YfromIndex(2.5), &variables::updates::update, 4);
						addLabel(xorStr("- Config tab changed"), XfromIndex(2.3), YfromIndex(3), &variables::updates::update, 4);


						addLabel(xorStr("- Added crash checker"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 5);
						addLabel(xorStr("- Changed UI elements"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 5);

						addLabel(xorStr("- Crashing bug fixed"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 6);
						addLabel(xorStr("- FPS patches"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 6);
						addLabel(xorStr("- ESP boxes realligned"), XfromIndex(2.3), YfromIndex(1.5), &variables::updates::update, 6);

						addLabel(xorStr("- ESP works in dangerzone"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 7);
						addLabel(xorStr("- Cheat updated for update"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 7);
						addLabel(xorStr("- Additional crash fixes"), XfromIndex(2.3), YfromIndex(1.5), &variables::updates::update, 7);
						
						addLabel(xorStr("- Knife animations fixed"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 8);
						addLabel(xorStr("- Fixed box outline not appearing"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 8);
						addLabel(xorStr("- Added draw backtrack"), XfromIndex(2.3), YfromIndex(1.5), &variables::updates::update, 8);
						
						
						addLabel(xorStr("- Stability fixes"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 9);
						addLabel(xorStr("- Added backtrack chams"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 9);
						addLabel(xorStr("- Added backtrack points"), XfromIndex(2.3), YfromIndex(1.5), &variables::updates::update, 9);
						addLabel(xorStr("- Fixed RCS Glitch"), XfromIndex(2.3), YfromIndex(2), &variables::updates::update, 9);
						addLabel(xorStr("- Added whocansee"), XfromIndex(2.3), YfromIndex(2.5), &variables::updates::update, 9);

						addLabel(xorStr("- Stability fixes (Thanks xcc5)"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 10);
						addLabel(xorStr("- Added RCS Enable"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 10);
						addLabel(xorStr("- Fixed RCS Glitch corrected"), XfromIndex(2.3), YfromIndex(1.5), &variables::updates::update, 10);
						addLabel(xorStr("- Skeleton color fixed (Thanks xcc5)"), XfromIndex(2.3), YfromIndex(2), &variables::updates::update, 10);
						addLabel(xorStr("- Backtrack point glitch fixed (Thanks xcc5)"), XfromIndex(2.3), YfromIndex(2.5), &variables::updates::update, 10);

						addLabel(xorStr("- Hopefully final stability update"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 11);
						addLabel(xorStr("- FOV Fixed (thanks louis)"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 11);

						addLabel(xorStr("- Added Grenade and Weapon ESP"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 12);
						addLabel(xorStr("- Fixed skinchanger not loading skins"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 12);
						addLabel(xorStr("- Fixed sliders not saving (Thanks xcc5 again!)"), XfromIndex(2.3), YfromIndex(1.5), &variables::updates::update, 12);


						addLabel(xorStr("- Rearranged aimbot tabs"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 13);
						addLabel(xorStr("- Readded crash log"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 13);
						

						addLabel(xorStr("- Crash Fixes"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 14);

						addLabel(xorStr("- Added freelook"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 15);
						addLabel(xorStr("- Added mirror cam"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 15);
						addLabel(xorStr("- Added height view"), XfromIndex(2.3), YfromIndex(1.5), &variables::updates::update, 15);

						addLabel(xorStr("- Experimental fix"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 16);
						addLabel(xorStr("- Triggerbot hitbox save fix"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 16);
				
						addLabel(xorStr("- Readded features"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 17);
						addLabel(xorStr("- Added What's New Section"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 17);
						addLabel(xorStr("- Added Glow"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 18);
						addLabel(xorStr("- Crash Fix"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 18);


						addLabel(xorStr("- Experimental Crash Fix"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 19);
						addLabel(xorStr("- Added 3D Box"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 19);
						
						addLabel(xorStr("- Readded chams"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 20);
						addLabel(xorStr("- Added statistics page"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 20);
						addLabel(xorStr("- Readded night mode"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 20);

						addLabel(xorStr("- Triggerbot crash fix"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 21);

						addLabel(xorStr("- Added asus walls"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 22);
						addLabel(xorStr("- Added grenade helper"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 22);
						addLabel(xorStr("- Added Particle trail"), XfromIndex(2.3), YfromIndex(1.5), &variables::updates::update, 22);


						addLabel(xorStr("- Added reload warning"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 23);
						addLabel(xorStr("- Added hostage warning"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 23);
						addLabel(xorStr("- Added scope warning"), XfromIndex(2.3), YfromIndex(1.5), &variables::updates::update, 23);
						addLabel(xorStr("- Added helmet esp"), XfromIndex(2.3), YfromIndex(2), &variables::updates::update, 23);
						addLabel(xorStr("- Added defuse warning"), XfromIndex(2.3), YfromIndex(2.5), &variables::updates::update, 23);


						addLabel(xorStr("- Changed grenade throw thickensss"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 25);
						addLabel(xorStr("- Changed grenade throw color"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 25);
						addLabel(xorStr("- Readded FOV changer"), XfromIndex(2.3), YfromIndex(1.5), &variables::updates::update, 25);
						addLabel(xorStr("- Added clan changer"), XfromIndex(2.3), YfromIndex(2), &variables::updates::update, 25);
						addLabel(xorStr("- Fixed Mirrorcam"), XfromIndex(2.3), YfromIndex(2.5), &variables::updates::update, 25);
						addLabel(xorStr("- Fixed Free Cam"), XfromIndex(2.3), YfromIndex(3), &variables::updates::update, 25);
						addLabel(xorStr("- Fixed Height Cam"), XfromIndex(2.3), YfromIndex(3.5), &variables::updates::update, 25);
						

						addLabel(xorStr("- Added multiple fixes"), XfromIndex(2.3), YfromIndex(0.5), &variables::updates::update, 25);
						addLabel(xorStr("- Added lines"), XfromIndex(2.3), YfromIndex(1), &variables::updates::update, 25);
						addLabel(xorStr("- Added accurate bomb damage"), XfromIndex(2.3), YfromIndex(1.5), &variables::updates::update, 25);

						finalizePage();
					}*/
					createPage(xorStr("Colors"), color(162, 10, 20), XfromIndex(0), YfromIndex(0), NULL);
					{
						addListbox(xorStr("Colors"), XfromIndex(0), YfromIndex(0), 0.61 * temporaryWindow->height,
							{ xorStr("GUI Background"),
							xorStr("GUI Primary"),
							xorStr("GUI Text"),

							xorStr("Enemy Box Visible"),
							xorStr("Enemy Box Invisible"),
							xorStr("Team Box Visible"),
							xorStr("Team Box Invisible"),

							xorStr("Enemy Name Visible"),
							xorStr("Enemy Name Invisible"),
							xorStr("Team Name Visible"),
							xorStr("Team Name Invisible"),


							xorStr("Enemy Weapon Visible"),
							xorStr("Enemy Weapon Invisible"),
							xorStr("Team Weapon Visible"),
							xorStr("Team Weapon Invisible"),

							xorStr("Enemy Health Visible"),
							xorStr("Enemy Health Invisible"),
							xorStr("Team Health Visible"),
							xorStr("Team Health Invisible"),

							xorStr("Enemy Money Visible"),
							xorStr("Enemy Money Invisible"),
							xorStr("Team Money Visible"),
							xorStr("Team Money Invisible"),

							xorStr("Enemy Ammunition Visible"),
							xorStr("Enemy Ammunition Invisible"),
							xorStr("Team Ammunition Visible"),
							xorStr("Team Ammunition Invisible"),

							xorStr("Enemy Chams Visible"),
							xorStr("Enemy Chams Invisible"),
							xorStr("Team Chams Visible"),
							xorStr("Team Chams Invisible") ,


							xorStr("Enemy Barrel Visible"),
							xorStr("Enemy Barrel Invisible"),
							xorStr("Team Barrel Visible"),
							xorStr("Team Barrel Invisible")

							 ,
							xorStr("Enemy Distance Visible"),
							xorStr("Enemy Distance Invisible"),
							xorStr("Team Distance Visible"),
							xorStr("Team Distance Invisible") ,

							xorStr("Enemy Skeleton Visible"),
							xorStr("Enemy Skeleton Invisible"),
							xorStr("Team Skeleton Visible"),
							xorStr("Team Skeleton Invisible"),
							
							
							xorStr("Enemy Reload Visible"),
							xorStr("Enemy Reload Invisible"),
							xorStr("Team Reload Visible"),
							xorStr("Team Reload Invisible"),
							
							xorStr("Enemy Scoped Visible"),
							xorStr("Enemy Scoped Invisible"),
							xorStr("Team Scoped Visible"),
							xorStr("Team Scoped Invisible"),
							

							xorStr("Enemy Hostage Visible"),
							xorStr("Enemy Hostage Invisible"),
							xorStr("Team Hostage Visible"),
							xorStr("Team Hostage Invisible"),

							xorStr("Enemy Defusing Visible"),
							xorStr("Enemy Defusing Invisible"),
							xorStr("Team Defusing Visible"),
							xorStr("Team Defusing Invisible"),

							xorStr("Enemy Helmet Visible"),
							xorStr("Enemy Helmet Invisible"),
							xorStr("Team Helmet Visible"),
							xorStr("Team Helmet Invisible")
							},
							&variables::gui::colors::index, &variables::gui::bMenuConstant);


						addColorPicker(xorStr("GUI Background"), XfromIndex(2.3), YfromIndex(0), &variables::gui::colors::background, &variables::gui::colors::index, 0);
						addSlider(xorStr("GUI Secondary Brightness"), XfromIndex(2.3), YfromIndex(6), &variables::gui::colors::lighterBackgroundHuePlus, -30, 30, &variables::gui::colors::index, 0);
						addColorPicker(xorStr("GUI Primary"), XfromIndex(2.3), YfromIndex(0), &variables::gui::colors::primary, &variables::gui::colors::index, 1);
						addColorPicker(xorStr("GUI Text"), XfromIndex(2.3), YfromIndex(0), &variables::gui::colors::text, &variables::gui::colors::index, 2);


						addColorPicker(xorStr("Enemy Box Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::boxVisible, &variables::gui::colors::index, 3);
						addColorPicker(xorStr("Enemy Box Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::boxInvisible, &variables::gui::colors::index, 4);
						addColorPicker(xorStr("Team Box Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::boxVisible, &variables::gui::colors::index, 5);
						addColorPicker(xorStr("Team Box Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::boxInvisible, &variables::gui::colors::index, 6);


						addColorPicker(xorStr("Enemy Name Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::nameVisible, &variables::gui::colors::index, 7);
						addColorPicker(xorStr("Enemy Name Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::nameInvisible, &variables::gui::colors::index, 8);
						addColorPicker(xorStr("Team Name Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::nameVisible, &variables::gui::colors::index, 9);
						addColorPicker(xorStr("Team Name Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::nameInvisible, &variables::gui::colors::index, 10);


						addColorPicker(xorStr("Enemy Weapon Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::weaponVisible, &variables::gui::colors::index, 11);
						addColorPicker(xorStr("Enemy Weapon Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::weaponInvisible, &variables::gui::colors::index, 12);
						addColorPicker(xorStr("Team Weapon Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::weaponVisible, &variables::gui::colors::index, 13);
						addColorPicker(xorStr("Team Weapon Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::weaponInvisible, &variables::gui::colors::index, 14);


						addColorPicker(xorStr("Enemy Health Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::healthVisible, &variables::gui::colors::index, 15);
						addColorPicker(xorStr("Enemy Health Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::healthInvisible, &variables::gui::colors::index, 16);
						addColorPicker(xorStr("Team Health Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::healthVisible, &variables::gui::colors::index, 17);
						addColorPicker(xorStr("Team Health Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::healthInvisible, &variables::gui::colors::index, 18);

						addColorPicker(xorStr("Enemy Money Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::moneyVisible, &variables::gui::colors::index, 19);
						addColorPicker(xorStr("Enemy Money Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::moneyInvisible, &variables::gui::colors::index, 20);
						addColorPicker(xorStr("Team Money Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::moneyVisible, &variables::gui::colors::index, 21);
						addColorPicker(xorStr("Team Money Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::moneyInvisible, &variables::gui::colors::index, 22);


						addColorPicker(xorStr("Enemy Ammunition Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::ammunitionVisible, &variables::gui::colors::index, 23);
						addColorPicker(xorStr("Enemy Ammunition Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::ammunitionInvisible, &variables::gui::colors::index, 24);
						addColorPicker(xorStr("Team Ammunition Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::ammunitionVisible, &variables::gui::colors::index, 25);
						addColorPicker(xorStr("Team Ammunition Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::ammunitionInvisible, &variables::gui::colors::index, 26);


						addColorPicker(xorStr("Enemy Chams Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::chamsVisible, &variables::gui::colors::index, 27);
						addColorPicker(xorStr("Enemy Chams Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::chamsInvisible, &variables::gui::colors::index, 28);
						addColorPicker(xorStr("Team Chams Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::chamsVisible, &variables::gui::colors::index, 29);
						addColorPicker(xorStr("Team Chams Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::chamsInvisible, &variables::gui::colors::index, 30);


						addColorPicker(xorStr("Enemy Barrel Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::barrelVisible, &variables::gui::colors::index, 31);
						addColorPicker(xorStr("Enemy Barrel Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::barrelInvisible, &variables::gui::colors::index, 32);
						addColorPicker(xorStr("Team Barrel Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::barrelVisible, &variables::gui::colors::index, 33);
						addColorPicker(xorStr("Team Barrel Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::barrelInvisible, &variables::gui::colors::index, 34);

						addColorPicker(xorStr("Enemy Distance Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::distanceVisible, &variables::gui::colors::index, 35);
						addColorPicker(xorStr("Enemy Distance Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::distanceInvisible, &variables::gui::colors::index, 36);
						addColorPicker(xorStr("Team Distance Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::distanceVisible, &variables::gui::colors::index, 37);
						addColorPicker(xorStr("Team Distance Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::distanceInvisible, &variables::gui::colors::index, 38);

						addColorPicker(xorStr("Enemy Skeleton Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::skeletonVisible, &variables::gui::colors::index, 39);
						addColorPicker(xorStr("Enemy Skeleton Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::skeletonInvisible, &variables::gui::colors::index, 40);
						addColorPicker(xorStr("Team Skeleton Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::skeletonVisible, &variables::gui::colors::index, 41);
						addColorPicker(xorStr("Team Skeleton Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::skeletonInvisible, &variables::gui::colors::index, 42);


						addColorPicker(xorStr("Enemy Reload Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::reloadWarningVisible, &variables::gui::colors::index, 43);
						addColorPicker(xorStr("Enemy Reload Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::reloadWarningInvisible, &variables::gui::colors::index, 44);
						addColorPicker(xorStr("Team Reload Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::reloadWarningVisible, &variables::gui::colors::index, 45);
						addColorPicker(xorStr("Team  Reload Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::reloadWarningInvisible, &variables::gui::colors::index, 46);


						addColorPicker(xorStr("Enemy Scoped Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::scopedWarningVisible, &variables::gui::colors::index, 47);
						addColorPicker(xorStr("Enemy Scoped Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::scopedWarningInvisible, &variables::gui::colors::index, 48);
						addColorPicker(xorStr("Team Scoped Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::scopedWarningVisible, &variables::gui::colors::index, 49);
						addColorPicker(xorStr("Team  Scoped Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::scopedWarningInvisible, &variables::gui::colors::index, 50);
						
						addColorPicker(xorStr("Enemy Hostage Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::hostageWarningVisible, &variables::gui::colors::index, 51);
						addColorPicker(xorStr("Enemy Hostage Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::hostageWarningInvisible, &variables::gui::colors::index, 52);
						addColorPicker(xorStr("Team Hostage Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::hostageWarningVisible, &variables::gui::colors::index, 53);
						addColorPicker(xorStr("Team Hostage Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::hostageWarningInvisible, &variables::gui::colors::index, 54);


						addColorPicker(xorStr("Enemy Defusing Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::defuseWarningVisible, &variables::gui::colors::index, 55);
						addColorPicker(xorStr("Enemy Defusing Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::defuseWarningInvisible, &variables::gui::colors::index, 56);
						addColorPicker(xorStr("Team Defusing Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::defuseWarningVisible, &variables::gui::colors::index, 57);
						addColorPicker(xorStr("Team Defusing Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::defuseWarningInvisible, &variables::gui::colors::index, 58);
						

						addColorPicker(xorStr("Enemy Helmet Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::helmetESPVisible, &variables::gui::colors::index, 59);
						addColorPicker(xorStr("Enemy Helmet Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::enemies::helmetESPInvisible, &variables::gui::colors::index, 60);
						addColorPicker(xorStr("Team Helmet Visible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::helmetESPVisible, &variables::gui::colors::index, 61);
						addColorPicker(xorStr("Team Helmet Invisible"), XfromIndex(2.3), YfromIndex(0), &variables::esp::team::helmetESPInvisible, &variables::gui::colors::index, 62);

						finalizePage();
					}
					finalizeCluster();
				}
			}
			finalizeWindow();
		}
		SETTINGS::RefreshSettings();

		
		runUpdateCheck();
		bSetup = true;
	}
	

	float currentVersion = 5.128;
	std::vector<std::shared_ptr<popupMessage>> alertMessages;
	int controlIncrementer = 0;
	bool bSetup = false;
	std::shared_ptr <edgeWindow>temporaryWindow;
	std::shared_ptr <edgeCluster> tempoaryCluster;
	std::shared_ptr <edgePage> tempoaryPage;
	std::vector<std::shared_ptr<edgeWindow>> Windows;
};
