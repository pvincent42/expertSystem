
#ifndef		BTREE_HPP
# define	BTREE_HPP

# include <iostream>

class Btree
{
	public:
		Btree(void);
		~Btree(void);

		Btree & operator = (Btree const & rhs);

	private:
		Btree(Btree const & src);
};

std::ostream			&operator<<(std::ostream &o, Btree const &i);

#endif
