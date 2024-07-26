#include <player.h>
#include <memory>

Player::Player() : m_accel(0.5f), m_maxspeed(5.f), m_state(0), m_animIndex(0), m_flip(false), m_position( 600, 300){
	m_idle = std::make_unique<Animation>("resource/idle.png", 4, sf::Vector2<uint16_t>{ 4, 1 }, sf::Vector2<uint16_t>{ 64, 64 }, sf::Vector2f( 2.f, 2.f));
	m_walk = std::make_unique<Animation>("resource/walk.png", 5, sf::Vector2<uint16_t>{ 5, 1 }, sf::Vector2<uint16_t>{ 64, 64 }, sf::Vector2f( 2.f, 2.f));
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

void Player::animationState() {
	// Select animation to play.
	Animation* anim = nullptr;
	switch (m_state) {
		case 0: anim = m_idle.get(); break;
		case 1: anim = m_walk.get(); break;
		default: break;
	}

	// Get next animation sprite.
	if (anim != nullptr && m_clock.getElapsedTime().asSeconds() > 0.16f) {
		m_sprite = anim->at(m_animIndex++ % anim->getImgCount(), m_flip);
		m_clock.restart();
	}
}

void Player::move(uint32_t deltaTime) {
	float preX = m_position.x;
	float speed = (m_movement[1] - m_movement[0]) * m_accel * static_cast<float>(deltaTime);
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

void Player::update(uint32_t deltaTime)
{
	move(deltaTime);
	animationState();
}

void Player::render(sf::RenderTarget& window)
{
	m_sprite.setPosition(m_position);
	window.draw(m_sprite);

	// TODO - Remove later after fixing the origin and scale
	sf::CircleShape pos(10);
	pos.setFillColor(sf::Color::Green);
	pos.setPosition(m_position);
	sf::RectangleShape rect(m_sprite.getLocalBounds().getSize());
	rect.setPosition(m_sprite.getPosition());
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Yellow);
	rect.setOutlineThickness(2.f);
	window.draw(pos);
	window.draw(rect);
}
