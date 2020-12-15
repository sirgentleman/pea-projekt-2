#include "TabuSearch.h"
#include <iostream>
#include <time.h>

TabuSearch::TabuSearch(Matrix* inputMatrix, int townAmount)
    : Algorithm(inputMatrix, townAmount)
{
    tabuLifetime = 100;
    maxIterations = 100000;
    stopTimeSec = 120;
}

TabuSearch::~TabuSearch()
{

}

int* TabuSearch::randomizeSolution()
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
            index = (rand() % (townAmount - 1)) + 1;
        } while (isVisited[index] == true);

        solution[iii] = index;
        isVisited[index] = true;
    }

    delete[] isVisited;
    return solution;
}

void TabuSearch::swapElements(int* path, int x, int y)
{
    int temp = path[x];
    path[x] = path[y];
    path[y] = temp;
}

int* TabuSearch::getBestNeighbour(int* currentPath, Matrix* tabuList)
{
    int* bestFoundPath = new int[townAmount - 1];
    int bestFoundCost = INT_MAX;
    int* tempPath = new int[townAmount - 1];
    copy(currentPath, currentPath + (townAmount - 1), tempPath);
    int tempPathCost = 0;
    int swapX = 0, swapY = 0;

    for (int first_node = 0; first_node < townAmount - 1; first_node++)
    {
        for (int second_node = first_node + 1; second_node < townAmount - 1; second_node++)
        {   
            // Je¿eli zamiana nie jest zakazana
            if (tabuList->at_element(currentPath[first_node], currentPath[second_node]) == 0)
            {
                swapElements(tempPath, first_node, second_node);
                tempPathCost = getPathCost(tempPath);

                if (tempPathCost < bestFoundCost)
                {
                    copy(tempPath, tempPath + (townAmount - 1), bestFoundPath);
                    bestFoundCost = tempPathCost;
                    swapX = first_node;
                    swapY = second_node;
                }
                
                swapElements(tempPath, second_node, first_node);
            }
        }
    }
    delete[] tempPath;
    tabuList->set_element(swapX, swapY, tabuLifetime);
    return bestFoundPath;
}

int TabuSearch::getPathCost(int* currentSolution)
{
    int pathCost = townMatrix->at_element(0, currentSolution[0]);

    for (int iii = 1; iii < townAmount - 1; iii++)
    {
        pathCost += townMatrix->at_element(currentSolution[iii - 1], currentSolution[iii]);
    }

    pathCost += townMatrix->at_element(currentSolution[townAmount - 2], 0);

    return pathCost;
}

void TabuSearch::setStopTime(int timeInSec)
{
    stopTimeSec = timeInSec;
}

void TabuSearch::startAlgorithm()
{
    Matrix* tabuList = new Matrix();
    tabuList->initMatrix(townAmount, townAmount);
    for (int iii = 0; iii < townAmount; iii++)
        for (int jjj = 0; jjj < townAmount; jjj++)
            tabuList->set_element(iii, jjj, 0);

    int* currentBest = randomizeSolution();
    int currentBestValue = getPathCost(currentBest);
    int* tempPath;
    if (bestPath != nullptr)
        delete[] bestPath;
    bestPath = new int[townAmount - 1];
    bestCost = currentBestValue;

    time_t startTime = time(NULL);

    for (int iii = 0; iii < maxIterations; iii++)
    {
        if (startTime + stopTimeSec <= time(NULL))
            break;

        tempPath = getBestNeighbour(currentBest, tabuList);
        delete[] currentBest;
        currentBest = tempPath;
        currentBestValue = getPathCost(currentBest);

        if (currentBestValue < bestCost)
        {
            copy(currentBest, currentBest + (townAmount - 1), bestPath);
            bestCost = currentBestValue;
        }

        for (int iii = 0; iii < townAmount; iii++)
        {
            for (int jjj = 0; jjj < townAmount; jjj++)
            {
                int temp = tabuList->at_element(iii, jjj);
                if (temp > 0)
                    tabuList->set_element(iii, jjj, temp - 1);
            }
        }
    }
    delete[] currentBest;
}

void TabuSearch::printResult()
{
    cout << "\nFINAL COST: " << bestCost << "\nFINAL PATH: 0 ->";
    for (int iii = 0; iii < townAmount - 1; iii++)
    {
        cout << bestPath[iii] << " -> ";
    }
    cout << " 0\n";
}