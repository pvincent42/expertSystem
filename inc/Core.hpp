
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
		bool				verified[26];
		std::list<Rule *>	ruleList;

		bool				checkValidity(char lettre, bool result);
		void				setFact(char letter, bool result);
		void				addRule(Rule *rule);
		bool				getAnd(bool l1, bool l2, bool neg1, bool neg2);
		bool				getAnd(char l1, char l2, bool neg1, bool neg2);
		bool				getOr(bool l1, bool l2, bool neg1, bool neg2);
		bool				getOr(char l1, char l2, bool neg1, bool neg2);
		bool				getXor(bool l1, bool l2, bool neg1, bool neg2);
		bool				getXor(char l1, char l2, bool neg1, bool neg2);
		bool				getState(char letter);
		std::list<Rule *>	getRule(char letter);

		Core & operator = (Core const & rhs);

	private:
};

std::ostream			&operator<<(std::ostream &o, Core const &i);

#endif
