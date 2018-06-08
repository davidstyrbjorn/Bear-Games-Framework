#include"../include/GLFW_window.h"

#include<GLFW\glfw3.h>

bear::window::GLFW_Window::GLFW_Window(unsigned int a_Width, unsigned int a_Height, std::string a_Caption)
	: m_Width(a_Width), m_Height(a_Height)
{
	// Create GLFW window (assuming init has already been called)
	m_Window = glfwCreateWindow(a_Width, a_Height, a_Caption.c_str(), nullptr, nullptr);

	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
	
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
	m_Events.clear();
	glfwSwapBuffers(m_Window);
}

const std::deque<bear::Event> bear::window::GLFW_Window::getRegisteredEvents() const
{
	return m_Events;
}

const bool bear::window::GLFW_Window::isKeyDown(int a_Key)
{
	return glfwGetKey(m_Window, a_Key);
}

const bool bear::window::GLFW_Window::isMouseDown(int a_Button)
{
	return glfwGetMouseButton(m_Window, a_Button);
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

void bear::window::GLFW_Window::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	// Take event and push back into event queue
	if (action == GLFW_PRESS || action == GLFW_RELEASE || action == GLFW_REPEAT) {
		bear::Event event;

		event.key = key;
		if (action == GLFW_REPEAT) event.type = EventType::KeyDown;
		else if (action == GLFW_PRESS) event.type = EventType::KeyPressed;
		else if (action == GLFW_RELEASE) event.type = EventType::KeyReleased;

		GLFW_Window* temp = (GLFW_Window*)(glfwGetWindowUserPointer(window));
		temp->m_Events.push_back(event);
	}
}

void bear::window::GLFW_Window::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	// Take event and push back into event queue
	if (action == GLFW_PRESS || action == GLFW_RELEASE || action == GLFW_REPEAT) {
		bear::Event event;

		event.button = button;

		if (action == GLFW_PRESS) event.type = EventType::MousePressed;
		else if (action == GLFW_RELEASE) event.type = EventType::MouseReleased;

		GLFW_Window* temp = (GLFW_Window*)(glfwGetWindowUserPointer(window));
		temp->m_Events.push_back(event);
	}
}
