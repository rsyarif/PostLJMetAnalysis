#define tpmultlepmaincalc_cxx
#include "interface/tpmultlepmaincalc.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include "TProfile.h"
#include <map>
#include <set>
#include <cmath>
#include "TMath.h"
#include <algorithm>
#include <utility>
//#include "SusyMainAna_MC_arg.h"
//#include "SusyEventPrinter.h"
//#include "../jec/JetMETObjects/interface/JetCorrectorParameters.h"
//#include "../jec/JetMETObjects/interface/FactorizedJetCorrector.h"
//my additions
#include "TAxis.h"
#include <TH3.h>
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TGraphErrors.h"
#include <assert.h>
#include "TF1.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include "TVector3.h"
//#include <algorithm>
#include "TLorentzVector.h"
//user defiend
//#include "utilities.h"
//#include "quicksave.C"
#include "interface/CMSStyle.C"
//#include "SFb.h"
//#include "SFl.h"
//#include "BTagWeight6.h"
#include <time.h>
#include "interface/stringmap.h"
#include "interface/DMCblock.h"
#include "interface/DMCblock_list.h"
#include "interface/controlpannel.h"
#include "interface/KinematicVar.h"
#include "eventRegistry.C"
#include "interface/EleIDCuts.h"
#include "interface/fakerate_3lep.h"
#include "interface/JetScaleFactors.h"
#include "check_dup.C"
//#include "EventTopology.h"

//   In a ROOT session, you can do:
//      root> .L tpmultlepmaincalc.C
//      root> tpmultlepmaincalc* t = new tpmultlepmaincalc("blockname")
//      root> t->Loop();       // Loop on all entries
//	Loops over a DMC block. 
//	
//	Origionally:
//      root> .L tpmultlepmaincalc.C
//      root> tpmultlepmaincalc t
//      root> t.Loop();       // Loop on all entries

using namespace std;

template<typename T> bool EtGreater(const T* p1, const T* p2) {
    return (p1->momentum.Et() > p2->momentum.Et());
}

typedef stringmap<TH1F*> LabelHist;
typedef stringmap<LabelHist> Label2Hist;
typedef stringmap<TH2F*> LabelHist2D;
typedef stringmap<LabelHist2D> Label2Hist2D;

class counters: public stringmap<int>{
    public:
	vector <string> order;
	void addCounter(string Label){
	    set(Label,0);
	    order.push_back(Label);
	}
	int increment(string Label){
	    if(tmap.find(Label) != tmap.end()) return ++tmap[Label];
	    else{
		cerr<<"Warning! in counters.increment received Invalid key string "<<Label<< endl;
		return -1;
	    }
	}
};

struct topoCutDecision{
    topoCutDecision(bool EventIsTightTightTight, bool otherReq):pass(EventIsTightTightTight && otherReq),bkgpass(otherReq){
    }
    bool pass; //main pass bit for tight-tight-tight
    bool bkgpass;//pass bit with ttt requrement removed.  
};
topoCutDecision tcdFALSE(false,false);//all decisions are false


int makeYield(bool is_elelel, bool is_elelmu, bool is_elmumu, bool is_mumumu, bool main);
void setCutBits(stringmap<topoCutDecision*>* AlltopoCut, bool is_triLepT , float met, int nJetAK4 , int nBJetAK4CISVm , float HT , float ST, float MinMlb, float Mlll, float MtSum);
//void setCutBits(namedbool* AlltopoCut, bool is_triLepT , float met, int nJetAK4 , int nBJetAK4CISVm , float HT , float ST, float MinMlb, float Mlll);

TH1F* init_TH1F_special(string label, string var, LabelKinVars &KinVars ); //cant throw  <std::string,int> errorpair
TH1F* init_TH1F_special(string label, KinematicVar* k); //cant throw  <std::string,int> errorpair
TH2F* init_bkg_TH2F_special(string label, KinematicVar* k); //cant throw  <std::string,int> errorpair
TH2F* init_bkg_TH2F_special(string label, string var, LabelKinVars &KinVars ); //cant throw  <std::string,int> errorpair
void MakeTriggerIndicies(std::vector<int> & TriggerIndicies, int NTriggers, string Triggers[], vector<string>  * vsSelTriggers);
std::map<int,int> Make_HLT_map_selIndex_to_stringIndex(int NTriggers, string Triggers[], vector<string>  * vsSelTriggers);
void Fill_HLT_study(TH2F* h, std::map<int,int> indexmap, int nTrig, std::vector<int> TriggerIndicies, vector<int> *viSelTriggers, bool verbose);
bool checkTriggerList(std::vector<int> & TriggerIndicies, int NTriggers, string Triggers[], vector<string>  * vsSelTriggers);
void indexPtSort(vector<int>& indicies, int n, vector<double> pt);
struct mypair{ int index; double pt; };
bool pairCompare(mypair* firstElem, mypair* secondElem);
void FillBkg(TH2F* h, float x, double bkgweights[], double auxWeight);
float MCbrReweight( bool isBWBW, bool isTHBW, bool isTHTH, bool isTZBW, bool isTZTH, bool isTZTZ,
	    float bWbr, float tHbr, float tZbr);

void doLHEweights(DMCblock* block, vector<int> *LHEWeightids_singleLepCalc, vector<double>  *LHEWeights_singleLepCalc, 
	std::vector<double>* renorm, std::vector<double>* pdf  );
struct val_err_pair{float val; float err;};
bool VEpairCompare(val_err_pair* firstElem, val_err_pair* secondElem);
void Convert_nPolySysYields_to_nSysYields(TH2F* s_yield,TH2F* ps_yield);
void FillPSYields(TH2F* ps_yield,float yield,float weight_before_PU,   double puweight_nominal,double puweight_up,double puweight_down, float* jetSFs, std::vector<double>* renorm, std::vector<double>* pdf );

static const double puweight260627_72ub[60] = {1.048445e+02, 1.417593e+02, 8.807366e+01, 3.236995e+01, 1.683957e+01, 2.831305e+00, 1.423759e+00, 1.612828e+00, 2.306693e+00, 2.473619e+00, 2.514170e+00, 2.546666e+00, 2.333108e+00, 1.836848e+00, 1.221869e+00, 6.836922e-01, 3.275329e-01, 1.432766e-01, 6.667120e-02, 3.763312e-02, 2.341225e-02, 1.359301e-02, 6.804618e-03, 2.922054e-03, 1.130104e-03, 4.448707e-04, 2.080687e-04, 1.239100e-04, 8.786009e-05, 6.837745e-05, 5.143024e-05, 3.476586e-05, 1.906542e-05, 9.115409e-06, 3.556074e-06, 1.447242e-06, 5.171527e-07, 1.940254e-07, 6.513423e-08, 2.309190e-08, 7.790329e-09, 2.199365e-09, 6.795396e-10, 1.624286e-10, 4.931596e-11, 1.298753e-11, 7.930341e-12, 2.315454e-12, 1.497868e-11, 2.172998e-12, 9.012326e-14, 1.094585e-14, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00};
static const double puweight260627_69ub[60] = {1.245238e+02, 1.562054e+02, 9.528614e+01, 3.645428e+01, 2.049345e+01, 3.843197e+00, 2.215886e+00, 2.747772e+00, 3.412640e+00, 3.156122e+00, 2.921218e+00, 2.709273e+00, 2.214740e+00, 1.509242e+00, 8.529270e-01, 4.047681e-01, 1.706805e-01, 7.408239e-02, 3.853898e-02, 2.208110e-02, 1.157933e-02, 5.111779e-03, 1.897273e-03, 6.326908e-04, 2.194698e-04, 9.396686e-05, 5.134064e-05, 3.356329e-05, 2.432826e-05, 1.843384e-05, 1.299881e-05, 8.002472e-06, 3.916437e-06, 1.648432e-06, 5.607770e-07, 1.975807e-07, 6.075239e-08, 1.950465e-08, 5.573450e-09, 1.673234e-09, 4.755563e-10, 1.125301e-10, 2.899281e-11, 5.749377e-12, 1.440875e-12, 3.115802e-13, 1.554955e-13, 3.630806e-14, 2.427227e-13, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00};
static const double puweight260627_65ub[60] = {1.458817e+02, 1.724645e+02, 1.043786e+02, 4.182011e+01, 2.579572e+01, 5.495080e+00, 3.731141e+00, 4.618505e+00, 4.765473e+00, 3.872168e+00, 3.259346e+00, 2.705177e+00, 1.908453e+00, 1.092269e+00, 5.137612e-01, 2.085454e-01, 8.454498e-02, 4.109705e-02, 2.206794e-02, 1.053976e-02, 4.084606e-03, 1.298473e-03, 3.698050e-04, 1.135070e-04, 4.460047e-05, 2.240654e-05, 1.319444e-05, 8.644198e-06, 5.969210e-06, 4.142850e-06, 2.600931e-06, 1.398830e-06, 5.905424e-07, 2.124612e-07, 6.132579e-08, 1.821361e-08, 4.691640e-09, 1.254258e-09, 2.966644e-10, 7.328361e-11, 1.703655e-11, 3.277952e-12, 6.826269e-13, 1.087907e-13, 2.182661e-14, 3.753385e-15, 1.408114e-15, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00};

