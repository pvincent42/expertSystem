// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Phonebook.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/06 07:04:30 by rdavid            #+#    #+#             //
//   Updated: 2015/01/06 07:04:31 by rdavid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //
#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <string>
# include <stdint.h>
# include <Contact.hpp>

class Phonebook
{
public:
	Contact					contacts[CONTACTS_MAX];
	std::string				fields[FIELDS_NUMBER];
	int32_t					nbr_contacts;

	Phonebook();
	~Phonebook();

	Contact
	create_contact(void) const;

	void
	add_contact(Contact contact);

	void
	search(void) const;

private:
	std::string
	_get_column(std::string str) const;

	std::string
	_itoa(uint32_t n) const;

	int32_t
	_atoi(std::string str) const;
};

#endif