#ifndef _ELEIDCUTS_H
#define _ELEIDCUTS_H


#include <iostream>
#include "math.h"
#include "TMath.h"
//#include "TH2.h"
//#include "TRandom.h"
using namespace std; 

inline float _max(float a, double b);
inline bool is_bar_ele(float eta);
inline bool is_ec_ele(float eta);

float AreaEff(float SCeta, bool T50ns_F25ns);
double RelIso_w_EA(
	double PF_chargedHadronIso,
	double PF_neutralHadronIso,
	double PF_photonIso,
	double PF_PUIso,
	double Pt,
	double SCeta,
	bool T50ns_F25ns);


bool is_veto_ele_2015(
	bool T50ns_F25ns,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float RelIso_w_EA,
	float Einv_m_Pinv,
	float D0,
	float DZ,
	int MHits,
	bool VtxFitConv);
bool is_loose_ele_2015(
	bool T50ns_F25ns,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float RelIso_w_EA,
	float Einv_m_Pinv,
	float D0,
	float DZ,
	int MHits,
	bool VtxFitConv);
bool is_medium_ele_2015(
	bool T50ns_F25ns,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float RelIso_w_EA,
	float Einv_m_Pinv,
	float D0,
	float DZ,
	int MHits,
	bool VtxFitConv);
bool is_tight_ele_2015(
	bool T50ns_F25ns,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float RelIso_w_EA,
	float Einv_m_Pinv,
	float D0,
	float DZ,
	int MHits,
	bool VtxFitConv);
int ele_ID_level_2015(
	bool T50ns_F25ns,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float RelIso_w_EA,
	float Einv_m_Pinv,
	float D0,
	float DZ,
	int MHits,
	bool VtxFitConv);

bool is_tight_ele_2015_MVA_trig( 
	float MVAvalue,
	bool T50ns_F25ns,
	float pt,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float EcalRelIso,
	float HcalRelIso,
	float Track03RelIso);
bool is_tight_ele_2015_MVA_trig_mvaonly( float MVAvalue, bool T50ns_F25ns, float SCEta);
bool is_loose_ele_2015_MVA_trig(
	float MVAvalue,
	bool T50ns_F25ns,
	float pt,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float EcalRelIso,
	float HcalRelIso,
	float Track03RelIso);
bool is_loose_ele_2015_MVA_trig_mvaonly( float MVAvalue, bool T50ns_F25ns, float SCEta);
bool is_ele_2015_MVA_trig_preselection(
	bool T50ns_F25ns,
	float pt,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float EcalRelIso,
	float HcalRelIso,
	float Track03RelIso);
int ele_ID_level_2015_MVA_trig( 
	float MVAvalue,
	bool T50ns_F25ns,
	float pt,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float EcalRelIso,
	float HcalRelIso,
	float Track03RelIso);

bool is_loose_ele_2015_MVA_nontrig( float pt, float SCEta, float MVAvalue, float eleMiniIso);
bool is_tight_ele_2015_MVA_nontrig( float pt, float SCEta, float MVAvalue, float eleMiniIso);
int ele_ID_level_2015_MVA_nontrig( float pt, float SCEta, float MVAvalue, float eleMiniIso);

float eleChargeMisIDRate(float eta, float pt);
int btreeSearch(float x, std::vector<float>ranges);
int btreeSearch(float x, float ranges[], int size);
//float MCsmear(float eta, float r9,TRandom* r);
//float MCsmear_fullsim(float eta, float r9,TRandom* r);

float Get_Ele_MVA_ID_SF(float leppt, float lepeta);
float Get_Muon_Mini_Iso_SF(float leppt, float lepeta);
float Get_Ele_Mini_Iso_SF(float leppt, float lepeta);
float Get_Muon_MVA_ID_SF(float leppt, float lepeta);

// end prototyping

static const float MuMiniIsoThreshTight = 0.2;
static const float MuMiniIsoThreshLoose = 0.4;

inline float _max(float a, double b){
    return a >= (float)b?(float)b:a;
}

inline bool is_bar_ele(float eta){
    return fabs(eta)<1.479;
}
inline bool is_ec_ele(float eta){
    return fabs(eta)>1.479 && fabs(eta)<2.5;
}

float AreaEff(float SCeta, bool T50ns_F25ns){
    //use Ecal Driven Eta; SCEta.
    //T50ns_F25ns = True means use 50ns values, false means use 25ns values
    //For confirmation of Eta bins, see here: 
    //https://indico.cern.ch/event/369235/contribution/4/attachments/734635/1007867/Rami_EffAreas.pdf
    //For 50ns AEff, see here (v2): 
    //slide 8: https://indico.cern.ch/event/369235/contribution/4/attachments/734635/1007867/Rami_EffAreas.pdf
    //https://indico.cern.ch/event/369245/contribution/2/attachments/1153005/1655984/Rami_eleCB_ID_50ns_V2.pdf
    //For 25ns AEff, see here: 
    //slide 12: https://indico.cern.ch/event/369239/contribution/4/attachments/1134761/1623262/talk_effective_areas_25ns.pdf
    //slide 4: https://indico.cern.ch/event/370507/contribution/1/attachments/1140657/1633761/Rami_eleCB_ID_25ns.pdf
    //note the notation { 0.0973, 0.0954, 0.0632, 0.0727, 0.1337 } has Eta [0-0.8] bin first and [2.2,2.5] bin last.
    SCeta = fabs(SCeta);
    if(T50ns_F25ns){ //50 ns
	//valid ofr ele Pt > 20
	if(SCeta >2.2) return 0.1337;
	else if(SCeta >2.0) return 0.0727;
	else if(SCeta >1.3) return  0.0632;
	else if(SCeta >0.8) return 0.0954;
	else return 0.0973;
    }
    else{ //else 25ns
	if(SCeta >2.4) return 0.2687;
	else if(SCeta >2.3) return 0.2243;
	else if(SCeta >2.2) return 0.1903;
	else if(SCeta >2.0) return 0.1534;
	else if(SCeta >1.479) return 0.1411;
	else if(SCeta >1.0) return 0.1862;
	else return 0.1752;
    }
}//end AreaEff

