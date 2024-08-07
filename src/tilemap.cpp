#include <tilemap.h>
#include <iostream>

tilemap::tilemap(const std::string& filepath, uint16_t tilesize)
	: m_tileIndex(0), m_tileSize(tilesize)
{
	if (!m_tileMapTexture.loadFromFile(filepath)) {
		throw std::exception("Error: no texture to open");
	}

	m_tileColumn = m_tileMapTexture.getSize().x / m_tileSize;
	m_tileCount = (m_tileMapTexture.getSize().x / m_tileSize) * (m_tileMapTexture.getSize().y / m_tileSize);

	float origin = static_cast<float>(m_tileSize / 2);
	loadTexture(origin);
}

void tilemap::loadTexture(float origin)
{
	for (size_t i = 0; i < m_tileCount; i++) {

		uint16_t ix = static_cast<uint16_t>(i % m_tileColumn);
		uint16_t iy = static_cast<uint16_t>(floor(i / m_tileColumn));

		m_tileOptions.emplace_back().setTexture(m_tileMapTexture);
		m_tileOptions.back().setTextureRect(sf::IntRect(m_tileSize * ix, m_tileSize * iy, m_tileSize, m_tileSize));
		m_tileOptions.back().setOrigin(origin, origin);
	}
}

std::vector<sf::Vector2i> tilemap::nearTiles(sf::Vector2f playerPos)
{
	std::vector<sf::Vector2i> tiles;
	std::vector<sf::Vector2i> nearTiles{ sf::Vector2i(-1,-1),sf::Vector2i(0,-1),sf::Vector2i(1,-1),sf::Vector2i(-1,0),sf::Vector2i(1,0),sf::Vector2i(-1,1),sf::Vector2i(0,1),sf::Vector2i(1,1)};
	uint16_t x = playerPos.x / m_tileSize;
	uint16_t y = playerPos.y / m_tileSize;
	for (size_t i = 0; i < nearTiles.size(); i++) {
		if (m_checker[x + nearTiles.at(i).x][y + nearTiles.at(i).y])
			tiles.push_back(sf::Vector2i((x + nearTiles.at(i).x) * m_tileSize, (y + nearTiles.at(i).y)*m_tileSize));
	}

	return tiles;
}

void tilemap::changeIndex(sf::Event event)
{
	if (event.type == event.MouseWheelScrolled) {

		m_tileIndex += static_cast<int16_t>(event.mouseWheelScroll.delta);
		m_tileIndex = (m_tileIndex % m_tileCount + m_tileCount) % m_tileCount;
	}
}

void tilemap::checkDuplicates(sf::Sprite tile)
{
	for (size_t i = 0; i < m_tiles.size(); i++) {
		if (m_tiles[i].getPosition() == tile.getPosition()) {

			m_tiles[i] = m_tiles.back();
			m_tiles.pop_back();

			break;
		}
	}
}

void tilemap::createTileat(sf::Event event)
{
	if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		
		sf::Sprite& tile = m_tileOptions[m_tileIndex];

		tile.setPosition(m_mouseToTileIndex.x * m_tileSize + m_tileSize/2, m_mouseToTileIndex.y * m_tileSize + m_tileSize/2);
		checkDuplicates(tile);

		m_tiles.push_back(tile);
		m_checker[m_mouseToTileIndex.x][m_mouseToTileIndex.y] = 1;
	}
}

void tilemap::removeTile(sf::Event event)
{
	if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
		for (size_t i = 0; i < m_tiles.size(); i++) {
			if (m_tiles[i].getPosition() == sf::Vector2f(m_mouseToTileIndex.x * m_tileSize + m_tileSize / 2, m_mouseToTileIndex.y * m_tileSize + m_tileSize / 2)) {

				m_tiles.erase(m_tiles.begin() + i);
				m_checker[m_mouseToTileIndex.x][m_mouseToTileIndex.y] = 0;

				break;
			}
		}
	}
}

void tilemap::update(sf::Mouse mouse, sf::RenderWindow& window, sf::Vector2f position, uint16_t size)
{
	m_mousePos.x = std::clamp(mouse.getPosition(window).x, 0, static_cast<int16_t>(window.getSize().x) - 1);
	m_mousePos.y = std::clamp(mouse.getPosition(window).y, 0, static_cast<int16_t>(window.getSize().y) - 1);

	m_mouseToTileIndex = sf::Vector2i(m_mousePos.x / m_tileSize, m_mousePos.y / m_tileSize);

	m_tileOptions[m_tileIndex].setPosition(static_cast<sf::Vector2f>(m_mousePos));
}

void tilemap::render(sf::RenderTarget& window)
{
	window.draw(m_tileOptions[m_tileIndex]);
	for (sf::Sprite tile : m_tiles) {
		window.draw(tile);
	}
}