//      __                    
//     / /   ____  ____  ____ 
//    / /   / __ \/ __ \/ __ \
//   / /___/ /_/ / /_/ / /_/ /
//  /_____/\____/\____/ .___/ 
//                   /_/      
//
void tpmultlepmaincalc::Loop(eventRegistry* EventRegistry,eventRegistry* BadEventRegistry)
{
    cout<<"Loop lives"<<endl;
    ofstream firealarm;
    bool onfire = false; //set to true in case of alarming error.
    firealarm.open("tmpfirealarm.txt");
    firealarm << "tpmultlepmaincalc is on FIRE"<<endl;
    firealarm.close();

    const bool makeBkgs = !dmcblock->isMC;//may want to expand this to other bkgs
    const bool isSignal = dmcblock->type == 1 or dmcblock->type == 2;
    ///////////////////////////////////////////////////////
    //control pannel; dashboard
    static const int printlevel=3;//print level printlevel printlevel
    //0 = Stealth
    //1 = Annouce birth, death, marriage, and explosions
    //2 = Christmas and easter only; turn on 1000th event heart monitor, Normal for running
    //3 = Casual:         Tick off major blocks and probe suspicious lines
    //***Begin compartmentalizing the verbosity with print blocks***
    //4 = Currious:	 Tick off minor blocks
    //5 = Probe loops 1 level deep and chosen significant lines
    //6 = Probe loops 2 levels deep
    //7 = Probe loops 3+ levels deep
    //8 = Paranoid:        Probe every significant operation that looks like it could fail
    //9 = FBI Colonoscopy: Probe every operation, even if it's unlikely that it'll fail
    //10= Hyperbarf:       Print a probe after every line
    //11= ALICE: 	       Blast appart its nuclei and examinef(printlevel > 3) std::cout << "Initialize event counters." << std::endl;	
    if(printlevel > 3) std::cout << "Initialize event counters." << std::endl;	
    //vector <string> Counter_order;
    counters Counters;
    Counters.addCounter("no cuts");
    Counters.addCounter("pre HLT");
    Counters.addCounter("post HLT");
    Counters.addCounter("Has 2 leptons");
    Counters.addCounter("Has exactly 2 leptons");
    namedbool* KinVarSwitches = MakeKinVarSwitches(); //out of all the kinvars you've imagined, which are to be used? 

    if(printlevel >= 5) std::cout << "counters started" << std::endl;	

    //namedbool* AlltopoCut = new namedbool();
    stringmap<topoCutDecision*>* AlltopoCut = new stringmap<topoCutDecision*>();
    namedint AlltopoNpass;
    //namedbool* topoCut = new namedbool();
    stringmap<topoCutDecision*>* topoCut = new stringmap<topoCutDecision*>();
    if(printlevel >= 9) std::cout << "made namedbool" << std::endl;	

    for (int iTopo = 0; iTopo<nEventTopologies; iTopo++) {
	//topoCut->set(s_EventTopology[iTopo], false);
	AlltopoNpass.set(s_EventTopology[iTopo], 0);
    }
    if(printlevel >= 9) std::cout << "done setting topoCuts" << std::endl;	

    Label2Hist lh_unsliced;
    Label2Hist2D lb_unsliced;



    /*   Int_t           nSelBtagJets_CommonCalc;
	 Int_t           nAllJets_CommonCalc;
	 Int_t           nSelJets_CommonCalc;
    //   Also see: 
    Int_t           nBJets_CATopoCalc; 
    Int_t           nJets_CATopoCalc;
    */


    string s_forTopo[nEventTopologies];
    for (int iTopo=0; iTopo<nEventTopologies; iTopo++){
	s_forTopo[iTopo]=string(" for ")+s_EventTopology[iTopo];
    }

    typedef stringmap<KinematicVar*>* LabelKinVars;
    LabelKinVars KinVars = setupKinematicVar();

    if(printlevel >= 4) cout<<"initializing hist grid"<<endl;
    //Initialize the grid of histograms
    try{
	for (int iTopo = 0; iTopo<nEventTopologies; iTopo++) {
	    LabelHist tmpMapKinVar; 
	    //cout<<"nKinemVars_all "<<nKinemVars_all<<endl;
	    for (int kKinVar = 0; kKinVar < nKinemVars_all; kKinVar++) {
		//cout<<"kinvars: "<<s_KinemVars_all[kKinVar]<<endl;
		KinematicVar* tmpKinVar = KinVars->get_throwable(s_KinemVars_all[kKinVar],3);
		if(tmpKinVar->useCustomBinning){
		    tmpMapKinVar.set(s_KinemVars_all[kKinVar], new TH1F(
				(char*)(string("h_")+s_KinemVars_all[kKinVar]+s_EventTopology[iTopo]).c_str(),
				(char*)(tmpKinVar->titles+s_forTopo[iTopo]+";"+tmpKinVar->xlabels).c_str(),
				tmpKinVar->nbins,
				tmpKinVar->CustomBinning));
		}
		else{
		    tmpMapKinVar.set(s_KinemVars_all[kKinVar], new TH1F(
				(char*)(string("h_")+s_KinemVars_all[kKinVar]+s_EventTopology[iTopo]).c_str(),
				(char*)(tmpKinVar->titles+s_forTopo[iTopo]+";"+tmpKinVar->xlabels).c_str(),
				tmpKinVar->nbins,
				tmpKinVar->hmin,
				tmpKinVar->hmax));
		}
	    }//end for every kinematic varriable.
	    lh_unsliced.set(s_EventTopology[iTopo], tmpMapKinVar); 
	}//end for every topology
    }//end try
    catch(std::pair <std::string,int> errorpair){
	cerr<<"Error while initalizing  histograms; Invalid kinematic variable key string \""<<errorpair.first<<"\" sought in KinVars"<<endl;
	std::terminate();
    } //end catch failed stringmap gets

    //Initalize bkg curves to the grid of of histograms
    if(makeBkgs){
	if(printlevel >= 4) cout<<"initializing hist bkg grid"<<endl;
	try{
	    for (int iTopo = 0; iTopo<nEventTopologies; iTopo++) {
		LabelHist2D tmpMapKinVar2; 
		//cout<<"nKinemVars_all "<<nKinemVars_all<<endl;
		for (int kKinVar = 0; kKinVar < nKinemVars_all; kKinVar++) {
		    //cout<<"kinvars: "<<s_KinemVars_all[kKinVar]<<endl;
		    KinematicVar* tmpKinVar = KinVars->get_throwable(s_KinemVars_all[kKinVar],3);
		    if(tmpKinVar->useCustomBinning){
			tmpMapKinVar2.set(s_KinemVars_all[kKinVar], new TH2F(
				    (char*)(string("b_")+s_KinemVars_all[kKinVar]+s_EventTopology[iTopo]).c_str(),
				    (char*)(tmpKinVar->titles+s_forTopo[iTopo]+";"+tmpKinVar->xlabels).c_str(),
				    tmpKinVar->nbins,
				    tmpKinVar->CustomBinning,
				    nmodes,0,nmodes));
		    }
		    else{
			tmpMapKinVar2.set(s_KinemVars_all[kKinVar], new TH2F(
				    (char*)(string("b_")+s_KinemVars_all[kKinVar]+s_EventTopology[iTopo]).c_str(),
				    (char*)(tmpKinVar->titles+s_forTopo[iTopo]+";"+tmpKinVar->xlabels).c_str(),
				    tmpKinVar->nbins,
				    tmpKinVar->hmin,
				    tmpKinVar->hmax,
				    nmodes,0,nmodes));
		    }
		}//end for every kinematic varriable.
		lb_unsliced.set(s_EventTopology[iTopo], tmpMapKinVar2); 
	    }//end for every topology
	}//end try
	catch(std::pair <std::string,int> errorpair){
	    cerr<<"Error while initalizing bkg 2D histograms; Invalid kinematic variable key string \""<<errorpair.first<<"\" sought in KinVars"<<endl;
	    std::terminate();
	} //end catch failed stringmap gets
    }//end if data bkgs

    if(printlevel >= 4) cout<<"initializing specials"<<endl;
    ///////////////////Initalize Specials//////////////////////
//Eg.     TH1F* h_MinMlb_OSDL1sanslb;	TH2F* b_MinMlb_OSDL1sanslb;
   
    TH1F* h_yield = new TH1F( "h_yield", "Yields in Various Channels;Channel", 4,0,4);
    TH2F* s_yield = new TH2F( "s_yield", "Yields in Various Channels;Channel", 4,0,4,nSysYields,0,nSysYields); //systematics, what gets saved.
    TH2F* ps_yield= new TH2F("ps_yield","Yields in Various Channels;Channel", 4,0,4,nPolySysYields,0,nPolySysYields); //poly systematics, internal only.
    TH2F* b_yield = new TH2F( "b_yield", "Yields in Various Channels;Channel", 4,0,4,nmodes,0,nmodes);


    TH1F* h_yield_BB[nBByields];
    TH2F* s_yield_BB[nBByields];
    TH2F* ps_yield_BB[nBByields];
        //0:WW, 1:WH, 2: WZ, 3: HH, 4: HZ, 5: ZZ 
    string channel_abbrev[nBByields] = {"WW","WH","WZ","HH","HZ","ZZ"};
    enum yield_BB_indicies{WW=0,WH=1,WZ=2,HH=3,HZ=4,ZZ=5};
    for(int i=0;i<nBByields;i++) //nominals 
	    h_yield_BB[i] = new TH1F( (((string)"h_yield_")+channel_abbrev[i]).c_str(), 
		    (((string)"Yields in Various Channels from ")+channel_abbrev[i]+";Channel").c_str(), 4,0,4);

    for(int i=0;i<nBByields;i++) //nominals 
	    s_yield_BB[i] = new TH2F( (((string)"s_yield_")+channel_abbrev[i]).c_str(), 
		    (((string)"Yields in Various Channels from ")+channel_abbrev[i]+";Channel").c_str(), 4,0,4,nSysYields,0,nSysYields);

    for(int i=0;i<nBByields;i++) //nominals 
	    ps_yield_BB[i] = new TH2F( (((string)"ps_yield_")+channel_abbrev[i]).c_str(), 
		    (((string)"Yields in Various Channels from ")+channel_abbrev[i]+";Channel").c_str(), 4,0,4,nPolySysYields,0,nPolySysYields);

    try{
		//INITALIZE SPECIAL PLOTS HERE
	//	KinematicVar* kST = KinVars->get_throwable("ST",3);
	//	h_ST_OSDL1sansS	= init_TH1F_special("h_ST_OSDL1sansS", kST);
	//	h_MinMlb_OSDL1sanslb= init_TH1F_special( "h_MinMlb_OSDL1sanslb", "MinMlb", KinVars ); 

		//Yield
		const char *yieldbins[4] = {"eee","eem","emm","mmm"};

	for (int i=1;i<=4;i++) h_yield->GetXaxis()->SetBinLabel(i,yieldbins[i-1]);
	for (int i=1;i<=4;i++) s_yield->GetXaxis()->SetBinLabel(i,yieldbins[i-1]);
	for (int i=1;i<=4;i++)ps_yield->GetXaxis()->SetBinLabel(i,yieldbins[i-1]);
	if(isSignal){    
	    for (int i=1;i<=4;i++){     for(int j=0;j<nBByields;j++){     h_yield_BB[j]->GetXaxis()->SetBinLabel(i,yieldbins[i-1]); }}
	    for (int i=1;i<=4;i++){     for(int j=0;j<nBByields;j++){     s_yield_BB[j]->GetXaxis()->SetBinLabel(i,yieldbins[i-1]); }}
	    for (int i=1;i<=4;i++){     for(int j=0;j<nBByields;j++){     ps_yield_BB[j]->GetXaxis()->SetBinLabel(i,yieldbins[i-1]); }}
	} //set bin labels on the BB yields
	//INITALIZE SPECIAL-PLOT BACKGROUNDS HERE
	// 	    b_ST_OSDL1sansS	= init_bkg_TH2F_special("b_ST_OSDL1sansS", kST);
	// 	    b_MinMlb_OSDL1sanslb= init_bkg_TH2F_special( "b_MinMlb_OSDL1sanslb", "MinMlb", KinVars ); 

		if(makeBkgs){
			//Yield
			for (int i=1;i<=4;i++) b_yield->GetXaxis()->SetBinLabel(i,yieldbins[i-1]);
	  
	}

    }//end try
    catch(std::pair <std::string,int> errorpair){
	cerr<<"Error while initalizing special histograms; Invalid kinematic variable key string \""<<errorpair.first<<"\" sought in KinVars"<<endl;
	std::terminate();
    } //end catch failed stringmap gets

    //sc manually define a heap of diagnostic plots of most variables

    //define an array of trigger names.
    //Ele-mu triggers live in both lists; it doesn't matter which list you put them in. 
    //but be careful to only put double electron triggers in the electron list and muon triggers in the muon list else weird failures. 
    const int NEleTriggers = 3;
    string EleTriggers[NEleTriggers ] = {
	"HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v",
	"HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v",
	"HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v"
	};

    const int NMuTriggers = 3;
    string MuTriggers[NMuTriggers ] = {
	"HLT_TripleMu_12_10_5_v",
	"HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v",
	"HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v"
	};



    //Initialize the HLT study histograms and set their bin labels. 
    TH2F* HLT_coincidience_ele_main = new TH2F("HLT_coincidience_ele_main","HLT_coincidience_ele_main",NEleTriggers+1,0,NEleTriggers+1,NEleTriggers,0,NEleTriggers);
    TH2F* HLT_coincidience_mu_main = new TH2F("HLT_coincidience_mu_main","HLT_coincidience_mu_main",NMuTriggers+1,0,NMuTriggers+1,NMuTriggers,0,NMuTriggers);
    TH2F* HLT_coincidience_ele = new TH2F("HLT_coincidience_ele","HLT_coincidience_ele",NEleTriggers+1,0,NEleTriggers+1,NEleTriggers,0,NEleTriggers);
    TH2F* HLT_coincidience_mu = new TH2F("HLT_coincidience_mu","HLT_coincidience_mu",NMuTriggers+1,0,NMuTriggers+1,NMuTriggers,0,NMuTriggers);
    for (int i=0;i<NEleTriggers;i++){
	    HLT_coincidience_ele_main->GetXaxis()->SetBinLabel(i+1,EleTriggers[i].c_str());
	    HLT_coincidience_ele_main->GetYaxis()->SetBinLabel(i+1,EleTriggers[i].c_str());
	    HLT_coincidience_ele->GetXaxis()->SetBinLabel(i+1,EleTriggers[i].c_str());
	    HLT_coincidience_ele->GetYaxis()->SetBinLabel(i+1,EleTriggers[i].c_str());
    }
    HLT_coincidience_ele_main->GetXaxis()->SetBinLabel(NEleTriggers+1,"uniquely");
    HLT_coincidience_ele->GetXaxis()->SetBinLabel(NEleTriggers+1,"uniquely");
    for (int i=0;i<NMuTriggers;i++){
	    HLT_coincidience_mu_main->GetXaxis()->SetBinLabel(i+1,MuTriggers[i].c_str());
	    HLT_coincidience_mu_main->GetYaxis()->SetBinLabel(i+1,MuTriggers[i].c_str());
	    HLT_coincidience_mu->GetXaxis()->SetBinLabel(i+1,MuTriggers[i].c_str());
	    HLT_coincidience_mu->GetYaxis()->SetBinLabel(i+1,MuTriggers[i].c_str());
    }
    HLT_coincidience_mu_main->GetXaxis()->SetBinLabel(NMuTriggers+1,"uniquely");
    HLT_coincidience_mu->GetXaxis()->SetBinLabel(NMuTriggers+1,"uniquely");

	int Neee[4]={0};
	int Neem[6]={0};
	int Nemm[6]={0};
	int Nmmm[4]={0};

	int nPassTrilepCut = 0; 
	int nDuplicates = 0;

    //     __  ______   _____  __  __   ____  ____  ___ 
    //    /  |/  / _ | /  _/ |/ / / /  / __ \/ __ \/ _ \
    //   / /|_/ / __ |_/ //    / / /__/ /_/ / /_/ / ___/
    //  /_/  /_/_/ |_/___/_/|_/ /____/\____/\____/_/    
    //                                                  
    if(printlevel >= 5) std::cout << "Approach Main Loop" << std::endl;	
    //MAIN EVENT LOOP
    if (fChain == 0) return;
    bool first_event = true;
    vector<int> MuTriggerIndicies;
    vector<int> EleTriggerIndicies;
    std::map<int,int> HLT_map_ele;
    std::map<int,int> HLT_map_mu;

    if(printlevel >= 6) std::cout << "try GetEntriesFast" << std::endl;	
    Long64_t nentries = fChain->GetEntriesFast();//this segfaults. 
    if(printlevel >= 6) std::cout << "did it" << std::endl;	
    //for (Long64_t jentry=0; jentry<100;jentry++) {
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
	if( jentry%1000 == 0 && printlevel >=3 ) printf("%i out of %i events processing\n",int(jentry), int(nentries));

	if(printlevel >= 6) std::cout << "Attempt LoadTree" << std::endl;	
	Long64_t ientry = LoadTree(jentry);
	if(printlevel >= 6) std::cout << "fin LoadTree, attempt GetEntry" << std::endl;	
	if (ientry < 0) break;
	if(GetEntry(jentry) == 0) break;  
	//fChain->GetEntry(jentry);   
	if(printlevel >= 6) std::cout << "fin attempt GetEntry" << std::endl;	
	// if (Cut(ientry) < 0) continue;
	//lets just explore the object size for a bit: 

	/*	printf("muons: nT %i ",nTightMuons_CommonCalc);
		printf(" nL %i ", nLooseMuons_CommonCalc);
		printf(" nVect %i \n",(int)muEnergy_singleLepCalc->size());
		printf("ele: nT %i ",nSelElectrons_CommonCalc);
		printf(" nVect %i \n", (int)elEnergy_singleLepCalc->size());*/

	Counters.increment("no cuts");

	Counters.increment("pre HLT");

	if(first_event){ //search through the string of trigger indicies 
	    if(dmcblock->isMC){
		MakeTriggerIndicies(EleTriggerIndicies, NEleTriggers, EleTriggers, vsSelMCTriggersEl_singleLepCalc);
		MakeTriggerIndicies(MuTriggerIndicies, NMuTriggers, MuTriggers, vsSelMCTriggersMu_singleLepCalc);

		//cout<<"Running the map maker MC"<<endl;
		HLT_map_ele = Make_HLT_map_selIndex_to_stringIndex(NEleTriggers, EleTriggers, vsSelMCTriggersEl_singleLepCalc);
		HLT_map_mu = Make_HLT_map_selIndex_to_stringIndex(NMuTriggers, MuTriggers, vsSelMCTriggersMu_singleLepCalc);
	    }
	    else{
		MakeTriggerIndicies(EleTriggerIndicies, NEleTriggers, EleTriggers, vsSelTriggersEl_singleLepCalc);
		MakeTriggerIndicies(MuTriggerIndicies, NMuTriggers, MuTriggers, vsSelTriggersMu_singleLepCalc);

		//cout<<"Running the map maker"<<endl;
		HLT_map_ele = Make_HLT_map_selIndex_to_stringIndex(NEleTriggers, EleTriggers, vsSelTriggersEl_singleLepCalc);
		HLT_map_mu =  Make_HLT_map_selIndex_to_stringIndex(NMuTriggers,  MuTriggers,  vsSelTriggersMu_singleLepCalc);
	    }
	} //end compile trigger indicies

	//occasionally check that the trigger location really is consistent. 
	if( jentry%1000 == 0){ 
	    //if( jentry%1000 == 0 && !first_event ){ 

	    //look at the trigger list
	    /*if(printlevel >=3){//normally 5
	      cout<<"Reaching for electron triggers:"<<endl;
	      if(dmcblock->isMC){
	      for(std::vector<int>::iterator i = EleTriggerIndicies.begin(); i != EleTriggerIndicies.end(); i++)
	      cout<< (*vsSelMCTriggersEl_singleLepCalc)[*i] <<endl; //conclude that we didn't find any ele triggers
	      }
	      else{
	      for(std::vector<int>::iterator i = EleTriggerIndicies.begin(); i != EleTriggerIndicies.end(); i++){
	      cout<< (*vsSelTriggersEl_singleLepCalc)[*i]<<endl;
	      }
	      }
	      cout<<"Reaching for muon triggers:"<<endl;
	      if(dmcblock->isMC){
	      for(std::vector<int>::iterator i = MuTriggerIndicies.begin(); i != MuTriggerIndicies.end(); i++)
	      cout<< (*vsSelMCTriggersMu_singleLepCalc)[*i] <<endl;
	      }
	      else{
	      for(std::vector<int>::iterator i = MuTriggerIndicies.begin(); i != MuTriggerIndicies.end(); i++)
	      cout<< (*vsSelTriggersMu_singleLepCalc)[*i]<<endl;
	      }
	      }//end print if curious
	      */

	    bool trigs_match = true;
	    if(dmcblock->isMC){
		trigs_match &= checkTriggerList(EleTriggerIndicies, NEleTriggers, EleTriggers, vsSelMCTriggersEl_singleLepCalc);
		trigs_match &= checkTriggerList(MuTriggerIndicies, NMuTriggers, MuTriggers, vsSelMCTriggersMu_singleLepCalc);
	    }
	    else{
		trigs_match &= checkTriggerList(EleTriggerIndicies, NEleTriggers, EleTriggers, vsSelTriggersEl_singleLepCalc);
		trigs_match &= checkTriggerList(MuTriggerIndicies, NMuTriggers, MuTriggers, vsSelTriggersMu_singleLepCalc);
	    }
	    if(!trigs_match){
		cout<<"ERROR! trigger list no longer matches what it started as. Your trigger selection is probably broken!"<<endl;
		std::terminate();
	    }

	} //end occasionally
	first_event = false;

	bool passHLT = false;
	if(dmcblock->isMC){
	    for(std::vector<int>::iterator i = EleTriggerIndicies.begin(); i != EleTriggerIndicies.end() && !passHLT; i++)
		passHLT |= (*viSelMCTriggersEl_singleLepCalc)[*i];
	    for(std::vector<int>::iterator i = MuTriggerIndicies.begin(); i != MuTriggerIndicies.end() && !passHLT; i++)
		passHLT |= (*viSelMCTriggersMu_singleLepCalc)[*i];
	}
	else{
	    for(std::vector<int>::iterator i = EleTriggerIndicies.begin(); i != EleTriggerIndicies.end() && !passHLT; i++)
		passHLT |= (*viSelTriggersEl_singleLepCalc)[*i];
	    for(std::vector<int>::iterator i = MuTriggerIndicies.begin(); i != MuTriggerIndicies.end() && !passHLT; i++)
		passHLT |= (*viSelTriggersMu_singleLepCalc)[*i];
	}


	if(!passHLT) continue;

	Counters.increment("post HLT");

	//cout<< run_CommonCalc <<"  "<< lumi_CommonCalc<<"  "<< event_CommonCalc<<endl;//xxx
	//if(isIn1LepDataset( run_CommonCalc , lumi_CommonCalc, event_CommonCalc))
	//	cout<<"Single Lep Dataset Event Found: "<< run_CommonCalc <<"  "<< lumi_CommonCalc<<"  "<< event_CommonCalc<<endl;//xxx
		
	if(printlevel >= 6) std::cout << "incremented some coutners" << std::endl;	
	//make vectors of objects like electrons, muons, jets, and b-jets

	/////////////////////////////////////////////////////////////////
	//////////////////////// FIND THE PRIMARY VERTEX ////////////////
	/////////////////////////////////////////////////////////////////
	//This is already done by LJmet

	/////////////////////////////////////////////////////////////////
	//////////////////////// FIND MUONS  ////////////////////////////
	/////////////////////////////////////////////////////////////////
	//    __  __                       
	//   |  \/  |_   _  ___  _ __  ___ 
	//   | |\/| | | | |/ _ \| '_ \/ __|
	//   | |  | | |_| | (_) | | | \__ \
	//   |_|  |_|\__,_|\___/|_| |_|___/
	//                                 
	//xxmu
	if(printlevel >= 5) cout<<"Begind muons"<<endl;
	float MuT = 0;
	float lep_Mini_Iso_SF = 1.;
	float lep_MVA_ID_SF = 1.;
	TLorentzVector VLep(0,0,0,0);
	/*if(nLooseMuons_CommonCalc != (int)muEnergy_singleLepCalc->size() ){
	  if(nTightMuons_CommonCalc != (int)muEnergy_singleLepCalc->size() )
	  cout<<"neither tight nor nLooseMuons_CommonCalc matches muon vector size "<<endl;//soemtimes
	  else cout<<"muon vector size matches tight"<<endl; //this happens a lot
	  }*/

	vector<int> selMuonIndicies;
	int nSelMuons = 0;
	vector<int> TightMuonIndicies;
	int nTightMuons = 0;
	vector<int> LooseMuonIndicies;
	int nLooseMuons = 0;
	//vector<int> LooseNotTightMuonIndicies;
	//int nLooseNotTightMuons = 0;
	//for(int imu = 0; imu < nLooseMuons_CommonCalc; ++imu)
	for(int imu = 0; imu < (int)muEnergy_singleLepCalc->size(); ++imu){
	    if((*muPt_singleLepCalc)[imu] < 20.) continue;

	    if((*muIsLoose_singleLepCalc)[imu] and (*muMiniIso_singleLepCalc)[imu] < 0.4){
		nLooseMuons++;
		LooseMuonIndicies.push_back(imu);
		if((*muIsTight_singleLepCalc)[imu] and (*muMiniIso_singleLepCalc)[imu] < 0.2){
		
		    nTightMuons++;
		    TightMuonIndicies.push_back(imu);

		    TLorentzVector Vmu;
		    Vmu.SetPtEtaPhiE ( (*muPt_singleLepCalc)[imu], (*muEta_singleLepCalc)[imu], (*muPhi_singleLepCalc)[imu], (*muEnergy_singleLepCalc)[imu]); 
		    VLep = VLep + Vmu;
		}//end mu is tight
		//else{
		    //nLooseNotTightMuons++;
		    //LooseNotTightMuonIndicies.push_back(imu); //xxx why is this commented out??? Should be using this for bkgs. 
		//}
	    }//end mu is loose

	}//end muon for loop
	selMuonIndicies = makeBkgs?LooseMuonIndicies:TightMuonIndicies;
	nSelMuons = makeBkgs?nLooseMuons:nTightMuons;
	indexPtSort(selMuonIndicies,nSelMuons, (*muPt_singleLepCalc));

	for(int imu = 0; imu<nSelMuons; ++imu) MuT+= (*muPt_singleLepCalc)[selMuonIndicies[imu]];




	/////////////////////////////////////////////////////////////////
	//////////////////////// FIND pfElectrons  //////////////////////
	/////////////////////////////////////////////////////////////////
	//    _____ _           _                       
	//   | ____| | ___  ___| |_ _ __ ___  _ __  ___ 
	//   |  _| | |/ _ \/ __| __| '__/ _ \| '_ \/ __|
	//   | |___| |  __/ (__| |_| | | (_) | | | \__ \
	//   |_____|_|\___|\___|\__|_|  \___/|_| |_|___/
	//                                              
	//xxele
	//if(nSelElectrons_CommonCalc != (int)elEnergy_singleLepCalc->size() )
	//cout<<"nSelElectrons_CommonCalc does not match the size of the el vectors"<<endl;

	if(printlevel >= 5) cout<<"Begind electrons"<<endl;
	vector<int> selEleIndicies;
	int nSelEle = 0;
	vector<int> LooseEleIndicies;
	int nLooseEle = 0;
	vector<int> TightEleIndicies;
	int nTightEle = 0;
	
	//NEEDS TO BE CLEANED UP? - start
	vector<bool> isEleTight; //added by rizki
	vector<bool> isEleLoose;  //added rizki
	for(int iele = 0; iele<(int)elEnergy_singleLepCalc->size(); ++iele){ //added by rizki
		isEleTight.push_back(false); //added by rizki
		isEleLoose.push_back(false); //added by rizki			
	}; //added by rizki
	//NEEDS TO BE CLEANED UP? - end
	
	//vector<int> LooseNotTightEleIndicies;
	//int nLooseNotTightEle = 0;
	int nVetoEle= 0;
	float EleT = 0;
	if(printlevel >= 6) cout<<"Begind electrons loop"<<endl;
	for(int iele = 0; iele<(int)elEnergy_singleLepCalc->size(); ++iele){
	    if(printlevel >= 6) cout<<"Start ele loop for ele "<<iele<<endl;

	    if((*elPt_singleLepCalc)[iele] < 20.) continue; 
	    if(printlevel >= 7) cout<<"ele survived pt cut"<<endl;

	    //dR 0.3 cut between electrons and muons with preference to muons 
	    bool eleFailsMuDRcut = false;
	    TLorentzVector Vele, Vmu;
	    Vele.SetPtEtaPhiE ((*elPt_singleLepCalc)[iele],(*elEta_singleLepCalc)[iele], (*elPhi_singleLepCalc)[iele], (*elEnergy_singleLepCalc)[iele]);
	    if(printlevel >= 7) cout<<"approach muon dR cutwork"<<endl;
	    for(int imu = 0; imu<nSelMuons && !eleFailsMuDRcut; ++imu){
		Vmu.SetPtEtaPhiE ( (*muPt_singleLepCalc)[selMuonIndicies[imu]], (*muEta_singleLepCalc)[selMuonIndicies[imu]], (*muPhi_singleLepCalc)[selMuonIndicies[imu]], (*muEnergy_singleLepCalc)[selMuonIndicies[imu]]); 
		eleFailsMuDRcut |= isSameObject(Vele, Vmu, 0.1);
	    } //end dR cut. 
	    if(eleFailsMuDRcut) continue;
	    if(printlevel >= 7) cout<<"survived muon dR cut"<<endl;

	    //int eleIdLevel = T50ns_F25ns?(*elIDLevel50ns_singleLepCalc)[iele]:(*elIDLevel25ns_singleLepCalc)[iele]; //eleIdLevel is generated by ele_ID_level_2015 in EleIDCuts.h
	    int eleIdLevel = 0;
	    switch(EleSelectionToUse){
		case cutbased:
		    eleIdLevel = ele_ID_level_2015(
			    T50ns_F25ns,
			    (*elEta_singleLepCalc)[iele],
			    (*elSihih_singleLepCalc)[iele],
			    (*elDeta_singleLepCalc)[iele],
			    (*elDphi_singleLepCalc)[iele],
			    (*elHoE_singleLepCalc)[iele],
			    (*elRelIso_singleLepCalc)[iele], //I'm guessing this is reliso with effective area. need to check. 
			    (*elOoemoop_singleLepCalc)[iele],
			    (*elD0_singleLepCalc)[iele],
			    (*elDZ_singleLepCalc)[iele],
			    (*elMHits_singleLepCalc)[iele],
			    (*elVtxFitConv_singleLepCalc)[iele]);
		    break;
		case MVA_nontrigger:
		    eleIdLevel = ele_ID_level_2015_MVA_nontrig( 
			    (*elPt_singleLepCalc)[iele],
			    (*elEta_singleLepCalc)[iele],
			    (*elMVAValue_singleLepCalc)[iele],
			    (*elMiniIso_singleLepCalc)[iele]);
		    break;
		case MVA_trigger:
		    cout<<"Error! Electron MVA selection is not yet possible"<<endl;
		    std::terminate();
		    /*eleIdLevel = ele_ID_level_2015_MVA_trig(
		      (*elMVAValue_singleLepCalc)[iele],
		      T50ns_F25ns,
		      (*elPt_singleLepCalc)[iele],
		      (*elEta_singleLepCalc)[iele],
		      (*elSihih_singleLepCalc)[iele],
		      (*elDeta_singleLepCalc)[iele],
		      (*elDphi_singleLepCalc)[iele], 
		      (*elHoE_singleLepCalc)[iele],
		      float EcalRelIso, //yet to be included in ntuple
		      float HcalRelIso,//yet to be included in ntuple
		      float Track03RelIso); //yet to be included in ntuple
		      break; */
	    }//end switch

	    //elID does not exist in data -> segfault.
	    if(printlevel >= 8) cout<<"got eleIDLevel: "<<eleIdLevel<<endl;
	    //ele ID level single lept calc. 

	    if(eleIdLevel >= 1) { //if veto or tighter
			nVetoEle++;
			if(eleIdLevel >= 2){ // if loose
				LooseEleIndicies.push_back(iele);
				++nLooseEle;
				isEleLoose.at(iele) = true; //added by rizki
				//EleT += (*elPt_singleLepCalc)[iele];//with the tt cut, same as if you had asked for it with tight. 
				if(eleIdLevel >= 4){ //if tight
					TightEleIndicies.push_back(iele);
					nTightEle++;
					isEleTight.at(iele) = true; //added by rizki
					if(printlevel >= 9) cout<<"try to get elPt"<<endl;
					//EleT += (*elPt_singleLepCalc)[iele];
					VLep = VLep + Vele;
					if(printlevel >= 9) cout<<"gotit"<<endl;
				}
				//LooseNotTightEleIndicies.push_back(iele);
				//++nLooseNotTightEle;
			}//end if loose ele;
			else {
				if(printlevel >= 8) cout<<"running continue"<<endl;
				continue;
			}
		}//end if veto electron
	    if(printlevel >= 6) cout<<"at end of ele loop"<<iele<<endl;

	}//end electron loop
	selEleIndicies = makeBkgs?LooseEleIndicies:TightEleIndicies;
	nSelEle = makeBkgs?nLooseEle:nTightEle;
	indexPtSort(selEleIndicies,nSelEle,  (*elPt_singleLepCalc));

	for(int iele = 0; iele<nSelEle; ++iele) EleT+= (*elPt_singleLepCalc)[selEleIndicies[iele]];

	///////////////////////////////////////////////////////////////////
	//////////////////////// Trilepton Cut /////////////////////////////
	///////////////////////////////////////////////////////////////////

	if(printlevel >= 5) cout<<"Make Trilepton Cut"<<endl;
	//then make a Trielectron cut.

    if(!makeBkgs && (nTightMuons + nTightEle < 3) ) continue;
    else if(makeBkgs && ( nLooseMuons + nLooseEle < 3)  ) continue;

	Counters.increment("Has exactly 2 leptons");

	if(!makeBkgs && !(nTightMuons + nTightEle >= 3 )) cerr<<"Error! somehow the trilepton requirement is failing!"<<endl;
	if(makeBkgs && !(nLooseMuons + nLooseEle >= 3 )) cerr<<"Error! somehow the trilepton requirement is failing!"<<endl;

	assert(nLooseMuons + nLooseEle >= 3); //for background 
	//At this point, we may be running backgrounds so we cannot assert three tight leptons.

	float LepT = EleT + MuT;//LepT is total Transverse energy of all leptons found. 

	//Combine electons+Muons=leptons then sort in pt and Tight/Loose - start

	vector<double> lepPt,lepPhi,lepEta, lepEnergy;
	vector<int> selLepIndicies;
	vector<int> selLepTightIndicies;
	vector<int> selLepLooseIndicies;
	vector<int> selLepCharge;
	vector<bool> is_lepMu;
	vector<bool> is_lepTight;
	vector<bool> is_lepLoose;
	int nSelLep = 0;

	//collect Tight leptons
	for(int iele = 0; iele<nSelEle; ++iele){
		if(isEleTight[selEleIndicies[iele]]){

			lepPt.push_back((*elPt_singleLepCalc)[selEleIndicies[iele]]);		
			lepPhi.push_back((*elPhi_singleLepCalc)[selEleIndicies[iele]]);		
			lepEta.push_back((*elEta_singleLepCalc)[selEleIndicies[iele]]);		
			lepEnergy.push_back((*elEnergy_singleLepCalc)[selEleIndicies[iele]]);		
			is_lepMu.push_back(0);		

			selLepCharge.push_back((*elCharge_singleLepCalc)[selEleIndicies[iele]]);

			is_lepTight.push_back(isEleTight[selEleIndicies[iele]]);		
			is_lepLoose.push_back(isEleLoose[selEleIndicies[iele]]);		

			selLepTightIndicies.push_back(nSelLep);

			nSelLep++;
		}
	}
	for(int imu = 0; imu<nSelMuons; ++imu){
		if((*muIsTight_singleLepCalc)[selMuonIndicies[imu]]){		

			lepPt.push_back((*muPt_singleLepCalc)[selMuonIndicies[imu]]);		
			lepPhi.push_back((*muPhi_singleLepCalc)[selMuonIndicies[imu]]);		
			lepEta.push_back((*muEta_singleLepCalc)[selMuonIndicies[imu]]);		
			lepEnergy.push_back((*muEnergy_singleLepCalc)[selMuonIndicies[imu]]);		
			is_lepMu.push_back(1);		

			selLepCharge.push_back((*muCharge_singleLepCalc)[selMuonIndicies[imu]]);

			is_lepTight.push_back((*muIsTight_singleLepCalc)[selMuonIndicies[imu]]);	
			is_lepLoose.push_back((*muIsLoose_singleLepCalc)[selMuonIndicies[imu]]);	

			selLepTightIndicies.push_back(nSelLep);

			nSelLep++;
		}
	}
	//collect Tight leptons - end

	indexPtSort(selLepTightIndicies, selLepTightIndicies.size(), lepPt);	

	//collect Loose (BUT NOT TIGHT) leptons
	for(int iele = 0; iele<nSelEle; ++iele){
		if(isEleLoose[selEleIndicies[iele]] && !isEleTight[selEleIndicies[iele]]){

			lepPt.push_back((*elPt_singleLepCalc)[selEleIndicies[iele]]);		
			lepPhi.push_back((*elPhi_singleLepCalc)[selEleIndicies[iele]]);		
			lepEta.push_back((*elEta_singleLepCalc)[selEleIndicies[iele]]);		
			lepEnergy.push_back((*elEnergy_singleLepCalc)[selEleIndicies[iele]]);		
			is_lepMu.push_back(0);		

			selLepCharge.push_back((*elCharge_singleLepCalc)[selEleIndicies[iele]]);

			is_lepTight.push_back(isEleTight[selEleIndicies[iele]]);		
			is_lepLoose.push_back(isEleLoose[selEleIndicies[iele]]);		

			selLepLooseIndicies.push_back(nSelLep);

			nSelLep++;
		}
	}
	for(int imu = 0; imu<nSelMuons; ++imu){
		if((*muIsLoose_singleLepCalc)[selMuonIndicies[imu]] && !(*muIsTight_singleLepCalc)[selMuonIndicies[imu]]){		

			lepPt.push_back((*muPt_singleLepCalc)[selMuonIndicies[imu]]);		
			lepPhi.push_back((*muPhi_singleLepCalc)[selMuonIndicies[imu]]);		
			lepEta.push_back((*muEta_singleLepCalc)[selMuonIndicies[imu]]);		
			lepEnergy.push_back((*muEnergy_singleLepCalc)[selMuonIndicies[imu]]);		
			is_lepMu.push_back(1);		

			selLepCharge.push_back((*muCharge_singleLepCalc)[selMuonIndicies[imu]]);

			is_lepTight.push_back((*muIsTight_singleLepCalc)[selMuonIndicies[imu]]);	
			is_lepLoose.push_back((*muIsLoose_singleLepCalc)[selMuonIndicies[imu]]);	

			selLepLooseIndicies.push_back(nSelLep);

			nSelLep++;
		}
	}		
	//collect Loose (BUT NOT TIGHT) leptons - end

	indexPtSort(selLepLooseIndicies, selLepLooseIndicies.size(), lepPt);	

	//append tight loose indices in to lepton indices
	selLepIndicies.insert(selLepIndicies.end(), selLepTightIndicies.begin(), selLepTightIndicies.end());
	selLepIndicies.insert(selLepIndicies.end(), selLepLooseIndicies.begin(), selLepLooseIndicies.end());
	
	if(printlevel >= 5){
		cout << " After sort ==== " << endl;
		cout << "++++ event = " << jentry << endl;
		for(int ilep = 0; ilep<nSelLep; ++ilep){
			cout << " lep: index =" << selLepIndicies[ilep] << ", pt =" << lepPt[selLepIndicies[ilep]] << ", ele(0)|mu(1) = " << is_lepMu[selLepIndicies[ilep]] << ", is_lepTight = " << is_lepTight[selLepIndicies[ilep]] << endl;
			cout << " nSelLep = " << nSelLep << ", nSelEle = " << nSelEle << ", nSelMuons = " << nSelMuons << ", nTightEle = " << nTightEle << ", nTightMuons = " << nTightMuons << endl;
		}	
	}

	//Combine electons+Muons=leptons then sort in pt and Tight/Loose - end


	//Loop on just top 3 on sorted leptons list
	
	int nSelEle_top3 = 0;
	int nSelMuons_top3 = 0;
	int nTightEle_top3 = 0;
	int nTightMuons_top3 = 0;

	vector<TLorentzVector> Lep_lv;
	TLorentzVector Lep1, Lep2, Lep3;
	Lep_lv.push_back(Lep1);
	Lep_lv.push_back(Lep2);
	Lep_lv.push_back(Lep3);

	for(int ilep = 0; ilep<3; ++ilep){ 
		
		if(!is_lepMu[selLepIndicies[ilep]]){

			nSelEle_top3++;
			if(is_lepTight[selLepIndicies[ilep]]) nTightEle_top3++;
		}
		else{
			nSelMuons_top3++;
			if(is_lepTight[selLepIndicies[ilep]]) nTightMuons_top3++;
		}
		
		//Set Leptons Lorentz vector for later calculations
		Lep_lv[ilep].SetPtEtaPhiE(lepPt[selLepIndicies[ilep]],lepPhi[selLepIndicies[ilep]],lepEta[selLepIndicies[ilep]],lepEnergy[selLepIndicies[ilep]]);
	}

	if(printlevel >= 5) cout << " nSelEle_top3 = " << nSelEle_top3 << ", nSelMuons_top3 = "<< nSelMuons_top3 << ", nTightEle_top3 = " << nTightEle_top3 << ", nTightMuons_top3 = " << nTightMuons_top3 << endl;

	bool is_triLepT = nTightMuons_top3 + nTightEle_top3 >= 3;//is it tight-tight-tight?

	//classification - start
	bool is_elelel = (nSelEle_top3 == 3 );
	bool is_elelmu = (nSelEle_top3 == 2 ) && (nSelMuons_top3 == 1);
	bool is_elmumu = (nSelEle_top3 == 1 ) && (nSelMuons_top3 == 2);
	bool is_mumumu = (nSelMuons_top3 == 3);
	//classification - end
		
	Lep1 = Lep_lv[0];
	Lep2 = Lep_lv[1];
	Lep3 = Lep_lv[2];
	
	float Mlll = (Lep1+Lep2+Lep3).M();

	float Mll12 = (Lep1+Lep2).M();
	float Mll23 = (Lep2+Lep3).M();
	float Mll13 = (Lep1+Lep3).M();

	float lepDPhi12 = dPhi(Lep1,Lep2);
	float lepDPhi23 = dPhi(Lep2,Lep3);
	float lepDPhi13 = dPhi(Lep1,Lep3);

	float 	lepDR12 = dR(Lep1,Lep2);
	float 	lepDR23 = dR(Lep2,Lep3);
	float 	lepDR13 = dR(Lep1,Lep3);


	//cut out DY MC overlap
	/*	if(dmcblock->type == 71 && //if on DY
		((dmcblock->processID == 1 && Mlll > 100) || //if DYJetsToLL50toINFf and M > 100
		(dmcblock->processID == 2 && Mlll < 100))  ) //or if DYJetsToLL100to200f and M<100
		continue;*/

	/*if(isSpecial( run_CommonCalc , lumi_CommonCalc, event_CommonCalc) ){
		cout<<"Special Event Found after dilepton cut: "<< run_CommonCalc <<"  "<< lumi_CommonCalc<<"  "<< event_CommonCalc<<endl;//xxx
		if(is_elel) cout<<"double electron event"<<endl;
		if(is_elmu) cout<<"electron muon event"<<endl;
		if(is_mumu) cout<<"double muon event"<<endl;
		cout<<"Lep 1 pt: "<<Lep1.Pt()<<" Lep 2 pt: "<<Lep2.Pt()<<endl;
	}*/
	
	nPassTrilepCut++;
	if(!dmcblock->isMC){
	    if(   RegisterEvent(run_CommonCalc , lumi_CommonCalc, event_CommonCalc, EventRegistry)  ){
		//If this passes, this event is a duplicate. 
		//cout<<"Duplicate Event Found after dilepton cut: "<< run_CommonCalc <<"  "<< lumi_CommonCalc<<"  "<< event_CommonCalc<<endl;//xxx
		nDuplicates++;
		continue;
		}
	}//end if isData
	else{ //unrelated; if it is MC, figure the lepton scale factors
	    for(int iele = 0; iele<nTightEle; ++iele){
		lep_MVA_ID_SF   *= Get_Ele_MVA_ID_SF(   (*elPt_singleLepCalc)[TightEleIndicies[iele]], (*elEta_singleLepCalc)[TightEleIndicies[iele]]);
		lep_Mini_Iso_SF *= Get_Ele_Mini_Iso_SF( (*elPt_singleLepCalc)[TightEleIndicies[iele]], (*elEta_singleLepCalc)[TightEleIndicies[iele]]);
	    }
	    for(int imu = 0; imu<nTightMuons; ++imu){
		lep_MVA_ID_SF   *= Get_Muon_MVA_ID_SF(   (*muPt_singleLepCalc)[TightMuonIndicies[imu]], (*muEta_singleLepCalc)[TightMuonIndicies[imu]]);
		lep_Mini_Iso_SF *= Get_Muon_Mini_Iso_SF( (*muPt_singleLepCalc)[TightMuonIndicies[imu]], (*muEta_singleLepCalc)[TightMuonIndicies[imu]]);
	    }
	}//end else if is MC

	/////////////////////////////////////////////////////////////////
	//////////////////////// FIND JETS  /////////////////////////////
	/////////////////////////////////////////////////////////////////
	//        _      _       
	//       | | ___| |_ ___ 
	//    _  | |/ _ \ __/ __|
	//   | |_| |  __/ |_\__ \
	//    \___/ \___|\__|___/
	//                       
	//xxjets
	if(printlevel >= 5) cout<<"Begind jets"<<endl;
	vector<int> JetAK4Indicies;
	int nJetAK4= 0;
	float HT = 0;
	float jetSFs[3] = {1.f}; //enum JetSFmode{JetSFnominal = 0, JetSFup = 1, JetSFdown = 2};
	TLorentzVector VHad(0,0,0,0);
	for(int ijet = 0; ijet< (int)AK4JetPt_singleLepCalc->size(); ++ijet){ //jets are approxomately sorted in Pt order. 
	    //but you saw an instance of
	    //JetPt: 189.88 25.9926 80.4774 
	    //strange thing: we always have at least two jets. 
	    //these are born with pt > 25 cut and |eta| < 2.5 cut
	    if((*AK4JetPt_singleLepCalc)[ijet] < 35 || fabs((*AK4JetEta_singleLepCalc)[ijet]) > 2.4) continue;

	    //seperate the leptons from the jets using cuts listed in B2G-12-015
	    bool jet_passes_DR = true;
	    TLorentzVector vJ, vEl, vMu;
	    vJ.SetPtEtaPhiE((*AK4JetPt_singleLepCalc)[ijet],(*AK4JetEta_singleLepCalc)[ijet], (*AK4JetPhi_singleLepCalc)[ijet], (*AK4JetEnergy_singleLepCalc)[ijet]);
	    for(int iel = 0; iel<nSelEle && jet_passes_DR; ++iel){
		int iele = selEleIndicies[iel];
		vEl.SetPtEtaPhiE((*elPt_singleLepCalc)[iele],(*elEta_singleLepCalc)[iele], (*elPhi_singleLepCalc)[iele], (*elEnergy_singleLepCalc)[iele]);
		jet_passes_DR &= !isSameObject(vJ, vEl, 0.3);
	    }	
	    if(!jet_passes_DR) continue;
	    for(int iMu = 0; iMu<nSelMuons && jet_passes_DR; ++iMu){
		int imu = selMuonIndicies[iMu];
		vMu.SetPtEtaPhiE((*muPt_singleLepCalc)[imu], (*muEta_singleLepCalc)[imu], (*muPhi_singleLepCalc)[imu], (*muEnergy_singleLepCalc)[imu]); 
		jet_passes_DR &= !isSameObject(vJ, vMu, 0.4);
	    }	
	    if(!jet_passes_DR) continue;

	    //jet passes:
	    if(dmcblock->isMC) GetJetSF( (*AK4JetPt_singleLepCalc)[ijet], jetSFs);

	    JetAK4Indicies.push_back(ijet);
	    nJetAK4++;
	    HT += (*AK4JetPt_singleLepCalc)[ijet];
	    VHad = VHad + vJ;
	}//end for all jets
	indexPtSort(JetAK4Indicies, nJetAK4, (*AK4JetPt_singleLepCalc));
	//
	//      Int_t           nJets_CATopoCalc
	//      AK4HT_singleLepCalc
	//      theJetHT_JetSubCalc

	float ST = LepT + HT + corr_met_singleLepCalc; 
	TLorentzVector VSum = VHad + VLep;
	//float MHT = VHad.Pt();
	float MSum = VSum.M();
	float MtSum = Mt(VSum, corr_met_singleLepCalc, corr_met_phi_singleLepCalc);

	float leadjetDR = -1;
	if(nJetAK4 >=2){
	    TLorentzVector vJ1, vJ2;
	    int ijet = JetAK4Indicies[0];
	    vJ1.SetPtEtaPhiE((*AK4JetPt_singleLepCalc)[ijet],(*AK4JetEta_singleLepCalc)[ijet], (*AK4JetPhi_singleLepCalc)[ijet], (*AK4JetEnergy_singleLepCalc)[ijet]);
	    ijet = JetAK4Indicies[1];
	    vJ2.SetPtEtaPhiE((*AK4JetPt_singleLepCalc)[ijet],(*AK4JetEta_singleLepCalc)[ijet], (*AK4JetPhi_singleLepCalc)[ijet], (*AK4JetEnergy_singleLepCalc)[ijet]);
	    leadjetDR = dR(vJ1,vJ2);
	}//end calculate leadjetDR

	/////////////////////////////////////////////////////////////////
	//////////////////////// FIND B-JETS  ///////////////////////////
	/////////////////////////////////////////////////////////////////
	//    ____            _      _       
	//   | __ )          | | ___| |_ ___ 
	//   |  _ \ _____ _  | |/ _ \ __/ __|
	//   | |_) |_____| |_| |  __/ |_\__ \
	//   |____/       \___/ \___|\__|___/
	//                                   
	// xxbtag
	float BTl = 0;
	float BTm = 0;
	//theJetBTag_JetSubCalc
	//theJetFlav_JetSubCalc;
	//theJetCSV_JetSubCalc;
	//nBJets_CATopoCalc
	//int AK4JetBTag_singleLepCalc;  = int value representing a bool = isJetTagged
	//double AK4JetBDisc_singleLepCalc; = pfCombinedInclusiveSecondaryVertexV2BJetTags
	//CISVv2L
	//CISVv2M
	//CISVv2T 

	if(printlevel >= 5) cout<<"Begind Bjets"<<endl;
	vector<int> BJetAK4CISVmIndicies; //these include all the efficiencies and scale factors
	int nBJetAK4CISVm= 0;

	vector<int> BJetAK4CISVtIndicies; //dumb CISV cut, no efficiencies or SF's
	int nBJetAK4CISVt= 0;

	vector<int> BJetAK4CISVmSimpleIndicies;//dumb CISV cut, no efficiencies or SF's
	int nBJetAK4CISVmSimple= 0;

	vector<int> BJetAK4CISVlIndicies;//dumb CISV cut, no efficiencies or SF's
	int nBJetAK4CISVl= 0;

	for(int ijet = 0; ijet<nJetAK4; ++ijet){
	    if((*AK4JetBTag_singleLepCalc)[JetAK4Indicies[ijet]] == 1){ //these include all the scale factors and efficiencies.
		BJetAK4CISVmIndicies.push_back(JetAK4Indicies[ijet]);
		nBJetAK4CISVm++;
	    }
	    float cisv = (*AK4JetBDisc_singleLepCalc)[JetAK4Indicies[ijet]];

	    //if(cisv > CISVv2L){
	    if((*theJetBTagLoose_JetSubCalc)[ijet]==1){
		BJetAK4CISVlIndicies.push_back(JetAK4Indicies[ijet]);
		nBJetAK4CISVl++;
		BTl += (*AK4JetPt_singleLepCalc)[JetAK4Indicies[ijet]];
	    }

		//if(cisv > CISVv2M){
		if((*theJetBTag_JetSubCalc)[ijet]==1){
		    BJetAK4CISVmSimpleIndicies.push_back(JetAK4Indicies[ijet]);
		    nBJetAK4CISVmSimple++;
		    BTm += (*AK4JetPt_singleLepCalc)[JetAK4Indicies[ijet]];

		    if(cisv > CISVv2T){
			BJetAK4CISVtIndicies.push_back(JetAK4Indicies[ijet]);
			nBJetAK4CISVt++;
		    }//end if tight

		}//end if medium

	}//end for all used jets

	indexPtSort(BJetAK4CISVmIndicies, nBJetAK4CISVm, (*AK4JetPt_singleLepCalc));
	indexPtSort(BJetAK4CISVtIndicies, nBJetAK4CISVt, (*AK4JetPt_singleLepCalc));
	indexPtSort(BJetAK4CISVmSimpleIndicies, nBJetAK4CISVmSimple, (*AK4JetPt_singleLepCalc));
	indexPtSort(BJetAK4CISVlIndicies, nBJetAK4CISVl, (*AK4JetPt_singleLepCalc));

	float leadBjetDR = -1;
	if(nBJetAK4CISVm >=2){
	    TLorentzVector vJ1, vJ2;
	    int ijet = BJetAK4CISVmIndicies[0];
	    vJ1.SetPtEtaPhiE((*AK4JetPt_singleLepCalc)[ijet],(*AK4JetEta_singleLepCalc)[ijet], (*AK4JetPhi_singleLepCalc)[ijet], (*AK4JetEnergy_singleLepCalc)[ijet]);
	    ijet = BJetAK4CISVmIndicies[1];
	    vJ2.SetPtEtaPhiE((*AK4JetPt_singleLepCalc)[ijet],(*AK4JetEta_singleLepCalc)[ijet], (*AK4JetPhi_singleLepCalc)[ijet], (*AK4JetEnergy_singleLepCalc)[ijet]);
	    leadBjetDR = dR(vJ1,vJ2);
	}//end calculate leadjetDR

	/*	float Bl_over_HT= BTl/HT;//(0,1)
		float Bm_over_HT= BTm/HT;//(0,1)
		float LepT_over_HT= LepT/HT;
		float HT_over_ST= HT/ST;//(0,1)
		float LepT_over_ST= LepT/ST;//(0,1)
		float MET_over_ST= corr_met_singleLepCalc/ST; //(0,1)
		float MSum_over_ST= MSum/ST;*/

	if(printlevel >= 5) cout<<"Ready for Physics"<<endl;

	//                   __    __        __          __    __        __          __    __
	//                  (//    \\)    __(//   __    (//    \\)    __(//   __    (//    \\)  
	//                  /"      / __  \\)"    \\)_  /"      / __  \\)"    \\)_  /"      / __
	//                '|-..__..-''\_''-.\__..-''  '|-..__..-''\_''-.\__..-''  '|-..__..-''\
	//                (\\  \_    _(\\      _/     (\\  \_    _(\\      _/     (\\  \_    //)
	//                 ""  (\\  //)""     //)      ""  (\\  //)""     //)      ""  (\\   ""
	//                      ""  ""        ""            ""  ""        ""            ""
	//////////////////////////////////////////////////////////////////////
	//////////////////////// READY FOR PHYSICS ///////////////////////////
	//////////////////////////////////////////////////////////////////////
	//xxphysics
	
	//figure the MC br reweight	
	float brWeight = 1.0;
	//if(dmcblock->isMC && dmcblock->string_meta.get("TprimeMass",-1)>0) 
	
	if(fix_BR_event_by_event and isSignal) //this will not run in the final analysis. 
	    brWeight = MCbrReweight( isBWBW_TpTpCalc, isTHBW_TpTpCalc, isTHTH_TpTpCalc, 
		    isTZBW_TpTpCalc, isTZTH_TpTpCalc, isTZTZ_TpTpCalc, 
			dmcblock->float_meta["bWbr"], dmcblock->float_meta["tHbr"], dmcblock->float_meta["tZbr"]);

	//calculate the minimum dR between either lepton and any jet.
	float lepJetDR = -1 + 1000*nJetAK4;//-1 if no jets, some large val to start the minimization otherwise. 
	for(int ijet = 0; ijet < nJetAK4; ijet++){
	    TLorentzVector vJ;
	    vJ.SetPtEtaPhiE((*AK4JetPt_singleLepCalc)[ijet],(*AK4JetEta_singleLepCalc)[ijet], (*AK4JetPhi_singleLepCalc)[ijet], (*AK4JetEnergy_singleLepCalc)[ijet]);
	    lepJetDR = min(dR(vJ,Lep1), lepJetDR);
	    lepJetDR = min(dR(vJ,Lep2), lepJetDR);
	    lepJetDR = min(dR(vJ,Lep3), lepJetDR);

	}//end calculate leadjetDR


	float MinMlb=0.0;
		{
			float MinMeb = 999999.;
			float MinMmb = 999999.;
			TLorentzVector vB, vEl, vMu;
			for(int ijet = 0; ijet < nBJetAK4CISVm; ++ijet){
				int iJet = BJetAK4CISVmIndicies[ijet];
				vB.SetPtEtaPhiE((*AK4JetPt_singleLepCalc)[iJet],(*AK4JetEta_singleLepCalc)[iJet], (*AK4JetPhi_singleLepCalc)[iJet], (*AK4JetEnergy_singleLepCalc)[iJet]);
				for(int iel = 0; iel<nSelEle; ++iel){
					int iele = selEleIndicies[iel];
					vEl.SetPtEtaPhiE((*elPt_singleLepCalc)[iele],(*elEta_singleLepCalc)[iele], (*elPhi_singleLepCalc)[iele], (*elEnergy_singleLepCalc)[iele]);
					float Meb = (vEl+vB).M();
					if(Meb < MinMeb) MinMeb = Meb;
				}	
				for(int iMu = 0; iMu<nSelMuons; ++iMu){
					int imu = selMuonIndicies[iMu];
					vMu.SetPtEtaPhiE((*muPt_singleLepCalc)[imu], (*muEta_singleLepCalc)[imu], (*muPhi_singleLepCalc)[imu], (*muEnergy_singleLepCalc)[imu]); 
					float Mmb = (vMu+vB).M();
					if(Mmb < MinMmb) MinMmb = Mmb;
				}	
			}//end for every b-jet
			MinMlb = MinMeb < MinMmb? MinMeb : MinMmb;
			if(MinMlb > 999998.) MinMlb = -1.;
		}//end minMlb


	setCutBits(AlltopoCut,
		is_triLepT ,
		corr_met_singleLepCalc,
		nJetAK4 ,
		nBJetAK4CISVm ,
		HT ,
		ST,
		MinMlb,
		Mlll,
		MtSum);


	int yield = makeYield(is_elelel, is_elelmu, is_elmumu, is_mumumu,
		AlltopoCut->get("NULL",&tcdFALSE)->pass);
	int yield_bkg = -1;
	if(makeBkgs) yield_bkg = makeYield(is_elelel, is_elelmu, is_elmumu, is_mumumu, 
		AlltopoCut->get("NULL",&tcdFALSE)->bkgpass);

	if(printlevel >= 5)cout<<"Check point 1"<< endl;
	std::vector<double> renorm;                                                                                                                                                              
	std::vector<double> pdf;                                                                                                                                                                 
	//this gives a compiler warning because I'm using passing it two pointers which are effectively return values. 
	if(dmcblock->isMC) doLHEweights(dmcblock, LHEWeightids_singleLepCalc, LHEWeights_singleLepCalc, &renorm, &pdf);
	if(printlevel >= 5)cout<<"Check point 2"<< endl;
	else{ //is data
	    if(is_triLepT){
		Fill_HLT_study(HLT_coincidience_ele, HLT_map_ele, NEleTriggers, EleTriggerIndicies, viSelTriggersEl_singleLepCalc,false);
		Fill_HLT_study(HLT_coincidience_mu,  HLT_map_mu , NMuTriggers,  MuTriggerIndicies,  viSelTriggersMu_singleLepCalc,false);
	    }
	    if(AlltopoCut->get("main",&tcdFALSE)->pass){
		Fill_HLT_study(HLT_coincidience_ele_main, HLT_map_ele, NEleTriggers, EleTriggerIndicies, viSelTriggersEl_singleLepCalc,false);
		Fill_HLT_study(HLT_coincidience_mu_main,  HLT_map_mu , NMuTriggers,  MuTriggerIndicies,  viSelTriggersMu_singleLepCalc,false);
	    }
	}

	if(printlevel >= 5)cout<<"Check point 3"<< endl;

	//for( std::map<std::string,bool>::iterator thiscut = AlltopoCut->begin(); thiscut != AlltopoCut->end(); thiscut++) {
	//AlltopoNpass.touch(thiscut->first,0); //if it doesn't exist, make it.
	//if(thiscut->second) AlltopoNpass.increment(thiscut->first); //if it doesn't exist 
	//}

	////transfer the cuts that you care about into topoCut
	try{
	    for (int iTopo = 0; iTopo<nEventTopologies; iTopo++) {
		topoCut->set(s_EventTopology[iTopo], AlltopoCut->get_throwable(s_EventTopology[iTopo]) );
	    }
	}
	catch(std::pair <std::string,int> errorpair){
	    cerr<<"Error transfering topoCut bools; Invalid event topology key string \""<<errorpair.first<<"\" sought in AlltopoCut" <<endl;
	    std::terminate();
	}

	//Count how many events pass each topology.
	for( std::map<std::string,topoCutDecision *>::iterator thiscut = topoCut->begin(); thiscut != topoCut->end(); thiscut++) {
	    if(thiscut->second->pass) AlltopoNpass.increment(thiscut->first); 
	}
	if(printlevel > 5) cout << "check point A.0" << endl; //debug rizki
	//////////////////////////////////////////////////////////////////////
	////////////////////////// Fill Variables ////////////////////////////
	//////////////////////////////////////////////////////////////////////
	double bkgweights[nmodes] = {0};
	//for this to work there has to be a nLooseLepton == 2 cut. 
	//mode 0 = nominal. 1 = fakerate plus, 2 = fakerate minus, 3 = passrate plus, 4 = passrate minus
	//see feModeBehavior in fakerate.h
	if(makeBkgs){
	    if(is_elelel){
// 			float ele1Pt = Lep1.Pt();
// 			float ele2Pt = Lep2.Pt();
// 			float ele3Pt = Lep3.Pt();
// 			float ele1Eta = Lep1.Eta();
// 			float ele2Eta = Lep2.Eta();
// 			float ele3Eta = Lep3.Eta();
			for(int imode=0;imode<nmodes;imode++){
				bkgweights[imode] = GetWeight_eee(nTightEle_top3, imode);
			}
	    }
	    else if(is_mumumu){
			for(int imode=0;imode<nmodes;imode++){
				bkgweights[imode] = GetWeight_mmm(nTightMuons_top3, imode);
			}
	    }
	    else if(is_elelmu){
// 			float elePt = Lep1.Pt();
// 			float eleEta = Lep1.Eta();
			for(int imode=0;imode<nmodes;imode++){
				bkgweights[imode] = GetWeight_eem(nTightEle_top3, nTightMuons_top3, imode);
			}
	    }
	    else if(is_elmumu){
// 			float elePt = Lep1.Pt();
// 			float eleEta = Lep1.Eta();
			for(int imode=0;imode<nmodes;imode++){
				bkgweights[imode] = GetWeight_emm(nTightEle_top3, nTightMuons_top3, imode);
			}
	    }
	    else{ cerr<<"Error! no combination of eee, eem, emm, mmm, so what the hell is it?"<<endl; assert(0);}
	}//end make background weights.
	if(printlevel > 5) cout << "check point A" << endl; //debug rizki
	if(is_elelel){
		Neee[nTightEle_top3]++;
	}
	else if(is_elelmu){
	    Neem[2*nTightEle_top3 + nTightMuons_top3]++;
	}
	else if(is_elmumu){
	    Nemm[nTightEle_top3 + 2*nTightMuons_top3]++;
	}
	else if(is_mumumu){
	    Nmmm[nTightMuons_top3]++;
	}
	if(printlevel > 5) cout << "check point B" << endl; //debug rizki

	float weight = (MCWeight_singleLepCalc<0.)? -1. : 1.;
	weight *= brWeight*lep_Mini_Iso_SF*lep_MVA_ID_SF;;
	if(printlevel > 5) cout << "check point B-1" << endl; //debug rizki
	float weight_before_PU = weight;
	double puweight_nominal = 1.0;
	double puweight_up =      1.0;
	double puweight_down =    1.0;
	if(dmcblock->isMC){
	    puweight_nominal = puweight260627_69ub[nTrueInteractions_singleLepCalc];
	    puweight_up =      puweight260627_72ub[nTrueInteractions_singleLepCalc]; 
	    puweight_down =    puweight260627_65ub[nTrueInteractions_singleLepCalc]; 
	    weight*= puweight_nominal * jetSFs[JetSFnominal];
	    /*if((nJetAK4 >= 0 and nJetAK4 < 4 and jentry%100 == 0 ) or 
		    (nJetAK4 >= 4) )
		cout<<"nJ: "<<nJetAK4<<" \tJetSF: "<<jetSFs[JetSFnominal]<<"\t weight: "<<weight<<" \tbr*lepSFs "<<weight_before_PU<<" \twPU "<<puweight_nominal<<" \tHT/nJ "<<HT/((float)nJetAK4)<<endl;*/
	
	}
	//puweight260627_72ub
	//puweight260627_65ub

	try{
	    //FILL SPECIAL PLOTS HERE.
	    if(AlltopoCut->get_throwable("main")->pass){ 
		h_yield->Fill(yield,weight);
// 		h_yieldsum->Fill(yield,      weight);
// 		h_yieldsum->Fill(yieldSumary,weight);
		if(dmcblock->isMC){
		    //std::vector<double>* renorm, std::vector<double>* pdf 
		    FillPSYields(ps_yield,yield,weight_before_PU,   puweight_nominal,puweight_up,puweight_down,jetSFs,   &renorm, &pdf);
		}
		if(isSignal){
		    if(isBWBW_TpTpCalc)	{	
			h_yield_BB[WW]->Fill(yield, weight);
			FillPSYields(ps_yield_BB[WW],yield,weight_before_PU,  puweight_nominal,puweight_up,puweight_down,jetSFs,  &renorm, &pdf);
		    }
		    else if(isTHBW_TpTpCalc){	
			h_yield_BB[WH]->Fill(yield, weight);
			FillPSYields(ps_yield_BB[WH],yield,weight_before_PU,  puweight_nominal,puweight_up,puweight_down,jetSFs,  &renorm, &pdf);
		    }
		    else if(isTZBW_TpTpCalc){	
			h_yield_BB[WZ]->Fill(yield, weight);
			FillPSYields(ps_yield_BB[WZ],yield,weight_before_PU,  puweight_nominal,puweight_up,puweight_down,jetSFs,  &renorm, &pdf);
		    }
		    else if(isTHTH_TpTpCalc){	
			h_yield_BB[HH]->Fill(yield, weight);
			FillPSYields(ps_yield_BB[HH],yield,weight_before_PU,  puweight_nominal,puweight_up,puweight_down,jetSFs,  &renorm, &pdf);
		    }
		    else if(isTZTH_TpTpCalc){	
			h_yield_BB[HZ]->Fill(yield, weight);
			FillPSYields(ps_yield_BB[HZ],yield,weight_before_PU,  puweight_nominal,puweight_up,puweight_down,jetSFs, &renorm, &pdf);
		    }
		    else if(isTZTZ_TpTpCalc){	
			h_yield_BB[ZZ]->Fill(yield, weight);
			FillPSYields(ps_yield_BB[ZZ],yield,weight_before_PU,  puweight_nominal,puweight_up,puweight_down,jetSFs,    &renorm, &pdf);
		    }
		}//end if signal

	    }//end if main
	}//end try
	catch(std::pair <std::string,int> errorpair){
	    cerr<<"Error cut-filling special plots; Invalid event topology key string \""<<errorpair.first<<"\" sought in AlltopoCut" <<endl;
	    std::terminate();
	}
	if(printlevel > 5) cout << "C" << std::endl;

if(printlevel > 5) cout << "D" << std::endl;
	if(makeBkgs){ //fill bkg specials
	    //FillBkg(TH2F* h, float x, bkgweights, weight);

	    try{
			//FILL SPECIAL PLOT BACKGROUNDS HERE.
	// 		if(AlltopoCut->get_throwable("OSDL1sanslb")->bkgpass) 	FillBkg(b_MinMlb_OSDL1sanslb,MinMlb,	bkgweightsOS,weight);
	// 		if(AlltopoCut->get_throwable("OSDL1sansS")->bkgpass) 	FillBkg(b_ST_OSDL1sansS,ST,	bkgweightsOS,weight);
			if(AlltopoCut->get_throwable("main")->bkgpass) 	        FillBkg(b_yield,yield_bkg,	bkgweights,weight);

	    	}
	    catch(std::pair <std::string,int> errorpair){
			cerr<<"Error cut-filling special plots; Invalid event topology key string \""<<errorpair.first<<"\" sought in AlltopoCut" <<endl;
			std::terminate();
			}


if(printlevel > 5) cout << "E" << std::endl;
	}//end fill bkg specials 

	//Fill the For-Everys
	for (int iTopo=0; iTopo<nEventTopologies; iTopo++) {
	    try{
		if(topoCut->get_throwable(s_EventTopology[iTopo],1)->pass ){
		    //float weight = m_BTagWeight[s_EventTopology[iTopo]]->weight(jetInfoVVector);//takes significant time.
		    LabelHist MapKinVar = lh_unsliced.get_throwable(s_EventTopology[iTopo],2);

			if(KinVarSwitches->get_throwable("yield",3)) MapKinVar.get_throwable("yield",4)->Fill(yield,weight);

		    //you're using lh_unsliced, which is thing that didn't feel M_gg binning; so always use that.
		    if(KinVarSwitches->get_throwable("nJ",3)) MapKinVar.get_throwable("nJ",4)->Fill(nJetAK4,weight);
		    if(KinVarSwitches->get_throwable("nBm",3)) MapKinVar.get_throwable("nBm",4)->Fill(nBJetAK4CISVm,weight);
		    if(KinVarSwitches->get_throwable("nBl",3)) MapKinVar.get_throwable("nBl",4)->Fill(nBJetAK4CISVl,weight);
		    if(KinVarSwitches->get_throwable("BTm",3)) MapKinVar.get_throwable("BTm",4)->Fill(BTm,weight);
		    if(KinVarSwitches->get_throwable("BTl",3)) MapKinVar.get_throwable("BTl",4)->Fill(BTl,weight);
		    if(KinVarSwitches->get_throwable("LHT",3)) MapKinVar.get_throwable("LHT",4)->Fill(HT-BTl,weight);
		    if(KinVarSwitches->get_throwable("HT",3)) MapKinVar.get_throwable("HT",4)->Fill(HT,weight);
		    if(KinVarSwitches->get_throwable("ST",3)) MapKinVar.get_throwable("ST",4)->Fill(ST,weight);
		    if(KinVarSwitches->get_throwable("LepT",3)) MapKinVar.get_throwable("LepT",4)->Fill(LepT,weight);
		    if(KinVarSwitches->get_throwable("EleT",3)) MapKinVar.get_throwable("EleT",4)->Fill(EleT,weight);
		    if(KinVarSwitches->get_throwable("MuT",3)) MapKinVar.get_throwable("MuT",4)->Fill(MuT,weight);
		    if(KinVarSwitches->get_throwable("MET",3)) MapKinVar.get_throwable("MET",4)->Fill(corr_met_singleLepCalc ,weight);

		    if(KinVarSwitches->get_throwable("Mlll",3)) MapKinVar.get_throwable("Mlll",4)->Fill(Mlll ,weight);

		    if(KinVarSwitches->get_throwable("Mll",3)){
				MapKinVar.get_throwable("Mll",4)->Fill(Mll12 ,weight);
				MapKinVar.get_throwable("Mll",4)->Fill(Mll23 ,weight);
				MapKinVar.get_throwable("Mll",4)->Fill(Mll13 ,weight);
			}

		    if(KinVarSwitches->get_throwable("minMll",3)) MapKinVar.get_throwable("minMll",4)->Fill(min(min(Mll12,Mll23),Mll13) ,weight);

		    if(KinVarSwitches->get_throwable("MinMlb",3)) MapKinVar.get_throwable("MinMlb",4)->Fill(MinMlb ,weight);

		    /*if(KinVarSwitches->get_throwable("BLovHT",3)) MapKinVar.get_throwable("BLovHT",4)->Fill(Bl_over_HT ,weight);
		      if(KinVarSwitches->get_throwable("BMovHT",3)) MapKinVar.get_throwable("BMovHT",4)->Fill(Bm_over_HT ,weight);
		      if(KinVarSwitches->get_throwable("LepTovHT",3)) MapKinVar.get_throwable("LepTovHT",4)->Fill(LepT_over_HT ,weight);
		      if(KinVarSwitches->get_throwable("HTovST",3)) MapKinVar.get_throwable("HTovST",4)->Fill(HT_over_ST ,weight);
		      if(KinVarSwitches->get_throwable("LepTovST",3)) MapKinVar.get_throwable("LepTovST",4)->Fill(LepT_over_ST ,weight);
		      if(KinVarSwitches->get_throwable("METovST",3)) MapKinVar.get_throwable("METovST",4)->Fill(MET_over_ST ,weight);
		      if(KinVarSwitches->get_throwable("MSumovST",3)) MapKinVar.get_throwable("MSumovST",4)->Fill(MSum_over_ST ,weight);*/
		    if(KinVarSwitches->get_throwable("MSum",3)) MapKinVar.get_throwable("MSum",4)->Fill(MSum ,weight);
		    if(KinVarSwitches->get_throwable("MtSum",3)) MapKinVar.get_throwable("MtSum",4)->Fill(MtSum ,weight);

		    if(KinVarSwitches->get_throwable("lepPt",3)){
		    	for(int ilep = 0; ilep<nSelLep; ++ilep){
					MapKinVar.get_throwable("lepPt",4)->Fill(lepPt[ilep] ,weight);
					//lepPt.push_back((*elPt_singleLepCalc)[selEleIndicies[iele]]);		
					//lepPhi.push_back((*elPhi_singleLepCalc)[selEleIndicies[iele]]);		
					//lepEta.push_back((*elEta_singleLepCalc)[selEleIndicies[iele]]);		
				}
		    }
		    if(KinVarSwitches->get_throwable("lepEta",3)){
		    	for(int ilep = 0; ilep<nSelLep; ++ilep){
					MapKinVar.get_throwable("lepEta",4)->Fill(lepEta[ilep] ,weight);
				}
			}
			
			if(KinVarSwitches->get_throwable("eleMiniIso",3)){
		    	for(int iele = 0; iele<nSelEle; ++iele){
					MapKinVar.get_throwable("eleMiniIso",4)->Fill((*elMiniIso_singleLepCalc)[selEleIndicies[iele]] ,weight);
				}
			}

			if(KinVarSwitches->get_throwable("muMiniIso",3)){
		    	for(int imu = 0; imu<nSelMuons; ++imi){
					MapKinVar.get_throwable("muMiniIso",4)->Fill((*muMiniIso_singleLepCalc)[selMuonIndicies[iele]] ,weight);
				}
			}
			
		    if(KinVarSwitches->get_throwable("lepDPhi",3)){
				MapKinVar.get_throwable("lepDPhi",4)->Fill(lepDPhi12 ,weight);
				MapKinVar.get_throwable("lepDPhi",4)->Fill(lepDPhi23 ,weight);
				MapKinVar.get_throwable("lepDPhi",4)->Fill(lepDPhi13 ,weight);
			}
		    if(KinVarSwitches->get_throwable("lepDPhi",3)){
				MapKinVar.get_throwable("minLepDPhi",4)->Fill(min(min(lepDPhi12,lepDPhi23),lepDPhi13) ,weight);
			}
		    if(KinVarSwitches->get_throwable("lepDR",3)){
				MapKinVar.get_throwable("lepDR",4)->Fill(lepDR12 ,weight);
				MapKinVar.get_throwable("lepDR",4)->Fill(lepDR23 ,weight);
				MapKinVar.get_throwable("lepDR",4)->Fill(lepDR13 ,weight);
			}
		    if(KinVarSwitches->get_throwable("minLepDR",3)){
				MapKinVar.get_throwable("minLepDR",4)->Fill(min(min(lepDR12,lepDR23),lepDR13) ,weight);
			}
		    if(KinVarSwitches->get_throwable("jetPt",3)) 
			for(int ijet = 0;ijet<nJetAK4; ++ijet)
			    MapKinVar.get_throwable("jetPt",4)->Fill((*AK4JetPt_singleLepCalc)[JetAK4Indicies[ijet]] ,weight); //only want jet that pass right??

		    if(KinVarSwitches->get_throwable("jetEta",3)) 
			for(int ijet = 0;ijet<nJetAK4; ++ijet)
			    MapKinVar.get_throwable("jetEta",4)->Fill((*AK4JetEta_singleLepCalc)[JetAK4Indicies[ijet]] ,weight); //only want jet that pass, right??

		    if(KinVarSwitches->get_throwable("leadjetDR",3)) MapKinVar.get_throwable("leadjetDR",4)->Fill(leadjetDR ,weight);
		    if(KinVarSwitches->get_throwable("leadBjetDR",3)) MapKinVar.get_throwable("leadBjetDR",4)->Fill(leadBjetDR ,weight);
		    if(KinVarSwitches->get_throwable("lepJetDR",3)) MapKinVar.get_throwable("lepJetDR",4)->Fill(lepJetDR ,weight);


		}//end if event passes topo
	    }//end try
	    catch(std::pair <std::string,int> errorpair){
		switch(errorpair.second ){
		    case 1: cerr<<"Error while looping through event topologies: Invalid event topology key string \""<<errorpair.first<<"\" sought in topoCut" <<endl; break;
		    case 2:cerr<<"Error while filling histograms: Invalid event topology key string \""<<errorpair.first<<"\" sought in lh_unsliced "<<endl; break;
		    case 3:cerr<<"Error while filling histograms; Invalid kinematic variable key string \""<<errorpair.first<<"\" sought in KinVarSwitches"<<endl; break;
		    case 4:cerr<<"Error while filling histograms; Invalid kinematic variable key string \""<<errorpair.first<<"\" sought in lh_unsliced for topo  "<<  s_EventTopology[iTopo]<<endl; break;
		}//end switch
		std::terminate();
	    } //end catch failed stringmap gets
	}//end for every event topology

if(printlevel > 5) cout << "F" << std::endl;

	//Fill Background distributions
	if(makeBkgs){
	    //Fill the For-Everys
	    for (int iTopo=0; iTopo<nEventTopologies; iTopo++) {
			try{
				if(topoCut->get_throwable(s_EventTopology[iTopo],1)->bkgpass){
				//float weight = m_BTagWeight[s_EventTopology[iTopo]]->weight(jetInfoVVector);//takes significant time.

				LabelHist2D MapKinVar = lb_unsliced.get_throwable(s_EventTopology[iTopo],2);

				if(KinVarSwitches->get_throwable("yield",3)) FillBkg(MapKinVar.get_throwable("yield",4),yield_bkg, bkgweights, weight);

				if(KinVarSwitches->get_throwable("nJ",3)) FillBkg(MapKinVar.get_throwable("nJ",4),nJetAK4, bkgweights, weight);
				if(KinVarSwitches->get_throwable("nBm",3)) FillBkg(MapKinVar.get_throwable("nBm",4),nBJetAK4CISVm, bkgweights, weight);
				if(KinVarSwitches->get_throwable("nBl",3)) FillBkg(MapKinVar.get_throwable("nBl",4),nBJetAK4CISVl, bkgweights, weight);
				if(KinVarSwitches->get_throwable("BTm",3)) FillBkg(MapKinVar.get_throwable("BTm",4),BTm, bkgweights, weight);
				if(KinVarSwitches->get_throwable("BTl",3)) FillBkg(MapKinVar.get_throwable("BTl",4),BTl, bkgweights, weight);
				if(KinVarSwitches->get_throwable("LHT",3)) FillBkg(MapKinVar.get_throwable("LHT",4),HT-BTl, bkgweights, weight);
				if(KinVarSwitches->get_throwable("HT",3)) FillBkg(MapKinVar.get_throwable("HT",4),HT, bkgweights, weight);
				if(KinVarSwitches->get_throwable("ST",3)) FillBkg(MapKinVar.get_throwable("ST",4),ST, bkgweights, weight);
				if(KinVarSwitches->get_throwable("LepT",3)) FillBkg(MapKinVar.get_throwable("LepT",4),LepT, bkgweights, weight);
				if(KinVarSwitches->get_throwable("EleT",3)) FillBkg(MapKinVar.get_throwable("EleT",4),EleT, bkgweights, weight);
				if(KinVarSwitches->get_throwable("MuT",3)) FillBkg(MapKinVar.get_throwable("MuT",4),MuT, bkgweights, weight);
				if(KinVarSwitches->get_throwable("MET",3)) FillBkg(MapKinVar.get_throwable("MET",4),corr_met_singleLepCalc , bkgweights, weight);

				if(KinVarSwitches->get_throwable("Mlll",3)) FillBkg(MapKinVar.get_throwable("Mlll",4),Mlll , bkgweights, weight);

				if(KinVarSwitches->get_throwable("Mll",3)){ 
					FillBkg(MapKinVar.get_throwable("Mll",4), Mll12 , bkgweights, weight);
					FillBkg(MapKinVar.get_throwable("Mll",4), Mll23 , bkgweights, weight);
					FillBkg(MapKinVar.get_throwable("Mll",4), Mll13 , bkgweights, weight);
				}

				if(KinVarSwitches->get_throwable("minMll",3)) FillBkg(MapKinVar.get_throwable("minMll",4), min(min(Mll12,Mll23),Mll13) , bkgweights, weight);

				if(KinVarSwitches->get_throwable("MinMlb",3)) FillBkg(MapKinVar.get_throwable("MinMlb",4),MinMlb , bkgweights, weight);

				if(KinVarSwitches->get_throwable("MSum",3)) FillBkg(MapKinVar.get_throwable("MSum",4),MSum , bkgweights, weight);
				if(KinVarSwitches->get_throwable("MtSum",3)) FillBkg(MapKinVar.get_throwable("MtSum",4),MtSum , bkgweights, weight);

				if(KinVarSwitches->get_throwable("lepPt",3)){
					for(int ilep = 0; ilep<nSelLep; ++ilep){
						FillBkg(MapKinVar.get_throwable("lepPt",4), lepPt[ilep], bkgweights, weight);
					}
				}
				if(KinVarSwitches->get_throwable("lepEta",3)){
					for(int ilep = 0; ilep<nSelLep; ++ilep){
						FillBkg(MapKinVar.get_throwable("lepEta",4), lepEta[ilep], bkgweights, weight);
					}
				}
				
				if(KinVarSwitches->get_throwable("eleMiniIso",3)){
					for(int iele = 0; iele<nSelEle; ++iele){
						FillBkg(MapKinVar.get_throwable("eleMiniIso",4), (*elMiniIso_singleLepCalc)[selEleIndicies[iele]], bkgweights, weight);
					}
				}

				if(KinVarSwitches->get_throwable("muMiniIso",3)){
					for(int imu = 0; imu<nSelMuons; ++imi){
						FillBkg(MapKinVar.get_throwable("muMiniIso",4), (*muMiniIso_singleLepCalc)[selMuonIndicies[iele]], bkgweights ,weight);
					}
				}
				
				if(KinVarSwitches->get_throwable("lepDPhi",3)) {
					FillBkg(MapKinVar.get_throwable("lepDPhi",4),lepDPhi12 , bkgweights, weight);
					FillBkg(MapKinVar.get_throwable("lepDPhi",4),lepDPhi23 , bkgweights, weight);
					FillBkg(MapKinVar.get_throwable("lepDPhi",4),lepDPhi13 , bkgweights, weight);
				}
				if(KinVarSwitches->get_throwable("lepDPhi",3)){
						FillBkg(MapKinVar.get_throwable("minLepDPhi",4), (min(min(lepDPhi12,lepDPhi23),lepDPhi13)) , bkgweights, weight);
					}	
				if(KinVarSwitches->get_throwable("lepDR",3)){ 
					FillBkg(MapKinVar.get_throwable("lepDR",4),lepDR12 , bkgweights, weight);
					FillBkg(MapKinVar.get_throwable("lepDR",4),lepDR23 , bkgweights, weight);
					FillBkg(MapKinVar.get_throwable("lepDR",4),lepDR13 , bkgweights, weight);
				}
				if(KinVarSwitches->get_throwable("minLepDR",3)){
					FillBkg(MapKinVar.get_throwable("minLepDR",4), (min(min(lepDR12,lepDR23),lepDR13)), bkgweights, weight);
				}				
				if(KinVarSwitches->get_throwable("jetPt",3)) 
					for(int ijet = 0;ijet<nJetAK4; ++ijet)
					FillBkg(MapKinVar.get_throwable("jetPt",4),(*AK4JetPt_singleLepCalc)[JetAK4Indicies[ijet]] , bkgweights, weight); //only want jet that pass, right??

				if(KinVarSwitches->get_throwable("jetEta",3)) 
					for(int ijet = 0;ijet<nJetAK4; ++ijet)
					FillBkg(MapKinVar.get_throwable("jetEta",4),(*AK4JetEta_singleLepCalc)[JetAK4Indicies[ijet]] , bkgweights, weight); //only want jet that pass, right??

				if(KinVarSwitches->get_throwable("leadjetDR",3)) FillBkg(MapKinVar.get_throwable("leadjetDR",4),leadjetDR , bkgweights, weight);
				if(KinVarSwitches->get_throwable("leadBjetDR",3)) FillBkg(MapKinVar.get_throwable("leadBjetDR",4),leadBjetDR , bkgweights, weight);
				if(KinVarSwitches->get_throwable("lepJetDR",3)) FillBkg(MapKinVar.get_throwable("lepJetDR",4),lepJetDR , bkgweights, weight);
	if(printlevel > 5) cout << "G" << std::endl;

				}//end if event passes topo
			}//end try
			catch(std::pair <std::string,int> errorpair){
				switch(errorpair.second ){
				case 1: cerr<<"Error while looping through event topologies: Invalid event topology key string \""<<errorpair.first<<"\" sought in topoCut" <<endl;
				case 2:cerr<<"Error while filling histograms: Invalid event topology key string \""<<errorpair.first<<"\" sought in lh_unsliced "<<endl;
				case 3:cerr<<"Error while filling histograms; Invalid kinematic variable key string \""<<errorpair.first<<"\" sought in KinVarSwitches"<<endl;
				case 4:cerr<<"Error while filling histograms; Invalid kinematic variable key string \""<<errorpair.first<<"\" sought in lh_unsliced for topo  "<<  s_EventTopology[iTopo]<<endl;
				}//end switch
				std::terminate();
			} //end catch failed stringmap gets
	    }//end for every event topology
	}//end fill bkg grid
if(printlevel > 5) cout << "H" << std::endl;

	}//end main event loop
	//////////////////////////////////////////////////////////////
	//////////////////////// FINISH UP ///////////////////////////
	///////////////////////////////////////////////////////////////

