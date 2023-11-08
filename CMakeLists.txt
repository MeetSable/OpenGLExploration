cmake_minimum_required(VERSION 3.16)

project(
	OpenGLExploration
	LANGUAGES C CXX
	VERSION "1.0.0"
)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

find_program(CMAKE_C_COMPILER NAMES x86_64-w64-mingw32-gcc)
find_program(CMAKE_CXX_COMPILER NAMES x86_64-w64-mingw32-g++)

if(NOT CMAKE_C_COMPILER)
	message(FATAL_ERROR "Failed to find CMAKE_C_COMPILER.")
endif()

if(NOT CMAKE_CXX_COMPILER)
	message(FATAL_ERROR "Failed to find CMAKE_CXX_COMPILER.")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OGLSources
	src/OGL/stb_image/stb_image.cpp
	src/OGL/glad.c
	src/OGL/IndexBuffer.cpp
	src/OGL/Renderer.cpp
	src/OGL/Shader.cpp
	src/OGL/Texture.cpp
	src/OGL/VertexArray.cpp
	src/OGL/VertexBuffer.cpp
	src/OGL/VertexBufferLayout.cpp
)

set(EngineSources
	src/Engine/Engine.cpp
)

add_executable(app ${OGLSources} ${EngineSources} src/main.cpp)

target_compile_options(app PRIVATE -mwindows -mconsole -Ofast)

target_include_directories(
	app
	PRIVATE
	src
	libs/gl_loader
	libs/glm
	libs/SDL/include
)

target_link_directories(
	app
	PUBLIC
	libs/SDL/build
)

target_link_libraries(
	app
	PUBLIC
	libSDL3
)
