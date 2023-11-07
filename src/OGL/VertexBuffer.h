#pragma once

class VertexBuffer
{
private:
    unsigned int m_RendererId;

public:
    VertexBuffer(const void* data, unsigned int size);
    VertexBuffer() :m_RendererId(0) {}
    ~VertexBuffer();

    void CreateBuffer(const void* data, unsigned int size);
    void Bind() const;
    void Unbind() const;
};