// Astar.cpp
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "Coordinate.h"

using namespace std;

//const int n=7; // horizontal size of the map
//const int m=7; // vertical size size of the map
//static int map[n][m] = {0,0,0,1,0,0,0,
//                        0,0,0,0,0,0,0,
//                        0,0,0,1,0,0,0,
//                        1,1,1,1,1,1,0,
//                        0,0,0,0,0,0,0,
//                        0,0,0,1,1,1,1,
//                        0,0,0,0,0,0,0};
//static int closed_nodes_map[n][m]; // map of closed (tried-out) nodes
//static int open_nodes_map[n][m]; // map of open (not-yet-tried) nodes
//static int dir_map[n][m]; // map of directions
const int dir=8; // number of possible directions to go at any position
// if dir==4
//static int dx[dir]={1, 0, -1, 0};
//static int dy[dir]={0, 1, 0, -1};
// if dir==8
static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};

class node
{
    // current position
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level;
    // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority

    public:
        node(int xp, int yp, int d, int p) 
            {xPos=xp; yPos=yp; level=d; priority=p;}
    
        int getxPos() const {return xPos;}
        int getyPos() const {return yPos;}
        int getLevel() const {return level;}
        int getPriority() const {return priority;}

        void updatePriority(const int & xDest, const int & yDest)
        {
             priority=level+estimate(xDest, yDest)*10; //A*
        }

        // give better priority to going strait instead of diagonally
        void nextLevel(const int & i) // i: direction
        {
             level+=(dir==8?(i%2==0?10:14):10);
        }
        
        // Estimation function for the remaining distance to the goal.
        const int & estimate(const int & xDest, const int & yDest) const
        {
            static int xd, yd, d;
            xd=xDest-xPos;
            yd=yDest-yPos;         

            // Euclidian Distance
            d=static_cast<int>(sqrt(xd*xd+yd*yd));

            // Manhattan distance
            //d=abs(xd)+abs(yd);
            
            // Chebyshev distance
            //d=max(abs(xd), abs(yd));

            return(d);
        }
};

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
  return a.getPriority() > b.getPriority();
}

// A-star algorithm.
// The route returned is a string of direction digits.
// xStart - x coordinate of start point.
// yStart - y coordinate of start point.
// xFinish - x coordinate of finish point.
// yFinish - y coordinate of finish point.
// n - horizontal length of the matrix.
// m - vertical length of the matrix.
// map - the matrix itself.
string pathFind( const int & xStart, const int & yStart, 
                 const int & xFinish, const int & yFinish,
                int n, int m, int **map)
{
    
    int closed_nodes_map[n][m]; // map of closed (tried-out) nodes
    int open_nodes_map[n][m]; // map of open (not-yet-tried) nodes
    int dir_map[n][m]; // map of directions
    static priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
    static int pqi; // pq index
    static node* n0;
    static node* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    pqi=0;

    // reset the node maps
    for(y=0;y<m;y++)
    {
        for(x=0;x<n;x++)
        {
            closed_nodes_map[x][y]=0;
            open_nodes_map[x][y]=0;
        }
    }

    // create the start node and push into list of open nodes
    n0=new node(xStart, yStart, 0, 0);
    n0->updatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    open_nodes_map[x][y]=n0->getPriority(); // mark it on the open nodes map

    // A* search
    while(!pq[pqi].empty())
    {
        // get the current node w/ the highest priority
        // from the list of open nodes
        n0=new node( pq[pqi].top().getxPos(), pq[pqi].top().getyPos(), 
                     pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

        x=n0->getxPos(); y=n0->getyPos();

        pq[pqi].pop(); // remove the node from the open list
        open_nodes_map[x][y]=0;
        // mark it on the closed nodes map
        closed_nodes_map[x][y]=1;

        // quit searching when the goal state is reached
        //if((*n0).estimate(xFinish, yFinish) == 0)
        if(x==xFinish && y==yFinish) 
        {
            // generate the path from finish to start
            // by following the directions
            string path="";
            while(!(x==xStart && y==yStart))
            {
                j=dir_map[x][y];
                c='0'+(j+dir/2)%dir;
                path=c+path;
                x+=dx[j];
                y+=dy[j];
            }

            // garbage collection
            delete n0;
            // empty the leftover nodes
            while(!pq[pqi].empty()) pq[pqi].pop();           
            return path;
        }

        // generate moves (child nodes) in all possible directions
        for(i=0;i<dir;i++)
        {
            xdx=x+dx[i]; ydy=y+dy[i];

            if(!(xdx<0 || xdx>n-1 || ydy<0 || ydy>m-1 || map[xdx][ydy]==1 
                || closed_nodes_map[xdx][ydy]==1))
            {
                // generate a child node
                m0=new node( xdx, ydy, n0->getLevel(), 
                             n0->getPriority());
                m0->nextLevel(i);
                m0->updatePriority(xFinish, yFinish);

                // if it is not in the open list then add into that
                if(open_nodes_map[xdx][ydy]==0)
                {
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    //delete m0;
                    pq[pqi].push(*m0);
                    // mark its parent node direction
                    dir_map[xdx][ydy]=(i+dir/2)%dir;
                }
                else if(open_nodes_map[xdx][ydy]>m0->getPriority())
                {
                    // update the priority info
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    // update the parent direction info
                    dir_map[xdx][ydy]=(i+dir/2)%dir;

                    // replace the node
                    // by emptying one pq to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(pq[pqi].top().getxPos()==xdx && 
                           pq[pqi].top().getyPos()==ydy))
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pq[pqi].pop(); // remove the wanted node
                    
                    // empty the larger size pq to the smaller one
                    if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
                    while(!pq[pqi].empty())
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pqi=1-pqi;
                    pq[pqi].push(*m0); // add the better node instead
                    //delete m0;
                }
                else delete m0; // garbage collection
            }
        }
        delete n0; // garbage collection
    }
    return ""; // no route found
}

