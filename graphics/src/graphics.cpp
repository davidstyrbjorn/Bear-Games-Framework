#include "../include/graphics/graphics.h"

#define GLEW_STATIC
#include"GL\glew.h"

using namespace bear;
using namespace bear::graphics;

bool bear::graphics::Graphics::init(window::Window& a_Window)
{
	glewExperimental = true;
	GLenum result = glewInit();

	if (result != GLEW_OK) {
		if (result == GLEW_ERROR_NO_GL_VERSION) {
			printf("No GL context ( GLEW_ERROR_NO_GL_VERSION )\n");
		}
		return false;
	}

	GraphicsInformation::instance()->creteInstance(a_Window);

	return true;
}

bool bear::graphics::Graphics::exit()
{
	return true;
}

// GRAPHICS INFORMATION //  

GraphicsInformation* GraphicsInformation::Instance = nullptr;

GraphicsInformation::GraphicsInformation(window::Window& a_Window) : m_Window(a_Window)
{

}

void bear::graphics::GraphicsInformation::creteInstance(window::Window& a_Window)
{
	Instance = new GraphicsInformation(a_Window);
}

GraphicsInformation * GraphicsInformation::instance()
{
	return Instance;
}