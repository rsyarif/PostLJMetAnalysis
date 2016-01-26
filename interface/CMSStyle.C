#ifndef CMSSTYLE_C // if not defined
#define CMSSTYLE_C

#include "TStyle.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TH1.h"
#include "TROOT.h"
#include <TCanvas.h>
#include "TLegend.h"
#include "utilities.h"
#include "TPaveText.h"
#include "TLatex.h"
#include <limits>
#include "interface/stringmap.h"
	//##########################################################################
	// Initialization code executed at the start of a ROOT session.
	//##########################################################################

	//#include <iostream>
	//using namespace std;


void CMSStyle();
enum fonts{
    TimesNewRoman = 132,
    TimesNewRoman_italic = 12,
    TimesNewRoman_bold = 22,
    TimesNewRoman_bolditalic = 32,
    Helvetica = 42, //Helvetica is the X11 and CMS name. Really it's closer to Arial. 
    Helvetica_italic = 52,
    Helvetica_bold = 62,
    Helvetica_bolditalic = 72,
    Courier = 82,
    Courier_italic = 92,
    Courier_bold = 102,
    Courier_bolditalic = 112,
    Symbol = 122, 
    Wingdings = 142 };
enum textalignment{left_justify = 11, center_justify = 21, right_justify = 31};//ex: my_tlatex.SetTextAlign(right_justify); //text location aligns w/ bottom of text.
//left_justify_vertical_center = 12, center_justify_vertical_center  = 22, right_justify_vertical_center  = 32 //text vertical location is centered. 
//left_justify_vertical_top = 13, center_justify_vertical_top  = 23, right_justify_vertical_top  = 33 //text vertical locaiton aligns with top of text.
//default is 11 = left justify with vertical position aligned with the bottom of the text; ypqgj will dip below that vertical position. 
TLegend*   PrettyLegend(TLegend* leg, float fontSize = 0.055);
TPaveText* PrettyText(TPaveText* text, float fontSize = 0.055);
TLatex*    PrettyLatex(TLatex* text, float fontSize = 0.055, int font = Helvetica);//TDR style suggests a font size of 0.25 -- crazy. 
TH1F*      PrettyHist(TH1F* h, int color = 1, int width = 3, int linestyle = 0);
TH1D*      PrettyHist(TH1D* h, int color = 1, int width = 3, int linestyle = 0);
TH2F*      PrettyHist(TH2F* h, int color = 1, int width = 3, int linestyle = 0);
TH2D*      PrettyHist(TH2D* h, int color = 1, int width = 3, int linestyle = 0);
TH1F*      PrettyRatioPlot(TH1F*);
TGraph*    PrettyGraph(TGraph* h, int color=1, int width=3, int linestyle=1);
TCanvas*   PrettyCanvas(TCanvas* c);//for now just calls PrettyMargins, but in the future may do more.

TH1F* PrettyMarker(TH1F* h, int color = 1, int markerstyle = 20, float markersize = 1.2f);
TH2F* PrettyMarker(TH2F* h, int color = 1, int markerstyle = 20, float markersize = 1.2f);
TH1F* PrettyFonts(TH1F* h);
TH1D* PrettyFonts(TH1D* h);
TH2F* PrettyFonts(TH2F* h);
TH2D* PrettyFonts(TH2D* h);
TCanvas* PrettyMargins(TCanvas* c, float left=0.12, float bottom=0.12, float top=0.10, float right=0.12);

TH1F* PrettyFillColor(TH1F* h, int color);
TH1* PrettyBlock2(TH1* hist, int color=4, int style=1001, int width=1);
TH1* PrettyBlock(TH1* hist, int color=4, string option="//thatch");

TLegend* newTLegend();
TH1F* UnitNorm(TH1F* hist);
TH2F* UnitNorm(TH2F* hist);
TH1F* MatchArea(TH1F* toScale, TH1F* toMatch);
void SameRange(TH1F* hist1, TH1F* hist2);
void SetRange(TH1F* hist, float _min = 0.0f, float _max = -1.15);
void SameRange_and_leave_legend_room_log(std::vector<TH1F*> hists, float legendFraction=0., bool tinymin_override = false, Double_t _min = -1.0, Double_t _max = -1.0, bool useRangeMax = false);
void SameRange_and_leave_legend_room(std::vector<TH1F*> hists, float legendFraction=0., Double_t _min = -1.0, Double_t _max = -1.0, bool useRangeMax = false);

float RaiseRangeRoof(TH1F* hist, float mult=1.2);
float highestErrorBar(TH1F *h);
float lowestErrorBar(TH1F *h, bool ignorezero = false);
float lowestBin(TH1F *h, bool ignorezero = false); //gets the min bin, if ignorezero, get the min bin that's not zero.
float highestBin(TH1F *h);
TH1F* playNiceWithLegend(TH1F* h, float legendFraction, float h_min=-1.0f, float h_max=-1.0f);
TH1F* playNiceWithLegendLog(TH1F* h, float legendFraction, float h_min=-1.0f, float h_max=-1.0f);

void DrawSame(TH1F* h0, TH1F* h1, string ops="");
void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, string ops="");
void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, TH1F* h3, string ops="");
void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, TH1F* h3,TH1F* h4, string ops="");
void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, TH1F* h3,TH1F* h4,TH1F* h5, string ops="");
TCanvas * newTCanvas(char* rootname, char* title); //makes an 800x800 TCanvas and cd's into it.
TCanvas * newTCanvas(string rootname, string title = "");

