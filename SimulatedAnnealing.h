#pragma once
#include "Algorithm.h"
class SimulatedAnnealing :
    public Algorithm
{
private:
    double initalTemp;
    double tempStop;
    double tempChange;
    
    int iterationTempChange;

    int* findNewSolution(int* currentSolution);
    int getPathCost(int* currentSolution);
    int* randomizeSolution();

public:
    SimulatedAnnealing(Matrix* inputMatrix, int townAmount);
    ~SimulatedAnnealing();

    void setInitalParams(double initalTemp, double tempStop, double tempChange, int iterationTempChange);

    void startAlgorithm();
    void printResult();
};

