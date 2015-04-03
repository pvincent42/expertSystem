
#include "Core.hpp"

Core::Core(void)
{
	return ;
}

Core::Core(int &ac, char **av)
{
	int								i, j;
	std::list<Rule *>::iterator		it, ite;

	if (ac < 2)
	{
		std::cerr << "You must provide an input file !" << std::endl;
		return ;
	}
	for (j = 1; j < ac; ++j)
	{
		std::cout << "----- " << av[j] << " -----" << std::endl;
		for (i = 0; i < 26; ++i)
		{
			this->facts[i] = false;
			this->verified[i] = false;
		}
		if (this->parser.parseInputFile(av[j], this->facts, this->verified, &this->queries, &this->rules) == PARSE_SUCCESS)
		{
			ite = rules.end();
			for (it = rules.begin(); it != ite; it++)
			{
				std::cerr << (*it)->rpn << ": ";
				this->evaluateInference((*it)->rpn);
				std::cerr << std::endl;
			}
			if (rules.size() > 0)
			{
				ite = rules.end();
				for (it = rules.begin(); it != ite; ++it)
					delete *it;
				rules.clear();
			}
		}
	}
	return ;
}
/*
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
*/
void
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
	//debug
	std::list<bool>::iterator		it;

	for (it = vs.begin(); it != vs.end(); it++)
		std::cerr << *it;
}
/*
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
*/
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
	o << "\nRules list :\n";
	while (p != i.rules.end())
	{

		o << "Rule " << j << " : " << *(*p) << "\n";
		++p;
		++j;
	}
	o << std::endl;
	return (o);
}
