#pragma once
#include "Invader.h"
#include "Laser.h"
#include "AnimationRenderer.h"
#include <vector>
using namespace std;

class InvaderControl
{
public:
	InvaderControl(float speed);//Create invaders with such speed
	int getInvaderNum() { return m_aliveInvaders; };//how many invaders are alive
	void drawInvaders(RenderTarget& target);
	void tryCollideWithlasers(std::vector<Laser>& lasers, int& score);//increase score if hit
	void tryStep();//move left ot tight if it is the end of the screen, move down
	bool goDown();//move down
	void enemyLaserFire(std::vector<Laser>& m_lasers);//shoot at player
	bool lineCrossed(int y);//check if invader crossed y coord
	sf::Vector2f getLowestInvaderPoint();

private:
	vector<Invader> m_invaders;
	Clock m_stepTimer;
	Clock m_invaderShotClock;
	Time m_stepGap;//time for a step

	Sound m_stepSounds[4];
	Sound m_invaderKilledSound;

	AnimationRenderer m_Renderer;//animation
	int m_aliveInvaders = 0;
	int m_ticks = 0;
	bool m_MoveLeft = true;
	float m_speed;
	float m_MinX = 50;//screen
	float m_MaxX = 1100;//screen
};
