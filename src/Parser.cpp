
#include <unistd.h>
#include <sys/stat.h>
#include "Parser.hpp"

Parser::Parser(void)
{
	return ;
}

Parser::~Parser(void)
{
	this->clean();
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
	char									c;
	std::string								*current_rule = 0;
	int										state = GET_RULES;
	bool									act = false;
	struct stat								buffer;
	std::string								file;
	int										i;
	int										file_length;
	std::list<std::string *>::iterator		it_s, ite_s;
	std::list<char>::iterator				it_c, ite_c;

	// check file
	if (access(filename.c_str(), R_OK) == -1)
	{
		perror(filename.c_str());
		return (READ_FILE_ERROR);
	}
	if (stat(filename.c_str(), &buffer) != 0)
		return (printError(std::ostringstream().flush() << "Can't open file: " << filename, OPEN_FILE_ERROR));
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
		// do not "act" on these characters, ['\n', '=', '?']
		if (act)
		{
			if (state == GET_FACTS)
			{
				if (c != ' ' && c != '\t' && c != '\n')
				{
					if (c >= 'A' && c <= 'Z')
					{
						facts[c - 'A'] = true;
						verified[c - 'A'] = true;
					}
					else
						return (printError(std::ostringstream().flush() << "Wrong fact : [" << c << "]", WRONG_FACT));
				}
			}
			else if (state == GET_QUERIES)
			{
				if (c != ' ' && c != '\t' && c != '\n')
				{
					if (c >= 'A' && c <= 'Z')
						queries->push_back(c);
					else
						return (printError(std::ostringstream().flush() << "Wrong query : [" << c << "]", WRONG_QUERY));
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
	// check raw rules
	if (raw_rules.size() == 0)
		return (printError("No rules !", NO_RULES));
	i = 0;
	it_s = raw_rules.begin();
	ite_s = raw_rules.end();
	while (it_s != ite_s)
	{
		if ((*it_s)->size() == 0)
			return (printError(std::ostringstream().flush() << "Rule " << i << " is empty !", EMPTY_RULE));
		++it_s;
		++i;
	}
	// check queries and facts
	for (i = 0; i < 26; ++i)
	{
		if (facts[i])
			break;
	}
	if (i == 26)
		return (printError("No facts !", WRONG_FACT));
	if (queries->size() == 0)
		return (printError("No queries !", WRONG_QUERY));
#ifdef _DEBUG
	// print parsed data
	for (it_s = raw_rules.begin(); it_s != raw_rules.end(); it_s++)
		std::cerr << "rule  : [" << *(*it_s) << "]" << std::endl;
	for (it_c = queries->begin(); it_c != queries->end(); it_c++)
		std::cerr << "query : [" << *it_c << "]" << std::endl;
#endif
	// parse rules
	i = 1;
	for (it_s = raw_rules.begin(); it_s != raw_rules.end(); it_s++)
	{
		if (!this->parseRawRule(*(*it_s), rules, i))
			return (PARSE_FAIL);
		++i;
	}
	// delete raw rules
	return (PARSE_SUCCESS);
}

void
Parser::clean(void)
{
	std::list<std::string *>::iterator		it_s, ite_s;

	if (this->raw_rules.size() > 0)
	{
		ite_s = raw_rules.end();
		for (it_s = this->raw_rules.begin(); it_s != ite_s; ++it_s)
			delete *it_s;
		this->raw_rules.clear();
	}
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
Parser::printError(std::ostream &msg, int const &code)
{
	std::cerr << dynamic_cast<std::ostringstream &>(msg).str() << std::endl;
	return (code);
}

int
Parser::printError(std::string const &msg, int const &code)
{
	std::cerr << msg << std::endl;
	return (code);
}

bool
Parser::check_syntax_error(std::string const &e, int const &rule_number)
{
	int						i, j;
	int						len = e.length();
	static int const		op_n[3] = {3, 5, 6};
	static char const		opr[6] = {'+', '|', '^', ')', '(', '!'};
	std::string				error;
	std::string const		s1 = "Syntax error in rule";
	std::string const		s2 = "at column";
	std::string const		s3 = "Operator alone !";
	int						err;

	// check letters
	if (len == 1)
	{
		for (i = 0; i < op_n[2]; ++i)
		{
			if (e[0] == opr[i])
				return (printError(std::ostringstream().flush() << s3, false));
		}
	}
	if (len > 1 && isalpha(e[0]) && isalpha(e[1]))
		return (printError(std::ostringstream().flush() << s1 << " `" << rule_number << "` -> [" << ".. " + e.substr(0, 2) + " .." << "] " << s2 << " `0`", false));
	if (len > 1 && isalpha(e[len - 1]) && isalpha(e[len - 2]))
		return (printError(std::ostringstream().flush() << s1 << " `" << rule_number << "` -> [" << ".. " + e.substr(len - 2, 2) + " .." << "] " << s2 << " `" << len - 1 << "`", false));
	if (len > 2)
	{
		for (i = 1; i < len - 1; ++i)
		{
			if (isalpha(e[i]) && (isalpha(e[i - 1]) || isalpha(e[i + 1])))
				return (printError(std::ostringstream().flush() << s1 << " `" << rule_number << "` -> [" << ".. " + e.substr(i - 1, 3) + " .." << "] " << s2 << " `" << i << "`", false));
		}
	}
	// check operators		
	for (j = 0; j < op_n[0]; ++j)
	{
		if (e[0] == opr[j])
			return (printError(std::ostringstream().flush() << s1 << " `" << rule_number << "` -> [" << ".. " + e.substr(0, 2) + " .." << "] " << s2 << " `0`", false));
		if (e[len - 1] == opr[j])
			return (printError(std::ostringstream().flush() << s1 << " `" << rule_number << "` -> [" << ".. " + e.substr(len - 2, 2) + " .." << "] " << s2 << " `" << len - 1 << "`", false));
	}
	if (e[len - 1] == opr[5] || e[len - 1] == opr[4])
		return (printError(std::ostringstream().flush() << s1 << " `" << rule_number << "` -> [" << ".. " + e.substr(len - 2, 2) + " .." << "] " << s2 << " `" << len - 1 << "`", false));
	if (e[0] == opr[4])
		return (printError(std::ostringstream().flush() << s1 << " `" << rule_number << "` -> [" << ".. " + e.substr(0, 2) + " .." << "] " << s2 << " `0`", false));
	if (len > 1)
	{
		err = 0;
		for (i = 1; i < len - 1; ++i)
		{
			// iterate characters to check, break to process it when found
			for (j = 0; j < op_n[2]; ++j)
				if (e[i] == opr[j])
					break;
			if (j < op_n[0]) // '+' '|' '^'
			{
				for (j = 0; j < op_n[0]; ++j)
				{
					if (e[i - 1] == opr[j] || e[i + 1] == opr[j])
					{
						err = 1;
						break;
					}
				}
			}
			else if (j == 3) // ')'
			{
				if (e[i - 1] == opr[5] || e[i - 1] == opr[4])
					err = 1;
				else
				{
					for (j = 0; j < op_n[0]; ++j)
					{
						if (e[i - 1] == opr[j])
						{
							err = 1;
							break;
						}
					}
				}
			}
			else if (j == 4) // '('
			{
				if (e[i - 1] == opr[3]) // ')('
					err = 1;
				else if (e[i + 1] == opr[3]) // '()'
					err = 1;
			}
			else if (j == 5) // '!'
			{
				if (e[i - 1] == opr[3]) // ')!'
					err = 1;
				else if (e[i + 1] == opr[3]) // '!)'
					err = 1;
				else
				{
					for (j = 0; j < op_n[0]; ++j)
					{
						if (e[i - 1] == opr[j] || e[i + 1] == opr[j])
						{
							err = 1;
							break;
						}
					}
				}
			}
		}
		if (err)
		{
			error = len > 2 ? ".. " + e.substr(i - 1, 3) + " .." : e;
			return (printError(std::ostringstream().flush() << s1 << " `" << rule_number << "` -> [" << error << "] " << s2 << " `" << i << "`", false));
		}
	}
	return (true);
}

// at this point all characters are valid
// given inference, creates RPN
int
Parser::buildRPN(std::string const &f, std::string &rpn)
{
	int								i, j;
	int const						length = f.length();
	char							o;
	static int const				op_n = 4; // number of operators
	static char const				opr[op_n][3] = {{'!', 4, 1}, // operator / precedence / associativity (Left:0, Right:1)
													{'+', 3, 0},
													{'|', 2, 0},
													{'^', 1, 0}}; // operators sorted by priority
	std::list<int>					os; // operator stack
	std::list<int>::iterator		it, ite;
	int								err;

	// build rpn for later evaluation
	for (i = 0; i < length; ++i)
	{
		if (f[i] >= 'A' && f[i] <= 'Z')
			rpn += f[i];
		else
		{
			// check for array operator
			for (j = 0; j < op_n; ++j)
			{
				if (f[i] == opr[j][0])
				{
					if (os.size() > 0)
					{
						it = os.begin();
						ite = os.end();
						while (it != ite)
						{
							if (*it == op_n)
								break;
							if ((!opr[j][2] && opr[j][1] <= opr[*it][1])
								|| (opr[j][2] && opr[j][1] < opr[*it][1]))
							{
								rpn += opr[*it][0];
								os.erase(it++);
							}
							else
								++it;
						}
						os.push_front(j);
					}
					else
						os.push_front(j);
					break;
				}
			}
			if (f[i] == '(')
			{
				// push the left parenthesis on the operator stack with an index outside of the operator array
				os.push_front(op_n);
			}
			else if (f[i] == ')')
			{
				for (it = os.begin(); it != os.end(); it = os.begin())
				{
					if (*it == op_n)
					{
						os.pop_front();
						break;
					}
					else
					{
						rpn += opr[*it][0];
						os.pop_front();
					}
				}
			}
		}
#ifdef _DEBUG
		// print separator
		std::cerr << "----- step -----" << std::endl;
		// print token
		std::cerr << "token : " << f[i] << std::endl;
		// print RPN
		std::cerr << "rpn   : " << rpn << std::endl;
		// print operator stack
		std::cerr << "stack : ";
		for (it = os.begin(); it != os.end(); ++it)
			std::cerr << (*it < op_n ? opr[*it][0] : '(');
		std::cerr << std::endl;
#endif
	}
	if (os.size() > 0)
	{
		// ite = os.end()
		for (it = os.begin(); it != os.end(); it = os.begin())
		{
			if (*it == op_n)
				return (printError("Mismatched parenthesis !", 0));
			rpn += opr[*it][0];
			os.pop_front();
		}
	}
	//
	return (1);
}

// ! 33, + 43, | 124, ^ 94 

bool
Parser::getPartsFromRule(std::string const &r, int const &rule_length, std::string &inference, std::string &implied)
{
	for (int i = 0; i < rule_length; ++i)
	{
		if (r[i] == '=' && i + 1 < rule_length && r[i + 1] == '>' && i + 2 < rule_length && r[i + 2])
		{
			inference = r.substr(0, i);
			implied = r.substr(i + 2, rule_length);
			return (true);
		}
		if (!ruleCharValid(r[i]))
			return (printError(std::ostringstream().flush() << r << ": " << "Invalid char `" << r[i] << "` at column `" << i << "` !", false));
	}
	return (printError(std::ostringstream().flush() << "[" << r << "] Incomplete rule !", false));
}

int
Parser::parseRawRule(std::string const &r, std::list<Rule *> *rules, int const &number)
{
	int						i;
	int const				rule_length = r.length();
	std::string				inference;
	std::string				implied;
	std::string				implied_rpn;
	std::string				rpn;
	Rule					*rule;

	i = 0;
	// only checks for character validity
	if (!getPartsFromRule(r, rule_length, inference, implied))
		return (0);
	if (!check_syntax_error(inference, number))
		return (0);
	if (!check_syntax_error(implied, number))
		return (0);
	if (!buildRPN(inference, rpn))
		return (0);
	if (!buildRPN(implied, implied_rpn))
		return (0);
	std::cerr << inference << " [" << rpn << "]" << " => " << implied_rpn << std::endl;
	rule = new Rule(inference, implied_rpn, rpn);
	rules->push_back(rule);
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
