#include "Game.h"
#include "MainMenu.h"


Game::Game() : m_context(std::make_shared<Context>())
{
    // 480p - 854 x 480
    // ??? - 1600 x 900
    // 1600, 900
	m_context->m_window->create(sf::VideoMode(800, 800), "Minicraft", sf::Style::Close);
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
}

Game::~Game()
{

}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;
    m_context->m_window->setFramerateLimit(60);

    while (m_context->m_window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;

            m_context->m_states->ProcessStateChange();
            m_context->m_states->GetCurrent()->ProcessInput();
            m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
            m_context->m_states->GetCurrent()->Draw();
        }
    }
}