#include<iostream>

#include<window\window.h>
#include<core\bounding_box.h>
#include<core\vector2.h>
#include<graphics\graphics.h>

#include<graphics/renderers/particle_source.h>
#include<graphics/renderers/renderer.h>

#include<memory/resource_manager.h>

#include<core/random.h>

#include<graphics/animated_sprite.h>

#include<math.h>

using namespace bear;

constexpr auto WIDTH = 1920;
constexpr auto HEIGHT = 1080;

#define CREATE_TEXTURE(name, path, format) bear::ResourceManager::Instance()->CreateTexture(name, path, format)

int main()
{
	bear::window::Window myWindow(WIDTH, HEIGHT, "Let's go", true);
	myWindow.setVSync(true);

	if (!graphics::Graphics::init(WIDTH, HEIGHT))
		std::cout << "Graphics failed to init send help\n";

	// Create the framebuffer shader 
	graphics::Shader* fbShader = ResourceManager::Instance()->CreateShaderFromFile("fbShader",
		"shaders\\fb_vertex.txt", 
		"shaders\\fb_fragment2.txt", 
		"");
	fbShader->enable();
	fbShader->setUniformInteger("texFramebuffer", 0);

	// Create the framebuffer
	graphics::Framebuffer* fb1 = new graphics::Framebuffer(WIDTH, HEIGHT);
	fb1->setShader("fbShader");

	// Create the batch renderer
	//graphics::BatchRenderer _renderer;
	//_renderer.init();
	graphics::View view;
	view.setPosition({ 500,500 });	
	core::Vector2f _x = { -500,-500 };

	graphics::Renderer slow_fuck;
	slow_fuck.init();
	//slow_fuck.setFramebuffer(fb1);
	
	// Create the particle renderer
	//graphics::ParticleSource pr;
	//pr.init();

	CREATE_TEXTURE("fire", "shaders\\fire.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("cat", "shaders\\cat.png", graphics::image_format::RGBA);
	CREATE_TEXTURE("floor", "shaders\\floor.png", graphics::image_format::RGBA);

	std::vector<graphics::Renderable> renderable_list;
	const int SIZE = 32;
	for (int i = 0; i <= 24; i++) {
		for (int j = 0; j <= 24; j++) {
			renderable_list.push_back(graphics::Renderable());
			renderable_list.back().m_TextureName = "floor";
			renderable_list.back().m_Transform.m_Size = core::Vector2f(SIZE, SIZE);
			renderable_list.back().m_Transform.m_Position = core::Vector2f(i*SIZE, j*SIZE);
		}
	}

	graphics::Renderable renderable;
	renderable.m_Layer = 10;
	renderable.setTextureNameWData("fire");

	graphics::Renderable cat;
	cat.m_Layer = 11;
	cat.setTextureNameWData("cat");

	core::Clock fpsTimer;
	unsigned int fps = 0;
	fpsTimer.reset();
	fpsTimer.start();

	int counter = 0;

	while (myWindow.isOpen()) 
	{
		counter++;
		if (fpsTimer.getTicks() >= 1000) {
			fpsTimer.reset();
			std::cout << "Measured FPS: " << fps << std::endl;
			fps = 0;
		}

		float dt = myWindow.getDeltaTime(); // Get the delta time for the last frame
		for (Event event : myWindow.getRegisteredEvents()) { // Process the events here
			if (event.type == EventType::WindowReiszed) {
				graphics::Graphics::window_resize_callback(event.size.x, event.size.y);
				//graphics::Graphics::set_uniform_size(event.size.x, event.size.y);
				float temp = (WIDTH / event.size.x);
				graphics::Graphics::set_zoom(temp);
			}
		}	

		if (myWindow.isKeyDown(Key::D))
			//_x.x -= 1 * dt;
			view.translate(core::Vector2f(-1 * dt, 0));
		if (myWindow.isKeyDown(Key::A))
			//_x.x += 1 * dt;			
			view.translate(core::Vector2f(1 * dt, 0));
		if (myWindow.isKeyDown(Key::S))
			//_x.y += 1 * dt;			
			view.translate(core::Vector2f(0, -1 * dt));
		if (myWindow.isKeyDown(Key::W))
			//_x.y -= 1 * dt;
			view.translate(core::Vector2f(0, 1 * dt));
		if (myWindow.isKeyDown(Key::X))
			graphics::Graphics::set_zoom(0.5f);
		if (myWindow.isKeyDown(Key::Z))
			graphics::Graphics::set_zoom(1.0f);
		if (myWindow.isKeyDown(Key::C))
			graphics::Graphics::set_zoom(1.5f);

		counter += 1;
		float mouse_x = myWindow.getMousePosition().x;
		mouse_x /= WIDTH;
		fbShader->setUniformFloat("vx_offset", mouse_x);

		//pr.update(dt);

		// =================================== RENDERING BEGINS HERE ===========================================0
		myWindow.clear(); // Here is where the window is cleared and we can now render to the fresh window

		// Rendering begin
		//_renderer.begin();

		core::Vector2f pos = view.getPosition();
		pos.lerp(_x, 0.000005*dt);
		pos.x = round(pos.x);
		pos.y = round(pos.y);
		view.setPosition(pos);

		// Slow rendering BITCH
		slow_fuck.begin();
		
		//slow_fuck.submit(renderable);
		//slow_fuck.submit(cat);
		for (graphics::Renderable &r : renderable_list) {
			slow_fuck.submit(r);
		}

		slow_fuck.flush(view);

		myWindow.display(); 

		fps++;
	}

	graphics::Graphics::exit();

	return 0;
}