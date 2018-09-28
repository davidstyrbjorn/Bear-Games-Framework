#include<iostream>

#include<window\window.h>
#include<sound\sound.h>
#include<core\bounding_box.h>
#include<core\vector2.h>
#include<graphics\graphics.h>

#include<graphics/renderers/batch_renderer.h>
#include<graphics/renderers/particle_source.h>

#include<memory/resource_manager.h>

#include<core/random.h>

#include<graphics/animated_sprite.h>

//#include<SDL_mixer.h>

using namespace bear;

constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 640;

#define CREATE_TEXTURE(name, path, format) bear::ResourceManager::Instance()->CreateTexture(name, path, format)

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

	// Create the framebuffer
	graphics::Framebuffer* fb1 = new graphics::Framebuffer(WIDTH, HEIGHT);
	fb1->setShader("fbShader");

	// Create the batch renderer
	graphics::BatchRenderer _renderer;
	_renderer.init();
	graphics::View view;
	
	// Create the particle renderer
	graphics::ParticleSource pr;
	pr.init();
	graphics::ParticleSource pr2;
	pr2.init();
	graphics::ParticlePool pool;
	graphics::ParticlePool pool2;

	// Create some render objects	&     textures

	CREATE_TEXTURE("floor", "shaders\\floor.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("floor1", "shaders\\floor1.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("floor2", "shaders\\floor2.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("floor3", "shaders\\floor3.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("floor4", "shaders\\floor4.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("placeholder", "shaders\\placeholder.png", graphics::image_format::RGBA);

	CREATE_TEXTURE("wall_up", "shaders\\wallTop.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("wall_down", "shaders\\wallBottom.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("wall_right", "shaders\\wallRight.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("wall_left", "shaders\\wallLeft.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("top_left", "shaders\\topLeftCorner.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("top_right", "shaders\\topRightCorner.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("bottom_left", "shaders\\bottomLeftCorner.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("bottom_right", "shaders\\bottomRightCorner.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("fire", "shaders\\fire.png", graphics::image_format::RGBA);

	// Animation object creation example
	/*
	std::vector<graphics::AnimatedKeyframe> keyframes = { 
		{ "wall_up" }, 
		{ "wall_down" }, 
		{ "wall_left" },
		{ "wall_right" },
		{ "top_right" },
		{ "top_left" },
		{ "bottom_left" },
		{ "bottom_right" }
	};

	graphics::AnimatedSprite anim;
	anim.m_Keyframes = keyframes;
	anim.m_TickBreak = 100;
	anim.m_IsLooping = true;

	graphics::Renderable animation_sprite;
	animation_sprite.m_TextureName = "wall_up";
	animation_sprite.m_Transform.m_Size = core::Vector2f(100, 100);
	animation_sprite.m_Transform.m_Position = core::Vector2f(110, 110);
	*/

	static core::Vector2f WALL_SIZE = core::Vector2f(64, 64);
	unsigned int WIDTH = 12;
	unsigned int HEIGHT = 12;
	std::vector<graphics::Renderable> walls;
	for (int x = 0; x <= WIDTH; x++) {
		for (int y = 0; y <= HEIGHT; y++) {
			if (x == 0 || x == WIDTH || y == 0 || y == HEIGHT) {
				walls.push_back(graphics::Renderable());
				walls.back().m_Transform.m_Size = WALL_SIZE;
				walls.back().m_Transform.m_Position = core::Vector2f(x*WALL_SIZE.x, y*WALL_SIZE.y);
				if (x == 0 && y == 0) {
					walls.back().m_TextureName = "top_left";
					walls.back().m_Layer = 2;
				}
				else if (x == WIDTH && y == 0) {
					walls.back().m_TextureName = "top_right";
					walls.back().m_Layer = 2;
				}
				else if (x == 0 && y == HEIGHT) {
					walls.back().m_TextureName = "bottom_left";
					walls.back().m_Layer = 2;
				}
				else if (x == WIDTH && y == HEIGHT) {
					walls.back().m_TextureName = "bottom_right";
					walls.back().m_Layer = 2;
				}
				else if (x == 0) {
					walls.back().m_TextureName = "wall_left";
				}
				else if (x == WIDTH) {
					walls.back().m_TextureName = "wall_right";
				}
				else if (y == 0) {
					walls.back().m_TextureName = "wall_up";
				}
				else if (y == HEIGHT) {
					walls.back().m_TextureName = "wall_down";
				}
			}
			else {
				walls.push_back(graphics::Renderable());
				walls.back().m_Transform.m_Size = WALL_SIZE;
				walls.back().m_Transform.m_Position = core::Vector2f(x*WALL_SIZE.x, y*WALL_SIZE.y);
				walls.back().m_TextureName = "placeholder";
			}
		}
	}

	core::Clock fpsTimer;
	unsigned int fps = 0;
	fpsTimer.reset();
	fpsTimer.start();

	// Creat an ASS load of quads
	static int size = 32;
	std::vector<graphics::Renderable*> reestList;
	for (int x = 0; x < 64; x++) {
		for (int y = 0; y < 64; y++) {
			reestList.push_back(new graphics::Renderable());
			reestList.back()->m_Color = core::Color(core::randomFloatZeroToOne(), core::randomFloatZeroToOne(), core::randomFloatZeroToOne());
			reestList.back()->m_Transform.m_Size = core::Vector2f(size, size);
			reestList.back()->m_Transform.m_Position = core::Vector2f(x*size, y*size);
			reestList.back()->m_TextureName = "fire";
		}
	}

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
		if (myWindow.isKeyDown(Key::F)) {
			graphics::ParticleConfig config;
			config.position = core::Vector2f(400, 400) + core::randomPointInsideCircle(150);
			config.makeSizeRandom(5, 50);
			config.makeColorRandom();
			pool.addParticles(1, config, 300);
		}

		// =================================== RENDERING BEGINS HERE ===========================================0
		myWindow.clear(core::Color(0.05, 0.05, 0.05)); // Here is where the window is cleared and we can now render to the fresh window

		pool.process(dt);

		// Rendering begin
		_renderer.begin();
		pr.begin();

		// Rendering submit
		//for (graphics::Renderable& r : walls) {
		//	_renderer.submit(&r);
		//}
		pr.submit(pool);
		//man.m_TextureName = "fire";
		//_renderer.submit(&man);

		// Render an ASS load of quads
		//for (graphics::Renderable* r : reestList) {
		//	_renderer.submit(r);
		//}


		// Rendering flush
		//fb1->bind();
		
		pr.flush(view);
		_renderer.flush(view);

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