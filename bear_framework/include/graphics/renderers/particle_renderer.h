#pragma once

#include"../particle.h"
#include"../vertex.h"
#include"unlit_batch.h"

#define PARTICLE_SIZE sizeof(bear::graphics::Vertex)*4
#define MAX_PARTICLES 5000
#define PARTICLE_BUFFER_SIZE PARTICLE_SIZE * MAX_PARTICLES
#define INDICES_COUNT MAX_PARTICLES*6

namespace bear { namespace graphics {

	struct Image;

	class ParticleRenderer {
	private:
		UnlitBatcher* m_Batch;
		unsigned int m_TBO;
		unsigned int m_ParticleCount = 0;

	public:
		ParticleRenderer() { }
		~ParticleRenderer();

		// Init required stuff for particle buffer
		void init();

		// Render routines
		void begin();
		void submit(ParticlePool& a_ParticlePool);
		void flush();

		// Config methods
		void setGravityAcceleration(core::Vector2f& a_Vector);
		void setUseTexture(bool a_UseTexture);
		void setActiveTexture(const Image& a_Image);
	};

} }