#include "Algorithm.h"

Algorithm::Algorithm(Matrix* inputMatrix, int townAmount)
{
	townMatrix = inputMatrix;
	this->townAmount = townAmount;
	bestCost = INT_MAX;
	bestPath = nullptr;
}

Algorithm::~Algorithm()
{
	townMatrix = nullptr;
	bestPath = nullptr;
}
