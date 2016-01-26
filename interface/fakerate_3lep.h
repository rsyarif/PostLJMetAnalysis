#ifndef _FAKERATE_H
#define _FAKERATE_H
#include <TRandom2.h>
#include "Math/Random.h"
#include <iostream>
#include "interface/CMSStyle.C"

#include "TStyle.h"
#include "TColor.h"
#include <TH1F.h>
#include <TH2.h>
#include "TCanvas.h"

using namespace std;

float Pe(int mode = 0);
inline float uPe();
float Fe(int mode = 0);
inline float uFe();
float Pm(int mode = 0);
inline float uPm();
float Fm(int mode = 0);
inline float uFm();
inline float uQe();
inline double epsilon(double f);//these are guearenteed to be small numbers
inline double eta(double p);//these are guearenteed to be small numbers

inline int feModeBehavior(int mode);
inline int fmModeBehavior(int mode);
inline int peModeBehavior(int mode);
inline int pmModeBehavior(int mode);
inline int qeModeBehavior(int mode);

vector<double> optomizeFP_SFDL(int N_t0, int N_t1, int N_t2, bool ee);
TCanvas* exploreFP_SF(int N_t0, int N_t1, int N_t2);
TCanvas* exploreFP_SFint(int N_t0, int N_t1, int N_t2,int n_t0, int n_t1, int n_t2);

//float eleChargeMisIDRate(float eta, float pt);//this takes 7x longer to run than eleChargeMisIDRate_lin
float eleChargeMisIDRate_lin(float eta, float pt, int mode);//same as eleChargeMisIDRate except in edge cases. 
float eleChargeMisIDRate_lin_guts(float eta, float pt);

vector<double> SingleLepbkg(double f, double p, int N_t0, int N_t1); //output: {N_p, N_f, N_signal, N_bkg}
double SingleLepbkg_simple(double f, double p, int N_t0, int N_t1);

vector<double> SFDLbkg(double f, double p, int N_t0, int N_t1, int N_t2); //output: {0:N_pp, 1:N_fp, 2:N_ff, 3:N_signal, 4:N_1fake, 5:N_2fakes, 6:N_bkg}
double SFDLbkg_simple(double f, double p, int N_t0, int N_t1, int N_t2);
//double SFDLbkg_simpler(double f, double p, int N_t0, int N_t1, int N_t2);//broken! does not agree with SFDLbkg_simple.
//double SFDLbkg_simplest(double f, double p, int N_t0, int N_t1, int N_t2);//broken


vector<double> OFDLbkg(double fe, double fm, double pe, double pm, int N_t00, int N_t10, int N_t01, int N_t11);
	//output: {0:N_pp, 1:N_fp, 2:N_pf, 3:N_ff, 4:N_signal, 5:N_efakes, 6:N_mfakes, 7:N_bothfake, 8:N_bkg}
double OFDLbkg_simple(double fe, double fm, double pe, double pm, int N_t00, int N_t10, int N_t01, int N_t11);
double OFDLbkg_simpler(double fe, double fm, double pe, double pm, int N_t00, int N_t10, int N_t01, int N_t11);
double DilepNonPromptBkgUncertAll( int Nem_t00, int Nem_t10, int Nem_t01, int Nem_t11, int Nee_t0, int Nee_t1, int Nee_t2, int Nmm_t0, int Nmm_t1, int Nmm_t2, int ndice, int& seed);

vector<double> SF3Lepbkg(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3);
	//output: {0:N_ppp, 1:N_fpp, 2:N_ffp, 3:N_fff, 4:N_signal, 5:N_1fake, 6:N_2fakes, 7:N_3fakes, 8:N_bkg}
double SF3Lepbkg_simple(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3);

double ChiSquared(int k);
int ThrowPoissonFromMeasurement(TRandom2* r, int n);

///////////////////////coifs for SS emu////////////////////////////
double Wemss_llos(float elePt, float eleEta, int mode);
double Wemss_llss(float elePt, float eleEta,int mode );
double Wemss_ltos(float elePt, float eleEta,int mode );
double Wemss_ltss(float elePt, float eleEta,int mode );
double Wemss_tlos(float elePt, float eleEta,int mode );
double Wemss_tlss(float elePt, float eleEta,int mode );
double Wemss_ttos(float elePt, float eleEta,int mode );
double Wemss_ttss(float elePt, float eleEta,int mode );

double Wemos_llos(float elePt, float eleEta,int mode );
double Wemos_llss(float elePt, float eleEta,int mode );
double Wemos_ltos(float elePt, float eleEta,int mode );
double Wemos_ltss(float elePt, float eleEta,int mode );
double Wemos_tlos(float elePt, float eleEta,int mode );
double Wemos_tlss(float elePt, float eleEta,int mode );
double Wemos_ttos(float elePt, float eleEta,int mode );
double Wemos_ttss(float elePt, float eleEta,int mode );

inline double alpha(double q1,double q2);
inline double beta( double q1,double q2);
inline double Det_ee(double a, double b, double fe, double pe);
inline double Det_em(double fe, double pe, double fm, double pm, double q);
double Weess_llos(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode);
double Weess_llss(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode);
double Weess_tlos(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode);
double Weess_tlss(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode);
double Weess_ttos(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode);
double Weess_ttss(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode);

double Weeos_llos(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode);
double Weeos_llss(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode);
double Weeos_tlos(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode);
double Weeos_tlss(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode);
double Weeos_ttos(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode);
double Weeos_ttss(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode);

/////////////////////// coifs for mm //////////////////////////////
double Wmmss_ttss(int mode); //Nt2 //can serve as a test; ought to give the same thing as Wmmxs_ttxs
double Wmmss_tlss(int mode); //Nt1 //can serve as a test; ought to give the same thing as Wmmxs_ttxs
double Wmmss_llss(int mode); //Nt0 //can serve as a test; ought to give the same thing as Wmmxs_ttxs

double Wmmxs_ttxs(int mode); //Nt2
double Wmmxs_tlxs(int mode); //Nt1
double Wmmxs_llxs(int mode); //Nt0
double GetWeight_mmxs(int nTightMuons, int mode);

double GetWeight_emss(bool is_SSDL, bool ele_is_Tight, bool mu_is_Tight, float elePt, float eleEta,int mode);
double GetWeight_emos(bool is_SSDL, bool ele_is_Tight, bool mu_is_Tight, float elePt, float eleEta,int mode);
double GetWeight_eess(bool is_SSDL, bool ele1_is_Tight, bool ele2_is_Tight, float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode);
double GetWeight_eeos(bool is_SSDL, bool ele1_is_Tight, bool ele2_is_Tight, float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode);
double GetWeight_mmos(bool is_SSDL, int nTightMuons, int mode);
double GetWeight_mmss(bool is_SSDL, int nTightMuons, int mode);

/////////////////// Tripple electron ////////////////////////
double GetWeight_emm(int nTightEle, int nTightMu, int mode);
double GetWeight_eem(int nTightEle, int nTightMu, int mode);
double GetWeight_mmm(int nTightMu, int mode);
double GetWeight_eee(int nTightEle, int mode);

double Wemm_ttt(int mode );
double Wemm_tetmlm(int mode );
double Wemm_tmtmle(int mode );
double Wemm_tmlmle(int mode );
double Wemm_lmlmte(int mode );
double Wemm_lll(int mode );
double Weem_ttt(int mode );
double Weem_tmtele(int mode );
double Weem_tetelm(int mode );
double Weem_telelm(int mode );
double Weem_leletm(int mode );
double Weem_lll(int mode );
double Wmmm_ttt(int mode);
double Wmmm_llt(int mode);
double Wmmm_ltt(int mode);
double Wmmm_lll(int mode); 
double Weee_ttt(int mode);
double Weee_llt(int mode);
double Weee_ltt(int mode);
double Weee_lll(int mode); 
/////////////////////////////

//from AN-15-148 v4 sections 5.2.1 and 5.2.2; see Figure 12 for evidence that the fake rates are pt independent. 
float Pe(int mode){return 0.87 + uPe()*peModeBehavior(mode);}  //ele prompt rate
inline float uPe(){return 0.005;}  //ele prompt rate

float Fe(int mode){return 0.663 + uFm()*fmModeBehavior(mode);} //ele fake rate
inline float uFe(){return 0.009;} //ele fake rate = 0.663 +- 0.009

float Pm(int mode){return 0.94 + uPm()*pmModeBehavior(mode);} //mu prompt rate
inline float uPm(){return 0.05;}  //muon prompt rate

float Fm(int mode){return 0.887 + uFe()*feModeBehavior(mode);} //mu fake rate
inline float uFm(){return 0.005;} //muon fake rate= 0.887 +- 0.005

inline float uQe(){return 0.30;}//percent

inline double epsilon(double f){return f/(1.0-f);} 
inline double eta(double p){return (1.0-p)/p;}

/*float eleChargeMisIDRate(float eta, float pt){ //does the same job as eleChargeMisIDRate_lin but takes 7x longer to run 
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
*/
float eleChargeMisIDRate_lin(float eta, float pt, int mode){ 
	return eleChargeMisIDRate_lin_guts(eta,pt)*( 1.0+ qeModeBehavior(mode)*uQe() );
}

