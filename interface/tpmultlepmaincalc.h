//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Dec 21 15:46:49 2015 by ROOT version 6.02/05
// from TTree ljmet/ljmet
// found on file: TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8_25ns_1.root
//////////////////////////////////////////////////////////

#ifndef tpmultlepmaincalc_h
#define tpmultlepmaincalc_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include "vector"
#include <map>
#include "interface/utilities.h"
#include "interface/DMCblock.h"
#include "interface/DMCblock_list.h"
#include "eventRegistry.C"

class tpmultlepmaincalc {
public :
   TTree          *fChain;   //pointer to the analyzed TTree or TChain
   //TTree          *fChain;   //pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //current Tree number in a TChain
   DMCblock* 	   dmcblock;

   tpmultlepmaincalc(TTree *tree=0);
   tpmultlepmaincalc(DMCblock* block);
   tpmultlepmaincalc(string blockname);
   virtual ~tpmultlepmaincalc();
   //virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(eventRegistry* EventRegistry);
   virtual void     Show(Long64_t entry = -1);
   //void SetUseTrigger(bool v) { useTrigger = v; }
   void SetUseJSON(bool v) { useJSON = v; }
   bool isSameObject(TLorentzVector& p1, TLorentzVector& p2, const float dRmax);
   void IncludeAJson(std::string jsonfile);
   bool isInJson(Int_t run,Int_t lumi);
   //bool PassTrigger(TString v); // return true if path v is fired
   //bool PassTriggers(); // return true if any of names in hltNames are fired

// Fixed size dimensions of array or collections stored in the TTree if any.



////////////////////////////////////////////////////////////////////////////
   Int_t           event_CommonCalc;
   Int_t           lumi_CommonCalc;
   Int_t           run_CommonCalc;
   Int_t           nLooseMuons_CommonCalc;
   //Int_t           nTightMuons_CommonCalc; //turned into selMuons. 
   Int_t  	   nSelMuons_CommonCalc;
   Int_t           nSelElectrons_CommonCalc;
   Int_t           nSelBtagJets_CommonCalc;
   Int_t           nAllJets_CommonCalc;
   Int_t           nSelJets_CommonCalc;
//   Also see: 
 
////////////////////////////////////////////////////////////////////////////
   vector<double>  *theJetEnergy_JetSubCalc;
   vector<double>  *theJetEta_JetSubCalc;
   vector<double>  *theJetPhi_JetSubCalc;
   vector<double>  *theJetPt_JetSubCalc;
   Double_t        theJetHT_JetSubCalc;
   Double_t        theJetLeadPt_JetSubCalc;
   Double_t        theJetSubLeadPt_JetSubCalc;
   vector<int>     *theJetBTag_JetSubCalc;
   vector<int>     *theJetFlav_JetSubCalc;
   vector<double>  *theJetCSV_JetSubCalc;
   vector<int>     *theJetnDaughters_JetSubCalc;
   vector<double>  *theJetCEmEFrac_JetSubCalc;
   vector<double>  *theJetCEmEnergy_JetSubCalc;
   vector<double>  *theJetCHadEFrac_JetSubCalc;
   vector<double>  *theJetCHadEnergy_JetSubCalc;
   vector<double>  *theJetNEmEFrac_JetSubCalc;
   vector<double>  *theJetNEmEnergy_JetSubCalc;
   vector<double>  *theJetNHadEFrac_JetSubCalc;
   vector<double>  *theJetNHadEnergy_JetSubCalc;
   //vector<double>  *theJetHTTNjettinessTau1_JetSubCalc;
   //vector<double>  *theJetHTTNjettinessTau2_JetSubCalc;
   //vector<double>  *theJetHTTNjettinessTau3_JetSubCalc;
   //vector<double>  *theJetHTTRoptCalcPt_JetSubCalc;
   //vector<double>  *theJetHTTRoptCalc_JetSubCalc;
   //vector<double>  *theJetHTTRopt_JetSubCalc;
   //vector<double>  *theJetHTTTopMass_JetSubCalc;
   //vector<double>  *theJetHTTfRec_JetSubCalc;
   //vector<double>  *theJetHTTufNjettinessTau1_JetSubCalc;
   //vector<double>  *theJetHTTufNjettinessTau2_JetSubCalc;
   //vector<double>  *theJetHTTufNjettinessTau3_JetSubCalc;
   vector<double>  *theJetPileupJetId_JetSubCalc;
   vector<double>  *theJetVtx3DSig_JetSubCalc;
   vector<double>  *theJetVtx3DVal_JetSubCalc;
   vector<double>  *theJetVtxMass_JetSubCalc;
   vector<double>  *theJetVtxNtracks_JetSubCalc;

   vector<double>  *theJetAK8Energy_JetSubCalc;
   vector<double>  *theJetAK8Eta_JetSubCalc;
   vector<double>  *theJetAK8Phi_JetSubCalc;
   vector<double>  *theJetAK8Pt_JetSubCalc;
   vector<double>  *theJetAK8CSV_JetSubCalc;
   vector<bool>    *theJetAK8PrunedTau21Tag_JetSubCalc; //pointers to vectors
   //vector<bool>    *theJetAK8SoftDropTau21Tag_JetSubCalc;
   //vector<bool>    *theJetAK8SoftDropTau32Tag_JetSubCalc;
   //vector<bool>    *theJetAK8caTopRun1Tag_JetSubCalc;
   vector<int>     *theJetAK8SDSubjetIndex_JetSubCalc;
   vector<int>     *theJetAK8SDSubjetNCSVL_JetSubCalc;
   vector<int>     *theJetAK8SDSubjetNCSVM_JetSubCalc;
   vector<int>     *theJetAK8SDSubjetSize_JetSubCalc;
   vector<int>     *theJetAK8nDaughters_JetSubCalc;
   vector<double>  *theJetAK8CEmEFrac_JetSubCalc;
   vector<double>  *theJetAK8CEmEnergy_JetSubCalc;
   vector<double>  *theJetAK8CHadEFrac_JetSubCalc;
   vector<double>  *theJetAK8CHadEnergy_JetSubCalc;
   vector<double>  *theJetAK8NEmEFrac_JetSubCalc;
   vector<double>  *theJetAK8NEmEnergy_JetSubCalc;
   vector<double>  *theJetAK8NHadEFrac_JetSubCalc;
   vector<double>  *theJetAK8NHadEnergy_JetSubCalc;
   vector<double>  *theJetAK8FilteredMass_JetSubCalc;
   vector<double>  *theJetAK8JetCharge_JetSubCalc;
   vector<double>  *theJetAK8Mass_JetSubCalc;
   vector<double>  *theJetAK8NjettinessTau1_JetSubCalc;
   vector<double>  *theJetAK8NjettinessTau2_JetSubCalc;
   vector<double>  *theJetAK8NjettinessTau3_JetSubCalc;
   vector<double>  *theJetAK8PrunedMass_JetSubCalc;
   vector<double>  *theJetAK8SDSubjetCSV_JetSubCalc;
   vector<double>  *theJetAK8SDSubjetDR_JetSubCalc;
   vector<double>  *theJetAK8SDSubjetEta_JetSubCalc;
   vector<double>  *theJetAK8SDSubjetMass_JetSubCalc;
   vector<double>  *theJetAK8SDSubjetPhi_JetSubCalc;
   vector<double>  *theJetAK8SDSubjetPt_JetSubCalc;
   vector<double>  *theJetAK8SoftDropMass_JetSubCalc;
   vector<double>  *theJetAK8TrimmedMass_JetSubCalc;
   //vector<int>     *theJetAK8caTopSubjetIndex_JetSubCalc;
   //vector<int>     *theJetAK8caTopSubjetNCSVL_JetSubCalc;
   //vector<int>     *theJetAK8caTopSubjetNCSVM_JetSubCalc;
   //vector<int>     *theJetAK8caTopSubjetSize_JetSubCalc;
   vector<int>     *theJetAK8caTopnSubJets_JetSubCalc;
   vector<double>  *theJetAK8caTopMinMass_JetSubCalc;
   //vector<double>  *theJetAK8caTopSubjetCSV_JetSubCalc;
   //vector<double>  *theJetAK8caTopSubjetDR_JetSubCalc;
   //vector<double>  *theJetAK8caTopSubjetEta_JetSubCalc;
   //vector<double>  *theJetAK8caTopSubjetMass_JetSubCalc;
   //vector<double>  *theJetAK8caTopSubjetPhi_JetSubCalc;
   //vector<double>  *theJetAK8caTopSubjetPt_JetSubCalc;
   vector<double>  *theJetAK8caTopTopMass_JetSubCalc;

   //vector<double>  *theJetCA15Energy_JetSubCalc;
   //vector<double>  *theJetCA15Eta_JetSubCalc;
   //vector<double>  *theJetCA15Phi_JetSubCalc;
   //vector<double>  *theJetCA15Pt_JetSubCalc;
   //vector<double>  *theJetCA15Mass_JetSubCalc;
   //vector<double>  *theJetCA15NjettinessTau1_JetSubCalc;
   //vector<double>  *theJetCA15NjettinessTau2_JetSubCalc;
   //vector<double>  *theJetCA15NjettinessTau3_JetSubCalc;
   //vector<double>  *theJetCA15SoftDropMass_JetSubCalc;

////////////////////////////////////////////////////////////////////////////
   vector<double>  *pfCombinedInclusiveSecondaryVertexV2BJetTags_BTagSFCalc;
   vector<double>  *pfCombinedSecondaryVertexV2BJetTags_BTagSFCalc;
   vector<double>  *pfCombinedMVABJetTags_BTagSFCalc;
   vector<double>  *pfJetBProbabilityBJetTags_BTagSFCalc;
   vector<double>  *pfJetProbabilityBJetTags_BTagSFCalc;
   vector<double>  *pfSimpleSecondaryVertexHighEffBJetTags_BTagSFCalc;
   vector<double>  *pfSimpleSecondaryVertexHighPurBJetTags_BTagSFCalc;
   vector<double>  *pfTrackCountingHighEffBJetTags_BTagSFCalc;
   vector<double>  *pfTrackCountingHighPurBJetTags_BTagSFCalc;

////////////////////////////////////////////////////////////////////////////
   //Int_t           nBJets_CATopoCalc;
//   Int_t           nJets_CATopoCalc;
   //Double_t        CAMindrBMass_CATopoCalc;
   //Double_t        bestTopMasslnub_CATopoCalc;
   //Double_t        minDRCAtoB_CATopoCalc;
   //Double_t        tPrimeMassBestTop_CATopoCalc;
   //Double_t        tPrimeMass_CATopoCalc;
   //vector<double>  *bJetEta_CATopoCalc;
   //vector<double>  *bJetPhi_CATopoCalc;
   //vector<double>  *bJetPt_CATopoCalc;

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
   Int_t           dataE_singleLepCalc;
   Int_t           dataM_singleLepCalc;
   Int_t           nPV_singleLepCalc;
   Double_t        MCWeight_singleLepCalc;
   vector<double>  *evtWeightsMC_singleLepCalc;

//HLT information
   vector<int>     *viSelMCTriggersEl_singleLepCalc;//passbits; 1 = pass, 0 = fail.
   vector<int>     *viSelMCTriggersMu_singleLepCalc;//MC has triggers appropriate for MC; 
   //vector<int>     *viSelPrescalesEl_singleLepCalc;
   //vector<int>     *viSelPrescalesMu_singleLepCalc;
   vector<int>     *viSelTriggersEl_singleLepCalc;//triggers appropriate for data.
   vector<int>     *viSelTriggersMu_singleLepCalc;
   vector<string>  *electron_hltfilters_singleLepCalc;
   vector<string>  *muon_hltfilters_singleLepCalc;
   vector<string>  *vsSelMCTriggersEl_singleLepCalc;//HLT names.
   vector<string>  *vsSelMCTriggersMu_singleLepCalc;
   vector<string>  *vsSelTriggersEl_singleLepCalc;
   vector<string>  *vsSelTriggersMu_singleLepCalc;

   vector<double>  *elEnergy_singleLepCalc;
   vector<double>  *elEta_singleLepCalc;
   vector<double>  *elPhi_singleLepCalc;
   vector<double>  *elPt_singleLepCalc;
   vector<int>     *elChargeConsistent_singleLepCalc;
   vector<int>     *elCharge_singleLepCalc;
   vector<int>     *elIDLevel25ns_singleLepCalc;
   vector<int>     *elIDLevel50ns_singleLepCalc;
   vector<int>     *elIsEBEE_singleLepCalc;
   vector<int>     *elMatched_singleLepCalc;
   vector<int>     *elMother_id_singleLepCalc;
   vector<int>     *elMother_status_singleLepCalc;
   vector<int>     *elNotConversion_singleLepCalc;
   vector<int>     *elNumberOfMothers_singleLepCalc;
   vector<int>     *elPdgId_singleLepCalc;
   vector<int>     *elStatus_singleLepCalc;
   vector<int>     *electron_1_hltmatched_singleLepCalc;
   vector<double>  *elAEff_singleLepCalc;
   vector<double>  *elChIso_singleLepCalc;
   vector<double>  *elDxy_singleLepCalc;
   vector<double>  *elGen_Reco_dr_singleLepCalc;
   vector<double>  *elMVAValue_singleLepCalc;
   vector<double>  *elMatchedEnergy_singleLepCalc;
   vector<double>  *elMatchedEta_singleLepCalc;
   vector<double>  *elMatchedPhi_singleLepCalc;
   vector<double>  *elMatchedPt_singleLepCalc;
   vector<double>  *elMiniIso_singleLepCalc;
   vector<double>  *elMother_energy_singleLepCalc;
   vector<double>  *elMother_eta_singleLepCalc;
   vector<double>  *elMother_phi_singleLepCalc;
   vector<double>  *elMother_pt_singleLepCalc;
   vector<double>  *elNhIso_singleLepCalc;
   vector<double>  *elPhIso_singleLepCalc;
   vector<double>  *elRhoIso_singleLepCalc;
   vector<double>  *elSihih_singleLepCalc;
   vector<double>  *elDeta_singleLepCalc;
   vector<double>  *elDphi_singleLepCalc;
   vector<double>  *elHoE_singleLepCalc;
   vector<double>  *elRelIso_singleLepCalc; //I'm guessing this is reliso with effective area. need to check. 
   vector<double>  *elOoemoop_singleLepCalc;
   vector<double>  *elD0_singleLepCalc;
   vector<double>  *elDZ_singleLepCalc;
   vector<int>     *elMHits_singleLepCalc;
   vector<int>     *elVtxFitConv_singleLepCalc;

