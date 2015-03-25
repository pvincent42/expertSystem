
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
Parser::parseInputFile(std::string const &filename, bool *facts, std::list<char> *queries, std::list<Rule *> *rules)
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
	for (i = 0; i < file_length; ++i)
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
						facts[c - 'A'] = true;
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
	}
	if (state == GET_RULES && current_rule)
	{
		raw_rules.push_back(current_rule);
		current_rule = 0;
	}
	// parse rules
	for (std::list<std::string *>::iterator it = raw_rules.begin(); it != raw_rules.end(); it++)
		this->parseRawRule(*(*it), rules);
#ifdef _DEBUG
	// print parsed data
	for (std::list<std::string *>::iterator it = raw_rules.begin(); it != raw_rules.end(); it++)
		std::cerr << "rule  : [" << *(*it) << "]" << std::endl;
	for (std::list<char>::iterator it = queries->begin(); it != queries->end(); it++)
		std::cerr << "query : [" << *it << "]" << std::endl;
#endif
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

// notes:
// - go through string and check for invalid characters, eventually return an error.
// - go through string and check ^, |, (
// -- when you get a ^ or a | go back to the first + or ) and go forth to the first + or (
// -- when you get a ( go to the first ), creating a string for recursive call
// -- push onto the stack

int
Parser::buildInference(std::string const &r, int &i, int const &length)
{
	for (; i < length; ++i)
	{
		if (!ruleCharValid(r[i]))
			return (0);
	}
	return (1);
}

int
Parser::parseRawRule(std::string const &r, std::list<Rule *> *rules)
{
	int						i;
	int const				rule_length = r.length();
	std::string				result;

	(void)rules;
	i = 0;
	buildInference(r, i, rule_length);
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