float eleChargeMisIDRate_lin_guts(float eta, float pt){ //needs testing xxx, make sure this does the same thing as the btree verions, but faster. 
	//returns the charge misID probability. This ought to do the same thing as eleChargeMisIDRate,
	//I'm writing it to see which will run faster. 
	bool lowpt = pt<100;
	//electrons are likely to be central so give them a short return path. 
	if(eta < -0.2){
		if(eta > -0.6) return lowpt?0.00034:0.00265;//-0.6 to -0.2
		else if(eta > -1.0) return lowpt?0.00052:0.00309;//-1.0 to -0.6
		else if(eta > -1.4) return lowpt?0.0009:0.00998;//-1.4 to -1.0
		else if(eta > -1.8) return lowpt?0.00234:0.01792;//-1.8 to -1.4
		else if(eta > -2.2) return lowpt?0.00303:0.0131;//-2.2 to -1.8
		else if(eta > -2.6) return lowpt?0.00304:0.02734;//-2.6 to -2.2
		else return lowpt?0.0:0.0;//-3.0 to -2.6  //probably should be using the -2.6 to -2.2 range. xxx
	}
	else{ //eta > -0.2
		if(eta < 0.2) return lowpt?0.00031:0.00397;//0.6 to 1.0
		else if(eta < 0.6) return lowpt?0.00030:0.00209;//0.6 to 1.0
		else if(eta < 1.0) return lowpt?0.00053:0.00202;//0.6 to 1.0
		else if(eta < 1.4) return lowpt?0.00081:0.00654;//1.0 to 1.4
		else if(eta < 1.8) return lowpt?0.00269:0.01380;//1.4 to 1.8
		else if(eta < 2.2) return lowpt?0.00297:0.01306;//1.8 to 2.2
		else if(eta < 2.6) return lowpt?0.00327:0.01550; //2.2 to 2.6
		else return lowpt?0.0:0.0; //2.6 to 3.0 //probably should be using the -2.6 to -2.2 range. xxx
	}
}//end eleChargeMisIDRate

//    __ 
//   /_ |
//    | |
//    | |
//    | |
//    |_|
//       

vector<double> SingleLepbkg(double f, double p, int N_t0, int N_t1){
	//Calculates all prompt and fake bkg info for same flavor dilepton events 
	//output: {N_p, N_f, N_signal, N_bkg}
	//          0    1     2        3 
	//This is taken from AN-10-261_v1 Section 2
	//N_t0 is #events with a loose lepton that fails tight
	//N_t1 is #events with a tight lepton
	//p is the probability ratio of a true lepton passes tight / a true lepton passing loose
	//f is the probability ratio of a fake lepton passes tight / a true lepton passing loose
	//N_p is the nubmer of true leptons passing loose 
	//N_f is the number of fake leptons passing loose 
	//N_signal is the number of real leptons passing tight
	//N_bkg is the number of fake leptons passing loose. 
	double div = 1.0/(p-f);
	vector<double> out;	
	out.push_back(div*((1.0-f)*N_t1 - f*N_t0));
	out.push_back(div*(p*N_t0 - (1-p)*N_t1));
	out.push_back(p*out[0]);
	out.push_back(f*out[1]);
	return out;
}

double SingleLepbkg_simple(double f, double p, int N_t0, int N_t1){
	//returns the expected number of fake events in the tight sample (N_bkg from SingleLepbkg above)
	//This is taken from AN-10-261_v1 Section 2
	//N_t0 is #events with a loose lepton that fails tight
	//N_t1 is #events with a tight lepton
	//p is the probability ratio of a true lepton passes tight / a true lepton passing loose
	//f is the probability ratio of a fake lepton passes tight / a true lepton passing loose
	return f*(p*N_t0 - (1-p)*N_t1)/(p-f);
}

//    ___  
//   |__ \
//      ) |
//     / / 
//    / /_ 
//   |____|
//         

vector<double> SFDLbkg(double f, double p, int N_t0, int N_t1, int N_t2){
	//Calculates all prompt and fake bkg info for same flavor dilepton events 
	//output: {0:N_pp, 1:N_fp, 2:N_ff, 3:N_signal, 4:N_1fake, 5:N_2fakes, 6:N_bkg}
	//This is taken from AN-10-261_v1 Section 3
	//N_t0 is #events with both loose leptons failing tight
	//N_t1 is #events with one loose leptons failing tight and the other passing.
	//N_t2 is #events with both loose leptons passing tight
	//p is the probability ratio of a true lepton passes tight / a true lepton passing loose
	//f is the probability ratio of a fake lepton passes tight / a true lepton passing loose
	//N_pp is the nubmer of true leptons passing loose 
	//N_pf is the loose leptons with one real lepton and one fake. (mostly tt, WJet)
	//N_ff is the loose leptons from two non-prompt fakes.  (mostly QCD)
	//N_signal is the number of real leptons passing tight-tight. 
	//N_1fake  is the number of events passing tight-tight with one fake lepton
	//N_2fake  is the number of events passing tight-tight with both lepton fake
	//N_bkg = N_1fake + N_2fake is the number of events passing tight that are not from two real leptons.
	double div = 1.0/pow(p-f,2); 
	double omf = 1.0-f;	
	double omp = 1.0-p;
	vector<double> out;	
	out.push_back(div*(omf*omf*N_t2 - f*omf*N_t1 + f*f*N_t0)); //N_pp, eq8
	out.push_back(div*(-2.0*f*p*N_t0 + (f*omp + p*omf)*N_t1 - 2.0*omp*omf*N_t2)); //N_fp, eq9
	out.push_back(div*(p*p*N_t0 - p*omp*N_t1 + omp*omp*N_t2)); //N_ff, eq9
	out.push_back(p*p*out[0]);//6
	out.push_back(p*f*out[1]);//4
	out.push_back(f*f*out[2]);//5
	out.push_back(out[4] + out[5]);//6
	return out;
}

double SFDLbkg_simple(double f, double p, int N_t0, int N_t1, int N_t2){
	//returns the number of non prompt-prompt events entering tight-tight (N_bkg as discussed in SFbkg)
	//This is taken from AN-10-261_v1 Section 3
	//N_t0 is #events with both loose leptons failing tight
	//N_t1 is #events with one loose leptons failing tight and the other passing.
	//N_t2 is #events with both loose leptons passing tight
	//p is the probability ratio of a true lepton passes tight / a true lepton passing loose
	//f is the probability ratio of a fake lepton passes tight / a true lepton passing loose
	double div = 1.0/pow(p-f,2);
	double omf = 1.0-f;	
	double omp = 1.0-p;
	return p*f*div*(-2.0*f*p*N_t0 + (f*omp + p*omf)*N_t1 - 2.0*omp*omf*N_t2) + 
		f*f*div*(p*p*N_t0 - p*omp*N_t1 + omp*omp*N_t2);//eq 9
	//double N_pf = div*(-2.0*f*p*N_t0 + (f*omp + p*omf)*N_t1 - 2.0*omp*omf*N_t2);
	//double N_ff = div*(p*p*N_t0 - p*omp*N_t1 + omp*omp*N_t2);
	//return p*f*N_pf + f*f*N_ff;
}
/*double SFDLbkg_simpler(double f, double p, int N_t0, int N_t1, int N_t2){ //broken! does not agree with SFDLbkg_simple
	//returns the number of non prompt-prompt events entering tight-tight (N_bkg as discussed in SFbkg)
	//This is taken from AN-10-261_v1 Section 3
	//N_t0 is #events with both loose leptons failing tight
	//N_t1 is #events with one loose leptons failing tight and the other passing.
	//N_t2 is #events with both loose leptons passing tight
	//p is the probability ratio of a true lepton passes tight / a true lepton passing loose
	//f is the probability ratio of a fake lepton passes tight / a true lepton passing loose
	double div = 1.0/pow(p-f,2);
	return f*(-f*p*p*N_t0 + p*p*(1.0-f)*N_t1 + (1.0-p)*(f+f*p - 2.0*p)*N_t2)/div;
}
double SFDLbkg_simplest(double f, double p, int N_t0, int N_t1, int N_t2){ //this does not work. 
	//returns the number of non prompt-prompt events entering tight-tight (N_bkg as discussed in SFbkg)
	//same thing as SFDLbkg_simpler, but with a little algebra to reduce the number of operations. 
	double e = epsilon(f);
	double h = eta(p);
	return e*( -e*N_t0 + N_t1 - (2.0 + e*h)*h*N_t2 ) / pow(1.0-e*h,2);
}*/


