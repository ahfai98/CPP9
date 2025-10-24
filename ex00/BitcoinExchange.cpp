#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>

BitcoinExchange::BitcoinExchange(const std::string &databaseFile)
{
	std::ifstream db(databaseFile.c_str());
	if (!db.is_open())
	{
		std::cerr << "Error: Could not open database." << std::endl;
		return;
	}
	std::string line;
	if (!db.eof())
		std::getline(db, line);
	while (std::getline(db, line))
	{
		if (line.empty())
			continue;
		std::istringstream ss(line);
		std::string date;
		std::string price;
		if (!std::getline(ss, date, ',') || !std::getline(ss, price))
			continue;
		trim_frontback_spaces(date);
		trim_frontback_spaces(price);
		if (!isValidDate(date) || !isValidValueDatabase(price))
			continue;
		float f_price = static_cast<float>(atof(price.c_str()));
		_btcDatabase[date] = f_price;
	}
	db.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	if (this != &src)
		_btcDatabase = src._btcDatabase;
}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
		_btcDatabase = src._btcDatabase;
	return (*this);
}

bool BitcoinExchange::isLeapYear(int year) const
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	std::string d = date;
	if (d.size() != 10 || d[4] != '-' || d[7] != '-')
		return (false);

	for (size_t i = 0; i < d.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(d[i]))
			return (false);
	}

	int year  = atoi(d.substr(0, 4).c_str());
	int month = atoi(d.substr(5, 2).c_str());
	int day   = atoi(d.substr(8, 2).c_str());

	if (year <= 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return (false);

	static const int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int maxDays = daysInMonth[month];
	if (month == 2 && isLeapYear(year))
		maxDays = 29;
	return (day <= maxDays);
}

bool BitcoinExchange::isValidValueInput(const std::string &value, float &input_value) const
{
	std::string s = value;
	//empty or scientific notation like 1e3 is rejected
	if (s.empty() || s.find('e') != std::string::npos || s.find('E') != std::string::npos)
	{
		std::cerr << "Error: bad input for value => " << value << std::endl;
		return (false);
	}
	std::string lower;
	for (size_t i = 0; i < s.size(); ++i)
		lower += std::tolower(static_cast<unsigned char>(s[i]));
	if (lower == "nan" || lower == "+nan" || lower == "-nan")
	{
		std::cerr << "Error: bad input for value => " << value << std::endl;
		return (false);
	}
	char *endptr = 0;
	errno = 0;
	double val = strtod(s.c_str(), &endptr);
	if (*endptr != '\0' || errno == ERANGE)
	{
		std::cerr << "Error: bad input for value => " << value << std::endl;
		return (false);
	}
	if (val < 0.0f)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	if (val > 1000.0f)
	{
		std::cerr << "Error: too large a number. => " << value << std::endl;
		return (false);
	}
	input_value = static_cast<float>(val);
	if (val != 0.0 && input_value == 0.0f)
    	std::cerr << "Warning: value underflowed to 0. => " << value << std::endl;
	return (true);
}

bool BitcoinExchange::isValidValueDatabase(const std::string &value) const
{
	std::string s = value;
	if (s.empty() || s.find('e') != std::string::npos || s.find('E') != std::string::npos)
		return (false);
	
	std::string lower;
	for (size_t i = 0; i < s.size(); ++i)
    	lower += std::tolower(static_cast<unsigned char>(s[i]));
	if (lower == "nan" || lower == "+nan" || lower == "-nan")
		return (false);
	char *endptr = 0;
	errno = 0;
	double val = strtod(s.c_str(), &endptr);
	if (*endptr != '\0' || val < 0.0 || errno == ERANGE)
		return (false);
	return (true);
}

bool BitcoinExchange::getClosestPrice(const std::string &date, float &price) const
{
	if (_btcDatabase.empty())
		return (false);
	std::map<std::string, float>::const_iterator it = _btcDatabase.lower_bound(date);
	if (it == _btcDatabase.begin() && it->first != date) 
		return (false);
	if (it == _btcDatabase.end() || it->first != date)
		--it;
	price = it->second;
	return (true);
}

bool BitcoinExchange::calculateValue(const std::string &date, float value, double &result) const
{
	float price = 0.0f;
	if (getClosestPrice(date, price))
	{
		result = static_cast<double>(price) * static_cast<double>(value);
		return (true);
	}
	return (false);
}

void BitcoinExchange::trim_frontback_spaces(std::string &str) const
{
	size_t start = str.find_first_not_of(" \t");
	if (start == std::string::npos)
	{
		str.clear();
		return;
	}
	size_t end = str.find_last_not_of(" \t");
	str = str.substr(start, end - start + 1);
}
