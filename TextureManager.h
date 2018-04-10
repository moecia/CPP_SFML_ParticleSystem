#pragma once
#include <SFML/Graphics.hpp>
class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	sf::Texture LoadTexture(int index) const;	
private:
	std::vector<sf::Texture> m_textureLib;
	int textureCount = 3;
};

