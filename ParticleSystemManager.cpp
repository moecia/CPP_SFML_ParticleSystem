#include "ParticleSystemManager.h"

ParticleSystemManager::ParticleSystemManager()
{
	/*particleSystemCount = count;
	m_particleSystem->resize(2);

	for (std::size_t i = 0; i < m_particleSystem->size(); ++i)
	{
		sf::Vector2f fixedPosition;
		fixedPosition.x = window->getSize().x / particleSystemCount;
		fixedPosition.y = window->getSize().x / 2;
		m_particleSystem[i]->SetEmitter(fixedPosition);
	}*/

	m_particleSystem_0 = new ParticleSystem();
	m_particleSystem_1 = new ParticleSystem();
	m_particleSystem_0->SetEmitter(sf::Vector2f(150,150));
	m_particleSystem_1->SetEmitter(sf::Vector2f(100, 100));
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
	/*for (std::size_t i = 0; i < m_particleSystem->size(); ++i)
		m_particleSystem[i]->Update(elapsed);*/
	m_particleSystem_0->Update(elapsed);
	m_particleSystem_1->Update(elapsed);
}

void ParticleSystemManager::Draw(sf::RenderWindow* window)
{
	/*for (std::size_t i = 0; i < m_particleSystem->size(); ++i)
		window->draw(m_particleSystem[i]);*/
	window->draw(*m_particleSystem_0); 
	window->draw(*m_particleSystem_1);
}
