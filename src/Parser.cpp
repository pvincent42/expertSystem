
#include <unistd.h>
#include <sys/stat.h>
#include "Parser.hpp"

Parser::Parser(void)
{
	return ;
}

Parser::~Parser(void)
{
	return ;
}

static std::string
get_file_contents(const std::string &filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);

	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	}
	throw (errno);
}

int
Parser::parseInputFile(std::string const &filename, bool *facts, bool *verified, std::list<char> *queries, std::list<Rule *> *rules)
{
	char			c;
	std::string		*current_rule = 0;
	int				state = GET_RULES;
	bool			act = false;
	struct stat		buffer;
	std::string		file;
	int				i;
	int				file_length;

	// check file
	if (access(filename.c_str(), R_OK) == -1)
	{
		perror(filename.c_str());
		return (READ_FILE_ERROR);
	}
	if (stat(filename.c_str(), &buffer) != 0)
	{
		std::cerr << "Can't open file: " << filename << std::endl;
		return (OPEN_FILE_ERROR);
	}
	(void)rules;
	// read file in a string
	file = get_file_contents(filename);
	file_length = file.length();
	// begin parsing
	i = 0;
	while (i < file_length)
	{
		// each iteration works on a single character
		c = file[i];
		act = true;
		if (c == '\n')
		{
			// add rule
			if (state == GET_RULES && current_rule)
			{
				if (current_rule->length() != 0)
					raw_rules.push_back(current_rule);
				current_rule = 0;
			}
		}
		else if (c == '#')
		{
			// search for end of line
			for (; i < file_length; ++i)
			{
				c = file[i];
				if (c == '\n')
				{
					act = false;
					state = GET_RULES;

					i--;
					break ;
				}
			}
			if (act)
				break ;
		}
		else if (!current_rule && c == '=')
		{
			state = GET_FACTS;
			act = false;
		}
		else if (!current_rule && c == '?')
		{
			state = GET_QUERIES;
			act = false;
		}
		// do not "act" on this character, ['\n', '=', '?']
		if (act)
		{
			if (state == GET_FACTS)
			{
				if (c != ' ' && c != '\t')
				{
					if (c >= 'A' && c <= 'Z')
					{
						facts[c - 'A'] = true;
						verified[c - 'A'] = true;
					}
					else
					{
						std::cerr << "Wrong fact : [" << c << "]" << std::endl;
						return (WRONG_FACT);
					}
				}
			}
			else if (state == GET_QUERIES)
			{
				if (c != ' ' && c != '\t')
				{
					if (c >= 'A' && c <= 'Z')
						queries->push_back(c);
					else
					{
						std::cerr << "Wrong query : [" << c << "]" << std::endl;
						return (WRONG_QUERY);
					}
				}
			}
			else
			{
				if (c != '\n' && !current_rule)
					current_rule = new std::string();
				if (c != ' ' && c != '\t' && c != '\n')
					*current_rule += c;
			}
		}
		++i;
	}
	if (state == GET_RULES && current_rule)
	{
		raw_rules.push_back(current_rule);
		current_rule = 0;
	}
#ifdef _DEBUG
	// print parsed data
	for (std::list<std::string *>::iterator it = raw_rules.begin(); it != raw_rules.end(); it++)
		std::cerr << "rule  : [" << *(*it) << "]" << std::endl;
	for (std::list<char>::iterator it = queries->begin(); it != queries->end(); it++)
		std::cerr << "query : [" << *it << "]" << std::endl;
#endif
	// parse rules
	for (std::list<std::string *>::iterator it = raw_rules.begin(); it != raw_rules.end(); it++)
		this->parseRawRule(*(*it), rules);
	return (PARSE_SUCCESS);
}

bool
Parser::ruleCharValid(char const &c)
{
	if ((c >= 'A' && c <= 'Z')
		|| c == '+'
		|| c == '^'
		|| c == '|'
		|| c == '!'
		|| c == '('
		|| c == ')')
		return (true);
	return (false);
}

int
Parser::printParsingError(std::string const &msg, int const &code)
{
	std::cerr << msg << std::endl;
	return (code);
}

// at this point all characters are valid
// given inference, creates RPN
int
Parser::buildRPN(std::string const &f, std::string &rpn)
{
	register int		i, j;
	int const			length = f.length();
	int					result;
	char				o;
	static int const	arg = [1, 2, 2, 2]; // number of operands (sorted by priority)
	static char const	opr = ['!', '+', '|', '^'] // operators (sorted by priority)
	int					stack_size;
	bool				stack[3]; // to keep track of the results
	

	// just in case
	rpn.clear();
	// build rpn for later evaluation, and get immediate result
	stack_size = 0;
	for (i = 0; i < length; ++i)
	{
		if (f[i] >= 'A' && f[i] <= 'Z')
		{
			rpn += f[i];
			++stack_size;
		}
		else
		{
			for (j = 0; j < 4; ++j)
			{
				if (f[i] == opr[j])
				{
					if (stack_size > arg[j])
					{

					}
					break ;
				}
			}
		}
	}
	return (1);
}

// ! 33, + 43, | 124, ^ 94 

bool
Parser::getInferenceFromRule(std::string const &r, int const &rule_length, std::string &inference)
{
	for (int i = 0; i < rule_length; ++i)
	{
		if (r[i] == '=' && i + 1 < rule_length && r[i + 1] == '>')
		{
			inference = r.substr(0, i);
			return (true);
		}
		if (!ruleCharValid(r[i]))
			return (false);
	}
	return (true);
}

int
Parser::parseRawRule(std::string const &r, std::list<Rule *> *rules)
{
	int						i;
	int const				rule_length = r.length();
	std::string				inference;
	std::string				rpn;

	(void)rules;
	i = 0;
	// only checks for character validity
	if (!getInferenceFromRule(r, rule_length, inference))
		return (0);
	buildRPN(inference, rpn);
	std::cerr << "inference: " << inference << " -- RPN: " << rpn << std::endl;
	return (1);
}

Parser &
Parser::operator=(Parser const & rhs)
{
	if (this != &rhs)
	{
	}
	return (*this);
}

std::ostream&
operator<<(std::ostream &o, Parser const &i)
{
	(void)i;
	o << "Class : Parser : " << &i << std::endl;
	return (o);
}
