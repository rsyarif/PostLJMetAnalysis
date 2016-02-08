#ifndef _UTILITIES_H // if not defined
#define _UTILITIES_H

#include <iostream>
#include "math.h"
#include "TMath.h"
#include "THStack.h"
#include "TList.h"
#include "TRandom2.h"
#include "TString.h"
#include <TFile.h> 
#include <TTree.h> 
#include "TH2.h"
#include <vector>
#include <map>
#include <fstream>
#include "TStopwatch.h"
#include "TLorentzVector.h"
#include "TVector2.h"
#include <sys/stat.h>  //needed for fileExists
#include "TGraph.h"
using namespace std;

void m(int i);
bool aeq(float A, float B, int scale=5);
bool strCmp(string a, string b); //a == b
bool is_real(float x);
TString RandomString(int length);
bool fileExists(std::string fname);
//vector geometry and operations
float dPhi(float phi1, float phi2);
float dPhi(TLorentzVector A, TLorentzVector B);
float phi_0_2pi(float phi);
float phi_negpi_pi(float phi);
float phi_0_pi(float phi);
float dR(TLorentzVector A, TLorentzVector B);
inline Double_t Mt2(TLorentzVector v); //Transverse mass squared. 
inline Double_t Mt(TLorentzVector  v); //Transverse mass
inline Double_t Mt(TLorentzVector  v, float met, float metphi); 
float Dot(TVector2 a, TVector2 b);//take the dotproduct of 2 TVector2's 
float ThetaStar(TLorentzVector & a,TLorentzVector & b);
TVector2* TransverseVec(TLorentzVector& v);//return the transverse vector <Px,Py>
//map operations.
inline bool is_in_map(std::map<string,int> themap, string thestring);
inline bool is_in_map(std::map<string,float> themap, string thestring);
inline bool is_in_map(std::map<string,double> themap, string thestring);
inline bool is_in_map(std::map<string,string> themap, string thestring);
inline bool is_in_map(std::map<string,TH1*> themap, string thestring);
inline bool is_in_map(std::map<string,TH2*> themap, string thestring);
inline bool is_in_map(std::map<string,TFile*> themap, string thestring);
void printmap(std::map<string,string> themap, int format = 0);
void printmap(std::map<string,double> themap, int format = 0);
void printmap(std::map<string,float> themap, int format = 0);
void printmap(std::map<string,int> themap, int format = 0);

//Histogram operations
void NameHist(TH1F* h, string rootname, string title);
void printHist(TH1F* h);
bool histisempty(TH1F* h);
TH1F* Clone(TH1F* h);
TH1F* vslice(TH2F* h, int bin);
TH1F* hslice(TH2F* h, int bin);
TH2F* DivideHists(TH2F* numerator, TH2F* denominator, int mode=0);
TH1F* DivideHists(TH1F* numerator, TH1F* denominator, int mode=0);
TH2F* MultiplyHists(TH2F* A, TH2F* B);
TH1F* MultiplyHists(TH1F* A, TH1F* B);
TH1F* InvertHists(TH1F* A);
TH2F* InvertHists(TH2F* A);
void Sqrt(TH1F* hin); //takes the bin-by-bin sqrt, hin = sqrt(hin)
TH2F* SQRT(TH2F* hin); //returns bin-by-bin sqrt, without altering hin
TH1F* SQRT(TH1F* hin);
TH1F* AddOverflow(TH1F* h);
TH2F* AddOverflow(TH2F* h);
TH2F* AddOverflowX(TH2F* h);
void fixNAN(TH1F* h,float nonsenceval=-1.0, float nonsenceerr = 0);
TH1F* ForcePositive(TH1F* h);
TGraph* makeband(TGraph* A, TGraph* B, int color);
TGraph* makeband_0guard(TGraph* A, TGraph* B, int color);
THStack * RebinTHStack(THStack* stack, int nbins, Double_t newbins[]);
void ExcludeAfter(TH1F* h,float val);
void blind(TH1F* h, float from, float to);

//Razor variables
float razorMR(TLorentzVector &j1, TLorentzVector &j2);
float razorMTR(float& met, float& metPhi, TLorentzVector& j1, TLorentzVector& j2);
float razorR(float& met, float& metPhi, TLorentzVector& j1, TLorentzVector& j2);

//how are these not built in?
int max(int a, int b);
float max(float a, float b);
double max(double a, double b);
double max(float a, double b);
double max(double a, float b);
float max(int a, float b);
float max(float a, int b);
double max(int a, double b);
double max(double a, int b);
int min(int a, int b);
float min(float a, float b);
double min(double a, double b);
double min(float a, double b);
double min(double a, float b);
float min(int a, float b);
float min(float a, int b);
double min(int a, double b);
double min(double a, int b);

int btreeSearch(float x, std::vector<float>ranges);
int btreeSearch(float x, float ranges[], int size);

	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void m(int i){ cout<<"mark "<<i<<endl; }

	//aproxomately equals function
	//test if A and B are within 10^-scale of each other
bool aeq(float A, float B, int scale ){
	if(A>(B-pow(10,-1*scale)) && A<(B+pow(10,-1*scale))) return true;
	else return false;
}

bool strCmp(string a, string b){
        //returns true if strings match; a == b
        return a.compare(b) == 0 && b.compare(a) == 0;
}

bool is_real(float x){
	if(TMath::IsNaN(x)) return false;
	return TMath::Finite(x);
}

