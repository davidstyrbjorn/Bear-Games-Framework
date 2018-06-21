#include "../include/graphics/graphics.h"

#define GLEW_STATIC
#include"GL\glew.h"

bool bear::graphics::Graphics::init()
{
	glewInit();
	return true;
}

bool bear::graphics::Graphics::exit()
{
	return true;
}
