#define post_C

#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2.h>
#include <TH3.h>
#include "TAxis.h"
#include "TF1.h"
#include "TLine.h"
#include "TColor.h"

#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TLatex.h"
//#include "TGraphAsymmErrors.h"
#include <iostream>
#include <fstream>
#include "interface/DMCclass_list.h"
#include "interface/DMCblock.h"
#include "interface/stringmap.h"
#include "interface/controlpannel.h"
#include "interface/utilities.h"
#include "interface/CMSStyle.C"
#include "interface/KinematicVar.h"
#include <assert.h>

using namespace std;
using namespace controlpannel;
//void SaveCanvas(TCanvas * c, string fileNameAndDir, string FileTypes =  "crootpdfjpggif");
typedef stringmap<TH1F*> histmap;
typedef stringmap<histmap*> histtable;
typedef stringmap<TH2F*> histmap2D;
typedef stringmap<histmap2D*> histtable2D;

struct thetaSigFile{
	thetaSigFile(string _filename, double _bWbr, double _tHbr):filename(_filename),bWbr(_bWbr),tHbr(_tHbr){}
	string filename;
	double bWbr;
	double tHbr;
};
TH1F* extrackBkg(TH2F* bkg_hist);
TH1F* make_ratio_uncertainty_hist(TH1F* data, TH1F* bkg);
void fix_negatives(TH1F* hist);
void fix_negativesX(TH2F* hist);
void check_for_negatives(TH1F* hist);
string MakeThetaRootFile_Yield(string varname_, histtable htable, histmap2D* histmapbkg, histtable2D htable2D, string dir,
								std::vector<DMCclass*> vSigClassesAll, 
								std::vector<DMCclass*> vSigClassesUP, 
								std::vector<DMCclass*> vSigClassesDOWN, 
								int SignalInflationFactor,
								string dataClassName, 
								std::vector<DMCclass*> vBkgClasses, 
								std::vector<DMCclass*> vBkgClassesUP, 
								std::vector<DMCclass*> vBkgClassesDOWN, 
								bool draw_ddbkg);
string MakeThetaRootFile_Yield_nonsignal(histtable htable, histmap2D* histmapbkg,    string dir, 
	string dataClassName, std::vector<DMCclass*> vBkgClasses, std::vector<DMCclass*> vBkgClassesUP, std::vector<DMCclass*> vBkgClassesDOWN, bool draw_ddbkg );
std::vector<thetaSigFile*> MakeThetaRootFile_Yield_signalScan(stringmap<std::vector<TH1F*>> Signal_yields,  std::vector<DMCclass*> vSigClassesAll,string dir, int nBRslices);
TH1F* brRescale( std::vector<TH1F*> hists, float bWbr, float tHbr, string outname);
string MakeThetaCounts(histtable htable, histmap2D* histmapbkg, string SigClassToUse, std::vector<DMCclass*> vBkgClasses,bool draw_ddbkg);

string ThetaFileNameSig(string directory, string classname, double bWbr, double tHbr);
float get_bZbr(float bWbr, float tHbr);


