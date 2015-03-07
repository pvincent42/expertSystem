
#ifndef		CORE_HPP
# define	CORE_HPP

# include <iostream>
# include <list>
# include <Rule.hpp>

class Core
{
	public:
		Core(void);
		Core(Core const & src);
		~Core(void);

		bool				fact[26];
		std::list<Rule *>	ruleList;

		void				setFact(char letter);
		void				addRule(Rule *rule);
		bool				getAnd(char l1, char l2, bool neg1, bool neg2);
		bool				getOr(char l1, char l2, bool neg1, bool neg2);
		bool				getXor(char l1, char l2, bool neg1, bool neg2);
		std::list<Rule *>	getRule(char letter);

		Core & operator = (Core const & rhs);

	private:
};

std::ostream			&operator<<(std::ostream &o, Core const &i);

#endif
