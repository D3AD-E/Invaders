#include "Laser.h"

Laser::Laser(const sf::Vector2f& position, Type type, Direction direction)
	: Collidable(WIDTH / 1.5, HEIGHT)
	, m_position(position)
	, m_type(type)
	, m_direction(direction)
{
}

void Laser::update(float att)
{
	float speed = 10 * (float)m_direction * att;
	m_position.y += speed;
	if (m_position.y <= 0 || m_position.y >= 900) {
		destroy();
	}
}

void Laser::onCollide(Collidable& other)
{
	destroy();
}

void Laser::destroy()
{
	m_isActive = false;
}

const sf::Vector2f& Laser::getPosition() const
{
	return m_position;
}

Laser::Type Laser::getType() const
{
	return m_type;
}

bool Laser::isActive() const
{
	return m_isActive;
}

Laser::Direction Laser::getDirection() const
{
	return m_direction;
}