void post(){
	CMSStyle();
	TH1::AddDirectory(kFALSE);
	//typedef stringmap<TH1F*> histmap;
	//typedef stringmap<histmap*> histtable;
	//typedef stringmap<TH2F*> histmap2D;
	//typedef stringmap<histmap2D*> histtable2D;
	std::vector<string> SigtoInclude;
	std::vector<string> plotnames; 
	std::vector<string> bkgplotnames; 
	std::vector<string> sysplotnames; // added by rizki - for s_yield 
	LabelKinVars allkinvar_stringmap = setupAllKinematicVar(); //the entire universe of kinvars
	stringmap<KinematicVar*> chosenkinvar_stringmap; // map from plotname to the corresponding kinvar. 

	///////////////////////////// Switcehs //////////////////////////////////////
	//Most switches are on the control pannel. 
	bool saveImages = true;
	bool draw_ddbkg  = true;
	//
	bool makeStackPlots_lin = false;
	bool makeStackPlots_lin_ratio = false;

	bool makeStackPlots_log = false;
	bool makeStackPlots_log_ratio = true;
	
	bool makeStackPlots_log_SBsignif = false ; //added by rizki
	bool produceThetaOut = true;

	///////////////////////////// Lists  //////////////////////////////////////
	namedstring plotdirs;
	plotdirs.set("c", plotsdirC);
	plotdirs.set("root", plotsdirroot);
	plotdirs.set("jpg", plotsdirjpg );
	plotdirs.set("pdf", plotsdirpdf );
	plotdirs.set("png", plotsdirpng );
	plotdirs.set("gif", plotsdirgif );
	plotdirs.set("eps", plotsdireps );


	SigtoInclude.push_back(string("sigTpTp700")+(T50ns_F25ns?"s":"f"));
// 	SigtoInclude.push_back(string("sigTpTp800")+(T50ns_F25ns?"s":"f"));
	SigtoInclude.push_back(string("sigTpTp1200")+(T50ns_F25ns?"s":"f"));
	string dataClassName = string("Data2lep")+(T50ns_F25ns?"s":"f");

	//MAKE A LIST OF ALL THE PLOT NAMES TO LOAD IN: "plotnames", AND BKG PLOT NAMES "bkgplotnames"
	//Map the plotname or bkgplotname  to the kinvar in chosenkinvar_stringmap.set
	try{
	    //Special plots to load in

// 	    plotnames.push_back("h_ST_OSDL1sansS"); chosenkinvar_stringmap.set(plotnames.back(),allkinvar_stringmap->get_throwable("ST",1));
// 	    plotnames.push_back("h_ST_OSDL1sansSlb"); chosenkinvar_stringmap.set(plotnames.back(),allkinvar_stringmap->get_throwable("ST",1));
	    plotnames.push_back("h_yield"); chosenkinvar_stringmap.set(plotnames.back(),allkinvar_stringmap->get_throwable("yield",1));

	    sysplotnames.push_back("s_yield"); chosenkinvar_stringmap.set(sysplotnames.back(),allkinvar_stringmap->get_throwable("yield",1)); //added by rizki - for s_yield

		//Special background plots to load in	
// 	    bkgplotnames.push_back("b_ST_OSDL1sansS"); chosenkinvar_stringmap.set(bkgplotnames.back(),allkinvar_stringmap->get_throwable("ST",1));
// 	    bkgplotnames.push_back("b_ST_OSDL1sansSlb"); chosenkinvar_stringmap.set(bkgplotnames.back(),allkinvar_stringmap->get_throwable("ST",1));
	    bkgplotnames.push_back("b_yield"); chosenkinvar_stringmap.set(bkgplotnames.back(),allkinvar_stringmap->get_throwable("yield",1));

		for (int iTopo = 0; iTopo<nEventTopologies; iTopo++) {
		    for (int kKinVar = 0; kKinVar < nKinemVars_all; kKinVar++) {

				//make a list of the names of all the grid plots
				plotnames.push_back( string("h_")+s_KinemVars_all[kKinVar]+s_EventTopology[iTopo]);
				chosenkinvar_stringmap.set(plotnames.back(),allkinvar_stringmap->get_throwable(s_KinemVars_all[kKinVar],2)); //map kinvars to plotname

				//make a list of the names of all the background grid plots
				bkgplotnames.push_back( string("b_")+s_KinemVars_all[kKinVar]+s_EventTopology[iTopo]);
				chosenkinvar_stringmap.set(bkgplotnames.back(),allkinvar_stringmap->get_throwable(s_KinemVars_all[kKinVar],3)); //map kinvars to plotname
		    }//end for every kinvar
		}//end for every topo
	}//end list all special plot names
	catch(std::pair <std::string,int> errorpair){
        switch(errorpair.second ){
        	case 1: cerr<<"Stringmap Error! While setting up specail plot names. Invalid string key "<<errorpair.first<< " sought in allkinvar_stringmap"<<endl; break;
        	case 2: cerr<<"Stringmap Error! While setting up general plot names. Invalid string key "<<errorpair.first<< " sought in allkinvar_stringmap"<<endl;
        	case 3: cerr<<"Stringmap Error! While setting up general plot names. Invalid string key "<<errorpair.first<< " sought in allkinvar_stringmap"<<endl;
        }//end switch
	    std::terminate();
	}

	//add to the list  a list of all the grid plots names to intake, then list all the bkg plots. 
		
	//Make a list vClasses of all the classes to run
	DMCclass* dataClass = setupDMCclass( dataClassName);
	std::vector<DMCclass*> vBkgClasses     = MCbkgDMCclass(T50ns_F25ns);//bkgs that will go on the plot. 
	std::vector<DMCclass*> vBkgClassesDOWN = MCbkgDMCclassDOWN(T50ns_F25ns, useBTagSys, useJECsys, useJERsys);
	std::vector<DMCclass*> vBkgClassesUP   = MCbkgDMCclassUP(T50ns_F25ns, useBTagSys, useJECsys, useJERsys);
	std::vector<DMCclass*> vSigClassesAll = MCTpTpsigDMCclass(T50ns_F25ns);//all the signal classes, used for limits. 
	std::vector<DMCclass*> vSigClasses; //The signal classes to go on the plots

	std::vector<DMCclass*> vSigClassesUP = MCTpTpsigDMCclassUP(T50ns_F25ns, useBTagSys, useJECsys, useJERsys); 
	std::vector<DMCclass*> vSigClassesDOWN = MCTpTpsigDMCclassDOWN(T50ns_F25ns, useBTagSys, useJECsys, useJERsys); 

	std::vector<DMCclass*> vClasses; //mostly a copy of vBkgClasses, but with MC and data appended. 
	std::vector<DMCclass*> vClassesAll; //data+sig+sig_up/down+bkg+bkg_up/down
	std::vector<DMCclass*> vClassesSys; //for pulling out s_yield in sig+bkg
	
	//vectorize all the classes 

	//find the signal classes you want on the plots. add them to vSigClasses and vClasses. 
	for(std::vector<string>::iterator istr=SigtoInclude.begin();istr<SigtoInclude.end();istr++){ //for all the chosen siganl classes. 
	    for(std::vector<DMCclass*>::iterator iclass = vSigClassesAll.begin();iclass< vSigClassesAll.end();iclass++){ //look @ all sig classes
			if((*iclass)->name.compare(*istr) ==0){ //if it's one of the signal classes you wanted. 
				vSigClasses.push_back(*iclass);//add to the list of desired signal classes
				vClasses.push_back(*iclass); //and add it to the list of all classes for the plots .
				break;
			}
	    }
	}
	//for(std::vector<string>::iterator    istr   =SigtoInclude.begin();istr  <SigtoInclude.end();istr++)vSigClasses.push_back(setupDMCclass(*istr));
	//for(std::vector<DMCclass*>::iterator iclass = vSigClasses.begin();iclass< vSigClasses.end();iclass++) vClasses.push_back((*iclass));
	vClasses.push_back(dataClass);
	stringmap<DMCclass*>* mClasses =  makemap(vClasses);
// 	for(std::vector<DMCclass*>::iterator iclass = vClasses.begin();iclass< vClasses.end();iclass++) vClassesAll.push_back((*iclass));

	vClassesAll.push_back(dataClass);
	for(std::vector<DMCclass*>::iterator iclass = vSigClassesAll.begin();iclass< vSigClassesAll.end();iclass++)vClassesAll.push_back((*iclass));
	for(std::vector<DMCclass*>::iterator iclass = vSigClassesUP.begin();iclass< vSigClassesUP.end();iclass++) vClassesAll.push_back((*iclass));
	for(std::vector<DMCclass*>::iterator iclass = vSigClassesDOWN.begin();iclass< vSigClassesDOWN.end();iclass++) vClassesAll.push_back((*iclass));
	for(std::vector<DMCclass*>::iterator iclass = vBkgClasses.begin();iclass< vBkgClasses.end();iclass++)vClassesAll.push_back((*iclass));
	for(std::vector<DMCclass*>::iterator iclass = vBkgClassesUP.begin();iclass< vBkgClassesUP.end();iclass++) vClassesAll.push_back((*iclass));
	for(std::vector<DMCclass*>::iterator iclass = vBkgClassesDOWN.begin();iclass< vBkgClassesDOWN.end();iclass++) vClassesAll.push_back((*iclass));
	stringmap<DMCclass*>* mClassesAll =  makemap(vClassesAll);

	// for pulling out s_yield - added by rizki
	for(std::vector<DMCclass*>::iterator iclass = vSigClassesAll.begin();iclass< vSigClassesAll.end();iclass++)vClassesSys.push_back((*iclass));
	for(std::vector<DMCclass*>::iterator iclass = vBkgClasses.begin();iclass< vBkgClasses.end();iclass++)vClassesSys.push_back((*iclass));

	
	    ///////////////////////////// File Work ///////////////////////////////////////

	    ////////////////////////// LOAD MAIN HISTOGRAMS ///////////////////////////////

	//load in all the histograms from all the files. 
	cout<<"Start loading plots from files"<<endl;
	histtable htable; //[vClass name][plotname]
	std::vector<TFile*> vFiles;
	int start_of_data_in_vFiles=-1;//will hold the index of vFiles of the first data file. 
	int start_of_signal_in_vFiles=-1;//will hold the index of vFiles of the first data file. 
	for(std::vector<DMCclass*>::iterator iclass = vClassesAll.begin();iclass<vClassesAll.end();iclass++){ //for every dmc class. 
		bool firstround = true; //tells if it's the first block in the iclass. 
		histmap* temphistmap = new histmap();
		//cout<<"loading for "<<(*iclass)->name<<endl;
		for(std::vector<DMCblock*>::iterator iblock = (*iclass)->blocks.begin();iblock<(*iclass)->blocks.end();iblock++){ //for every block
			if( not fileExists( (*iblock)->string_meta["EventLoopOutRoot"]) ){
			    cerr<<"Error! Cannot find EventLoop file "<<(*iblock)->string_meta["EventLoopOutRoot"]<< " for DMCblock "<<(*iblock)->name<<endl;
			    std::terminate();
			}
			vFiles.push_back(TFile::Open((*iblock)->string_meta["EventLoopOutRoot"].c_str(), "READ"));
			//vFiles.push_back(new TFile((*iblock)->string_meta["EventLoopOutRoot"].c_str(), "READ"));
			//if((*iclass)->name.compare(dataClassName)==0 and firstround) start_of_data_in_vFiles = vFiles.size()-1;//old note which file the data starts on.
			if((*iclass)->int_meta["isData"]==1   and start_of_data_in_vFiles   ==-1) start_of_data_in_vFiles = vFiles.size()-1;//note which file the data starts on.
			if((*iclass)->int_meta["isSignal"]==1 and start_of_signal_in_vFiles ==-1){
			    start_of_signal_in_vFiles = vFiles.size()-1;//note which file the signal starts on.
				cout<<"setting start_of_signal_in_vFiles to "<<start_of_signal_in_vFiles<<" which is "<<vFiles.back()->GetName()<<" = "<<vFiles[start_of_signal_in_vFiles]->GetName()<<endl;
			}
			vFiles.back()->cd();

		//cout<<"loading for block "<<(*iblock)->name<<endl;
			for(std::vector<string>::iterator iplot = plotnames.begin(); iplot<plotnames.end();iplot++){
				if(not vFiles.back()->GetListOfKeys()->Contains((*iplot).c_str()) ){
				    cerr<<"Error! Cannot find plot "<<*iplot<<" in file "<<(*iblock)->string_meta["EventLoopOutRoot"]<< " for DMCblock "<<(*iblock)->name<<endl;
				    std::terminate();

				}
				//cout<<"fetching "<<*iplot<<endl;

                TH1F* temp = (TH1F*)vFiles.back()->Get((*iplot).c_str());//
				TH1F* temp2;
				if(firstround) temp2 = (TH1F*)temp->Clone((*iplot + "_" + (*iclass)->name ).c_str());
				else           temp2 = (TH1F*)temp->Clone((*iplot + "_" + (*iblock)->name ).c_str());

				AddOverflow(temp2);
				fix_negatives(temp2);

				if((*iblock)->isMC) temp2->Scale(Integrated_Luminosity_Data*1000.0*(*iblock)->cs_pb/((*iblock)->NGenPoints));

				try{
				    KinematicVar* thiskinvar = chosenkinvar_stringmap.get_throwable(*iplot,2);

					//rebin histogram
				    /*if( thiskinvar->useCustomReBinning) 
					temp2 = (TH1F*)temp2->Rebin(thiskinvar->nbins_rebin / thiskinvar->nbins, (string(temp2->GetName())+"_r").c_str(), thiskinvar->CustomReBinning );
				    else temp2 = (TH1F*)temp2->Rebin(thiskinvar->nbins_rebin, (string(temp2->GetName())+"_r").c_str() );
					*/
					//see Rebin documentation here: https://root.cern.ch/doc/master/classTH1.html#aff6520fdae026334bf34fa1800946790
					//attempt to set labels
					if(thiskinvar->tag.compare("HT") == 0) temp2 = (TH1F*)temp2->Rebin(40,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("ST") == 0) temp2 = (TH1F*)temp2->Rebin(2,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("MET") == 0) temp2 = (TH1F*)temp2->Rebin(12,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("BTm") == 0) temp2 = (TH1F*)temp2->Rebin(30,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("BTl") == 0) temp2 = (TH1F*)temp2->Rebin(30,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("MinMlb") == 0) temp2 = (TH1F*)temp2->Rebin(2,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("Mll") == 0) temp2 = (TH1F*)temp2->Rebin(4,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("Mlll") == 0) temp2 = (TH1F*)temp2->Rebin(8,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("minMll") == 0) temp2 = (TH1F*)temp2->Rebin(10,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("LepT") == 0) temp2 = (TH1F*)temp2->Rebin(16,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("MSum") == 0) temp2 = (TH1F*)temp2->Rebin(10,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("LHT") == 0) temp2 = (TH1F*)temp2->Rebin(20,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("MSumovST") == 0) temp2 = (TH1F*)temp2->Rebin(4,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("MtSum") == 0) temp2 = (TH1F*)temp2->Rebin(25,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("lepPt") == 0) temp2 = (TH1F*)temp2->Rebin(4,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("jetPt") == 0) temp2 = (TH1F*)temp2->Rebin(4,(string(temp2->GetName())+"_r").c_str());	

					else if(thiskinvar->tag.compare("jetLooseNotTightMuonDR") == 0) temp2 = (TH1F*)temp2->Rebin(2,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("TightEleLooseNotTightMuonDR") == 0) temp2 = (TH1F*)temp2->Rebin(2,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("LooseMuonLooseNotTightEleDR") == 0) temp2 = (TH1F*)temp2->Rebin(2,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("jetLooseNotTightEleDR") == 0) temp2 = (TH1F*)temp2->Rebin(2,(string(temp2->GetName())+"_r").c_str());	


				    temp2->SetTitle( thiskinvar->titles.c_str() );
				    temp2->SetXTitle( thiskinvar->xlabels.c_str() );
				    temp2->SetYTitle( "Events" );

				    if(firstround) temphistmap->set(*iplot,temp2); 
				    else temphistmap->get_throwable(*iplot,3)->Add(temp2); 
				    //cout<<"Class "<<(*iclass)->name<<" block "<<(*iblock)->name<<" plot "<<*iplot<<". Adding "<<temp2->Integral()<<" Sum: "<<
				    //	temphistmap->get_throwable(*iplot)->Integral()<<endl;
				}
				catch(std::pair <std::string,int> errorpair){
				    cerr<<"Stringmap Error! Invalid string key "<<errorpair.first<< " sought in temphistmap. Error code "<<errorpair.second<<endl;
				    std::terminate();
				}
			//	cout<<"end "<<*iplot<<endl<<flush;

			} //for ever plot in the file 
			firstround = false;
			cout<<"end block "<<(*iblock)->name<<endl<<flush;
			delete vFiles.back() ; //TESTINGG!! - rizki
		}//for every block in the class
		htable.set((*iclass)->name,temphistmap);
	}//end for every DMCclass

	/*cout<<"Test bkgplotname behavior on repeated calling"<<endl;
	    for(std::vector<string>::iterator iplot = bkgplotnames.begin(); iplot<bkgplotnames.end();iplot++){ cout<<*iplot<<endl; }
	cout<<"2"<<endl<<flush;
	    for(std::vector<string>::iterator iplot = bkgplotnames.begin(); iplot<bkgplotnames.end();iplot++){ cout<<*iplot<<endl; }
	cout<<"3"<<endl<<flush;
	    for(std::vector<string>::iterator iplot = bkgplotnames.begin(); iplot<bkgplotnames.end();iplot++){ cout<<*iplot<<endl; }
	cout<<"Should be stable by now. if this isn't changig, then something is changing iplot as it gots."<<endl<<flush;*/
		//you know this produces nothing. 
	

	////////////////////////// Load signal yields /////////////////////////////////////
	        //construct a map of Signal_yields[iClass name in vSigClassesAll][iyield]
	        /*
	string h_yield_strings[nBByields] = {"h_yield_WW", "h_yield_WH", "h_yield_WZ", "h_yield_HH", "h_yield_HZ", "h_yield_ZZ"};
	        //0:WW, 1:WH, 2: WZ, 3: HH, 4: HZ, 5: ZZ 
	stringmap<std::vector<TH1F*>> Signal_yields;//only the ones that are meant to be included. 
	stringmap<std::vector<TH1F*>> Signal_yields_all;//for all the signal. 

	cout<<"Beginning to Fetch Yields"<<endl;
	for(std::vector<DMCclass*>::iterator iclass = vSigClassesAll.begin();iclass<vSigClassesAll.end();iclass++){ //for every dmc class. 
	    bool firstblock = true;
	    std::vector<TH1F*> hists; 

	    for(std::vector<DMCblock*>::iterator iblock = (*iclass)->blocks.begin();iblock<(*iclass)->blocks.end();iblock++){ //for every block
		int thisfile = start_of_signal_in_vFiles++; //appears to not be getting pointed to the right file.
		vFiles[thisfile]->cd();

		for(int iyield = 0;iyield<nBByields;iyield++){
		    if( string(vFiles[thisfile]->GetName()).compare((*iblock)->string_meta["EventLoopOutRoot"]) != 0){
			cerr<<"Yield File Getter has file mismatch: start_of_signal_in_vFiles indicates "<<vFiles[thisfile]->GetName()<<" but we want "<<(*iblock)->string_meta["EventLoopOutRoot"]<<endl;
			std::terminate();
		    } 
		    if(not vFiles[thisfile]->GetListOfKeys()->Contains((h_yield_strings[iyield]).c_str()) ){
			cerr<<"Error! in Get BByields: Cannot find plot "<<h_yield_strings[iyield]<<" in file "<<(*iblock)->string_meta["EventLoopOutRoot"]<< " for DMCblock "<<(*iblock)->name<<endl;
			std::terminate();
		    }

		    TH1F* temp = (TH1F*) vFiles[thisfile]->Get(h_yield_strings[iyield].c_str());
		    TH1F* temp2;
		    if(firstblock) temp2 = (TH1F*)temp->Clone((h_yield_strings[iyield] + "_" + (*iclass)->name ).c_str());
		    else           temp2 = (TH1F*)temp->Clone((h_yield_strings[iyield] + "_" + (*iblock)->name ).c_str());

		    temp2->Scale(Integrated_Luminosity_Data*1000.0*(*iblock)->cs_pb/((*iblock)->NGenPoints));

		    if(firstblock) hists.push_back(temp2);
		    else hists[iyield]->Add(temp2); 
		}//for every h_yield.
		firstblock = false;
	    }//end for every block
	    Signal_yields.set((*iclass)->name,hists);
	}//end for every signal class
*/



	////////////////////////// LOAD BACKGROUND HISTOGRAMS ///////////////////////////////
	cout<<"Start loading bkg plots from files"<<endl;
	//load histograms into histmapbkg

	bool firstround = true;
	TFile* data_f;
	histmap2D* histmapbkg = new histmap2D();
	for(std::vector<DMCblock*>::iterator iblock = dataClass->blocks.begin();iblock<dataClass->blocks.end();iblock++){ //for every block
	    int thisfile = start_of_data_in_vFiles++;
// 	    vFiles[thisfile]->cd();//cd to the data files. This only works if ddbkgclass only contains dataClass.
		if( not fileExists( (*iblock)->string_meta["EventLoopOutRoot"]) ){
			    cerr<<"Error! Cannot find EventLoop file "<<(*iblock)->string_meta["EventLoopOutRoot"]<< " for DMCblock "<<(*iblock)->name<<endl;
			    std::terminate();
		}
		data_f = TFile::Open((*iblock)->string_meta["EventLoopOutRoot"].c_str(), "READ");
		data_f->cd();

// 	    cout<<"loading for block "<<(*iblock)->name<<endl;
	    for(std::vector<string>::iterator iplot = bkgplotnames.begin(); iplot<bkgplotnames.end();iplot++){
// 			if(not vFiles[thisfile]->GetListOfKeys()->Contains((*iplot).c_str()) ){
			if(not data_f->GetListOfKeys()->Contains((*iplot).c_str()) ){
				cerr<<"Error! Cannot find plot "<<*iplot<<" in file "<<(*iblock)->string_meta["EventLoopOutRoot"]<< " for DMCblock "<<(*iblock)->name<<endl;
				std::terminate();
			}
	// 		cout<<"fetching "<<*iplot<<endl;

// 			TH2F* temp = (TH2F*)vFiles[thisfile]->Get((*iplot).c_str());///fix.
			TH2F* temp = (TH2F*)data_f->Get((*iplot).c_str());///fix.
			//cout<<"bkg "<<(*iblock)->name<<" plot "<<*iplot<<" first bkg bin: "<<temp->GetBinContent(1,1)<<endl;//xxx
			TH2F* temp2;
			if(firstround) temp2 = (TH2F*)temp->Clone((*iplot + "_ddBkg").c_str());
			else{
				temp2 = (TH2F*)temp->Clone((*iplot + "_" + (*iblock)->name ).c_str());
				//cout<<"Try cloning under second round with "<<(*iplot) + "_" + (*iblock)->name<<endl<<flush;
			}

			AddOverflowX(temp2);
			fix_negativesX(temp2);
			assert(!(*iblock)->isMC);

			try{
				KinematicVar* thiskinvar = chosenkinvar_stringmap.get_throwable(*iplot,2);

				if(thiskinvar->tag.compare("HT") == 0) temp2 = (TH2F*)temp2->RebinX(40,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("ST") == 0) temp2 = (TH2F*)temp2->RebinX(2,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("MET") == 0) temp2 = (TH2F*)temp2->RebinX(12,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("BTm") == 0) temp2 = (TH2F*)temp2->RebinX(30,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("BTl") == 0) temp2 = (TH2F*)temp2->RebinX(30,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("MinMlb") == 0) temp2 = (TH2F*)temp2->RebinX(2,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("Mll") == 0) temp2 = (TH2F*)temp2->RebinX(4,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("Mlll") == 0) temp2 = (TH2F*)temp2->RebinX(8,(string(temp2->GetName())+"_r").c_str());	// added by rizki - IS THIS RIGHT??
				else if(thiskinvar->tag.compare("minMll") == 0) temp2 = (TH2F*)temp2->RebinX(10,(string(temp2->GetName())+"_r").c_str()); // added by rizki - IS THIS RIGHT??
				else if(thiskinvar->tag.compare("LepT") == 0) temp2 = (TH2F*)temp2->RebinX(16,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("MSum") == 0) temp2 = (TH2F*)temp2->RebinX(10,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("LHT") == 0) temp2 = (TH2F*)temp2->RebinX(20,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("MSumovST") == 0) temp2 = (TH2F*)temp2->RebinX(4,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("MtSum") == 0) temp2 = (TH2F*)temp2->RebinX(25,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("lepPt") == 0) temp2 = (TH2F*)temp2->RebinX(4,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("jetPt") == 0) temp2 = (TH2F*)temp2->RebinX(4,(string(temp2->GetName())+"_r").c_str());	

				else if(thiskinvar->tag.compare("jetLooseNotTightMuonDR") == 0) temp2 = (TH2F*)temp2->RebinX(2,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("TightEleLooseNotTightMuonDR") == 0) temp2 = (TH2F*)temp2->RebinX(2,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("LooseMuonLooseNotTightEleDR") == 0) temp2 = (TH2F*)temp2->RebinX(2,(string(temp2->GetName())+"_r").c_str());	
				else if(thiskinvar->tag.compare("jetLooseNotTightEleDR") == 0) temp2 = (TH2F*)temp2->RebinX(2,(string(temp2->GetName())+"_r").c_str());	


				temp2->SetTitle( thiskinvar->titles.c_str() );
				temp2->SetXTitle( thiskinvar->xlabels.c_str() );
				temp2->SetYTitle( "Events" );

				//change the plot name index to the same index system used by everything else. 
				string thisbkgplotname(*iplot);//copy iplot
				thisbkgplotname.replace(0,1,"h");//convert to the h_form for indexing. 
				//cout<<"Check: iplot should be b_: "<<*iplot<<" and thisbkgplotname should be h_: "<<thisbkgplotname<<endl;
				assert(thisbkgplotname.compare(*iplot));

				if(firstround) histmapbkg->set(thisbkgplotname,temp2); 
				else histmapbkg->get_throwable(thisbkgplotname,3)->Add(temp2); 
			}
			catch(std::pair <std::string,int> errorpair){
				cerr<<"Stringmap Error! Invalid string key "<<errorpair.first<< " sought in histmapbkg. Error code "<<errorpair.second<<endl;
				std::terminate();
			}//end catch 
	    } //for ever plot in the file 
	    firstround = false;
	    delete data_f; //TESTING!! this seems to work? -rizki
	}//for every block in the class


	// added by rizki - start - attempt to pull out s_yields
	////////////////////////// LOAD SYSTEMATICS (s_yield) HISTOGRAMS ///////////////////////////////
	cout<<"Start loading sys plots from files"<<endl;
	//load histograms into histmapsys
	TFile *sys_f;
	histtable2D htable2D; //[vClass name][plotname]	
	for(std::vector<DMCclass*>::iterator iclass = vClassesSys.begin();iclass<vClassesSys.end();iclass++){ //for every dmc class. 
		bool firstround = true; //tells if it's the first block in the iclass. 
		histmap2D* histmapsys = new histmap2D();
		//cout<<"loading for "<<(*iclass)->name<<endl;
		for(std::vector<DMCblock*>::iterator iblock = (*iclass)->blocks.begin();iblock<(*iclass)->blocks.end();iblock++){ //for every block
			if( not fileExists( (*iblock)->string_meta["EventLoopOutRoot"]) ){
			    cerr<<"Error! Cannot find EventLoop file "<<(*iblock)->string_meta["EventLoopOutRoot"]<< " for DMCblock "<<(*iblock)->name<<endl;
			    std::terminate();
			}
			sys_f = TFile::Open((*iblock)->string_meta["EventLoopOutRoot"].c_str(), "READ");
			sys_f->cd();


		//cout<<"loading for block "<<(*iblock)->name<<endl;
			for(std::vector<string>::iterator iplot = sysplotnames.begin(); iplot<sysplotnames.end();iplot++){
				if(not sys_f->GetListOfKeys()->Contains((*iplot).c_str()) ){
					cerr<<"Error! Cannot find plot "<<*iplot<<" in file "<<(*iblock)->string_meta["EventLoopOutRoot"]<< " for DMCblock "<<(*iblock)->name<<endl;
					std::terminate();
				}
	// 		cout<<"fetching "<<*iplot<<endl;

				TH2F* temp = (TH2F*)sys_f->Get((*iplot).c_str());///fix.
				//cout<<"bkg "<<(*iblock)->name<<" plot "<<*iplot<<" first bkg bin: "<<temp->GetBinContent(1,1)<<endl;//xxx
				TH2F* temp2;
				
				//what is this for??
// 				if(firstround) temp2 = (TH2F*)temp->Clone((*iplot + "_" + (*iclass)->name).c_str());
// 				else           temp2 = (TH2F*)temp->Clone((*iplot + "_" + (*iblock)->name ).c_str());

				temp2 = (TH2F*)temp->Clone((*iplot + "_" + (*iblock)->name).c_str());


				AddOverflowX(temp2);
				fix_negativesX(temp2);

				//need to scale same as in LOAD MAIN HISTOGRAM section
				temp2->Scale(Integrated_Luminosity_Data*1000.0*(*iblock)->cs_pb/((*iblock)->NGenPoints));

				try{
					KinematicVar* thiskinvar = chosenkinvar_stringmap.get_throwable(*iplot,2);

					if(thiskinvar->tag.compare("HT") == 0) temp2 = (TH2F*)temp2->RebinX(40,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("ST") == 0) temp2 = (TH2F*)temp2->RebinX(2,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("MET") == 0) temp2 = (TH2F*)temp2->RebinX(12,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("BTm") == 0) temp2 = (TH2F*)temp2->RebinX(30,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("BTl") == 0) temp2 = (TH2F*)temp2->RebinX(30,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("MinMlb") == 0) temp2 = (TH2F*)temp2->RebinX(2,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("Mll") == 0) temp2 = (TH2F*)temp2->RebinX(4,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("Mlll") == 0) temp2 = (TH2F*)temp2->RebinX(8,(string(temp2->GetName())+"_r").c_str());	// added by rizki - IS THIS RIGHT??
					else if(thiskinvar->tag.compare("minMll") == 0) temp2 = (TH2F*)temp2->RebinX(10,(string(temp2->GetName())+"_r").c_str()); // added by rizki - IS THIS RIGHT??
					else if(thiskinvar->tag.compare("LepT") == 0) temp2 = (TH2F*)temp2->RebinX(16,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("MSum") == 0) temp2 = (TH2F*)temp2->RebinX(10,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("LHT") == 0) temp2 = (TH2F*)temp2->RebinX(20,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("MSumovST") == 0) temp2 = (TH2F*)temp2->RebinX(4,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("MtSum") == 0) temp2 = (TH2F*)temp2->RebinX(25,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("lepPt") == 0) temp2 = (TH2F*)temp2->RebinX(4,(string(temp2->GetName())+"_r").c_str());	
					else if(thiskinvar->tag.compare("jetPt") == 0) temp2 = (TH2F*)temp2->RebinX(4,(string(temp2->GetName())+"_r").c_str());	

					temp2->SetTitle( thiskinvar->titles.c_str() );
					temp2->SetXTitle( thiskinvar->xlabels.c_str() );
					temp2->SetYTitle( "Events" );

					//change the plot name index to the same index system used by everything else. 
					string thisplotname(*iplot);//copy iplot
					thisplotname.replace(0,1,"h");//convert to the h_form for indexing. 
					//cout<<"Check: iplot should be s_: "<<*iplot<<" and thisbkgplotname should be h_: "<<thisbkgplotname<<endl;
					assert(thisplotname.compare(*iplot));

					if(firstround) histmapsys->set(thisplotname,temp2); 
					else histmapsys->get_throwable(thisplotname,3)->Add(temp2); 
				}
				catch(std::pair <std::string,int> errorpair){
					cerr<<"Stringmap Error! Invalid string key "<<errorpair.first<< " sought in histmapbkg. Error code "<<errorpair.second<<endl;
					std::terminate();
				}//end catch 
			} //for ever plot in the file 
	    	firstround = false;
	    	delete sys_f; //this seems to work? - rizki
		}//for every block in the class
		htable2D.set((*iclass)->name,histmapsys);
	}
	// added by rizki - end - attempt to pull out s_yields


	////////////////////////////////////////////////////////
	//////////////////////// END FILEWORK //////////////////
	////////////////////////////////////////////////////////
	//finished loading all the plots into memory. 
	cout<<"Finished loading all plots from all files"<<endl;
	

	//Build 1D data driven backgrounds
	histmap histmapbkg1D; 		
	for(std::map<std::string, TH2F*>::iterator iplot=histmapbkg->begin(); iplot!=histmapbkg->end(); ++iplot) {
	    histmapbkg1D.set(iplot->first, extrackBkg(iplot->second));
	}
		

	

	////////////////////////////////////////////////////////
	//////////////////////MAKE PLOTS////////////////////////
	////////////////////////////////////////////////////////
 	
//Run 2 has different rules for the plot decorations: 
//no more integal sign, no more sqrt symbol. 
//use Helvetica. 
	
      TLatex *TEX_CMSlumi = new TLatex(0.879397, 0.92238,Form("%.1f fb^{-1} (13 TeV)",Integrated_Luminosity_Data));
      TLatex *TEX_CMSlumi_rat = new TLatex(0.943467,0.92,Form("%.1f fb^{-1} (13 TeV)",Integrated_Luminosity_Data));
      TEX_CMSlumi->SetTextAlign(right_justify);
      TEX_CMSlumi_rat->SetTextAlign(right_justify);

      TLatex *TEX_CMSSim = new TLatex(0.174623, 0.92238,"#bf{CMS} #it{Simulation}");
      TLatex *TEX_CMSPrelim = new TLatex(0.174623, 0.92238, "#bf{CMS} #it{Preliminary}");
      TLatex *TEX_CMSReal = new TLatex(0.174623, 0.92238,"#bf{CMS}");
      //TLatex *TEX_CMSReal = new TLatex(0.15,0.92,"#bf{CMS}");

      TLatex *TEX_CMSSim_rat = new TLatex(0.174623,0.92,"#bf{CMS} #it{Simulation}");
      TLatex *TEX_CMSPrelim_rat = new TLatex(0.174623,0.92, "#bf{CMS} #it{Preliminary}");
      TLatex *TEX_CMSReal_rat = new TLatex(0.174623,0.92,"#bf{CMS}");

      /*TLatex *TEX_CMSSim = new TLatex(0.15,0.92,Form("CMS Simulation, #scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}, #sqrt{s} = 13 TeV",Integrated_Luminosity_Data));
      TLatex *TEX_CMSPrelim = new TLatex(0.15,0.92,Form("CMS Preliminary, #scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}, #sqrt{s} = 13 TeV",Integrated_Luminosity_Data));
      TLatex *TEX_CMSReal = new TLatex(0.15,0.92,Form("CMS, #scale[0.75]{#int}#it{L} d#it{t} = %.1f fb^{-1}, #sqrt{s} = 13 TeV",Integrated_Luminosity_Data));*/
      PrettyLatex(TEX_CMSlumi,0.04);
      PrettyLatex(TEX_CMSSim,0.04);
      PrettyLatex(TEX_CMSPrelim,0.04);
      PrettyLatex(TEX_CMSReal,0.04);
      int MCcolor0 = kGreen; 
      int MCcolor1 = kBlue; 
      int MCcolor2 = kRed; 
      int MCcolorDef = kMagenta+2; 

	//Common procedure: 
      //Inflate selected signals
      try{
		  for(std::vector<string>::iterator iplot = plotnames.begin(); iplot<plotnames.end();iplot++){
			  for(std::vector<string>::iterator imc = SigtoInclude.begin();imc<SigtoInclude.end();imc++){
			  htable.get_throwable(*imc,5)->get_throwable(*iplot,6)->Scale(SignalInflationFactor); 
			  }
		  }
      }//end try;
      catch(std::pair <std::string,int> errorpair){
		  cerr<<"Stringmap Error! While making StackPlots, Invalid string key "<<errorpair.first<< " error code "<<errorpair.second<<endl;
		  std::terminate();
      }


	if(makeStackPlots_lin){
	    try{
		for(std::vector<string>::iterator iplot = plotnames.begin(); iplot<plotnames.end();iplot++){
		    TH1F* nametemplate = htable.get_throwable( vClasses[0]->name,1)->get_throwable(*iplot,2);
		    TH1F* background = (TH1F*) nametemplate->Clone((*iplot + "_bkg").c_str());
		    background->Reset(); 
		    //string Xaxislabel =  nametemplate->GetXaxis()->GetTitle();
		    //string Yaxislabel =  nametemplate->GetYaxis()->GetTitle();
		    //string title = nametemplate->GetTitle();
		    //string canvtitle = title + ";" + Xaxislabel + ";" + Yaxislabel;
		    //TCanvas* canv =PrettyCanvas( newTCanvas((*iplot).c_str(),canvtitle.c_str())); //turns out the title is ugly and undesirable.
			
		    TCanvas* canv =PrettyCanvas( newTCanvas((*iplot + "_lin").c_str(),""));
		    canv->SetLeftMargin(0.12);
		    canv->cd();
		
		    THStack* sstack = new THStack((*iplot + "_stack_lin").c_str(), "");
		    //now for everything on the 
		    TLegend* leg_left = new TLegend( 0.153266, 0.624352, 0.384422, 0.876943);
		    TLegend* leg_right = new TLegend( 0.616834, 0.624352, 0.84799 , 0.876943);
		    PrettyLegend(leg_left,0.041);
		    PrettyLegend(leg_right,0.041);
		    std::vector<TH1F*> hists_for_set_range;

		    TH1F* ddbkghist = histmapbkg1D.get_throwable(*iplot,20);
		    check_for_negatives(ddbkghist);
		    TH1F* datahist = htable.get_throwable(dataClassName,7)->get_throwable(*iplot,8);

		    for(std::vector<string>::iterator imc = SigtoInclude.begin();imc<SigtoInclude.end();imc++){
			hists_for_set_range.push_back(htable.get_throwable(*imc,5)->get_throwable(*iplot,6));
		    }
                    hists_for_set_range.push_back(datahist);



		    //beautify data and put it on the legend 
		    PrettyHist(datahist);
		    PrettyMarker(datahist);
		    datahist->SetBinErrorOption(TH1::kPoisson);
		    if(showData) leg_left->AddEntry(datahist,"DATA");

		    //beautify dd bkg and put it on the legend 
		    int ddbkgcolor = kGray;
		    PrettyHist(ddbkghist, ddbkgcolor);
		    PrettyMarker(ddbkghist,ddbkgcolor,20,0.);
		    PrettyFillColor(ddbkghist, ddbkgcolor);
		    ddbkghist->SetBinErrorOption(TH1::kPoisson);
		    if(draw_ddbkg) leg_left->AddEntry(ddbkghist,"DD Bkg");

			//compute legend division
		    int nTotal = vBkgClasses.size() + SigtoInclude.size() + showData+1; //use this for splitting the legend in two
		    int nBkgLeft = nTotal/2 + nTotal%2 - SigtoInclude.size() - showData-1;//use this for splitting the legend in two
		
		    //Add all the MC plots and the ddBkg to the stack. Also add them to the 
		    int i = 1;
		    for(std::vector<DMCclass*>::iterator iclass = vBkgClasses.begin();iclass<vBkgClasses.end();iclass++){
			//cout<<"plot "<<*iplot<<" filling bkg for class "<< (*iclass)->name<<endl;
			TH1F* thishist = htable.get_throwable((*iclass)->name,3)->get_throwable(*iplot,4); // threw 4 on h_MinMlb_OSDL1_sansMlb
			//cout<<"plotting bkg for "<<(*iclass)->name<<" X: "<<thishist->GetXaxis()->GetTitle()<<" Y: "<<thishist->GetYaxis()->GetTitle()<<endl;
			PrettyFillColor( thishist, (*iclass)->int_meta["FillColor"] );
			PrettyMarker( thishist, (*iclass)->int_meta["FillColor"] ,20,0.);

			sstack->Add( thishist);
			background->Add( thishist);
			if(i++ <= nBkgLeft) leg_left->AddEntry( thishist, (*iclass)->string_meta["LegendLabel"].c_str() );
			else               leg_right->AddEntry( thishist, (*iclass)->string_meta["LegendLabel"].c_str() );
		    }//end for all the Backgrounds
		    if(draw_ddbkg) sstack->Add( ddbkghist);//hopefully this will be the top of the stack.  //this line is not the problem.
                    if(draw_ddbkg) background->Add(ddbkghist);
		    hists_for_set_range.push_back(background);

		    //void SameRange_and_leave_legend_room(std::vector<TH1F*> hists, float legendFraction=0., Double_t _min = -1.0, Double_t _max = -1.0);
		    SameRange_and_leave_legend_room(hists_for_set_range, 0.37, 0.0, -1);

		    if(((int)SigtoInclude.size())>0){ //I'm guessing this is needed to get the axis labels down.
			TH1F* starter_hist = htable.get_throwable(SigtoInclude[0],10)->get_throwable(*iplot,11);
			starter_hist->Draw("histo");
		    }//end if.
		    sstack->Draw("sameHISTO");	

		    int whichmc = 0; 
		    for(std::vector<string>::iterator imc = SigtoInclude.begin();imc<SigtoInclude.end();imc++){
				TH1F* thishist = htable.get_throwable(*imc,5)->get_throwable(*iplot,6); //alternative failure point xxx
				int linecolor;
				switch (whichmc){ //this is inelegant. use meta info.
					case 0: linecolor = MCcolor0 /*kGreen*/; break;
					case 1: linecolor = MCcolor1 /*kBlue*/; break;
					case 2: linecolor = MCcolor2 /*kRed*/; break;
					default:linecolor = MCcolorDef /*kMagenta+2*/; break;
				}
				PrettyHist(thishist, linecolor); //PrettyHist(TH1D* h, int color = 1, int width = 3, int linestyle = 0);
				PrettyMarker(thishist,linecolor,20,0.);
				//thishist->Sumw2();
				thishist->Draw("samehisto");
				int thisTpMass = mClassesAll->get_throwable(*imc,7)->blocks[0]->int_meta["TprimeMass"];//xxx update class with metainfo	
				leg_left->AddEntry(thishist, ("T'#bar{T}' ("+to_string(thisTpMass) + " GeV) x " + to_string((int) SignalInflationFactor)).c_str() );//xxx could use update with metainfo
				//leg_left->AddEntry(thishist,mClassesAll->get_throwable(*imc,7)->string_meta["LegendLabel"].c_str()); // ("T'#bar{T}' ("+to_string(thisTpMass) + " GeV) x " + to_string((int) SignalInflationFactor)).c_str() );//xxx could use update with metainfo
				whichmc++;
		    }
			cout<<"drawing hist "<<*iplot<<endl; //problem is after here. 
		    if(showData) datahist->Draw("Esame"); 
			cout<<"fin draw data"<<endl;

		    leg_left->Draw("same");
		    leg_right->Draw("same");

		
		    TLatex *plotlabel = new TLatex(0.07,0.015,(*iplot).c_str());
		    PrettyLatex(plotlabel,0.03);
		    plotlabel->Draw("same");

		    gPad->RedrawAxis();

		    if(showData && preliminary) TEX_CMSPrelim->Draw("same");
		    else if(showData)  TEX_CMSReal->Draw("same");
		    else TEX_CMSSim->Draw("same"); //this will change once you have a data driven Background. 
		    TEX_CMSlumi->Draw("same");

		    //problem is before here. 
		    if(saveImages) SaveCanvas(canv,*iplot + "_lin", &plotdirs,savewhat);
		}//end for every plot. 
	    }//end try;
	    catch(std::pair <std::string,int> errorpair){
		cerr<<"Stringmap Error! While making StackPlots, Invalid string key "<<errorpair.first<< " error code "<<errorpair.second<<endl;
		std::terminate();
	    }
	} //end StackPlots


	if(makeStackPlots_lin_ratio){
	    try{
		for(std::vector<string>::iterator iplot = plotnames.begin(); iplot<plotnames.end();iplot++){
		    TH1F* nametemplate = htable.get_throwable( vClasses[0]->name,1)->get_throwable(*iplot,2);
		    TH1F* background = (TH1F*) nametemplate->Clone((*iplot + "_bkg").c_str());
		    background->Reset(); 
		    TH1F* MCbackground = (TH1F*) nametemplate->Clone((*iplot + "_mcbkg").c_str());
		    MCbackground->Reset(); 
		    //string Xaxislabel =  nametemplate->GetXaxis()->GetTitle();
		    //string Yaxislabel =  nametemplate->GetYaxis()->GetTitle();
		    //string title = nametemplate->GetTitle();
		    //string canvtitle = title + ";" + Xaxislabel + ";" + Yaxislabel;
		    //TCanvas* canv =PrettyCanvas( newTCanvas((*iplot).c_str(),canvtitle.c_str())); //turns out the title is ugly and undesirable.
			
		    TCanvas* canv =PrettyCanvas( newTCanvas((*iplot + "_linR").c_str(),""));
		    TPad* pad_main_for_ratio = new TPad("pad_main_for_ratio","",0.,0.30,1.,0.94);
		    TPad* pad_ratio = new TPad("pad_ratio","", 0.,0.061,1.,0.30);
		    //TPad* pad_ratio = new TPad("pad_ratio","", 0.,0.145,1.,0.30);
		    pad_main_for_ratio->SetBottomMargin(0);
		    pad_ratio->SetTopMargin(0);
		    pad_ratio->SetBottomMargin(0.43);

		    pad_main_for_ratio->cd();
		
		    THStack* sstack = new THStack((*iplot + "_stack_linR").c_str(), "");
		    //now for everything on the 
		    TLegend* leg_left = new TLegend( 0.21608, 0.624352, 0.447236, 0.91385);
		    TLegend* leg_right = new TLegend( 0.616834, 0.624352, 0.84799 , 0.91385);
		    PrettyLegend(leg_left,0.041);
		    PrettyLegend(leg_right,0.041);
		    std::vector<TH1F*> hists_for_set_range;

		    TH1F* ddbkghist = histmapbkg1D.get_throwable(*iplot,20);
		    check_for_negatives(ddbkghist);
		    TH1F* datahist = htable.get_throwable(dataClassName,7)->get_throwable(*iplot,8);

		    for(std::vector<string>::iterator imc = SigtoInclude.begin();imc<SigtoInclude.end();imc++){
			hists_for_set_range.push_back(htable.get_throwable(*imc,5)->get_throwable(*iplot,6));
		    }
		    hists_for_set_range.push_back(datahist);

		    //beautify data and put it on the legend 
		    PrettyHist(datahist);
		    PrettyMarker(datahist);
		    datahist->SetBinErrorOption(TH1::kPoisson);
		    if(showData) leg_left->AddEntry(datahist,"DATA");

		    //beautify dd bkg and put it on the legend 
		    int ddbkgcolor = kGray;
		    PrettyHist(ddbkghist, ddbkgcolor);
		    PrettyMarker(ddbkghist,ddbkgcolor,20,0.);
		    PrettyFillColor(ddbkghist, ddbkgcolor);
		    ddbkghist->SetBinErrorOption(TH1::kPoisson);
		    if(draw_ddbkg) leg_left->AddEntry(ddbkghist,"DD Bkg");

			//compute legend division
		    int nTotal = vBkgClasses.size() + SigtoInclude.size() + showData+1; //use this for splitting the legend in two
		    int nBkgLeft = nTotal/2 + nTotal%2 - SigtoInclude.size() - showData-1;//use this for splitting the legend in two
		
		    //Add all the MC plots and the ddBkg to the stack. Also add them to the 
		    int i = 1;
		    for(std::vector<DMCclass*>::iterator iclass = vBkgClasses.begin();iclass<vBkgClasses.end();iclass++){
			//cout<<"plot "<<*iplot<<" filling bkg for class "<< (*iclass)->name<<endl;
			TH1F* thishist = htable.get_throwable((*iclass)->name,3)->get_throwable(*iplot,4); // threw 4 on h_MinMlb_OSDL1_sansMlb
			//cout<<"plotting bkg for "<<(*iclass)->name<<" X: "<<thishist->GetXaxis()->GetTitle()<<" Y: "<<thishist->GetYaxis()->GetTitle()<<endl;
			PrettyFillColor( thishist, (*iclass)->int_meta["FillColor"] );
			PrettyMarker( thishist, (*iclass)->int_meta["FillColor"] ,20,0.);

			sstack->Add( thishist);
			background->Add( thishist); 
			MCbackground->Add( thishist); 
			if(i++ <= nBkgLeft) leg_left->AddEntry( thishist, (*iclass)->string_meta["LegendLabel"].c_str() );
			else               leg_right->AddEntry( thishist, (*iclass)->string_meta["LegendLabel"].c_str() );
		    }//end for all the Backgrounds
		    if(draw_ddbkg) sstack->Add( ddbkghist);//hopefully this will be the top of the stack. 
		    if(draw_ddbkg) background->Add(ddbkghist);
		    hists_for_set_range.push_back(background);

		    //SameRange_and_leave_legend_room(hists_for_set_range, 0.37,false,0.05); //fix scale: 
		    SameRange_and_leave_legend_room(hists_for_set_range, 0.37, 0.0, -1);//********************************

		    if(((int)SigtoInclude.size())>0){ //I'm guessing this is needed to get the axis labels down.
			TH1F* starter_hist = htable.get_throwable(SigtoInclude[0],10)->get_throwable(*iplot,11);
			starter_hist->Draw("histo");
		    }//end if.
		    sstack->Draw("sameHISTO");	

		    int whichmc = 0; 
		    for(std::vector<string>::iterator imc = SigtoInclude.begin();imc<SigtoInclude.end();imc++){
			TH1F* thishist = htable.get_throwable(*imc,5)->get_throwable(*iplot,6); //alternative failure point xxx
			int linecolor;
			switch (whichmc){ //this is inelegant. use meta info.
			    case 0: linecolor = MCcolor0 /*kGreen*/; break;
			    case 1: linecolor = MCcolor1 /*kBlue*/; break;
			    case 2: linecolor = MCcolor2 /*kRed*/; break;
			    default:linecolor = MCcolorDef /*kMagenta+2*/; break;
			}
			PrettyHist(thishist, linecolor); //PrettyHist(TH1D* h, int color = 1, int width = 3, int linestyle = 0);
			PrettyMarker(thishist,linecolor,20,0.);
			//thishist->Sumw2();
			thishist->Draw("samehisto");
			int thisTpMass = mClassesAll->get_throwable(*imc,7)->blocks[0]->int_meta["TprimeMass"];//xxx update class with metainfo	
			leg_left->AddEntry(thishist, ("T'#bar{T}' ("+to_string(thisTpMass) + " GeV) x " + to_string((int) SignalInflationFactor)).c_str() );//xxx could use update with metainfo
			//leg_left->AddEntry(thishist,mClassesAll->get_throwable(*imc,7)->string_meta["LegendLabel"].c_str()); // ("T'#bar{T}' ("+to_string(thisTpMass) + " GeV) x " + to_string((int) SignalInflationFactor)).c_str() );//xxx could use update with metainfo
			whichmc++;
		    }
			cout<<"drawing hist "<<*iplot<<endl; //problem is after here. 
		    if(showData) datahist->Draw("Esame"); 

		    leg_left->Draw("same");
		    leg_right->Draw("same");

		    gPad->RedrawAxis();

			///////////////// Ratio subplot ///////////////////////
		    pad_ratio->cd();

		    TH1F* ratio ;
		    if(!draw_ddbkg){
		    	ratio = DivideHists(datahist,MCbackground);	//ot be drawn as data. with Draw("Esame")
		    	ratio->GetYaxis()->SetTitle("Data/MC Bkg");
		    }
		    else{
		    	ratio = DivideHists(datahist,background);	//ot be drawn as data. with Draw("Esame")
		    	ratio->GetYaxis()->SetTitle("Data/Bkg");
		    }
		    PrettyRatioPlot(ratio);
		    PrettyMarker(ratio);
		    ratio->GetYaxis()->SetRangeUser(0.,2.);
		    ratio->Draw("Esame");
		    TH1F* uncert = make_ratio_uncertainty_hist(datahist, MCbackground);
		    //PrettyRatioPlot(uncert);
		    PrettyBlock(uncert, kGray,"//thach");//PrettyBlock2(h[3],kRed,3345,2);
		    uncert->Draw("E2same");

			//Draw the one-line.
		    TAxis* x = ratio->GetXaxis();
		    TLine *OneLine = new TLine(x->GetXmin(),1.0,x->GetXmax(),1.0);
		    OneLine->SetLineColor(kBlack);
		    OneLine->SetLineWidth(2);
		    OneLine->SetLineStyle(7);//dashed.
		    OneLine->Draw("same");

		    ratio->Draw("Esame");
			
		    gPad->RedrawAxis();

			////////////////////////////////////////
			
			//label bins for "yield" plots - rizki - start
			const char *yieldbins[4] = {"eee","eem","emm","mmm"};
			if ((*iplot).find("h_yield")==0){
				for (int i=1;i<=4;i++){
					ratio->GetXaxis()->SetBinLabel(i,yieldbins[i-1]);
					ratio->GetXaxis()->SetLabelSize(0.35);
				}
			}
			//label bins for "yield plots - rizki - end
			
		    canv->cd();
		    pad_main_for_ratio->Draw();
		    pad_ratio->Draw("same");

		    TLatex *plotlabel = new TLatex(0.07,0.015,(*iplot).c_str());
		    PrettyLatex(plotlabel,0.03);
		    plotlabel->Draw("same");

		    if(showData && preliminary) TEX_CMSPrelim->Draw("same");
		    else if(showData)  TEX_CMSReal->Draw("same");
		    else TEX_CMSSim->Draw("same"); //this will change once you have a data driven background. 
		    TEX_CMSlumi->Draw("same");

		    //SaveCanvas(canv,plotsdir + *iplot,savewhat);
		    if(saveImages) SaveCanvas(canv,*iplot + "_linRat", &plotdirs,savewhat);
		}//end for every plot. 
	    }//end try;
	    catch(std::pair <std::string,int> errorpair){
		cerr<<"Stringmap Error! While making StackPlots, Invalid string key "<<errorpair.first<< " error code "<<errorpair.second<<endl;
		std::terminate();
	    }
	} //end StackPlots


	if(makeStackPlots_log){
	    try{
		for(std::vector<string>::iterator iplot = plotnames.begin(); iplot<plotnames.end();iplot++){
		    TH1F* nametemplate = htable.get_throwable( vClasses[0]->name,1)->get_throwable(*iplot,2);
		    TH1F* background = (TH1F*) nametemplate->Clone((*iplot + "_bkg").c_str());
		    background->Reset(); 
		    //string Xaxislabel =  nametemplate->GetXaxis()->GetTitle();
		    //string Yaxislabel =  nametemplate->GetYaxis()->GetTitle();
		    //string title = nametemplate->GetTitle();
		    //string canvtitle = title + ";" + Xaxislabel + ";" + Yaxislabel;
		    //TCanvas* canv =PrettyCanvas( newTCanvas((*iplot).c_str(),canvtitle.c_str())); //turns out the title is ugly and undesirable.
			
		    TCanvas* canv =PrettyCanvas( newTCanvas((*iplot + "_log").c_str(),""));
		    canv->SetLeftMargin(0.12);
		    canv->cd();
		    canv->SetLogy();
		    THStack* sstack = new THStack((*iplot + "_stack_log").c_str(), "");
		    //now for everything on the 
		    TLegend* leg_left = new TLegend( 0.153266, 0.624352, 0.384422, 0.876943);
		    TLegend* leg_right = new TLegend( 0.616834, 0.624352, 0.84799 , 0.876943);
		    PrettyLegend(leg_left,0.041);
		    PrettyLegend(leg_right,0.041);
		    std::vector<TH1F*> hists_for_set_range;

		    TH1F* ddbkghist = histmapbkg1D.get_throwable(*iplot,20);
		    check_for_negatives(ddbkghist);
		    TH1F* datahist = htable.get_throwable(dataClassName,7)->get_throwable(*iplot,8);

		    for(std::vector<string>::iterator imc = SigtoInclude.begin();imc<SigtoInclude.end();imc++){
			//htable.get_throwable(*imc,5)->get_throwable(*iplot,6)->Scale(SignalInflationFactor); 

			//fill a vector with everything to go on this plot. 
			hists_for_set_range.push_back(htable.get_throwable(*imc,5)->get_throwable(*iplot,6));
		    }
		    hists_for_set_range.push_back(datahist);

		    //beautify data and put it on the legend 
		    PrettyHist(datahist);
		    PrettyMarker(datahist);
		    datahist->SetBinErrorOption(TH1::kPoisson);
		    if(showData) leg_left->AddEntry(datahist,"DATA");

		    //beautify dd bkg and put it on the legend 
		    int ddbkgcolor = kGray;
		    PrettyHist(ddbkghist, ddbkgcolor);
		    PrettyMarker(ddbkghist,ddbkgcolor,20,0.);
		    PrettyFillColor(ddbkghist, ddbkgcolor);
		    ddbkghist->SetBinErrorOption(TH1::kPoisson);
		    leg_left->AddEntry(ddbkghist,"DD Bkg");

			//compute legend division
		    int nTotal = vBkgClasses.size() + SigtoInclude.size() + showData+1; //use this for splitting the legend in two
		    int nBkgLeft = nTotal/2 + nTotal%2 - SigtoInclude.size() - showData-1;//use this for splitting the legend in two
		
		    //Add all the MC plots and the ddBkg to the stack. Also add them to the 
		    int i = 1;
		    for(std::vector<DMCclass*>::iterator iclass = vBkgClasses.begin();iclass<vBkgClasses.end();iclass++){
			//cout<<"plot "<<*iplot<<" filling bkg for class "<< (*iclass)->name<<endl;
			TH1F* thishist = htable.get_throwable((*iclass)->name,3)->get_throwable(*iplot,4); // threw 4 on h_MinMlb_OSDL1_sansMlb
			//cout<<"plotting bkg for "<<(*iclass)->name<<" X: "<<thishist->GetXaxis()->GetTitle()<<" Y: "<<thishist->GetYaxis()->GetTitle()<<endl;
			PrettyFillColor( thishist, (*iclass)->int_meta["FillColor"] );
			PrettyMarker( thishist, (*iclass)->int_meta["FillColor"] ,20,0.);

			sstack->Add( thishist);
			background->Add( thishist); 

			if(i++ <= nBkgLeft) leg_left->AddEntry( thishist, (*iclass)->string_meta["LegendLabel"].c_str() );
			else               leg_right->AddEntry( thishist, (*iclass)->string_meta["LegendLabel"].c_str() );
		    }//end for all the Backgrounds
		    if(draw_ddbkg) sstack->Add( ddbkghist);//hopefully this will be the top of the stack. 
		    if(draw_ddbkg) background->Add(ddbkghist);
		    hists_for_set_range.push_back(background);


		    //void SameRange_and_leave_legend_room_log(std::vector<TH1F*> hists, float legendFraction, bool tinymin_override, Double_t _min, Double_t _max){
		    SameRange_and_leave_legend_room_log(hists_for_set_range, 0.37,false,0.05); //fix scale: 


		    if(((int)SigtoInclude.size())>0){ //I'm guessing this is needed to get the axis labels down.
			TH1F* starter_hist = htable.get_throwable(SigtoInclude[0],10)->get_throwable(*iplot,11);
			starter_hist->Draw("histo");
		    }//end if.
		    sstack->Draw("sameHISTO");	

		    int whichmc = 0; 
		    for(std::vector<string>::iterator imc = SigtoInclude.begin();imc<SigtoInclude.end();imc++){
			TH1F* thishist = htable.get_throwable(*imc,5)->get_throwable(*iplot,6); //alternative failure point xxx
			int linecolor;
			switch (whichmc){ //this is inelegant. use meta info.
			    case 0: linecolor = MCcolor0 /*kGreen*/; break;
			    case 1: linecolor = MCcolor1 /*kBlue*/; break;
			    case 2: linecolor = MCcolor2 /*kRed*/; break;
			    default:linecolor = MCcolorDef /*kMagenta+2*/; break;
			}
			PrettyHist(thishist, linecolor); //PrettyHist(TH1D* h, int color = 1, int width = 3, int linestyle = 0);
			PrettyMarker(thishist,linecolor,20,0.);
			//thishist->Sumw2();
			thishist->Draw("samehisto");
			int thisTpMass = mClassesAll->get_throwable(*imc,7)->blocks[0]->int_meta["TprimeMass"];//xxx update class with metainfo	
			leg_left->AddEntry(thishist, ("T'#bar{T}' ("+to_string(thisTpMass) + " GeV) x " + to_string((int) SignalInflationFactor)).c_str() );//xxx could use update with metainfo
			//leg_left->AddEntry(thishist,mClassesAll->get_throwable(*imc,7)->string_meta["LegendLabel"].c_str()); // ("T'#bar{T}' ("+to_string(thisTpMass) + " GeV) x " + to_string((int) SignalInflationFactor)).c_str() );//xxx could use update with metainfo
			whichmc++;
		    }
			cout<<"drawing hist "<<*iplot<<endl; //problem is after here. 
		    if(showData) datahist->Draw("Esame"); 

		    leg_left->Draw("same");
		    leg_right->Draw("same");

		
		    TLatex *plotlabel = new TLatex(0.07,0.015,(*iplot).c_str());
		    PrettyLatex(plotlabel,0.03);
		    plotlabel->Draw("same");

		    gPad->RedrawAxis();

		    if(showData && preliminary) TEX_CMSPrelim->Draw("same");
		    else if(showData)  TEX_CMSReal->Draw("same");
		    else TEX_CMSSim->Draw("same"); //this will change once you have a data driven background. 
		    TEX_CMSlumi->Draw("same");

		    //SaveCanvas(canv,plotsdir + *iplot,savewhat);
		    if(saveImages) SaveCanvas(canv,*iplot + "_log", &plotdirs,savewhat);
		}//end for every plot. 
	    }//end try;
	    catch(std::pair <std::string,int> errorpair){
		cerr<<"Stringmap Error! While making StackPlots, Invalid string key "<<errorpair.first<< " error code "<<errorpair.second<<endl;
		std::terminate();
	    }
	} //end StackPlots


	if(makeStackPlots_log_ratio){
	    try{
		for(std::vector<string>::iterator iplot = plotnames.begin(); iplot<plotnames.end();iplot++){
		    TH1F* nametemplate = htable.get_throwable( vClasses[0]->name,1)->get_throwable(*iplot,2);
		    TH1F* background = (TH1F*) nametemplate->Clone((*iplot + "_bkg").c_str());
		    background->Reset();
		    TH1F* MCbackground = (TH1F*) nametemplate->Clone((*iplot + "_MCbkg").c_str());
		    MCbackground->Reset();
		    //string Xaxislabel =  nametemplate->GetXaxis()->GetTitle();
		    //string Yaxislabel =  nametemplate->GetYaxis()->GetTitle();
		    //string title = nametemplate->GetTitle();
		    //string canvtitle = title + ";" + Xaxislabel + ";" + Yaxislabel;
		    //TCanvas* canv =PrettyCanvas( newTCanvas((*iplot).c_str(),canvtitle.c_str())); //turns out the title is ugly and undesirable.
			
		    TCanvas* canv =PrettyCanvas( newTCanvas((*iplot + "_logR").c_str(),""));
		    TPad* pad_main_for_ratio = new TPad("pad_main_for_ratio","",0.,0.30,1.,0.94);
		    TPad* pad_ratio = new TPad("pad_ratio","", 0.,0.061,1.,0.30);
		    //TPad* pad_ratio = new TPad("pad_ratio","", 0.,0.145,1.,0.30);
		    pad_main_for_ratio->SetBottomMargin(0);
		    pad_ratio->SetTopMargin(0);
		    pad_ratio->SetBottomMargin(0.43);

		    pad_main_for_ratio->cd();
		    pad_main_for_ratio->SetLogy();
		    THStack* sstack = new THStack((*iplot + "_stack_logR").c_str(), "");
		    //now for everything on the 
		    TLegend* leg_left = new TLegend( 0.21608, 0.624352, 0.447236, 0.91385);
		    TLegend* leg_right = new TLegend( 0.616834, 0.624352, 0.84799 , 0.91385);
		    PrettyLegend(leg_left,0.041);
		    PrettyLegend(leg_right,0.041);
		    std::vector<TH1F*> hists_for_set_range;

		    TH1F* ddbkghist = histmapbkg1D.get_throwable(*iplot,20);
		    check_for_negatives(ddbkghist);
		    TH1F* datahist = htable.get_throwable(dataClassName,7)->get_throwable(*iplot,8);

		    for(std::vector<string>::iterator imc = SigtoInclude.begin();imc<SigtoInclude.end();imc++){
			hists_for_set_range.push_back(htable.get_throwable(*imc,5)->get_throwable(*iplot,6));
		    }
		    hists_for_set_range.push_back(datahist);



		    //beautify data and put it on the legend 
		    PrettyHist(datahist);
		    PrettyMarker(datahist);
		    datahist->SetBinErrorOption(TH1::kPoisson);
		    if(showData) leg_left->AddEntry(datahist,"DATA");

		    //beautify dd bkg and put it on the legend 
		    int ddbkgcolor = kGray;
		    PrettyHist(ddbkghist, ddbkgcolor);
		    PrettyMarker(ddbkghist,ddbkgcolor,20,0.);
		    PrettyFillColor(ddbkghist, ddbkgcolor);
		    ddbkghist->SetBinErrorOption(TH1::kPoisson);
		    if(draw_ddbkg) leg_left->AddEntry(ddbkghist,"DD Bkg");

			//compute legend division
		    int nTotal = vBkgClasses.size() + SigtoInclude.size() + showData+1; //use this for splitting the legend in two
		    int nBkgLeft = nTotal/2 + nTotal%2 - SigtoInclude.size() - showData-1;//use this for splitting the legend in two
		
		    //Add all the MC plots and the ddBkg to the stack. Also add them to the 
		    int i = 1;
		    for(std::vector<DMCclass*>::iterator iclass = vBkgClasses.begin();iclass<vBkgClasses.end();iclass++){
			//cout<<"plot "<<*iplot<<" filling bkg for class "<< (*iclass)->name<<endl;
			TH1F* thishist = htable.get_throwable((*iclass)->name,3)->get_throwable(*iplot,4); // threw 4 on h_MinMlb_OSDL1_sansMlb
			//cout<<"plotting bkg for "<<(*iclass)->name<<" X: "<<thishist->GetXaxis()->GetTitle()<<" Y: "<<thishist->GetYaxis()->GetTitle()<<endl;
			PrettyFillColor( thishist, (*iclass)->int_meta["FillColor"] );
			PrettyMarker( thishist, (*iclass)->int_meta["FillColor"] ,20,0.);

			sstack->Add( thishist);
			background->Add( thishist); 
			MCbackground->Add( thishist); 
			//HERE add the uncertainty to the bkg.

			if(i++ <= nBkgLeft) leg_left->AddEntry( thishist, (*iclass)->string_meta["LegendLabel"].c_str() );
			else               leg_right->AddEntry( thishist, (*iclass)->string_meta["LegendLabel"].c_str() );
		    }//end for all the backgrounds
		    if(draw_ddbkg) sstack->Add( ddbkghist);//hopefully this will be the top of the stack. 
		    if(draw_ddbkg) background->Add(ddbkghist);
		    hists_for_set_range.push_back(background);

		    SameRange_and_leave_legend_room_log(hists_for_set_range, 0.37,false,0.05); //fix scale: 

		    if(((int)SigtoInclude.size())>0){ //I'm guessing this is needed to get the axis labels down.
			TH1F* starter_hist = htable.get_throwable(SigtoInclude[0],10)->get_throwable(*iplot,11);
			starter_hist->Draw("histo");
		    }//end if.
		    sstack->Draw("sameHISTO");	

		    int whichmc = 0; 
		    for(std::vector<string>::iterator imc = SigtoInclude.begin();imc<SigtoInclude.end();imc++){
			TH1F* thishist = htable.get_throwable(*imc,5)->get_throwable(*iplot,6); //alternative failure point xxx
			int linecolor;
			switch (whichmc){ //this is inelegant. use meta info.
			    case 0: linecolor = MCcolor0 /*kGreen*/; break;
			    case 1: linecolor = MCcolor1 /*kBlue*/; break;
			    case 2: linecolor = MCcolor2 /*kRed*/; break;
			    default:linecolor = MCcolorDef /*kMagenta+2*/; break;
			}
			PrettyHist(thishist, linecolor); //PrettyHist(TH1D* h, int color = 1, int width = 3, int linestyle = 0);
			PrettyMarker(thishist,linecolor,20,0.);
			//thishist->Sumw2();
			thishist->Draw("samehisto");
			int thisTpMass = mClassesAll->get_throwable(*imc,7)->blocks[0]->int_meta["TprimeMass"];//xxx update class with metainfo	
			leg_left->AddEntry(thishist, ("T'#bar{T}' ("+to_string(thisTpMass) + " GeV) x " + to_string((int) SignalInflationFactor)).c_str() );//xxx could use update with metainfo
			//leg_left->AddEntry(thishist,mClassesAll->get_throwable(*imc,7)->string_meta["LegendLabel"].c_str()); // ("T'#bar{T}' ("+to_string(thisTpMass) + " GeV) x " + to_string((int) SignalInflationFactor)).c_str() );//xxx could use update with metainfo
			whichmc++;
		    }
			cout<<"drawing hist "<<*iplot<<endl; //problem is after here. 
		    if(showData) datahist->Draw("Esame"); 

		    leg_left->Draw("same");
		    leg_right->Draw("same");

		    gPad->RedrawAxis();

			///////////////// Ratio subplot ///////////////////////
		    pad_ratio->cd();

		    TH1F* ratio;
		    if(!draw_ddbkg){
		    	ratio = DivideHists(datahist,MCbackground);	//ot be drawn as data. with Draw("Esame")
		    	ratio->GetYaxis()->SetTitle("Data/MC Bkg");
		    }
		    else{
		    	ratio = DivideHists(datahist,background);	//ot be drawn as data. with Draw("Esame")
		    	ratio->GetYaxis()->SetTitle("Data/Bkg");
		    }
		    PrettyRatioPlot(ratio);
		    PrettyMarker(ratio);
		    ratio->GetYaxis()->SetRangeUser(0.,2.);
		    ratio->Draw("Esame");
		    TH1F* uncert = make_ratio_uncertainty_hist(datahist, MCbackground);
		    //PrettyRatioPlot(uncert);
		    PrettyBlock(uncert, kGray,"//thach");//PrettyBlock2(h[3],kRed,3345,2);
		    uncert->Draw("E2same");

			//Draw the one-line.
		    TAxis* x = ratio->GetXaxis();
		    TLine *OneLine = new TLine(x->GetXmin(),1.0,x->GetXmax(),1.0);
		    OneLine->SetLineColor(kBlack);
		    OneLine->SetLineWidth(2);
		    OneLine->SetLineStyle(7);//dashed.
		    OneLine->Draw("same");

		    ratio->Draw("Esame");
			
		    gPad->RedrawAxis();

			////////////////////////////////////////
			
			//label bins for "yield" plots - rizki - start
			const char *yieldbins[4] = {"eee","eem","emm","mmm"};
			if ((*iplot).find("h_yield")==0){
				for (int i=1;i<=4;i++){
					ratio->GetXaxis()->SetBinLabel(i,yieldbins[i-1]);
					ratio->GetXaxis()->SetLabelSize(0.35);
				}	
			}
			//label bins for "yield plots - rizki - end
			
		    canv->cd();
		    pad_main_for_ratio->Draw();
		    pad_ratio->Draw("same");

		    TLatex *plotlabel = new TLatex(0.07,0.015,(*iplot).c_str());
		    PrettyLatex(plotlabel,0.03);
		    plotlabel->Draw("same");

		    if(showData && preliminary) TEX_CMSPrelim->Draw("same");
		    else if(showData)  TEX_CMSReal->Draw("same");
		    else TEX_CMSSim->Draw("same"); //this will change once you have a data driven background. 
		    TEX_CMSlumi->Draw("same");

		    //SaveCanvas(canv,plotsdir + *iplot,savewhat);
		    if(saveImages) SaveCanvas(canv,*iplot + "_logRat", &plotdirs,savewhat);
		}//end for every plot. 
	    }//end try;
	    catch(std::pair <std::string,int> errorpair){
		cerr<<"Stringmap Error! While making StackPlots, Invalid string key "<<errorpair.first<< " error code "<<errorpair.second<<endl;
		std::terminate();
	    }
	} //end StackPlots


	// added by rizki - make S/sqrt{S+B} plot intead of ratio - start
	if(makeStackPlots_log_SBsignif){
	    try{
		for(std::vector<string>::iterator iplot = plotnames.begin(); iplot<plotnames.end();iplot++){
		    TH1F* nametemplate = htable.get_throwable( vClasses[0]->name,1)->get_throwable(*iplot,2);
		    TH1F* background = (TH1F*) nametemplate->Clone((*iplot + "_bkg").c_str());
		    background->Reset();
		    TH1F* MCbackground = (TH1F*) nametemplate->Clone((*iplot + "_MCbkg").c_str());
		    MCbackground->Reset();
		    //string Xaxislabel =  nametemplate->GetXaxis()->GetTitle();
		    //string Yaxislabel =  nametemplate->GetYaxis()->GetTitle();
		    //string title = nametemplate->GetTitle();
		    //string canvtitle = title + ";" + Xaxislabel + ";" + Yaxislabel;
		    //TCanvas* canv =PrettyCanvas( newTCanvas((*iplot).c_str(),canvtitle.c_str())); //turns out the title is ugly and undesirable.
			
		    TCanvas* canv =PrettyCanvas( newTCanvas((*iplot + "_logR").c_str(),""));
		    TPad* pad_main_for_ratio = new TPad("pad_main_for_ratio","",0.,0.30,1.,0.94);
		    TPad* pad_ratio = new TPad("pad_ratio","", 0.,0.061,1.,0.30);
		    //TPad* pad_ratio = new TPad("pad_ratio","", 0.,0.145,1.,0.30);
		    pad_main_for_ratio->SetBottomMargin(0);
		    pad_ratio->SetTopMargin(0);
		    pad_ratio->SetBottomMargin(0.43);

		    pad_main_for_ratio->cd();
		    pad_main_for_ratio->SetLogy();
		    THStack* sstack = new THStack((*iplot + "_stack_logR").c_str(), "");
		    //now for everything on the 
		    TLegend* leg_left = new TLegend( 0.21608, 0.624352, 0.447236, 0.91385);
		    TLegend* leg_right = new TLegend( 0.616834, 0.624352, 0.84799 , 0.91385);
		    PrettyLegend(leg_left,0.041);
		    PrettyLegend(leg_right,0.041);
		    std::vector<TH1F*> hists_for_set_range;

		    TH1F* ddbkghist = histmapbkg1D.get_throwable(*iplot,20);
		    TH1F* datahist = htable.get_throwable(dataClassName,7)->get_throwable(*iplot,8);

		    for(std::vector<string>::iterator imc = SigtoInclude.begin();imc<SigtoInclude.end();imc++){
				hists_for_set_range.push_back(htable.get_throwable(*imc,5)->get_throwable(*iplot,6));
		    }
		    hists_for_set_range.push_back(datahist);



		    //beautify data and put it on the legend 
		    PrettyHist(datahist);
		    PrettyMarker(datahist);
		    datahist->SetBinErrorOption(TH1::kPoisson);
		    if(showData) leg_left->AddEntry(datahist,"DATA");

		    //beautify dd bkg and put it on the legend 
		    int ddbkgcolor = kGray;
		    PrettyHist(ddbkghist, ddbkgcolor);
		    PrettyMarker(ddbkghist,ddbkgcolor,20,0.);
		    PrettyFillColor(ddbkghist, ddbkgcolor);
		    ddbkghist->SetBinErrorOption(TH1::kPoisson);
		    if(draw_ddbkg) leg_left->AddEntry(ddbkghist,"DD Bkg");

			//compute legend division
		    int nTotal = vBkgClasses.size() + SigtoInclude.size() + showData+1; //use this for splitting the legend in two
		    int nBkgLeft = nTotal/2 + nTotal%2 - SigtoInclude.size() - showData-1;//use this for splitting the legend in two
		
		    //Add all the MC plots and the ddBkg to the stack. Also add them to the 
		    int i = 1;
		    for(std::vector<DMCclass*>::iterator iclass = vBkgClasses.begin();iclass<vBkgClasses.end();iclass++){
			//cout<<"plot "<<*iplot<<" filling bkg for class "<< (*iclass)->name<<endl;
			TH1F* thishist = htable.get_throwable((*iclass)->name,3)->get_throwable(*iplot,4); // threw 4 on h_MinMlb_OSDL1_sansMlb
			//cout<<"plotting bkg for "<<(*iclass)->name<<" X: "<<thishist->GetXaxis()->GetTitle()<<" Y: "<<thishist->GetYaxis()->GetTitle()<<endl;
			PrettyFillColor( thishist, (*iclass)->int_meta["FillColor"] );
			PrettyMarker( thishist, (*iclass)->int_meta["FillColor"] ,20,0.);

			sstack->Add( thishist);
			background->Add( thishist); 
			MCbackground->Add( thishist); 
			//HERE add the uncertainty to the bkg.

			if(i++ <= nBkgLeft) leg_left->AddEntry( thishist, (*iclass)->string_meta["LegendLabel"].c_str() );
			else               leg_right->AddEntry( thishist, (*iclass)->string_meta["LegendLabel"].c_str() );
		    }//end for all the backgrounds
		    if(draw_ddbkg) sstack->Add( ddbkghist);//hopefully this will be the top of the stack. 
		    if(draw_ddbkg) background->Add(ddbkghist);
		    hists_for_set_range.push_back(background);

		    SameRange_and_leave_legend_room_log(hists_for_set_range, 0.37,false,0.05); //fix scale: 

		    if(((int)SigtoInclude.size())>0){ //I'm guessing this is needed to get the axis labels down.
			TH1F* starter_hist = htable.get_throwable(SigtoInclude[0],10)->get_throwable(*iplot,11);
			starter_hist->Draw("histo");
		    }//end if.
		    sstack->Draw("sameHISTO");	

		    int whichmc = 0; 
		    for(std::vector<string>::iterator imc = SigtoInclude.begin();imc<SigtoInclude.end();imc++){
				TH1F* thishist = htable.get_throwable(*imc,5)->get_throwable(*iplot,6); //alternative failure point xxx
				int linecolor;
				switch (whichmc){ //this is inelegant. use meta info.
					case 0: linecolor = MCcolor0 /*kGreen*/; break;
					case 1: linecolor = MCcolor1 /*kBlue*/; break;
					case 2: linecolor = MCcolor2 /*kRed*/; break;
					default:linecolor = MCcolorDef /*kMagenta+2*/; break;
				}
				PrettyHist(thishist, linecolor); //PrettyHist(TH1D* h, int color = 1, int width = 3, int linestyle = 0);
				PrettyMarker(thishist,linecolor,20,0.);
				//thishist->Sumw2();
				thishist->Draw("samehisto");
				int thisTpMass = mClassesAll->get_throwable(*imc,7)->blocks[0]->int_meta["TprimeMass"];//xxx update class with metainfo	
				leg_left->AddEntry(thishist, ("T'#bar{T}' ("+to_string(thisTpMass) + " GeV) x " + to_string((int) SignalInflationFactor)).c_str() );//xxx could use update with metainfo
				//leg_left->AddEntry(thishist,mClassesAll->get_throwable(*imc,7)->string_meta["LegendLabel"].c_str()); // ("T'#bar{T}' ("+to_string(thisTpMass) + " GeV) x " + to_string((int) SignalInflationFactor)).c_str() );//xxx could use update with metainfo
				whichmc++;
		    }
			cout<<"drawing hist "<<*iplot<<endl; //problem is after here. 
		    if(showData) datahist->Draw("Esame"); 

		    leg_left->Draw("same");
		    leg_right->Draw("same");

		    gPad->RedrawAxis();

			///////////////// S/sqrt(S+B) subplot ///////////////////////
		    pad_ratio->cd();			
			pad_ratio->SetGridy();
			TH1F* sighist = (TH1F*) htable.get_throwable(SigtoInclude[0],5)->get_throwable(*iplot,6)->Clone("sighist");
			sighist->Scale(1./SignalInflationFactor); //undo SignalInflationFactor
			TH1F* sig_plus_MCBkg_hist = (TH1F*) sighist->Clone("sig_plus_MCBkg_hist");;
			sig_plus_MCBkg_hist->Add(MCbackground);			
		    TH1F* ratio = DivideHists(sighist,sig_plus_MCBkg_hist,1);	//mode=1: num/sqrt(denom)
		    ratio->GetYaxis()->SetTitle("S/#sqrt{S+B}");
		    PrettyRatioPlot(ratio);
		    PrettyMarker(ratio);
		    ratio->GetYaxis()->SetRangeUser(0.,ratio->GetMaximum()*1.1);
		    ratio->Draw("Esame");

		    TH1F* uncert = make_ratio_uncertainty_hist(sighist, sig_plus_MCBkg_hist); // rizki comment: this might not be the correct way to get the uncert.
		    //PrettyRatioPlot(uncert);

		    PrettyBlock(uncert, kGray,"//thach");//PrettyBlock2(h[3],kRed,3345,2);

// 		    uncert->Draw("E2same");

			//Draw the one-line.

// 		    TAxis* x = ratio->GetXaxis();
// 		    TLine *OneLine = new TLine(x->GetXmin(),1.0,x->GetXmax(),1.0);
// 		    OneLine->SetLineColor(kBlack);
// 		    OneLine->SetLineWidth(2);
// 		    OneLine->SetLineStyle(7);//dashed.
// 		    OneLine->Draw("same");

// 		    ratio->Draw("Esame");
			
		    gPad->RedrawAxis();

			////////////////////////////////////////
		    canv->cd();
		    pad_main_for_ratio->Draw();
		    pad_ratio->Draw("same");

		    TLatex *plotlabel = new TLatex(0.07,0.015,(*iplot).c_str());
		    PrettyLatex(plotlabel,0.03);
		    plotlabel->Draw("same");

		    if(showData && preliminary) TEX_CMSPrelim->Draw("same");
		    else if(showData)  TEX_CMSReal->Draw("same");
		    else TEX_CMSSim->Draw("same"); //this will change once you have a data driven background. 
		    TEX_CMSlumi->Draw("same");

		    //SaveCanvas(canv,plotsdir + *iplot,savewhat);
		    if(saveImages) SaveCanvas(canv,*iplot + "_logSBsignif", &plotdirs,savewhat);
		}//end for every plot. 
	    }//end try;
	    catch(std::pair <std::string,int> errorpair){
		cerr<<"Stringmap Error! While making StackPlots, Invalid string key "<<errorpair.first<< " error code "<<errorpair.second<<endl;
		std::terminate();
	    }
	} //end StackPlots
	// added by rizki - make S/sqrt{S+B} plot intead of ratio - end
	
	//undo SignalInflationFactor - added by rizki - start
	try{
		for(std::vector<string>::iterator iplot = plotnames.begin(); iplot<plotnames.end();iplot++){
			  for(std::vector<string>::iterator imc = SigtoInclude.begin();imc<SigtoInclude.end();imc++){
			  htable.get_throwable(*imc,5)->get_throwable(*iplot,6)->Scale(1./SignalInflationFactor); 
			  }
		}
    }//end try;
    catch(std::pair <std::string,int> errorpair){
		cerr<<"Stringmap Error! While making StackPlots, Invalid string key "<<errorpair.first<< " error code "<<errorpair.second<<endl;
		std::terminate();
    }
	//undo SignalInflationFactor - added by rizki - end	
	
	//added by rizki - output for Theta - start
	if(produceThetaOut)MakeThetaRootFile_Yield("yield", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldNULL", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldNULL_eee", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldNULL_eem", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldNULL_emm", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldNULL_mmm", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);

	if(produceThetaOut)MakeThetaRootFile_Yield("yieldmain", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldmain_eee", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldmain_eem", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldmain_emm", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldmain_mmm", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);

	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST1100B1J3MtSum50", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST1000B1J3MtSum50", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST900B1J3MtSum50", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST800B1J3MtSum50", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST700B1J3MtSum50", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST600B1J3MtSum50", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST500B1J3MtSum50", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);

	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST1100J3MtSum50", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);

	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST1100_1BmJ_3J", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST1000_1BmJ_3J", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST900_1BmJ_3J", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST800_1BmJ_3J", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);

	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST1100_3J", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST1100_3J", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST1000_3J", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST900_3J", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);

	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST1100_1BmJ", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST1000_1BmJ", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST900_1BmJ", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);

	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST1100", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST1000", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST900", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST800", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);
	if(produceThetaOut)MakeThetaRootFile_Yield("yieldST700", htable,histmapbkg,htable2D,"forTheta", vSigClassesAll, vSigClassesUP, vSigClassesDOWN , SignalInflationFactor, dataClassName, vBkgClasses, vBkgClassesUP, vBkgClassesDOWN ,draw_ddbkg);


	//added by rizki - output for Theta - end

	//close all the files you opened. 
