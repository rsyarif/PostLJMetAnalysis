#define runone_cxx
#include "tpmultlepmaincalc.C"
#include "interface/DMCblock.h"
#include "interface/DMCblock_list.h"
#include "interface/DMCclass_list.h"
#include <iostream>
#include <time.h>
using namespace std;
//nohup root -l -b -q runall.C+ > runall.log
void runone(){
	clock_t startfor = clock();
// 	DMCclass * dc =setupDMCclass("DYJetsToLLf");
// 	DMCclass * dc =setupDMCclass("ttjf");
	DMCclass * dc =setupDMCclass("Data2lepf");
// 	DMCclass * dc =setupDMCclass("Data1lepf");
//  	DMCclass * dc =setupDMCclass("TpTp800f");
//	DMCclass * dc =setupDMCclass("QCDf");
	eventRegistry EventRegistry; //for data only. 
	for(std::vector<DMCblock*>::iterator dit = dc->blocks.begin(); dit != dc->blocks.end(); dit++){
		if((*dit)->Tis50ns_Fis25ns) continue; //don't run 50ns swill
		//if((*dit)->type <0 ) continue; //don't data

		cout<<endl<<"RUNNING BLOCK "<<(*dit)->name<<endl;
	
		clock_t startloop= clock();
		tpmultlepmaincalc* t = new tpmultlepmaincalc(*dit);
		t->Loop(&EventRegistry);
		//if((*dit)->type == 71 && (*dit)->processID == 1) cout<<"Found DY 50? "<<(*dit)->name<<endl;
		clock_t endloop= clock();
		cout << "Block "<<(*dit)->name<<" ran in "<<((float) (endloop - startloop))/CLOCKS_PER_SEC<<" seconds"<<endl;
	}//end for all blocks
	clock_t endfor = clock();
	cout << "All blocks ran in "<<((float) (endfor - startfor))/CLOCKS_PER_SEC<<" seconds"<<endl;
}//end runall
