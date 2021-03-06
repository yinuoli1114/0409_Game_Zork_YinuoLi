#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include "rapidxml.hpp"

#include "Container.h"
#include "Trigger.h"
#include "Room.h"
#include "Creature.h"
#include "Item.h"


#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"


using namespace std;
using namespace rapidxml;

bool Exit = false;

map <string, Room> all_rooms;
map <string, Item> all_items;
map <string, Container> all_containers;
map <string, Creature> all_creatures;
map <string, Trigger> all_triggers;

map <string, Room> aall_rooms;
map <string, Item> aall_items;
map <string, Container> aall_containers;
map <string, Creature> aall_creatures;
map <string, Trigger> aall_triggers;

vector <string> Inventory;
vector <string> cur_items;
vector <string> cur_containers;
vector <string> cur_creatures;
vector <Trigger> cur_triggers;

Room* curRoom;
void gotoRoom(string input);
void dealItems(std::string input);
void SplitInput(const std::string& str, std::vector<std::string>& v);
void updateCurrentItems();
void removeItemFromContainer(string item_name);
void behindScenesCommands(string actionstr);
void checkInput(string input);
bool checkTiggersOverride();
bool checkTiggersOverride2();
void checkCommandTrigger(string input);

Room* getRoomFromMap(string name){
	map <string, Room>::iterator p;
	p = all_rooms.find(name);
	if(p != all_rooms.end()){
		return &(p->second);
	}
	else{
		return 0;
	}
}
Item* getItemFromMap(string name){
	map <string, Item>::iterator p;
	p = all_items.find(name);
	if(p != all_items.end()){
		return &(p->second);
	}
	else{
		return 0;
	}
}
Container* getContainerFromMap(string name){
	map <string, Container>::iterator p;
	p = all_containers.find(name);
	if(p != all_containers.end()){
		return &(p->second);
	}
	else{
		return 0;
	}
}
Creature* getCreatureFromMap(string name){
	map <string, Creature>::iterator p;
	p = all_creatures.find(name);
	if(p != all_creatures.end()){
		return &(p->second);
	}
	else{
		return 0;
	}
}
Trigger* getTriggerFromMap(string name){
	map <string, Trigger>::iterator p;
	//cout<<"    triiii"<<endl;
	p = all_triggers.find(name);
	if(p != all_triggers.end()){
		//cout<<"    trii11"<<endl;
		return &(p->second);
	}
	else{
		return 0;
	}
}


Room* ggetRoomFromMap(string name){
	map <string, Room>::iterator p;
	p = aall_rooms.find(name);
	if(p != aall_rooms.end()){
		return &(p->second);
	}
	else{
		return 0;
	}
}
Item* ggetItemFromMap(string name){
	map <string, Item>::iterator p;
	p = aall_items.find(name);
	if(p != aall_items.end()){
		return &(p->second);
	}
	else{
		return 0;
	}
}
Container* ggetContainerFromMap(string name){
	map <string, Container>::iterator p;
	p = aall_containers.find(name);
	if(p != aall_containers.end()){
		return &(p->second);
	}
	else{
		return 0;
	}
}
Creature* ggetCreatureFromMap(string name){
	map <string, Creature>::iterator p;
	p = aall_creatures.find(name);
	if(p != aall_creatures.end()){
		return &(p->second);
	}
	else{
		return 0;
	}
}
Trigger* ggetTriggerFromMap(string name){
	map <string, Trigger>::iterator p;
	//cout<<"    triiii"<<endl;
	p = aall_triggers.find(name);
	if(p != aall_triggers.end()){
		return &(p->second);
	}
	else{
		return 0;
	}
}


