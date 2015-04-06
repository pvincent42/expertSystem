// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Phonebook.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/06 07:04:22 by rdavid            #+#    #+#             //
//   Updated: 2015/01/06 07:04:24 by rdavid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //
#include <Phonebook.hpp>
#include <iostream>
#include <string>

Phonebook::Phonebook(void)
{
	this->nbr_contacts = 0;
	this->fields[FIRST_NAME]		= "first name";
	this->fields[LAST_NAME]			= "last name";
	this->fields[NICKNAME]			= "nickname";
	this->fields[LOGIN]				= "login";
	this->fields[POSTAL_ADDRESS]	= "postal address";
	this->fields[EMAIL_ADDRESS]		= "email address";
	this->fields[PHONE_NUMBER]		= "phone number";
	this->fields[BIRTHDAY_DATE]		= "birthday date";
	this->fields[FAVORITE_MEAL]		= "favorite meal";
	this->fields[UNDERWEAR_COLOR]	= "underwear color";
	this->fields[DARKEST_SECRET]	= "darkest secret";
}

Phonebook::~Phonebook(void)
{
}

Contact
Phonebook::create_contact(void) const
{
	uint32_t	i;
	Contact		contact;

	i = 0;
	while (i < FIELDS_NUMBER)
	{
		std::cout << this->fields[i] << ": ";
		std::cin >> contact.values[i];
		++i;
	}
	return (contact);
}

void
Phonebook::add_contact(Contact contact)
{
	contact.index = this->nbr_contacts;
	this->contacts[this->nbr_contacts] = contact;
	this->nbr_contacts++;
}

void
Phonebook::search(void) const
{
	int32_t			i;
	int32_t			n;
	std::string		str;

	i = 0;
	while (i < this->nbr_contacts)
	{
		std::cout << this->_get_column(this->_itoa(this->contacts[i].index)) << "|";
		std::cout << this->_get_column(this->contacts[i].values[FIRST_NAME]) << "|";
		std::cout << this->_get_column(this->contacts[i].values[LAST_NAME]) << "|";
		std::cout << this->_get_column(this->contacts[i].values[NICKNAME]);
		std::cout << std::endl;
		++i;
	}
	std::cout << "Enter an index: ";
	std::cin >> str;
	n = this->_atoi(str);
	if (n != -1 && n < this->nbr_contacts)
	{
		i = 0;
		while (i < FIELDS_NUMBER)
		{
			std::cout << this->fields[i] << ": " << this->contacts[n].values[i] << std::endl;
			++i;
		}
	}
}

std::string
Phonebook::_itoa(uint32_t n) const
{
	std::string		str;
	std::string		tmp;

	if (n == 0)
		return "0";
	while (n)
	{
		tmp = "0";
		tmp[0] += (n % 10);
		str.insert(0, tmp);
		n /= 10;
	}
	return (str);
}

int32_t
Phonebook::_atoi(std::string str) const
{
	uint32_t		n;
	uint32_t		i;

	n = 0;
	i = 0;
	while (i < str.length())
	{
		if ((str[i] >= '0') & (str[i] <= '9'))
			n = (n * 10) + str[i] - '0';
		else
			return (-1);
		i++;
	}
	return (n);
}

std::string
Phonebook::_get_column(std::string str) const
{
	uint32_t		spaces;
	std::string		tmp_string;

	if (!str.empty())
	{
		if (str.length() >= 10)
		{
			str.resize(10);
			str[9] = '.';
		}
		else if (str.length() < 10)
		{
			spaces = 10 - str.length();
			while (spaces--)
				tmp_string += " ";
			tmp_string += str;
			str = tmp_string;
		}
	}
	else
		str = "          ";
	return (str);
}
