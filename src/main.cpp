# include <iostream>
# include <Rule.hpp>
# include <Core.hpp>

int
main(int argc, char **argv)
{
	std::string			test;
	std::string			test2;
	std::string			test3;
	std::string			test4;
	std::list<Rule *>	getRuleTest;

	test = "A + B";
	test2 = " A";
	test3 = "D + R";
	test4 = " E";
	Rule			newR(test, test2);
	Rule			newR2(test3, test4);
	Core			*newC = new Core;

	newC->addRule(&newR);
	newC->addRule(&newR2);
	newC->setFact('V', 1);
	newC->setFact('a', 1);
	std::cout << *newC << std::endl;
	getRuleTest = newC->getRule('E');
	std::list<Rule *>::iterator p = getRuleTest.begin();
	while (p != getRuleTest.end())
	{
		std::cout << *(*p) << std::endl;
		++p;
	}
	std::cout << newC->getAnd('V', 'a', 1, 1) << std::endl;
	std::cout << newC->getAnd('V', 'e', 0, 1) << std::endl;
	std::cout << newC->getOr('V', 'e', 1 , 0) << std::endl;
	std::cout << newC->getXor('V', 'e', 1, 0) << std::endl;
	std::cout << newC->getXor('V', 'a', 0, 1) << std::endl;
	std::cout << newC->getXor('e', 'b', 0, 1) << std::endl;
	(void)argc;
	(void)argv;
	return (0);
}
