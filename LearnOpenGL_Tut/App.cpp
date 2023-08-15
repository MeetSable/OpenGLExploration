#include "App.h"
#include <Renderer.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_opengl3.h"

#include <VertexBuffer.h>
#include <VertexBufferLayout.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

static glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
	glm::vec3( 0.7f,  0.2f,  2.0f),
	glm::vec3( 2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3( 0.0f,  0.0f, -3.0f)
};  

App::App(int w, int h)
	: m_width(w), m_height(h), m_isRunning(true), m_keyState(nullptr), m_clearColor(0.f), pointLights(NR_POINT_LIGHTS)
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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL3_InitForOpenGL(m_window, m_context);
	ImGui_ImplOpenGL3_Init("#version 460");

	mouse_x = m_width / 2.f, mouse_y = m_height / 2.f;

	camera = new Camera(
		glm::vec3(0.f, 0.f, 7.5f),
		-90, 0,
		glm::vec3(0.f, 1.f, 0.f),
		m_width, m_height);

	float vertices[] = {
	    // positions          // normals           // texture coords
	    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	VertexBuffer vb(vertices, sizeof(vertices));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	cube_va = new VertexArray();
	cube_va->AddBuffer(vb, layout);
	cube_va->Unbind();
	lampShader = new Shader("res/base_vs.glsl", "res/lamp_fs.glsl");
	cubeShader = new Shader("res/base_vs.glsl", "res/multiple_lights.glsl");
	diffuseMap = new Texture("res/container2.png");
	diffuseMap->Unbind();
	// specularMap = new Texture("res/container2_specular.png");
	specularMap = new Texture("res/lighting_maps_specular_color.png");
	specularMap->Unbind();
	emissionMap = new Texture("res/matrix.jpg");
	emissionMap->Unbind();
	
	cubeShader->Bind();
	cubeShader->SetUniform1i("material.diffuse", 0);
	cubeShader->SetUniform1i("material.specular", 1);
	// cubeShader->SetUniform1i("material.emission", 2);
	cubeShader->Unbind();

	for(int i = 0 ; i < NR_POINT_LIGHTS ; i++)
	{
		pointLights[i].position = pointLightPositions[i];
		pointLights[i].constant = 1.f;
		pointLights[i].linear = 0.09f;
		pointLights[i].quadratic = 0.032f;
	}

	m_lastFrame = SDL_GetTicks();
}

App::~App()
{
	delete(diffuseMap);
	delete(specularMap);
	delete(emissionMap);
	delete(cube_va);
	delete(lampShader);
	delete(cubeShader);
	delete(camera);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
	
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
		ImGui_ImplSDL3_ProcessEvent(&event);
		
		if (event.type == SDL_EVENT_QUIT)
		{
			m_isRunning = false;
		}
		else if (event.type == SDL_EVENT_MOUSE_WHEEL)
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
	if(SDL_GetMouseState(&mouse_x, &mouse_y) & SDL_BUTTON_RMASK)
		camera->RightButtonPressed();
	
	camera->ProcessInputs(m_keyState, mouse_x, mouse_y);
}

void App::Update()
{
	m_deltaTime = static_cast<float>(SDL_GetTicks() - m_lastFrame) * 1000.f;
}

void App::Draw()
{
	glViewport(0, 0, m_width, m_height);
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	{
		cube_va->Bind();
		cubeShader->Bind();
		diffuseMap->Bind(0);
		specularMap->Bind(1);
		emissionMap->Bind(2);
		// coords
		cubeShader->SetUniform4mat("projection", camera->GetProjectionMatrix());
		cubeShader->SetUniform4mat("view", camera->GetViewMatrix());
		cubeShader->SetUniform3f("viewPos", camera->GetCameraPos());
		// lamp properties
		// cubeShader->SetUniform3f("light.position", lamp.position); // point light
		// cubeShader->SetUniform3f("light.direction", glm::vec3(-.2f, -1.f, -.3f)); // directional light
		for(int i = 0 ; i < NR_POINT_LIGHTS ; i++)
		{
			std::string l = "pointLights[" + std::to_string(i) + "].";
			cubeShader->SetUniform3f(l + "position", pointLights[i].position);
			cubeShader->SetUniform3f(l + "ambient", pointLights[i].ambient);
			cubeShader->SetUniform3f(l + "diffuse", pointLights[i].diffuse);
			cubeShader->SetUniform3f(l + "specular", pointLights[i].specular);
			cubeShader->SetUniform1f(l + "constant", pointLights[i].constant);
			cubeShader->SetUniform1f(l + "linear", pointLights[i].linear);
			cubeShader->SetUniform1f(l + "quadratic", pointLights[i].quadratic);
		}
		// Spotlight -------
		// cubeShader->SetUniform3f("light.position", camera->GetCameraPos());
		// cubeShader->SetUniform3f("light.direction", camera->GetCameraFront());
		// Spotlight -------
		// cube material
		cubeShader->SetUniform1f("material.shininess", cubeMaterial.shininess);
		for(int i = 0 ; i < 10 ; i++)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.f), cubePositions[i]);
			model = glm::rotate(model, glm::radians(i * 20.f), glm::vec3(1.f, .3f, .5f));
			cubeShader->SetUniform4mat("model", model);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		}
		specularMap->Unbind();
		diffuseMap->Unbind();
		cubeShader->Unbind();

		// lamp cube
		lampShader->Bind();
		lampShader->SetUniform4mat("projection", camera->GetProjectionMatrix());
		lampShader->SetUniform4mat("view", camera->GetViewMatrix());
		for(int i = 0 ; i < NR_POINT_LIGHTS ; i++)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.f), pointLightPositions[i]);
			lampShader->SetUniform4mat("model", glm::scale(model, glm::vec3(.2f, .2f, .2f)));
			lampShader->SetUniform3f("sourceColor", pointLights[i].ambient);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		}
		lampShader->Unbind();
	}

	// start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	{
		ImGui::NewFrame();
		ImGui::Begin("Performace", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove);
		ImGui::Value("FPS", ImGui::GetIO().Framerate);
		ImGui::End();
		
		ImGui::Begin("Editor");
		ImGui::ColorEdit3("Background Color", &m_clearColor[0]);
		for(int i = 0 ; i < NR_POINT_LIGHTS ; i++)
		{
			if(!ImGui::CollapsingHeader(("Point Light " + std::to_string(i+1)).c_str())) continue;
			ImGui::ColorEdit3("Ambient", &pointLights[i].ambient[0]);
			ImGui::InputFloat3("Diffuse", &pointLights[i].diffuse[0]);
			ImGui::InputFloat3("Specular", &pointLights[i].specular[0]);
		}
		if (ImGui::CollapsingHeader("Cube Material"))
		{
			ImGui::SliderFloat("Shininess", &cubeMaterial.shininess, 1.f, 128.f, "%.2f");
		}
		ImGui::End();
		
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(m_window);
}