
#ifndef		CORE_HPP
# define	CORE_HPP

# include <iostream>
# include <list>
# include "Rule.hpp"
# include "Parser.hpp"

class Core
{
	public:
		Parser		parser;

		Core(void);
		Core(Core const & src);
		~Core(void);

		bool				facts[26];
		std::list<char>		queries;
		std::list<Rule *>	rules;

		void				setFact(char letter);
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
