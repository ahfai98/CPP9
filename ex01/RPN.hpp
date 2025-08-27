#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stdexcept>
# include <stack>
# include <cctype>
#include <sstream>

class RPN
{
	public:
		RPN();
		RPN(const RPN &src);
		~RPN();
		RPN &operator=(const RPN &src);
		long calculate(const std::string &str) const ;

	private:
		bool isOperator(const char &token) const;
		long applyOperator(long lhs, long rhs, char op) const;
		bool isNumber(const char &token) const;
};

#endif