bool histisempty(TH1F* h){
	bool empty = true;
	for(int i=1;i<=h->GetNbinsX();i++) empty &= aeq(0.0f,h->GetBinContent(i));
	return empty;
}

void printHist(TH1F* h){
	printf("integral %i\n",(int)h->Integral());
	TAxis *x = h->GetXaxis();
	printf("bin    Range                    val+- Error\n");
	printf("underflow bin                  %f +- %f\n", h->GetBinContent(0),h->GetBinError(0));
	for(int i=1;i<=h->GetNbinsX();i++){
		printf("bin %i %f-%f        %f +- %f\n",i,x->GetBinLowEdge(i),x->GetBinUpEdge(i), h->GetBinContent(i),h->GetBinError(i));
	} 
	int j = h->GetNbinsX()+1;
	printf("overflow bin                   %f +- %f\n", h->GetBinContent(j),h->GetBinError(j));
}

void NameHist(TH1F* h, string rootname, string title){
	h->SetName(rootname.c_str());
	h->SetTitle(title.c_str());
}

TString RandomString(int length){
 //returns a TString of (length) random upper and lower case letters 
 //TString f = RandomString(12) // f = JxcDLbEaRpAR
 //good for random titles. 
	TString randstring("");
	static TRandom2 * r = new TRandom2();
	while (length > 0) {
		length--;
		int j = r->Integer(52); //25ns per call
		if (j<26) j += 65;//A
		else j += 71;
		randstring.Append((char)j);
	}
	return randstring;
} // end RandomString

float dPhi(float phi1, float phi2){
	//returns dPhi on [0,pi]
	float dphi = fabs(phi1 - phi2);
	if (dphi > 3.14159265359) return 6.28318530718 - dphi;
	return dphi;
}
float dPhi(TLorentzVector A, TLorentzVector B){ return dPhi(A.Phi(),B.Phi()); }
float dR(TLorentzVector A, TLorentzVector B){
	float dphi = dPhi(A.Phi(),B.Phi());
	float dEta = fabs(A.Eta() - B.Eta());
	return sqrt(dphi*dphi  +  dEta*dEta);
}
float phi_0_2pi(float phi){ //forces phi to be on 0..2pi
	if(phi >= 0) return phi;
	else return 6.28318530718 + phi;
}
float phi_negpi_pi(float phi){ //forces phi to be on 0..2pi
	if(phi >= 3.14159265359) return phi - 6.28318530718;
	else return phi;
}
float phi_0_pi(float phi){ //forces phi to be on 0,pi, folds 0-2pi back to 0-pi
	phi = fabs(phi);
	if (phi > 3.14159265359) return 6.28318530718 - phi;
	return phi;
}

TVector2* TransverseVec(TLorentzVector& v){return new TVector2(v.X(),v.Y());}

//why is this not built into TVector2?
float Dot(TVector2 a, TVector2 b){return a.Mod()*b.Mod()*cos(a.DeltaPhi(b)); }

//float Mt(TLorentzVector x){return sqrt(x.E()*x.E() - x.Perp2());}
	//sqrt(E^2 - Pt^2)
	
inline Double_t Mt2(TLorentzVector v){
        return v.E()*v.E() - v.Perp2(); // this line is the whole purpose. It uses the correct def of Mt
}
inline Double_t Mt(TLorentzVector v){
        Double_t mm = Mt2(v);
	return mm < 0.0 ? -TMath::Sqrt(-mm) : TMath::Sqrt(mm);
}
Double_t Mt(TLorentzVector  v, Double_t met, Double_t metphi){
    //expects phi in radians. 
	Double_t mm = 2.0* met * v.Et() *( 1.0 - TMath::Cos(metphi - v.Phi() ) );
	return mm < 0.0 ? -TMath::Sqrt(-mm) : TMath::Sqrt(mm);
}

//For a reference into Razor variables, see SUS-12-005 or this
//https://www.evernote.com/shard/s31/sh/8f76fb8e-84b8-4174-bd16-cd5062ef5761/8aa98aa9f0ceec9b6656813e5ff9c40c
float razorMR(TLorentzVector &j1, TLorentzVector &j2){
	return sqrt(pow((j1.Vect().Mag() + j2.Vect().Mag()),2) - pow((j1.Z() + j2.Z()),2));
}

float razorMTR(float& met, float& metPhi, TLorentzVector& j1, TLorentzVector& j2){
	TVector2 MET;
	MET.SetMagPhi(met,metPhi);
	TVector2* j1t = TransverseVec(j1);
	TVector2* j2t = TransverseVec(j2);
	return sqrt(0.5*(met*(j1t->Mod() + j2t->Mod()) - Dot(MET,*j1t + *j2t)));
}
float razorR(float& met, float& metPhi, TLorentzVector& j1, TLorentzVector& j2){
	float Mr = razorMR(j1,j2);
	if(Mr == 0) return 0;
	return razorMTR(met,metPhi,j1,j2)/Mr;
}

float ThetaStar(TLorentzVector & a,TLorentzVector & b){
    //calculate cos(theta*), the angle between the two vectors  in their center of mass frame.

    TLorentzVector A(a); //copy A so we dont' spoil the origional
    TLorentzVector sum = a + b;
	TVector3 xhat(1,0,0);//x_hat unit vector
    TVector3 axis = (sum.Vect().Cross(xhat)).Unit(); //get rot axis by which to rotate sum to x-axis
    A.Rotate(sum.Angle(xhat),axis); //Rotate the sum to lie along the x-axis
    A.Boost(-sum.Beta(),0,0); //boost along the x-axis to move to CM frame
    return fabs(A.Vect() * xhat)/A.Vect().Mag(); //get cos(theta) w.r.t. x-axis/boost direction.
}//end 

