#ifndef DMCBLOCK
#define DMCBLOCK
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "TString.h"
#include <TChain.h>
#include "TTree.h"
#include "interface/utilities.h"
using namespace std;

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

typedef map<string,int> namedInt;
typedef map<string,float> namedFloat;
typedef map<string,string> namedString;

class DMCblock{
	public:
		int type; //-1 is reserved for daat. 
		int processID; //distinguishes files within a type. 
		string name; 
		namedInt int_meta;
		namedFloat float_meta;
		namedString string_meta;

		double cs_pb; //cross section in pico barns
		double cs_pb_uncert;
		int NGenPoints;
		bool Tis50ns_Fis25ns;
		float sqrtS; 
		bool BfieldOn; 
		bool isMC;

		int nfiles; 
		vector<string> rootFilePaths; 

		float lumiscalefactor(float lumi_in_fb){
			if(not isMC or type <= -1) return 1;//if data
			return (lumi_in_fb * cs_fb())/((float) NGenPoints);
        	}

		//option 1: point to a single file. 
		//DMCblock(int, string, double, double, int, string, {},{},{},[bool],[float], [bool])
		DMCblock(int type_, string name_, double cs_pb_, double cs_pb_uncert_, int NGenPoints_, string rootFilePath, 
				namedInt int_meta_, namedFloat float_meta_, namedString string_meta_,
				bool isMC_ = true, bool Tis50ns_Fis25ns_ = false, float sqrtS_ = 13., bool BfieldOn_ = true){
				//copy in meta if not already done.
			type=type_;
			name=name_;
			cs_pb=cs_pb_;
			cs_pb_uncert=cs_pb_uncert_;
			NGenPoints=NGenPoints_;
			int_meta=int_meta_;
			float_meta=float_meta_;
			string_meta=string_meta_;
			isMC=isMC_;
			Tis50ns_Fis25ns=Tis50ns_Fis25ns_;
			sqrtS=sqrtS_;
			BfieldOn=BfieldOn_;

			//copy in rootFilePath
			nfiles = 1;
			//check that the file exists. 
			if(not fileExists(rootFilePath)){
				fprintf(stderr, "WARNING! Cannot find file for DMCblock %i type %s: %s\n", type_, name_.c_str(), rootFilePath.c_str());
				nfiles = 0;
			}
			rootFilePaths.push_back(rootFilePath);
			setup(type_);

		}//end DMCblock option 

		//option 2: load a list of file paths from file at rootFilePathsList. 
		//DMCblock(string, int, string, double, double, int, {},{},{},[bool],[float], [bool]), order alone distinguishes this from option1. 
		DMCblock(string name_of_rootFilePathsList, int type_, string name_, double cs_pb_, double cs_pb_uncert_, int NGenPoints_, 
				namedInt int_meta_, namedFloat float_meta_, namedString string_meta_,
				bool isMC_ = true, bool Tis50ns_Fis25ns_ = false, float sqrtS_ = 13., bool BfieldOn_ = true){
			type=type_;
			name=name_;
			cs_pb=cs_pb_;
			cs_pb_uncert=cs_pb_uncert_;
			NGenPoints=NGenPoints_;
			int_meta=int_meta_;
			float_meta=float_meta_;
			string_meta=string_meta_;
			isMC=isMC_;
			Tis50ns_Fis25ns=Tis50ns_Fis25ns_;
			sqrtS=sqrtS_;
			BfieldOn=BfieldOn_;

			nfiles =0;
			if(fileExists(name_of_rootFilePathsList)){ //check that the list of files actually exists
				FILE *fdin = fopen(name_of_rootFilePathsList.c_str(), "r");
				char thisfile[256];
				while(fscanf(fdin,"%s",thisfile)!=EOF) { //load all the files in the list into the vector rootFilePaths
					rootFilePaths.push_back(  string(thisfile)  );
					nfiles++; //count how many files there are. 
				}
				checkFileList(); //complain if the files don't actually exist. 
			}//end if file exists
			else{ //can't find list of filenames
				fprintf(stderr, "WARNING! Cannot find list of file paths %s for DMCblock %i type %s\n", 
					name_of_rootFilePathsList.c_str(), type_, name_.c_str());
				nfiles = 0;
			}//end else
			setup(type_);
		}//end DMCblock option 2

		//option 3: load a vector literal of filepaths
		DMCblock(int type_, string name_, double cs_pb_, double cs_pb_uncert_, int NGenPoints_, 
				vector<string> rootFilePaths_, 
				namedInt int_meta_, namedFloat float_meta_, namedString string_meta_,
				bool isMC_ = true, bool Tis50ns_Fis25ns_ = false, float sqrtS_ = 13., bool BfieldOn_ = true){
			type=type_;
			name=name_;
			cs_pb=cs_pb_;
			cs_pb_uncert=cs_pb_uncert_;
			NGenPoints=NGenPoints_;
			int_meta=int_meta_;
			float_meta=float_meta_;
			string_meta=string_meta_;
			isMC=isMC_;
			Tis50ns_Fis25ns=Tis50ns_Fis25ns_;
			sqrtS=sqrtS_;
			BfieldOn=BfieldOn_;
			rootFilePaths=rootFilePaths_;
			
			nfiles = (int)rootFilePaths.size();
			checkFileList();
			setup(type_);
		}//end DMCblock option3.

		~DMCblock(){
			//delete int_meta;
			//delete float_meta;
			//delete string_meta;
			//for(std::vector<string>::iterator i = rootFilePaths.begin(); i<rootFilePaths.end();i++) delete *i; 
			//delete name;
		}//end ~DMCblock


