#include<iostream>

#include<window\window.h>
#include<sound\sound.h>
#include<core\bounding_box.h>
#include<core\vector2.h>
#include<graphics\graphics.h>

#include<graphics/renderers/batch_renderer.h>
#include<graphics/renderers/particle_source.h>
#include<graphics/renderers/slow_renderer.h>

#include<memory/resource_manager.h>

#include<core/random.h>

#include<graphics/animated_sprite.h>

using namespace bear;

constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 640;

#define CREATE_TEXTURE(name, path, format) bear::ResourceManager::Instance()->CreateTexture(name, path, format)

int main()
{
	bear::window::Window myWindow(WIDTH, HEIGHT, "Let's go");
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

	// Create the framebuffer
	graphics::Framebuffer* fb1 = new graphics::Framebuffer(WIDTH, HEIGHT);
	fb1->setShader("fbShader");

	// Create the batch renderer
	graphics::BatchRenderer _renderer;
	_renderer.init();
	graphics::View view;

	graphics::SlowRenderer slow_fuck;
	slow_fuck.init();
	
	// Create the particle renderer
	graphics::ParticleSource pr;
	pr.init();

	std::vector<graphics::Renderable> renderable_list;
	const int SIZE = 128;
	for (int i = 1; i <= 16; i++) {
		CREATE_TEXTURE(std::to_string(i), "shaders\\" + std::to_string(i) + ".png", graphics::image_format::RGBA);
		renderable_list.push_back(graphics::Renderable());
		renderable_list.back().setTextureNameWData(std::to_string(i));
		renderable_list.back().m_Transform.m_Size = core::Vector2f(SIZE, SIZE);
		renderable_list.back().m_Transform.m_Position.x = i * SIZE;
	}

	core::Clock fpsTimer;
	unsigned int fps = 0;
	fpsTimer.reset();
	fpsTimer.start();

	while (myWindow.isOpen()) 
	{
		if (fpsTimer.getTicks() >= 1000) {
			fpsTimer.reset();
			std::cout << "Measured FPS: " << fps << std::endl;
			fps = 0;
		}

		float dt = myWindow.getDeltaTime(); // Get the delta time for the last frame
		for (Event event : myWindow.getRegisteredEvents()) { // Process the events here
			if (event.type == EventType::WindowReiszed) {
				graphics::Graphics::window_resize_callback(event.size.x, event.size.y);
				fb1->windowResize(event.size.x, event.size.y);
			}
		}	

		if (myWindow.isKeyDown(Key::D))				   
			view.translate(core::Vector2f(-1 * dt, 0));
		if (myWindow.isKeyDown(Key::A))
			view.translate(core::Vector2f(1 * dt, 0));
		if (myWindow.isKeyDown(Key::S))
			view.translate(core::Vector2f(0, -1 * dt));
		if (myWindow.isKeyDown(Key::W))
			view.translate(core::Vector2f(0, 1 * dt));

		//pr.update(dt);

		// =================================== RENDERING BEGINS HERE ===========================================0
		myWindow.clear(core::Color(0.2, 0.05, 0.05)); // Here is where the window is cleared and we can now render to the fresh window

		// Rendering begin
		_renderer.begin();

		// Rendering submit
		//for (graphics::Renderable& r : walls) {
		//	_renderer.submit(&r);
		//}
		//man.m_TextureName = "fire";
		//_renderer.submit(&man);

		// Render an ASS load of quads
		//for (graphics::Renderable* r : reestList) {
		//	//r->m_Transform.m_Position = r->m_Transform.m_Position + core::randomPointInsideCircle(5);
		//	_renderer.submit(r);
		//}


		// Slow rendering BITCH
		slow_fuck.begin();

		slow_fuck.submit(renderable_list.at(0));	
		slow_fuck.submit(renderable_list.at(1));
		slow_fuck.submit(renderable_list.at(2));

		slow_fuck.flush();

		// Rendering flush
		//fb1->bind();
		
		//pr.render(view);
		//_renderer.flush(view);

		//fb1->unbind();
		
		// Render the vignetteFramebuffer texture then clear it		
		//fb1->drawFramebufferTextureToScreen();
		//fb1->clearFBO();

		myWindow.display(); 

		fps++;
	}

	graphics::Graphics::exit();

	return 0;
}