/*
 * map.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#include "map.h"
#include <libplayerc++/playerc++.h>
#include <iostream>
#include "lodepng.h"
#include "Robot.h"
#include "map.h"


map::map() {
	// TODO Auto-generated constructor stub

	newfile =  "hospital_section3.png";
	const char* filename = "hospital_section.png";
			loadImage(filename);

			cout << "width: " << width << ", height: " << height << endl;
			for (int i = 0; i < 4; i++)
			{
				cout << (int)image[i] << " ";
			}
			cout << endl;

			/*//  Change the first line to black
			for (unsigned int i = 0; i < width * 4 * 4; i+=4)
			{
				image[i] = 0;
				image[i + 1] = 0;
				image[i + 2] = 0;
				//image[i + 3] = 255;
			}*/

			int x= height;
			thisMap = new int*[x];
			for( int i=0; i < height; i++ ) thisMap[i] = new int[width];


			//create matritza map
			for (int j = 0 ; j < height ; j++)
			{
				for(int i = 0; i < width * 4 ; i+=4)
				{
					if(image[i + j*width*4] == 0)
						thisMap[j][i/4] = 1;
					else
						thisMap[j][i/4] = 0;
				}
			}

			blowUpMap(2);
			revertToVector();







			//todo:grid vs map resulotion






			saveImage(newfile, image, width, height);
}

map::~map() {
	// TODO Auto-generated destructor stub
}

void map::blowUpMap(int Rsize)
{
	for (unsigned int j = 0 ; j < height ; j++)
									{
										thisMap[j][0] = 1;
										thisMap[j][width-1] = 1;
									}

	for (unsigned int j = 0 ; j < width ; j++)
									{
										thisMap[0][j] = 1;
										thisMap[height-1][j] = 1;
									}

	for (unsigned int j = 0 ; j < height ; j++)
							{
								for(unsigned int i = 0; i < width ; i++)
								{
									if(thisMap[j][i]  == 1)
										paintArea(j,i,Rsize);
								}
							}
	for (unsigned int j = 0 ; j < height ; j++)
								{
									for(unsigned int i = 0; i < width ; i++)
									{
										if(thisMap[j][i]  == 2)
											thisMap[j][i]  == 1;
									}
								}

}

void map::paintArea(int x, int y, int Rsize)
{
	for(int i= (x-Rsize > 0 ? (x - Rsize) : 0) ; i< (x+Rsize < height ? x+Rsize: height ) ; i++)
	{
		for(int j=(y-Rsize > 0 ? (y - Rsize) : 0)  ;j< (y+Rsize < width ? y+Rsize: width )  ; j++)
		{
			thisMap[i][j] = 2;
		}
	}
}

void map::revertToVector()
{
	// revert to vector
				for (unsigned int j = 0 ; j < height ; j++)
							{
								for(unsigned int i = 0; i < width * 4 ; i+=4)
								{
									if(thisMap[j][i/4] == 0)
										{
											image[j*width*4 + i] = 255;
											image[j*width*4 + i+1] = 255;
											image[j*width*4 +i+2] = 255;
											image[j*width*4 +i+3] = 255;
										}

									else
										{
											image[j*width*4 +i] = 0;
											image[j*width*4 +i+1] = 0;
											image[j*width*4 +i+2] = 0;
											image[j*width*4 +i+3] = 255;
										}
								}
							}
}

//Example 1
//Decode from disk to raw pixels with a single function call
void map::loadImage(const char* filename)
{
  //decode
	unsigned error = lodepng::decode(image, width, height, filename);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

//Example 1
//Encode from raw pixels to disk with a single function call
//The image argument has width * height RGBA pixels or width * height * 4 bytes
void map::saveImage(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}



