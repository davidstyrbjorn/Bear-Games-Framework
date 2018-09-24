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

constexpr auto WIDTH = 1600;
constexpr auto HEIGHT = 900;

int main()
{
	bear::window::Window myWindow(WIDTH, HEIGHT, "Let's go");
	myWindow.setVSync(false);

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

	graphics::Framebuffer* fb1 = new graphics::Framebuffer(1600, 900);
	fb1->setShader("fbShader");
	graphics::Framebuffer* fb2 = new graphics::Framebuffer(1600, 900);
	fb2->setShader("fbShader2");

	fb2->setFramebufferRenderTarget(fb1->getFBO()); // VignetteFramebuffer will now render to the fb2 texture

	// Create the batch renderer
	graphics::BatchRenderer _renderer;
	_renderer.init();
	graphics::View view;
	
	// Create the particle renderer
	//graphics::ParticleRenderer *pr = new graphics::ParticleRenderer();
	//pr->init();
	//graphics::ParticlePool pool;

	// Create some render objects	&     textures
	ResourceManager::Instance()->CreateTexture("cat_texture", "shaders\\cat.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("dide_texture", "shaders\\dide.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("wall_up", "shaders\\wallTop.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("wall_down", "shaders\\wallBottom.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("wall_right", "shaders\\wallRight.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("wall_left", "shaders\\wallLeft.png", graphics::image_format::RGBA);


	static core::Vector2f WALL_SIZE = core::Vector2f(64, 64);
	graphics::Renderable walls[40];
	// Top
	for (int i = 0; i < 10; i++) {
		walls[i].m_Color = core::Color::White();
		walls[i].m_TextureName = "wall_up";
		walls[i].m_Transform.m_Size = WALL_SIZE;
		walls[i].m_Transform.m_Position = core::Vector2f(WALL_SIZE.x*i, 0);
	}
	// Left
	for (int i = 10; i < 20; i++) {
		walls[i].m_Color = core::Color::White();
		walls[i].m_TextureName = "wall_left";
		walls[i].m_Transform.m_Size = WALL_SIZE;
		walls[i].m_Transform.m_Position = core::Vector2f(0, WALL_SIZE.y + WALL_SIZE.y*(i-10));
	}
	// Right
	for (int i = 20; i < 30; i++) {
		walls[i].m_Color = core::Color::White();
		walls[i].m_TextureName = "wall_right";
		walls[i].m_Transform.m_Size = WALL_SIZE;
		walls[i].m_Transform.m_Position = core::Vector2f(WALL_SIZE.x*9, WALL_SIZE.y + WALL_SIZE.y*(i-20));
	}
	// Bottom
	for (int i = 30; i < 40; i++) {
		walls[i].m_Color = core::Color::White();
		walls[i].m_TextureName = "wall_down";
		walls[i].m_Transform.m_Size = WALL_SIZE;
		walls[i].m_Transform.m_Position = core::Vector2f(WALL_SIZE.x*(i-30), WALL_SIZE.y*10);
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
				fb2->windowResize(event.size.x, event.size.y);
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

		// RENDERING BEGINS HERE
		myWindow.clear(core::Color(0.05, 0.05, 0.05)); // Here is where the window is cleared and we can now render to the fresh window
		
		// The normal renderer
		_renderer.begin();

		for (graphics::Renderable& r : walls) {
			_renderer.submit(&r, 4);
		}

		// Perform the normal render flush, which will be to the currently bound framebuffer
		//fb2->bind();
		_renderer.flush(view);
		//pr->flush();
		//fb2->unbind();

		/*
		// Render the vignetteFramebuffer texture then clear it
		fb2->drawFramebufferTextureToScreen();
		fb2->clearFBO();
		
		fb1->drawFramebufferTextureToScreen();
		fb1->clearFBO();
		*/

		myWindow.display(); 

		fps++;
	}

	graphics::Graphics::exit();

	return 0;
}