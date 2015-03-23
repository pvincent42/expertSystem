
#include "Parser.hpp"

Parser::Parser(void)
{
	return ;
}

Parser::~Parser(void)
{
	return ;
}

Parser &
Parser::operator=(Parser const & rhs)
{
	if (this != &rhs)
	{
	}
	return (*this);
}

std::ostream&
operator<<(std::ostream &o, Parser const &i)
{
	(void)i;
	o << "Class : Parser" << std::endl;
	return (o);
}
