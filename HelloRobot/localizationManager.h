/*
 * localizationManager.h
 */

#ifndef _localization_Manager_H
#define _localization_Manager_H

#include <vector>

using std::vector;

class Robot;
class Particle;

class localizationManager
{
public:
	localizationManager(Robot* robot);
	~localizationManager();

public:
	void Update(double deltaX, double deltaY, double deltaYaw);
	bool AddParticle(Particle* par);
	bool DeleteParticle(int index);

private:
	vector<Particle*> m_particles;
	Robot* m_robot;
	int m_particles_num;
};

#endif // _localization_Manager_H
