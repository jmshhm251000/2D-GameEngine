#include <game.h>

Game::Game()
	: m_window(nullptr), m_view(sf::Vector2f(0.f,0.f), sf::Vector2f( SCREEN_WIDTH, SCREEN_HEIGHT)), m_tileMap("resource/tilemap.png", 35)
{
	initWindow();
}

Game::~Game()
{
	delete m_window;
}

void Game::initWindow()
{
	m_window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "2D GameEngine", sf::Style::Titlebar | sf::Style::Close);
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
		m_player.keyListener(m_event);
		m_tileMap.changeIndex(m_event);
		m_tileMap.createTileat(m_event);
		m_tileMap.removeTile(m_event);
	}
}

void Game::update()
{
	sf::Time elapsedTimePerFrame = m_deltaTimer.getElapsedTime();
	float deltaTimeFloat = m_deltaTimer.getElapsedTime().asSeconds();
	uint32_t deltaTime = elapsedTimePerFrame.asMilliseconds();

	pollEvents();
	m_player.update(deltaTimeFloat, m_tileMap.nearTiles(m_player.getPos()));
	m_fire.update(deltaTimeFloat);
	m_tileMap.update(mouse, *m_window, m_player.getPos(), 64);
	m_deltaTimer.restart();
}


void Game::render()
{
	m_window->clear();

	m_tileMap.render(*m_window);
	m_player.render(*m_window);
	m_fire.render(*m_window);

	m_window->display();
}