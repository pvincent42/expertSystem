
#include "Core.hpp"

Core::Core(void)
{
	int		i;

	i = 0;
	while (i < 26)
	{
		this->fact[i] = false;
		i++;
	}
	return ;
}

Core::Core(Core const & src)
{
	*this = src;

	return ;
}

void
Core::setFact(char letter)
{
	if (letter >= 65 && letter <= 90)
		this->fact[letter - 65] = true;
	else if (letter >= 97 && letter <= 122)
		this->fact[letter - 97] = true;
	else
		std::cerr << letter << " isn't a letter" << std::endl;
	return ;
}

void
Core::addRule(Rule	*rule)
{
	this->ruleList.push_back(rule);
	return ;
}

std::list <Rule *>
Core::getRule(char letter)
{
	std::size_t					result;
	std::list<Rule *>			resultList;
	std::list<Rule *>::iterator	p = this->ruleList.begin();

	letter = toupper(letter);
	while (p != this->ruleList.end())
	{
		result = (*p)->result.find(letter);
		if (result != std::string::npos)
			resultList.push_back(*p);
		++p;
	}
	return resultList;
}

Core::~Core(void)
{
	return ;
}

Core &
Core::operator=(Core const & rhs)
{
	if (this != &rhs)
	{
			//// PUT VALUE HERE
			//// this-> val = rhs.getVal();
	}
	return (*this);
}

std::ostream&
operator<<(std::ostream &o, Core const &i)
{
	int		j;
	char	letter;
	std::list<Rule *>::const_iterator p = i.ruleList.begin();

	j = 0;
	o << "Class : Core " << '\n';
	o << "Fact :" << '\n';
	while (j < 26)
	{
		letter = 'A' + j;
		o << letter << " " << i.fact[j] << "\n";
		++j;
	}
	j = 0;
	while (p != i.ruleList.end())
	{

		o << "Rule " << j << " : " << *(*p) << "\n";
		++p;
		++j;
	}
	o << std::endl;
	return (o);
}
