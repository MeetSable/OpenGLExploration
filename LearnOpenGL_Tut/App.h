#pragma once

#include <Renderer.h>
#include <Shader.h>
#include <Texture.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include "Camera.h"

#include "glm/glm.hpp"

struct Material {
	glm::vec3 ambient;
	float diffuse;
	float specular;
	float shininess;

	Material() :ambient(1.f), diffuse(0.8f), specular(1.f), shininess(1.f) {}
};

struct PointLight
{
	glm::vec3 position;
    
	glm::vec3 ambient;
    
	float constant;
	float linear;
	float quadratic;

	PointLight():ambient(.05f) {}
};

struct DirLight
{
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct SpotLight{
	glm::vec3 position;
	glm::vec3 direction;
	float cutOff;
	float outerCutOff;
    
	glm::vec3 ambient;
    
	float constant;
	float linear;
	float quadratic;
    
	bool isOn;
	SpotLight():isOn(false), cutOff(glm::radians(12.f)), outerCutOff(glm::radians(17.5f)) {}
};

#define NR_POINT_LIGHTS 4

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
	Shader *lampShader, *cubeShader;
	Texture *diffuseMap, *specularMap, *emissionMap;
	Material cubeMaterial;
	DirLight dirLight;
	std::vector<PointLight> pointLights;
	SpotLight spotLight;

	glm::vec3 m_clearColor;

	float m_deltaTime;
	uint64_t m_lastFrame;
	
public:
	App(int w, int h);
	~App();
	void Run();
	void ProcessEvent();
	void ProcessInput();
	void Update();
	void Draw();
};