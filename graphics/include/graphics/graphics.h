#pragma once

namespace bear { namespace graphics {

	class Graphics {
	private:
		static bool s_DirtyRender;

	public:
		/* 
		* Initalize GLEW OpenGL bindings 
		* \param value for enabling/disabling dirty rendering 
		*/
		static bool init(bool a_V);

		/* */
		static bool exit();

		static bool doDirtyRender() { return s_DirtyRender; }
	};

} }

// Include files for the graphics module to work 
#include"shader.h"
#include"renderable.h"