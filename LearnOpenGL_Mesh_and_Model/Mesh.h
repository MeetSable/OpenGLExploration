#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "TextureManager.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

class Mesh {
private:
	std::vector<unsigned int> m_textures;
	void setupMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	VertexArray m_va;
	VertexBuffer* m_vb;
	IndexBuffer m_ib;
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<unsigned int>& textures);
	~Mesh();
	void Draw(Shader& shader);
};