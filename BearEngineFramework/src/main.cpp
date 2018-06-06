#include<iostream>

#define BEAR_SFML_WINDOW
#include<window.h>

int main()
{
	// SFML
	
	bear::window::SFML_Window window(400, 400, "SFML FUCKY");
	while (window.is_open()) {
		window.clear();

		window.display();
	}
	
	// GLFW
	/*
	bear::window::GLFW_Window::init();
	
	bear::window::GLFW_Window window(400, 400, "Fuck");
	while (window.is_open()) {
		window.clear();
	
		window.display();
	}
	
	bear::window::GLFW_Window::exit();
	*/

	return 0;
}