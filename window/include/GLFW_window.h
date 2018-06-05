#pragma once

#include"window_framework.h"

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

		static bool init();
		static bool exit();

	private:
		GLFWwindow *m_Window;
		unsigned int m_Width, m_Height;
	};

} }