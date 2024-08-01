#include <player.h>
#include <memory>

Player::Player() 
	: m_accel(0.3f), m_maxspeed(3.5f), m_state(0), m_animIndex(0), m_flip(false), m_position( 500, 360), m_animTimer(0.f)
{
	m_idle = std::make_unique<Animation>("resource/idle.png", 4, sf::Vector2<uint16_t>{ 4, 1 }, sf::Vector2<uint16_t>{ 64, 64 }, sf::Vector2f( 1.5f, 1.5f));
	m_walk = std::make_unique<Animation>("resource/walk.png", 5, sf::Vector2<uint16_t>{ 5, 1 }, sf::Vector2<uint16_t>{ 64, 64 }, sf::Vector2f( 1.5f, 1.5f));
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
	float speed = (m_movement[1] - m_movement[0]) * m_accel * deltaTime*1000;
	speed = std::clamp(speed, -m_maxspeed, m_maxspeed);
	m_position.x += speed;
	if (m_position.x != preX) {
		m_state = 1;
		m_flip = m_position.x < preX;
	}
	else {
		m_state = 0;
	}
}

void Player::update(float deltaTime)
{
	move(deltaTime);
	animationState(deltaTime);
}

void Player::render(sf::RenderTarget& window)
{
	m_sprite.setPosition(m_position);
	window.draw(m_sprite);
}
