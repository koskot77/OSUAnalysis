#include "TH1.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

struct Pass{
   double passMain, passCenter, passJecUp, passJecDown, passScaleUp, passScaleDown, passMatchUp, passMatchDown;
   const char *name;
};

using namespace std;

double SQR(double a){ return a*a; }

double metPtRec, metPhiRec;
double weight;
int    sele, typ;
int    numberOfBJets;

double leadingJetPtRec, leadingJetEtaRec, leadingJetPhiRec, leadingJetCSV;
double subleadJetPtRec, subleadJetEtaRec, subleadJetPhiRec, subleadJetCSV;
double thirdJetPtRec, thirdJetEtaRec, thirdJetPhiRec, thirdJetCSV;
double forthJetPtRec, forthJetEtaRec, forthJetPhiRec, forthJetCSV;

void attachBranches(TChain *micro){
   micro->SetBranchAddress("metPtRec", &metPtRec);
   micro->SetBranchAddress("metPhiRec",&metPhiRec);
   micro->SetBranchAddress("weight",   &weight);
   micro->SetBranchAddress("selection",&sele);
   micro->SetBranchAddress("type",     &typ);
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
}
/*
double cut(int bits, double met, int nBjets, vector<const char *> &file, int type){
  if( file.size()==0 ) return 0;

  TChain *micro = new TChain("micro");
  for(unsigned int i=0; i<file.size(); i++){
     if( file[i]==0 ) return 0;
     micro->AddFile(file[i]);
  }

  TH1F *tmp = new TH1F("tmp","",2048,0,2048);
  char buff[128];

//  sprintf(buff,"((selection&%d)==%d && numberOfBJets==%d && metPtRec>%f && type==%d)*weight",bits,bits,nBjets,met,type);
//
//  micro->Draw("selection>>tmp",buff);
//  double yield = tmp->Integral();

  attachBranches(micro);

  double yield = 0;
  for(int entry=0; micro->GetEntry(entry); entry++){
     if( typ!=type ) continue;
     if( (entry%100000) == 0 ) std::cout<<"Event: "<<entry<<"/"<<micro->GetEntries()<<std::endl;

     if( (sele & bits) == bits && thirdJetPtRec>40 && forthJetPtRec<35 && numberOfBJets==nBjets && metPtRec>met ){
        TLorentzVector jet1, jet2, jet3;
        jet1.SetPtEtaPhiM(leadingJetPtRec, leadingJetEtaRec, leadingJetPhiRec, 0.);
        jet2.SetPtEtaPhiM(subleadJetPtRec, subleadJetEtaRec, subleadJetPhiRec, 0.);
        jet3.SetPtEtaPhiM(  thirdJetPtRec,   thirdJetEtaRec,   thirdJetPhiRec, 0.);
        TLorentzVector sum( jet1 + jet2 + jet3 );
        if( sum.M()<250 ) yield += weight;
     }
  }

  delete tmp;
  delete micro;
  return yield;
}
*/

double cut(int bits, double met, int nBjets, vector<const char *> &file, int type){
  if( file.size()==0 ) return 0;
  
  TChain *micro = new TChain("micro");
  for(unsigned int i=0; i<file.size(); i++){
     if( file[i]==0 ) return 0;
     micro->AddFile(file[i]);
  }
  
  TH1F *tmp = new TH1F("tmp","",2048,0,2048);
  char buff[128];
  
  sprintf(buff,"((selection&%d)==%d && thirdJetPtRec>40 && forthJetPtRec<35 && numberOfBJets==%d && thMrec<250 && metPtRec>%f && type==%d)*weight",bits,bits,nBjets,met,type);
  
  micro->Draw("selection>>tmp",buff);
  double yield = tmp->Integral(); // tmp->GetEntries();
  
  delete tmp;
  delete micro; 
  return yield; 
} 

enum {s3m0=57, s3m50=60, s3m100=62, s3m150=63, s3m200=64, s3m300=65, s3m500=66, 
      s4m0=37, s4m50=40, s4m100=42, s4m150=43, s4m200=44, s4m300=45, s4m500=46,
      S3m0=47, S3m50=50, S3m100=52, S3m150=53, S3m200=54, S3m300=55, S3m400=67, S3m500=56, S3m600=68,
      S4m0=27, S4m50=30, S4m100=32, S4m150=33, S4m200=34, S4m300=35, S4m400=69, S4m500=36, S4m600=70, S4m700=71, S4m800=72, S4m900=73, S4m1000=74,
      ttjets=1, wjets=2, zjets=3, ww=24, wz=25, zz=26, zn50=4, zn100=5, zn200=6, zn400=7,
      tW=16, tbarW=17, t=18,tbar=19, tS=20, tbarS=21};

