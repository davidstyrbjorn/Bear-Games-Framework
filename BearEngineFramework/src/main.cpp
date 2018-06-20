#include<iostream>

#define BEAR_GLFW_WINDOW
#include<window/window.h>

#include<graphics\rectangle.h>

int main()
{
	bear::graphics::Rectangle rect;

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
	
		//rect.draw();
	
		window.display();
	}
	
	bear::window::GLFW_Window::exit();

	return 0;
}