		float cs_fb(){ return (float)(cs_pb * 1E3); }
		void setup(int type_);
		int gettype(){return type;}
		void checkFileList(){
			for(std::vector<string>::iterator f = rootFilePaths.begin(); f != rootFilePaths.end(); f++){ 
				if( not fileExists(*f)) //gripe if any don't exist. 
					//this is unhappy because f is an iterator.
					fprintf(stderr, "WARNING! Cannot find file %s for DMCblock %i type %s\n", (*f).c_str(), type, name.c_str());
			}//end for
		}//end checkFileList.

		//TString makeLimitCardName(TString topo, TString kinvar);//Returns name of Card File 

		TChain* getTchain(string subdir){
			TChain * theTchain = new TChain(subdir.c_str());
			for(std::vector<string>::iterator f = rootFilePaths.begin(); f != rootFilePaths.end(); f++) theTchain->Add((*f).c_str());
			return theTchain;	
		}//
		TTree* getTTree(string subdir){ return (TTree *) getTchain(subdir); }
}; //end DMCblock

void DMCblock::setup(int type_){ //xxx needs work.

	
	cs_pb_uncert = -1;
	if(type_ <= -1){ //types less than 0 are reserved for data.
		//     ___       __
		//    / _ \___ _/ /____ _
		//   / // / _ `/ __/ _ `/
		//  /____/\_,_/\__/\_,_/
		//

		cs_pb = 0;
		cs_pb_uncert = 0;
		NGenPoints = -1;
		isMC = false;

		//string Data = "Data";
		//string_meta["s_DataAndMcFiles"] = Data;
		//string_meta["outroot_mc"] = outroot_data;
		//string_meta["btageff_file"] = "";
		//string_meta["plotsroot_mc"] = plotsroot_data;
		//string_meta["logplotsroot_mc"] = plotsroot_mc_copy.replace(pos1,std::string(".root").length(),".log");
	//	string_meta["plotsAndBackground_mc"] = plotsAndBackground_data;
	//	string_meta["logplotsAndBackground_mc"] = logplotsAndBackground_data;
	//	string_meta["formatedplotsroot_mc"]= formatedplotsroot_data;

	}

	//else if(type_ == 4){ //Higgs to GG fullsim MC
	//}
	//else if(type_ == 5){ //Fullsim MC
	//}	
	string_meta["EventLoopOutRoot"] = "eventloop_"+name+".root";
}//end setup


class DMCclass{
	public:
	string name;
	int nblocks;
	std::vector<DMCblock*> blocks;
	bool Tis50ns_Fis25ns;
	namedInt int_meta;
	namedFloat float_meta;
	namedString string_meta;


	DMCclass(string name_, bool Tis50ns_Fis25ns_ = false){
	    name = name_;
	    Tis50ns_Fis25ns = Tis50ns_Fis25ns_;
	    nblocks = 0;
	    //int_meta=int_meta_;
	    //float_meta=float_meta_;
	    //string_meta=string_meta_;
	}

	DMCclass(string name_, DMCblock* b, 
		namedInt int_meta_, namedFloat float_meta_, namedString string_meta_,
		bool Tis50ns_Fis25ns_ = false){
	    name = name_;
	    Tis50ns_Fis25ns = Tis50ns_Fis25ns_;
	    nblocks = 0;
	    int_meta=int_meta_;
	    float_meta=float_meta_;
	    string_meta=string_meta_;
	    add(b);
	}

	DMCclass(string name_, int type, std::vector<DMCblock*> vb, 
		namedInt int_meta_, namedFloat float_meta_, namedString string_meta_,
		bool Tis50ns_Fis25ns_ = false){
	    name = name_;
	    Tis50ns_Fis25ns = Tis50ns_Fis25ns_;
	    nblocks = 0;
	    int_meta=int_meta_;
	    float_meta=float_meta_;
	    string_meta=string_meta_;
	    addtype(type,vb);
	}

	DMCclass(string name_, int typelow, int typehigh, std::vector<DMCblock*> vb, 
		namedInt int_meta_, namedFloat float_meta_, namedString string_meta_,
		bool Tis50ns_Fis25ns_ = false){
	    name = name_;
	    Tis50ns_Fis25ns = Tis50ns_Fis25ns_;
	    nblocks = 0;
	    int_meta=int_meta_;
	    float_meta=float_meta_;
	    string_meta=string_meta_;
	    addtyperange(typelow, typehigh,vb);
	}

	~DMCclass(){
	    //for(std::vector<DMCblock*>::iterator i = blocks.begin(); i<blocks.end();i++) delete *i; 
	    //delete int_meta;
	    //delete float_meta;
	    //delete string_meta;
	}

	void add(DMCblock* b){
		if(b->Tis50ns_Fis25ns == Tis50ns_Fis25ns){
		    nblocks++;
		    blocks.push_back(b);
		}
	}

	void addtype(int type, std::vector<DMCblock*> vb){
	    for(std::vector<DMCblock*>::iterator thisblock = vb.begin();thisblock<vb.end();thisblock++){
		if((*thisblock)->type == type)
			add(*thisblock);
	    }//end for
	}//end addtype
	void addtyperange(int typelow, int typehigh, std::vector<DMCblock*> vb){
	    for(std::vector<DMCblock*>::iterator thisblock = vb.begin();thisblock<vb.end();thisblock++){
		if((*thisblock)->type <= typehigh && (*thisblock)->type >= typelow)
			add(*thisblock);
	    }//end for
	}//end addtype

/*	double cs_pb; //total cross section
	double cs_pb_uncert;
	float sqrtS;
	bool BfieldOn;
	bool isMC;*/
	//the block names
	//string meta?

};
	

#endif
