#ifndef _CONTROLPANNEL_H // if not defined
#define _CONTROLPANNEL_H 

#include <iostream>
#include <vector>
using namespace std; 

namespace controlpannel{

//data
const float Integrated_Luminosity_Data = 2.215;//in inverse femptobarns
/*
string plotsroot= "raw_plots_data_GLL12ABC.root"; 
string logplotsroot= "raw_plots_data_GLL12ABC.log";
string formatedplotsroot= "formatted_plots_dataGLL12.root";
bool useMETFilter_data = true;
*/

//MC
//int type_to_run = 10;
//string which_MC_to_use2 = "FSst_185_mu_150"; //this should become "which_DMCblock_to_use"
const bool makeEventsList = false;
const bool T50ns_F25ns = false;
const bool fix_BR_event_by_event = true; //turn this off when doing the real thing. 

enum EleSelection {cutbased, MVA_nontrigger, MVA_trigger};
EleSelection EleSelectionToUse = MVA_nontrigger;

//Data+MC
//string formatedplotsroot_combined= "formatted_plots_dataMC.root"; //output from format_plots.C

//Limit Setting
//bool remake_Limit_packages = true;

// long int probeevent = 10496;
long int probeevent = 666;

//shift jet energy corrections and all up/down by one sigma. 
int bumpJEC = 0;//is allowed to be +- 1 and 0	//assuems 2% uncertainty.  
int bumpBtagEff = 0;//is allowed to be +- 1 and 0 

	///LISTS FOR INDEXING
const int nEventTopologies = 53; // the number of types of cuts selected, like 1JB...
//const int nEventTopologies = 37; // the number of types of cuts selected, like 1JB...
//const int nEventTopologies = 24; // the number of types of cuts selected, like 1JB...
string s_EventTopology[nEventTopologies] = {
 "NULL","main",//2

 "NULL_eee","main_eee",//2
 "NULL_eem","main_eem",//2
 "NULL_emm","main_emm",//2
 "NULL_mmm","main_mmm",//2

 "ST1100B1J3MtSum50","ST1000B1J3MtSum50","ST900B1J3MtSum50","ST800B1J3MtSum50","ST700B1J3MtSum50","ST600B1J3MtSum50","ST500B1J3MtSum50",//7

 "ST1100J3MtSum50",//1

 "1J","2J","3J","4J",//4

 "HT400","HT500","HT600",//3
 "ST700","ST800","ST900","ST1000","ST1100",//5

 "Mt30","Mt40","Mt50", // 3

 "ST800_2J","ST800_3J","ST800_1BmJ", //3
 "ST800_1BmJ_2J","ST800_1BmJ_3J", //2

 "ST900_2J","ST900_3J","ST900_1BmJ", //3
 "ST900_1BmJ_2J","ST900_1BmJ_3J", //2

 "ST1000_2J","ST1000_3J","ST1000_1BmJ", //3
 "ST1000_1BmJ_2J","ST1000_1BmJ_3J", //2

 "ST1100_2J","ST1100_3J","ST1100_1BmJ", //3
 "ST1100_1BmJ_2J","ST1100_1BmJ_3J", //2
 };


const int nKinemVars_all = 28;
string s_KinemVars_all[nKinemVars_all]={
				"nTightLep","nJ",//"nBl", 
                "nBm", //"BTm", "BTl",
                "LHT", "HT", "ST",
                "LepT", //"EleTT", "MuT",
                "MET", "Mlll", "Mll","minMll", //"MinMlb",
				"lepPt","lepEta","lepDPhi","minLepDPhi", 
				"lepDR","minLepDR",
				"jetPt","jetEta","leadjetDR",
				"lepJetDR",//"leadBjetDR", 
				"MSum", "MtSum",
				"eleMiniIso","muMiniIso",
				"eleMiniIso_top3","muMiniIso_top3",
                "yield", //"yieldsum"};
				//"BLovHT", "BMovHT", "LepTovHT", 
				//"HTovST", "LepTovST", "METovST", "MSumovST", 
				};
				//nJ
				//Ask for JetPtThreshl

//const int nEventTopologies_limit = 5; // the number of types of cuts selected, like 1JB...
//string s_EventTopology_limit[nEventTopologies_limit] = {
	//"NULL","gbar2",
	//"2JewkMjjgbar2lep0notH"};