int main(int argc, char **argv)
{
	xml_document<> doc;
	//xml_node<> *root_node;
	ifstream file(argv[1]);
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	string content(buffer.str());

	/*vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	buffer.push_back('\0'); */
	doc.parse<0>(&content[0]);

	xml_node<> *pRoot = doc.first_node();
	
	string big_name;

	for(xml_node<> *pNode=pRoot->first_node(); pNode; pNode=pNode->next_sibling()){
		
		big_name = pNode -> name();
		
		if(big_name.compare("room") == 0){
			//cout<<"arrrr"<<pNode->value()<<endl;
			Room room(pNode);
			all_rooms.insert(make_pair(room.name, room));
			aall_rooms.insert(make_pair(room.name, room));
		}
		else if(big_name.compare("item") == 0){
			//cout<<"arrrr"<<pNode->value()<<endl;
			
			Item item(pNode);
			all_items.insert(make_pair(item.name, item));
			aall_items.insert(make_pair(item.name, item));
			//cout<<"6282938373737373 item.print"<<item.turnon.print<<endl;
			//cout<<"6282938373737373 item.name"<<item.name<<endl;
			//cout<<"rrrrrrooomm"<<endl;
		}
		else if(big_name.compare("container") == 0){
			//cout<<"arrrr"<<pNode->value()<<endl;
			
			Container container(pNode);
			all_containers.insert(make_pair(container.name, container));
			aall_containers.insert(make_pair(container.name, container));
			//cout<<"rrrrrrooomm"<<endl;
		}
		else if(big_name.compare("trigger") == 0){
			//cout<<"arrrr"<<pNode->value()<<endl;
			Trigger trigger(pNode);
			all_triggers.insert(make_pair(trigger.print, trigger));
			aall_triggers.insert(make_pair(trigger.print, trigger));
			

			//cout<<"yyyyyyyyyyyyy"<<endl;
		}
		else if(big_name.compare("creature") == 0){
			//cout<<"arrrr"<<pNode->value()<<endl;
			Creature creature(pNode);
			all_creatures.insert(make_pair(creature.name, creature));
			aall_creatures.insert(make_pair(creature.name, creature));
			

			//cout<<"yyyyyyyyyyyyy"<<endl;
		}
		
	}
	Room *start_room = getRoomFromMap("Entrance");
	curRoom = start_room;
	cout<<start_room->description<<endl;
	
	while(Exit == false){
		char input[100];
		cout<<">";
		cin.getline(input,100);
		//cout<<" #1"<<endl;
		//gotoRoom(input);
		updateCurrentItems();
		//cout<<"1111122"<<endl;
		//checkTiggers();
		//if(checkTiggersOverride() == false){
		//cout<<" #2"<<endl;
		if(checkTiggersOverride() == false){//has command
			//cout<<" #3"<<endl;
			checkInput(input);
			//cout<<" #3.5"<<endl;
			checkTiggersOverride2();
			//cout<<" #4"<<endl;
			//bool b = checkTiggersOverride();
		}
		else{
			//cout<<"rrr777"<<endl;
			//if(checkTiggersOverride2() )
			//cout<<" #5"<<endl;
			
			checkCommandTrigger(input);
			checkTiggersOverride2();

			//cout<<" #6"<<endl;
			//checkInput(input);
			//dealItems(input);
			//cout<<"55rrr"<<endl;
		}
	}
}
/*
bool checkOverride(sting input){
	bool Override = false;

}*/

