#include "ParticleSystemManager.h"

ParticleSystemManager::ParticleSystemManager(int count, sf::Window* window)
{
	particleSystemCount = count;
	m_particleSystem.resize(2);

	for (std::size_t i = 0; i < m_particleSystem.size(); ++i)
	{
		sf::Vector2f fixedPosition;
		fixedPosition.x = i * window->getSize().x / particleSystemCount + 200;
		fixedPosition.y = window->getSize().x / 4 ;
		m_particleSystem[i].SetEmitter(fixedPosition);
	}
}


//ParticleSystemManager::~ParticleSystemManager()
//{
//	/*for (std::size_t i = 0; i < m_particleSystem->size(); ++i)
//		m_particleSystem[i]->~ParticleSystem();
//	m_particleSystem->clear();*/
//
//}

void ParticleSystemManager::Update(sf::Time elapsed)
{
	for (std::size_t i = 0; i < m_particleSystem.size(); ++i)
		m_particleSystem[i].Update(elapsed);
}

void ParticleSystemManager::Draw(sf::RenderWindow* window)
{
	for (std::size_t i = 0; i < m_particleSystem.size(); ++i)
		window->draw(m_particleSystem[i]);
}
