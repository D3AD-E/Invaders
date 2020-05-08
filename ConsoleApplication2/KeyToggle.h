#pragma once

#include <SFML/Graphics.hpp>

class KeyToggle
{
private:
	sf::Keyboard::Key m_key;
	sf::Clock m_delayTimer;

public:
	KeyToggle(sf::Keyboard::Key);

	bool isKeyPressed();
};