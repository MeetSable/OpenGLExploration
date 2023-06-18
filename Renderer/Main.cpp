#include <iostream>

#include "Renderer.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>


const float ASPECT = 16.f / 9.f;
const int WinHeight = 480;
const int WinWidth = WinHeight * ASPECT;

SDL_Window* window = NULL;
uint32_t window_flags = SDL_WINDOW_OPENGL;
SDL_GLContext context;

unsigned char isRunning = 1;

int main(int argc, char** argv)
{
	window = SDL_CreateWindow("opengl",WinWidth, WinHeight, window_flags);
	if (!window)
	{
		std::cout << "Failed to create window\n" << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	context = SDL_GL_CreateContext(window);
	if (!context)
	{
		std::cout << "failed to create context\n" << SDL_GetError() << std::endl;
		return -1;
	}
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "failed to load glew\n" << glewGetErrorString(err) << std::endl;
		return -1;
	}

	while (isRunning)
	{
		SDL_Event event;	
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
				isRunning = 0;
		}

		glViewport(0, 0, WinWidth, WinHeight);
		glClearColor(0.2f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}