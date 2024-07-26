#pragma once

#include <SFML/Graphics.hpp>
#include <animation.h>

class Fire
{
private:
	sf::Clock m_clock;
	std::unique_ptr<Animation> m_fire;
	sf::Sprite m_sprite;
	uint32_t m_animIndex;

public:
	Fire();
	~Fire() = default;

	void update();
	void render(sf::RenderTarget& window);
};