void checkCommandTrigger(string input){
	for(int i=0; i < cur_triggers.size(); i++){
		Trigger trigger = cur_triggers[i];
		//cout<<"   q1"<<endl;
		if(!trigger.command.empty()){//command exist
			//cout<<"   q2"<<endl;
			//checkInput(input);
			if(trigger.command.compare(input) == 0){
				//cout<<"   q3"<<endl;

				if(checkTiggersOverride2() == false){
					//cout<<"   q4"<<endl;
						cout<<trigger.print<<endl;
						for(int i=0; i < trigger.actions.size(); i++){
							//cout<<"22222111"<<endl;
							behindScenesCommands(trigger.actions[i]);
						}
					}
			}
			else{
				checkInput(input);
			}
			
		}
		
	}

}
bool checkTiggersOverride2(){//trigger without command
	bool Override = false;

	for(int i=0; i < cur_triggers.size(); i++){
		Trigger &trigger = cur_triggers[i];
		//cout<<"   ##1"<<endl;
		for(int i=0; i < trigger.conditions.size(); i++){
			//cout<<"   ##1.5"<<endl;
			//cout<<i<<"   trigger.name="<<trigger.conditions[i].object<<endl;
			//cout<<i<<"   trigger.command="<<trigger.command<<endl;
			//cout<<i<<"   trigger.status="<<trigger.conditions[i].status<<endl;
			//cout<<i<<"   trigger.triggered="<<trigger.triggered<<endl;
			if(trigger.command.empty() && trigger.triggered == false){//no command
				//cout<<"   ##2"<<endl;
						if(trigger.conditions[i].has.empty()){//if has not exist
							//cout<<"   ##3"<<endl;
							string ob_name = trigger.conditions[i].object;
							string ob_status = trigger.conditions[i].status;
							if(getItemFromMap(ob_name) != 0){
								//cout<<"  @1"<<endl;
								Item * item = getItemFromMap(ob_name);
								if(item->status.compare(ob_status) == 0){
									Override = true;
									//cout<<"  @1.1"<<endl;
									cout<<trigger.print<<endl;
									if(trigger.type.compare("single") == 0){
										//trigger.triggered = true;
										//cout<<"  @1.15"<<endl;
										//cout<<i<<"   trigger.triggered="<<trigger.triggered<<endl;
										//trigger.conditions[i].status = "women";
										item->status = "go";
										//Trigger *t = getTriggerFromMap(trigger.print);
										//t->triggered = true;
									}
								}
								else{
									Override = false;
									//cout<<"  @1.2"<<endl;
								}
							}
							else if(getContainerFromMap(ob_name) != 0){
								//cout<<"   @2"<<endl;
								Container * container = getContainerFromMap(ob_name);
								//cout<<"  container->status= "<<container->status<<endl;
								//cout<<"  ob_status= "<<ob_status<<endl;
								if(container->status.compare(ob_status) == 0){
									Override = true;
									if(trigger.type.compare("single") == 0){
										container->status = "go";
									}
								}
								else{
									Override = false;
								}
								//cout<<"  o2= "<<Override<<endl;
							}
							else if(getCreatureFromMap(ob_name) != 0){
								//cout<<"   @3"<<endl;
								Creature * creature = getCreatureFromMap(ob_name);
								if(creature->status.compare(ob_status) == 0){
									Override = true;
									if(trigger.type.compare("single") == 0){
										creature->status = "go";
									}
								}
								else{
									Override = false;
								}
							}
							else if(getRoomFromMap(ob_name) != 0){
								//cout<<"   @4"<<endl;
								Room * room = getRoomFromMap(ob_name);
								if(room->status.compare(ob_status) == 0){
									Override = true;
									if(trigger.type.compare("single") == 0){
										room->status = "go";
									}
								}
								else{
									Override = false;
								}
							}
						}
						else{// if has exist
							string own_name = trigger.conditions[i].owner;
							string ob_name = trigger.conditions[i].object;
							string yn = trigger.conditions[i].has;
							if(own_name.compare("inventory") == 0){
								//cout<<"   @5"<<endl;
								if(std::find(Inventory.begin(), Inventory.end(), ob_name) != Inventory.end()){
									if(yn.compare("yes") == 0){
										//cout<<"@115"<<endl;
										Override = true;
										cout<<trigger.print<<endl;
										for(int i=0; i < trigger.actions.size(); i++){
											behindScenesCommands(trigger.actions[i]);
										}
									}
									else{
										Override = false;
									}

								}
								else if(std::find(Inventory.begin(), Inventory.end(), ob_name) == Inventory.end()){
									//cout<<"   @6"<<endl;
									if(yn.compare("no") == 0){
										//cout<<"@116"<<endl;
										Override = false;
										cout<<trigger.print<<endl;
										for(int i=0; i < trigger.actions.size(); i++){
											behindScenesCommands(trigger.actions[i]);
										}
									}
									else{
										Override = true;
									}
								}
							}
							else{
								if(getItemFromMap(ob_name) != 0 && getContainerFromMap(own_name) != 0){
									//cout<<"   @7"<<endl;
									Item *item = getItemFromMap(ob_name);
									Container *container = getContainerFromMap(own_name);
									if(std::find(container->items.begin(), container->items.end(), ob_name) != container->items.end() && yn.compare("yes") == 0){
										Override = true;
										cout<<trigger.print<<endl;
										for(int i=0; i < trigger.actions.size(); i++){
											//cout<<"22222111"<<endl;
											//cout<<"    t1rigger.action="<<trigger.actions[i]<<endl;
											//cout<<trigger.print<<endl;
											behindScenesCommands(trigger.actions[i]);
											//cout<<"    71gotoAction"<<endl;
										}
									}
									else if(std::find(container->items.begin(), container->items.end(), ob_name) == container->items.end() && yn.compare("no") == 0){
										Override = true;
										cout<<trigger.print<<endl;
										for(int i=0; i < trigger.actions.size(); i++){
											//cout<<"22222111"<<endl;
											//cout<<"    t2rigger.action="<<trigger.actions[i]<<endl;
											behindScenesCommands(trigger.actions[i]);
											//cout<<"    72gotoAction"<<endl;
										}
									}
									else{
										Override = false;



									}
									//cout<<"   item->name= "<<item->name<<endl;
									//cout<<"   container->name= "<<container->name<<endl;
									//cout<<"   o7= "<<Override<<endl;
								}
								else if(getItemFromMap(ob_name) != 0 && getRoomFromMap(own_name) != 0){
									//cout<<"   @8"<<endl;
									Item *item = getItemFromMap(ob_name);
									Room *room = getRoomFromMap(own_name);
									if(std::find(room->items.begin(), room->items.end(), ob_name) != room->items.end() && yn.compare("yes") == 0){
										Override = true;
									}
									else if(std::find(room->items.begin(), room->items.end(), ob_name) == room->items.end() && yn.compare("no") == 0){
										Override = true;
									}
									else{
										Override = false;
									}
								}
							}
						}
			}
		}
	}
	//cout<<"override= "<<Override<<endl;
	return Override;

}

