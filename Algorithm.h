#pragma once

#include "Matrix.h"


/*
	Klasa bazowa dla kolejnych algorytmów
	Zawiera macierz z drogami oraz najlepsz¹ œcie¿kê.
*/

using namespace std;

class Algorithm
{
public:
	Matrix* townMatrix;
	int townAmount;
	int* bestPath;
	int bestCost;

	Algorithm(Matrix* inputMatrix, int townAmount);
	~Algorithm();

	virtual void startAlgorithm() = 0;
	virtual void printResult() = 0;
};

