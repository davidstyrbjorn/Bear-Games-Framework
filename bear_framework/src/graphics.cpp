#include "../include/graphics/graphics.h"

#include"../include/core/matrix4x4.h"
#include"../include/memory/resource_manager.h"

#define GLEW_STATIC
#include"GL\glew.h"

using namespace bear;
using namespace bear::graphics;

Shader* Graphics::s_DefaultShader = nullptr;

Shader* Graphics::s_DefaultShaderText = new Shader();
Shader* Graphics::s_DefaultParticleShader = new Shader();

unsigned int Graphics::m_ScreenWidth = 0;
unsigned int Graphics::m_ScreenHeight = 0;

bool bear::graphics::Graphics::init(unsigned int a_Width, unsigned int a_Height)
{
	// Init GLEW
	glewExperimental = true;
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		if (result == GLEW_ERROR_NO_GL_VERSION) {
			printf("No GL context ( GLEW_ERROR_NO_GL_VERSION )\n");
		}
		return false;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	#pragma region STRINGIFY SHADERS	
	size_t count;
	int i = 0;
	count = sizeof(default_vertex_shader_source) / sizeof(std::string);
	for (i = 0; i < count; i++) {
		default_vertex_shader_stringified += default_vertex_shader_source[i] + "\n";
	}
	count = sizeof(default_fragment_shader_source) / sizeof(std::string);
	for (i = 0; i < count; i++) {
		default_fragment_shader_stringified += default_fragment_shader_source[i] + "\n";
	}
	// Text shader
	count = sizeof(text_vertex_shader_source) / sizeof(std::string);
	for (i = 0; i < count; i++) {
		text_vertex_shader_stringified += text_vertex_shader_source[i] + "\n";
	}
	count = sizeof(text_fragment_shader_source) / sizeof(std::string);
	for (i = 0; i < count; i++) {
		text_fragment_shader_stringified += text_fragment_shader_source[i] + "\n";
	}
	#pragma endregion

	// Setup the default shaders used by the renderers
	ResourceManager::Instance()->CreateShaderFromSource("default_shader",
		default_vertex_shader_stringified, default_fragment_shader_stringified, "");
	s_DefaultShader = ResourceManager::Instance()->GetShader("default_shader");
	s_DefaultShader->enable();
	s_DefaultShader->setUniformVector2f("light_pos", core::Vector2f(300, 300));
	s_DefaultShader->setUniformVector4f("light_color", core::Color::White());
	
	ResourceManager::Instance()->CreateShaderFromSource("text_shader",
		text_vertex_shader_stringified,
		text_fragment_shader_stringified, "");
	s_DefaultShaderText = ResourceManager::Instance()->GetShader("text_shader");
	
	s_DefaultParticleShader->setSourceFromFile("shaders\\particle_vertex.txt", "shaders\\particle_frag.txt");
	s_DefaultParticleShader->setGeometrySourcePath("shaders\\particle_geometry.txt");
	s_DefaultParticleShader->compile();

	window_resize_callback(a_Width, a_Height);

	return true;
}

bool bear::graphics::Graphics::exit()
{
	//delete s_DefaultShader;
	delete s_DefaultShaderText;
	delete s_DefaultParticleShader;
	return true;
}

void bear::graphics::Graphics::window_resize_callback(unsigned int a_Width, unsigned int a_Height)
{
	m_ScreenWidth = a_Width;
	m_ScreenHeight = a_Height;
	// Update shader matrix uniforms
	core::Matrix4x4 ortho = core::Matrix4x4::Orthographic(0, m_ScreenWidth, m_ScreenHeight, 0, -1, 1);
	s_DefaultShader->enable();
	s_DefaultShader->setUniformMatrix4x4("projection_matrix", ortho);
	s_DefaultShaderText->enable();
	s_DefaultShaderText->setUniformMatrix4x4("projection_matrix", ortho);
	s_DefaultParticleShader->enable();
	s_DefaultParticleShader->setUniformMatrix4x4("projection_matrix", ortho);

	glViewport(0, 0, a_Width, a_Height);
}