vector<double> OFDLbkg(double fe, double fm, double pe, double pm, int N_t00, int N_t10, int N_t01, int N_t11){
	//Calculates all prompt and fake bkg info for same flavor dilepton events 
	//output: {0:N_pp, 1:N_fp, 2:N_pf, 3:N_ff, 4:N_signal, 5:N_efakes, 6:N_mfakes, 7:N_bothfake, 8:N_bkg}
	//This is taken from AN-10-261_v1 Section 5, equations 19 and 20.
	//N_txy is the number of events with 1 loose ele and 1 tight ele where 
		//x is the number of ele passing tight and y is the number of muons passing tight.
	//p(e,m) is the probability ratio of a true (ele, muon) passes tight / a true (ele, mu)  passing loose
	//f(e,m) is the probability ratio of a fake (ele, muon) passes tight / a true (ele, mu)passing loose
	//N_pp is the nubmer of true e+mu events passing loose 
	//N_pf is the number of loose e+mu events where the muon is fake and the ele is real.
	//N_fp is the number of loose e+mu events where the ele is fake and the muon is real.
	//N_ff is the number of loose e+mu events where both objects are fake. 
	//N_signal is the number of real e+mu events passing tight-tight. 
	//N_efakes is the number of tight-tight e+mu events where the electron is fake.
	//N_mfakes is the number of tight-tight e+mu events where the muon is fake.
	//N_bothfake is the number of tight-tight e+mu events where both objects are fake.
	//N_bkg = N_efakes + N_mfakes + N_bothfake is the number of e+m events passing tight-tight that are not from two real leptons.
	double omfe = 1.0-fe;
	double omfm = 1.0-fm;
	double ompe = 1.0-pe;
	double ompm = 1.0-pm;
	double div = 1.0/((pe-fe)*(pm-fm));
	vector<double> out;	
	out.push_back(div*(omfe*omfm*N_t11 - omfe*fm*N_t10 - fe*omfm*N_t01 + fe*fm*N_t00 )); //0 N_pp
	out.push_back(div*(-fe*pm*N_t00 + omfe*pm*N_t10 + fe*ompm*N_t01 - omfe*ompm*N_t11)); //1 N_pf
	out.push_back(div*(-fm*pe*N_t00 + ompe*fm*N_t10 + pe*omfm*N_t01 - ompe*omfm*N_t11)); //2 N_fp
	out.push_back(div*( pe*pm*N_t00 - ompe*pm*N_t10 - pe*ompm*N_t01 + ompe*ompm*N_t11)); //3 N_ff
	out.push_back(pe*pm*out[0]);//4
	out.push_back(pe*fm*out[1]);//5
	out.push_back(pm*fe*out[2]);//6
	out.push_back(fe*fm*out[3]);//7
	out.push_back(out[5] + out[6] + out[7] );//8
	return out;
}
double OFDLbkg_simple(double fe, double fm, double pe, double pm, int N_t00, int N_t10, int N_t01, int N_t11){
	//returns the number of e+m events passing tight-tight that are not from two real leptons.
	//This is taken from AN-10-261_v1 Section 5, equation 21
	//N_txy is the number of events with 1 loose ele and 1 tight ele where 
		//x is the number of ele passing tight and y is the number of muons passing tight.
	//p(e,m) is the probability ratio of a true (ele, muon) passes tight / a true (ele, mu)  passing loose
	//f(e,m) is the probability ratio of a fake (ele, muon) passes tight / a true (ele, mu)passing loose
	double ee = epsilon(fe);
	double em = epsilon(fm);
	double he = eta(pe);
	double hm = eta(pm);
	double div = 1.0/((1.0 - ee*he)*(1.0-em*hm));
	double N_pf_pass = em*div*(-ee*N_t00 + N_t10 + ee*hm*N_t01 - hm*N_t11);
	double N_fp_pass = ee*div*(-em*N_t00 + he*em*N_t10 + N_t01 - he*N_t11);
	double N_ff_pass = ee*em*div*(N_t00 - he*N_t10 - hm*N_t01 + he*hm*N_t11);
	return N_pf_pass + N_fp_pass + N_ff_pass;
}
double OFDLbkg_simpler(double fe, double fm, double pe, double pm, int N_t00, int N_t10, int N_t01, int N_t11){
	double ee = epsilon(fe);
	double em = epsilon(fm);
	double he = eta(pe);
	double hm = eta(pm);
	/*double div = 1.0/((1.0 - ee*he)*(1.0-em*hm));
	return em*div*(-ee*N_t00 + N_t10 + ee*hm*N_t01 - hm*N_t11) +
	ee*div*(-em*N_t00 + he*em*N_t10 + N_t01 - he*N_t11) +
	ee*em*div*(N_t00 - he*N_t10 - hm*N_t01 + he*hm*N_t11);

	return div*(
			(-em*ee*N_t00 + em*N_t10 + em*ee*hm*N_t01 - em*hm*N_t11) +
			(-ee*em*N_t00 + he*ee*em*N_t10 + ee*N_t01 - ee*he*N_t11) +
			(ee*em*N_t00 - he*ee*em*N_t10 - hm*ee*em*N_t01 + ee*em*he*hm*N_t11)
	);

	return div*(
			(-em*ee -ee*em + ee*em)*N_t00 + 
			(em+ he*ee*em- he*ee*em)*N_t10 + 
			(em*ee*hm+ ee- hm*ee*em)*N_t01 +
			(-em*hm - ee*he+ ee*em*he*hm)*N_t11
	);

	return div*( -em*ee*N_t00 + em*N_t10 + ee*N_t01 + (-em*hm - ee*he+ ee*em*he*hm)*N_t11 );
	*/
	return ( -em*ee*N_t00 + em*N_t10 + ee*N_t01 + (-em*hm - ee*he+ ee*em*he*hm)*N_t11 ) / ((1.0 - ee*he)*(1.0-em*hm));
}

double DilepNonPromptBkgUncertAll( int Nem_t00, int Nem_t10, int Nem_t01, int Nem_t11, int Nee_t0, int Nee_t1, int Nee_t2, int Nmm_t0, int Nmm_t1, int Nmm_t2, int ndice, int& seed){ //broken. 
/*double DilepBkgUncertAll(double fe, double fm, double pe, double pm, 
		double ufe, double ufm, double upe, double upm, 
		int Nem_t00, int Nem_t10, int Nem_t01, int Nem_t11,
		int Nee_t0, int Nee_t1, int Nee_t2,
		int Nmm_t0, int Nmm_t1, int Nmm_t2,
		int ndice, int& seed){*/
	//xxx this needs a decision on whether to use stdev or randoms. Also, your understanding of statistics has progressed since writing htis. 
	//xxx this may well get abandoned. 

	ndice = ndice<5?5:ndice;//prevent divide by 0 errors and other silliness. 

	double meanBkgEst = 
		SFDLbkg_simple(Fe(), Pe(), Nee_t0, Nee_t1, Nee_t2) +
		SFDLbkg_simple(Fm(), Pm(), Nmm_t0, Nmm_t1, Nmm_t2) +
		OFDLbkg_simpler(Fe(), Fm(), Pe(), Pm(), Nem_t00, Nem_t10, Nem_t01, Nem_t11) ;
	double varianceBkgEst = 0;

	double bkgEstimates[ndice];
	TRandom2* r = new TRandom2(seed);
	for(int i=0;i<ndice;i++){
		double fe_test = r->Gaus(Fe(),uFe());
		double fm_test = r->Gaus(Fm(),uFm());
		double pe_test = Pe() + r->Uniform(uPe()*2) - uPe();
		double pm_test = Pm() + r->Uniform(uPm()*2) - uPm();
		double ee = epsilon(fe_test);
		double em = epsilon(fm_test);
		double he = eta(pe_test);
		double hm = eta(pm_test);

			//make test counts
			//use the observed N to estimate a poisson dist; then sample from that dist to get the test count. 
		int nem_t00 = ThrowPoissonFromMeasurement(r,Nem_t00);
		int nem_t10 = ThrowPoissonFromMeasurement(r,Nem_t10);
		int nem_t01 = ThrowPoissonFromMeasurement(r,Nem_t01);
		int nem_t11 = ThrowPoissonFromMeasurement(r,Nem_t11);

		int nee_t0 = ThrowPoissonFromMeasurement(r,Nee_t0);
		int nee_t1 = ThrowPoissonFromMeasurement(r,Nee_t1);
		int nee_t2 = ThrowPoissonFromMeasurement(r,Nee_t2);

		int nmm_t0 = ThrowPoissonFromMeasurement(r,Nmm_t0);
		int nmm_t1 = ThrowPoissonFromMeasurement(r,Nmm_t1);
		int nmm_t2 = ThrowPoissonFromMeasurement(r,Nmm_t2);


		//ee:
		double ee_bkg = ee*( -ee*nee_t0 + nee_t1 - (2.0 + ee*he)*he*nee_t2 ) / pow(1.0-ee*he,2); //using the "SFDLbkg_simplest" formulation
		//mm:
		double mm_bkg = em*( -em*nmm_t0 + nmm_t1 - (2.0 + em*hm)*hm*nmm_t2 ) / pow(1.0-em*hm,2); //using the "SFDLbkg_simplest" formulation
		//em:
		double em_bkg = ( -em*ee*nem_t00 + em*nem_t10 + ee*nem_t01 + (-em*hm - ee*he+ ee*em*he*hm)*nem_t11 ) / ((1.0 - ee*he)*(1.0-em*hm));
		//fill: 
		bkgEstimates[i] = ee_bkg + mm_bkg + em_bkg;
		varianceBkgEst += pow(ee_bkg + mm_bkg + em_bkg - meanBkgEst,2);
	}//end for
	varianceBkgEst /= (double) ndice;
	double stdev = sqrt(varianceBkgEst);//two sided stdev. 
	//either make the stdev or sort it and report 1 sigma quartiles. 

	return stdev;
}//end DilepBkgUncertAll //broken via SFDLbkg_simplest bug. 


//    ____  
//   |___ \
//     __) |
//    |__ < 
//    ___) |
//   |____/ 
//          
//          


