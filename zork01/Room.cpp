#include "Room.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

Room::Room(xml_node<> * node)
{
	for(xml_node<> *s = node->first_node(); s; s=s->next_sibling()){
		string s_name = s->name();
		string s_value = s->value();
		
		if(s_name.compare("name") == 0){
			name = s_value;
			//cout<<"Room_name="<<name<<endl;
		}
		else if(s_name.compare("status") == 0){
			status = s_value;
			//cout<<"Room_status="<<status<<endl;
		}
		else if(s_name.compare("type") == 0){
			type = s_value;
			//cout<<"Room_type="<<type<<endl;
		}
		else if(s_name.compare("description") == 0){
			description = s_value;
			//cout<<"Room_description="<<description<<endl;
		}
		else if(s_name.compare("border") == 0){
			//accept = s->value();
			Border border;
			for (xml_node<> *p=s->first_node();p; p=p->next_sibling()){
				string b_name = p->name();
				string b_value = p->value();
				if(b_name.compare("direction") == 0){
					border.direction = b_value;
				}
				else if(b_name.compare("name") == 0){
					border.name = b_value;
				}
				

			}
			borders.push_back(border);
			//cout<<"Room_border.direction="<<borders[0].direction<<endl;
			
		}
		else if(s_name.compare("container") == 0){
			//accept = s->value();
			containers.push_back(s_value);
			//cout<<"Room_containers="<<containers[0]<<endl;
		}
		else if(s_name.compare("item") == 0){
			//accept = s->value();
			items.push_back(s_value);
			//cout<<"Room_items="<<items[0]<<endl;
		}
		else if(s_name.compare("creature") == 0){
			//accept = s->value();
			creatures.push_back(s_value);
			//cout<<"Room_creature="<<creatures[0]<<endl;
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
