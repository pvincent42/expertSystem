
#ifndef		PARSER_HPP
# define	PARSER_HPP

# include <iostream>
# include <fstream>
# include <list>
# include "Rule.hpp"

# define GET_RULES			0
# define GET_FACTS			1
# define GET_QUERIES		2

# define PARSE_SUCCESS		1
# define WRONG_FACT			-1
# define WRONG_QUERY		-2
# define READ_FILE_ERROR	-3
# define OPEN_FILE_ERROR	-4

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
