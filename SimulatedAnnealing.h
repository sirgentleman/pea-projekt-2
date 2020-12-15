#pragma once
#include "Algorithm.h"
class SimulatedAnnealing :
    public Algorithm
{
private:
    double initalTemp;
    double tempChange;
    int stopTimeSec;
    int iterationTempChange;

    int* findNewSolution(int* currentSolution);
    int getPathCost(int* currentSolution);
    int* randomizeSolution();

public:
    SimulatedAnnealing(Matrix* inputMatrix, int townAmount);
    ~SimulatedAnnealing();

    void setInitalParams(double tempChange, int iterationTempChange);
    void setStopTime(int timeInSec);

    void startAlgorithm();
    void printResult();
};

