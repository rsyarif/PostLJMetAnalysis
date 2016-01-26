#include <cmath>
#include <math.h>
#include <iostream>
#include <string.h>
//#include "TMatrixT.h"
//#include "TMatrixTBase.h"
//#include "TFile.h"
#include "CMSStyle.C" 
#include "TString.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2.h"
//#include <map>
//#include "params_arg_Hmx.h"
//#include "TMath.h"
#include "utilities.h"
#include "TRandom3.h"

using namespace std;
enum modes {lte=0,lt=1,gt=2,gte=3};//enums to keep track of the mode convention.

TH1F* makeGoodCDF(TH1F* rawhist, bool print);//complete and usable 1D CDF from a bkg hist coming right out of postanaana (plotsWithBackground*.root style).
TH2F* makeGoodCDF(TH2F* rawhist, bool print);//complete and usable 1D CDF from a bkg hist coming right out of postanaana (plotsWithBackground*.root style).

TH1F* makeCDF(TH1F* h, int mode = 0);//wad
TH2F* makeCDF(TH2F* h, int mode = 0); //wad
TH2F* makeHorizontalCDF(TH2F* h, int mode=0);//wad
TH2F* makeVerticalCDF(  TH2F* h, int mode=0);//wad
float KSStatistic(TH1F* h1, TH1F* h2);//wad
void compareKSStatistic();//wad
TH1F* toTH1F(TH1D* h);
TGraph* cutCurve(TH1F* B, TH1F* S); //makes bkg rejection vs sig efficiency
TGraph* cutCurve(TH1D* B, TH1D* S);

void Replace0withRes(TH1F* cdf, float resolution);//these two replace all values in a CDF < resolution with the resolution. wad
void Replace0withRes(TH2F* cdf, float resolution);//which keeps the CDF probability from bottoming out. 

float LinearInterpolateCDF(TH1F* cdf, float x, float resolution, char mode=-1);//wad 
float LinearInterpolateCDF(TH2F* cdf, float x, float y,float resolution,char mode=-1);//wad
	//no mode: tries for auto mode. if fails, uses mode 0
	//mode 0 = don't interpolate at all, just return the value of the bin. 
	//mode 1 = interpolate from left edge (lower left corners for 2D) 
	//mode 2 = interpolate from right edge (upper right corners for 2D)
	//mode 3 = interpolate from bin centers.

	//These two are completely general and are the guts of LinearInterpolateCDF. 
	//Same mode structure as above except no "no mode" option.
float LinearInterpolateHist(float x, TH1F* H, char mode);//wad
float LinearInterpolateHist(float x, float y, TH2F* H, char mode);//wad

//once you've built these you'll want to save them or print out results as fucnctions. . 
void printHistFunction(TH1F* H);//print histograms as functions (segments of C++ code. wad
void printHistFunction(TH2F* H);//wad
void printHistRebuilder(TH1F* H, string varname);//print code to build the THistogram. wad
void printHistRebuilder(TH2F* H, string varname);//wad
void printHistLatex(TH1F* H);//print histogram as a latex table. wad
TH1F* showall(TH1F* h);//wad
float guessMean(TH1F* pdf,TH1F* cdf);
float guessMean(TH2F* pdf,TH2F* cdf);
//void printHistLatex(TH2F* H);//I'm not yet sure how to build this. 

//CDF calculators
double PoissonCDF(double poissMean, double poissSTDev, int nObs, int nDice); 
//meant to tell you what probability the poisson dist comes out >= nObs. 
//the estimate of the poisson mean (poissmean) has gaussian uncertinty poisssSTDev


float KSStatistic(TH1F* h1, TH1F* h2){
	//http://www.soest.hawaii.edu/wessel/courses/gg313/Critical_KS.pdf
	TH1F* cdf1 = makeCDF(h1,0);
	TH1F* cdf2 = makeCDF(h2,0);
	float  n1 = (float)h1->GetEntries();	
	float  n2 = (float)h2->GetEntries();	
	float D=0;
	int nbins1 = h1->GetXaxis()->GetNbins();
	int nbins2 = h2->GetXaxis()->GetNbins();
	if(nbins1 != nbins2) return -1;
	for(int i = 1;i<nbins1;i++){
		float temp = fabs(cdf1->GetBinContent(i) - cdf2->GetBinContent(i));
		if(temp>D) D=temp;
	}
	return D*sqrt(n1*n2/(n1+n2));
}//end KSStatistic
void compareKSStatistic(){
	printf("Significant results at a given alpha have a KSStatistic results are greater than CA\n");
	//boarder colly. 
	printf("alpha\t| 0.10\t| 0.05\t| 0.025\t| 0.01\t| 0.005\t| 0.001\t|\n");
	printf("CA   \t| 1.22\t| 1.36\t| 1.48 \t| 1.63\t| 1.73 \t| 1.95 \t|\n");
}//compareKSStatistic

