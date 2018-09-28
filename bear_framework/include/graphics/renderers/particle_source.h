#pragma once

#include"../particle.h"
#include"../vertex.h"
#include"unlit_batch.h"

#define PARTICLE_SIZE sizeof(bear::graphics::Vertex)*4
#define MAX_PARTICLES 10000
#define PARTICLE_BUFFER_SIZE PARTICLE_SIZE * MAX_PARTICLES
#define INDICES_COUNT MAX_PARTICLES*6

namespace bear { namespace graphics {

	struct Image;
	class Texture;
	class View;

	struct ParticleSourceConfiguration {
		core::Vector2f gravity_vector;
		std::string texture_name;
	};

	class ParticleSource {
	private:
		UnlitBatcher* m_Batch;
		unsigned int m_ParticleCount = 0;
		ParticleSourceConfiguration m_Config;
		Texture* m_Texture;

		static View &defaultView;

	public:
		ParticleSource() { }
		~ParticleSource();

		// Init required stuff for particle buffer
		void init();

		// Render routines
		void begin();
		void submit(ParticlePool& a_ParticlePool);
		void flush(View& a_View = defaultView);

		// Config methods
		void setGravityAcceleration(core::Vector2f& a_Vector);
		void setActiveTexture(const std::string& a_TextureName);
	};

} }