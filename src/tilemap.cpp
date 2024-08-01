#include <tilemap.h>
#include <iostream>

tilemap::tilemap(const std::string& filepath, uint16_t tilesize, sf::Vector2f scale)
	: m_tileIndex(0), m_tileSize(tilesize), m_scale(scale)
{
	if (!m_tileMapTexture.loadFromFile(filepath)) {
		throw std::exception("Error: no texture to open");
	}
	m_tileColumn = m_tileMapTexture.getSize().x / m_tileSize;
	m_tileCount = (m_tileMapTexture.getSize().x / m_tileSize) * (m_tileMapTexture.getSize().y / m_tileSize);
	m_tile.setTexture(m_tileMapTexture);
	float origin = static_cast<float>(m_tileSize / 2);
	m_tile.setOrigin(origin, origin);
}

void tilemap::changeIndex(sf::Event event)
{
	if (event.type == event.MouseWheelScrolled) {
		m_tileIndex += static_cast<int16_t>(event.mouseWheelScroll.delta);
		m_tileIndex = (m_tileIndex % m_tileCount + m_tileCount) % m_tileCount;
	}
}

sf::Sprite tilemap::loadTexture(uint16_t i)
{
	i = i % m_tileCount;

	uint16_t ix = static_cast<uint16_t>(i % m_tileColumn);
	uint16_t iy = static_cast<uint16_t>(floor(i / m_tileColumn));

	m_tile.setTextureRect(sf::IntRect(m_tileSize * ix, m_tileSize * iy, m_tileSize, m_tileSize));

	return m_tile;
}

void tilemap::createTileat(sf::Event event)
{
	if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		m_tiles.push_back(m_tile);
		m_tiles.back().setPosition(m_mousePos.x / m_tileSize * m_tileSize + m_tileSize/2, m_mousePos.y / m_tileSize * m_tileSize + m_tileSize/2);
	}
}

void tilemap::update(sf::Mouse mouse, sf::RenderWindow& window)
{
	m_mousePos.x = std::clamp(mouse.getPosition(window).x, 0, static_cast<int16_t>(window.getSize().x) - 1);
	m_mousePos.y = std::clamp(mouse.getPosition(window).y, 0, static_cast<int16_t>(window.getSize().y) - 1);
	m_tile.setPosition(static_cast<sf::Vector2f>(m_mousePos));
	loadTexture(m_tileIndex);
}

void tilemap::render(sf::RenderTarget& window)
{
	window.draw(m_tile);
	for (sf::Sprite tile : m_tiles) {
		window.draw(tile);
	}
}