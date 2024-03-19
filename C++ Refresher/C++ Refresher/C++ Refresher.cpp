// C++ Refresher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace std;

#include <iostream>
#include "Header.h"

int main()
{
	//Task1();
	//Task2();
	//Task3();
	Task4();
	//Task5();
}

void Task1()
{
	std::cout << "\n\n------Task 1-----\n\n";
	float width = 0;
	float height = 0;

	std::cout << "Please enter the width of the rectange: ";
	std::cin >> width;
	std::cout << "Please enter the height of the rectange: ";
	std::cin >> height;

	std::cout << "\nThe area of the rectangle: " << width * height;
	std::cout << "\nThe perimeter of the rectangle: " << (2 * width) + (2 * height) << "\n";
}

void Task2()
{
	std::cout << "\n\n------Task 2-----\n\n";
	int intArray[10];
	int highestValue = 0;

	for (int i = 0; i < sizeof(intArray) / sizeof(intArray[0]); i++)
	{
		cout << "Please enter number " << i + 1 << ": ";
		cin >> intArray[i];

		if (highestValue < intArray[i])
			highestValue = intArray[i];
	}

	cout << "\n\nThe highest value of these inputs are: " << highestValue;
}

void Task3()
{
	std::cout << "\n\n------Task 3-----\n\n";
	int input;

	do
	{
		cout << "Please choose an option from the following: \n 1. Sunny \n 2. Cloudy \n 3. Raining \n 4. Exit\nYour input: ";
		cin >> input;

		if(cin.fail() || input < 1 || input > 4)
		{
			cout << "\nInvalid input, please try again...\n\n";
			cin.clear(); 
			cin.ignore(1000, '\n');
		}

		switch (input)
		{
		case 1:
			cout << "\nDon't forget your sunscreen\n\n";
			break;
		case 2:
			cout << "\nNot much needed, just cloudy\n\n";
			break;
		case 3:
			cout << "\nYou might want your umbrella and coat\n\n";
			break;
		}
	} while (input != 4);

	cout << "\nExiting...\n";
}

void Task4()
{
	std::cout << "\n\n------Task 4-----\n\n";
	int numOfLines = 0;

	cout << "Please enter the number of lines you want to be printed out: ";
	cin >> numOfLines;

	for (int y = 0; y <= numOfLines; y++)
	{
		for (int x = 0; x < y; x++)
		{
			cout << x + 1 << "  ";
		}
		cout << "\n";
	}
}

void Task5()
{
	MathsExperiment me;
	MathsExperiment* mePointer = new MathsExperiment();

	delete(mePointer);
} 