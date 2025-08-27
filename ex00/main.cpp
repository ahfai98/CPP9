#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
	BitcoinExchange btc("data.csv");
	std::string line;
	if (!input.eof())
		std::getline(input, line);

	while (std::getline(input, line))
	{
		if (line.empty())
			continue;

		std::string dateStr, valueStr;
		std::size_t sep = line.find('|');
		if (sep == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		dateStr = line.substr(0, sep);
		valueStr = line.substr(sep + 1);
		btc.trim(dateStr);
		btc.trim(valueStr);
		if (!btc.isValidDate(dateStr))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (!btc.isValidValue(valueStr))
		{
			if (valueStr.find('e') != std::string::npos || valueStr.find('E') != std::string::npos)
			{
				std::cerr << "Error: bad input => " << line << std::endl;
				continue;
			}
			std::istringstream ss(valueStr);
			float val;
			ss >> val;
			if (ss.fail() || !ss.eof())
				std::cerr << "Error: bad input => " << line << std::endl;
			else if (val < 0.0f)
				std::cerr << "Error: not a positive number." << std::endl;
			else
				std::cerr << "Error: too large a number." << std::endl;
			continue;
		}
		float value;
		std::istringstream ss(valueStr);
		ss >> value;
		double result = btc.calculateValue(dateStr, value);
		if (result >= 0)
			std::cout << dateStr << " => " << value << " = " << result << std::endl;
		else
			std::cerr << "Error: could not find price for date " << dateStr << std::endl;
	}
	input.close();
	return (0);
}
