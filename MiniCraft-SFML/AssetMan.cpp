#include "AssetMan.h"

Engine::AssetMan::AssetMan()
= default;

Engine::AssetMan::~AssetMan()
= default;

void Engine::AssetMan::AddTexture(const int id, const std::string filePath, const int x, const int y, const bool wantRepeated, const int size)
{
    auto texture = std::make_unique<sf::Texture>();

    // load a rectangle that starts at (10, 10) of size 32x32
    if (texture->loadFromFile(filePath, sf::IntRect(x, y, size, size)))
    {
        texture->setRepeated(wantRepeated);
        //texture->setSmooth(true);
        m_textures[id] = std::move(texture);
    }
}

void Engine::AssetMan::AddFont(const int id, const std::string& filePath)
{
    auto font = std::make_unique<sf::Font>();

    if (font->loadFromFile(filePath))
    {
        m_fonts[id] = std::move(font);
    }
}

const sf::Texture& Engine::AssetMan::GetTexture(int id) const
{
    //*() for DE-reference pointer 
    return *(m_textures.at(id).get());
}

const sf::Font& Engine::AssetMan::GetFont(int id) const
{
    return *(m_fonts.at(id).get());
}