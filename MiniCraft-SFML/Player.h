#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Player : public sf::Drawable
{
private:
    sf::Sprite m_playerSprite;

public:
    Player();
    ~Player();

    void Init(const sf::Texture &texture);
    void Move(const sf::Vector2f& direction);
    bool IsOn(const sf::Sprite &direction);

    sf::Sprite GetSprite();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