// 	cout<<"begin closing plot files"<<endl;
// 	for(std::vector<TFile*>::iterator ifile = vFiles.begin();ifile<vFiles.end();ifile++) delete (*ifile); //this should be the last line in the program.
	//for(std::vector<TFile*>::iterator ifile = vFiles.begin();ifile<vFiles.end();ifile++) (*ifile)->Close(); //this should be the last line in the program.
	cout<<"finish post.C"<<endl;
}//end post

TH1F* extrackBkg(TH2F* bkg_hist){
	//this assumes that row1 of the histogram is the main thing to return with everything higher being variations. 
	//take the stdev of the variations and add that systematic in quadurture with the statistical error. 
	bkg_hist->Sumw2();
	TH1F* out = hslice(bkg_hist,1);
	int nx = bkg_hist->GetNbinsX();
	int ny = bkg_hist->GetNbinsY();

        for(int i=0;i<=nx+1;i++){//for every horizontal bin, including underflow and overflow
			float mean = out->GetBinContent(i);
			float variance = 0;
			for(int y=2;y<=ny;y++){ //for every filled bin above the mean value slice (ny-1) bins
				variance+=pow(bkg_hist->GetBinContent(i,y)-mean,2);	
			}
			variance/=(float)(ny-2);//probably should be ny-2 for sample stdev. 
			//variance/=(ny-1);//probably should be ny-2 for sample stdev. 
			float newerror = sqrt(variance+ pow(out->GetBinError(i),2));
			out->SetBinError(i,newerror);
        }
	return out;
}//end extrackBkg


