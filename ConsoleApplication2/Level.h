#pragma once
#include "Laser.h"
#include "InvaderControl.h"
#include "Player.h"
#include "AnimationRenderer.h"
#include "Barrier.h"
class Level
{
public:
	Level(float speed, int score = 0);//create level with invader speed
	int getScore();
	int getLives();
	void draw(sf::RenderTarget& target);
	void drawLasers(sf::RenderTarget& target);
	int run(); //returns 0: if player lost, 1: if cycle ended cyccessfully, 2: if player won and level ended

	void drawBarrires(RenderTarget& m_window);
	void collideBarriers();
private:
	int m_Score;
	InvaderControl IC;
	Player p1;
	AnimationRenderer m_Renderer;
	sf::Clock Revivetime;
	std::vector<Laser> m_lasers;
	std::vector<Barrier> m_barriers;
};
