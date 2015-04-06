// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Contact.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/06 07:04:10 by rdavid            #+#    #+#             //
//   Updated: 2015/01/06 07:04:12 by rdavid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //
#include <Contact.hpp>

Contact::Contact(void)
{

}

Contact::~Contact(void)
{

}

void
Contact::add_field(const uint32_t field_index, const std::string value)
{
	if (field_index < FIELDS_NUMBER)
		this->values[field_index] = value;
}
