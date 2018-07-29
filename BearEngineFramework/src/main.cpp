#include<iostream>

#include<graphics\graphics.h>
#include<graphics\renderers\batch_renderer.h>

#include<window/window.h>

#include<core\matrix4x4.h>
#include<core\file_utility.h>

#include<time.h>
#include<functional>

using namespace bear;

class Foo {
public:
	void bar(int a_Width, int a_Height) {
		//std::cout << a_Width << ", " << a_Height << std::endl;
	}

private:
	int x = 0;
};

void shitInTriangles(graphics::Renderable _list[])
{
	for (int i = 0; i < 60; i++) {
		int x = rand() % 720;
		int y = rand() % 540;
		int w = rand() % 100;
		int h = rand() % 100;

		float r = rand() % 255;
		float g = rand() % 255;
		float b = rand() % 255;
		core::Color c = core::Color(r / 255, g / 255, b / 255);

		_list[i].transform().m_Position = core::Vector2f(x, y);
		_list[i].transform().m_Size = core::Vector2f(w, h);
		_list[i].setColor(c);
	}
}

graphics::Shader shader;

int main()
{
	void (Foo::*funcPtr)(int, int) = &Foo::bar;
	Foo *obj = nullptr;
	(obj->*funcPtr)(100, 100);
	(obj->*funcPtr)(100, 110);
	(obj->*funcPtr)(200, 125);
	
	bear::window::Window myWindow(720, 540, "Fuck");
	
	if (!graphics::Graphics::init()) {
		printf("False returned from Graphics::init()\n");
	}
	
	//shader.compile("D:\\temp\\vert.txt", "D:\\temp\\frag_unlit.txt", false);
	//shader.enable();
	//shader.setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, 720, 540, 0, -1, 1));
	//shader.setUniformInteger("textureSampler", 0);
	//
	//graphics::Shape triangle = graphics::Shape::CreateTriangle(core::Vector2f(100, 100), core::Vector2f(100, 100), core::Color::Red());
	//graphics::Shape rectangle = graphics::Shape::CreateRectangle(core::Vector2f(250, 400), core::Vector2f(250, 60), core::Color::Blue());

	srand(time(NULL));

	graphics::BatchRenderer renderer;
	renderer.init(720, 540);

	graphics::Renderable x(graphics::renderable_type::Rectangle);
	x.transform().m_Size = core::Vector2f(150, 50);
	x.setColor(core::Color(0.2, 0.6, 0.1));

	graphics::Renderable x(graphics::renderable_type::Rectangle);
	x.transform().m_Size = core::Vector2f(150, 50);
	x.setColor(core::Color(0.2, 0.6, 0.1));

	graphics::Renderable list[60];
	shitInTriangles(list);

	while (myWindow.isOpen()) 
	{
		myWindow.clear(core::Color::Black());
		//if (myWindow.isKeyDown(Key::D))
		//	triangle.transform().move(core::Vector2f(2, 0));
		//if (myWindow.isKeyDown(Key::A))
		//	triangle.transform().move(core::Vector2f(-2, 0));
		//if (myWindow.isKeyDown(Key::S))
		//	triangle.transform().move(core::Vector2f(0, 2));
		//if (myWindow.isKeyDown(Key::W))
		//	triangle.transform().move(core::Vector2f(0, -2));
		//
		//shader.enable();
		//triangle.draw(shader);
		//rectangle.draw(shader);
				
		renderer.begin();

		//for (int i = 0; i < 60; i++) {
		//	renderer.submit(list[i]);
		//}
		renderer.submit(x);

		renderer.flush();

		myWindow.display();
	}
		
	graphics::Graphics::exit();

	return 0;
}