// My includes
#include "Renderer.h"

// SDL includes
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include "Model.h"
#include "TextureManager.h"
#include "Camera.h"

// constants
const int
    window_width = 1280,
    window_height = 720;

// SDL variables
SDL_Window* window = nullptr;
SDL_GLContext gl_context;

bool isRunning = false;

const uint8_t *keyState;


bool Init()
{
    window = SDL_CreateWindow("OpenGL meshes and models", window_width, window_height, SDL_WINDOW_OPENGL);
    if(!window)
    {
        std::cout << "Failed to create window\n" << SDL_GetError() << std::endl;
        return false;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    gl_context = SDL_GL_CreateContext(window);
    if(!gl_context)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        
        std::cout << "Failed to create OpenGL context\n" << SDL_GetError() << std::endl;
        return false;
    }

    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        
        std::cout << "Failed to intialize GLAD\n" << std::endl;
        return false;
    }

    GLCall(glEnable(GL_DEPTH_TEST));

    return true;
}

int main(int argc, char* argv[])
{  
    if(!Init())
        return -1;
    isRunning = true;
    {
        TextureManager textureManager;
        char modelPath[] = "res/backpack/backpack.obj";
        Model backpack(modelPath, &textureManager);
        Shader basic_shader("res/basic_vs.glsl", "res/basic_fs.glsl");
        basic_shader.Bind();
        basic_shader.SetUniform1i("texture_diffuse", 0);
        basic_shader.Unbind();
        Camera camera(
        glm::vec3(0.f, 0.f, 7.5f),
        -90, 0,
        glm::vec3(0.f, 1.f, 0.f),
        window_width, window_height);
        while(isRunning)
        {
            SDL_Event e;
            while(SDL_PollEvent(&e))
            {
                if(e.type == SDL_EVENT_QUIT)
                    isRunning = false;
            }

            keyState = SDL_GetKeyboardState(NULL);

            if(keyState[SDL_SCANCODE_ESCAPE]) isRunning = false;

            static float mouse_x, mouse_y;
            if (SDL_GetMouseState(&mouse_x, &mouse_y) & SDL_BUTTON_RMASK)
                camera.RightButtonPressed();
            camera.ProcessInputs(keyState, mouse_x, mouse_y);

            GLCall(glViewport(0,0,window_width, window_height));
            GLCall(glClearColor(0.2f, 0.2f, 0.4f, 0.f));
            GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

            basic_shader.Bind();
            basic_shader.SetUniform4mat("model", glm::mat4(1.f));
            basic_shader.SetUniform4mat("view", camera.GetViewMatrix());
            basic_shader.SetUniform4mat("projection", camera.GetProjectionMatrix());
            basic_shader.Unbind();
            textureManager.Bind(0);
            backpack.Draw(basic_shader);
            textureManager.Unbind(0);

            SDL_GL_SwapWindow(window);
        }   
    }

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
