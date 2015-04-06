// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/06 07:04:53 by rdavid            #+#    #+#             //
//   Updated: 2015/01/06 07:04:54 by rdavid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //
#include <iostream>
#include <stdint.h>
#include <Phonebook.hpp>

int
main()
{
	register int32_t	quit = 0;
	std::string			str;
	Phonebook			phonebook;

	while (!quit)
	{
		std::cout << "Enter a command: ";
		std::cin >> str;
		if (str == "EXIT")
			quit = 1;
		else if (str == "ADD")
		{
			if (phonebook.nbr_contacts < CONTACTS_MAX)
			{
				Contact contact = phonebook.create_contact();
				phonebook.add_contact(contact);
			}
		}
		else if (str == "SEARCH")
		{
			if (phonebook.nbr_contacts > 0)
				phonebook.search();
		}
	}
	return (0);
}
