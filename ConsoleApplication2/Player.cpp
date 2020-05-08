#include "Player.h"
#include "RHolder.h"
#include "Laser.h"
#include <SFML/Graphics.hpp>
Player::Player()
	: Collidable(44, 32)
{
	m_sprite.setSize({ 44, 32 });
	m_sprite.setPosition({ 600 , 800 });
	m_sprite.setTexture(&RHolder::get().textures.get("si/player"));
	m_sprite.setTextureRect({ 0, 0, 11, 8 });
	m_DeathSprite.setSize({ 44, 32 });
	m_DeathSprite.setPosition({ 600 , 800 });
	m_DeathSprite.setTexture(&RHolder::get().textures.get("si/explosion"));
	m_DeathSprite.setTextureRect({ 0, 0, 11, 8 });
	m_deathSound.setBuffer(RHolder::get().soundBuffers.get("si/explosion"));
	m_Shoot.setBuffer(RHolder::get().soundBuffers.get("si/shoot"));
	m_Shoot.setVolume(25);
}

bool Player::restart()
{
	m_livesLeft--;
	if (m_livesLeft < 0)
		return 0;
	m_velocity *= 0.0f;
	m_sprite.setTextureRect({ 0, 0, 11, 8 });
	m_isAlive = true;
	m_sprite.setPosition({ 600 , 800 });
	return 1;
}

void Player::input(std::vector<Laser>& m_lasers)
{
	using Key = sf::Keyboard::Key;
	auto keyDown = [](sf::Keyboard::Key k)
	{
		return sf::Keyboard::isKeyPressed(k);
	};

	float speed = 20;
	if (keyDown(Key::A)) {
		if (m_sprite.getPosition().x > 0)
		{
			m_sprite.setPosition(m_sprite.getPosition().x - speed, 800);
		}
	}
	else if (keyDown(Key::D)) {
		if (m_sprite.getPosition().x < 1180 - WIDTH)
		{
			m_sprite.setPosition(m_sprite.getPosition().x + speed, 800);
		}
	}
	else if (keyDown(Key::Space) && m_playerShotClock.getElapsedTime().asSeconds() > 0.5f)
	{
		sf::Vector2f point = { m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2,
			m_sprite.getPosition().y };
		point.y -= Laser::HEIGHT;
		point.x -= Laser::WIDTH / 2.0f;
		m_lasers.emplace_back(point, Laser::Type::Rectangle, Laser::Direction::Up);
		m_Shoot.play();
		m_playerShotClock.restart();
	}
}

void Player::draw(sf::RenderTarget& target)
{
	if (!m_isAlive) {
		target.draw(m_DeathSprite);
	}
	else if (m_livesLeft >= 0) {
		target.draw(m_sprite);
	}
}

const sf::Vector2f& Player::getPosition() const
{
	return m_sprite.getPosition();
}

void Player::onCollide(Collidable& other)
{
	m_isAlive = false;
}

int Player::getLives() const
{
	return m_livesLeft;
}

bool Player::isAlive() const
{
	return m_isAlive;
}

void Player::tryCollideWithLasers(std::vector<Laser>& m_lasers)
{
	for (auto& laser : m_lasers) {
		if (!laser.isActive() && (int)laser.getDirection() == 1)
			continue;
		if (laser.tryCollideWith(*this)) {
			m_isAlive = false;
			m_deathSound.play();
			m_DeathSprite.setPosition(getPosition());
		}
	}
}