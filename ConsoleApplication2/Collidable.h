#pragma once

#include <SFML/Graphics.hpp>

class Collidable
{
public:
	Collidable(float width, float height);//creater hitbox

	bool tryCollideWith(Collidable& other);//checks collision
	sf::FloatRect getBox() const;//return size of hitbox

	virtual const sf::Vector2f& getPosition()const = 0;
	virtual void onCollide(Collidable& other) = 0;

private:
	sf::Vector2f m_size;
};