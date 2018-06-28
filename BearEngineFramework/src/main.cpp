#include<iostream>

#define BEAR_DIRTY_RENDER
#include<graphics\graphics.h>

#define BEAR_GLFW_WINDOW
#include<window/window.h>

#include<core\matrix4x4.h>

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
	shader.setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, 400, 400, 0, -1, 1));

	graphics::Renderable triangle(graphics::renderable_type::Rectangle, core::Vector2f(10,10), core::Vector2f(100, 100), core::Color::Blue());
	graphics::Renderable rect(graphics::renderable_type::Triangle, core::Vector2f(100, 150), core::Vector2f(200, 100), core::Color::Red());

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
		rect.draw(shader);
	
		window.display();
	}
	
	bear::window::GLFW_Window::exit();
	graphics::Graphics::exit();

	return 0;
}