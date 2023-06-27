#pragma once

#include <Renderer.h>
#include <Shader.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include "Camera.h"

#include "glm/glm.hpp"

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	Material() :ambient(1.f), diffuse(1.f), specular(1.f), shininess(1.f) {}
};

struct Light {
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Light(): position(1.f), ambient(1.f), diffuse(1.f), specular(1.f) {}
};

class App {
private:
	int m_width, m_height;
	SDL_Window* m_window;
	SDL_GLContext m_context;
	bool m_isRunning;
	const uint8_t *m_keyState;
	float mouse_x, mouse_y;

	Camera* camera;
	VertexArray *cube_va;
	glm::mat4 lightModel;
	Shader* lampShader, *cubeShader;
	Material cubeMaterial;
	Light lamp;
	
public:
	App(int w, int h);
	~App();
	void Run();
	void ProcessEvent();
	void ProcessInput();
	void Update();
	void Draw();
};