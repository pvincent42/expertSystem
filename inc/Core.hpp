
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

		int					evaluateInference(std::string const &rpn);
		void				evaluate_input(void);

		Core & operator = (Core const & rhs);

	private:
		Core(Core const & src);

		void				clean(void);
};

std::ostream			&operator<<(std::ostream &o, Core const &i);

#endif
