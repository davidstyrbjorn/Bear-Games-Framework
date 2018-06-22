#include<iostream>

#define BEAR_GLFW_WINDOW
#include<window/window.h>

#define BEAR_DIRTY_RENDER
#include<graphics\graphics.h>

using namespace bear;

int main()
{

	// SFML
	//bear::window::SFML_Window window(400, 400, "SFML FUCKY");
	//while (window.is_open()) {
	//
	//	window.clear();
	//	
	//	for(bear::Event _event : window.getRegisteredEvents())
	//	{
	//
	//	}
	//	// Realtime test
	//	rect.Draw();
	//
	//	window.display();
	//}

	// GLFW
	if (graphics::Graphics::init()) {
		printf("flowers");
	}

	graphics::Renderable shape(graphics::renderable_type::Rectangle);
	graphics::Shader shader;

	bear::window::GLFW_Window::init();
	bear::window::GLFW_Window window(400, 400, "Fuck");

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
		
		shape.draw(shader);
	
		window.display();
	}
	
	bear::window::GLFW_Window::exit();
	graphics::Graphics::exit();

	return 0;
}