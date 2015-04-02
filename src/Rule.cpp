
#include "Rule.hpp"

Rule::Rule(void)
{
	return ;
}

Rule::Rule(std::string const &inference, std::string const &implied) : inference(inference), implied(implied)
{
	return ;
}

Rule::Rule(std::string const &inference, std::string const &implied, std::string const &rpn) : rpn(rpn), inference(inference), implied(implied)
{
	return ;
}

Rule::Rule(Rule const & src)
{
	*this = src;

	return ;
}

Rule::~Rule(void)
{
	return ;
}

Rule &
Rule::operator=(Rule const & rhs)
{
	if (this != &rhs)
	{
		this->inference = rhs.inference;
		this->implied = rhs.implied;
	}
	return (*this);
}

std::ostream&
operator<<(std::ostream &o, Rule const &i)
{
	o << "Class : Rule" << std::endl;
	o << i.inference << " => " << i.implied << std::endl;
	return (o);
}
