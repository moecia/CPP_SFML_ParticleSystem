#pragma once
#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"

class ParticleSystemManager
{
public:
	ParticleSystemManager();
	//~ParticleSystemManager();
	void Update(sf::Time elapsed);
	void Draw(sf::RenderWindow* window);
private:
	//std::vector<ParticleSystem> m_particleSystem;
	ParticleSystem* m_particleSystem_0;
	ParticleSystem* m_particleSystem_1;
	int particleSystemCount;
};