   vector<double>  *muEnergy_singleLepCalc;
   vector<double>  *muEta_singleLepCalc;
   vector<double>  *muPhi_singleLepCalc;
   vector<double>  *muPt_singleLepCalc;
   vector<int>     *muCharge_singleLepCalc;
   vector<int>     *muGlobal_singleLepCalc;
   vector<int>     *muIsLoose_singleLepCalc;
   vector<int>     *muIsMedium_singleLepCalc;
   vector<int>     *muIsTight_singleLepCalc;
   vector<int>     *muMatched_singleLepCalc;
   vector<int>     *muMother_id_singleLepCalc;
   vector<int>     *muMother_status_singleLepCalc;
   vector<int>     *muNMatchedStations_singleLepCalc;
   vector<int>     *muNTrackerLayers_singleLepCalc;
   vector<int>     *muNValMuHits_singleLepCalc;
   vector<int>     *muNValPixelHits_singleLepCalc;
   vector<int>     *muNumberOfMothers_singleLepCalc;
   vector<int>     *muPdgId_singleLepCalc;
   vector<int>     *muStatus_singleLepCalc;
   vector<int>     *muon_1_hltmatched_singleLepCalc;
   vector<double>  *muChIso_singleLepCalc;
   vector<double>  *muChi2_singleLepCalc;
   vector<double>  *muDxy_singleLepCalc;
   vector<double>  *muDz_singleLepCalc;
   vector<double>  *muGIso_singleLepCalc;
   vector<double>  *muGen_Reco_dr_singleLepCalc;
   vector<double>  *muMatchedEnergy_singleLepCalc;
   vector<double>  *muMatchedEta_singleLepCalc;
   vector<double>  *muMatchedPhi_singleLepCalc;
   vector<double>  *muMatchedPt_singleLepCalc;
   vector<double>  *muMiniIso_singleLepCalc;
   vector<double>  *muMother_energy_singleLepCalc;
   vector<double>  *muMother_eta_singleLepCalc;
   vector<double>  *muMother_phi_singleLepCalc;
   vector<double>  *muMother_pt_singleLepCalc;
   vector<double>  *muNhIso_singleLepCalc;
   vector<double>  *muPuIso_singleLepCalc;
   vector<double>  *muRelIso_singleLepCalc;

   Double_t        corr_met_singleLepCalc;
   Double_t        corr_met_phi_singleLepCalc;
   Double_t        met_singleLepCalc;
   Double_t        met_phi_singleLepCalc;

   Double_t        AK4HT_singleLepCalc;

   vector<double>  *AK4JetEnergy_singleLepCalc;
   vector<double>  *AK4JetEta_singleLepCalc;
   vector<double>  *AK4JetPhi_singleLepCalc;
   vector<double>  *AK4JetPt_singleLepCalc;
   vector<int>     *AK4JetBTag_singleLepCalc; //a boolean pass bit = output of BaseEventSelector.cc::isJetTagged w/ applySF = true.
   vector<int>     *AK4JetFlav_singleLepCalc; //I don't know what this is. It's probably a mamber of PAT jets called partonFlavour
   vector<double>  *AK4JetBDisc_singleLepCalc; //=bDiscriminator( "pfCombinedInclusiveSecondaryVertexV2BJetTags")

   vector<double>  *AK8JetEnergy_singleLepCalc;
   vector<double>  *AK8JetEta_singleLepCalc;
   vector<double>  *AK8JetPhi_singleLepCalc;
   vector<double>  *AK8JetPt_singleLepCalc;
   vector<double>  *AK8JetCSV_singleLepCalc;

   Int_t           genTDLID_singleLepCalc;
   Double_t        genTDLEnergy_singleLepCalc;
   Double_t        genTDLEta_singleLepCalc;
   Double_t        genTDLPhi_singleLepCalc;
   Double_t        genTDLPt_singleLepCalc;

   vector<int>     *genID_singleLepCalc;
   vector<double>  *genEnergy_singleLepCalc;
   vector<double>  *genEta_singleLepCalc;
   vector<double>  *genPhi_singleLepCalc;
   vector<double>  *genPt_singleLepCalc;
   vector<int>     *genIndex_singleLepCalc;
   vector<int>     *genStatus_singleLepCalc;
   vector<int>     *genMotherID_singleLepCalc;
   vector<int>     *genMotherIndex_singleLepCalc;

   vector<int>     *genBSLID_singleLepCalc;
   vector<double>  *genBSLEnergy_singleLepCalc;
   vector<double>  *genBSLEta_singleLepCalc;
   vector<double>  *genBSLPhi_singleLepCalc;
   vector<double>  *genBSLPt_singleLepCalc;

   vector<double>  *genJetEnergy_singleLepCalc;
   vector<double>  *genJetEta_singleLepCalc;
   vector<double>  *genJetPhi_singleLepCalc;
   vector<double>  *genJetPt_singleLepCalc;


////////////////////////////////////////////////////////////////////////////
   Bool_t          isBWBW_TpTpCalc;
   Bool_t          isTHBW_TpTpCalc;
   Bool_t          isTHTH_TpTpCalc;
   Bool_t          isTZBW_TpTpCalc;
   Bool_t          isTZTH_TpTpCalc;
   Bool_t          isTZTZ_TpTpCalc;

   vector<int>     *tPrimeID_TpTpCalc;
   vector<int>     *tPrimeNDaughters_TpTpCalc;
   vector<int>     *tPrimeStatus_TpTpCalc;
   vector<double>  *tPrimeEnergy_TpTpCalc;
   vector<double>  *tPrimeEta_TpTpCalc;
   vector<double>  *tPrimeMass_TpTpCalc;
   vector<double>  *tPrimePhi_TpTpCalc;
   vector<double>  *tPrimePt_TpTpCalc;

   vector<int>     *bosonID_TpTpCalc;
   vector<double>  *bosonEnergy_TpTpCalc;
   vector<double>  *bosonEta_TpTpCalc;
   vector<double>  *bosonPhi_TpTpCalc;
   vector<double>  *bosonPt_TpTpCalc;

   vector<int>     *quarkID_TpTpCalc;
   vector<double>  *quarkEnergy_TpTpCalc;
   vector<double>  *quarkEta_TpTpCalc;
   vector<double>  *quarkPhi_TpTpCalc;
   vector<double>  *quarkPt_TpTpCalc;

   Int_t           NLeptonDecays_TpTpCalc;
   vector<int>     *LeptonID_TpTpCalc;
   vector<int>     *LeptonParentID_TpTpCalc;
   vector<double>  *LeptonEnergy_TpTpCalc;
   vector<double>  *LeptonEta_TpTpCalc;
   vector<double>  *LeptonPhi_TpTpCalc;
   vector<double>  *LeptonPt_TpTpCalc;


vector<bool> *theJetAK8SDTau32Tag3_JetSubCalc;
vector<double> *topPt_TTbarMassCalc;
vector<double> *WdecayEnergy_TpTpCalc;
vector<bool> *theJetAK8SDTau32Tag10_JetSubCalc;
vector<double> *ZdecayPt_TpTpCalc;
vector<double> *topPhi_TTbarMassCalc;
Double_t metnohf_singleLepCalc;
vector<double> *allTopsEnergy_TTbarMassCalc;
Double_t metnohf_phi_singleLepCalc;
vector<int> *ZdecayID_TpTpCalc;
vector<double> *elDPhiSCTkAtVtx_singleLepCalc;
vector<bool> *theJetAK8SDTau32Tag0p3_JetSubCalc;
Int_t nPileupInteractions_singleLepCalc;
vector<double> *bPrimePhi_TpTpCalc;
vector<double> *WdecayPt_TpTpCalc;
vector<int> *allTopsID_TTbarMassCalc;
vector<int> *theJetBTagLoose_JetSubCalc;
vector<double> *theJetMuonEFrac_JetSubCalc;
vector<double> *elDR03TkSumPt_singleLepCalc;
Bool_t isBZTW_TpTpCalc;
vector<double> *allTopsPt_TTbarMassCalc;
vector<int> *bPrimeID_TpTpCalc;
vector<bool> *theJetAK8SDTau32BTag10_JetSubCalc;
vector<double> *bPrimeMass_TpTpCalc;
Double_t corr_metnohf_phi_singleLepCalc;
vector<double> *HdecayEta_TpTpCalc;
vector<double> *HdecayPt_TpTpCalc;
vector<double> *allTopsEta_TTbarMassCalc;
vector<double> *ZdecayPhi_TpTpCalc;
vector<bool> *theJetAK8SDTau32Tag0p1_JetSubCalc;
vector<double> *topMass_TTbarMassCalc;
vector<double> *elMVATrigValue_singleLepCalc;
vector<double> *WdecayPhi_TpTpCalc;
vector<double> *bPrimePt_TpTpCalc;
vector<double> *elPhiVtx_singleLepCalc;
vector<double> *HdecayEnergy_TpTpCalc;
vector<bool> *theJetAK8SDTau32Tag1_JetSubCalc;
vector<double> *topEnergy_TTbarMassCalc;
vector<int> *LHEWeightids_singleLepCalc;
Double_t corr_metnohf_singleLepCalc;
vector<bool> *theJetAK8SDTau32BTag3_JetSubCalc;
vector<double> *ZdecayEta_TpTpCalc;
Int_t nLooseElectrons_CommonCalc;
vector<bool> *theJetAK8SDTau32BTag0p3_JetSubCalc;
vector<double> *elDEtaSCTkAtVtx_singleLepCalc;
vector<double> *elEcalPFClusterIso_singleLepCalc;
vector<bool> *theJetAK8SDTau32BTag1_JetSubCalc;
vector<int> *WdecayID_TpTpCalc;
vector<double> *elHcalPFClusterIso_singleLepCalc;
vector<double> *WdecayEta_TpTpCalc;
vector<double> *HdecayPhi_TpTpCalc;
vector<int> *topID_TTbarMassCalc;
vector<int> *WdecayIndex_TpTpCalc;
vector<int> *allTopsStatus_TTbarMassCalc;
vector<int> *bPrimeNDaughters_TpTpCalc;
Int_t nTrueInteractions_singleLepCalc;
vector<double> *LHEWeights_singleLepCalc;
vector<double> *elEtaVtx_singleLepCalc;
Double_t ttbarMass_TTbarMassCalc;
vector<bool> *theJetAK8SDTau32BTag0p1_JetSubCalc;
vector<double> *allTopsPhi_TTbarMassCalc;
vector<double> *topEta_TTbarMassCalc;
Bool_t isTWTW_TpTpCalc;
Bool_t isBHBH_TpTpCalc;
Bool_t isBHTW_TpTpCalc;
Bool_t isBZBZ_TpTpCalc;
Bool_t isBZBH_TpTpCalc;
vector<int> *bPrimeStatus_TpTpCalc;
vector<double> *ZdecayEnergy_TpTpCalc;
vector<int> *HdecayID_TpTpCalc;
vector<int> *HdecayIndex_TpTpCalc;
vector<int> *ZdecayIndex_TpTpCalc;
vector<double> *bPrimeEnergy_TpTpCalc;
vector<double> *bPrimeEta_TpTpCalc;