void SaveCanvas(TCanvas * c, string fileNameAndDir, string FileTypes = "crootpdfjpggif");
void SaveCanvas(TCanvas * c, string filename, namedstring* fileDir, string FileTypes = "crootpdfjpggif");

void CMSStyle(){
		// use the 'plain' style for plots (white backgrounds, etc)
		//  cout << "...using style 'Plain'" << endl;
	gROOT->SetStyle("Plain");

		// Create the 'CMS' style for approved plots. Note that this style may need
		// some fine tuning in your macro depending on what you are plotting, e.g.
		//
		//  gStyle->SetMarkerSize(0.75);  // use smaller markers in a histogram with many bins
		//  gStyle->SetTitleOffset(0.65,"y");  // bring y axis label closer to narrow values

	TStyle *cmsStyle= new TStyle("CMS","CMS approved plots style");

		// use plain black on white colors
	cmsStyle->SetFrameBorderMode(0);
	cmsStyle->SetCanvasBorderMode(0);
	cmsStyle->SetPadBorderMode(0);
	cmsStyle->SetPadColor(0);
	cmsStyle->SetCanvasColor(0);
	cmsStyle->SetTitleColor(1);
	cmsStyle->SetStatColor(0);
	cmsStyle->SetFrameFillColor(0);

		// set the paper & margin sizes
	cmsStyle->SetPaperSize(20,26);
	cmsStyle->SetPadTopMargin(0.05);
	cmsStyle->SetPadRightMargin(0.05);
	cmsStyle->SetPadBottomMargin(0.17);
	cmsStyle->SetPadLeftMargin(0.17);

		// use large Times-Roman fonts
	cmsStyle->SetTextFont(Helvetica);
	cmsStyle->SetTextSize(0.08);
	cmsStyle->SetLabelFont(Helvetica,"x");
	cmsStyle->SetLabelFont(Helvetica,"y");
	cmsStyle->SetLabelFont(Helvetica,"z");
	cmsStyle->SetLabelSize(0.05,"x");
	cmsStyle->SetTitleSize(0.06,"x");
	cmsStyle->SetLabelSize(0.05,"y");
	cmsStyle->SetTitleSize(0.06,"y");
	cmsStyle->SetLabelSize(0.05,"z");
	cmsStyle->SetTitleSize(0.06,"z");

		// use bold lines and markers
	cmsStyle->SetMarkerStyle(8);
	cmsStyle->SetHistLineWidth(2);
	cmsStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

		// do not display any of the standard histogram decorations
	cmsStyle->SetOptTitle(1);
	cmsStyle->SetOptStat(1);
	cmsStyle->SetOptFit(1);
	cmsStyle->SetOptTitle(0);
	cmsStyle->SetOptStat(0);

		// put tick marks on top and RHS of plots
	cmsStyle->SetPadTickX(1);
	cmsStyle->SetPadTickY(1);

		//  cout << endl << "    For approved plots use: gROOT->SetStyle(\"CMS\");"
		//       << endl << "  To add a CMS label use: CMSLabel();"
		//       << endl << endl;

		// restore the plain style
	gROOT->SetStyle("Plain");
	gROOT->SetStyle("CMS");
	return ;
}

