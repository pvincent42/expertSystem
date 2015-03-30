
#ifndef		RULE_HPP
# define	RULE_HPP

# include <iostream>

class Rule
{
	public:
		// rule example : A + B + (C | D) => G + E
		std::string			rpn; // reverse polish notation of the inference	: "AB+CD|+"
		std::string			inference; // inference, left part of the rule		: "A+B+(C|D)"
		std::string			result; // result, right part of the rule			: "G+E"

		Rule(void);
		Rule(std::string const & inference, std::string const & result);
		Rule(Rule const & src);
		~Rule(void);

		Rule & operator = (Rule const & rhs);

	private:
};

std::ostream			&operator<<(std::ostream &o, Rule const &i);

#endif