TH1F* makeCDF(TH1F* h, int mode){
	//Integrates to make CDF Over/underflows are included. 
	//The output histogram has the same binning as the input. mode = 0,1,2,3.
	//The underflow and overlfow bins are relied upon to show some of the information. 
	//recommend use enum modes {lte=0,lt=1,gt=2,gte=3}
	//modes 0, 1 are the normal way we think of CDF, 0 on the left underflow, ranging to 1 in the overflow. 
	//modes 2,3 are reversed, starting at 1 in the underflow and decrementing down to 0 in the overflow. 
	//mode 0 cdf(x) = probability that event is <= x.//normal
	//mode 1 cdf(x) = probability that event is < x. //rarely used. 
	//mode 2 cdf(x) = probability that event is > x. //rarely used
	//mode 3 cdf(x) = probability that event is >= x.//best for metrics.
	//mode_2 = 1 - mode_0
	//mode_3 = 1 - mode_1
	//include underflows

	string name = h->GetName();
	name+= "_cdf";
	name+= Form("_MODE%i",mode);
	TH1F* cdf = (TH1F*) h->Clone(name.c_str());
	TH1F* pdf = (TH1F*) h->Clone();
	UnitNorm(pdf);
	double integ = 0.;

	int nbinsx = cdf->GetXaxis()->GetNbins();
	cdf->Reset();
	switch(mode){
	case 0: //less than or equal to this bin   //wad
		for(int i=0;i<=nbinsx+1;i++){
		    integ += pdf->GetBinContent(i);
		    cdf->SetBinContent(i,integ);
		}
	    break;
	case 1: //less than this bin //probably not the one you want to use
		cdf->SetBinContent(0,0);
		for(int i=1;i<=nbinsx+1;i++){
		    integ += pdf->GetBinContent(i-1);
		    cdf->SetBinContent(i,integ);
		}
	    break;
	case 2: //greater than this bin 
	    //see 1 by the end.  
		cdf->SetBinContent(nbinsx+1,0);
		for(int i=nbinsx;i>=0;--i){
		    integ += pdf->GetBinContent(i+1);
		    cdf->SetBinContent(i,integ);
		}
	    break;
	case 3: //greater than or equal to this bin
	    //probably the one you'll always want to use. 
		for(int i=nbinsx+1;i>=0; --i){
		    integ += pdf->GetBinContent(i);
		    cdf->SetBinContent(i,integ);
		}
	    break;
	}//end switch;
	return cdf;
}//end makeCDF

//TH2F* makeCDF(TH2F* h, int mode = 0){
//}
TH2F* makeCDF(TH2F* h, int mode){
	//The output histogram has the same binning as the input. mode = 0,1,2,3.
	//The underflow and overlfow bins are relied upon to show some of the information. 
	//recommend use enum modes {lte=0,lt=1,gt=2,gte=3}
	//modes 0, 1 are the normal way we think of CDF, 0 on the left underflow, ranging to 1 in the overflow. 
	//modes 2,3 are reversed, starting at 1 in the underflow and decrementing down to 0 in the overflow. 
	//mode 0 cdf(x) = probability that event is <= x.//normal
	//mode 1 cdf(x) = probability that event is < x. //rarely used. 
	//mode 2 cdf(x) = probability that event is > x. //rarely used
	//mode 3 cdf(x) = probability that event is >= x.//best for metrics.
	string name = h->GetName();
	name+= "_cdf";
	name+= Form("_MODE%i",mode);
	TH2F* cdf = (TH2F*) h->Clone(name.c_str());
	TH2F* pdf = (TH2F*) h->Clone();
	
	UnitNorm(pdf);
	int nbinsx = cdf->GetXaxis()->GetNbins();
	int nbinsy = cdf->GetYaxis()->GetNbins();
	cdf->Reset();
	switch(mode){
	case 0: 
		//the entire underlfow edge goes to zero. 
	    for(int i=0;i<=nbinsx+1;i++) cdf->SetBinContent(i,0,0);
	    for(int j=1;j<=nbinsy+1;j++) cdf->SetBinContent(0,j,0);
	    //main loop
	    for(int i=1;i<=nbinsx;i++){
	    for(int j=1;j<=nbinsy;j++){
		cdf->SetBinContent(i,j,pdf->GetBinContent(i,j)+
			cdf->GetBinContent(i-1,j)+
			cdf->GetBinContent(i,j-1)-
			cdf->GetBinContent(i-1,j-1));

	    }}
	    //ignore any overflow, act like its zero. and overwrite them. 
	    for(int i=1;i<=nbinsx;i++) {
		    int j = nbinsy+1;
		    cdf->SetBinContent(i,j,
				    cdf->GetBinContent(i-1,j)+
				    cdf->GetBinContent(i,j-1)-
				    cdf->GetBinContent(i-1,j-1));
	    }
	    for(int j=1;j<=nbinsy+1;j++){
		    int i = nbinsx+1;
		    cdf->SetBinContent(i,j,
				    cdf->GetBinContent(i-1,j)+
				    cdf->GetBinContent(i,j-1)-
				    cdf->GetBinContent(i-1,j-1));
	    }
	    break;
	case 1: //probably not the one you want to use
		//the entire underlfow edge goes to zero. 
	    for(int i=0;i<=nbinsx+1;i++) cdf->SetBinContent(i,0,0);
	    for(int j=1;j<=nbinsy+1;j++) cdf->SetBinContent(0,j,0);
		//entire first row and coll are also all zero.
	    for(int i=1;i<=nbinsx+1;i++) cdf->SetBinContent(i,1,0);
	    for(int j=2;j<=nbinsy+1;j++) cdf->SetBinContent(1,j,0);
	    //main loop
	    for(int i=1;i<=nbinsx;i++){
	    for(int j=1;j<=nbinsy;j++){
		cdf->SetBinContent(i+1,j+1,pdf->GetBinContent(i,j)+
			cdf->GetBinContent(i,j+1)+
			cdf->GetBinContent(i+1,j)-
			cdf->GetBinContent(i,j));

	    }}
	    //overflow is never even considered because it's < and not <=
	    break;
	case 2:
		//the entire overflow edge goes to zero. 
	    for(int i=0;i<=nbinsx+1;i++) cdf->SetBinContent(i,nbinsy+1,0);
	    for(int j=0;j<=nbinsy;j++) cdf->SetBinContent(nbinsx+1,j,0);
	    //entire last collumn and row are all zero too. 
	    for(int i=0;i<=nbinsx;i++) cdf->SetBinContent(i,nbinsy,0);
	    for(int j=0;j<=nbinsy-1;j++) cdf->SetBinContent(nbinsx,j,0);
	    //main loop
	    for(int i=nbinsx;i>=1;i--){
	    for(int j=nbinsy;j>=1;j--){
		    cdf->SetBinContent(i-1,j-1,pdf->GetBinContent(i,j)+
				    cdf->GetBinContent(i,j-1)+
				    cdf->GetBinContent(i-1,j)-
				    cdf->GetBinContent(i,j));

	    }}
		//underflow is automatically taken care of and never integrated up. 
	    break;
	case 3: //probably the one you'll always want to use. 
		//the entire overflow edge goes to zero. 
	    for(int i=0;i<=nbinsx+1;i++) cdf->SetBinContent(i,nbinsy+1,0);
	    for(int j=0;j<=nbinsy;j++) cdf->SetBinContent(nbinsx+1,j,0);
	    //main loop
	    for(int i=nbinsx;i>=1;i--){
	    for(int j=nbinsy;j>=1;j--){
		    cdf->SetBinContent(i,j,pdf->GetBinContent(i,j)+
				    cdf->GetBinContent(i+1,j)+
				    cdf->GetBinContent(i,j+1)-
				    cdf->GetBinContent(i+1,j+1));

	    }}
	    //ignore any underflow, act like its zero. and overwrite them. 
	    for(int i=nbinsx;i>=1;i--){
		    int j = 0;
		    cdf->SetBinContent(i,j,
				    cdf->GetBinContent(i+1,j)+
				    cdf->GetBinContent(i,j+1)-
				    cdf->GetBinContent(i+1,j+1));
	    }
	    for(int j=nbinsy;j>=0;j--){
		    int i = 0;
		    cdf->SetBinContent(i,j,
				    cdf->GetBinContent(i+1,j)+
				    cdf->GetBinContent(i,j+1)-
				    cdf->GetBinContent(i+1,j+1));
	    }
	    break;
	}//end switch;
	return cdf;
}//end makeCDF

