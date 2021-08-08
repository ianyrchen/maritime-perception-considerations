#include "stdSysImports.h"
#include "bresenham.h"

using namespace std;

int main () {

    ofstream myfile;
    myfile.open("animation.csv");

    int timesteps = 5000;

        pair<int,int> chaser = {2048,2048}; //chaser starts in the middle
        std::pair<int,int> boatPositions[timesteps] = {};
        std::pair<int,int> followingBoatPositions[timesteps] = {};
        std::pair<int,int> chasingBoatPositions[timesteps] = {};

        boatPositions[0] = chaser;
        chasingBoatPositions[0] = chaser;
        followingBoatPositions[0] = chaser;
        int dir = rand() % 4 + 1; 
        //pair<int,int> runner = {(rand() % 2)*(chaser.first+512) + rand() % (chaser.first-512) + 1,(rand() % 2)*(chaser.second+512) +rand() % (chaser.second-512) + 1}; //randomize runner pos
        pair<int,int> runner = {2000,2000};

        for (int i = 1; i<= timesteps; i++){ //looping through each step
        
            int currXf = followingBoatPositions[i-1].first;
            int currYf = followingBoatPositions[i-1].second;
            int currXc = chasingBoatPositions[i-1].first;
            int currYc = chasingBoatPositions[i-1].second;
            int currX = boatPositions[i-1].first;
            int currY = boatPositions[i-1].second;
            boatPositions[i] = randMove(currX, currY);
            
            if ((currXc != runner.first || currYc != runner.second) && currXc != -1){ //checking for collision
                chasingBoatPositions[i] = bresenhamstep(currXc,currYc,runner.first,runner.second);
            }
            else{
                chasingBoatPositions[i] = {-1,-1};
            }
            if ((currXf != runner.first || currYf != runner.second) && currXf != -1){
                followingBoatPositions[i] = randFollowMove(currXf,currYf,runner.first,runner.second);
            }
            else{
                followingBoatPositions[i] = {-1,-1};
            }


            myfile << currX << "," << currY << "," << currXc << "," << currYc 
            << "," << currXf << "," << currYf << "," <<runner.first << "," << runner.second << "\n";
            if (i % 6 == 1){
                if (dir == 1){
                    runner.first++;
                }
                else if (dir == 2) {
                    runner.first --;
                }
                else if (dir == 3) {
                    runner.second ++;
                }
                else{
                    runner.second--;
                }
            }

        }

    

    myfile.close();

    return 0;
}