#pragma once

#include"window_framework.h"

#include<GLFW\glfw3.h>

namespace bear { namespace window {

	/* Type: GLFW Window */
	/* GLFW Implementation */
	class GLFW_Window : public WindowFramework {
	public:


		bool is_open() override;
		void close() override;
		void clear() override;
		void display() override;
	};

} }