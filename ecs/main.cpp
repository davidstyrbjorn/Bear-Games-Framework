#include"include\ecs\entity.h"
#include"include\ecs\world.h"
#include"include\ecs\bear_components\rectangle_component.h"
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
	bool reset() override { return true; }
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
	david->addComponent(component_types::RENDERABLE_COMPONENT);
	david->getComponent<RectangleComponent>(component_types::RENDERABLE_COMPONENT)->setColor(Color::Blue());
	//david->transform()->m_Position = Vector2f(10, 20);

	david->addComponent<MyComponent>();
	david->getComponent<MyComponent>()->x += 5;

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