double RelIso_w_EA(
	double PF_chargedHadronIso,
	double PF_neutralHadronIso,
	double PF_photonIso,
	double PF_PUIso,
	double Pt,
	double SCeta,
	bool T50ns_F25ns){
    //relative isolation with effective area. 
    //see https://indico.cern.ch/event/369235/contribution/4/attachments/734635/1007867/Rami_EffAreas.pdf
    //PF_PUIso may be the same thing as rho, I'm following the lead in DileptonEventSelector.cc
    //to be used with the electron cut fucntions below 
    return ( PF_chargedHadronIso + _max(0.0, PF_neutralHadronIso + PF_photonIso - PF_PUIso*AreaEff(SCeta,T50ns_F25ns)) ) / Pt;
}//end RelIso_w_EA

bool is_tight_ele_2015(
	bool T50ns_F25ns,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float RelIso_w_EA,
	float Einv_m_Pinv,
	float D0,
	float DZ,
	int MHits,
	bool VtxFitConv){
    //T50ns_F25ns = true, use 50ns selection, else use 25ns selection
    //from https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Working_points_for_Spring15_MC_s
    if(!VtxFitConv) return false; //if not pass conversion veto.
    if(T50ns_F25ns){ //50ns
	if(is_bar_ele(SCEta)){
	    return elSihih   < 0.0101 &&
		Deta_SC_TrkAtVtx < 0.00864 &&
		Dphi_SC_TrkAtVtx < 0.0286 &&
		HoverE < 0.0342 &&
		RelIso_w_EA < 0.0591 &&
		Einv_m_Pinv < 0.0116 &&
		fabs(D0) < 0.0103 &&
		fabs(DZ) < 0.170 &&
		MHits <= 2;
	} //end bar
	else if(is_ec_ele(SCEta)){//EC
	    return elSihih   < 0.0287 &&
		Deta_SC_TrkAtVtx < 0.00762 &&
		Dphi_SC_TrkAtVtx < 0.0439 &&
		HoverE < 0.0544 &&
		RelIso_w_EA < 0.0759 &&
		Einv_m_Pinv < 0.01 &&
		fabs(D0) < 0.0377 &&
		fabs(DZ) < 0.571 &&
		MHits <= 1;
	}//end EC
	else return false;
    }//end 50ns 
    else{ //25ns
	if(is_bar_ele(SCEta)){
	    return elSihih   < 0.0101 &&
		Deta_SC_TrkAtVtx < 0.00926 &&
		Dphi_SC_TrkAtVtx < 0.0336 &&
		HoverE < 0.0597 &&
		RelIso_w_EA < 0.0354 &&
		Einv_m_Pinv < 0.012 &&
		fabs(D0) < 0.0111 &&
		fabs(DZ) < 0.0466 &&
		MHits <= 2;
	}//end bar
	else if(is_ec_ele(SCEta)){//EC
	    return elSihih   < 0.0279 &&
		Deta_SC_TrkAtVtx < 0.00724 &&
		Dphi_SC_TrkAtVtx < 0.0918 &&
		HoverE < 0.0615 &&
		RelIso_w_EA < 0.0646 &&
		Einv_m_Pinv < 0.00999 &&
		fabs(D0) < 0.0351 &&
		fabs(DZ) < 0.417 &&
		MHits <= 1;
	}//end EC
	else return false;
    }//end 25ns
}//end is_tight_ele_2015

bool is_medium_ele_2015(
	bool T50ns_F25ns,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float RelIso_w_EA,
	float Einv_m_Pinv,
	float D0,
	float DZ,
	int MHits,
	bool VtxFitConv){
    //T50ns_F25ns = true, use 50ns selection, else use 25ns selection
    //from https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Working_points_for_Spring15_MC_s
    if(!VtxFitConv) return false; //if not pass conversion veto.
    if(T50ns_F25ns){ //50ns
	if(is_bar_ele(SCEta)){
	    return elSihih   < 0.0101 &&
		Deta_SC_TrkAtVtx < 0.0094 &&
		Dphi_SC_TrkAtVtx < 0.0296 &&
		HoverE < 0.0372 &&
		RelIso_w_EA < 0.0987 &&
		Einv_m_Pinv < 0.118 &&
		fabs(D0) < 0.0151 &&
		fabs(DZ) < 0.238 &&
		MHits <= 2;
	} //end bar
	else if(is_ec_ele(SCEta)){//EC
	    return elSihih   < 0.0287 &&
		Deta_SC_TrkAtVtx < 0.00773 &&
		Dphi_SC_TrkAtVtx < 0.148 &&
		HoverE < 0.0546 &&
		RelIso_w_EA < 0.0902 &&
		Einv_m_Pinv < 0.104 &&
		fabs(D0) < 0.0535 &&
		fabs(DZ) < 0.572 &&
		MHits <= 1;
	}//end EC
	else return false;
    }//end 50ns 
    else{ //25ns
	if(is_bar_ele(SCEta)){
	    return elSihih   < 0.0101 &&
		Deta_SC_TrkAtVtx < 0.0103 &&
		Dphi_SC_TrkAtVtx < 0.0336 &&
		HoverE < 0.0876 &&
		RelIso_w_EA < 0.0766 &&
		Einv_m_Pinv < 0.0174 &&
		fabs(D0) < 0.0118 &&
		fabs(DZ) < 0.373 &&
		MHits <= 2;
	}//end bar
	else if(is_ec_ele(SCEta)){//EC
	    return elSihih   < 0.0283 &&
		Deta_SC_TrkAtVtx < 0.00733 &&
		Dphi_SC_TrkAtVtx < 0.114 &&
		HoverE < 0.0678 &&
		RelIso_w_EA < 0.0678 &&
		Einv_m_Pinv < 0.0898 &&
		fabs(D0) < 0.0739 &&
		fabs(DZ) < 0.602 &&
		MHits <= 1;
	}//end EC
	else return false;
    }//end 25ns
}//end is_medium_ele_2015

