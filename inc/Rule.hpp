
#ifndef		RULE_HPP
# define	RULE_HPP

# include <iostream>

class Rule
{
	public:
		Rule(void);
		Rule(std::string const & inference, std::string const & result);
		Rule(Rule const & src);
		~Rule(void);

		std::string			inference;
		std::string			result;

		Rule & operator = (Rule const & rhs);

	private:
};

std::ostream			&operator<<(std::ostream &o, Rule const &i);

#endif