// This method returns the way of the robot as a vector of coordinates.
// xStart - x coordinate of start point.
// yStart - y coordinate of start point.
// xFinish - x coordinate of finish point.
// yFinish - y coordinate of finish point.
// n - horizontal length of the matrix.
// m - vertical length of the matrix.
// map - the matrix itself.
vector<Coordinate> getWayOfRobot (const int & xStart, const int & yStart,
                 const int & xFinish, const int & yFinish,
                int n, int m, int **map)
{
	int i;

	// Getting the directions of the robot.
	string route = pathFind(xStart, yStart, xFinish, yFinish, n, m, map);

	cout << route;

	// Creating the way of the robot, and fill the first cell with
	// the start position of the robot.
	vector<Coordinate> wayOfRobot(route.length());
	wayOfRobot[0].x = xStart;
	wayOfRobot[0].y = yStart;

	// Defining the start point as the last cell the robot was.
	Coordinate lastCell;
	lastCell.x = xStart;
	lastCell.y = yStart;

	// Running over the route, to create the way of the robot
	// as an array of coordinates.
	for (i = 0; i <= route.length(); i++)
	{
		// Creating the next cell the robot should go.
		Coordinate currentCell;

		// Setting the next cell by the direction number we got from ASTAR.pathFind.
		switch (route[i])
		{
			// Go right: same row, +1 to column.
			case(0):
			{
				currentCell.x = lastCell.x; // row.
				currentCell.y = lastCell.y + 1; // column.
				break;
			}
			// Go down-right: +1 to row, +1 to column.
			case(1):
			{
				currentCell.x = lastCell.x + 1; // row.
				currentCell.y = lastCell.y + 1; // column.
				break;

			}
			// Go down: +1 to row, same column.
			case(2):
			{
				currentCell.x = lastCell.x + 1; // row.
				currentCell.y = lastCell.y; // column.
				break;

			}
			// Go down-left: +1 to row, -1 to column.
			case(3):
			{
				currentCell.x = lastCell.x + 1; // row.
				currentCell.y = lastCell.y - 1; // column.
				break;

			}
			// Go left: same row, -1 to column.
			case(4):
			{
				currentCell.x = lastCell.x; // row.
				currentCell.y = lastCell.y - 1; // column.
				break;

			}
			// Go up-left: -1 to row, -1 to column.
			case(5):
			{
					currentCell.x = lastCell.x - 1; // row.
					currentCell.y = lastCell.y - 1; // column.
					break;

			}
			// Go up: -1 to row, same column.
			case(6):
			{
				currentCell.x = lastCell.x - 1; // row.
				currentCell.y = lastCell.y; // column.
				break;

			}
			// Go up-right: -1 to row, +1 to column.
			case(7):
			{
				currentCell.x = lastCell.x - 1; // row.
				currentCell.y = lastCell.y + 1; // column.
				break;

			}
		}

		// Adding the next cell to the way of the robot.
		wayOfRobot[i] = currentCell;

		// Marking the next cell as the last cell that the robot was for the next round.
		lastCell = currentCell;
	}

	// Returning the way of robot.
	return (wayOfRobot);
}