bool is_loose_ele_2015(
	bool T50ns_F25ns,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float RelIso_w_EA,
	float Einv_m_Pinv,
	float D0,
	float DZ,
	int MHits,
	bool VtxFitConv){
    //T50ns_F25ns = true, use 50ns selection, else use 25ns selection
    //from https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Working_points_for_Spring15_MC_s
    if(!VtxFitConv) return false; //if not pass conversion veto.
    if(T50ns_F25ns){ //50ns
	if(is_bar_ele(SCEta)){
	    return elSihih   < 0.0105 &&
		Deta_SC_TrkAtVtx < 0.00976 &&
		Dphi_SC_TrkAtVtx < 0.0929 &&
		HoverE < 0.0765 &&
		RelIso_w_EA < 0.118 &&
		Einv_m_Pinv < 0.184 &&
		fabs(D0) < 0.0227 &&
		fabs(DZ) < 0.379 &&
		MHits <= 2;
	} //end bar
	else if(is_ec_ele(SCEta)){//EC
	    return elSihih   < 0.0318 &&
		Deta_SC_TrkAtVtx < 0.00952 &&
		Dphi_SC_TrkAtVtx < 0.181 &&
		HoverE < 0.0824 &&
		RelIso_w_EA < 0.118 &&
		Einv_m_Pinv < 0.125 &&
		fabs(D0) < 0.242 &&
		fabs(DZ) < 0.921 &&
		MHits <= 1;
	}//end EC
	else return false;
    }//end 50ns 
    else{ //25ns
	if(is_bar_ele(SCEta)){
	    return elSihih   < 0.0103 &&
		Deta_SC_TrkAtVtx < 0.0105 &&
		Dphi_SC_TrkAtVtx < 0.115 &&
		HoverE < 0.104 &&
		RelIso_w_EA < 0.0893 &&
		Einv_m_Pinv < 0.102 &&
		fabs(D0) < 0.0261 &&
		fabs(DZ) < 0.41 &&
		MHits <= 2;
	}//end bar
	else if(is_ec_ele(SCEta)){//EC
	    return elSihih   < 0.0301 &&
		Deta_SC_TrkAtVtx < 0.00814 &&
		Dphi_SC_TrkAtVtx < 0.182 &&
		HoverE < 0.182 &&
		RelIso_w_EA < 0.121 &&
		Einv_m_Pinv < 0.126 &&
		fabs(D0) < 0.118 &&
		fabs(DZ) < 0.822 &&
		MHits <= 1;
	}//end EC
	else return false;
    }//end 25ns
}//end is_loose_ele_2015

bool is_veto_ele_2015(
	bool T50ns_F25ns,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float RelIso_w_EA,
	float Einv_m_Pinv,
	float D0,
	float DZ,
	int MHits,
	bool VtxFitConv){
    //T50ns_F25ns = true, use 50ns selection, else use 25ns selection
    //from https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Working_points_for_Spring15_MC_s
    if(!VtxFitConv) return false; //if not pass conversion veto.
    if(T50ns_F25ns){ //50ns
	if(is_bar_ele(SCEta)){
	    return elSihih   < 0.012 &&
		Deta_SC_TrkAtVtx < 0.0126 &&
		Dphi_SC_TrkAtVtx < 0.107 &&
		HoverE < 0.186 &&
		RelIso_w_EA < 0.161 &&
		Einv_m_Pinv < 0.239 &&
		fabs(D0) < 0.0621 &&
		fabs(DZ) < 0.613 &&
		MHits <= 2;
	} //end bar
	else if(is_ec_ele(SCEta)){//EC
	    return elSihih   < 0.0339 &&
		Deta_SC_TrkAtVtx < 0.0109 &&
		Dphi_SC_TrkAtVtx < 0.219 &&
		HoverE < 0.0962 &&
		RelIso_w_EA < 0.193 &&
		Einv_m_Pinv < 0.141 &&
		fabs(D0) < 0.279 &&
		fabs(DZ) < 0.947 &&
		MHits <= 3;
	}//end EC
	else return false;
    }//end 50ns 
    else{ //25ns
	if(is_bar_ele(SCEta)){
	    return elSihih   < 0.0114 &&
		Deta_SC_TrkAtVtx < 0.0152 &&
		Dphi_SC_TrkAtVtx < 0.216 &&
		HoverE < 0.181 &&
		RelIso_w_EA < 0.126 &&
		Einv_m_Pinv < 0.207 &&
		fabs(D0) < 0.0564 &&
		fabs(DZ) < 0.472 &&
		MHits <= 2;
	}//end bar
	else if(is_ec_ele(SCEta)){//EC
	    return elSihih   < 0.0352 &&
		Deta_SC_TrkAtVtx < 0.0113 &&
		Dphi_SC_TrkAtVtx < 0.237 &&
		HoverE < 0.116 &&
		RelIso_w_EA < 0.144 &&
		Einv_m_Pinv < 0.174 &&
		fabs(D0) < 0.222 &&
		fabs(DZ) < 0.921 &&
		MHits <= 3;
	}//end EC
	else return false;
    }//end 25ns
}//end is_veto_ele_2015


