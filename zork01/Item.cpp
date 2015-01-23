#include "Item.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

Item::Item(xml_node<> * node)
{
	for(xml_node<> *s = node->first_node(); s; s=s->next_sibling()){
		string s_name = s->name();
		string s_value = s->value();
		
		if(s_name.compare("name") == 0){
			name = s_value;
			//cout<<"Item_name="<<name<<endl;
		}
		else if(s_name.compare("status") == 0){
			status = s_value;
			//cout<<"Item_status="<<status<<endl;
		}
		else if(s_name.compare("description") == 0){
			description = s_value;
			//cout<<"Item_description="<<description<<endl;
		}
		else if(s_name.compare("writing") == 0){
			writing = s_value;
			//cout<<"Item_writing="<<writing<<endl;
		}
		else if(s_name.compare("turnon") == 0){
			//accept = s->value();
			//Turnon turnon;
			for (xml_node<> *p=s->first_node();p; p=p->next_sibling()){
				string b_name = p->name();
				string b_value = p->value();
				if(b_name.compare("print") == 0){
					turnon.print = b_value;
				}
				else if(b_name.compare("action") == 0){
					turnon.actions.push_back(b_value);
				}
				

			}
			
			//cout<<"Item_turnon.print="<<turnon.print<<endl;
			
		}
		
		else if(s_name.compare("trigger") == 0){
			//accept = s->value();
			Trigger trigger(s);
			triggers.push_back(trigger);
			//cout<<"Room_trigger.condition.object="<<triggers[0].conditions[0].object<<endl;
			//cout<<"Room_trigger.condition.owner="<<triggers[0].conditions[0].owner<<endl;
		}
	}

}
