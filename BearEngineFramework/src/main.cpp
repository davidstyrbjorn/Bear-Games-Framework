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
	bear::window::Window myWindow(WIDTH, HEIGHT, "THIS IS A WINDOW");

	if (!graphics::Graphics::init(WIDTH, HEIGHT))
		std::cout << "Graphics failed to init send help\n";

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
						config.size = core::randomIntegerInterval(1,5);
						config.position = core::Vector2f(WIDTH / 2, HEIGHT / 2);

						pool.addParticles(1, config, core::randomIntegerInterval(250, 2000));
					}
				}
			}
		}	

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
			
		// RENDERING BEGINS HERE
		myWindow.clear(core::Color(0.05f,0.05f,0.05f)); // Here is where the window is cleared and we can now render to the fresh window
		
		pool.process(dt);
		pr->begin();
		pr->submit(pool);
		pr->flush();

		myWindow.display(); 
	}

	graphics::Graphics::exit();

	return 0;
}