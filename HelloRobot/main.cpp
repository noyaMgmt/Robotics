/*
 * main.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */
#include "Robot.h"
#include "Manager.h"
#include "pngUtil.h"
#include "AStar.cpp"

#include "Plans/Plan.h"
int main()
{

	//ConvertMapBlackToWhiteAndWhiteToBlack("/usr/robotics/PcBotWorld/hospital_section.png");

	Robot robot("localhost",6665);
	map ThisMap();

	getWayOfRobot(-6,2.4,-6,7.4,ThisMap.getMap());

	/*
	Plan plnOA(&robot);

	map.loadPngToGrid("roboticLabMap.png");
	Map inflatedMap(map,138,95,2.5,10);
	inflatedMap.inflateMap(30,30);

	Manager manager(&robot, &plnOA, &map, &inflatedMap);
	manager.run();

	//robot.Move();
*/
}
