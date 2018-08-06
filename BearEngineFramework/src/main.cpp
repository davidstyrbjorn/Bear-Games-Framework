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
	
	if (!graphics::Graphics::init()) {
		printf("False returned from Graphics::init()\n");
	}
	
	shader.compile("D:\\temp\\text_vertex.txt", "D:\\temp\\text_fragment.txt", false);
	shader.enable();
	shader.setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, 720, 0, 540, -1, 1));
	shader.setUniformInteger("texture", 0);

	graphics::Font font("D:\\temp\\arial.ttf", 30);
	graphics::TextLabel text("This is my finish accent", font, core::Vector2f(0,100), core::Color::Red());
	graphics::TextLabel text2("Sample text", font, core::Vector2f(0, 0), core::Color::Blue());
	graphics::TextLabel text3("Permanent vacation", font, core::Vector2f(100, 300), core::Color::Green());

	graphics::BatchRenderer renderer;
	renderer.init(720, 540);

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

	graphics::Renderable sprite2("D:\\temp\\sample.jpg");
	sprite2.transform().m_Position = core::Vector2f(400, 300);

	graphics::Renderable list[60];
	shitInShapes(list);

	core::Clock c;
	c.start();
	unsigned int fps = 0;

	sound::SoundSource source("D:\\temp\\sound.wav");
	source.play();

	test sounding;
	//sounding.play();

	while (myWindow.isOpen()) 
	{
		if (c.getTicks() >= 1000) {
			std::cout << fps << "\n";
			c.reset();
			fps = 0;
		}

		myWindow.clear(core::Color(0.1f,0.1f,0.1f));

		if (myWindow.isKeyDown(Key::D))
			x.transform().move(core::Vector2f(2, 0));
		if (myWindow.isKeyDown(Key::A))
			x.transform().move(core::Vector2f(-2, 0));
		if (myWindow.isKeyDown(Key::S))
			x.transform().move(core::Vector2f(0, 2));
		if (myWindow.isKeyDown(Key::W))
			x.transform().move(core::Vector2f(0, -2));			

		for (Event event : myWindow.getRegisteredEvents()) {
			if (event.type == EventType::KeyPressed)
				source.play();
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

		renderer.flush();
		text.draw(shader);
		text2.draw(shader);
		text3.draw(shader);

		myWindow.display();

		fps++;
	}
		
	graphics::Graphics::exit();
	openal.exit();

	return 0;
}