#include "Game.h"

Game::Game()
	: m_player(new Player), m_window(nullptr)
{
	initWindow();
}

Game::~Game()
{
	delete m_window;
	delete m_player;
}

void Game::initWindow()
{
	m_window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
	m_window->setVerticalSyncEnabled(true);
}


const bool Game::running()
{
	return m_window->isOpen();
}

void Game::pollEvents()
{
	while (m_window->pollEvent(m_event)) {
		if (m_event.type == sf::Event::Closed)
			m_window->close();
		m_player->keyListener(m_event);
	}
}

void Game::update()
{
	sf::Time elapsedTimePerFrame = m_deltaTimer.getElapsedTime();

	float deltaTime = elapsedTimePerFrame.asMilliseconds();
	pollEvents();
	m_player->update(deltaTime);
	m_vfx.update();

	m_deltaTimer.restart();
}


void Game::render()
{
	m_window->clear();

	m_player->render(*m_window);
	m_vfx.render(*m_window);

	m_window->display();
}