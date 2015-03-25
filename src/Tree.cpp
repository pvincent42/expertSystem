
#include "Tree.hpp"

Tree::Tree(void)
{
	return ;
}

Tree::~Tree(void)
{
	return ;
}

Tree &
Tree::operator=(Tree const & rhs)
{
	if (this != &rhs)
	{
	}
	return (*this);
}

std::ostream&
operator<<(std::ostream &o, Tree const &i)
{
	o << "Class : Tree : " << &i << std::endl;
	return (o);
}
