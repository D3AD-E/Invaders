#pragma once
#include <SFML/Graphics.hpp>
#include "Collidable.h"
class Barrier : public Collidable
{
public:
	Barrier(sf::Vector2f& startinglocation);//creates barrier at {x,y}
	const sf::Vector2f& getPosition() const;//returns place of barrier
	void onCollide(Collidable& other) override;//reduce hitpoints
	void destruct();//active = false
	void draw(sf::RenderTarget& target);//draw barrier
	bool isActive();//check if the barrier is alive
	constexpr static float WIDTH = 100;
	constexpr static float HEIGHT = 50;

private:
	bool m_isActive = true;
	int m_health = 8;
	sf::Vector2f m_Location;
	sf::RectangleShape m_sprite; //texture
};
