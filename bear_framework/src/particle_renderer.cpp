#include"../include/graphics/renderers/particle_renderer.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include"../include/graphics/graphics.h"
#include"../include/graphics/shader.h"

using namespace bear;
using namespace bear::graphics;

ParticleRenderer::~ParticleRenderer()
{
	// Delete shit
	delete m_Batch;
	glDeleteTextures(1, &m_TBO);
}

void ParticleRenderer::init()
{
	/*
	0. Renderer uploads only particle data to the next stage/shader stage
	1. Vertex shader passes the data to the geometry shader
	2. In geomtry shader we create quad out of the data and transform positions, send data to frag shader
	3. In the fragment shader we colorize then we're done
	*/

	// Create an opengl image
	glGenTextures(1, &m_TBO);
	glBindTexture(GL_TEXTURE_2D, m_TBO);
	//glTexImage2D(GL_TEXTURE_2D, 0, test_image.m_Format, test_image.m_ImageSize.x, test_image.m_ImageSize.y, 0, test_image.m_Format, GL_UNSIGNED_BYTE, test_image.m_ImageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	VertexAttribute temp[] = {
		{ 0, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (GLvoid*)0 },
		{ 1, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (GLvoid*)(sizeof(core::Vector2f)) },
		{ 2, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color)) },
		{ 3, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color) + sizeof(float)) },
		{ 4, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color) + sizeof(float) + sizeof(core::Vector2f)) },
		{ 5, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color) + sizeof(float) + sizeof(core::Vector2f) + sizeof(float)) }
	};

	m_Batch = new UnlitBatcher(PARTICLE_BUFFER_SIZE, temp, 6);
}

void bear::graphics::ParticleRenderer::begin()
{
	// Reset the particle buffer data and count
	m_ParticleCount = 0;
	m_Batch->clearBatch();
}

void bear::graphics::ParticleRenderer::submit(ParticlePool& a_ParticlePool)
{
	// Go through each particle in the particle pool and add it to the buffer
	static core::Vector2f ts = core::Vector2f(-1, -1);
	for (Particle& p : a_ParticlePool.particle_list) {
		// we're sending only points to the vertex buffer, the geometry shader takes care of expanding into quad primitive
		ParticleVertex vert_point[] = { p.position, p.color, static_cast<float>(p.size), p.velocity, p.aliveTime, p.deathTime };
		m_Batch->updateBatch(vert_point, sizeof(vert_point));
		m_ParticleCount++;
	}
}

void bear::graphics::ParticleRenderer::flush()
{
	// Draw point primitive
	// Bind
	Graphics::s_DefaultParticleShader->enable();
	glBindTexture(GL_TEXTURE_2D, m_TBO);
	m_Batch->bindBatch();
	// Draw
	glDrawArrays(GL_POINTS, 0, m_ParticleCount);
	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	Graphics::s_DefaultParticleShader->disable();
}

void bear::graphics::ParticleRenderer::setGravityAcceleration(core::Vector2f & a_Vector)
{
	Graphics::s_DefaultParticleShader->enable();
	Graphics::s_DefaultParticleShader->setUniformVector2f("gravity", a_Vector);
	Graphics::s_DefaultParticleShader->disable();
}

void bear::graphics::ParticleRenderer::setUseTexture(bool a_UseTexture)
{
	Graphics::s_DefaultParticleShader->enable();
	Graphics::s_DefaultParticleShader->setUniformInteger("texture_mode", a_UseTexture);
	Graphics::s_DefaultParticleShader->disable();
}

void bear::graphics::ParticleRenderer::setActiveTexture(const Image & a_Image)
{
	glBindTexture(GL_TEXTURE_2D, m_TBO);
	glTexImage2D(GL_TEXTURE_2D, 0, a_Image.m_Format, a_Image.m_ImageSize.x, a_Image.m_ImageSize.y, 0, a_Image.m_Format, GL_UNSIGNED_BYTE, a_Image.m_ImageData);
	glBindTexture(GL_TEXTURE_2D, 0);
}