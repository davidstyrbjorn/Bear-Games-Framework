#include"../include/graphics/renderers/batch_renderer.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include"../include/graphics/shader.h"
#include"../include/graphics/renderable.h"
#include"../include/graphics/view.h"
#include"../include/graphics/graphics.h"
#include"../include/core/matrix4x4.h"
#include"../include/graphics/vertex.h"

#include"../include/memory/resource_manager.h"

#include<vector>
#include<iostream>
#include<cstdio>

using namespace bear::graphics;

View& BatchRenderer::defaultView = View();

bear::graphics::BatchRenderer::BatchRenderer()
{
	// Do nothing
}

bear::graphics::BatchRenderer::~BatchRenderer()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete m_UnlitBatch;

	glDeleteVertexArrays(1, &_textured_buffers.VAO);
	glDeleteBuffers(1, &_textured_buffers.VBO);
	glDeleteBuffers(1, &_textured_buffers.IBO);
}

void bear::graphics::BatchRenderer::init()
{
	VertexAttribute temp[] = {
		{ default_shader_pos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0 },
		{ default_shader_col_location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(core::Vector2f)) },
		{ default_shader_uv_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(core::Vector2f) + sizeof(core::Color)) },
	};
	
	m_UnlitBatch = new UnlitBatcher(UNLIT_BUFFER_SIZE, temp, 3);

	Graphics::s_DefaultShader->enable();
	Graphics::s_DefaultShader->setUniformInteger("texture_sampler", 0);

	glGenBuffers(1, &_textured_buffers.VBO);
	glGenBuffers(1, &_textured_buffers.IBO);
	glGenVertexArrays(1, &_textured_buffers.VAO);

	glBindVertexArray(_textured_buffers.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _textured_buffers.VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), nullptr, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0); // position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(1); // color		
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(core::Vector2f));
	glEnableVertexAttribArray(2); // uv							   
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color)));

	glActiveTexture(GL_TEXTURE0);

	unsigned int indicies[] = { 0, 1, 2, 0, 2, 3 };
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _textured_buffers.IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void bear::graphics::BatchRenderer::begin()
{
	m_UnlitVertCount = 0; 
	m_UnlitBatch->clearBatch();
}

void bear::graphics::BatchRenderer::submit(Renderable * a_Renderable, unsigned int a_VertCount)
{
	if (a_Renderable->m_TextureName.empty()) {
		submit_unlit(a_Renderable, a_VertCount);
	}
	else {
		submit_texture(a_Renderable);
	}
}

void bear::graphics::BatchRenderer::flush(View& a_View)
{
	// ================== Unlit flush
	Graphics::s_DefaultShader->enable();
	Graphics::s_DefaultShader->setUniformMatrix4x4("view_matrix", a_View.getViewMatrix());
	Graphics::s_DefaultShader->setUniformInteger("texture_mode", 0);
	
	m_UnlitBatch->bindBatch();
	glDrawArrays(GL_TRIANGLES, 0, m_UnlitVertCount);
	
	// ================== Texture flush
	Graphics::s_DefaultShader->setUniformInteger("texture_mode", 1);
	glBindVertexArray(_textured_buffers.VAO);
	while (!_textured_buffers.m_TextureBatch.empty()) 
	{
		graphics::Renderable* renderable = _textured_buffers.m_TextureBatch.back();
		core::Vector2f pos = renderable->m_Transform.m_Position;
		core::Vector2f size = renderable->m_Transform.m_Size;
		core::Color col = renderable->m_Color;
		unsigned int TBO = ResourceManager::Instance()->GetTexture(renderable->m_TextureName)->getTextureID();
	
		// Bind
		glBindTexture(GL_TEXTURE_2D, TBO);
		glBindBuffer(GL_ARRAY_BUFFER, _textured_buffers.VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _textured_buffers.IBO);
	
		// Update texture vertex buffer data with renderable data
		Vertex vertData[] = {
			{ pos, col, core::Vector2f(0, 0) },
			{ core::Vector2f(pos.x, pos.y + size.y), col, core::Vector2f(0, 1.0f) },
			{ pos+size, col, core::Vector2f(1.0f, 1.0f) },
			{ core::Vector2f(pos.x + size.x, pos.y), col, core::Vector2f(1.0f, 0) }
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertData), vertData, GL_STATIC_DRAW);
	
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
						
		//std::remove_reference
		_textured_buffers.m_TextureBatch.pop_back();
	}
	
	Graphics::s_DefaultShader->disable();
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void bear::graphics::BatchRenderer::submit_unlit(Renderable * a_UnlitRenderable, unsigned int a_VertCount)
{
	core::Vector2f pos = a_UnlitRenderable->m_Transform.m_Position;
	core::Vector2f size = a_UnlitRenderable->m_Transform.m_Size;
	core::Color col = a_UnlitRenderable->m_Color;
	core::Vector2f uv = core::Vector2f(0, 0);

	std::vector<Vertex> vertList;
	if (a_VertCount == 3) {
		vertList.push_back(Vertex{ pos, col,  uv, });
		vertList.push_back(Vertex{ core::Vector2f(pos.x, pos.y + size.y), col, uv, });
		vertList.push_back(Vertex{ pos + size, col, uv, });
	}
	else {
		// No indices so we're doing 2 triangles
		vertList.push_back({ pos, col,  uv, });
		vertList.push_back({ core::Vector2f(pos.x, pos.y + size.y), col, uv, });
		vertList.push_back({ pos + size, col, uv, });

		vertList.push_back({ pos, col, uv, });
		vertList.push_back({ core::Vector2f(pos.x + size.x, pos.y), col, uv, });
		vertList.push_back({ pos + size, col, uv, });
	}

	m_UnlitBatch->updateBatch(&vertList[0], sizeof(Vertex)*vertList.size());

	if (a_VertCount == 4) {
		m_UnlitVertCount += 6;
	}
	else {
		m_UnlitVertCount += 3;
	}
}

void bear::graphics::BatchRenderer::submit_texture(Renderable * a_TexturedRenderable)
{
	_textured_buffers.m_TextureBatch.push_back(a_TexturedRenderable);
}