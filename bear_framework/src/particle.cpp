#include"../include/graphics/particle.h"

#include<random>

using namespace bear;
using namespace bear::graphics;

Particle::Particle(core::Vector2f& _position, core::Color& _color, core::Vector2f& _velocity, int _life_time)
{
	position = _position;
	color = _color;
	velocity = _velocity;
	life_time = _life_time;
}

void ParticlePool::addParticles(int num, core::Vector2f& position, core::Color& color, core::Vector2f& velocity, int life_time)
{
	for (int i = 0; i < num; i++) {
		particle_list.push_back(Particle(position, color, velocity, life_time));
		particle_list.back().birth_time = pool_timer;
	}
}

void ParticlePool::addParticles(int num, ParticleConfig& config, int life_time)
{
	for (int i = 0; i < num; i++) {
		particle_list.push_back(Particle(config.position, config.color, config.velocity, life_time));
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
			std::cout << "Erased particle\n";
		}
	}
}

void bear::graphics::ParticleConfig::makePositionRandom(float min_x, float max_x, float min_y, float max_y)
{
	// @ TODO
}

void bear::graphics::ParticleConfig::makeColorRandom()
{
	// @ TODO
}

void bear::graphics::ParticleConfig::makeVelocityRandom(float min_x, float max_x, float min_y, float max_y)
{
	// @ TODO
}
