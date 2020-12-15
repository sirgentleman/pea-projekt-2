#include "Application.h"
#include <fstream>
#include <iostream>
#include <random>
#include <time.h>

Application::Application()
{
	inputMatrix = nullptr;

	showMenu();
}

Application::~Application()
{
	delete inputMatrix;
	delete sa;
	delete ts;
}

void Application::showMenu()
{
	while (true)
	{
		cout << "MENU GLOWNE\n";
		cout << "1. Zaladuj plik testowy\n";
		cout << "2. Wyswietl zaladowana macierz\n";
		cout << "3. Zmien poczatkowe ustawienia SA\n";
		cout << "4. Uruchom SA\n";
		cout << "5. Uruchom TS\n";

		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			cout << "Podaj nazwe pliku: ";
			string fileName;
			cin >> fileName;
			this->loadTestFile(fileName);
			sa = new SimulatedAnnealing(inputMatrix, townAmount);
			ts = new TabuSearch(inputMatrix, townAmount);
			break;
		}
		case 2:
		{
			this->printSavedMatrix();
			break;
		}
		case 3:
		{
			cout << "Podaj wspolczynnik zmiany temperatury:";
			double tempChange;
			cin >> tempChange;
			cout << "Podaj liczbe iteracji w jednej temperaturze:";
			int iteration;
			cin >> iteration;
			sa->setInitalParams(tempChange, iteration);
			break;
		}
		case 4:
		{
			cout << "Maksymalny czas wykonania: ";
			int maxTime;
			cin >> maxTime;
			sa->setStopTime(maxTime);
			sa->startAlgorithm();
			sa->printResult();
			break;
		}
		case 5:
		{
			cout << "Maksymalny czas wykonania: ";
			int maxTime;
			cin >> maxTime;
			ts->setStopTime(maxTime);
			ts->startAlgorithm();
			ts->printResult();
			break;
		}
		}
	}
}

void Application::loadTestFile(string filePath)
{
	ifstream testFile(filePath);

	if (testFile.is_open())
	{
		string buffer;
		getline(testFile, buffer);
		townAmount = stoi(buffer);
		inputMatrix = new Matrix();
		inputMatrix->initMatrix(townAmount, townAmount);

		for (int iii = 0; iii < townAmount; iii++)
		{
			for (int jjj = 0; jjj < townAmount; jjj++)
			{
				int value;
				testFile >> value;
				inputMatrix->set_element(iii, jjj, value);
			}

		}
	}
}


void Application::generateRandomMatrix(int townAmount)
{
	delete inputMatrix;
	inputMatrix = nullptr;
	this->townAmount = townAmount;
	inputMatrix = new Matrix();
	inputMatrix->initMatrix(townAmount, townAmount);
	srand(time(NULL));
	for (int iii = 0; iii < townAmount; iii++)
	{
		for (int jjj = 0; jjj < townAmount; jjj++)
		{
			if (iii == jjj)
				inputMatrix->set_element(iii, jjj, 0);
			else
				inputMatrix->set_element(iii, jjj, rand() % 100 + 1);
		}
	}
}

void Application::printSavedMatrix()
{
	for (int iii = 0; iii < townAmount; iii++)
	{
		for (int jjj = 0; jjj < townAmount; jjj++)
			cout << inputMatrix->at_element(iii, jjj) << " ";
		cout << endl;
	}
}