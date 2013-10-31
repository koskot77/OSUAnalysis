#include <iostream>
#include <map>
#include <stdio.h>
#include "TH1.h"
#include "TFile.h"
#include "TChain.h"
#include "TLorentzVector.h"

enum {s3m0=57, s3m50=60, s3m100=62, s3m150=63, s3m200=64, s3m300=65, s3m500=66,
      s4m0=37, s4m50=40, s4m100=42, s4m150=43, s4m200=44, s4m300=45, s4m500=46,
      tt=1, wj=2, zjets=3, top=16, ww=24, wz=25, zz=26, zn50=4, zn100=5, zn200=6, zn400=7,
      S3m0=47, S3m50=50, S3m100=52, S3m150=53, S3m200=54, S3m300=55, S3m400=67, S3m500=56, S3m600=68,
      S4m0=27, S4m50=30, S4m100=32, S4m150=33, S4m200=34, S4m300=35, S4m400=69, S4m500=36, S4m600=70, S4m700=71, S4m800=72, S4m900=73, S4m1000=74,
      tW=16, tbarW=17, t=18,tbar=19, tS=20, tbarS=21};

void calcPDF(int process=s3m0, int nBjets=1, double MET=250){

TChain *micro = new TChain("micro");

switch( process ){
  case tt :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_TT_metSel.root");
  break;
  case  wj :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_WJ1_metSel.root");
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_WJ2_metSel.root");
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_WJ3_metSel.root");
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_WJ4_metSel.root");
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_WJ5_metSel.root");
  break;
  case tW :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_T_metSel.root");
  break;
  case tbarW :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_T_metSel.root");
  break;
  case t :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_T_metSel.root");
  break;
  case tbar :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_T_metSel.root");
  break;
  case tS :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_T_metSel.root");
  break;
  case tbarS :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_T_metSel.root");
  break;
  case zn400 :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_ZN_metSel.root");
  break;
  case zn200 :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_ZN_metSel.root");
  break;
  case zn100 :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_ZN_metSel.root");
  break;
  case zn50 :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_ZN_metSel.root");
  break;
  case ww :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_WW_metSel.root");
  break;
  case wz :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_WZ_metSel.root");
  break;
  case zz :
    micro->AddFile("/mnt/hadoop/users/kkotov/new/micro_ZZ_metSel.root");
  break;
  default :
    micro->AddFile("micro_signals_metSel.root");
    micro->AddFile("micro_signalsMore_metSel.root");
  break;
}


double q2WeightUp, q2WeightDown, pdfWeights[45];

double metPtRec, metPhiRec;
double weight;
int    selection, type, run, numberOfJets, numberOfBJets;
double thMrec;
ULong64_t trig;

micro->SetBranchAddress("pdfWeights",    pdfWeights);
micro->SetBranchAddress("q2WeightUp",   &q2WeightUp);
micro->SetBranchAddress("q2WeightDown", &q2WeightDown);
micro->SetBranchAddress("numberOfJets", &numberOfJets);
micro->SetBranchAddress("numberOfBJets",&numberOfBJets);

micro->SetBranchAddress("metPtRec", &metPtRec);
micro->SetBranchAddress("metPhiRec",&metPhiRec);
micro->SetBranchAddress("weight",   &weight);
micro->SetBranchAddress("selection",&selection);
micro->SetBranchAddress("type",     &type);
micro->SetBranchAddress("run",      &run);
//micro->SetBranchAddress("metTRIGs", &trig);

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
micro->SetBranchAddress("numberOfJets",    &numberOfJets);
micro->SetBranchAddress("numberOfBJets",   &numberOfBJets);
micro->SetBranchAddress("thMrec",          &thMrec);

double pdfWtSel[45];
bzero(pdfWtSel,sizeof(double)*45);

for(int event=0; micro->GetEntry(event) /*&& event<500*/; event++){

   if( process!=type ) continue;

//if( (trig&0x10)!=0x10 ) continue; // HLT_Ele27_WP80
//if( (trig&0x80000000)!=0x80000000 ) continue; // HLT_IsoMu24

   if( (event%100000) == 0 ) std::cout<<"Event: "<<event<<"/"<<micro->GetEntries()<<std::endl;

   if( (selection&31)==31 && numberOfBJets==nBjets && metPtRec>MET ){
//       std::cout<<"Event: "<<event<<"/"<<micro->GetEntries()<<std::endl;

      if( thirdJetPtRec>40 && forthJetPtRec<35 ){
///      if( thirdJetPtRec>40 && forthJetPtRec>40 && numberOfJets==4 ){
//         TLorentzVector jet1, jet2, jet3;
//         jet1.SetPtEtaPhiM(leadingJetPtRec, leadingJetEtaRec, leadingJetPhiRec, 0.);
//         jet2.SetPtEtaPhiM(subleadJetPtRec, subleadJetEtaRec, subleadJetPhiRec, 0.);
//         jet3.SetPtEtaPhiM(  thirdJetPtRec,   thirdJetEtaRec,   thirdJetPhiRec, 0.);
//         TLorentzVector sum( jet1 + jet2 + jet3 );
//         if( sum.M()<250 ){
         if( thMrec<250 ){
            for(unsigned int index = 0; index <= 44; index++)
               pdfWtSel[index] += pdfWeights[index];
         }
      }
   }

}

double baseNumEvts = pdfWtSel[0];
if( baseNumEvts <= 0.0 ) {
   cout << "No events processed\n";
   return;
}
unsigned int numPairs = 22;
double wplus = 0.0, wminus = 0.0;
for(unsigned int index = 0; index < numPairs; ++index) {
    double wa = (pdfWtSel[(2 * index) + 1] / baseNumEvts) - 1.0;
    double wb = (pdfWtSel[(2 * index) + 2] / baseNumEvts) - 1.0;
    if( wa < wb ){
        double tmp = wa;
        wa = wb;
        wb = tmp;
    }
    if( wa < 0.0 ) wa = 0.0;
    if( wb > 0.0 ) wb = 0.0;
    wplus += wa * wa;
    wminus += wb * wb;
}
if( wplus  > 0 ) wplus  = sqrt(wplus);
if( wminus > 0 ) wminus = sqrt(wminus);
cout << "PDF uncertainty: +" << wplus;
cout << " -" << wminus << endl;
cout << "Using " << numPairs << " eigenvectors\n";

}
