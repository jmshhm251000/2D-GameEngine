#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class tilemap
{
private:
	int16_t m_tileIndex;
	uint16_t m_tileCount;
	uint16_t m_tileSize;
	uint16_t m_tileColumn;
	sf::Texture m_tileMapTexture;
	sf::Sprite m_tile;
	sf::Vector2i m_mousePos;
	sf::Vector2f m_scale;
	std::vector<sf::Sprite> m_tiles;

public:
	tilemap(const std::string& filepath, uint16_t tilesize, sf::Vector2f scale);
	~tilemap() = default;

	void changeIndex(sf::Event event);
	sf::Sprite loadTexture(uint16_t i);
	void createTileat(sf::Event events);
	void update(sf::Mouse mouse, sf::RenderWindow& window);
	void render(sf::RenderTarget& window);
};