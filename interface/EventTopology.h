#ifndef EVENTTOPOLOGY_h
#define EVENTTOPOLOGY_h

#include <iostream>
//#include <TH2.h>
//#include <TStyle.h>
//#include <TCanvas.h>
//#include <TH1F.h>
//#include "TAxis.h"
//#include "TMath.h"
//#include "math.h"
//#include <TH3.h>
#include "TFile.h"
//#include "TTree.h"
//#include "TLegend.h"
//#include "TLorentzVector.h"
//#include "PoissonError.h"
//#include "TGraphAsymmErrors.h"
//#include "TGraphErrors.h"
//#include "TGraph.h"
//#include "TF1.h"
//#include <map>
#include "interface/stringmap.h"
#include "interface/controlpannel.h"

using namespace std;
using namespace controlpannel;

		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	

class EventTopology{
    public:
	EventTopology(string _tag):tag(_tag){}
	~EventTopology(){
		passbit = false;
	}
	string tag;
	bool passbit;
	//maybe encode the definition of the cut.
};

typedef stringmap<EventTopology*>* LabelTopo;
LabelTopo setupTopos();
LabelTopo setupAllTopos();//for internal use only

LabelTopo setupTopos(){
    LabelTopo allTopos = setupAllTopos();
    LabelTopo retTopos = new stringmap<EventTopology*>();
    try{
	    for(int k=0;k<nEventTopologies;k++){
		    retTopos->set(s_EventTopology[k] , allTopos->get_throwable(s_EventTopology[k]));
	    }
    }
    catch(std::pair <std::string,int> errorpair){
	    cerr<<"Error in setupTopos: allTopos received invalid string key "<<errorpair.first<<endl;
	    std::terminate();
    }
    return retTopos;
}

LabelTopo setupAllTopos(){
//sets up all the Event topologies you've ever imagined. 
//call syntax: 
//LabelTopo topos = setupAllTopos();

	LabelTopo allTopos = new stringmap<EventTopology*>();
	//first compose an object for everything we've ever defined. 
	
	//examples:
        allTopos->set("MET30", new EventTopology("MET30"));
	{ EventTopology* temp = new EventTopology("ST");
	    temp->passbit = true;
		allTopos->set(temp->tag, temp); }

	return allTopos;
}//end setupAllTopos

#endif
