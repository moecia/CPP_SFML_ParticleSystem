#include <SFML/Graphics.hpp>
#pragma once
class ParticleSystem : public sf::Drawable, public sf::Transformable
{
	
public:
	ParticleSystem();
	//~ParticleSystem();
	int GetParticleCount();	
	void Update(sf::Time elapsed);
	void SetEmitter(sf::Vector2f position);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
private:
	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
	};

	void ResetParticle(std::size_t index);

	std::vector<Particle> m_particles;
	//std::vector<sf::RectangleShape> m_shapes;
	sf::VertexArray m_shapes;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;
	sf::Texture m_texture;
	int count = 1000;

	//bool isTextureSet = false;
};