if(printlevel > 5) cout << "I.0" << std::endl;
	TFile* fout = new TFile(dmcblock->string_meta["EventLoopOutRoot"].c_str(),"RECREATE");
	fout->cd();
	//write out the files

	//direcly write out the various selvars //this is inelegant. automate it. 

if(printlevel > 5) cout << "I" << std::endl;
	/////////////////////Write Kinvar Histograms//////////////////
	try{
	    for (int iTopo=0; iTopo<nEventTopologies; iTopo++) {
		LabelHist MapKinVar = lh_unsliced.get_throwable(s_EventTopology[iTopo],-1);
		for (int kKinVar = 0; kKinVar<nKinemVars_all; kKinVar++) {
		    MapKinVar.get_throwable(s_KinemVars_all[kKinVar],iTopo)->Write();
		}//for every kinvar
	    }//end for every topology

	    if(makeBkgs){
		//write the grid of background histograms
		for (int iTopo=0; iTopo<nEventTopologies; iTopo++) {
		    LabelHist2D MapKinVar = lb_unsliced.get_throwable(s_EventTopology[iTopo],-1);
		    for (int kKinVar = 0; kKinVar<nKinemVars_all; kKinVar++) {
			MapKinVar.get_throwable(s_KinemVars_all[kKinVar],iTopo)->Write();
		    }//for every kinvar
		}//end for every topology
	    }
	}
	catch(std::pair <std::string,int> errorpair){
	    if (errorpair.second == -1)
		cerr<<"Error while writing histograms: Invalid event topology key string \""<<errorpair.first<<"\" sought in lh_unsliced "<<endl;
	    else{ //else take the error code to be iTopo
		cerr<<"Error while writing histograms; Invalid kinematic variable key string \""<<errorpair.first<<"\" sought in lh_unsliced for topo  "<<  s_EventTopology[errorpair.second]<<endl;
	    }
	    fout->Close();
	    //empty the output file so you don't mistaknely think it worked.
	    TFile* fout_killer = new TFile(dmcblock->string_meta["EventLoopOutRoot"].c_str(),"RECREATE");
	    fout_killer->Close();
	    std::terminate();
	} //end catch failed stringmap gets
