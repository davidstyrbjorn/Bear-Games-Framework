#pragma once

#include<string>

// Include files for the graphics module to work 
#include"vertex.h"
#include"shader.h"
#include"renderable.h"
#include"image.h"
#include"shape.h"
#include"text.h"

namespace bear { namespace graphics {

	class Graphics {
	public:
		static Shader* defaultUnlitShader;

	public:
		/* 
		* Initalize GLEW OpenGL bindings 
		*/
		static bool init();

		/* */
		static bool exit();
	};
	//static std::string default_vertex_shader = "#version330 \nlayout(location=0) in vec2 in_pos; \nlayout(location=1) in vec4 in_color; \nlayout(location=2) in vec2 in_uv; \nuniform mat4 projection_matrix; \nuniform mat4 model_matrix = mat4(1.0); \nuniform mat4 view_matrix = mat4(1.0); \nout vec4 color; \nout vec2 uv; \n void main(){ \ngl_Position = projection_matrix * model_matrix * view_matrix * vec4(in_pos.x, in_pos.y, 0, 1.0); \ncolor = in_color; \nuv = in_uv; \n} ";                                                                                             
	//static std::string unlit_default_fragment_shader = "#version 330 \nin vec4 color; \nin vec2 uv; \nuniform sampler2D textureSampler; \nvoid main(){ \ngl_FragColor = color; \n}";
	//static std::string textured_default_fragment_shader = "#version 330 \nin vec4 color; \nin vec2 uv; \nuniform sampler2D textureSampler; \nvoid main(){ \ngl_FragColor = texture(textureSampler, uv); \n}";
	static std::string default_vertex_shader = "D:\\temp\\vertex.txt";
	static std::string unlit_default_fragment_shader = "D:\\temp\\frag_unlit.txt";
} }


// Default shaders

