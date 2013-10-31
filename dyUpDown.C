#include <iostream>
#include <map>
#include <stdio.h>
#include "TH1.h"
#include "TFile.h"
#include "TChain.h"
#include "TLorentzVector.h"

double lepton1PtRec,  lepton2PtRec,  lepton3PtRec;
double lepton1EtaRec, lepton2EtaRec, lepton3EtaRec;
double lepton1PhiRec, lepton2PhiRec, lepton3PhiRec;
double lepton1PtGen,  lepton2PtGen,  lepton3PtGen;
double lepton1EtaGen, lepton2EtaGen, lepton3EtaGen;
double lepton1PhiGen, lepton2PhiGen, lepton3PhiGen;
double metPtRec, metPhiRec;
double weight;
int    selection, type, run, event, nVerts;
int    numberOfBJets;

double leadingJetPtRec, leadingJetEtaRec, leadingJetPhiRec, leadingJetCSV;
double subleadJetPtRec, subleadJetEtaRec, subleadJetPhiRec, subleadJetCSV;
double thirdJetPtRec, thirdJetEtaRec, thirdJetPhiRec, thirdJetCSV;
double forthJetPtRec, forthJetEtaRec, forthJetPhiRec, forthJetCSV;
double thMrec;

void attachBranches(TChain *micro){
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

   micro->SetBranchAddress("metPtRec", &metPtRec);
   micro->SetBranchAddress("metPhiRec",&metPhiRec);
   micro->SetBranchAddress("weight",   &weight);
   micro->SetBranchAddress("selection",&selection);
   micro->SetBranchAddress("type",     &type);
   micro->SetBranchAddress("run",      &run);
   micro->SetBranchAddress("event",    &event);
   micro->SetBranchAddress("numberOfBJets", &numberOfBJets);

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

   micro->SetBranchAddress("thMrec", &thMrec);
}

double select(TChain *micro, int &pass, int nBjets, double MET, double M3J){
   double yield = 0;
   pass = 0;

   for(int entry=0; micro->GetEntry(entry) /*&& entry<500*/; entry++){

//      if( type!=3 ) continue;

//      if( (entry%1000000) == 0 ) std::cout<<"Event: "<<entry<<"/"<<micro->GetEntries()<<std::endl;
/*
      if( lepton1PtRec>20 && lepton2PtRec>20 && fabs(lepton1EtaRec)<2.1 && fabs(lepton2EtaRec)<2.1 && (selection&31)==31 && thirdJetPtRec>40 ){
            TLorentzVector lepton1, lepton2;
            lepton1.SetPtEtaPhiM(lepton1PtRec, lepton1EtaRec, lepton1PhiRec, 0.113);
            lepton2.SetPtEtaPhiM(lepton2PtRec, lepton2EtaRec, lepton2PhiRec, 0.113);
            TLorentzVector sum( lepton1 + lepton2 );
            double fakeMET = sum.Pt();

            TLorentzVector jet1, jet2, jet3;
            jet1.SetPtEtaPhiM(leadingJetPtRec, leadingJetEtaRec, leadingJetPhiRec, 0.);
            jet2.SetPtEtaPhiM(subleadJetPtRec, subleadJetEtaRec, subleadJetPhiRec, 0.);
            jet3.SetPtEtaPhiM(  thirdJetPtRec,   thirdJetEtaRec,   thirdJetPhiRec, 0.);
            TLorentzVector triJet( jet1 + jet2 + jet3 );
            if( fakeMET > MET && (nBjets<0 || numberOfBJets == nBjets) && (M3J>0 ? forthJetPtRec<35 && triJet.M()<M3J : true)){
//               yield += weight;
//               pass++;
cout<<"lepton1PtGen="<<lepton1PtGen<<" lepton2PtGen="<<lepton2PtGen<<endl;
            }

      }
*/
      if( lepton1PtGen>0 && lepton2PtGen>0 && (selection&31)==31 && thirdJetPtRec>40 ){
            TLorentzVector lepton1, lepton2;
            lepton1.SetPtEtaPhiM(lepton1PtGen, lepton1EtaGen, lepton1PhiGen, 0.113);
            lepton2.SetPtEtaPhiM(lepton2PtGen, lepton2EtaGen, lepton2PhiGen, 0.113);
            TLorentzVector sum( lepton1 + lepton2 );
            double fakeMET = sum.Pt();

            TLorentzVector jet1, jet2, jet3;
            jet1.SetPtEtaPhiM(leadingJetPtRec, leadingJetEtaRec, leadingJetPhiRec, 0.);
            jet2.SetPtEtaPhiM(subleadJetPtRec, subleadJetEtaRec, subleadJetPhiRec, 0.);
            jet3.SetPtEtaPhiM(  thirdJetPtRec,   thirdJetEtaRec,   thirdJetPhiRec, 0.);
            TLorentzVector triJet( jet1 + jet2 + jet3 );
            if( fakeMET > MET && (nBjets<0 || numberOfBJets == nBjets) && (M3J>0 ? forthJetPtRec<35 && triJet.M()<M3J : true)){
               yield += weight;
               pass++;
            }
      }
   }

   return yield;
}

