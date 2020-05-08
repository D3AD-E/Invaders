#pragma once

#include <SFML/Graphics.hpp>
#include "RHolder.h"
#include "Collidable.h"

class Laser : public Collidable
{
public:
	constexpr static float HEIGHT = 24;
	constexpr static float WIDTH = 12;

	enum class Type//textures
	{
		Rectangle,
		Lightning,
		Knife
	};

	enum class Direction //direction of laser
	{
		Up = -1,
		Down = 1
	};

	Laser(const sf::Vector2f& position, Type type, Direction direction);
	void update(float att);
	void onCollide(Collidable& other) override;
	void destroy();

	const sf::Vector2f& getPosition() const;
	Type getType() const;
	bool isActive() const;
	Direction getDirection() const;

private:
	sf::Vector2f m_position;
	Type m_type;
	Direction m_direction;
	bool m_isActive = true;
};