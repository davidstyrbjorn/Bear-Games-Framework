#include"../include/graphics/renderers/particle_source.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include"../include/graphics/graphics.h"
#include"../include/graphics/shader.h"

#include"../include/memory/resource_manager.h"

using namespace bear;
using namespace bear::graphics;

View& ParticleSource::defaultView = View();

ParticleSource::~ParticleSource()
{
	// Delete shit
	delete m_Batch;
}

void ParticleSource::init()
{
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

void bear::graphics::ParticleSource::begin()
{
	// Reset the particle buffer data and count
	m_ParticleCount = 0;
	m_Batch->clearBatch();
}

void bear::graphics::ParticleSource::submit(ParticlePool& a_ParticlePool)
{
	// Go through each particle in the particle pool and add it to the buffer
	for (Particle& p : a_ParticlePool.particle_list) {
		// we're sending only points to the vertex buffer, the geometry shader takes care of expanding into quad primitive
		ParticleVertex vert_point[] = { p.position, p.color, static_cast<float>(p.size), p.velocity, p.aliveTime, p.deathTime };
		m_Batch->updateBatch(vert_point, sizeof(vert_point));
		m_ParticleCount++;
	}
}

void bear::graphics::ParticleSource::flush(View& a_View)
{
	// Draw point primitive
	// Bind
	Graphics::s_DefaultParticleShader->enable();
	Graphics::s_DefaultParticleShader->setUniformMatrix4x4("view_matrix", a_View.getViewMatrix());
	Graphics::s_DefaultParticleShader->setUniformVector2f("gravity", m_Config.gravity_vector);
	if(m_Texture != nullptr)
		Graphics::s_

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture->getTextureID());

	m_Batch->bindBatch();
	// Draw
	glDrawArrays(GL_POINTS, 0, m_ParticleCount);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	Graphics::s_DefaultParticleShader->disable();
}

void bear::graphics::ParticleSource::setGravityAcceleration(core::Vector2f & a_Vector)
{
	m_Config.gravity_vector = a_Vector;
}

void bear::graphics::ParticleSource::setActiveTexture(const std::string& a_TextureName)
{
	m_Config.texture_name = a_TextureName;
	m_Texture = ResourceManager::Instance()->GetTexture(m_Config.texture_name);
}