bool checkTiggersOverride(){
	bool Override = false;
	for(int i=0; i < cur_triggers.size(); i++){
		Trigger trigger = cur_triggers[i];
		for(int i=0; i < trigger.conditions.size(); i++){
			if(!trigger.command.empty()){

						if(trigger.conditions[i].has.empty()){//if has not exist
							string ob_name = trigger.conditions[i].object;
							string ob_status = trigger.conditions[i].status;
							if(getItemFromMap(ob_name) != 0){
								//cout<<"1"<<endl;
								Item * item = getItemFromMap(ob_name);
								if(item->status.compare(ob_status) == 0){
									Override = true;
								}
								else{
									Override = false;
								}
							}
							else if(getContainerFromMap(ob_name) != 0){
								//cout<<"2"<<endl;
								Container * container = getContainerFromMap(ob_name);
								//cout<<"  container->status= "<<container->status<<endl;
								//cout<<"  ob_status= "<<ob_status<<endl;
								if(container->status.compare(ob_status) == 0){
									Override = true;
								}
								else{
									Override = false;
								}
								//cout<<"  o2= "<<Override<<endl;
							}
							else if(getCreatureFromMap(ob_name) != 0){
								//cout<<"3"<<endl;
								Creature * creature = getCreatureFromMap(ob_name);
								if(creature->status.compare(ob_status) == 0){
									Override = true;
								}
								else{
									Override = false;
								}
							}
							else if(getRoomFromMap(ob_name) != 0){
								//cout<<"4"<<endl;
								Room * room = getRoomFromMap(ob_name);
								if(room->status.compare(ob_status) == 0){
									Override = true;
								}
								else{
									Override = false;
								}
							}
						}
						else{// if has exist
							string own_name = trigger.conditions[i].owner;
							string ob_name = trigger.conditions[i].object;
							string yn = trigger.conditions[i].has;
							if(own_name.compare("inventory") == 0){
								//cout<<"5"<<endl;
								if(std::find(Inventory.begin(), Inventory.end(), ob_name) != Inventory.end()){
									if(yn.compare("yes") == 0){
										Override = true;
									}
									else{
										Override = false;
									}

								}
								else if(std::find(Inventory.begin(), Inventory.end(), ob_name) == Inventory.end()){
									//cout<<"6"<<endl;
									if(yn.compare("no") == 0){
										Override = true;
									}
									else{
										Override = false;
									}
								}
							}
							else{
								if(getItemFromMap(ob_name) != 0 && getContainerFromMap(own_name) != 0){
									//cout<<"7"<<endl;
									Item *item = getItemFromMap(ob_name);
									Container *container = getContainerFromMap(own_name);
									if(std::find(container->items.begin(), container->items.end(), ob_name) != container->items.end() && yn.compare("yes") == 0){
										Override = true;
									}
									else if(std::find(container->items.begin(), container->items.end(), ob_name) == container->items.end() && yn.compare("no") == 0){
										Override = true;
									}
									else{
										Override = false;
									}
									//cout<<"   item->name= "<<item->name<<endl;
									//cout<<"   container->name= "<<container->name<<endl;
									//cout<<"   o7= "<<Override<<endl;
								}
								else if(getItemFromMap(ob_name) != 0 && getRoomFromMap(own_name) != 0){
									//cout<<"8"<<endl;
									Item *item = getItemFromMap(ob_name);
									Room *room = getRoomFromMap(own_name);
									if(std::find(room->items.begin(), room->items.end(), ob_name) != room->items.end() && yn.compare("yes") == 0){
										Override = true;
									}
									else if(std::find(room->items.begin(), room->items.end(), ob_name) == room->items.end() && yn.compare("no") == 0){
										Override = true;
									}
									else{
										Override = false;
									}
								}
							}
						}
			}
		}
	}
	//cout<<"override= "<<Override<<endl;
	return Override;

}

void checkInput(std::string input){
	if(input.compare("n") == 0 || input.compare("s") == 0 || input.compare("w") == 0 || input.compare("e") == 0){
		gotoRoom(input);
	}
	else{
		//behindScenesCommands(input);
		dealItems(input);

	}
}



void SplitInput(const std::string& str, std::vector<std::string>& v)
{
	std::stringstream ss(str);
  	ss >> std::noskipws;
  	std::string field;
  	char ws_delim;
  	while(1) {
    	if( ss >> field )
      		v.push_back(field);
    	else if (ss.eof())
      		break;
    	else
      		v.push_back(std::string());

    	ss.clear();
    	ss >> ws_delim;
  }
}

/*bool checkInventory(string item_name){

}*/
void updateCurrentItems(){
	cur_items.clear();
	//cout<<"  ww1"<<endl;
	cur_items.insert(cur_items.end(), curRoom->items.begin(), curRoom->items.end());
	//cout<<"  ww2"<<endl;
	cur_containers.clear();
	//cout<<"  ww3"<<endl;
	cur_containers.insert(cur_containers.end(), curRoom->containers.begin(), curRoom->containers.end());
	//cout<<"  ww4"<<endl;
	for(int i=0; i < cur_containers.size(); i++){
		//cout<<getContainerFromMap(cur_containers[i])->name<<endl;
		Container* cur_container = getContainerFromMap(cur_containers[i]);
		if(cur_container->open == true){
			cur_items.insert(cur_items.end(), cur_container->items.begin(), cur_container->items.end());
		}
	}
	//cout<<"  ww5"<<endl;
	cur_creatures.clear();
	//cout<<"  ww6"<<endl;
	if(curRoom->creatures.size()>0){
		cur_creatures.insert(cur_creatures.end(), curRoom->creatures.begin(), curRoom->creatures.end());
	}
	//cout<<"  ww7"<<endl;
	cur_triggers.clear();
	//cout<<"  ww8"<<endl;
	cur_triggers.insert(cur_triggers.end(), curRoom->triggers.begin(), curRoom->triggers.end());
	//cout<<"  ww9"<<endl;
	for(int i=0; i < cur_items.size(); i++){
		Item * cur_item = getItemFromMap(cur_items[i]);
		cur_triggers.insert(cur_triggers.end(), cur_item->triggers.begin(), cur_item->triggers.end());
	}
	//cout<<"  ww10"<<endl;
	for(int i=0; i < cur_containers.size(); i++){
		Container * cur_container = getContainerFromMap(cur_containers[i]);
		cur_triggers.insert(cur_triggers.end(), cur_container->triggers.begin(), cur_container->triggers.end());
	}
	//cout<<"  ww11"<<endl;
	//cout<<"cur_creature.size="<<cur_creatures.size()<<endl;
	if(cur_creatures.size()>0){
		for(int i=0; i < cur_creatures.size(); i++){
			if(all_creatures.find(cur_creatures[i]) != all_creatures.end()){
				Creature * cur_creature = getCreatureFromMap(cur_creatures[i]);
				cur_triggers.insert(cur_triggers.end(), cur_creature->triggers.begin(), cur_creature->triggers.end());
			}
		}
	}
	//cout<<"  ww12"<<endl;

}

