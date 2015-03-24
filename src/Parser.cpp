
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

	file = get_file_contents(filename);
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
	file_length = file.length();
	for (i = 0; i < file_length; ++i)
	{
		c = file[i];
		act = true;
		if (c == '\n')
		{
			if (state == GET_RULES && current_rule)
			{
				if (current_rule->length() != 0)
					raw_rules.push_back(current_rule);
				current_rule = 0;
			}
		}
		else if (c == '#')
		{
			// skip line
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
		if (act)
		{
			if (state == GET_FACTS)
			{
				if (c != ' ' && c != '\t')
				{
					if (c >= 'A' && c <= 'Z')
						facts[c - 65] = true;
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
						return (WRONG_QUERY);
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
		this->parseRawRule(*it, rules);
#ifdef _DEBUG
	// print parsed data
	for (std::list<std::string *>::iterator it = raw_rules.begin(); it != raw_rules.end(); it++)
		std::cerr << "rule  : [" << *(*it) << "]" << std::endl;
	for (std::list<char>::iterator it = queries->begin(); it != queries->end(); it++)
		std::cerr << "query : [" << *it << "]" << std::endl;
#endif
	return (PARSE_SUCCESS);
}

void
Parser::parseRawRule(std::string *rule, std::list<Rule *> *rules)
{
	int				i;
	int				rule_length;

	(void)rules;
	rule_length = rule->length();
	for (i = 0; i < rule_length; ++i)
	{
		
	}
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
	o << "Class : Parser" << std::endl;
	return (o);
}