/*float slowThetaStar(TLorentzVector a,TLorentzVector b){
                        //calculate cos(theta*), the angle between the two vectors  in their center of mass frame.
			//I keep this comment because the derrivaiton is a little clearer
                TLorentzVector A(a);
                TLorentzVector B(b);
                TLorentzVector sum = a + b;

                TVector3 v3sum = sum.Vect();//get the spacial vector.                
		TVector3 xhat(1,0,0);//x_hat unit vector
                TVector3 axis = (v3sum.Cross(xhat)).Unit();
                double theta = sum.Angle(xhat);
                printf("sum before: E %.1f P %.1f Px %.1f Py %.1f Pz %.1f\n",sum.E(),sum.P(),sum.Px(),sum.Py(),sum.Pz());
                printf("axis: x %.2f y %.2f z %.2f theta %.2f \n",axis.Px(),axis.Py(),axis.Pz(),theta);
                sum.Rotate(theta,axis); //rotate so that sum is parallel with the x-axis. This makes the boost 1D
                A.Rotate(theta,axis);
                B.Rotate(theta,axis);
		printf("sum afterR: E %.1f P %.1f Px %.1f Py %.1f Pz %.1f\n",sum.E(),sum.P(),sum.Px(),sum.Py(),sum.Pz());
                double beta = sum.Beta();
                sum.Boost(-beta,0,0);
                A.Boost(-beta,0,0);
                B.Boost(-beta,0,0);
                //these are now in the center of mass frame. and the boost is along xhat
                //A and B are identically back to back. So it doesn't matter which one we choose. 
//              printf("sum afterB: E %.1f P %.1f Px %.1f Py %.1f Pz %.1f\n",sum.E(),sum.P(),sum.Px(),sum.Py(),sum.Pz());
                TVector3 Aprime = A.Vect().Unit();
                //TVector3 p1prime = B.Vect().Unit();
                //printf("p0prime: x %.2f y %.2f z %.2f \n",p0prime.Px(),p0prime.Py(),p0prime.Pz());
                return fabs(Aprime * xhat/Aprime.Mag());
}//end */

void fixNAN(TH1F* h,float nonsenceval, float nonsenceerr){
	for(int i=0;i<= h->GetNbinsX(); i++){
		if(TMath::IsNaN(h->GetBinContent(i)) || !TMath::Finite(h->GetBinContent(i)) ||
		   TMath::IsNaN(h->GetBinError(i)) || !TMath::Finite(h->GetBinError(i))){
			h->SetBinContent(i,nonsenceval);
			h->SetBinContent(i,nonsenceerr);
		}//end if something is wrong with it.
	}//end for.
}//end fixNAN

TH1F* ForcePositive(TH1F* h){
	//This forces the content of the histogram to be positive; dealing with negative weights. 
	//It preserves the histogram's integral. 	
	float int_before = h->Integral();
	int nb = h->GetNbinsX();
	for(int i=1;i<=nb;++i){
		if(h->GetBinContent(i) < 0) h->SetBinContent(i,0);	
	}
	float int_after = h->Integral();
	if(fabs(int_after) > 0.000001) h->Scale(int_before/int_after);
	return h;
}

TH1F* AddOverflow(TH1F* h){
		//merges the overflow bin and the last bin.
	int nb = h->GetNbinsX();
	float lastbin = h->GetBinContent(nb);
	float overflow = h->GetBinContent(nb+1);
	float lbErr = h->GetBinError(nb);
	float ofError = h->GetBinError(nb+1);

	h->SetBinContent(nb,lastbin+overflow);
	h->SetBinError(nb,sqrt(lbErr*lbErr + ofError*ofError)  );
	h->SetBinContent(nb+1,0.0);
	h->SetBinError(nb+1,0.0);
	return h;
}
TH2F* AddOverflow(TH2F* h){
		//merges the overflow bin and the last bin.
	int nbx = h->GetNbinsX();
	int nby = h->GetNbinsY();
	//add in the top edge
	for(int i=1;i<=nbx;i++){
	    float lastbin = h->GetBinContent(i,nby);
	    float overflow = h->GetBinContent(i,nby+1);
	    float lbErr = h->GetBinError(i,nby);
	    float ofError = h->GetBinError(i,nby+1);
	    h->SetBinContent(i,nby,lastbin+overflow);
	    h->SetBinError(i,nby,sqrt(lbErr*lbErr + ofError*ofError)  );
	    h->SetBinContent(i,nby+1,0.0);
	    h->SetBinError(i,nby+1,0.0);
	}
	//add in the right edge. 
	for(int j=1;j<=nby;j++){
	    float lastbin = h->GetBinContent(nbx,j);
	    float overflow = h->GetBinContent(nbx+1,j);
	    float lbErr = h->GetBinError(nbx,j);
	    float ofError = h->GetBinError(nbx+1,j);
	    h->SetBinContent(nbx,j,lastbin+overflow);
	    h->SetBinError(nbx,j,sqrt(lbErr*lbErr + ofError*ofError)  );
	    h->SetBinContent(nbx+1,j,0.0);
	    h->SetBinError(nbx+1,j,0.0);
	}
	//add in the corner 
	float lastbin = h->GetBinContent(nbx,nby);
	float overflow = h->GetBinContent(nbx+1,nby+1);
	float lbErr = h->GetBinError(nbx,nby);
	float ofError = h->GetBinError(nbx+1,nby+1);

	h->SetBinContent(nbx,nby,lastbin+overflow);
	h->SetBinError(nbx,nby,sqrt(lbErr*lbErr + ofError*ofError)  );
	h->SetBinContent(nbx+1,nby+1,0.0);
	h->SetBinError(nbx+1,nby+1,0.0);
	return h;
}

