#pragma once

#include"../core/vector2.h"
#include"../core/color.h"

#include<vector>

#define PARTICLE_INCREMENT_CONST 1

namespace bear { namespace graphics {

	// Used when rendering a particle primitive
	struct ParticleVertex {
		core::Vector2f position;
		core::Color color;
		float size;
		core::Vector2f velocity;
		float aliveTime;
		float deathTime;
	};

	struct Particle {
		core::Vector2f position;
		int size;
		core::Color color;
		core::Vector2f velocity;
		float aliveTime = 0;
		float deathTime;

		// Constructor
		Particle() { }
		Particle(core::Vector2f& _position, int _size, core::Color& _color, core::Vector2f& _velocity, float _life_time);
	};

	struct ParticleConfig {
		core::Vector2f position;
		int size;
		core::Color color;
		core::Vector2f velocity;

		/* Makes particle size a random integer between min/max */
		void makeSizeRandom(int min, int max);
		/* Makes the particle color a random RGB color value */
		void makeColorRandom();
		/* Makes velocity a random vector with set min/max values */
		void makeVelocityRandom(float min_x, float max_x, float min_y, float max_y);
	};

	struct ParticlePool {
		std::vector<Particle> particle_list;

		void addParticles(int num, ParticleConfig& config, int life_time);
		void process(float delta_time);
	};


} }