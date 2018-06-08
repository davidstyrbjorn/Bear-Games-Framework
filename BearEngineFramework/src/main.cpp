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
			if(_event.type == bear::EventType::KeyReleased){
				if(_event.key == bear::Key::X){
					window.close();
				}
			}
			if (_event.type == bear::EventType::MouseReleased) {
				if(_event.button == bear::Mouse::MOUSE_BUTTON_RIGHT)
					printf("mouse pressed!!\n");
			}
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
			if (_event.type == bear::EventType::MousePressed) {
				if (_event.button == bear::Mouse::MOUSE_BUTTON_RIGHT)
					printf("ass");
			}
		}

		window.display();
	}
	
	bear::window::GLFW_Window::exit();
	*/

	return 0;
}