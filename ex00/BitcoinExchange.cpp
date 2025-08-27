#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &dbFile)
{
	std::ifstream db(dbFile.c_str());
	if (!db.is_open())
	{
		std::cerr << "Error: Could not open database." << std::endl;
		return;
	}

	std::string line;
	while (std::getline(db, line))
	{
		if (line.empty())
			continue;
		std::istringstream ss(line);
		std::string date, price;
		if (!std::getline(ss, date, ',') || !std::getline(ss, price))
			continue;
		trim(date);
		trim(price);
		float f_price = atof(price.c_str());
		_btcDatabase[date] = f_price;
	}
	db.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	if (this != &src)
	{
		_btcDatabase = src._btcDatabase;
	}
}

BitcoinExchange::~BitcoinExchange()
{
}

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
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	for (size_t i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(date[i]))
			return (false);
	}

	int year  = atoi(date.substr(0, 4).c_str());
	int month = atoi(date.substr(5, 2).c_str());
	int day   = atoi(date.substr(8, 2).c_str());

	if (year <= 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return (false);

	int daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (month == 2 && isLeapYear(year))
		daysInMonth[2] = 29;

	return (day <= daysInMonth[month]);
}


bool BitcoinExchange::isValidValue(const std::string &value) const
{
	std::string s = value;
	trim(s);
	if (s.empty())
		return (false);
	if (s.find('e') != std::string::npos || s.find('E') != std::string::npos)
		return (false);
	std::istringstream ss(value);
	float temp;
	ss >> temp;
	//conversion failed or there are remaining characters not read
	if (ss.fail() || !ss.eof())
		return (false);
	if (temp < 0.0f || temp > 1000.0f) 
		return (false);
	return (true);
}

bool BitcoinExchange::getClosestPrice(const std::string &date, float &price) const
{
	std::map<std::string, float>::const_iterator it = _btcDatabase.lower_bound(date);

	if (it == _btcDatabase.end() || it->first != date)
	{
		if (it == _btcDatabase.begin()) 
			return (false);
		--it;
	}
	price = it->second;
	return (true);
}

double BitcoinExchange::calculateValue(const std::string &date, float value) const
{
	float price = 0;
	double dvalue = 0;
	if (getClosestPrice(date, price))
	{
		dvalue = static_cast<double>(price) * static_cast<double>(value);
		return (dvalue);
	}
	return (-1);
}

void BitcoinExchange::trim(std::string &str) const
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
