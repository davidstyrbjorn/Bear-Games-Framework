#include"../include/graphics/particle.h"

#include"../include/core/random.h"

using namespace bear;
using namespace bear::graphics;

Particle::Particle(core::Vector2f& _position, int _size, core::Color& _color, core::Vector2f& _velocity, int _life_time)
{
	position = _position;
	size = _size;
	color = _color;
	velocity = _velocity;
	life_time = _life_time;
}

void ParticlePool::addParticles(int num, core::Vector2f& position, int size, core::Color& color, core::Vector2f& velocity, int life_time)
{
	for (int i = 0; i < num; i++) {
		particle_list.push_back(Particle(position, size, color, velocity, life_time));
		particle_list.back().birth_time = pool_timer;
	}
}

void ParticlePool::addParticles(int num, ParticleConfig& config, int life_time)
{
	for (int i = 0; i < num; i++) {
		particle_list.push_back(Particle(config.position, config.size, config.color, config.velocity, life_time));
		particle_list.back().birth_time = pool_timer;
	}
}

void ParticlePool::process(float delta_time)
{
	if (particle_list.empty())
		pool_timer = 0;
	pool_timer += PARTICLE_INCREMENT_CONST * delta_time;

	for (int i = 0; i < particle_list.size(); i++) {
		Particle& particle = particle_list.at(i);
		// The particle is dead
		if (pool_timer >= particle.birth_time + particle.life_time) {
			particle_list.erase(particle_list.begin() + i);
		}
		else {
			/*
			@ PARTICLE: This I want to move away from the cpu side possible, allow the shader(GPU) to do this computation
			*/
			particle.position += particle.velocity*delta_time;
			float test = pool_timer / (float)(particle.birth_time + particle.life_time);
			//particle.color.a = 1 - test;

		}
	}
}

/*
Functions used from core/random.h
*/

void bear::graphics::ParticleConfig::makeSizeRandom(int min, int max)
{
	size = core::randomIntegerInterval(min, max);
}

void bear::graphics::ParticleConfig::makeColorRandom()
{
	color = core::Color(core::randomFloatInterval(0.f, 1.f), core::randomFloatInterval(0.f, 1.f), core::randomFloatInterval(0.f,1.f), 1.f);
}

void bear::graphics::ParticleConfig::makeVelocityRandom(float min_x, float max_x, float min_y, float max_y)
{
	velocity = core::Vector2f(core::randomFloatInterval(min_x, max_x), core::randomFloatInterval(min_y, max_y));
}