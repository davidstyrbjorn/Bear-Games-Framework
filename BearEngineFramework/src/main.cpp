#include<iostream>

#include<window\window.h>
#include<sound\sound.h>
#include<core\bounding_box.h>
#include<core\vector2.h>
#include<graphics\graphics.h>

#include<graphics/renderers/particle_renderer.h>

#include<core/random.h>

using namespace bear;

constexpr auto WIDTH = 720;
constexpr auto HEIGHT = 510;

int main()
{
	sound::SoundContext::init();

	bear::window::Window myWindow(WIDTH, HEIGHT, "THIS IS A WINDOW");

	if (!graphics::Graphics::init(WIDTH, HEIGHT))
		std::cout << "Graphics failed to init send help\n";

	graphics::Shader shader;
	shader.setSource(graphics::default_vertex_shader_source, graphics::default_fragment_shader_source);
	shader.compile();
	shader.enable();
	shader.setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, WIDTH, HEIGHT, 0, -1, 1));

	graphics::Shape shape = graphics::Shape::CreateRectangle(core::Vector2f(50, 50), core::Vector2f(110, 50), core::Color::Red());
	graphics::Shape shape2 = graphics::Shape::CreateRectangle(core::Vector2f(100, 120), core::Vector2f(50, 50), core::Color::Blue());

	graphics::ParticleRenderer *pr = new graphics::ParticleRenderer();
	pr->init();
	graphics::ParticlePool pool;

	while (myWindow.isOpen()) 
	{
		float dt = myWindow.getDeltaTime(); // Get the delta time for the last frame
		for (Event event : myWindow.getRegisteredEvents()) { // Process the events here
			if (event.type == EventType::WindowReiszed) {
				graphics::Graphics::window_resize_callback(event.size.x, event.size.y);
			}
			if (event.type == EventType::KeyPressed) {
				if (event.key == Key::X) {
					for (int i = 0; i < 500; i++)	
					{
						graphics::ParticleConfig config;
						config.makeColorRandom();
						config.makeVelocityRandom(-0.3, 0.3, -0.3, 0.3);
						config.size = 5;
						config.position = core::Vector2f(WIDTH / 2, HEIGHT / 2);

						pool.addParticles(1, config, core::randomIntegerInterval(250, 2000));
					}
				}
			}
		}	

		if (myWindow.isKeyDown(Key::W))
			shape.transform().move(core::Vector2f(0, -.1)*dt);
		if (myWindow.isKeyDown(Key::S))
			shape.transform().move(core::Vector2f(0, .1)*dt);
		if (myWindow.isKeyDown(Key::D))
			shape.transform().move(core::Vector2f(.1, 0)*dt);
		if (myWindow.isKeyDown(Key::A))
			shape.transform().move(core::Vector2f(-.1, 0)*dt);
		if (myWindow.isKeyDown(Key::X))
		{
			//graphics::ParticleConfig config;
			//config.makeColorRandom();
			//config.makeVelocityRandom(-0.3, 0.3, -0.3, 0.3);
			//config.size = 3;
			//config.position = core::Vector2f(WIDTH/2, HEIGHT/2);
			//
			//pool.addParticles(1, config, core::randomIntegerInterval(250,2000));
		}
			

		myWindow.clear(core::Color(0.1f,0.1f,0.1f)); // Here is where the window is cleared and we can now render to the fresh window
		
		pool.process(dt);
		pr->begin();
		pr->submit(pool);
		pr->flush();

		//shape.draw(shader);

		myWindow.display(); // Swaps the back and front buffers 
	}

	graphics::Graphics::exit();

	return 0;
}