if(printlevel > 5) cout << "J" << std::endl;
	//Write the specials 
	h_yield->Write();

	Convert_nPolySysYields_to_nSysYields(s_yield,ps_yield);
	s_yield->Write();
	
	if(isSignal){
	    for(int i=0;i<nBByields;i++) h_yield_BB[i]->Write();
	    for(int i=0;i<nBByields;i++) Convert_nPolySysYields_to_nSysYields(s_yield_BB[i],ps_yield_BB[i]);
	    for(int i=0;i<nBByields;i++) s_yield_BB[i]->Write();
	}

// 	h_MinMlb_OSDL1sanslb->Write();
// 	h_ST_OSDL1sansS->Write();

	/////////////////End Write Kinvar Histograms//////////////////

	/////////////////Write Special Background Histograms////////////
	if(makeBkgs){

	    b_yield->Write();

// 	    b_MinMlb_OSDL1sanslb->Write();
// 	    b_ST_OSDL1sansS->Write();
	}

	printf("Counts passing trilep Cut: %i, duplicates: %i\n",nPassTrilepCut, nDuplicates);
	printf("Counts of eee: LLL(%i), LLT(%i), LTT(%i), TTT(%i)\n", Neee[0], Neee[1], Neee[2], Neee[3]);
	printf("Counts of eem: LLL(%i), LLT(%i), LTL(%i), LTT(%i), TTL(%i), TTT(%i)\n", Neem[0], Neem[1], Neem[2], Neem[3], Neem[4], Neem[5]);
	printf("Counts of emm: LLL(%i), TLL(%i), LLT(%i), TLT(%i), LTT(%i), TTT(%i)\n", Nemm[0], Nemm[1], Nemm[2], Nemm[3], Nemm[4], Nemm[5]);
	printf("Counts of mmm: LLL(%i), LLT(%i), LTT(%i), TTT(%i)\n", Nmmm[0], Nmmm[1], Nmmm[2], Nmmm[3]);

	fout->Close();


	//delete all those histograms you made
	for (int iTopo = 0; iTopo<nEventTopologies; iTopo++) {
	    for (int kKinVar = 0; kKinVar < nKinemVars_all; kKinVar++) {
		delete gDirectory->FindObject( (char*)(string("h_")+s_KinemVars_all[kKinVar]+s_EventTopology[iTopo]).c_str());
	    }//end for every kinematic varriable.
	}//end for every topology

	if(!onfire){
	    ofstream firealarm2;
	    firealarm2.open("tmpfirealarm.txt");
	    firealarm2 << "SusyAna_MC_BTagEff_arg is ok"<<endl;
	    firealarm2.close();
	}
    }//end Loop

    bool tpmultlepmaincalc::isSameObject(TLorentzVector& p1, TLorentzVector& p2, const float dRmax){
	float dEta = p1.Eta() - p2.Eta();
	float dPhi = TVector2::Phi_mpi_pi(p1.Phi() - p2.Phi());
	return std::sqrt(dEta*dEta + dPhi*dPhi) < dRmax;
    }//dR cut

    /*   ____________________________________________________________
	 /\    /\    /\    /\    /\    /\    /\    /\    /\    /\
	 /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \
	 /    \/    \/    \/    \/    \/    \/    \/    \/    \/    \
	 \    /\    /\    /\    /\    /\    /\    /\    /\    /\    /
	 \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /  \  /
	 __\/____\/____\/____\/____\/____\/____\/____\/____\/____\/__
	 */

    void setCutBits(stringmap<topoCutDecision*>* AlltopoCut, bool is_triLepT , float met, int nJetAK4 , 
	    int nBJetAK4CISVm , float HT , float ST, float MinMlb, float Mlll, float MtSum){

// 	bool met30 = met > 30.;
// 	bool MinMlbcut = MinMlb > 170.;
// 	bool Mlll20 = Mlll>20.;
// 	bool MlllOffZ =  Mlll<76. || Mlll > 106.;
// 	bool J23 = (nJetAK4 == 2 || nJetAK4 == 3);
	bool J2 = nJetAK4 >= 2;
	bool J3 = nJetAK4 >= 3;
// 	bool J4 = nJetAK4 >= 4;
// 	bool J5 = nJetAK4 >= 5;
	bool B1 = nBJetAK4CISVm >= 1;
// 	bool B2 = nBJetAK4CISVm >= 2;
// 
// 	bool HT300os1 = HT > 300.;
// 	bool ST900os1 = ST > 1000.;//900.;
// 
// 	bool HT500os2 = HT> 500.;
// 	bool ST1kos2  = ST > 1200.; //1000.;
// 
// 	bool HT500ss = HT > 500.;
// 	bool ST700ss = ST > 1100.;//700.;

	//     ______                           __
	//    / ____/__  ____  ___  _________ _/ /
	//   / / __/ _ \/ __ \/ _ \/ ___/ __ `/ / 
	//  / /_/ /  __/ / / /  __/ /  / /_/ / /  
	//  \____/\___/_/ /_/\___/_/   \__,_/_/   
	//                                        

	//topoCutDecision(bool EventIsTightTightTight, bool otherReq)
	AlltopoCut->set("NULL", new topoCutDecision(is_triLepT,true));
	AlltopoCut->set("main", 
		new topoCutDecision(is_triLepT,
			ST>=1100 && 
			B1 && 
			J3 &&
			MtSum >=50)); 

	AlltopoCut->set("ST1100J3MtSum50", 
		new topoCutDecision(is_triLepT,
			ST>=1100 && 
			J3 &&
			MtSum >=50)); 
			
	AlltopoCut->set("ST1100B1J3MtSum50", 
		new topoCutDecision(is_triLepT,
			ST>=1100 && 
			B1 && 
			J3 &&
			MtSum >=50)); 
	AlltopoCut->set("ST1000B1J3MtSum50",
			new topoCutDecision(is_triLepT,
                        ST>=1000 &&
                        B1 &&
                        J3 &&
			MtSum >=50));
	AlltopoCut->set("ST900B1J3MtSum50",
			new topoCutDecision(is_triLepT,
                        ST>=900 &&
                        B1 &&
                        J3 &&
			MtSum >=50));
	AlltopoCut->set("ST800B1J3MtSum50",
			new topoCutDecision(is_triLepT,
                        ST>=800 &&
                        B1 &&
                        J3 &&
			MtSum >=50));
	AlltopoCut->set("ST700B1J3MtSum50",
			new topoCutDecision(is_triLepT,
                        ST>=700 &&
                        B1 &&
                        J3 &&
			MtSum >=50));
	AlltopoCut->set("ST600B1J3MtSum50",
			new topoCutDecision(is_triLepT,
                        ST>=600 &&
                        B1 &&
                        J3 &&
			MtSum >=50));
	AlltopoCut->set("ST500B1J3MtSum50",
			new topoCutDecision(is_triLepT,
                        ST>=500 &&
                        B1 &&
                        J3 &&
			MtSum >=50));

			 
// EXAMPLE:
// 	AlltopoCut->set("OSDL1",  //MAIN OSDL1
// 		new topoCutDecision(is_triLepT,
// 		    met30 && 
// 		    J23 &&
// 		    B1 && 
// 		    HT300os1 && 
// 		    ST900os1 &&
// 		    MinMlbcut &&
// 		    Mlll20 && MllOffZ));

	AlltopoCut->set("1J", new topoCutDecision(is_triLepT,nJetAK4>=1)); 
	AlltopoCut->set("2J", new topoCutDecision(is_triLepT,nJetAK4>=2)); 
	AlltopoCut->set("3J", new topoCutDecision(is_triLepT,nJetAK4>=3)); 
	AlltopoCut->set("4J", new topoCutDecision(is_triLepT,nJetAK4>=4)); 

	AlltopoCut->set("HT400", new topoCutDecision(is_triLepT,HT>=400)); 
	AlltopoCut->set("HT500", new topoCutDecision(is_triLepT,HT>=500)); 
	AlltopoCut->set("HT600", new topoCutDecision(is_triLepT,HT>=600)); 

	AlltopoCut->set("ST700", new topoCutDecision(is_triLepT,ST>=700)); 
	AlltopoCut->set("ST800", new topoCutDecision(is_triLepT,ST>=800)); 
	AlltopoCut->set("ST900", new topoCutDecision(is_triLepT,ST>=900)); 
	AlltopoCut->set("ST1000", new topoCutDecision(is_triLepT,ST>=1000)); 
	AlltopoCut->set("ST1100", new topoCutDecision(is_triLepT,ST>=1100)); 

	AlltopoCut->set("Mt30", new topoCutDecision(is_triLepT,MtSum>=30)); 
	AlltopoCut->set("Mt40", new topoCutDecision(is_triLepT,MtSum>=40)); 
	AlltopoCut->set("Mt50", new topoCutDecision(is_triLepT,MtSum>=50)); 


	//ST800 ...
	AlltopoCut->set("ST800_2J", 
		new topoCutDecision(is_triLepT,
			ST>=800 && 
			J2)); 

	AlltopoCut->set("ST800_3J", 
		new topoCutDecision(is_triLepT,
			ST>=800 && 
			J3)); 

	AlltopoCut->set("ST800_1BmJ", 
		new topoCutDecision(is_triLepT,
			ST>=800 && 
			B1)); 

	AlltopoCut->set("ST800_1BmJ_2J", 
		new topoCutDecision(is_triLepT,
			ST>=800 && 
			B1 && 
			J2)); 

	AlltopoCut->set("ST800_1BmJ_3J", 
		new topoCutDecision(is_triLepT,
			ST>=800 && 
			B1 && 
			J3)); 

	//ST900 ...
	AlltopoCut->set("ST900_2J", 
		new topoCutDecision(is_triLepT,
			ST>=900 && 
			J2)); 

	AlltopoCut->set("ST900_3J", 
		new topoCutDecision(is_triLepT,
			ST>=900 && 
			J3)); 

	AlltopoCut->set("ST900_1BmJ", 
		new topoCutDecision(is_triLepT,
			ST>=1000 && 
			B1)); 

	AlltopoCut->set("ST900_1BmJ_2J", 
		new topoCutDecision(is_triLepT,
			ST>=900 && 
			B1 && 
			J2)); 

	AlltopoCut->set("ST900_1BmJ_3J", 
		new topoCutDecision(is_triLepT,
			ST>=900 && 
			B1 && 
			J3)); 

	//ST1000 ..
	AlltopoCut->set("ST1000_2J", 
		new topoCutDecision(is_triLepT,
			ST>=1000 && 
			J2)); 

	AlltopoCut->set("ST1000_3J", 
		new topoCutDecision(is_triLepT,
			ST>=1000 && 
			J3)); 

	AlltopoCut->set("ST1000_1BmJ", 
		new topoCutDecision(is_triLepT,
			ST>=1000 && 
			B1)); 

	AlltopoCut->set("ST1000_1BmJ_2J", 
		new topoCutDecision(is_triLepT,
			ST>=1000 && 
			B1 && 
			J2)); 

	AlltopoCut->set("ST1000_1BmJ_3J", 
		new topoCutDecision(is_triLepT,
			ST>=1000 && 
			B1 && 
			J3)); 

	//ST1100 ..
	AlltopoCut->set("ST1100_2J", 
		new topoCutDecision(is_triLepT,
			ST>=1100 && 
			J2)); 

	AlltopoCut->set("ST1100_3J", 
		new topoCutDecision(is_triLepT,
			ST>=1100 && 
			J3)); 

	AlltopoCut->set("ST1100_1BmJ", 
		new topoCutDecision(is_triLepT,
			ST>=1100 && 
			B1)); 

	AlltopoCut->set("ST1100_1BmJ_2J", 
		new topoCutDecision(is_triLepT,
			ST>=1100 && 
			B1 && 
			J2)); 

	AlltopoCut->set("ST1100_1BmJ_3J", 
		new topoCutDecision(is_triLepT,
			ST>=1100 && 
			B1 && 
			J3)); 


    } //end set cut bits

    TH1F* init_TH1F_special(string label, string var, LabelKinVars &KinVars ){ //cant throw  <std::string,int> errorpair
	KinematicVar* k= KinVars->get_throwable(var,3);
	return init_TH1F_special(label, k); 
    }
    TH1F* init_TH1F_special(string label, KinematicVar* k){ //cant throw  <std::string,int> errorpair
	TH1F* h;
	if(k->useCustomBinning) h = new TH1F( label.c_str(),
		(char*)(k->titles+";"+k->xlabels).c_str(),
		k->nbins, k->CustomBinning);

	else h = new TH1F( label.c_str(),
		(char*)(k->titles+";"+k->xlabels).c_str(),
		k->nbins, k->hmin, k->hmax);
	return h;
    }


    TH2F* init_bkg_TH2F_special(string label, string var, LabelKinVars &KinVars ){ //cant throw  <std::string,int> errorpair
	KinematicVar* k= KinVars->get_throwable(var,3);
	return init_bkg_TH2F_special(label, k); 
    }
    TH2F* init_bkg_TH2F_special(string label, KinematicVar* k){ //cant throw  <std::string,int> errorpair
	TH2F* h;
	if(k->useCustomBinning) h = new TH2F( label.c_str(),
		(char*)(k->titles+";"+k->xlabels).c_str(),
		k->nbins, k->CustomBinning, nmodes, 0, nmodes);

	else h = new TH2F( label.c_str(),
		(char*)(k->titles+";"+k->xlabels).c_str(),
		k->nbins, k->hmin, k->hmax, nmodes,0,nmodes);
	return h;
    }

    std::map<int,int> Make_HLT_map_selIndex_to_stringIndex(int NTriggers, string Triggers[], vector<string>  * vsSelTriggers){
	std::map<int,int> m;
	int i= 0;
	//cout<<"in Make_HLT_map_selIndex_to_stringIndex"<<endl;
	for( std::vector<string>::iterator itrig = vsSelTriggers->begin(); itrig != vsSelTriggers->end(); itrig++){ 
		//cout<<"consider vsSelTriggers::"<<*itrig<<endl;
	    for(int jtrig = 0; jtrig<NTriggers; jtrig++){
		//cout<<"  against "<<Triggers[jtrig]<<endl;
		if((*itrig).compare(0,Triggers[jtrig].size(),Triggers[jtrig]) ==0  ){ //if the vector on the lists starts with Trigger[jtrig]
		    m[i] = jtrig; //map to the first string named. 
			//cout<<"Mapping LJMET trigger index "<<i<<" to string index "<<jtrig<<endl;
		    break;
		}
	    }//end for every trigger that you actually want
	    i++;
	}//for every trigger in the tuple's vector
	return m;
    }

    void MakeTriggerIndicies(std::vector<int> & TriggerIndicies, int NTriggers, string Triggers[], vector<string>  * vsSelTriggers){
	int i= 0;
	for( std::vector<string>::iterator itrig = vsSelTriggers->begin(); itrig != vsSelTriggers->end(); itrig++){ 
	    for(int jtrig = 0; jtrig<NTriggers; jtrig++){
		if((*itrig).compare(0,Triggers[jtrig].size(),Triggers[jtrig]) ==0  ){ //if the vector on the lists starts with Trigger[jtrig]
		    TriggerIndicies.push_back(i);
		    break;
		}
	    }//end for every trigger that you actually want
	    i++;
	}//for every trigger in the tuple's vector
    }
    bool checkTriggerList(std::vector<int> & TriggerIndicies, int NTriggers, string Triggers[], vector<string>  * vsSelTriggers){
	bool all_trigs_are_ok = true;
	for(std::vector<int>::iterator i=TriggerIndicies.begin(); i!=TriggerIndicies.end();i++){ //for every index that ought to be there.
	    bool trig_is_ok = false;
	    for(int jtrig = 0; jtrig<NTriggers && !trig_is_ok; jtrig++){
		trig_is_ok |= (*vsSelTriggers)[*i].compare(0,Triggers[jtrig].size(),Triggers[jtrig]) ==0;
	    }
	    all_trigs_are_ok &= trig_is_ok;
	    if(!trig_is_ok) cout<<"Warning! trigger at index "<<*i<< " has moved and is not on the trigger list. The trig at that index now reads "<<(*vsSelTriggers)[*i]<<endl;
	}
	return all_trigs_are_ok;
    }

    void indexPtSort(vector<int>& indicies, int n, vector<double> pt){
	//given an array length n of indecies of pt, sort the elements of indicies[] so that pt[indicies[]] is in decending order.

	if(n<2) return;
	else if(n==2){
	    if(pt[indicies[0]]<pt[indicies[1]]){ 
		//swap the indicies so the higher pt one is first
		//note: the xor swap trick works here, but would take 70% longer to run.
		int temp = indicies[0];
		indicies[0] = indicies[1];
		indicies[1] = temp;
	    }
	}//end if 2
	else{
	    //check if sorted
	    bool is_sorting = true;
	    double last = n>0?pt[indicies[0]]:0;
	    for(int i= 1; i<n; ++i){
			double now = pt[indicies[i]];
			if(now>last){ 
				is_sorting = false;
				break;
			}
		last = now;
	    }
	    if(is_sorting) return;

	    //bundle the index and the pt
	    std::vector<mypair*> pairs;
	    for(int i= 0; i<n; ++i){
			mypair *apair = new mypair();
			apair->index = indicies[i];
			apair->pt = pt[indicies[i]];
			pairs.push_back(apair);
	    }
	    std::sort(pairs.begin(), pairs.end(), pairCompare);
	    for(int i= 0; i<n; ++i){
	    	indicies[i] = pairs[i]->index;//put the reults back.
	    	}
	}
    }//end sort by pt

    bool pairCompare(mypair* firstElem, mypair* secondElem) {
	return firstElem->pt > secondElem->pt;
    }

    void FillBkg(TH2F* h, float x, double bkgweights[], double auxWeight){
	//mode 0 = nominal. 1 = fakerate plus, 2 = fakerate minus, 3 = passrate plus, 4 = passrate minus //see feModeBehavior in fakerate.h
	for(int imode=0;imode<nmodes;imode++) h->Fill(x,imode,bkgweights[imode]*auxWeight);
    }
 
	//Yield Sum and YieldSumary return the bin to be filled in the Yield and YieldSum plots, corresponding to the type of event. 
    int makeYield(bool is_elelel, bool is_elelmu, bool is_elmumu, bool is_mumumu, bool main){
	//yield:meaning = {-1:default 0:eee 1:eem 2:emm 3:mmm 4:4orMore}
	int yield;
	if(is_elelel) yield = 0;
	else if(is_elelmu) yield = 1;
	else if(is_elmumu) yield = 2;
	else if(is_mumumu) yield = 3;
	else return -1; //should never happen, but just for the sake of sterilization. 

	if(main) return yield;
	else return -1;
    }//end yield


    float MCbrReweight(
	    bool isBWBW,
	    bool isTHBW,
	    bool isTHTH,
	    bool isTZBW,
	    bool isTZTH,
	    bool isTZTZ,
	    float bWbr,
	    float tHbr,
	    float tZbr){
	//MCbrReweight( isBWBW_TpTpCalc, isTHBW_TpTpCalc, isTHTH_TpTpCalc, isTZBW_TpTpCalc, isTZTH_TpTpCalc, isTZTZ_TpTpCalc,     ... )
	//multiplying by nine = dividing by (1/3)^2
	//the combinatorial factors of 2 cancel. 
	if(isTZTH) return tZbr*tHbr*9.0;
	else if(isTZBW) return tZbr*bWbr*9.0; 
	else if(isTHBW) return tHbr*bWbr*9.0;
	else if(isTZTZ) return tZbr*tZbr*9.0;
	else if(isTHTH) return tHbr*tHbr*9.0;
	else if(isBWBW) return bWbr*bWbr*9.0;
	else return 1.0;
    }//end MCbrReweight

    void Fill_HLT_study(TH2F* h, std::map<int,int> indexmap, int nTrig, std::vector<int> TriggerIndicies, vector<int> *viSelTriggers, bool verbose){
	for(std::vector<int>::iterator i = TriggerIndicies.begin(); i != TriggerIndicies.end(); i++){
	    if(!(*viSelTriggers)[*i]) continue;
	    int I = indexmap[*i];
	    h->Fill(I,I); //diag is how many passed this trigger in general. 
		if(verbose) cout<<"Filling diagonal at "<<I<<endl;
	    bool something_else_passed = false;
	    for(std::vector<int>::iterator j = TriggerIndicies.begin(); j != TriggerIndicies.end(); j++){
		if(*j == *i) continue;
		if(!(*viSelTriggers)[*j]) continue;
		something_else_passed = true;
		int J = indexmap[*j];
		h->Fill(I,J);
		if(verbose) cout<<"Filling off- diagonal at "<<I<<" "<<J<<endl;
	    }//end second loop;
	    if(!something_else_passed){
		h->Fill(nTrig,I);
		if(verbose) cout<<"Filling unique at "<<I<<endl;
	    }
	}//end first loop
    }//end Fill_HLT_study

