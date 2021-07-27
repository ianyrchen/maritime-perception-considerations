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
using namespace std;
#define LL long long

double calcBoundary(double firstMean, double firstStdDev, double secMean, double secStdDev)
{
	double boundary = firstMean + firstStdDev * (secMean-firstMean)/(firstStdDev+secStdDev);
	return boundary;
}

double findEntropy(int timesteps, vector<pair<int, int>> boatpositions) {
	int dx, dy;
	int p[9] = {}; //0-8 each index represents a move (not accounting for invis yet)

	//loop through the position array to create probability array
	for (int i = 1; i < timesteps; i++) 
	{
		dx = boatpositions[i].first - boatpositions[i - 1].first;
		dy = boatpositions[i].second - boatpositions[i - 1].second;

		if (dx == 1) 
		{
			if (dy == 1) 
			{
				p[2] = p[2] + 1;
			}
			else if (dy == -1) 
			{
				p[4]++;
			}
			else 
			{
				p[3]++;
			}
		}
		else if (dx == -1) 
		{
			if (dy == 1) 
				p[8] ++;

			else if (dy == -1) 
				p[6]++;

			else 
				p[7]++;
		}
		else if (dx == 0) 
		{
			if (dy == 1) 
			{
				p[1] ++;
			}
			else if (dy == -1) 
			{
				p[5]++;
			}
			else 
			{
				p[0]++;
			}
		}

		//std::cout << dx << ',' << dy<< std::endl;
	}

	double H = 0; double P;
	for (int j = 0; j <= 8; j++) 
	{
		P = p[j] / double(timesteps);
		if (P == 0) 
			continue;
		
		//std::cout<< "probability: " << P << std::endl;
		H += P * log2(1 / P);
	}
	return H;

}

int main(void)
{
	// stats.csv must be a two-column, three row csv, 
	// with means in first col and std dev in second col 
	// AND IN ORDER FROM 1st TO 3rd
	FILE *f1 = freopen("stats.csv", "r", stdin); 

	vector<int> means, stdDevs;
	
	string line;
	for (int i = 0 ;i < 3; i++)
	{
		getline(cin, line);
		vector<string> result;
		stringstream s_stream(line); //create string stream from the string
		while (s_stream.good()) {
			string substr;
			getline(s_stream, substr, ','); //get first string delimited by comma
			result.push_back(substr);
		}

		means.push_back( stoi(result[0]) );
		stdDevs.push_back( stoi(result[1].substr(1, result[1].length() - 1)) );
	}
	fclose(f1);
	
	// calc first boundary
	double firstBoundary = calcBoundary(means[0], stdDevs[0], means[1], stdDevs[1]);
	// calc sec boundary
	double secBoundary = calcBoundary(means[1], stdDevs[1], means[2], stdDevs[2]);


	// read in a csv file of coords
	FILE *f2 = freopen("trajectory.csv", "r", stdin);
	string line; 
	int timesteps = 0;
	vector<pair<int, int>> boatpositions;
	while (getline(cin,line))
	{
		timesteps++;
		vector<string> result;
		stringstream s_stream(line); //create string stream from the string
		while (s_stream.good()) {
			string substr;
			getline(s_stream, substr, ','); //get first string delimited by comma
			result.push_back(substr);
		}

		pair<int, int> temp;
		temp.first = stoi(result[0]);
		temp.second = stoi(result[1].substr(1, result[1].length() - 1));
		boatpositions.push_back(temp);
	}
	fclose(f2);

	// get entropy
	double e = 0;
	e = findEntropy(timesteps,boatpositions);

	
	if (e < firstBoundary)
	{
		cout << "chasing";
	}
	else if (e >= firstBoundary && e < secBoundary)
	{
		cout << "following";
	}
	else if (e >= secBoundary)
	{
		cout << "randomwalk";
	}

	return 0;
}