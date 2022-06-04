#include "GamePlay.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include "GameTile.h"

GamePlay::GamePlay(std::shared_ptr<Context>& context)
    : m_context(context),
    m_playerDirection({ 16.f, 0.f }),
    m_char("assets/sprites/icons.png", 16, 16, 4, false, false),
    m_elapsedTime(sf::Time::Zero)
{
}

GamePlay::~GamePlay() = default;

float GamePlay::ScreenToWorldX(const int i) const
{
    const float j = (i - m_offsetX) / m_tileSize;
    return j;
}

float GamePlay::ScreenToWorldY(const int i) const
{
    const float j = (i - m_offsetY) / (m_tileSize);
    return j;
}

float GamePlay::WorldToScreenX(const int i) const
{
    const float j = m_offsetX + (m_tileSize * i);
    return j;
}

float GamePlay::WorldToScreenY(const int i) const
{
    const float j = m_offsetY + (m_tileSize * i);
    return j;
}

void GamePlay::Init()
{


    m_context->m_assets->AddTexture(GRASS, "assets/sprites/tiles-color.png", 24, 48);
    m_context->m_assets->AddTexture(SAND, "assets/sprites/tiles-color.png", 64, 32);
    m_context->m_assets->AddTexture(WATER, "assets/sprites/tiles-color.png", 24, 24);

    m_context->m_assets->AddTexture(PLAYER, "assets/sprites/char.png", 0, 0, false, 128);

    //m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
    //m_grass.setScale(10, 10);
    //m_grass.setPosition(sf::Vector2f(0, 0));
    ////m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    //m_sand.setTexture(m_context->m_assets->GetTexture(SAND));
    //m_sand.setScale(10, 10);
    //m_sand.setPosition(sf::Vector2f(160, 0));

    //m_water.setTexture(m_context->m_assets->GetTexture(WATER));
    //m_water.setScale(10, 10);
    //m_water.setPosition(sf::Vector2f(320, 0));

    /*for (auto& wall : m_walls)
    {
        wall.setTexture(m_context->m_assets->GetTexture(SAND));
    }

    m_walls[0].setTextureRect(sf::IntRect(0, 0, 854, 16));*/

    m_seed = 1335;
    m_waterLevel = 0.99;

    m_heightNoise.SetSeed(m_seed);
    m_heightNoise.SetFrequency(0.02);
    m_heightNoise.SetNoiseType(FastNoise::PerlinFractal);

    m_heightNoise2.SetSeed(m_seed);
    m_heightNoise2.SetFrequency(0.002);
    m_heightNoise2.SetNoiseType(FastNoise::PerlinFractal);
    m_testVecMotherFucker = MakeWorld();

    //todo CAMERA VIEW
    //m_camera_controller->init(sf::Vector2f(400, 400), sf::Vector2f(200, 200));
    m_cameraController = camera_controller(sf::Vector2f(100, 100), sf::Vector2f(200, 200));

    m_player.Init(m_context->m_assets->GetTexture(PLAYER));
    m_player.GetSprite().setPosition(sf::Vector2f(150, 150));

    m_char.getSpriteObj().setPosition(sf::Vector2f(150, 150));
}

void GamePlay::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        m_storedEvent = event;

        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }

        if (event.type == sf::Event::KeyPressed)
        {

            switch (event.key.code)
            {
            case sf::Keyboard::W:
                m_playerDirection = { 0.f, -16.f };
                break;
            case sf::Keyboard::S:
                m_playerDirection = { 0.f, 16.f };
                break;
            case sf::Keyboard::A:
                m_playerDirection = { -16.f, 0.f };
                break;
            case sf::Keyboard::D:
                m_playerDirection = { 16.f, 0.f };
                break;

            }
            HandleKeyPress(event.key.code);
        }
    }
}

void GamePlay::Update(sf::Time deltaTime)
{
    m_elapsedTime += deltaTime;

    if (m_elapsedTime.asSeconds() > 0.1)
    {
        //m_player.Move(m_playerDirection);
        m_elapsedTime = sf::Time::Zero;
        m_char.charMove();
    }

    // below should move
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        //cameraView.zoom(1.0005f);
        std::cout << "zoom in" << std::endl;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        std::cout << "zoom out" << std::endl;
    //cameraView.zoom(-0.0005f);

//switch (storedEvent.key.code)

//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//{
//	cameraView.move(0, -1.0f);
//}

//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//{
//	cameraView.move(0, +1.0f);
//}

//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//{
//	cameraView.move(-1.0f, 0);
//}

//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//{
//	cameraView.move(1.0f, 0);
//}

}

void GamePlay::HandleKeyPress(const sf::Keyboard::Key keycode)
{
    ////std::cout << "Event: " << event.key.code << std::endl;
    ////m_camera_controller->move_camera_controller(sf::Keyboard());
    //switch (keycode)
    //{
    //case sf::Keyboard::W:
    //    m_playerDirection = { 0.f, 16.f };
    //}
}


void GamePlay::Draw()
{
    m_context->m_window->clear();

    m_context->m_window->setView(m_cameraController.m_cameraView);

    for (auto& sprite : m_testVecMotherFucker)
    {
        m_context->m_window->draw(sprite);
    }

    //m_context->m_window->draw(m_player.GetSprite());
    m_context->m_window->draw(m_char.getSpriteObj());

    m_context->m_window->display();
}


void GamePlay::Pause()
{
}

void GamePlay::Start()
{
}

std::vector<sf::Sprite> GamePlay::MakeWorld() const
{
    //sprites
    sf::Sprite tile;
    std::vector<sf::Sprite> tilesVec;
    constexpr int maxHeight = 1000 / 16;

    for (int x = 0; x < maxHeight; x++) { //int x = -offsetX / tileSize - cameraView.getSize().x / tileSize / 2 + 1; x < visibleTilesX - offsetX / tileSize + cameraView.getSize().x / tileSize / 2 + 1; x++
        for (int y = 0; y < maxHeight; y++) { //int y = -offsetY / tileSize - cameraView.getSize().y / tileSize / 2 + 1; y < visibleTilesY - offsetY / tileSize + cameraView.getSize().y / tileSize / 2 + 1; y++
            float tileHeight = m_heightNoise.GetNoise(x, y);
            tileHeight += 1;
            //std::cout << "TILE HEIGHT: " << tileHeight << "\n";
            if (tileHeight > m_waterLevel && tileHeight >= m_waterLevel + 0.05) {
                tile.setTexture(m_context->m_assets->GetTexture(SAND));
                //std::cout << "sand" << std::endl;
            }
            else if (tileHeight > m_waterLevel) {
                tile.setTexture(m_context->m_assets->GetTexture(GRASS));
                //std::cout << "grass" << std::endl;
            }
            else {
                tile.setTexture(m_context->m_assets->GetTexture(WATER));
                //std::cout << "water" << std::endl;
            }
            tile.setPosition(WorldToScreenX(x), WorldToScreenY(y));

            tileHeight = -abs(tileHeight - m_waterLevel);
            tileHeight += 1;
            tileHeight *= 10;
            tileHeight = floor(tileHeight);
            tileHeight *= 15;
            tileHeight += 119;

            tile.setColor(sf::Color(tileHeight, tileHeight, tileHeight));
            //std::cout << tile.getPosition().x << tile.getPosition().y <<" DONE!" << std::endl;
            tilesVec.emplace_back(tile);
        }
    }
    return tilesVec;
}