TH2F* makeHorizontalCDF(TH2F* h, int mode){
	//Integrates horizontally to make CDF, but does not integrate vertically.
	//Each row is individually normalized. Over/underflows are included. 
	//The output histogram has the same binning as the input. mode = 0,1,2,3.
	//The underflow and overlfow bins are relied upon to show some of the information. 
	//recommend use enum modes {lte=0,lt=1,gt=2,gte=3}
	//modes 0, 1 are the normal way we think of CDF, 0 on the left underflow, ranging to 1 in the overflow. 
	//modes 2,3 are reversed, starting at 1 in the underflow and decrementing down to 0 in the overflow. 
	//mode 0 cdf(x) = probability that event is <= x.//normal
	//mode 1 cdf(x) = probability that event is < x. //rarely used. 
	//mode 2 cdf(x) = probability that event is > x. //rarely used
	//mode 3 cdf(x) = probability that event is >= x.//best for metrics.
	//mode_2 = 1 - mode_0
	//mode_3 = 1 - mode_1
	//include underflows

	string name = h->GetName();
	name+= "_cdf";
	name+= Form("_MODE%i",mode);
	TH2F* cdf = (TH2F*) h->Clone(name.c_str());
	TH2F* pdf = (TH2F*) h->Clone();
	TH1D * 	projY = h->ProjectionY(); //project hist onto Y axis as a fast way to add up the rows. 

	int nbinsx = cdf->GetXaxis()->GetNbins();
	int nbinsy = cdf->GetYaxis()->GetNbins();
	cdf->Reset();
	switch(mode){
	case 0: //less than or equal to this bin   //wad
	    for(int j=0;j<=nbinsy+1;++j){
		double row_integral = projY->GetBinContent(j);
		if( row_integral==0.0) row_integral = 1.;
		double integ = 0.;
		for(int i=0;i<=nbinsx+1;i++){
		    integ += pdf->GetBinContent(i,j);
		    cdf->SetBinContent(i,j,integ/row_integral);
		}
	    }//end for every row.
	    break;
	case 1: //less than this bin //probably not the one you want to use
	    for(int j=0;j<=nbinsy+1;++j){
		double row_integral = projY->GetBinContent(j);
		if( row_integral==0.0) row_integral = 1.;
		cdf->SetBinContent(0,j,0);
		double integ = 0.;
		for(int i=1;i<=nbinsx+1;i++){
		    integ += pdf->GetBinContent(i-1,j);
		    cdf->SetBinContent(i,j,integ/row_integral);
		}
	    }//end for every row.
	    break;
	case 2: //greater than this bin 
	    //see 1 by the end.  
	    for(int j=0;j<=nbinsy+1;++j){
		double row_integral = projY->GetBinContent(j);
		if( row_integral==0.0) row_integral = 1.;
		cdf->SetBinContent(nbinsx+1,j,0);
		double integ = 0;
		for(int i=nbinsx;i>=0;--i){
		    integ += pdf->GetBinContent(i+1,j);
		    cdf->SetBinContent(i,j,integ/row_integral);
		}
	    }//end for every row.
	    break;
	case 3: //greater than or equal to this bin
	    //probably the one you'll always want to use. 
	    for(int j=0;j<=nbinsy+1;++j){
		double row_integral = projY->GetBinContent(j);
		if( row_integral==0.0) row_integral = 1.;
		double integ = 0.;
		for(int i=nbinsx+1;i>=0; --i){
		    integ += pdf->GetBinContent(i,j);
		    cdf->SetBinContent(i,j,integ/row_integral);
		}
	    }//end for every row.
	    break;
	}//end switch;
	return cdf;
}//end makeHorizontalCDF