TLegend* PrettyLegend(TLegend* leg, float fontSize){
		//default fontSize = 0.05;
	leg->SetTextFont(Helvetica);
	leg->SetFillColor(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(fontSize);
	return leg;
}

TPaveText* PrettyText(TPaveText* text, float fontSize){
		//default fontSize = 0.05;
		//	text->SetNDC();
	text->SetTextFont(Helvetica);
	text->SetFillColor(0);
	text->SetBorderSize(0);
	text->SetTextSize(fontSize);
	return text;//
		//	textlims->SetShadowColor(0); //if need to kill the ugly shadow.
}
TLatex* PrettyLatex(TLatex* text, float fontSize, int font){
	text->SetNDC();
	text->SetTextFont(font);
	text->SetTextSize(fontSize);
	text->SetLineWidth(2);
	return text;
}

TH1F* PrettyHist(TH1F* h, int color, int width, int linestyle ){
		//defaults: PrettyHist(TH1F* h, int color = 1, int width = 3, int linestyle = 0){
	h->SetLineColor(color);
	h->SetLineWidth(width);
	h->SetLineStyle(linestyle);
	h->SetStats(0);
	PrettyFonts(h);
	h->GetXaxis()->SetLabelSize(0.055);
	h->GetYaxis()->SetLabelSize(0.055);
	return h;
}
TH1D* PrettyHist(TH1D* h, int color, int width, int linestyle ){
		//defaults: PrettyHist(TH1F* h, int color = 1, int width = 3, int linestyle = 0){
	h->SetLineColor(color);
	h->SetLineWidth(width);
	h->SetLineStyle(linestyle);
	h->SetStats(0);
	PrettyFonts(h);
	h->GetXaxis()->SetLabelSize(0.055);
	h->GetYaxis()->SetLabelSize(0.055);
	return h;
}
TH2F* PrettyHist(TH2F* h, int color, int width, int linestyle ){
		//defaults: PrettyHist(TH1F* h, int color = 1, int width = 3, int linestyle = 0){
	h->SetLineColor(color);
	h->SetLineWidth(width);
	h->SetLineStyle(linestyle);
	h->SetStats(0);
	PrettyFonts(h);
	h->GetXaxis()->SetLabelSize(0.055);
	h->GetYaxis()->SetLabelSize(0.055);
	h->GetZaxis()->SetLabelSize(0.055);
	return h;
}
TH2D* PrettyHist(TH2D* h, int color, int width, int linestyle ){
		//defaults: PrettyHist(TH1F* h, int color = 1, int width = 3, int linestyle = 0){
	h->SetLineColor(color);
	h->SetLineWidth(width);
	h->SetLineStyle(linestyle);
	h->SetStats(0);
	PrettyFonts(h);
	h->GetXaxis()->SetLabelSize(0.055);
	h->GetYaxis()->SetLabelSize(0.055);
	h->GetZaxis()->SetLabelSize(0.055);
	return h;
}
TGraph* PrettyGraph(TGraph* h, int color, int width, int linestyle ){
                //defaults: PrettyHist(TH1F* h, int color = 1, int width = 3, int linestyle = 0){
        h->SetLineColor(color);
        h->SetLineWidth(width);
        h->SetLineStyle(linestyle);
	return h;
}

	///Can I do this?
	//Descriptive constants for line Styles.
static const int sSolid = 1;
static const int sdashed = 2;
static const int sDashed = 7;
static const int sdotted = 3;
static const int sdotdash = 4;
static const int sdotDash = 5;
static const int sbigDash = 9;
static const int bigdotDash = 10;

TH1F* PrettyFonts(TH1F* h){
	TAxis * x = h->GetXaxis();
	TAxis * y = h->GetYaxis();
	x->SetTitleFont(Helvetica);
	y->SetTitleFont(Helvetica);
	x->SetTitleSize(0.055);//0.08
	x->SetTitleOffset(1.0); //make the Title a little further from the axis
	//x->SetTitleOffset(0.80); //make the Title a little further from the axis
	y->SetTitleOffset(1.06);
	//y->SetTitleOffset(0.80);
	y->SetTitleSize(0.055);//0.08
	x->SetLabelFont(Helvetica);
	y->SetLabelFont(Helvetica);
	x->SetLabelSize(0.055);//0.06
	y->SetLabelSize(0.055);//0.06
	return h;
}
TH1D* PrettyFonts(TH1D* h){
	TAxis * x = h->GetXaxis();
	TAxis * y = h->GetYaxis();
	x->SetTitleFont(Helvetica);
	y->SetTitleFont(Helvetica);
	x->SetTitleSize(0.055);
	//x->SetTitleSize(0.08);
	x->SetTitleOffset(1.00); //make the Title a little further from the axis
	y->SetTitleOffset(1.05);
	y->SetTitleSize(0.055);
	//y->SetTitleSize(0.08);
	x->SetLabelFont(Helvetica);
	y->SetLabelFont(Helvetica);
	x->SetLabelSize(0.055);
	y->SetLabelSize(0.055);
	return h;
}
TH2F* PrettyFonts(TH2F* h){
	TAxis * x = h->GetXaxis();
	TAxis * y = h->GetYaxis();
	TAxis * z = h->GetZaxis();
	x->SetTitleFont(Helvetica);
	y->SetTitleFont(Helvetica);
	z->SetTitleFont(Helvetica);
	x->SetTitleOffset(1.05); //make the Title a little further from the axis
	y->SetTitleOffset(1.05);
	z->SetTitleOffset(1.05);
	x->SetTitleSize(0.055);
	//x->SetTitleSize(0.08);
	y->SetTitleSize(0.055);
	//y->SetTitleSize(0.08);
	z->SetTitleSize(0.055); ///cartoonishly large for test
	//z->SetTitleSize(0.08);
	x->SetLabelFont(Helvetica);
	y->SetLabelFont(Helvetica);
	z->SetLabelFont(Helvetica);
	x->SetLabelSize(0.055);//all were 0.06
	y->SetLabelSize(0.055);
	z->SetLabelSize(0.055);
	return h;
}
TH2D* PrettyFonts(TH2D* h){
	TAxis * x = h->GetXaxis();
	TAxis * y = h->GetYaxis();
	TAxis * z = h->GetZaxis();
	x->SetTitleFont(Helvetica);
	y->SetTitleFont(Helvetica);
	z->SetTitleFont(Helvetica);
	x->SetTitleOffset(1.05); //make the Title a little further from the axis
	y->SetTitleOffset(1.05);
	z->SetTitleOffset(0.95);
	y->SetTitleSize(0.055);
	x->SetTitleSize(0.055);
	z->SetTitleSize(0.055);
	x->SetLabelFont(Helvetica);
	y->SetLabelFont(Helvetica);
	z->SetLabelFont(Helvetica);
	x->SetLabelSize(0.055);
	y->SetLabelSize(0.055);
	z->SetLabelSize(0.055);
	return h;
}

TH1F* PrettyFillColor(TH1F* h, int color){
	//Recommend also using Draw("hist") 
	//Normally this is enough to get root to draw the histogram with a filled area. 
	//but sometimes it doesn't respond. In that caset Draw("hist") forces a filled area. 
	h->SetLineColor(color);
	h->SetFillColor(color);
	h->SetFillStyle(1001);
	return h;
}

TH1* PrettyBlock2(TH1* hist, int color, int style, int width){
		//These are meant for hist markers where the uncertainty range is a filled rectangle for each point and no marker
		//recommend the Draw("E2") option.
		//http://root.cern.ch/root/html/TAttFill.html
	hist->SetFillColor(color);
	hist->SetMarkerColor(color);
	hist->SetFillStyle(style);
	hist->SetMarkerSize(0); //totally sufficient for turning off the marker.
	gStyle->SetHatchesLineWidth(width);
	return hist;
}

TH1* PrettyBlock(TH1* hist, int color, string option){
		//These are meant for hist markers where the uncertainty range is a filled rectangle for each point and no marker
		//recommend the Draw("E2") option.
		//http://root.cern.ch/root/html/TAttFill.html
		//Give it a string and it'll give you your working point.
	std::map<string,int> optionMap;
	optionMap["solid"] = 0;
	optionMap[""] = 0;//also solid
	optionMap["\\thatch"] =1;//bold wide thatch \ way
	optionMap["//thatch"] = 2;//bold wide thatch / way
	optionMap["transparent"] = 3;//half transparent
		//for finer thatching, try 3004(/), 3005(\)

	hist->SetFillColor(color);
	hist->SetMarkerColor(color);
	hist->SetMarkerSize(0); //totally sufficient for turning off the marker.
	switch( optionMap[option]){
		case 0: //solid
			hist->SetFillStyle(1001);
			gStyle->SetHatchesLineWidth(1);
		case 1: //  "\thatch"
			hist->SetFillStyle(3345);
			gStyle->SetHatchesLineWidth(2);
		case 2: //  "/thatch"
			hist->SetFillStyle(3354);
			gStyle->SetHatchesLineWidth(2);
		case 3: //  transparent
			hist->SetFillStyle(4050);//half transparent, half visible
			gStyle->SetHatchesLineWidth(1);
	}//end switch
	return hist;
}



TH1F* PrettyMarker(TH1F* h, int color, int markerstyle, float markersize){
	h->SetMarkerColor(color);
	h->SetMarkerSize(markersize);
	h->SetMarkerStyle(markerstyle);
	return h;
}
TH2F* PrettyMarker(TH2F* h, int color, int markerstyle, float markersize){
	h->SetMarkerColor(color);
	h->SetMarkerSize(markersize);
	h->SetMarkerStyle(markerstyle);
	return h;
}
/*
 Marker Styles:
 Marker number         Marker shape          Marker name
 0                    no marker?
 1                    dot                  kDot
 2                    +                    kPlus
 3                    *                    kStar
 4                    o                    kCircle
 5                    x                    kMultiply
 6                    small scalable dot   kFullDotSmall
 7                    medium scalable dot  kFullDotMedium
 8                    large scalable dot   kFullDotLarge
 9 -->19              dot
 20                    full circle          kFullCircle
 21                    full square          kFullSquare
 22                    full triangle up     kFullTriangleUp
 23                    full triangle down   kFullTriangleDown
 24                    open circle          kOpenCircle
 25                    open square          kOpenSquare
 26                    open triangle up     kOpenTriangleUp
 27                    open diamond         kOpenDiamond
 28                    open cross           kOpenCross
 29                    open star            kOpenStar
 30                    full star            kFullStar
 http://physics.lunet.edu/docs/root/TAttMarker.html
 */


TLegend* newTLegend(){
		//makes a pretty TLegend with an unremarkable initial position. Use in place of "new TLegend(..." when you're lazy.
	TLegend* leg = 	new TLegend(0.75,0.60,.95,.80);
	PrettyLegend(leg);
	return leg;
}
TH1F* UnitNorm(TH1F* hist){ //makes hist have unit norm
	float norm = hist->Integral();
	if(norm >0.00001) hist->Scale(1.f/norm);
	else printf("WARNING: trying to take unit norm of an empty histogram\n");
	return hist;
}
TH2F* UnitNorm(TH2F* hist){ //makes hist have unit norm
	float norm = hist->Integral();
	if(norm >0.00001) hist->Scale(1.f/norm);
	else printf("WARNING: trying to take unit norm of an empty histogram\n");
	return hist;
}
TH1F* MatchArea(TH1F* toScale, TH1F* toMatch){
		//makes the area of toScale the same as toMatch
	float normM = toMatch->Integral();
	float normS = toScale->Integral();
	toScale->Scale(normM/normS);
	return toScale;
}
void SetRange(TH1F* hist, float _min, float _max){
//void SetRange(TH1F* hist, float min = 0.0f, float Max = -1.15);
		//set histogram range. Max = -1.15 -> Max is 115% highest bin.
	if(_max < -1 && _max > -1.2) _max = 1.15*hist->GetMaximum();
	hist->SetMaximum(_max);
	hist->SetMinimum(_min);
}
void SameRange(TH1F* hist1, TH1F* hist2){
		//sets makes the range of both histograms accomodate either histogram.
	float _max = TMath::Max(hist1->GetMaximum(),hist2->GetMaximum());
	float _min = TMath::Min(hist1->GetMinimum(),hist2->GetMinimum());
	hist1->SetMaximum(_max);
	hist1->SetMinimum(_min);
	hist2->SetMaximum(_max);
	hist2->SetMinimum(_min);
}
void SameRange(TH1F* hist1, TH1F* hist2, TH1F* hist3){
		//sets makes the range of both histograms accomodate either histogram.
	float _max = TMath::Max((float)hist1->GetMaximum(),(float)hist2->GetMaximum());
	_max = TMath::Max((float)_max,(float)hist3->GetMaximum());
	float _min = TMath::Min((float)hist1->GetMinimum(),(float)hist2->GetMinimum());
	_min = TMath::Min((float)_min,(float)hist3->GetMinimum());
	hist1->SetMaximum(_max);
	hist1->SetMinimum(_min);
	hist2->SetMaximum(_max);
	hist2->SetMinimum(_min);
	hist3->SetMaximum(_max);
	hist3->SetMinimum(_min);
}


void SameRange_and_leave_legend_room_log(std::vector<TH1F*> hists, float legendFraction, bool tinymin_override, Double_t _min, Double_t _max, bool useRangeMax){
    //Defaults: _min = -1.0, _max = -1.0, legendFraction = 0, tinymin_override = false
    //_min, _max = -1 mean we automatically set the min, if specified, we try to force the min and max to whatever is specified. 
    //Min is set to the steralized minimum of the smallest range, the lowest error bar, or the lowest bin. 
    //Max is set to the max of the highest range and the highest error bar. 
    //if Mins go less than 10^-7 we assume the min is bottoming out to zero and default it to:
    static const double default_min = 0.1;
    //This can be overridden by setting tinymin_override = true. The min will be forced non-negative. 

	//compute the min range
    Double_t h_min = default_min;
    if(aeq(_min,-1.0f)){ //if min is on auto
	Double_t min_range = hists[0]->GetMinimum();
	if( (min_range < 1.0e-7 && !tinymin_override) or min_range <= 0.0 ) min_range = default_min; //zero protect

	float min_bin = lowestBin(hists[0], true);
	if( (min_bin < 1.0e-7 && !tinymin_override) or min_bin <= 0.0 ) min_bin = default_min; //zero protect

	float min_errorbar = lowestErrorBar(hists[0], true);
	if( (min_errorbar < 1.0e-7 && !tinymin_override) or min_errorbar <= 0.0 ) min_errorbar = default_min; //zero protect

	float this_bin_min, this_min_errorbar;
	Double_t this_range_min;
	for(std::vector<TH1F*>::iterator h=hists.begin()+1; h<hists.end(); h++){
	    this_range_min = (*h)->GetMinimum();
	    if( (this_range_min < 1.0e-7 && !tinymin_override) or this_range_min <= 0.0 ) this_range_min = default_min; //zero protect
	    if(this_range_min < min_range) min_range = this_range_min;

	    this_bin_min = lowestBin(*h, true);
	    if( (this_bin_min < 1.0e-7 && !tinymin_override) or this_bin_min <= 0.0 ) this_bin_min = default_min; //zero protect
	    if(this_bin_min < min_bin) min_bin = this_bin_min;

	    this_min_errorbar = lowestErrorBar(*h, true);
	    if( (this_min_errorbar < 1.0e-7 && !tinymin_override) or this_min_errorbar <= 0.0 ) this_min_errorbar = default_min; //zero protect
	    if(this_min_errorbar < min_errorbar) min_errorbar = this_min_errorbar;
	}
	//then find the min of these three that isn't zero.
	if( (min_range > 1.0e-7      || tinymin_override) && min_range > 0.0 ) h_min = min_range;
	if( (min_bin > 1.0e-7        || tinymin_override) && min_bin > 0.0 && min_bin < h_min ) h_min = min_bin;
	if( (min_errorbar > 1.0e-7   || tinymin_override) && min_errorbar > 0.0 && min_errorbar < h_min ) h_min = min_errorbar;

	if( (h_min < 1.0e-7 && !tinymin_override) or h_min <= 0.0 ) h_min = default_min; //redundant zero protect
    }//end if find min automatically
    else{ //if h_min is specified
	h_min = _min;
	if(h_min < 0){
		cout<<"Warning! A log plot has foolishly been given a negative range min. Resetting min to 0.1"<<endl;
		h_min = 0.1;
	}
	else if(h_min < 1.0e-7 && !tinymin_override){
		 cout<<"Warning! Log plot min range set less than 10^-7, but not obviously negative. Resetting min to 0.1."<<endl<<
		       "If this isn't what you want set tinymin_override=true)"<<endl;
	}
    }//end h_min specified. 

	//compute max
    Double_t h_max;
    if(aeq(_max,-1.0f)){ //if max is on auto
	h_max = hists[0]->GetBinContent(1);
	float e_max = highestErrorBar(hists[0]);
	for(std::vector<TH1F*>::iterator h=hists.begin(); h<hists.end(); h++){
	    Double_t this_max = (*h)->GetMaximum();
	    float this_bin_max = highestBin(*h);
	    float this_e_max = highestErrorBar(*h);
	    if(useRangeMax and h_max < this_max) h_max = this_max; 
	    if(h_max < this_bin_max ) h_max = this_bin_max;
	    if(e_max < this_e_max) e_max = this_e_max;
	}//end for
	if(e_max < 2.0*h_max) h_max = TMath::Max(h_max,(double) e_max);//if max error is remotely sane
	else h_max*= 1.1;
    }
    else h_max = _max;

    if(h_max < h_min){
	h_max = 10*(h_min + 0.1); //force h_max to be more than h_min
    }

    //allow room for the legend, this is working just fine.
    float newmax;
    if(legendFraction <0 || legendFraction>1){ //if the legend fraction is borked. 
	newmax = h_max;
    }
    else newmax = TMath::Exp((TMath::Log(h_max) - legendFraction*TMath::Log(h_min))/(1.0f-legendFraction));

    for(std::vector<TH1F*>::iterator h=hists.begin(); h<hists.end(); h++) SetRange(*h,h_min,newmax); //set the ranges.
}//SameRange_and_leave_legend_room_log

void SameRange_and_leave_legend_room(std::vector<TH1F*> hists, float legendFraction, Double_t _min, Double_t _max, bool useRangeMax ){
    //Defaults: _min = -1.0, _max = -1.0, legendFraction = 0
    //_min, _max = -1 mean we automatically set the min, if specified, we try to force the min and max to whatever is specified. 
    //Min is set to the minimum of the smallest range, lowest bin, and, if either of those are < 0, the lowest error bar.
    //Max is set to the max of the highest range and the highest error bar. 
    static const double default_min = 0.;
	static const bool verbose = false;

	//compute the min range
    Double_t h_min = default_min;
    if(aeq(_min,-1.0f)){ //if min is on auto
	// if no bins go below zero, just set min to zero. 
	Double_t min_range = hists[0]->GetMinimum();
	float min_bin = lowestBin(hists[0], false);
	float min_errorbar = lowestErrorBar(hists[0], false);

	float this_bin_min, this_min_errorbar;
	Double_t this_range_min;
	for(std::vector<TH1F*>::iterator h=hists.begin()+1; h<hists.end(); h++){
	    this_range_min = (*h)->GetMinimum();
	    if(this_range_min < min_range) min_range = this_range_min;

	    this_bin_min = lowestBin(*h, false);
	    if(this_bin_min < min_bin) min_bin = this_bin_min;

	    this_min_errorbar = lowestErrorBar(*h, false);
	    if(this_min_errorbar < min_errorbar) min_errorbar = this_min_errorbar;
	}
	//then find the min of these three that isn't zero.
	if( min_range < 0.0 ) h_min = min_range;
	if( min_bin < 0.0 and min_bin < h_min ) h_min = min_bin;
	if( h_min<0.0 and min_errorbar < h_min ) h_min = min_errorbar;
    }//end if find min automatically
    else h_min = _min;//if h_min is specified

	//compute max
    Double_t h_max;
    if(aeq(_max,-1.0f)){ //if max is on auto
	if(verbose) cout<<"Doing max for "<<hists[0]->GetName()<<endl;
	h_max = hists[0]->GetBinContent(1);
	float e_max = highestErrorBar(hists[0]);
	if(verbose) cout<<"    h_max "<<h_max<<" e_max: "<<e_max<<endl;
	for(std::vector<TH1F*>::iterator h=hists.begin(); h<hists.end(); h++){
	    Double_t this_max = (*h)->GetMaximum();
	    if(verbose) cout<<"Doing max for "<<(*h)->GetName()<<endl;
	    float this_bin_max = highestBin(*h);
	    float this_e_max = highestErrorBar(*h);
	    if(useRangeMax and h_max < this_max) h_max = this_max;
	    if(h_max < this_bin_max) h_max = this_bin_max;
	    if(e_max < this_e_max) e_max = this_e_max;
	    if(verbose) cout<<"   max bin: "<<this_bin_max<<" max range: "<<this_max<<" new h_max: "<<h_max<<" max errorbar "<<this_e_max<<" new e_max "<<e_max<<endl;
	}//end for
	if(verbose) cout<<"Resut: h_max "<<h_max<<" e_max "<<e_max<<endl;
	if(e_max < 2.0*h_max) h_max = TMath::Max(h_max,(double) e_max);//if max error is remotely sane
	else h_max*= 1.1;
    }
    else h_max = _max;

    if(h_max < h_min){
	h_max = 10*(h_min + 0.1); //force h_max to be more than h_min
    }

    //allow room for the legend, this is working just fine.
    float newmax;
    if(legendFraction <=0. || legendFraction>=1.){ //if the legend fraction is borked. 
	newmax = h_max;
    }
    else newmax = (h_max - legendFraction*h_min)/(1.0f-legendFraction);
    if(verbose) cout<<"  final h_max: "<<h_max<<" newmax "<<newmax<<endl;

    for(std::vector<TH1F*>::iterator h=hists.begin(); h<hists.end(); h++) SetRange(*h,h_min,newmax); //set the ranges.
}//SameRange_and_leave_legend_room_log




float RaiseRangeRoof(TH1F* hist, float mult){
		//takes the existing max range and multiplies it by mult. Default is 1.2
		//returns what the new max is set to.
	float newmax = hist->GetMaximum()*mult;
	hist->SetMaximum(newmax);
	return newmax;
}
float highestErrorBar(TH1F *h){
	float ret = h->GetBinContent(1);
	for(int i=1;i<=h->GetNbinsX();i++){
		float temp = h->GetBinContent(i)+h->GetBinError(i);
		ret = (float)TMath::Max((Float_t)ret,(Float_t)temp);
	}
	return ret;
}
float lowestErrorBar(TH1F *h, bool ignorezero /*= false*/){
	double ret = 0;
	if(ignorezero){
	    bool uninitalized = true;
	    for(int i=1;i<=h->GetNbinsX();i++){
		double thisbin = h->GetBinContent(i);
		double thisbar = thisbin-h->GetBinError(i);
		if(!aeq(thisbin,0) && !aeq(thisbar,0) ){
		    if(uninitalized){
			ret = thisbin; //initalizer ret to the first non-zero bin you find.
			uninitalized = false;
		    }
		    else ret = TMath::Min(ret,thisbin); //once initialized, compare to find the minimum.
		}//end non-zero bin.
	    }//end for
	}//end ignore zero
	else{
	    ret = h->GetBinContent(1);
	    for(int i=1;i<=h->GetNbinsX();i++)
		ret = TMath::Min(ret,h->GetBinContent(i)-h->GetBinError(i));
	}
	return (float) ret;
}//end lowestErrorBar

float lowestBin(TH1F *h, bool ignorezero ){
	// default  ignorezero = false
	// even if ignorezero, the result may come out zero.  
	double ret = 0;//using double b/c of TMath::Min
	if(ignorezero){
	    bool uninitalized = true;
	    for(int i=1;i<=h->GetNbinsX();i++){
		double thisbin = h->GetBinContent(i);
		if(!aeq(thisbin,0) ){
		    if(uninitalized){
			ret = thisbin; //initalizer ret to the first non-zero bin you find.
			uninitalized = false;
		    }
		    else ret = TMath::Min(ret,thisbin); //once initialized, compare to find the minimum.
		}//end non-zero bin.
	    }//end for
	}//end ignore zero
	else{ //if not ignoring zero, do the simple min.
	    ret = h->GetBinContent(1);
	    for(int i=1;i<=h->GetNbinsX();i++)
		ret = TMath::Min(ret, h->GetBinContent(i));
	}
	return (float) ret;
}

float highestBin(TH1F *h){
    float ret = h->GetBinContent(1);
    for(int i=1;i<=h->GetNbinsX();i++){
	ret = (float)TMath::Max((Float_t)ret,(Float_t) h->GetBinContent(i));
    }
    return ret;
}
TH1F* playNiceWithLegend(TH1F* h, float legendFraction, float h_min, float h_max){
    //legendFraction is the proportion of the plot space on top reserved for the legend.
    //h_max and h_min are the usual bounds on the hist; by default they subsume the widest error bars.
    //IF WORKING WITH MULTIPLE HISTS, FOLLOW THIS WITH A SameRange COMMAND
    if(aeq(h_min,-1.0f)) h_min = lowestErrorBar(h);
    if(aeq(h_max,-1.0f)) h_max = highestErrorBar(h);
    if(legendFraction <0.0f || legendFraction>=1.0f){
	SetRange(h,h_min,h_max);
	return h;
    }
    float newmax = (h_max - legendFraction*h_min)/(1.0f-legendFraction);

    SetRange(h,h_min,newmax);
    return h;
}
TH1F* playNiceWithLegendLog(TH1F* h, float legendFraction, float h_min, float h_max){
    //legendFraction is the proportion of the plot space on top reserved for the legend.
    //h_max and h_min are the usual bounds on the hist; by default they subsume the widest error bars.
    //IF WORKING WITH MULTIPLE HISTS, FOLLOW THIS WITH A SameRange COMMAND


    if(aeq(h_min,-1.0f)) h_min = lowestErrorBar(h);
    if(aeq(h_max,-1.0f)) h_max = highestErrorBar(h);
    else if(h_max <=0.0f)h_max = highestErrorBar(h); //if user was stupid, fix it.

    if(h_max <=0.0f) return h;

    if(h_min <= 0.0f){
	h_min = (float) TMath::Min((double) h_min, (double) lowestBin(h)/3.0);
	if(h_min <= 0.000001) h_min = 0.1;
    }

    if(legendFraction <0.0f || legendFraction>=1.0f){
	SetRange(h,h_min,h_max);
	return h;
    }
    float newmax = TMath::Exp((TMath::Log(h_max) - legendFraction*TMath::Log(h_min))/(1.0f-legendFraction));
    SetRange(h,h_min,newmax);
    return h;
}



void DrawSame(TH1F* h0, TH1F* h1, string ops){
	std::string same = "same";
	h0->Draw(ops.c_str());
	h1->Draw((same+ops).c_str());
}
void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, string ops){
	std::string same = "same";
	h0->Draw(ops.c_str());
	h1->Draw((same+ops).c_str());
	h2->Draw((same+ops).c_str());
}

