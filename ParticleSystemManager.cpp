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

ParticleSystemManager::~ParticleSystemManager()
{

}

void ParticleSystemManager::Update(sf::Time deltaTime)
{
	SetEasingMode();

	std::string easingMode = "";
	switch (currentEasing)
	{
		case ParticleSystem::easing::quad:
			easingMode = "Quadratic";
			break;
		case ParticleSystem::easing::cube:
			easingMode = "Cubic";
			break;
		case ParticleSystem::easing::quar:
			easingMode = "Quartic";
			break;
		case ParticleSystem::easing::sin:
			easingMode = "Sinusoidal";
			break;
		case ParticleSystem::easing::liner:
			easingMode = "Liner";
			break;
	}

	int temp = 0;

	for (std::size_t i = 0; i < m_particleSystem.size(); ++i)
	{
		if (m_particleSystem[i].GetEasingMode() != currentEasing)
			m_particleSystem[i].SetEasingMode(currentEasing);
		m_particleSystem[i].Update(deltaTime);
		temp += m_particleSystem[i].GetParticleCount();
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
	particleSystemToAdd->SetEasingMode(currentEasing);
	particleSystemToAdd->SetEmitter(position);
	particleSystemToAdd->SetEmitAngle(rand() % 360);
	particleSystemToAdd->SetInitialSpeed(rand() % 200);
	m_particleSystem.emplace_back(*particleSystemToAdd);
}

void ParticleSystemManager::SetEasingMode()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { currentEasing = ParticleSystem::easing::quad; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { currentEasing = ParticleSystem::easing::cube; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) { currentEasing = ParticleSystem::easing::quar; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) { currentEasing = ParticleSystem::easing::sin; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) { currentEasing = ParticleSystem::easing::liner; }
}
