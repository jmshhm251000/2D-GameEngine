#include "visualFX.h"

visualFX::visualFX()
	: m_entities(new std::vector<components>)
{
	addSprite("resource/Fire+Sparks-Sheet.png", 96, 96, (600 + 150), (250));
}

visualFX::~visualFX()
{
	delete m_entities;
}

void visualFX::addSprite(const char* filePath, uint32_t rectX, uint32_t rectY, uint32_t posX, uint32_t posY)
{
	m_entities->emplace_back();
	if (!m_entities->back().texture.loadFromFile(filePath)) {
		std::cerr << "Error: Failed to load sprite";
	}
	m_entities->back().rect = sf::IntRect(0, 0, rectX, rectY);
	m_entities->back().sprite.setTexture(m_entities->back().texture);
	m_entities->back().sprite.setTextureRect(m_entities->back().rect);
	m_entities->back().sprite.setPosition(sf::Vector2f( posX, posY));
}

void visualFX::animation(uint8_t index)
{
}

void visualFX::update()
{
	animation(0);
}

void visualFX::render(sf::RenderTarget& window)
{
	window.draw(m_entities->at(0).sprite);
}
