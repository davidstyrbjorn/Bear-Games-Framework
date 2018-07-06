#include<iostream>

#define BEAR_DIRTY_RENDER
#include<graphics\graphics.h>

#define BEAR_SFML_WINDOW
#include<window/window.h>

#include<core\matrix4x4.h>
#include<core\file_utility.h>

using namespace bear;

int main()
{
	// SFML
	bear::window::SFML_Window window(300, 300, "SFML FUCKY");
	
	if (!graphics::Graphics::init(true)) {
		printf("False returned from Graphics::init()\n");
	}
	graphics::Shader shader("D:\\temp\\vert.txt", "D:\\temp\\frag.txt");
	shader.enable();
	shader.setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, 300, 300, 0, -1, 1));
	shader.setUniformInteger("textureSampler", 0);

	graphics::Renderable rect(graphics::renderable_type::Sprite, core::Vector2f(0, 0), "D:\\temp\\cat.png");
	
	while (window.isOpen()) 
	{
		window.clear();
	
		for (Event e : window.getRegisteredEvents()) {
			if (e.type == EventType::KeyPressed) {
				if(e.key == Key::F)
					printf("shit works");
			}
		}

		rect.draw(shader);

		window.display();
	}

	//bear::window::GLFW_Window::init();
	//bear::window::GLFW_Window window(400, 400, "Fuck");
	//
	//while (window.is_open()) {
	//	window.clear();
	//
	//	for (bear::Event _event : window.getRegisteredEvents()) {
	//		if (_event.type == bear::EventType::KeyPressed) {
	//			if (_event.key == bear::Key::X) {
	//				printf("silly boy");
	//			}
	//		}
	//	}
	//	// Realtime test
	//	if (window.isKeyDown(bear::X)) {
	//		//printf(" _DOWN_ ");
	//	}
	//	
	//	triangle.draw(shader);
	//	rect.draw(shader);
	//
	//	window.display();
	//}
	//
	//bear::window::GLFW_Window::exit();
	
	graphics::Graphics::exit();

	return 0;
}