enum {TT=0, ZN=1, WJ=2, Top=3, VV=4, S=5};

map<int, vector<int> > groups;

map<int, const char*> names;

void jesFlow(int group=TT, double MET=250){

  if( group<TT || group>S ) {
    cout<<"Unknown group "<<group<<", choose in [0-4]"<<endl;
    return;
  }

  groups[TT].push_back(ttjets);
  groups[WJ].push_back(wjets);
  groups[ZN].push_back(zn50);
  groups[ZN].push_back(zn100);
  groups[ZN].push_back(zn200);
  groups[ZN].push_back(zn400);
  groups[Top].push_back(tW);
  groups[Top].push_back(tbarW);
  groups[Top].push_back(t);
  groups[Top].push_back(tbar);
  groups[Top].push_back(tS);
  groups[Top].push_back(tbarS);
  groups[VV].push_back(ww);
  groups[VV].push_back(wz);
  groups[VV].push_back(zz);
  groups[S].push_back(S3m0);
  groups[S].push_back(S3m50);
  groups[S].push_back(S3m100);
  groups[S].push_back(S3m150);
  groups[S].push_back(S3m200);
  groups[S].push_back(S3m300);
  groups[S].push_back(S3m400);
  groups[S].push_back(S3m500);
  groups[S].push_back(S3m600);
  groups[S].push_back(S4m0);
  groups[S].push_back(S4m50);
  groups[S].push_back(S4m100);
  groups[S].push_back(S4m150);
  groups[S].push_back(S4m200);
  groups[S].push_back(S4m300);
  groups[S].push_back(S4m400);
  groups[S].push_back(S4m500);
  groups[S].push_back(S4m600);
  groups[S].push_back(S4m700);
  groups[S].push_back(S4m800);
  groups[S].push_back(S4m900);
  groups[S].push_back(S4m1000);

  names[ttjets] = "tt";
  names[wjets]  = "wj";
  names[zn50]   = "zn50";
  names[zn100]  = "zn100";
  names[zn200]  = "zn200";
  names[zn400]  = "zn400";
  names[ww]     = "ww";
  names[wz]     = "wz";
  names[zz]     = "zz";
  names[tW]     = "tW";
  names[tbarW]  = "tbarW";
  names[t]      = "t";
  names[tbar]   = "tbar";
  names[tS]     = "tS";
  names[tbarS]  = "tbarS";
  names[s3m0]   = "s3m0";
  names[s3m50]  = "s3m50";
  names[s3m100] = "s3m100";
  names[s3m150] = "s3m150";
  names[s3m200] = "s3m200";
  names[s3m300] = "s3m300";
  names[s3m500] = "s3m500";
  names[S3m0]   = "S3m0";
  names[S3m50]  = "S3m50";
  names[S3m100] = "S3m100";
  names[S3m150] = "S3m150";
  names[S3m200] = "S3m200";
  names[S3m300] = "S3m300";
  names[S3m400] = "S3m400";
  names[S3m500] = "S3m500";
  names[S3m600] = "S3m600";
  names[s4m0]   = "s4m0";
  names[s4m50]  = "s4m50";
  names[s4m100] = "s4m100";
  names[s4m150] = "s4m150";
  names[s4m200] = "s4m200";
  names[s4m300] = "s4m300";
  names[s4m500] = "s4m500";
  names[S4m0]   = "S4m0";
  names[S4m50]  = "S4m50";
  names[S4m100] = "S4m100";
  names[S4m150] = "S4m150";
  names[S4m200] = "S4m200";
  names[S4m300] = "S4m300";
  names[S4m400] = "S4m400";
  names[S4m500] = "S4m500";
  names[S4m600] = "S4m600";
  names[S4m700] = "S4m700";
  names[S4m800] = "S4m800";
  names[S4m900] = "S4m900";
  names[S4m1000]= "S4m1000";

  const double lumi = (0.802 + 4.403 + 6.388 + 7.248)*1000.;
  const double lumiScale = lumi/5000.;

  map<int,int> nGen;
  nGen[s3m0]   = 8.307 * lumi;
  nGen[s3m50]  = 6.705 * lumi;
  nGen[s3m100] = 4.159 * lumi;
  nGen[s3m150] = 2.299 * lumi;
  nGen[s3m200] = 1.412 * lumi;
  nGen[s3m300] = .6048 * lumi;
  nGen[s3m500] = .1463 * lumi;
  nGen[s4m0]   = 100.0 * lumi;
  nGen[s4m50]  = 133.8 * lumi;
  nGen[s4m100] = 41.67 * lumi;
  nGen[s4m150] = 18.46 * lumi;
  nGen[s4m200] = 9.687 * lumi;
  nGen[s4m300] = 3.289 * lumi;
  nGen[s4m500] = .6325 * lumi;
  nGen[S3m0]   = 6.314 * lumi;
  nGen[S3m50]  = 5.072 * lumi;
  nGen[S3m100] = 3.406 * lumi;
  nGen[S3m150] = 2.227 * lumi;
  nGen[S3m200] = 1.447 * lumi;
  nGen[S3m300] = .6242 * lumi;
  nGen[S3m400] = .2903 * lumi;
  nGen[S3m500] = .1490 * lumi;
  nGen[S3m600] = .07878* lumi;
  nGen[S4m0]   = 93.26 * lumi;
  nGen[S4m50]  = 110.0 * lumi;
  nGen[S4m100] = 36.37 * lumi;
  nGen[S4m150] = 17.46 * lumi;
  nGen[S4m200] = 9.357 * lumi;
  nGen[S4m300] = 3.216 * lumi;
  nGen[S4m400] = 1.304 * lumi;
  nGen[S4m500] = 0.607 * lumi;
  nGen[S4m600] = 0.298 * lumi;
  nGen[S4m700] = 0.1578* lumi;
  nGen[S4m800] = 0.08733*lumi;
  nGen[S4m900] = 0.05012*lumi;
  nGen[S4m1000]= 0.02969*lumi;

  nGen[ttjets] = 225.2 * lumi;
  nGen[wjets]  = 36257.2*lumi;
  nGen[zjets]  = 3503.7* lumi;

  nGen[tW]    = 11.1 * lumi;
  nGen[tbarW] = 11.1 * lumi;
  nGen[t]     = 56.4 * lumi;
  nGen[tbar]  = 30.7 * lumi;
  nGen[tS]    = 3.79 * lumi;
  nGen[tbarS] = 1.76 * lumi;

  nGen[ww]  = 54.838 * lumi;
  nGen[wz]  = 32.316 * lumi;
  nGen[zz]  = 8.059  * lumi;

  nGen[zn50]  = 381.2 * lumi;
  nGen[zn100] = 160.3 * lumi;
  nGen[zn200] = 41.49 * lumi;
  nGen[zn400] = 5.274 * lumi;

  vector<const char *> signalCenter;  signalCenter. push_back("micro_signals_metSel.root");
                                      signalCenter. push_back("micro_signalsMore_metSel.root");
  vector<const char *> signalJecUp;   signalJecUp.  push_back("micro_signals_metSel_jecUp.root");
                                      signalJecUp.  push_back("micro_signalsMore_metSel_jecUp.root");
  vector<const char *> signalJecDown; signalJecDown.push_back("micro_signals_metSel_jecDown.root");
                                      signalJecDown.push_back("micro_signalsMore_metSel_jecDown.root");
  vector<const char *> ttjetsMain;      ttjetsMain.     push_back("/mnt/hadoop/users/kkotov/new/micro_TT_metSel.root");
  vector<const char *> ttjetsCenter;    ttjetsCenter.   push_back("/mnt/hadoop/users/kkotov/new/micro_TT_metSel.root");
  vector<const char *> ttjetsScaleUp;   ttjetsScaleUp.  push_back("/mnt/hadoop/users/kkotov/new/micro_TTsu_metSel.root");
  vector<const char *> ttjetsScaleDown; ttjetsScaleDown.push_back("/mnt/hadoop/users/kkotov/new/micro_TTsd_metSel.root");
  vector<const char *> ttjetsMatchUp;   ttjetsMatchUp.  push_back("/mnt/hadoop/users/kkotov/new/micro_TTmu_metSel.root");
  vector<const char *> ttjetsMatchDown; ttjetsMatchDown.push_back("/mnt/hadoop/users/kkotov/new/micro_TTmd_metSel.root");
  vector<const char *> ttjetsJecUp;     ttjetsJecUp.    push_back("/mnt/hadoop/users/kkotov/new/micro_TT_metSel_jecUp.root");
  vector<const char *> ttjetsJecDown;   ttjetsJecDown.  push_back("/mnt/hadoop/users/kkotov/new/micro_TT_metSel_jecDown.root");

  vector<const char *> znjetsMain;      znjetsMain.   push_back("/mnt/hadoop/users/kkotov/new/micro_ZN_metSel.root");
  vector<const char *> znjetsCenter;    znjetsCenter. push_back("/mnt/hadoop/users/kkotov/new/micro_ZN_metSel.root");
  vector<const char *> znjetsJecDown;   znjetsJecDown.push_back("/mnt/hadoop/users/kkotov/new/micro_ZN_metSel_jecDown.root");
  vector<const char *> znjetsJecUp;     znjetsJecUp.  push_back("/mnt/hadoop/users/kkotov/new/micro_ZN_metSel_jecUp.root");

  vector<const char *> wjetsMain;
     wjetsMain.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ1_metSel.root");
     wjetsMain.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ2_metSel.root");
     wjetsMain.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ3_metSel.root");
     wjetsMain.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ4_metSel.root");
     wjetsMain.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ5_metSel.root");
  vector<const char *> wjetsCenter;
     wjetsCenter.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ1_metSel.root");
     wjetsCenter.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ2_metSel.root");
     wjetsCenter.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ3_metSel.root");
     wjetsCenter.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ4_metSel.root");
     wjetsCenter.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ5_metSel.root");
  vector<const char *> wjetsScaleUp;    wjetsScaleUp.  push_back("/mnt/hadoop/users/kkotov/new/micro_WJsu_metSel.root");
  vector<const char *> wjetsScaleDown;  wjetsScaleDown.push_back("/mnt/hadoop/users/kkotov/new/micro_WJsd_metSel.root");
  vector<const char *> wjetsMatchUp;    wjetsMatchUp.  push_back("/mnt/hadoop/users/kkotov/new/micro_WJmu_metSel.root");
  vector<const char *> wjetsMatchDown;  wjetsMatchDown.push_back("/mnt/hadoop/users/kkotov/new/micro_WJmd_metSel.root");
  vector<const char *> wjetsJecUp;
     wjetsJecUp.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ1_metSel_jecUp.root");
     wjetsJecUp.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ2_metSel_jecUp.root");
     wjetsJecUp.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ3_metSel_jecUp.root");
     wjetsJecUp.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ4_metSel_jecUp.root");
     wjetsJecUp.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ5_metSel_jecUp.root");
  vector<const char *> wjetsJecDown;
     wjetsJecDown.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ1_metSel_jecDown.root");
     wjetsJecDown.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ2_metSel_jecDown.root");
     wjetsJecDown.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ3_metSel_jecDown.root");
     wjetsJecDown.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ4_metSel_jecDown.root");
     wjetsJecDown.push_back("/mnt/hadoop/users/kkotov/new/micro_WJ5_metSel_jecDown.root");

  vector<const char *> zjetsMain;
     zjetsMain.push_back("/data/users/kkotov/micro_ZJ1_muSel.root");
     zjetsMain.push_back("/data/users/kkotov/micro_ZJ2_muSel.root");
     zjetsMain.push_back("/data/users/kkotov/micro_ZJ3_muSel.root");
     zjetsMain.push_back("/data/users/kkotov/micro_ZJ4_muSel.root");
     zjetsMain.push_back("/data/users/kkotov/micro_ZJ5_muSel.root");
  vector<const char *> zjetsCenter;
     zjetsCenter.push_back("/data/users/kkotov/micro_ZJ1_muSel.root");
     zjetsCenter.push_back("/data/users/kkotov/micro_ZJ2_muSel.root");
     zjetsCenter.push_back("/data/users/kkotov/micro_ZJ3_muSel.root");
     zjetsCenter.push_back("/data/users/kkotov/micro_ZJ4_muSel.root");
     zjetsCenter.push_back("/data/users/kkotov/micro_ZJ5_muSel.root");
  vector<const char *> zjetsScaleUp;    zjetsScaleUp.  push_back("/data/users/kkotov/micro_ZJsu_muSel.root");
  vector<const char *> zjetsScaleDown;  zjetsScaleDown.push_back("/data/users/kkotov/micro_ZJsd_muSel.root");
  vector<const char *> zjetsMatchUp;    zjetsMatchUp.  push_back("/data/users/kkotov/micro_ZJmu_muSel.root");
  vector<const char *> zjetsMatchDown;  zjetsMatchDown.push_back("/data/users/kkotov/micro_ZJmd_muSel.root");
  vector<const char *> zjetsJecUp;
     zjetsJecUp.push_back("/data/users/kkotov/micro_ZJ1_muSel_jecUp.root");
     zjetsJecUp.push_back("/data/users/kkotov/micro_ZJ2_muSel_jecUp.root");
     zjetsJecUp.push_back("/data/users/kkotov/micro_ZJ3_muSel_jecUp.root");
     zjetsJecUp.push_back("/data/users/kkotov/micro_ZJ4_muSel_jecUp.root");
     zjetsJecUp.push_back("/data/users/kkotov/micro_ZJ5_muSel_jecUp.root");
  vector<const char *> zjetsJecDown;
     zjetsJecDown.push_back("/data/users/kkotov/micro_ZJ1_muSel_jecDown.root");
     zjetsJecDown.push_back("/data/users/kkotov/micro_ZJ2_muSel_jecDown.root");
     zjetsJecDown.push_back("/data/users/kkotov/micro_ZJ3_muSel_jecDown.root");
     zjetsJecDown.push_back("/data/users/kkotov/micro_ZJ4_muSel_jecDown.root");
     zjetsJecDown.push_back("/data/users/kkotov/micro_ZJ5_muSel_jecDown.root");

  vector<const char *> wwMain;      wwMain.   push_back("/mnt/hadoop/users/kkotov/new/micro_WW_metSel.root");
  vector<const char *> wwCenter;    wwCenter. push_back("/mnt/hadoop/users/kkotov/new/micro_WW_metSel.root");
  vector<const char *> wwJecDown;   wwJecDown.push_back("/mnt/hadoop/users/kkotov/new/micro_WW_metSel_jecDown.root");
  vector<const char *> wwJecUp;     wwJecUp.  push_back("/mnt/hadoop/users/kkotov/new/micro_WW_metSel_jecUp.root");
  vector<const char *> wzMain;      wzMain.   push_back("/mnt/hadoop/users/kkotov/new/micro_WZ_metSel.root");
  vector<const char *> wzCenter;    wzCenter. push_back("/mnt/hadoop/users/kkotov/new/micro_WZ_metSel.root");
  vector<const char *> wzJecDown;   wzJecDown.push_back("/mnt/hadoop/users/kkotov/new/micro_WZ_metSel_jecDown.root");
  vector<const char *> wzJecUp;     wzJecUp.  push_back("/mnt/hadoop/users/kkotov/new/micro_WZ_metSel_jecUp.root");
  vector<const char *> zzMain;      zzMain.   push_back("/mnt/hadoop/users/kkotov/new/micro_ZZ_metSel.root");
  vector<const char *> zzCenter;    zzCenter. push_back("/mnt/hadoop/users/kkotov/new/micro_ZZ_metSel.root");
  vector<const char *> zzJecDown;   zzJecDown.push_back("/mnt/hadoop/users/kkotov/new/micro_ZZ_metSel_jecDown.root");
  vector<const char *> zzJecUp;     zzJecUp.  push_back("/mnt/hadoop/users/kkotov/new/micro_ZZ_metSel_jecUp.root");

  vector<const char *> topMain;     topMain.   push_back("/mnt/hadoop/users/kkotov/new/micro_T_metSel.root");
  vector<const char *> topCenter;   topCenter. push_back("/mnt/hadoop/users/kkotov/new/micro_T_metSel.root");
  vector<const char *> topJecDown;  topJecDown.push_back("/mnt/hadoop/users/kkotov/new/micro_T_metSel_jecDown.root");
  vector<const char *> topJecUp;    topJecUp.  push_back("/mnt/hadoop/users/kkotov/new/micro_T_metSel_jecUp.root");

  vector<const char *> sampleMain;
  vector<const char *> sampleCenter;
  vector<const char *> sampleScaleUp;
  vector<const char *> sampleScaleDown;
  vector<const char *> sampleMatchUp;
  vector<const char *> sampleMatchDown;
  vector<const char *> sampleJecUp;
  vector<const char *> sampleJecDown;

  switch( group ){
    case TT:
      sampleMain        = ttjetsMain;
      sampleCenter      = ttjetsCenter;
      sampleScaleUp     = ttjetsScaleUp;
      sampleScaleDown   = ttjetsScaleDown;
      sampleMatchUp     = ttjetsMatchUp;
      sampleMatchDown   = ttjetsMatchDown;
      sampleJecUp       = ttjetsJecUp;
      sampleJecDown     = ttjetsJecDown;
    break;
    case WJ:
      sampleMain        = wjetsMain;
      sampleCenter      = wjetsCenter;
      sampleScaleUp     = wjetsScaleUp;
      sampleScaleDown   = wjetsScaleDown;
      sampleMatchUp     = wjetsMatchUp;
      sampleMatchDown   = wjetsMatchDown;
      sampleJecUp       = wjetsJecUp;
      sampleJecDown     = wjetsJecDown;
    break;
    case ZN:
      sampleMain        = znjetsMain;
      sampleCenter      = znjetsCenter;
//      sampleScaleUp     = znjetsScaleUp;
//      sampleScaleDown   = znjetsScaleDown;
//      sampleMatchUp     = znjetsMatchUp;
//      sampleMatchDown   = znjetsMatchDown;
      sampleJecUp       = znjetsJecUp;
      sampleJecDown     = znjetsJecDown;
    break;
    case VV:
      sampleMain.insert( sampleMain.end(), wwMain.begin(), wwMain.end() );
      sampleMain.insert( sampleMain.end(), wzMain.begin(), wzMain.end() );
      sampleMain.insert( sampleMain.end(), zzMain.begin(), zzMain.end() );
      sampleCenter.insert( sampleCenter.end(), wwCenter.begin(), wwCenter.end() );
      sampleCenter.insert( sampleCenter.end(), wzCenter.begin(), wzCenter.end() );
      sampleCenter.insert( sampleCenter.end(), zzCenter.begin(), zzCenter.end() );
      sampleJecUp.insert( sampleJecUp.end(), wwJecUp.begin(), wwJecUp.end() );
      sampleJecUp.insert( sampleJecUp.end(), wzJecUp.begin(), wzJecUp.end() );
      sampleJecUp.insert( sampleJecUp.end(), zzJecUp.begin(), zzJecUp.end() );
      sampleJecDown.insert( sampleJecDown.end(), wwJecDown.begin(), wwJecDown.end() );
      sampleJecDown.insert( sampleJecDown.end(), wzJecDown.begin(), wzJecDown.end() );
      sampleJecDown.insert( sampleJecDown.end(), zzJecDown.begin(), zzJecDown.end() );
    break;
   case Top:
      sampleMain        = topMain;
      sampleCenter      = topCenter;
      sampleJecUp       = topJecUp;
      sampleJecDown     = topJecDown;
   break;
   case S:
      sampleMain        = signalCenter;
      sampleCenter      = signalCenter;
      sampleJecUp       = signalJecUp;
      sampleJecDown     = signalJecDown;
   break;
   default : break;
}


int selection = 31; // up to stage 5

double mets[7]   = {0, 250., 300., 350., 400., 450., 500.};
//double mets[2]   = {0, MET};

int metStart = 1, metEnd = 5;
//int metStart = 1, metEnd = 2;

for(int b=0; b<2; b++)
{
  cout<<"Requiring "<<b<<"-tag (X=="<<b<<")"<<endl;

  vector<Pass> allResults[7];

  for(int m=metStart; m<metEnd; m++){

     vector<Pass> &results = allResults[m];
     for(vector<int>::const_iterator type=groups[group].begin(); type!=groups[group].end(); type++){
cout<<" type="<<(*type)<<" met="<<mets[m]<<endl;
        Pass res;
        res.passMain      = cut(selection, mets[m], b, sampleMain,      *type)*lumiScale;
        res.passCenter    = cut(selection, mets[m], b, sampleCenter,    *type)*lumiScale;
        res.passJecUp     = cut(selection, mets[m], b, sampleJecUp,     *type)*lumiScale;
        res.passJecDown   = cut(selection, mets[m], b, sampleJecDown,   *type)*lumiScale;
        res.passScaleUp   = 0;//cut(selection, mets[m], b, sampleScaleUp,   *type)*lumiScale;
        res.passScaleDown = 0;//cut(selection, mets[m], b, sampleScaleDown, *type)*lumiScale;
        res.passMatchUp   = 0;//cut(selection, mets[m], b, sampleMatchUp,   *type)*lumiScale;
        res.passMatchDown = 0;//cut(selection, mets[m], b, sampleMatchDown, *type)*lumiScale;
        res.name          = names[*type];
        results.push_back(res);
     }

     double norm = 0;
     cout<<"bg"<<b<<"b         ->SetBinContent("<<(group+1)<<",";
     for(vector<Pass>::const_iterator res=results.begin(); res!=results.end(); res++){
        cout<<res->passMain<<" + ";
        norm += res->passMain;
     }
     cout<<"0); //"<<norm<<endl;

     double sumJecUp = 0;
     cout<<"bg"<<b<<"bJecUp    ->SetBinContent("<<(group+1)<<",";
     for(vector<Pass>::const_iterator res=results.begin(); res!=results.end(); res++){
        cout<<res->passMain<<"*(1+"<<(res->passCenter>0 ? (res->passJecUp-res->passCenter)/res->passCenter : 0)<<"/*"<<res->passJecUp<<"*/) +";
        sumJecUp += res->passJecUp;
     }
     cout<<"0); //"<<sumJecUp<<" = "<<sumJecUp/norm<<endl;

     double sumJecDown = 0;
     cout<<"bg"<<b<<"bJecDown  ->SetBinContent("<<(group+1)<<",";
     for(vector<Pass>::const_iterator res=results.begin(); res!=results.end(); res++){
        cout<<res->passMain<<"*(1-"<<(res->passCenter>0 ? (res->passCenter-res->passJecDown)/res->passCenter : 0)<<"/*"<<res->passJecDown<<"*/) +";
        sumJecDown += res->passJecDown;
     }
     cout<<"0); //"<<sumJecDown<<" = "<<sumJecDown/norm<<endl;

     double sumScaleUp = 0;
     cout<<"bg"<<b<<"bScaleUp  ->SetBinContent("<<(group+1)<<",";
     for(vector<Pass>::const_iterator res=results.begin(); res!=results.end(); res++){
        double passScaleUp = ( res->passScaleUp < res->passScaleDown ? res->passScaleDown : res->passScaleUp );
        sumScaleUp += passScaleUp;
        if( passScaleUp>0 )
           cout<<res->passMain<<"*(1+"<<(res->passCenter>0 ? (passScaleUp-res->passCenter)/res->passCenter : 0)<<"/*"<<passScaleUp<<"*/) +";
        else
           cout<<res->passMain<<"*(1+SCALE"<<b<<res->name<<") +";
     }
     cout<<"0); //"<<sumScaleUp<<" = "<<sumScaleUp/norm<<endl;

     double sumScaleDown = 0;
     cout<<"bg"<<b<<"bScaleDown->SetBinContent("<<(group+1)<<",";
     for(vector<Pass>::const_iterator res=results.begin(); res!=results.end(); res++){
        double passScaleDown = ( res->passScaleUp < res->passScaleDown ? res->passScaleUp : res->passScaleDown );
        sumScaleDown += passScaleDown;
        if( passScaleDown>0 )
           cout<<res->passMain<<"*(1-"<<(res->passCenter>0 ? (res->passCenter-passScaleDown)/res->passCenter : 0)<<"/*"<<passScaleDown<<"*/) +";
        else
           cout<<res->passMain<<"*(1-SCALE"<<b<<res->name<<") +";
     }
     cout<<"0); //"<<sumScaleDown<<" = "<<sumScaleDown/norm<<endl;

     double sumMatchUp = 0;
     cout<<"bg"<<b<<"bMatchUp  ->SetBinContent("<<(group+1)<<",";
     for(vector<Pass>::const_iterator res=results.begin(); res!=results.end(); res++){
        sumMatchUp += res->passMatchUp;
        if( res->passMatchUp>0 )
           cout<<res->passMain<<"*(1-"<<(res->passCenter>0 ? (res->passCenter-res->passMatchUp)/res->passCenter : 0)<<"/*"<<res->passMatchUp<<"*/) +";
        else
           cout<<res->passMain<<"*(1-0) +";
     }
     cout<<"0); //"<<sumMatchUp<<" = "<<sumMatchUp/norm<<endl;

     double sumMatchDown = 0;
     cout<<"bg"<<b<<"bMatchDown->SetBinContent("<<(group+1)<<",";
     for(vector<Pass>::const_iterator res=results.begin(); res!=results.end(); res++){
        sumMatchDown = res->passMatchDown;
        if( res->passMatchDown>0 )
           cout<<res->passMain<<"*(1+"<<(res->passCenter>0 ? (res->passMatchDown-res->passCenter)/res->passCenter : 0)<<"/*"<<res->passMatchDown<<"*/) +";
        else
           cout<<res->passMain<<"*(1+0) +";
     }
     cout<<"0); //"<<sumMatchDown<<" = "<<sumMatchDown/norm<<endl;

     cout<<"jec: $^{+"<<setw(4)<<(sumJecUp/norm-1.)*100.<<"\\%}$ $_{"<<setw(4)<<(sumJecDown/norm-1.)*100.<<"\\%}$"<<endl;

     cout<<"bg"<<b<<"bPDFplus  ->SetBinContent("<<(group+1)<<",";
     for(vector<Pass>::const_iterator res=results.begin(); res!=results.end(); res++)
        cout<<res->passMain<<"*(1+PDF"<<b<<res->name<<") +";
     cout<<"0);"<<endl;

     cout<<"bg"<<b<<"bPDFminus->SetBinContent("<<(group+1)<<",";
     for(vector<Pass>::const_iterator res=results.begin(); res!=results.end(); res++)
        cout<<res->passMain<<"*(1-PDF"<<b<<res->name<<") +";
     cout<<"0);"<<endl;

  }
/////////////////////////////////

  if( group == TT || group == WJ ){
     string name;
     switch( group ) {
        case TT : name="tt"; break;
        case WJ : name="wj"; break;
        default : break;
     }
     cout<<"double "<<name<<"Eff"<<b<<"b[] = {";
     for(int m=metStart; m<metEnd; m++){
        vector<Pass>::const_iterator res = allResults[m].begin();
        cout<<res->passMain/nGen[ *(groups[group].begin()) ];
        if( m != metEnd-1 ) cout<<", ";
     }
     cout<<"};"<<endl;

     cout<<"double "<<name<<"Jec"<<b<<"b[] = {";
     for(int m=metStart; m<metEnd; m++){
        vector<Pass>::const_iterator res = allResults[m].begin();
        cout<<( fabs(res->passJecUp-res->passCenter) > fabs(res->passCenter-res->passJecDown) ?
                    (res->passJecUp-res->passCenter)/res->passCenter :
                    (res->passCenter-res->passJecDown)/res->passCenter );
        if( m != metEnd-1 ) cout<<", ";
     }
     cout<<"};"<<endl;

     cout<<"double "<<name<<"Scale"<<b<<"b[] = {";
     for(int m=metStart; m<metEnd; m++){
        vector<Pass>::const_iterator res = allResults[m].begin();
        double passScaleUp   = ( res->passScaleUp>res->passScaleDown ? res->passScaleUp   : res->passScaleDown );
        double passScaleDown = ( res->passScaleUp>res->passScaleDown ? res->passScaleDown : res->passScaleUp   );
        cout<<(  passScaleUp-res->passCenter > res->passCenter-passScaleDown ?
                (passScaleUp-res->passCenter  )/res->passCenter :
                (res->passCenter-passScaleDown)/res->passCenter );
        if( m != metEnd-1 ) cout<<", ";
     }
     cout<<"};"<<endl;

     cout<<"double "<<name<<"Match"<<b<<"b[] = {";
     for(int m=metStart; m<metEnd; m++){
        vector<Pass>::const_iterator res = allResults[m].begin();
        double passMatchUp   = ( res->passMatchUp>res->passMatchDown ? res->passMatchUp   : res->passMatchDown );
        double passMatchDown = ( res->passMatchUp>res->passMatchDown ? res->passMatchDown : res->passMatchUp   );
        cout<<(  passMatchUp-res->passCenter > res->passCenter-passMatchDown ?
                (passMatchUp-res->passCenter)/res->passCenter :
                (res->passCenter-passMatchDown)/res->passCenter );
        if( m != metEnd-1 ) cout<<", ";
     }
     cout<<"};"<<endl;
  }

  if( group == Top || group == VV ){
     string name;
     switch( group ) {
        case Top : name="t"; break;
        case VV  : name="vv"; break;
        default : break;
     }

     cout<<"double "<<name<<"Yield"<<b<<"b[] = {";
     for(int m=metStart; m<metEnd; m++){
        vector<Pass> &results = allResults[m];
        for(vector<Pass>::const_iterator res=results.begin(); res!=results.end(); res++)
           cout<<res->passMain<<" + ";
        cout<<"0"<<endl;
        if( m != metEnd-1 ) cout<<", ";
     }
     cout<<"};"<<endl;

     cout<<"double "<<name<<"Jec"<<b<<"b[] = {";
     for(int m=metStart; m<metEnd; m++){
        vector<Pass> &results = allResults[m];
        double passJecUp=0, passJecDown=0, passCenter=0;
        for(vector<Pass>::const_iterator res=results.begin(); res!=results.end(); res++){
           passJecUp   += res->passJecUp;
           passJecDown += res->passJecDown;
           passCenter  += res->passCenter;
        }
        cout<<( passJecUp-passCenter > passCenter-passJecDown ?
               (passJecUp -passCenter )/passCenter :
               (passCenter-passJecDown)/passCenter );

        if( m != metEnd-1 ) cout<<", ";
     }
     cout<<"};"<<endl;
  }

  if( group == ZN || group == S ){

     for(vector<int>::iterator type = groups[group].begin(); type != groups[group].end(); type++){

        string name = names[*type];

        cout<<"double "<<name<<"Eff"<<b<<"b[] = {";
        for(int m=metStart; m<metEnd; m++){
           vector<Pass>::const_iterator res = allResults[m].begin() + distance(groups[group].begin(),type);
           cout<<res->passMain/nGen[*type];
           if( m != metEnd-1 ) cout<<", ";
        }
        cout<<"};"<<endl;

        cout<<"double "<<name<<"Jec"<<b<<"b[] = {";
        for(int m=metStart; m<metEnd; m++){
           vector<Pass>::const_iterator res = allResults[m].begin() + distance(groups[group].begin(),type);
           if( res->passCenter>0 )
              cout<<( fabs(res->passJecUp-res->passCenter) > fabs(res->passCenter-res->passJecDown) ?
                          (res->passJecUp-res->passCenter)/res->passCenter :
                          (res->passCenter-res->passJecDown)/res->passCenter );
           else cout<<0;

           if( m != metEnd-1 ) cout<<", ";
        }
        cout<<"};"<<endl;
     }

  }

}
}
