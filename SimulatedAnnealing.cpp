#include "SimulatedAnnealing.h"
#include <random>
#include <time.h>
#include <math.h>
#include <iostream>

SimulatedAnnealing::SimulatedAnnealing(Matrix* inputMatrix, int townAmount)
    : Algorithm(inputMatrix, townAmount)
{
    //defaults
    srand(time(NULL));
    initalTemp = 10000;
    tempChange = 0.995;
    iterationTempChange = 20000;
    stopTimeSec = 60;
}

SimulatedAnnealing::~SimulatedAnnealing()
{
    delete[] bestPath;
    delete townMatrix;
}

void SimulatedAnnealing::setStopTime(int timeInSec)
{
    stopTimeSec = timeInSec;
}

int* SimulatedAnnealing::randomizeSolution()
{
    bool* isVisited = new bool[townAmount];
    int* solution = new int[townAmount - 1];
    for (int iii = 0; iii < townAmount - 1; iii++)
        isVisited[iii] = false;

    for (int iii = 0; iii < townAmount - 1; iii++)
    {
        int index;
        do
        {
            index = (rand() % (townAmount-1))+1;
        } while (isVisited[index] == true);

        solution[iii] = index;
        isVisited[index] = true;
    }

    delete[] isVisited;
    return solution;
}

/*
* Szukanie nowego rozwi¹zania - losowe wybieranie dwóch wierzcho³ków i zamiana miejscami
*/
int* SimulatedAnnealing::findNewSolution(int* currentSolution)
{
    int* newSolution = new int[townAmount - 1];
    copy(currentSolution, currentSolution + (townAmount - 1), newSolution);

    int first = rand() % (townAmount - 2);
    int second;
    do 
    {
        second = rand() % (townAmount - 2);
    } while (second == first);

    int temp = newSolution[first];
    newSolution[first] = newSolution[second];
    newSolution[second] = temp;

    return newSolution;
}

int SimulatedAnnealing::getPathCost(int* currentSolution)
{
    int pathCost = townMatrix->at_element(0, currentSolution[0]);

    for (int iii = 1; iii < townAmount-1; iii++)
    {
        pathCost += townMatrix->at_element(currentSolution[iii - 1], currentSolution[iii]);
    }

    pathCost += townMatrix->at_element(currentSolution[townAmount-2], 0);

    return pathCost;
}

void SimulatedAnnealing::setInitalParams(double tempChange, int iterationTempChange)
{
    this->tempChange = tempChange;
    this->iterationTempChange = iterationTempChange;
}

void SimulatedAnnealing::startAlgorithm()
{
    time_t startTime = time(NULL);

    int* currentSolution = this->randomizeSolution();
    int solutionCost = this->getPathCost(currentSolution);
    bestCost = INT_MAX;
    if (bestPath != nullptr)
        delete[] bestPath;
    bestPath = new int[townAmount - 1];

    double currentTemp = NULL;

    while (true)
    {

        for (int iteration = 0; iteration < iterationTempChange; iteration++)
        {
            if (time(NULL) >= startTime + stopTimeSec)
            {
                delete[] currentSolution;
                return;
            }

            if (solutionCost < bestCost)
            {
                bestCost = solutionCost;
                copy(currentSolution, currentSolution + (townAmount - 1), bestPath);
            }
            
            int* newSolution = this->findNewSolution(currentSolution);
            int newSolutionCost = this->getPathCost(newSolution);

            if (currentTemp == NULL)
                currentTemp = -abs((double)solutionCost - (double)newSolutionCost)/log(0.98);

            if (newSolutionCost < solutionCost || exp((solutionCost - newSolutionCost) / currentTemp) > rand())
            {
                delete[] currentSolution;
                currentSolution = newSolution;
                solutionCost = newSolutionCost;
            }
            else
                delete[] newSolution;
        }

        currentTemp *= tempChange;
    }

    delete[] currentSolution;
}

void SimulatedAnnealing::printResult()
{
    cout << "\nFINAL COST: " << bestCost << "\nFINAL PATH: 0 ->";
    for (int iii = 0; iii < townAmount-1; iii++)
    {
        cout << bestPath[iii] << " -> ";
    }
    cout << " 0\n";
}
