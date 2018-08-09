#include<iostream>

#include<graphics\graphics.h>
#include<graphics\renderers\batch_renderer.h>

#include<window/window.h>

#include<sound\sound.h>

#include<core\matrix4x4.h>
#include<core\file_utility.h>
#include<core\clock.h>

#include<time.h>
#include<functional>

using namespace bear;

void shitInShapes(graphics::Renderable _list[])
{
	srand(time(NULL));
	for (int i = 0; i < 60; i++)
	{
		int n = rand() % 100;
		graphics::renderable_type t = n < 50 ? graphics::renderable_type::Rectangle : graphics::renderable_type::Triangle;
		_list[i].setType(t);

		int x = rand() % 720;
		int y = rand() % 540;
		int w = (rand() % 100) + 25;
		int h = (rand() % 100) + 25;

		float r = rand() % 255;
		float g = rand() % 255;
		float b = rand() % 255;
		core::Color c = core::Color(r / 255, g / 255, b / 255);

		_list[i].transform().m_Position = core::Vector2f(x, y);
		_list[i].transform().m_Size = core::Vector2f(w, h);
		_list[i].setColor(c);
	}
}

graphics::Shader shader;

int main()
{
	sound::SoundContext openal;
	openal.init();

	bear::window::Window myWindow(720, 540, "THIS IS A WINDOW");
	
	if (!graphics::Graphics::init(720, 540)) {
		printf("False returned from Graphics::init()\n");
	}

	graphics::Font font("D:\\temp\\arial.ttf", 30);
	graphics::TextLabel text("ThiS Is SoMe FucKEd T_EX@TWA", font, core::Vector2f(0,100), core::Color::Red());
	graphics::TextLabel text2("Sample text", font, core::Vector2f(0, 540), core::Color::Blue());
	graphics::TextLabel text3("Permanent vacation", font, core::Vector2f(0, 300), core::Color::Green());

	graphics::BatchRenderer renderer;
	renderer.init(720, 540);

	//graphics::View view(720, 540); // This feels so redundant and hard to keep up

	// IDEA:
	// Inside the graphics module have a singleton class called ContextInformation/GraphicsInformation
	// From the user side all we have to call is graphics::Graphics::init(myWindow);
	// renderers etc can then use this myWindow to get useful information like cursor position and window size 

	graphics::Renderable x(graphics::renderable_type::Rectangle);
	x.transform().m_Position = core::Vector2f(100, 100);
	x.transform().m_Size = core::Vector2f(150, 50);
	x.setColor(core::Color::Blue());

	graphics::Renderable y(graphics::renderable_type::Rectangle);
	y.transform().m_Size = core::Vector2f(75, 125);
	y.setColor(core::Color::Red());

	graphics::Renderable z(graphics::renderable_type::Triangle);
	z.transform().m_Size = core::Vector2f(120, 100);
	z.transform().m_Position = core::Vector2f(500, 400);
	z.setColor(core::Color::Green());

	graphics::Renderable w(graphics::renderable_type::Triangle);
	w.transform().m_Position = core::Vector2f(650, 300);
	w.transform().m_Size = core::Vector2f(60, 150);
	w.setColor(core::Color::Red());

	graphics::Renderable sprite("D:\\temp\\cat.png");
	sprite.transform().m_Position = core::Vector2f(0, 0);

	graphics::Renderable sprite2("D:\\temp\\sample.jpg");
	sprite2.transform().m_Position = core::Vector2f(400, 300);

	graphics::Renderable list[60];
	shitInShapes(list);

	core::Clock c;
	c.start();
	unsigned int fps = 0;

	sound::SoundSource sfx("D:\\temp\\sound.wav");

	graphics::View view;
	core::Vector2f viewPos;

	while (myWindow.isOpen()) 
	{
		if (c.getTicks() >= 1000) {
			std::cout << fps << "\n";
			c.reset();
			fps = 0;
		}

		myWindow.clear(core::Color(0.1f,0.1f,0.1f));

		// Camera movement
		if (myWindow.isKeyDown(Key::D))
			viewPos += core::Vector2f(-0.5f, 0);
		if (myWindow.isKeyDown(Key::A))
			viewPos += core::Vector2f(0.5f, 0);
		if (myWindow.isKeyDown(Key::S))
			viewPos += core::Vector2f(0, -0.5f);
		if (myWindow.isKeyDown(Key::W))
			viewPos += core::Vector2f(0, 0.5f);

		view.setPosition(viewPos);

		for (Event event : myWindow.getRegisteredEvents()) {
			if (event.type == EventType::WindowReiszed) {
				graphics::Graphics::window_resize_callback(event.size.x, event.size.y);
			}
		}

		renderer.begin();
		for (int i = 0; i < 60; i++) {
			renderer.submit(list[i]);
		}
		renderer.submit(x);
		renderer.submit(y);
		renderer.submit(z);
		renderer.submit(w);
		renderer.submit(sprite);
		renderer.submit(sprite2);
		renderer.flush(view);

		text.draw();
		text2.draw(view);
		text3.draw();

		myWindow.display();

		fps++;
	}
		
	graphics::Graphics::exit();
	openal.exit();

	return 0;
}