TH2F* AddOverflowX(TH2F* h){
        //merge overflow from the right edge only
        int nbx = h->GetNbinsX();
        for(int j=1;j<=h->GetNbinsY()+1;j++){
            float lastbin = h->GetBinContent(nbx,j);
            float overflow = h->GetBinContent(nbx+1,j);
            float lbErr = h->GetBinError(nbx,j);
            float ofError = h->GetBinError(nbx+1,j);
            h->SetBinContent(nbx,j,lastbin+overflow);
            h->SetBinError(nbx,j,sqrt(lbErr*lbErr + ofError*ofError)  );
            h->SetBinContent(nbx+1,j,0.0);
            h->SetBinError(nbx+1,j,0.0);
        }
        return h;
} //end AddOverflowX

void ExcludeAfter(TH1F* h,float val){
		//hids/blinds bins with with x >= val by making them 0.
		//if val lands in the middle of a bin, the bin gets hidden
		//also hids the overflow bin. 
	int binstart = h->FindBin(val);
	int nb = h->GetNbinsX();
	for(int ibin = binstart; ibin <= nb+1; ibin++){
		h->SetBinContent(ibin,0);
		h->SetBinError(ibin,0);
	}
}//end ExcludeAfter

void blind(TH1F* h, float from, float to){
	//blinds a histogram between x-values from-to
	int binlow = h->FindBin(from);
	int binhigh = h->FindBin(to);
	for(int i=binlow;i<=binhigh;i++){
		h->SetBinContent(i,0);
		h->SetBinError(i,0);
	}
}//end blind

class probe{
/*
This gives a quick cout function for probing lines and also gives time measurements to understand code efficiency. 
Define a probe at the start. 
p("message to print to terminal");//simplified cout, adds time stamp 
put a ppush before a loop or block to start a new coutner. the string becomes it's name and gets printed
ppop to remove a counter
pall prints the last n counters defined along with your message. just neglect n to print all. 
*/
public:
	probe(string s = "begin probe");
	void p(string s);
	void ppush(string s, bool silent = false);
	void ppop(bool silent = false);
	void pall(string s,int n=-1);
private:
	std::vector<TStopwatch*> vts;
	std::vector<string> vs;
	double tinstant;
};
probe::probe(string s){
	vts.push_back(new TStopwatch());
	vs.push_back(s);
	vts[0]->Start();
	tinstant = vts[0]->RealTime();
	vts[0]->Continue();
}
void probe::p(string s){
		//prints your message s and tells the time since the last push or the start. 
	printf("%s %.3f ms\n",s.c_str(),(vts.back()->RealTime() - tinstant)*1000.0);
	vts.back()->Continue();
}
void probe::ppush(string s, bool silent){
		//make a new timer, add it to the list, start it, give it a name s, print s unless silent
	if(!silent) p(Form("start %s",s.c_str()));
	vs.push_back(s);
	vts.push_back(new TStopwatch());
	vts.back()->Start();
}

void probe::ppop(bool silent){
		//removes the last timer and tell how long it ran (unless silent)
	if(!silent) p(Form("finished %s",vs.back().c_str()));
	vs.pop_back();
	vts.pop_back();
}
void probe::pall(string s,int n){
		//print s and print the last n timers. 
	int nst = (int)vts.size();
	printf("%s\n",s.c_str());
	if (n == -1 || n >= nst) {
		n = nst;
	}
		std::vector<TStopwatch*>::reverse_iterator vit = vts.rbegin();
		std::vector<string>::reverse_iterator sit = vs.rbegin();
		while (vit != vts.rend()-(nst-n)) {
			printf("probe %s took %.3f ms\n",(*sit).c_str(),((*vit)->RealTime()-tinstant)*1000.0);
			vit++; sit++;
		}
		for(std::vector<TStopwatch*>::reverse_iterator it = vts.rbegin(); it != vts.rend()-(nst-n); ++it) (*it)->Continue();
}//end pall

bool fileExists(std::string filename){
		//returns true if a file exists
		//if file doesn't exist, runs in 0.72 microseconds
		//if file exists and is 500MB, runs in 0.93 microseconds
    struct stat buf;
    return stat(filename.c_str(), &buf) != -1;

		/*alternatively could do
			ifstream infile(filename.data());
			return (bool) infile;
		//requires 2.36 microseconds if the file doesn't exist
		//requires 17.4 microseconds for a 500MB file */
}

