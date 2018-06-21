#include<iostream>

#define BEAR_GLFW_WINDOW
#include<window/window.h>

#define BEAR_DIRTY_RENDER
#include<graphics\graphics.h>

#include<gl\GLU.h>

using namespace bear;

int main()
{
	graphics::Graphics::init();

	graphics::Renderable shape(graphics::renderable_type::Rectangle);
	graphics::Shader shader;

	graphics::Graphics::exit();

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
		
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(0.5, 0);
		glVertex2f(0.5, 0.5);
		glEnd();
		
		shape.draw(shader);
	
		window.display();
	}
	
	bear::window::GLFW_Window::exit();

	return 0;
}