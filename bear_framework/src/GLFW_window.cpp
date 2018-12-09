#include"../include/window/GLFW_window.h"

#include<GLFW\glfw3.h>

#include"../include/core/color.h"

bear::window::Window::Window(unsigned int a_Width, unsigned int a_Height, std::string a_Caption, bool a_Fullscreen)
{
	// Init GLFW API
	glfwInit();

	// GLFWwindow creation
	if (a_Fullscreen) {
		GLFWmonitor *monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		a_Width = mode->width;
		a_Height = mode->height;
		m_Window = glfwCreateWindow(a_Width, a_Height, a_Caption.c_str(), monitor, nullptr);
	}
	else {
		m_Window = glfwCreateWindow(a_Width, a_Height, a_Caption.c_str(), nullptr, nullptr);
	}
	glfwMakeContextCurrent(m_Window);

	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
	glfwSetWindowSizeCallback(m_Window, window_resize_callback);

	setVSync(false);
	m_WindowSize = core::Vector2i(a_Width, a_Height);

	glfwSetWindowUserPointer(m_Window, this); 

	// This is not needed, is automatically set during GL context creation!
	glViewport(0, 0, a_Width, a_Height);

	// Delta timer
	m_DeltaTime = 1.0f;
	m_DeltaClock.start();
}

bear::window::Window::~Window()
{
	// Handles GLFW pointers and allocations
	glfwTerminate();
}

bool bear::window::Window::isOpen()
{
	return !glfwWindowShouldClose(m_Window);
}

void bear::window::Window::close()
{
	glfwSetWindowShouldClose(m_Window, true);
}

void bear::window::Window::clear(core::Color a_Color)
{
	m_DeltaClock.reset();

	glClearColor(a_Color.r, a_Color.g, a_Color.b, a_Color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void bear::window::Window::display()
{
	m_Events.clear();
	glfwSwapBuffers(m_Window);

	glfwPollEvents();
	glfwGetCursorPos(m_Window, &m_MousePosition.x, &m_MousePosition.y);

	m_DeltaTime = m_DeltaClock.getTicks();
}

void bear::window::Window::setFrameRateLimit(unsigned int a_Limit)
{
	printf("GLFW SET FRAME RATE NOT IMPLEMENTED");
}

void bear::window::Window::setVSync(bool a_Value)
{
	m_VSync = a_Value;
	int x = a_Value == true ? 0 : -1;
	glfwSwapInterval(a_Value);
}

bool bear::window::Window::getVSync()
{
	return m_VSync;
}

const std::deque<bear::Event>& bear::window::Window::getRegisteredEvents() const
{
	return m_Events;
}

const bool bear::window::Window::isKeyDown(int a_Key)
{
	return glfwGetKey(m_Window, a_Key);
}

const bool bear::window::Window::isMouseDown(int a_Button)
{
	return glfwGetMouseButton(m_Window, a_Button);
}

const bear::core::Vector2d bear::window::Window::getMousePosition()
{
	return m_MousePosition;
}

const bear::core::Vector2i bear::window::Window::getWindowPosition()
{
	int x, y;
	glfwGetWindowPos(m_Window, &x, &y);
	return core::Vector2i(x, y);
}

void bear::window::Window::setWindowPosition(core::Vector2i & a_WindowPosition)
{
	glfwSetWindowPos(m_Window, a_WindowPosition.x, a_WindowPosition.y);
}

const bear::core::Vector2i bear::window::Window::getWindowSize()
{
	return m_WindowSize;
}

const float bear::window::Window::getDeltaTime()
{
	return m_DeltaTime;
}

void bear::window::Window::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	// Take event and push back into event queue
	if (action == GLFW_PRESS || action == GLFW_RELEASE || action == GLFW_REPEAT) {
		bear::Event event;

		event.key = key;
		if (action == GLFW_PRESS) event.type = EventType::KeyPressed;
		else if (action == GLFW_RELEASE) event.type = EventType::KeyReleased;

		Window* temp = static_cast<Window*>(glfwGetWindowUserPointer(window));
		temp->m_Events.push_back(event);
	}
}

void bear::window::Window::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	// Take event and push back into event queue
	if (action == GLFW_PRESS || action == GLFW_RELEASE || action == GLFW_REPEAT) {
		bear::Event event;

		event.button = button;

		if (action == GLFW_PRESS) event.type = EventType::MousePressed;
		else if (action == GLFW_RELEASE) event.type = EventType::MouseReleased;

		Window* temp = static_cast<Window*>(glfwGetWindowUserPointer(window));
		temp->m_Events.push_back(event);
	}
}

void bear::window::Window::window_resize_callback(GLFWwindow * window, int width, int height)
{
	Window* temp = static_cast<Window*>(glfwGetWindowUserPointer(window));
	temp->m_WindowSize = core::Vector2i(width, height);

	bear::Event event;
	event.type = bear::EventType::WindowReiszed;
	event.size = core::Vector2f(width, height);
	temp->m_Events.push_back(event);
}