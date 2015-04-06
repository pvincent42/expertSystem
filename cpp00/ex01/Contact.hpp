// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Contact.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/06 07:04:02 by rdavid            #+#    #+#             //
//   Updated: 2015/01/06 07:04:16 by rdavid           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //
#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>
# include <stdint.h>
# include <defines.h>

class Contact
{
public:
	uint32_t		index;
	std::string		values[FIELDS_NUMBER];

	Contact(void);
	~Contact(void);

	void
	add_field(const uint32_t field_index, const std::string value);
};

#endif