#pragma once
#include "Renderer.h"
class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& filePath);
	Texture(unsigned char* textureBuffer, int width, int height, int BPP);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	void UpdateTexture(unsigned char* textureBuffer);

	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }

};

