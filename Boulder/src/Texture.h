#pragma once
#include "GLCall.h"
#include <vector>

class Texture
{
private:
	unsigned int boulder_textureID;
	std::string filePath;
	unsigned char* boulder_localBuffer;
	int m_Width, m_Height, m_BPP;

	void Create2DTexture();
public:
	Texture();
	Texture(const std::string& filePath);
	~Texture();

	static int debug_texture_count;

	void Bind(unsigned int slot = 0) const;
	void Unbine() const;

	void CreateTexture(unsigned char* buffer, int width, int height, int bpp);
	
	static unsigned char* GetTexture(const std::string& filePath, int* width, int* height, int* bpp);

	inline int GetRenderID() const { return boulder_textureID; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline std::string GetFilePath() const { return filePath; }
};