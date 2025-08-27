#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &src)
{
	(void)src;
}

RPN::~RPN()
{
}

RPN &RPN::operator=(const RPN &src)
{
	(void)src;
	return (*this);
}

bool RPN::isOperator(const char &token) const
{
	return (token == '+' || token == '-' ||token == '*' ||token == '/');
}

long RPN::applyOperator(long lhs, long rhs, char op) const
{
	switch (op)
	{
		case '+': return (lhs + rhs);
		case '-': return (lhs - rhs);
		case '*': return (lhs * rhs);
		case '/':
			if (rhs == 0)
				throw std::runtime_error("Error: Division by zero");
			return (lhs / rhs);
		default:
			throw std::runtime_error("Error: Invalid Operator");
	}
}

bool RPN::isNumber(const char &token) const
{
	return(std::isdigit(token));
}

long RPN::calculate(const std::string &str) const
{
	std::stack<long> stk;
	std::istringstream iss(str);
	std::string token;

	while (iss >> token)
	{
		if (token.size() != 1)
			throw std::runtime_error("Error: Invalid Input.");
		else
		{
			char c = token[0];
			if (isNumber(c))
				stk.push(c - '0');
			else if (isOperator(c))
			{
				if (stk.size() < 2)
					throw std::runtime_error("Error: not enough operands.");
				long rhs = stk.top();
				stk.pop();
				long lhs = stk.top();
				stk.pop();
				long result = applyOperator(lhs, rhs, c);
				stk.push(result);
			}
			else
				throw std::runtime_error("Error: Invalid Token.");
		}
	}
	if (stk.size() != 1)
		throw std::runtime_error("Error: Invalid Input.(More than 1 number left)");
	return (stk.top());
}
