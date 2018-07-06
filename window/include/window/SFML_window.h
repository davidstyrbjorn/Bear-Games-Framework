#pragma once

#include"window_framework.h"

#include<string>
#include<deque>

namespace sf {
	class Window;
	class Event;
}

namespace bear { namespace window {

	class SFML_Window : public WindowFramework {
	private:
		sf::Window* m_Window;
		unsigned int m_Width, m_Height;
		std::deque<bear::Event> m_Events;

	public:
		SFML_Window(unsigned int a_Width, unsigned int a_Height, std::string a_Caption);

		bool isOpen() override;
		void close() override;
		void clear(core::Color a_Color = core::Color(72 / 255.0f, 214 / 255.0f, 190 / 255.0f)) override;
		void display() override;
		void setFrameRateLimit(unsigned int a_Limit) override;
	
		const std::deque<bear::Event> getRegisteredEvents() const override;
		const bool isKeyDown(int a_Key) override;
		const bool isMouseDown(int a_Button) override;
		const core::Vector2d getMousePosition() override;

		/*
		static bool init();
		static bool exit();
		*/

	private:
		bear::EventType sfmlToBearEventType(sf::Event a_SFMLEvent);
	};

} }