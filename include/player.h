#pragma once

#include <iostream>
#include <animation.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
private:
	sf::Sprite m_sprite;
	sf::Clock m_clock;

	std::unique_ptr<Animation> m_idle;
	std::unique_ptr<Animation> m_walk;

	bool m_movement[2] = { false, false };
	bool m_flip;
	float m_accel;
	float m_maxspeed;
	sf::Vector2f m_position;
	uint32_t m_animIndex;
	uint8_t m_state;

public:
	Player();
	~Player() = default;

	void keyListener(sf::Event event);
	void animationState();
	void move(uint32_t deltaTime);
	void update(uint32_t deltaTime);
	void render(sf::RenderTarget& window);
};

