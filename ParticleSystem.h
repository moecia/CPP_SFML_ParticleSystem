#include <SFML/Graphics.hpp>
#include "TextureManager.h"

#pragma once
class ParticleSystem : public sf::Drawable, public sf::Transformable
{
	
public:
	ParticleSystem(TextureManager* m_textureManager);
	//~ParticleSystem();
	void Update(sf::Time deltaTime);
	void SetEmitter(sf::Vector2f position);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	int GetParticleCount();
	void SetEmitAngle(int angle);
	void SetInitialSpeed(float initialSpeed);
private:
	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
	};
	void ResetParticle(std::size_t index);
	std::vector<Particle> m_particles;
	std::vector<sf::CircleShape> m_shapes;
	sf::Time m_emiterLifetime;
	sf::Vector2f m_emitter;
	sf::Texture m_texture;
	int count = 500;
	float timer = 0;
	int emiterAngle = 360;
	float initialSpeed = 50;
	bool isTextureSet = false;
};

