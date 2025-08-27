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
		BitcoinExchange(const std::string &dbFile);
		BitcoinExchange(const BitcoinExchange &src);
		~BitcoinExchange();
		BitcoinExchange &operator=(const BitcoinExchange &src);
		bool isValidDate(const std::string &date) const;
		bool isValidValue(const std::string &value) const;
		bool isLeapYear(int year) const;
		bool getClosestPrice(const std::string &date, float &price) const;
		double calculateValue(const std::string &date, float value) const;
		void trim(std::string &str) const;

	private:
		std::map<std::string, float> _btcDatabase;
};

#endif
