
#include "Rule.hpp"

Rule::Rule(void)
{
	return ;
}

Rule::Rule(std::string const & inference, std::string const & result) : inference(inference), result(result)
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
			this->result = rhs.result;
	}
	return (*this);
}

std::ostream&
operator<<(std::ostream &o, Rule const &i)
{
	o << "Class : Rule" << std::endl;
	o << i.inference << " => " << i.result << std::endl;
	return (o);
}
