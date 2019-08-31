
#include "pch.h"
#include <iostream>
#include <array>
#include <random>
#include <vector>
#include "LightsOut.h"


void printMap(std::vector< std::vector<int> >& gameMap, int& gameSize)
{
	std::cout << "   ";
	for (int i = 0; i < gameSize; i++)
		std::cout << i << " ";
	std::cout << "\n ";
	for (int i = 0; i < gameSize; i++)
		std::cout << "---";
	std::cout << " \n";

	for (int i = 0; i < gameSize; i++)
	{
		std::cout << i << "| ";
		for (int j = 0; j < gameSize; j++)
		{
			std::cout << gameMap[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

bool winCheck(std::vector< std::vector<int> >& gameMap, int& gameSize)
{
	for (int i = 0; i < gameSize; i++)
	{
		for (int j = 0; j < gameSize; j++)
		{
			if (gameMap[i][j] == 0)
				return false;
		}
	}
	return true;
}

bool checkRange(int a, int& gameSize)
{
	if (!(a >= 0 && a < gameSize))
		return false;
	return true;
}

void lightSwitch(std::vector< std::vector<int> >& gameMap, int& gameSize, int const &x, int const &y)
{
	if (checkRange(x, gameSize) && checkRange(y, gameSize))
	{
		gameMap[x][y] += 1;
		if (gameMap[x][y] > 1)
		{
			if (gameMap[x][y] % 2 == 0)
				gameMap[x][y] = 0;
			else
				gameMap[x][y] = 1;
		}
	}
}

void lightPress(std::vector< std::vector<int> >& gameMap, int& gameSize, int const &x, int const &y)
{
	//If the coordinates given are out of range
	if ( !checkRange(x, gameSize) || !checkRange(y, gameSize) )
	{
		std::cout << "Out of range. \n";
	}
	else 
	{
		lightSwitch(gameMap, gameSize, x, y);
		lightSwitch(gameMap, gameSize, x + 1, y);
		lightSwitch(gameMap, gameSize, x - 1, y);
		lightSwitch(gameMap, gameSize, x, y + 1);
		lightSwitch(gameMap, gameSize, x, y - 1);
	}
	
}

void generateMap(std::vector< std::vector<int> >& gameMap, int& gameSize, int& difficulty)
{
	if (difficulty < 1)
		difficulty = 1;
	else if (difficulty > 100)
		difficulty = 100;

	std::random_device random; //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(random()); //Standard mersenne_twister_engine seeded with random()
	std::uniform_int_distribution<> dis(0, gameSize - 1); // dis(gen)

	for (int i = 0; i < gameSize; i++)
	{
		std::vector<int> temp;
		for (int j = 0; j < gameSize; j++)
		{
			temp.push_back(1);
		}
		gameMap.push_back(temp);
	}
	while (winCheck(gameMap, gameSize) == 1)
	{
		for (int ct = 0; ct < difficulty; ct++)
		{
			int row = dis(gen), col = dis(gen);
			lightPress(gameMap, gameSize, row, col);
			std::cout << "[" << row << "," << col << "]\n";
		}
	}

	std::cout << "Lights shuffled " << difficulty << " time(s):\n" << "----------------------\n";
	printMap(gameMap, gameSize);
}

int main()
{
	int gameSize, difficulty;
	std::vector< std::vector<int> > gameMap;
	
	//Game Size
	std::cout << "Input game size: ", std::cin >> gameSize;
	while (!std::cin || ((gameSize < 1) || (gameSize > 9))) 
	{
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Game size must be a number from 1 to 9. Try again: ", std::cin >> gameSize;
			continue;
		}
		if ((gameSize < 1) || (gameSize > 9))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Game size must be a number from 1 to 9. Try again: ", std::cin >> gameSize;
		}
	}


	//Shuffles
	std::cout << "Please select amount of shuffles (1 to 100): \n", std::cin >> difficulty;
	while (!std::cin || ((difficulty < 1) || (difficulty > 100))) 
	{
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Shuffles amount must be a number from 1 to 100. Try again: ", std::cin >> difficulty;
		}
		if ((difficulty < 1) || (difficulty > 100))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Shuffles amount must be a number from 1 to 100. Try again: ", std::cin >> difficulty;
		}
	}

	
	generateMap(gameMap, gameSize, difficulty); //Map generation

	//Game loop
	int userInput = 1, x, y, moves = 0;
	while (userInput != 9)
	{
		//User input coordinates
		std::cout << "Please input 2 positive numbers as coordinates x (row) and y (col) -- or 9 to close: \n", std::cin >> userInput;
		while (!std::cin || ((userInput < 0) || (userInput > (gameSize - 1) * 10 + (gameSize - 1))))
		{
			if (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Coordinates must be integers. Try again: ", std::cin >> userInput;
			}

			if ((userInput < 0) || (userInput > (gameSize - 1) * 10 + (gameSize - 1)))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			    std::cout << "Inputted coordinates are out of range. Try again: ", std::cin >> userInput;
			}
		}

		if (userInput == 9)
			return 0;
		x = static_cast<int>(userInput / 10);
		y = static_cast<int>(userInput % 10);	

		moves++;

		lightPress(gameMap, gameSize, x, y);
		printMap(gameMap, gameSize);
		
		if (winCheck(gameMap, gameSize) == 1)
		{
			std::cout << "\n****************\n*** YOU WIN! ***\n****************\n";
			std::cout << "All lights switched ON in: " << moves << " move(s).\n";
			return 0;
		}
	}
}
