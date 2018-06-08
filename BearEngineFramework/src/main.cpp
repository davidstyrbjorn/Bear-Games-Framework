#include<iostream>

#define BEAR_SFML_WINDOW
#include<window.h>

int main()
{
	// SFML
	bear::window::SFML_Window window(400, 400, "SFML FUCKY");
	while (window.is_open()) {

		window.clear();
		
		for(bear::Event _event : window.getRegisteredEvents())
		{
			
		}
		// Realtime test
		if (window.isMouseDown(bear::Mouse::MOUSE_BUTTON_LEFT)) {
			printf(" _DOWN_ ");
		}

		window.display();
	}
	
	// GLFW
	/*
	bear::window::GLFW_Window::init();
	
	bear::window::GLFW_Window window(400, 400, "Fuck");
	while (window.is_open()) {
		window.clear();
	
		for (bear::Event _event : window.getRegisteredEvents()) {
			//if (_event.type == bear::EventType::KeyDown) {
			//	if (_event.key == bear::Key::X) {
			//		printf("silly boy");
			//	}
			//}
		}
		// Realtime test
		if (window.isMouseDown(bear::Mouse::MOUSE_BUTTON_MIDDLE)) {
			printf(" _DOWN_ ");
		}

		window.display();
	}
	
	bear::window::GLFW_Window::exit();
	*/

	return 0;
}