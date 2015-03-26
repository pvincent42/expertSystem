
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
		int								parseInputFile(std::string const &filename, bool *facts, bool *verified, std::list<char> *queries, std::list<Rule *> *rules);
		int								parseRawRule(std::string const &rule, std::list<Rule *> *rules);

		Parser & operator = (Parser const & rhs);

	private:
		Parser(Parser const & src);

		bool							ruleCharValid(char const &c);
		bool							getInferenceFromRule(std::string const &r, int const &rule_length, std::string &inference);
		int								buildRPN(std::string const &f, std::string &rpn);
		int								printParsingError(std::string const &msg, int const &code);
};

std::ostream			&operator<<(std::ostream &o, Parser const &i);

#endif
