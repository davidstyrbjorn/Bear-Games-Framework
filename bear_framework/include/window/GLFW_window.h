#pragma once

#include"window_framework.h"
#include"GLFW_event.h"
#include<deque>
#include<string>

#include"../core/clock.h"

struct GLFWwindow; // GLFW struct

namespace bear { namespace window {

	/* Type: GLFW Window */
	/* GLFW Implementation */
	class Window : public WindowFramework {
	public:
		Window(unsigned int a_Width, unsigned int a_Height, std::string a_Caption = "GLFW Window");
		~Window();

		bool isOpen() override;
		void close() override;
		void clear(core::Color a_Color = core::Color(72 / 255.0f, 214 / 255.0f, 190 / 255.0f)) override;
		void display() override;
		void setFrameRateLimit(unsigned int a_Limit) override;

		void setVSync(bool a_Value);
		bool getVSync();

		const std::deque<bear::Event>& getRegisteredEvents() const override;
		const bool isKeyDown(int a_Key) override;
		const bool isMouseDown(int a_Button) override;
		const core::Vector2d getMousePosition() override;

		const core::Vector2i getWindowPosition();
		void setWindowPosition(core::Vector2i& a_WindowPosition);
		const core::Vector2i getWindowSize();
		const float getDeltaTime();

		/* GLFW callbacks */
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void window_resize_callback(GLFWwindow* window, int width, int height);

	private:
		core::Clock m_DeltaClock;
		float m_DeltaTime = 1;
		GLFWwindow *m_Window;
		core::Vector2i m_WindowSize;
		std::deque<Event> m_Events;
		core::Vector2d m_MousePosition;
		bool m_VSync;
	};

} }