vector<double> SF3Lepbkg(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3){
	//Calculates all prompt and fake bkg info for Same Flavor trilepton events 
	//output: {0:N_ppp, 1:N_fpp, 2:N_ffp, 3:N_fff, 4:N_signal, 5:N_1fake, 6:N_2fakes, 7:N_3fakes, 8:N_bkg}
	//This is taken from AN-10-261_v1 Section 4
	//N_t0 is #events with all 3 loose leptons failing tight
	//N_t1 is #events with one loose leptons failing tight and the other 2 passing tight
	//N_t2 is #events with two  loose leptons failing tight and the other one passing tight
	//N_t3 is #events with all 3 loose leptons passing tight
	//p is the probability ratio of a true lepton passes tight / a true lepton passing loose
	//f is the probability ratio of a fake lepton passes tight / a true lepton passing loose
	//N_fff is the loose leptons from three non-prompt fakes. 
	//N_ffp is the loose leptons with one real lepton and two fakes.
	//N_fpp is the loose leptons with two real lepton and one fakes.
	//N_ppp is the number of true tri-lepton events passing loose 
	//N_signal is the number of true tri-leptons all passing tight
	//N_1fake  is the number of events passing tight-tight with one fake lepton
	//N_2fake  is the number of events passing tight-tight with two fake lepton 
	//N_3fake  is the number of events passing tight-tight with all three leptons fake
	//N_bkg = N_1fake + N_2fake + N_3fakes is the number of events passing tight that are not from two real leptons.
	double div = 1.0/pow(p-f,3);
	double omf = 1.0-f;	
	double omp = 1.0-p;
	vector<double> out;	
	out.push_back(div*(omf*omf*omf*N_t0 - f*omf*omf*N_t2 + f*f*omf*N_t1 - f*f*f*N_t0)); //N_ppp 0
	out.push_back(div*( 3.0*p*f*f*N_t0 - (f*f*omp + 2.0*p*f*omf)*N_t1 + (2.0*f*omp*omf + p*omf*omf)*N_t2 - 3.0*omp*omf*omf*N_t3) );//N_fpp 1
	out.push_back(div*(-3.0*p*p*f*N_t0 + (2.0*p*f*omp + p*p*omf)*N_t1 - (f*omp*omp + 2.0*p*omp*omf)*N_t2 + 2.0*omp*omp*omf*N_t3) );//N_ffp 2
	out.push_back(div*(p*p*p*N_t0 - p*p*omp*N_t1 + p*omp*omp*N_t2 - omp*omp*omp*N_t3));// N_fff 3
	out.push_back(p*p*p*out[0]); //4
	out.push_back(p*p*f*out[1]); //5
	out.push_back(p*f*f*out[2]); //6
	out.push_back(f*f*f*out[3]); //7
	out.push_back(out[5] + out[6] + out[7]);
	return out;
}
double SF3Lepbkg_simple(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3){
	//returns  the number of tight tri-lepton events with at least one fake object (N_bkg from SF3Lepbkg)
	//This is taken from AN-10-261_v1 Section 4
	//N_t0 is #events with all 3 loose leptons failing tight
	//N_t1 is #events with one loose leptons failing tight and the other 2 passing tight
	//N_t2 is #events with two  loose leptons failing tight and the other one passing tight
	//N_t3 is #events with all 3 loose leptons passing tight
	//p is the probability ratio of a true lepton passes tight / a true lepton passing loose
	//f is the probability ratio of a fake lepton passes tight / a true lepton passing loose
	double div = 1.0/pow(p-f,3);
	double omf = 1.0-f;	
	double omp = 1.0-p;
	double N_fpp = div*( 3.0*p*f*f*N_t0 - (f*f*omp + 2.0*p*f*omf)*N_t1 + (2.0*f*omp*omf + p*omf*omf)*N_t2 - 3.0*omp*omf*omf*N_t3); 
	double N_ffp = div*(-3.0*p*p*f*N_t0 + (2.0*p*f*omp + p*p*omf)*N_t1 - (f*omp*omp + 2.0*p*omp*omf)*N_t2 + 2.0*omp*omp*omf*N_t3);
	double N_fff = div*(p*p*p*N_t0 - p*p*omp*N_t1 + p*omp*omp*N_t2 - omp*omp*omp*N_t3);
	return p*p*f*N_fpp + p*f*f*N_ffp + f*f*f*N_fff;
}

/////////////////////////////////////////////////////////////

int ThrowPoissonFromMeasurement(TRandom2* r, int n){//wad
	if(n>100) return (int) r->Gaus(n, sqrt((float)n));
	//figure out what the distribution of poisson parameters are. 
	return r->Poisson( 0.5*ChiSquared(2*(n+1) ) );
}
double ChiSquared(int k){//wad
	ROOT::Math::Random<ROOT::Math::GSLRngMT> r;
	return r.ChiSquare(k);
}


/////////////////////// FUNCTIONS FOR WEIGHTS /////////////////////
///////////////////////coifs for SS emu////////////////////////////
//mode 0 = nominal. 1 = fakerate plus, 2 = fakerate minus, 3 = passrate plus, 4 = passrate minus, 5 = q plus, 6 = q minus
inline int feModeBehavior(int mode){ return mode==1?1:(mode==2?-1:0); }//these wad
inline int fmModeBehavior(int mode){ return mode==1?1:(mode==2?-1:0); } //+1,-1 for 1,2, else 0
//inline int fmModeBehavior(int mode){ return mode==5?1:(mode==6?-1:0); } //+1,-1 for 5,6, else 0
inline int peModeBehavior(int mode){ return mode==3?1:(mode==4?-1:0); }
inline int pmModeBehavior(int mode){ return mode==3?1:(mode==4?-1:0); } //+1,-1 for 3,4, else 0
//inline int pmModeBehavior(int mode){ return mode==7?1:(mode==8?-1:0); } //+1,-1 for 3,4, else 0
inline int qeModeBehavior(int mode){ return mode==5?1:(mode==6?-1:0); }

inline double Det_em(double fe, double pe, double fm, double pm, double q){ return -(1.0 - 2.0* q)*(pe - fe)*(pm - fm); } //det is always negative.

//multiply these by the corresponding observed n, or bin with the weight for every observation. 
double Wemss_llos(float elePt, float eleEta, int mode){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	return (-fe*fm*pe*pm*( 1.0 - q)*q )/det;
}
double Wemss_llss(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	return (fe*fm*pe*pm*pow( 1.0 - q,2) )/det;
}
double Wemss_ltos(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	return (fe*( 1.0 - fm)*pe*pm*( 1.0 - q)*q )/det;
}
double Wemss_ltss(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	return -(fe*( 1.0 - fm)*pe*pm*pow( 1.0 - q,2) )/det;
}
double Wemss_tlos(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	return ( ( 1.0 - fe)*fm*pe*pm*( 1.0 - q)*q )/det;
}
double Wemss_tlss(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	return -((1.0 - fe)*fm*pe*pm*pow( 1.0 - q,2) )/det;
}
double Wemss_ttos(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	return -(( 1.0 - fe)*( 1.0 - fm)*pe*pm*( 1.0 - q)*q )/det;
}
double Wemss_ttss(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	double qbar2 = pow( 1.0-q ,2);
	return (pe*(pm*q*q - fm*(-1.0 + pm*qbar2 + 2.0*q)) + fe*(-pm*(-1.0 + pe*qbar2 + 2.0*q) + fm*(-1.0 + pe*pm*qbar2 + 2.0*q)) )/det;
}


/////////////////////// coifs for OS emu //////////////////////////////
double Wemos_llos(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	return (fe*fm*pe*pm*pow( 1.0 - q,2) )/det;
}
double Wemos_llss(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	return -(fe*fm*pe*pm*( 1.0 - q)*q )/det;
}
double Wemos_ltos(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	return -(fe*( 1.0 - fm)*pe*pm*pow( 1.0 - q,2) )/det;
}
double Wemos_ltss(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	return (fe*( 1.0 - fm)*pe*pm*( 1.0 - q)*q )/det;
}
double Wemos_tlos(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	return -(( 1.0 - fe)*fm*pe*pm*pow( 1.0 - q,2) )/det;
}
double Wemos_tlss(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	return (( 1.0 - fe)*fm*pe*pm*( 1.0 - q)*q )/det;
}
double Wemos_ttos(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	double qbar2 = pow( 1.0-q ,2);
	return (pe*(pm*q*q - fm*(-1.0 + pm*qbar2 + 2.0*q)) + fe*(-pm*(-1.0 + pe*qbar2 + 2.0*q) + fm*(-1.0 + pe*pm*qbar2 + 2.0*q)) )/det;
}
double Wemos_ttss(float elePt, float eleEta,int mode ){
	double q = eleChargeMisIDRate_lin(eleEta, elePt, mode);
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = Det_em(fe, pe, fm, pm, q);
	return -(( 1.0 - fe)*( 1.0 - fm)*pe*pm*( 1.0 - q)*q )/det;
}

/////////////////////// coifs for SS ee //////////////////////////////
inline double alpha(double q1,double q2){ return (1.0-q1)*(1.0-q2) + q1*q2; }
inline double beta( double q1,double q2){ return q1*(1.0-q2) + q2*(1.0-q1); }
inline double Det_ee(double a, double b, double fe, double pe){return pow(fe - pe,2)*(a - b)*(a + b);}//new

double Weess_llos(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode){
	double q1 = eleChargeMisIDRate_lin(ele1Eta, ele1Pt, mode);
	double q2 = eleChargeMisIDRate_lin(ele2Eta, ele2Pt, mode);
	double a = alpha(q1,q2);
	double b = beta(q1,q2);
	double fe = Fe(mode);
	double pe = Pe(mode);
	double det = Det_ee(a,b,fe,pe);
	return (a*b*fe*fe*pe*pe)/det;
}
double Weess_llss(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode){
	double q1 = eleChargeMisIDRate_lin(ele1Eta, ele1Pt, mode);
	double q2 = eleChargeMisIDRate_lin(ele2Eta, ele2Pt, mode);
	double a = alpha(q1,q2);
	double b = beta(q1,q2);
	double fe = Fe(mode);
	double pe = Pe(mode);
	double det = Det_ee(a,b,fe,pe);
	return -(a*a*fe*fe*pe*pe)/det;
}
double Weess_tlos(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode){
	double q1 = eleChargeMisIDRate_lin(ele1Eta, ele1Pt, mode);
	double q2 = eleChargeMisIDRate_lin(ele2Eta, ele2Pt, mode);
	double a = alpha(q1,q2);
	double b = beta(q1,q2);
	double fe = Fe(mode);
	double pe = Pe(mode);
	double det = Det_ee(a,b,fe,pe);
	return (a*b*(-1.0 + fe)*fe*pe*pe )/det;
}
double Weess_tlss(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode){
	double q1 = eleChargeMisIDRate_lin(ele1Eta, ele1Pt, mode);
	double q2 = eleChargeMisIDRate_lin(ele2Eta, ele2Pt, mode);
	double a = alpha(q1,q2);
	double b = beta(q1,q2);
	double fe = Fe(mode);
	double pe = Pe(mode);
	double det = Det_ee(a,b,fe,pe);
	return -(a*a*(-1.0 + fe)*fe*pe*pe )/det;
}
double Weess_ttos(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode){
	double q1 = eleChargeMisIDRate_lin(ele1Eta, ele1Pt, mode);
	double q2 = eleChargeMisIDRate_lin(ele2Eta, ele2Pt, mode);
	double a = alpha(q1,q2);
	double b = beta(q1,q2);
	double fe = Fe(mode);
	double pe = Pe(mode);
	double det = Det_ee(a,b,fe,pe);
	return (a*b*pow(-1.0 + fe,2)*pe*pe)/det;
}
double Weess_ttss(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode){
	double q1 = eleChargeMisIDRate_lin(ele1Eta, ele1Pt, mode);
	double q2 = eleChargeMisIDRate_lin(ele2Eta, ele2Pt, mode);
	double a = alpha(q1,q2);
	double b = beta(q1,q2);
	double fe = Fe(mode);
	double pe = Pe(mode);
	double det = Det_ee(a,b,fe,pe);
	return (-b*b*pow(fe - pe,2) - a*a*fe*(-1.0 + pe)*(fe + (-2.0 + fe)*pe))/det;
}



