#include"../include/graphics/renderers/particle_renderer.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include"../include/graphics/graphics.h"

using namespace bear;
using namespace bear::graphics;

void ParticleRenderer::init()
{
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
	//glEnableVertexAttribArray(2);
	//glEnableVertexAttribArray(3);
	//glEnableVertexAttribArray(4);
	// Layout
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), nullptr); // position
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)sizeof(core::Vector2f)); // color
	//glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, sizeof(Particle), (GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color))); // life_time
	//glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color) + sizeof(int))); // velocity
	//glVertexAttribPointer(4, 1, GL_INT, GL_INT, sizeof(Particle), (GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color) + sizeof(int) + sizeof(core::Vector2f))); // birth_time 
	// birth_time is a long int but the byte size is the same as a normal int so that's the type we tell OpenGL it is, should work fine
	
	// Index buffer
	// Generate the index data structure
	glGenBuffers(1, &_unlit_buffers.IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _unlit_buffers.IBO);
	int offset = 0;
	GLuint indices[INDICES_COUNT];
	for (int i = 0; i < INDICES_COUNT; i = i + 6) {
		indices[i] = offset;			// 0 
		indices[i + 1] = offset + 1;	// 1
		indices[i + 2] = offset + 2;	// 2
		indices[i + 3] = offset + 2;	// 2
		indices[i + 4] = offset + 3;	// 3
		indices[i + 5] = offset;		// 0
		offset += 4;
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
	constexpr float particle_size = 10.0f; // @ this shouldn't be a constant expression value
	for (Particle& p : a_ParticlePool.particle_list) {
		// Using the particle information
		Vertex vert_data[] = 
		{
			{ p.position, p.color, ts },
			{ p.position + core::Vector2f(0, particle_size), p.color, ts },
			{ p.position + core::Vector2f(particle_size, particle_size), p.color, ts },
			{ p.position + core::Vector2f(particle_size, 0), p.color, ts } 
		};
		// Send to the particle buffer
		glBindVertexArray(_unlit_buffers.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);
		unsigned int _buffer_offset = (sizeof(Vertex) * 4) * m_ParticleCount; // Calculate the current-allocated data size of the buffer
		glBufferSubData(GL_ARRAY_BUFFER, _buffer_offset, sizeof(vert_data), vert_data); // Where we actually insert the vert_data
	
		m_ParticleCount++;
	}
}

void bear::graphics::ParticleRenderer::flush()
{
	Graphics::s_DefaultParticleShader->enable();
	// Bind
	glBindVertexArray(_unlit_buffers.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _unlit_buffers.IBO);
	// Draw call
	glDrawElements(GL_TRIANGLES, m_ParticleCount * 6, GL_UNSIGNED_INT, nullptr);
	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	Graphics::s_DefaultParticleShader->disable();
}
