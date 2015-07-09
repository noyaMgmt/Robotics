/*
 * Particle.cpp
 */

#include "Particle.h"
#include "map.h"
#include "Robot.h"
#include "Point.h"
#include "config.h"

Particle::Particle(Point p_pPoint,double p_dYaw,double p_dBel)
			:_particleLocation(p_pPoint),
			 _particleYaw(p_dYaw),
			 _particleBelief(p_dBel)
{
}

void Particle::update(Point p_dDeltaLocation, double p_dDeltaYaw)
{
	// Update The location according to delta
	_particleLocation.x += p_dDeltaLocation.x;
	_particleLocation.y += p_dDeltaLocation.y;
	_particleYaw += p_dDeltaYaw;

	// Robot path posterior
	double probOfPath = this->getParticleProbability(p_dDeltaLocation, p_dDeltaYaw);

	// Calculate new belief according to path, observations and previous belief
	_particleBelief = SAFETY_FACTORY * _particleBelief * probOfPath ;//* ProbOfObs;

	// Check to see if particle exceeded the maximum probability
	if (_particleBelief > 1)
	{
		_particleBelief = 1;
	}
}

// Calculates the probability that the movement is accurate
double Particle::getParticleProbability(Point p_pLocation, double p_dDeltaYaw)
{
	// Distance Traveled
	double distance = sqrt(pow(p_pLocation.x, 2) + pow(p_pLocation.y, 2));

	// Kept moving forward
	if ((p_dDeltaYaw == 0) && (distance < DISTANCE_LIMIT))
	{
		return 1;
	}
	else if ((distance < DISTANCE_LIMIT) && (p_dDeltaYaw < YAW_LIMIT))
	{
		return 0.8;
	}
	else if (((distance > DISTANCE_LIMIT) && (p_dDeltaYaw < YAW_LIMIT)) ||
			 ((distance < DISTANCE_LIMIT) && (p_dDeltaYaw > YAW_LIMIT)))
	{
		return 0.6;
	}
	else
	{
		return 0.2;
	}
}

Particle* Particle::CreateParticle()
{
	double newX = _particleLocation.x + (rand() % 21) / 100;
	double newY = _particleLocation.y + (rand() % 21) / 100;
	double newYaw = _particleYaw + (rand() % 61 - 30.0) * PI / 180.0;
	return new Particle(Point(newX, newY), newYaw, _particleBelief);//, new Map(*_particleMap));
}


double Particle::getBelief()
{
	return this->_particleBelief;
}

Particle::~Particle()
{
}
