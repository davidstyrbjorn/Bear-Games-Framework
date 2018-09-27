#include"../include/graphics/framebuffer.h"

#include"../include/memory/resource_manager.h"
#include"../include/graphics/shader.h"

#define GLEW_STATIC
#include<GL/glew.h>

using namespace bear;
using namespace bear::graphics;

Framebuffer::Framebuffer(unsigned int a_Width, unsigned int a_Height)
{
	// Generate and configure the framebuffer + related buffers

	// 1. Create the frambuffer
	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

	// 2. Create the texture unit
	glActiveTexture(GL_TEXTURE0 + 0);
	glGenTextures(1, &m_TBO);
	glBindTexture(GL_TEXTURE_2D, m_TBO);
	// Give an empty image to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, a_Width, a_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	// Bad filtering, important
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_TBO, 0);
	glDrawBuffers(1, m_DrawBuffer); // 1 because we have one color buffer

	// Unbind our shit
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Setup our framebuffer quad!
	glGenVertexArrays(1, &m_QuadVAO);
	glBindVertexArray(m_QuadVAO);

	glGenBuffers(1, &m_QuadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_QuadVBO);

	float buffer_data[] = {
		// pos              uv
		-1.0f, -1.0f,    0.0, 0.0,
		1.0f,  -1.0f,    1.0, 0.0,
		-1.0f,  1.0f,    0.0, 1.0,
		-1.0f,  1.0f,    0.0, 1.0,
		1.0f,  -1.0f,    1.0, 0.0,
		1.0f,   1.0f,    1.0, 1.0
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

	glBindVertexArray(0);
}

Framebuffer::~Framebuffer()
{
	// @TODO Delete the FBO and related buffers
	unbind();
	glDeleteFramebuffers(1, &m_FBO);
	glDeleteTextures(1, &m_TBO);
	glDeleteVertexArrays(1, &m_QuadVAO);
	glDeleteBuffers(1, &m_QuadVBO);
}

void bear::graphics::Framebuffer::setShader(std::string a_ShaderName)
{
	m_FramebufferShader = ResourceManager::Instance()->GetShader(a_ShaderName);
}

void bear::graphics::Framebuffer::setFramebufferRenderTarget(unsigned int a_FBO)
{
	m_TargetFBO = a_FBO;
}

void bear::graphics::Framebuffer::windowResize(unsigned int a_Width, unsigned int a_Height)
{
	std::cout << "Asshole\n";
	glBindTexture(GL_TEXTURE_2D, m_TBO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, a_Width, a_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void bear::graphics::Framebuffer::clearFBO()
{
	bind();
	glClear(GL_COLOR_BUFFER_BIT);
}

void Framebuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}

void Framebuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void bear::graphics::Framebuffer::FBOunbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::drawFramebufferTextureToScreen()
{
	// Bind to the m_FrameBufferDrawTarget if we have one or simply bind to no FBO and draw to that texture/screen
	glBindFramebuffer(GL_FRAMEBUFFER, m_TargetFBO);

	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(m_QuadVAO);
	m_FramebufferShader->enable();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TBO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

unsigned int bear::graphics::Framebuffer::getFBO()
{
	return m_FBO;
}
