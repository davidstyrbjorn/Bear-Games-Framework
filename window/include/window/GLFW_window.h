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

		bool isOpen() override;
		void close() override;
		void clear(core::Color a_Color = core::Color(72 / 255.0f, 214 / 255.0f, 190 / 255.0f)) override;
		void display() override;
		void setFrameRateLimit(unsigned int a_Limit) override;

		const std::deque<bear::Event> getRegisteredEvents() const override;
		const bool isKeyDown(int a_Key) override;
		const bool isMouseDown(int a_Button) override;
		const core::Vector2d getMousePosition() override;

		static bool init();
		static bool exit();

		/* GLFW callbacks */
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	private:
		GLFWwindow *m_Window;
		unsigned int m_Width, m_Height;
		std::deque<Event> m_Events;
		core::Vector2d m_MousePosition;
	};

} }