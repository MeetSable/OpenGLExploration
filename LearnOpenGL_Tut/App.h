#pragma once

#include "Renderer.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_opengl.h"

#include "Cubes.h"

class App {
private:
	int m_width, m_height;
	SDL_Window* m_window;
	SDL_GLContext m_context;
	bool m_isRunning;
	const uint8_t *m_keyState;

	Cubes *cubes;
public:
	App(int w, int h);
	~App();
	void Run();
	void ProcessEvent();
	void ProcessInput();
	void Update();
	void Draw();
};