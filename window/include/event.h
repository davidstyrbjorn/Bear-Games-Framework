#pragma once


namespace bear {

	/*
	Enumeration table for the type of each event registered
	Same regardless of underlying framework (GLFW/SFML/SDL)
	*/
	enum EventType {
		KeyPressed,
		KeyDown,
		KeyReleased,
		MousePressed,
		MouseReleased,
		Closed
	};

	/* Struct for actual event */
	/* Same regardless of underlying framework (GLFW/SFML/SDL) */
	struct Event {
		EventType type;
		int key; // keyboard
		int button; // mouse
	};

}