string MakeThetaRootFile_Yield_nonsignal(histtable htable, histmap2D* histmapbkg,    string dir, 
	string dataClassName, std::vector<DMCclass*> vBkgClasses, std::vector<DMCclass*> vBkgClassesUP, std::vector<DMCclass*> vBkgClassesDOWN,bool draw_ddbkg ){
	//takes in a heap of histograms and produces a root file with all those histograms. 
	//
	//This takes in Data, all backgrounds, and all their variations, and writes them to a file.
	
	string varname = "yield";
	string plotname = "h_"+varname; 

	string filename = dir+"/hist4limit_yield.root";
	cout<<"writing limit root file to "<<filename<<endl;

	TFile * f = new TFile(filename.c_str(), "RECREATE");
	f->cd();

	try{
		//fetch data. 
		TH1F* datahist = (TH1F*) htable.get_throwable(dataClassName,1)->get_throwable(plotname,2)->Clone((plotname+"__DATA").c_str());
		datahist->Write(); 

		//write all the background histograms. 
		for(std::vector<DMCclass*>::iterator iclass = vBkgClasses.begin();iclass<vBkgClasses.end();iclass++){ //for every bkg class
			TH1F* thisbkghist = (TH1F*) htable.get_throwable((*iclass)->name,1)->get_throwable(plotname,2)->Clone((plotname+"__"+(*iclass)->name).c_str());
			thisbkghist->Write();
		}
		for(std::vector<DMCclass*>::iterator iclass = vBkgClassesUP.begin();iclass<vBkgClassesUP.end();iclass++){ //for every bkg class
				//PSES = Parton Shower Eneryg Scale up
			TH1F* thisbkghist = htable.get_throwable((*iclass)->name,1)->get_throwable(plotname,2);
			TH1F* thisbkghistclone = (TH1F*) thisbkghist->Clone((plotname+"__"+(*iclass)->name+"__PSES__plus").c_str());
			thisbkghistclone->Write();
		}
		for(std::vector<DMCclass*>::iterator iclass = vBkgClassesDOWN.begin();iclass<vBkgClassesDOWN.end();iclass++){ //for every bkg class
				//PSES = Parton Shower Eneryg Scale down
			TH1F* thisbkghist = htable.get_throwable((*iclass)->name,1)->get_throwable(plotname,2);
			TH1F* thisbkghistclone = (TH1F*) thisbkghist->Clone((plotname+"__"+(*iclass)->name+"__PSES__minus").c_str());
			thisbkghistclone->Write();
		}

		//Get the ddhists
		TH2F* ddbkgs = histmapbkg->get_throwable(plotname,3); 
		//histmapbkg is indexed using the h_ name rather than the b_name
		//This is done around the line "histmapbkg->set(thisbkgplotname,temp2);"
		TH1F* ddbks[nmodes];
		ddbks[0] = (TH1F*) hslice(ddbkgs,1)->Clone((plotname+"__DDBKG").c_str());
		ddbks[1] = (TH1F*) hslice(ddbkgs,2)->Clone((plotname+"__DDBKG__passrate__plus").c_str());
		ddbks[2] = (TH1F*) hslice(ddbkgs,3)->Clone((plotname+"__DDBKG__passrate__minus").c_str());
		ddbks[3] = (TH1F*) hslice(ddbkgs,4)->Clone((plotname+"__DDBKG__failrate__plus").c_str());
		ddbks[4] = (TH1F*) hslice(ddbkgs,5)->Clone((plotname+"__DDBKG__failrate__minus").c_str());
		if(draw_ddbkg){
			for(int i=0;i<nmodes;i++) ddbks[i]->Write();
		}		
		
	}//end try
	catch(std::pair <std::string,int> errorpair){
	    switch(errorpair.second ){
		case 1: cerr<<"Stringmap Error! While making Theta nonsig root files. Invalid string key "<<errorpair.first<< " sought in htable"<<endl; break;
		case 2: cerr<<"Stringmap Error! While making Theta nonsig root files. Invalid string key "<<errorpair.first<< " sought in htable submap"<<endl; break;
		case 3: cerr<<"Stringmap Error! While making Theta nonsig root files. Invalid string key "<<errorpair.first<< " sought in histmapbkg"<<endl; break;
	    }//end switch
	    std::terminate();
	}//end catch;

	f->Close();
	return filename;
} //end MakeThetaRootFile_Yield_nonsignal

