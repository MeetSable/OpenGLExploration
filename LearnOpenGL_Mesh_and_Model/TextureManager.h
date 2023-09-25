#pragma once
#include <vector>
#include "Texture.h"

class TextureManager
{
private:
    std::vector<Texture*> m_textures;
public:
    TextureManager(){}
    ~TextureManager()
    {
        for(auto &texture : m_textures) texture->~Texture();
    }
    int AddTexture(const char* path, TextureType type)
    {
        for(int i = 0 ; i < m_textures.size(); i++)
        {
            if(std::strcmp(m_textures[i]->GetFilePath().c_str(), path) == 0) return i;
        }
        Texture *temp_tex = new Texture(path, type);
        m_textures.push_back(temp_tex);
        return (m_textures.size() - 1);
    }
    void Bind(int id, int slot=0){ m_textures[id]->Bind(slot); }
    void Unbind(int id){ m_textures[id]->Unbind(); }
};