void doLHEweights(DMCblock* block, vector<int> *LHEWeightids_singleLepCalc, vector<double>  *LHEWeights_singleLepCalc, 
	std::vector<double>* renorm, std::vector<double>* pdf  ){
	//fetches a vector of 6 renormalization weights and a vector of 100 pdf weights. 
	//you are to take the envelope of the renormalization weights and something like the stdev of the fills with pdf weights. 
	//this is computationally wasteful. 
	if(block->type <=0) return;//if data, do nothing 

	if(block->type > 0 and block->type < 10)//if is signal //all signal, b/c it uses a 4 flavor pdf instead of a 5 flavor pdf->
	{
		for(unsigned int i = 0; i < LHEWeightids_singleLepCalc->size(); i++){ //for every LHE weight ID:
			int LHEweightID = LHEWeightids_singleLepCalc->at(i);
			if(LHEweightID < 10 and LHEweightID > 1 and LHEweightID != 6 and LHEweightID != 8){ //ID in {2,3,4,5,7,9}
				renorm->push_back(LHEWeights_singleLepCalc->at(i));
				//renormWeights.push_back(LHEWeights_singleLepCalc->at(i));
			}
			if(LHEweightID > 111 && LHEweightID < 212){ //if ID is in 
				pdf->push_back(LHEWeights_singleLepCalc->at(i));
			}
		}//end for.
	}//end signal
	else if(//all madgraphMLM
			block->type == 85 or  //QCD_HTXtoY_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns
			block->type == 111 or //WJetsToLNu_HT-XToY_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns
			block->type == 113 or //WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
			block->type == 49)    //TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_25ns 
	{
		for(unsigned int i = 0; i < LHEWeightids_singleLepCalc->size(); i++){
			int LHEweightID = LHEWeightids_singleLepCalc->at(i);
			if(LHEweightID < 10 and LHEweightID > 1 and LHEweightID != 6 and LHEweightID != 8){ //ID in {2,3,4,5,7,9}
				renorm->push_back(LHEWeights_singleLepCalc->at(i));
				//renormWeights.push_back(LHEWeights_singleLepCalc->at(i));
			}
			if(LHEweightID < 111 and LHEweightID > 10){
				pdf->push_back(LHEWeights_singleLepCalc->at(i));
			}
		}//end for
	}
	//REMOVE - below - once these block types dataset are fixed / rerun on LJMet !!
   	else if(block->type == 17 || block->type == 19 || block->type == 131 || block->name == "STtWf_BTag_up" || block->name == "STtWf_JEC_up" || block->name == "STtWf_JEC_down" || block->name =="STtWf_JER_up" || block->name =="STtWf_JER_down"){ //KLUGE. 
		for(int i=0;i<nRenorm;++i) renorm->push_back(1.);
		for(int i=0;i<nPDF;++i) pdf->push_back(1.);
	}
	//REMOVE - above - once STf dataset is rerun on LJMet !!
	else
	{ //all MCNLO, all powheg, all pythia
		for(unsigned int i = 0; i < LHEWeightids_singleLepCalc->size(); i++){
			int LHEweightID = LHEWeightids_singleLepCalc->at(i);
			if(LHEweightID > 1001 and LHEweightID < 1010 and LHEweightID != 1006 and LHEweightID != 1008){
				renorm->push_back(LHEWeights_singleLepCalc->at(i));
				//renormWeights.push_back(LHEWeights_singleLepCalc->at(i));
			}
			else if(LHEweightID > 2000 and LHEweightID < 2101){
				pdf->push_back(LHEWeights_singleLepCalc->at(i));
			}
			//else if(LHEweightID == 2101 or LHEweightID == 2102){
			//	alphaSWeights.push_back(LHEWeights_singleLepCalc->at(i));
			//}
		}//end for
	}
}//doLHEweights