//added by rizki - start
string MakeThetaRootFile_Yield(	string varname_, histtable htable, histmap2D* histmapbkg, histtable2D htable2D, string dir, 
								std::vector<DMCclass*> vSigClassesAll, 
								std::vector<DMCclass*> vSigClassesUP, 
								std::vector<DMCclass*> vSigClassesDOWN, 
								int SignalInflationFactor,
								string dataClassName, 
								std::vector<DMCclass*> vBkgClasses, 
								std::vector<DMCclass*> vBkgClassesUP, 
								std::vector<DMCclass*> vBkgClassesDOWN,
								bool draw_ddbkg){
	//takes in a heap of histograms and produces a root file with all those histograms. 
	//This takes in Data, all backgrounds, and all their variations, and writes them to a file.
	
	string varname = varname_;
	string plotname = "h_"+varname; 

	string filename = dir+"/hist4limit_"+varname+".root";
	cout<<"writing limit root file to "<<filename<<endl;

	TFile * f = new TFile(filename.c_str(), "RECREATE");
	f->cd();

	try{
		//fetch data. 
		TH1F* datahist = (TH1F*) htable.get_throwable(dataClassName,1)->get_throwable(plotname,2)->Clone((plotname+"__DATA").c_str());
		datahist->Write(); 

		//get signal
		for(std::vector<DMCclass*>::iterator iclass = vSigClassesAll.begin();iclass<vSigClassesAll.end();iclass++){ 
			TH1F* sighistclone = (TH1F*) htable.get_throwable((*iclass)->name,1)->get_throwable(plotname,2)->Clone((plotname+"__"+(*iclass)->name).c_str());
			float cs_pb_ = (*iclass)->blocks[0]->cs_pb; //assume signal class has one block
			//cout<< "class: " << (*iclass)->name << ", nblock = "<< (*iclass)->nblocks << ", block: " << (*iclass)->blocks[0]->name << ", cs_pb = " << cs_pb_ << endl;
			sighistclone->Scale(1./(cs_pb_)); //scale to 1 pb
			sighistclone->Write();
		}
		//write all the UP signal histograms. 
		for(std::vector<DMCclass*>::iterator iclass = vSigClassesUP.begin();iclass<vSigClassesUP.end();iclass++){ 
			TH1F* sighistclone = (TH1F*) htable.get_throwable((*iclass)->name,1)->get_throwable(plotname,2)->Clone((plotname+"__"+(*iclass)->name).c_str());
			float cs_pb_ = (*iclass)->blocks[0]->cs_pb; //assume signal class has one block
			sighistclone->Scale(1./(cs_pb_)); //scale to 1 pb
			sighistclone->Write();
		}
		//write all the DOWN signal histograms. 
		for(std::vector<DMCclass*>::iterator iclass = vSigClassesDOWN.begin();iclass<vSigClassesDOWN.end();iclass++){ 
			TH1F* sighistclone = (TH1F*) htable.get_throwable((*iclass)->name,1)->get_throwable(plotname,2)->Clone((plotname+"__"+(*iclass)->name).c_str());
			float cs_pb_ = (*iclass)->blocks[0]->cs_pb; //assume signal class has one block
			sighistclone->Scale(1./(cs_pb_)); //scale to 1 pb
			sighistclone->Write();
		}
		//write all the background histograms. 
		for(std::vector<DMCclass*>::iterator iclass = vBkgClasses.begin();iclass<vBkgClasses.end();iclass++){ //for every bkg class
			TH1F* thisbkghist = htable.get_throwable((*iclass)->name,1)->get_throwable(plotname,2);
			TH1F* thisbkghistclone = (TH1F*) thisbkghist->Clone((plotname+"__"+(*iclass)->name).c_str());
			thisbkghistclone->Write();
		}
		//write all the UP background histograms. 
		for(std::vector<DMCclass*>::iterator iclass = vBkgClassesUP.begin();iclass<vBkgClassesUP.end();iclass++){ //for every bkg class
			TH1F* thisbkghist = htable.get_throwable((*iclass)->name,1)->get_throwable(plotname,2);
			TH1F* thisbkghistclone = (TH1F*) thisbkghist->Clone((plotname+"__"+(*iclass)->name).c_str());
			thisbkghistclone->Write();
		}
		//write all the DOWN background histograms. 
		for(std::vector<DMCclass*>::iterator iclass = vBkgClassesDOWN.begin();iclass<vBkgClassesDOWN.end();iclass++){ //for every bkg class
			TH1F* thisbkghist = htable.get_throwable((*iclass)->name,1)->get_throwable(plotname,2);
			TH1F* thisbkghistclone = (TH1F*) thisbkghist->Clone((plotname+"__"+(*iclass)->name).c_str());
			thisbkghistclone->Write();
		}

		//Get the ddhists
		TH2F* ddbkgs = histmapbkg->get_throwable(plotname,3); 
		//histmapbkg is indexed using the h_ name rather than the b_name
		//This is done around the line "histmapbkg->set(thisbkgplotname,temp2);"
		TH1F* ddbks[nmodes];
		ddbks[0] = (TH1F*) hslice(ddbkgs,1)->Clone((plotname+"__DDBKG").c_str());
		ddbks[1] = (TH1F*) hslice(ddbkgs,2)->Clone((plotname+"__DDBKG__passrate__plus").c_str());
		ddbks[2] = (TH1F*) hslice(ddbkgs,3)->Clone((plotname+"__DDBKG__passrate__minus").c_str());
		ddbks[3] = (TH1F*) hslice(ddbkgs,4)->Clone((plotname+"__DDBKG__failrate__plus").c_str());
		ddbks[4] = (TH1F*) hslice(ddbkgs,5)->Clone((plotname+"__DDBKG__failrate__minus").c_str());
		if(draw_ddbkg){
		    for(int i=0;i<nmodes;i++) ddbks[i]->Write();
		}
		
		//get SYS (s_yield) - added by rizki - start
		//right now s_yield is a special, so this exist only for varname="yield" for the moment
		if(varname=="yield"){
			for(std::vector<DMCclass*>::iterator iclass = vSigClassesAll.begin();iclass<vSigClassesAll.end();iclass++){ 
				float cs_pb_ = (*iclass)->blocks[0]->cs_pb;
				TH2F* sys = (TH2F*) htable2D.get_throwable((*iclass)->name,1)->get_throwable(plotname,3); 
				//histmapsys is indexed using the h_ name rather than the s_name
				//This is done around the line "histmapsys->set(thisplotname,temp2);"
				TH1F* sys_[nSysYields];
				sys_[0] = (TH1F*) hslice(sys,1)->Clone((plotname+"__"+(*iclass)->name+"__nominal").c_str());

				//Pileup auncertainties should be left full-value for signal.
				sys_[1] = (TH1F*) hslice(sys,2)->Clone((plotname+"__"+(*iclass)->name+"__PU__plus").c_str());
				sys_[2] = (TH1F*) hslice(sys,3)->Clone((plotname+"__"+(*iclass)->name+"__PU__minus").c_str());
				
				//Renorm and PDF uncertainties should be shape-only for signal, or else the limits will explode. 
				//The signal MC is all leading order with extremely huge uncertainty and theta can't really handle it. 
				//So the procedure for signal is that those uncertainty histograms get normalized: 
				//ShiftedHist->Scale(CentralValueHist->Integral() / ShiftedHist->Integral())

				sys_[3] = (TH1F*) hslice(sys,4)->Clone((plotname+"__"+(*iclass)->name+"__renorm__plus").c_str());
				sys_[4] = (TH1F*) hslice(sys,5)->Clone((plotname+"__"+(*iclass)->name+"__renorm__minus").c_str());
				sys_[5] = (TH1F*) hslice(sys,6)->Clone((plotname+"__"+(*iclass)->name+"__pdf__plus").c_str());
				sys_[6] = (TH1F*) hslice(sys,7)->Clone((plotname+"__"+(*iclass)->name+"__pdf__minus").c_str());

				sys_[3]->Scale(sys_[0]->Integral()/sys_[3]->Integral());
				sys_[4]->Scale(sys_[0]->Integral()/sys_[4]->Integral());
				sys_[5]->Scale(sys_[0]->Integral()/sys_[5]->Integral());
				sys_[6]->Scale(sys_[0]->Integral()/sys_[6]->Integral());

				//JetSF uncertainties should be left full-value for signal.
				sys_[7] = (TH1F*) hslice(sys,8)->Clone((plotname+"__"+(*iclass)->name+"__JetSF__plus").c_str());
				sys_[8] = (TH1F*) hslice(sys,9)->Clone((plotname+"__"+(*iclass)->name+"__JetSF__minus").c_str());
			
// 				for(int i=1;i<nSysYields;i++){
				for(int i=0;i<nSysYields;i++){
					sys_[i]->Scale(1./(cs_pb_)); //scale to 1 pb
					sys_[i]->Write();
				}
			}
			
			for(std::vector<DMCclass*>::iterator iclass = vBkgClasses.begin();iclass<vBkgClasses.end();iclass++){ //for every bkg class
				TH2F* sys = (TH2F*) htable2D.get_throwable((*iclass)->name,1)->get_throwable(plotname,3); 
				//histmapsys is indexed using the h_ name rather than the s_name
				//This is done around the line "histmapsys->set(thisplotname,temp2);"
				TH1F* sys_[nSysYields];
				sys_[0] = (TH1F*) hslice(sys,1)->Clone((plotname+"__"+(*iclass)->name+"__nominal").c_str());
				sys_[1] = (TH1F*) hslice(sys,2)->Clone((plotname+"__"+(*iclass)->name+"__PU__plus").c_str());
				sys_[2] = (TH1F*) hslice(sys,3)->Clone((plotname+"__"+(*iclass)->name+"__PU__minus").c_str());
				sys_[3] = (TH1F*) hslice(sys,4)->Clone((plotname+"__"+(*iclass)->name+"__renorm__plus").c_str());
				sys_[4] = (TH1F*) hslice(sys,5)->Clone((plotname+"__"+(*iclass)->name+"__renorm__minus").c_str());
				sys_[5] = (TH1F*) hslice(sys,6)->Clone((plotname+"__"+(*iclass)->name+"__pdf__plus").c_str());
				sys_[6] = (TH1F*) hslice(sys,7)->Clone((plotname+"__"+(*iclass)->name+"__pdf__minus").c_str());
				sys_[7] = (TH1F*) hslice(sys,8)->Clone((plotname+"__"+(*iclass)->name+"__JetSF__plus").c_str());
				sys_[8] = (TH1F*) hslice(sys,9)->Clone((plotname+"__"+(*iclass)->name+"__JetSF__minus").c_str());
			
				for(int i=1;i<nSysYields;i++){
					sys_[i]->Write();
				}	
			}
		}		
		//get SYS (s_yield) - added by rizki - end

		
	}//end try
	catch(std::pair <std::string,int> errorpair){
	    switch(errorpair.second ){
		case 1: cerr<<"Stringmap Error! While making Theta root files. Invalid string key "<<errorpair.first<< " sought in htable"<<endl; break;
		case 2: cerr<<"Stringmap Error! While making Theta root files. Invalid string key "<<errorpair.first<< " sought in htable submap"<<endl; break;
		case 3: cerr<<"Stringmap Error! While making Theta root files. Invalid string key "<<errorpair.first<< " sought in histmapbkg"<<endl; break;
	    }//end switch
	    std::terminate();
	}//end catch;

	f->Close();
	return filename;
} //end MakeThetaRootFile_Yield with signal - added by Rizki