TH2F* makeVerticalCDF(TH2F* h, int mode) {
	//Integrates vertically  to make CDF, but does not integrate horizontally.
	//Each column is individually normalized. Over/underflows are included. 
	//The output histogram has the same binning as the input. mode = 0,1,2,3.
	//The underflow and overlfow bins are relied upon to show some of the information. 
	//recommend use enum modes {lte=0,lt=1,gt=2,gte=3}
	//modes 0, 1 are the normal way we think of CDF, 0 on the left underflow, ranging to 1 in the overflow. 
	//modes 2,3 are reversed, starting at 1 in the underflow and decrementing down to 0 in the overflow. 
	//mode 0 cdf(x) = probability that event is <= x.//normal
	//mode 1 cdf(x) = probability that event is < x. //rarely used. 
	//mode 2 cdf(x) = probability that event is > x. //rarely used
	//mode 3 cdf(x) = probability that event is >= x.//best for metrics.
	//mode_2 = 1 - mode_0
	//mode_3 = 1 - mode_1
	//include underflows

	string name = h->GetName();
	name+= "_cdf";
	name+= Form("_MODE%i",mode);
	TH2F* cdf = (TH2F*) h->Clone(name.c_str());
	TH2F* pdf = (TH2F*) h->Clone();
	TH1D * 	projX = h->ProjectionX(); //project hist onto Y axis as a fast way to add up the rows. 

	int nbinsx = cdf->GetXaxis()->GetNbins();
	int nbinsy = cdf->GetYaxis()->GetNbins();
	cdf->Reset();
	switch(mode){
	case 0: //less than or equal to this bin   //wad
	    for(int j=0;j<=nbinsx+1;++j){
		double column_integral = projX->GetBinContent(j);
		if( column_integral==0.0) column_integral = 1.;
		double integ = 0.;
		for(int i=0;i<=nbinsy+1;i++){
		    integ += pdf->GetBinContent(j,i);
		    cdf->SetBinContent(j,i,integ/column_integral);
		}
	    }//end for every row.
	    break;
	case 1: //less than this bin //probably not the one you want to use
	    for(int j=0;j<=nbinsx+1;++j){
		double column_integral = projX->GetBinContent(j);
		if( column_integral==0.0) column_integral = 1.;
		cdf->SetBinContent(j,0,0);
		double integ = 0.;
		for(int i=1;i<=nbinsy+1;i++){
		    integ += pdf->GetBinContent(j,i-1);
		    cdf->SetBinContent(j,i,integ/column_integral);
		}
	    }//end for every row.
	    break;
	case 2: //greater than this bin 
	    //see 1 by the end.  
	    for(int j=0;j<=nbinsx+1;++j){
		double column_integral = projX->GetBinContent(j);
		if( column_integral==0.0) column_integral = 1.;
		cdf->SetBinContent(j,nbinsy+1,0);
		double integ = 0;
		for(int i=nbinsy;i>=0;--i){
		    integ += pdf->GetBinContent(j,i+1);
		    cdf->SetBinContent(j,i,integ/column_integral);
		}
	    }//end for every row.
	    break;
	case 3: //greater than or equal to this bin
	    //probably the one you'll always want to use. 
	    for(int j=0;j<=nbinsx+1;++j){
		double column_integral = projX->GetBinContent(j);
		if( column_integral==0.0) column_integral = 1.;
		double integ = 0.;
		for(int i=nbinsy+1;i>=0; --i){
		    integ += pdf->GetBinContent(j,i);
		    cdf->SetBinContent(j,i,integ/column_integral);
		}
	    }//end for every row.
	    break;
	}//end switch;
	return cdf;
}//end makeVerticalCDF

