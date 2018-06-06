/*
 Author: Dan Mitu, Daniel Jarc
		
 CS 325
 Spring 2018
 Description: The project makes to solve the Travelling Salesman Problem using the Nearest Neighbor Algorithm.
 
 Reference:
    https://www.youtube.com/watch?v=RK6eu3jvKzw
 
 */


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <vector>
#include <map>
#include <iostream>

using namespace std;
struct city{
    int id;
    int x;
    int y;
};

void calculateDistanceBetweenCities(vector<struct city>&vectorCities,vector<vector<int> > &distanceCities){
    int distance = 0;
    
    int i = 0;
    int j=0;
    for(i=0;i<vectorCities.size();i++){
        distanceCities[i] = vector<int>(distanceCities.size());
        for(j=0;j<vectorCities.size();j++){
            //if two cities is same, set up distance is INT_MAX
            if(i == j)
                distanceCities[i][j] = INT_MAX;
            else{
                distance = round(sqrt(pow(vectorCities[j].x - vectorCities[i].x,2) + pow(vectorCities[j].y - vectorCities[i].y,2)));
          
                distanceCities[i][j] = distance;
            }
        }
    }
    
}

void takeInput(vector<struct city>&vectorCities,char fileName[])
{
    int i,j;

    FILE *readFile;
    char line[1000];
    char* strCity;
    char* strX;
    char* strY;
    int city=0;
    int xCity=0;
    int yCity =0;
    struct city structCity;
    
    readFile = fopen(fileName,"r+");
    if(readFile == NULL)
        printf("\nCan't open file data\n");
    else{
        while(fgets(line,sizeof(line),readFile)!=NULL){
            strCity = strtok(line," ");
            strX    = strtok(NULL," ");
            strY    = strtok(NULL," ");
            
            if(strCity != NULL && strX != NULL && strY != NULL){
                city  = atoi(strCity);
                xCity = atoi(strX);
                yCity = atoi(strY);
                structCity.id = city;
                structCity.x = xCity;
                structCity.y = yCity;
                vectorCities.push_back(structCity);
            }
        }
    }
   
}


// checks if a city has been visited already
bool checkVisited(vector<int>& visitedList, int id){
    for (int i = 0; i < visitedList.size(); i++){
        if (visitedList[i] == id)
            return true;
    }
    return false;
}
/*
 Travelling Salesman Problem - Nearest Neighbor Algorithm
 */
void NNGFindTour(vector<vector<int> >&distanceCity,vector<int>& visited,int size,int&cost){
    //Choose Start at City 12
    int start = 12;
    visited.push_back(start);
    int min;
    int index;
    int i = 0;
    
    while( visited.size() < size){
        min = INT_MAX;
        index = -1;
        for(i =0;i<size;i++){

            if(distanceCity[start][i] < min && !checkVisited(visited,i)){
                min=distanceCity[start][i];
                index = i;
            }
        }
        if(min!=INT_MAX)
            cost += min;
        visited.push_back(index);
        start = index;
    }
    //add cost between last city with start city at 12
    cost = cost + distanceCity[visited[size-1]][12];
}



int main(int argc,char *argv[])
{
    clock_t clock_start = clock();
    int cost = 0;
    int sizeCity = 0;
    char fileName[100];
    //char fileName[100] = "tsp_example_1.txt";
    FILE *writeFile;
    vector<struct city> cities;
    
    if (argc != 2){
        printf ("Invalid number of arguments.\n");
        exit(1);
    }
    
    strcpy(fileName, argv[1]);
    takeInput(cities,fileName);
   
    sizeCity = cities.size();
    vector<vector <int> > distanceCity(sizeCity);
    calculateDistanceBetweenCities(cities, distanceCity);

    vector<int>visited;
  
    NNGFindTour(distanceCity,visited,sizeCity,cost);
    
    //Write to the find
    strcat(fileName, ".tour");
    writeFile = fopen(fileName,"w+");
    fprintf(writeFile, "%d",cost);
    for(int i=0;i<sizeCity;i++){
        fprintf(writeFile, "\n%d",visited[i]);
    }
    
    clock_t clock_end = clock();
    double duration = ( clock_end - clock_start ) / (double) CLOCKS_PER_SEC;
    printf("\nDuration: %f\n",duration);
    
    return 0;
}