std::vector<thetaSigFile*> MakeThetaRootFile_Yield_signalScan(stringmap<std::vector<TH1F*>> Signal_yields,  std::vector<DMCclass*> vSigClassesAll,string dir, int nBRslices){
	//take in signal yields broken up by MCtrue branching and produces a scan of files containing just them. 	
	//I need six versions of h_yield from each signal file: WW, WH, WZ, HZ, HH, ZZ. 
	double div = 1.0/((double) nBRslices); 
	std::vector<thetaSigFile*> thetaSigFiles;
	
	//then I'm going to get their branching ratios and scan them. 
	for(std::vector<DMCclass*>::iterator iclass = vSigClassesAll.begin();iclass<vSigClassesAll.end();iclass++){ //for every bkg class
		std::vector<TH1F*> hists = Signal_yields.get_throwable((*iclass)->name,1);
		for(double bWbr = 0.0; bWbr <= 1.0; bWbr += div){
		    for(double tHbr = 0.0; tHbr <= 1.0-bWbr; tHbr += div){
			string thisfilename = ThetaFileNameSig(dir,(*iclass)->name,bWbr, tHbr);

			TH1F* thissig =  brRescale( hists, bWbr, tHbr,"yield__signal");
			thetaSigFiles.push_back(new thetaSigFile(thisfilename,bWbr, tHbr));
			TFile* f = new TFile(thisfilename.c_str() ,"RECREATE");
			f->cd();
			thissig->Write();
			//eventually you'll be writing a great many more into this file. 
			f->Close();
		    }//end tHbr scan. 
		}//end bWbr scan
        }//end for every class. 
	return thetaSigFiles;
}//end MakeThetaRootFile_Yield_signalScan

