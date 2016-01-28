#ifndef populate_BadEventRegistry_C
#define populate_BadEventRegistry_C

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "eventRegistry.C"
using namespace std;
void populate_BadEventRegistry(eventRegistry* BadEventRegistry, bool verbose=false);
void populate_from_file(eventRegistry* BadEventRegistry, string filename, bool verbose=false);


void populate_BadEventRegistry(eventRegistry* BadEventRegistry, bool verbose){
	//populates the bad event registry using known bad events from file. 
	//File lists retreived Jan 27, 2016 from https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#Event_Lists
	//This is the main script to interface with.
    clock_t startfor = clock();

    populate_from_file(BadEventRegistry, "/uscms_data/d2/abarker/area2/CMSSW_7_4_7/src/LJMet/Com/BadEventsBadEvents/badResolutionTrack_Jan13.txt", verbose);
    populate_from_file(BadEventRegistry, "/uscms_data/d2/abarker/area2/CMSSW_7_4_7/src/LJMet/Com/BadEvents/csc2015_Dec01.txt", verbose);
    populate_from_file(BadEventRegistry, "/uscms_data/d2/abarker/area2/CMSSW_7_4_7/src/LJMet/Com/BadEvents/ecalscn1043093_Dec01.txt", verbose);
    populate_from_file(BadEventRegistry, "/uscms_data/d2/abarker/area2/CMSSW_7_4_7/src/LJMet/Com/BadEvents/muonBadTrack_Jan13.txt", verbose);

    clock_t endfor = clock();
    if(verbose) cout << "Populated the BadEventRegistry in "<<((float) (endfor - startfor))/CLOCKS_PER_SEC<<" seconds"<<endl;
}//populate_BadEventRegistry



void populate_from_file(eventRegistry* BadEventRegistry, string filename, bool verbose){
	if(verbose) cout << "Reading CSC file" << std::endl;
	long int nEventsRead = 0;
	ifstream infile( filename );
	while (infile)
	{
		string thisline;
		if (!getline( infile, thisline )) break;

		istringstream thisline_stringstream( thisline );
		vector <string> line;
		while (thisline_stringstream)
		{
			string thenumber;
			if (!getline( thisline_stringstream, thenumber, ':' )) break;
			line.push_back( thenumber );
		}
		int run= std::atoi(line[0].c_str());
		int lumi = std::atoi(line[1].c_str());
		int event= std::atoi(line[2].c_str());
		RegisterEvent(run, lumi, event, BadEventRegistry);
	}
	if (!infile.eof()) cerr << "Error while reading bad event file!";
	if(verbose) cout << "Done reading Bad Evetns file, read in  "<<nEventsRead << " events"<<std::endl;
}//end populate_from_file
#endif

