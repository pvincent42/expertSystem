
#ifndef		TREE_HPP
# define	TREE_HPP

# include <iostream>
# include <list>

class Tree
{
	public:
		std::list<Tree *>		children;

		Tree(void);
		~Tree(void);

		Tree & operator = (Tree const & rhs);

	private:
		Tree(Tree const & src);
};

std::ostream			&operator<<(std::ostream &o, Tree const &i);

#endif
