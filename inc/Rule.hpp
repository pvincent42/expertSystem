
#ifndef		RULE_HPP
# define	RULE_HPP

# include <iostream>
# include "Tree.hpp"

class Rule
{
	public:
		Tree				tree;
		std::string			inference; // "A + B"
		std::string			result; // "C"

		Rule(void);
		Rule(std::string const & inference, std::string const & result);
		Rule(Rule const & src);
		~Rule(void);

		Rule & operator = (Rule const & rhs);

	private:
};

std::ostream			&operator<<(std::ostream &o, Rule const &i);

#endif
