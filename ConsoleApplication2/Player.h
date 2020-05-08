#pragma once
#include "SFML/Graphics.hpp"
#include "Laser.h"
#include "AnimationRenderer.h"
class Player : Collidable
{
public:
	constexpr static int WIDTH = 44;
	constexpr static int HEIGHT = 32;

	Player();
	void input(std::vector<Laser>& m_lasers);//keyboard
	void draw(sf::RenderTarget& target);

	const sf::Vector2f& getPosition() const;
	void onCollide(Collidable& other) override;//die if got hit by laser
	void tryCollideWithLasers(std::vector<Laser>& m_lasers);
	int getLives() const;
	bool isAlive() const;
	bool restart();//if there are any lifes => true else false

private:
	sf::RectangleShape m_sprite;
	sf::RectangleShape m_DeathSprite;
	sf::Vector2f m_velocity;
	sf::Sound m_deathSound;
	sf::Sound m_Shoot;
	bool m_isAlive = true;
	int m_livesLeft = 3;
	sf::Clock m_playerShotClock;
};
