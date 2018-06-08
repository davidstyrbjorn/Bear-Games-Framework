#pragma once

#include"window_framework.h"
#include"GLFW_event.h"
#include<deque>
#include<string>

struct GLFWwindow; // GLFW struct

namespace bear { namespace window {

	/* Type: GLFW Window */
	/* GLFW Implementation */
	class GLFW_Window : public WindowFramework {
	public:
		GLFW_Window(unsigned int a_Width, unsigned int a_Height, std::string a_Caption = "GLFW Window");

		bool is_open() override;
		void close() override;
		void clear() override;
		void display() override;
		const std::deque<bear::Event> getRegisteredEvents() const override;

		static bool init();
		static bool exit();

		/* GLFW callbacks */
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	private:
		GLFWwindow *m_Window;
		unsigned int m_Width, m_Height;
		std::deque<Event> m_Events;
	};

} }