#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class tilemap
{
private:
	bool m_checker[37][21] = { 0 };
	int16_t m_tileIndex;
	uint16_t m_tileCount;
	uint16_t m_tileSize;
	uint16_t m_tileColumn;
	sf::Texture m_tileMapTexture;
	sf::Vector2i m_mousePos;
	sf::Vector2i m_mouseToTileIndex;
	std::vector<sf::Sprite> m_tiles;
	std::vector<sf::Sprite> m_tileOptions;

public:
	tilemap(const std::string& filepath, uint16_t tilesize);
	~tilemap() = default;

	std::vector<sf::Vector2i> nearTiles(sf::Vector2f playerPos);
	void changeIndex(sf::Event event);
	void loadTexture(float origin);
	void createTileat(sf::Event event);
	void removeTile(sf::Event event);
	void checkDuplicates(sf::Sprite tile);
	void update(sf::Mouse mouse, sf::RenderWindow& window, sf::Vector2f position, uint16_t size);
	void render(sf::RenderTarget& window);
};