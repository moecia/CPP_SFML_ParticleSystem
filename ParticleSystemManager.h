#pragma once
#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"

class ParticleSystemManager
{
public:
	ParticleSystemManager(sf::RenderWindow* window);
	//~ParticleSystemManager();
	void Update(sf::Time deltaTime);
	void Draw(sf::RenderWindow* window);
	void AddParticleSystem(sf::Vector2f position);
private:
	std::vector<ParticleSystem> m_particleSystem;
	int particleSystemCount = 0;
	sf::Text* m_particlesCount = new sf::Text;
	sf::Font* m_font = new sf::Font;
	int particlesCount = 0;
};

