#include "RPN.hpp"

RPN::RPN(){}

RPN::RPN(const RPN &src)
{
	(void)src;
}

RPN::~RPN(){}

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
				throw RPNException("Error: Division by zero");
			return (lhs / rhs);
		default:
			throw RPNException("Error: Invalid Operator");
	}
}

bool RPN::isNumber(const std::string &token) const
{
	if (token.empty())
		return (false);
	else if (token.size() == 2 && token[0] == '-')
		return (isdigit(token[1]));
	return(token.size() == 1 && isdigit(token[0]));
}

long RPN::calculate(const std::string &str) const
{
	std::stack<long> stk;
	std::istringstream iss(str);
	std::string token;

	while (iss >> token)
	{
		if (isNumber(token))
		{
			char *endptr;
			long num = strtol(token.c_str(), &endptr, 10);
			if (*endptr != '\0')
				throw RPNException("Error: Invalid number.");
			stk.push(num);
		}
		else if (token.size() == 1 && isOperator(token[0]))
		{
			if (stk.size() < 2)
				throw RPNException("Error: not enough operands.");
			long rhs = stk.top();
			stk.pop();
			long lhs = stk.top();
			stk.pop();
			long result = applyOperator(lhs, rhs, token[0]);
			stk.push(result);
		}
		else
			throw RPNException("Error: Invalid Token.");
	}
	if (stk.size() != 1)
		throw RPNException("Error: Invalid Input.(More than 1 number left)");
	return (stk.top());
}
