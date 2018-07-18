#include"include\ecs\entity.h"
#include"include\ecs\world.h"
#include"include\ecs\rectangle_component.h"

#include<Windows.h>

using namespace bear::ecs;
using namespace bear::core;

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
	david->getComponent<RectangleComponent>(component_types::RENDERABLE_COMPONENT)->setColor(Color::Blue());
	std::cout << david->getComponent<RectangleComponent>(component_types::RENDERABLE_COMPONENT)->getColor().r << std::endl;

	world.remove("Fabbe");
}

int main()
{
	fillWorld();
	modifyWorld();

	/*
	world.getEntity("Ass")->addComponent(component_type::RectangleComponent);

	*/

	system("pause>null");
	return 0;
}