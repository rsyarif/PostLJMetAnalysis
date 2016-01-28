#ifndef eventRegistry_C 
#define eventRegistry_C 
#include <unordered_set>
#include <unordered_map>
#include <utility>
//#include <iostream>
//#include <string>
using namespace std;
typedef std::unordered_set<int> events_in_lumi;//a list of the events in one lumi.
typedef std::unordered_map<int,events_in_lumi*> lumi_in_run; //maps lumi::events_in_lumi

/*
 * Makes a list of events by {int run, int lumisection, int event}
 * for the sake of checking for duplicates. 
 *
 * Usage syntax: 
 * eventRegistry registry;
 * if(   RegisterEvent(run, lumi, event, &registry)  ) 
 *       cout<<"Duplicate event found"<<endl;
 *
 * returns true if the event has already been registered
 * else returns false and adds the Event to the list. 
 */

/////////////////////////////////////////////////////////////////////////
//////////// Main things that user will interface with: /////////////////
/////////////////////////////////////////////////////////////////////////
//     |      |      |      |      |      |      |      |      |      | 
//     |      |      |      |      |      |      |      |      |      |  
//     |      |      |      |      |      |      |      |      |      |   
//  \  |  /\  |  /\  |  /\  |  /\  |  /\  |  /\  |  /\  |  /\  |  /\  |  /
//   \ | /  \ | /  \ | /  \ | /  \ | /  \ | /  \ | /  \ | /  \ | /  \ | /
//    \|/    \|/    \|/    \|/    \|/    \|/    \|/    \|/    \|/    \|/  
//
typedef std::unordered_map< int, lumi_in_run* >  eventRegistry; //maps run::list of lumin in the run lumi_in_run

bool RegisterEvent(int run, int lumi, int event, eventRegistry* reg);
bool CheckEvent(int run, int lumi, int event, eventRegistry* reg);

//    /|\    /|\    /|\    /|\    /|\    /|\    /|\    /|\    /|\    /|\
//   / | \  / | \  / | \  / | \  / | \  / | \  / | \  / | \  / | \  / | \
//  /  |  \/  |  \/  |  \/  |  \/  |  \/  |  \/  |  \/  |  \/  |  \/  |  \
//     |      |      |      |      |      |      |      |      |      |   
//     |      |      |      |      |      |      |      |      |      |  
//     |      |      |      |      |      |      |      |      |      |   

//     __    __        __          __    __        __          __    __
//    (//    \\)    __(//   __    (//    \\)    __(//   __    (//    \\)
//    /"      / __  \\)"    \\)_  /"      / __  \\)"    \\)_  /"      / __
//  '|-..__..-''\_''-.\__..-''  '|-..__..-''\_''-.\__..-''  '|-..__..-''\
//  (\\  \_    _(\\      _/     (\\  \_    _(\\      _/     (\\  \_    //)
//   ""  (\\  //)""     //)      ""  (\\  //)""     //)      ""  (\\   ""
//        ""  ""        ""            ""  ""        ""            ""

	//Functions that the user don't need to touch. 
bool InvestigateLumi(int lumi, int event, eventRegistry::const_iterator RunNode);
bool InvestigateEvent(         int event, lumi_in_run::const_iterator LumiNode);
bool probeLumi(int lumi, int event, eventRegistry::const_iterator RunNode);
bool probeEvent(         int event, lumi_in_run::const_iterator LumiNode);
void AddRun(int run, int lumi, int event, eventRegistry*  reg);
void AddLumi(        int lumi, int event, lumi_in_run* LumiList);

bool RegisterEvent(int run, int lumi, int event, eventRegistry* reg){
	//This is the main function that the user will interface with. 
	//It takes a eventRegistry that needs no pre-treatment. 
	//Enter event {run number, lumisection, event number}
	//This checks whether they exist in the list already, in which case it returns true
	//If they are not already enlisted, returns false. 
	eventRegistry::const_iterator RunNode = reg->find(run); //that's a lumi_in_run
	if(RunNode == reg->end() ){ //if run number is not found; enlist it.
		AddRun(run, lumi, event, reg);
		return false;
	}
	else return InvestigateLumi(lumi, event, RunNode); //found run, look for lumi
}//end RegisterEvent