void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, TH1F* h3, string ops){
	std::string same = "same";
	h0->Draw(ops.c_str());
	h1->Draw((same+ops).c_str());
	h2->Draw((same+ops).c_str());
	h3->Draw((same+ops).c_str());
}
void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, TH1F* h3,TH1F* h4, string ops){
	std::string same = "same";
	h0->Draw(ops.c_str());
	h1->Draw((same+ops).c_str());
	h2->Draw((same+ops).c_str());
	h3->Draw((same+ops).c_str());
	h4->Draw((same+ops).c_str());
}
void DrawSame(TH1F* h0, TH1F* h1, TH1F* h2, TH1F* h3,TH1F* h4,TH1F* h5, string ops){
	std::string same = "same";
	h0->Draw(ops.c_str());
	h1->Draw((same+ops).c_str());
	h2->Draw((same+ops).c_str());
	h3->Draw((same+ops).c_str());
	h4->Draw((same+ops).c_str());
	h5->Draw((same+ops).c_str());
}



TCanvas * newTCanvas(char* rootname, char* title){
	TCanvas * canv =new TCanvas( rootname, title, 800, 800);
	canv->SetTopMargin(0.06);
	canv->SetBottomMargin(0.15);
	canv->cd();
	return canv;
}
TCanvas * newTCanvas(string rootname, string title){
	TCanvas * canv =new TCanvas( rootname.data(), title.data(), 800, 800);
	canv->SetTopMargin(0.06);
	canv->SetBottomMargin(0.15);
	canv->cd();
	return canv;
}

