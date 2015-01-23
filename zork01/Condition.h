#ifndef CONDITION_H_
#define CONDITION_H_
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <fstream>
#include "rapidxml.hpp"


using namespace std;
using namespace rapidxml;

class Condition
{
public:
	Condition(xml_node<> * node);
	string has;
	string object;
	string owner;
	string status;
};

#endif /*CONDITION_H_*/
