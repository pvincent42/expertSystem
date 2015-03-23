
#ifndef		PARSER_HPP
# define	PARSER_HPP

# include <iostream>

class Parser
{
	public:
		Parser(void);
		~Parser(void);

		Parser & operator = (Parser const & rhs);

	private:
		Parser(Parser const & src);
};

std::ostream			&operator<<(std::ostream &o, Parser const &i);

#endif