void removeItemFromContainer(string item_name){
	for(int i=0; i < cur_containers.size(); i++){
		Container* ct = getContainerFromMap(cur_containers[i]);
		if(std::find(ct->items.begin(), ct->items.end(), item_name) != ct->items.end()){
			//cout<<"iiiii"<<endl;
			std::vector<string>::iterator it;
			for(it = ct->items.begin(); it!=ct->items.end();it++){
				string it_name = *it;
				//cout<<"222"<<endl;
				if(it_name.compare(item_name) == 0){
					ct->items.erase(it);
					break;
				}
			}
		}
	}
}

void removeItemFromInventory(string item_name){
	std::vector<string>::iterator it;
	for(it = Inventory.begin(); it!=Inventory.end();it++){
		string it_name = *it;
		//cout<<"333"<<endl;
		if(it_name.compare(item_name) == 0){
			Inventory.erase(it);
			break;
		}
	}
}

void dealItems(std::string input){
	if(input.find("take") != string::npos){
		std::vector <string> words;
		SplitInput(input, words);
		if(words.size() == 2){
			
			if(std::find(Inventory.begin(), Inventory.end(), words[1]) != Inventory.end()){
				cout<<"This item have already been in the Inventory"<<endl;
			}
			else if(std::find(cur_items.begin(), cur_items.end(), words[1]) != cur_items.end()){
				//cout<<"Can't take "<<words[1]<<endl;
				Inventory.push_back(words[1]);
				cout<<"Item "<<words[1]<< " added to Inventory"<<endl;
				removeItemFromContainer(words[1]);
			}
			else{
				cout<<"Can't take "<<words[1]<<endl;
			}
		}
		else{
			cout<<"Take Error"<<endl;
			cout<<"Please enter: take (item)"<<endl;
		}
	}
	else if(input.find("drop") != string::npos){
		std::vector <string> words;
		SplitInput(input, words);
		if(words.size() == 2){
			if(std::find(Inventory.begin(), Inventory.end(), words[1]) != Inventory.end()){
				cout<<words[1]<<" dropped"<<endl;
				removeItemFromInventory(words[1]);
				Room * room = getRoomFromMap(curRoom->name);
				room->items.push_back(words[1]);
			}
			else{
				cout<<"No such item in Inventory"<<endl;
			}
		}
		else{
			cout<<"Drop Error"<<endl;
			cout<<"Please enter: drop (item)"<<endl;
		}
	}
	else if(input.find("put") != string::npos){
		std::vector <string> words;
		SplitInput(input, words);
		if(words.size() == 4){
			if(words[2].compare("in") == 0){
				Item * it = getItemFromMap(words[1]);
				if(it == 0){
					cout<<"Item not exist"<<endl;
				}
				else if(std::find(Inventory.begin(), Inventory.end(), words[1]) == Inventory.end()){
					cout<<"No such item in Inventory"<<endl;
				}
				else if(std::find(cur_containers.begin(), cur_containers.end(), words[3]) == cur_containers.end()){
					cout<<"No such container in this room"<<endl;
				}
				else{
					Container * container = getContainerFromMap(words[3]);
					if(container->accepts.size() == 0){

						cout<<"Item "<<words[1]<<" added to "<<words[3]<<endl;
						Container* ct = getContainerFromMap(words[3]);
						ct->items.push_back(words[1]);
						removeItemFromInventory(words[1]);
					}else{
						//bool can_accept = false;
						for(int i=0; i < container->accepts.size(); i++){
							if(container->accepts[i].compare(it->name) == 0){
								cout<<"Item "<<words[1]<<" added to "<<words[3]<<endl;
								//Container* ct = getContainerFromMap(words[3]);
								container->items.push_back(words[1]);
								removeItemFromInventory(words[1]);
							}
							else{
								cout<<words[3]<<" doesn't accept "<<words[1]<<endl;
							}
						}
					}
				}
			}
			else{
				cout<<"Put Error"<<endl;
			}
		}
		else{
			cout<<"Put Error"<<endl;
			cout<<"Please enter: put (item) in (container)"<<endl;
		}
	}
	else if(input.find("open") != string::npos){
		std::vector <string> words;
		SplitInput(input, words);
		if(words.size() == 2){
			if(words[1].compare("exit") == 0){
				if(curRoom->type.compare("exit") == 0){
					cout<<"Win!!!"<<endl;
					Exit = true;
				}
				else{
					cout<<"Can't exit"<<endl;
				}
			}
			else if(std::find(cur_containers.begin(), cur_containers.end(), words[1]) != cur_containers.end()){
				//cout<<"enter 1"<<endl;
				Container * ct = getContainerFromMap(words[1]);
				if(ct -> items.size() == 0){
					cout<<words[1]<<" is empty"<<endl;
				}
				else{
					ct->open = true;
					cout<<words[1]<<" contains: ";
					for(int i=0; i < ct-> items.size(); i++){
						cout<<ct->items[i]<<" ";
					}
					cout<<" "<<endl;
				}
			}
			
			else if(all_containers.find(words[1]) != all_containers.end()){
				cout<<words[1]<<" is not in this room"<<endl;
			}
			else{
				cout<<words[1]<<" is not a container"<<endl;
			}

		}
		else{
			cout<<"Open Error"<<endl;
			cout<<"Please enter: open (item)"<<endl;
		}
	}
	else if(input.find("read") != string::npos){
		std::vector <string> words;
		SplitInput(input, words);
		if(words.size() == 2){
			if(std::find(Inventory.begin(), Inventory.end(), words[1]) != Inventory.end()){
				Item * item = getItemFromMap(words[1]);
				if(item->writing.empty()){
					cout<<"Noting written"<<endl;
				}
				else{
					cout<<item->writing<<endl;
				}
			}
			else{
				cout<<"Please take it before read"<<endl;
			}
		}
		else{
			cout<<"Read Error"<<endl;
			cout<<"Please enter: read (item)"<<endl;
		}
	}
	else if(input.find("turn on") != string::npos){
		std::vector <string> words;
		SplitInput(input, words);
		if(words.size() == 3){
			if(std::find(Inventory.begin(), Inventory.end(), words[2]) != Inventory.end()){
				Item * item = getItemFromMap(words[2]);
				cout<<"You activate the "<<words[2]<<endl;
				if(!item->turnon.print.empty()){
					cout<<item->turnon.print<<endl;
				}
				if(item->turnon.actions.size()>0){
					for(int i=0; i < item->turnon.actions.size(); i++){
						behindScenesCommands(item->turnon.actions[i]);
						//cout<<"2345"<<endl;
					}
				}
			}
			else{
				cout<<"No such item in Inventory"<<endl;
			}
		}
		else{
			cout<<"Tuen on Error"<<endl;
			cout<<"Please enter: turn on (item)"<<endl;
		}
	}
	else if(input.compare("i") == 0){
		cout<<"Inventory: ";
		if(Inventory.size() > 0){
			for(int i=0; i < Inventory.size(); i++){
				cout<<Inventory[i]<<" ";
			}
			cout<<""<<endl;
		}
		else{
			cout<<"empty"<<endl;
		}
	}
	else if(input.find("attack") != string::npos){
		std::vector <string> words;
		SplitInput(input, words);
		//cout<<"  &1"<<endl;
		if(words.size() == 4){
			if(words[2].compare("with") == 0){
				if(getCreatureFromMap(words[1]) == 0){
					cout<<"No such creature"<<endl;
				}
				else if(std::find(cur_creatures.begin(), cur_creatures.end(), words[1]) == cur_creatures.end()){
					cout<<"Creature is not in this room"<<endl;
				}
				else if(getItemFromMap(words[3]) == 0){
					cout<<"Item not exist"<<endl;
				}
				else if(std::find(Inventory.begin(), Inventory.end(), words[3]) == Inventory.end()){
					cout<<"No such item in Inventory"<<endl;
				}
				else{
					Creature * creature = getCreatureFromMap(words[1]);
					Item * item = getItemFromMap(words[3]);
					string ob_status = creature->attack.condition.status;
					//cout<<"item->status = "<<item->status<<endl;
					if(std::find(creature->vulnerabilities.begin(), creature->vulnerabilities.end(), item->name) != creature->vulnerabilities.end()){
						if(creature->attack.condition.object.empty()){
							cout<<"You assalt the "<<creature->name<<" with "<<item->name<<endl;
							cout<<creature->attack.print<<endl;
							for(int i=0; i < creature->attack.actions.size(); i++){
								//cout<< "  ee1"<<endl;
								behindScenesCommands(creature->attack.actions[i]);
							}
						}
						else{
							string ob_name = creature->attack.condition.object;
							if(getItemFromMap(ob_name) != 0){
								Item * item = getItemFromMap(ob_name);
								if(item->status.compare(ob_status) == 0){
									cout<<"You assalt the "<<creature->name<<" with "<<item->name<<endl;
									cout<<creature->attack.print<<endl;
									//cout<<"  &2"<<endl;
									for(int i=0; i < creature->attack.actions.size(); i++){
										//cout<< "  ee1"<<endl;
										behindScenesCommands(creature->attack.actions[i]);
									}
								}
								else{
									cout<<words[3]<<" is not activated to attack "<<words[1]<<endl;
								}
							}
							else if(getCreatureFromMap(ob_name) != 0){
								Creature * creature = getCreatureFromMap(ob_name);
								if(creature->status.compare(ob_status) == 0){
									cout<<"You assalt the "<<creature->name<<" with "<<creature->name<<endl;
									cout<<creature->attack.print<<endl;
									for(int i=0; i < creature->attack.actions.size(); i++){
										//cout<< "  ee1"<<endl;
										behindScenesCommands(creature->attack.actions[i]);
									}
								}
								else{
									cout<<words[3]<<" is not activated to attack "<<words[1]<<endl;
								}
							}
							else if(getContainerFromMap(ob_name) != 0){
								Container * container = getContainerFromMap(ob_name);
								if(container->status.compare(ob_status) == 0){
									cout<<"You assalt the "<<creature->name<<" with "<<creature->name<<endl;
									cout<<creature->attack.print<<endl;
									for(int i=0; i < creature->attack.actions.size(); i++){
										//cout<< "  ee1"<<endl;
										behindScenesCommands(creature->attack.actions[i]);
									}
								}
								else{
									cout<<words[3]<<" is not activated to attack "<<words[1]<<endl;
								}
							}
							else if(getRoomFromMap(ob_name) != 0){
								Room * room = getRoomFromMap(ob_name);
								if(room->status.compare(ob_status) == 0){
									cout<<"You assalt the "<<creature->name<<" with "<<item->name<<endl;
									cout<<creature->attack.print<<endl;
									for(int i=0; i < creature->attack.actions.size(); i++){
										behindScenesCommands(creature->attack.actions[i]);
									}
								}
								else{
									cout<<words[3]<<" is not activated to attack "<<words[1]<<endl;
								}
							}
							else{
								cout<<words[3]<<" can't attack "<<words[1]<<endl;
							}
						}
						
					}
					else{
						cout<<words[3]<<" can't attack "<<words[1]<<endl;
					}

				}
			}
			else{
			cout<<"Attack Error"<<endl;
			cout<<"Please enter: attack (creature) with (item)"<<endl;
		}
		}
		else{
			cout<<"Attack Error"<<endl;
			cout<<"Please enter: attack (creature) with (item)"<<endl;
		}
		
	}
	else{
		cout<<"Invalid instruction"<<endl;
	}


}

