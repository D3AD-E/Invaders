#include "InvaderControl.h"
#include "RHolder.h"

InvaderControl::InvaderControl(float speed)
	: m_stepGap(seconds(speed))
	, m_Renderer(12, 8, Invader::WIDTH, Invader::HEIGHT,
		RHolder::get().textures.get("si/invaders"))
{
	m_speed = speed;
	std::srand((unsigned int)time(NULL));
	Invader::Type types[] = {
		Invader::Type::Squid,
		Invader::Type::Crab,
		Invader::Type::Crab,
		Invader::Type::Octopus,
		Invader::Type::Octopus,
	};
	const unsigned int GAP = 20;
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 11; x++)
		{
			float invaderX = x * Invader::WIDTH + (GAP * x * 2) + 100;
			float invaderY = y * Invader::HEIGHT + (GAP * y) + 100;
			m_invaders.emplace_back(sf::Vector2f{ invaderX, invaderY }, types[y]);
			m_aliveInvaders++;
		}
	}

	for (int i = 0; i < 4; i++) {
		m_stepSounds[i].setBuffer(RHolder::get().soundBuffers.get("si/fastinvader" + std::to_string(i + 1)));
	}
	m_invaderKilledSound.setBuffer(RHolder::get().soundBuffers.get("si/invaderkilled"));
}

void InvaderControl::enemyLaserFire(std::vector<Laser>& m_lasers)
{
	if (m_invaderShotClock.getElapsedTime().asSeconds() >= 0.1 &&
		rand() % 31 == 2)
	{
		auto point = getLowestInvaderPoint();
		if ((int)point.x == -1) return;
		auto type = static_cast<Laser::Type>(rand() % 2 + 1);
		m_lasers.emplace_back(point, type, Laser::Direction::Down);
		m_invaderShotClock.restart();
	}
}

bool InvaderControl::lineCrossed(int y)
{
	auto point = getLowestInvaderPoint();
	if (point.y >= y)
		return true;
	else
		return false;
}

sf::Vector2f InvaderControl::getLowestInvaderPoint()
{
	if (m_aliveInvaders == 0) return { -1, -1 };
	//Keep looping until an invader is found
	while (true) {
		auto invaderColumn = rand() % 11;
		for (int y = 4; y >= 0; y--) {
			int index = y * 11 + invaderColumn;
			auto& invader = m_invaders.at(index);
			if (invader.isAlive()) {
				return {
					//transform to below the invader's center
					invader.getPosition().x + Invader::WIDTH / 2,
					invader.getPosition().y + Invader::HEIGHT + 5
				};
			}
		}
	}
}

void InvaderControl::drawInvaders(RenderTarget& target)
{
	for (auto& invader : m_invaders) {
		if (!invader.isAlive()) continue;
		m_Renderer.renderEntity(target, (int)invader.getType(), invader.getPosition());
	}
}
void InvaderControl::tryCollideWithlasers(std::vector<Laser>& lasers, int& score)
{
	for (auto& laser : lasers) {
		for (auto& invader : m_invaders) {
			if (!invader.isAlive() || !laser.isActive())
				continue;
			if (laser.tryCollideWith(invader))
			{
				m_aliveInvaders--;
				m_invaderKilledSound.play();
				score += 20;
				invader.die();
			}
		}
	}
}

void InvaderControl::tryStep()
{
	const float step = 15;
	static bool movedDown;
	switch (m_aliveInvaders)
	{
	case 1:
		m_stepGap = seconds(m_speed - 0.25f);
		break;
	case 3:
		m_stepGap = seconds(m_speed - 0.15f);
		break;
	case 5:
		m_stepGap = seconds(m_speed - 0.1f);
		break;
	case 6:
		m_stepGap = seconds(m_speed - 0.05f);
		break;
	}
	if (m_stepTimer.getElapsedTime() > m_stepGap)
	{
		m_stepSounds[m_ticks++ % 4].play();
		if (!movedDown && goDown())
		{
			if (m_MoveLeft)
				m_MoveLeft = false;
			else
				m_MoveLeft = true;
			for (auto& invader : m_invaders)
				invader.move(0, step);//Move down
			movedDown = true;
		}
		else
		{
			movedDown = false;
			for (auto& invader : m_invaders)
			{
				if (m_MoveLeft)
				{
					invader.move(-invader.WIDTH, 0);
				}
				else
				{
					invader.move(invader.WIDTH, 0);
				}
			}
		}
		m_stepTimer.restart();
	}
}

bool InvaderControl::goDown()
{
	for (auto& invader : m_invaders)
	{
		if (invader.isAlive() && invader.getPosition().x <= m_MinX)
			return true;
		if (invader.isAlive() && invader.getPosition().x >= m_MaxX)
			return true;
	}
	return false;
}