/////////////////////// coifs for OS ee //////////////////////////////
double Weeos_llos(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode){
	double q1 = eleChargeMisIDRate_lin(ele1Eta, ele1Pt, mode);
	double q2 = eleChargeMisIDRate_lin(ele2Eta, ele2Pt, mode);
	double a = alpha(q1,q2);
	double b = beta(q1,q2);
	double fe = Fe(mode);
	double pe = Pe(mode);
	double det = Det_ee(a,b,fe,pe);
	return -(a*a*fe*fe*pe*pe )/det;
}
double Weeos_llss(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode){
	double q1 = eleChargeMisIDRate_lin(ele1Eta, ele1Pt, mode);
	double q2 = eleChargeMisIDRate_lin(ele2Eta, ele2Pt, mode);
	double a = alpha(q1,q2);
	double b = beta(q1,q2);
	double fe = Fe(mode);
	double pe = Pe(mode);
	double det = Det_ee(a,b,fe,pe);
	return (a*b*fe*fe*pe*pe)/ det;
}
double Weeos_tlos(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode){
	double q1 = eleChargeMisIDRate_lin(ele1Eta, ele1Pt, mode);
	double q2 = eleChargeMisIDRate_lin(ele2Eta, ele2Pt, mode);
	double a = alpha(q1,q2);
	double b = beta(q1,q2);
	double fe = Fe(mode);
	double pe = Pe(mode);
	double det = Det_ee(a,b,fe,pe);
	return -(a*a*(-1.0 + fe)*fe*pe*pe)/det;
}
double Weeos_tlss(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode){
	double q1 = eleChargeMisIDRate_lin(ele1Eta, ele1Pt, mode);
	double q2 = eleChargeMisIDRate_lin(ele2Eta, ele2Pt, mode);
	double a = alpha(q1,q2);
	double b = beta(q1,q2);
	double fe = Fe(mode);
	double pe = Pe(mode);
	double det = Det_ee(a,b,fe,pe);
	return (a*b*(-1.0 + fe)*fe*pe*pe )/det;
}
double Weeos_ttos(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode){
	double q1 = eleChargeMisIDRate_lin(ele1Eta, ele1Pt, mode);
	double q2 = eleChargeMisIDRate_lin(ele2Eta, ele2Pt, mode);
	double a = alpha(q1,q2);
	double b = beta(q1,q2);
	double fe = Fe(mode);
	double pe = Pe(mode);
	double det = Det_ee(a,b,fe,pe);
	return -(b*b*pow(fe - pe,2)   +   a*a*fe*(-1.0 + pe)*(fe + (-2.0 + fe)*pe) )/det;
}
double Weeos_ttss(float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode){
	double q1 = eleChargeMisIDRate_lin(ele1Eta, ele1Pt, mode);
	double q2 = eleChargeMisIDRate_lin(ele2Eta, ele2Pt, mode);
	double a = alpha(q1,q2);
	double b = beta(q1,q2);
	double fe = Fe(mode);
	double pe = Pe(mode);
	double det = Det_ee(a,b,fe,pe);
	return (a*b*pow(-1.0 + fe,2)*pe*pe)/det;
}

/////////////////////////////////////
/////////////////////// coifs for SS mm //////////////////////////////
double Wmmss_ttss(int mode){ //Nt2
	double fm = Fm(mode);
	double pm = Pm(mode);
	double div = pow(pm-fm,2);	
	return fm*( -2.0*pm*(1.0-pm)*(1.0-fm) + fm*(1.0-pm)*(1.0-pm))/div;//This is taken from AN-10-261_v1 Section 3, eq9
}
double Wmmss_tlss(int mode){ //Nt1
	double fm = Fm(mode);
	double pm = Pm(mode);
	double div = pow(pm-fm,2);	
	return fm*pm*pm*(1.0-fm)/div;//This is taken from AN-10-261_v1 Section 3, eq9
}
double Wmmss_llss(int mode){ //Nt0
	double fm = Fm(mode);
	double pm = Pm(mode);
	double div = pow(pm-fm,2);	
	return -fm*fm*pm*pm/div; //This is taken from AN-10-261_v1 Section 3, eq9
	//double check these, I think they're wrong. 
}

/////////////////////// coifs for OS mm //////////////////////////////
double Wmmxs_ttxs(int mode){ //Nt2
	double fm = Fm(mode);
	double pm = Pm(mode);
	double div = pow(pm-fm,2);	
	return fm*(1.0-pm)*(fm+fm*pm-2.0*pm)/div;
}
double Wmmxs_tlxs(int mode){ //Nt1
	double fm = Fm(mode);
	double pm = Pm(mode);
	double div = pow(pm-fm,2);	
	return pm*pm*fm*(1.0-fm)/div;
}
double Wmmxs_llxs(int mode){ //Nt0
	double fm = Fm(mode);
	double pm = Pm(mode);
	double div = pow(pm-fm,2);	
	return -fm*fm*pm*pm/div;
}
//////////////////////////////////////////////////////////////////

double GetWeight_emss(bool is_SSDL, bool ele_is_Tight, bool mu_is_Tight, float elePt, float eleEta,int mode){
	if(ele_is_Tight and mu_is_Tight){
		if(is_SSDL) return Wemss_ttss(elePt, eleEta, mode);
		else return Wemss_ttos(elePt, eleEta, mode);
	}
	else if(!ele_is_Tight and !mu_is_Tight){
		if(is_SSDL) return Wemss_llss(elePt, eleEta, mode);
		else return Wemss_llos(elePt, eleEta, mode);
	}
	else if(ele_is_Tight and !mu_is_Tight){
		if(is_SSDL) return Wemss_tlss(elePt, eleEta, mode);
		else return Wemss_tlos(elePt, eleEta, mode);
	}
	else{
		if(is_SSDL) return Wemss_ltss(elePt, eleEta, mode);
		else return Wemss_ltos(elePt, eleEta, mode);
	}
}
double GetWeight_emos(bool is_SSDL, bool ele_is_Tight, bool mu_is_Tight, float elePt, float eleEta,int mode){
	//get the weight for calculating the bkg to e mu opposite signed. 
	if(ele_is_Tight and mu_is_Tight){
		if(is_SSDL) return Wemos_ttss(elePt, eleEta, mode);
		else return Wemos_ttos(elePt, eleEta, mode);
	}
	else if(!ele_is_Tight and !mu_is_Tight){
		if(is_SSDL) return Wemos_llss(elePt, eleEta, mode);
		else return Wemos_llos(elePt, eleEta, mode);
	}
	else if(ele_is_Tight and !mu_is_Tight){
		if(is_SSDL) return Wemos_tlss(elePt, eleEta, mode);
		else return Wemos_tlos(elePt, eleEta, mode);
	}
	else{
		if(is_SSDL) return Wemos_ltss(elePt, eleEta, mode);
		else return Wemos_ltos(elePt, eleEta, mode);
	}
}
double GetWeight_eess(bool is_SSDL, int nTightEle, float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode){
    switch(nTightEle){
	case 2:
	    if(is_SSDL) return Weess_ttss(ele1Pt, ele1Eta, ele2Pt, ele2Eta, mode);
	    else return Weess_ttos(ele1Pt, ele1Eta, ele2Pt, ele2Eta, mode);
	case 1:
	    if(is_SSDL) return Weess_tlss(ele1Pt, ele1Eta, ele2Pt, ele2Eta, mode);
	    else return Weess_tlos(ele1Pt, ele1Eta, ele2Pt, ele2Eta, mode);
	case 0:
	    if(is_SSDL) return Weess_llss(ele1Pt, ele1Eta, ele2Pt, ele2Eta, mode);
	    else return Weess_llos(ele1Pt, ele1Eta, ele2Pt, ele2Eta, mode);
	default: return 0.0;
    }
}
double GetWeight_eeos(bool is_SSDL, int nTightEle, float ele1Pt, float ele1Eta, float ele2Pt, float ele2Eta, int mode){
    switch(nTightEle){
	case 2:
	    if(is_SSDL) return Weeos_ttss(ele1Pt, ele1Eta, ele2Pt, ele2Eta, mode);
	    else return Weeos_ttos(ele1Pt, ele1Eta, ele2Pt, ele2Eta, mode);
	case 1:
	    if(is_SSDL) return Weeos_tlss(ele1Pt, ele1Eta, ele2Pt, ele2Eta, mode);
	    else return Weeos_tlos(ele1Pt, ele1Eta, ele2Pt, ele2Eta, mode);
	case 0:
	    if(is_SSDL) return Weeos_llss(ele1Pt, ele1Eta, ele2Pt, ele2Eta, mode);
	    else return Weeos_llos(ele1Pt, ele1Eta, ele2Pt, ele2Eta, mode);
	default: return 0.0;
    }
}
//double GetWeight_mmxs(bool muon1_is_Tight, bool muon2_is_Tight, int mode){
double GetWeight_mmos(bool is_SSDL, int nTightMuons, int mode){
	if(is_SSDL) return 0.0;
	else return GetWeight_mmxs(nTightMuons, mode);
}
double GetWeight_mmss(bool is_SSDL, int nTightMuons, int mode){
	if(is_SSDL) return GetWeight_mmxs(nTightMuons, mode);
	else return 0.0;
}
double GetWeight_mmxs(int nTightMuons, int mode){
	//for the background to SS, use SS muons only; 
	//for the background to OS, use OS muons only; 
	switch(nTightMuons){
		case 2: return Wmmxs_ttxs(mode);
		case 1: return Wmmxs_tlxs(mode);
		case 0: return Wmmxs_llxs(mode);
		default: return 0.0;
	}
}

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////Tripple Lepton /////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
double GetWeight_eee(int nTightEle, int mode){
    switch(nTightEle){
	case 3: return Weee_ttt(mode);
	case 2: return Weee_ltt(mode);
	case 1: return Weee_llt(mode);
	case 0: return Weee_lll(mode);
	default: return 0.0;
    }
}
double GetWeight_mmm(int nTightMu, int mode){
    switch(nTightMu){
	case 3: return Wmmm_ttt(mode);
	case 2: return Wmmm_ltt(mode);
	case 1: return Wmmm_llt(mode);
	case 0: return Wmmm_lll(mode);
	default: return 0.0;
    }
}
double GetWeight_eem(int nTightEle, int nTightMu, int mode){
	if(     nTightEle == 2 and nTightMu == 1) return Weem_ttt(mode);
	else if(nTightEle == 2 and nTightMu == 0) return Weem_tetelm(mode);
	else if(nTightEle == 1 and nTightMu == 0) return Weem_telelm(mode);
	else if(nTightEle == 1 and nTightMu == 1) return Weem_tmtele(mode);
	else if(nTightEle == 0 and nTightMu == 1) return Weem_leletm(mode);
	else if(nTightEle == 0 and nTightMu == 0) return Weem_lll(mode);
	else return 0.0;
}
double GetWeight_emm(int nTightEle, int nTightMu, int mode){
	if(     nTightMu == 2 and nTightEle == 1) return Wemm_ttt(mode);
	else if(nTightMu == 2 and nTightEle == 0) return Wemm_tmtmle(mode);
	else if(nTightMu == 1 and nTightEle == 0) return Wemm_tmlmle(mode);
	else if(nTightMu == 1 and nTightEle == 1) return Wemm_tetmlm(mode);
	else if(nTightMu == 0 and nTightEle == 1) return Wemm_lmlmte(mode);
	else if(nTightMu == 0 and nTightEle == 0) return Wemm_lll(mode);
	else return 0.0;
}

