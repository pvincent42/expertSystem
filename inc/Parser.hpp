
#ifndef		PARSER_HPP
# define	PARSER_HPP

# include <iostream>
# include <sstream>
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
		int								parseRawRule(std::string const &rule, std::list<Rule *> *rules, int const &number);
		void							clean(void);

		Parser & operator = (Parser const & rhs);

	private:
		Parser(Parser const & src);

		bool							ruleCharValid(char const &c);
		bool							getPartsFromRule(std::string const &r, int const &rule_length, std::string &inference, std::string &implied);
		int								buildRPN(std::string const &f, std::string &rpn);
		int								printError(std::ostream &msg, int const &code);
		int								printError(std::string const &msg, int const &code);
		bool							check_syntax_error(std::string const &e, int const &rule_number);
		bool							check_for_bonus_in_implied(std::string const &implied, int const &number);
};

std::ostream			&operator<<(std::ostream &o, Parser const &i);

#endif
