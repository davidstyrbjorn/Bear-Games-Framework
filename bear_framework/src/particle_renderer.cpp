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

	Graphics::s_DefaultParticleShader->setUniformVector2f("acceleration", core::Vector2f(0, 0.001));

	// Generate the particle buffers
	glGenBuffers(1, &_unlit_buffers.VBO);
	glGenBuffers(1, &_unlit_buffers.IBO);
	glGenVertexArrays(1, &_unlit_buffers.VAO);

	glBindVertexArray(_unlit_buffers.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);
	glBufferData(GL_ARRAY_BUFFER, PARTICLE_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
	
	// Buffer layout
	// Enable the attributes in shader -> layout(location = n)
	glEnableVertexAttribArray(0); // position  (vec2)
	glEnableVertexAttribArray(1); // color     (vec4)
	glEnableVertexAttribArray(2); // size      (float)
	glEnableVertexAttribArray(3); // velocity  (vec2)
	glEnableVertexAttribArray(4); // lifeTime  (float)
	glEnableVertexAttribArray(5); // deathTime (float)
	// Specify the layout attributes
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), 
		(GLvoid*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), 
		(GLvoid*)(sizeof(core::Vector2f)));
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), 
		(GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex),
		(GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color) + sizeof(float)));
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex),
		(GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color) + sizeof(float) + sizeof(core::Vector2f)));
	glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex),
		(GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color) + sizeof(float) + sizeof(core::Vector2f) + sizeof(float)));

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
		ParticleVertex vert_point[] = { p.position, p.color, static_cast<float>(p.size), p.velocity, p.aliveTime, p.deathTime };
		glBindVertexArray(_unlit_buffers.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);
		unsigned int _offset = sizeof(ParticleVertex) * m_ParticleCount; // Current allocated buffer size
		glBufferSubData(GL_ARRAY_BUFFER, _offset, sizeof(vert_point), vert_point);
		m_ParticleCount++;
	}
}

void bear::graphics::ParticleRenderer::flush()
{
	// Draw point primitive
	// Bind
	Graphics::s_DefaultParticleShader->enable();
	glBindVertexArray(_unlit_buffers.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);
	// Draw
	glDrawArrays(GL_POINTS, 0, m_ParticleCount);
	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