//int main()
//{
//
//}
////  srand(time(NULL));
////
////    // create empty map
////    for(int y=0;y<m;y++)
////    {
////        for(int x=0;x<n;x++) map[x][y]=0;
////    }
////
////    // fillout the map matrix with a '+' pattern
////    for(int x=n/8;x<n*7/8;x++)
////    {
////        map[x][m/2]=1;
////    }
////    for(int y=m/8;y<m*7/8;y++)
////    {
////        map[n/2][y]=1;
////    }
////    
////    // randomly select start and finish locations
////    int xA, yA, xB, yB;
////    switch(rand()%8)
////    {
////        case 0: xA=0;yA=0;xB=n-1;yB=m-1; break;
////        case 1: xA=0;yA=m-1;xB=n-1;yB=0; break;
////        case 2: xA=n/2-1;yA=m/2-1;xB=n/2+1;yB=m/2+1; break;
////        case 3: xA=n/2-1;yA=m/2+1;xB=n/2+1;yB=m/2-1; break;
////        case 4: xA=n/2-1;yA=0;xB=n/2+1;yB=m-1; break;
////        case 5: xA=n/2+1;yA=m-1;xB=n/2-1;yB=0; break;
////        case 6: xA=0;yA=m/2-1;xB=n-1;yB=m/2+1; break;
////        case 7: xA=n-1;yA=m/2+1;xB=0;yB=m/2-1; break;
////    }
//
//    int xA, yA, xB, yB;
//    xA = 0;
//    xB = 6;
//    yA = 0;
//    yB = 6;
//    
//    for (int i=0; i <= m; i++)
//    {
//        for (int j=0; j<= n; j++)
//        {
//            cout << " " + map[i][j];
//        }
//        cout << endl;
//    }
//    cout<<"Map Size (X,Y): "<<n<<","<<m<<endl;
//    cout<<"Start: "<<xA<<","<<yA<<endl;
//    cout<<"Finish: "<<xB<<","<<yB<<endl;
//    // get the route
//    string route=pathFind(xA, yA, xB, yB);
//    if(route=="") cout<<"An empty route generated!"<<endl;
//    cout<<"Route:"<<endl;
//    cout<<route<<endl<<endl;
//
//    // follow the route on the map and display it 
//    if(route.length()>0)
//    {
//        int j; char c;
//        int x=xA;
//        int y=yA;
//        map[x][y]=2;
//        for(int i=0;i<route.length();i++)
//        {
//            c =route.at(i);
//            j=atoi(&c); 
//            x=x+dx[j];
//            y=y+dy[j];
//            map[x][y]=3;
//        }
//        map[x][y]=4;
//    
//        // display the map with the route
//        for(int y=0;y<m;y++)
//        {
//            for(int x=0;x<n;x++)
//                if(map[x][y]==0)
//                    cout<<".";
//                else if(map[x][y]==1)
//                    cout<<"O"; //obstacle
//                else if(map[x][y]==2)
//                    cout<<"S"; //start
//                else if(map[x][y]==3)
//                    cout<<"R"; //route
//                else if(map[x][y]==4)
//                    cout<<"F"; //finish
//            cout<<endl;
//        }
//    }
//    return(0);
//}
