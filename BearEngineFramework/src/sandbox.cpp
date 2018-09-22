#include<iostream>

#include<window\window.h>
#include<sound\sound.h>
#include<core\bounding_box.h>
#include<core\vector2.h>
#include<graphics\graphics.h>

#include<graphics/renderers/batch_renderer.h>
#include<graphics/renderers/particle_renderer.h>

#include<memory/resource_manager.h>

#include<core/random.h>

using namespace bear;

constexpr auto WIDTH = 600;
constexpr auto HEIGHT = 600;

int main()
{
	bear::window::Window myWindow(WIDTH, HEIGHT, "THIS IS A WINDOW");
	myWindow.setVSync(true);

	if (!graphics::Graphics::init(WIDTH, HEIGHT))
		std::cout << "Graphics failed to init send help\n";


	// Create the framebuffer shader 
	graphics::Shader* fbShader = ResourceManager::Instance()->CreateShaderFromFile("fbShader",
		"shaders\\fb_vertex.txt", 
		"shaders\\fb_fragment.txt", 
		"");
	fbShader->enable();
	fbShader->setUniformInteger("texFramebuffer", 0);

	graphics::Shader* fbShader2 = ResourceManager::Instance()->CreateShaderFromFile("fbShader2", 
		"shaders\\fb_vertex.txt",
		"shaders\\fb_fragment2.txt",
		"");
	fbShader2->enable();
	fbShader2->setUniformInteger("texFramebuffer", 0);

	graphics::Framebuffer* fb1 = new graphics::Framebuffer(600, 600);
	fb1->setShader("fbShader");
	graphics::Framebuffer* fb2 = new graphics::Framebuffer(600, 600);
	fb2->setShader("fbShader2");

	fb2->setFramebufferRenderTarget(fb1->getFBO()); // VignetteFramebuffer will now render to the fb2 texture

	// Create the batch renderer
	graphics::BatchRenderer _renderer;
	_renderer.init();
	
	// Create the particle renderer
	graphics::ParticleRenderer *pr = new graphics::ParticleRenderer();
	pr->init();
	graphics::ParticlePool pool;

	// Create some render objects
	graphics::Renderable torch2(graphics::renderable_type::Rectangle);
	torch2.transform().m_Position = core::Vector2f(300, 300);
	torch2.transform().m_Size = core::Vector2f(30, 30);
	torch2.setColor(core::Color::Green());

	graphics::Renderable lightCube(graphics::renderable_type::Rectangle);
	lightCube.transform().m_Position = core::Vector2f(300, 300);
	lightCube.transform().m_Size = core::Vector2f(10, 10);
	lightCube.setColor(core::Color::White());
	
	graphics::Image testImage2("shaders\\big_cat_image.png", graphics::image_format::RGBA);
	graphics::Renderable cat(testImage2);
	cat.transform().m_Size.scale(0.1f);
	cat.setColor(core::Color(0.4f, 0.2f, 1.0f, 0.8f));
	
	while (myWindow.isOpen()) 
	{
		float dt = myWindow.getDeltaTime(); // Get the delta time for the last frame
		for (Event event : myWindow.getRegisteredEvents()) { // Process the events here
			if (event.type == EventType::WindowReiszed) {
				graphics::Graphics::window_resize_callback(event.size.x, event.size.y);
			}
		}	

		if (myWindow.isKeyDown(Key::UP)) {
			cat.transform().m_Size.scale(1.1f);
		}
		if (myWindow.isKeyDown(Key::DOWN)) {
			cat.transform().m_Size.scale(0.9f);
		}

		{
			//graphics::ParticleConfig config;
			//config.color = core::Color::White();
			//config.makeColorRandom();
			//config.size = core::randomIntegerInter'val(5, 50);
			//config.position = core::Vector2f(WIDTH/2,HEIGHT/2) + core::randomPointInsideCircle(200);
			////config.velocity = core::Vector2f(0, -0.1f);
			//
			//pool.addParticles(1, config, core::randomIntegerInterval(1000, 3000));
		}
		
		// RENDERING BEGINS HERE
		myWindow.clear(core::Color(0.1, 0.1, 0.1)); // Here is where the window is cleared and we can now render to the fresh window
		
		// The normal renderer
		_renderer.begin();
		_renderer.submit(torch2);
		_renderer.submit(cat);
		_renderer.submit(lightCube);

		//vignetteFramebuffer->bind();
		//_renderer.flush();
		//vignetteFramebuffer->unbind();
		//
		//vignetteFramebuffer->drawFramebufferTextureToScreen();
		//vignetteFramebuffer->clearFBO();

		// Perform the normal render
		fb2->bind();
		_renderer.flush();
		fb2->unbind();

		// Render the vignetteFramebuffer texture then clear it
		fb2->drawFramebufferTextureToScreen();
		fb2->clearFBO();
		
		fb1->drawFramebufferTextureToScreen();
		fb1->clearFBO();

		myWindow.display(); 
	}

	graphics::Graphics::exit();

	return 0;
}