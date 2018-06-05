#include"../include/SFML_window.h"

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
	// @ Nothing here?
}

void bear::window::SFML_Window::display()
{
	m_Window->display();
}