///Tri-electron
//B = {(fe*pe^3*(-fe^2*n_lll + (-1 + fe)*(n_ttl - fe*(n_tll + n_ttl))) + fe*(fe^2 - 3 fe*pe + 3*pe^2 - (3 + (-3 + fe)*fe) pe^3)*n_ttt)/(fe - pe)^3}
double Weee_lll(int mode){ 
	//B = {(fe*pe^3*(-fe^2*n_lll + (-1 + fe)*(n_ttl - fe*(n_tll + n_ttl))) + fe*(fe^2 - 3 fe*pe + 3*pe^2 - (3 + (-3 + fe)*fe) pe^3)*n_ttt)/(fe - pe)^3}
	double fe = Fe(mode);
	double pe = Pe(mode);
	double div = pow(fe-pe,3);	
	return -fe*pow(pe,3)*fe*fe/div;
}
double Weee_ltt(int mode){
	//B = {(fe*pe^3*(-fe^2*n_lll + (-1 + fe)*(n_ttl - fe*(n_tll + n_ttl))) + fe*(fe^2 - 3 fe*pe + 3*pe^2 - (3 + (-3 + fe)*fe) pe^3)*n_ttt)/(fe - pe)^3}
	double fe = Fe(mode);
	double pe = Pe(mode);
	double div = pow(fe-pe,3);	
	//B = {(fe*pe^3*( (-1 + fe)*(n_ttl - fe*(n_ttl)))  )/(fe - pe)^3}
	//B = {(fe*pe^3* (-1 + fe)*(1-fe)*n_ttl   )/div;
	return (fe*pow(pe,3)*(-1.0 + fe)*(1.0-fe) )/div;
}
double Weee_llt(int mode){
	//B = {(fe*pe^3*(-fe^2*n_lll + (-1 + fe)*(n_ttl - fe*(n_tll + n_ttl))) + fe*(fe^2 - 3 fe*pe + 3*pe^2 - (3 + (-3 + fe)*fe) pe^3)*n_ttt)/(fe - pe)^3}
	//B = {(fe*pe^3*( (-1 + fe)*(- fe*(n_tll ))) )/div;
	double fe = Fe(mode);
	double pe = Pe(mode);
	double div = pow(fe-pe,3);	
	return (fe*pow(pe,3)* (1.0 - fe)*fe )/div;
}
double Weee_ttt(int mode){
	//B = {(fe*pe^3*(-fe^2*n_lll + (-1 + fe)*(n_ttl - fe*(n_tll + n_ttl))) + fe*(fe^2 - 3 fe*pe + 3*pe^2 - (3 + (-3 + fe)*fe) pe^3)*n_ttt)/(fe - pe)^3}
	//B = (  fe*(fe^2 - 3 fe*pe + 3*pe^2 - (3 + (-3 + fe)*fe) pe^3)*n_ttt)/(fe - pe)^3
	double fe = Fe(mode);
	double pe = Pe(mode);
	double div = pow(fe-pe,3);	
	return (  fe*(fe*fe - 3.0*fe*pe + 3.0*pe*pe - (3.0 + (-3.0 + fe)*fe)*pow(pe,3) ))/div;
}

//B = {(fe*pe^3*(-fe^2*n_lll + (-1 + fe)*(n_ttl - fe*(n_tll + n_ttl))) + fe*(fe^2 - 3 fe*pe + 3*pe^2 - (3 + (-3 + fe)*fe) pe^3)*n_ttt)/(fe - pe)^3}
//Tri-muon
//B = {(fm pm^3 (-fm^2 n_lll + (-1 + fm) (n_ttl - fm (n_tll + n_ttl))) + fm (fm^2 - 3 fm pm + 3 pm^2 - (3 + (-3 + fm) fm) pm^3) n_ttt)/(fm - pm)^3
double Wmmm_lll(int mode){ 
	//B = {(fm*pm^3*(-fm^2*n_lll + (-1 + fm)*(n_ttl - fm*(n_tll + n_ttl))) + fm*(fm^2 - 3 fm*pm + 3*pm^2 - (3 + (-3 + fm)*fm) pm^3)*n_ttt)/(fm - pm)^3}
	double fm = Fm(mode);
	double pm = Pm(mode);
	double div = pow(fm-pm,3);	
	return -fm*pow(pm,3)*fm*fm/div;
}
double Wmmm_ltt(int mode){
	//B = {(fm*pm^3*(-fm^2*n_lll + (-1 + fm)*(n_ttl - fm*(n_tll + n_ttl))) + fm*(fm^2 - 3 fm*pm + 3*pm^2 - (3 + (-3 + fm)*fm) pm^3)*n_ttt)/(fm - pm)^3}
	double fm = Fm(mode);
	double pm = Pm(mode);
	double div = pow(fm-pm,3);	
	//B = {(fm*pm^3*( (-1 + fm)*(n_ttl - fm*(n_ttl)))  )/(fm - pm)^3}
	//B = {(fm*pm^3* (-1 + fm)*(1-fm)*n_ttl   )/div;
	return (fm*pow(pm,3)*(-1.0 + fm)*(1.0-fm) )/div;
}
double Wmmm_llt(int mode){
	//B = {(fm*pm^3*(-fm^2*n_lll + (-1 + fm)*(n_ttl - fm*(n_tll + n_ttl))) + fm*(fm^2 - 3 fm*pm + 3*pm^2 - (3 + (-3 + fm)*fm) pm^3)*n_ttt)/(fm - pm)^3}
	//B = {(fm*pm^3*( (-1 + fm)*(- fm*(n_tll ))) )/div;
	double fm = Fm(mode);
	double pm = Pm(mode);
	double div = pow(fm-pm,3);	
	return (fm*pow(pm,3)* (1.0 - fm)*fm )/div;
}
double Wmmm_ttt(int mode){
	//B = {(fm*pm^3*(-fm^2*n_lll + (-1 + fm)*(n_ttl - fm*(n_tll + n_ttl))) + fm*(fm^2 - 3 fm*pm + 3*pm^2 - (3 + (-3 + fm)*fm) pm^3)*n_ttt)/(fm - pm)^3}
	//B = (  fm*(fm^2 - 3 fm*pm + 3*pm^2 - (3 + (-3 + fm)*fm) pm^3)*n_ttt)/(fm - pm)^3
	double fm = Fm(mode);
	double pm = Pm(mode);
	double div = pow(fm-pm,3);	
	return (  fm*(fm*fm - 3.0*fm*pm + 3.0*pm*pm - (3.0 + (-3.0 + fm)*fm)*pow(pm,3) ))/div;
}


