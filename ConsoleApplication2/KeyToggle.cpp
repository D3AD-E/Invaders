#include "KeyToggle.h"

KeyToggle::KeyToggle(sf::Keyboard::Key key)
	: m_key(key)
{ }

bool KeyToggle::isKeyPressed()
{
	if (m_delayTimer.getElapsedTime().asSeconds() > 0.2) {
		if (sf::Keyboard::isKeyPressed(m_key)) {
			m_delayTimer.restart();
			return true;
		}
	}
	return false;
}