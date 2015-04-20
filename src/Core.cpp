
#include "Core.hpp"

Core::Core(void)
{
	return ;
}

Core::Core(int &ac, char **av)
{
	int								j;
	std::list<Rule *>::iterator		it, ite;
	std::list<char>::iterator		qit;

	(void)ac;
	(void)av;
	if (ac < 2)
	{
		std::cerr << "You must provide an input file !" << std::endl;
		return ;
	}
	for (j = 1; j < ac; ++j)
	{
		this->parser.clean();
		this->clean();
		std::cerr << "----- " << av[j] << " -----" << std::endl;
		if (this->parser.parseInputFile(av[j], this->facts, this->verified, &this->queries, &this->rules) == PARSE_SUCCESS)
		{
			this->evaluate_input();
			qit = this->queries.begin();
			std::cerr << std::endl;
			while (qit != this->queries.end())
			{
				std::cerr << *qit << " is ";
				if (this->facts[*qit - 65])
					std::cerr << "\033[1;32m";
				else
					std::cerr << "\033[1;31m";
				std::cerr << std::boolalpha << this->facts[*qit - 65] << std::endl << "\033[0m";
				qit++;
			}
		}
	}

	return ;
}

void
Core::clean(void)
{
	std::list<Rule *>::iterator		it, ite;
	int								i;

	for (i = 0; i < 26; ++i)
	{
		this->facts[i] = false;
		this->verified[i] = false;
	}
	this->queries.clear();
	if (this->rules.size() > 0)
	{
		for (it = this->rules.begin(), ite = this->rules.end(); it != ite; ++it)
			delete *it;
		this->rules.clear();
	}
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
	std::cerr << std::endl;
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

Core::~Core(void)
{
	this->clean();
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
