#include "App.h"
#include "Renderer.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

App::App(int w, int h)
	: m_width(w), m_height(h), m_isRunning(true), m_keyState(nullptr)
{
	m_window = SDL_CreateWindow("Learning OpenGL...", m_width, m_height, SDL_WINDOW_OPENGL);
	if (!m_window)
	{
		std::cout << "Failed to create window\n" << SDL_GetError() << std::endl;
		exit(-1);
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	m_context = SDL_GL_CreateContext(m_window);
	if (!m_context)
	{
		std::cout << "failed to create context\n" << SDL_GetError() << std::endl;
		exit(-1);
	}
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n" << std::endl;
		exit(-1);
	}
	GLCall(glEnable(GL_DEPTH_TEST));

	mouse_x = m_width / 2.f, mouse_y = m_height / 2.f;

	cubes = new Cubes();
	camera = new Camera(
		glm::vec3(0.f, 0.f, 3.f),
		glm::vec3(0.f, 0.f, -1.f),
		glm::vec3(0.f, 1.f, 0.f),
		m_width, m_height);
}

App::~App()
{
	delete(cubes);
	delete(camera);
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void App::Run()
{
	while (m_isRunning)
	{
		ProcessEvent();
		ProcessInput();
		Update();
		Draw();
	}
}

void App::ProcessEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)
			m_isRunning = false;

		if (event.type == SDL_EVENT_MOUSE_WHEEL)
		{
			camera->ProcessMouseWheelEvent(event.wheel.x, event.wheel.y);
		}
	}
}

void App::ProcessInput()
{
	m_keyState = SDL_GetKeyboardState(NULL);
	if (m_keyState[SDL_SCANCODE_ESCAPE])
		m_isRunning = false;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	camera->ProcessInputs(m_keyState, mouse_x, mouse_y);
}

void App::Update()
{
}

void App::Draw()
{
	glViewport(0, 0, m_width, m_height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	{
		cubes->Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	}
	SDL_GL_SwapWindow(m_window);
}