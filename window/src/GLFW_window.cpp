#include"../include/GLFW_window.h"

#include<GLFW\glfw3.h>

bear::window::GLFW_Window::GLFW_Window(unsigned int a_Width, unsigned int a_Height, std::string a_Caption)
	: m_Width(a_Width), m_Height(a_Height)
{
	// Create GLFW window (assuming init has already been called)
	m_Window = glfwCreateWindow(a_Width, a_Height, a_Caption.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(m_Window, this); // @ We might now want to do this?
}

bool bear::window::GLFW_Window::is_open()
{
	return !glfwWindowShouldClose(m_Window);
}

void bear::window::GLFW_Window::close()
{
	glfwSetWindowShouldClose(m_Window, true);
}

void bear::window::GLFW_Window::clear()
{
	glfwPollEvents();
}

void bear::window::GLFW_Window::display()
{
	glfwSwapBuffers(m_Window);
}

/* Static */
bool bear::window::GLFW_Window::init()
{
	if (!glfwInit()) {
		/* @ Print some kind of error maybe? */
		return false;
	}
	return true;
}

/* Static */
bool bear::window::GLFW_Window::exit()
{
	glfwTerminate();
	return true;
}