		//Will be used if either bumpBtagEff != 0 or bumpJEC != 0. 
		//list of kin vars to make limits on. These must be singly-filled per event and otherwise make sense.
//const int nKinemVars_limit = 2;
//string s_KinemVars_limit[nKinemVars_limit] = {
//"MET", "PtGGPtBB"};//, "PtGGPtVjj",


bool IsTopo(string topo);
bool IsKinvar(string kinvar);
//bool IsTopoLim(string topo);
//bool IsKinvarLim(string kinvar);

bool IsTopo(string topo){
                //      true iff topo is in s_EventTopology.
        for (int iTopo = 0; iTopo<nEventTopologies; iTopo++)
                if( topo.compare(s_EventTopology[iTopo]) == 0)
		    return true;
        return false;
} //end IsTopo
bool IsKinvar(string kinvar){
                //      true iff kinvar is in s_KinemVars_all.
        for (int kKinVar = 0; kKinVar<nKinemVars_all; kKinVar++)
                if( kinvar.compare(s_KinemVars_all[kKinVar]) == 0) //I think this is a "contains and starts at 0, not equality"
		    return true;
        return false;
}// end IsKinvar
/*bool IsTopoLim(TString topo){
                //      true iff topo is in s_EventTopology_limit.
        for (int iTopo = 0; iTopo<nEventTopologies_limit; iTopo++)
                if( topo.compare(s_EventTopology_limit[iTopo]) == 0)
		    return true;
        return false;
}*/ //end IsTopoLim
/*bool IsKinvarLim(TString kinvar){
                //      true iff kinvar is in s_KinemVars_limit.
        for (int kKinVar = 0; kKinVar<nKinemVars_limit; kKinVar++)
                if( kinvar.compare(s_KinemVars_limit[kKinVar]) == 0) //I think this is a "contains and starts at 0, not equality"
                                return true;
        return false;
}//end IsKinvarLim
*/
	const float CISVv2L = 0.605;
	const float CISVv2M = 0.890;
	const float CISVv2T = 0.907;

	//Controls for post.C
	const bool showData = true; //Gabriele
	const bool preliminary = true;
	const bool saveImages = true;
    const bool writeRootFile = true;
    const string savewhat = "gCpdfpngroot";//ggifpdfeps
    const float SignalInflationFactor = 1000; //scale up the signal by this much. 
    const bool divideOutBinWidths = 1;
	
	//Controls for including up/downs files in post.C - added by rizki - start
    const bool useBTagSys = true;
    const bool useJECsys = true;
    const bool useJERsys = true;
	//Controls for including up/downs files in post.C - added by rizki - end

	string plotsdirC   = "plots/C/";
	string plotsdirroot ="plots/root/";
	string plotsdirjpg = "plots/jpg/";
	string plotsdirpdf = "plots/pdf/";
	string plotsdirpng = "plots/png/";
	//string plotsdirpng = "/uscms_data/d3/rsyarif/BrownFall2015/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/plots/";
	string plotsdirgif = "plots/gif/";
	string plotsdireps = "plots/eps/";
	string htmldir   = "/uscms_data/d3/rsyarif/BrownFall2015/TprimeANALYSIS_copy/CMSSW_7_4_15/src/LJMet/Com/public_html/"; //not yet made

	const int nmodes = 5;
	static const int nBByields = 6;
	static const int nSysYields = 1+//nominal
					2+//PU corrections
					2+//renorm envelope
					2+//pdf 1 sigmas. 
					2;//Julie Jet SFs 
	static const int nRenorm = 6;
	static const int nPDF = 100;
	static const int nPolySysYields = 1+//nominal
					2+//PU corrections
					nRenorm+//renorm envelope
					nPDF+//pdf 1 sigmas. 
					2;//Julie Jet SFs
	//mode 0 = nominal. 1 = fakerate plus, 2 = fakerate minus, 3 = passrate plus, 4 = passrate minus 5=qg fake plus, 6=qg fake minus.
	//see feModeBehavior in fakerate.h

} //end namespace params
#endif

