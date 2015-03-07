# include <iostream>
# include <Rule.hpp>

int
main(int argc, char **argv)
{
	std::cout << "Bonjour" << std::endl;
	std::string		test;
	std::string		test2;

	test = "A + B";
	test2 = " C";
	Rule			newR(test, test2);

	std::cout << newR << std::endl;
	(void)argc;
	(void)argv;

	return (0);
}
