#include "ParticleSystemManager.h"

ParticleSystemManager::ParticleSystemManager(sf::RenderWindow* window)
{
	m_particlesCount = new sf::Text;
	m_font = new sf::Font;

	m_font->loadFromFile("Fonts/visitor1.ttf");
	m_particlesCount->setFont(*m_font);
	m_particlesCount->setCharacterSize(30);
	m_particlesCount->setString("Particles Count: 0");
	m_particlesCount->setPosition((window->getSize().x - m_particlesCount->getGlobalBounds().width) / 2, 0);
	
}

//ParticleSystemManager::~ParticleSystemManager()
//{
//	/*for (std::size_t i = 0; i < m_particleSystem->size(); ++i)
//		m_particleSystem[i]->~ParticleSystem();
//	m_particleSystem->clear();*/
//
//}

void ParticleSystemManager::Update(sf::Time deltaTime)
{
	int temp = 0;
	for (std::size_t i = 0; i < m_particleSystem.size(); ++i)
	{
		m_particleSystem[i].Update(deltaTime);
		temp += m_particleSystem[i].GetParticleCount();
	}
	particlesCount = temp;
	m_particlesCount->setString("Particles Count: " + std::to_string(particlesCount));
}

void ParticleSystemManager::Draw(sf::RenderWindow* window)
{
	for (std::size_t i = 0; i < m_particleSystem.size(); ++i)
		window->draw(m_particleSystem[i]);
	window->draw(*m_particlesCount);
}

void ParticleSystemManager::AddParticleSystem(sf::Vector2f position)
{
	particleSystemCount += 1;
	m_particleSystem.resize(particleSystemCount);

	m_particleSystem[m_particleSystem.size()-1].SetEmitter(position);
	m_particleSystem[m_particleSystem.size() - 1].SetEmitAngle(rand() % 360);
	m_particleSystem[m_particleSystem.size() - 1].SetInitialSpeed(rand() % 200);
}
