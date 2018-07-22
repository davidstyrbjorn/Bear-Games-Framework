#include<iostream>

#include<graphics\graphics.h>

#define BEAR_SFML_WINDOW
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

	// SFML
	bear::window::SFML_Window window(860, 720, "SFML Window");
	
	if (!graphics::Graphics::init()) {
		printf("False returned from Graphics::init()\n");
	}

	shader.compile("D:\\temp\\vert.txt", "D:\\temp\\frag_unlit.txt");
	shader.enable();
	shader.setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, 860, 720, 0, -1, 1));	

	graphics::Shape shape = graphics::Shape::CreateTriangle(core::Vector2f(0, 0), core::Vector2f(100, 100), core::Color::Red());

	while (window.isOpen()) 
	{
		window.clear(core::Color(0.2f, 0.1f, 0.25f));
	
		for (Event e : window.getRegisteredEvents()) {
			if (e.type == EventType::KeyPressed) {
				if(e.key == Key::F)
					printf("shit works");
			}
			if (e.type == EventType::WindowReiszed) {
				shader.setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, e.size.x, e.size.y, 0, -1, 1));
			}
		}
	
		shader.enable();
		shape.draw(shader);
	
		window.display();
	}

	//bear::window::GLFW_Window::init();
	//bear::window::GLFW_Window myWindow(720, 540, "Fuck");
	//
	//if (!graphics::Graphics::init(true)) {
	//	printf("False returned from Graphics::init()\n");
	//}
	//
	//shader.compile("D:\\temp\\vert.txt", "D:\\temp\\frag.txt");
	//shader.enable();
	//shader.setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, 720, 540, 0, -1, 1));
	//shader.setUniformInteger("textureSampler", 0);
	//
	//graphics::Renderable rect(graphics::renderable_type::Sprite, core::Vector2f(100, 100), "D:\\temp\\cat.png");
	//
	//while (myWindow.isOpen()) {
	//	myWindow.clear(core::Color::Black());
	//
	//	for (bear::Event _event : myWindow.getRegisteredEvents()) {
	//		if (_event.type == bear::EventType::WindowReiszed)
	//		{
	//			std::cout << _event.size << std::endl;
	//			//shader.setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, _event.size.x, _event.size.y, 0, -1, 1));
	//		}
	//	}
	//	
	//	rect.draw(shader);
	//
	//	myWindow.display();
	//}
	//
	//bear::window::GLFW_Window::exit();
	//
	//graphics::Graphics::exit();

	return 0;
}