   // List of branches
   TBranch        *b_isBHBH_TpTpCalc;   //!
   TBranch        *b_isBHTW_TpTpCalc;   //!
   TBranch        *b_isBWBW_TpTpCalc;   //!
   TBranch        *b_isBZBH_TpTpCalc;   //!
   TBranch        *b_isBZBZ_TpTpCalc;   //!
   TBranch        *b_isBZTW_TpTpCalc;   //!
   TBranch        *b_isTHBW_TpTpCalc;   //!
   TBranch        *b_isTHTH_TpTpCalc;   //!
   TBranch        *b_isTWTW_TpTpCalc;   //!
   TBranch        *b_isTZBW_TpTpCalc;   //!
   TBranch        *b_isTZTH_TpTpCalc;   //!
   TBranch        *b_isTZTZ_TpTpCalc;   //!
   TBranch        *b_NLeptonDecays_TpTpCalc;   //!
   TBranch        *b_dataE_singleLepCalc;   //!
   TBranch        *b_dataM_singleLepCalc;   //!
   TBranch        *b_event_CommonCalc;   //!
   TBranch        *b_genTDLID_singleLepCalc;   //!
   TBranch        *b_lumi_CommonCalc;   //!
   TBranch        *b_nAllJets_CommonCalc;   //!
   TBranch        *b_nLooseElectrons_CommonCalc;   //!
   TBranch        *b_nLooseMuons_CommonCalc;   //!
   TBranch        *b_nPV_singleLepCalc;   //!
   TBranch        *b_nPileupInteractions_singleLepCalc;   //!
   TBranch        *b_nSelBtagJets_CommonCalc;   //!
   TBranch        *b_nSelElectrons_CommonCalc;   //!
   TBranch        *b_nSelJets_CommonCalc;   //!
   TBranch        *b_nSelMuons_CommonCalc;   //!
   TBranch        *b_nTrueInteractions_singleLepCalc;   //!
   TBranch        *b_run_CommonCalc;   //!
   TBranch        *b_AK4HT_singleLepCalc;   //!
   TBranch        *b_MCWeight_singleLepCalc;   //!
   TBranch        *b_corr_met_phi_singleLepCalc;   //!
   TBranch        *b_corr_met_singleLepCalc;   //!
   TBranch        *b_corr_metnohf_phi_singleLepCalc;   //!
   TBranch        *b_corr_metnohf_singleLepCalc;   //!
   TBranch        *b_genTDLEnergy_singleLepCalc;   //!
   TBranch        *b_genTDLEta_singleLepCalc;   //!
   TBranch        *b_genTDLPhi_singleLepCalc;   //!
   TBranch        *b_genTDLPt_singleLepCalc;   //!
   TBranch        *b_met_phi_singleLepCalc;   //!
   TBranch        *b_met_singleLepCalc;   //!
   TBranch        *b_metnohf_phi_singleLepCalc;   //!
   TBranch        *b_metnohf_singleLepCalc;   //!
   TBranch        *b_theJetHT_JetSubCalc;   //!
   TBranch        *b_theJetLeadPt_JetSubCalc;   //!
   TBranch        *b_theJetSubLeadPt_JetSubCalc;   //!
   TBranch        *b_ttbarMass_TTbarMassCalc;   //!
   TBranch        *b_theJetAK8PrunedTau21Tag_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDTau32BTag0p1_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDTau32BTag0p3_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDTau32BTag10_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDTau32BTag1_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDTau32BTag3_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDTau32Tag0p1_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDTau32Tag0p3_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDTau32Tag10_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDTau32Tag1_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDTau32Tag3_JetSubCalc;   //!
   TBranch        *b_AK4JetBTag_singleLepCalc;   //!
   TBranch        *b_AK4JetFlav_singleLepCalc;   //!
   TBranch        *b_HdecayID_TpTpCalc;   //!
   TBranch        *b_HdecayIndex_TpTpCalc;   //!
   TBranch        *b_LHEWeightids_singleLepCalc;   //!
   TBranch        *b_LeptonID_TpTpCalc;   //!
   TBranch        *b_LeptonParentID_TpTpCalc;   //!
   TBranch        *b_WdecayID_TpTpCalc;   //!
   TBranch        *b_WdecayIndex_TpTpCalc;   //!
   TBranch        *b_ZdecayID_TpTpCalc;   //!
   TBranch        *b_ZdecayIndex_TpTpCalc;   //!
   TBranch        *b_allTopsID_TTbarMassCalc;   //!
   TBranch        *b_allTopsStatus_TTbarMassCalc;   //!
   TBranch        *b_bPrimeID_TpTpCalc;   //!
   TBranch        *b_bPrimeNDaughters_TpTpCalc;   //!
   TBranch        *b_bPrimeStatus_TpTpCalc;   //!
   TBranch        *b_bosonID_TpTpCalc;   //!
   TBranch        *b_elChargeConsistent_singleLepCalc;   //!
   TBranch        *b_elCharge_singleLepCalc;   //!
   TBranch        *b_elIDLevel25ns_singleLepCalc;   //!
   TBranch        *b_elIDLevel50ns_singleLepCalc;   //!
   TBranch        *b_elIsEBEE_singleLepCalc;   //!
   TBranch        *b_elMHits_singleLepCalc;   //!
   TBranch        *b_elMatched_singleLepCalc;   //!
   TBranch        *b_elMother_id_singleLepCalc;   //!
   TBranch        *b_elMother_status_singleLepCalc;   //!
   TBranch        *b_elNotConversion_singleLepCalc;   //!
   TBranch        *b_elNumberOfMothers_singleLepCalc;   //!
   TBranch        *b_elPdgId_singleLepCalc;   //!
   TBranch        *b_elStatus_singleLepCalc;   //!
   TBranch        *b_elVtxFitConv_singleLepCalc;   //!
   TBranch        *b_electron_1_hltmatched_singleLepCalc;   //!
   TBranch        *b_genBSLID_singleLepCalc;   //!
   TBranch        *b_genID_singleLepCalc;   //!
   TBranch        *b_genIndex_singleLepCalc;   //!
   TBranch        *b_genMotherID_singleLepCalc;   //!
   TBranch        *b_genMotherIndex_singleLepCalc;   //!
   TBranch        *b_genStatus_singleLepCalc;   //!
   TBranch        *b_muCharge_singleLepCalc;   //!
   TBranch        *b_muGlobal_singleLepCalc;   //!
   TBranch        *b_muIsLoose_singleLepCalc;   //!
   TBranch        *b_muIsMedium_singleLepCalc;   //!
   TBranch        *b_muIsTight_singleLepCalc;   //!
   TBranch        *b_muMatched_singleLepCalc;   //!
   TBranch        *b_muMother_id_singleLepCalc;   //!
   TBranch        *b_muMother_status_singleLepCalc;   //!
   TBranch        *b_muNMatchedStations_singleLepCalc;   //!
   TBranch        *b_muNTrackerLayers_singleLepCalc;   //!
   TBranch        *b_muNValMuHits_singleLepCalc;   //!
   TBranch        *b_muNValPixelHits_singleLepCalc;   //!
   TBranch        *b_muNumberOfMothers_singleLepCalc;   //!
   TBranch        *b_muPdgId_singleLepCalc;   //!
   TBranch        *b_muStatus_singleLepCalc;   //!
   TBranch        *b_muon_1_hltmatched_singleLepCalc;   //!
   TBranch        *b_quarkID_TpTpCalc;   //!
   TBranch        *b_tPrimeID_TpTpCalc;   //!
   TBranch        *b_tPrimeNDaughters_TpTpCalc;   //!
   TBranch        *b_tPrimeStatus_TpTpCalc;   //!
   TBranch        *b_theJetAK8SDSubjetIndex_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDSubjetNCSVL_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDSubjetNCSVM_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDSubjetSize_JetSubCalc;   //!
   TBranch        *b_theJetAK8caTopnSubJets_JetSubCalc;   //!
   TBranch        *b_theJetAK8nDaughters_JetSubCalc;   //!
   TBranch        *b_theJetBTagLoose_JetSubCalc;   //!
   TBranch        *b_theJetBTag_JetSubCalc;   //!
   TBranch        *b_theJetFlav_JetSubCalc;   //!
   TBranch        *b_theJetnDaughters_JetSubCalc;   //!
   TBranch        *b_topID_TTbarMassCalc;   //!
   TBranch        *b_viSelMCTriggersEl_singleLepCalc;   //!
   TBranch        *b_viSelMCTriggersMu_singleLepCalc;   //!
   TBranch        *b_viSelTriggersEl_singleLepCalc;   //!
   TBranch        *b_viSelTriggersMu_singleLepCalc;   //!
   TBranch        *b_AK4JetBDisc_singleLepCalc;   //!
   TBranch        *b_AK4JetEnergy_singleLepCalc;   //!
   TBranch        *b_AK4JetEta_singleLepCalc;   //!
   TBranch        *b_AK4JetPhi_singleLepCalc;   //!
   TBranch        *b_AK4JetPt_singleLepCalc;   //!
   TBranch        *b_AK8JetCSV_singleLepCalc;   //!
   TBranch        *b_AK8JetEnergy_singleLepCalc;   //!
   TBranch        *b_AK8JetEta_singleLepCalc;   //!
   TBranch        *b_AK8JetPhi_singleLepCalc;   //!
   TBranch        *b_AK8JetPt_singleLepCalc;   //!
   TBranch        *b_HdecayEnergy_TpTpCalc;   //!
   TBranch        *b_HdecayEta_TpTpCalc;   //!
   TBranch        *b_HdecayPhi_TpTpCalc;   //!
   TBranch        *b_HdecayPt_TpTpCalc;   //!
   TBranch        *b_LHEWeights_singleLepCalc;   //!
   TBranch        *b_LeptonEnergy_TpTpCalc;   //!
   TBranch        *b_LeptonEta_TpTpCalc;   //!
   TBranch        *b_LeptonPhi_TpTpCalc;   //!
   TBranch        *b_LeptonPt_TpTpCalc;   //!
   TBranch        *b_WdecayEnergy_TpTpCalc;   //!
   TBranch        *b_WdecayEta_TpTpCalc;   //!
   TBranch        *b_WdecayPhi_TpTpCalc;   //!
   TBranch        *b_WdecayPt_TpTpCalc;   //!
   TBranch        *b_ZdecayEnergy_TpTpCalc;   //!
   TBranch        *b_ZdecayEta_TpTpCalc;   //!
   TBranch        *b_ZdecayPhi_TpTpCalc;   //!
   TBranch        *b_ZdecayPt_TpTpCalc;   //!
   TBranch        *b_allTopsEnergy_TTbarMassCalc;   //!
   TBranch        *b_allTopsEta_TTbarMassCalc;   //!
   TBranch        *b_allTopsPhi_TTbarMassCalc;   //!
   TBranch        *b_allTopsPt_TTbarMassCalc;   //!
   TBranch        *b_bPrimeEnergy_TpTpCalc;   //!
   TBranch        *b_bPrimeEta_TpTpCalc;   //!
   TBranch        *b_bPrimeMass_TpTpCalc;   //!
   TBranch        *b_bPrimePhi_TpTpCalc;   //!
   TBranch        *b_bPrimePt_TpTpCalc;   //!
   TBranch        *b_bosonEnergy_TpTpCalc;   //!
   TBranch        *b_bosonEta_TpTpCalc;   //!
   TBranch        *b_bosonPhi_TpTpCalc;   //!
   TBranch        *b_bosonPt_TpTpCalc;   //!
   TBranch        *b_elAEff_singleLepCalc;   //!
   TBranch        *b_elChIso_singleLepCalc;   //!
   TBranch        *b_elD0_singleLepCalc;   //!
   TBranch        *b_elDEtaSCTkAtVtx_singleLepCalc;   //!
   TBranch        *b_elDPhiSCTkAtVtx_singleLepCalc;   //!
   TBranch        *b_elDR03TkSumPt_singleLepCalc;   //!
   TBranch        *b_elDZ_singleLepCalc;   //!
   TBranch        *b_elDeta_singleLepCalc;   //!
   TBranch        *b_elDphi_singleLepCalc;   //!
   TBranch        *b_elDxy_singleLepCalc;   //!
   TBranch        *b_elEcalPFClusterIso_singleLepCalc;   //!
   TBranch        *b_elEnergy_singleLepCalc;   //!
   TBranch        *b_elEtaVtx_singleLepCalc;   //!
   TBranch        *b_elEta_singleLepCalc;   //!
   TBranch        *b_elGen_Reco_dr_singleLepCalc;   //!
   TBranch        *b_elHcalPFClusterIso_singleLepCalc;   //!
   TBranch        *b_elHoE_singleLepCalc;   //!
   TBranch        *b_elMVATrigValue_singleLepCalc;   //!
   TBranch        *b_elMVAValue_singleLepCalc;   //!
   TBranch        *b_elMatchedEnergy_singleLepCalc;   //!
   TBranch        *b_elMatchedEta_singleLepCalc;   //!
   TBranch        *b_elMatchedPhi_singleLepCalc;   //!
   TBranch        *b_elMatchedPt_singleLepCalc;   //!
   TBranch        *b_elMiniIso_singleLepCalc;   //!
   TBranch        *b_elMother_energy_singleLepCalc;   //!
   TBranch        *b_elMother_eta_singleLepCalc;   //!
   TBranch        *b_elMother_phi_singleLepCalc;   //!
   TBranch        *b_elMother_pt_singleLepCalc;   //!
   TBranch        *b_elNhIso_singleLepCalc;   //!
   TBranch        *b_elOoemoop_singleLepCalc;   //!
   TBranch        *b_elPhIso_singleLepCalc;   //!
   TBranch        *b_elPhiVtx_singleLepCalc;   //!
   TBranch        *b_elPhi_singleLepCalc;   //!
   TBranch        *b_elPt_singleLepCalc;   //!
   TBranch        *b_elRelIso_singleLepCalc;   //!
   TBranch        *b_elRhoIso_singleLepCalc;   //!
   TBranch        *b_elSihih_singleLepCalc;   //!
   TBranch        *b_evtWeightsMC_singleLepCalc;   //!
   TBranch        *b_genBSLEnergy_singleLepCalc;   //!
   TBranch        *b_genBSLEta_singleLepCalc;   //!
   TBranch        *b_genBSLPhi_singleLepCalc;   //!
   TBranch        *b_genBSLPt_singleLepCalc;   //!
   TBranch        *b_genEnergy_singleLepCalc;   //!
   TBranch        *b_genEta_singleLepCalc;   //!
   TBranch        *b_genJetEnergy_singleLepCalc;   //!
   TBranch        *b_genJetEta_singleLepCalc;   //!
   TBranch        *b_genJetPhi_singleLepCalc;   //!
   TBranch        *b_genJetPt_singleLepCalc;   //!
   TBranch        *b_genPhi_singleLepCalc;   //!
   TBranch        *b_genPt_singleLepCalc;   //!
   TBranch        *b_muChIso_singleLepCalc;   //!
   TBranch        *b_muChi2_singleLepCalc;   //!
   TBranch        *b_muDxy_singleLepCalc;   //!
   TBranch        *b_muDz_singleLepCalc;   //!
   TBranch        *b_muEnergy_singleLepCalc;   //!
   TBranch        *b_muEta_singleLepCalc;   //!
   TBranch        *b_muGIso_singleLepCalc;   //!
   TBranch        *b_muGen_Reco_dr_singleLepCalc;   //!
   TBranch        *b_muMatchedEnergy_singleLepCalc;   //!
   TBranch        *b_muMatchedEta_singleLepCalc;   //!
   TBranch        *b_muMatchedPhi_singleLepCalc;   //!
   TBranch        *b_muMatchedPt_singleLepCalc;   //!
   TBranch        *b_muMiniIso_singleLepCalc;   //!
   TBranch        *b_muMother_energy_singleLepCalc;   //!
   TBranch        *b_muMother_eta_singleLepCalc;   //!
   TBranch        *b_muMother_phi_singleLepCalc;   //!
   TBranch        *b_muMother_pt_singleLepCalc;   //!
   TBranch        *b_muNhIso_singleLepCalc;   //!
   TBranch        *b_muPhi_singleLepCalc;   //!
   TBranch        *b_muPt_singleLepCalc;   //!
   TBranch        *b_muPuIso_singleLepCalc;   //!
   TBranch        *b_muRelIso_singleLepCalc;   //!
   TBranch        *b_pfCombinedInclusiveSecondaryVertexV2BJetTags_BTagSFCalc;   //!
   TBranch        *b_pfCombinedMVABJetTags_BTagSFCalc;   //!
   TBranch        *b_pfCombinedSecondaryVertexV2BJetTags_BTagSFCalc;   //!
   TBranch        *b_pfJetBProbabilityBJetTags_BTagSFCalc;   //!
   TBranch        *b_pfJetProbabilityBJetTags_BTagSFCalc;   //!
   TBranch        *b_pfSimpleSecondaryVertexHighEffBJetTags_BTagSFCalc;   //!
   TBranch        *b_pfSimpleSecondaryVertexHighPurBJetTags_BTagSFCalc;   //!
   TBranch        *b_pfTrackCountingHighEffBJetTags_BTagSFCalc;   //!
   TBranch        *b_pfTrackCountingHighPurBJetTags_BTagSFCalc;   //!
   TBranch        *b_quarkEnergy_TpTpCalc;   //!
   TBranch        *b_quarkEta_TpTpCalc;   //!
   TBranch        *b_quarkPhi_TpTpCalc;   //!
   TBranch        *b_quarkPt_TpTpCalc;   //!
   TBranch        *b_tPrimeEnergy_TpTpCalc;   //!
   TBranch        *b_tPrimeEta_TpTpCalc;   //!
   TBranch        *b_tPrimeMass_TpTpCalc;   //!
   TBranch        *b_tPrimePhi_TpTpCalc;   //!
   TBranch        *b_tPrimePt_TpTpCalc;   //!
   TBranch        *b_theJetAK8CEmEFrac_JetSubCalc;   //!
   TBranch        *b_theJetAK8CEmEnergy_JetSubCalc;   //!
   TBranch        *b_theJetAK8CHadEFrac_JetSubCalc;   //!
   TBranch        *b_theJetAK8CHadEnergy_JetSubCalc;   //!
   TBranch        *b_theJetAK8CSV_JetSubCalc;   //!
   TBranch        *b_theJetAK8Energy_JetSubCalc;   //!
   TBranch        *b_theJetAK8Eta_JetSubCalc;   //!
   TBranch        *b_theJetAK8FilteredMass_JetSubCalc;   //!
   TBranch        *b_theJetAK8JetCharge_JetSubCalc;   //!
   TBranch        *b_theJetAK8Mass_JetSubCalc;   //!
   TBranch        *b_theJetAK8NEmEFrac_JetSubCalc;   //!
   TBranch        *b_theJetAK8NEmEnergy_JetSubCalc;   //!
   TBranch        *b_theJetAK8NHadEFrac_JetSubCalc;   //!
   TBranch        *b_theJetAK8NHadEnergy_JetSubCalc;   //!
   TBranch        *b_theJetAK8NjettinessTau1_JetSubCalc;   //!
   TBranch        *b_theJetAK8NjettinessTau2_JetSubCalc;   //!
   TBranch        *b_theJetAK8NjettinessTau3_JetSubCalc;   //!
   TBranch        *b_theJetAK8Phi_JetSubCalc;   //!
   TBranch        *b_theJetAK8PrunedMass_JetSubCalc;   //!
   TBranch        *b_theJetAK8Pt_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDSubjetCSV_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDSubjetDR_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDSubjetEta_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDSubjetMass_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDSubjetPhi_JetSubCalc;   //!
   TBranch        *b_theJetAK8SDSubjetPt_JetSubCalc;   //!
   TBranch        *b_theJetAK8SoftDropMass_JetSubCalc;   //!
   TBranch        *b_theJetAK8TrimmedMass_JetSubCalc;   //!
   TBranch        *b_theJetAK8caTopMinMass_JetSubCalc;   //!
   TBranch        *b_theJetAK8caTopTopMass_JetSubCalc;   //!
   TBranch        *b_theJetCEmEFrac_JetSubCalc;   //!
   TBranch        *b_theJetCEmEnergy_JetSubCalc;   //!
   TBranch        *b_theJetCHadEFrac_JetSubCalc;   //!
   TBranch        *b_theJetCHadEnergy_JetSubCalc;   //!
   TBranch        *b_theJetCSV_JetSubCalc;   //!
   TBranch        *b_theJetEnergy_JetSubCalc;   //!
   TBranch        *b_theJetEta_JetSubCalc;   //!
   TBranch        *b_theJetMuonEFrac_JetSubCalc;   //!
   TBranch        *b_theJetNEmEFrac_JetSubCalc;   //!
   TBranch        *b_theJetNEmEnergy_JetSubCalc;   //!
   TBranch        *b_theJetNHadEFrac_JetSubCalc;   //!
   TBranch        *b_theJetNHadEnergy_JetSubCalc;   //!
   TBranch        *b_theJetPhi_JetSubCalc;   //!
   TBranch        *b_theJetPileupJetId_JetSubCalc;   //!
   TBranch        *b_theJetPt_JetSubCalc;   //!
   TBranch        *b_theJetVtx3DSig_JetSubCalc;   //!
   TBranch        *b_theJetVtx3DVal_JetSubCalc;   //!
   TBranch        *b_theJetVtxMass_JetSubCalc;   //!
   TBranch        *b_theJetVtxNtracks_JetSubCalc;   //!
   TBranch        *b_topEnergy_TTbarMassCalc;   //!
   TBranch        *b_topEta_TTbarMassCalc;   //!
   TBranch        *b_topMass_TTbarMassCalc;   //!
   TBranch        *b_topPhi_TTbarMassCalc;   //!
   TBranch        *b_topPt_TTbarMassCalc;   //!
   TBranch        *b_electron_hltfilters_singleLepCalc;   //!
   TBranch        *b_muon_hltfilters_singleLepCalc;   //!
   TBranch        *b_vsSelMCTriggersEl_singleLepCalc;   //!
   TBranch        *b_vsSelMCTriggersMu_singleLepCalc;   //!
   TBranch        *b_vsSelTriggersEl_singleLepCalc;   //!
   TBranch        *b_vsSelTriggersMu_singleLepCalc;   //!

private:
   bool useJSON;
   //bool useTrigger;
   std::vector<TString> hltNames;          // HLT trigger path names
   typedef std::map<int,std::map<int,bool> > RunLumiFlagHolder;  //define map that holds json list
   RunLumiFlagHolder goodrunlumilist;  // instantiate it
}; //end class

