#pragma once

#include"window_framework.h"

#include<string>
#include<deque>

namespace sf {
	class Window;
}

namespace bear { namespace window {

	class SFML_Window : public WindowFramework {
	private:
		sf::Window* m_Window;
		unsigned int m_Width, m_Height;
		std::deque<bear::Event> m_Events;

	public:
		SFML_Window(unsigned int a_Width, unsigned int a_Height, std::string a_Caption);

		bool is_open() override;
		void close() override;
		void clear() override;
		void display() override;
	
		const std::deque<bear::Event> getRegisteredEvents() const override;

		/*
		static bool init();
		static bool exit();
		*/
	};

} }