float LinearInterpolateCDF(TH1F* cdf, float x, float resolution, char mode){
	string name = cdf->GetName();
	if(mode == -1){ //if no edge mode was given, try to figure it out yourself from the MODE information
		if (name.find("MODE0") != std::string::npos) mode = 2;//use left edges
		else if (name.find("MODE1") != std::string::npos)mode = 1;
		else if (name.find("MODE2") != std::string::npos)mode = 2;
		else if (name.find("MODE3") != std::string::npos)mode = 1;//use right edges
		else {
			mode = 0;
			printf("Warning! No Edgemode recieved and no mode inforation in the CDF for %s. Not interpolating.\n",name.c_str());
		}
	}//end if default. 
	float out = LinearInterpolateHist(x, cdf, mode);
	return out<resolution? resolution: out;
}
float LinearInterpolateCDF(TH2F* cdf, float x, float y,float resolution,char mode){
	string name = cdf->GetName();
	if(mode == -1){ //if no edge mode was given, try to figure it out yourself from the MODE information
		if (name.find("MODE0") != std::string::npos) mode = 2;//use left edges
		else if (name.find("MODE1") != std::string::npos)mode = 1;
		else if (name.find("MODE2") != std::string::npos)mode = 2;
		else if (name.find("MODE3") != std::string::npos)mode = 1;//use right edges
		else {
			mode = 0;
			printf("Warning! No Edgemode recieved and no mode inforation in the CDF for %s. Not interpolating.\n",name.c_str());
		}
	}//end if default. 
	float out = LinearInterpolateHist(x, y,cdf, mode);
	return out<resolution? resolution: out;
}
float LinearInterpolateHist(float x, TH1F* H, char mode) {
	//linear interpolates a histogram H, uses that as a function of x and returns the corresponding y. 
	//mode 0 = don't interpolate at all, just return the value of the bin. 
	//mode 1 = interpolate from left edge
	//mode 2 = interpolate from right edge
	//mode 3 = interpolate from bin centers.
	if(mode<0 || mode>3){
		printf("Warning! LinearInterpolateHist 1D recieved invalid mode %i\n",mode);
		return -1;
	}
	if(mode == 0) return H->GetBinContent(H->GetXaxis()->FindBin(x));//just evaluate the hist at x
	float y1, y2, x1, x2;
	TAxis *xaxis = H->GetXaxis();
	int nbins = xaxis->GetNbins();
	int binx = xaxis->FindBin(x);
	float thisbiny = H->GetBinContent(binx);
	
	switch(mode){
	case 1://use lines between left edges
		x1 = (float) xaxis->GetBinLowEdge(binx);
		x2 = (float) xaxis->GetBinUpEdge(binx);
		y1 = thisbiny;	
		if(binx!=nbins+1) y2 = H->GetBinContent(binx+1);
		else y2 = thisbiny;	//overflow
		break;
	case 2://use lines between right edges
		x1 = (float) xaxis->GetBinLowEdge(binx);
		x2 = (float) xaxis->GetBinUpEdge(binx);
		y2 = thisbiny;	
		if(binx!=0) y1 = H->GetBinContent(binx-1);
		else y1 = thisbiny;	//overflow
		break;
	case 3://use center-to-center lines 
		float binCenter = (float) xaxis->GetBinCenter(binx);
		bool lowerHalf = x<binCenter;
		if((binx==0 && lowerHalf) || (binx==nbins+1 && !lowerHalf) ) return H->GetBinContent(binx);//underflow or overlfow
		if(lowerHalf){
			x2 = binCenter;	
			x1 = (float) xaxis->GetBinCenter(binx-1);
			y2 = thisbiny;
			y1 = H->GetBinContent(binx-1);
		}
		else{
			x2 = (float) xaxis->GetBinCenter(binx+1);
			x1 = binCenter;	
			y2 = H->GetBinContent(binx+1);
			y1 = thisbiny;
		}
		break;
	}//end case 3 = center to center case. 
	return y1 + ((y2-y1)/(x2-x1))*(x-x1);
}//end linear interpolate

float LinearInterpolateHist(float x, float y,TH2F* H, char mode) {
	//bi-linear interpolates a histogram H, uses that as a function of x,y and returns the corresponding z. 
	//mode 0 = don't interpolate at all, just return the value of the bin. 
	//mode 1 = interpolate from left edge
	//mode 2 = interpolate from right edge
	//mode 3 = interpolate from bin centers.
	if(mode<0 || mode>3){
		printf("Warning! LinearInterpolateHist 2D recieved invalid mode %i\n",mode);
		return -1;
	}
	if(mode == 0) return H->GetBinContent(H->GetXaxis()->FindBin(x), H->GetYaxis()->FindBin(y));//just evaluate the hist at x,y
	float Y[2];
	float X[2];
	float Z[2][2];
	TAxis *xaxis = H->GetXaxis();
	TAxis *yaxis = H->GetYaxis();
	int nbinsx = xaxis->GetNbins();
	int nbinsy = yaxis->GetNbins();
	int binx = xaxis->FindBin(x);
	int biny = yaxis->FindBin(y);
	switch(mode){
	case 1://use  planes from lower left corner of bin to lower left corners  of adjacent bins 
		{
		X[0] = (float) xaxis->GetBinLowEdge(binx);
		X[1] = (float) xaxis->GetBinUpEdge(binx);
		Y[0] = (float) yaxis->GetBinLowEdge(biny);
		Y[1] = (float) yaxis->GetBinUpEdge(biny);
		bool incrementX = binx != nbinsx+1;
		bool incrementY = biny != nbinsy+1;
		Z[0][0] = H->GetBinContent(binx,biny);
		Z[0][1] = H->GetBinContent(binx,biny+incrementY);
		Z[1][0] = H->GetBinContent(binx+incrementX,biny);
		Z[1][1] = H->GetBinContent(binx+incrementX,biny+incrementY);
		}
		break;
	case 2://use  planes from upper right corner of bin to upper right corners of adjacent bins 
		{
		X[0] = (float) xaxis->GetBinLowEdge(binx);
		X[1] = (float) xaxis->GetBinUpEdge(binx);
		Y[0] = (float) yaxis->GetBinLowEdge(biny);
		Y[1] = (float) yaxis->GetBinUpEdge(biny);
		bool incrementX = binx != 0;
		bool incrementY = biny != 0;
		Z[0][0] = H->GetBinContent(binx-incrementX,biny-incrementY);
		Z[0][1] = H->GetBinContent(binx-incrementX,biny);
		Z[1][0] = H->GetBinContent(binx,biny-incrementY);
		Z[1][1] = H->GetBinContent(binx,biny);
		}
		break;
	case 3://use plane between bin centers. 
		{
		bool upperHalfx = x>xaxis->GetBinCenter(binx);
		bool upperHalfy = y>yaxis->GetBinCenter(biny);
		bool Xover = binx == nbinsx+1;
		bool Yover = biny == nbinsy+1;
		bool Xunder = binx != nbinsx+1;
		bool Yunder = biny != nbinsx+1;
		float Xraw[3];//{xaxis->GetBinCenter(binx-!Xunder),xaxis->GetBinCenter(binx),xaxis->GetBinCenter(binx+!Xover)};
		float Yraw[3];//{yaxis->GetBinCenter(biny-!Yunder),yaxis->GetBinCenter(biny),yaxis->GetBinCenter(biny+!Yover)};
		float Zraw[3][3];
		for(int i = 0;i<=2;i++) Xraw[i] = xaxis->GetBinCenter(binx + (i-1) + Xunder - Xover);
		for(int j = 0;j<=2;j++) Yraw[j] = yaxis->GetBinCenter(biny + (j-1) + Yunder - Yover);
		for(int i = 0;i<=2;i++){
			for(int j = 0;j<=2;j++){
				Zraw[i][j] = H->GetBinContent(binx + (i-1) - Xover + Xunder,biny + (j-1) - Yover + Yunder);
		}}
		X[0] = Xraw[upperHalfx];
		X[1] = Xraw[upperHalfx+1];
		Y[0] = Yraw[upperHalfy];
		Y[1] = Yraw[upperHalfy+1];
		Z[0][0] = Zraw[upperHalfx][upperHalfy];
		Z[1][0] = Zraw[upperHalfx+1][upperHalfy];
		Z[0][1] = Zraw[upperHalfx][upperHalfy+1];
		Z[1][1] = Zraw[upperHalfx+1][upperHalfy+1];
		}
		break;
	}//end case 3 = center to center case. 
	return (Z[0][0]*(X[1]-x)*(Y[1]-y) + Z[1][0]*(x-X[0])*(Y[1]-y) + Z[0][1]*(X[1]-x)*(y-Y[0]) + Z[1][1]*(x-X[0])*(y-Y[0]))/((X[1]-X[0])*(Y[1]-Y[0]));
}//end interpolate 2d


