#include <iostream>
#include <map>
#include <set>
#include <stdio.h>
#include "TH1.h"
#include "TFile.h"
#include "TChain.h"
#include "TLorentzVector.h"
//#include "../../../tdrstyle.C"

std::map<int,std::set<int> > uniqueEvents;

enum {Data=0, TTJets=1, WJets=2, ZJets=3, Znunu=4, QCD=8, Top=16, WW=24, WZ=25, ZZ=26, W1J=67, W2J=68, W3J=69, W4J=70, SIG=1000, A=1001, B=1002, C=1003, D=1004, E=1005};
enum {CENTER=0, Q2UP=1, Q2DOWN=2, MATCHUP=3, MATCHDOWN=4};

void tPeak(int lastStage=0,int nBjets=-1, double MET=0, int process=-1, int variation=CENTER){
////gROOT->ProcessLine(".L ../../../tdrstyle.C");
//setTDRStyle();
if( lastStage>9 && lastStage<1 ){
   cout<<"Wrong stage:"<<lastStage<<" (first argument should be between 1 and 9)"<<endl;
   return;
}
unsigned    lookUpMask[10] = {1, 3, 7, 15, 31, 31, 31, 31, 31, 31};
unsigned    lookUpMET [10] = {0, 0, 0,  0,  0,  0,150,250,350,450};
const char *lookUpName[10] = {"","3jets/tPeakStage1trg","3jets/tPeakStage2trg","3jets/tPeakStage3trg","3jets/tPeakStage4trg",
"3jets/tPeakStage4", "tPeakStage4met150", "tPeakStage4met250", "tPeakStage4met350", "tPeakStage4met450"};

TChain *micro = new TChain("micro");

if( process==-1 || process==QCD ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_QCD_170_300_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_QCD_300_470_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_QCD_470_600_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_QCD_600_800_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_QCD_800_1000_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_QCD_1000_1400_metSel.root");
}

if( process==-1 || process==SIG ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_signals_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.05.12/micro_signals_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.05.12/micro_signalsMore_metSel_jecDown.root");
}
if( process==-1 || process==Znunu ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZN1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZN2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZN3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZN4_metSel.root");
}
if( process==-1 || process==ZJets ){
switch(variation){
case CENTER:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ5_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ6_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ7_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ8_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ9_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ10_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ11_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ12_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ13_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ14_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ15_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJ16_metSel.root");
break;
case Q2UP:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJsu_metSel.root");
return;
break;
case Q2DOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJsd_metSel.root");
break;
return;
case MATCHUP:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJmu_metSel.root");
return;
break;
case MATCHDOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJmd_metSel.root");
return;
break;
default: return; break;
}
}
if( process==-1 || process==WJets ){
switch(variation){
case CENTER:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ5_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ6_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ7_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ8_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ9_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ10_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ11_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ12_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ13_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ14_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ15_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ16_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ17_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ18_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ19_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ20_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ21_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ22_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ23_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ24_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ25_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ26_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ27_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ28_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJ29_metSel.root");
break;
case Q2UP:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJsu_metSel.root"); //??
break;
case Q2DOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJsd_metSel.root"); //??
break;
case MATCHUP:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJmu_metSel.root"); //??
break;
case MATCHDOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJmd_metSel.root"); //??
break;
default: return; break;
}
}
if( process==-1 || process==W1J ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W1J1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W1J2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W1J3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W1J4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W1J5_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W1J6_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W1J7_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W1J8_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W1J9_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W1J10_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W1J11_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W1J12_metSel.root");
}
if( process==-1 || process==W2J ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J5_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J6_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J7_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J8_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J9_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J10_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J11_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J12_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J13_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J14_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J15_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J16_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W2J17_metSel.root");
}
if( process==-1 || process==W3J ){
switch(variation){
case CENTER:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3J1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3J2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3J3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3J4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3J5_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3J6_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3J7_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3J8_metSel.root");
break;
case Q2UP:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jsu1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jsu2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jsu3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jsu4_metSel.root");
break;
case Q2DOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jsd1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jsd2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jsd3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jsd4_metSel.root");
break;
case MATCHUP:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jmu1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jmu2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jmu3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jmu4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jmu5_metSel.root");
break;
case MATCHDOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jmd1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jmd2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jmd3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jmd4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W3Jmd5_metSel.root");
break;
default: return; break;
}
}
if( process==-1 || process==W4J ){
switch(variation){
case CENTER:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4J1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4J2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4J3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4J4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4J5_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4J6_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4J7_metSel.root");
break;
case Q2UP:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jsu1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jsu2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jsu3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jsu4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jsu5_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jsu6_metSel.root");
break;
case Q2DOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jsd1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jsd2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jsd3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jsd4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jsd5_metSel.root");
break;
case MATCHUP:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jmu1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jmu2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jmu3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jmu4_metSel.root");
break;
case MATCHDOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jmd1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jmd2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jmd3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jmd4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_W4Jmd5_metSel.root");
break;
default: return; break;
}
}
if( process==-1 || process==TTJets ){
switch(variation){
case CENTER:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TT1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TT2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TT3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TT4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TT5_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TT6_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TT7_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TT8_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TT9_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TT10_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TT11_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TT12_metSel.root");
break;
case Q2UP:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTsu_metSel.root");
break;
case Q2DOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTsd_metSel.root");
break;
case MATCHUP:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTmu_metSel.root");
break;
case MATCHDOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTmd_metSel.root");
break;
default: return; break;
}
}
if( process==-1 || process==Top ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_T1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_T2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_T3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_T4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_T5_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_T6_metSel.root");
}
if( process==-1 || process==WW ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WW1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WW2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WW3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WW4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WW5_metSel.root");
}
if( process==-1 || process==WZ ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WZ1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WZ2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WZ3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WZ4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WZ5_metSel.root");
}
if( process==-1 || process==ZZ ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZZ1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZZ2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZZ3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZZ4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZZ5_metSel.root");
}
if( process==-1 || process==A ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012A_metSel.root");
//cout<<"EntriesA= "<<micro->GetEntries()<<endl;
//return;
}
if( process==-1 || process==B ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012B_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012B2_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012B3_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012B4_metSel.root");
//cout<<"EntriesB= "<<micro->GetEntries()<<endl;
//return;
}
if( process==-1 || process==C ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012C_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012C2_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012C3_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012C4_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012C5_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012C6_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012C7_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012C8_metSel.root");
//cout<<"EntriesC= "<<micro->GetEntries()<<endl;
//return;
}
if( process==-1 || process==D ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012D_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012D2_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012D3_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012D4_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012D5_metSel.root");
//micro->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012D6_metSel.root");
//cout<<"EntriesD= "<<micro->GetEntries()<<endl;
//return;
}
//double lumiScale = (0.802 + 4.403 + 6.388 + 7.248)/5.;
double lumiScale = ( 19.7 )/5.;

//micro->AddFile("/data/users/kkotov/2013.05.12/micro_JetHT_Run2012B-13Jul2012-v1_AOD_metSel.root");

double scaler2012A      = 1;
double scaler2012B      = 1;
double scalerSingleTop  = 1;
double scalerTTJets     = 1;
double scalerWJetsToLNu = (process==W1J || process==W2J || process==W3J || process==W4J ? 1.23 : 1);
double scalerZJetsToLL  = 1;
double scalerZJetsToNuNu= 1;
double scalerWW         = 1;
double scalerWZ         = 1;
double scalerZZ         = 1;
double scalerQCD        = 1;

double leadingJetPtRec, leadingJetEtaRec, leadingJetPhiRec, leadingJetCSV;
double subleadJetPtRec, subleadJetEtaRec, subleadJetPhiRec, subleadJetCSV;
double thirdJetPtRec, thirdJetEtaRec, thirdJetPhiRec, thirdJetCSV;
double forthJetPtRec, forthJetEtaRec, forthJetPhiRec, forthJetCSV;

double metPtRec, metPhiRec, thMrec, whMrec;
double weight;
int    selection, type, run, numberOfJets, numberOfBJets, nVerts;
char   fileName[32];
ULong64_t trig;

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
micro->SetBranchAddress("nVerts",          &nVerts);

micro->SetBranchAddress("whMrec",   &whMrec);
micro->SetBranchAddress("thMrec",   &thMrec);
micro->SetBranchAddress("metPtRec", &metPtRec);
micro->SetBranchAddress("metPhiRec",&metPhiRec);
micro->SetBranchAddress("weight",   &weight);
micro->SetBranchAddress("selection",&selection);
micro->SetBranchAddress("type",     &type);
micro->SetBranchAddress("run",      &run);
micro->SetBranchAddress("otherTRIGs", &trig);
//micro->SetBranchAddress("fileName", fileName);
/*
double   chi2;
double   bJetPtRec,   bJetEtaRec,   bJetPhiRec;
double jet1WhPtRec, jet1WhEtaRec, jet1WhPhiRec;
double jet2WhPtRec, jet2WhEtaRec, jet2WhPhiRec;
micro->SetBranchAddress("Chi2", &chi2);
micro->SetBranchAddress("bJetPtRec",   &bJetPtRec);
micro->SetBranchAddress("bJetEtaRec",  &bJetEtaRec);
micro->SetBranchAddress("bJetPhiRec",  &bJetPhiRec);
micro->SetBranchAddress("jet1WhPtRec", &jet1WhPtRec);
micro->SetBranchAddress("jet1WhEtaRec",&jet1WhEtaRec);
micro->SetBranchAddress("jet1WhPhiRec",&jet1WhPhiRec);
micro->SetBranchAddress("jet2WhPtRec", &jet2WhPtRec);
micro->SetBranchAddress("jet2WhEtaRec",&jet2WhEtaRec);
micro->SetBranchAddress("jet2WhPhiRec",&jet2WhPhiRec);
*/

double lepton1PtRec,  lepton2PtRec,  lepton3PtRec;
double lepton1EtaRec, lepton2EtaRec, lepton3EtaRec;
double lepton1PhiRec, lepton2PhiRec, lepton3PhiRec;
int    lepton1IsTight, lepton2IsTight, lepton3IsTight;

micro->SetBranchAddress("lepton1PtRec",&lepton1PtRec);
micro->SetBranchAddress("lepton2PtRec",&lepton2PtRec);
micro->SetBranchAddress("lepton3PtRec",&lepton3PtRec);
micro->SetBranchAddress("lepton1EtaRec",&lepton1EtaRec);
micro->SetBranchAddress("lepton2EtaRec",&lepton2EtaRec);
micro->SetBranchAddress("lepton3EtaRec",&lepton3EtaRec);
micro->SetBranchAddress("lepton1PhiRec",&lepton1PhiRec);
micro->SetBranchAddress("lepton2PhiRec",&lepton2PhiRec);
micro->SetBranchAddress("lepton3PhiRec",&lepton3PhiRec);
//micro->SetBranchAddress("lepton1IsTight",&lepton1IsTight);
//micro->SetBranchAddress("lepton2IsTight",&lepton2IsTight);
//micro->SetBranchAddress("lepton3IsTight",&lepton3IsTight);

double t1PtGen, t2PtGen;
if( process == TTJets ){
micro->SetBranchAddress("t1PtGen",&t1PtGen);
micro->SetBranchAddress("t2PtGen",&t2PtGen);
}

int    nBinsM=1500, nBinsMET=750, nBinsPt=1000, nBinsEta=500, nBinsPhi=500, nBinsMETphi=500;
double leftM=0, rightM=1500, leftMET=0, rightMET=750, leftPt=0, rightPt=1000, leftEta=-2.5, rightEta=2.5, leftPhi=-3.1415927, rightPhi=3.1415927, leftMETphi=-3.1415927, rightMETphi=3.1415927;

TH1F *triJetMassAB = new TH1F("triJetMassAB","",nBinsM, leftM, rightM);
TH1F *triJetMassTT = new TH1F("triJetMassTT","",nBinsM, leftM, rightM);
TH1F *triJetMassWJ = new TH1F("triJetMassWJ","",nBinsM, leftM, rightM);
TH1F *triJetMassZJ = new TH1F("triJetMassZJ","",nBinsM, leftM, rightM);
TH1F *triJetMassT  = new TH1F("triJetMassT", "",nBinsM, leftM, rightM);
TH1F *triJetMassVV = new TH1F("triJetMassVV","",nBinsM, leftM, rightM);
TH1F *triJetMassQCD= new TH1F("triJetMassQCD","",nBinsM, leftM, rightM);

TH1F *topMassAB = new TH1F("topMassAB","",nBinsM, leftM, rightM);
TH1F *topMassTT = new TH1F("topMassTT","",nBinsM, leftM, rightM);
TH1F *topMassWJ = new TH1F("topMassWJ","",nBinsM, leftM, rightM);
TH1F *topMassZJ = new TH1F("topMassZJ","",nBinsM, leftM, rightM);
TH1F *topMassT  = new TH1F("topMassT", "",nBinsM, leftM, rightM);
TH1F *topMassVV = new TH1F("topMassVV","",nBinsM, leftM, rightM);
TH1F *topMassQCD= new TH1F("topMassQCD","",nBinsM, leftM, rightM);

TH1F *topMassAB2p1 = new TH1F("topMassAB2p1","",nBinsM, leftM, rightM);
TH1F *topMassTT2p1 = new TH1F("topMassTT2p1","",nBinsM, leftM, rightM);
TH1F *topMassWJ2p1 = new TH1F("topMassWJ2p1","",nBinsM, leftM, rightM);
TH1F *topMassZJ2p1 = new TH1F("topMassZJ2p1","",nBinsM, leftM, rightM);
TH1F *topMassT2p1  = new TH1F("topMassT2p1", "",nBinsM, leftM, rightM);
TH1F *topMassVV2p1 = new TH1F("topMassVV2p1","",nBinsM, leftM, rightM);
TH1F *topMassQCD2p1= new TH1F("topMassQCD2p1","",nBinsM, leftM, rightM);

TH1F *metAB = new TH1F("metAB", "",nBinsMET, leftMET, rightMET);
TH1F *metTT = new TH1F("metTT", "",nBinsMET, leftMET, rightMET);
TH1F *metWJ = new TH1F("metWJ", "",nBinsMET, leftMET, rightMET);
TH1F *metZJ = new TH1F("metZJ", "",nBinsMET, leftMET, rightMET);
TH1F *metT  = new TH1F("metT",  "",nBinsMET, leftMET, rightMET);
TH1F *metVV = new TH1F("metVV", "",nBinsMET, leftMET, rightMET);
TH1F *metQCD= new TH1F("metQCD","",nBinsMET, leftMET, rightMET);

TH1F *metPhiAB = new TH1F("metPhiAB", "",nBinsMETphi, leftMETphi, rightMETphi);
TH1F *metPhiTT = new TH1F("metPhiTT", "",nBinsMETphi, leftMETphi, rightMETphi);
TH1F *metPhiWJ = new TH1F("metPhiWJ", "",nBinsMETphi, leftMETphi, rightMETphi);
TH1F *metPhiZJ = new TH1F("metPhiZJ", "",nBinsMETphi, leftMETphi, rightMETphi);
TH1F *metPhiT  = new TH1F("metPhiT",  "",nBinsMETphi, leftMETphi, rightMETphi);
TH1F *metPhiVV = new TH1F("metPhiVV", "",nBinsMETphi, leftMETphi, rightMETphi);
TH1F *metPhiQCD= new TH1F("metPhiQCD","",nBinsMETphi, leftMETphi, rightMETphi);

TH1F *l1PtAB = new TH1F("l1PtAB", "",nBinsPt, leftPt, rightPt);
TH1F *l1PtTT = new TH1F("l1PtTT", "",nBinsPt, leftPt, rightPt);
TH1F *l1PtWJ = new TH1F("l1PtWJ", "",nBinsPt, leftPt, rightPt);
TH1F *l1PtZJ = new TH1F("l1PtZJ", "",nBinsPt, leftPt, rightPt);
TH1F *l1PtT  = new TH1F("l1PtT",  "",nBinsPt, leftPt, rightPt);
TH1F *l1PtVV = new TH1F("l1PtVV", "",nBinsPt, leftPt, rightPt);
TH1F *l1PtQCD= new TH1F("l1PtQCD","",nBinsPt, leftPt, rightPt);

TH1F *j1PtAB = new TH1F("j1PtAB", "",nBinsPt, leftPt, rightPt);
TH1F *j1PtTT = new TH1F("j1PtTT", "",nBinsPt, leftPt, rightPt);
TH1F *j1PtWJ = new TH1F("j1PtWJ", "",nBinsPt, leftPt, rightPt);
TH1F *j1PtZJ = new TH1F("j1PtZJ", "",nBinsPt, leftPt, rightPt);
TH1F *j1PtT  = new TH1F("j1PtT",  "",nBinsPt, leftPt, rightPt);
TH1F *j1PtVV = new TH1F("j1PtVV", "",nBinsPt, leftPt, rightPt);
TH1F *j1PtQCD= new TH1F("j1PtQCD","",nBinsPt, leftPt, rightPt);

TH1F *j2PtAB = new TH1F("j2PtAB", "",nBinsPt, leftPt, rightPt);
TH1F *j2PtTT = new TH1F("j2PtTT", "",nBinsPt, leftPt, rightPt);
TH1F *j2PtWJ = new TH1F("j2PtWJ", "",nBinsPt, leftPt, rightPt);
TH1F *j2PtZJ = new TH1F("j2PtZJ", "",nBinsPt, leftPt, rightPt);
TH1F *j2PtT  = new TH1F("j2PtT",  "",nBinsPt, leftPt, rightPt);
TH1F *j2PtVV = new TH1F("j2PtVV", "",nBinsPt, leftPt, rightPt);
TH1F *j2PtQCD= new TH1F("j2PtQCD","",nBinsPt, leftPt, rightPt);

TH1F *j3PtAB = new TH1F("j3PtAB", "",nBinsPt, leftPt, rightPt);
TH1F *j3PtTT = new TH1F("j3PtTT", "",nBinsPt, leftPt, rightPt);
TH1F *j3PtWJ = new TH1F("j3PtWJ", "",nBinsPt, leftPt, rightPt);
TH1F *j3PtZJ = new TH1F("j3PtZJ", "",nBinsPt, leftPt, rightPt);
TH1F *j3PtT  = new TH1F("j3PtT",  "",nBinsPt, leftPt, rightPt);
TH1F *j3PtVV = new TH1F("j3PtVV", "",nBinsPt, leftPt, rightPt);
TH1F *j3PtQCD= new TH1F("j3PtQCD","",nBinsPt, leftPt, rightPt);

TH1F *l1EtaAB = new TH1F("l1EtaAB", "",nBinsEta, leftEta, rightEta);
TH1F *l1EtaTT = new TH1F("l1EtaTT", "",nBinsEta, leftEta, rightEta);
TH1F *l1EtaWJ = new TH1F("l1EtaWJ", "",nBinsEta, leftEta, rightEta);
TH1F *l1EtaZJ = new TH1F("l1EtaZJ", "",nBinsEta, leftEta, rightEta);
TH1F *l1EtaT  = new TH1F("l1EtaT",  "",nBinsEta, leftEta, rightEta);
TH1F *l1EtaVV = new TH1F("l1EtaVV", "",nBinsEta, leftEta, rightEta);
TH1F *l1EtaQCD= new TH1F("l1EtaQCD","",nBinsEta, leftEta, rightEta);

TH1F *j1EtaAB = new TH1F("j1EtaAB", "",nBinsEta, leftEta, rightEta);
TH1F *j1EtaTT = new TH1F("j1EtaTT", "",nBinsEta, leftEta, rightEta);
TH1F *j1EtaWJ = new TH1F("j1EtaWJ", "",nBinsEta, leftEta, rightEta);
TH1F *j1EtaZJ = new TH1F("j1EtaZJ", "",nBinsEta, leftEta, rightEta);
TH1F *j1EtaT  = new TH1F("j1EtaT",  "",nBinsEta, leftEta, rightEta);
TH1F *j1EtaVV = new TH1F("j1EtaVV", "",nBinsEta, leftEta, rightEta);
TH1F *j1EtaQCD= new TH1F("j1EtaQCD","",nBinsEta, leftEta, rightEta);

TH1F *j2EtaAB = new TH1F("j2EtaAB", "",nBinsEta, leftEta, rightEta);
TH1F *j2EtaTT = new TH1F("j2EtaTT", "",nBinsEta, leftEta, rightEta);
TH1F *j2EtaWJ = new TH1F("j2EtaWJ", "",nBinsEta, leftEta, rightEta);
TH1F *j2EtaZJ = new TH1F("j2EtaZJ", "",nBinsEta, leftEta, rightEta);
TH1F *j2EtaT  = new TH1F("j2EtaT",  "",nBinsEta, leftEta, rightEta);
TH1F *j2EtaVV = new TH1F("j2EtaVV", "",nBinsEta, leftEta, rightEta);
TH1F *j2EtaQCD= new TH1F("j2EtaQCD","",nBinsEta, leftEta, rightEta);

TH1F *j3EtaAB = new TH1F("j3EtaAB", "",nBinsEta, leftEta, rightEta);
TH1F *j3EtaTT = new TH1F("j3EtaTT", "",nBinsEta, leftEta, rightEta);
TH1F *j3EtaWJ = new TH1F("j3EtaWJ", "",nBinsEta, leftEta, rightEta);
TH1F *j3EtaZJ = new TH1F("j3EtaZJ", "",nBinsEta, leftEta, rightEta);
TH1F *j3EtaT  = new TH1F("j3EtaT",  "",nBinsEta, leftEta, rightEta);
TH1F *j3EtaVV = new TH1F("j3EtaVV", "",nBinsEta, leftEta, rightEta);
TH1F *j3EtaQCD= new TH1F("j3EtaQCD","",nBinsEta, leftEta, rightEta);

TH1F *l1PhiAB = new TH1F("l1PhiAB", "",nBinsPhi, leftPhi, rightPhi);
TH1F *l1PhiTT = new TH1F("l1PhiTT", "",nBinsPhi, leftPhi, rightPhi);
TH1F *l1PhiWJ = new TH1F("l1PhiWJ", "",nBinsPhi, leftPhi, rightPhi);
TH1F *l1PhiZJ = new TH1F("l1PhiZJ", "",nBinsPhi, leftPhi, rightPhi);
TH1F *l1PhiT  = new TH1F("l1PhiT",  "",nBinsPhi, leftPhi, rightPhi);
TH1F *l1PhiVV = new TH1F("l1PhiVV", "",nBinsPhi, leftPhi, rightPhi);
TH1F *l1PhiQCD= new TH1F("l1PhiQCD","",nBinsPhi, leftPhi, rightPhi);

TH1F *j1PhiAB = new TH1F("j1PhiAB", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j1PhiTT = new TH1F("j1PhiTT", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j1PhiWJ = new TH1F("j1PhiWJ", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j1PhiZJ = new TH1F("j1PhiZJ", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j1PhiT  = new TH1F("j1PhiT",  "",nBinsPhi, leftPhi, rightPhi);
TH1F *j1PhiVV = new TH1F("j1PhiVV", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j1PhiQCD= new TH1F("j1PhiQCD","",nBinsPhi, leftPhi, rightPhi);

TH1F *j2PhiAB = new TH1F("j2PhiAB", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j2PhiTT = new TH1F("j2PhiTT", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j2PhiWJ = new TH1F("j2PhiWJ", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j2PhiZJ = new TH1F("j2PhiZJ", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j2PhiT  = new TH1F("j2PhiT",  "",nBinsPhi, leftPhi, rightPhi);
TH1F *j2PhiVV = new TH1F("j2PhiVV", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j2PhiQCD= new TH1F("j2PhiQCD","",nBinsPhi, leftPhi, rightPhi);

TH1F *j3PhiAB = new TH1F("j3PhiAB", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j3PhiTT = new TH1F("j3PhiTT", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j3PhiWJ = new TH1F("j3PhiWJ", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j3PhiZJ = new TH1F("j3PhiZJ", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j3PhiT  = new TH1F("j3PhiT",  "",nBinsPhi, leftPhi, rightPhi);
TH1F *j3PhiVV = new TH1F("j3PhiVV", "",nBinsPhi, leftPhi, rightPhi);
TH1F *j3PhiQCD= new TH1F("j3PhiQCD","",nBinsPhi, leftPhi, rightPhi);

TH1F *j12PhiAB = new TH1F("j12PhiAB", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *j12PhiTT = new TH1F("j12PhiTT", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *j12PhiWJ = new TH1F("j12PhiWJ", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *j12PhiZJ = new TH1F("j12PhiZJ", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *j12PhiT  = new TH1F("j12PhiT",  "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *j12PhiVV = new TH1F("j12PhiVV", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *j12PhiQCD= new TH1F("j12PhiQCD","",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);

TH1F *lmdPhiAB = new TH1F("lmdPhiAB", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *lmdPhiTT = new TH1F("lmdPhiTT", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *lmdPhiWJ = new TH1F("lmdPhiWJ", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *lmdPhiZJ = new TH1F("lmdPhiZJ", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *lmdPhiT  = new TH1F("lmdPhiT",  "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *lmdPhiVV = new TH1F("lmdPhiVV", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *lmdPhiQCD= new TH1F("lmdPhiQCD","",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);

TH1F *jmdPhiAB = new TH1F("jmdPhiAB", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *jmdPhiTT = new TH1F("jmdPhiTT", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *jmdPhiWJ = new TH1F("jmdPhiWJ", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *jmdPhiZJ = new TH1F("jmdPhiZJ", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *jmdPhiT  = new TH1F("jmdPhiT",  "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *jmdPhiVV = new TH1F("jmdPhiVV", "",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);
TH1F *jmdPhiQCD= new TH1F("jmdPhiQCD","",nBinsPhi, leftPhi+3.1415927, rightPhi+3.1415927);

std::map<int,int> s3typeId, s4typeId, S3typeId, S4typeId;
s3typeId[57] = 0; s3typeId[60] = 1; s3typeId[62] = 2; s3typeId[63] = 3; s3typeId[64] = 4; s3typeId[65] = 5; s3typeId[66] = 6;
s4typeId[37] = 0; s4typeId[40] = 1; s4typeId[42] = 2; s4typeId[43] = 3; s4typeId[44] = 4; s4typeId[45] = 5; s4typeId[46] = 6;
S3typeId[47] = 0; S3typeId[50] = 1; S3typeId[52] = 2; S3typeId[53] = 3; S3typeId[54] = 4; S3typeId[55] = 5; S3typeId[56] = 6;
S4typeId[27] = 0; S4typeId[30] = 1; S4typeId[32] = 2; S4typeId[33] = 3; S4typeId[34] = 4; S4typeId[35] = 5; S4typeId[36] = 6;
S3typeId[75] = 7; S3typeId[76] = 8;
S4typeId[77] = 7; S4typeId[78] = 8; S4typeId[79] = 9; S4typeId[80] =10; S4typeId[81] =11; S4typeId[82] =12;

TH1F *topMassSig[2][2][13], *topMassSig2p1[2][2][13], *triJetMassSig[2][2][13];
int sigMass[13] = {0, 50, 100, 150, 200, 300, 500, 400, 600, 700, 800, 900, 1000};
for(int scenario=3; scenario<5; scenario++)
  for(int point=0; point<13; point++){
     char name[128];
     sprintf(name,"triJetMassS%dM%d",scenario,sigMass[point]);
     triJetMassSig[scenario-3][0][point] = new TH1F(name,"",nBinsM, leftM, rightM);
     sprintf(name,"triJetMassJ%dM%d",scenario,sigMass[point]);
     triJetMassSig[scenario-3][1][point] = new TH1F(name,"",nBinsM, leftM, rightM);
     sprintf(name,"topMassS%dM%d",scenario,sigMass[point]);
     topMassSig   [scenario-3][0][point] = new TH1F(name,"",nBinsM, leftM, rightM);
     sprintf(name,"topMassJ%dM%d",scenario,sigMass[point]);
     topMassSig   [scenario-3][1][point] = new TH1F(name,"",nBinsM, leftM, rightM);
     sprintf(name,"topMass2p1S%dM%d",scenario,sigMass[point]);
     topMassSig2p1[scenario-3][0][point] = new TH1F(name,"",nBinsM, leftM, rightM);
     sprintf(name,"topMass2p1J%dM%d",scenario,sigMass[point]);
     topMassSig2p1[scenario-3][1][point] = new TH1F(name,"",nBinsM, leftM, rightM);
  }

TH1F *triJetMass=0, *topMass=0, *topMass2p1=0, *met=0, *l1Pt=0, *j1Pt=0, *j2Pt=0, *j3Pt=0, *l1Eta=0, *j1Eta=0, *j2Eta=0, *j3Eta=0, *l1Phi=0, *j1Phi=0, *j2Phi=0, *j3Phi=0, *j12Phi=0, *metPhi=0, *lmdPhi=0, *jmdPhi=0;

for(int event=0; micro->GetEntry(event) /*&& event<10000*/; event++){

   if( (event%100000) == 0 ) std::cout<<"Event: "<<event<<"/"<<micro->GetEntries()<<std::endl;

if( ( (trig&0x100)!=0x100 )
// || lepton1PtRec<10 || !lepton1IsTight || fabs(lepton1EtaRec)>2.4 
) continue; //  HLT_PFMET150

//if( lepton1PtRec<0 ) continue;

  if( type==Data && !uniqueEvents[run].insert(event).second ){
     cout<<"Run "<<run<<", event "<<event<<" was already processed"<<endl;
     continue;
  }

  if( type!=Data ) weight *= lumiScale;

if(type==71) type = TTJets; // TTJets_HadronicMGDecays,
if(type==72) type = TTJets; // TTJets_SemiLeptMGDecays,
if(type==73) type = TTJets; // TTJets_FullLeptMGDecays,
if(type==74) type = TTJets; // BN_TTJets_FullLeptMGDecays,

if(type<27 || type==W1J || type==W2J || type==W3J || type==W4J)
   switch ( type ) {
     case Data:   triJetMass = triJetMassAB; topMass = topMassAB; topMass2p1 = topMassAB2p1;
                  met   = metAB;   metPhi= metPhiAB;
                  l1Pt  = l1PtAB;  l1Eta = l1EtaAB; l1Phi = l1PhiAB;
                  j1Pt  = j1PtAB;  j2Pt  = j2PtAB;  j3Pt  = j3PtAB;
                  j1Eta = j1EtaAB; j2Eta = j2EtaAB; j3Eta = j3EtaAB;
                  j1Phi = j1PhiAB; j2Phi = j2PhiAB; j3Phi = j3PhiAB; j12Phi = j12PhiAB; lmdPhi = lmdPhiAB; jmdPhi = jmdPhiAB;
                  if( run<193752 ) weight *= scaler2012A; else weight *= scaler2012B; break;
     case TTJets: triJetMass = triJetMassTT; topMass = topMassTT; topMass2p1 = topMassTT2p1; weight *= scalerTTJets; 
                  met   = metTT;   metPhi= metPhiTT;
                  l1Pt  = l1PtTT;  l1Eta = l1EtaTT; l1Phi = l1PhiTT;
                  j1Pt  = j1PtTT;  j2Pt  = j2PtTT;  j3Pt  = j3PtTT;
                  j1Eta = j1EtaTT; j2Eta = j2EtaTT; j3Eta = j3EtaTT;
                  j1Phi = j1PhiTT; j2Phi = j2PhiTT; j3Phi = j3PhiTT; j12Phi = j12PhiTT; lmdPhi = lmdPhiTT; jmdPhi = jmdPhiTT;
     break;
     case WJets:  triJetMass = triJetMassWJ; topMass = topMassWJ; topMass2p1 = topMassWJ2p1; weight *= scalerWJetsToLNu;
                  met   = metWJ;   metPhi= metPhiWJ;
                  l1Pt  = l1PtWJ;  l1Eta = l1EtaWJ; l1Phi = l1PhiWJ;
                  j1Pt  = j1PtWJ;  j2Pt  = j2PtWJ;  j3Pt  = j3PtWJ;
                  j1Eta = j1EtaWJ; j2Eta = j2EtaWJ; j3Eta = j3EtaWJ;
                  j1Phi = j1PhiWJ; j2Phi = j2PhiWJ; j3Phi = j3PhiWJ; j12Phi = j12PhiWJ; lmdPhi = lmdPhiWJ; jmdPhi = jmdPhiWJ;
     break;
     case W1J:    triJetMass = triJetMassWJ; topMass = topMassWJ; topMass2p1 = topMassWJ2p1; weight *= scalerWJetsToLNu;
                  met   = metWJ;   metPhi= metPhiWJ;
                  l1Pt  = l1PtWJ;  l1Eta = l1EtaWJ; l1Phi = l1PhiWJ;
                  j1Pt  = j1PtWJ;  j2Pt  = j2PtWJ;  j3Pt  = j3PtWJ;
                  j1Eta = j1EtaWJ; j2Eta = j2EtaWJ; j3Eta = j3EtaWJ;
                  j1Phi = j1PhiWJ; j2Phi = j2PhiWJ; j3Phi = j3PhiWJ; j12Phi = j12PhiWJ; lmdPhi = lmdPhiWJ; jmdPhi = jmdPhiWJ;
     break;
     case W2J:    triJetMass = triJetMassWJ; topMass = topMassWJ; topMass2p1 = topMassWJ2p1; weight *= scalerWJetsToLNu;
                  met   = metWJ;   metPhi= metPhiWJ;
                  l1Pt  = l1PtWJ;  l1Eta = l1EtaWJ; l1Phi = l1PhiWJ;
                  j1Pt  = j1PtWJ;  j2Pt  = j2PtWJ;  j3Pt  = j3PtWJ;
                  j1Eta = j1EtaWJ; j2Eta = j2EtaWJ; j3Eta = j3EtaWJ;
                  j1Phi = j1PhiWJ; j2Phi = j2PhiWJ; j3Phi = j3PhiWJ; j12Phi = j12PhiWJ; lmdPhi = lmdPhiWJ; jmdPhi = jmdPhiWJ;
     break;
     case W3J:    triJetMass = triJetMassWJ; topMass = topMassWJ; topMass2p1 = topMassWJ2p1; weight *= scalerWJetsToLNu;
                  met   = metWJ;   metPhi= metPhiWJ;
                  l1Pt  = l1PtWJ;  l1Eta = l1EtaWJ; l1Phi = l1PhiWJ;
                  j1Pt  = j1PtWJ;  j2Pt  = j2PtWJ;  j3Pt  = j3PtWJ;
                  j1Eta = j1EtaWJ, j2Eta = j2EtaWJ, j3Eta = j3EtaWJ;
                  j1Phi = j1PhiWJ; j2Phi = j2PhiWJ; j3Phi = j3PhiWJ; j12Phi = j12PhiWJ; lmdPhi = lmdPhiWJ; jmdPhi = jmdPhiWJ;
     break;
     case W4J:    triJetMass = triJetMassWJ; topMass = topMassWJ; topMass2p1 = topMassWJ2p1; weight *= scalerWJetsToLNu;
                  met   = metWJ;   metPhi= metPhiWJ;
                  l1Pt  = l1PtWJ;  l1Eta = l1EtaWJ; l1Phi = l1PhiWJ;
                  j1Pt  = j1PtWJ;  j2Pt  = j2PtWJ;  j3Pt  = j3PtWJ;
                  j1Eta = j1EtaWJ; j2Eta = j2EtaWJ; j3Eta = j3EtaWJ;
                  j1Phi = j1PhiWJ; j2Phi = j2PhiWJ; j3Phi = j3PhiWJ; j12Phi = j12PhiWJ; lmdPhi = lmdPhiWJ; jmdPhi = jmdPhiWJ;
     break;
     case ZJets:  triJetMass = triJetMassZJ; topMass = topMassZJ; topMass2p1 = topMassZJ2p1; weight *= scalerZJetsToLL;
                  met   = metZJ;   metPhi= metPhiZJ;
                  l1Pt  = l1PtZJ;  l1Eta = l1EtaZJ; l1Phi = l1PhiZJ;
                  j1Pt  = j1PtZJ;  j2Pt  = j2PtZJ;  j3Pt  = j3PtZJ;
                  j1Eta = j1EtaZJ; j2Eta = j2EtaZJ; j3Eta = j3EtaZJ;
                  j1Phi = j1PhiZJ; j2Phi = j2PhiZJ; j3Phi = j3PhiZJ; j12Phi = j12PhiZJ; lmdPhi = lmdPhiZJ; jmdPhi = jmdPhiZJ;
     break;
     case WW:     triJetMass = triJetMassVV; topMass = topMassVV; topMass2p1 = topMassVV2p1; weight *= scalerWW;
                  met   = metVV;   metPhi= metPhiVV;
                  l1Pt  = l1PtVV;  l1Eta = l1EtaVV; l1Phi = l1PhiVV;
                  j1Pt  = j1PtVV;  j2Pt  = j2PtVV;  j3Pt  = j3PtVV;
                  j1Eta = j1EtaVV; j2Eta = j2EtaVV; j3Eta = j3EtaVV;
                  j1Phi = j1PhiVV; j2Phi = j2PhiVV; j3Phi = j3PhiVV; j12Phi = j12PhiVV; lmdPhi = lmdPhiVV; jmdPhi = jmdPhiVV;
     break;
     case WZ:     triJetMass = triJetMassVV; topMass = topMassVV; topMass2p1 = topMassVV2p1; weight *= scalerWZ;
                  met   = metVV;   metPhi= metPhiVV;
                  l1Pt  = l1PtVV;  l1Eta = l1EtaVV; l1Phi = l1PhiVV;
                  j1Pt  = j1PtVV;  j2Pt  = j2PtVV;  j3Pt  = j3PtVV;
                  j1Eta = j1EtaVV; j2Eta = j2EtaVV; j3Eta = j3EtaVV;
                  j1Phi = j1PhiVV; j2Phi = j2PhiVV; j3Phi = j3PhiVV; j12Phi = j12PhiVV; lmdPhi = lmdPhiVV; jmdPhi = jmdPhiVV;
     break;
     case ZZ:     triJetMass = triJetMassVV; topMass = topMassVV; topMass2p1 = topMassVV2p1; weight *= scalerZZ;
                  met   = metVV;   metPhi= metPhiVV;
                  l1Pt  = l1PtVV;  l1Eta = l1EtaVV; l1Phi = l1PhiVV;
                  j1Pt  = j1PtVV;  j2Pt  = j2PtVV;  j3Pt  = j3PtVV;
                  j1Eta = j1EtaVV; j2Eta = j2EtaVV; j3Eta = j3EtaVV;
                  j1Phi = j1PhiVV; j2Phi = j2PhiVV; j3Phi = j3PhiVV; j12Phi = j12PhiVV; lmdPhi = lmdPhiVV; jmdPhi = jmdPhiVV;
     break;
     default :
       triJetMass = 0;
       topMass    = 0;
       topMass2p1 = 0;
       met=0; j1Pt=0; j2Pt=0; j3Pt=0; j1Eta=0; j2Eta=0; j3Eta=0; j1Phi=0; j2Phi=0; j3Phi=0; j12Phi=0; metPhi=0;

       if( type>=Znunu && type<QCD ){
           triJetMass = triJetMassZJ; topMass = topMassZJ; topMass2p1 = topMassZJ2p1;  weight *= scalerZJetsToNuNu;
           met   = metZJ;   metPhi= metPhiZJ;  
           l1Pt  = l1PtZJ;  l1Eta = l1EtaZJ; l1Phi = l1PhiZJ;
           j1Pt  = j1PtZJ;  j2Pt  = j2PtZJ;  j3Pt  = j3PtZJ;
           j1Eta = j1EtaZJ, j2Eta = j2EtaZJ, j3Eta = j3EtaZJ;
           j1Phi = j1PhiZJ; j2Phi = j2PhiZJ; j3Phi = j3PhiZJ; j12Phi = j12PhiZJ; lmdPhi = lmdPhiZJ; jmdPhi = jmdPhiZJ;
       }
       if( type>=QCD   && type<Top ){
           triJetMass = triJetMassQCD;topMass = topMassQCD;topMass2p1 = topMassQCD2p1; weight *= scalerQCD;
           met   = metQCD;   metPhi= metPhiQCD; 
           l1Pt  = l1PtQCD;  l1Eta = l1EtaQCD; l1Phi = l1PhiQCD;
           j1Pt  = j1PtQCD;  j2Pt  = j2PtQCD;  j3Pt  = j3PtQCD;
           j1Eta = j1EtaQCD; j2Eta = j2EtaQCD; j3Eta = j3EtaQCD;
           j1Phi = j1PhiQCD; j2Phi = j2PhiQCD; j3Phi = j3PhiQCD; j12Phi = j12PhiQCD; lmdPhi = lmdPhiQCD; jmdPhi = jmdPhiQCD;
       }
       if( type>=Top   && type<WW  ){
           triJetMass = triJetMassT;  topMass = topMassT;  topMass2p1 = topMassT2p1;   weight *= scalerSingleTop;
           met   = metT;   metPhi= metPhiT; 
           l1Pt  = l1PtT;  l1Eta = l1EtaT; l1Phi = l1PhiT;
           j1Pt  = j1PtT;  j2Pt  = j2PtT;  j3Pt  = j3PtT;
           j1Eta = j1EtaT; j2Eta = j2EtaT; j3Eta = j3EtaT;
           j1Phi = j1PhiT; j2Phi = j2PhiT; j3Phi = j3PhiT; j12Phi = j12PhiT; lmdPhi = lmdPhiT; jmdPhi = jmdPhiT;
       }
       break;
   }
if((type>=27 && type<37) || type>76){
   if( S4typeId.find(type) == S4typeId.end() ){
      std::cout<<"Unknown type: "<<type<<std::endl;
      return;
   }
   triJetMass = triJetMassSig[1][0][ S4typeId[type] ];
   topMass    = topMassSig   [1][0][ S4typeId[type] ];
   topMass2p1 = topMassSig2p1[1][0][ S4typeId[type] ];
}
if( type>=37 && type<47 ){
   if( s4typeId.find(type) == s4typeId.end() ){
      std::cout<<"Unknown type: "<<type<<std::endl;
      return;
   }
   triJetMass = triJetMassSig[1][1][ s4typeId[type] ];
   topMass    = topMassSig   [1][1][ s4typeId[type] ];
   topMass2p1 = topMassSig2p1[1][1][ s4typeId[type] ];
}
if((type>=47 && type<57) || type==75 || type==76 ){
   if( S3typeId.find(type) == S3typeId.end() ){
      std::cout<<"Unknown type: "<<type<<std::endl;
      return;
   }
   triJetMass = triJetMassSig[0][0][ S3typeId[type] ];
   topMass    = topMassSig   [0][0][ S3typeId[type] ];
   topMass2p1 = topMassSig2p1[0][0][ S3typeId[type] ];
}
if(type>=57 && type<75 && type!=W1J && type!=W2J && type!=W3J && type!=W4J){
   if( s3typeId.find(type) == s3typeId.end() ){
      std::cout<<"Unknown type: "<<type<<std::endl;
      return;
   }
   triJetMass = triJetMassSig[0][1][ s3typeId[type] ];
   topMass    = topMassSig   [0][1][ s3typeId[type] ];
   topMass2p1 = topMassSig2p1[0][1][ s3typeId[type] ];
}
if( !triJetMass || !topMass || !topMass2p1 ){ std::cout<<"Unknown type: "<<type<<std::endl; return; }

      bool passB = false;
      switch(nBjets){
          case -2 : passB = (leadingJetCSV<0.244 && subleadJetCSV<0.244 && thirdJetCSV<0.244 && forthJetCSV<0.244); break;
          case -1 : passB = true; break;
          case  0 : passB = (numberOfBJets==0); break; //( leadingJetCSV<0.244 && subleadJetCSV<0.244 && thirdJetCSV<0.244 && forthJetCSV<0.244 ); break;
          case  1 : passB = (numberOfBJets==1); break; //(
          case  2 : passB = (numberOfBJets==2); break; //(
//(leadingJetCSV>0.679 && subleadJetCSV<0.244 && thirdJetCSV<0.244 && forthJetCSV<0.244) ||
//(leadingJetCSV<0.244 && subleadJetCSV>0.679 && thirdJetCSV<0.244 && forthJetCSV<0.244) ||
//(leadingJetCSV<0.244 && subleadJetCSV>0.679 && thirdJetCSV<0.244 && forthJetCSV<0.244) ||
//(leadingJetCSV<0.244 && subleadJetCSV<0.244 && thirdJetCSV>0.679 && forthJetCSV<0.244) ||
//(leadingJetCSV<0.244 && subleadJetCSV<0.244 && thirdJetCSV<0.244 && forthJetCSV>0.679)
// ); break;
          default : break;
      }


      if( (selection & lookUpMask[lastStage]) == lookUpMask[lastStage] && (lastStage>=4 ? thirdJetPtRec>40 && forthJetPtRec<35: true )
&& passB && metPtRec>(MET>lookUpMET[lastStage]?MET:lookUpMET[lastStage]) ){

         TLorentzVector jet1, jet2, jet3;
         jet1.SetPtEtaPhiM(leadingJetPtRec, leadingJetEtaRec, leadingJetPhiRec, 0.);
         jet2.SetPtEtaPhiM(subleadJetPtRec, subleadJetEtaRec, subleadJetPhiRec, 0.);
         jet3.SetPtEtaPhiM(  thirdJetPtRec,   thirdJetEtaRec,   thirdJetPhiRec, 0.);

         TLorentzVector sum( jet1 + jet2 + jet3 );
/*
//if( fabs(sum.M() - thMrec)>30 ){
std::cout<<"numberOfJets = "<<numberOfJets<<std::endl;
std::cout<<"Leading jet: pt="<<leadingJetPtRec<<" eta="<<leadingJetEtaRec<<" phi="<<leadingJetPhiRec<<" csv="<<leadingJetCSV<<std::endl;
std::cout<<"Sublead jet: pt="<<subleadJetPtRec<<" eta="<<subleadJetEtaRec<<" phi="<<subleadJetPhiRec<<" csv="<<subleadJetCSV<<std::endl;
std::cout<<"Third   jet: pt="<<thirdJetPtRec  <<" eta="<<thirdJetEtaRec  <<" phi="<<thirdJetPhiRec  <<" csv="<<thirdJetCSV<<std::endl;
std::cout<<"chi2="<<chi2<<" triMass="<<sum.M()<<" topMass="<<thMrec<<" Wmass="<<whMrec<<std::endl;
std::cout<<"bJet:        pt="<<  bJetPtRec<<" eta="<<  bJetEtaRec<<" phi="<<  bJetPhiRec<<std::endl;
std::cout<<"W jet1:      pt="<<jet1WhPtRec<<" eta="<<jet1WhEtaRec<<" phi="<<jet1WhPhiRec<<std::endl;
std::cout<<"W jet2:      pt="<<jet2WhPtRec<<" eta="<<jet2WhEtaRec<<" phi="<<jet2WhPhiRec<<std::endl;
std::cout<<"TLorentzVector v0,v1,v2;"<<std::endl;
std::cout<<"v0.SetPtEtaPhiM("<<bJetPtRec<<","<<bJetEtaRec<<","<<bJetPhiRec<<",0);"<<std::endl;
std::cout<<"v1.SetPtEtaPhiM("<<jet1WhPtRec<<","<<jet1WhEtaRec<<","<<jet1WhPhiRec<<",0);"<<std::endl;
std::cout<<"v2.SetPtEtaPhiM("<<jet2WhPtRec<<","<<jet2WhEtaRec<<","<<jet2WhPhiRec<<",0);"<<std::endl;
std::cout<<"(v0+v1+v2).M()"<<std::endl;
//}
*/

if( type==TTJets ){
 weight *= sqrt(exp(0.156-0.00137*t1PtGen)*exp(0.156-0.00137*t2PtGen));
// cout<<"t1PtGen= "<<t1PtGen<<" t2PtGen= "<<t2PtGen<<" rew="<<sqrt(exp(0.156-0.00137*t1PtGen)*exp(0.156-0.00137*t2PtGen))<<endl;
}

         double dPhi = fabs(leadingJetPhiRec - subleadJetPhiRec);
         if( dPhi>3.1415927 ) dPhi = 2.*3.1415927 - dPhi;
         if( j12Phi ) j12Phi->Fill(dPhi, weight);

if( fabs(dPhi-3.1415927)>0.36 ){ // && metPtRec>250 

         triJetMass->Fill( sum.M(),  weight);
         topMass->Fill( thMrec, weight );
         topMass2p1->Fill( thMrec, weight );

         if( (type>=27 && type<37) || (type>=37 && type<47) || (type>=47 && type<57) || (type>=57 && type!=W1J && type!=W2J && type!=W3J && type!=W4J) ){
         } else {
             j1Pt->Fill(leadingJetPtRec, weight);
             j2Pt->Fill(subleadJetPtRec, weight);
             j3Pt->Fill(  thirdJetPtRec, weight);
             l1Pt->Fill(  lepton1PtRec , weight);
             j1Eta->Fill(leadingJetEtaRec, weight);
             j2Eta->Fill(subleadJetEtaRec, weight);
             j3Eta->Fill(  thirdJetEtaRec, weight);
             if(lepton1PtRec>0 ) l1Eta->Fill( lepton1EtaRec  , weight);
             j1Phi->Fill(leadingJetPhiRec, weight);
             j2Phi->Fill(subleadJetPhiRec, weight);
             j3Phi->Fill(  thirdJetPhiRec, weight);
             if(lepton1PtRec>0 ) l1Phi->Fill(  lepton1PhiRec,  weight);
             if( lepton1PtRec>0 && fabs(lepton1EtaRec)<2.1 )
               lmdPhi->Fill( ( abs(metPhiRec-lepton1PhiRec)<3.1415927 ? abs(metPhiRec-lepton1PhiRec) : (2.*3.1415927 - abs(metPhiRec-lepton1PhiRec)) ), weight );
             jmdPhi->Fill( ( abs(metPhiRec-leadingJetPhiRec)<3.1415927 ? abs(metPhiRec-leadingJetPhiRec) : (2.*3.1415927 - abs(metPhiRec-leadingJetPhiRec)) ), weight );
             met->Fill( metPtRec, weight );
             metPhi->Fill( metPhiRec, weight );
//             TVector2 oldMet;
//             oldMet.SetMagPhi(metPtRec, metPhiRec);
//             TVector2 newMet = oldMet;//phiCorrection(oldMet, nVerts, type==Data);
//             met->Fill( newMet.Mod(), weight );
//             metPhi->Fill( newMet.Phi() - 3.1415927, weight );
         }
}
      }

}
//return;
int dups = 0;
for(std::map<int,std::set<int> >::const_iterator it=uniqueEvents.begin(); it!=uniqueEvents.end(); it++){
   if( it->second.size() ) cout<<"run: "<<it->first<<" # of events: "<<it->second.size()<<endl;
   dups += it->second.size();
}
string outputName( lookUpName[lastStage] );
switch( nBjets ){
  case -2 : outputName.append("_vetoB"); break;
  case -1 : outputName.append("_xb"); break;
  case 0  : outputName.append("_0b"); break;
  case 1  : outputName.append("_1b"); break;
  case 2  : outputName.append("_2b"); break;
  default : outputName.append("_fewBs"); break;
}
char buff[128];
sprintf(buff,"MET%d",int(MET>lookUpMET[lastStage]?MET:lookUpMET[lastStage]));
outputName.append(buff);

if( process==QCD ) outputName.append("_QCD");
if( process==SIG ) outputName.append("_SIG");
if( process==ZJets ) outputName.append("_ZJ");
if( process==Znunu ) outputName.append("_ZN");
if( process==WJets ) outputName.append("_WJ");
if( process==W1J ) outputName.append("_W1J");
if( process==W2J ) outputName.append("_W2J");
if( process==W3J ) outputName.append("_W3J");
if( process==W4J ) outputName.append("_W4J");
if( process==TTJets ) outputName.append("_TT");
if( process==Top ) outputName.append("_Top");
if( process==WW ) outputName.append("_WW");
if( process==WZ ) outputName.append("_WZ");
if( process==ZZ ) outputName.append("_ZZ");
if( process==A ) outputName.append("_A");
if( process==B ) outputName.append("_B");
if( process==C ) outputName.append("_C");
if( process==D ) outputName.append("_D");
if( process==E ) outputName.append("_E");

if( process==WJets || process==W1J || process==W2J || process==W3J || process==W4J || process==TTJets || process==ZJets )
switch(variation){
case CENTER: break;
case Q2UP:      outputName.append("su"); break;
case Q2DOWN:    outputName.append("sd"); break;
case MATCHUP:   outputName.append("mu"); break;
case MATCHDOWN: outputName.append("md"); break;
default: break;
}

outputName.append(".root");

TFile *out = new TFile(outputName.c_str(),"RECREATE");

if( process==-1 || process==SIG ){
for(int scenario=3; scenario<5; scenario++)
  for(int point=0; point<13; point++){
     if( point>8 && scenario==3 ) continue;
     triJetMassSig[scenario-3][0][point]->Write();
     topMassSig   [scenario-3][0][point]->Write();
     topMassSig2p1[scenario-3][0][point]->Write();
///     triJetMassSig[scenario-3][1][point]->Write();
///     topMassSig   [scenario-3][1][point]->Write();
///     topMassSig2p1[scenario-3][1][point]->Write();
  }
}

if( process==-1 || process==Data || process==A || process==B || process==C || process==D || process==E ){
triJetMassAB->Write();
topMassAB->Write();
topMassAB2p1->Write();
metAB->Write();
metPhiAB->Write();
l1PtAB->Write();
j1PtAB->Write();
j2PtAB->Write();
j3PtAB->Write();
l1EtaAB->Write();
j1EtaAB->Write();
j2EtaAB->Write();
j3EtaAB->Write();
l1PhiAB->Write();
j1PhiAB->Write();
j2PhiAB->Write();
j3PhiAB->Write();
j12PhiAB->Write();
jmdPhiAB->Write();
lmdPhiAB->Write();
}

if( process==-1 || process==TTJets ){
triJetMassTT->Write();
topMassTT->Write();
topMassTT2p1->Write();
metTT->Write();
metPhiTT->Write();
l1PtTT->Write();
j1PtTT->Write();
j2PtTT->Write();
j3PtTT->Write();
l1EtaTT->Write();
j1EtaTT->Write();
j2EtaTT->Write();
j3EtaTT->Write();
l1PhiTT->Write();
j1PhiTT->Write();
j2PhiTT->Write();
j3PhiTT->Write();
j12PhiTT->Write();
jmdPhiTT->Write();
lmdPhiTT->Write();
}

if( process==-1 || process==W1J || process==W2J || process==W3J || process==W4J || process==WJets ){
triJetMassWJ->Write();
topMassWJ->Write();
topMassWJ2p1->Write();
metWJ->Write();
metPhiWJ->Write();
l1PtWJ->Write();
j1PtWJ->Write();
j2PtWJ->Write();
j3PtWJ->Write();
l1EtaWJ->Write();
j1EtaWJ->Write();
j2EtaWJ->Write();
j3EtaWJ->Write();
l1PhiWJ->Write();
j1PhiWJ->Write();
j2PhiWJ->Write();
j3PhiWJ->Write();
j12PhiWJ->Write();
jmdPhiWJ->Write();
lmdPhiWJ->Write();
}

if( process==-1 || process==ZJets || process==Znunu ){
triJetMassZJ->Write();
topMassZJ->Write();
topMassZJ2p1->Write();
metZJ->Write();
metPhiZJ->Write();
l1PtZJ->Write();
j1PtZJ->Write();
j2PtZJ->Write();
j3PtZJ->Write();
l1EtaZJ->Write();
j1EtaZJ->Write();
j2EtaZJ->Write();
j3EtaZJ->Write();
l1PhiZJ->Write();
j1PhiZJ->Write();
j2PhiZJ->Write();
j3PhiZJ->Write();
j12PhiZJ->Write();
jmdPhiZJ->Write();
lmdPhiZJ->Write();
}

if( process==-1 || process==Top ){
triJetMassT->Write();
topMassT->Write();
topMassT2p1->Write();
metT->Write();
metPhiT->Write();
l1PtT->Write();
j1PtT->Write();
j2PtT->Write();
j3PtT->Write();
l1EtaT->Write();
j1EtaT->Write();
j2EtaT->Write();
j3EtaT->Write();
l1PhiT->Write();
j1PhiT->Write();
j2PhiT->Write();
j3PhiT->Write();
j12PhiT->Write();
jmdPhiT->Write();
lmdPhiT->Write();
}

if( process==-1 || process==WW || process==WZ || process==ZZ ){
triJetMassVV->Write();
topMassVV->Write();
topMassVV2p1->Write();
metVV->Write();
metPhiVV->Write();
l1PtVV->Write();
j1PtVV->Write();
j2PtVV->Write();
j3PtVV->Write();
l1EtaVV->Write();
j1EtaVV->Write();
j2EtaVV->Write();
j3EtaVV->Write();
l1PhiVV->Write();
j1PhiVV->Write();
j2PhiVV->Write();
j3PhiVV->Write();
j12PhiVV->Write();
jmdPhiVV->Write();
lmdPhiVV->Write();
}

if( process==-1 || process==QCD ){
triJetMassQCD->Write();
topMassQCD->Write();
topMassQCD2p1->Write();
metQCD->Write();
metPhiQCD->Write();
l1PtQCD->Write();
j1PtQCD->Write();
j2PtQCD->Write();
j3PtQCD->Write();
l1EtaQCD->Write();
j1EtaQCD->Write();
j2EtaQCD->Write();
j3EtaQCD->Write();
l1PhiQCD->Write();
j1PhiQCD->Write();
j2PhiQCD->Write();
j3PhiQCD->Write();
j12PhiQCD->Write();
jmdPhiQCD->Write();
lmdPhiQCD->Write();
}

out->Write();
out->Close();
}
