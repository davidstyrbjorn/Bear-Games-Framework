#pragma once

#include"../particle.h"
#include"../vertex.h"

#define PARTICLE_SIZE sizeof(bear::graphics::Vertex)*4
#define MAX_PARTICLES 1000
#define PARTICLE_BUFFER_SIZE PARTICLE_SIZE * MAX_PARTICLES
#define INDICES_COUNT MAX_PARTICLES*6

namespace bear { namespace graphics {

	struct unlit_buffers
	{
		unsigned int VAO, VBO, IBO;
	};

	class ParticleRenderer {
	private:
		unlit_buffers _unlit_buffers;
		unsigned int m_ParticleCount = 0;

	public:
		ParticleRenderer() { }
		// @ Constructor and delete shit!

		/*
		Init the particle buffer
		*/
		void init();

		// Render routines
		void begin();
		void submit(ParticlePool& a_ParticlePool);
		void flush();
	};

} }