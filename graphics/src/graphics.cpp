#include "../include/graphics/graphics.h"

#define GLEW_STATIC
#include"GL\glew.h"

bool bear::graphics::Graphics::s_DirtyRender = false;

bool bear::graphics::Graphics::init(bool a_V)
{
	bear::graphics::Graphics::s_DirtyRender = a_V;

	if (!glewInit()) {
		return false;
	}
	return true;
}

bool bear::graphics::Graphics::exit()
{
	return true;
}
