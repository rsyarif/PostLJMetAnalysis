#ifndef KINEMATICVAR_H
#define KINEMATICVAR_H

#include <iostream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include "TAxis.h"
#include "TMath.h"
#include "math.h"
#include <TH3.h>
#include "TFile.h"
//#include "TTree.h"
//#include "TLegend.h"
//#include "TLorentzVector.h"
//#include "PoissonError.h"
//#include "TGraphAsymmErrors.h"
//#include "TGraphErrors.h"
//#include "TGraph.h"
//#include "TF1.h"
	//user defiend
//#include "utilities.h"
#include <map>
#include "interface/stringmap.h"
#include "interface/controlpannel.h"

using namespace std;
using namespace controlpannel;

//enum cutmode {LEFT=0, RIGHT=1, DOUBLESIDED=2, HIGGS=3, Z=4};
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	

class KinematicVar{
	public:
	KinematicVar(){}

/*	KinematicVar(string _tag, string _titles, string _xlabels,bool _useCustomBinning, int _nbins, float min = 0, float max = -1):tag(_tag),titles(_titles),xlabels(_xlabels),useCustomBinning(_useCustomBinning),nbins(_nbins),hmin(min),hmax(max){ 
		//CustomBinning = new Double_t[nbins+1];
		//by default, the rebinning shall be the same as the old binning
		CustomReBinning = CustomBinning;
		nbins_rebin = nbins;
		useCustomReBinning = false;
	//	mode = LEFT;
	} */
	KinematicVar(string _tag, string _titles, string _xlabels,bool _useCustomBinning, int _nbins, float min = 0, float max = -1, int _nRebins = 0):tag(_tag),titles(_titles),xlabels(_xlabels),useCustomBinning(_useCustomBinning),nbins(_nbins),hmin(min),hmax(max),nbins_rebin(_nRebins){ 
		//CustomBinning = new Double_t[nbins+1];
		//going to use normal rebinning;
		useCustomReBinning = false;
		if(_nRebins==0){
		    CustomReBinning = CustomBinning;
		    nbins_rebin = nbins;
		}
	} 
	~KinematicVar(){}

	string tag;
	string titles;
	string xlabels;
	bool useCustomBinning;
	int nbins;
	float hmin;
	float hmax;
	Double_t *CustomBinning; 
	void usearray(Double_t* f);
	//void printarray();

	int nbins_rebin;
	bool useCustomReBinning;
	Double_t *CustomReBinning; 
	void SetRebinning(int nbins,Double_t* f);
	//enum cutmode mode; //if you were to cut on it, from which direction would you cut?
};
void KinematicVar::usearray(Double_t* f){
	for(int i = 0;i<=nbins;i++) CustomBinning[i] = f[i];
}
void KinematicVar::SetRebinning(int _nbins,Double_t* f){
	useCustomReBinning = true;
	nbins_rebin = _nbins;
	CustomReBinning = new Double_t[_nbins+1];
	for(int i = 0;i<=_nbins;i++) CustomReBinning[i] = f[i];
}
//for setting other metadata, you can just directly access nbins, hmin, hmax


/*void KinematicVar::printarray(){
	printf("{");
	for(int i = 0;i<=nbins;i++) printf("%f, ",CustomBinning[i]);
	printf("}\n");
}*/

typedef stringmap<KinematicVar*>* LabelKinVars;
LabelKinVars setupKinematicVar();
LabelKinVars setupAllKinematicVar();//for internal use only
namedbool* MakeKinVarSwitches();

LabelKinVars setupKinematicVar(){
    LabelKinVars allKinVars = setupAllKinematicVar();
    LabelKinVars retKinVars = new stringmap<KinematicVar*>();
    try{
	    for(int k=0;k<nKinemVars_all;k++){
		    retKinVars->set(s_KinemVars_all[k] , allKinVars->get_throwable(s_KinemVars_all[k]));
	    }
    }
    catch(std::pair <std::string,int> errorpair){
	    cerr<<"Error in setupKinematicVar: allKinVars received invalid string key "<<errorpair.first<<endl;
	    std::terminate();
    }
    return retKinVars;
}

