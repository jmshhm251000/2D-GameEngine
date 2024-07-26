#pragma once

#include <SFML/Graphics.hpp>

class Animation {
public:
	Animation(const std::string& filepath, uint16_t imgCount, sf::Vector2<uint16_t> tileCount, sf::Vector2<uint16_t> dimensions, sf::Vector2f scale)
		: m_imgCount(imgCount), m_tileCount(tileCount), m_dimensions(dimensions), m_sprite(m_texture)
	{
		if (!m_texture.loadFromFile(filepath)) {
			throw std::exception("Error: no texture to open");
		}
	}

	Animation(sf::Texture& texture, uint16_t imgCount, sf::Vector2<uint16_t> tileCount, sf::Vector2<uint16_t> dimensions, sf::Vector2f scale)
		: m_imgCount(imgCount), m_tileCount(tileCount), m_dimensions(dimensions), m_sprite(texture) {
		// TODO - m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2));
		//TODO - m_sprite.setScale(scale);
	}
	~Animation() = default;

	sf::Sprite at(uint16_t i, bool flip) {
#if defined _DEBUG
		if (i > m_imgCount) printf("Warning: animation index overflow.");
#endif
		i = i % m_imgCount;
		uint16_t ix = static_cast<uint16_t>(i % m_tileCount.x);
		uint16_t iy = static_cast<uint16_t>(floor(i / m_tileCount.x));
		if (flip) {
			m_sprite.setTextureRect(sf::IntRect(m_dimensions.x * (ix + 1), m_dimensions.y * iy, -m_dimensions.x, m_dimensions.y));
		}
		else {
			m_sprite.setTextureRect(sf::IntRect(m_dimensions.x * ix, m_dimensions.y * iy, m_dimensions.x, m_dimensions.y));
		}

		return m_sprite;
	}

	uint16_t getImgCount() const {
		return m_imgCount;
	}

private:
	sf::Texture m_texture;
	uint16_t m_imgCount;
	sf::Sprite m_sprite;
	sf::Vector2<uint16_t> m_tileCount;
	sf::Vector2<uint16_t> m_dimensions;
};