#endif

#ifdef tpmultlepmaincalc_cxx
tpmultlepmaincalc::tpmultlepmaincalc(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
	cout<<"WARNING: This is probably not what you intended; Running the placeholder file"<<endl;
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/uscms/store/user/lpcljm/METnoHFplusHTT/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8/jmh_25nsKeepAll/150922_193607/0000/METnoHFplusHTT_2.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("root://cmsxrootd.fnal.gov///store/user/lpcljm/METnoHFplusHTT/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8/jmh_25nsKeepAll/150922_193607/0000/METnoHFplusHTT_2.root");
         //f = new TFile("/eos/uscms/store/user/lpcljm/METnoHFplusHTT/TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8/jmh_25nsKeepAll/150922_193607/0000/METnoHFplusHTT_2.root");
      }
      f->GetObject("ljmet",tree);

   }
   Init(tree);
}//end simple tpmultlepmaincalc

tpmultlepmaincalc::tpmultlepmaincalc(DMCblock* block){
	TChain* chain = new TChain("thething","");
	chain->SetDebug(chain->GetDebugMax());//lets hope this helps. 
	cout<<"nfiles: "<<block->nfiles<<endl;
	for(int i=0;i<block->nfiles;++i){
		//TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(block->rootFilePaths[i]);
		//cout<<"start for with i="<<i<<" checking"<<block->rootFilePaths[i]<<endl;
		cout<<"Reaching for file "<<block->rootFilePaths[i]; cout.flush();
		if (!fileExists(block->rootFilePaths[i])){ //this is probably not EOS safe xxx HACK
			cout<<"\t\tFile Not Found!"<<endl;
			cout<<endl<<"ERROR! File does not exist "<<block->rootFilePaths[i]<<endl;
			std::terminate();
		}
		//else if(f->IsOpen()){
			//cout<<"ERROR! Cannot access file because it is open "<<block->rootFilePaths[i]<<endl;
		//}
		else{
			//chain->Add((block->rootFilePaths[i] + "/ljmet").c_str());
			//EOS example: TFile* f = TFile::Open("root://cmsxrootd.fnal.gov///store/user/asdf/asdf/asdf/asdf.root") //xxx known to work
			//The following is an attempt to do the above line in an eos safe way. 
			string fname = block->rootFilePaths[i]; //get the path.

			//strip /eos/uscms off the front
			const static string prefix = "/eos/uscms";
			size_t wherefound = fname.find(prefix);
			if(wherefound  != string::npos) //if found
				fname.replace(wherefound,prefix.length(),"");//remove it.
			string chain_command = "root://cmsxrootd.fnal.gov//"+fname + "/ljmet";

			chain->Add(chain_command.c_str());

			cout<<"\t\tgot it."<<endl;
		}//end else.
	}//end for
	dmcblock = block;

	Init((TTree*)chain);

}//end tpmultlepmaincalc for DMCblock

tpmultlepmaincalc::tpmultlepmaincalc(string blockname) : tpmultlepmaincalc(setupDMCblock(blockname,"")){
}

tpmultlepmaincalc::~tpmultlepmaincalc()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tpmultlepmaincalc::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tpmultlepmaincalc::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      
   }
   return centry;
}

void tpmultlepmaincalc::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

	//cout<<"beginning Init()"<<endl;

	//useTrigger = true;
	useJSON = false;

   // Set object pointer
   theJetAK8PrunedTau21Tag_JetSubCalc = 0;
   theJetAK8SDTau32BTag0p1_JetSubCalc = 0;
   theJetAK8SDTau32BTag0p3_JetSubCalc = 0;
   theJetAK8SDTau32BTag10_JetSubCalc = 0;
   theJetAK8SDTau32BTag1_JetSubCalc = 0;
   theJetAK8SDTau32BTag3_JetSubCalc = 0;
   theJetAK8SDTau32Tag0p1_JetSubCalc = 0;
   theJetAK8SDTau32Tag0p3_JetSubCalc = 0;
   theJetAK8SDTau32Tag10_JetSubCalc = 0;
   theJetAK8SDTau32Tag1_JetSubCalc = 0;
   theJetAK8SDTau32Tag3_JetSubCalc = 0;
   AK4JetBTag_singleLepCalc = 0;
   AK4JetFlav_singleLepCalc = 0;
   HdecayID_TpTpCalc = 0;
   HdecayIndex_TpTpCalc = 0;
   LHEWeightids_singleLepCalc = 0;
   LeptonID_TpTpCalc = 0;
   LeptonParentID_TpTpCalc = 0;
   WdecayID_TpTpCalc = 0;
   WdecayIndex_TpTpCalc = 0;
   ZdecayID_TpTpCalc = 0;
   ZdecayIndex_TpTpCalc = 0;
   allTopsID_TTbarMassCalc = 0;
   allTopsStatus_TTbarMassCalc = 0;
   bPrimeID_TpTpCalc = 0;
   bPrimeNDaughters_TpTpCalc = 0;
   bPrimeStatus_TpTpCalc = 0;
   bosonID_TpTpCalc = 0;
   elChargeConsistent_singleLepCalc = 0;
   elCharge_singleLepCalc = 0;
   elIDLevel25ns_singleLepCalc = 0;
   elIDLevel50ns_singleLepCalc = 0;
   elIsEBEE_singleLepCalc = 0;
   elMHits_singleLepCalc = 0;
   elMatched_singleLepCalc = 0;
   elMother_id_singleLepCalc = 0;
   elMother_status_singleLepCalc = 0;
   elNotConversion_singleLepCalc = 0;
   elNumberOfMothers_singleLepCalc = 0;
   elPdgId_singleLepCalc = 0;
   elStatus_singleLepCalc = 0;
   elVtxFitConv_singleLepCalc = 0;
   electron_1_hltmatched_singleLepCalc = 0;
   genBSLID_singleLepCalc = 0;
   genID_singleLepCalc = 0;
   genIndex_singleLepCalc = 0;
   genMotherID_singleLepCalc = 0;
   genMotherIndex_singleLepCalc = 0;
   genStatus_singleLepCalc = 0;
   muCharge_singleLepCalc = 0;
   muGlobal_singleLepCalc = 0;
   muIsLoose_singleLepCalc = 0;
   muIsMedium_singleLepCalc = 0;
   muIsTight_singleLepCalc = 0;
   muMatched_singleLepCalc = 0;
   muMother_id_singleLepCalc = 0;
   muMother_status_singleLepCalc = 0;
   muNMatchedStations_singleLepCalc = 0;
   muNTrackerLayers_singleLepCalc = 0;
   muNValMuHits_singleLepCalc = 0;
   muNValPixelHits_singleLepCalc = 0;
   muNumberOfMothers_singleLepCalc = 0;
   muPdgId_singleLepCalc = 0;
   muStatus_singleLepCalc = 0;
   muon_1_hltmatched_singleLepCalc = 0;
   quarkID_TpTpCalc = 0;
   tPrimeID_TpTpCalc = 0;
   tPrimeNDaughters_TpTpCalc = 0;
   tPrimeStatus_TpTpCalc = 0;
   theJetAK8SDSubjetIndex_JetSubCalc = 0;
   theJetAK8SDSubjetNCSVL_JetSubCalc = 0;
   theJetAK8SDSubjetNCSVM_JetSubCalc = 0;
   theJetAK8SDSubjetSize_JetSubCalc = 0;
   theJetAK8caTopnSubJets_JetSubCalc = 0;
   theJetAK8nDaughters_JetSubCalc = 0;
   theJetBTagLoose_JetSubCalc = 0;
   theJetBTag_JetSubCalc = 0;
   theJetFlav_JetSubCalc = 0;
   theJetnDaughters_JetSubCalc = 0;
   topID_TTbarMassCalc = 0;
   viSelMCTriggersEl_singleLepCalc = 0;
   viSelMCTriggersMu_singleLepCalc = 0;
   viSelTriggersEl_singleLepCalc = 0;
   viSelTriggersMu_singleLepCalc = 0;
   AK4JetBDisc_singleLepCalc = 0;
   AK4JetEnergy_singleLepCalc = 0;
   AK4JetEta_singleLepCalc = 0;
   AK4JetPhi_singleLepCalc = 0;
   AK4JetPt_singleLepCalc = 0;
   AK8JetCSV_singleLepCalc = 0;
   AK8JetEnergy_singleLepCalc = 0;
   AK8JetEta_singleLepCalc = 0;
   AK8JetPhi_singleLepCalc = 0;
   AK8JetPt_singleLepCalc = 0;
   HdecayEnergy_TpTpCalc = 0;
   HdecayEta_TpTpCalc = 0;
   HdecayPhi_TpTpCalc = 0;
   HdecayPt_TpTpCalc = 0;
   LHEWeights_singleLepCalc = 0;
   LeptonEnergy_TpTpCalc = 0;
   LeptonEta_TpTpCalc = 0;
   LeptonPhi_TpTpCalc = 0;
   LeptonPt_TpTpCalc = 0;
   WdecayEnergy_TpTpCalc = 0;
   WdecayEta_TpTpCalc = 0;
   WdecayPhi_TpTpCalc = 0;
   WdecayPt_TpTpCalc = 0;
   ZdecayEnergy_TpTpCalc = 0;
   ZdecayEta_TpTpCalc = 0;
   ZdecayPhi_TpTpCalc = 0;
   ZdecayPt_TpTpCalc = 0;
   allTopsEnergy_TTbarMassCalc = 0;
   allTopsEta_TTbarMassCalc = 0;
   allTopsPhi_TTbarMassCalc = 0;
   allTopsPt_TTbarMassCalc = 0;
   bPrimeEnergy_TpTpCalc = 0;
   bPrimeEta_TpTpCalc = 0;
   bPrimeMass_TpTpCalc = 0;
   bPrimePhi_TpTpCalc = 0;
   bPrimePt_TpTpCalc = 0;
   bosonEnergy_TpTpCalc = 0;
   bosonEta_TpTpCalc = 0;
   bosonPhi_TpTpCalc = 0;
   bosonPt_TpTpCalc = 0;
   elAEff_singleLepCalc = 0;
   elChIso_singleLepCalc = 0;
   elD0_singleLepCalc = 0;
   elDEtaSCTkAtVtx_singleLepCalc = 0;
   elDPhiSCTkAtVtx_singleLepCalc = 0;
   elDR03TkSumPt_singleLepCalc = 0;
   elDZ_singleLepCalc = 0;
   elDeta_singleLepCalc = 0;
   elDphi_singleLepCalc = 0;
   elDxy_singleLepCalc = 0;
   elEcalPFClusterIso_singleLepCalc = 0;
   elEnergy_singleLepCalc = 0;
   elEtaVtx_singleLepCalc = 0;
   elEta_singleLepCalc = 0;
   elGen_Reco_dr_singleLepCalc = 0;
   elHcalPFClusterIso_singleLepCalc = 0;
   elHoE_singleLepCalc = 0;
   elMVATrigValue_singleLepCalc = 0;
   elMVAValue_singleLepCalc = 0;
   elMatchedEnergy_singleLepCalc = 0;
   elMatchedEta_singleLepCalc = 0;
   elMatchedPhi_singleLepCalc = 0;
   elMatchedPt_singleLepCalc = 0;
   elMiniIso_singleLepCalc = 0;
   elMother_energy_singleLepCalc = 0;
   elMother_eta_singleLepCalc = 0;
   elMother_phi_singleLepCalc = 0;
   elMother_pt_singleLepCalc = 0;
   elNhIso_singleLepCalc = 0;
   elOoemoop_singleLepCalc = 0;
   elPhIso_singleLepCalc = 0;
   elPhiVtx_singleLepCalc = 0;
   elPhi_singleLepCalc = 0;
   elPt_singleLepCalc = 0;
   elRelIso_singleLepCalc = 0;
   elRhoIso_singleLepCalc = 0;
   elSihih_singleLepCalc = 0;
   evtWeightsMC_singleLepCalc = 0;
   genBSLEnergy_singleLepCalc = 0;
   genBSLEta_singleLepCalc = 0;
   genBSLPhi_singleLepCalc = 0;
   genBSLPt_singleLepCalc = 0;
   genEnergy_singleLepCalc = 0;
   genEta_singleLepCalc = 0;
   genJetEnergy_singleLepCalc = 0;
   genJetEta_singleLepCalc = 0;
   genJetPhi_singleLepCalc = 0;
   genJetPt_singleLepCalc = 0;
   genPhi_singleLepCalc = 0;
   genPt_singleLepCalc = 0;
   muChIso_singleLepCalc = 0;
   muChi2_singleLepCalc = 0;
   muDxy_singleLepCalc = 0;
   muDz_singleLepCalc = 0;
   muEnergy_singleLepCalc = 0;
   muEta_singleLepCalc = 0;
   muGIso_singleLepCalc = 0;
   muGen_Reco_dr_singleLepCalc = 0;
   muMatchedEnergy_singleLepCalc = 0;
   muMatchedEta_singleLepCalc = 0;
   muMatchedPhi_singleLepCalc = 0;
   muMatchedPt_singleLepCalc = 0;
   muMiniIso_singleLepCalc = 0;
   muMother_energy_singleLepCalc = 0;
   muMother_eta_singleLepCalc = 0;
   muMother_phi_singleLepCalc = 0;
   muMother_pt_singleLepCalc = 0;
   muNhIso_singleLepCalc = 0;
   muPhi_singleLepCalc = 0;
   muPt_singleLepCalc = 0;
   muPuIso_singleLepCalc = 0;
   muRelIso_singleLepCalc = 0;
   pfCombinedInclusiveSecondaryVertexV2BJetTags_BTagSFCalc = 0;
   pfCombinedMVABJetTags_BTagSFCalc = 0;
   pfCombinedSecondaryVertexV2BJetTags_BTagSFCalc = 0;
   pfJetBProbabilityBJetTags_BTagSFCalc = 0;
   pfJetProbabilityBJetTags_BTagSFCalc = 0;
   pfSimpleSecondaryVertexHighEffBJetTags_BTagSFCalc = 0;
   pfSimpleSecondaryVertexHighPurBJetTags_BTagSFCalc = 0;
   pfTrackCountingHighEffBJetTags_BTagSFCalc = 0;
   pfTrackCountingHighPurBJetTags_BTagSFCalc = 0;
   quarkEnergy_TpTpCalc = 0;
   quarkEta_TpTpCalc = 0;
   quarkPhi_TpTpCalc = 0;
   quarkPt_TpTpCalc = 0;
   tPrimeEnergy_TpTpCalc = 0;
   tPrimeEta_TpTpCalc = 0;
   tPrimeMass_TpTpCalc = 0;
   tPrimePhi_TpTpCalc = 0;
   tPrimePt_TpTpCalc = 0;
   theJetAK8CEmEFrac_JetSubCalc = 0;
   theJetAK8CEmEnergy_JetSubCalc = 0;
   theJetAK8CHadEFrac_JetSubCalc = 0;
   theJetAK8CHadEnergy_JetSubCalc = 0;
   theJetAK8CSV_JetSubCalc = 0;
   theJetAK8Energy_JetSubCalc = 0;
   theJetAK8Eta_JetSubCalc = 0;
   theJetAK8FilteredMass_JetSubCalc = 0;
   theJetAK8JetCharge_JetSubCalc = 0;
   theJetAK8Mass_JetSubCalc = 0;
   theJetAK8NEmEFrac_JetSubCalc = 0;
   theJetAK8NEmEnergy_JetSubCalc = 0;
   theJetAK8NHadEFrac_JetSubCalc = 0;
   theJetAK8NHadEnergy_JetSubCalc = 0;
   theJetAK8NjettinessTau1_JetSubCalc = 0;
   theJetAK8NjettinessTau2_JetSubCalc = 0;
   theJetAK8NjettinessTau3_JetSubCalc = 0;
   theJetAK8Phi_JetSubCalc = 0;
   theJetAK8PrunedMass_JetSubCalc = 0;
   theJetAK8Pt_JetSubCalc = 0;
   theJetAK8SDSubjetCSV_JetSubCalc = 0;
   theJetAK8SDSubjetDR_JetSubCalc = 0;
   theJetAK8SDSubjetEta_JetSubCalc = 0;
   theJetAK8SDSubjetMass_JetSubCalc = 0;
   theJetAK8SDSubjetPhi_JetSubCalc = 0;
   theJetAK8SDSubjetPt_JetSubCalc = 0;
   theJetAK8SoftDropMass_JetSubCalc = 0;
   theJetAK8TrimmedMass_JetSubCalc = 0;
   theJetAK8caTopMinMass_JetSubCalc = 0;
   theJetAK8caTopTopMass_JetSubCalc = 0;
   theJetCEmEFrac_JetSubCalc = 0;
   theJetCEmEnergy_JetSubCalc = 0;
   theJetCHadEFrac_JetSubCalc = 0;
   theJetCHadEnergy_JetSubCalc = 0;
   theJetCSV_JetSubCalc = 0;
   theJetEnergy_JetSubCalc = 0;
   theJetEta_JetSubCalc = 0;
   theJetMuonEFrac_JetSubCalc = 0;
   theJetNEmEFrac_JetSubCalc = 0;
   theJetNEmEnergy_JetSubCalc = 0;
   theJetNHadEFrac_JetSubCalc = 0;
   theJetNHadEnergy_JetSubCalc = 0;
   theJetPhi_JetSubCalc = 0;
   theJetPileupJetId_JetSubCalc = 0;
   theJetPt_JetSubCalc = 0;
   theJetVtx3DSig_JetSubCalc = 0;
   theJetVtx3DVal_JetSubCalc = 0;
   theJetVtxMass_JetSubCalc = 0;
   theJetVtxNtracks_JetSubCalc = 0;
   topEnergy_TTbarMassCalc = 0;
   topEta_TTbarMassCalc = 0;
   topMass_TTbarMassCalc = 0;
   topPhi_TTbarMassCalc = 0;
   topPt_TTbarMassCalc = 0;
   electron_hltfilters_singleLepCalc = 0;
   muon_hltfilters_singleLepCalc = 0;
   vsSelMCTriggersEl_singleLepCalc = 0;
   vsSelMCTriggersMu_singleLepCalc = 0;
   vsSelTriggersEl_singleLepCalc = 0;
   vsSelTriggersMu_singleLepCalc = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

