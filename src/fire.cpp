#include <fire.h>

Fire::Fire()
	: m_animIndex(0), m_animTime(0.f)
{
	m_fire = std::make_unique<Animation>("resource/Fire+Sparks-Sheet.png", 19, sf::Vector2<uint16_t>{ 4, 5 }, sf::Vector2<uint16_t>{ 96, 96 }, sf::Vector2f( 1.5f, 1.5f));
}

void Fire::update(float deltaTime)
{
	m_animTime += deltaTime;
	if (m_animTime > 0.08f) {
		m_sprite = m_fire->at(m_animIndex++ % m_fire->getImgCount(), false);
		m_animTime = 0.f;
	}
}

void Fire::render(sf::RenderTarget& window)
{
	m_sprite.setPosition(sf::Vector2f(300, 310));
	window.draw(m_sprite);
}