TGraph* makeband(TGraph* A, TGraph* B, int color){
		//Takes two TGraphs, presumably parallel..
		//makes a third TGraph that is a loop connecting the end of one to the start of the other
		//it closes the loop so you can plot it as a band. 
	int nA = A->GetN();
	int nB = B->GetN();
	int npoints = nA + nB + 1;
	Double_t x[npoints];
	Double_t y[npoints];
	for (int i = 0; i<nA; i++) {
		Double_t tmpx, tmpy;
		A->GetPoint(i,tmpx,tmpy);
		x[i]=tmpx;
		y[i]=tmpy;
		cout<<"A: x="<<tmpx<<" y="<<tmpy<<endl;
	}
	for (int i = 0; i<nB; i++) {
		Double_t tmpx, tmpy;
		B->GetPoint(nB-1-i,tmpx,tmpy);
		x[i+nA]=tmpx;
		y[i+nA]=tmpy;
		cout<<"B: x="<<tmpx<<" y="<<tmpy<<endl;
	}
	
	cout<<"EndPoint: x="<<x[0]<<" y="<<y[0]<<endl;
	x[npoints-1]=x[0];
	y[npoints-1]=y[0];
	TGraph* out = new TGraph(npoints,x,y);
	out->SetFillColor(color);
	return out;
}//end makeband
TGraph* makeband_0guard(TGraph* A, TGraph* B, int color){
		//Takes two TGraphs, presumably parallel..
		//makes a third TGraph that is a loop connecting the end of one to the start of the other
		//it closes the loop so you can plot it as a band. 
	int nA = 0;
	int nB = 0;
	for (int i = 0; i<A->GetN(); i++) {
		Double_t tmpx, tmpy;
		A->GetPoint(i,tmpx,tmpy);
		if(tmpx!=0 && tmpy!=0) nA++;
	}
	for (int i = 0; i<B->GetN(); i++) {
		Double_t tmpx, tmpy;
		B->GetPoint(i,tmpx,tmpy);
		if(tmpx!=0 && tmpy!=0) nB++;
	}
	int npoints = nA + nB + 1;
	Double_t x[npoints];
	Double_t y[npoints];
	for (int i = 0; i<nA; i++) {
		Double_t tmpx, tmpy;
		A->GetPoint(i,tmpx,tmpy);
		x[i]=tmpx;
		y[i]=tmpy;
		cout<<"i="<<i<<" A: x="<<tmpx<<" y="<<tmpy<<endl;
	}
	for (int i = 0; i<nB; i++) {
		Double_t tmpx, tmpy;
		B->GetPoint(nB-1-i,tmpx,tmpy);
		x[i+nA]=tmpx;
		y[i+nA]=tmpy;
		cout<<"i="<<i+nA<<" B: x="<<tmpx<<" y="<<tmpy<<endl;
	}
	
	cout<<"i="<<npoints-1<<" EndPoint: x="<<x[0]<<" y="<<y[0]<<endl;
	x[npoints-1]=x[0];
	y[npoints-1]=y[0];
	TGraph* out = new TGraph(npoints,x,y);
	out->SetFillColor(color);
	return out;
}//end makeband

void Sqrt(TH1F* hin){
	//hin = sqrt(hin)
	for (int ibin=0; ibin<= hin->GetXaxis()->GetNbins(); ++ibin) {
		float rootbin = sqrt(hin->GetBinContent(ibin));
		hin->SetBinContent(ibin,rootbin);
		hin->SetBinError(ibin,0.5f*hin->GetBinError(ibin)/rootbin);
	}
}//end Sqrt

TH1F* SQRT(TH1F* hin){
	//out= sqrt(hin)
	TH1F* out = (TH1F*) hin->Clone((string(hin->GetName())+"_sqrt").c_str());
	for (int ibin=0; ibin<= hin->GetXaxis()->GetNbins()+1; ++ibin) {
		float bincontent = hin->GetBinContent(ibin);
		float rootbin;
		if(bincontent <0) rootbin = -sqrt(-bincontent);
		else rootbin = sqrt(bincontent);
		out->SetBinContent(ibin,rootbin);
		out->SetBinError(ibin,0.5f*hin->GetBinError(ibin)/rootbin);
	}
	return out;
}//end Sqrt

TH2F* SQRT(TH2F* hin){
	//out= sqrt(hin)
	TH2F* out = (TH2F*) hin->Clone((string(hin->GetName())+"_sqrt").c_str());
	for (int ibin=0; ibin<= hin->GetXaxis()->GetNbins()+1; ++ibin) {
	    for (int jbin=0; jbin<= hin->GetYaxis()->GetNbins()+1; ++jbin) {
		float bincontent = hin->GetBinContent(ibin,jbin);
		float rootbin;
		if(bincontent <0) rootbin = -sqrt(-bincontent);
		else rootbin = sqrt(bincontent);
		out->SetBinContent(ibin,jbin,rootbin);
		out->SetBinError(ibin,jbin,0.5f*hin->GetBinError(ibin)/rootbin);
	    }
	}
	return out;
}//end Sqrt

THStack * RebinTHStack(THStack* stack, int nbins, Double_t newbins[]){
	//Rebin the stack (replaces the existing object) 
	THStack * newstack = new THStack(Form("%s_rebin",stack->GetName()),stack->GetTitle());

	//In case the end of right end of the new set of bins is past the right end of the old axis, handel it properly. 
	const int nbinsS = nbins;
	Double_t newbins_temp[nbinsS+1];
	for(int j=0;j<nbinsS+1;++j) newbins_temp[j] = newbins[j];

	TList* hists = stack->GetHists();
	TIter next(hists);
	bool first = true;
	TObject *obj;
	while ((obj = next())){
		TH1* hobj = (TH1*)obj;
		if(first){
			TAxis* X = hobj->GetXaxis(); 
			newbins_temp[nbinsS] = X->GetBinUpEdge(X->GetLast());
			first = false;
		}
		TH1* temp     = hobj->Rebin(nbinsS,"temp",newbins_temp); 
		TH1* thishist = hobj->Rebin(nbinsS,Form("%s_rebin",hobj->GetName()),newbins);//unhappy
		thishist->SetBinContent(nbinsS, temp->GetBinContent(nbinsS));
		thishist->SetBinError(  nbinsS, temp->GetBinError(nbinsS));
		newstack->Add(thishist);
	}
	return newstack;
	//stack = newstack;
}//end RebinTHStack

