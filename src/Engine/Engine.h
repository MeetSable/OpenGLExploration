#pragma once

#include "OGL/Renderer.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <stdint.h>


class Engine
{
private:
	unsigned int
		m_winWidth,
		m_winHeight;
	SDL_Window* m_window;
	SDL_GLContext gl_context;
	
	bool s_deinited;
	bool s_isRunning;
private:
	void Update(uint64_t deltaTime);
	void ProcessEvent();
	void ProcessInput();
	void Draw();
	void Deinit();
public:
	Engine();
	~Engine();
	bool Init(unsigned int width, unsigned int height);
	void Run();
};
