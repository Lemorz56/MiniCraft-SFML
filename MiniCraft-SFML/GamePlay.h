#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <array>
#include "fastNoise/FastNoise.h"
#include "State.h"
#include "Game.h"
#include "GameWorld.h"
#include "CameraController.h"
#include "Character.h"
#include "Player.h"
// Now use the C++ SFML TileMap tutorial on YT?

class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;

    std::array<sf::Sprite, 4> m_walls;

    // SPRITES
    sf::Sprite m_character;
    sf::Sprite m_grass;
    sf::Sprite m_sand;
    sf::Sprite m_water;

    Player m_player;
    sf::Vector2f m_playerDirection;

    Character m_char;

        std::vector<sf::Sprite> m_testVecMotherFucker;
    GameWorld m_gameWorld;

    sf::Time m_elapsedTime;

    // WORLD
    float m_seed;
    float m_waterLevel;

    // NOISE
    FastNoise m_heightNoise;
    FastNoise m_heightNoise2;



    // VIEWS / CAMERA
    //sf::FloatRect floatRect = sf::FloatRect(0.f, 0.f, m_context->m_window->getSize().x, m_context->m_window->getSize().y);

    /* OLD VIEW */
    //sf::View cameraView = sf::View(sf::Vector2f(400, 400), sf::Vector2f(200, 200));

    // MORE CRAP
    // what
    //tiles
    int m_tileSize = 16;
    int m_visibleTilesX = ceil(m_context->m_window->getSize().x / m_tileSize);
    int m_visibleTilesY = ceil(m_context->m_window->getSize().y / m_tileSize);

    float m_offsetX = 0;
    float m_offsetY = 0;

    //functions
    float ScreenToWorldX(int i) const;
    float ScreenToWorldY(int i) const;
    float WorldToScreenX(int i) const;
    float WorldToScreenY(int i) const;

public:
    GamePlay(std::shared_ptr<Context>& context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;

    static void HandleKeyPress(const sf::Keyboard::Key keycode);

    std::vector<sf::Sprite> MakeWorld() const;
    sf::Sprite m_testSprite;

    //std::shared_ptr<camera_controller> m_camera_controller;
    camera_controller m_cameraController;
};
