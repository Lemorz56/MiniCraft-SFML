#pragma once
#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Engine
{
	class AssetMan
	{
	private:
		std::map<int, std::unique_ptr<sf::Texture>> m_textures;
		std::map<int, std::unique_ptr<sf::Font>> m_fonts;

	public:
		AssetMan();
		~AssetMan();
		
		void AddTexture(int id, std::string filePath, int x = 0, int y = 0, bool wantRepeated = false, int size = 16);
		void AddFont(int id, const std::string& filePath);

		const sf::Texture& GetTexture(int id) const;
		const sf::Font& GetFont(int id) const;
	};
}