//EEM 
//B = {(1/((fe - pe)^2 (fm - pm)))*(pe^2 pm (-fe^2 fm n_lll - (-1 + fe) fe fm n_telelm - fm n_tetelm + 2 fe fm n_tetelm - fe^2 fm n_tetelm + fe^2 n_tmlele - fe^2 fm n_tmlele - (-1 + fe) fe (-1 + fm) n_tmtele) + (fm (fe - pe)^2 - (fe^2 - 2 fe pe + ((-2 + fe) fe (-1 + fm) + fm) pe^2) pm) n_ttt)}
double Weem_lll(int mode ){
	//B = (pe^2*pm*(-fe^2*fm*n_lll - (-1 + fe)*fe*fm*n_telelm - fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm + fe^2*n_tmlele - fe^2*fm*n_tmlele - (-1 + fe)*fe*(-1 + fm)*n_tmtele) + (fm*(fe - pe)^2 - (fe^2 - 2*fe*pe + ((-2 + fe)*fe*(-1 + fm) + fm)*pe^2)*pm)*n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fe - pe,2) * (fm - pm);
	return (-pe*pe*pm*fe*fe*fm)/det;
}
double Weem_leletm(int mode ){
	//B = {(1/((fe - pe)^2 (fm - pm)))(pe^2 pm (-fe^2 fm n_lll - (-1 + fe) fe fm n_telelm - fm n_tetelm + 2 fe fm n_tetelm - fe^2 fm n_tetelm + fe^2 n_tmlele - fe^2 fm n_tmlele - (-1 + fe) fe (-1 + fm) n_tmtele) + (fm (fe - pe)^2 - (fe^2 - 2 fe pe + ((-2 + fe) fe (-1 + fm) + fm) pe^2) pm) n_ttt)}

	//B = (pe^2*pm*(  (1 - fe)*fe*fm*n_telelm - fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm + fe^2*n_tmlele - fe^2*fm*n_tmlele - (-1 + fe)*fe*(-1 + fm)*n_tmtele) )}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fe - pe,2) * (fm - pm);
	return  pe*pe*pm*( fe*fe*(1.0 - fm) )/det;
}

double Weem_telelm(int mode ){
	//B = {(1/((fe - pe)^2 (fm - pm)))(pe^2 pm (-fe^2 fm n_lll - (-1 + fe) fe fm n_telelm - fm n_tetelm + 2 fe fm n_tetelm - fe^2 fm n_tetelm + fe^2 n_tmlele - fe^2 fm n_tmlele - (-1 + fe) fe (-1 + fm) n_tmtele) + (fm (fe - pe)^2 - (fe^2 - 2 fe pe + ((-2 + fe) fe (-1 + fm) + fm) pe^2) pm) n_ttt)}

	//B = (pe*pe*pm*(  (1 - fe)*fe*fm*n_telelm - fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm + fe^2*n_tmlele - fe^2*fm*n_tmlele - (-1 + fe)*fe*(-1 + fm)*n_tmtele) )}
	//B = (pe*pe*pm*(  (1 - fe)*fe*fm*n_telelm - fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm - (-1 + fe)*fe*(-1 + fm)*n_tmtele) )}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fe - pe,2) * (fm - pm);
	return  (pe*pe*pm*(  (1.0 - fe)*fe*fm) )/det;
}
double Weem_tetelm(int mode ){
	//B = {(1/((fe - pe)^2 (fm - pm)))(pe^2 pm (-fe^2 fm n_lll - (-1 + fe) fe fm n_telelm - fm n_tetelm + 2 fe fm n_tetelm - fe^2 fm n_tetelm + fe^2 n_tmlele - fe^2 fm n_tmlele - (-1 + fe) fe (-1 + fm) n_tmtele) + (fm (fe - pe)^2 - (fe^2 - 2 fe pe + ((-2 + fe) fe (-1 + fm) + fm) pe^2) pm) n_ttt)}

	//B = (pe*pe*pm*(  (1 - fe)*fe*fm*n_telelm - fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm + fe^2*n_tmlele - fe^2*fm*n_tmlele - (-1 + fe)*fe*(-1 + fm)*n_tmtele) )}
	//B = (pe*pe*pm*(  -fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm - (-1 + fe)*fe*(-1 + fm)*n_tmtele) )}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fe - pe,2) * (fm - pm);
	return  (pe*pe*pm*(  -fm + 2.0*fe*fm - fe*fe*fm) )/det;
}

double Weem_tmtele(int mode ){
	//B = {(1/((fe - pe)^2 (fm - pm)))(pe^2 pm (-fe^2 fm n_lll - (-1 + fe) fe fm n_telelm - fm n_tetelm + 2 fe fm n_tetelm - fe^2 fm n_tetelm + fe^2 n_tmlele - fe^2 fm n_tmlele - (-1 + fe) fe (-1 + fm) n_tmtele) + (fm (fe - pe)^2 - (fe^2 - 2 fe pe + ((-2 + fe) fe (-1 + fm) + fm) pe^2) pm) n_ttt)}

	//B = (pe*pe*pm*(  (1 - fe)*fe*fm*n_telelm - fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm + fe^2*n_tmlele - fe^2*fm*n_tmlele - (-1 + fe)*fe*(-1 + fm)*n_tmtele) )}
	//B = (pe*pe*pm*( - (-1 + fe)*fe*(-1 + fm)*n_tmtele) )}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fe - pe,2) * (fm - pm);
	return  (pe*pe*pm*(1.0 - fe)*fe*(-1.0 + fm) )/det;
}

double Weem_ttt(int mode ){
	//B = {(1/((fe - pe)^2 (fm - pm)))(pe^2 pm (-fe^2 fm n_lll - (-1 + fe) fe fm n_telelm - fm n_tetelm + 2 fe fm n_tetelm - fe^2 fm n_tetelm + fe^2 n_tmlele - fe^2 fm n_tmlele - (-1 + fe) fe (-1 + fm) n_tmtele) + (fm (fe - pe)^2 - (fe^2 - 2 fe pe + ((-2 + fe) fe (-1 + fm) + fm) pe^2) pm) n_ttt)}
	//B = (pe^2*pm*(-fe^2*fm*n_lll - (-1 + fe)*fe*fm*n_telelm - fm*n_tetelm + 2*fe*fm*n_tetelm - fe^2*fm*n_tetelm + fe^2*n_tmlele - fe^2*fm*n_tmlele - (-1 + fe)*fe*(-1 + fm)*n_tmtele) + (fm*(fe - pe)^2 - (fe^2 - 2*fe*pe + ((-2 + fe)*fe*(-1 + fm) + fm)*pe^2)*pm)*n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fe - pe,2) * (fm - pm);
	return (fm*pow(fe - pe,2) - (fe*fe - 2.0*fe*pe + ((-2.0 + fe)*fe*(-1.0 + fm) + fm)*pe*pe)*pm)/det;
}

//EMM

double Wemm_lll(int mode ){
	//B = {(1/((fe - pe) (fm - pm)^2))*(pe pm^2 (-fm (fe fm n_lll + (-1 + fe) fm n_telmlm + (-1 + fm) ((-1 + fe) n_tetmlm + fe n_tmlmle)) - fe (-1 + fm)^2 n_tmtmle) + (fm pe (-1 + pm) (fm + (-2 + fm) pm) + fe (fm^2 - 2 fm pm - (-1 + (-1 + fm)^2 pe) pm^2)) n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = (fe - pe)*pow(fm - pm,2);
	//return (-pm*pm*pe*fm*fm*fe)/det;//converted
	return   (-pe*pm*pm*fm*fe*fm)/det; //matches.
}
double Wemm_lmlmte(int mode ){
	//B = {(1/((fe - pe) (fm - pm)^2))*(pe pm^2 (-fm (fe fm n_lll + (-1 + fe) fm n_telmlm + (-1 + fm) ((-1 + fe) n_tetmlm + fe n_tmlmle)) - fe (-1 + fm)^2 n_tmtmle) + (fm pe (-1 + pm) (fm + (-2 + fm) pm) + fe (fm^2 - 2 fm pm - (-1 + (-1 + fm)^2 pe) pm^2)) n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fm - pm,2) * (fe - pe);
	//return  pm*pm*pe*( fm*fm*(1.0 - fe) )/det;//converted 
	return   (pe*pm*pm*(fm*(1.0 - fe)*fm) )/det; //matches.
}

double Wemm_tmlmle(int mode ){
	//B = {(1/((fe - pe) (fm - pm)^2))*(pe pm^2 (-fm (fe fm n_lll + (-1 + fe) fm n_telmlm + (-1 + fm) ((-1 + fe) n_tetmlm + fe n_tmlmle)) - fe (-1 + fm)^2 n_tmtmle) + (fm pe (-1 + pm) (fm + (-2 + fm) pm) + fe (fm^2 - 2 fm pm - (-1 + (-1 + fm)^2 pe) pm^2)) n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fm - pm,2) * (fe - pe);
	//return  (pm*pm*pe*(  (1.0 - fm)*fm*fe) )/det;//converted
	return (pe*pm*pm*fm*(1.0 - fm)*fe )/det;//matches.
}

double Wemm_tmtmle(int mode ){
	//B = {(1/((fe - pe) (fm - pm)^2))*(pe pm^2 (-fm (fe fm n_lll + (-1 + fe) fm n_telmlm + (-1 + fm) ((-1 + fe) n_tetmlm + fe n_tmlmle)) - fe (-1 + fm)^2 n_tmtmle) + (fm pe (-1 + pm) (fm + (-2 + fm) pm) + fe (fm^2 - 2 fm pm - (-1 + (-1 + fm)^2 pe) pm^2)) n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fm - pm,2) * (fe - pe);
	//return  (pm*pm*pe*(  -fe + 2.0*fm*fe - fm*fm*fe) )/det;//converted; 
	return (pe*pm*pm*(  - fe*pow(1.0 - fm,2) ) )/det; //matches.
}

