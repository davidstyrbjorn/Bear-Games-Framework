#include"../include/graphics/renderers/particle_renderer.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include"../include/graphics/graphics.h"
#include"../include/graphics/shader.h"

using namespace bear;
using namespace bear::graphics;

void ParticleRenderer::init()
{
	/*
	0. Renderer stores data which is sent to the shader during the main render pass
	1. Send primitive points to the vertex shader, set position, then send to geomtry shader
	2. In geomtry shader create quad and transform into screenspace
	3. In the fragment shader we colorize and render
	
	*/

	m_Shader = new Shader();
	m_Shader->setSourceFromFile("C:\\temp\\particle_vertex.txt", "C:\\temp\\particle_frag.txt");
	m_Shader->setGeometrySourcePath("C:\\temp\\particle_geometry.txt");
	m_Shader->compile();
	m_Shader->enable();
	m_Shader->setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, 510, 720, 0, -1, 1));

	std::cout << "VERTEX SHADER: \n";
	std::cout << m_Shader->m_VertexSource << std::endl << std::endl;

	std::cout << "GEOMETRY SHADER: \n";
	std::cout << m_Shader->m_GeometrySource << std::endl << std::endl;

	std::cout << "FRAGMENT SHADER: \n";
	std::cout << m_Shader->m_FragmentSource << std::endl << std::endl;

	// Generate the particle buffers
	glGenBuffers(1, &_unlit_buffers.VBO);
	glGenBuffers(1, &_unlit_buffers.IBO);
	glGenVertexArrays(1, &_unlit_buffers.VAO);

	glBindVertexArray(_unlit_buffers.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);
	glBufferData(GL_ARRAY_BUFFER, PARTICLE_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
	
	// Buffer layout with the current bound vertex array buffer
	// Enable the attributes in shader -> layout(location = 0)
	glEnableVertexAttribArray(0); // position
	glEnableVertexAttribArray(1); // color
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(core::Vector2f)));
}

void bear::graphics::ParticleRenderer::begin()
{
	// Reset the particle buffer data and count
	m_ParticleCount = 0;
	glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);
	glBufferData(GL_ARRAY_BUFFER, PARTICLE_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
}

void bear::graphics::ParticleRenderer::submit(ParticlePool& a_ParticlePool)
{

	// Go through each particle in the particle pool and add it to the buffer
	static core::Vector2f ts = core::Vector2f(-1, -1);
	for (Particle& p : a_ParticlePool.particle_list) {
		// we're sending only points to the vertex buffer, the geometry shader takes care of expanding into quad primitive
		Vertex vert_point[] = { p.position, p.color, ts };
		glBindVertexArray(_unlit_buffers.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);
		unsigned int _offset = sizeof(Vertex) * m_ParticleCount; // Current allocated buffer size
		glBufferSubData(GL_ARRAY_BUFFER, _offset, sizeof(vert_point), vert_point);
		m_ParticleCount++;
	}
}

void bear::graphics::ParticleRenderer::flush()
{
	// Draw point primitive
	// Bind
	//Graphics::s_DefaultParticleShader->enable();
	m_Shader->enable();

	glBindVertexArray(_unlit_buffers.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);
	// Draw
	glDrawArrays(GL_POINTS, 0, m_ParticleCount);
	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
