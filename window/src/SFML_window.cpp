#include"../include/SFML_window.h"

#include<iostream>

#include<SFML\Window.hpp>

bear::window::SFML_Window::SFML_Window(unsigned int a_Width, unsigned int a_Height, std::string a_Caption)
	: m_Width(a_Width), m_Height(a_Height)
{
	m_Window = new sf::Window(sf::VideoMode(a_Width, a_Height), a_Caption);
}

bool bear::window::SFML_Window::is_open()
{
	return m_Window->isOpen();
}

void bear::window::SFML_Window::close()
{
	m_Window->close();
}

void bear::window::SFML_Window::clear()
{
	sf::Event event;
	while (m_Window->pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			// Register event
			bear::Event _event;
			_event.type = bear::EventType::KeyPressed;
			_event.key = event.key.code; 
			m_Events.push_back(_event);
		}
		else if (event.type == sf::Event::KeyReleased) {
			// Register event
			bear::Event _event;
			_event.type = bear::EventType::KeyReleased;
			_event.key = event.key.code;
			m_Events.push_back(_event);
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			// Register event
			bear::Event _event;
			_event.type = bear::EventType::MousePressed;
			_event.button = event.mouseButton.button;
			m_Events.push_back(_event);
		}
		else if (event.type == sf::Event::MouseButtonReleased) {
			// Register event
			bear::Event _event;
			_event.type = bear::EventType::MouseReleased;
			_event.button = event.mouseButton.button;
			m_Events.push_back(_event);
		}

		if (event.type == sf::Event::Closed) {
			this->close();
		}
	}
}

void bear::window::SFML_Window::display()
{
	m_Events.clear();
	m_Window->display();
}

const std::deque<bear::Event> bear::window::SFML_Window::getRegisteredEvents() const
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
