#ifndef DMCBLOCK_LIST_H
#define DMCBLOCK_LIST_H
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "TString.h"
#include <TChain.h>
#include "TTree.h"
#include "interface/utilities.h"
#include "interface/DMCblock.h"
using namespace std;

//For T' work, use this in concert with 
//makeLJMETflist.csh
//which builds the filelists here.

/******* TABLE OF CONTENTS ********
  Reference	Type	Description
  -----------------------------------
  higgsBr
  data_t1	-1	data
  stophig_t0	0	stop-higgsino fastsim, Yevgeni origional, default 
 *********************************/

/******* STRING_META TABLE *******
  Label		Description
  -----------------------------------
 *********************************/

/******** INT_META TABLE ********
  Label		Description
  -----------------------------------
 *********************************/

/******* FLOAT_META TABLE ********
  Label		Description
  -----------------------------------
 *********************************/
 //Written by Anthony Barker, 2015


DMCblock * setupDMCblock(string name, string filepath="");
//void printDMCblocks();
std::map<string, int> makemap(std::vector<DMCblock*> DMCblocks); //a LUT map between the DMCblock names and where they are in the DMCblocks vector, so you can call by name.
std::vector<DMCblock*> setupDMCblocks();

std::vector<DMCblock*> setupDMCblocks(){
	std::vector<DMCblock*> DMCblocks;
	cout<<"start setupDMCblocks:"<<endl;
	//last four inputs: bool isMC_ = true, bool Tis50ns_Fis25ns_ = false, float sqrtS_ = 13., bool BfieldOn_ = true

	namedInt null_int_meta;
	namedFloat null_float_meta;
	namedString null_string_meta;

	//      ____        __       
	//     / __ \____ _/ /_____ _
	//    / / / / __ `/ __/ __ `/
	//   / /_/ / /_/ / /_/ /_/ / 
	//  /_____/\__,_/\__/\__,_/  
	//                           

	//Currently PRD consists of only one run: 258159, so the data is only 2 or 3 files. The RR stops at RR stopped at 258158, it has a lot of files.  2015D has 552 /pb so far. We drop 2015C b/c it only has 16/pb.

/*	{//Single Electron 
		int typedecade = 0;
		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/SingleElectron_PRC.txt", typedecade-1, "DATA1elePRCf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/SingleElectron_PRD_25ns.txt", typedecade-1, "DATA1elePRDf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/SingleElectron_RRD_25ns.txt", typedecade-3, "DATA1eleRRDf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
	}

	{//Single Muon
		int typedecade = -10;
		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/SingleMuon_PRC.txt", typedecade-1, "DATA1muPRCf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/SingleMuon_PRD_25ns.txt", typedecade-1, "DATA1muPRDf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/SingleMuon_RRD_25ns.txt", typedecade-3, "DATA1muRRDf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
	}*/
	{//Double Electron
		int typedecade = -20;
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DoubleEG_PRD_25ns.txt", typedecade-1, "DATA2elePRDf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DoubleEG_RRC_25ns.txt", typedecade-3, "DATA2eleRRCf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DoubleEG_RRD_25ns.txt", typedecade-5, "DATA2eleRRDf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
	}
	{//Double Muon
		int typedecade = -30;
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DoubleMuon_PRD_25ns.txt", typedecade-1, "DATA2muPRDf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DoubleMuon_RRC_25ns.txt", typedecade-3, "DATA2muRRCf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DoubleMuon_RRD_25ns.txt", typedecade-5, "DATA2muRRDf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
	}
	{//Electron Muon MuonEG
		int typedecade = -40;
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/MuonEG_PRD_25ns.txt", typedecade-1, "DATA1ele1muPRDf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/MuonEG_RRC_25ns.txt", typedecade-3, "DATA1ele1muRRCf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/MuonEG_RRD_25ns.txt", typedecade-5, "DATA1ele1muRRDf", 0, 0, -1, null_int_meta, null_float_meta, null_string_meta, false, false, 13., true));
	}


	//     _____ _                   __   __  _________
	//    / ___/(_)___ _____  ____ _/ /  /  |/  / ____/
	//    \__ \/ / __ `/ __ \/ __ `/ /  / /|_/ / /     
	//   ___/ / / /_/ / / / / /_/ / /  / /  / / /___   
	//  /____/_/\__, /_/ /_/\__,_/_/  /_/  /_/\____/   
	//         /____/                                  

	{ //TprimeTprime Signal 25ns
		//cross sections for masses [700-1500] are from twiki.cern.ch/twiki/bin/view/CMS/B2GMonteCarlo, masses [1600-1800] are from MCM. 
		//cross section uncertainties for M700-M1500 are taken from the twiki. Take the max of the low and high scale error, and the max of the low and high PDF error
		//Then get the absoute error from each of these, then add the two errors in quadurture to get the results here. 
		int type = 1;
		static const float def_bWbr = 0.5;
		static const float def_tHbr = 0.25;
		static const float def_tZbr = 0.25;
		//more sensible br's can be found Tp toplogies.xlxs under Desktop/Tprime
		//Which is just a reading of Figure 2 out of FTR-13-026
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-700_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp700f", 0.455, 0.019, 798600, {{"TprimeMass",700}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp800f", 0.196, 0.008, 822000, {{"TprimeMass",800}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));//this cross section is wrong!
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp900f", 0.0903, 0.0041, 832800, {{"TprimeMass",900}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp1000f", 0.0440, 0.0021, 822800, {{"TprimeMass",1000}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp1100f", 0.0224, 0.0011, 821600, {{"TprimeMass",1100}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp1200f", 0.0118, 0.0006, 832800, {{"TprimeMass",1200}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp1300f", 0.00639, 0.00037, 830400, {{"TprimeMass",1300}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp1400f", 0.000354, 0.00022, 832800, {{"TprimeMass",1400}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp1500f", 0.00200, 0.00014, 812200, {{"TprimeMass",1500}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp1600f", 0.001148, 0.00009, 804000, {{"TprimeMass",1600}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));
		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp1600f", 0.00093471, cs_uncert, 804000, {{"TprimeMass",1600}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1700_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp1700f", 0.000666, 0.00006, 832400, {{"TprimeMass",1700}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));
		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1700_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp1700f", 0.00055711, cs_uncert, 832400, {{"TprimeMass",1700}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp1800f", 0.000391, 0.00004, 832800, {{"TprimeMass",1800}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));
		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns.txt", type, "TpTp1800f", 0.00033677, cs_uncert, 832800, {{"TprimeMass",1800}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, false, 13., true));
	}

	/*{ //TprimeTprime Signal 50ns
		//cross sections for masses [700-1500] are from twiki.cern.ch/twiki/bin/view/CMS/B2GMonteCarlo, masses [1600-1800] are from MCM. 
		int type = 2;
		static const float def_bWbr = 0.5;
		static const float def_tHbr = 0.25;
		static const float def_tZbr = 0.25;
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-700_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp700s", 0.455, 0.019, 798600, {{"TprimeMass",700}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp800s", 0.196, 0.008, 820000, {{"TprimeMass",800}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp900s", 0.0903, 0.0041, 832800, {{"TprimeMass",900}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp1000s", 0.0440, 0.0021, 819400, {{"TprimeMass",1000}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp1100s", 0.0224, 0.0011, 792600, {{"TprimeMass",1100}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp1200s", 0.0118, 0.0006, 832800, {{"TprimeMass",1200}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp1300s", 0.00639, 0.00036, 830400, {{"TprimeMass",1300}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp1400s", 0.000354, 0.00022, 832800, {{"TprimeMass",1400}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp1500s", 0.00200, 0.00014, 825800, {{"TprimeMass",1500}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp1600s", 0.001148, 0.00009, 804000, {{"TprimeMass",1600}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp1600s", 0.00093471, cs_uncert, 804000, {{"TprimeMass",1600}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1700_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp1700s", 0.000666, 0.00006, 832400, {{"TprimeMass",1700}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1700_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp1700s", 0.00055711, cs_uncert, 832400, {{"TprimeMass",1700}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp1800s", 0.000391, 0.00004, 832800, {{"TprimeMass",1800}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8_50ns.txt", type, "TpTp1800s", 0.00033677, cs_uncert, 832800, {{"TprimeMass",1800}}, {{"bWbr",def_bWbr},{"tHbr",def_tHbr},{"tZbr",def_tZbr}}, null_string_meta, true, true, 13., true));
	}*/

	//      ____  __            __  _________
	//     / __ )/ /______ _   /  |/  / ____/
	//    / __  / //_/ __ `/  / /|_/ / /     
	//   / /_/ / ,< / /_/ /  / /  / / /___   
	//  /_____/_/|_|\__, /  /_/  /_/\____/   
	//             /____/                    
	//Backgrounds 

	{	//Single Top 25ns
		//cs from https://twiki.cern.ch/twiki/bin/viewauth/CMS/SingleTopSigma
		int type_decade = 10; //types [11-32]
		float cs_pb_tchannel = 216.99;
		float cs_uncert_tchannel = 9.22;//=sqrt(6.62^2+6.16^2+1.81^2)
		float cs_pb_tW = 35.6;
		float cs_uncert_tW = 1.9;//=sqrt(0.9^2+1.7^2);
		float cs_pb_schannel = 11.36; //5% of single top.
		float cs_uncert_schannel = 0.48;//=sqrt(0.18^2+0.45^2)

		//25ns
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_25ns.txt", type_decade + 1, "STtchf", cs_pb_tchannel, cs_uncert_tchannel, 4291728, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));//MAIN //ngen was 6442497
		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_t-channel_4f_scaledown_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_25ns.txt", type_decade + 3, "STtchDOWNf", cs_pb_tchannel, cs_uncert_tchannel, 6442497, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));//DOWN
		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_t-channel_4f_scaleup_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_25ns.txt", type_decade + 5, "STtchUPf", cs_pb_tchannel, cs_uncert_tchannel, 6442497, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));//UP

		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_25ns.txt", type_decade + 7, "STtbarWf", cs_pb_tW, cs_uncert_tW, 988500, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));//tW antitop Powheg
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_tW_antitop_5f_scaledown_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_25ns.txt", type_decade + 9, "STtbarWDOWNf", cs_pb_tW, cs_uncert_tW, 497600, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));//tW antitop powheg down
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_tW_antitop_5f_scaleup_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_25ns.txt", type_decade + 11, "STtbarWUPf", cs_pb_tW, cs_uncert_tW, 500000, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));//tW antitop powheg up
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_25ns.txt", type_decade + 13, "STtWf", cs_pb_tW, cs_uncert_tW, 995600, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));//tW top Powheg
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_tW_top_5f_scaledown_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_25ns.txt", type_decade + 15, "STtWDOWNf", cs_pb_tW, cs_uncert_tW, 499200, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));//tW top powheg down
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_tW_top_5f_scaleup_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_25ns.txt", type_decade + 17, "STtWUPf", cs_pb_tW, cs_uncert_tW, 497600, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));//tW top powheg down .
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_25ns.txt", type_decade + 19, "STsf", cs_pb_schannel, cs_uncert_schannel, 613384, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));//tW top powheg down . //n events from https://cmsweb.cern.ch/das/request?input=/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM

		/* //Single Top 50ns
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_50ns.txt", type_decade + 2, "STtchs", cs_pb_tchannel, cs_uncert_tchannel, 860070, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));//Main for 50ns
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_t-channel_4f_scaledown_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_50ns.txt", type_decade + 4, "STtchDOWNs", cs_pb_tchannel, cs_uncert_tchannel, 860070, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));//up
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_t-channel_4f_scaleup_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_50ns.txt", type_decade + 6, "STtchUPs", cs_pb_tchannel, cs_uncert_tchannel, 860070, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));//Down


		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_50ns.txt", type_decade + 8, "STtbarWs", cs_pb_tW, cs_uncert_tW, 1000000, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));//tW antitop powheg 
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_tW_antitop_5f_scaledown_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_50ns.txt", type_decade + 10, "STtbarWDOWNs", cs_pb_tW, cs_uncert_tW, 1000000, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));//tW antitop powheg down
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_tW_antitop_5f_scaleup_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_50ns.txt", type_decade + 12, "STtbarWUPs", cs_pb_tW, cs_uncert_tW, 1000000, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));//tW antitop powheg up
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_50ns.txt", type_decade + 14, "STtWs", cs_pb_tW, cs_uncert_tW, 998400, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));//tW top powheg
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_tW_top_5f_scaledown_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_50ns.txt", type_decade + 16, "STtWDOWNs", cs_pb_tW, cs_uncert_tW, 998400, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));//tW top powheg
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_tW_top_5f_scaleup_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_50ns.txt", type_decade + 18, "STtWUPs", cs_pb_tW, cs_uncert_tW, 998400, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));//tW top powheg
		*/

		//why is there no 25ns version of these??? Is it just to see the difference between top and anti-top? 
		//these are very similar to type type_decade + 2 except with a different generator. 
		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1_50ns.txt", type_decade + 20, "STtchPowhegs", 136.02, 5.51, Ngen, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));
		//cs uncert = sqrt(4.09^2+3.52^2+1.11^2)

		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1_50ns.txt", type_decade + 22, "STtchbarPowhegs", 80.95, 4.13, Ngen, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));
		//cs uncert = sqrt(2.53^2+3.18^2+0.71^2)
	}//end singletop

	{//TTjets
		int type_decade = 40;
		float cs_pb = 831.76; // from https://twiki.cern.ch/twiki/bin/view/CMS/B2GPHYS14, bottom of the page
		float cs_uncert = 51.18; //from https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO#Top_quark_pair_cross_sections_at table for M=172.5
		//If for some strange reason you think you need to model the high Mtt taill, there are 
		//  TT_Mtt-700to1000_TuneCUETP8M1_13TeV-powheg-pythia8_25ns.txt
		//  TT_Mtt-1000toInf_TuneCUETP8M1_13TeV-powheg-pythia8_25ns.txt

		//25ns
// 		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TT_TuneCUETP8M1_13TeV-powheg-pythia8_25ns.txt", type_decade + 1, "ttjf", cs_pb, cs_uncert, 19757190, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true)); //MAIN NEW
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TT_TuneCUETP8M1_13TeV-powheg-pythia8_highstats_25ns.txt", type_decade + 3, "ttj_highstatsf", cs_pb, cs_uncert, 96834559, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true)); //extension high stats
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TT_TuneCUETP8M1_13TeV-powheg-scaledown-pythia8_25ns.txt", type_decade + 5, "ttjDOWNf", cs_pb, cs_uncert, 9860774, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true)); //down //NEW
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TT_TuneCUETP8M1_13TeV-powheg-scaleup-pythia8_25ns.txt", type_decade + 7, "ttjUPf", cs_pb, cs_uncert, 9921174, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true)); //up NEW

// 		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type_decade + 9, "ttjmadgraphf", cs_pb, cs_uncert, 11344206, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true)); //This exists for the sake of comparing generators if needed. I'm not sure whether the nGen is this or 11413480
	
		//50ns
		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_50ns.txt", type_decade + 0, "ttj$f", cs_pb, cs_uncert, Ngen = ???, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true)); //main madgraph.
	/*	int Ngen = 1656654; 
		//cs_pb = 831.76; stays the same
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_50ns.txt", type_decade + 2, "ttjs", cs_pb, cs_uncert, Ngen, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true)); // main 50ns 
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-scaledown-pythia8_50ns.txt", type_decade + 4, "ttjDOWNs", cs_pb, cs_uncert, Ngen, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true)); //down 50ns
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-scaleup-pythia8_50ns.txt", type_decade + 6, "ttjUPs", cs_pb, cs_uncert, Ngen, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true)); //up 25ns 
	*/
	}//end TTjets

	{//TTW
		//xxx check factors of three
		//cs from MCM
		int type_decade = 50;	
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_25ns.txt", type_decade + 1, "ttwLNuf", 0.2043, 0.0020, 129850, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_25ns.txt", type_decade + 3, "ttwQQf", 0.4062, 0.0021, 430330, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));

	//	DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_50ns.txt", type_decade + 2, "ttwLNus", 0.2043, 0.0020, 129527, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));
	//	DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_50ns.txt", type_decade + 4, "ttwQQs", 0.4062, 0.0021, 430031, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));
	}

	{//TTZ
		//xxx check factors of three
		int type_decade = 60;	
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_25ns.txt", type_decade +1, "ttzLLNNf", 0.2529, 0.0004, 184990, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_25ns.txt", type_decade+3, "ttzQQf", 0.5297, 0.0008, 351398, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));

		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_50ns.txt", type_decade+2, "ttzLLNNs", 0.2529, 0.0004, 185862 , null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));
	//	DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_50ns.txt", type_decade+4, "ttzQQs", 0.5297, 0.0008, 351398, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));
	}

	{//Drell Yan (Z) 25ns
		int type = 71;
		//cs: https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns#DY_Z
		//Get NGen from above by clicking on the DAS links. 
		//see also  https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeVInclusive, in the table multiply Z/a* / m(ll)>50 GeV = 2008.4*3=6025.2 
		//see also https://twiki.cern.ch/twiki/bin/view/CMS/B2GPHYS14 
		//to use this you would need to get effective ngen that includes negative weights, beware; 50-100 is really >50
		//float cs_uncert = 0;//xxx
		//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_25ns.txt", type, "DYJetsToLL10to50f", 18610, cs_uncert, 22217467, {{"Mlow",10},{"Mhigh",50}}, null_float_meta, null_string_meta, true, false, 13., true));///xxx
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_25ns.txt", type, "DYJetsToLL50toINFf", 6025.2 , 228.5, 19259107, {{"Mlow",50},{"Mhigh",99999}}, null_float_meta, null_string_meta, true, false, 13., true));
		//nGen was 19310834, previously 12020067. But the cross section is obviously too big if you do that and DAS says 28825132. That's probably #positibe - #negative. 
//https://cmsweb.cern.ch/das/request?input=/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM
		/*DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-100to200_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_25ns.txt", type, "DYJetsToLL100to200f", cs_pb, cs_uncert, 66348, {{"Mlow",100},{"Mhigh",200}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-200to400_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_25ns.txt", type, "DYJetsToLL200to400f", cs_pb, cs_uncert, 54656, {{"Mlow",200},{"Mhigh",400}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-400to500_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_25ns.txt", type, "DYJetsToLL400to500f", cs_pb, cs_uncert, 52045, {{"Mlow",400},{"Mhigh",500}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-500to700_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_25ns.txt", type, "DYJetsToLL500to700f", cs_pb, cs_uncert, 52027, {{"Mlow",500},{"Mhigh",700}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-700to800_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_25ns.txt", type, "DYJetsToLL700to800f", cs_pb, cs_uncert, 47947, {{"Mlow",700},{"Mhigh",800}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-800to1000_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_25ns.txt", type, "DYJetsToLL8000to1000f", cs_pb, cs_uncert, 20581, {{"Mlow",800},{"Mhigh",1000}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-1000to1500_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_25ns.txt", type, "DYJetsToLL1000to1500f", cs_pb, cs_uncert, 42155, {{"Mlow",1000},{"Mhigh",1500}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-1500to2000_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_25ns.txt", type, "DYJetsToLL1500to2000f", cs_pb, cs_uncert, 41185, {{"Mlow",1500},{"Mhigh",2000}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-2000to3000_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_25ns.txt", type, "DYJetsToLL2000to3000", cs_pb, cs_uncert, 37894, {{"Mlow",2000},{"Mhigh",99999}}, null_float_meta, null_string_meta, true, false, 13., true));*/
	}

	/*{//Drell Yan (Z) 50ns
		int type = 72;
		int Ngen = 13351018;  //this is broken for sure. xxx. guessing this is the ngen for >50
		//cs: https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns#DY_Z
		//see also  https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeVInclusive, in the table multiply Z/a* / m(ll)>50 GeV = 2008.4*3=6025.2 
		//see also https://twiki.cern.ch/twiki/bin/view/CMS/B2GPHYS14 
		//to use this you would need to get effective ngen that includes negative weights, beware; 50-100 is really >50
		float cs_uncert = 0;//xxx
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_50ns.txt", type, "DYJetsToLL10to50s", 18610, cs_uncert, Ngen, {{"Mlow",10},{"Mhigh",50}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_50ns.txt", type, "DYJetsToLL50toINFs", 6025.2, 228.5, Ngen, {{"Mlow",50},{"Mhigh",99999}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-100to200_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_50ns.txt", type, "DYJetsToLL100to200s", cs_pb, cs_uncert, Ngen, {{"Mlow",100},{"Mhigh",200}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-200to400_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_50ns.txt", type, "DYJetsToLL200to400s", cs_pb, cs_uncert, Ngen, {{"Mlow",200},{"Mhigh",400}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-400to500_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_50ns.txt", type, "DYJetsToLL400to500s", cs_pb, cs_uncert, Ngen, {{"Mlow",400},{"Mhigh",500}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-500to700_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_50ns.txt", type, "DYJetsToLL500to700s", cs_pb, cs_uncert, Ngen, {{"Mlow",500},{"Mhigh",700}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-700to800_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_50ns.txt", type, "DYJetsToLL700to800s", cs_pb, cs_uncert, Ngen, {{"Mlow",700},{"Mhigh",800}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-800to1000_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_50ns.txt", type, "DYJetsToLL800to1000s", cs_pb, cs_uncert, Ngen, {{"Mlow",800},{"Mhigh",1000}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-1000to1500_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_50ns.txt", type, "DYJetsToLL1000to1500s", cs_pb, cs_uncert, Ngen, {{"Mlow",1000},{"Mhigh",1500}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-1500to2000_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_50ns.txt", type, "DYJetsToLL1500to2000s", cs_pb, cs_uncert, Ngen, {{"Mlow",1500},{"Mhigh",2000}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/DYJetsToLL_M-2000to3000_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_50ns.txt", type, "DYJetsToLL2000to3000s", cs_pb, cs_uncert, Ngen, {{"Mlow",2000},{"Mhigh",99999}}, null_float_meta, null_string_meta, true, true, 13., true));
	}*/

	/*{//QCD Pt sorted, all 50ns. 
		int type = 80;
		float cs_uncert = 0;//xxx
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8_50ns.txt", type, "QCD30to50s", 140932000. , cs_uncert, 4899251, {{"PtLow",30},{"PtHigh",50}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8_50ns.txt", type, "QCD50to80s", 19204300., cs_uncert, 4966990, {{"PtLow",50},{"PtHigh",80}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8_50ns.txt", type, "QCD80to120s", 2762530. , cs_uncert, 3465021, {{"PtLow",80},{"PtHigh",120}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8_50ns.txt", type, "QCD120to170s", 471100. , cs_uncert, 3446207, {{"PtLow",120},{"PtHigh",170}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8_50ns.txt", type, "QCD170to300s", 117276. , cs_uncert, 3438066, {{"PtLow",170},{"PtHigh",300}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8_50ns.txt", type, "QCD300to470s", 7823. , cs_uncert, 2930578, {{"PtLow",300},{"PtHigh",470}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8_50ns.txt", type, "QCD470to600s", 648.2 , cs_uncert, 1939229, {{"PtLow",470},{"PtHigh",600}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8_50ns.txt", type, "QCD600to800s", 186.9 , cs_uncert, 1890256, {{"PtLow",600},{"PtHigh",800}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8_50ns.txt", type, "QCD800to1000s", 32.293 , cs_uncert, 1911296, {{"PtLow",800},{"PtHigh",1000}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8_50ns.txt", type, "QCD1000to1400s", 9.4183 , cs_uncert, 1461216, {{"PtLow",1000},{"PtHigh",1400}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8_50ns.txt", type, "QCD1400to1800s", 0.84265, cs_uncert, 197959, {{"PtLow",1400},{"PtHigh",1800}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8_50ns.txt", type, "QCD1800to2400s", 0.114943, cs_uncert, 194924, {{"PtLow",1800},{"PtHigh",2400}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8_50ns.txt", type, "QCD2400to3200s", 0.00682981, cs_uncert, 198383, {{"PtLow",2400},{"PtHigh",3200}}, null_float_meta, null_string_meta, true, true, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8_50ns.txt", type, "QCD3200toInfs", 0.000165445 , cs_uncert, 188696, {{"PtLow",3200},{"PtHigh",99999}}, null_float_meta, null_string_meta, true, true, 13., true));
	}*/

	/*{//QCD ele enriched 25ns
		//cross sections are MCM cross section * filter efficiency
		int type = 81;
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDelEn30to50f", 136000000*0.073 , 136000000*0.015, 4695884, {{"PtLow",30},{"PtHigh",50}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDelEn50to80f", 19800000*0.146 , 19800000*0.021, 5226884, {{"PtLow",50},{"PtHigh",80}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDelEn80to120f", 2800000*0.125 , 2800000*0.019, 8130424, {{"PtLow",80},{"PtHigh",120}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDelEn120to170f", 477000*0.132 , 477000*0.02, 8499194, {{"PtLow",120},{"PtHigh",170}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDelEn170to300f", 114000*0.165 , 114000*0.026, 5735584, {{"PtLow",170},{"PtHigh",300}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDelEn300toInff", 9000*0.15 , 9000*0.036, 3696716, {{"PtLow",300},{"PtHigh",99999}}, null_float_meta, null_string_meta, true, false, 13., true));
	}

	{//QCD mu enriched 25ns
		//cross sections are MCM cross section * filter efficiency
		int type = 83;
		float cs_uncert = 0;//xxx cross sections are not on the twiki https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns#QCD
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDmuEn30to50f", 139803000*0.01182 , cs_uncert, 9842165, {{"PtLow",30},{"PtHigh",50}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDmuEn50to80f", 19222500*0.02276 , cs_uncert, 5069469, {{"PtLow",50},{"PtHigh",80}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDmuEn80to120f", 2758420*0.03844 , cs_uncert, 2926805, {{"PtLow",80},{"PtHigh",120}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDmuEn120to170f", 469797*0.05362 , cs_uncert, 4026104, {{"PtLow",120},{"PtHigh",170}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDmuEn170to300f", 117989*0.07335 , cs_uncert, 3942640 , {{"PtLow",170},{"PtHigh",300}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDmuEn300to470f", 7820.25*0.10196 , cs_uncert, 3910268, {{"PtLow",300},{"PtHigh",470}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDmuEn470to600f", 645.528*0.12242 , cs_uncert, 1928421, {{"PtLow",470},{"PtHigh",600}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDmuEn600to800f", 187.109*0.13412 , cs_uncert, catdog, {{"PtLow",600},{"PtHigh",800}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDmuEn800to1000f", 32.3486*0.14552 , cs_uncert, 1982314, {{"PtLow",800},{"PtHigh",1000}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_25ns.txt", type, "QCDmuEn1000toInff", 10.4305*0.15544 , cs_uncert, 1981954, {{"PtLow",1000},{"PtHigh",99999}}, null_float_meta, null_string_meta, true, false, 13., true));
	}*/

	{
	//This is the main thing that everyone uses. 
	//https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns#QCD
	//ngen updated Jan 4, 2016.
	    int type = 85;
	    DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "QCDht100to200f", 27990000, 4073,  81637494, {{"HtLow",100},{"HtHigh",200}}, null_float_meta, null_string_meta, true, false, 13., true));
	    DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "QCDht200to300f", 1712000, 376.3,  18718905, {{"HtLow",200},{"HtHigh",300}}, null_float_meta, null_string_meta, true, false, 13., true));
	    DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "QCDht300to500f", 347700, 74.81,   19826197, {{"HtLow",300},{"HtHigh",500}}, null_float_meta, null_string_meta, true, false, 13., true));
	    DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "QCDht500to700f", 32100, 7,        19664159, {{"HtLow",500},{"HtHigh",700}}, null_float_meta, null_string_meta, true, false, 13., true));
	    DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "QCDht700to1000f", 6831, 1.7,    15356448, {{"HtLow",700},{"HtHigh",1000}}, null_float_meta, null_string_meta, true, false, 13., true));
	    DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "QCDht1000to1500f", 1207, 0.5,  4963895, {{"HtLow",1000},{"HtHigh",1500}}, null_float_meta, null_string_meta, true, false, 13., true));
	    DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "QCDht1500to2000f", 119.9, 0.06,3868886, {{"HtLow",1500},{"HtHigh",2000}}, null_float_meta, null_string_meta, true, false, 13., true));
	    DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "QCDht2000toInff", 25.24,  0.02,  1912529, {{"HtLow",2000},{"HtHigh",99999}}, null_float_meta, null_string_meta, true, false, 13., true));
	}

	{//Wjets
		int type = 111;
		float k_wjet = 1.21; //1.21 = k-factor )# https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
		//Useing high precision cross sections from Sadia's email Nov 4, 2015 titled " higher precision cross-sections for the GJets, QCD and WJets HT-binned samples ""
		//Formerly used Cross sections from https://twiki.cern.ch/twiki/bin/view/CMS/B2GPHYS14, bottom of the page
		// this reference is partly broken. the twiki above only gives cross sections up to 600 then merges 600 to infinity into one cross section. 
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "WJetToLNu100To200f", 1347*k_wjet, 1.2, 10142187, {{"PtLow",100},{"PtHigh",200}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "WJetToLNu200To400f", 359.7*k_wjet, 0.20, 5231856, {{"PtLow",200},{"PtHigh",400}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "WJetToLNu400To600f", 48.91*k_wjet, 0.072, 1901705, {{"PtLow",400},{"PtHigh",600}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "WJetToLNu600To800f", 12.05*k_wjet, 0.0073, 3984529, {{"PtLow",600},{"PtHigh",800}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "WJetToLNu800To1200f", 5.501*k_wjet, 0.017, 1574633, {{"PtLow",800},{"PtHigh",1200}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "WJetToLNu1200To2500f", 1.329*k_wjet, 0.0025, 255637, {{"PtLow",1200},{"PtHigh",2500}}, null_float_meta, null_string_meta, true, false, 13., true));
		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "WJetToLNu2500ToInff", 0.03216*k_wjet, 0.000104, 253036, {{"PtLow",2500},{"PtHigh",99999}}, null_float_meta, null_string_meta, true, false, 13., true));

		//These two exist only for the sake of comparing generators. The madgraph should be essentially the same as the above, but lower stats. The amcatnlo is a different generator. 
		// cs from https://twiki.cern.ch/twiki/bin/view/CMS/B2GPHYS14, bottom of the page
		type = 113;
// 		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns.txt", type, "WJetToLNu_madgraph", 61526.7, 2365.5, 72207128, {{"PtLow",0},{"PtHigh",99999}}, null_float_meta, null_string_meta, true, false, 13., true));
		type = 115;
// 		DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_25ns.txt", type, "WJetToLNu_amcatnlo", 61526.7, 2365.5, 16541248, {{"PtLow",0},{"PtHigh",99999}}, null_float_meta, null_string_meta, true, false, 13., true));
	}


	//WW types 120
	//cs and cs_uncert from arXiv:1408.5243, NNLO QCD. Also see https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeVInclusive
	DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/WW_TuneCUETP8M1_13TeV-pythia8_25ns.txt", 121, "WWf", 118.7, 2.5, 993640, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));
	//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/WW_TuneCUETP8M1_13TeV-pythia8_50ns.txt", 122, "WWs", 118.7, 2.5, 989608, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));

	//WZ types 130
	//https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeVInclusive
	//note that on the twiki W+ and W- are listed seperately. 
	DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/WZ_TuneCUETP8M1_13TeV-pythia8_25ns.txt", 131, "WZf", 40.2 + 25.9, 1.8 + 1.1, 978512, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));
	//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/WZ_TuneCUETP8M1_13TeV-pythia8_50ns.txt", 132, "WZs", 40.2 + 25.9, 1.8 + 1.1, 996920, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));

	//ZZ types 140
	//for cs and cs_uncert see https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeVInclusive under Z/a* Z/a*
	DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ZZ_TuneCUETP8M1_13TeV-pythia8_25ns.txt", 141, "ZZf", 31.8, 1.2, 996944, null_int_meta, null_float_meta, null_string_meta, true, false, 13., true));
	//DMCblocks.push_back(new DMCblock("/uscms_data/d3/rsyarif/Spring2016/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/filelists/ljmetout/ZZ_TuneCUETP8M1_13TeV-pythia8_50ns.txt", 142, "ZZs", 31.8, 1.2, 998848, null_int_meta, null_float_meta, null_string_meta, true, true, 13., true));

	//https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns#Triboson
	//WWW types 150
	//WWZ types 160  cs = 0.1651 pb at NLO
	//WZZ types 170  cs = 0.05565 pb at NLO
	//ZZZ types 180  cs = 0.01398 pb at NLO

	//                       /9                          6\
	//                    // |                          | \\
	//                  //  |                          |  \\
	//                //    |                          |    \\
	//              //    __|__                        |      \\
	//            //      |__X__|                    __|__      \\
	//___________//___________________________________|__X__|________\\____________
	//|_____|_____|_____|_____|_____|_____|_____|_____|#####|_____|_____|_____|____
	//___|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_
	//|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|____
	//___|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_
	//|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|____
	//___|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_
	//Finish up processes. 
	//within in a type, assign an index number to each.

	//every DMCblock within a type gets a processID, starting at 0 and counting up. We reset upon encountering a new type.
	int i_processID = 0;
	std::vector<DMCblock*>::iterator it = DMCblocks.begin();
	int thistype = (*it)->type;
	for(;it!=DMCblocks.end();it++){
		int temptype = (*it)->type; //sometimes calling (*it)->type will segfault for no reason
		//placeholder
		if(temptype == thistype){
			(*it)->processID = ++i_processID;
		}
		else{
			i_processID = 0;
			(*it)->processID = i_processID;
			thistype = temptype;//used for cluster
		}
	}
	cout<<"finished setupDMCblocks"<<endl;
	return DMCblocks;
}//end setup

