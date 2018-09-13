#pragma once

#include"../particle.h"
#include"../vertex.h"

#define PARTICLE_SIZE sizeof(bear::graphics::Vertex)*4
#define MAX_PARTICLES 5000
#define PARTICLE_BUFFER_SIZE PARTICLE_SIZE * MAX_PARTICLES
#define INDICES_COUNT MAX_PARTICLES*6

namespace bear { namespace graphics {

	struct particle_buffers
	{
		unsigned int VAO, VBO;
	};

	class ParticleRenderer {
	private:
		particle_buffers _unlit_buffers;
		unsigned int m_ParticleCount = 0;

	public:
		ParticleRenderer() { }
		~ParticleRenderer();

		/*
		Init the particle buffer
		*/
		void init();

		// Render routines
		void begin();
		void submit(ParticlePool& a_ParticlePool);
		void flush();

		void setGravityAcceleration(core::Vector2f& a_Vector);
	};

} }