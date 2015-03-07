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

	test = "A + B";
	test2 = " C";
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
	(void)argc;
	(void)argv;

	return (0);
}
