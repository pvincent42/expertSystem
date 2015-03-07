# include <iostream>
# include <Rule.hpp>
# include <Core.hpp>

int
main(int argc, char **argv)
{
	std::cout << "Bonjour" << std::endl;
	std::string		test;
	std::string		test2;

	test = "A + B";
	test2 = " C";
	Rule			newR(test, test2);
	Core			*newC = new Core;


	std::cout << newR << std::endl;
	std::cout << *newC << std::endl;
	newC->setFact('V');
	newC->setFact('a');
	std::cout << *newC << std::endl;
	(void)argc;
	(void)argv;

	return (0);
}