void behindScenesCommands(string actionstr){
	if(actionstr.find("Add") != string::npos){
		//cout<<"$    1"<<endl;
		std::vector <string> words;
		SplitInput(actionstr, words);
		int ob_type = 0;
		int cr_type = 0;
		if(words.size() == 4){
			if(ggetItemFromMap(words[1]) != 0){
				Item * item = ggetItemFromMap(words[1]);
				ob_type = 1;
			}
			else if(ggetContainerFromMap(words[1]) != 0){
				Container * container = ggetContainerFromMap(words[1]);
				ob_type = 2;
			}
			else if(ggetCreatureFromMap(words[1]) != 0){
				Creature * creature = ggetCreatureFromMap(words[1]);
				ob_type = 3;
			}

			if(ggetContainerFromMap(words[3]) != 0){
				cr_type = 1;
			}
			else if(ggetRoomFromMap(words[3]) != 0){
				cr_type = 2;
			}
		}

		if(ob_type == 1 && cr_type == 1){

			Item * item = ggetItemFromMap(words[1]);
			Container * container = getContainerFromMap(words[3]);
			container->items.push_back(words[1]);
			//cout<<"  !1"<<endl;
		}
		else if(ob_type == 1 && cr_type == 2){
			Item * item = ggetItemFromMap(words[1]);
			Room * room = getRoomFromMap(words[3]);
			room->items.push_back(words[1]);
			//cout<<"  !2"<<endl;
		}
		else if(ob_type == 2 && cr_type == 1){
			Container * container = ggetContainerFromMap(words[1]);
			//Container * container = getContainerFromMap(words[3]);
			//container->items.push_back(words[1]);
		}
		else if(ob_type == 2 && cr_type == 2){
			Container * container = ggetContainerFromMap(words[1]);
			Room * room = getRoomFromMap(words[3]);
			room->containers.push_back(words[1]);
			//cout<<"  !3"<<endl;
		}
		else if(ob_type == 3 && cr_type == 1){
			Item * item = ggetItemFromMap(words[1]);
			Container * container = ggetContainerFromMap(words[3]);
			//container->items.push_back(words[1]);
		}
		else if(ob_type == 3 && cr_type == 2){
			Creature * creature = ggetCreatureFromMap(words[1]);
			Room * room = getRoomFromMap(words[3]);
			room->creatures.push_back(words[1]);
			//cout<<"  !4"<<endl;
		}
	}
	else if(actionstr.find("Delete") != string::npos){
		//cout<<"$    2"<<endl;
		std::vector <string> words;
		SplitInput(actionstr, words);
		if(words.size() == 2){
			if(getItemFromMap(words[1]) != 0){
				//all_items.erase(words[1]);
				std::map <string,Item>::iterator it;
				it = all_items.find(words[1]);
				all_items.erase(it);
				//cout<<"  *1"<<endl;
			}
			
			else if(getContainerFromMap(words[1]) != 0){
				std::map <string,Container>::iterator it;
				it = all_containers.find(words[1]);
				all_containers.erase(it);
				//cout<<"  *2"<<endl;
			}
			else if(getRoomFromMap(words[1]) != 0){
				std::map <string,Room>::iterator it;
				it = all_rooms.find(words[1]);
				all_rooms.erase(it);
				//cout<<"  *3"<<endl;
			}
			else if(getCreatureFromMap(words[1]) != 0){
				std::map <string,Creature>::iterator it;
				it = all_creatures.find(words[1]);
				all_creatures.erase(it);
				//cur_creatures.erase(std::remove(cur_creatures.begin(), cur_creatures.end(), words[1]), cur_creatures.end());
				//cout<<"  *4"<<endl;
			}

		}
	}
	else if(actionstr.find("Update") != string::npos){
		//cout<<"$    3"<<endl;
		std::vector <string> words;
		SplitInput(actionstr, words);
		if(words.size() == 4){
			if(getItemFromMap(words[1]) != 0){
				Item * item = getItemFromMap(words[1]);
				item->status = words[3];
			}
			else if(getContainerFromMap(words[1]) != 0){
				Container * container = getContainerFromMap(words[1]);
				container->status = words[3];
			}
			else if(getCreatureFromMap(words[1]) != 0){
				Creature * creature = getCreatureFromMap(words[1]);
				creature->status = words[3];
			}
			else if(getRoomFromMap(words[1]) != 0){
				Room * room = getRoomFromMap(words[1]);
				room->status = words[3];
			}
		}
		if(getContainerFromMap(words[1]) != 0){
		Container * container = getContainerFromMap(words[1]);
		//cout<<"   Check_container->status= "<<container->status<<endl;
		}

	}
	else if(actionstr.compare("Game Over") == 0){
		cout<<"Victory!"<<endl;
		Exit = true;
	}
	else{
		//cout<<"   check1"<<endl;
		checkInput(actionstr);
	}

	
}

