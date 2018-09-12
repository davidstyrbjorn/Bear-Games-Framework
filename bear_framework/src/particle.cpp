#include"../include/graphics/particle.h"

#include"../include/core/random.h"

using namespace bear;
using namespace bear::graphics;

Particle::Particle(core::Vector2f& _position, int _size, core::Color& _color, core::Vector2f& _velocity, float _life_time)
{
	position = _position;
	size = _size;
	color = _color;
	velocity = _velocity;
	deathTime = _life_time;
}

void ParticlePool::addParticles(int num, ParticleConfig& config, int life_time)
{
	for (int i = 0; i < num; i++) {
		particle_list.push_back(Particle(config.position, config.size, config.color, config.velocity, life_time));
	}
}

void ParticlePool::process(float delta_time)
{
	for (int i = 0; i < particle_list.size(); i++) {
		Particle& particle = particle_list.at(i);
		// The particle is dead
		particle.aliveTime += PARTICLE_INCREMENT_CONST * delta_time;
		if (particle.aliveTime >= particle.deathTime) {
			particle_list.erase(particle_list.begin() + i);
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