TH1F* showall(TH1F* h){
	//returns a histogram with overflow and underflow bins tacked on. The bins of h do not keep their bin widths. 
	int nbins = h->GetXaxis()->GetNbins();
	TH1F* out = new TH1F("asdf","",nbins+2,1,nbins+3);
	for(int i=1;i<=nbins+2;i++)
		out->SetBinContent(i,h->GetBinContent(i-1));
	out->GetXaxis()->SetTitle("Bin Number");
	return out;
}

void printHistFunction(TH1F* H){
	//takes a 1D histogram and prints if statements that give its bin contant. Meant to be used as a code fragment of a function. 
	TAxis* x = H->GetXaxis();
	int nbinsx = x->GetNbins();
	printf("if(x<%f) return %f;\n",x->GetBinLowEdge(1), H->GetBinContent(0) );
	for(int ibin = 1;ibin<= nbinsx;ibin++)
	  	printf("else if(x<%f) return %f;\n",x->GetBinUpEdge(ibin),  H->GetBinContent(ibin));
	printf("else return %f;\n", H->GetBinContent(nbinsx+1) );//overflow
}
void printHistFunction(TH2F* H){
	//takes a 2D histogram and prints if statements that give its bin contant. Meant to be used as a code fragment of a function. 
	TAxis* x = H->GetXaxis();
	TAxis* y = H->GetYaxis();
	int nbinsx = x->GetNbins();
	int nbinsy = y->GetNbins();
	printf("if(x<%f) return %f;\n",x->GetBinLowEdge(1), H->GetBinContent(0) );
	
	printf("if(x<%f){\n",x->GetBinUpEdge(0));
	printf("\tif(y<%f) return %f;\n",y->GetBinLowEdge(1), H->GetBinContent(0, 0) );
	for(int jbin = 1;jbin<= nbinsy;jbin++)
		printf("\telse if(y<%f) return %f;\n",y->GetBinUpEdge(jbin),  H->GetBinContent(0, jbin));
	printf("\telse return %f;\n", H->GetBinContent(nbinsy+1) );//overflow
	printf("}\n");
	for(int ibin = 1;ibin<= nbinsx;ibin++){
		printf("else if(x<%f){\n",x->GetBinUpEdge(ibin));
		printf("\tif(y<%f) return %f;\n",y->GetBinLowEdge(1), H->GetBinContent(ibin, 0) );
		for(int jbin = 1;jbin<= nbinsy;jbin++)
			printf("\telse if(y<%f) return %f;\n",y->GetBinUpEdge(jbin),  H->GetBinContent(ibin, jbin));
		printf("\telse return %f;\n", H->GetBinContent(ibin, nbinsy+1) );//overflow
		printf("}\n");
	}
	printf("else{\n");
	printf("\tif(y<%f) return %f;\n",y->GetBinLowEdge(1), H->GetBinContent(nbinsx+1, 0) );
	for(int jbin = 1;jbin<= nbinsy;jbin++)
		printf("\telse if(y<%f) return %f;\n",y->GetBinUpEdge(jbin),  H->GetBinContent(nbinsx+1, jbin));
	printf("\telse return %f;\n", H->GetBinContent(nbinsx+1,nbinsy+1) );//overflow
	printf("}\n");
}
void printHistRebuilder(TH1F* H, string varname){
	TAxis * x= H->GetXaxis();
	int nbinsx = x->GetNbins();
	//make a binning array
	string binning = "binning_"+varname;
	printf("float %s[%i] = {",binning.c_str(),nbinsx+1);
	for(int i = 1;i<=nbinsx;i++) printf("%f, ",x->GetBinLowEdge(i));
	printf("%f};\n",x->GetBinUpEdge(nbinsx));
	//initialize the histogram
	printf("TH1F* %s = new TH1F(\"%s\",\"%s\",%i, %s);\n",varname.c_str(),H->GetName(),H->GetTitle(),nbinsx, binning.c_str());
	//set all values
	for(int ibin = 0;ibin<= nbinsx+1;ibin++) printf("%s->SetBinContent(%i,%f);\n",varname.c_str(), ibin, H->GetBinContent(ibin));
	//set all errors 
	for(int ibin = 0;ibin<= nbinsx+1;ibin++) printf("%s->SetBinError(%i,%f);\n",varname.c_str(), ibin, H->GetBinError(ibin));
	printf("\n");
}//printHistRebuilder
void printHistRebuilder(TH2F* H, string varname){
	TAxis * x= H->GetXaxis();
	TAxis * y= H->GetYaxis();
	int nbinsx = x->GetNbins();
	int nbinsy = y->GetNbins();
	//make a binning array
	string binningx = "binningx_"+varname;
	string binningy = "binningy_"+varname;
	printf("float %s[%i] = {",binningx.c_str(),nbinsx+1);
	for(int i = 1;i<=nbinsx;i++) printf("%f, ",x->GetBinLowEdge(i));
	printf("%f};\n",x->GetBinUpEdge(nbinsx));

	printf("float %s[%i] = {",binningy.c_str(),nbinsy+1);
	for(int i = 1;i<=nbinsy;i++) printf("%f, ",y->GetBinLowEdge(i));
	printf("%f};\n",y->GetBinUpEdge(nbinsy));
	//initialize the histogram
	printf("TH2F* %s = new TH2F(\"%s\",\"%s\",%i, %s, %i, %s);\n",varname.c_str(),H->GetName(),H->GetTitle(),nbinsx, binningx.c_str(), nbinsy, binningy.c_str());
	//set all values
	for(int ibin = 0;ibin<= nbinsx+1;ibin++) 
		for(int jbin = 0;jbin<= nbinsy+1;jbin++) 
			printf("%s->SetBinContent(%i,%i,%f);\n",varname.c_str(),ibin, jbin, H->GetBinContent(ibin,jbin));
	//set all errors 
	for(int ibin = 0;ibin<= nbinsx+1;ibin++) 
		for(int jbin = 0;jbin<= nbinsy+1;jbin++) 
			printf("%s->SetBinError(%i,%i,%f);\n",varname.c_str(), ibin, jbin, H->GetBinError(ibin,jbin));
	printf("\n");
}//end printHistRebuilder

