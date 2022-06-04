#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(const sf::Texture& texture)
{
    m_playerSprite.setTexture(texture);
}

void Player::Move(const sf::Vector2f& direction)
{
    m_playerSprite.setPosition(m_playerSprite.getPosition() + direction);
}

bool Player::IsOn(const sf::Sprite& direction)
{
    return false;
}

sf::Sprite Player::GetSprite()
{
    return m_playerSprite;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_playerSprite);
}
