#include<iostream>

#define BEAR_DIRTY_RENDER
#include<graphics\graphics.h>

#define BEAR_GLFW_WINDOW
#include<window/window.h>

#include<core\matrix4x4.h>
#include<core\file_utility.h>

#include<functional>

using namespace bear;

class Foo {
public:
	void bar(int a_Width, int a_Height) {
		std::cout << a_Width << ", " << a_Height << std::endl;
	}

private:
	int x = 0;
};

void foo(int a_Width, int a_Height);

graphics::Shader shader;

// BRB
int main()
{
	void (Foo::*funcPtr)(int, int) = &Foo::bar;
	Foo *obj = nullptr;
	(obj->*funcPtr)(100, 100);
	(obj->*funcPtr)(100, 110);
	(obj->*funcPtr)(200, 125);

	// SFML
	//bear::window::SFML_Window window(300, 300, "SFML FUCKY");
	//
	//if (!graphics::Graphics::init(true)) {
	//	printf("False returned from Graphics::init()\n");
	//}
	//graphics::Shader shader("D:\\temp\\vert.txt", "D:\\temp\\frag.txt");
	//shader.enable();
	//shader.setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, 300, 300, 0, -1, 1));
	//shader.setUniformInteger("textureSampler", 0);
	//
	//graphics::Renderable rect(graphics::renderable_type::Sprite, core::Vector2f(0, 0), "D:\\temp\\cat.png");
	//
	//while (window.isOpen()) 
	//{
	//	window.clear();
	//
	//	for (Event e : window.getRegisteredEvents()) {
	//		if (e.type == EventType::KeyPressed) {
	//			if(e.key == Key::F)
	//				printf("shit works");
	//		}
	//	}
	//
	//	rect.draw(shader);
	//
	//	window.display();
	//}

	bear::window::GLFW_Window<Foo>::init();
	bear::window::GLFW_Window<Foo> myWindow(720, 540, "Fuck");

	if (!graphics::Graphics::init(true)) {
		printf("False returned from Graphics::init()\n");
	}

	shader.compile("D:\\temp\\vert.txt", "D:\\temp\\frag.txt");
	shader.enable();
	shader.setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, 720, 540, 0, -1, 1));
	shader.setUniformInteger("textureSampler", 0);

	myWindow.resize_callback = &foo;

	graphics::Renderable rect(graphics::renderable_type::Sprite, core::Vector2f(100, 100), "D:\\temp\\cat.png");

	while (myWindow.isOpen()) {
		myWindow.clear(core::Color::Black());
	
		for (bear::Event _event : myWindow.getRegisteredEvents()) {
			if (_event.type == bear::EventType::KeyPressed) {
				if (_event.key == bear::Key::X) {
					printf("silly boy");
				}
			}
		}
		
		rect.draw(shader);
	
		myWindow.display();
	}
	
	bear::window::GLFW_Window<Foo>::exit();
	
	graphics::Graphics::exit();

	return 0;
}

void foo(int a_Width, int a_Height)
{
	shader.setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, a_Width, a_Height, 0, -1, 1));
}