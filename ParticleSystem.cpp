#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	m_particles.resize(count);
	m_shapes.resize(count);
	m_shapes.setPrimitiveType(sf::Points);
	m_lifetime = sf::seconds(3);
	m_emitter.x = 0;
	m_emitter.y = 0;
}

//ParticleSystem::~ParticleSystem()
//{
//	m_particles.clear();
//}

//void ParticleSystem::SetTexture()
//{
//	if (!isTextureSet)
//	{
//		if (!m_texture.loadFromFile("Images/ParticleFirecloud.png"))
//			return;
//	}
//	isTextureSet = true;
//}

void ParticleSystem::SetEmitter(sf::Vector2f position)
{
	m_emitter = position;
}

void ParticleSystem::Update(sf::Time elapsed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		count += 1000;
		m_particles.resize(count);
		m_shapes.resize(count);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		if (count > 100)
		{
			count -= 100;
			m_particles.resize(count);
			m_shapes.resize(count);
		}
	}

	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= elapsed;

		// if the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero)
			ResetParticle(i);

		// update the position of the corresponding shapes
		m_shapes[i].position += p.velocity * elapsed.asSeconds();

		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
		m_shapes[i].color.a = static_cast<sf::Uint8>(ratio * 255);
	}
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// Set texture
		
	//states.texture = NULL;
	states.texture = NULL;

	// draw the vertex array
	target.draw(m_shapes, states);
}

void ParticleSystem::ResetParticle(std::size_t index) 
{
	// give a random velocity and lifetime to the particle
	float angle = (std::rand() % 360) * 3.14f / 180.f;
	float speed = (std::rand() % 50) + 50.f;
	m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

	// reset the position of the corresponding vertex
	m_shapes[index].position = m_emitter;
}

int ParticleSystem::GetParticleCount()
{
	return count;
}
