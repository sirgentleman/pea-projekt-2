#include "TabuSearch.h"

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
        for (int second_node = first_node + 1; second_node < townAmount - 1; second_node)
        {   
            // Je¿eli zamiana nie jest zakazana
            if (tabuList->at_element(first_node, second_node) == 0)
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