void dyUpDown(int nBjets=0, double MET=250, double M3J=-1){

  TChain *center = new TChain("micro");
  center->AddFile("/data/users/kkotov/new/micro_ZJ1_muSel.root");
  center->AddFile("/data/users/kkotov/new/micro_ZJ2_muSel.root");
  center->AddFile("/data/users/kkotov/new/micro_ZJ3_muSel.root");
  center->AddFile("/data/users/kkotov/new/micro_ZJ4_muSel.root");
  center->AddFile("/data/users/kkotov/new/micro_ZJ5_muSel.root");

  TChain *scaleUp = new TChain("micro");
  scaleUp->AddFile("/data/users/kkotov/new/micro_ZJsu_muSel.root");

  TChain *scaleDown = new TChain("micro");
  scaleDown->AddFile("/data/users/kkotov/new/micro_ZJsd_muSel.root");

  TChain *matchUp = new TChain("micro");
  matchUp->AddFile("/data/users/kkotov/new/micro_ZJmu_muSel.root");

  TChain *matchDown = new TChain("micro");
  matchDown->AddFile("/data/users/kkotov/new/micro_ZJmd_muSel.root");

  attachBranches(center);
  attachBranches(scaleUp);
  attachBranches(scaleDown);
  attachBranches(matchUp);
  attachBranches(matchDown);

  cout<<"Center: ";
  int    passCenter  = 0;
  double yieldCenter = select(center, passCenter, nBjets, MET, M3J);
  cout<<passCenter<<endl;

  cout<<"ScaleUp: ";
  int    passScaleUp = 0;
  double yieldScaleUp = select(scaleUp, passScaleUp, nBjets, MET, M3J);
  cout<<passScaleUp<<endl;

  cout<<"ScaleDown: ";
  int    passScaleDown = 0;
  double yieldScaleDown = select(scaleDown, passScaleDown, nBjets, MET, M3J);
  cout<<passScaleDown<<endl;

  cout<<"MatchUp: ";
  int    passMatchUp = 0;
  double yieldMatchUp = select(matchUp, passMatchUp, nBjets, MET, M3J);
  cout<<passMatchUp<<endl;

  cout<<"MatchDown: ";
  int    passMatchDown = 0;
  double yieldMatchDown = select(matchDown, passMatchDown, nBjets, MET, M3J);
  cout<<passMatchDown<<endl;

  cout<<"YieldCenter="<<yieldCenter<<" (unweighted: "<<passCenter<<")"<<endl;
  cout<<"YieldScaleUp="<<yieldScaleUp<<" (unweighted: "<<passScaleUp<<")"<<endl;
  cout<<"YieldScaleDown="<<yieldScaleDown<<" (unweighted: "<<passScaleDown<<")"<<endl;
  cout<<"YieldMatchUp="<<yieldMatchUp<<" (unweighted: "<<passMatchUp<<")"<<endl;
  cout<<"YieldMatchDown="<<yieldMatchDown<<" (unweighted: "<<passMatchDown<<")"<<endl;

  cout<<"Q2 scale variation: +"<<(yieldScaleUp-yieldCenter)/yieldCenter<<" -"<<(yieldCenter-yieldScaleDown)/yieldCenter<<endl;
  cout<<"Matching variation: +"<<(yieldMatchDown-yieldCenter)/yieldCenter<<" -"<<(yieldCenter-yieldMatchUp)/yieldMatchUp<<endl;
}
