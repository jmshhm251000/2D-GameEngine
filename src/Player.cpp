#include <player.h>
#include <memory>

Player::Player()
	: m_accel(0.3f), m_maxspeed(3.5f), m_state(0), m_animIndex(0), m_flip(false), m_position(500, 120), m_animTimer(0.f), m_speed(0.f, 0.f), m_gravity(0.3f)
{
	m_idle = std::make_unique<Animation>("resource/idle.png", 4, sf::Vector2<uint16_t>{ 4, 1 }, sf::Vector2<uint16_t>{ 64, 64 }, sf::Vector2f( 1.5f, 1.5f));
	m_walk = std::make_unique<Animation>("resource/walk.png", 5, sf::Vector2<uint16_t>{ 5, 1 }, sf::Vector2<uint16_t>{ 64, 64 }, sf::Vector2f( 1.5f, 1.5f));
}

sf::Vector2f Player::getPos()
{
	return sf::Vector2f(m_position);
}

void Player::keyListener(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::A)
			m_movement[0] = true;

		if (event.key.code == sf::Keyboard::D)
			m_movement[1] = true;

	}
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::A)
			m_movement[0] = false;

		if (event.key.code == sf::Keyboard::D)
			m_movement[1] = false;

	}
}

void Player::animationState(float deltaTime) {
	// Select animation to play.
	Animation* anim = nullptr;
	switch (m_state) {
		case 0: anim = m_idle.get(); break;
		case 1: anim = m_walk.get(); break;
		default: break;
	}

	m_animTimer += deltaTime;
	// Get next animation sprite.
	if (anim != nullptr && m_animTimer > 0.16f) {
		m_sprite = anim->at(m_animIndex++ , m_flip);
		m_animTimer = 0.f;
	}
}

void Player::move(float deltaTime) {
	float preX = m_position.x;
	m_speed.x = (m_movement[1] - m_movement[0]) * m_accel * deltaTime*1000;
	m_speed.x = std::clamp(m_speed.x, -m_maxspeed, m_maxspeed);
	m_position.x += m_speed.x;
	m_speed.y = m_gravity * deltaTime * 1000;
	m_position.y += m_speed.y;
	if (m_position.x != preX) {
		m_state = 1;
		m_flip = m_position.x < preX;
	}
	else {
		m_state = 0;
	}
}

void Player::checkCollision(std::vector<sf::Vector2i> tiles)
{
	for (sf::Vector2i tile : tiles) {
		if (m_speed.y > 0) {
			if (m_position.y + 24 > tile.y && m_position.y + 24 < tile.y + 35)
				m_position.y -= m_speed.y;
		}
		if (m_speed.x > 0) {
			if (m_position.x + 12 > tile.x && m_position.x + 12 < tile.x + 35 && m_position.y > tile.y && m_position.y < tile.y + 35)
					m_position.x -= m_speed.x;
		}
		if (m_speed.x < 0) {
			if (m_position.x - 12 > tile.x && m_position.x - 12 < tile.x + 35 && m_position.y > tile.y && m_position.y < tile.y + 35)
				m_position.x += m_speed.x * -1;
		}
	}
}

void Player::update(float deltaTime, std::vector<sf::Vector2i> tiles)
{
	move(deltaTime);
	checkCollision(tiles);
	animationState(deltaTime);
}

void Player::render(sf::RenderTarget& window)
{
	m_sprite.setPosition(m_position);
	window.draw(m_sprite);
}
