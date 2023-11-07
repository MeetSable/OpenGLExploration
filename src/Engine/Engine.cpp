#include "Engine.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_video.h"

// Public functions
Engine::Engine()
{
	m_winWidth = m_winHeight = 0;
	m_window = nullptr;
	s_deinited = false;
}
Engine::~Engine()
{
	if(!s_deinited) Deinit();
}
bool Engine::Init(unsigned int width, unsigned int height)
{
	m_winWidth = width, m_winHeight = height;
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("OpenGL window", width, height, SDL_WINDOW_OPENGL);
	if(!m_window)
	{
		std::cout << "Failed to create window\n" << SDL_GetError() << std::endl;
		return false;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	gl_context = SDL_GL_CreateContext(m_window);
	if(!gl_context)
	{
		std::cout << "Failed to create context\n" << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n" << std::endl;
		Deinit();
		return false;
	}
	return true;
}
void Engine::Run()
{
	s_isRunning = true;
	uint64_t startTime=0, deltaTime=0;
	while(s_isRunning)
	{
		startTime = SDL_GetTicks();
		ProcessEvent();
		ProcessInput();
		Update(deltaTime);
		Draw();
		deltaTime = SDL_GetTicks() - startTime;
	}
	Deinit();
}
// private functions
void Engine::ProcessEvent()
{
	static SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_EVENT_QUIT)
		{
			s_isRunning = false;
		}
	}
}
void Engine::ProcessInput()
{
	static const uint8_t* keyState;
	keyState = SDL_GetKeyboardState(NULL);
	if(keyState[SDL_SCANCODE_ESCAPE])
	{
		s_isRunning = false;
	}
}
void Engine::Update(uint64_t deltaTime){}
void Engine::Draw()
{
	glViewport(0,0,m_winWidth, m_winHeight);
	glClearColor(0.2f, 0.3f, 0.3f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	SDL_GL_SwapWindow(m_window);
}
void Engine::Deinit()
{
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
