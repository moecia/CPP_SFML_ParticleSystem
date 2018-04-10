#include "ParticleSystem.h"


ParticleSystem::ParticleSystem(TextureManager* m_textureManager)
{
	m_particles.resize(count);
	m_shapes.resize(count);
	m_emiterLifetime = sf::seconds(3);
	m_emitter.x = 0;
	m_emitter.y = 0;

	if (rand() % 3 == 0)
		m_texture = m_textureManager->LoadTexture(0);

	if (rand() % 3 == 1)
		m_texture = m_textureManager->LoadTexture(1);

	if (rand() % 3 == 2)
		m_texture = m_textureManager->LoadTexture(2);

	for (int i = 0; i < m_shapes.size(); i++)
	{
		m_shapes[i].setRadius(rand() % 10);
		m_shapes[i].setTexture(&m_texture);
		m_shapes[i].setTextureRect(sf::IntRect(0, 0, 56, 56));
	}

}

//ParticleSystem::~ParticleSystem()
//{
//	m_particles.clear();
//}

void ParticleSystem::SetEmitter(sf::Vector2f position)
{
	m_emitter = position;
}

void ParticleSystem::Update(sf::Time deltaTime)
{
	/*if (m_textureManager && !isTextureSet)
	{
		if (rand() % 3 == 0)
			m_texture = m_textureManager->LoadTexture(0);

		if (rand() % 3 == 1)
			m_texture = m_textureManager->LoadTexture(1);

		if (rand() % 3 == 2)
			m_texture = m_textureManager->LoadTexture(2);
	
		for (int i = 0; i < m_shapes.size(); i++)
		{
			m_shapes[i].setRadius(rand() % 10);
			m_shapes[i].setTexture(&m_texture);
			m_shapes[i].setTextureRect(sf::IntRect(0, 0, 56, 56));
		}
		isTextureSet = true;
	}*/

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

		// if the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero)
			ResetParticle(i);

		// update the position of the corresponding shapes
		sf::Vector2f lastFramePos = m_shapes[i].getPosition();
		sf::Vector2f newPos = lastFramePos + p.velocity * deltaTime.asSeconds();
		m_shapes[i].setPosition(newPos);

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
	m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

	// Spraying effect
	//m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

	// Firework effect
	m_particles[index].lifetime = sf::milliseconds(3000);
	// reset the position of the corresponding vertex

	//m_shapes[index].position = m_emitter;
	m_shapes[index].setPosition(m_emitter);
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

