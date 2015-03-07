
#ifndef		CORE_HPP
# define	CORE_HPP

# include <iostream>

class Core
{
	public:
		Core(void);
		Core(Core const & src);
		~Core(void);

		bool			fact[26];

		void			setFact(char letter);
		Core & operator = (Core const & rhs);

	private:
};

std::ostream			&operator<<(std::ostream &o, Core const &i);

#endif
