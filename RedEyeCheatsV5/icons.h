#pragma once

#include <Windows.h>
#include <string>
struct imageData {
	imageData(int w_, int h_) {
		m_iW = w_; m_iH = h_;
	}
	
	uint32_t m_iTexture{0};
	uint32_t m_iW, m_iH;
}; 


namespace images
{
	extern imageData colorpicker;
	extern imageData colorgradient;
	extern imageData csgocharacter;

	extern imageData csgoCTDefault;
	extern imageData csgoCTChams;
	extern imageData csgoCTWireframe;
	extern imageData csgoCTGold;
	extern imageData csgoCTPlastic;
	extern imageData csgoCTplatinum;
	extern imageData csgoTDefault;
	extern imageData csgoTChams;
	extern imageData csgoTWireframe;
	extern imageData csgoTGold;
	extern imageData csgoTPlastic;
	extern imageData csgoTplatinum;

	extern std::uint8_t* load_image(unsigned short id, int width, int height, const std::string& type = "PNG");
	extern void cacheImages();
	extern bool imagesCached;
}
















