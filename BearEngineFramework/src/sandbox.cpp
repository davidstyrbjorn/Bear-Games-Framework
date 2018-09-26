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

#include<graphics/animated_sprite.h>

using namespace bear;

constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 640;

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
	ResourceManager::Instance()->CreateTexture("torch", "shaders\\torch.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("cat", "shaders\\cat.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("wall_up", "shaders\\wallTop.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("wall_down", "shaders\\wallBottom.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("wall_right", "shaders\\wallRight.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("wall_left", "shaders\\wallLeft.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("top_left", "shaders\\topLeftCorner.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("top_right", "shaders\\topRightCorner.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("bottom_left", "shaders\\bottomLeftCorner.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("bottom_right", "shaders\\bottomRightCorner.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("man1", "shaders\\Hat_man1.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("man2", "shaders\\Hat_man2.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("man3", "shaders\\Hat_man3.png", graphics::image_format::RGBA);
	ResourceManager::Instance()->CreateTexture("man4", "shaders\\Hat_man4.png", graphics::image_format::RGBA);

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

	static core::Vector2f WALL_SIZE = core::Vector2f(64, 64);
	graphics::Renderable walls[20];
	// Top
	for (int i = 0; i < 5; i++) {
		walls[i].m_Color = core::Color::White();
		walls[i].m_TextureName = "wall_up";
		walls[i].m_Transform.m_Size = WALL_SIZE;
		walls[i].m_Transform.m_Position = core::Vector2f(WALL_SIZE.x*i, 0);
		walls[i].m_VertexCount = 4;
		if (i == 0)
			walls[i].m_TextureName = "top_left";
		if (i == 4)
			walls[i].m_TextureName = "top_right";
	}
	// Left
	for (int i = 5; i < 10; i++) {
		walls[i].m_Color = core::Color::White();
		walls[i].m_TextureName = "wall_left";
		walls[i].m_Transform.m_Size = WALL_SIZE;
		walls[i].m_Transform.m_Position = core::Vector2f(0, WALL_SIZE.y + WALL_SIZE.y*(i-5));
		walls[i].m_VertexCount = 4;
		if (i == 9)
			walls[i].m_TextureName = "bottom_left";
	}
	// Right
	for (int i = 10; i < 15; i++) {
		walls[i].m_Color = core::Color::White();
		walls[i].m_TextureName = "wall_right";
		walls[i].m_Transform.m_Size = WALL_SIZE;
		walls[i].m_Transform.m_Position = core::Vector2f(WALL_SIZE.x*4, WALL_SIZE.y + WALL_SIZE.y*(i-10));
		walls[i].m_VertexCount = 4;
		if (i == 14)
			walls[i].m_TextureName = "bottom_right";
	}
	// Bottom
	for (int i = 15; i < 20; i++) {
		walls[i].m_Color = core::Color::White();
		walls[i].m_TextureName = "wall_down";
		walls[i].m_Transform.m_Size = WALL_SIZE;
		walls[i].m_Transform.m_Position = core::Vector2f(WALL_SIZE.x*(i-15), WALL_SIZE.y*5);
		walls[i].m_VertexCount = 4;
	}

	graphics::Renderable rectangle;
	rectangle.m_Transform.m_Size = core::Vector2f(150, 75);
	rectangle.m_Color = core::Color::Red();
	rectangle.m_Transform.m_Position = core::Vector2f(200, 200);
	rectangle.m_VertexCount = 4;

	graphics::Renderable cat1;
	cat1.setTextureNameWData("cat");
	cat1.m_Transform.m_Size.scale(0.3f);
	cat1.m_Layer = 10;

	graphics::Renderable torch1;
	torch1.setTextureNameWData("torch");
	torch1.m_Transform.m_Position = core::Vector2f(50, 10);
	torch1.m_Layer = 1;

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
			if (myWindow.isKeyDown(Key::X)) {
				anim.play();
			}
			if (myWindow.isKeyDown(Key::Z)) {
				anim.stop();
				anim.reset();
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

		anim.update(dt);
		animation_sprite.m_TextureName = anim.m_CurrentTextureName;

		// =================================== RENDERING BEGINS HERE ===========================================0
		myWindow.clear(core::Color(1, 1, 1)); // Here is where the window is cleared and we can now render to the fresh window

		// The normal renderer
		_renderer.begin();

		//for (graphics::Renderable& r : walls) {
		//	_renderer.submit(&r);
		//}
		//_renderer.submit(&rectangle);
		//_renderer.submit(&cat1);
		//_renderer.submit(&torch1);
		_renderer.submit(&animation_sprite);

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