LabelKinVars setupAllKinematicVar(){
//will consider the list of kinematic variables in params_arg and 
//make a map from kinvars to *KinematicVar
//call syntax: 
//LabelKinVars KinVars = setupKinematicVar();

	LabelKinVars allKinVars = new stringmap<KinematicVar*>();
	//first compose an object for everything we've ever defined. 
	
	//examples:
	//KinematicVar(string _tag, string _titles, string _xlabels,bool _useCustomBinning, int _nbins, float min = 0, float max = -1)
	//not covered:
	//int nbins_rebin; Double_t *CustomReBinning;
	//SetRebinning
    //allKinVars->set("MET", new KinematicVar("MET","Missing Transverse Energy","#slash{E}_{T} (GeV)",false, 60, 0.f, 300));
	/*{ KinematicVar* temp = new KinematicVar("ST","Scalar Sum of all Calorimeter Energy","#SigmaE_{E}_{T} (GeV)",true,7);
		Double_t a[] = {0,100,200,300,400,600,800,1000};//remember nbins is #items in a[] -1
		temp->usearray(a);
		//temp->mode = LEFT;
		allKinVars->set("ST", temp); }*/

	//KinematicVar(_tag, _titles, _xlabels,false, _nbins, min, max, _nRebins)
	allKinVars->set("MET", new KinematicVar("MET","Missing Transverse Energy","#slash{E}_{T} (GeV)",false, 240, 0.f, 600, 120));
	allKinVars->set("nJ", new KinematicVar("nJ", "Number of Jets", "Number of Jets",false, 8, 0.f, 8));

	allKinVars->set("nLep", new KinematicVar("nLep", "Number of Leptons", "Number of Leptons",false, 10, 0.f, 10));
	allKinVars->set("nTightLep", new KinematicVar("nLep", "Number of Tight Leptons", "Number of Tight Leptons",false, 10, 0.f, 10));

	allKinVars->set("nBm", new KinematicVar("nBm", "Number of B-Jets", "Number of B-Jets",false, 6, 0.f, 6));
	allKinVars->set("nBl", new KinematicVar("nBl", "Number of Loose B-Jets", "Number of Loose B-Jets",false, 6, 0.f, 6));
	allKinVars->set("BTm", new KinematicVar("BTm","Scalar Sum of all B-jet Transverse Energy", "#SigmaB_{T} (GeV)", false, 750, 0.f, 1500.f,150));
	allKinVars->set("BTl", new KinematicVar("BTl","Scalar Sum of all Loose B-jet Transverse Energy", "#SigmaB_{T} (GeV)", false, 750, 0.f, 1500.f,150));
	allKinVars->set("LHT", new KinematicVar("LHT","Scalar Sum of Light Hadronic Transverse Energy", "#SigmaH_{T} (GeV)", false, 500, 0.f, 1000.f,100));
	allKinVars->set("HT", new KinematicVar("HT","Scalar Sum of all Hadronic Transverse Energy","#SigmaH_{T} (GeV)",false, 1500, 0.f, 3000.f,200));

	{   KinematicVar* temp = new KinematicVar("ST","Scalar Sum of All Reconstructed Transverse Energy","#SigmaE_{T} (GeV)",false,75,0.f,3000.f);
	Double_t a[] = {0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 900, 1000, 2000, 3000}; //remember nbins is #items in a[] -1
	temp->SetRebinning(20,a);
	allKinVars->set("ST", temp);
	}

	allKinVars->set("LepT", new KinematicVar("LepT","Sum Leptonic Transverse Energy", "Lep #SigmaE_{T} (GeV)", false, 400.f, 0.f, 1000.f,200));
	allKinVars->set("EleT", new KinematicVar("EleT","Sum Electron Transverse Energy", "Ele #SigmaE_{T} (GeV)", false, 400.f, 0.f, 1000.f,200));
	allKinVars->set("MuT", new KinematicVar("MuT","Sum Muon Transverse Energy", "Mu #SigmaE_{T} (GeV)", false, 400.f, 0.f, 1000.f,200));

	allKinVars->set("Mlll", new KinematicVar("Mlll","Trilepton Mass","M_{lll} (GeV)",false, 100, 0, 200, 200)); //probably end up with custom rebinning here.
	allKinVars->set("Mll", new KinematicVar("Mll","Dilepton Mass","M_{ll} (GeV)",false, 100, 0, 200, 200));
	allKinVars->set("minMll", new KinematicVar("minMll","Minimum Dilepton Mass","Min(M_{ll}) (GeV)",false, 100, 0, 200, 200));

	{   KinematicVar* temp = new KinematicVar("MinMlb","Minimum lepton-bjet mass","Min(M_{lb}) (GeV)",false, 60, 0, 600);
	Double_t a[] = {0, 34, 68, 102, 136, 170, 204, 238, 300, 400, 600};
	temp->SetRebinning(10,a);//remember nbins is #items in a[] -1
	allKinVars->set("MinMlb", temp);
	}

	allKinVars->set("yield", new KinematicVar("yield","Yields in Various Channels","Channel",false, 4, 0, 4, 1));
	allKinVars->set("yieldsum", new KinematicVar("yieldsum","Yields in Various Channels","Channel",false, 12, 0, 12, 1));

	allKinVars->set("BLovHT", new KinematicVar("BLovHT","BT loose over HT","B_{T}^{loose} / H_{T}",false, 100, 0.0, 1.0, 2)); 
	allKinVars->set("BMovHT", new KinematicVar("BMovHT","BT medium over HT","B_{T}^{medium} / H_{T}",false, 100, 0.0, 1.0, 2)); 
	allKinVars->set("HTovST", new KinematicVar("HTovST","HT over ST","H_{T} / S_{T}",false, 100, 0.0, 1.0, 2)); 
	allKinVars->set("LepTovST", new KinematicVar("LepTovST","LepT over ST","Lep_{T} / S_{T}",false, 100, 0.0, 1.0, 2)); 
	allKinVars->set("METovST", new KinematicVar("METovST","#slash{E}_{T} over ST","#slash{E}_{T} / S_{T}",false, 100, 0.0, 1.0, 2)); 

	allKinVars->set("LepTovHT", new KinematicVar("LepTovHT","LepT over HT","Lep_{T} / H_{T}",false, 100, 0.0, 1.5, 2)); 
	allKinVars->set("MSumovST", new KinematicVar("MSumovST","MSum over ST","M_{#Sigma} / S_{T}",false, 100, 0.0, 1.5, 2)); 
	
	allKinVars->set("MSum", new KinematicVar("MSum","Total Vector Mass of all Reconstructed Jets and Leptons","M_{#Sigma} (GeV)",false, 1000, 0.f, 2000.f,200));
	allKinVars->set("MtSum", new KinematicVar("MtSum","Transverse Mass of Total Reconstructed Vector and #slash{E}_{T}","Mt(V_{#Sigma},#slash{E}_{T}) (GeV)",false, 1000, 0.f, 2000.f,200));

	allKinVars->set("lepPt", new KinematicVar("lepPt","Lepton P_{T}","P_{T} (GeV)",false,240,0,960,2));
	allKinVars->set("jetPt", new KinematicVar("jetPt","Jet P_{T} (GeV)","P_{T} (GeV)",false,240,0,960,2));

	allKinVars->set("lepEta", new KinematicVar("lepEta","Lepton |#eta|","|#eta|",false, 24, 0, 3.5,2));
	allKinVars->set("jetEta", new KinematicVar("jetEta","Jet |#eta|","|#eta|",false, 24, 0, 3.5,2));

	allKinVars->set("lepDPhi", new KinematicVar("lepDPhi","","",false, 30, 0, 3.14159,2));
	allKinVars->set("minLepDPhi", new KinematicVar("minLepDPhi","","",false, 30, 0, 3.14159,2));

	allKinVars->set("lepDR", new KinematicVar("lepDR","Lepton dR","dR",false,120,0,8,2));
	allKinVars->set("minLepDR", new KinematicVar("minLepDR","Minimum Lepton dR","dR",false,120,0,8,2));
	allKinVars->set("leadjetDR", new KinematicVar("leadjetDR","dR between the two leading Jets","dR",false,120,0,8,2));
	allKinVars->set("leadBjetDR", new KinematicVar("leadBjetDR","dR between the leading two B-jets","dR",false,120,0,8,2));
	allKinVars->set("lepJetDR", new KinematicVar("lepJetDR","dR between leptons and the nearest jet","dR",false,120,0,8,2));

	allKinVars->set("eleMiniIso", new KinematicVar("eleMiniIso","electron miniIsolation","e miniIsolation",false,100,0,0.5,1));
	allKinVars->set("muMiniIso", new KinematicVar("muMiniIso","muon miniIsolation","#mu miniIsolation",false,100,0,0.5,1));

	allKinVars->set("eleMiniIso_top3", new KinematicVar("eleMiniIso_top3","electron miniIsolation (of top 3 selected leptons) ","e miniIsolation (of 3 leading leptons)",false,100,0,0.5,1));
	allKinVars->set("muMiniIso_top3", new KinematicVar("muMiniIso_top3","muon miniIsolation (of top 3 selected leptons) ","#mu miniIsolation (of 3 leading leptons",false,100,0,0.5,1));

	allKinVars->set("jetLooseNotTightMuonDR", new KinematicVar("jetLooseNotTightMuonDR","dR between jets and LooseNotTight Muons","dR(jet,#mu)",false,120,0,1.2,2));
	allKinVars->set("TightEleLooseNotTightMuonDR", new KinematicVar("TightEleLooseNotTightMuonDR","dR between tight electrons and looseNotTight muons ","dR(e,#mu)",false,120,0,1.2,2));
	allKinVars->set("LooseMuonLooseNotTightEleDR", new KinematicVar("LooseMuonLooseNotTightEleDR","dR between loose muons and LooseNotTight electrons","dR(#mu,e)",false,120,0,1.2,2));
	allKinVars->set("jetLooseNotTightEleDR", new KinematicVar("jetLooseNotTightEleDR","dR between between jets and LooseNotTight electons","dR(jet,e)",false,120,0,1.2,2));
	

	return allKinVars;
}//end setupAllKinematicVar

