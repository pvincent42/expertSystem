// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   megaphone.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/06 00:15:25 by rdavid            #+#    #+#             //
//   Updated: 2015/01/06 00:15:28 by rdavid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <string>
#include <stdint.h>

#define NOARGS		"* LOUD AND UNBEARABLE FEEDBACK NOISE *"

std::string
toupper(std::string str)
{
	register int32_t	i;

	i = -1;
	while (str[++i])
		str[i] = std::toupper(str[i], std::locale());
	return (str);
}

int
main(int ac, char **av)
{
	register uint32_t	i;

	(void)ac;
	if (ac > 1)
	{
		i = 0;
		while (av[++i])
			std::cout << toupper(av[i]);
		std::cout << std::endl;
	}
	else
		std::cout << NOARGS << std::endl;
	return (0);
}
