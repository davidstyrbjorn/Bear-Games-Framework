#include"../include/window/SFML_window.h"

#include<iostream>

#include<SFML\Window.hpp>
#include<GLFW\glfw3.h>

bear::window::SFML_Window::SFML_Window(unsigned int a_Width, unsigned int a_Height, std::string a_Caption)
	: m_Width(a_Width), m_Height(a_Height)
{
	m_Window = new sf::Window(sf::VideoMode(a_Width, a_Height), a_Caption);
}

bool bear::window::SFML_Window::isOpen()
{
	return m_Window->isOpen();
}

void bear::window::SFML_Window::close()
{
	m_Window->close();
	delete m_Window;
}

void bear::window::SFML_Window::clear(core::Color a_Color)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(a_Color.r, a_Color.g, a_Color.b, a_Color.a);

	sf::Event sfml_event;
	while (m_Window->pollEvent(sfml_event))
	{
		bear::Event event;
		event.type = sfmlToBearEventType(sfml_event);
		event.key = sfml_event.key.code;
		event.button = sfml_event.mouseButton.button;
		m_Events.push_back(event);

		if (sfml_event.type == sf::Event::Closed) {
			this->close();
		}
	}
}

void bear::window::SFML_Window::display()
{
	m_Events.clear();
	m_Window->display();
}

void bear::window::SFML_Window::setFrameRateLimit(unsigned int a_Limit)
{
	m_Window->setFramerateLimit(a_Limit);
}

const std::deque<bear::Event>& bear::window::SFML_Window::getRegisteredEvents() const
{
	return m_Events;
}

const bool bear::window::SFML_Window::isKeyDown(int a_Key)
{
	return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(a_Key));
}

const bool bear::window::SFML_Window::isMouseDown(int a_Button)
{
	return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(a_Button));
}

const bear::core::Vector2d bear::window::SFML_Window::getMousePosition()
{
	return bear::core::Vector2d(sf::Mouse::getPosition(*m_Window).x, sf::Mouse::getPosition(*m_Window).y);
}

bear::EventType bear::window::SFML_Window::sfmlToBearEventType(sf::Event a_SFMLEvent)
{
	if (a_SFMLEvent.type == sf::Event::KeyPressed) {
		return bear::EventType::KeyPressed;
	}
	else if (a_SFMLEvent.type == sf::Event::KeyReleased) {
		return bear::EventType::KeyReleased;
	}
	else if (a_SFMLEvent.type == sf::Event::MouseButtonPressed) {
		return bear::EventType::MousePressed;
	}
	else if (a_SFMLEvent.type == sf::Event::MouseButtonReleased) {
		return bear::EventType::MouseReleased;
	}
}
