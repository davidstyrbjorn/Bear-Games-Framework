#pragma once

#include<deque>

#include"../renderable.h"

namespace bear { namespace graphics {

class SlowRenderer {

private:
	unsigned int VBO; // Vertex buffer object
	unsigned int VAO; // Vertex array object
	unsigned int TBO; // Texture buffer object
	std::deque<Renderable> render_poll;

public:
	/* Constructor */
	SlowRenderer();
	/* Destructor */
	~SlowRenderer();

	/* Should initalize the opengl buffers */
	void init();

	/* Rendering routines */
	void begin();
	void submit(Renderable& renderable);
	void flush();

};


	
}}