inline bool is_in_map(std::map<string,int> themap, string thestring){ return themap.find(thestring) != themap.end(); }
inline bool is_in_map(std::map<string,float> themap, string thestring){ return themap.find(thestring) != themap.end(); }
inline bool is_in_map(std::map<string,double> themap, string thestring){ return themap.find(thestring) != themap.end(); }
inline bool is_in_map(std::map<string,string> themap, string thestring){ return themap.find(thestring) != themap.end(); }
inline bool is_in_map(std::map<string,TH1*> themap, string thestring){ return not (themap.find(thestring) == themap.end()); }
inline bool is_in_map(std::map<string,TH2*> themap, string thestring){ return themap.find(thestring) != themap.end(); }
inline bool is_in_map(std::map<string,TFile*> themap, string thestring){ return themap.find(thestring) != themap.end(); }


void printmap(std::map<string,int> themap, int format){
	switch (format){
		case 0:
			//format 0:
			//apples 	1
			//bananas 	3
			for( std::map<string,int>::iterator i=themap.begin(); i!=themap.end(); ++i){
				cout << (*i).first << " \t" << (*i).second << endl;
			}
			break;
		case 1:
			//format 1:
			//1 	apples
			//3 	bananas
			for( std::map<string,int>::iterator i=themap.begin(); i!=themap.end(); ++i){
				cout << (*i).second << " \t" << (*i).first << endl;
			}
			break;
		default:
			cout<<"printmap needs a valid format int"<<endl;
			break;
	}//end switch
}//end printmap int

void printmap(std::map<string,float> themap, int format){
	switch (format){
		case 0:
			//format 0:
			//apples 	1
			//bananas 	3
			for( std::map<string,float>::iterator i=themap.begin(); i!=themap.end(); ++i){
				cout << (*i).first << " \t" << (*i).second << endl;
			}
			break;
		case 1:
			//format 1:
			//1 	apples
			//3 	bananas
			for( std::map<string,float>::iterator i=themap.begin(); i!=themap.end(); ++i){
				cout << (*i).second << " \t" << (*i).first << endl;
			}
			break;
		default:
			cout<<"printmap needs a valid format int"<<endl;
			break;
	}//end switch
}//end printmap float

void printmap(std::map<string,double> themap, int format){
	switch (format){
		case 0:
			//format 0:
			//apples 	1
			//bananas 	3
			for( std::map<string,double>::iterator i=themap.begin(); i!=themap.end(); ++i){
				cout << (*i).first << " \t" << (*i).second << endl;
			}
			break;
		case 1:
			//format 1:
			//1 	apples
			//3 	bananas
			for( std::map<string,double>::iterator i=themap.begin(); i!=themap.end(); ++i){
				cout << (*i).second << " \t" << (*i).first << endl;
			}
			break;
		default:
			cout<<"printmap needs a valid format int"<<endl;
			break;
	}//end switch
}//end print double

void printmap(std::map<string,string> themap, int format){
	switch (format){
		case 0:
			//format 0:
			//apples 	1
			//bananas 	3
			for( std::map<string,string>::iterator i=themap.begin(); i!=themap.end(); ++i){
				cout << (*i).first << " \t" << (*i).second << endl;
			}
			break;
		case 1:
			//format 1:
			//1 	apples
			//3 	bananas
			for( std::map<string,string>::iterator i=themap.begin(); i!=themap.end(); ++i){
				cout << (*i).second << " \t" << (*i).first << endl;
			}
			break;
		default:
			cout<<"printmap needs a valid format int"<<endl;
			break;
	}//end switch
}//end printmap string
/*TH1F* Clone(TH1F* h){
	//You're writing this because the root built-in Clone function doesn't work. 
	//If you take a file, read in a histogram, clone, it, and close the file: the clone gets whacked. 
	int nx = h->GetNbinsX();
	string name(h->GetName());
	string title(h->GetTitle());

	//snatch the binning
	float *xb = new float[nx+1];
	for(int i=0;i<nx;i++) xb[i] = h->GetXaxis()->GetBinLowEdge(i+1);
	xb[nx] = h->GetXaxis()->GetBinUpEdge(nx);

	TH1F* out = new TH1F(name.c_str(), title.c_str(),nx ,xb);

	//snatch bin labels in case they're custom. 
	for(int i=1;i<=nx;i++){
		string s = string(h->GetXaxis()->GetBinLabel(i));
		out->GetXaxis()->SetBinLabel(i,s.c_str());
	}

	//snatch axis titles
	string xlabel = string(h->GetXaxis()->GetTitle());	
	string ylabel = string(h->GetYaxis()->GetTitle());	
	out->GetXaxis()->SetTitle(xlabel.c_str());
	out->GetYaxis()->SetTitle(ylabel.c_str());

	//snatch content
	for(int i=0;i<=nx+1;i++){
	    out->SetBinContent(i,h->GetBinContent(i));
	    out->SetBinError(i,h->GetBinError(i));
	}
	return out;
}//end Clone
*/
TH1F* Clone(TH1F* h){
	//You're writing this because the root built-in Clone function doesn't work. 
	//If you take a file, read in a histogram, clone, it, and close the file: the clone gets whacked. 
	int nx = h->GetNbinsX();

	//snatch the binning
	float *xb = new float[nx+1];
	for(int i=0;i<nx;i++) xb[i] = h->GetXaxis()->GetBinLowEdge(i+1);
	xb[nx] = h->GetXaxis()->GetBinUpEdge(nx);

	TH1F* out = new TH1F("asdf","qwer",nx ,xb);
	delete xb;//new

	//snatch content
	for(int i=0;i<=nx+1;i++){
	    out->SetBinContent(i,h->GetBinContent(i));
	    out->SetBinError(i,h->GetBinError(i));
	}
	return out;
}//end Clone

