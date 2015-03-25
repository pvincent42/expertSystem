
#ifndef		PARSER_HPP
# define	PARSER_HPP

# include <iostream>
# include <fstream>
# include <list>
# include "Constants.hpp"
# include "Rule.hpp"

class Parser
{
	public:
		std::list<std::string *>		raw_rules;

		Parser(void);
		~Parser(void);
		int								parseInputFile(std::string const &filename, bool *facts, std::list<char> *queries, std::list<Rule *> *rules);
		void							parseRawRule(std::string *rule, std::list<Rule *> *rules);

		Parser & operator = (Parser const & rhs);

	private:
		Parser(Parser const & src);
};

std::ostream			&operator<<(std::ostream &o, Parser const &i);

#endif
