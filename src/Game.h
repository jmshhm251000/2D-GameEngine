#pragma once

#include "Player.h"
#include "visualFX.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

class Game
{
private:

	sf::RenderWindow* m_window;
	sf::Event m_event;

	Player* m_player;
	visualFX m_vfx;

	sf::Clock m_deltaTimer;

	void initWindow();

public:

	Game();
	~Game();

	const bool running();

	void pollEvents();
	void update();
	void render();

};

