#include"../include/graphics/text.h"

#define GLEW_STATIC
#include"GL\glew.h"

#include<core\vector2.h>

#include<ft2build.h>
#include FT_FREETYPE_H

namespace bear { namespace graphics {

	Font::Font(const char * a_path, const int a_size)
	{
		// Glew
		glewInit();
		glewExperimental = true;

		m_Face = new FT_Face();
		m_Lib = new FT_Library();

		// Init lib and face
		if (FT_Init_FreeType(m_Lib))
		{
			std::cout << "Could not load font at " << a_path << std::endl;
			return;
		}
		if (FT_New_Face(*m_Lib, a_path, 0, m_Face))
		{
			std::cout << "Could not load font at " << a_path << std::endl;

			// The font path we got failed so use the default arial.ttf (! WINDOWS ONLY CODE @ !)
			//char *sysDrive = getenv("SystemDrive"); // C:, D:, E:, etc the drive letter of the system 
			//FT_New_Face(*m_Lib, (std::string(sysDrive) + "\\Windows\\Fonts\\arial.ttf").c_str(), 0, m_Face);
		}

		m_FontSize = a_size;
		FT_Set_Pixel_Sizes(*m_Face, 0, a_size);

		// Disables byte sized alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Fill the m_character map
		for (GLubyte c = 0; c < 128; c++) {
			// Load the charcter glyph
			if (FT_Load_Char(*m_Face, c, FT_LOAD_RENDER)) {
				continue;
			}

			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (*m_Face)->glyph->bitmap.width, (*m_Face)->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, (*m_Face)->glyph->bitmap.buffer);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Create the glyph struct and store it
			graphics::glyph_character character = {
				texture,
				core::Vector2f((*m_Face)->glyph->bitmap.width, (*m_Face)->glyph->bitmap.rows),
				core::Vector2f((*m_Face)->glyph->bitmap_left,  (*m_Face)->glyph->bitmap_top),
				(*m_Face)->glyph->advance.x
			};
			m_Characters.insert(std::pair<char, graphics::glyph_character>(c, character));
		}
	}

	//void Font::setFontSize(const int a_size)
	//{
	//	if (m_FontSize != a_size && a_size != -1) {
	//		m_FontSize = a_size;
	//		FT_Set_Pixel_Sizes(*m_Face, 0, a_size);
	//	}
	//}

} }