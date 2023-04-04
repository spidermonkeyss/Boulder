#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../Dependencies/stb_image/stb_image.h"

int Texture::debug_texture_count = 0;

void Texture::Create2DTexture()
{
	GLCall(glGenTextures(1, &boulder_textureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, boulder_textureID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, boulder_localBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (boulder_localBuffer)
		stbi_image_free(boulder_localBuffer);
}

Texture::Texture()
	: boulder_textureID(0), filePath(""), boulder_localBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	std::cout << "Texture created id:" << boulder_textureID << std::endl;
	debug_texture_count++;
}

Texture::Texture(const std::string& filePath)
	: boulder_textureID(0), filePath(filePath), boulder_localBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	boulder_localBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	Create2DTexture();

	std::cout << "Texture created id:" << boulder_textureID << std::endl;
	debug_texture_count++;
}

Texture::~Texture()
{
	std::cout << "Texture deleted id:" << boulder_textureID << std::endl;
	GLCall(glDeleteTextures(1, &boulder_textureID));
	debug_texture_count--;
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, boulder_textureID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::CreateTexture(unsigned char* buffer, int width, int height, int bpp)
{
	//if (m_RendererID != 0)
	//{
	//	std::cout << "Texture deleted id:" << m_RendererID << std::endl;
	//	GLCall(glDeleteTextures(1, &m_RendererID));
	//	m_RendererID = 0;
	//	debug_texture_count--;
	//}

	boulder_localBuffer = buffer;
	m_Width = width;
	m_Height = height;
	m_BPP = bpp;
	Create2DTexture();
}

unsigned char* Texture::GetTexture(const std::string& filePath, int* width, int* height, int* bpp)
{
	stbi_set_flip_vertically_on_load(1);
	return stbi_load(filePath.c_str(), width, height, bpp, 4);
}