if(dmcblock->isMC){
	//contain TpTpCalc and 
   fChain->SetBranchAddress("isBHBH_TpTpCalc", &isBHBH_TpTpCalc, &b_isBHBH_TpTpCalc);
   fChain->SetBranchAddress("isBHTW_TpTpCalc", &isBHTW_TpTpCalc, &b_isBHTW_TpTpCalc);
   fChain->SetBranchAddress("isBWBW_TpTpCalc", &isBWBW_TpTpCalc, &b_isBWBW_TpTpCalc);
   fChain->SetBranchAddress("isBZBH_TpTpCalc", &isBZBH_TpTpCalc, &b_isBZBH_TpTpCalc);
   fChain->SetBranchAddress("isBZBZ_TpTpCalc", &isBZBZ_TpTpCalc, &b_isBZBZ_TpTpCalc);
   fChain->SetBranchAddress("isBZTW_TpTpCalc", &isBZTW_TpTpCalc, &b_isBZTW_TpTpCalc);
   fChain->SetBranchAddress("isTHBW_TpTpCalc", &isTHBW_TpTpCalc, &b_isTHBW_TpTpCalc);
   fChain->SetBranchAddress("isTHTH_TpTpCalc", &isTHTH_TpTpCalc, &b_isTHTH_TpTpCalc);
   fChain->SetBranchAddress("isTWTW_TpTpCalc", &isTWTW_TpTpCalc, &b_isTWTW_TpTpCalc);
   fChain->SetBranchAddress("isTZBW_TpTpCalc", &isTZBW_TpTpCalc, &b_isTZBW_TpTpCalc);
   fChain->SetBranchAddress("isTZTH_TpTpCalc", &isTZTH_TpTpCalc, &b_isTZTH_TpTpCalc);
   fChain->SetBranchAddress("isTZTZ_TpTpCalc", &isTZTZ_TpTpCalc, &b_isTZTZ_TpTpCalc);
   fChain->SetBranchAddress("NLeptonDecays_TpTpCalc", &NLeptonDecays_TpTpCalc, &b_NLeptonDecays_TpTpCalc);
   fChain->SetBranchAddress("HdecayID_TpTpCalc", &HdecayID_TpTpCalc, &b_HdecayID_TpTpCalc);
   fChain->SetBranchAddress("HdecayIndex_TpTpCalc", &HdecayIndex_TpTpCalc, &b_HdecayIndex_TpTpCalc);
   fChain->SetBranchAddress("LeptonID_TpTpCalc", &LeptonID_TpTpCalc, &b_LeptonID_TpTpCalc);
   fChain->SetBranchAddress("LeptonParentID_TpTpCalc", &LeptonParentID_TpTpCalc, &b_LeptonParentID_TpTpCalc);
   fChain->SetBranchAddress("WdecayID_TpTpCalc", &WdecayID_TpTpCalc, &b_WdecayID_TpTpCalc);
   fChain->SetBranchAddress("WdecayIndex_TpTpCalc", &WdecayIndex_TpTpCalc, &b_WdecayIndex_TpTpCalc);
   fChain->SetBranchAddress("ZdecayID_TpTpCalc", &ZdecayID_TpTpCalc, &b_ZdecayID_TpTpCalc);
   fChain->SetBranchAddress("ZdecayIndex_TpTpCalc", &ZdecayIndex_TpTpCalc, &b_ZdecayIndex_TpTpCalc);
   fChain->SetBranchAddress("bPrimeID_TpTpCalc", &bPrimeID_TpTpCalc, &b_bPrimeID_TpTpCalc);
   fChain->SetBranchAddress("bPrimeNDaughters_TpTpCalc", &bPrimeNDaughters_TpTpCalc, &b_bPrimeNDaughters_TpTpCalc);
   fChain->SetBranchAddress("bPrimeStatus_TpTpCalc", &bPrimeStatus_TpTpCalc, &b_bPrimeStatus_TpTpCalc);
   fChain->SetBranchAddress("bosonID_TpTpCalc", &bosonID_TpTpCalc, &b_bosonID_TpTpCalc);
   fChain->SetBranchAddress("quarkID_TpTpCalc", &quarkID_TpTpCalc, &b_quarkID_TpTpCalc);
   fChain->SetBranchAddress("tPrimeID_TpTpCalc", &tPrimeID_TpTpCalc, &b_tPrimeID_TpTpCalc);
   fChain->SetBranchAddress("tPrimeNDaughters_TpTpCalc", &tPrimeNDaughters_TpTpCalc, &b_tPrimeNDaughters_TpTpCalc);
   fChain->SetBranchAddress("tPrimeStatus_TpTpCalc", &tPrimeStatus_TpTpCalc, &b_tPrimeStatus_TpTpCalc);
   fChain->SetBranchAddress("HdecayEnergy_TpTpCalc", &HdecayEnergy_TpTpCalc, &b_HdecayEnergy_TpTpCalc);
   fChain->SetBranchAddress("HdecayEta_TpTpCalc", &HdecayEta_TpTpCalc, &b_HdecayEta_TpTpCalc);
   fChain->SetBranchAddress("HdecayPhi_TpTpCalc", &HdecayPhi_TpTpCalc, &b_HdecayPhi_TpTpCalc);
   fChain->SetBranchAddress("HdecayPt_TpTpCalc", &HdecayPt_TpTpCalc, &b_HdecayPt_TpTpCalc);
   fChain->SetBranchAddress("LeptonEnergy_TpTpCalc", &LeptonEnergy_TpTpCalc, &b_LeptonEnergy_TpTpCalc);
   fChain->SetBranchAddress("LeptonEta_TpTpCalc", &LeptonEta_TpTpCalc, &b_LeptonEta_TpTpCalc);
   fChain->SetBranchAddress("LeptonPhi_TpTpCalc", &LeptonPhi_TpTpCalc, &b_LeptonPhi_TpTpCalc);
   fChain->SetBranchAddress("LeptonPt_TpTpCalc", &LeptonPt_TpTpCalc, &b_LeptonPt_TpTpCalc);
   fChain->SetBranchAddress("WdecayEnergy_TpTpCalc", &WdecayEnergy_TpTpCalc, &b_WdecayEnergy_TpTpCalc);
   fChain->SetBranchAddress("WdecayEta_TpTpCalc", &WdecayEta_TpTpCalc, &b_WdecayEta_TpTpCalc);
   fChain->SetBranchAddress("WdecayPhi_TpTpCalc", &WdecayPhi_TpTpCalc, &b_WdecayPhi_TpTpCalc);
   fChain->SetBranchAddress("WdecayPt_TpTpCalc", &WdecayPt_TpTpCalc, &b_WdecayPt_TpTpCalc);
   fChain->SetBranchAddress("ZdecayEnergy_TpTpCalc", &ZdecayEnergy_TpTpCalc, &b_ZdecayEnergy_TpTpCalc);
   fChain->SetBranchAddress("ZdecayEta_TpTpCalc", &ZdecayEta_TpTpCalc, &b_ZdecayEta_TpTpCalc);
   fChain->SetBranchAddress("ZdecayPhi_TpTpCalc", &ZdecayPhi_TpTpCalc, &b_ZdecayPhi_TpTpCalc);
   fChain->SetBranchAddress("ZdecayPt_TpTpCalc", &ZdecayPt_TpTpCalc, &b_ZdecayPt_TpTpCalc);
   fChain->SetBranchAddress("bPrimeEnergy_TpTpCalc", &bPrimeEnergy_TpTpCalc, &b_bPrimeEnergy_TpTpCalc);
   fChain->SetBranchAddress("bPrimeEta_TpTpCalc", &bPrimeEta_TpTpCalc, &b_bPrimeEta_TpTpCalc);
   fChain->SetBranchAddress("bPrimeMass_TpTpCalc", &bPrimeMass_TpTpCalc, &b_bPrimeMass_TpTpCalc);
   fChain->SetBranchAddress("bPrimePhi_TpTpCalc", &bPrimePhi_TpTpCalc, &b_bPrimePhi_TpTpCalc);
   fChain->SetBranchAddress("bPrimePt_TpTpCalc", &bPrimePt_TpTpCalc, &b_bPrimePt_TpTpCalc);
   fChain->SetBranchAddress("bosonEnergy_TpTpCalc", &bosonEnergy_TpTpCalc, &b_bosonEnergy_TpTpCalc);
   fChain->SetBranchAddress("bosonEta_TpTpCalc", &bosonEta_TpTpCalc, &b_bosonEta_TpTpCalc);
   fChain->SetBranchAddress("bosonPhi_TpTpCalc", &bosonPhi_TpTpCalc, &b_bosonPhi_TpTpCalc);
   fChain->SetBranchAddress("bosonPt_TpTpCalc", &bosonPt_TpTpCalc, &b_bosonPt_TpTpCalc);
   fChain->SetBranchAddress("quarkEnergy_TpTpCalc", &quarkEnergy_TpTpCalc, &b_quarkEnergy_TpTpCalc);
   fChain->SetBranchAddress("quarkEta_TpTpCalc", &quarkEta_TpTpCalc, &b_quarkEta_TpTpCalc);
   fChain->SetBranchAddress("quarkPhi_TpTpCalc", &quarkPhi_TpTpCalc, &b_quarkPhi_TpTpCalc);
   fChain->SetBranchAddress("quarkPt_TpTpCalc", &quarkPt_TpTpCalc, &b_quarkPt_TpTpCalc);
   fChain->SetBranchAddress("tPrimeEnergy_TpTpCalc", &tPrimeEnergy_TpTpCalc, &b_tPrimeEnergy_TpTpCalc);
   fChain->SetBranchAddress("tPrimeEta_TpTpCalc", &tPrimeEta_TpTpCalc, &b_tPrimeEta_TpTpCalc);
   fChain->SetBranchAddress("tPrimeMass_TpTpCalc", &tPrimeMass_TpTpCalc, &b_tPrimeMass_TpTpCalc);
   fChain->SetBranchAddress("tPrimePhi_TpTpCalc", &tPrimePhi_TpTpCalc, &b_tPrimePhi_TpTpCalc);
   fChain->SetBranchAddress("tPrimePt_TpTpCalc", &tPrimePt_TpTpCalc, &b_tPrimePt_TpTpCalc);
}//end if MC

   fChain->SetBranchAddress("dataE_singleLepCalc", &dataE_singleLepCalc, &b_dataE_singleLepCalc);
   fChain->SetBranchAddress("dataM_singleLepCalc", &dataM_singleLepCalc, &b_dataM_singleLepCalc);
   fChain->SetBranchAddress("event_CommonCalc", &event_CommonCalc, &b_event_CommonCalc);
   fChain->SetBranchAddress("genTDLID_singleLepCalc", &genTDLID_singleLepCalc, &b_genTDLID_singleLepCalc);
   fChain->SetBranchAddress("lumi_CommonCalc", &lumi_CommonCalc, &b_lumi_CommonCalc);
   fChain->SetBranchAddress("nAllJets_CommonCalc", &nAllJets_CommonCalc, &b_nAllJets_CommonCalc);
   fChain->SetBranchAddress("nLooseElectrons_CommonCalc", &nLooseElectrons_CommonCalc, &b_nLooseElectrons_CommonCalc);
   fChain->SetBranchAddress("nLooseMuons_CommonCalc", &nLooseMuons_CommonCalc, &b_nLooseMuons_CommonCalc);
   fChain->SetBranchAddress("nPV_singleLepCalc", &nPV_singleLepCalc, &b_nPV_singleLepCalc);
   fChain->SetBranchAddress("nPileupInteractions_singleLepCalc", &nPileupInteractions_singleLepCalc, &b_nPileupInteractions_singleLepCalc);
   fChain->SetBranchAddress("nSelBtagJets_CommonCalc", &nSelBtagJets_CommonCalc, &b_nSelBtagJets_CommonCalc);
   fChain->SetBranchAddress("nSelElectrons_CommonCalc", &nSelElectrons_CommonCalc, &b_nSelElectrons_CommonCalc);
   fChain->SetBranchAddress("nSelJets_CommonCalc", &nSelJets_CommonCalc, &b_nSelJets_CommonCalc);
   fChain->SetBranchAddress("nSelMuons_CommonCalc", &nSelMuons_CommonCalc, &b_nSelMuons_CommonCalc);
   fChain->SetBranchAddress("nTrueInteractions_singleLepCalc", &nTrueInteractions_singleLepCalc, &b_nTrueInteractions_singleLepCalc);
   fChain->SetBranchAddress("run_CommonCalc", &run_CommonCalc, &b_run_CommonCalc);
   fChain->SetBranchAddress("AK4HT_singleLepCalc", &AK4HT_singleLepCalc, &b_AK4HT_singleLepCalc);
   fChain->SetBranchAddress("MCWeight_singleLepCalc", &MCWeight_singleLepCalc, &b_MCWeight_singleLepCalc);
   fChain->SetBranchAddress("corr_met_phi_singleLepCalc", &corr_met_phi_singleLepCalc, &b_corr_met_phi_singleLepCalc);
   fChain->SetBranchAddress("corr_met_singleLepCalc", &corr_met_singleLepCalc, &b_corr_met_singleLepCalc);
   fChain->SetBranchAddress("corr_metnohf_phi_singleLepCalc", &corr_metnohf_phi_singleLepCalc, &b_corr_metnohf_phi_singleLepCalc);
   fChain->SetBranchAddress("corr_metnohf_singleLepCalc", &corr_metnohf_singleLepCalc, &b_corr_metnohf_singleLepCalc);
   fChain->SetBranchAddress("genTDLEnergy_singleLepCalc", &genTDLEnergy_singleLepCalc, &b_genTDLEnergy_singleLepCalc);
   fChain->SetBranchAddress("genTDLEta_singleLepCalc", &genTDLEta_singleLepCalc, &b_genTDLEta_singleLepCalc);
   fChain->SetBranchAddress("genTDLPhi_singleLepCalc", &genTDLPhi_singleLepCalc, &b_genTDLPhi_singleLepCalc);
   fChain->SetBranchAddress("genTDLPt_singleLepCalc", &genTDLPt_singleLepCalc, &b_genTDLPt_singleLepCalc);
   fChain->SetBranchAddress("met_phi_singleLepCalc", &met_phi_singleLepCalc, &b_met_phi_singleLepCalc);
   fChain->SetBranchAddress("met_singleLepCalc", &met_singleLepCalc, &b_met_singleLepCalc);
   fChain->SetBranchAddress("metnohf_phi_singleLepCalc", &metnohf_phi_singleLepCalc, &b_metnohf_phi_singleLepCalc);
   fChain->SetBranchAddress("metnohf_singleLepCalc", &metnohf_singleLepCalc, &b_metnohf_singleLepCalc);
   fChain->SetBranchAddress("theJetHT_JetSubCalc", &theJetHT_JetSubCalc, &b_theJetHT_JetSubCalc);
   fChain->SetBranchAddress("theJetLeadPt_JetSubCalc", &theJetLeadPt_JetSubCalc, &b_theJetLeadPt_JetSubCalc);
   fChain->SetBranchAddress("theJetSubLeadPt_JetSubCalc", &theJetSubLeadPt_JetSubCalc, &b_theJetSubLeadPt_JetSubCalc);
   fChain->SetBranchAddress("ttbarMass_TTbarMassCalc", &ttbarMass_TTbarMassCalc, &b_ttbarMass_TTbarMassCalc);
   fChain->SetBranchAddress("theJetAK8PrunedTau21Tag_JetSubCalc", &theJetAK8PrunedTau21Tag_JetSubCalc, &b_theJetAK8PrunedTau21Tag_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDTau32BTag0p1_JetSubCalc", &theJetAK8SDTau32BTag0p1_JetSubCalc, &b_theJetAK8SDTau32BTag0p1_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDTau32BTag0p3_JetSubCalc", &theJetAK8SDTau32BTag0p3_JetSubCalc, &b_theJetAK8SDTau32BTag0p3_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDTau32BTag10_JetSubCalc", &theJetAK8SDTau32BTag10_JetSubCalc, &b_theJetAK8SDTau32BTag10_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDTau32BTag1_JetSubCalc", &theJetAK8SDTau32BTag1_JetSubCalc, &b_theJetAK8SDTau32BTag1_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDTau32BTag3_JetSubCalc", &theJetAK8SDTau32BTag3_JetSubCalc, &b_theJetAK8SDTau32BTag3_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDTau32Tag0p1_JetSubCalc", &theJetAK8SDTau32Tag0p1_JetSubCalc, &b_theJetAK8SDTau32Tag0p1_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDTau32Tag0p3_JetSubCalc", &theJetAK8SDTau32Tag0p3_JetSubCalc, &b_theJetAK8SDTau32Tag0p3_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDTau32Tag10_JetSubCalc", &theJetAK8SDTau32Tag10_JetSubCalc, &b_theJetAK8SDTau32Tag10_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDTau32Tag1_JetSubCalc", &theJetAK8SDTau32Tag1_JetSubCalc, &b_theJetAK8SDTau32Tag1_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDTau32Tag3_JetSubCalc", &theJetAK8SDTau32Tag3_JetSubCalc, &b_theJetAK8SDTau32Tag3_JetSubCalc);
   fChain->SetBranchAddress("AK4JetBTag_singleLepCalc", &AK4JetBTag_singleLepCalc, &b_AK4JetBTag_singleLepCalc);
   fChain->SetBranchAddress("AK4JetFlav_singleLepCalc", &AK4JetFlav_singleLepCalc, &b_AK4JetFlav_singleLepCalc);
   fChain->SetBranchAddress("LHEWeightids_singleLepCalc", &LHEWeightids_singleLepCalc, &b_LHEWeightids_singleLepCalc);
   fChain->SetBranchAddress("allTopsID_TTbarMassCalc", &allTopsID_TTbarMassCalc, &b_allTopsID_TTbarMassCalc);
   fChain->SetBranchAddress("allTopsStatus_TTbarMassCalc", &allTopsStatus_TTbarMassCalc, &b_allTopsStatus_TTbarMassCalc);
   fChain->SetBranchAddress("elChargeConsistent_singleLepCalc", &elChargeConsistent_singleLepCalc, &b_elChargeConsistent_singleLepCalc);
   fChain->SetBranchAddress("elCharge_singleLepCalc", &elCharge_singleLepCalc, &b_elCharge_singleLepCalc);
   fChain->SetBranchAddress("elIDLevel25ns_singleLepCalc", &elIDLevel25ns_singleLepCalc, &b_elIDLevel25ns_singleLepCalc);
   fChain->SetBranchAddress("elIDLevel50ns_singleLepCalc", &elIDLevel50ns_singleLepCalc, &b_elIDLevel50ns_singleLepCalc);
   fChain->SetBranchAddress("elIsEBEE_singleLepCalc", &elIsEBEE_singleLepCalc, &b_elIsEBEE_singleLepCalc);
   fChain->SetBranchAddress("elMHits_singleLepCalc", &elMHits_singleLepCalc, &b_elMHits_singleLepCalc);
   fChain->SetBranchAddress("elMatched_singleLepCalc", &elMatched_singleLepCalc, &b_elMatched_singleLepCalc);
   fChain->SetBranchAddress("elMother_id_singleLepCalc", &elMother_id_singleLepCalc, &b_elMother_id_singleLepCalc);
   fChain->SetBranchAddress("elMother_status_singleLepCalc", &elMother_status_singleLepCalc, &b_elMother_status_singleLepCalc);
   fChain->SetBranchAddress("elNotConversion_singleLepCalc", &elNotConversion_singleLepCalc, &b_elNotConversion_singleLepCalc);
   fChain->SetBranchAddress("elNumberOfMothers_singleLepCalc", &elNumberOfMothers_singleLepCalc, &b_elNumberOfMothers_singleLepCalc);
   fChain->SetBranchAddress("elPdgId_singleLepCalc", &elPdgId_singleLepCalc, &b_elPdgId_singleLepCalc);
   fChain->SetBranchAddress("elStatus_singleLepCalc", &elStatus_singleLepCalc, &b_elStatus_singleLepCalc);
   fChain->SetBranchAddress("elVtxFitConv_singleLepCalc", &elVtxFitConv_singleLepCalc, &b_elVtxFitConv_singleLepCalc);
   fChain->SetBranchAddress("electron_1_hltmatched_singleLepCalc", &electron_1_hltmatched_singleLepCalc, &b_electron_1_hltmatched_singleLepCalc);
   fChain->SetBranchAddress("genBSLID_singleLepCalc", &genBSLID_singleLepCalc, &b_genBSLID_singleLepCalc);
   fChain->SetBranchAddress("genID_singleLepCalc", &genID_singleLepCalc, &b_genID_singleLepCalc);
   fChain->SetBranchAddress("genIndex_singleLepCalc", &genIndex_singleLepCalc, &b_genIndex_singleLepCalc);
   fChain->SetBranchAddress("genMotherID_singleLepCalc", &genMotherID_singleLepCalc, &b_genMotherID_singleLepCalc);
   fChain->SetBranchAddress("genMotherIndex_singleLepCalc", &genMotherIndex_singleLepCalc, &b_genMotherIndex_singleLepCalc);
   fChain->SetBranchAddress("genStatus_singleLepCalc", &genStatus_singleLepCalc, &b_genStatus_singleLepCalc);
   fChain->SetBranchAddress("muCharge_singleLepCalc", &muCharge_singleLepCalc, &b_muCharge_singleLepCalc);
   fChain->SetBranchAddress("muGlobal_singleLepCalc", &muGlobal_singleLepCalc, &b_muGlobal_singleLepCalc);
   fChain->SetBranchAddress("muIsLoose_singleLepCalc", &muIsLoose_singleLepCalc, &b_muIsLoose_singleLepCalc);
   fChain->SetBranchAddress("muIsMedium_singleLepCalc", &muIsMedium_singleLepCalc, &b_muIsMedium_singleLepCalc);
   fChain->SetBranchAddress("muIsTight_singleLepCalc", &muIsTight_singleLepCalc, &b_muIsTight_singleLepCalc);
   fChain->SetBranchAddress("muMatched_singleLepCalc", &muMatched_singleLepCalc, &b_muMatched_singleLepCalc);
   fChain->SetBranchAddress("muMother_id_singleLepCalc", &muMother_id_singleLepCalc, &b_muMother_id_singleLepCalc);
   fChain->SetBranchAddress("muMother_status_singleLepCalc", &muMother_status_singleLepCalc, &b_muMother_status_singleLepCalc);
   fChain->SetBranchAddress("muNMatchedStations_singleLepCalc", &muNMatchedStations_singleLepCalc, &b_muNMatchedStations_singleLepCalc);
   fChain->SetBranchAddress("muNTrackerLayers_singleLepCalc", &muNTrackerLayers_singleLepCalc, &b_muNTrackerLayers_singleLepCalc);
   fChain->SetBranchAddress("muNValMuHits_singleLepCalc", &muNValMuHits_singleLepCalc, &b_muNValMuHits_singleLepCalc);
   fChain->SetBranchAddress("muNValPixelHits_singleLepCalc", &muNValPixelHits_singleLepCalc, &b_muNValPixelHits_singleLepCalc);
   fChain->SetBranchAddress("muNumberOfMothers_singleLepCalc", &muNumberOfMothers_singleLepCalc, &b_muNumberOfMothers_singleLepCalc);
   fChain->SetBranchAddress("muPdgId_singleLepCalc", &muPdgId_singleLepCalc, &b_muPdgId_singleLepCalc);
   fChain->SetBranchAddress("muStatus_singleLepCalc", &muStatus_singleLepCalc, &b_muStatus_singleLepCalc);
   fChain->SetBranchAddress("muon_1_hltmatched_singleLepCalc", &muon_1_hltmatched_singleLepCalc, &b_muon_1_hltmatched_singleLepCalc);
   fChain->SetBranchAddress("theJetAK8SDSubjetIndex_JetSubCalc", &theJetAK8SDSubjetIndex_JetSubCalc, &b_theJetAK8SDSubjetIndex_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDSubjetNCSVL_JetSubCalc", &theJetAK8SDSubjetNCSVL_JetSubCalc, &b_theJetAK8SDSubjetNCSVL_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDSubjetNCSVM_JetSubCalc", &theJetAK8SDSubjetNCSVM_JetSubCalc, &b_theJetAK8SDSubjetNCSVM_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDSubjetSize_JetSubCalc", &theJetAK8SDSubjetSize_JetSubCalc, &b_theJetAK8SDSubjetSize_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8caTopnSubJets_JetSubCalc", &theJetAK8caTopnSubJets_JetSubCalc, &b_theJetAK8caTopnSubJets_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8nDaughters_JetSubCalc", &theJetAK8nDaughters_JetSubCalc, &b_theJetAK8nDaughters_JetSubCalc);
   fChain->SetBranchAddress("theJetBTagLoose_JetSubCalc", &theJetBTagLoose_JetSubCalc, &b_theJetBTagLoose_JetSubCalc);
   fChain->SetBranchAddress("theJetBTag_JetSubCalc", &theJetBTag_JetSubCalc, &b_theJetBTag_JetSubCalc);
   fChain->SetBranchAddress("theJetFlav_JetSubCalc", &theJetFlav_JetSubCalc, &b_theJetFlav_JetSubCalc);
   fChain->SetBranchAddress("theJetnDaughters_JetSubCalc", &theJetnDaughters_JetSubCalc, &b_theJetnDaughters_JetSubCalc);
   fChain->SetBranchAddress("topID_TTbarMassCalc", &topID_TTbarMassCalc, &b_topID_TTbarMassCalc);
   fChain->SetBranchAddress("viSelMCTriggersEl_singleLepCalc", &viSelMCTriggersEl_singleLepCalc, &b_viSelMCTriggersEl_singleLepCalc);
   fChain->SetBranchAddress("viSelMCTriggersMu_singleLepCalc", &viSelMCTriggersMu_singleLepCalc, &b_viSelMCTriggersMu_singleLepCalc);
   fChain->SetBranchAddress("viSelTriggersEl_singleLepCalc", &viSelTriggersEl_singleLepCalc, &b_viSelTriggersEl_singleLepCalc);
   fChain->SetBranchAddress("viSelTriggersMu_singleLepCalc", &viSelTriggersMu_singleLepCalc, &b_viSelTriggersMu_singleLepCalc);
   fChain->SetBranchAddress("AK4JetBDisc_singleLepCalc", &AK4JetBDisc_singleLepCalc, &b_AK4JetBDisc_singleLepCalc);
   fChain->SetBranchAddress("AK4JetEnergy_singleLepCalc", &AK4JetEnergy_singleLepCalc, &b_AK4JetEnergy_singleLepCalc);
   fChain->SetBranchAddress("AK4JetEta_singleLepCalc", &AK4JetEta_singleLepCalc, &b_AK4JetEta_singleLepCalc);
   fChain->SetBranchAddress("AK4JetPhi_singleLepCalc", &AK4JetPhi_singleLepCalc, &b_AK4JetPhi_singleLepCalc);
   fChain->SetBranchAddress("AK4JetPt_singleLepCalc", &AK4JetPt_singleLepCalc, &b_AK4JetPt_singleLepCalc);
   fChain->SetBranchAddress("AK8JetCSV_singleLepCalc", &AK8JetCSV_singleLepCalc, &b_AK8JetCSV_singleLepCalc);
   fChain->SetBranchAddress("AK8JetEnergy_singleLepCalc", &AK8JetEnergy_singleLepCalc, &b_AK8JetEnergy_singleLepCalc);
   fChain->SetBranchAddress("AK8JetEta_singleLepCalc", &AK8JetEta_singleLepCalc, &b_AK8JetEta_singleLepCalc);
   fChain->SetBranchAddress("AK8JetPhi_singleLepCalc", &AK8JetPhi_singleLepCalc, &b_AK8JetPhi_singleLepCalc);
   fChain->SetBranchAddress("AK8JetPt_singleLepCalc", &AK8JetPt_singleLepCalc, &b_AK8JetPt_singleLepCalc);
   fChain->SetBranchAddress("LHEWeights_singleLepCalc", &LHEWeights_singleLepCalc, &b_LHEWeights_singleLepCalc);
   fChain->SetBranchAddress("allTopsEnergy_TTbarMassCalc", &allTopsEnergy_TTbarMassCalc, &b_allTopsEnergy_TTbarMassCalc);
   fChain->SetBranchAddress("allTopsEta_TTbarMassCalc", &allTopsEta_TTbarMassCalc, &b_allTopsEta_TTbarMassCalc);
   fChain->SetBranchAddress("allTopsPhi_TTbarMassCalc", &allTopsPhi_TTbarMassCalc, &b_allTopsPhi_TTbarMassCalc);
   fChain->SetBranchAddress("allTopsPt_TTbarMassCalc", &allTopsPt_TTbarMassCalc, &b_allTopsPt_TTbarMassCalc);
   fChain->SetBranchAddress("elAEff_singleLepCalc", &elAEff_singleLepCalc, &b_elAEff_singleLepCalc);
   fChain->SetBranchAddress("elChIso_singleLepCalc", &elChIso_singleLepCalc, &b_elChIso_singleLepCalc);
   fChain->SetBranchAddress("elD0_singleLepCalc", &elD0_singleLepCalc, &b_elD0_singleLepCalc);
   fChain->SetBranchAddress("elDEtaSCTkAtVtx_singleLepCalc", &elDEtaSCTkAtVtx_singleLepCalc, &b_elDEtaSCTkAtVtx_singleLepCalc);
   fChain->SetBranchAddress("elDPhiSCTkAtVtx_singleLepCalc", &elDPhiSCTkAtVtx_singleLepCalc, &b_elDPhiSCTkAtVtx_singleLepCalc);
   fChain->SetBranchAddress("elDR03TkSumPt_singleLepCalc", &elDR03TkSumPt_singleLepCalc, &b_elDR03TkSumPt_singleLepCalc);
   fChain->SetBranchAddress("elDZ_singleLepCalc", &elDZ_singleLepCalc, &b_elDZ_singleLepCalc);
   fChain->SetBranchAddress("elDeta_singleLepCalc", &elDeta_singleLepCalc, &b_elDeta_singleLepCalc);
   fChain->SetBranchAddress("elDphi_singleLepCalc", &elDphi_singleLepCalc, &b_elDphi_singleLepCalc);
   fChain->SetBranchAddress("elDxy_singleLepCalc", &elDxy_singleLepCalc, &b_elDxy_singleLepCalc);
   fChain->SetBranchAddress("elEcalPFClusterIso_singleLepCalc", &elEcalPFClusterIso_singleLepCalc, &b_elEcalPFClusterIso_singleLepCalc);
   fChain->SetBranchAddress("elEnergy_singleLepCalc", &elEnergy_singleLepCalc, &b_elEnergy_singleLepCalc);
   fChain->SetBranchAddress("elEtaVtx_singleLepCalc", &elEtaVtx_singleLepCalc, &b_elEtaVtx_singleLepCalc);
   fChain->SetBranchAddress("elEta_singleLepCalc", &elEta_singleLepCalc, &b_elEta_singleLepCalc);
   fChain->SetBranchAddress("elGen_Reco_dr_singleLepCalc", &elGen_Reco_dr_singleLepCalc, &b_elGen_Reco_dr_singleLepCalc);
   fChain->SetBranchAddress("elHcalPFClusterIso_singleLepCalc", &elHcalPFClusterIso_singleLepCalc, &b_elHcalPFClusterIso_singleLepCalc);
   fChain->SetBranchAddress("elHoE_singleLepCalc", &elHoE_singleLepCalc, &b_elHoE_singleLepCalc);
   fChain->SetBranchAddress("elMVATrigValue_singleLepCalc", &elMVATrigValue_singleLepCalc, &b_elMVATrigValue_singleLepCalc);
   fChain->SetBranchAddress("elMVAValue_singleLepCalc", &elMVAValue_singleLepCalc, &b_elMVAValue_singleLepCalc);
   fChain->SetBranchAddress("elMatchedEnergy_singleLepCalc", &elMatchedEnergy_singleLepCalc, &b_elMatchedEnergy_singleLepCalc);
   fChain->SetBranchAddress("elMatchedEta_singleLepCalc", &elMatchedEta_singleLepCalc, &b_elMatchedEta_singleLepCalc);
   fChain->SetBranchAddress("elMatchedPhi_singleLepCalc", &elMatchedPhi_singleLepCalc, &b_elMatchedPhi_singleLepCalc);
   fChain->SetBranchAddress("elMatchedPt_singleLepCalc", &elMatchedPt_singleLepCalc, &b_elMatchedPt_singleLepCalc);
   fChain->SetBranchAddress("elMiniIso_singleLepCalc", &elMiniIso_singleLepCalc, &b_elMiniIso_singleLepCalc);
   fChain->SetBranchAddress("elMother_energy_singleLepCalc", &elMother_energy_singleLepCalc, &b_elMother_energy_singleLepCalc);
   fChain->SetBranchAddress("elMother_eta_singleLepCalc", &elMother_eta_singleLepCalc, &b_elMother_eta_singleLepCalc);
   fChain->SetBranchAddress("elMother_phi_singleLepCalc", &elMother_phi_singleLepCalc, &b_elMother_phi_singleLepCalc);
   fChain->SetBranchAddress("elMother_pt_singleLepCalc", &elMother_pt_singleLepCalc, &b_elMother_pt_singleLepCalc);
   fChain->SetBranchAddress("elNhIso_singleLepCalc", &elNhIso_singleLepCalc, &b_elNhIso_singleLepCalc);
   fChain->SetBranchAddress("elOoemoop_singleLepCalc", &elOoemoop_singleLepCalc, &b_elOoemoop_singleLepCalc);
   fChain->SetBranchAddress("elPhIso_singleLepCalc", &elPhIso_singleLepCalc, &b_elPhIso_singleLepCalc);
   fChain->SetBranchAddress("elPhiVtx_singleLepCalc", &elPhiVtx_singleLepCalc, &b_elPhiVtx_singleLepCalc);
   fChain->SetBranchAddress("elPhi_singleLepCalc", &elPhi_singleLepCalc, &b_elPhi_singleLepCalc);
   fChain->SetBranchAddress("elPt_singleLepCalc", &elPt_singleLepCalc, &b_elPt_singleLepCalc);
   fChain->SetBranchAddress("elRelIso_singleLepCalc", &elRelIso_singleLepCalc, &b_elRelIso_singleLepCalc);
   fChain->SetBranchAddress("elRhoIso_singleLepCalc", &elRhoIso_singleLepCalc, &b_elRhoIso_singleLepCalc);
   fChain->SetBranchAddress("elSihih_singleLepCalc", &elSihih_singleLepCalc, &b_elSihih_singleLepCalc);
   fChain->SetBranchAddress("evtWeightsMC_singleLepCalc", &evtWeightsMC_singleLepCalc, &b_evtWeightsMC_singleLepCalc);
   fChain->SetBranchAddress("genBSLEnergy_singleLepCalc", &genBSLEnergy_singleLepCalc, &b_genBSLEnergy_singleLepCalc);
   fChain->SetBranchAddress("genBSLEta_singleLepCalc", &genBSLEta_singleLepCalc, &b_genBSLEta_singleLepCalc);
   fChain->SetBranchAddress("genBSLPhi_singleLepCalc", &genBSLPhi_singleLepCalc, &b_genBSLPhi_singleLepCalc);
   fChain->SetBranchAddress("genBSLPt_singleLepCalc", &genBSLPt_singleLepCalc, &b_genBSLPt_singleLepCalc);
   fChain->SetBranchAddress("genEnergy_singleLepCalc", &genEnergy_singleLepCalc, &b_genEnergy_singleLepCalc);
   fChain->SetBranchAddress("genEta_singleLepCalc", &genEta_singleLepCalc, &b_genEta_singleLepCalc);
   fChain->SetBranchAddress("genJetEnergy_singleLepCalc", &genJetEnergy_singleLepCalc, &b_genJetEnergy_singleLepCalc);
   fChain->SetBranchAddress("genJetEta_singleLepCalc", &genJetEta_singleLepCalc, &b_genJetEta_singleLepCalc);
   fChain->SetBranchAddress("genJetPhi_singleLepCalc", &genJetPhi_singleLepCalc, &b_genJetPhi_singleLepCalc);
   fChain->SetBranchAddress("genJetPt_singleLepCalc", &genJetPt_singleLepCalc, &b_genJetPt_singleLepCalc);
   fChain->SetBranchAddress("genPhi_singleLepCalc", &genPhi_singleLepCalc, &b_genPhi_singleLepCalc);
   fChain->SetBranchAddress("genPt_singleLepCalc", &genPt_singleLepCalc, &b_genPt_singleLepCalc);
   fChain->SetBranchAddress("muChIso_singleLepCalc", &muChIso_singleLepCalc, &b_muChIso_singleLepCalc);
   fChain->SetBranchAddress("muChi2_singleLepCalc", &muChi2_singleLepCalc, &b_muChi2_singleLepCalc);
   fChain->SetBranchAddress("muDxy_singleLepCalc", &muDxy_singleLepCalc, &b_muDxy_singleLepCalc);
   fChain->SetBranchAddress("muDz_singleLepCalc", &muDz_singleLepCalc, &b_muDz_singleLepCalc);
   fChain->SetBranchAddress("muEnergy_singleLepCalc", &muEnergy_singleLepCalc, &b_muEnergy_singleLepCalc);
   fChain->SetBranchAddress("muEta_singleLepCalc", &muEta_singleLepCalc, &b_muEta_singleLepCalc);
   fChain->SetBranchAddress("muGIso_singleLepCalc", &muGIso_singleLepCalc, &b_muGIso_singleLepCalc);
   fChain->SetBranchAddress("muGen_Reco_dr_singleLepCalc", &muGen_Reco_dr_singleLepCalc, &b_muGen_Reco_dr_singleLepCalc);
   fChain->SetBranchAddress("muMatchedEnergy_singleLepCalc", &muMatchedEnergy_singleLepCalc, &b_muMatchedEnergy_singleLepCalc);
   fChain->SetBranchAddress("muMatchedEta_singleLepCalc", &muMatchedEta_singleLepCalc, &b_muMatchedEta_singleLepCalc);
   fChain->SetBranchAddress("muMatchedPhi_singleLepCalc", &muMatchedPhi_singleLepCalc, &b_muMatchedPhi_singleLepCalc);
   fChain->SetBranchAddress("muMatchedPt_singleLepCalc", &muMatchedPt_singleLepCalc, &b_muMatchedPt_singleLepCalc);
   fChain->SetBranchAddress("muMiniIso_singleLepCalc", &muMiniIso_singleLepCalc, &b_muMiniIso_singleLepCalc);
   fChain->SetBranchAddress("muMother_energy_singleLepCalc", &muMother_energy_singleLepCalc, &b_muMother_energy_singleLepCalc);
   fChain->SetBranchAddress("muMother_eta_singleLepCalc", &muMother_eta_singleLepCalc, &b_muMother_eta_singleLepCalc);
   fChain->SetBranchAddress("muMother_phi_singleLepCalc", &muMother_phi_singleLepCalc, &b_muMother_phi_singleLepCalc);
   fChain->SetBranchAddress("muMother_pt_singleLepCalc", &muMother_pt_singleLepCalc, &b_muMother_pt_singleLepCalc);
   fChain->SetBranchAddress("muNhIso_singleLepCalc", &muNhIso_singleLepCalc, &b_muNhIso_singleLepCalc);
   fChain->SetBranchAddress("muPhi_singleLepCalc", &muPhi_singleLepCalc, &b_muPhi_singleLepCalc);
   fChain->SetBranchAddress("muPt_singleLepCalc", &muPt_singleLepCalc, &b_muPt_singleLepCalc);
   fChain->SetBranchAddress("muPuIso_singleLepCalc", &muPuIso_singleLepCalc, &b_muPuIso_singleLepCalc);
   fChain->SetBranchAddress("muRelIso_singleLepCalc", &muRelIso_singleLepCalc, &b_muRelIso_singleLepCalc);
   fChain->SetBranchAddress("pfCombinedInclusiveSecondaryVertexV2BJetTags_BTagSFCalc", &pfCombinedInclusiveSecondaryVertexV2BJetTags_BTagSFCalc, &b_pfCombinedInclusiveSecondaryVertexV2BJetTags_BTagSFCalc);
   fChain->SetBranchAddress("pfCombinedMVABJetTags_BTagSFCalc", &pfCombinedMVABJetTags_BTagSFCalc, &b_pfCombinedMVABJetTags_BTagSFCalc);
   fChain->SetBranchAddress("pfCombinedSecondaryVertexV2BJetTags_BTagSFCalc", &pfCombinedSecondaryVertexV2BJetTags_BTagSFCalc, &b_pfCombinedSecondaryVertexV2BJetTags_BTagSFCalc);
   fChain->SetBranchAddress("pfJetBProbabilityBJetTags_BTagSFCalc", &pfJetBProbabilityBJetTags_BTagSFCalc, &b_pfJetBProbabilityBJetTags_BTagSFCalc);
   fChain->SetBranchAddress("pfJetProbabilityBJetTags_BTagSFCalc", &pfJetProbabilityBJetTags_BTagSFCalc, &b_pfJetProbabilityBJetTags_BTagSFCalc);
   fChain->SetBranchAddress("pfSimpleSecondaryVertexHighEffBJetTags_BTagSFCalc", &pfSimpleSecondaryVertexHighEffBJetTags_BTagSFCalc, &b_pfSimpleSecondaryVertexHighEffBJetTags_BTagSFCalc);
   fChain->SetBranchAddress("pfSimpleSecondaryVertexHighPurBJetTags_BTagSFCalc", &pfSimpleSecondaryVertexHighPurBJetTags_BTagSFCalc, &b_pfSimpleSecondaryVertexHighPurBJetTags_BTagSFCalc);
   fChain->SetBranchAddress("pfTrackCountingHighEffBJetTags_BTagSFCalc", &pfTrackCountingHighEffBJetTags_BTagSFCalc, &b_pfTrackCountingHighEffBJetTags_BTagSFCalc);
   fChain->SetBranchAddress("pfTrackCountingHighPurBJetTags_BTagSFCalc", &pfTrackCountingHighPurBJetTags_BTagSFCalc, &b_pfTrackCountingHighPurBJetTags_BTagSFCalc);
   fChain->SetBranchAddress("theJetAK8CEmEFrac_JetSubCalc", &theJetAK8CEmEFrac_JetSubCalc, &b_theJetAK8CEmEFrac_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8CEmEnergy_JetSubCalc", &theJetAK8CEmEnergy_JetSubCalc, &b_theJetAK8CEmEnergy_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8CHadEFrac_JetSubCalc", &theJetAK8CHadEFrac_JetSubCalc, &b_theJetAK8CHadEFrac_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8CHadEnergy_JetSubCalc", &theJetAK8CHadEnergy_JetSubCalc, &b_theJetAK8CHadEnergy_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8CSV_JetSubCalc", &theJetAK8CSV_JetSubCalc, &b_theJetAK8CSV_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8Energy_JetSubCalc", &theJetAK8Energy_JetSubCalc, &b_theJetAK8Energy_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8Eta_JetSubCalc", &theJetAK8Eta_JetSubCalc, &b_theJetAK8Eta_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8FilteredMass_JetSubCalc", &theJetAK8FilteredMass_JetSubCalc, &b_theJetAK8FilteredMass_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8JetCharge_JetSubCalc", &theJetAK8JetCharge_JetSubCalc, &b_theJetAK8JetCharge_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8Mass_JetSubCalc", &theJetAK8Mass_JetSubCalc, &b_theJetAK8Mass_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8NEmEFrac_JetSubCalc", &theJetAK8NEmEFrac_JetSubCalc, &b_theJetAK8NEmEFrac_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8NEmEnergy_JetSubCalc", &theJetAK8NEmEnergy_JetSubCalc, &b_theJetAK8NEmEnergy_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8NHadEFrac_JetSubCalc", &theJetAK8NHadEFrac_JetSubCalc, &b_theJetAK8NHadEFrac_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8NHadEnergy_JetSubCalc", &theJetAK8NHadEnergy_JetSubCalc, &b_theJetAK8NHadEnergy_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8NjettinessTau1_JetSubCalc", &theJetAK8NjettinessTau1_JetSubCalc, &b_theJetAK8NjettinessTau1_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8NjettinessTau2_JetSubCalc", &theJetAK8NjettinessTau2_JetSubCalc, &b_theJetAK8NjettinessTau2_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8NjettinessTau3_JetSubCalc", &theJetAK8NjettinessTau3_JetSubCalc, &b_theJetAK8NjettinessTau3_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8Phi_JetSubCalc", &theJetAK8Phi_JetSubCalc, &b_theJetAK8Phi_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8PrunedMass_JetSubCalc", &theJetAK8PrunedMass_JetSubCalc, &b_theJetAK8PrunedMass_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8Pt_JetSubCalc", &theJetAK8Pt_JetSubCalc, &b_theJetAK8Pt_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDSubjetCSV_JetSubCalc", &theJetAK8SDSubjetCSV_JetSubCalc, &b_theJetAK8SDSubjetCSV_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDSubjetDR_JetSubCalc", &theJetAK8SDSubjetDR_JetSubCalc, &b_theJetAK8SDSubjetDR_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDSubjetEta_JetSubCalc", &theJetAK8SDSubjetEta_JetSubCalc, &b_theJetAK8SDSubjetEta_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDSubjetMass_JetSubCalc", &theJetAK8SDSubjetMass_JetSubCalc, &b_theJetAK8SDSubjetMass_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDSubjetPhi_JetSubCalc", &theJetAK8SDSubjetPhi_JetSubCalc, &b_theJetAK8SDSubjetPhi_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SDSubjetPt_JetSubCalc", &theJetAK8SDSubjetPt_JetSubCalc, &b_theJetAK8SDSubjetPt_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8SoftDropMass_JetSubCalc", &theJetAK8SoftDropMass_JetSubCalc, &b_theJetAK8SoftDropMass_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8TrimmedMass_JetSubCalc", &theJetAK8TrimmedMass_JetSubCalc, &b_theJetAK8TrimmedMass_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8caTopMinMass_JetSubCalc", &theJetAK8caTopMinMass_JetSubCalc, &b_theJetAK8caTopMinMass_JetSubCalc);
   fChain->SetBranchAddress("theJetAK8caTopTopMass_JetSubCalc", &theJetAK8caTopTopMass_JetSubCalc, &b_theJetAK8caTopTopMass_JetSubCalc);
   fChain->SetBranchAddress("theJetCEmEFrac_JetSubCalc", &theJetCEmEFrac_JetSubCalc, &b_theJetCEmEFrac_JetSubCalc);
   fChain->SetBranchAddress("theJetCEmEnergy_JetSubCalc", &theJetCEmEnergy_JetSubCalc, &b_theJetCEmEnergy_JetSubCalc);
   fChain->SetBranchAddress("theJetCHadEFrac_JetSubCalc", &theJetCHadEFrac_JetSubCalc, &b_theJetCHadEFrac_JetSubCalc);
   fChain->SetBranchAddress("theJetCHadEnergy_JetSubCalc", &theJetCHadEnergy_JetSubCalc, &b_theJetCHadEnergy_JetSubCalc);
   fChain->SetBranchAddress("theJetCSV_JetSubCalc", &theJetCSV_JetSubCalc, &b_theJetCSV_JetSubCalc);
   fChain->SetBranchAddress("theJetEnergy_JetSubCalc", &theJetEnergy_JetSubCalc, &b_theJetEnergy_JetSubCalc);
   fChain->SetBranchAddress("theJetEta_JetSubCalc", &theJetEta_JetSubCalc, &b_theJetEta_JetSubCalc);
   fChain->SetBranchAddress("theJetMuonEFrac_JetSubCalc", &theJetMuonEFrac_JetSubCalc, &b_theJetMuonEFrac_JetSubCalc);
   fChain->SetBranchAddress("theJetNEmEFrac_JetSubCalc", &theJetNEmEFrac_JetSubCalc, &b_theJetNEmEFrac_JetSubCalc);
   fChain->SetBranchAddress("theJetNEmEnergy_JetSubCalc", &theJetNEmEnergy_JetSubCalc, &b_theJetNEmEnergy_JetSubCalc);
   fChain->SetBranchAddress("theJetNHadEFrac_JetSubCalc", &theJetNHadEFrac_JetSubCalc, &b_theJetNHadEFrac_JetSubCalc);
   fChain->SetBranchAddress("theJetNHadEnergy_JetSubCalc", &theJetNHadEnergy_JetSubCalc, &b_theJetNHadEnergy_JetSubCalc);
   fChain->SetBranchAddress("theJetPhi_JetSubCalc", &theJetPhi_JetSubCalc, &b_theJetPhi_JetSubCalc);
   fChain->SetBranchAddress("theJetPileupJetId_JetSubCalc", &theJetPileupJetId_JetSubCalc, &b_theJetPileupJetId_JetSubCalc);
   fChain->SetBranchAddress("theJetPt_JetSubCalc", &theJetPt_JetSubCalc, &b_theJetPt_JetSubCalc);
   fChain->SetBranchAddress("theJetVtx3DSig_JetSubCalc", &theJetVtx3DSig_JetSubCalc, &b_theJetVtx3DSig_JetSubCalc);
   fChain->SetBranchAddress("theJetVtx3DVal_JetSubCalc", &theJetVtx3DVal_JetSubCalc, &b_theJetVtx3DVal_JetSubCalc);
   fChain->SetBranchAddress("theJetVtxMass_JetSubCalc", &theJetVtxMass_JetSubCalc, &b_theJetVtxMass_JetSubCalc);
   fChain->SetBranchAddress("theJetVtxNtracks_JetSubCalc", &theJetVtxNtracks_JetSubCalc, &b_theJetVtxNtracks_JetSubCalc);
   fChain->SetBranchAddress("topEnergy_TTbarMassCalc", &topEnergy_TTbarMassCalc, &b_topEnergy_TTbarMassCalc);
   fChain->SetBranchAddress("topEta_TTbarMassCalc", &topEta_TTbarMassCalc, &b_topEta_TTbarMassCalc);
   fChain->SetBranchAddress("topMass_TTbarMassCalc", &topMass_TTbarMassCalc, &b_topMass_TTbarMassCalc);
   fChain->SetBranchAddress("topPhi_TTbarMassCalc", &topPhi_TTbarMassCalc, &b_topPhi_TTbarMassCalc);
   fChain->SetBranchAddress("topPt_TTbarMassCalc", &topPt_TTbarMassCalc, &b_topPt_TTbarMassCalc);
   fChain->SetBranchAddress("electron_hltfilters_singleLepCalc", &electron_hltfilters_singleLepCalc, &b_electron_hltfilters_singleLepCalc);
   fChain->SetBranchAddress("muon_hltfilters_singleLepCalc", &muon_hltfilters_singleLepCalc, &b_muon_hltfilters_singleLepCalc);
   fChain->SetBranchAddress("vsSelMCTriggersEl_singleLepCalc", &vsSelMCTriggersEl_singleLepCalc, &b_vsSelMCTriggersEl_singleLepCalc);
   fChain->SetBranchAddress("vsSelMCTriggersMu_singleLepCalc", &vsSelMCTriggersMu_singleLepCalc, &b_vsSelMCTriggersMu_singleLepCalc);
   fChain->SetBranchAddress("vsSelTriggersEl_singleLepCalc", &vsSelTriggersEl_singleLepCalc, &b_vsSelTriggersEl_singleLepCalc);
   fChain->SetBranchAddress("vsSelTriggersMu_singleLepCalc", &vsSelTriggersMu_singleLepCalc, &b_vsSelTriggersMu_singleLepCalc);

}//init