string ThetaFileNameSig(string directory, string classname, double bWbr, double tHbr){
	//makes the names for root files going to Theta 
	//for bWbr = 0.12, tHbr = 0.34 class TpTp800f, returns directory/hist4limit_yield_TpTp800f_Wbr12_Hbr34.root;
	char bufferW[5]; //4 for 2 decimal places, 5 for 3. 
	char bufferH[5]; //4 for 2 decimal places, 5 for 3. 
	sprintf(bufferW,"%.3f",bWbr);
	sprintf(bufferH,"%.3f",tHbr);
	string sW(bufferW);
	string sH(bufferH);
	return directory+"/hist4limit_yield_"+classname+"_Wbr"+sW.substr(2)+"_Hbr"+sH.substr(2)+ ".root";
} 

TH1F* brRescale( std::vector<TH1F*> hists, float bWbr, float tHbr, string outname){
	//Take a vector of simulated signal, divided up by branching. Reweight (without changing hists) to a new br. 
	//add that all up and return it.  
    //Assumes the vector is of length 6 = nBByields
    //0:WW, 1:WH, 2: WZ, 3: HH, 4: HZ, 5: ZZ 
    float tZbr = get_bZbr(bWbr, tHbr);

    vector<TH1F*> hout;
    for(int i=0;i<nBByields;i++) hout.push_back( (TH1F*) hists[i]->Clone((((string) hists[i]->GetName()) + "_" + to_string(bWbr) + "_" + to_string(tHbr)).c_str() ) );

	//multiplying by nine = dividing by (1/3)^2
	//the combinatorial factors of 2 cancel. 
    hout[0]->Scale( bWbr*bWbr*9.0 );
    hout[1]->Scale( bWbr*tHbr*9.0 );
    hout[2]->Scale( bWbr*tZbr*9.0 );
    hout[3]->Scale( tHbr*tHbr*9.0 );
    hout[4]->Scale( tHbr*tZbr*9.0 );
    hout[5]->Scale( tZbr*tZbr*9.0 );
	TH1F* out = (TH1F*) hout[0]->Clone(outname.c_str());
    for(int i=1;i<nBByields;i++) out->Add(hout[i]);
    return out;
}//end MCbrReweight

