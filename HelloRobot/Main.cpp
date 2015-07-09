/*
 * Main.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <iostream>
#include "lodepng.h"
#include "Robot.h"
#include "map.h"
#include <AStar.cpp>

using namespace PlayerCc;

int main()
{

	Robot robot("localhost",6665);


	map ThisMap;

	vector<Coordinate> cor =  getWayOfRobot(-6,2.4,-6,7.4,ThisMap.height, ThisMap.width, ThisMap.getMap());

	/*
	Plan plnOA(&robot);

	map.loadPngToGrid("roboticLabMap.png");
	Map inflatedMap(map,138,95,2.5,10);
	inflatedMap.inflateMap(30,30);

	Manager manager(&robot, &plnOA, &map, &inflatedMap);
	manager.run();

	//robot.Move();
*/
	return 0;
}
