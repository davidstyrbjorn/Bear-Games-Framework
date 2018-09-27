#include"../include/graphics/renderers/unlit_batch.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include"../include/graphics/graphics.h"

using namespace bear::graphics;

UnlitBatcher::~UnlitBatcher()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
}

UnlitBatcher::UnlitBatcher(size_t a_BatchSize, VertexAttribute* a_VertexAttributes, size_t a_AttributeCount) :
	c_BatchSize(a_BatchSize)
{
	glGenVertexArrays(1, &m_VAO); // Gen vertex array
	glGenBuffers(1, &m_VBO); // Gen vbo buffer
	
	// Bind
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, c_BatchSize, nullptr, GL_DYNAMIC_DRAW); // Allocate the neccesary space

	for (unsigned int i = 0; i < a_AttributeCount; i++) {
		glEnableVertexAttribArray(a_VertexAttributes[i].index);
		glVertexAttribPointer(a_VertexAttributes[i].index, a_VertexAttributes[i].count, a_VertexAttributes[i].type, a_VertexAttributes[i].normalize, a_VertexAttributes[i].stride, a_VertexAttributes[i].starting_offset);
	}
}

void bear::graphics::UnlitBatcher::clearBatch()
{
	// Clear all buffer data
	bindBatch();
	glBufferData(GL_ARRAY_BUFFER, c_BatchSize, nullptr, GL_DYNAMIC_DRAW);
	m_ByteSizeOffset = 0; // Reset the offset
}

bool bear::graphics::UnlitBatcher::updateBatch(void * a_Data, size_t a_Size)
{
	// Batch size check before we add
	if ( m_ByteSizeOffset + a_Size >= c_BatchSize )
		return false;

	// Insert a_Data, taking up a_Size space (bytes)
	bindBatch();
	glBufferSubData(GL_ARRAY_BUFFER, m_ByteSizeOffset, a_Size, a_Data);
	m_ByteSizeOffset += a_Size; // Update the offset
	return true;
}

void bear::graphics::UnlitBatcher::bindBatch()
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}
