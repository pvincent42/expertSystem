
#include "Core.hpp"

Core::Core(void)
{
	int		i;

	i = 0;
	while (i < 26)
	{
		this->facts[i] = false;
		this->verified[i] = false;
		i++;
	}
	std::cerr << this->parser.parseInputFile("inputs/input1", this->facts, &this->queries, &this->rules) << std::endl;
	return ;
}

Core::Core(Core const & src)
{
	*this = src;

	return ;
}

bool
Core::checkValidity(char letter, bool result)
{
	bool		test1;
	bool		test2;

	if (this->verified[letter - 65] == 1)
	{
		if (this->facts[letter - 65] == result)
			return (true);
		else
			return (false);
	}
	else
	{
		this->facts[letter - 65] = result;
		this->verified[letter - 65] = true;
		return (true);
	}
}

bool
Core::setFact(char letter, bool result)
{
	if (this->checkValidity(letter, result))
	{
		this->facts[letter - 65] = result;
		this->verified[letter - 65] = true;
		return true;
	}
	else
	{
		std::cerr << std::boolalpha <<
			letter << " was first " <<
			facts[letter - 65] <<
			" and you try to set it at " <<
			result << std::endl;
		return (false);
	}
}


void
Core::setFalse(void)
{
	char				i;
	std::list<Rule *>	result;

	i = 'A';
	while (i <= 'Z')
	{
		result = this->getRule(i);
		if (result.size() == 0 && !this->verified[i - 65])
			this->setFact(i, false);
		i++;
	}
}

void
Core::addRule(Rule *rule)
{
	this->rules.push_back(rule);
	return ;
}

std::list <Rule *>
Core::getRule(char letter)
{
	std::size_t					result;
	std::list<Rule *>			resultList;
	std::list<Rule *>::iterator	p = this->rules.begin();

	letter = toupper(letter);
	while (p != this->rules.end())
	{
		result = (*p)->result.find(letter);
		if (result != std::string::npos)
			resultList.push_back(*p);
		++p;
	}
	return resultList;
}

bool
Core::getOr(bool l1, bool l2, bool neg1, bool neg2)
{
	return (((l1 + neg1) % 2) || ((l2 + neg2) % 2));
}

bool
Core::getOr(char l1, char l2, bool neg1, bool neg2)
{
	l1 = toupper(l1);
	l2 = toupper(l2);

	return (((facts[l1 - 65] + neg1) % 2) || ((facts[l2 - 65] + neg2) % 2));
}

bool
Core::getXor(bool l1, bool l2, bool neg1, bool neg2)
{
	return (((l1 + neg1) % 2) + ((l2 + neg2) % 2) % 2);
}

bool
Core::getXor(char l1, char l2, bool neg1, bool neg2)
{
	l1 = toupper(l1);
	l2 = toupper(l2);

	return (((facts[l1 - 65] + neg1) % 2) + ((facts[l2 - 65] + neg2) % 2) % 2);
}

bool
Core::getAnd(bool l1, bool l2, bool neg1, bool neg2)
{
	return (((l1 + neg1) % 2) && ((l2 + neg2) % 2));
}

bool
Core::getAnd(char l1, char l2, bool neg1, bool neg2)
{
	l1 = toupper(l1);
	l2 = toupper(l2);

	return (((facts[l1 - 65] + neg1) % 2) && ((facts[l2 - 65] + neg2) % 2));
}

bool
Core::getState(char letter)
{
	return (facts[toupper(letter) - 65]);
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
	std::list<Rule *>::const_iterator p = i.rules.begin();

	j = 0;
	o << "Class : Core " << '\n';
	o << "Facts :" << '\n';
	while (j < 26)
	{
		letter = 'A' + j;
		o << letter << " " << std::boolalpha << i.facts[j] << " verified " << i.verified[j] << "\n";
		++j;
	}
	j = 0;
	while (p != i.rules.end())
	{

		o << "Rule " << j << " : " << *(*p) << "\n";
		++p;
		++j;
	}
	o << std::endl;
	return (o);
}