void printHistLatex(TH1F* H){
	TAxis * x= H->GetXaxis();
	int nbinsx = x->GetNbins();
	printf("\\begin{tabular}{ c | c }\n");
	printf("Range & Value \\\\\n");
	printf("< %f & %f\\\\\n",x->GetBinUpEdge(0),H->GetBinContent(0));
	for(int ibin = 1;ibin<= nbinsx;ibin++) printf("%f - %f & %f\\\\\n",x->GetBinLowEdge(ibin),x->GetBinUpEdge(ibin),H->GetBinContent(ibin));
	printf("> %f & %f\\\\\n",x->GetBinUpEdge(nbinsx),H->GetBinContent(nbinsx+1));
	printf("\\end{tabular}\n");
}
//void printHistLatex(TH2F* H){}
//I'm not yet sure what I want here, 

//before you can print these, you have to put the resolution in right. 
void Replace0withRes(TH1F* cdf, float resolution){
	for(int ibin = 0;ibin<= cdf->GetXaxis()->GetNbins()+1;ibin++)
		if(cdf->GetBinContent(ibin)<resolution) cdf->SetBinContent(ibin,resolution);
}
void Replace0withRes(TH2F* cdf, float resolution){
	for(int ibin = 0;ibin<= cdf->GetXaxis()->GetNbins()+1;ibin++)
	for(int jbin = 0;jbin<= cdf->GetYaxis()->GetNbins()+1;jbin++)
		if(cdf->GetBinContent(ibin,jbin)<resolution) cdf->SetBinContent(ibin,jbin,resolution);
}

TH1F* makeGoodCDF(TH1F* rawhist, bool print){
	int entries = rawhist->GetEntries();
	AddOverflow(rawhist);	
	TH1F* cdf = makeCDF(rawhist, 3);
	Replace0withRes(cdf, 1.0/((double)entries));//these two replace all values in a CDF < resolution with the resolution. wad
	if(print){
		printHistFunction(cdf);
		printf("guess of mean: %f\n",guessMean(rawhist,cdf));
	}
	return cdf;
}
TH2F* makeGoodCDF(TH2F* rawhist, bool print){
	int entries = rawhist->GetEntries();
	AddOverflow(rawhist);	
	TH2F* cdf = makeCDF(rawhist, 3);
	Replace0withRes(cdf, 1.0/((double)entries));//these two replace all values in a CDF < resolution with the resolution. wad
	if(print){
		printHistFunction(cdf);
		printf("guess of mean: %f\n",guessMean(rawhist,cdf));
	}
	return cdf;
}
float guessMean(TH1F* pdf,TH1F* cdf){
	//assume the cdf is a makeCDF mode 3, properly fixed up by makeGoodCDF.
	float mean=0;
	UnitNorm(pdf);
	AddOverflow(pdf);	
	for(int ibin = 1;ibin<= pdf->GetXaxis()->GetNbins();ibin++)
		mean += -TMath::Log(cdf->GetBinContent(ibin)) * pdf->GetBinContent(ibin);
	return mean; 
}
float guessMean(TH2F* pdf,TH2F* cdf){
	//assume the cdf is a makeCDF mode 3, properly fixed up by makeGoodCDF.
	float mean=0;
	UnitNorm(pdf);
	AddOverflow(pdf);	
	for(int ibin = 1;ibin<= pdf->GetXaxis()->GetNbins();ibin++)
	for(int jbin = 1;jbin<= pdf->GetYaxis()->GetNbins();jbin++)
		mean+=-TMath::Log(cdf->GetBinContent(ibin,jbin)) * pdf->GetBinContent(ibin,jbin);
	return mean; 
}