bool is_loose_ele_2015_MVA_nontrig( float pt, float SCEta, float MVAvalue, float eleMiniIso){
	//see https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2#Non_triggering_electron_MVA_deta
    //As is, this is defined only for 25ns and pt > 5 GeV
    if(eleMiniIso > 0.4) return false;

    SCEta = fabs(SCEta);
    if(pt>10){
	if(SCEta<0.8) return MVAvalue > 0.913286;
	else if(is_bar_ele(SCEta)) return MVAvalue > 0.805013;
	else if(is_ec_ele(SCEta)) return MVAvalue > 0.358969;
	else return false;
    }
    else if(pt<5) return false;
    else{ //ele pt between 5 and 10 GeV
	if(SCEta<0.8) return MVAvalue > -0.083313;
	else if(is_bar_ele(SCEta)) return MVAvalue > -0.235222;
	else if(is_ec_ele(SCEta)) return MVAvalue > -0.67099;
	else return false;
    }
}//end is_loose_ele_2015_MVA_nontrig

bool is_tight_ele_2015_MVA_nontrig( float pt, float SCEta, float MVAvalue, float eleMiniIso){
	//see https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2#Non_triggering_electron_MVA_deta
    //As is, this is defined only for 25ns and pt > 5 GeV
    if(eleMiniIso > 0.1) return false;

    SCEta = fabs(SCEta);
    if(pt>10){
	if(SCEta<0.8) return MVAvalue > 0.967083;
	else if(is_bar_ele(SCEta)) return MVAvalue > 0.929117;
	else if(is_ec_ele(SCEta)) return MVAvalue > 0.726311;
	else return false;
    }
    else if(pt<5) return false;
    else{ //ele pt between 5 and 10 GeV
	if(SCEta<0.8) return MVAvalue > 0.287435;
	else if(is_bar_ele(SCEta)) return MVAvalue > 0.221846;
	else if(is_ec_ele(SCEta)) return MVAvalue > -0.303263;
	else return false;
    }
}

bool is_tight_ele_2015_MVA_trig( 
	float MVAvalue,
	bool T50ns_F25ns,
	float pt,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float EcalRelIso,
	float HcalRelIso,
	float Track03RelIso){
    //80% efficiency working point
    return is_ele_2015_MVA_trig_preselection(
	    T50ns_F25ns,
	    pt,
	    SCEta,
	    elSihih,
	    Deta_SC_TrkAtVtx,
	    Dphi_SC_TrkAtVtx,
	    HoverE,
	    EcalRelIso,
	    HcalRelIso,
	    Track03RelIso) &&
	is_tight_ele_2015_MVA_trig_mvaonly( MVAvalue, T50ns_F25ns, SCEta);

}
bool is_tight_ele_2015_MVA_trig_mvaonly( float MVAvalue, bool T50ns_F25ns, float SCEta){
    //80% efficiency working point
    SCEta = fabs(SCEta);
    if(T50ns_F25ns){ //50ns
	if(SCEta<0.8) return MVAvalue > 0.981841;
	else if(is_bar_ele(SCEta)) return MVAvalue > 0.946762;
	else if(is_ec_ele(SCEta)) return MVAvalue > 0.797040;
	else return false;
    }
    else{ //25 ns
	if(SCEta<0.8) return MVAvalue > 0.988153;
	else if(is_bar_ele(SCEta)) return MVAvalue > 0.967910;
	else if(is_ec_ele(SCEta)) return MVAvalue > 0.841729;
	else return false;
    }
}

bool is_loose_ele_2015_MVA_trig(
	float MVAvalue,
	bool T50ns_F25ns,
	float pt,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float EcalRelIso,
	float HcalRelIso,
	float Track03RelIso){
    //90% efficiency working point
    return is_ele_2015_MVA_trig_preselection(
	    T50ns_F25ns,
	    pt,
	    SCEta,
	    elSihih,
	    Deta_SC_TrkAtVtx,
	    Dphi_SC_TrkAtVtx,
	    HoverE,
	    EcalRelIso,
	    HcalRelIso,
	    Track03RelIso) &&
	is_loose_ele_2015_MVA_trig_mvaonly( MVAvalue, T50ns_F25ns, SCEta);
}
bool is_loose_ele_2015_MVA_trig_mvaonly( //this is not the full selection, don't run this alone. 
	float MVAvalue,
	bool T50ns_F25ns,
	float SCEta){
    //90% efficiency working point
    SCEta = fabs(SCEta);
    if(T50ns_F25ns){ //50ns
	if(SCEta<0.8) return MVAvalue > 0.953843;
	else if(is_bar_ele(SCEta)) return MVAvalue > 0.849994;
	else if(is_ec_ele(SCEta)) return MVAvalue > 0.514118;
	else return false;
    }
    else{ //25 ns
	if(SCEta<0.8) return MVAvalue > 0.972153;
	else if(is_bar_ele(SCEta)) return MVAvalue > 0.922126;
	else if(is_ec_ele(SCEta)) return MVAvalue > 0.610764;
	else return false;
    }
}

