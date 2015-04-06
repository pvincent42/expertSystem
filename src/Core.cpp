
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
	for (j = 1; j < ac; ++j)
	{
		this->parser.clean();
		for (i = 0; i < 26; ++i)
		{
			this->facts[i] = false;
			this->verified[i] = false;
		}
		std::cerr << "----- " << av[j] << " -----" << std::endl;
		if (this->parser.parseInputFile(av[j], this->facts, this->verified, &this->queries, &this->rules) == PARSE_SUCCESS)
			this->evaluate_input();
	}
	return ;
}

void
Core::evaluate_input(void)
{
	std::list<Rule *>::iterator		it, ite;
	int								i;
	int								j;
	int								k;
	std::string						implied;
	int								len;

	i = 0;
	j = this->rules.size();
	while (i < j)
	{
		it = rules.begin();
		ite = rules.end();
		while (it != ite)
		{
			if (this->evaluateInference((*it)->rpn))
			{
				std::cerr << (*it)->rpn << " is true, therefore ";
				implied.clear();
				len = (*it)->implied.length();
				for (k = 0; k < len; ++k)
				{
					if (isalpha((*it)->implied[k]))
						implied += (*it)->implied[k];
				}
				len = implied.length();
				k = 0;
				while (k < len)
				{
					std::cerr << implied[k];
					if (implied[k + 1] && implied[k + 2])
						std::cerr << ", ";
					else if (implied[k + 1])
						std::cerr << " and ";
					this->facts[implied[k] - 65] = true;
					k++;
				}
				if (k > 1)
					std::cerr << " are true." << std::endl;
				else if (k == 1)
					std::cerr << " is true." << std::endl;
			}
			++it;
		}
		i++;
	}
	i = 0;
	std::cerr << "----- RESULTS -----" << std::endl;
	while (i < 26)
	{
		std::cerr << (char)(i + 65) << ' ' << this->facts[i] << std::endl;
		i++;
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
*/
/*std::list <Rule *>
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