#define  A1  (-3.969683028665376e+01)
#define  A2   2.209460984245205e+02
#define  A3  (-2.759285104469687e+02)
#define  A4   1.383577518672690e+02
#define  A5  (-3.066479806614716e+01)
#define  A6   2.506628277459239e+00

#define  B1  (-5.447609879822406e+01)
#define  B2   1.615858368580409e+02
#define  B3  (-1.556989798598866e+02)
#define  B4   6.680131188771972e+01
#define  B5  (-1.328068155288572e+01)

#define  C1  (-7.784894002430293e-03)
#define  C2  (-3.223964580411365e-01)
#define  C3  (-2.400758277161838e+00)
#define  C4  (-2.549732539343734e+00)
#define  C5   4.374664141464968e+00
#define  C6   2.938163982698783e+00

#define  D1   7.784695709041462e-03
#define  D2   3.224671290700398e-01
#define  D3   2.445134137142996e+00
#define  D4   3.754408661907416e+00

/* P_high = 1 - p_low*/
#define P_LOW   0.02425
#define P_HIGH  0.97575

double inverseNormalCDF(double p){
	//inverse normal CDF function. 
	//Source: http://home.online.no/~pjacklam/notes/invnorm/#An_overview_of_the_algorithm
	//This is an adaptation that combines the best features of the Chad Sprouse and Thomas Ziegler implementations. 
	double q;
	if ((P_LOW <= p) && (p <= P_HIGH)){
		q = p - 0.5;
		double r = q*q;
		return (((((A1*r+A2)*r+A3)*r+A4)*r+A5)*r+A6)*q /(((((B1*r+B2)*r+B3)*r+B4)*r+B5)*r+1);
	}
	else if ((0 < p )  && (p < P_LOW)){
		q = sqrt(-2*log(p));
		return (((((C1*q+C2)*q+C3)*q+C4)*q+C5)*q+C6) / ((((D1*q+D2)*q+D3)*q+D4)*q+1);
	}
	else if ((P_HIGH < p)&&(p < 1)){
		q = sqrt(-2*log(1-p));
		return -(((((C1*q+C2)*q+C3)*q+C4)*q+C5)*q+C6) / ((((D1*q+D2)*q+D3)*q+D4)*q+1);
	}
	else if (p >= 1) return HUGE_VAL;// "infinity"
	else /*p <= 0*/ return -HUGE_VAL;//minus "infinity"
}//end invnormcdf
double inverseHalfNormalCDF(double p){
	return inverseNormalCDF(p/2.0);
}


#define a1   2.54829592e-01
#define a2 (-2.84496736e-01)
#define a3   1.41421356237e+00
#define a4 (-1.453152027e+00)
#define a5   1.061405429e+00
#define p1    3.275911e-01
double normalCDF(double x){
    //source: http://www.johndcook.com/cpp_phi.html

//    int sign = 1; 
 //   if (x < 0) sign = -1;
    int sign = (x<0)?-1:1;// Save the sign of x
    //x = fabs(x)/sqrt(2.0);
    x = fabs(x)/a3;

    // A&S formula 7.1.26
    double t = 1.0/(1.0 + p1*x);
    double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);

    return 0.5*(1.0 + sign*y);
}
double PoissonCDF(double poissMean, double poissSTDev, int nObs, int nDice){ 
//meant to tell you what probability the poisson dist comes out >= nObs. 
//the estimate of the poisson mean (poissmean) has gaussian uncertinty poisssSTDev
//This is not the width of the poisson distribution, rather how sure you are of where the mean is.
//nDice is the number of random trials that are thrown. 
	TRandom3 r; 
	int success = 0;
	for(int i=0;i<nDice;i++) success += (r.Poisson(r.Gaus(poissMean,poissSTDev)) >= nObs);
	return ((double) success)/((double) nDice);
}

TGraph* cutCurve(TH1F* B, TH1F* S){
	//returns a cruve of bkg rejection vs signal efficiency. 
        TH1F* Binteg = makeCDF(B, lt); 
        TH1F* Sinteg = makeCDF(S, gt);
	int n= B->GetXaxis()->GetNbins() + 1;
	Double_t x[n];
	Double_t y[n];
	for (int i=1;i<=n;++i) {
		x[i] = Sinteg->GetBinContent(i);
		y[i] = Binteg->GetBinContent(i);
	}
	TGraph* out = new TGraph(n,x,y);
	out->SetTitle(";Signal Efficiency;Background Rejection");
	return out;
}//end cutCurve

TGraph* cutCurve(TH1D* B, TH1D* S){
	//returns a cruve of bkg rejection vs signal efficiency. 
	return cutCurve(toTH1F(B),toTH1F(S));
}//end cutCurve

TH1F* toTH1F(TH1D* h){
        int nx = h->GetNbinsX();

        //snatch the binning
        float *xb = new float[nx+1];
        for(int i=0;i<nx;i++) xb[i] = h->GetXaxis()->GetBinLowEdge(i+1);
        xb[nx] = h->GetXaxis()->GetBinUpEdge(nx);

        TH1F* out = new TH1F((string(h->GetName()) +"_f").c_str(),h->GetTitle(),nx ,xb);
	delete xb;

        //snatch content
        for(int i=0;i<=nx+1;i++){
            out->SetBinContent(i,h->GetBinContent(i));
            out->SetBinError(i,h->GetBinError(i));
        }
        return out;
}//end Clone	
