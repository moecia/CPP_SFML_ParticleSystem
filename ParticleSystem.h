#include <SFML/Graphics.hpp>
#include "TextureManager.h"

#pragma once
class ParticleSystem : public sf::Drawable, public sf::Transformable
{
	enum easing
	{
		liner,
		quad,
		cube,
		sin,
		quar
	};
public:
	ParticleSystem(TextureManager* m_textureManager);
	//~ParticleSystem();
	void Update(sf::Time deltaTime);
	void SetEmitter(sf::Vector2f position);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	int GetParticleCount();
	std::string GetEasingMode();
	void SetEmitAngle(int angle);
	void SetInitialSpeed(float initialSpeed);
private:
	float timer = 0;
	easing currentEasing = liner;
	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
		sf::Vector2f size;
		float growsSpeed;
		float rotation;
		sf::Time timePassed;
		float angle;
		float velAcc;
		float rotAcc;
	};
	float p_lifetime = 6000.0f;
	void ResetParticle(std::size_t index);
	float QuarticEasing(sf::Time timePassed);
	float CubeEasing(sf::Time timePassed);
	float QuadEasing(sf::Time timePassed);
	float SinEasing(sf::Time timePassed);

	std::vector<Particle> m_particles;
	std::vector<sf::CircleShape> m_shapes;
	sf::Texture m_texture;

	sf::Time m_emiterLifetime;
	sf::Vector2f m_emitter;

	int emiterAngle = 360;
	float initialSpeed = 500;
	int count = 500;

};

