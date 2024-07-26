#include <fire.h>

Fire::Fire()
{
	m_fire = std::make_unique<Animation>("resource/Fire+Sparks-Sheet.png", 19, sf::Vector2<uint16_t>{ 4, 5 }, sf::Vector2<uint16_t>{ 96, 96 }, sf::Vector2f(2.f, 2.f));
}

void Fire::update()
{
	if (m_clock.getElapsedTime().asSeconds() > 0.08f) {
		m_sprite = m_fire->at(m_animIndex++ % m_fire->getImgCount(), false);
		m_clock.restart();
	}
}

void Fire::render(sf::RenderTarget& window)
{
	m_sprite.setPosition(sf::Vector2f(700, 300));
	window.draw(m_sprite);
}
