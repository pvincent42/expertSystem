
#include "Btree.hpp"

Btree::Btree(void)
{
	return ;
}

Btree::~Btree(void)
{
	return ;
}

Btree &
Btree::operator=(Btree const & rhs)
{
	if (this != &rhs)
	{
	}
	return (*this);
}

std::ostream&
operator<<(std::ostream &o, Btree const &i)
{
	o << "Class : Btree : " << &i << std::endl;
	return (o);
}
