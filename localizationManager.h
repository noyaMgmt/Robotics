/*
 * SlamManager.h
 */

#ifndef _SLAM_MANAGER_H
#define _SLAM_MANAGER_H

#include <vector>

using std::vector;

class Robot;
class Particle;

class SlamManager
{
public:
	SlamManager(Robot* robot);
	~SlamManager();

public:
	void Update(double deltaX, double deltaY, double deltaYaw);
	bool AddParticle(Particle* par);
	bool DeleteParticle(int index);

private:
	vector<Particle*> m_particles;
	Robot* m_robot;
	int m_particles_num;
};

#endif // _SLAM_MANAGER_H
