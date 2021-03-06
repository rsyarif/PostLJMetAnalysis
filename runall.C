#define runall_cxx
#include "tpmultlepmaincalc.C"
#include "interface/DMCblock.h"
#include "interface/DMCblock_list.h"
#include <iostream>
#include <time.h>
#include "eventRegistry.C"
#include "populate_BadEventRegistry.C"
#include "interface/controlpannel.h"
using namespace std;
//nohup root -l -b -q runall.C+ > runall.log
void runall(){
	clock_t startfor = clock();
	bool rundata = true;
	std::vector<DMCblock*> vp = setupDMCblocks();
	std::vector<DMCblock*> vp_BTag_up = setupDMCblocks_BTag_up();
	std::vector<DMCblock*> vp_BTag_down = setupDMCblocks_BTag_down();
	std::vector<DMCblock*> vp_JEC_up = setupDMCblocks_JEC_up();
	std::vector<DMCblock*> vp_JEC_down = setupDMCblocks_JEC_down();
	std::vector<DMCblock*> vp_JER_up = setupDMCblocks_JER_up();
	std::vector<DMCblock*> vp_JER_down = setupDMCblocks_JER_down();

	int i =1;
	eventRegistry EventRegistry;
	eventRegistry BadEventRegistry;
	if(rundata) populate_BadEventRegistry(&BadEventRegistry,true);
	for(std::vector<DMCblock*>::iterator dit = vp.begin(); dit != vp.end(); dit++){
		cout<<"in for"<<endl;
		if((*dit)->Tis50ns_Fis25ns) continue; //don't run 50ns swill
		//if((*dit)->type <0 ) continue; //don't data

		cout<<endl<<"RUNNING BLOCK "<<(*dit)->name<<" NUMBER "<<i<<endl;
	
		clock_t startloop= clock();
		tpmultlepmaincalc* t = new tpmultlepmaincalc(*dit);
		t->Loop(&EventRegistry,&BadEventRegistry);
		clock_t endloop= clock();
		cout << "Block "<<(*dit)->name<<" ran in "<<((float) (endloop - startloop))/CLOCKS_PER_SEC<<" seconds"<<endl;
	}//end for all blocks 
	for(std::vector<DMCblock*>::iterator dit = vp_BTag_up.begin(); dit != vp_BTag_up.end() && useBTagSys; dit++){
		cout<<"in for"<<endl;
		if((*dit)->Tis50ns_Fis25ns) continue; //don't run 50ns swill
		//if((*dit)->type <0 ) continue; //don't data

		cout<<endl<<"RUNNING BLOCK "<<(*dit)->name<<" NUMBER "<<i<<endl;
	
		clock_t startloop= clock();
		tpmultlepmaincalc* t = new tpmultlepmaincalc(*dit);
		t->Loop(&EventRegistry,&BadEventRegistry);
		clock_t endloop= clock();
		cout << "Block "<<(*dit)->name<<" ran in "<<((float) (endloop - startloop))/CLOCKS_PER_SEC<<" seconds"<<endl;
	}//end for all BTag_up blocks 
	for(std::vector<DMCblock*>::iterator dit = vp_BTag_down.begin(); dit != vp_BTag_down.end() && useBTagSys; dit++){
		cout<<"in for"<<endl;
		if((*dit)->Tis50ns_Fis25ns) continue; //don't run 50ns swill
		//if((*dit)->type <0 ) continue; //don't data

		cout<<endl<<"RUNNING BLOCK "<<(*dit)->name<<" NUMBER "<<i<<endl;
	
		clock_t startloop= clock();
		tpmultlepmaincalc* t = new tpmultlepmaincalc(*dit);
		t->Loop(&EventRegistry,&BadEventRegistry);
		clock_t endloop= clock();
		cout << "Block "<<(*dit)->name<<" ran in "<<((float) (endloop - startloop))/CLOCKS_PER_SEC<<" seconds"<<endl;
	}//end for all BTag_down blocks 
	for(std::vector<DMCblock*>::iterator dit = vp_JEC_up.begin(); dit != vp_JEC_up.end() && useJECsys; dit++){
		cout<<"in for"<<endl;
		if((*dit)->Tis50ns_Fis25ns) continue; //don't run 50ns swill
		//if((*dit)->type <0 ) continue; //don't data

		cout<<endl<<"RUNNING BLOCK "<<(*dit)->name<<" NUMBER "<<i<<endl;
	
		clock_t startloop= clock();
		tpmultlepmaincalc* t = new tpmultlepmaincalc(*dit);
		t->Loop(&EventRegistry,&BadEventRegistry);
		clock_t endloop= clock();
		cout << "Block "<<(*dit)->name<<" ran in "<<((float) (endloop - startloop))/CLOCKS_PER_SEC<<" seconds"<<endl;
	}//end for all JEC_up blocks 
	for(std::vector<DMCblock*>::iterator dit = vp_JEC_down.begin(); dit != vp_JEC_down.end() && useJECsys; dit++){
		cout<<"in for"<<endl;
		if((*dit)->Tis50ns_Fis25ns) continue; //don't run 50ns swill
		//if((*dit)->type <0 ) continue; //don't data

		cout<<endl<<"RUNNING BLOCK "<<(*dit)->name<<" NUMBER "<<i<<endl;
	
		clock_t startloop= clock();
		tpmultlepmaincalc* t = new tpmultlepmaincalc(*dit);
		t->Loop(&EventRegistry,&BadEventRegistry);
		clock_t endloop= clock();
		cout << "Block "<<(*dit)->name<<" ran in "<<((float) (endloop - startloop))/CLOCKS_PER_SEC<<" seconds"<<endl;
	}//end for all JEC_down blocks
	for(std::vector<DMCblock*>::iterator dit = vp_JER_up.begin(); dit != vp_JER_up.end() && useJERsys; dit++){
		cout<<"in for"<<endl;
		if((*dit)->Tis50ns_Fis25ns) continue; //don't run 50ns swill
		//if((*dit)->type <0 ) continue; //don't data

		cout<<endl<<"RUNNING BLOCK "<<(*dit)->name<<" NUMBER "<<i<<endl;
	
		clock_t startloop= clock();
		tpmultlepmaincalc* t = new tpmultlepmaincalc(*dit);
		t->Loop(&EventRegistry,&BadEventRegistry);
		clock_t endloop= clock();
		cout << "Block "<<(*dit)->name<<" ran in "<<((float) (endloop - startloop))/CLOCKS_PER_SEC<<" seconds"<<endl;
	}//end for all JER_up blocks
	for(std::vector<DMCblock*>::iterator dit = vp_JER_down.begin(); dit != vp_JER_down.end() && useJERsys; dit++){
		cout<<"in for"<<endl;
		if((*dit)->Tis50ns_Fis25ns) continue; //don't run 50ns swill
		//if((*dit)->type <0 ) continue; //don't data

		cout<<endl<<"RUNNING BLOCK "<<(*dit)->name<<" NUMBER "<<i<<endl;
	
		clock_t startloop= clock();
		tpmultlepmaincalc* t = new tpmultlepmaincalc(*dit);
		t->Loop(&EventRegistry,&BadEventRegistry);
		clock_t endloop= clock();
		cout << "Block "<<(*dit)->name<<" ran in "<<((float) (endloop - startloop))/CLOCKS_PER_SEC<<" seconds"<<endl;
	}//end for all JER_down blocks

	clock_t endfor = clock();
	cout << "All blocks ran in "<<((float) (endfor - startfor))/CLOCKS_PER_SEC<<" seconds"<<endl;
}//end runall
