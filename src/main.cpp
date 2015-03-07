# include <iostream>
# include <Rule.hpp>
# include <Core.hpp>

int
main(int argc, char **argv)
{
	std::cout << "Bonjour" << std::endl;
	std::string		test;
	std::string		test2;
	std::string		test3;
	std::string		test4;
	std::list<Rule *>	getRuleTest;
	test = "A + B";
	test2 = " E";
	test3 = "D + R";
	test4 = " E";
	Rule			newR(test, test2);
	Rule			newR2(test3, test4);
	Core			*newC = new Core;


	newC->setFact('V');
	newC->setFact('a');
	newC->addRule(&newR);
	newC->addRule(&newR2);
	std::cout << *newC << std::endl;
	getRuleTest = newC->getRule('e');
	std::list<Rule *>::iterator p = getRuleTest.begin();
	while (p != getRuleTest.end())
	{
		std::cout << *(*p) << std::endl;
		++p;
	}

	(void)argc;
	(void)argv;

	return (0);
}
