#pragma once

#include<deque>
#include"event.h"

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
		for(Event event : window.getRegisteredEvents()){
			...
			deal with event
			...
		}
		*/
		virtual const std::deque<Event> getRegisteredEvents() const = 0;
	};

} }