void DivideOutBinWidths(TH1F* h, float w){
//scale all bins to be nEvents per W[x_units] rather than nEvents per binWidth[x_units]
	for(short i=1;i<=h->GetXaxis()->GetNbins();i++){
		float scale = w/(h->GetXaxis()->GetBinWidth(i));
		float err = scale*h->GetBinError(i);
		h->SetBinContent(i,scale*h->GetBinContent(i));
		h->SetBinError(i,err);
	}
}//end DivideOutBinWidths

TCanvas*   PrettyCanvas(TCanvas* c){
    PrettyMargins(c);
    return c;
}
TCanvas* PrettyMargins(TCanvas* c, float left, float bottom, float top, float right){
    c->SetBottomMargin(bottom);
    c->SetLeftMargin(left);
    c->SetRightMargin(right);
    c->SetTopMargin(top);
    return c;
}

void SaveCanvas(TCanvas * c, string fileNameAndDir, string FileTypes){
    /*
       Supply a canvas, a name you'd like the file to have (possibly prefixed by a directory),
       and a string containing the names of file extensons.  The default is to save as .C, .root, .pdf, .jpg, .gif, .png, and .eps
       The filetype string is case insensitive.
       For example
       SaveCanvas(myCanvas, "plots/mycanvas")
       saves canvas in dir plots as mycanvas.C, mycanvas.root, mycanvas.jpg
       all types are saved.
       SaveCanvas(myCanvas, "mycanvas","jpgif")
       saves the canvas as mycanvas.jpg and mycanvas.gif
       */

    TString TFileTypes = FileTypes;
    TFileTypes.ToLower();
    string lc_types = TFileTypes.Data();
    if(lc_types.find("c")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".C").c_str());
    if(lc_types.find("root")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".root").c_str());
    if(lc_types.find("pdf")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".pdf").c_str());
    if(lc_types.find("jpg")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".jpg").c_str());
    if(lc_types.find("gif")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".gif").c_str());
    if(lc_types.find("png")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".png").c_str());
    if(lc_types.find("eps")!=string::npos) c->SaveAs((char*)(fileNameAndDir+".eps").c_str());
}