bool CheckEvent(int run, int lumi, int event, eventRegistry* reg){
	//Check if an event is in the registry.
	//This never adds anything to the eventRegistry,only asks if the event is already there. 
	eventRegistry::const_iterator RunNode = reg->find(run); //that's a lumi_in_run
	if(RunNode == reg->end() ){ //if run number is not found; enlist it.
		return false;
	}
	else return probeLumi(lumi, event, RunNode); //found run, look for lumi
}//end CheckEvent

bool InvestigateLumi(int lumi, int event, eventRegistry::const_iterator RunNode){ 
	//Use this when the run is found. 
	//Takes in RunNode -- which is the entry in eventRegistry for this run number. 
	//It searches for the event in RunNode's lumi_in_run. 
	//If found, investigate the event number; 
	//else if not found, enlist it. 
	lumi_in_run::const_iterator LumiNode = RunNode->second->find(lumi);//Try to find this lumi in the list for this runNode. 
									   //under this runNode, access the lumi list, find lumi in it.
	if(LumiNode == RunNode->second->end() ){ //if lumi is not found the in list
		AddLumi(lumi, event, RunNode->second); //enlist it
		return false;
	}
	else return InvestigateEvent(event, LumiNode); //else if found lumi, see if the event number is enlisted.
}//end InvestigateLumi
bool probeLumi(int lumi, int event, eventRegistry::const_iterator RunNode){ 
	//Use this when the run is found. 
	//Takes in RunNode -- which is the entry in eventRegistry for this run number. 
	//It searches for the event in RunNode's lumi_in_run. 
	//If found, check the event number; 
	//else if not found, return false.
	//This never adds anything to the eventRegistry
	lumi_in_run::const_iterator LumiNode = RunNode->second->find(lumi);//Try to find this lumi in the list for this runNode. 
									   //under this runNode, access the lumi list, find lumi in it.
	if(LumiNode == RunNode->second->end() ){ //if lumi is not found the in list
		return false;
	}
	else return probeEvent(event, LumiNode); //else if found lumi, see if the event number is enlisted.
}//end InvestigateLumi
	
bool InvestigateEvent(int event, lumi_in_run::const_iterator LumiNode){ 
	//Use this when the run and lumisection are found. 
	//Takes in LumiNode -- which is the entry in lumi_in_run for this lumi. 
	//It searches for the event in LumiNode's event_in_lumi. 
	//If found, return true; else if not found, enlist it. 
	events_in_lumi::const_iterator EventNode = LumiNode->second->find(event);//under this lumiNode, access the event list, find  event in it.
	if(EventNode == LumiNode->second->end() ){ //if not event number found event in the list
		LumiNode->second->insert(LumiNode->second->cend(),event); //enlist it
		return false;
	}
	else return true; //event is already in the list 
}//end InvestigateEvent

bool probeEvent(int event, lumi_in_run::const_iterator LumiNode){ 
	//Use this when the run and lumisection are found. 
	//Takes in LumiNode -- which is the entry in lumi_in_run for this lumi. 
	//It searches for the event in LumiNode's event_in_lumi. 
	//If found, return true; else if not found return false
	//This never adds anything to the eventRegistry
	events_in_lumi::const_iterator EventNode = LumiNode->second->find(event);//under this lumiNode, access the event list, find  event in it.
	return EventNode != LumiNode->second->end();
}//end InvestigateEvent

void AddLumi(int lumi, int event, lumi_in_run* LumiList){
	//Use this if lumisection has not yet been seen. 
	//Adds this lumi to the list of lumisections and enlists that event number 
	events_in_lumi* newevents = new events_in_lumi(); //make a new list of events
	newevents->insert(newevents->cend(),event); //insert the event number into that list. 
	LumiList->insert
	    (
	     LumiList->cend(),
	     std::pair<int,events_in_lumi*>(lumi,newevents)
	    ); //Add the list of events, indexed under the lumi, to the list of lumisections. 
}//end AddLumi

void AddRun(int run, int lumi, int event, eventRegistry* reg){
	//Use this if run has not yet been seen. 
	//Adds run to the list of runs and enlists that lumi and event number 
	events_in_lumi* newevents = new events_in_lumi();
	newevents->insert(newevents->cend(),event);
	lumi_in_run* newlumi = new lumi_in_run();
	newlumi->insert
	    (
	     newlumi->cend(),//first arg is the position hint. 
	     std::pair<int,events_in_lumi*>(lumi,newevents)
	    );

        reg->insert
	    (
	     reg->cend(),//first arg is position hint
	     std::pair<int,lumi_in_run *>(run,newlumi)
	    );
}//end AddRun

#endif
