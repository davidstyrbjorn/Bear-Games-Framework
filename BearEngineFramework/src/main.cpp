#include<iostream>

#define BEAR_DIRTY_RENDER
#include<graphics\graphics.h>

#define BEAR_GLFW_WINDOW
#include<window/window.h>

using namespace bear;

int main()
{

	// SFML
	//bear::window::SFML_Window window(400, 400, "SFML FUCKY");
	//
	//if (!graphics::Graphics::init(true)) {
	//	printf("False returned from Graphics::init()\n");
	//}
	//graphics::Renderable shape(graphics::renderable_type::Rectangle);
	//graphics::Shader shader("D:\\temp\\vert.txt", "D:\\temp\\frag.txt");
	//
	//while (window.is_open()) {
	//
	//	window.clear();
	//	
	//	for(bear::Event _event : window.getRegisteredEvents())
	//	{
	//
	//	}
	//	// Realtime test
	//
	//	window.display();
	//}



	bear::window::GLFW_Window::init();
	bear::window::GLFW_Window window(400, 400, "Fuck");
	
	if (!graphics::Graphics::init(true)) {
		printf("False returned from Graphics::init()\n");
	}
	graphics::Shader shader("D:\\temp\\vert.txt", "D:\\temp\\frag.txt");
	shader.enable();

	graphics::Renderable triangle(graphics::renderable_type::Rectangle, core::Vector2f(0,0), core::Vector2f(100, 100), core::Color::Blue());
	
	while (window.is_open()) {
		window.clear();
	
		for (bear::Event _event : window.getRegisteredEvents()) {
			if (_event.type == bear::EventType::KeyPressed) {
				if (_event.key == bear::Key::X) {
					printf("silly boy");
				}
			}
		}
		// Realtime test
		if (window.isKeyDown(bear::X)) {
			//printf(" _DOWN_ ");
		}
		
		triangle.draw(shader);
	
		window.display();
	}
	
	bear::window::GLFW_Window::exit();
	graphics::Graphics::exit();

	return 0;
}