/*	void printDMCblocks(){
		std::vector<DMCblock*> DMCblocks = setupDMCblocks();
		printf("$M_{stop}$ & $M_{higgsino}$ & cross section (fb)\\\\ \n");
		printf("\\hline\n");
		for(int i=0; i<(int)DMCblocks.size();i++){
			printf("%i & %i & %.2E \\\\ \n",DMCblocks[i]->Mstop,DMCblocks[i]->Mhiggsino, DMCblocks[i]->cs_fb());
			printf("\n",);
		}
	}//end printDMCblocks
*/

	std::map<string, int> makemap(std::vector<DMCblock*> DMCblocks){
		//produces a map from the DMCblock name to the index within the vector 
		//this lets you call a block by its name
		std::map<string,int> m;
		for(int i=0; i<(int)(DMCblocks.size());i++){
			string temp = DMCblocks[i]->name;
			m[temp] = i;
		}
		return m;
	} //make map

	DMCblock * setupDMCblock(string name, string filepath){  		//I'm counting on this working properly.
		//returns a pointer to a fully setup DMCblock, ready to use.
		//you should add a check that the file exists.
		/*if(name.compare("Data") ==0 ){
			DMCblock *d = new DMCblock(-1, "Data", 0, 0, -1, filepath, {},{},{}, false); 
			if(filepath.compare("")!=0){ d->rootFilePaths.push_back(filepath); d->nfiles += 1;}
			return d;
		}*/

		std::vector<DMCblock*> vp = setupDMCblocks();
		cout<<"Doing setupDMCblock for "<<name<<endl;

		bool foundit = false;
		std::vector<DMCblock*>::iterator it = vp.begin();
		DMCblock* thisblock = *it;// = vp[pmap[s_name]];//default nonsense value
		while (it != vp.end() ){
			//if((*it)->Mhiggsino == 250 && (*it)->type==30) cout<<"comparing "<<name<<" to "<<(*it)->name.c_str()<<endl;
			if((*it)->name.compare(name) == 0){ // they are the same
				//if((*it)->Mhiggsino == 250 && (*it)->type==30) cout<<"    found it!"<<endl;
				foundit = true;
				thisblock = *it;
				it++;
				cout<<"In setupDMCblock, searching for "<<name<<" and foind it"<<endl;
			}
			else{
				vp.erase(it);	//delete and go to the next one.
				//if((*it)->Mhiggsino == 250 && (*it)->type==30) cout<<"    rejected"<<endl;
			}
		}//end while
		if(!foundit) cout<<"WARNING !! DID NOT FIND MC POINT!! USING DEFAULT POINT"<<endl;
		if(filepath.compare("")!=0){ thisblock->rootFilePaths.push_back(filepath); thisblock->nfiles += 1;}// its not ""
		return thisblock;
	}//end setupDMCblock

#endif
