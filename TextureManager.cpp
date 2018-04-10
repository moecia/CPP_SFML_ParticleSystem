#include "TextureManager.h"


TextureManager::TextureManager()
{
	// TODO: Procedurally add file
	m_textureLib.resize(textureCount);
	for (int i = 0; i < textureCount; i++)
	{
		switch (i)
		{
			case 0:
				if (!m_textureLib[0].loadFromFile("Images/Smoke.png"))
					return;
				break;
			case 1:
				if (!m_textureLib[1].loadFromFile("Images/Water.png"))
					return;
				break;
			case 2:
				if (!m_textureLib[2].loadFromFile("Images/Star.png"))
					return;
				break;
		}
	}
}

sf::Texture TextureManager::LoadTexture(int index) const
{
	if (index > textureCount) { return m_textureLib[0]; }
	return m_textureLib[index];
}

TextureManager::~TextureManager()
{
}