void FillPSYields(TH2F* ps_yield,float yield,float weight_before_PU,   double puweight_nominal,double puweight_up,double puweight_down, float* jetSFs, std::vector<double>* renorm, std::vector<double>* pdf ){
	//fills ps_yields with 
    float nominalJetSF = jetSFs[JetSFnominal];
    //enum JetSFmode{JetSFnominal = 0, JetSFup = 1, JetSFdown = 2};
    float nominalweight = weight_before_PU*puweight_nominal*nominalJetSF ;
    ps_yield->Fill(yield,nominalweight,1);//nominal, identical to h_yield
    ps_yield->Fill(yield,weight_before_PU*puweight_down*nominalJetSF,2);//PU uncertainty shifted down
    ps_yield->Fill(yield,weight_before_PU*puweight_up*nominalJetSF,3);//PU uncertianty shifted up
    int next_row = 4;

    if(renorm->size() != nRenorm){
	cout<<"Error! renorm is too short! Renorm size: "<<renorm->size()<< " pdf size: "<<pdf->size()<< endl;
	std::terminate();
    }
    for(int i=0;i<nRenorm;++i) ps_yield->Fill(yield,nominalweight*(*renorm)[i],next_row+i);//renorm uncertainties and nominal PU. 

    if(pdf->size() != nPDF){
	cout<<"Error! pdf is wrong size! PDF size: "<<pdf->size()<<endl;
	std::terminate();
    }
    for(int i=0;i<nPDF;++i) ps_yield->Fill(yield,nominalweight*(*pdf)[i],next_row+nRenorm+i);//with pdf uncertainties and nominal PU

    ps_yield->Fill(yield,weight_before_PU*puweight_nominal*jetSFs[JetSFdown],next_row+nRenorm+nPDF);//Julie Jet SF uncertainty shifted down
    ps_yield->Fill(yield,weight_before_PU*puweight_nominal*jetSFs[JetSFup],  next_row+nRenorm+nPDF+1);//Julie Jet SF uncertainty shifted up

}//end FillPSYields;

