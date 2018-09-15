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
	pr->init();
	pr->setUseTexture(true);
	graphics::ParticlePool pool;

	graphics::BatchRenderer _renderer;
	_renderer.init();
	
	graphics::Renderable torch("shaders\\torch.png");
	torch.transform().m_Position = core::Vector2f(0, 150);
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
					pr->setGravityAcceleration(core::Vector2f(0.001, 0));
					break;
				case Key::A:
					pr->setGravityAcceleration(core::Vector2f(-0.001, 0));
					break;
				case Key::S:
					pr->setGravityAcceleration(core::Vector2f(0, 0.001));
					break;
				case Key::W:
					pr->setGravityAcceleration(core::Vector2f(0, -0.00025));
					break;
				}
				if (event.key == Key::X) {
					pr->setUseTexture(true);
				}
				else if (event.key == Key::Z) {
					pr->setUseTexture(false);
				}
				else if (event.key == Key::C) {
					graphics::Image image("shaders\\particle.png");
					pr->setActiveTexture(image);
				}
			}
		}	

		//if (myWindow.isKeyDown(Key::X))
		{
			graphics::ParticleConfig config;
			config.color = core::Color::White();
			config.makeColorRandom();
			config.size = core::randomIntegerInterval(5, 25);
			config.position = core::Vector2f(WIDTH/2,HEIGHT/2) + core::randomPointInsideCircle(25);
			config.velocity = core::Vector2f(0, -0.1f);

			pool.addParticles(1, config, core::randomIntegerInterval(250, 2000));
		}
			
		// RENDERING BEGINS HERE
		myWindow.clear(core::Color(0.09f,0.09f,0.12f)); // Here is where the window is cleared and we can now render to the fresh window
		
		// The normal renderer
		_renderer.begin();
		//_renderer.submit(torch);
		_renderer.flush();

		// Particles
		pool.process(dt);
		pr->begin();
		pr->submit(pool);
		pr->flush();
		
		myWindow.display(); 
	}

	graphics::Graphics::exit();

	return 0;
}