void gotoRoom(std::string input)
{
	//cout<<curRoom->borders[0].direction<<endl;
	//cout<<"llll"<<endl;
	
	if(input == "n"){
		vector <Border> rborders = curRoom->borders;
		//cout<<"nnn"<<endl;
		bool checkDirection = false;
		for(int i=0; i < rborders.size(); i++){
			if(rborders[i].direction == "north"){
				curRoom = getRoomFromMap(rborders[i].name);
				checkDirection = true;
				cout<<curRoom->description<<endl;
			}
		}
		if(checkDirection == false){
			cout<<"Can't go that way!"<<endl;
		}
		cout<<"Your current room is "<<curRoom->name<<endl;
	}
	else if(input == "s"){
		vector <Border> rborders = curRoom->borders;
		//cout<<"sss"<<endl;
		bool checkDirection = false;
		for(int i=0; i < rborders.size(); i++){
			if(rborders[i].direction == "south"){
				curRoom = getRoomFromMap(rborders[i].name);
				checkDirection = true;
				cout<<curRoom->description<<endl;
			}
		}
		if(checkDirection == false){
			cout<<"Can't go that way!"<<endl;
		}
		cout<<"Your current room is "<<curRoom->name<<endl;
	}
	else if(input == "w"){
		vector <Border> rborders = curRoom->borders;
		//cout<<"www"<<endl;
		bool checkDirection = false;
		for(int i=0; i < rborders.size(); i++){
			if(rborders[i].direction == "west"){
				curRoom = getRoomFromMap(rborders[i].name);
				checkDirection = true;
				cout<<curRoom->description<<endl;
			}
		}
		if(checkDirection == false){
			cout<<"Can't go that way!"<<endl;
		}
		cout<<"Your current room is "<<curRoom->name<<endl;
	}
	else if(input == "e"){
		vector <Border> rborders = curRoom->borders;
		//cout<<"eee"<<endl;
		bool checkDirection = false;
		for(int i=0; i < rborders.size(); i++){
			if(rborders[i].direction == "east"){
				curRoom = getRoomFromMap(rborders[i].name);
				checkDirection = true;
				cout<<curRoom->description<<endl;
			}
		}
		if(checkDirection == false){
			cout<<"Can't go that way!"<<endl;
		}
		cout<<"Your current room is "<<curRoom->name<<endl;
	}
	
	
}
