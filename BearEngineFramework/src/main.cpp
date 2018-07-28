#include<iostream>

#include<graphics\graphics.h>

#include<window/window.h>

#include<core\matrix4x4.h>
#include<core\file_utility.h>

#include<functional>

using namespace bear;

class Foo {
public:
	void bar(int a_Width, int a_Height) {
		//std::cout << a_Width << ", " << a_Height << std::endl;
	}

private:
	int x = 0;
};

graphics::Shader shader;

int main()
{
	void (Foo::*funcPtr)(int, int) = &Foo::bar;
	Foo *obj = nullptr;
	(obj->*funcPtr)(100, 100);
	(obj->*funcPtr)(100, 110);
	(obj->*funcPtr)(200, 125);
	
	bear::window::Window myWindow(720, 540, "Fuck");
	
	if (!graphics::Graphics::init()) {
		printf("False returned from Graphics::init()\n");
	}
	
	shader.compile("D:\\temp\\vert.txt", "D:\\temp\\frag_unlit.txt", false);
	shader.enable();
	shader.setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, 720, 540, 0, -1, 1));
	shader.setUniformInteger("textureSampler", 0);

	graphics::Shape triangle = graphics::Shape::CreateTriangle(core::Vector2f(100, 100), core::Vector2f(100, 100), core::Color::Red());
	graphics::Shape rectangle = graphics::Shape::CreateRectangle(core::Vector2f(250, 400), core::Vector2f(250, 60), core::Color::Blue());

	//graphics::Shape shape = graphics::Shape(graphics::renderable_type::Sprite);

	while (myWindow.isOpen()) 
	{
		myWindow.clear(core::Color::Black());
			
		if (myWindow.isKeyDown(Key::D))
			triangle.transform().move(core::Vector2f(2, 0));
		if (myWindow.isKeyDown(Key::A))
			triangle.transform().move(core::Vector2f(-2, 0));
		if (myWindow.isKeyDown(Key::S))
			triangle.transform().move(core::Vector2f(0, 2));
		if (myWindow.isKeyDown(Key::W))
			triangle.transform().move(core::Vector2f(0, -2));

		shader.enable();
		triangle.draw(shader);
		rectangle.draw(shader);

		myWindow.display();
	}
		
	graphics::Graphics::exit();

	return 0;
}