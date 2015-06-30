/*
 * config.h
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define DISTANCE_LIMIT           1.0
#define YAW_LIMIT		         120.0
#define SAFETY_FACTORY			 2.0
#define M_RESOLUTION  			 40
#define G_RESOLUTION             80


#define WORLD_WIDTH  			 40
#define WORLD_HIGHT              20
#define RESOLUTION  		     0.2
#define MIDDLE_OF_MAP  			 100
#define LASER_SENSORS_NUM        666
#define ROW_NUM  				 200
#define COL_NUM  				 200
#define PI					     3.141592653
#define PARTICLES_MAX            100
#define PARTICLES_MIN			 30
#define MOVE_SPEED				 1
#define TURN_LEFT_SPEED			 0.3
#define TURN_RIGHT_SPEED		0.3


enum CellState
{
	Free = 0,
	Occupied,
	Unknown
};

#endif /* CONFIG_H_ */
