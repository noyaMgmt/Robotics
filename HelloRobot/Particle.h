/*
 * Particle.h
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Point.h"

class Robot;
class Map;

class Particle
{
public:
	Particle(Point p_pPoint,double p_dYaw,double p_dBel, Map* p_mMap);
	~Particle();

public:
	void update(Point p_dDeltaLocation, double p_dDeltaYaw, Robot* robot);
	Particle* CreateParticle();
	double getBelief();
	Map* getMap();

private:
	double getParticleProbability(Point p_deltaLocation, double p_dDeltaYaw);
	double getParticleObservationsProbablity(Robot* robot);

private:
	Map* _particleMap;
	Point _particleLocation;
	double _particleYaw;
	double _particleBelief;
};

#endif /* PARTICLE_H_ */