void tpmultlepmaincalc::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
/*Int_t tpmultlepmaincalc::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}*/

void tpmultlepmaincalc::IncludeAJson(std::string jsonfile) {
		// Fairly primitive brute force json parser -- opens the json file named in the argument
		// and adds that to the goodrunlumilist map.  Overlapping jsons are merged inclusively.
	char thing;
	ifstream jsonInput;
	std::cout << "Sucking in Json file: " << jsonfile << " which includes: " << std::endl;
	jsonInput.open(jsonfile.c_str());
	if (!jsonInput.good()) {
		std::cout << "Problem reading Json file...  Didn't suck anything in... " << std::endl;
		return;
	}
	
	jsonInput.get(thing);
	while (jsonInput.good()) {
		if (thing=='{') {  // start of list
			while (thing != '}') {
				int runnum;
				if (thing == '"') {
					std::string srunnum;
					jsonInput.get(thing); // get stuff inside ""
					
					while (thing != '"') {
						srunnum+=thing; // get stuff inside ""
						jsonInput.get(thing);
						
					}
					sscanf(srunnum.c_str(),"%i",&runnum);
					std::cout << " runnum: " << runnum << std::endl;
					
				} // inside ""
				if (thing == '[') {
					jsonInput.get(thing); // get stuff inside []
					while (thing != ']') {
						if (thing == '[') {
							jsonInput.get(thing); // get stuff inside series []
							
							std::string lumiseries;
							int firstlumi,lastlumi;
							while (thing !=']') {
								lumiseries+=thing;
								jsonInput.get(thing); // get stuff inside series []
							}
							sscanf(lumiseries.c_str(),"%i,%i",&firstlumi,&lastlumi);
							//std::cout << "  lumis  " << firstlumi << " to " << lastlumi << std::endl;
							
								// At this point have runnum, first lumi, last lumi -- so can fill map here...
							for (int l=firstlumi;l<=lastlumi;l++) {
								goodrunlumilist[runnum][l]=true;
							}
							
						} // inside actual series []
						jsonInput.get(thing); // get stuff inside []
					}
				} // inside []
				jsonInput.get(thing); // get another char looking for "
			} 
		} // inside {}
		jsonInput.get(thing); // get another char looking for {
	} // EOF 
	jsonInput.close();
}//end json

bool tpmultlepmaincalc::isInJson(Int_t run,Int_t lumi) {
	return goodrunlumilist[run][lumi];
}

#endif // #ifdef tpmultlepmaincalc_cxx
