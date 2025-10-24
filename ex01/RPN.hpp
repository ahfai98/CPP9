#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stdexcept>
# include <stack>
# include <cctype>
# include <sstream>
# include <cmath>

class RPN
{
	public:
		RPN();
		RPN(const RPN &src);
		~RPN();
		RPN &operator=(const RPN &src);
		long calculate(const std::string &str) const;
		class RPNException : public std::exception
		{
			private:
				std::string msg;
			public:
				RPNException(const std::string &m): msg(m){}
				virtual const char* what() const throw() {return msg.c_str();}
				virtual ~RPNException() throw(){}
		};
	private:
		bool isOperator(const char &token) const;
		long applyOperator(long lhs, long rhs, char op) const;
		bool isNumber(const std::string &token) const;
};

#endif
