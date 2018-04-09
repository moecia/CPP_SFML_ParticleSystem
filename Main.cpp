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
	sf::RenderWindow window(sf::VideoMode(800, 600), "Particle DEMO");

	ParticleSystemManager* m_VFXManager = new ParticleSystemManager(2, &window);
	sf::Clock m_clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		// make the particle system emitter follow the mouse
		//sf::Vector2i mouse = sf::Mouse::getPosition(window);
		//m_particles->SetEmitter(window.mapPixelToCoords(mouse));

		// update it
		sf::Time elapsed = m_clock.restart();
		m_VFXManager->Update(elapsed);

		// draw it
		window.clear();
		m_VFXManager->Draw(&window);
		window.display();
	}

	return 0;
}
