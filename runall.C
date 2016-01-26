#define runall_cxx
#include "tpmultlepmaincalc.C"
#include "interface/DMCblock.h"
#include "interface/DMCblock_list.h"
#include <iostream>
#include <time.h>
using namespace std;
//nohup root -l -b -q runall.C+ > runall.log
void runall(){
	clock_t startfor = clock();
	std::vector<DMCblock*> vp = setupDMCblocks();
	int i =1;
	eventRegistry EventRegistry;
	for(std::vector<DMCblock*>::iterator dit = vp.begin(); dit != vp.end(); dit++){
		cout<<"in for"<<endl;
		if((*dit)->Tis50ns_Fis25ns) continue; //don't run 50ns swill
		//if((*dit)->type <0 ) continue; //don't data

		cout<<endl<<"RUNNING BLOCK "<<(*dit)->name<<" NUMBER "<<i<<endl;
	
		clock_t startloop= clock();
		tpmultlepmaincalc* t = new tpmultlepmaincalc(*dit);
		t->Loop(&EventRegistry);
		clock_t endloop= clock();
		cout << "Block "<<(*dit)->name<<" ran in "<<((float) (endloop - startloop))/CLOCKS_PER_SEC<<" seconds"<<endl;
	}//end for all blocks
	clock_t endfor = clock();
	cout << "All blocks ran in "<<((float) (endfor - startfor))/CLOCKS_PER_SEC<<" seconds"<<endl;
}//end runall
