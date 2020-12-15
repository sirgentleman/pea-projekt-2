#pragma once
#include "Algorithm.h"
class TabuSearch :
    public Algorithm
{
    
private:
    int tabuLifetime;
    int maxIterations;
    int stopTimeSec;

    int* getBestNeighbour(int* currentPath, Matrix* tabuList);
    int getPathCost(int* currentPath);
    void swapElements(int* path, int x, int y);
    int* randomizeSolution();

public:
    
    TabuSearch(Matrix* inputMatrix, int townAmount);
    ~TabuSearch();

    //void setInitalParams();
    void setStopTime(int timeInSec);

    void startAlgorithm();
    void printResult();

};

