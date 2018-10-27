#include"../include/graphics/renderers/slow_renderer.h"

#define GLEW_STATIC
#include<GL/glew.h>

using namespace bear::graphics;

SlowRenderer::SlowRenderer() {
	// Pass
}

SlowRenderer::~SlowRenderer() {
	// Delete shit
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteTextures(1, &VAO);
}

void SlowRenderer::init() {

	// Create buffers and shit

	// VAO
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glCreateBuffers(1, &VBO);


}

void SlowRenderer::begin() {

}

void SlowRenderer::submit(Renderable &renderable) {
	render_poll.emplace_back(renderable);
}

void SlowRenderer::flush() {
	// Go through each renderable in the polled 
	int i = 0;
	while (!render_poll.empty()) {
		Renderable& r = render_poll.back();

		// Do the render here
		std::cout << "We're supposed to render something" << std::endl;
		i++;

		render_poll.pop_back();
	}

	std::cout << i << std::endl;
}