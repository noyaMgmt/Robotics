/*
 * map.h
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include <libplayerc++/playerc++.h>
#include <iostream>
#include "lodepng.h"
#include "Robot.h"
#include "map.h"


class map {

private:
	std::vector<unsigned char> image; //the raw pixels
		unsigned width, height;
		unsigned G_width, G_height;
		char* newfile;
		void paintArea(int x, int y, int Rsize);

		int **thisMap;
		//int **thisGrid;
public:

	map();
	virtual ~map();
	void revertToVector();
	void loadImage(const char* filename);
	void saveImage(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);
	void blowUpMap(int Rsize);
	int** getMap();
	//int** getGrid();
	//void map2grid();

};

#endif /* MAP_H_ */
