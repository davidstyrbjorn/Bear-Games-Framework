#include"../include/graphics/renderers/slow_renderer.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include"../include/graphics/vertex.h"
#include"../include/graphics/graphics.h"

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
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glGenBuffers(1, &VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	// Vertex attrib pointers
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(core::Vector2f)));								
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(core::Vector2f) + sizeof(core::Color)));
}

void SlowRenderer::begin() {

}

void SlowRenderer::submit(Renderable &renderable) {
	render_poll.emplace_back(renderable);
}

void SlowRenderer::flush() {
	
	// Bind shit
	graphics::Graphics::s_DefaultShader->enable(); // Bind and enable shaders & buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	// Go through each renderable in the list
	while (!render_poll.empty()) {
		Renderable& r = render_poll.back();

		// Update the VBO data with the new "r" data
		Vertex data[] = {
			{ r.m_Transform.m_Position, r.m_Color, core::Vector2f(-1.0f,-1.0f), -1.0f },
			{ r.m_Transform.m_Position + core::Vector2f(r.m_Transform.m_Size.x, 0), r.m_Color, core::Vector2f(-1.0f, -1.0f), -1.0f },
			{ r.m_Transform.m_Position + r.m_Transform.m_Size, r.m_Color, core::Vector2f(-1.0f, -1.0f), -1.0f }
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_DYNAMIC_DRAW);

		// gl draw call
		glDrawArrays(GL_TRIANGLES, 0, 3);

		render_poll.pop_back();
	}

	// Reset buffer data
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

	// Unbind shit
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	graphics::Graphics::s_DefaultShader->disable();
}