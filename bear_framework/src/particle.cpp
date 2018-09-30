#include"../include/graphics/particle.h"

#include"../include/core/random.h"

using namespace bear;
using namespace bear::graphics;

Particle::Particle(ParticleConfig& a_Config, ParticleConfigFlags::Value a_Flags)
{
	position = a_Config.position;
	size = a_Config.size;
	color = a_Config.color;
	velocity = a_Config.velocity;
	deathTime = a_Config.deathTime;
	
	// Check the flags!
	if (a_Flags & ParticleConfigFlags::RANDOM_POSITION) {
		// @TODO
	}
	else if (a_Flags & ParticleConfigFlags::RANDOM_POSITION_CIRCLE) {
		position = a_Config.circlePositionCenter + core::randomPointInsideCircle(a_Config.circlePositionRadius);
	}
	if (a_Flags & ParticleConfigFlags::RANDOM_SIZE) {
		size = core::randomFloatInterval(a_Config.min_size, a_Config.max_size);
	}
	if (a_Flags & ParticleConfigFlags::RANDOM_VELOCITY) {
		// @TODO
	}
	if (a_Flags & ParticleConfigFlags::RANDOM_COLOR) {
		// @TODO
	}
	if (a_Flags & ParticleConfigFlags::RANDOM_DEATHTIME) {
		// @TODO
	}
}

void ParticlePool::addParticles(int num, ParticleConfig& config, ParticleConfigFlags::Value a_Flags)
{
	for (int i = 0; i < num; i++) {
		particle_list.push_back( Particle(config, a_Flags) );
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