/*
 * Particle.h
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Point.h"

class Robot;
class map;

class Particle
{
public:
	Particle(Point p_pPoint,double p_dYaw,double p_dBel);
	~Particle();

public:
	void update(Point p_dDeltaLocation, double p_dDeltaYaw);
	Particle* CreateParticle();
	double getBelief();
	//map* getMap();

private:
	double getParticleProbability(Point p_deltaLocation, double p_dDeltaYaw);
	double getParticleObservationsProbablity(Robot* robot);

private:
	//map* _particleMap;
	Point _particleLocation;
	double _particleYaw;
	double _particleBelief;
};

#endif /* PARTICLE_H_ */
