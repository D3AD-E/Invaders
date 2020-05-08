#pragma once
#include "Collidable.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class Invader : public Collidable
{
public:
	enum class Type//types of invaders for textures
	{
		Octopus, Crab, Squid,
	};
	Invader(sf::Vector2f& startinglocation, Type type);//create invader at x y
	void move(float x, float y);//move invader to x y
	bool isAlive() const;
	Type getType() const;
	const sf::Vector2f& getPosition() const;
	void onCollide(Collidable& other) override;

	void die(); //אכאיג = פמכס

	constexpr static float WIDTH = 48;
	constexpr static float HEIGHT = 32;

private:
	bool m_IsAlive = true;
	sf::Vector2f m_Location;
	Type m_Type;
};
