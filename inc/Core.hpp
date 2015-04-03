
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
		Core(int &ac, char **av);
		~Core(void);

		bool				facts[26];
		bool				verified[26];
		std::list<char>		queries;
		std::list<Rule *>	rules;

		void				evaluateInference(std::string const &rpn);
		bool				checkValidity(char lettre, bool result);
		void				setTrue(void);
		void				setFalse(void);
		bool				setFact(char letter, bool result);
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
		Core(Core const & src);
};

std::ostream			&operator<<(std::ostream &o, Core const &i);

#endif
