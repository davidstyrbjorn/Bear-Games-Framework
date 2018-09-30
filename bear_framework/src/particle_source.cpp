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
	m_EmissionClock.start();
}

void ParticleSource::update(float dt)
{
	std::cout << m_ParticlePool.particle_list.size() << std::endl;
	// Check if we want to perform an emission of particles
	if (m_EmissionClock.getTicks() >= m_Emitter.repeat_interval) {
		// Insert n number of particles with the correct configuration
		m_ParticlePool.addParticles(m_Emitter.count, m_ParticleConfig, m_ConfigFlags);
		// Reset the clock 
		m_EmissionClock.reset();
	}
	
	m_ParticlePool.process(dt);
}

void bear::graphics::ParticleSource::render(View& a_View)
{
	// Perform a render routine on the particle source
	// Rendering every particle currently inside the m_ParticlePool
	begin();
	submit(m_ParticlePool);
	flush(a_View);
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
	Graphics::s_DefaultParticleShader->setUniformVector2f("gravity", m_SourceConfig.gravity_vector);
	// Render with texture?
	if (m_Texture != nullptr) {
		// Tell shader to render with texture
		Graphics::s_DefaultParticleShader->setUniformInteger("texture_mode", 1);
		// Activate + bind texture target
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Texture->getTextureID());
	}
	else {
		Graphics::s_DefaultParticleShader->setUniformInteger("texture_mode", 0);
	}

	m_Batch->bindBatch();
	// Drawcall
	glDrawArrays(GL_POINTS, 0, m_ParticleCount);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	Graphics::s_DefaultParticleShader->disable();
}

void bear::graphics::ParticleSource::setGravityAcceleration(core::Vector2f & a_Vector)
{
	m_SourceConfig.gravity_vector = a_Vector;
}

void bear::graphics::ParticleSource::setActiveTexture(const std::string& a_TextureName)
{
	m_SourceConfig.texture_name = a_TextureName;
	m_Texture = ResourceManager::Instance()->GetTexture(m_SourceConfig.texture_name);
}

void bear::graphics::ParticleSource::setParticleEmitter(ParticleEmission & a_ParticleEmitter)
{
	m_Emitter = a_ParticleEmitter;
}

void bear::graphics::ParticleSource::setParticleConfiguration(ParticleConfig & a_ParticleConfig, ParticleConfigFlags::Value m_Flags)
{
	m_ParticleConfig = a_ParticleConfig;
	m_ConfigFlags = m_Flags;
}
