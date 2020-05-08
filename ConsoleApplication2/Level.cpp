#include "Level.h"

Level::Level(float speed, int score)
	: m_Renderer(4, 8, Laser::WIDTH, Laser::HEIGHT
		, RHolder::get().textures.get("si/laser"))
	, m_Score(score)
	, IC(speed)
{
	for (float i = 100; i <= 1000; i += 300)
		m_barriers.emplace_back(sf::Vector2f{ i,650 });
}

int Level::getScore()
{
	return m_Score;
}

int Level::getLives()
{
	return p1.getLives();
}

void Level::draw(sf::RenderTarget& target)
{
	p1.draw(target);
	IC.drawInvaders(target);
	drawLasers(target);
	drawBarrires(target);
}

int Level::run()
{
	IC.tryStep();

	if (IC.lineCrossed(620))
	{
		for (auto& barrier : m_barriers)
			barrier.destruct();
	}

	if (IC.lineCrossed(720))
	{
		return 0;
	}

	IC.enemyLaserFire(m_lasers);

	for (auto& laser : m_lasers) {
		laser.update(1.1f);
	}

	collideBarriers();
	p1.tryCollideWithLasers(m_lasers);

	if (!p1.isAlive())
	{
		if (Revivetime.getElapsedTime().asSeconds() >= 1.5f)
		{
			if (!p1.restart())
			{
				return 0;
			}
			Revivetime.restart();
		}
	}
	else
	{
		Revivetime.restart();
		p1.input(m_lasers);
		IC.tryCollideWithlasers(m_lasers, m_Score);
	}

	if (IC.getInvaderNum() == 0)
	{
		return 2;
	}

	return 1;
}

void Level::drawBarrires(RenderTarget& m_window)
{
	for (auto& barrier : m_barriers) {
		barrier.draw(m_window);
	}
}

void Level::collideBarriers()
{
	for (auto& laser : m_lasers) {
		for (auto& barrier : m_barriers) {
			if (!barrier.isActive() || !laser.isActive())
				continue;
			if (laser.tryCollideWith(barrier))
			{
				//Sounds
			}
		}
	}
}

void Level::drawLasers(sf::RenderTarget& target)
{
	for (auto& laser : m_lasers) {
		if (!laser.isActive()) continue;
		m_Renderer.renderEntity(target, (int)laser.getType(), laser.getPosition());
	}
}