int max(int a, int b){ return a>b? a: b;}
float max(float a, float b){ return a>b? a: b;}
double max(double a, double b){ return a>b? a: b;}
double max(float a, double b){ return a>b? a: b;}
double max(double a, float b){ return a>b? a: b;}
float max(int a, float b){ return a>b? a: b;}
float max(float a, int b){ return a>b? a: b;}
double max(int a, double b){ return a>b? a: b;}
double max(double a, int b){ return a>b? a: b;}
int min(int a, int b){ return a<b? a: b;}
float min(float a, float b){ return a<b? a: b;}
double min(double a, double b){ return a<b? a: b;}
double min(float a, double b){ return a<b? a: b;}
double min(double a, float b){ return a<b? a: b;}
float min(int a, float b){ return a<b? a: b;}
float min(float a, int b){ return a<b? a: b;}
double min(int a, double b){ return a<b? a: b;}
double min(double a, int b){ return a<b? a: b;}

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

TH1F* vslice(TH2F* h, int bin){
	//Takes a single column at bin "bin" and makes a histogram out of that. 
	int ny = h->GetNbinsY();

	//snatch the binning
	float *yb = new float[ny+1];
	for(int i=0;i<ny;i++) yb[i] = h->GetYaxis()->GetBinLowEdge(i+1);
	yb[ny] = h->GetYaxis()->GetBinUpEdge(ny);

	//make the 1D slice histogram
	TH1F* out = new TH1F((string(h->GetName()) + "_vslice"+to_string(bin)).c_str(),
			(string(h->GetTitle()) + " vslice " + to_string(bin)).c_str() ,ny ,yb);

	delete yb;//new

	//steralize bin
	if(bin<0 or bin >  h->GetNbinsX()+1){
		cout<<"Warning! vslice received out of range bin "<<bin<<" on hist "<<h->GetName()<<", Returning blank hist!"<<endl; 
		return out;
	}

	//fill the new histogram
	for(int i=0;i<=ny+1;i++){
	    out->SetBinContent(i,h->GetBinContent(bin, i));
	    out->SetBinError(  i,h->GetBinError(  bin, i));
	}
	return out;	
}//end vslice

TH1F* hslice(TH2F* h, int bin){
	//Takes a row column at bin "bin" and makes a histogram out of that. 
	int nx = h->GetNbinsX();

	//snatch the binning
	float *xb = new float[nx+1];
	for(int i=0;i<nx;i++) xb[i] = h->GetXaxis()->GetBinLowEdge(i+1);
	xb[nx] = h->GetXaxis()->GetBinUpEdge(nx);

	//make the 1D slice histogram
	TH1F* out = new TH1F((string(h->GetName()) + "_hslice"+to_string(bin)).c_str(), 
			(string(h->GetTitle()) + " hslice " + to_string(bin)).c_str() ,nx ,xb);
	delete xb;//new

	//steralize bin
	if(bin<0 or bin > h->GetNbinsY()+1){
		cout<<"Warning! hslice received out of range bin "<<bin<<" on hist "<<h->GetName()<<", Returning blank hist!"<<endl; 
		return out;
	}

	//fill the new histogram
	for(int i=0;i<=nx+1;i++){
	    out->SetBinContent(i,h->GetBinContent(i, bin));
	    out->SetBinError(i,h->GetBinError(i, bin));
	}
	return out;	
}//end hslice

TH1F* DivideHists(TH1F* numerator, TH1F* denominator, int mode){
	//returns the bin-by-bin division of numerator/denominator (under mode 0)
	//for mode 1, returns numerator/sqrt(denominator)
	static const bool verbose = false;	
	if(verbose) cout<<"In DivideHists)"<<endl;
	if(mode == 1) return DivideHists(numerator, SQRT(denominator), 0);
        string name = numerator->GetName();
	name += "_div";
        TH1F* out = (TH1F*) numerator->Clone(name.c_str());

        int nbinsx = numerator->GetXaxis()->GetNbins();
	if(     nbinsx != denominator->GetXaxis()->GetNbins() ){
	    cout<<"Error! DivideHists receives numerator and background histograms with mismatched binning"<<endl;
	    out->Reset();
	    return out;
	}
	for(int i=0;i<=nbinsx+1;++i){
	    float num = numerator->GetBinContent(i);
	    float den = denominator->GetBinContent(i);
	    if(num==0.){
		out->SetBinContent(i,0);
		out->SetBinError(i,0);
		continue;
	    }
	    if(den==0.) den=-1;
	    out->SetBinContent(i,num/den);

	    if(verbose) cout<<"   bin "<<i<<" num: "<<num<<" den "<<den<<" ratio "<<out->GetBinContent(i) <<endl;
	    if(den!=0.){
		out->SetBinError(i,
			fabs(num/den)*sqrt(    pow(denominator->GetBinError(i)/den,2) + pow(numerator->GetBinError(i)/num,2)       )     
			);
	    }
	    else{
		out->SetBinContent(i,-1);
		out->SetBinError(i,0);
	    }
	    if(verbose) cout<<"         "<<"Unum: "<<numerator->GetBinError(i)<<" Uden "<<denominator->GetBinError(i)<<" ratio "<<out->GetBinError(i) <<endl;
	}//end for
	return out;
}//end DivideHists;

