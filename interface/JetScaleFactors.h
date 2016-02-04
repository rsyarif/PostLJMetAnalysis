#ifndef _JETSCALEFACTOR_H
#define _JETSCALEFACTOR_H
//#include <iostream>
//#include "math.h"
//#include "TMath.h"
using namespace std; 


//float GetJetSF(float jetpt);
void GetJetSF( float jetpt, float* jetSFs );
enum JetSFmode{JetSFnominal = 0, JetSFup = 1, JetSFdown = 2};

/*float GetJetSF(float jetpt,int UpDownMode){
	//enum JetSFmode{JetSFnominal = 0, JetSFup = 1, JetSFdown = 2};
	//Weight MC events by the product(over all jets) of these scale factors
	//Developed by Julie Hogan, 2015.
      if(jetpt > 200.f){
	  float jetsfnom = 1.09771f - 0.000517529*jetpt;
	  if(UpDownMode == JetSFnominal)return min(1.f,jetsfnom);

	  float jetsferr = sqrt(1.479511e-3f + jetpt*jetpt*9.898156e-9f - 2.f*jetpt*3.610487e-6f);
	  //float jetsferr = sqrt(0.0014795109823 + jetpt*jetpt*9.89815635815e-9 - 2.0*jetpt*(3.6104869696e-6));
	  if(UpDownMode == JetSFup) 	return min(1.f,jetsfnom + jetsferr);
	  if(UpDownMode == JetSFdown) 	return min(1.f,jetsfnom - jetsferr);
      }//end if.
      return 1.0;
}//end GetJetSF
*/

void GetJetSF( float jetpt, float* jetSFs ){
	//Takes in an array of three jet scale factors with index = enum JetSFmode and increments the SFs in the array. 
	//Use only to weight MC events, run this for every jet.  
	//	after all reweighting is done, SF = product_{all jets} SF_ijet
	//uses enum JetSFmode{JetSFnominal = 0, JetSFup = 1, JetSFdown = 2};
	//Developed by Julie Hogan, 2015.
      if(jetpt > 200.f){
	  float jetsfnom = 1.09771f - 0.000517529*jetpt;
	  float jetsferr = sqrt(1.479511e-3f + jetpt*jetpt*9.898156e-9f - 2.f*jetpt*3.610487e-6f);
	  //float jetsferr = sqrt(0.0014795109823 + jetpt*jetpt*9.89815635815e-9 - 2.0*jetpt*(3.6104869696e-6));

	  jetSFs[JetSFnominal] *=  min(1.f,jetsfnom);
	  jetSFs[JetSFup]      *=  min(1.f,jetsfnom + jetsferr);
	  jetSFs[JetSFdown]    *=  min(1.f,jetsfnom - jetsferr);
      }//end if.
}//end GetJetSF

#endif
