
#include "Core.hpp"

Core::Core(void)
{
	return ;
}

Core::Core(int &ac, char **av)
{
	int								i, j;
	std::list<Rule *>::iterator		it, ite;

	(void)ac;
	(void)av;
	if (ac < 2)
	{
		std::cerr << "You must provide an input file !" << std::endl;
		return ;
	}
	i = 0;
//	this->setFalse();
	this->parser.parseInputFile("inputs/input4", this->facts, this->verified, &this->queries, &this->rules);
	for (j = 1; j < ac; ++j)
	{
		std::cout << "----- " << av[j] << " -----" << std::endl;
		if (this->parser.parseInputFile(av[j], this->facts, this->verified, &this->queries, &this->rules) == PARSE_SUCCESS)
		{
			for (i = 0; i < 26; ++i)
			{
				if (this->facts[i] != true)
				{
					this->facts[i] = false;
					this->verified[i] = false;
				}
			}
	/*		ite = rules.end();
			for (it = rules.begin(); it != ite; it++)
			{
				std::cerr << (*it)->rpn << ": ";
				this->evaluateInference((*it)->rpn);
				std::cerr << std::endl;
			}*/
		}
	}
	this->tmp();
	return ;
}

void
Core::tmp(void)
{
	std::list<Rule *>::iterator		it, ite;
	int								i;
	int								j;
	int								k;

	i = 0;
	j = 0;
	k = 0;
	ite = rules.end();
	j = this->rules.size();
	while (i < j)
	{
		for (it = rules.begin(); it != ite; it++)
		{
			if(this->evaluateInference((*it)->rpn))
			{
				std::cerr << (*it)->rpn << " EST VRAI ET DONC ";
				std::cerr << (*it)->implied << std::endl;
				while ((*it)->implied[k] && isalpha((*it)->implied[k]))
				{
					this->facts[(*it)->implied[k] - 65] = true;
					k++;
				}
				k = 0;
			}
		}
		it = rules.begin();
		i++;
	}
	i = 0;
		std::cout << "RESULT " << std::endl;
	while (i < 26)
	{
		std::cout << (char)(i + 65) << this->facts[i]  << std::endl;
		i++;
	}
}


bool
Core::checkValidity(char letter, bool result)
{
	bool		test1;
	bool		test2;
	int const	index = letter - 'A';

	if (this->verified[index] == true)
		return (this->facts[index] == result);
	else
	{
		this->facts[index] = result;
		this->verified[index] = true;
		return (true);
	}
}

void
Core::setTrue(void)
{
	std::list<char>::iterator	it = this->queries.begin();

	while (it != this->queries.end())
	{
		this->setFact(*it, true);
		it++;
	}
	return ;
}

bool
Core::setFact(char letter, bool result)
{
	int const		index = letter - 'A';

	if (this->checkValidity(letter, result))
	{
		this->facts[index] = result;
		this->verified[index] = true;
		return (true);
	}
	else
	{
		std::cerr << std::boolalpha <<
			letter << " was first " <<
			facts[index] <<
			" and you try to set it at " <<
			result << std::endl;
		return (false);
	}
}

int
Core::evaluateInference(std::string const &rpn)
{
	std::list<bool>					vs; // values stack
	size_t							i;
	bool							res;

	i = 0;
	while (i < rpn.size())
	{
		if (rpn[i] >= 'A' && rpn[i] <= 'Z')
			vs.push_front(this->facts[rpn[i] - 'A']);
		else if (vs.size() > 1)
		{
			if (rpn[i] == '!')
				vs.front() = !vs.front();
			else
			{
				res = vs.front();
				vs.pop_front();
				if (rpn[i] == '+')
					vs.front() &= res;
				else if (rpn[i] == '|')
					vs.front() |= res;
				else if (rpn[i] == '^')
					vs.front() ^= res;
			}
		}
		else if (vs.size() > 0 && rpn[i] == '!')
			vs.front() = !vs.front();
		i++;
	}

	return (vs.front());
	//debug
/*	std::list<bool>::iterator		it;
	for (it = vs.begin(); it != vs.end(); it++)
	{
		std::cerr << "E";
		std::cerr << *it;
	}*/
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
		result = (*p)->implied.find(letter);
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
	return (((facts[l1 - 'A'] + neg1) % 2) || ((facts[l2 - 'A'] + neg2) % 2));
}

bool
Core::getXor(bool l1, bool l2, bool neg1, bool neg2)
{
	return (((l1 + neg1) % 2) + ((l2 + neg2) % 2) % 2);
}

bool
Core::getXor(char l1, char l2, bool neg1, bool neg2)
{
	return (((facts[l1 - 'A'] + neg1) % 2) + ((facts[l2 - 'A'] + neg2) % 2) % 2);
}

bool
Core::getAnd(bool l1, bool l2, bool neg1, bool neg2)
{
	return (((l1 + neg1) % 2) && ((l2 + neg2) % 2));
}

bool
Core::getAnd(char l1, char l2, bool neg1, bool neg2)
{
	return (((facts[l1 - 'A'] + neg1) % 2) && ((facts[l2 - 'A'] + neg2) % 2));
}

bool
Core::getState(char letter)
{
	return (facts[toupper(letter) - 'A']);
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
		o << letter << " " << std::boolalpha << i.facts[j];
		if (i.verified[j])
			o << " verified";
		o << "\n";
		++j;
	}
	j = 0;
	o << "\nListe des règles :\n";
	while (p != i.rules.end())
	{

		o << "Rule " << j << " : " << *(*p) << "\n";
		++p;
		++j;
	}
	o << std::endl;
	return (o);
}
