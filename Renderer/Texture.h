#pragma once
#include "Renderer.h"

enum TextureType{Diffuse = 1, Specular = 2, Normal = 3};

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	TextureType m_type;
public:
	Texture(const std::string& filePath, TextureType type = Diffuse);
	Texture(unsigned char* textureBuffer, int width, int height, int BPP, TextureType type);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	void UpdateTexture(unsigned char* textureBuffer);

	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }
	inline std::string GetFilePath() {return m_FilePath;}

};

