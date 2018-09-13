#include<iostream>

#include<window\window.h>
#include<sound\sound.h>
#include<core\bounding_box.h>
#include<core\vector2.h>
#include<graphics\graphics.h>

#include<graphics/renderers/batch_renderer.h>
#include<graphics/renderers/particle_renderer.h>

#include<core/random.h>

using namespace bear;

constexpr auto WIDTH = 720;
constexpr auto HEIGHT = 510;

int main()
{
	bear::window::Window myWindow(WIDTH, HEIGHT, "THIS IS A WINDOW");
	myWindow.setVSync(true);

	if (!graphics::Graphics::init(WIDTH, HEIGHT))
		std::cout << "Graphics failed to init send help\n";

	graphics::ParticleRenderer *pr = new graphics::ParticleRenderer();
	//pr->setGravityAcceleration(core::Vector2f(0, -0.001));
	pr->init();
	graphics::ParticlePool pool;

	graphics::BatchRenderer _renderer;
	_renderer.init();
	
	//graphics::Renderable torch("C:\\Users\\David\\Desktop\\Images\\1890_art1.jpg");
	//torch.transform().m_Size = core::Vector2f(4812/10, 2417/10);
	
	while (myWindow.isOpen()) 
	{
		float dt = myWindow.getDeltaTime(); // Get the delta time for the last frame
		for (Event event : myWindow.getRegisteredEvents()) { // Process the events here
			if (event.type == EventType::WindowReiszed) {
				graphics::Graphics::window_resize_callback(event.size.x, event.size.y);
			}
			if (event.type == EventType::KeyPressed) {
				switch (event.key) {
				case Key::D:
					pr->setGravityAcceleration(core::Vector2f(1, 0));
					break;
				case Key::A:
					pr->setGravityAcceleration(core::Vector2f(-0.001, 0));
					break;
				case Key::S:
					pr->setGravityAcceleration(core::Vector2f(0, 0.001));
					break;
				case Key::W:
					pr->setGravityAcceleration(core::Vector2f(0, -0.001));
					break;
				}
			}
		}	

		//if (myWindow.isKeyDown(Key::X))
		{
			graphics::ParticleConfig config;
			config.color = core::Color::White();
			config.makeColorRandom();
			config.makeVelocityRandom(0, 0.3, 0, 0);
			config.size = core::randomIntegerInterval(5, 25);
			//config.position = core::Vector2f(WIDTH / 2, HEIGHT / 2);
			config.position = core::Vector2f(0,(HEIGHT/2)) + core::randomPointInsideCircle(60);

			pool.addParticles(1, config, core::randomIntegerInterval(250, 2000));
		}
			
		// RENDERING BEGINS HERE
		myWindow.clear(core::Color(0.09f,0.09f,0.12f)); // Here is where the window is cleared and we can now render to the fresh window
		
		// Particles
		pool.process(dt);
		pr->begin();
		pr->submit(pool);
		pr->flush();

		// The normal renderer
		_renderer.begin();
		//_renderer.submit(torch);
		_renderer.flush();

		myWindow.display(); 
	}

	graphics::Graphics::exit();

	return 0;
}