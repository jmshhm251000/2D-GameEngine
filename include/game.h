#pragma once

#include <player.h>
#include <fire.h>
#include <tilemap.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Game
{
private:

	sf::RenderWindow* m_window;
	sf::Event m_event;
	sf::Clock m_deltaTimer;
	sf::Mouse mouse;

	tilemap m_tileMap;
	Player m_player;
	Fire m_fire;

	void initWindow();

public:

	Game();
	~Game();

	const bool running();

	void pollEvents();
	void update();
	void render();

};

