#pragma once
#include "Algorithm.h"
class TabuSearch :
    public Algorithm
{
    
private:
    int tabuLifetime;

    int* getBestNeighbour(int* currentPath, Matrix* tabuList);
    int getPathCost(int* currentPath);
    void swapElements(int* path, int x, int y);

public:
    
    TabuSearch(Matrix* inputMatrix, int townAmount);
    ~TabuSearch();

    //void setInitalParams();

    void startAlgorithm();
    void printResult();

};

