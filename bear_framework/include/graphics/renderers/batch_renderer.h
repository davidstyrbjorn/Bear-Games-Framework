#pragma once

#include<vector>
#include<deque>

#include"../vertex.h"
#include"../types.h"
#include"unlit_batch.h"

namespace bear { namespace core {
	class Matrix4x4;
} }

namespace bear { namespace graphics {

#define VERTEX_SIZE sizeof(Vertex)
#define TRIANGLE_SIZE VERTEX_SIZE * 3
#define QUAD_SIZE VERTEX_SIZE * 6
#define QUAD_MAX_COUNT 500
#define UNLIT_BUFFER_SIZE QUAD_SIZE * QUAD_MAX_COUNT

	/*
	* This renderer batches data into one big buffer (for unlit-primitives)
	* When dealing with rendering textures, we render them after dealing with the unlit-primitives
	* REASON: I don't know how to batch triangle + quads + sprites so this renderer renders sprites seperate from triangle + quads
	*/

	class Shader;
	class Renderable;
	class View;

	struct texuted_buffers 
	{
		unsigned int VAO, VBO, IBO;
		std::deque<Renderable*> m_TextureBatch;
	};

	class BatchRenderer {
	private:
		UnlitBatcher *m_UnlitBatch;
		texuted_buffers _textured_buffers;
		unsigned int m_UnlitVertCount = 0;
		// Used by default if none is submitted by the caller
		static View& defaultView;

		std::vector<int> samplerIndexList;

	private:
		int getTextureSlot(const int a_TID);

	public:
		BatchRenderer();
		~BatchRenderer();
	
		/*
		* call init or the renderer won't work
		*/
		void init();

		/*
		* Render routines, use submit between begin&flush
		* begin prepares the renderer for new data through submit
		* flush renders the submitted data
		*/
		void begin();
		void submit(Renderable& a_Renderable);
		void flush(View& a_View = defaultView);

	private:
		void submit_unlit(Renderable& a_UnlitRenderable);
		void submit_texture(Renderable* a_TexturedRenderable);
	};

} }