bool is_ele_2015_MVA_trig_preselection(
	bool T50ns_F25ns,
	float pt,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float EcalRelIso,
	float HcalRelIso,
	float Track03RelIso){
    if(!(pt>15 &&
		HoverE < 0.09 &&
		Track03RelIso < 0.18)) return false;

    if(is_bar_ele(SCEta)){
	return elSihih < 0.012 &&
	    HoverE < 0.09 &&
	    EcalRelIso < 0.37 &&
	    HcalRelIso < 0.25 &&
	    Track03RelIso < 0.18 && 
	    (T50ns_F25ns || 
	     (Deta_SC_TrkAtVtx < 0.0095 &&  //only do these two in 25ns barrel
	      Dphi_SC_TrkAtVtx < 0.065));
    } //end bar
    else if(is_ec_ele(SCEta)){//EC
	return elSihih < 0.033 &&
	    HoverE < 0.09 &&
	    EcalRelIso < 0.45 &&
	    HcalRelIso < 0.28 &&
	    Track03RelIso < 0.18;
    }//end EC
    else return false;
}


//These are implemntations of the cuts listed on this twiki: https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2
//what is the use case? 
//so you want to implement all four and get an int back? Do you want to get a nice clear bool back? 

/*
   float MCsmear(float eta, float r9,TRandom* r){
//returns a random value for the MCsmearing scale factor. 
//these values come out of combineSmearing.C and are done with mst_185_mhiggsino_150 on fast sim and fullsim. 
//you need to give it a TRandom* so that you don't generate the same seed every time it's called 
//setup with TRandom *r = new TRandom();
float sigma;
eta = fabs(eta);
////////////////////////this block is generated automatically by combineSmearing.C

if(is_bar_ele(eta)){
if(eta < 1){
if(r9>0.94) sigma = 0.009213;
else sigma = 0.010046;
}
else{
if(r9>0.94) sigma = 0.016318;
else sigma = 0.017477;
}
}
else{ //ec
if(eta < 2){
if(r9>0.94) sigma = 0.029787;
else sigma = 0.029989;
}
else{
if(r9>0.94) sigma = 0.034883;
else sigma = 0.024528;
}
}

//////////////////////
//TRandom r;
return r->Gaus(1,sigma);
}

float MCsmear_fullsim(float eta, float r9,TRandom* r){

//returns a random value for the MCsmearing scale factor. 
//These are the smearing factors from the higgs analysis and are to be used only on Fullsim
//you need to give it a TRandom* so that you don't generate the same seed every time it's called 
//setup with TRandom *r = new TRandom();
float sigma;
eta = fabs(eta);

if(is_bar_ele(eta)){
if(eta < 1){
if(r9>0.94) sigma = 0.0113;
else sigma = 0.0109;
}
else{
if(r9>0.94) sigma = 0.0171;
else sigma = 0.0203;
}
}
else{ //ec
if(eta < 2){
if(r9>0.94) sigma = 0.0309;
else sigma = 0.0278;
}
else{
if(r9>0.94) sigma = 0.0372;
else sigma = 0.0375;
}
}

return r->Gaus(1,sigma);
}//end MCsmear_fullsim
*/

int ele_ID_level_2015(
	bool T50ns_F25ns,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float RelIso_w_EA,
	float Einv_m_Pinv,
	float D0,
	float DZ,
	int MHits,
	bool VtxFitConv){

    //returns the tightest workingpoint the electron reaches. 0 = junk, 1 = veto, 2 = loost, 3 = medium, 4 = tight. 
    int ID_level = 0;
    if(is_veto_ele_2015( T50ns_F25ns, SCEta, elSihih, Deta_SC_TrkAtVtx, Dphi_SC_TrkAtVtx, 
		HoverE, RelIso_w_EA, Einv_m_Pinv, D0, DZ, MHits, VtxFitConv))
    {
	ID_level = 1;
	if(is_loose_ele_2015( T50ns_F25ns, SCEta, elSihih, Deta_SC_TrkAtVtx, Dphi_SC_TrkAtVtx, 
		    HoverE, RelIso_w_EA, Einv_m_Pinv, D0, DZ, MHits, VtxFitConv))
	{
	    ID_level = 2;
	    if(is_medium_ele_2015( T50ns_F25ns, SCEta, elSihih, Deta_SC_TrkAtVtx, Dphi_SC_TrkAtVtx,
			HoverE, RelIso_w_EA, Einv_m_Pinv, D0, DZ, MHits, VtxFitConv))
	    {
		ID_level = 3;
		if(is_tight_ele_2015( T50ns_F25ns, SCEta, elSihih, Deta_SC_TrkAtVtx, Dphi_SC_TrkAtVtx, 
			    HoverE, RelIso_w_EA, Einv_m_Pinv, D0, DZ, MHits, VtxFitConv))
		{
		    ID_level = 4;
		}
	    }
	}
    }
    return ID_level;
}//end EleIDlevel 

int ele_ID_level_2015_MVA_nontrig( float pt, float SCEta, float MVAvalue, float eleMiniIso){
    //returns the tightest workingpoint the electron reaches. convention:  0 = junk, 1 = veto, 2 = loost, 3 = medium, 4 = tight. 
    int ID_level = 0;
    if( is_loose_ele_2015_MVA_nontrig( pt, SCEta, MVAvalue, eleMiniIso)){
	ID_level = 2;
	if(is_tight_ele_2015_MVA_nontrig( pt, SCEta, MVAvalue, eleMiniIso)) ID_level = 4;
    }

    return ID_level;
}//end EleIDlevel 

