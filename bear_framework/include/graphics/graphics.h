#pragma once

#include<string>
#include<memory>

// Include files for the graphics module to work 
#include"vertex.h"
#include"shader.h"
#include"renderable.h"
#include"texture.h"
#include"image.h"
#include"text.h"
#include"view.h"

namespace bear { namespace graphics {

	class Graphics {
		// Define some friendships between graphics classes
		friend class BatchRenderer;
		friend class TextLabel;
		friend class ParticleRenderer;
	
	private:
		// Used by: BatchRenderer
		static Shader* s_DefaultShader;
		static Shader* s_DefaultShaderText;
		static Shader* s_DefaultParticleShader;
		
		static unsigned int m_ScreenWidth;
		static unsigned int m_ScreenHeight;

	public:
		/* 
		* Initalize GLEW OpenGL bindings 
		* Arguments: window width and height used for shaders
		*/
		static bool init(unsigned int a_Width, unsigned int a_Height);

		/* Deallocates shader objects */
		static bool exit();

		/*
		* Callback for when window size is changed
		*/
		static void window_resize_callback(unsigned int a_Width, unsigned int a_Height);
	};

	// Used by Graphics::s_DefaultShader
	static int default_shader_pos_location = 0;
	static int default_shader_col_location = 1;
	static int default_shader_uv_location = 2;
	static std::string default_vertex_shader_source[] = {
		"#version 330", 

		"layout(location=0) in vec2 in_pos;",
		"layout(location=1) in vec4 in_color;", 
		"layout(location=2) in vec2 in_uv;",

		"uniform mat4 projection_matrix;", 
		"uniform mat4 model_matrix = mat4(1.0);", 
		"uniform mat4 view_matrix = mat4(1.0);",

		"out vec4 color;", 
		"out vec2 uv;", 
		"out vec2 pos",

		"void main() {",
		    "gl_Position = projection_matrix * model_matrix * view_matrix * vec4(in_pos.x, in_pos.y, 0, 1.0);",
		    "color = in_color;", 
			"uv = in_uv;", 
			"pos = in_pos;",
		"}" 
	};
	static std::string default_fragment_shader_source[] = {
		"#version 330",

		"in vec4 color;",
		"in vec2 uv;",
		"in vec2 pos",

		"uniform sampler2D texture_sampler;",
		"uniform int texture_mode;",

		"uniform vec2 light_pos;",
		"uniform vec4 directional_light_color;",
		"uniform float max_distance = 200;",

		"void main() {",

			"float d = distance(pos, light_pos);",
			"float ration = clamp(1 - (d/max_distance), 0.0, 1.0);",
			"vec4 lightColor = directional_light_color * ratio;",

			"if(texture_mode == 0) {",
			    "gl_FragColor = color;", 
			"}", 
			"else {", 
			    "gl_FragColor = texture(texture_sampler, uv) * color;", 
			"}",  
		"}" 
	};

	static std::string default_fragment_shader_source_stringified = "";
	static std::string default_vertex_shader_source_stringified = "";
	// Used by Graphics::s_DefaultShaderText
	static std::string text_vertex_shader_source = "#version 330 core \n layout(location = 0) in vec4 vertex; \n out vec2 TexCoords; \n uniform mat4 projection_matrix; \n uniform mat4 view_matrix = mat4(1.0f); \n void main() \n{ \n gl_Position = projection_matrix * view_matrix * vec4(vertex.xy, 0, 1); \n TexCoords = vertex.zw; \n }";
	static std::string text_fragment_shader_source = "#version 330 core \n in vec2 TexCoords; \n uniform sampler2D texture; \n uniform vec3 text_color; \n out vec4 color; \n void main() \n { \n color = vec4(1,1,1,texture2D(texture, TexCoords).r) * vec4(text_color,1); \n }";
	
} }