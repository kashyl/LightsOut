
#include "pch.h"
#include <iostream>
#include <array>
#include <random>
#include "LightsOut.h"


void printMap(unsigned int gameMap[][5], unsigned const int gameSize)
{
	std::cout << "   ";
	for (unsigned int i = 0; i < gameSize; i++)
		std::cout << i << " ";
	std::cout << "\n -------------- \n";
	for (unsigned int i = 0; i < gameSize; i++)
	{
		std::cout << i << "| ";
		for (unsigned int j = 0; j < gameSize; j++)
		{
			std::cout << gameMap[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

bool winCheck(unsigned int gameMap[][5], unsigned const int gameSize)
{
	for (unsigned int i = 0; i < gameSize; i++)
	{
		for (unsigned int j = 0; j < gameSize; j++)
		{
			if (gameMap[i][j] == 0)
				return false;
		}
	}
	return true;
}

bool checkRange(unsigned int a, unsigned const int gameSize)
{
	if (!(a >= 0 && a < gameSize))
		return false;
	return true;
}

unsigned int lightSwitch(unsigned int gameMap[][5], unsigned const int gameSize, unsigned int a, unsigned b)
{
	if (checkRange(a, gameSize) && checkRange(b, gameSize))
	{
		gameMap[a][b] += 1;
		if (gameMap[a][b] > 1)
		{
			if (gameMap[a][b] % 2 == 0)
				gameMap[a][b] = 0;
			else
				gameMap[a][b] = 1;
		}
	}
	return gameMap[gameSize][gameSize];
}

unsigned int lightPress(unsigned int gameMap[][5], unsigned const int gameSize, unsigned int x, unsigned int y)
{
	//If the coordinates given are out of range
	if ( !checkRange(x, gameSize) || !checkRange(y, gameSize) )
	{
		std::cout << "Out of range. \n";
		return 0;
	}
	
	gameMap[gameSize][gameSize] = lightSwitch(gameMap, gameSize, x, y);
	gameMap[gameSize][gameSize] = lightSwitch(gameMap, gameSize, x + 1, y);
	gameMap[gameSize][gameSize] = lightSwitch(gameMap, gameSize, x - 1, y);
	gameMap[gameSize][gameSize] = lightSwitch(gameMap, gameSize, x, y + 1);
	gameMap[gameSize][gameSize] = lightSwitch(gameMap, gameSize, x, y - 1);
	return gameMap[gameSize][gameSize];
}

unsigned int generateMap(unsigned int gameMap[][5], unsigned const int gameSize, unsigned int difficulty)
{
	if (difficulty < 1)
		difficulty = 1;
	else if (difficulty > 100)
		difficulty = 100;
	std::random_device random; //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(random()); //Standard mersenne_twister_engine seeded with random()
	std::uniform_int_distribution<> dis(0, gameSize - 1); // dis(gen)
	for (unsigned int i = 0; i < gameSize; i++)
	{
		for (unsigned int j = 0; j < gameSize; j++)
		{
			gameMap[i][j] = 1;
		}
	}
	while (winCheck(gameMap, gameSize) == 1)
	{
		for (unsigned int ct = 0; ct < difficulty; ct++)
		{
			int row = dis(gen), col = dis(gen);
			gameMap[gameSize][gameSize] = lightPress(gameMap, gameSize, row, col);
			std::cout << "[" << row << "," << col << "]\n";
		}
	}

	std::cout << "Lights shuffled " << difficulty << " time(s):\n" << "----------------------\n";
	printMap(gameMap, gameSize);

	return gameMap[gameSize][gameSize];
}

int main()
{
	unsigned const int gameSize = 5;
	unsigned int gameMap[gameSize][gameSize];
	int difficulty;
	std::cout << "Please select amount of shuffles (1 to 100): \n", std::cin >> difficulty;
	gameMap[gameSize][gameSize] = generateMap(gameMap, gameSize, difficulty);

	unsigned int userInput = 1, x, y;
	while (userInput != 9)
	{
		std::cout << "Please input 2 positive numbers as coordinates x (row) and y (col) -- or 9 to close: ", std::cin >> userInput;
		if (userInput == 9)
			return 0;
		x = static_cast<unsigned int>(userInput / 10);
		y = static_cast<unsigned int>(userInput % 10);	
		gameMap[gameSize][gameSize] = lightPress(gameMap, gameSize, x, y);
		printMap(gameMap, gameSize);
		
		if (winCheck(gameMap, gameSize) == 1)
		{
			std::cout << "\n****************\n*** YOU WIN! ***\n****************\n";
			return 0;
		}
	}
}
