#include "Invader.h"

Invader::Invader(Vector2f& startinglocation, Type type)
	:m_Location(startinglocation)
	, m_Type(type)
	, Collidable(WIDTH, HEIGHT)
{
}

void Invader::move(float x, float y)
{
	m_Location += {x, y};
}

bool Invader::isAlive() const
{
	return m_IsAlive;
}

Invader::Type Invader::getType() const
{
	return m_Type;
}

void Invader::die()
{
	m_IsAlive = false;
}

const sf::Vector2f& Invader::getPosition() const
{
	return m_Location;
}

void Invader::onCollide(Collidable& other)
{
	m_IsAlive = false;
}