
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
		std::list<Rule *>	ruleList;

		void				setFact(char letter);
		void				addRule(Rule *rule);

		Core & operator = (Core const & rhs);

	private:
};

std::ostream			&operator<<(std::ostream &o, Core &i);

#endif
