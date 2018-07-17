#include"include\ecs\entity.h"
#include"include\ecs\world.h"

#include<Windows.h>

using namespace bear::ecs;

World world;

typedef std::shared_ptr<Entity> entityPtr;

void fillWorld()
{
	world.create("David");
	world.create("Fabbe");
	world.create("Alex");
}

void modifyWorld()
{
	entityPtr david = world.getEntity("David");
	david->setID("Modified David");
	david->addComponent(component_types::RENDERABLE_COMPONENT);
	  david->getComponent(component_types::RENDERABLE_COMPONENT)->getType() << "\n";

	world.remove("Fabbe");
}

int main()
{
	fillWorld();
	modifyWorld();

	/*
	world.getEntity("Ass")->addComponent(component_type::RectangleComponent);

	*/

	return 0;
}