int ele_ID_level_2015_MVA_trig( 
	float MVAvalue,
	bool T50ns_F25ns,
	float pt,
	float SCEta,
	float elSihih,
	float Deta_SC_TrkAtVtx,
	float Dphi_SC_TrkAtVtx,
	float HoverE,
	float EcalRelIso,
	float HcalRelIso,
	float Track03RelIso){
    //returns the tightest workingpoint the electron reaches. convention:  0 = junk, 1 = veto, 2 = loost, 3 = medium, 4 = tight. 
    int ID_level = 0;
    bool pre = is_ele_2015_MVA_trig_preselection(
	    T50ns_F25ns,
	    pt,
	    SCEta,
	    elSihih,
	    Deta_SC_TrkAtVtx,
	    Dphi_SC_TrkAtVtx,
	    HoverE,
	    EcalRelIso,
	    HcalRelIso,
	    Track03RelIso);
    if( pre && is_loose_ele_2015_MVA_trig_mvaonly( MVAvalue, T50ns_F25ns, SCEta)){
	ID_level = 2;
	if( pre && is_tight_ele_2015_MVA_trig_mvaonly( MVAvalue, T50ns_F25ns, SCEta)) ID_level = 4;
    }

    return ID_level;
}//end ele_ID_level_2015_MVA_trig 

/*
//this has been moved to fakerate.h
//from AN-15-148 v4 sections 5.2.1 and 5.2.2; see Figure 12 for evidence that the fake rates are pt independent. 
inline float pe(){return 0.87;}  //ele prompt rate
inline float upe(){return 0.005;}  //ele prompt rate

inline float fe(){return 0.288;} //ele fake rate = 0.288 +- 0.009
inline float ufe(){return 0.009;} //ele fake rate = 0.288 +- 0.009

inline float pm(){return 0.94;}  //muon prompt rate
inline float upm(){return 0.005;}  //muon prompt rate

inline float fm(){return 0.347;} //muon fake rate= 0.347 +- 0.005
inline float ufm(){return 0.005;} //muon fake rate= 0.347 +- 0.005

float eleChargeMisIDRate(float eta, float pt){
    static const int nranges = 15;
    static const std::vector<float> etaRange = {-3.0, -2.6, -2.2, -1.8, -1.4, -1.0, -0.6, -0.2, 0.2, 0.6, 1.0, 1.4, 1.8, 2.2, 2.6, 3.0};//ranges+1 of these

    //from AN-15-148 v4 tables 8 and 9
    static const float lowPtQgMissID[nranges ] = {0.00000, 0.00304, 0.00303, 0.00234, 0.0009, 0.00052, 0.00034, 0.00031, 0.00030, 0.00053, 0.00081, 0.00269, 0.00297, 0.00327, 0.00000};//nrange of these

    static const float hiPtQgMissID[nranges ] = {0.00000, 0.02734, 0.0131, 0.01792, 0.00998, 0.00309, 0.00265, 0.00397, 0.00209, 0.00202, 0.00654, 0.01380, 0.01306, 0.01550, 0.00000};//nrange of these

    int bin = btreeSearch(eta, etaRange);
    if(bin < 0) return 0.0;
    if(pt < 100) return lowPtQgMissID[bin];
    else return hiPtQgMissID[bin];

}//end eleChargeMisIDRate


int btreeSearch(float x, std::vector<float>ranges){
    //return i such that ranges[i] <= x < ranges[i+1];
    //assumes range is sorted from low to high.
    //compexity ln_2(size(range));
    //if x<ranes[0] return -2
    //if x >= ranges.back  return -1

    if(x < ranges[0]) return -2;	
    int high = ranges.size()-1;
    if(x >= ranges[high]) return -1; 
    int low = 0;
    int mid = (high - low)/2;
    while(low < high - 1 ){
	if(x < ranges[mid]) high = mid;
	else low = mid;
	mid = (high - low)/2 + low;
    }//end while
    return low;
}//btreeSearch

int btreeSearch(float x, float ranges[], int size){
    //return i such that ranges[i] <= x < ranges[i+1];
    //assumes range is sorted from low to high.
    //compexity ln_2(size(range));
    //if x<ranes[0] return -2
    //if x >= ranges.back  return -1

    if(x < ranges[0]) return -2;	
    int high = size-1;
    if(x >= ranges[high]) return -1; 
    int low = 0;
    int mid = (high - low)/2;
    while(low < high - 1 ){
	if(x < ranges[mid]) high = mid;
	else low = mid;
	mid = (high - low)/2 + low;
    }//end while
    return low;
}//btreeSearch
*/

float Get_Muon_Mini_Iso_SF(float leppt, float lepeta){
    //Mini-iso < 0.2 SFs from SUSY TWiki
    float isosf = 1.f;
    lepeta = fabs(lepeta);
    if(leppt<40){
	if(lepeta < 0.9) {isosf= 1.000; }
	else if(lepeta< 1.2) {isosf= 1.000; }
	else if(lepeta< 2.1) {isosf= 0.999; }
	else if(lepeta< 2.4) {isosf= 0.999; }
    }
    else if(leppt<50){
	if(lepeta < 0.9) {isosf= 1.000; }
	else if(lepeta< 1.2) {isosf= 1.000; }
	else if(lepeta< 2.1) {isosf= 0.999; }
	else if(lepeta< 2.4) {isosf= 1.000; }
    }
    else if(leppt<60){
	if(lepeta < 0.9) {isosf= 1.000; }
	else if(lepeta< 1.2) {isosf= 1.000; }
	else if(lepeta< 2.1) {isosf= 1.000; }
	else if(lepeta< 2.4) {isosf= 1.000; }
    }
    else{
	if(lepeta < 0.9) {isosf= 1.000; }
	else if(lepeta< 1.2) {isosf= 0.999; }
	else if(lepeta< 2.1) {isosf= 0.998; }
	else if(lepeta< 2.4) {isosf= 1.000; }
    }
    return isosf;
}//end Get_Muon_Mini_Iso_SF

