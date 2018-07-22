#include"include\ecs\entity.h"
#include"include\ecs\world.h"
#include"include\ecs\bear_components\rectangle_component.h"
#include"include\ecs\bear_components\triangle_component.h"
#include"include\ecs\bear_components\transform_component.h"

#include<Windows.h>

using namespace bear::ecs;
using namespace bear::core;

class MyComponent : public IComponent {
public:
	int x = 0;

public:
	void init() override { }
	void update() override { }
	void terminate() override { }
};

World world;

void fillWorld()
{
	world.create("David");
	world.create("Fabbe");
	world.create("Alex");
}

void modifyWorld()
{
	auto david = world.getEntity("David");
	david->setID("Modified David");

	david->addComponent(component_types::TRIANGLE_COMPONENT);
	david->removeComponent(component_types::RENDERABLE_COMPONENT);

	david->update();

	auto temp = david->getComponent<TriangleComponent>(component_types::RENDERABLE_COMPONENT);
	if (temp == nullptr)
	{
		printf("Got NULLPTR from getComponent<RENDERABLE_COMPONENT>");
	}

	auto transform = david->transform();
	transform->m_Position = Vector2f(100, 100);

	//david->addComponent<MyComponent>();
	//david->getComponent<MyComponent>()->x += 5;

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