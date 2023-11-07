#include <Engine/Engine.h>

int main(int argc, char** argv)
{
	Engine engine;
	if(!engine.Init(1280, 720))
	{
		std::cout << "Failed to init engine" << std::endl;
		return -1;
	}
	engine.Run();
	return 0;
}
