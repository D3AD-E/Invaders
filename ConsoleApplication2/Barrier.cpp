#include "Barrier.h"
Barrier::Barrier(sf::Vector2f& startinglocation)
	:m_Location(startinglocation)
	, Collidable(WIDTH, HEIGHT)
{
	m_sprite.setSize({ WIDTH, HEIGHT });
	m_sprite.setPosition(startinglocation);
	m_sprite.setFillColor(sf::Color::Green);
}

const sf::Vector2f& Barrier::getPosition() const
{
	return m_Location;
}

void Barrier::onCollide(Collidable& other)
{
	m_health--;
	if (m_health == 0)
		destruct();
	else if (m_health == 3)
		m_sprite.setFillColor(sf::Color::Red);
	else if (m_health == 6)
		m_sprite.setFillColor(sf::Color::Yellow);
}

void Barrier::destruct()
{
	m_isActive = false;
}

void Barrier::draw(sf::RenderTarget& target)
{
	if (m_isActive) {
		target.draw(m_sprite);
	}
}

bool Barrier::isActive()
{
	return m_isActive;
}