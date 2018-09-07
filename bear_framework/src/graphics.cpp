#include "../include/graphics/graphics.h"

#include"../include/core/matrix4x4.h"

#define GLEW_STATIC
#include"GL\glew.h"

using namespace bear;
using namespace bear::graphics;

Shader* Graphics::s_DefaultShader = new Shader();
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

	// Setup the default shaders used by the renderers
	s_DefaultShader->setSource(default_vertex_shader_source, default_fragment_shader_source);
	s_DefaultShader->compile();
	s_DefaultShaderText->setSource(text_vertex_shader_source, text_fragment_shader_source);
	s_DefaultShaderText->compile();
	s_DefaultParticleShader->setSourceFromFile("C:\\temp\\particle_vertex.txt", "C:\\temp\\particle_frag.txt");
	s_DefaultParticleShader->setGeometrySourcePath("C:\\temp\\particle_geometry.txt");
	s_DefaultParticleShader->compile();

	window_resize_callback(a_Width, a_Height);

	return true;
}

bool bear::graphics::Graphics::exit()
{
	delete s_DefaultShader;
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