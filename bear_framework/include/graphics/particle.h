#pragma once

#include"../core/vector2.h"
#include"../core/color.h"

#include<vector>

#define PARTICLE_INCREMENT_CONST 1

namespace bear { namespace graphics {

	struct Particle {
		core::Vector2f position;
		core::Color color;
		int life_time;
		core::Vector2f velocity;
		int birth_time;

		// Constructor
		//Particle() { }
		//Particle(core::Vector2f& _position, core::Color& _color, core::Vector2f& velocity, int _life_time);
	};

	struct ParticleConfig {
		core::Vector2f position;
		core::Color color;
		core::Vector2f velocity;

		void makePositionRandom(float min_x, float max_x, float min_y, float max_y);
		void makeColorRandom();
		void makeVelocityRandom(float min_x, float max_x, float min_y, float max_y);
	};

	struct ParticlePool {
		std::vector<Particle> particle_list;
		long int pool_timer = 0; // A timer incremented based on delta time

		void addParticles(int num, core::Vector2f& position, core::Color& color, core::Vector2f& velocity, int life_time);
		void addParticles(int num, ParticleConfig& config, int life_time);
		void process(float delta_time);
	};


} }