double Wemm_tetmlm(int mode ){
	//B = {(1/((fe - pe) (fm - pm)^2))*(pe pm^2 (-fm (fe fm n_lll + (-1 + fe) fm n_telmlm + (-1 + fm) ((-1 + fe) n_tetmlm + fe n_tmlmle)) - fe (-1 + fm)^2 n_tmtmle) + (fm pe (-1 + pm) (fm + (-2 + fm) pm) + fe (fm^2 - 2 fm pm - (-1 + (-1 + fm)^2 pe) pm^2)) n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fm - pm,2) * (fe - pe);
	//return  (pm*pm*pe*(1.0 - fm)*fm*(-1.0 + fe) )/det; //converetd
	return    (pe*pm*pm*fm*(1.0 - fm)*(-1.0 + fe) )/det; //matches.
}

double Wemm_ttt(int mode ){
	//B = {(1/((fe - pe) (fm - pm)^2))*(pe pm^2 (-fm (fe fm n_lll + (-1 + fe) fm n_telmlm + (-1 + fm) ((-1 + fe) n_tetmlm + fe n_tmlmle)) - fe (-1 + fm)^2 n_tmtmle) + (fm pe (-1 + pm) (fm + (-2 + fm) pm) + fe (fm^2 - 2 fm pm - (-1 + (-1 + fm)^2 pe) pm^2)) n_ttt)}
	double fe = Fe(mode);
	double fm = Fm(mode);
	double pe = Pe(mode);
	double pm = Pm(mode);
	double det = pow(fm - pm,2) * (fe - pe);
	//return (fe*pow(fm - pm,2) - (fm*fm - 2.0*fm*pm + ((-2.0 + fm)*fm*(-1.0 + fe) + fe)*pm*pm)*pe)/det;//converted
        return (fm*pe*(-1.0 + pm)*(fm + (-2.0 + fm)*pm) + fe*(fm*fm - 2.0*fm*pm - (-1.0 + pow(-1.0 + fm,2)*pe)*pm*pm))/det;//mathematica .
		//It's not immediately obvious, but this is equivolent ot the converted form. 
}


vector<double> optomizeFP_SFDL(int N_t0, int N_t1, int N_t2, bool ee){
	float pT53 = ee?Pe():Pm();
	float fT53 = ee?Fe():Fm();
	float bestRes = 10000.;
	double MinNegInsanity = (double) -N_t0-N_t1-N_t2-1;
	float bestP = 2;
	float bestF = 2;

	for(double p=0;p<=1.0;p+=0.01){
	for(double f=0;f<=1.0;f+=0.01){
		vector<double> results = SFDLbkg(f, p, N_t0, N_t1, N_t2);
		double thisNegInsanity = (results[0]<0?results[0]:0.) + (results[1]<0?results[1]:0.) + (results[2]<0?results[2]:0.);
		//output: {0:N_pp, 1:N_fp, 2:N_ff, 3:N_signal, 4:N_1fake, 5:N_2fakes, 6:N_bkg}
		if(MinNegInsanity<-0.00001){
			if(MinNegInsanity < thisNegInsanity){
			    MinNegInsanity = thisNegInsanity;
			    double thisRes=pow(p-pT53,2)+pow(f-fT53,2);
			    bestRes = thisRes; 
			    bestP = p;
			    bestF = f;
			}
		}
		else if(thisNegInsanity<-0.00001){
		    double thisRes=pow(p-pT53,2)+pow(f-fT53,2);
		    if(bestRes > thisRes){ 
			MinNegInsanity = thisNegInsanity;
			bestRes=thisRes;
			bestP = p;
			bestF = f;
		    }
		}
		//else continue; //this one is insane and something better has been found. 
	}}
	if(MinNegInsanity < -0.0001)
	    printf("After first round, the results are insane %f, p=%f vs PT53=%f, f=%f vs FT53=%f, res=%f\n",MinNegInsanity,bestP,pT53,bestF,fT53, bestRes);
	else printf("After first round, the results are sane; insanity = %f, p=%f vs PT53=%f, f=%f vs FT53=%f, res=%f\n",MinNegInsanity,bestP,pT53,bestF,fT53, bestRes);
	

	double p_center = bestP;	
	double f_center = bestF;	
	for(double p=p_center-0.01;p<=p_center+0.01;p+=0.0001){
	for(double f=f_center-0.01;f<=f_center+0.01;f+=0.0001){
		vector<double> results = SFDLbkg(f, p, N_t0, N_t1, N_t2);
		double thisNegInsanity = (results[0]<0?results[0]:0.) + (results[1]<0?results[1]:0.) + (results[2]<0?results[2]:0.);
		//output: {0:N_pp, 1:N_fp, 2:N_ff, 3:N_signal, 4:N_1fake, 5:N_2fakes, 6:N_bkg}
		if(MinNegInsanity<-0.00001){
			if(MinNegInsanity < thisNegInsanity){
			    MinNegInsanity = thisNegInsanity;
			    double thisRes=pow(p-pT53,2)+pow(f-fT53,2);
			    bestRes = thisRes; 
			    bestP = p;
			    bestF = f;
			}
		}
		else if(thisNegInsanity<-0.00001){
		    double thisRes=pow(p-pT53,2)+pow(f-fT53,2);
		    if(bestRes > thisRes){ 
			bestRes=thisRes;
			bestP = p;
			bestF = f;
		    }
		}
		//else continue; //this one is insane and something better has been found. 
	}}

	if(MinNegInsanity < -0.0001)
	    printf("After second round, the results are insane %.1f, p=%f vs PT53=%f, f=%f vs FT53=%f, res=%f\n",MinNegInsanity,bestP,pT53,bestF,fT53, bestRes);
	else printf("After second round, the results are sane; insanity = %f, p=%f vs PT53=%f, f=%f vs FT53=%f, res=%f\n",MinNegInsanity,bestP,pT53,bestF,fT53, bestRes);

	return SFDLbkg(bestF, bestP, N_t0, N_t1, N_t2);	
}//end optomizeFP_SFDL

TCanvas* exploreFP_SF(int N_t0, int N_t1, int N_t2){
	TH2F* FPmap = new TH2F(("FPvalidity_"+to_string(N_t2)).c_str(),
		("FP validity with N_tt="+to_string(N_t2)+", N_tl="+to_string(N_t1)+", N_ll="+to_string(N_t0)+";f;p").c_str(),1000,0,1,1000,0,1);
	int worst = -(N_t0+N_t1+N_t2);

	for(double p=0;p<=1.0;p+=0.001){
	for(double f=0;f<=1.0;f+=0.001){
		vector<double> results = SFDLbkg(f, p, N_t0, N_t1, N_t2);
		double thisNegInsanity = (results[0]<0?results[0]:0.) + (results[1]<0?results[1]:0.) + (results[2]<0?results[2]:0.);
		if(thisNegInsanity<-0.00001){
			FPmap->Fill(f,p,-1);
			//FPmap->Fill(f,p,thisNegInsanity);
		}
		else FPmap->Fill(f,p);
	}}
	TCanvas *c = newTCanvas(("cFPvalidity_"+to_string(N_t2)).c_str(), ("FP validity with N_tt="+to_string(N_t2)+", N_tl="+to_string(N_t1)+", N_ll="+to_string(N_t0)).c_str());
	PrettyCanvas(c);
	PrettyHist(FPmap);
/*	const int NRGBs = 3, NCont = 50;
	Double_t insanity[NRGBs] = {(Double_t)worst,0.,1.};
	Double_t red[NRGBs]  = {1.,0.,0.};
	Double_t green[NRGBs] = {0.,0.,1.};
	Double_t blue[NRGBs]  = {0.,0.,0.};
	gStyle->SetNumberContours(NCont);
	TColor::CreateGradientColorTable(NRGBs, insanity, red, green, blue, NCont);*/
	FPmap->Draw("colz");
	return c;
}//end exploreFP_SF

TCanvas* exploreFP_SFint(int N_t0, int N_t1, int N_t2,int n_t0, int n_t1, int n_t2){
	TH2F* FPmap = new TH2F(("FPvalidity_"+to_string(N_t2)).c_str(), "Intersection of Validity between OS and SS;f;p", 1000,0,1,1000,0,1);

	for(double p=0;p<=1.0;p+=0.001){
	for(double f=0;f<=1.0;f+=0.001){
		vector<double> results  = SFDLbkg(f, p, N_t0, N_t1, N_t2);
		vector<double> results2 = SFDLbkg(f, p, n_t0, n_t1, n_t2);
		double thisNegInsanity  = (results[0]<0?results[0]:0.) + (results[1]<0?results[1]:0.) + (results[2]<0?results[2]:0.);
		double thisNegInsanity2 = (results2[0]<0?results2[0]:0.) + (results2[1]<0?results2[1]:0.) + (results2[2]<0?results2[2]:0.);
		if(thisNegInsanity<-0.00001 or thisNegInsanity2<-0.00001){
			FPmap->Fill(f,p,-1);
			//FPmap->Fill(f,p,thisNegInsanity);
		}
		else FPmap->Fill(f,p);
	}}
	TCanvas *c = newTCanvas(("cFPvalidity_"+to_string(N_t2)).c_str(), ("FP validity with N_tt="+to_string(N_t2)+", N_tl="+to_string(N_t1)+", N_ll="+to_string(N_t0)).c_str());
	PrettyCanvas(c);
	PrettyHist(FPmap);
	FPmap->Draw("colz");
	return c;
}//end exploreFP_SFint



#endif
