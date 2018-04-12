#include "ParticleSystemManager.h"

ParticleSystemManager::ParticleSystemManager(sf::RenderWindow* window, TextureManager* m_textureManager)
{
	m_particlesCount = new sf::Text;
	m_font = new sf::Font;

	m_font->loadFromFile("Fonts/visitor1.ttf");
	m_particlesCount->setFont(*m_font);
	m_particlesCount->setCharacterSize(24);
	m_particlesCount->setString("Particles Count: 0");
	m_particlesCount->setPosition(window->getSize().x - m_particlesCount->getGlobalBounds().width - 80, 0);
	
	this->m_textureManager = new TextureManager;
	this->m_textureManager = m_textureManager;
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
	std::string easingMode = "";
	for (std::size_t i = 0; i < m_particleSystem.size(); ++i)
	{
		m_particleSystem[i].Update(deltaTime);
		temp += m_particleSystem[i].GetParticleCount();
		easingMode = m_particleSystem[i].GetEasingMode();
	}
	particlesCount = temp;
	m_particlesCount->setString("Particles Count: " + std::to_string(particlesCount) + "\nEasing Mode:" + easingMode);
}

void ParticleSystemManager::Draw(sf::RenderWindow* window)
{
	for (std::size_t i = 0; i < m_particleSystem.size(); ++i)
		window->draw(m_particleSystem[i]);
	window->draw(*m_particlesCount);
}

void ParticleSystemManager::AddParticleSystem(sf::Vector2f position)
{
	ParticleSystem* particleSystemToAdd = new ParticleSystem(m_textureManager);
	particleSystemToAdd->SetEmitter(position);
	particleSystemToAdd->SetEmitAngle(rand() % 360);
	particleSystemToAdd->SetInitialSpeed(rand() % 200);
	m_particleSystem.emplace_back(*particleSystemToAdd);
}
