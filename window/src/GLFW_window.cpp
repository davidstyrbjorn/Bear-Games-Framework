#include"../include/window/GLFW_window.h"

#include<GLFW\glfw3.h>

#include<core\color.h>

template<typename T>
bear::window::GLFW_Window<T>::GLFW_Window(unsigned int a_Width, unsigned int a_Height, std::string a_Caption)
	: m_Width(a_Width), m_Height(a_Height)
{
	// Create GLFW window (assuming init has already been called)
	m_Window = glfwCreateWindow(a_Width, a_Height, a_Caption.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);

	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
	glfwSetWindowSizeCallback(m_Window, window_resize_callback);
	
	glfwSetWindowUserPointer(m_Window, this); // @ We might now want to do this?
}

template<typename T>
bool bear::window::GLFW_Window<T>::isOpen()
{
	return !glfwWindowShouldClose(m_Window);
}

template<typename T>
void bear::window::GLFW_Window<T>::close()
{
	glfwSetWindowShouldClose(m_Window, true);
}

template<typename T>
void bear::window::GLFW_Window<T>::clear(core::Color a_Color)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(a_Color.r, a_Color.g, a_Color.b, a_Color.a);

	glfwPollEvents();
	glfwGetCursorPos(m_Window, &m_MousePosition.x, &m_MousePosition.y);
}

template<typename T>
void bear::window::GLFW_Window<T>::display()
{
	m_Events.clear();
	glfwSwapBuffers(m_Window);
}

template<typename T>
void bear::window::GLFW_Window<T>::setFrameRateLimit(unsigned int a_Limit)
{
	printf("GLFW SET FRAME RATE NOT IMPLEMENTED");
}

template<typename T>
const std::deque<bear::Event> bear::window::GLFW_Window<T>::getRegisteredEvents() const
{
	return m_Events;
}

template<typename T>
const bool bear::window::GLFW_Window<T>::isKeyDown(int a_Key)
{
	return glfwGetKey(m_Window, a_Key);
}

template<typename T>
const bool bear::window::GLFW_Window<T>::isMouseDown(int a_Button)
{
	return glfwGetMouseButton(m_Window, a_Button);
}

template<typename T>
const bear::core::Vector2d bear::window::GLFW_Window<T>::getMousePosition()
{
	return m_MousePosition;
}

/* Static */
template<typename T>
bool bear::window::GLFW_Window<T>::init()
{
	if (!glfwInit()) {
		/* @ Print some kind of error maybe? */
		return false;
	}
	return true;
}

/* Static */
template<typename T>
bool bear::window::GLFW_Window<T>::exit()
{
	glfwTerminate();
	return true;
}

template<typename T>
void bear::window::GLFW_Window<T>::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	// Take event and push back into event queue
	if (action == GLFW_PRESS || action == GLFW_RELEASE || action == GLFW_REPEAT) {
		bear::Event event;

		event.key = key;
		if (action == GLFW_PRESS) event.type = EventType::KeyPressed;
		else if (action == GLFW_RELEASE) event.type = EventType::KeyReleased;

		GLFW_Window* temp = static_cast<GLFW_Window*>(glfwGetWindowUserPointer(window));
		temp->m_Events.push_back(event);
	}
}

template<typename T>
void bear::window::GLFW_Window<T>::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	// Take event and push back into event queue
	if (action == GLFW_PRESS || action == GLFW_RELEASE || action == GLFW_REPEAT) {
		bear::Event event;

		event.button = button;

		if (action == GLFW_PRESS) event.type = EventType::MousePressed;
		else if (action == GLFW_RELEASE) event.type = EventType::MouseReleased;

		GLFW_Window* temp = static_cast<GLFW_Window*>(glfwGetWindowUserPointer(window));
		temp->m_Events.push_back(event);
	}
}

template<typename T>
void bear::window::GLFW_Window<T>::window_resize_callback(GLFWwindow * window, int width, int height)
{
	GLFW_Window* temp = static_cast<GLFW_Window*>(glfwGetWindowUserPointer(window));
	temp->resize_callback(width, height);
	glViewport(0, 0, width, height);
}