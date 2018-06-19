#pragma once

#include"event.h"
#include<deque>
#include"core\vector2.h"

namespace bear { namespace window {

	enum WINDOW_FRAMEWORKS {
		GLFW,
		SFML,
		SDL
	};

	class WindowFramework {
	public:
		~WindowFramework() { }

		// Shared methods for every window framework implementation (BearWindow)
		virtual bool is_open() { return false; }
		virtual void close() { }
		/* Called at the top of every frame */
		virtual void clear() { }
		/* Called at the end of every frame */
		virtual void display() { }

		/* Event related methods */
		/*
		for(Event event : getRegisteredEvents()){
			...
			deal with event
			...
		}
		*/
		virtual const std::deque<bear::Event> getRegisteredEvents() const = 0;
		/* Realtime input methods */
		virtual const bool isKeyDown(int a_Key) = 0;
		virtual const bool isMouseDown(int a_Button) = 0;
		virtual const core::Vector2d getMousePosition() { return core::Vector2d(); }
	};

} }