#include"include\ecs\entity.h"
#include"include\ecs\world.h"

#include<Windows.h>

using namespace bear::ecs;

int main()
{
	World world;
	world.create("Ass");
	world.create("Flat");
	world.create("Shake");

	auto entity = world.getEntity("Ass").lock();
	entity->setID("yo");

	return 0;
}