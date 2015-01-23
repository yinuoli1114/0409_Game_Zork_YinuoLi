#include "Condition.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

Condition::Condition(xml_node<> * node)
{
	for(xml_node<> *s = node->first_node(); s; s=s->next_sibling()){
		string s_name = s->name();
		
		if(s_name.compare("has") == 0){
			has = s->value();
			cout<<"Condition_has="<<has<<endl;
		}
		else if(s_name.compare("object") == 0){
			object = s->value();
			cout<<"Condition_object="<<object<<endl;
		}
		else if(s_name.compare("owner") == 0){
			owner = s->value();
			cout<<"Condition_owner"<<owner<<endl;
		}
		else if(s_name.compare("status") == 0){
			//accept = s->value();
			status = s->value();
			cout<<"Condition="<<status<<endl;
		}
	}

}