void Convert_nPolySysYields_to_nSysYields(TH2F* s_yield,TH2F* ps_yield){
    int nx = ps_yield->GetNbinsX();

    //copy the first three rows
    for(int j=1;j<=3;++j){
	for(int i=0;i<=nx+1;i++){
	    s_yield->SetBinContent(i,j,ps_yield->GetBinContent(i,j));
	    s_yield->SetBinError(i,j,ps_yield->GetBinError(i,j));
	}//for every column
    }//for 3 rows
    int next_row = 4;

	//get envelop of the next nRenorm rows. 
    for(int i=0;i<=nx+1;i++){
	float max = 0.f;
	float max_unc = 0.f;
	float min = 9999999999.f;
	float min_unc = 0.f;
	for(int j=next_row;j<next_row+nRenorm;++j){
		float thisbin = ps_yield->GetBinContent(i,j);
		if(thisbin < min){
		    min = thisbin;
		    min_unc = ps_yield->GetBinError(i,j);
		}
		if(thisbin > max){
		    max = thisbin;
		    max_unc = ps_yield->GetBinError(i,j);
		}
	}
	s_yield->SetBinContent(i,next_row,min);
	s_yield->SetBinError(i,next_row,min_unc);
	
	s_yield->SetBinContent(i,next_row+1,max);
	s_yield->SetBinError(i,next_row+1,max_unc);
    }//for every column
    next_row+=2;

	//reduce the pdf entries
    for(int i=0;i<=nx+1;i++){
		std::vector<val_err_pair*> col;
		for(int j=next_row+nRenorm; j<nPolySysYields;++j){
			//transfer the column into a vector of val_err_pairs.
			val_err_pair *apair = new val_err_pair();
			apair->val = ps_yield->GetBinContent(i,j);
			apair->err = ps_yield->GetBinError(  i,j);
			col.push_back(apair);
		}
		std::sort( col.begin(), col.end() );
		//after sort, smallest is in front.
		s_yield->SetBinContent(i,next_row,col[16-1]->val); //1 sigma low 
		s_yield->SetBinError(  i,next_row,col[16-1]->err);

		s_yield->SetBinContent(i,next_row+1,col[84-1]->val);//1 sigma high
		s_yield->SetBinError(  i,next_row+1,col[84-1]->err);
    }//end for every column. 
    next_row+=2;

	//transfer the Julie 
    for(int j=0;j<2;++j){
	for(int i=0;i<=nx+1;i++){
	    s_yield->SetBinContent(i,next_row+j, ps_yield->GetBinContent(i,nRenorm+nPDF+4+j) );
	    s_yield->SetBinError(  i,next_row+j, ps_yield->GetBinError(  i,nRenorm+nPDF+4+j) );
	}//for every column
    }//for 2 rows

}//end Convert_nPolySysYields_to_nSysYields

bool VEpairCompare(val_err_pair* firstElem, val_err_pair* secondElem) {
	return firstElem->val > secondElem->val;
}

