#include"../include/graphics/framebuffer.h"

#include"../include/memory/resource_manager.h"
#include"../include/graphics/shader.h"

#define GLEW_STATIC
#include<GL/glew.h>

using namespace bear;
using namespace bear::graphics;

Framebuffer::Framebuffer()
{

	/*
	
	// 1. Create the render tearget
	// We're going to render to a Framebuffer. It's a container for textures and an optional depth buffer.
	// FramebufferName regroups 0, 1 or more textures and 0 or 1 depth buffers
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	glActiveTexture(GL_TEXTURE0);
	// 2. Create the texture which will contain the RGB output of our 'regular' render shader
	// Basic, simply create an empty texture
	glGenTextures(1, &RenderedTexture);
	glBindTexture(GL_TEXTURE_2D, RenderedTexture); // All future texture calls will now modify RenderedTexture
	// Give an "empty" image to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 600, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// We might also want to attatch a depth buffer, if we do this is how we would do it
	//glGenRenderbuffers(1, &DepthRenderBuffer);
	//glBindRenderbuffer(GL_RENDERBUFFER, DepthRenderBuffer);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 600, 600);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DepthRenderBuffer);

	// 3. Configure our framebuffer
	// Set RenderedTexture as color attatchement 0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, RenderedTexture, 0);
	glDrawBuffers(1, DrawBuffers); // 1 is the size of the DrawBuffers
	
	*/

	// Generate and configure the framebuffer related buffers

	// 1. Create the frambuffer
	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

	// 2. Create the texture unit
	glActiveTexture(GL_TEXTURE0 + 0);
	glGenTextures(1, &m_TBO);
	glBindTexture(GL_TEXTURE_2D, m_TBO);
	// Give an empty image to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 600, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
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

}

void bear::graphics::Framebuffer::setShader(std::string a_ShaderName)
{
	m_FramebufferShader = ResourceManager::Instance()->GetShader(a_ShaderName);
}

void bear::graphics::Framebuffer::setFramebufferRenderTarget()
{
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
	if (m_FramebufferDrawTarget == nullptr)
		Framebuffer::FBOunbind();
	else
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferDrawTarget->getFBO());

	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(m_QuadVAO);
	m_FramebufferShader->enable();
	glBindTexture(GL_TEXTURE_2D, m_TBO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

unsigned int bear::graphics::Framebuffer::getFBO()
{
	return m_FBO;
}
