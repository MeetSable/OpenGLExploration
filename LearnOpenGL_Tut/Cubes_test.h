#pragma once
#include <glm\glm.hpp>

class VertexArray;
class Shader;
class Texture;

class Cubes {
private:
	VertexArray* m_va;
	Shader* m_shader;
	Texture* m_tex;
public:
	Cubes();
	~Cubes();

	void Draw(glm::mat4 view, glm::mat4 projection);
};