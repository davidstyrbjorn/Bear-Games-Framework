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
#include<algorithm>

using namespace bear::graphics;

View& BatchRenderer::defaultView = View();

bear::graphics::BatchRenderer::BatchRenderer()
{
	// Do nothing
}

bear::graphics::BatchRenderer::~BatchRenderer()
{
	delete m_UnlitBatch;
}

void bear::graphics::BatchRenderer::init()
{
	VertexAttribute temp[] = {
		{ default_shader_pos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0 },
		{ default_shader_col_location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(core::Vector2f)) },
		{ default_shader_uv_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(core::Vector2f) + sizeof(core::Color)) },
		{ 3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(core::Vector2f)*2 + sizeof(core::Color)) }
	};
	
	m_UnlitBatch = new UnlitBatcher(UNLIT_BUFFER_SIZE, temp, 4);

	Graphics::s_DefaultShader->enable();
	int samplers[21] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	Graphics::s_DefaultShader->setUniformIntegerArray("texture_samplers", 21, samplers);
}

void bear::graphics::BatchRenderer::begin()
{
	m_IndicesCount = 0; 
	m_UnlitBatch->clearBatch();
}

void bear::graphics::BatchRenderer::submit(Renderable * a_Renderable)
{
	m_RenderableList.push_back(a_Renderable);
}

void bear::graphics::BatchRenderer::fill_buffer()
{
	for (Renderable* r : m_RenderableList) {
		// Get the neccesary data from the renderable
		core::Vector2f pos = r->m_Transform.m_Position;
		core::Vector2f size = r->m_Transform.m_Size;
		core::Color col = r->m_Color;
		unsigned short int verts = r->m_VertexCount;

		core::Vector2f uv1 = core::Vector2f(0, 0);
		core::Vector2f uv2 = core::Vector2f(0, 1.0f);
		core::Vector2f uv3 = core::Vector2f(1.0f, 1.0f);
		core::Vector2f uv4 = core::Vector2f(1.0f, 0);
		float texture_slot; // To  be initalized later

		// Texture slot 
		if (r->m_TextureName.empty()) // Is there no texture for this renderable?
			texture_slot = -1;
		else {
			// There is a texture for this renderable, but what sampler index does it have? If any.
			bool foundTexture = false;
			// Look the the renderables TBO inside the texture slot list
			unsigned int TBO = ResourceManager::Instance()->GetTexture(r->m_TextureName)->getTextureID();
			for (int i = 0; i < textureSlots.size(); i++) {
				if (textureSlots[i] == TBO) {
					texture_slot = i;
					foundTexture = true;
				}
			}
			if (!foundTexture) {
				if (textureSlots.size() >= 32) {
					// Reset, we have no more texture slots!
					textureSlots.clear();
					flush();
					begin();
					submit(r);
				}

				// No texture slot corresponding with the given TBO was found so add it to the list
				textureSlots.push_back(TBO);
				texture_slot = textureSlots.size();
			}
		}

		std::vector<Vertex> vertList;
		if (verts == 3) {
			vertList.push_back(Vertex{ pos, col,  uv1, texture_slot });
			vertList.push_back(Vertex{ core::Vector2f(pos.x, pos.y + size.y), col, uv2, texture_slot });
			vertList.push_back(Vertex{ pos + size, col, uv3, texture_slot });
		}
		else {
			// No indices so we're doing 2 triangles
			vertList.push_back({ pos, col,  uv1, texture_slot });
			vertList.push_back({ core::Vector2f(pos.x, pos.y + size.y), col, uv2, texture_slot });
			vertList.push_back({ pos + size, col, uv3, texture_slot });

			vertList.push_back({ pos, col, uv1, texture_slot });
			vertList.push_back({ core::Vector2f(pos.x + size.x, pos.y), col, uv4, texture_slot });
			vertList.push_back({ pos + size, col, uv3, texture_slot });
		}

		m_UnlitBatch->updateBatch(&vertList[0], sizeof(Vertex)*vertList.size());

		if (verts == 4) {
			m_IndicesCount += 6;
		}
		else {
			m_IndicesCount += 3;
		}
	}

	m_RenderableList.clear();
}

void bear::graphics::BatchRenderer::flush(View& a_View)
{
	// Sort the renderable list based on the their order integer
	std::sort(m_RenderableList.begin(), m_RenderableList.end(), _layer_compare);
	fill_buffer(); // Empties the renderable list into the batch buffer

	// ================== Unlit flush ========================= //
	Graphics::s_DefaultShader->enable();
	Graphics::s_DefaultShader->setUniformMatrix4x4("view_matrix", a_View.getViewMatrix());
	
	int bound_textures = 0;
	for (int i = 0; i < textureSlots.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textureSlots[i]);
		bound_textures++;
	}
	std::cout << bound_textures << std::endl;
	
	m_UnlitBatch->bindBatch();
	glDrawArrays(GL_TRIANGLES, 0, m_IndicesCount);
		
	Graphics::s_DefaultShader->disable();
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

bool bear::graphics::BatchRenderer::_layer_compare(Renderable * a_R1, Renderable * a_R2)
{
	return (a_R1->m_Layer < a_R2->m_Layer);
}