TH2F* DivideHists(TH2F* numerator, TH2F* denominator, int mode){
	//returns the bin-by-bin division of numerator/denominator (under mode 0)
	//for mode 1, returns numerator/sqrt(denominator)
	if(mode == 1) return DivideHists(numerator, SQRT(denominator), 0);

        string name = numerator->GetName();
	name += "_div";
        TH2F* out = (TH2F*) numerator->Clone(name.c_str());

        int nbinsx = numerator->GetXaxis()->GetNbins();
        int nbinsy = numerator->GetYaxis()->GetNbins();
	if(     nbinsx != denominator->GetXaxis()->GetNbins() or 
		nbinsy != denominator->GetYaxis()->GetNbins()    ){
	    cout<<"Error! DivideHists receives numerator and background histograms with mismatched binning"<<endl;
	    out->Reset();
	    return out;
	}
	for(int i=0;i<=nbinsx+1;++i){
	    for(int j=0;j<=nbinsy+1;++j){
		float den = denominator->GetBinContent(i,j);
		float num = numerator->GetBinContent(i,j);
		if(den!=0.){
		    out->SetBinContent(i,j,num/den);
		    out->SetBinError(i,j,
			    fabs(num/den)*sqrt(    pow(denominator->GetBinError(i,j)/den,2) + pow(numerator->GetBinError(i,j)/num,2)       )     
			    );
		}
		else{
		    out->SetBinContent(i,j,-1);
		    out->SetBinError(i,j,0);
		}
	    }//end for y
	}//end for x
	return out;
}//end DivideHists;

TH1F* MultiplyHists(TH1F* A, TH1F* B){
        string name = A->GetName();
	name += "_prod";
        TH1F* out = (TH1F*) A->Clone(name.c_str());

        int nbinsx = A->GetXaxis()->GetNbins();
        int nbinsy = A->GetYaxis()->GetNbins();
	if(     nbinsx != B->GetXaxis()->GetNbins() ){
	    cout<<"Error! MultiplyHists receives histograms with mismatched binning"<<endl;
	    out->Reset();
	    return out;
	}
	for(int i=0;i<=nbinsx+1;++i){
		float a = out->GetBinContent(i);
		float b = B->GetBinContent(i);
		out->SetBinContent(i,a*b);
		out->SetBinError(i,sqrt(pow(b*out->GetBinError(i),2) + pow(a*B->GetBinError(i),2) )   );
	}
	return out;
}//end MultiplyHists;

TH2F* MultiplyHists(TH2F* A, TH2F* B){
        string name = A->GetName();
	name += "_prod";
        TH2F* out = (TH2F*) A->Clone(name.c_str());

        int nbinsx = A->GetXaxis()->GetNbins();
        int nbinsy = A->GetYaxis()->GetNbins();
	if(     nbinsx != B->GetXaxis()->GetNbins() or 
		nbinsy != B->GetYaxis()->GetNbins()    ){
	    cout<<"Error! MultiplyHists receives histograms with mismatched binning"<<endl;
	    out->Reset();
	    return out;
	}
	for(int i=0;i<=nbinsx+1;++i){
	    for(int j=0;j<=nbinsy+1;++j){
		float a = out->GetBinContent(i,j);
		float b = B->GetBinContent(i,j);
		out->SetBinContent(i,j,a*b);
		out->SetBinError(i,j,sqrt(pow(b*out->GetBinError(i,j),2) + pow(a*B->GetBinError(i,j),2) )   );
	    }
	}
	return out;
}//end InvertHists;

TH2F* InvertHists(TH2F* A){
        string name = A->GetName();
	name += "_inv";
        TH2F* out = (TH2F*) A->Clone(name.c_str());

        int nbinsx = A->GetXaxis()->GetNbins();
        int nbinsy = A->GetYaxis()->GetNbins();
	for(int i=0;i<=nbinsx+1;++i){
	    for(int j=0;j<=nbinsy+1;++j){
		float a = out->GetBinContent(i,j);
		out->SetBinContent(i,j,1.0/a);
		out->SetBinError(i,j,out->GetBinError(i,j)/(a*a) );
	    }
	}
	return out;
}//end InvertHists;
TH1F* InvertHists(TH1F* A){
        string name = A->GetName();
	name += "_inv";
        TH1F* out = (TH1F*) A->Clone(name.c_str());

        int nbinsx = A->GetXaxis()->GetNbins();
	for(int i=0;i<=nbinsx+1;++i){
		float a = out->GetBinContent(i);
		out->SetBinContent(i,1.0/a);
		out->SetBinError(i,out->GetBinError(i)/(a*a) );
	}
	return out;
}//end InvertHists;


#endif
