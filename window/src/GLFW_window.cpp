#include"../include/window/GLFW_window.h"

#include<GLFW\glfw3.h>

#include<core\color.h>

bear::window::GLFW_Window::GLFW_Window(unsigned int a_Width, unsigned int a_Height, std::string a_Caption)
	: m_Width(a_Width), m_Height(a_Height)
{
	// Create GLFW window (assuming init has already been called)
	m_Window = glfwCreateWindow(a_Width, a_Height, a_Caption.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);

	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
	
	glfwSetWindowUserPointer(m_Window, this); // @ We might now want to do this?
}

bool bear::window::GLFW_Window::isOpen()
{
	return !glfwWindowShouldClose(m_Window);
}

void bear::window::GLFW_Window::close()
{
	glfwSetWindowShouldClose(m_Window, true);
}

void bear::window::GLFW_Window::clear(core::Color a_Color)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(a_Color.r, a_Color.g, a_Color.b, a_Color.a);

	glfwPollEvents();
	glfwGetCursorPos(m_Window, &m_MousePosition.x, &m_MousePosition.y);
}

void bear::window::GLFW_Window::display()
{
	m_Events.clear();
	glfwSwapBuffers(m_Window);
}

void bear::window::GLFW_Window::setFrameRateLimit(unsigned int a_Limit)
{
	printf("GLFW SET FRAME RATE NOT IMPLEMENTED");
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

const bear::core::Vector2d bear::window::GLFW_Window::getMousePosition()
{
	return m_MousePosition;
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
		if (action == GLFW_PRESS) event.type = EventType::KeyPressed;
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
