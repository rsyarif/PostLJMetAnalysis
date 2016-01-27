#ifndef DMCCLASS_LIST_H
#define DMCCLASS_LIST_H
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "TString.h"
#include <TChain.h>
#include "TTree.h"
#include "interface/utilities.h"
#include "interface/stringmap.h"
#include "interface/DMCblock.h"
#include "interface/DMCblock_list.h"
#include "interface/controlpannel.h"
using namespace std;
using namespace controlpannel;

/******* TABLE OF CONTENTS ********
vector<DMCclass*>    	setupDMCclasses()		sets up all the DMCclasses you've ever come up with
DMCclass* 		setupDMCclasses(name)		sets up one DMCclass that thaty you call by its name

stringmap<DMCclass*>* 	makemap(vector<DMCclass*>	makes a stringmap to all the DMCclasses so you can call a bunch by name

vector<DMCclass*> 	MCbkgDMCclassUP(bool Tis50ns_Fis25ns);  	returns a list of DMC classes for al the MC bkg
vector<DMCclass*> 	MCbkgDMCclassDOWN(bool Tis50ns_Fis25ns);  	//same but using DOWN	
vector<DMCclass*> 	MCbkgDMCclass(bool Tis50ns_Fis25ns);  		//same but using UP	
 *********************************/

 //Written by Anthony Barker, 2015


std::vector<DMCclass*> setupDMCclasses();
stringmap<DMCclass*>* makemap(std::vector<DMCclass*> vc);
DMCclass * setupDMCclass(string name);

std::vector<DMCclass*> MCbkgDMCclass(bool Tis50ns_Fis25ns, bool useV = true);  	
std::vector<DMCclass*> MCbkgDMCclassUP(bool Tis50ns_Fis25ns, bool useV = true);  	
std::vector<DMCclass*> MCbkgDMCclassDOWN(bool Tis50ns_Fis25ns, bool useV = true);  	
std::vector<DMCclass*> MCTpTpsigDMCclass(bool Tis50ns_Fis25ns);  	
void DoSignalMeta(DMCclass* c);

