#pragma once

class VTextureInternal
{
public:
	
};

class VTexture
{
public:
	
private:
	char pad_0x0000[0x50]; //0x0000
public:
	VTextureInternal** m_pTextureHandles; //0x0050 
};