/*
class Topology{
	string topo;
	//something about whether it passes? or maybe the definition of the cut. 
	//this is tricky, putting it here makes it less generalizable. 
	string title; //for use in postanaana.C
}
*/

namedbool* MakeKinVarSwitches(){
	//this draws from params.h
	//the bit tells whether the kinvar is on the list of current kinvars or not. 
	//use this to tell if you should try to write to a thing. 
	namedbool* kinvarSwitches = new namedbool();
	LabelKinVars allKinVars = setupAllKinematicVar();
	for( std::map<std::string,KinematicVar *>::iterator thisKinvar = allKinVars->begin(); thisKinvar != allKinVars->end(); thisKinvar++) {
	    kinvarSwitches->set(thisKinvar->second->tag,false); //is it .tag or ->tag?
	}

	//string *s_KinemVars = (bumpJEC == 0 &&  bumpBtagEff ==0)?s_KinemVars_all: s_KinemVars_limit;
	//int nKinemVars = (bumpJEC == 0 &&  bumpBtagEff ==0)?nKinemVars_all: nKinemVars_limit;
	for (int kKinVar = 0; kKinVar<nKinemVars_all; kKinVar++) {
	    kinvarSwitches->set(s_KinemVars_all[kKinVar], true);
	}
	return kinvarSwitches;
} //end MakeKinVarSwitches


/*
Ok, what else do I need? 
I think I need some 2D histograms. 
erm...so there's a difference between plots and kinvars. kinvars can be plotted any which way. 
you can plot one agains another quite happily. 
*/

#endif