std::vector<DMCclass*> setupDMCclasses(){
	std::vector<DMCclass*> DMCclasses;

	std::vector<DMCblock*> vb = setupDMCblocks(); //all the blocks
	std::map<string, int> mb = makemap(vb);
        namedInt null_int_meta;
        namedFloat null_float_meta;
        namedString null_string_meta;
        //null_int_meta, null_float_meta, null_string_meta,

	cout<<"start setupDMCclasses:"<<endl;

	//      ____        __       
	//     / __ \____ _/ /_____ _
	//    / / / / __ `/ __/ __ `/
	//   / /_/ / /_/ / /_/ /_/ / 
	//  /_____/\__,_/\__/\__,_/  

//chances are the only command you'll want here is: 
//DMCclass* mydata = setupDMCclass("Data2lepf");
        namedInt data_int_meta= {{"FillColor",0},{"LineColor",0},{"isData",1},{"isSignal",0}};
        namedString data_string_meta= {{"LegendLabel","DATA"}};
	DMCclasses.push_back(new DMCclass("Dataf",-1000,-1,vb,data_int_meta, null_float_meta, data_string_meta,false)); //all your 25ns data
	//DMCclasses.push_back(new DMCclass("Datas",-1000,-1,vb,data_int_meta, null_float_meta, data_string_meta,true)); //all your 50ns data, whether or not it has a field. 

	//DMCclasses.push_back(new DMCclass("Data1lepf",-19,-1,vb,data_int_meta, null_float_meta, data_string_meta,false)); //all the single lepton data sets with 25ns
	DMCclasses.push_back(new DMCclass("Data2lepf",-49,-20,vb,data_int_meta, null_float_meta, data_string_meta,false)); //all dilepton data sets with 25ns
        
	//     _____ _                   __   __  _________
	//    / ___/(_)___ _____  ____ _/ /  /  |/  / ____/
	//    \__ \/ / __ `/ __ \/ __ `/ /  / /|_/ / /     
	//   ___/ / / /_/ / / / / /_/ / /  / /  / / /___   
	//  /____/_/\__, /_/ /_/\__,_/_/  /_/  /_/\____/   
	//         /____/                                  
//{{"TprimeMass",900}}
//chances are the only command you'll want here is: 
//std::vector<DMCclass*> sigClasses = MCTpTpsigDMCclass(false);

        namedInt signal_int_meta= {{"FillColor",0},{"LineColor",kBlue},{"isData",0},{"isSignal",1}};
	DMCclasses.push_back(new DMCclass("TpTp700f",vb[mb["TpTp700f"]],signal_int_meta, null_float_meta, null_string_meta,false));
	DMCclasses.push_back(new DMCclass("TpTp800f",vb[mb["TpTp800f"]],signal_int_meta, null_float_meta, null_string_meta,false));
	DMCclasses.push_back(new DMCclass("TpTp900f",vb[mb["TpTp900f"]],signal_int_meta, null_float_meta, null_string_meta,false));
	DMCclasses.push_back(new DMCclass("TpTp1000f",vb[mb["TpTp1000f"]],signal_int_meta, null_float_meta, null_string_meta,false));
	DMCclasses.push_back(new DMCclass("TpTp1100f",vb[mb["TpTp1100f"]],signal_int_meta, null_float_meta, null_string_meta,false));
	DMCclasses.push_back(new DMCclass("TpTp1200f",vb[mb["TpTp1200f"]],signal_int_meta, null_float_meta, null_string_meta,false));
	DMCclasses.push_back(new DMCclass("TpTp1300f",vb[mb["TpTp1300f"]],signal_int_meta, null_float_meta, null_string_meta,false));
	DMCclasses.push_back(new DMCclass("TpTp1400f",vb[mb["TpTp1400f"]],signal_int_meta, null_float_meta, null_string_meta,false));
	DMCclasses.push_back(new DMCclass("TpTp1500f",vb[mb["TpTp1500f"]],signal_int_meta, null_float_meta, null_string_meta,false));
	DMCclasses.push_back(new DMCclass("TpTp1600f",vb[mb["TpTp1600f"]],signal_int_meta, null_float_meta, null_string_meta,false));
	DMCclasses.push_back(new DMCclass("TpTp1700f",vb[mb["TpTp1700f"]],signal_int_meta, null_float_meta, null_string_meta,false));
	DMCclasses.push_back(new DMCclass("TpTp1800f",vb[mb["TpTp1800f"]],signal_int_meta, null_float_meta, null_string_meta,false));

/*	DMCclasses.push_back(new DMCclass("TpTp700s",vb[mb["TpTp700s"]],signal_int_meta, null_float_meta, null_string_meta,true));
	DMCclasses.push_back(new DMCclass("TpTp800s",vb[mb["TpTp800s"]],signal_int_meta, null_float_meta, null_string_meta,true));
	DMCclasses.push_back(new DMCclass("TpTp900s",vb[mb["TpTp900s"]],signal_int_meta, null_float_meta, null_string_meta,true));
	DMCclasses.push_back(new DMCclass("TpTp1000s",vb[mb["TpTp1000s"]],signal_int_meta, null_float_meta, null_string_meta,true));
	DMCclasses.push_back(new DMCclass("TpTp1100s",vb[mb["TpTp1100s"]],signal_int_meta, null_float_meta, null_string_meta,true));
	DMCclasses.push_back(new DMCclass("TpTp1200s",vb[mb["TpTp1200s"]],signal_int_meta, null_float_meta, null_string_meta,true));
	DMCclasses.push_back(new DMCclass("TpTp1300s",vb[mb["TpTp1300s"]],signal_int_meta, null_float_meta, null_string_meta,true));
	DMCclasses.push_back(new DMCclass("TpTp1400s",vb[mb["TpTp1400s"]],signal_int_meta, null_float_meta, null_string_meta,true));
	DMCclasses.push_back(new DMCclass("TpTp1500s",vb[mb["TpTp1500s"]],signal_int_meta, null_float_meta, null_string_meta,true));
	DMCclasses.push_back(new DMCclass("TpTp1600s",vb[mb["TpTp1600s"]],signal_int_meta, null_float_meta, null_string_meta,true));
	DMCclasses.push_back(new DMCclass("TpTp1700s",vb[mb["TpTp1700s"]],signal_int_meta, null_float_meta, null_string_meta,true));
	DMCclasses.push_back(new DMCclass("TpTp1800s",vb[mb["TpTp1800s"]],signal_int_meta, null_float_meta, null_string_meta,true));*/

	//      ____  __            __  _________
	//     / __ )/ /______ _   /  |/  / ____/
	//    / __  / //_/ __ `/  / /|_/ / /     
	//   / /_/ / ,< / /_/ /  / /  / / /___   
	//  /_____/_/|_|\__, /  /_/  /_/\____/   
	//             /____/                    
	//Backgrounds 

        namedInt ST_int_meta= {{"FillColor",kViolet-6},{"LineColor",kViolet-6},{"isData",0},{"isSignal",0}};
        namedString ST_string_meta= {{"LegendLabel","SingleTop"}};
	{ DMCclass* temp = new DMCclass("STf",vb[mb["STtchf"]],ST_int_meta, null_float_meta, ST_string_meta,false);
	    temp->add(vb[mb["STtbarWf"]]);
	    temp->add(vb[mb["STtWf"]]);
	    DMCclasses.push_back(temp); }
	/*{ DMCclass* temp = new DMCclass("STDOWNs",vb[mb["STtchDOWNs"]],ST_int_meta, null_float_meta, ST_string_meta,true);
	    temp->add(vb[mb["STtbarWDOWNs"]]);
	    temp->add(vb[mb["STtWDOWNs"]]);
	    DMCclasses.push_back(temp); }*/
	{ DMCclass* temp = new DMCclass("STUPf",vb[mb["STtchUPf"]],ST_int_meta, null_float_meta, ST_string_meta,false);
	    temp->add(vb[mb["STtbarWUPf"]]);
	    temp->add(vb[mb["STtWUPf"]]);
	    DMCclasses.push_back(temp); }

	/*{ DMCclass* temp = new DMCclass("STs",vb[mb["STtchs"]],ST_int_meta, null_float_meta, ST_string_meta,true);
	    temp->add(vb[mb["STtbarWs"]]);
	    temp->add(vb[mb["STtWs"]]);
	    DMCclasses.push_back(temp); }*/
	{ DMCclass* temp = new DMCclass("STDOWNf",vb[mb["STtchDOWNf"]],ST_int_meta, null_float_meta, ST_string_meta,false);
	    temp->add(vb[mb["STtbarWDOWNf"]]);
	    temp->add(vb[mb["STtWDOWNf"]]);
	    DMCclasses.push_back(temp); }

	/*{ DMCclass* temp = new DMCclass("STUPs",vb[mb["STtchUPs"]],ST_int_meta, null_float_meta, ST_string_meta,true);
	    temp->add(vb[mb["STtbarWUPs"]]);
	    temp->add(vb[mb["STtWUPs"]]);
	    DMCclasses.push_back(temp); }*/


	namedInt ttj_int_meta= {{"FillColor",kViolet-5},{"LineColor",kViolet-5},{"isData",0},{"isSignal",0}};
	namedString ttj_string_meta= {{"LegendLabel","t#bar{t}"}};
	DMCclasses.push_back(new DMCclass("ttjf",vb[mb["ttj_highstatsf"]],ttj_int_meta, null_float_meta, ttj_string_meta,false);
	DMCclasses.push_back(new DMCclass("ttjDOWNf",vb[mb["ttjDOWNf"]],ttj_int_meta, null_float_meta, ttj_string_meta,false));
	DMCclasses.push_back(new DMCclass("ttjUPf",vb[mb["ttjUPf"]],ttj_int_meta, null_float_meta, ttj_string_meta,false));

	/*DMCclasses.push_back(new DMCclass("ttjs",vb[mb["ttjs"]],ttj_int_meta, null_float_meta, ttj_string_meta,true));
	DMCclasses.push_back(new DMCclass("ttjDOWNs",vb[mb["ttjDOWNs"]],ttj_int_meta, null_float_meta, ttj_string_meta,true));
	DMCclasses.push_back(new DMCclass("ttjUPs",vb[mb["ttjUPs"]],ttj_int_meta, null_float_meta, ttj_string_meta,true));*/


	DMCclasses.push_back(new DMCclass("TTVf",50, 69,vb,{{"FillColor",kViolet+5},{"LineColor",kViolet+5},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","t#bar{t}V"}},false)); //all TTV 25ns
	DMCclasses.push_back(new DMCclass("TTWf",50, 59,vb,{{"FillColor",kViolet+5},{"LineColor",kViolet+5},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","t#bar{t}W"}},false)); //all TTW 25ns
//	DMCclasses.push_back(new DMCclass("TTZf",60, 69,vb,{{"FillColor",kViolet+4},{"LineColor",kViolet+4},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","t#bar{t}Z"}},false)); //all TTZ 25ns

	//DMCclasses.push_back(new DMCclass("TTVs",50, 69,vb,{{"FillColor",kViolet+5},{"LineColor",kViolet+5},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","t#bar{t}V"}},true)); //all TTV 25ns
	//DMCclasses.push_back(new DMCclass("TTWs",50, 59,vb,{{"FillColor",kViolet+5},{"LineColor",kViolet+5},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","t#bar{t}W"}},true)); //all TTW 25ns
	//DMCclasses.push_back(new DMCclass("TTZs",60, 69,vb,{{"FillColor",kViolet+4},{"LineColor",kViolet+4},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","t#bar{t}Z"}},true)); //all TTZ 25ns

	DMCclasses.push_back(new DMCclass("DYJetsToLLf",71,vb,{{"FillColor",kRed+1},{"LineColor",kRed+1},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","DY"}},false));//DY 25ns
	//DMCclasses.push_back(new DMCclass("DYJetsToLLs",72,vb,{{"FillColor",kRed+1},{"LineColor",kRed+1},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","DY"}},true));//DY 50ns

	//DMCclasses.push_back(new DMCclass("QCDs",80,vb,{{"FillColor",kOrange-5},{"LineColor",kOrange-5},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","QCD"}},true));//qcd 50ns
	{
	    DMCclass* temp = new DMCclass("QCDf",85,vb,{{"FillColor",kOrange-5},{"LineColor",kOrange-5},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","QCD"}},false);//QCD 25ns em enriched
	    //temp->addtype(83,vb); //QCD em enriched 25ns
	    //temp->addtype(85,vb); //QCD mu enriched 25ns
	    DMCclasses.push_back(temp);
	}

	DMCclasses.push_back(new DMCclass("WJetToLNuf",111,vb,{{"FillColor",kPink-4},{"LineColor",kPink-4},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","WJET"}},false)); //25ns
// 	DMCclasses.push_back(new DMCclass("WJetToLNu_madgraphf",vb[mb["WJetToLNu_madgraph"]],{{"FillColor",kPink-4},{"LineColor",kPink-4},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","WJET"}},true)); //this weird 50ns WJetToLNu_thingys
// 	DMCclasses.push_back(new DMCclass("WJetToLNu_amcatnlof",vb[mb["WJetToLNu_amcatnlo"]],{{"FillColor",kPink-4},{"LineColor",kPink-4},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","WJET"}},true)); //this weird 50ns WJetToLNu_thingys
	//DMCclasses.push_back(new DMCclass("WJetToLNus",vb[mb["WJetToLNu_thingys"]],{{"FillColor",kPink-4},{"LineColor",kPink-4},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","WJET"}},true)); //this weird 50ns WJetToLNu_thingys

	DMCclasses.push_back(new DMCclass("VVf",121, 142,vb,{{"FillColor",kRed-9},{"LineColor",kRed-9},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","VV"}},false)); //25ns WW, ZZ, WZ combined
	DMCclasses.push_back(new DMCclass("WWf",vb[mb["WWf"]],{{"FillColor",kRed-9},{"LineColor",kRed-9},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","WW"}},false));
	DMCclasses.push_back(new DMCclass("WZf",vb[mb["WZf"]],{{"FillColor",kRed+4},{"LineColor",kRed+4},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","WZ"}},false));
	DMCclasses.push_back(new DMCclass("ZZf",vb[mb["ZZf"]],{{"FillColor",kRed+2},{"LineColor",kRed+2},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","ZZ"}},false));

/*	DMCclasses.push_back(new DMCclass("VVs",121, 142,vb,{{"FillColor",kRed-9},{"LineColor",kRed-9},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","VV"}},true)); //50ns WW, ZZ, WZ combined
	DMCclasses.push_back(new DMCclass("WWs",vb[mb["WWs"]],{{"FillColor",kRed-9},{"LineColor",kRed-9},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","WW"}},true));
	DMCclasses.push_back(new DMCclass("WZs",vb[mb["WZs"]],{{"FillColor",kRed+4},{"LineColor",kRed+4},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","WZ"}},true));
	DMCclasses.push_back(new DMCclass("ZZs",vb[mb["ZZs"]],{{"FillColor",kRed+3},{"LineColor",kRed+2},{"isData",0},{"isSignal",0}}, null_float_meta, {{"LegendLabel","ZZ"}},true));*/

//	DMCclasses.push_back(new DMCclass("VVVf",150, 189,vb,null_int_meta, null_float_meta, null_string_meta,false)); //25ns WWW, WWZ, WZZ, ZZZ
//	DMCclasses.push_back(new DMCclass("VVVs",150, 189,vb,null_int_meta, null_float_meta, null_string_meta,true)); //50ns WWW, WWZ, WZZ, ZZZ

	for(std::vector<DMCclass*>::iterator iclass = DMCclasses.begin();iclass<DMCclasses.end();iclass++){
		//cout<<"Do signal meta for "<<(*iclass)->name<<endl; //crashes just before 700s
		//This is a likely place for crashes to happen. 
		 DoSignalMeta(*iclass);
	}

	cout<<"finished setupDMCclasses"<<endl;
	return DMCclasses;
}//end setup

stringmap<DMCclass*>* makemap(std::vector<DMCclass*> vc){
    stringmap<DMCclass*>* m = new stringmap<DMCclass*>;
    for(std::vector<DMCclass*>::iterator it = vc.begin(); it != vc.end(); it++){ 
	m->set((*it)->name,*it);
    }
    return m;
} //make map

DMCclass * setupDMCclass(string name){  	
    //returns a pointer to a fully setup DMCclass, ready to use.

	cout<<"Doing setupDMCclass for "<<name<<endl;
    std::vector<DMCclass*> vp = setupDMCclasses();
    for(std::vector<DMCclass*>::iterator it = vp.begin(); it != vp.end(); it++){ 
	DMCclass* thisblock = *it;// = vp[pmap[s_name]];//default nonsense value
	if((*it)->name.compare(name) == 0){ // they are the same
	    	//cout<<"In setupDMCclass, searching for "<<name<<" and foind it"<<endl;
		return *it;
	}
    }//end for
    cerr<<"WARNING !! DID NOT FIND DMC class!! USING DEFAULT POINT"<<endl;
    return new DMCclass("default",true);
}//end setupDMCclass

std::vector<DMCclass*> MCbkgDMCclass(bool Tis50ns_Fis25ns, bool useV){  	
    std::vector<DMCclass*> vc = setupDMCclasses();
    stringmap<DMCclass*>*  mc = makemap(vc);
    std::vector<DMCclass*> vret;
    try{
	if(Tis50ns_Fis25ns){//50ns
	    vret.push_back(mc->get_throwable("STs"));
	    vret.push_back(mc->get_throwable("ttjs"));
	    if(useV)vret.push_back(mc->get_throwable("TTVs"));
	    else{
		vret.push_back(mc->get_throwable("TTWs"));
		vret.push_back(mc->get_throwable("TTZs"));
	    }
	    vret.push_back(mc->get_throwable("DYJetsToLLs"));
	    vret.push_back(mc->get_throwable("QCDs"));
	    vret.push_back(mc->get_throwable("WJetToLNus"));
	    if(useV)vret.push_back(mc->get_throwable("VVs"));
	    else{
		vret.push_back(mc->get_throwable("WWs"));
		vret.push_back(mc->get_throwable("WZs"));
		vret.push_back(mc->get_throwable("ZZs"));
	    }

	}
	else{//25ns
	    vret.push_back(mc->get_throwable("STf"));
	    vret.push_back(mc->get_throwable("ttjf"));
	    if(useV)vret.push_back(mc->get_throwable("TTVf"));
	    else{
		vret.push_back(mc->get_throwable("TTWf"));
		vret.push_back(mc->get_throwable("TTZf"));
	    }
	    vret.push_back(mc->get_throwable("DYJetsToLLf"));
	    vret.push_back(mc->get_throwable("QCDf"));
	    vret.push_back(mc->get_throwable("WJetToLNuf"));
	    if(useV)vret.push_back(mc->get_throwable("VVf"));
	    else{
		vret.push_back(mc->get_throwable("WWf"));
		vret.push_back(mc->get_throwable("WZf"));
		vret.push_back(mc->get_throwable("ZZf"));
	    }
	}
    }
    catch(std::pair <std::string,int> errorpair){
	cerr<<"Error in MCbkgDMCclass stringmap: Invalid string key "<<errorpair.first<<endl; 
	std::terminate();
    }
    return vret;
}//end MCbkgDMCclass

std::vector<DMCclass*> MCbkgDMCclassDOWN(bool Tis50ns_Fis25ns, bool useV){  	
    std::vector<DMCclass*> vc = setupDMCclasses();
    stringmap<DMCclass*>*  mc = makemap(vc);
    std::vector<DMCclass*> vret;
    try{
	if(Tis50ns_Fis25ns){//50ns
	    vret.push_back(mc->get_throwable("STDOWNs"));
	    vret.push_back(mc->get_throwable("ttjDOWNs"));
            if(useV)vret.push_back(mc->get_throwable("TTVs"));
            else{
                vret.push_back(mc->get_throwable("TTWs"));
                vret.push_back(mc->get_throwable("TTZs"));
            }
	    vret.push_back(mc->get_throwable("DYJetsToLLs"));
	    vret.push_back(mc->get_throwable("QCDs"));
	    vret.push_back(mc->get_throwable("WJetToLNus"));
	    if(useV)vret.push_back(mc->get_throwable("VVs"));
            else{
                vret.push_back(mc->get_throwable("WWs"));
                vret.push_back(mc->get_throwable("WZs"));
                vret.push_back(mc->get_throwable("ZZs"));
	    }

	}
	else{//25ns
	    vret.push_back(mc->get_throwable("STDOWNf"));
	    vret.push_back(mc->get_throwable("ttjDOWNf"));
	    if(useV)vret.push_back(mc->get_throwable("TTVf"));
	    else{
		vret.push_back(mc->get_throwable("TTWf"));
		vret.push_back(mc->get_throwable("TTZf"));
	    }
	    vret.push_back(mc->get_throwable("DYJetsToLLf"));
	    vret.push_back(mc->get_throwable("QCDf"));
	    vret.push_back(mc->get_throwable("WJetToLNuf"));
	    if(useV)vret.push_back(mc->get_throwable("VVf"));
	    else{
		vret.push_back(mc->get_throwable("WWf"));
		vret.push_back(mc->get_throwable("WZf"));
		vret.push_back(mc->get_throwable("ZZf"));
	    }
	}
    }
    catch(std::pair <std::string,int> errorpair){
	cerr<<"Error in MCbkgDMCclass stringmap: Invalid string key "<<errorpair.first<<endl; 
	std::terminate();
    }
    return vret;
}//end MCbkgDMCclassDOWN

std::vector<DMCclass*> MCbkgDMCclassUP(bool Tis50ns_Fis25ns, bool useV){  	
    std::vector<DMCclass*> vc = setupDMCclasses();
    stringmap<DMCclass*>*  mc = makemap(vc);
    std::vector<DMCclass*> vret;
    try{
	if(Tis50ns_Fis25ns){//50ns
	    vret.push_back(mc->get_throwable("STUPs"));
	    vret.push_back(mc->get_throwable("ttjUPs"));
            if(useV)vret.push_back(mc->get_throwable("TTVs"));
            else{
                vret.push_back(mc->get_throwable("TTWs"));
                vret.push_back(mc->get_throwable("TTZs"));
            }
	    vret.push_back(mc->get_throwable("DYJetsToLLs"));
	    vret.push_back(mc->get_throwable("QCDs"));
	    vret.push_back(mc->get_throwable("WJetToLNus"));
	    if(useV)vret.push_back(mc->get_throwable("VVs"));
            else{
                vret.push_back(mc->get_throwable("WWs"));
                vret.push_back(mc->get_throwable("WZs"));
                vret.push_back(mc->get_throwable("ZZs"));
	    }

	}
	else{//25ns
	    vret.push_back(mc->get_throwable("STUPf"));
	    vret.push_back(mc->get_throwable("ttjUPf"));
	    if(useV)vret.push_back(mc->get_throwable("TTVf"));
	    else{
		vret.push_back(mc->get_throwable("TTWf"));
		vret.push_back(mc->get_throwable("TTZf"));
	    }
	    vret.push_back(mc->get_throwable("DYJetsToLLf"));
	    vret.push_back(mc->get_throwable("QCDf"));
	    vret.push_back(mc->get_throwable("WJetToLNuf"));
	    if(useV)vret.push_back(mc->get_throwable("VVf"));
	    else{
		vret.push_back(mc->get_throwable("WWf"));
		vret.push_back(mc->get_throwable("WZf"));
		vret.push_back(mc->get_throwable("ZZf"));
	    }
	}
    }
    catch(std::pair <std::string,int> errorpair){
	cerr<<"Error in MCbkgDMCclass stringmap: Invalid string key "<<errorpair.first<<endl; 
	std::terminate();
    }
    return vret;
}//end MCbkgDMCclassUP

std::vector<DMCclass*> MCTpTpsigDMCclass(bool Tis50ns_Fis25ns){
    std::vector<DMCclass*> vc = setupDMCclasses();
    stringmap<DMCclass*>*  mc = makemap(vc);
    std::vector<DMCclass*> vret;
    try{
	if(Tis50ns_Fis25ns){//50ns
	    vret.push_back(mc->get_throwable("TpTp700s"));
	    vret.push_back(mc->get_throwable("TpTp800s"));
	    vret.push_back(mc->get_throwable("TpTp900s"));
	    vret.push_back(mc->get_throwable("TpTp1000s"));
	    vret.push_back(mc->get_throwable("TpTp1100s"));
	    vret.push_back(mc->get_throwable("TpTp1200s"));
	    vret.push_back(mc->get_throwable("TpTp1300s"));
	    vret.push_back(mc->get_throwable("TpTp1400s"));
	    vret.push_back(mc->get_throwable("TpTp1500s"));
	    vret.push_back(mc->get_throwable("TpTp1600s"));
	    vret.push_back(mc->get_throwable("TpTp1700s"));
	    vret.push_back(mc->get_throwable("TpTp1800s"));
	}//end if
	else{//25ns
	    vret.push_back(mc->get_throwable("TpTp700f"));
	    vret.push_back(mc->get_throwable("TpTp800f"));
	    vret.push_back(mc->get_throwable("TpTp900f"));
	    vret.push_back(mc->get_throwable("TpTp1000f"));
	    vret.push_back(mc->get_throwable("TpTp1100f"));
	    vret.push_back(mc->get_throwable("TpTp1200f"));
	    vret.push_back(mc->get_throwable("TpTp1300f"));
	    vret.push_back(mc->get_throwable("TpTp1400f"));
	    vret.push_back(mc->get_throwable("TpTp1500f"));
	    vret.push_back(mc->get_throwable("TpTp1600f"));
	    vret.push_back(mc->get_throwable("TpTp1700f"));
	    vret.push_back(mc->get_throwable("TpTp1800f"));
	}//end else
    }//end try
    catch(std::pair <std::string,int> errorpair){
	cerr<<"Error in MCbkgDMCclass stringmap: Invalid string key "<<errorpair.first<<endl; 
	std::terminate();
    }
    return vret;
}//end MCTpTpsigDMCclass

void DoSignalMeta(DMCclass* c){
	//automatically sets some metadata for signal
    if(c->int_meta.find("isSignal") != c->int_meta.end() && c->int_meta["isSignal"] == 1){
	int thisTpMass = c->blocks[0]->int_meta["TprimeMass"];
	c->int_meta["TprimeMass"] = thisTpMass;
	c->string_meta[""] = "T'#bar{T}' ("+to_string(thisTpMass) + " GeV) x " + to_string((int) SignalInflationFactor);
    }
}//end DOSignalMeta
#endif
