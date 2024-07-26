#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

struct components {
	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect rect;
};

class visualFX
{
private:
	std::vector<components>* m_entities;
	sf::Clock m_clock;

public:
	visualFX();
	~visualFX();

	void addSprite(const char* filePath, uint32_t rectX, uint32_t rectY, uint32_t posX, uint32_t posY);
	void animation(uint8_t index);
	void update();
	void render(sf::RenderTarget& window);
};

