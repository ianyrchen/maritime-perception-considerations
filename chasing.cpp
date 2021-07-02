#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>	
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <climits>
#include <chrono>
#include <thread>
using namespace std;
#define LL long long

pair<int, int> randMove(int x, int y, int gen) // note: x is positive towards right, y is positive downwards
{
	if (gen == 1)
	{
		// northwest
		x--; y--;
	}
	if (gen == 2)
	{
		// north
		y--;
	}
	if (gen == 3)
	{
		// northeast
		x++;  y--;
	}
	if (gen == 4)
	{
		//west
		x--;
	}
	if (gen == 5)
	{
		//stay still
	}
	if (gen == 6)
	{
		// east
		x++;
	}
	if (gen == 7)
	{
		// southwest
		x--; y++;
	}
	if (gen == 8)
	{
		//south
		y++;
	}
	if (gen == 9)
	{
		// southeast
		x++; y++;
	}
	if (gen == 10)
	{
		// invisible
		// invis = true;
	}

	if (x < 0 || x > 4096 || y < 0 || y > 4096)
		return { -1,-1 };
	else
		return { x,y };
}

pair<int, int> chaseMove(int curX, int curY, int goalX, int goalY)
{
	// magic

	return { curX,curY };
}


int main(void)
{
	//freopen("abc.in", "r", stdin);
	//freopen("abc.out", "w", stdout);
	
	// figure out how to csv output
	std::ofstream myfile;
	myfile.open("chase.csv");

	// myfile << std::to_string(x) + ", " + std::to_string(y) + "\n";

	int chaseX = 0, chaseY = 0, randX = 2047, randY = 2047;
	int time = 0;

	while (chaseX != randX && chaseY != randY)
	{
		time++;
		// move random
		int gen = rand() % 10 + 1; // gets random int from 1 to 10
		pair<int, int> temp = randMove(randX, randY, gen);
		while (temp.first == -1 && temp.second == -1)
		{
			gen = rand() % 10 + 1;
			temp = randMove(randX, randY, gen);
		}
		randX = temp.first; randY = temp.second; // what does invis do here??


		// move bresenham
		temp = chaseMove(chaseX, chaseY, randX, randY);
		chaseX = temp.first; chaseY = temp.second; // what does invis do here??


		myfile << "Time " + to_string(time);
		myfile << ": Chaser" + to_string(chaseX) + ", " + std::to_string(chaseY) + ". ";
		myfile << "Random" + to_string(randX) + ", " + std::to_string(randY) + "\n";

		//std::this_thread::sleep_for(std::chrono::seconds(1)); // sleep for one second (commented out for speed's sake)
	}

	myfile.close();
	return 0;
}