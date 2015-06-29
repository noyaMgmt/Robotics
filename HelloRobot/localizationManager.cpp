/*
 * localizationManager.cpp
 */

#include "localizationManager.h"
#include "Robot.h"
#include "Map.h"
#include "Particle.h"
#include "Point.h"
#include "config.h"

localizationManager::localizationManager(Robot* robot) : m_particles(), m_robot(robot), m_particles_num(1)
{
	m_particles.push_back(new Particle(Point(0,0),0,1,new Map()));
}

void localizationManager::Update(double deltaX, double deltaY, double deltaYaw)
{
	double maxBelief = 0;
	Particle* bestParticle = NULL;

	// If there are no particles
	if (m_particles_num == 0)
	{
		this->AddParticle(new Particle(Point(0,0),0,1,new Map()));
	}

	for (int currParticle = 0; currParticle < m_particles_num; ++currParticle)
	{
		// Update the particle according to robot's movement
		m_particles[currParticle]->update(Point(deltaX, deltaY), deltaYaw, m_robot);

		double particleBelief = m_particles[currParticle]->getBelief();

		// Too low
		if (particleBelief < 0.2)
		{
			DeleteParticle(currParticle);
		}
		else
		{
			if (maxBelief < particleBelief)
			{
				maxBelief = particleBelief;
				bestParticle = m_particles[currParticle];
			}
		}
	}

	if (m_particles_num < PARTICLES_MIN)
	{
		AddParticle(bestParticle->CreateParticle());
	}

	// Print the map of the best particle
	bestParticle->getMap()->printMap();
}

bool localizationManager::AddParticle(Particle* par)
{
	if (m_particles_num < PARTICLES_MAX)
	{
		m_particles.push_back(par);
		++m_particles_num;
		return true;
	}
	else
	{
		return false;
	}
}

bool localizationManager::DeleteParticle(int index)
{
	if (m_particles_num > index)
	{
		m_particles.erase(m_particles.begin() + index - 1);
		--m_particles_num;
		return true;
	}
	else
	{
		return false;
	}
}

localizationManager::~localizationManager()
{
	vector<Particle*>::iterator iter = m_particles.begin();
	vector<Particle*>::iterator endIter = m_particles.end();

	for (; iter != endIter; ++iter)
	{
		if ((*iter) != NULL)
		{
			delete (*iter);
			--m_particles_num;
		}
	}
}
