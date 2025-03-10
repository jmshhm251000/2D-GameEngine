#pragma once

#include <SFML/Graphics.hpp>
#include <animation.h>

class Entity
{
private:
	std::unique_ptr<Animation> m_fire;
	sf::Sprite m_sprite;
	uint32_t m_animIndex;
	float m_animTime;

public:
	Entity();
	~Entity() = default;

	void update(float deltaTime);
	void render(sf::RenderTarget& window);
};