float Get_Ele_Mini_Iso_SF(float leppt, float lepeta){
    //miniIso < 0.1 scale factors from https://indico.cern.ch/event/370512/contribution/1/attachments/1176496/1701148/2015_10_26_tnp.pdf
    float isosf = 1.f;
    if(leppt<=10) return isosf;
    lepeta = fabs(lepeta);
    if(lepeta<1.442){
	if(leppt<20) {isosf = 0.979; }// +/-0.004 
	else if(leppt<30) {isosf = 0.988; }// +/-0.002
	else if(leppt<40) {isosf = 0.995; }// +/-0.022
	else if(leppt<50) {isosf = 0.995; }// +/-0.011
	else if(leppt<200) {isosf = 0.995; }// +/-0.000
    }
    else if(lepeta<1.566){
	if(leppt<20) {isosf = 0.909; }// +/-0.05 
	else if(leppt<30) {isosf = 0.982; }// +/-0.014
	else if(leppt<40) {isosf = 1.001; }// +/-0.006
	else if(leppt<50) {isosf = 0.993; }// +/-0.007
	else if(leppt<200) {isosf = 0.988; }// +/-0.014
    }
    else if(lepeta<2.5){
	if(leppt<20) {isosf = 0.984; }// +/-0.011
	else if(leppt<30) {isosf = 0.997; }// +/-0.002
	else if(leppt<40) {isosf = 1.000; }// +/-0.001
	else if(leppt<50) {isosf = 1.019; }// +/-0.002
	else if(leppt<200) {isosf = 1.000; }// +/-0.002
    }
    //else {isosf = 1.; }
    return isosf;
}//end Get_Ele_Mini_Iso_SF

float Get_Muon_MVA_ID_SF(float leppt, float lepeta){
    //Cut-based ID scale factors from Clint Richardson 
    //https://indico.cern.ch/event/459111/contribution/1/attachments/1180755/1709309/B2G_Meeting_11.03.2015.pdf
    float lepidsf = 1.f;
    if(leppt<30.0) return lepidsf;
    if(lepeta>=-2.4 && lepeta<-2.1){
	if(leppt<40.0000) {lepidsf= 0.9812; }
	else if(leppt<60.0000) {lepidsf= 0.9793; } 
	else if(leppt<100.0000) {lepidsf= 0.9600; } 
	else if(leppt<1000.0000) {lepidsf= 0.9738; }
    } 
    else if(lepeta<-1.2){
	if(leppt<40.0000) {lepidsf= 0.9910; } 
	else if(leppt<60.0000) {lepidsf= 0.9922; } 
	else if(leppt<100.0000) {lepidsf= 0.9923; }
	else if(leppt<1000.0000) {lepidsf= 1.0039; }
    }
    else if(lepeta<-0.9){ 
	if(leppt<40.0000) {lepidsf= 0.9828; } 
	else if(leppt<60.0000) {lepidsf= 0.9886; } 
	else if(leppt<100.0000) {lepidsf= 0.9873; } 
	else if(leppt<1000.0000) {lepidsf= 0.9876; }
    }
    else if(lepeta<-0.4){ 
	if(leppt<40.0000) {lepidsf= 0.9909; } 
	else if(leppt<60.0000) {lepidsf= 0.9920; } 
	else if(leppt<100.0000) {lepidsf= 0.9854; } 
	else if(leppt<1000.0000) {lepidsf= 0.9951; }
    }
    else if(lepeta<0.0){ 
	if(leppt<40.0000) {lepidsf= 0.9878; } 
	else if(leppt<60.0000) {lepidsf= 0.9874; } 
	else if(leppt<100.0000) {lepidsf= 0.9885; } 
	else if(leppt<1000.0000) {lepidsf= 0.9985; }
    }
    else if(lepeta<0.4){
	if(leppt<40.0000) {lepidsf= 0.9847; } 
	else if(leppt<60.0000) {lepidsf= 0.9877; } 
	else if(leppt<100.0000) {lepidsf= 0.9896; } 
	else if(leppt<1000.0000) {lepidsf= 1.0165; }
    }
    else if(lepeta<0.9){ 
	if(leppt<40.0000) {lepidsf= 0.9869; } 
	else if(leppt<60.0000) {lepidsf= 0.9898; } 
	else if(leppt<100.0000) {lepidsf= 0.9875; } 
	else if(leppt<1000.0000) {lepidsf= 0.9754; }
    }
    else if(lepeta<1.2){ 
	if(leppt<40.0000) {lepidsf= 0.9724; } 
	else if(leppt<60.0000) {lepidsf= 0.9746; } 
	else if(leppt<100.0000) {lepidsf= 0.9696; } 
	else if(leppt<1000.0000) {lepidsf= 0.9757; }
    }
    else if(lepeta<2.1){ 
	if(leppt<40.0000) {lepidsf= 0.9929; } 
	else if(leppt<60.0000) {lepidsf= 0.9947; } 
	else if(leppt<100.0000) {lepidsf= 0.9929; } 
	else if(leppt<1000.0000) {lepidsf= 0.9987; }
    }
    else if(lepeta<2.4){ 
	if(leppt<40.0000) {lepidsf= 0.9818; } 
	else if(leppt<60.0000) {lepidsf= 0.9851; } 
	else if(leppt<100.0000) {lepidsf= 0.9724; } 
	else if(leppt<1000.0000) {lepidsf= 1.0028; }
    }
    //else{lepidsf= 1.0; } 
    return lepidsf;
}//end Get_Muon_MVA_ID_SF

