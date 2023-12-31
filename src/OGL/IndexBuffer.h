#pragma once

class IndexBuffer
{
private:
    unsigned int m_RendererId;
    unsigned int m_Count;

public:
    IndexBuffer(const unsigned int* data,const unsigned int &count);
    IndexBuffer() :m_RendererId(0), m_Count(0) {}
    ~IndexBuffer();

    void CreateBuffer(const unsigned int* data, const unsigned int& count);

    void Bind() const;
    void Unbind() const;

    unsigned int GetCount() const {return m_Count;}
};