void SaveCanvas(TCanvas * c, string filename, namedstring* fileDir, string FileTypes){
    /*
       Supply a canvas, a filename you'd like the file to have, and a namestring* of {filetype, directory/} 
       and a string containing the names of file extensons.  The default is to save as .C, .root, .pdf, .jpg, .gif, .png, and .eps
       each file type will be put in a different directory. 
       The filetype string is case insensitive.

       For example
 	 stringmap s
	 s.set("jpg","plots/jpg/");
	 s.set("gif","plots/gif/");
         SaveCanvas(myCanvas, "mycanvas",&s,"jpgif")
       saves the canvas as plots/jpg/mycanvas.jpg and plots/gif/mycanvas.gif
       */

    static const string defaultdir = "plots/";
    TString TFileTypes = FileTypes;
    TFileTypes.ToLower();
    string lc_types = TFileTypes.Data();
    if(lc_types.find("c")!=string::npos)   c->SaveAs( (fileDir->get("c",   defaultdir) + filename + ".C"   ).c_str() );
    if(lc_types.find("root")!=string::npos)c->SaveAs( (fileDir->get("root",defaultdir) + filename + ".root").c_str() );
    if(lc_types.find("jpg")!=string::npos) c->SaveAs( (fileDir->get("jpg", defaultdir) + filename + ".jpg" ).c_str() );
    if(lc_types.find("pdf")!=string::npos) c->SaveAs( (fileDir->get("pdf", defaultdir) + filename + ".pdf" ).c_str() );
    if(lc_types.find("gif")!=string::npos) c->SaveAs( (fileDir->get("gif", defaultdir) + filename + ".gif" ).c_str() );
    if(lc_types.find("png")!=string::npos) c->SaveAs( (fileDir->get("png", defaultdir) + filename + ".png" ).c_str() );
    if(lc_types.find("eps")!=string::npos) c->SaveAs( (fileDir->get("eps", defaultdir) + filename + ".eps" ).c_str() );
}

TH1F* PrettyRatioPlot(TH1F* h){
        h->SetStats(0);
//	h->SetTilteSize(0);
	h->SetTitle("");
	TAxis * x = h->GetXaxis();
	TAxis * y = h->GetYaxis();

        x->SetTitleFont(Helvetica);
        x->SetTitleSize(0.200);
        x->SetTitleOffset(0.9);
	x->SetLabelFont(Helvetica);
	x->SetLabelSize(0.150);

        y->SetTitleFont(Helvetica);
	y->SetTitleSize(0.15);
	y->SetTitleOffset(0.35);
	y->SetLabelFont(Helvetica);
	y->SetLabelSize(0.150);

	//https://root.cern.ch/doc/master/classTAttAxis.html
	y->SetNdivisions(4,1,0 /*,kFalse*/); //primary axis divisions: 4,secondary axis divisions: 1
        return h;
}

#endif


