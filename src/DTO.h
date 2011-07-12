/*
 * DTO.h
 *
 *  Created on: 06/12/2010
 *      Author: emoretto
 */
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>
#include <functional>
#include <string.h>
#include <sys/time.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <boost/flyweight.hpp>

using namespace std;
using namespace boost::flyweights;

#ifndef DTO_H_
#define DTO_H_

class DTO {
public:

	DTO();
	virtual ~DTO();
	void print();

	string id;
	string name1;
	string name2;
	flyweight<string> name3;

	// copy constructor
	DTO(DTO* const& p) :
		id(p->id),
		name1(p->name1),
		name2(p->name2),
		name3(p->name3)
	{
	};

};

#endif /* DTO_H_ */
