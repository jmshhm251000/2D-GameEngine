#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Animation {
public:
	Animation(sf::Texture& texture, uint16_t imgCount, sf::Vector2<uint16_t> tileCount, sf::Vector2<uint16_t> dimensions, sf::Vector2f scale)
		: m_imgCount(imgCount), m_tileCount(tileCount), m_dimensions(dimensions), m_sprite(texture) {
		// TODO - m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2));
		// TODO - m_sprite.setScale(scale);
	}
	~Animation() = default;

	sf::Sprite at(uint16_t i, bool flip) {
		if (i < m_imgCount) {
			uint16_t ix = i % m_tileCount.x;
			uint16_t iy = floor(i / m_tileCount.x);
			if (flip) {
				m_sprite.setTextureRect(sf::IntRect(m_dimensions.x * (ix+1), m_dimensions.y * iy, -m_dimensions.x, m_dimensions.y));
			}
			else {
				m_sprite.setTextureRect(sf::IntRect(m_dimensions.x * ix, m_dimensions.y * iy, m_dimensions.x, m_dimensions.y));
			}
			
			return m_sprite;
		}
	}

	uint16_t getImgCount() const {
		return m_imgCount;
	}
	
private:
	uint16_t m_imgCount;
	sf::Sprite m_sprite;
	sf::Vector2<uint16_t> m_tileCount;
	sf::Vector2<uint16_t> m_dimensions;

};

class Player
{
private:
	sf::Texture m_idleTexture;
	sf::Texture m_walkTexture;
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
	void move(float deltaTime);
	void update(float deltaTime);
	void render(sf::RenderTarget& window);
};

