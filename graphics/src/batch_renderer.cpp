#include"../include/graphics/renderers/batch_renderer.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include"../include/graphics/shader.h"
#include"../include/graphics/renderable.h"
#include"../include/graphics/graphics.h"

#include<core\matrix4x4.h>

using namespace bear::graphics;

bear::graphics::BatchRenderer::BatchRenderer()
{

}

bear::graphics::BatchRenderer::~BatchRenderer()
{
}

void bear::graphics::BatchRenderer::init(unsigned int a_Width, unsigned int a_Height)
{
	// Gen the buffers & create shaders
	m_UnlitShader = new Shader();
	m_UnlitShader->compile(default_vertex_shader, unlit_default_fragment_shader, true);
	m_UnlitShader->enable();
	m_UnlitShader->setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, a_Width, a_Height, 0, -1, 1));

	glGenBuffers(1, &_unlit_buffers.VBO);
	glGenVertexArrays(1, &_unlit_buffers.VAO);
}