float get_bZbr(float bWbr, float tHbr){
    assert(bWbr <= 1.0 and bWbr >= 0.0 and tHbr <= 1.0 and tHbr >= 0);
    float tZbr = 1.0 - tHbr - bWbr;
    assert(tZbr >= 0.0 and tZbr < 1.0);
    return tZbr;
}

string MakeThetaCounts(histtable htable, histmap2D* histmapbkg, string SigClassToUse, std::vector<DMCclass*> vBkgClasses, bool draw_ddbkg){
	//Here you're going to do the simplest thing. 
	//1. Get a all the background hists, add them into one hist. 
	//2. Then get the signal hists, add them into one hist. 
	//3. Do a very simple counting experiment in Theta to see where the ideal cut value is in terms of optomizing the expected limit. 
	//This will be done for every plot in sight, so it needs to be fast. 
	//You'll need to reach into kinvars and figure out which is the best thign to do. 
	
	string varname = "yield";
	string plotname = "h_"+varname; 

	string dir = ".";
	string filename = dir+"/hist4limit_yield.root";
	cout<<"writing limit root file to "<<filename<<endl;

	TFile * f = new TFile(filename.c_str(), "RECREATE");
	f->cd();

	try{

	    //write all the background histograms. 
	    for(std::vector<DMCclass*>::iterator iclass = vBkgClasses.begin();iclass<vBkgClasses.end();iclass++){ //for every bkg class
		TH1F* thisbkghist = (TH1F*) htable.get_throwable((*iclass)->name,1)->get_throwable(varname,2)->Clone((varname+"__"+(*iclass)->name).c_str());
		thisbkghist->Write();
	    }

	    //Get the ddhists
	    TH2F* ddbkgs = histmapbkg->get_throwable(plotname,3); 
	    //histmapbkg is indexed using the h_ name rather than the b_name
	    //This is done around the line "histmapbkg->set(thisbkgplotname,temp2);"
	    TH1F* ddbks[nmodes];
	    ddbks[0] = (TH1F*) hslice(ddbkgs,1)->Clone("yield__DDBKG");
	    ddbks[1] = (TH1F*) hslice(ddbkgs,1)->Clone("yield__DDBKG__passrate__plus");
	    ddbks[2] = (TH1F*) hslice(ddbkgs,1)->Clone("yield__DDBKG__passrate__minus");
	    ddbks[3] = (TH1F*) hslice(ddbkgs,1)->Clone("yield__DDBKG__failrate__plus");
	    ddbks[4] = (TH1F*) hslice(ddbkgs,1)->Clone("yield__DDBKG__failrate__minus");
// 	    ddbks[5] = (TH1F*) hslice(ddbkgs,1)->Clone("yield__DDBKG__qMisIDrate__plus");
// 	    ddbks[6] = (TH1F*) hslice(ddbkgs,1)->Clone("yield__DDBKG__qMisIDrate__minus");
	    if(draw_ddbkg){
		for(int i=0;i<nmodes;i++) ddbks[i]->Write();
	    }

	}//end try
	catch(std::pair <std::string,int> errorpair){
	    switch(errorpair.second ){
		case 1: cerr<<"Stringmap Error! While making Theta nonsig root files. Invalid string key "<<errorpair.first<< " sought in htable"<<endl; break;
		case 2: cerr<<"Stringmap Error! While making Theta nonsig root files. Invalid string key "<<errorpair.first<< " sought in htable submap"<<endl; break;
		case 3: cerr<<"Stringmap Error! While making Theta nonsig root files. Invalid string key "<<errorpair.first<< " sought in histmapbkg"<<endl; break;
	    }//end switch
	    std::terminate();
	}//end catch;

	f->Close();
	return filename;
} //end MakeThetaCounts

TH1F* make_ratio_uncertainty_hist(TH1F* data, TH1F* bkg){
	//Will return a histogram with bin values 1, but error bars equal to the 
	string name = string(bkg->GetName()) + "uncert";
	TH1F* uncert = new TH1F(*bkg);
	uncert->Reset();
	for(int i=1;i<=bkg->GetNbinsX();i++){
		float bin = bkg->GetBinContent(i);
		if(!aeq(bin,0.)) uncert->SetBinError(i,bkg->GetBinError(i)/pow(bin,2));
		else uncert->SetBinError(i,0);
		uncert->SetBinContent(i,1);
	}
	return uncert;
}

void fix_negatives(TH1F* hist){
	//Given a histogram that might have negative entries, 
	//Zero those entries and rescale the rest of the histogram to have the same integral. 
	float integ = 0.;
	float pos_integral = 0.;
	float stat_uncert = 0.;

	for(int i=1;i<=hist->GetNbinsX();i++){
		float bin = hist->GetBinContent(i);
		integ+= bin;
		stat_uncert+= fabs(bin);
		if(bin >=0) pos_integral += bin;
		else{
			 hist->SetBinContent(i,0);
			 hist->SetBinError(i,0);
		}
	}//for
	stat_uncert = sqrt(stat_uncert);

	// hist->Scale(integ/pos_integral);
	if(pos_integral>0 ){
	    for(int i=1;i<=hist->GetNbinsX();i++){
		float bin = hist->GetBinContent(i);
		float ubin = hist->GetBinError(i);
		
		float newbin = bin*integ/pos_integral;
		hist->SetBinContent(i, newbin);
		if(aeq(bin,0.) or aeq(integ, 0)  ) hist->SetBinError(i, 0.); 
		else hist->SetBinError(i, newbin*sqrt(
				pow(ubin/bin,2) +
				pow(stat_uncert/integ,2) + 
				(1.0/pos_integral)  )  );
		
	    }//end for
	}//end if there's no divide by zero error. 
}//end fix_negatives

void fix_negativesX(TH2F* hist){
    for(int j=1;j<=hist->GetNbinsY();j++){
	float integ = 0.;
	float pos_integral = 0.;
	float stat_uncert = 0.;

	for(int i=1;i<=hist->GetNbinsX();i++){
	    float bin = hist->GetBinContent(i);
	    integ+= bin;
	    stat_uncert+= fabs(bin);
	    if(bin >=0) pos_integral += bin;
	    else{
		hist->SetBinContent(i,0);
		hist->SetBinError(i,0);
	    }
	}//for
	stat_uncert = sqrt(stat_uncert);

	// hist->Scale(integ/pos_integral);
	if(pos_integral>0 ){
	    for(int i=1;i<=hist->GetNbinsX();i++){
		float bin = hist->GetBinContent(i);
		float ubin = hist->GetBinError(i);

		float newbin = bin*integ/pos_integral;
		hist->SetBinContent(i, newbin);
		if(aeq(bin,0.) or aeq(integ, 0)  ) hist->SetBinError(i, 0.); 
		else hist->SetBinError(i, newbin*sqrt(
			    pow(ubin/bin,2) +
			    pow(stat_uncert/integ,2) + 
			    (1.0/pos_integral)  )  );

	    }//end for
	}//end if there's no divide by zero error. 
    }//end for y
}

void check_for_negatives(TH1F* hist){
	bool has_neg = false;
	for(int i=1;i<=hist->GetNbinsX() and not has_neg;i++){
		if(hist->GetBinContent(i)<0) has_neg = true;
	}//for
	if(has_neg) cout<<"Hist still has negatives "<<hist->GetName()<<endl;
}

