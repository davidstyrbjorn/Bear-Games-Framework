#include"../include/graphics/text.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include"../include/graphics/shader.h"
#include"../include/graphics/view.h"

#include"../include/graphics/graphics.h"

using namespace bear::graphics;

View& TextLabel::defaultView = View();

bear::graphics::TextLabel::TextLabel(std::string a_Text, Font& a_Font, core::Vector2f a_Position, core::Color a_Color)
	: m_Font(a_Font)
{
	m_StringLiteral = a_Text;
	m_Position = a_Position;
	m_Color = a_Color;

	//const char* vertex = "#version 330 core \n layout(location = 0) in vec4 vertex; \n out vec2 TexCoords; \n uniform mat4 projection; \n void main() \n { \n gl_Position = projection * vec4(vertex.xy, 0, 1); \n TexCoords = vertex.zw; \n }";
	//const char* fragment = "#version 330 core \n in vec2 TexCoords; \n uniform sampler2D texture; \n uniform vec3 textColor; \n out vec4 color; \n void main() \n { \n color = vec4(1,1,1,texture2D(texture, TexCoords).r) * vec4(textColor,1); \n }";

	// BUFFER SETUP
	glGenVertexArrays(1, &m_Buffer.VAO);
	glBindVertexArray(m_Buffer.VAO);

	glGenBuffers(1, &m_Buffer.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffer.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

bear::graphics::TextLabel::~TextLabel()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &m_Buffer.VAO);
	glDeleteBuffers(1, &m_Buffer.VBO);
}

void bear::graphics::TextLabel::draw(View& a_View)
{
	Graphics::s_DefaultShaderText->enable();
	Graphics::s_DefaultShaderText->setUniformColor3f("text_color", core::Color(m_Color.r, m_Color.g, m_Color.b));
	Graphics::s_DefaultShaderText->setUniformMatrix4x4("view_matrix", a_View.getViewMatrix());

	glBindVertexArray(m_Buffer.VAO);

	float offsetX = 0;
	std::string::const_iterator c;
	for (c = m_StringLiteral.begin(); c != m_StringLiteral.end(); c++) 
	{
		glyph_character ch = m_Font.m_Characters[*c];
	
		float xpos = (m_Position.x + ch.m_Bearings.x) + offsetX;
		float ypos = m_Position.y + (ch.m_Size.y - ch.m_Bearings.y);
		float width = ch.m_Size.x;
		float height = ch.m_Size.y;

		// Update VBO 
		float vertices[6][4] = {
			{ xpos,			ypos - height,   0.0, 0.0 },
			{ xpos,			ypos,			 0.0, 1.0 },
			{ xpos + width, ypos,			 1.0, 1.0 },

			{ xpos,			ypos - height,   0.0, 0.0 },
			{ xpos + width, ypos,			 1.0, 1.0 },
			{ xpos + width, ypos - height,   1.0, 0.0 }
		};
		glBindTexture(GL_TEXTURE_2D, ch.m_TexID);

		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		offsetX += (ch.m_Offset >> 6); // Advance for the next glyph (note number is 1/64 of 1 pixel so bitshift by 6 to format into pixel size)
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void bear::graphics::TextLabel::setFont(Font & a_Font)
{
	m_Font = a_Font;
}

void bear::graphics::TextLabel::setStringLiteral(const std::string & a_StringLiteral)
{
	m_StringLiteral = a_StringLiteral;
}

void bear::graphics::TextLabel::setPosition(core::Vector2f a_Position)
{
	m_Position = a_Position;
}
