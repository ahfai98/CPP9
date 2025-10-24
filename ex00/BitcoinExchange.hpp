#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cstdlib>
#include <limits>

class BitcoinExchange
{
	public:
		BitcoinExchange(const std::string &databaseFile);
		BitcoinExchange(const BitcoinExchange &src);
		~BitcoinExchange();
		BitcoinExchange &operator=(const BitcoinExchange &src);
		bool isValidDate(const std::string &date) const;
		bool isValidValueInput(const std::string &value, float &input_value) const;
		bool isValidValueDatabase(const std::string &value) const;
		bool isLeapYear(int year) const;
		bool getClosestPrice(const std::string &date, float &price) const;
		bool calculateValue(const std::string &date, float value, double &result) const;
		void trim_frontback_spaces(std::string &str) const;

	private:
		std::map<std::string, float> _btcDatabase;
};

#endif
