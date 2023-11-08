#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "OGL/VertexArray.h"
#include "OGL/VertexBuffer.h"
#include "OGL/IndexBuffer.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

struct MeshData
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

struct Material
{
	std::string mtl_name;
	glm::vec3 Ka; // Ambient
	glm::vec3 Kd; // Diffuse
	glm::vec3 Ks; // Specular
	float Ns; // specular exponent
	float Ni; // refration index
	float d; // dissolve factor
	unsigned int illum; // illumination mode
	unsigned int map_Kd; // diffuse map
	unsigned int map_Bump; // normal map
	unsigned int map_Ks; // specular map
};

class Mesh
{
private:
	std::string name;
	VertexArray m_va;
	VertexBuffer *m_vb;
	IndexBuffer m_ib;
	Material m_material;
public:
	Mesh();
	~Mesh();
	void Draw();
};
