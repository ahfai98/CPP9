#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		std::cout << "Usage: ./btc <filename>" << std::endl;
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
		std::size_t sep = line.find('|');
		if (sep == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		std::string dateStr = line.substr(0, sep);
		std::string valueStr = line.substr(sep + 1);
		btc.trim_frontback_spaces(dateStr);
		btc.trim_frontback_spaces(valueStr);
		float input_value = 0.0f;
		if (!btc.isValidDate(dateStr))
		{
			std::cerr << "Error: bad input for date => " << line << std::endl;
			continue;
		}
		if (!btc.isValidValueInput(valueStr, input_value))
			continue;
		double result = 0.0;
		if (btc.calculateValue(dateStr, input_value, result))
			std::cout << dateStr << " => " << input_value << " = " << result << std::endl;
		else
			std::cerr << "Error: could not find price for date " << dateStr << std::endl;
	}
	input.close();
	return (0);
}
