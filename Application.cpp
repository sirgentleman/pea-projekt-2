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
}

void Application::showMenu()
{
	while (true)
	{
		cout << "MENU GLOWNE\n";
		cout << "1. Zaladuj plik testowy\n";
		cout << "2. Wyswietl zaladowana macierz\n";
		cout << "3. Uruchom algorytm\n";
		cout << "4. Uruchom testy\n";

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
			break;
		}
		case 2:
		{
			this->printSavedMatrix();
			break;
		}
		case 3:
		{
			sa = new SimulatedAnnealing(inputMatrix, townAmount);
			sa->startAlgorithm();
			sa->printResult();
			break;
		}
		case 4:
		{
			
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