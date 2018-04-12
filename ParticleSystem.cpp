#include "ParticleSystem.h"
#include <math.h>
#define PI 3.1415926

ParticleSystem::ParticleSystem(TextureManager* m_textureManager)
{
	m_particles.resize(count);
	m_shapes.resize(count);
	m_emiterLifetime = sf::seconds(6);
	m_emitter.x = 0;
	m_emitter.y = 0;
	if (rand() % 4 == 0)
		m_texture = m_textureManager->LoadTexture(0);

	if (rand() % 4 == 1)
		m_texture = m_textureManager->LoadTexture(1);

	if (rand() % 4 == 2)
		m_texture = m_textureManager->LoadTexture(2);

	if (rand() % 4 == 3)
		m_texture = m_textureManager->LoadTexture(3);

	for (int i = 0; i < m_shapes.size(); i++)
	{
		m_shapes[i].setRadius(rand() % 10);
		m_shapes[i].setTexture(&m_texture);
		m_shapes[i].setTextureRect(sf::IntRect(0, 0, 56, 56));
	}
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::SetEmitter(sf::Vector2f position)
{
	m_emitter = position;
}

void ParticleSystem::Update(sf::Time deltaTime)
{
	if (timer < .5f)
		timer += deltaTime.asSeconds();
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			count += 100;
			m_particles.resize(count);
			m_shapes.resize(count);
			timer = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if (count > 100)
			{
				for (int i = 0; i < 100; i++)
				{
					m_particles.pop_back();
					m_shapes.pop_back();
				}
				count -= 100;
				m_particles.resize(count);
				m_shapes.resize(count);
				timer = 0;
			}
		}

	}

	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= deltaTime;	
		p.timePassed += deltaTime;

		// if the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero)
			ResetParticle(i);

		// Set acceleration

		switch (currentEasing)
		{
			case quad: 
				p.velAcc = QuadEasing(p.timePassed) / 10 + p.velAcc;
				p.growsSpeed = QuadEasing(p.timePassed) / 10 + p.growsSpeed;
				p.rotAcc = QuadEasing(p.timePassed) + p.rotAcc;
				break;
			case cube:
				p.velAcc = CubeEasing(p.timePassed) / 10 + p.velAcc;
				p.growsSpeed = CubeEasing(p.timePassed) / 10 + p.growsSpeed;
				p.rotAcc = CubeEasing(p.timePassed) + p.rotAcc;
				break;
			case quar:
				p.velAcc = QuarticEasing(p.timePassed) / 10 + p.velAcc;
				p.growsSpeed = QuarticEasing(p.timePassed) / 10 + p.growsSpeed;
				p.rotAcc = QuarticEasing(p.timePassed)  + p.rotAcc;
				break;
			case sin:
				p.velAcc = SinEasing(p.timePassed) / 100 + p.velAcc;
				p.growsSpeed = SinEasing(p.timePassed) / 100 + p.growsSpeed;
				p.rotAcc = SinEasing(p.timePassed) / 10 + p.rotAcc;
				break;
			case liner:
				p.velAcc = 0;
				p.growsSpeed = 0;
				p.rotAcc = 0;
				break;
		}

 
		// update the position of the corresponding shapes
		p.velocity += sf::Vector2f(p.velAcc * deltaTime.asMilliseconds() * std::cos(p.angle), p.velAcc * deltaTime.asMilliseconds() * std::sin(p.angle));
		sf::Vector2f lastFramePos = m_shapes[i].getPosition();
		sf::Vector2f newPos = lastFramePos + p.velocity * deltaTime.asSeconds();
		m_shapes[i].setPosition(newPos);

		// update the size of the corresponding shapes
		if(currentEasing == sin )
			p.size += sf::Vector2f(p.growsSpeed * deltaTime.asSeconds(), p.growsSpeed * deltaTime.asSeconds());
		else
			p.size -= sf::Vector2f(p.growsSpeed * deltaTime.asSeconds(), p.growsSpeed * deltaTime.asSeconds());
		m_shapes[i].setScale(p.size);

		// update the angle of the corresponding shapes
		p.rotation += p.rotAcc * deltaTime.asSeconds();
		m_shapes[i].rotate(p.rotation);

		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime.asSeconds() / m_emiterLifetime.asSeconds();
		m_shapes[i].setFillColor(sf::Color(255,255,255, static_cast<sf::Uint8>(ratio * 255)));	
	}
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// Set texture
	states.texture = &m_texture;
	
	// draw the vertex array
	for(int i =0; i < m_shapes.size(); i++)
		target.draw(m_shapes[i], states);
}

void ParticleSystem::ResetParticle(std::size_t index)
{
	// give a random velocity and lifetime to the particle
	float angle = std::rand() % emiterAngle * 3.14f / 180.f;
	float speed = (std::rand() % 50) + initialSpeed;

	// Set timer to zero
	m_particles[index].timePassed = sf::Time::Zero;
	// Set initial velocity
	m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	
	// Set initial angle
	m_particles[index].angle = angle;

	// Set initial rotation
	m_particles[index].rotation = 0;

	// Set initial velocity acceleration
	m_particles[index].velAcc = 0;

	// Set initial rotation acceleration
	m_particles[index].rotAcc = 0;

	// Set initial grow speed
	m_particles[index].growsSpeed = 0;

	// Reset particle scale
	m_particles[index].size = sf::Vector2f(1.0f, 1.0f);
	m_shapes[index].setScale(m_particles[index].size);

	// Spraying effect
	//m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

	// Firework effect
	m_particles[index].lifetime = sf::milliseconds(p_lifetime);

	// Reset particle position
	m_shapes[index].setPosition(m_emitter);


}

float ParticleSystem::QuarticEasing(sf::Time timePassed)
{
	float t = timePassed.asMilliseconds();
	t /= p_lifetime;
	return .1f * (std::pow(t, 4) + .1f);
}

float ParticleSystem::CubeEasing(sf::Time timePassed)
{
	float t = timePassed.asMilliseconds();
	t /= p_lifetime;
	return .01f * (std::pow(t, 3) + .01f);
}

float ParticleSystem::QuadEasing(sf::Time timePassed)
{
	float t = timePassed.asMilliseconds();
	t /= p_lifetime;
	return .001f * (std::pow(t, 2) + .001f);
}

float ParticleSystem::SinEasing(sf::Time timePassed)
{
	//return -c / 2 * (Math.cos(Math.PI*t / d) - 1) + b;
	float t = timePassed.asMilliseconds();
	t /= p_lifetime;
	return -.1f/2 * std::cos(t * PI - 1);
}

int ParticleSystem::GetParticleCount()
{
	return count;
}

void ParticleSystem::SetEmitAngle(int emiterAngle)
{
	this->emiterAngle = emiterAngle;
}

void ParticleSystem::SetInitialSpeed(float initialSpeed)
{
	this->initialSpeed = initialSpeed;
}

void ParticleSystem::SetEasingMode(easing easingMode)
{
	currentEasing = easingMode;
}

ParticleSystem::easing ParticleSystem::GetEasingMode()
{
	return currentEasing;
}



