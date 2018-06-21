#pragma once

#define DEFAULT_CLEAR_COLOR { 1.0f, 1.0f, 1.0f }

#if defined( BEAR_GLFW_WINDOW )
/* Include GLFW implementation class */
#include"GLFW_window.h"
#include"GLFW_event.h"
#endif

#if defined( BEAR_SFML_WINDOW )
/* Include SFML implementation class */
#include"SFML_window.h"
#include"SFML_event.h"
#endif 

#if defined( BEAR_SDL_WINDOW )
/* Include SDL implementation class */
#endif
