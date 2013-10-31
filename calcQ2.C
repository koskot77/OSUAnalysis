#include <iostream>
#include <map>
#include <stdio.h>
#include "TH1.h"
#include "TFile.h"
#include "TChain.h"
#include "TLorentzVector.h"

enum {s3m0=57, s3m50=60, s3m100=62, s3m150=63, s3m200=64, s3m300=65, s3m500=66,
      s4m0=37, s4m50=40, s4m100=42, s4m150=43, s4m200=44, s4m300=45, s4m500=46,
      ttjets=1, wjets=2, zjets=3, top=16, ww=24, wz=25, zz=26, zn50=4, zn100=5, zn200=6, zn400=7,
      tW=16, tbarW=17, t=18,tbar=19, tS=20, tbarS=21};

void calcQ2(int process=0, int nBjets=0, double MET=250){

TChain *micro = new TChain("micro");

switch( process ){
  case ttjets :
    micro->AddFile("/tmp/kkotov/micro_TT_metSel.root");
  break;
  case  wjets :
    micro->AddFile("/tmp/kkotov/micro_WJ1_metSel.root");
    micro->AddFile("/tmp/kkotov/micro_WJ2_metSel.root");
    micro->AddFile("/tmp/kkotov/micro_WJ3_metSel.root");
    micro->AddFile("/tmp/kkotov/micro_WJ4_metSel.root");
    micro->AddFile("/tmp/kkotov/micro_WJ5_metSel.root");
  break;
  case zjets :
//    micro->AddFile("/tmp/kkotov/old/micro_DYJetsToLL_metSel.root");
    micro->AddFile("/tmp/kkotov/micro_ZJ1_muSel.root");
    micro->AddFile("/tmp/kkotov/micro_ZJ2_muSel.root");
    micro->AddFile("/tmp/kkotov/micro_ZJ3_muSel.root");
    micro->AddFile("/tmp/kkotov/micro_ZJ4_muSel.root");
    micro->AddFile("/tmp/kkotov/micro_ZJ5_muSel.root");
  break;
  case tW :
    micro->AddFile("/tmp/kkotov/micro_T_metSel.root");
  break;
  case tbarW :
    micro->AddFile("/tmp/kkotov/micro_T_metSel.root");
  break;
  case t :
    micro->AddFile("/tmp/kkotov/micro_T_metSel.root");
  break;
  case tbar :
    micro->AddFile("/tmp/kkotov/micro_T_metSel.root");
  break;
  case tS :
    micro->AddFile("/tmp/kkotov/micro_T_metSel.root");
  break;
  case tbarS :
    micro->AddFile("/tmp/kkotov/micro_T_metSel.root");
  break;
  case zn400 :
    micro->AddFile("/data/users/kkotov/old/micro_ZN_metSel.root");
  break;
  case zn200 :
    micro->AddFile("/data/users/kkotov/old/micro_ZN_metSel.root");
  break;
  case zn100 :
    micro->AddFile("/data/users/kkotov/old/micro_ZN_metSel.root");
  break;
  case zn50 :
    micro->AddFile("/data/users/kkotov/old/micro_ZN_metSel.root");
  break;
  case ww :
    micro->AddFile("/tmp/kkotov/micro_WW_metSel.root");
  break;
  case wz :
    micro->AddFile("/tmp/kkotov/micro_WZ_metSel.root");
  break;
  case zz :
    micro->AddFile("/tmp/kkotov/micro_ZZ_metSel.root");
  break;
  default :
    micro->AddFile("/tmp/kkotov/micro_signals_metSel.root");
  break;
}


double q2WeightUp, q2WeightDown;

double metPtRec, metPhiRec;
int    selection, type, run, numberOfJets, numberOfBJets;
ULong64_t trig;

micro->SetBranchAddress("q2WeightUp",   &q2WeightUp);
micro->SetBranchAddress("q2WeightDown", &q2WeightDown);
micro->SetBranchAddress("numberOfJets",&numberOfJets);
micro->SetBranchAddress("numberOfBJets",&numberOfBJets);

micro->SetBranchAddress("metPtRec", &metPtRec);
micro->SetBranchAddress("metPhiRec",&metPhiRec);
micro->SetBranchAddress("selection",&selection);
micro->SetBranchAddress("type",     &type);
micro->SetBranchAddress("run",      &run);
//micro->SetBranchAddress("metTRIGs", &trig);

double lepton1PtRec,  lepton2PtRec,  lepton3PtRec;
double lepton1EtaRec, lepton2EtaRec, lepton3EtaRec;
double lepton1PhiRec, lepton2PhiRec, lepton3PhiRec;
double lepton1PtGen,  lepton2PtGen,  lepton3PtGen;
double lepton1EtaGen, lepton2EtaGen, lepton3EtaGen;
double lepton1PhiGen, lepton2PhiGen, lepton3PhiGen;

micro->SetBranchAddress("lepton1PtRec",&lepton1PtRec);
micro->SetBranchAddress("lepton2PtRec",&lepton2PtRec);
micro->SetBranchAddress("lepton3PtRec",&lepton3PtRec);
micro->SetBranchAddress("lepton1EtaRec",&lepton1EtaRec);
micro->SetBranchAddress("lepton2EtaRec",&lepton2EtaRec);
micro->SetBranchAddress("lepton3EtaRec",&lepton3EtaRec);
micro->SetBranchAddress("lepton1PhiRec",&lepton1PhiRec);
micro->SetBranchAddress("lepton2PhiRec",&lepton2PhiRec);
micro->SetBranchAddress("lepton3PhiRec",&lepton3PhiRec);

micro->SetBranchAddress("lepton1PtGen",&lepton1PtGen);
micro->SetBranchAddress("lepton2PtGen",&lepton2PtGen);
micro->SetBranchAddress("lepton3PtGen",&lepton3PtGen);
micro->SetBranchAddress("lepton1EtaGen",&lepton1EtaGen);
micro->SetBranchAddress("lepton2EtaGen",&lepton2EtaGen);
micro->SetBranchAddress("lepton3EtaGen",&lepton3EtaGen);
micro->SetBranchAddress("lepton1PhiGen",&lepton1PhiGen);
micro->SetBranchAddress("lepton2PhiGen",&lepton2PhiGen);
micro->SetBranchAddress("lepton3PhiGen",&lepton3PhiGen);
/*
double leadingJetPtRec, leadingJetEtaRec, leadingJetPhiRec, leadingJetCSV;
double subleadJetPtRec, subleadJetEtaRec, subleadJetPhiRec, subleadJetCSV;
double thirdJetPtRec, thirdJetEtaRec, thirdJetPhiRec, thirdJetCSV;
double forthJetPtRec, forthJetEtaRec, forthJetPhiRec, forthJetCSV;
micro->SetBranchAddress("leadingJetPtRec", &leadingJetPtRec);
micro->SetBranchAddress("leadingJetEtaRec",&leadingJetEtaRec);
micro->SetBranchAddress("leadingJetPhiRec",&leadingJetPhiRec);
micro->SetBranchAddress("leadingJetCSV",   &leadingJetCSV);
micro->SetBranchAddress("subleadJetPtRec", &subleadJetPtRec);
micro->SetBranchAddress("subleadJetEtaRec",&subleadJetEtaRec);
micro->SetBranchAddress("subleadJetPhiRec",&subleadJetPhiRec);
micro->SetBranchAddress("subleadJetCSV",   &subleadJetCSV);
micro->SetBranchAddress("thirdJetPtRec",   &thirdJetPtRec);
micro->SetBranchAddress("thirdJetEtaRec",  &thirdJetEtaRec);
micro->SetBranchAddress("thirdJetPhiRec",  &thirdJetPhiRec);
micro->SetBranchAddress("thirdJetCSV",     &thirdJetCSV);
micro->SetBranchAddress("forthJetPtRec",   &forthJetPtRec);
micro->SetBranchAddress("forthJetEtaRec",  &forthJetEtaRec);
micro->SetBranchAddress("forthJetPhiRec",  &forthJetPhiRec);
micro->SetBranchAddress("forthJetCSV",     &forthJetCSV);
*/

double q2upWtSel=0, q2downWtSel=0, q2upWtAll=0, q2downWtAll=0, centralAll=0, centralSel=0;

for(int event=0; micro->GetEntry(event) /*&& event<10000*/; event++){

//if( (trig&0x10)!=0x10 ) continue; // HLT_Ele27_WP80
//if( (trig&0x80000000)!=0x80000000 ) continue; // HLT_IsoMu24

   if( process!=type ) continue;

   if( (event%100000) == 0 ) std::cout<<"Event: "<<event<<"/"<<micro->GetEntries()<<std::endl;
      q2upWtAll   += q2WeightUp;
      q2downWtAll += q2WeightDown;
      centralAll++;

      if( process == zjets ){
         if( lepton1PtRec>20 && lepton2PtRec>20 && fabs(lepton1EtaRec)<2.1 && fabs(lepton2EtaRec)<2.1 ){
            TLorentzVector lepton1, lepton2;
            lepton1.SetPtEtaPhiM(lepton1PtRec, lepton1EtaRec, lepton1PhiRec, 0.113);
            lepton2.SetPtEtaPhiM(lepton2PtRec, lepton2EtaRec, lepton2PhiRec, 0.113);
            TLorentzVector sum( lepton1 + lepton2 );
            metPtRec = sum.Pt(); // fakeMET
         } else {
            metPtRec = -1;
         }
      }

      if( (selection&31)==31 && numberOfBJets==nBjets && metPtRec>MET /*&& thirdJetPtRec>40*/ ){
           q2upWtSel   += q2WeightUp;
           q2downWtSel += q2WeightDown;
           centralSel++;
      }
}

cout<<"Selected: "<<centralSel<<" events"<<endl;

cout<<"Q2 scale variation: +"<<(centralSel/centralAll - q2upWtSel/q2upWtAll)/(centralSel/centralAll)<<" -"<<(q2downWtSel/q2downWtAll - centralSel/centralAll)/(centralSel/centralAll)<<endl;

}
