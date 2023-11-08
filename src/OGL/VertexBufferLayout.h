#pragma once

#include <vector>
#include "Renderer.h"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT: return sizeof(GLfloat);
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        }
        ASSERT(false);
        return 0;
    }
     
};


class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:

    VertexBufferLayout();
    ~VertexBufferLayout();

    template<typename T>
    void Push(unsigned int count);
    
    inline const std::vector<VertexBufferElement> GetElements() const {return m_Elements;}
    inline unsigned int GetStride() const {return m_Stride;}

};