float Get_Ele_MVA_ID_SF(float leppt, float lepeta){
    float lepidsf =1.f;
    if(leppt<30.0) return lepidsf;

    if(lepeta>=-2.5 && lepeta<-1.6){
	if(leppt<40.0000) {lepidsf= 0.9880; }
	else if(leppt<50.0000) {lepidsf= 0.9663; } 
	else if(leppt<70.0000) {lepidsf= 0.9884; }
	else if(leppt<90.0000) {lepidsf= 0.9762; } 
	else if(leppt<130.0000) {lepidsf= 0.9727; } 
	else if(leppt<180.0000) {lepidsf= 0.9978; } 
	else if(leppt<250.0000) {lepidsf= 0.9118; }
	else if(leppt<1000.0000) {lepidsf= 0.9205; }
    } 
    else if(lepeta<-1.4){
	if(leppt<40.0000) {lepidsf= 0.9788; } 
	else if(leppt<50.0000) {lepidsf= 0.9821; } 
	else if(leppt<70.0000) {lepidsf= 0.9567; } 
	else if(leppt<90.0000) {lepidsf= 0.9926; } 
	else if(leppt<130.0000) {lepidsf= 0.9889; } 
	else if(leppt<180.0000) {lepidsf= 1.0034; } 
	else if(leppt<250.0000) {lepidsf= 1.1316; } 
	else if(leppt<1000.0000) {lepidsf= 1.0000; }
    }
    else if(lepeta<-0.8){
	if(leppt<40.0000) {lepidsf= 0.9945; }
	else if(leppt<50.0000) {lepidsf= 0.9849; } 
	else if(leppt<70.0000) {lepidsf= 0.9944; }
	else if(leppt<90.0000) {lepidsf= 1.0008; } 
	else if(leppt<130.0000) {lepidsf= 1.0077; } 
	else if(leppt<180.0000) {lepidsf= 0.9915; } 
	else if(leppt<250.0000) {lepidsf= 0.9556; } 
	else if(leppt<1000.0000) {lepidsf= 0.9274; }
    } 
    else if(lepeta<0.0){
	if(leppt<40.0000) {lepidsf= 0.9923; } 
	else if(leppt<50.0000) {lepidsf= 0.9794; } 
	else if(leppt<70.0000) {lepidsf= 0.9887; } 
	else if(leppt<90.0000) {lepidsf= 0.9742; } 
	else if(leppt<130.0000) {lepidsf= 0.9611; } 
	else if(leppt<180.0000) {lepidsf= 1.0176; } 
	else if(leppt<250.0000) {lepidsf= 0.9990; } 
	else if(leppt<1000.0000) {lepidsf= 0.9677; }
    } 
    else if(lepeta<0.8){
	if(leppt<40.0000) {lepidsf= 0.9990; } 
	else if(leppt<50.0000) {lepidsf= 0.9808; } 
	else if(leppt<70.0000) {lepidsf= 0.9657; } 
	else if(leppt<90.0000) {lepidsf= 0.9963; } 
	else if(leppt<130.0000) {lepidsf= 0.9963; } 
	else if(leppt<180.0000) {lepidsf= 0.9725; } 
	else if(leppt<250.0000) {lepidsf= 0.9769; } 
	else if(leppt<1000.0000) {lepidsf= 0.9334; }
    } 
    else if(lepeta<1.4){
	if(leppt<40.0000) {lepidsf= 0.9934; } 
	else if(leppt<50.0000) {lepidsf= 0.9814; } 
	else if(leppt<70.0000) {lepidsf= 0.9871; } 
	else if(leppt<90.0000) {lepidsf= 0.9846; } 
	else if(leppt<130.0000) {lepidsf= 0.9545; } 
	else if(leppt<180.0000) {lepidsf= 1.0141; } 
	else if(leppt<250.0000) {lepidsf= 0.9824; } 
	else if(leppt<1000.0000) {lepidsf= 0.9443; }
    } 
    else if(lepeta<1.6){
	if(leppt<40.0000) {lepidsf= 0.9771; } 
	else if(leppt<50.0000) {lepidsf= 0.9796; } 
	else if(leppt<70.0000) {lepidsf= 0.9811; } 
	else if(leppt<90.0000) {lepidsf= 1.0291; } 
	else if(leppt<130.0000) {lepidsf= 0.9010; } 
	else if(leppt<180.0000) {lepidsf= 1.0490; } 
	else if(leppt<250.0000) {lepidsf= 0.6082; } 
	else if(leppt<1000.0000) {lepidsf= 1.1424; }
    } 
    else if(lepeta<2.5){
	if(leppt<40.0000) {lepidsf= 0.9746; } 
	else if(leppt<50.0000) {lepidsf= 0.9835; } 
	else if(leppt<70.0000) {lepidsf= 0.9868; } 
	else if(leppt<90.0000) {lepidsf= 0.9843; } 
	else if(leppt<130.0000) {lepidsf= 1.0039; } 
	else if(leppt<180.0000) {lepidsf= 0.9597; } 
	else if(leppt<250.0000) {lepidsf= 0.9987; } 
	else if(leppt<1000.0000) {lepidsf= 1.0271; }
    }
    //else{lepidsf= 1.0; }
    return lepidsf;
}//end Get_Ele_MVA_ID_SF

#endif
