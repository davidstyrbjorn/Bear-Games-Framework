#include"../include/graphics/renderers/renderer.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include"../include/graphics/vertex.h"
#include"../include/graphics/graphics.h"
#include"../include/memory/resource_manager.h"

#include<algorithm>

using namespace bear::graphics;

View Renderer::unit_view = View();

Renderer::Renderer() {
	target_framebuffer = nullptr; // On start
}

Renderer::~Renderer() {
	// Delete shit
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
}

void Renderer::init() {

	// Create buffers and shit

	// VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// IBO
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	unsigned int _indices[] = { 0, 1, 2, 0, 2, 3 };
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	// Vertex attrib pointers
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(core::Vector2f)));								
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(core::Vector2f) + sizeof(core::Color)));
}

void Renderer::begin() {

}

void Renderer::submit(Renderable &renderable) {
	render_poll.emplace_back(renderable);
}				

void Renderer::flush(View& view) {
	
	// Sort the list
	std::sort(render_poll.begin(), render_poll.end(),
		[](const Renderable& a, const Renderable& b) -> bool { return a.m_Layer > b.m_Layer; } // Sorting with lambda
	);

	if (target_framebuffer != nullptr) {
		// Make sure we're drawing to this if it's set to something other than nullptr
		target_framebuffer->bind();
	}

	graphics::Graphics::s_DefaultShader->enable(); // Bind and enable shaders & buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	
	graphics::Graphics::s_DefaultShader->setUniformInteger("texture_sampler", 0);
	graphics::Graphics::s_DefaultShader->setUniformMatrix4x4("view_matrix", view.getViewMatrix());

	// Go through each renderable in the list
	while (!render_poll.empty()) {
		Renderable& r = render_poll.back();

		// Get indices count
		int indicies = get_indicies_count(r.m_VertexCount);

		// Update the VBO data with the new "r" data
		if (r.m_TextureName == "") {
			Vertex data[] = {
				{ r.m_Transform.m_Position, r.m_Color, core::Vector2f(-1.0f,-1.0f), -1.0f },
				{ r.m_Transform.m_Position + core::Vector2f(0, r.m_Transform.m_Size.y), r.m_Color, core::Vector2f(-1.0f, -1.0f), -1.0f },
				{ r.m_Transform.m_Position + r.m_Transform.m_Size, r.m_Color, core::Vector2f(-1.0f, -1.0f), -1.0f },
				{ r.m_Transform.m_Position + core::Vector2f(r.m_Transform.m_Size.x, 0), r.m_Color, core::Vector2f(-1.0f, -1.0f), -1.0f }
			};
			glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_DYNAMIC_DRAW);
		}
		else {
			Vertex data[] = {
				{ r.m_Transform.m_Position,                                             r.m_Color, core::Vector2f(0.0f,0.0f),  -1.0f },
				{ r.m_Transform.m_Position + core::Vector2f(0, r.m_Transform.m_Size.y), r.m_Color, core::Vector2f(0.0f, 1.0f), -1.0f },
				{ r.m_Transform.m_Position + r.m_Transform.m_Size,                      r.m_Color, core::Vector2f(1.0f, 1.0f), -1.0f },
				{ r.m_Transform.m_Position + core::Vector2f(r.m_Transform.m_Size.x, 0), r.m_Color, core::Vector2f(1.0f, 0),    -1.0f }
			};
			glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_DYNAMIC_DRAW);

			// Texture bind 
			glActiveTexture(GL_TEXTURE0); // Specify texture unit, we're only using one
			bear::ResourceManager::Instance()->GetTexture(r.m_TextureName)->bind();
		}

		// gl draw call
		glDrawElements(GL_TRIANGLES, indicies, GL_UNSIGNED_INT, nullptr);

		render_poll.pop_back();
	}

	// Reset buffer data
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

	// Unbind shit
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	graphics::Graphics::s_DefaultShader->disable();

	if (target_framebuffer != nullptr) {
		// Unbind framebuffer and draw its texture if there is any
		target_framebuffer->unbind();
		target_framebuffer->drawFramebufferTextureToScreen();
		target_framebuffer->clearFBO();
	}
}

void Renderer::setFramebuffer(Framebuffer* a_Framebuffer) 
{
	target_framebuffer = a_Framebuffer;
}

Framebuffer* Renderer::getFramebuffer() 
{
	return target_framebuffer;
}

int bear::graphics::Renderer::get_indicies_count(int vertex_count)
{
	return vertex_count == 3 ? 3 : 6;
}
