#pragma once

#include"../core/vector2.h"
#include"../core/color.h"

namespace bear { namespace graphics { 

	struct Vertex {
		core::Vector2f Position;
		core::Color Color;
		core::Vector2f TextureCoordinates;

		//Vertex(core::Vector2f pos, core::Color col, core::Vector2f ts) {
		//	Position = pos;
		//	Color = col;
		//	TextureCoordinates = ts;
		//}
	};

}} 