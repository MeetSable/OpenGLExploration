#include "Mesh.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<unsigned int>& textures)
{
	m_textures = textures;
	setupMesh(vertices, indices);
}

Mesh::~Mesh()
{
	m_vb->~VertexBuffer();
	m_ib.~IndexBuffer();
	m_va.~VertexArray();
}

void Mesh::setupMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	// index buffer
	m_ib.CreateBuffer(&indices[0], indices.size());

	//vertex buffer
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));
	m_va.AddBuffer(*m_vb, layout);
}

void Mesh::Draw(Shader& shader)
{
	m_va.Bind();
	m_ib.Bind();
	shader.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, m_ib.GetCount(), GL_UNSIGNED_INT, NULL));
	m_va.Unbind();
	m_ib.Unbind();
	shader.Unbind();
};