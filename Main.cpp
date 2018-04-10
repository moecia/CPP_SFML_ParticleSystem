#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include "ParticleSystemManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Particle DEMO");

	//ParticleSystemManager* m_VFXManager = new ParticleSystemManager(2, &window);
	ParticleSystemManager* m_VFXManager = new ParticleSystemManager(&window);
	sf::Text* m_guild = new sf::Text;
	sf::Font* m_font = new sf::Font;
	m_font->loadFromFile("Fonts/visitor1.ttf");
	m_guild->setFont(*m_font);
	m_guild->setCharacterSize(30);
	m_guild->setString("E: Add particles \nQ: Remove particles");
	m_guild->setPosition(10, 10);

	sf::Clock m_clock;
	sf::Clock m_timer;
	float timer = 0.8f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		if (timer < 1.0f)
			timer += m_timer.restart().asSeconds();
		else
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mouse = sf::Mouse::getPosition(window);
				m_VFXManager->AddParticleSystem((sf::Vector2f)mouse);
				timer = 0;
			}
		}

		// update it
		sf::Time deltaTime = m_clock.restart();
		m_VFXManager->Update(deltaTime);

		// draw it
		window.clear();
		m_VFXManager->Draw(&window);
		window.draw(*m_guild);
		window.display();
	}

	return 0;
}
