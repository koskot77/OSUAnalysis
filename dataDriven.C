#include <iostream>
#include <map>
#include <set>
#include "TH1.h"
#include "TFile.h"
#include "TChain.h"
#include "TLorentzVector.h"
//#include "../../../tdrstyle.C"

std::map<int,std::set<int> > uniqueEvents;

enum {Data=0, TTJets=1, WJets=2, ZJets=3, Znunu=4, QCD=8, Top=16, WW=24, WZ=25, ZZ=26, W1J=67, W2J=68, W3J=69, W4J=70, SIG=1000, A=1001, B=1002, C=1003, D=1004, E=1005};
enum {CENTER=0, Q2UP=1, Q2DOWN=2, MATCHUP=3, MATCHDOWN=4};

void dataDriven(int lastStage=0,int nBjets=-1, double MET=0, double M3J=-1, int process=-1, int variation=CENTER){
////gROOT->ProcessLine(".L ../../../tdrstyle.C");
//setTDRStyle();
if( lastStage>9 && lastStage<1 ){
   cout<<"Wrong stage:"<<lastStage<<" (first argument should be between 1 and 9)"<<endl;
   return;
}
if( variation!=CENTER && variation!=Q2UP && variation!=Q2DOWN && variation!=MATCHUP && variation!=MATCHDOWN ) return;
unsigned    lookUpMask[10] = {1, 3, 7, 15, 31, 31, 31, 31, 31, 31};
unsigned    lookUpMET [10] = {0, 0, 0,  0,  0,  0,150,250,350,450};
const char *lookUpName[10] = {"","3jets/hists40IsoMu24Stage1","3jets/hists40IsoMu24Stage2","3jets/hists40IsoMu24Stage3",
"3jets/hists40IsoMu24Stage4",
//"3jets/hists40Ele27WP80Stage4",
"3jets/hists40IsoMu24Stage4", "3jets/hists40IsoMu24Stage4met150", "3jets/hists40IsoMu24Stage4met250", "3jets/hists40IsoMu24Stage4met350", "3jets/hists40IsoMu24Stage4met450"};

TChain *micro = new TChain("micro");

if( process==-1 || process==Znunu || process==ZJets ){ //2013.09.18
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
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJsu_muSel.root");
break;
case Q2DOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJsd_muSel.root");
break;
case MATCHUP:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJmu_muSel.root");
break;
case MATCHDOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_ZJmd_muSel.root");
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
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJsu_muSel.root");
break;
case Q2DOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJsd_muSel.root");
break;
case MATCHUP:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJmu_muSel.root");
break;
case MATCHDOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_WJmd_muSel.root");
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
/*
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
*/
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTll1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTll2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTll3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTll4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTll5_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTll6_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTlh1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTlh2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTlh3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTlh4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTlh5_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTlh6_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTlh7_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TThh1_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TThh2_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TThh3_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TThh4_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TThh5_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TThh6_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TThh7_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TThh8_metSel.root");
break;
case Q2UP:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTsu_muSel.root");
break;
case Q2DOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTsd_muSel.root");
break;
case MATCHUP:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTmu_muSel.root");
break;
case MATCHDOWN:
micro->AddFile("/data/users/kkotov/2013.11.15/micro_TTmd_muSel.root");
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
micro->AddFile("/data/users/kkotov/2013.11.15/micro_BN_SingleMu_Run2012A-22Jan2013-v1_AOD_0_muSel.root");
//cout<<"EntriesA= "<<micro->GetEntries()<<endl;
//return;
}
if( process==-1 || process==B ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012B_0_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012B_1_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012B_2_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012B_3_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012B_4_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012B_5_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012B_6_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012B_7_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012B_8_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012Bextra_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012Bend_muSel.root");
//cout<<"EntriesB= "<<micro->GetEntries()<<endl;
//return;
}
if( process==-1 || process==C ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C1_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C2_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C3_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C4_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C5_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C6_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C7_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C8_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C9_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C10_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C11_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C12_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C13_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C14_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012C15_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012Cextra_muSel.root");
//cout<<"EntriesC= "<<micro->GetEntries()<<endl;
//return;
}
if( process==-1 || process==D ){
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012D_0_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012D_1_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012D_2_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012D_3_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012D_4_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012D_5_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012D_6_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012D_7_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012D_8_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012D_9_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012D_10_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012D_11_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012D_12_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012D_13_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012Dextra_muSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_SingleMu2012Dend_muSel.root");
//cout<<"EntriesD= "<<micro->GetEntries()<<endl;
//return;
}

//double lumiScale = (0.802 + 4.403 + 6.388 + 7.248)/5.;
double lumiScale = 19.7/5.;

double scaler2012A      = 1;
double scaler2012B      = 1;
double scalerSingleTop  = 1;
double scalerTTJets     = 1;
double scalerWJetsToLNu = (process==W1J || process==W2J || process==W3J || process==W4J ? 1.23 : 1);
double scalerZJetsToLL  = 1;
double scalerWW         = 1;
double scalerWZ         = 1;
double scalerZZ         = 1;
double scalerQCD        = 1;

double t1PtGen, t2PtGen;
if(process==TTJets){
micro->SetBranchAddress("t1PtGen",&t1PtGen);
micro->SetBranchAddress("t2PtGen",&t2PtGen);
}

double lepton1PtRec,  lepton2PtRec,  lepton3PtRec;
double lepton1EtaRec, lepton2EtaRec, lepton3EtaRec;
double lepton1PhiRec, lepton2PhiRec, lepton3PhiRec;
double lepton1PtGen,  lepton2PtGen,  lepton3PtGen;
double lepton1EtaGen, lepton2EtaGen, lepton3EtaGen;
double lepton1PhiGen, lepton2PhiGen, lepton3PhiGen;
double neutrino1PtGen, neutrino1EtaGen, neutrino1PhiGen;
double neutrino2PtGen, neutrino2EtaGen, neutrino2PhiGen;
double metPtRec, metPhiRec, metPtGen, metPhiGen, metEtaGen;
double leadingJetPtRec, leadingJetEtaRec, leadingJetPhiRec, leadingJetCSV;
double subleadJetPtRec, subleadJetEtaRec, subleadJetPhiRec, subleadJetCSV;
double thirdJetPtRec, thirdJetEtaRec, thirdJetPhiRec, thirdJetCSV;
double forthJetPtRec, forthJetEtaRec, forthJetPhiRec, forthJetCSV;
double thMrec, m3jets;
double weight;
int    selection, type, run, event, nVerts;
int    numberOfJets, numberOfBJets, nTausGen;
int    lepton1IsTight, lepton2IsTight, lepton3IsTight;
char   fileName[32];
ULong64_t trig;

micro->SetBranchAddress("lepton1PtRec",&lepton1PtRec);
micro->SetBranchAddress("lepton2PtRec",&lepton2PtRec);
micro->SetBranchAddress("lepton3PtRec",&lepton3PtRec);
micro->SetBranchAddress("lepton1EtaRec",&lepton1EtaRec);
micro->SetBranchAddress("lepton2EtaRec",&lepton2EtaRec);
micro->SetBranchAddress("lepton3EtaRec",&lepton3EtaRec);
micro->SetBranchAddress("lepton1PhiRec",&lepton1PhiRec);
micro->SetBranchAddress("lepton2PhiRec",&lepton2PhiRec);
micro->SetBranchAddress("lepton3PhiRec",&lepton3PhiRec);
micro->SetBranchAddress("lepton1IsTight",&lepton1IsTight);
micro->SetBranchAddress("lepton2IsTight",&lepton2IsTight);
micro->SetBranchAddress("lepton3IsTight",&lepton3IsTight);

micro->SetBranchAddress("lepton1PtGen",&lepton1PtGen);
micro->SetBranchAddress("lepton2PtGen",&lepton2PtGen);
micro->SetBranchAddress("lepton3PtGen",&lepton3PtGen);
micro->SetBranchAddress("lepton1EtaGen",&lepton1EtaGen);
micro->SetBranchAddress("lepton2EtaGen",&lepton2EtaGen);
micro->SetBranchAddress("lepton3EtaGen",&lepton3EtaGen);
micro->SetBranchAddress("lepton1PhiGen",&lepton1PhiGen);
micro->SetBranchAddress("lepton2PhiGen",&lepton2PhiGen);
micro->SetBranchAddress("lepton3PhiGen",&lepton3PhiGen);
micro->SetBranchAddress("neutrino1PtGen", &neutrino1PtGen);
micro->SetBranchAddress("neutrino1EtaGen",&neutrino1EtaGen);
micro->SetBranchAddress("neutrino1PhiGen",&neutrino1PhiGen);
micro->SetBranchAddress("neutrino2PtGen", &neutrino2PtGen);
micro->SetBranchAddress("neutrino2EtaGen",&neutrino2EtaGen);
micro->SetBranchAddress("neutrino2PhiGen",&neutrino2PhiGen);

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
micro->SetBranchAddress("m3jets",          &m3jets);

micro->SetBranchAddress("metPtRec", &metPtRec);
micro->SetBranchAddress("metPhiRec",&metPhiRec);
micro->SetBranchAddress("metPtGen", &metPtGen);
micro->SetBranchAddress("metPhiGen",&metPhiGen);
micro->SetBranchAddress("metEtaGen",&metEtaGen);
micro->SetBranchAddress("weight",   &weight);
//micro->SetBranchAddress("selection",&selection);
micro->SetBranchAddress("muSel",    &selection);
micro->SetBranchAddress("type",     &type);
micro->SetBranchAddress("run",      &run);
micro->SetBranchAddress("event",    &event);
//micro->SetBranchAddress("eTRIGs",   &trig);
micro->SetBranchAddress("muTRIGs",   &trig);
micro->SetBranchAddress("nVerts",   &nVerts);
micro->SetBranchAddress("nTausGen", &nTausGen);

///micro->SetBranchAddress("fileName", fileName);

int    nBinsM=120, nBinsQt=750, nBinsMT=90;
int    nBinsMET=750, nBinsJetPt=200, nBinsLepPt=750, nBinsLepEta=100;
double leftM=60, rightM=120, leftQt=0, rightQt=750, leftMT=0, rightMT=180;
double leftMET=0, rightMET=750, leftJetPt=30, rightJetPt=230, leftLepPt=0, rightLepPt=750, leftLepEta=-2.6, rightLepEta=2.6;
int    nBinsDPhi=1000;
double leftDPhi=0, rightDPhi=3.1415927*2;

TH1F *diMuonMassAB = new TH1F("diMuonMassAB","",nBinsM, leftM, rightM);
TH1F *diMuonQtAB   = new TH1F("diMuonAB",    "",nBinsQt,leftQt,rightQt);
TH1F *mtAB         = new TH1F("mtAB",        "",nBinsMT,leftMT,rightMT);
TH1F *mtLepNeuAB   = new TH1F("mtLepNeuAB",  "",nBinsMT,leftMT,rightMT);
TH1F *jetPtAB      = new TH1F("jetPtAB",     "",nBinsJetPt, leftJetPt, rightJetPt);
TH1F *leptonPtAB   = new TH1F("leptonPtAB",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *leptonEtaAB  = new TH1F("leptonEtaAB", "",nBinsLepEta,leftLepEta,rightLepEta);
TH1F *metAB        = new TH1F("metAB",       "",nBinsMET,   leftMET,   rightMET);
TH1F *dPhiLepMetAB = new TH1F("dPhiLepMetAB","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGenMetAB = new TH1F("dPhiGenMetAB","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGenLepAB = new TH1F("dPhiGenLepAB","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGepGetAB = new TH1F("dPhiGepGetAB","",nBinsDPhi, leftDPhi, rightDPhi);

TH1F *diMuonMassTT = new TH1F("diMuonMassTT","",nBinsM, leftM, rightM);
TH1F *diMuonQtTT   = new TH1F("diMuonTT",    "",nBinsQt,leftQt,rightQt);
TH1F *diMuGenQtTT  = new TH1F("diMuGenTT",   "",nBinsQt,leftQt,rightQt);
TH1F *mtTT         = new TH1F("mtTT",        "",nBinsMT,leftMT,rightMT);
TH1F *mtLepNeuTT   = new TH1F("mtLepNeuTT",  "",nBinsMT,leftMT,rightMT);
TH1F *jetPtTT      = new TH1F("jetPtTT",     "",nBinsJetPt, leftJetPt, rightJetPt);
TH1F *leptonPtTT   = new TH1F("leptonPtTT",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *lepGenPtTT   = new TH1F("lepGenPtTT",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *leptonEtaTT  = new TH1F("leptonEtaTT", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *lepGenEtaTT  = new TH1F("lepGenEtaTT", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *neuGenPtTT   = new TH1F("neuGenPtTT",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *neuGenEtaTT  = new TH1F("neuGenEtaTT", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *metTT        = new TH1F("metTT",       "",nBinsMET,   leftMET,   rightMET);
TH1F *metGenTT     = new TH1F("metGenTT",    "",nBinsMET,   leftMET,   rightMET);
TH1F *massWGenTT   = new TH1F("massWGenTT",  "",nBinsM,     leftM,     rightM);
TH1F *dPhiLepMetTT = new TH1F("dPhiLepMetTT","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGenMetTT = new TH1F("dPhiGenMetTT","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGenLepTT = new TH1F("dPhiGenLepTT","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGepGetTT = new TH1F("dPhiGepGetTT","",nBinsDPhi, leftDPhi, rightDPhi);

TH1F *diMuonMassWJ = new TH1F("diMuonMassWJ","",nBinsM, leftM, rightM);
TH1F *diMuonQtWJ   = new TH1F("diMuonWJ",    "",nBinsQt,leftQt,rightQt);
TH1F *diMuGenQtWJ  = new TH1F("diMuGenWJ",   "",nBinsQt,leftQt,rightQt);
TH1F *mtWJ         = new TH1F("mtWJ",        "",nBinsMT,leftMT,rightMT);
TH1F *mtLepNeuWJ   = new TH1F("mtLepNeuWJ",  "",nBinsMT,leftMT,rightMT);
TH1F *jetPtWJ      = new TH1F("jetPtWJ",     "",nBinsJetPt, leftJetPt, rightJetPt);
TH1F *leptonPtWJ   = new TH1F("leptonPtWJ",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *lepGenPtWJ   = new TH1F("lepGenPtWJ",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *leptonEtaWJ  = new TH1F("leptonEtaWJ", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *lepGenEtaWJ  = new TH1F("lepGenEtaWJ", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *neuGenPtWJ   = new TH1F("neuGenPtWJ",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *neuGenEtaWJ  = new TH1F("neuGenEtaWJ", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *metWJ        = new TH1F("metWJ",       "",nBinsMET,   leftMET,   rightMET);
TH1F *metGenWJ     = new TH1F("metGenWJ",    "",nBinsMET,   leftMET,   rightMET);
TH1F *massWGenWJ   = new TH1F("massWGenWJ",  "",nBinsM,     leftM,     rightM);
TH1F *dPhiLepMetWJ = new TH1F("dPhiLepMetWJ","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGenMetWJ = new TH1F("dPhiGenMetWJ","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGenLepWJ = new TH1F("dPhiGenLepWJ","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGepGetWJ = new TH1F("dPhiGepGetWJ","",nBinsDPhi, leftDPhi, rightDPhi);

TH1F *diMuonMassZJ = new TH1F("diMuonMassZJ","",nBinsM, leftM, rightM);
TH1F *diMuonQtZJ   = new TH1F("diMuonZJ",    "",nBinsQt,leftQt,rightQt);
TH1F *diMuGenQtZJ  = new TH1F("diMuGenZJ",   "",nBinsQt,leftQt,rightQt);
TH1F *mtZJ         = new TH1F("mtZJ",        "",nBinsMT,leftMT,rightMT);
TH1F *mtLepNeuZJ   = new TH1F("mtLepNeuZJ",  "",nBinsMT,leftMT,rightMT);
TH1F *jetPtZJ      = new TH1F("jetPtZJ",     "",nBinsJetPt, leftJetPt, rightJetPt);
TH1F *leptonPtZJ   = new TH1F("leptonPtZJ",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *lepGenPtZJ   = new TH1F("lepGenPtZJ",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *leptonEtaZJ  = new TH1F("leptonEtaZJ", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *lepGenEtaZJ  = new TH1F("lepGenEtaZJ", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *neuGenPtZJ   = new TH1F("neuGenPtZJ",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *neuGenEtaZJ  = new TH1F("neuGenEtaZJ", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *metZJ        = new TH1F("metZJ",       "",nBinsMET,   leftMET,   rightMET);
TH1F *metGenZJ     = new TH1F("metGenZJ",    "",nBinsMET,   leftMET,   rightMET);
TH1F *massWGenZJ   = new TH1F("massWGenZJ",  "",nBinsM,     leftM,     rightM);
TH1F *dPhiLepMetZJ = new TH1F("dPhiLepMetZJ","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGenMetZJ = new TH1F("dPhiGenMetZJ","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGenLepZJ = new TH1F("dPhiGenLepZJ","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGepGetZJ = new TH1F("dPhiGepGetZJ","",nBinsDPhi, leftDPhi, rightDPhi);

TH1F *diMuonMassT  = new TH1F("diMuonMassT", "",nBinsM, leftM, rightM);
TH1F *diMuonQtT    = new TH1F("diMuonT",     "",nBinsQt,leftQt,rightQt);
TH1F *diMuGenQtT   = new TH1F("diMuGenT",    "",nBinsQt,leftQt,rightQt);
TH1F *mtT          = new TH1F("mtT",         "",nBinsMT,leftMT,rightMT);
TH1F *mtLepNeuT    = new TH1F("mtLepNeuT",   "",nBinsMT,leftMT,rightMT);
TH1F *jetPtT       = new TH1F("jetPtT",      "",nBinsJetPt, leftJetPt, rightJetPt);
TH1F *leptonPtT    = new TH1F("leptonPtT",   "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *lepGenPtT    = new TH1F("lepGenPtT",   "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *leptonEtaT   = new TH1F("leptonEtaT",  "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *lepGenEtaT   = new TH1F("lepGenEtaT",  "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *neuGenPtT    = new TH1F("neuGenPtT",   "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *neuGenEtaT   = new TH1F("neuGenEtaT",  "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *metT         = new TH1F("metT",        "",nBinsMET,   leftMET,   rightMET);
TH1F *metGenT      = new TH1F("metGenT",     "",nBinsMET,   leftMET,   rightMET);
TH1F *massWGenT    = new TH1F("massWGenT",   "",nBinsM,     leftM,     rightM);
TH1F *dPhiLepMetT  = new TH1F("dPhiLepMetT", "",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGenMetT  = new TH1F("dPhiGenMetT", "",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGenLepT  = new TH1F("dPhiGenLepT", "",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGepGetT  = new TH1F("dPhiGepGetT", "",nBinsDPhi, leftDPhi, rightDPhi);

TH1F *diMuonMassVV = new TH1F("diMuonMassVV","",nBinsM, leftM, rightM);
TH1F *diMuonQtVV   = new TH1F("diMuonVV",    "",nBinsQt,leftQt,rightQt);
TH1F *diMuGenQtVV  = new TH1F("diMuGenVV",   "",nBinsQt,leftQt,rightQt);
TH1F *mtVV         = new TH1F("mtVV",        "",nBinsMT,leftMT,rightMT);
TH1F *mtLepNeuVV   = new TH1F("mtLepNeuVV",  "",nBinsMT,leftMT,rightMT);
TH1F *jetPtVV      = new TH1F("jetPtVV",     "",nBinsJetPt, leftJetPt, rightJetPt);
TH1F *leptonPtVV   = new TH1F("leptonPtVV",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *lepGenPtVV   = new TH1F("lepGenPtVV",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *leptonEtaVV  = new TH1F("leptonEtaVV", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *lepGenEtaVV  = new TH1F("lepGenEtaVV", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *neuGenPtVV   = new TH1F("neuGenPtVV",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *neuGenEtaVV  = new TH1F("neuGenEtaVV", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *metVV        = new TH1F("metVV",       "",nBinsMET,   leftMET,   rightMET);
TH1F *metGenVV     = new TH1F("metGenVV",    "",nBinsMET,   leftMET,   rightMET);
TH1F *massWGenVV   = new TH1F("massWGenVV",  "",nBinsM,     leftM,     rightM);
TH1F *dPhiLepMetVV = new TH1F("dPhiLepMetVV","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGenMetVV = new TH1F("dPhiGenMetVV","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGenLepVV = new TH1F("dPhiGenLepVV","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGepGetVV = new TH1F("dPhiGepGetVV","",nBinsDPhi, leftDPhi, rightDPhi);

TH1F *diMuonMassQCD= new TH1F("diMuonMassQCD","",nBinsM, leftM, rightM);
TH1F *diMuonQtQCD  = new TH1F("diMuonQCD",    "",nBinsQt,leftQt,rightQt);
TH1F *diMuGenQtQCD = new TH1F("diMuGenQCD",   "",nBinsQt,leftQt,rightQt);
TH1F *mtQCD        = new TH1F("mtQCD",        "",nBinsMT,leftMT,rightMT);
TH1F *mtLepNeuQCD  = new TH1F("mtLepNeuQCD",  "",nBinsMT,leftMT,rightMT);
TH1F *jetPtQCD     = new TH1F("jetPtQCD",     "",nBinsJetPt, leftJetPt, rightJetPt);
TH1F *leptonPtQCD  = new TH1F("leptonPtQCD",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *lepGenPtQCD  = new TH1F("lepGenPtQCD",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *leptonEtaQCD = new TH1F("leptonEtaQCD", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *lepGenEtaQCD = new TH1F("lepGenEtaQCD", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *neuGenPtQCD  = new TH1F("neuGenPtQCD",  "",nBinsLepPt, leftLepPt, rightLepPt);
TH1F *neuGenEtaQCD = new TH1F("neuGenEtaQCD", "",nBinsLepEta, leftLepEta, rightLepEta);
TH1F *metQCD       = new TH1F("metQCD",       "",nBinsMET,   leftMET,   rightMET);
TH1F *metGenQCD    = new TH1F("metGenQCD",    "",nBinsMET,   leftMET,   rightMET);
TH1F *massWGenQCD  = new TH1F("massWGenQCD",  "",nBinsM,     leftM,     rightM);
TH1F *dPhiLepMetQCD= new TH1F("dPhiLepMetQCD","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGenMetQCD= new TH1F("dPhiGenMetQCD","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGenLepQCD= new TH1F("dPhiGenLepQCD","",nBinsDPhi, leftDPhi, rightDPhi);
TH1F *dPhiGepGetQCD= new TH1F("dPhiGepGetQCD","",nBinsDPhi, leftDPhi, rightDPhi);

TH1F *diMuonMass=0, *diMuonQt=0, *diMuGenQt=0, *mt=0, *jetPt=0, *leptonPt=0, *lepGenPt=0, *leptonEta=0, *lepGenEta=0, *met=0, *metGen=0, *neuGenPt=0, *neuGenEta=0, *massWGen=0, *dPhiLepMet=0, *dPhiGenMet=0, *dPhiGenLep=0, *mtLepNeu=0, *dPhiGepGet=0;

double effAcc2muQt250 = 0, nGenQt250 = 0, effAcc1muQt250 = 0, nGenNu250 = 0;
double effAcc1mu = 0, nGen1mu = 0;

for(int entry=0; micro->GetEntry(entry) /*&& entry<10000*/; entry++){

/*
lepton1IsTight = 1;
lepton2IsTight = 1;
lepton3IsTight = 1;
*/
   if( type!=Data ) weight *= lumiScale;
//weight=1;
//   if( nTausGen==0 ) continue;

if(type==71) type = TTJets; // TTJets_HadronicMGDecays,
if(type==72) type = TTJets; // TTJets_SemiLeptMGDecays,
if(type==73) type = TTJets; // TTJets_FullLeptMGDecays,
if(type==74) type = TTJets; // BN_TTJets_FullLeptMGDecays,

   switch ( type ) {
     case Data:
             diMuonMass = diMuonMassAB;   diMuonQt   = diMuonQtAB;    mt         = mtAB;         jetPt      = jetPtAB;
             leptonPt   = leptonPtAB;     leptonEta  = leptonEtaAB;   met        = metAB;        mtLepNeu   = mtLepNeuAB;
             dPhiLepMet = dPhiLepMetAB;   dPhiGenMet = dPhiGenMetAB;  dPhiGenLep = dPhiGenLepAB; dPhiGepGet = dPhiLepMetAB;
             if( run<193752 ) weight *= scaler2012A; else weight *= scaler2012B; break;
     case TTJets:
             weight    *= scalerTTJets;
             diMuonMass = diMuonMassTT;   diMuonQt   = diMuonQtTT;    diMuGenQt  = diMuGenQtTT; 
             mt         = mtTT;           jetPt      = jetPtTT;       mtLepNeu   = mtLepNeuTT;
             leptonPt   = leptonPtTT;     lepGenPt   = lepGenPtTT;    leptonEta  = leptonEtaTT;   lepGenEta  = lepGenEtaTT;
             neuGenPt   = neuGenPtTT;     neuGenEta  = neuGenEtaTT;
             met        = metTT;          metGen     = metGenTT;      massWGen   = massWGenTT;
             dPhiLepMet = dPhiLepMetTT;   dPhiGenMet = dPhiGenMetTT;  dPhiGenLep = dPhiGenLepTT;  dPhiGepGet = dPhiGepGetTT;
     break;
     case WJets:
             weight    *= scalerWJetsToLNu;
             diMuonMass = diMuonMassWJ;   diMuonQt   = diMuonQtWJ;    diMuGenQt  = diMuGenQtWJ;
             mt         = mtWJ;           jetPt      = jetPtWJ;       mtLepNeu   = mtLepNeuWJ;
             leptonPt   = leptonPtWJ;     lepGenPt   = lepGenPtWJ;    leptonEta  = leptonEtaWJ;   lepGenEta  = lepGenEtaWJ;
             neuGenPt   = neuGenPtWJ;     neuGenEta  = neuGenEtaWJ;
             met        = metWJ;          metGen     = metGenWJ;      massWGen   = massWGenWJ;
             dPhiLepMet = dPhiLepMetWJ;   dPhiGenMet = dPhiGenMetWJ;  dPhiGenLep = dPhiGenLepWJ;  dPhiGepGet = dPhiGepGetWJ;
     break;

     case W1J:
             weight    *= scalerWJetsToLNu;
             diMuonMass = diMuonMassWJ;   diMuonQt   = diMuonQtWJ;    diMuGenQt  = diMuGenQtWJ;
             mt         = mtWJ;           jetPt      = jetPtWJ;       mtLepNeu   = mtLepNeuWJ;
             leptonPt   = leptonPtWJ;     lepGenPt   = lepGenPtWJ;    leptonEta  = leptonEtaWJ;   lepGenEta  = lepGenEtaWJ;
             neuGenPt   = neuGenPtWJ;     neuGenEta  = neuGenEtaWJ;
             met        = metWJ;          metGen     = metGenWJ;      massWGen   = massWGenWJ;
             dPhiLepMet = dPhiLepMetWJ;   dPhiGenMet = dPhiGenMetWJ;  dPhiGenLep = dPhiGenLepWJ;  dPhiGepGet = dPhiGepGetWJ;
     break;
     case W2J:
             weight    *= scalerWJetsToLNu;
             diMuonMass = diMuonMassWJ;   diMuonQt   = diMuonQtWJ;    diMuGenQt  = diMuGenQtWJ;
             mt         = mtWJ;           jetPt      = jetPtWJ;       mtLepNeu   = mtLepNeuWJ;
             leptonPt   = leptonPtWJ;     lepGenPt   = lepGenPtWJ;    leptonEta  = leptonEtaWJ;   lepGenEta  = lepGenEtaWJ;
             neuGenPt   = neuGenPtWJ;     neuGenEta  = neuGenEtaWJ;
             met        = metWJ;          metGen     = metGenWJ;      massWGen   = massWGenWJ;
             dPhiLepMet = dPhiLepMetWJ;   dPhiGenMet = dPhiGenMetWJ;  dPhiGenLep = dPhiGenLepWJ;  dPhiGepGet = dPhiGepGetWJ;
     break;
     case W3J:
             weight    *= scalerWJetsToLNu;
             diMuonMass = diMuonMassWJ;   diMuonQt   = diMuonQtWJ;    diMuGenQt  = diMuGenQtWJ;
             mt         = mtWJ;           jetPt      = jetPtWJ;       mtLepNeu   = mtLepNeuWJ;
             leptonPt   = leptonPtWJ;     lepGenPt   = lepGenPtWJ;    leptonEta  = leptonEtaWJ;   lepGenEta  = lepGenEtaWJ;
             neuGenPt   = neuGenPtWJ;     neuGenEta  = neuGenEtaWJ;
             met        = metWJ;          metGen     = metGenWJ;      massWGen   = massWGenWJ;
             dPhiLepMet = dPhiLepMetWJ;   dPhiGenMet = dPhiGenMetWJ;  dPhiGenLep = dPhiGenLepWJ;  dPhiGepGet = dPhiGepGetWJ;
     break;
     case W4J:
             weight    *= scalerWJetsToLNu;
             diMuonMass = diMuonMassWJ;   diMuonQt   = diMuonQtWJ;    diMuGenQt  = diMuGenQtWJ;
             mt         = mtWJ;           jetPt      = jetPtWJ;       mtLepNeu   = mtLepNeuWJ;
             leptonPt   = leptonPtWJ;     lepGenPt   = lepGenPtWJ;    leptonEta  = leptonEtaWJ;   lepGenEta  = lepGenEtaWJ;
             neuGenPt   = neuGenPtWJ;     neuGenEta  = neuGenEtaWJ;
             met        = metWJ;          metGen     = metGenWJ;      massWGen   = massWGenWJ;
             dPhiLepMet = dPhiLepMetWJ;   dPhiGenMet = dPhiGenMetWJ;  dPhiGenLep = dPhiGenLepWJ;  dPhiGepGet = dPhiGepGetWJ;
     break;

     case ZJets:
             weight    *= scalerZJetsToLL;
             diMuonMass = diMuonMassZJ;   diMuonQt   = diMuonQtZJ;    diMuGenQt  = diMuGenQtZJ;
             mt         = mtZJ;           jetPt      = jetPtZJ;       mtLepNeu   = mtLepNeuZJ;
             leptonPt   = leptonPtZJ;     lepGenPt   = lepGenPtZJ;    leptonEta  = leptonEtaZJ;   lepGenEta  = lepGenEtaZJ;
             neuGenPt   = neuGenPtZJ;     neuGenEta  = neuGenEtaZJ;
             met        = metZJ;          metGen     = metGenZJ;      massWGen   = massWGenZJ;
             dPhiLepMet = dPhiLepMetZJ;   dPhiGenMet = dPhiGenMetZJ;  dPhiGenLep = dPhiGenLepZJ;  dPhiGepGet = dPhiGepGetZJ;
     break;
     case WW:
             weight    *= scalerWW;
             diMuonMass = diMuonMassVV;   diMuonQt   = diMuonQtVV;    diMuGenQt  = diMuGenQtVV;
             mt         = mtVV;           jetPt      = jetPtVV;       mtLepNeu   = mtLepNeuVV;
             leptonPt   = leptonPtVV;     lepGenPt   = lepGenPtVV;    leptonEta  = leptonEtaVV;   lepGenEta  = lepGenEtaVV;
             neuGenPt   = neuGenPtVV;     neuGenEta  = neuGenEtaVV;
             met        = metVV;          metGen     = metGenVV;      massWGen   = massWGenVV;
             dPhiLepMet = dPhiLepMetVV;   dPhiGenMet = dPhiGenMetVV;  dPhiGenLep = dPhiGenLepVV;  dPhiGepGet = dPhiGepGetVV;
     break;
     case WZ:
             weight    *= scalerWZ;
             diMuonMass = diMuonMassVV;   diMuonQt   = diMuonQtVV;    diMuGenQt  = diMuGenQtVV;
             mt         = mtVV;           jetPt      = jetPtVV;       mtLepNeu   = mtLepNeuVV;
             leptonPt   = leptonPtVV;     lepGenPt   = lepGenPtVV;    leptonEta  = leptonEtaVV;   lepGenEta  = lepGenEtaVV;
             neuGenPt   = neuGenPtVV;     neuGenEta  = neuGenEtaVV;
             met        = metVV;          metGen     = metGenVV;      massWGen   = massWGenVV;
             dPhiLepMet = dPhiLepMetVV;   dPhiGenMet = dPhiGenMetVV;  dPhiGenLep = dPhiGenLepVV;  dPhiGepGet = dPhiGepGetVV;
     break;
     case ZZ:
             weight    *= scalerZZ;
             diMuonMass = diMuonMassVV;   diMuonQt   = diMuonQtVV;    diMuGenQt  = diMuGenQtVV;
             mt         = mtVV;           jetPt      = jetPtVV;       mtLepNeu   = mtLepNeuVV;
             leptonPt   = leptonPtVV;     lepGenPt   = lepGenPtVV;    leptonEta  = leptonEtaVV;   lepGenEta  = lepGenEtaVV;
             neuGenPt   = neuGenPtVV;     neuGenEta  = neuGenEtaVV;
             met        = metVV;          metGen     = metGenVV;      massWGen   = massWGenVV;
             dPhiLepMet = dPhiLepMetVV;   dPhiGenMet = dPhiGenMetVV;  dPhiGenLep = dPhiGenLepVV;  dPhiGepGet = dPhiGepGetVV;
     break;
     default :
       if( type>=Znunu && type<QCD ) return;
       if( type>=QCD   && type<Top ){
             weight    *= scalerQCD;
             diMuonMass = diMuonMassQCD;   diMuonQt   = diMuonQtQCD;  diMuGenQt  = diMuGenQtQCD;
             mt         = mtQCD;           jetPt      = jetPtQCD;     mtLepNeu   = mtLepNeuQCD;
             leptonPt   = leptonPtQCD;     lepGenPt   = lepGenPtQCD;  leptonEta  = leptonEtaQCD;  lepGenEta  = lepGenEtaQCD;
             neuGenPt   = neuGenPtQCD;     neuGenEta  = neuGenEtaQCD;
             met        = metQCD;          metGen     = metGenQCD;    massWGen   = massWGenQCD;
             dPhiLepMet = dPhiLepMetQCD;   dPhiGenMet = dPhiGenMetQCD;dPhiGenLep = dPhiGenLepQCD; dPhiGepGet = dPhiGepGetQCD;
       }
       if( type>=Top   && type<WW  ){
             weight    *= scalerSingleTop;
             diMuonMass = diMuonMassT;     diMuonQt   = diMuonQtT;     diMuGenQt  = diMuGenQtT;
             mt         = mtT;             jetPt      = jetPtT;        mtLepNeu   = mtLepNeuT;
             leptonPt   = leptonPtT;       lepGenPt   = lepGenPtT;     leptonEta  = leptonEtaT;   lepGenEta  = lepGenEtaT;
             neuGenPt   = neuGenPtT;       neuGenEta  = neuGenEtaT;
             met        = metT;            metGen     = metGenT;       massWGen   = massWGenT;
             dPhiLepMet = dPhiLepMetT;     dPhiGenMet = dPhiGenMetT;   dPhiGenLep = dPhiGenLepT;  dPhiGepGet = dPhiGepGetT;
       }
       break;
   }

   if( (entry%100000) == 0 ) std::cout<<"Event: "<<entry<<"/"<<micro->GetEntries()<<std::endl;

   if( lepton1PtGen>0   ) nGen1mu   += weight;
   if( (selection&1)==1 ) effAcc1mu += weight;

   TLorentzVector jet1, jet2, jet3;
   jet1.SetPtEtaPhiM(leadingJetPtRec, leadingJetEtaRec, leadingJetPhiRec, 0.);
   jet2.SetPtEtaPhiM(subleadJetPtRec, subleadJetEtaRec, subleadJetPhiRec, 0.);
   jet3.SetPtEtaPhiM(  thirdJetPtRec,   thirdJetEtaRec,   thirdJetPhiRec, 0.);
   TLorentzVector sumJets( jet1 + jet2 + jet3 );

   double genQt = 0;
   if( lepton1PtGen>0 && lepton2PtGen>0 ){
      // di-lepton event
      TLorentzVector lepton1, lepton2;
      lepton1.SetPtEtaPhiM(lepton1PtGen, lepton1EtaGen, lepton1PhiGen, 0.113);
      lepton2.SetPtEtaPhiM(lepton2PtGen, lepton2EtaGen, lepton2PhiGen, 0.113);
      TLorentzVector sum( lepton1 + lepton2 );
      genQt = sum.Pt();
      if( genQt > (MET>lookUpMET[lastStage]?MET:lookUpMET[lastStage]) ) nGenQt250 += weight;
      if( (selection & (lookUpMask[lastStage]&0xFFFE)) == (lookUpMask[lastStage]&0xFFFE) &&
          (lastStage<4 ? true : thirdJetPtRec>40 && (M3J>0 ? forthJetPtRec<35 && sumJets.M()<M3J : true)) )
         diMuGenQt->Fill(genQt, weight);
   }

   if( lepton1PtGen>0 && lepton2PtGen<0 ){
      // W candidate 
      if( (selection & (lookUpMask[lastStage]&0xFFFE)) == (lookUpMask[lastStage]&0xFFFE) &&
          (lastStage<4 ? true : thirdJetPtRec>40 && (M3J>0 ? forthJetPtRec<35 && sumJets.M()<M3J : true)) ){
         metGen->Fill(metPtRec, weight);
         if( metPtRec > (MET>lookUpMET[lastStage]?MET:lookUpMET[lastStage]) ){
            nGenNu250 += weight;
            lepGenPt ->Fill(lepton1PtGen,   weight);
            lepGenEta->Fill(lepton1EtaGen,  weight);
            neuGenPt ->Fill(neutrino1PtGen, weight);
            neuGenEta->Fill(neutrino1EtaGen,weight);

            TLorentzVector lepton, neutrino;
            lepton.  SetPtEtaPhiM(lepton1PtGen,   lepton1EtaGen,   lepton1PhiGen,   0.113);
            neutrino.SetPtEtaPhiM(neutrino1PtGen, neutrino1EtaGen, neutrino1PhiGen, 0.0);
            TLorentzVector sum( lepton + neutrino );
            massWGen ->Fill(sum.M());
         }
      }
   }

//   if( (trig&0x10)!=0x10 ) continue; // HLT_Ele27_WP80
   if( (trig&0x80000000)!=0x80000000 ) continue; // HLT_IsoMu24


if( type==Data && !uniqueEvents[run].insert(event).second ){
     cout<<"Run "<<run<<", event "<<event<<" was already processed"<<endl;
     continue;
}

   bool passB = false;
   switch(nBjets){
       case -2 : passB = (leadingJetCSV<0.244 && subleadJetCSV<0.244 && thirdJetCSV<0.244 && forthJetCSV<0.244); break;
       case -1 : passB = true; break;
       case  0 : passB = (numberOfBJets==0); break; //( leadingJetCSV<0.244 && subleadJetCSV<0.244 && thirdJetCSV<0.244 && forthJetCSV<0.244 ); break;
       case  1 : passB = (numberOfBJets==1); break;
       case  2 : passB = (numberOfBJets==2); break;
       default : break;
   }

   if( lepton1PtRec>40 && lepton2PtRec>40 && lepton1IsTight && lepton2IsTight && fabs(lepton1EtaRec)<2.1 && fabs(lepton2EtaRec)<2.1 && lepton3PtRec<10 ){
      if( genQt > (MET>lookUpMET[lastStage]?MET:lookUpMET[lastStage]) ) effAcc2muQt250 += weight;
///      if( (selection&15)==15 ){
      if( (selection & lookUpMask[lastStage]) == lookUpMask[lastStage] && (lastStage>=4 ? thirdJetPtRec>40 : true ) ){
         TLorentzVector lepton1, lepton2, realMET;
         lepton1.SetPtEtaPhiM(lepton1PtRec, lepton1EtaRec, lepton1PhiRec, 0.113);
         lepton2.SetPtEtaPhiM(lepton2PtRec, lepton2EtaRec, lepton2PhiRec, 0.113);
         realMET.SetPtEtaPhiM(metPtRec,     0,             metPhiRec,     0.);
         TLorentzVector sum( lepton1 + lepton2 );
         double fakeMET = TLorentzVector( sum + realMET ).Pt();
///         TLorentzVector qT ( sum.Pt(), 0, sum.Phi(), 0);
///         TLorentzVector met( metPtRec, 0, metPhiRec, 0);
///         TLorentzVector mqT( met + qT );
///         mqT.SetE(mqT.Pt());
///         double fakeMET = mqT.Pt();

         if( fakeMET > (MET>lookUpMET[lastStage]?MET:lookUpMET[lastStage]) && passB  && (M3J>0 ? forthJetPtRec<35 && sumJets.M()<M3J : true) ){
            diMuonMass->Fill( sum.M(),  weight);
            if( sum.M()>60 && sum.M()<120 ) diMuonQt  ->Fill( sum.Pt(), weight);
         }
      }
   }

   if( lepton1PtRec>40 && lepton1IsTight && lepton2PtRec<10 && fabs(lepton1EtaRec)<2.1 ){
      if( (selection & lookUpMask[lastStage]) == lookUpMask[lastStage] && (lastStage>=4 ? thirdJetPtRec>40 : true ) ){

         if( metPtRec > (MET>lookUpMET[lastStage]?MET:lookUpMET[lastStage]) && passB  && (M3J>0 ? forthJetPtRec<35 && sumJets.M()<M3J : true) ){
///cout<<"event: "<<event<<" entry="<<entry<<" sel="<<selection<<" thirdJetPtRec="<<thirdJetPtRec<<" forthJetPtRec="<<forthJetPtRec<<" passB="<<passB<<" metPtRec="<<metPtRec<<endl;

             double MT = sqrt(2*lepton1PtRec*metPtRec*(1-cos(metPhiRec-lepton1PhiRec)));
             mt->Fill( MT, weight );
             effAcc1muQt250 += weight;

             if( MT>=0 && MT<180 ) met->Fill(metPtRec, weight);
             leptonPt ->Fill(lepton1PtRec,  weight);
//             leptonEta->Fill(lepton1EtaRec, weight);

             double dPhi = fabs(metPhiRec-lepton1PhiRec);
             if( dPhi>3.1415927 ) dPhi = 2.*3.1415927 - dPhi;
             dPhiLepMet->Fill( dPhi, weight );
             dPhi = fabs(metPhiGen-lepton1PhiGen);
             if( dPhi>3.1415927 ) dPhi = 2.*3.1415927 - dPhi;
             dPhiGepGet->Fill( dPhi, weight );
             dPhi = fabs(lepton1PhiGen-lepton1PhiRec);
             if( dPhi>3.1415927 ) dPhi = 2.*3.1415927 - dPhi;
             if( lepton1PtGen>0 ) dPhiGenLep->Fill( dPhi, weight );
             dPhi = fabs(metPhiRec-metPhiGen);
             if( dPhi>3.1415927 ) dPhi = 2.*3.1415927 - dPhi;
             if( metPhiGen>0 ) dPhiGenMet->Fill( dPhi, weight ); else dPhiGenMet->Fill( (double)0, weight );
if( lepton1PtGen>0 && metPtGen>0 ){
TLorentzVector lep, neu;
lep.SetPtEtaPhiM(lepton1PtGen, lepton1EtaGen, lepton1PhiGen, 0);
neu.SetPtEtaPhiM(metPtGen,     metEtaGen,     metPhiGen,     0);

             MT = sqrt(2*lepton1PtGen*metPtGen*(1-cos(metPhiGen-lepton1PhiGen)));
//             if( (lep+neu).M()>50 )
             mtLepNeu->Fill( MT, weight );
//             mtLepNeu->Fill( (lep+neu).M(), weight );
//             leptonEta->Fill( (lep+neu).Eta(), weight );
//cout<<"MT="<<MT<<" lepton1PtGen="<<lepton1PtGen<<" neutrino1PtGen="<<neutrino1PtGen<<" neutrino1PhiGen="<<neutrino1PhiGen<<" lepton1PhiRec="<<lepton1PhiRec<<endl;
}
//if( type == WJets ) cout<<"WJ "<<event<<" weight="<<weight<<" MT="<<sqrt(2*lepton1PtRec*metPtRec*(1-cos(metPhiRec-lepton1PhiRec)))<<endl;
///   leptonPt->Fill(lepton1PtRec, weight);
///   jetPt->Fill(leadingJetPtRec, weight);
///   met->Fill(metPtRec, weight);
         }
      }
   }
}

if( nGen1mu>0   ) effAcc1mu      /= nGen1mu;
if( nGenQt250>0 ) effAcc2muQt250 /= nGenQt250;
if( nGenNu250>0 ) effAcc1muQt250 /= nGenNu250;
std::cout<<"Single mu acc x eff = "<<effAcc1mu<<std::endl;

if( nGenQt250>0 ) std::cout<<"Di-muon efficiency x acceptance for MET>"<<(MET>lookUpMET[lastStage]?MET:lookUpMET[lastStage])<<" = "<<effAcc2muQt250<<std::endl;
if( nGenNu250>0 ) std::cout<<"Single muon efficiency x acceptance for MET>"<<(MET>lookUpMET[lastStage]?MET:lookUpMET[lastStage])<<" = "<<effAcc1muQt250<<std::endl;
//return;

string outputName( lookUpName[lastStage] );
switch( nBjets ){
  case -2 : outputName.append("_vetoB"); break;
  case -1 : outputName.append("_anyBs"); break;
  case 0  : outputName.append("_0b"); break;
  case 1  : outputName.append("_1b"); break;
  case 2  : outputName.append("_2b"); break;
  default : outputName.append("_fewBs"); break;
}
char buff[128];
sprintf(buff,"MET%d",int(MET>lookUpMET[lastStage]?MET:lookUpMET[lastStage]));
if( M3J>0 ){
   sprintf(buff,"%sm3j",buff);
   if( M3J<10000 )
      sprintf(buff,"%s%d",buff,int(M3J));
   else
      sprintf(buff,"%sINF",buff);
}
outputName.append(buff);
if( process==SIG ) outputName.append("_S");
if( process==ZJets ) outputName.append("_ZJ");
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

if( process==WJets || process==TTJets || process==ZJets || process==W1J || process==W2J || process==W3J || process==W4J )
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

if( process==-1 || process==Data || process==A || process==B || process==C || process==D || process==E ){
diMuonMassAB->Write();
diMuonQtAB->Write();
mtAB->Write();
leptonPtAB->Write();
leptonEtaAB->Write();
metAB->Write();
dPhiLepMetAB->Write();
dPhiGepGetAB->Write();
dPhiGenMetAB->Write();
dPhiGenLepAB->Write();
mtLepNeuAB->Write();
}

if( process==-1 || process==TTJets ){
diMuonMassTT->Write();
diMuonQtTT->Write();
diMuGenQtTT->Write();
mtTT->Write();
leptonPtTT->Write();
leptonEtaTT->Write();
lepGenPtTT->Write();
lepGenEtaTT->Write();
neuGenPtTT->Write();
dPhiLepMetTT->Write();
neuGenEtaTT->Write();
metTT->Write();
metGenTT->Write();
massWGenTT->Write();
dPhiGepGetTT->Write();
dPhiGenMetTT->Write();
dPhiGenLepTT->Write();
mtLepNeuTT->Write();
}

if( process==-1 || process==W1J || process==W2J || process==W3J || process==W4J || process==WJets ){
diMuonMassWJ->Write();
diMuonQtWJ->Write();
diMuGenQtWJ->Write();
mtWJ->Write();
leptonPtWJ->Write();
leptonEtaWJ->Write();
lepGenPtWJ->Write();
lepGenEtaWJ->Write();
neuGenPtWJ->Write();
neuGenEtaWJ->Write();
metWJ->Write();
metGenWJ->Write();
massWGenWJ->Write();
dPhiLepMetWJ->Write();
dPhiGepGetWJ->Write();
dPhiGenMetWJ->Write();
dPhiGenLepWJ->Write();
mtLepNeuWJ->Write();
}

if( process==-1 || process==ZJets || process==Znunu ){
diMuonMassZJ->Write();
diMuonQtZJ->Write();
diMuGenQtZJ->Write();
mtZJ->Write();
leptonPtZJ->Write();
leptonEtaZJ->Write();
lepGenPtZJ->Write();
lepGenEtaZJ->Write();
neuGenPtZJ->Write();
neuGenEtaZJ->Write();
metZJ->Write();
metGenZJ->Write();
massWGenZJ->Write();
dPhiLepMetZJ->Write();
dPhiGepGetZJ->Write();
dPhiGenMetZJ->Write();
dPhiGenLepZJ->Write();
mtLepNeuZJ->Write();
}

if( process==-1 || process==WW || process==WZ || process==ZZ ){
diMuonMassVV->Write();
diMuonQtVV->Write();
diMuGenQtVV->Write();
mtVV->Write();
leptonPtVV->Write();
leptonEtaVV->Write();
lepGenPtVV->Write();
lepGenEtaVV->Write();
neuGenPtVV->Write();
neuGenEtaVV->Write();
metVV->Write();
metGenVV->Write();
massWGenVV->Write();
dPhiLepMetVV->Write();
dPhiGepGetVV->Write();
dPhiGenMetVV->Write();
dPhiGenLepVV->Write();
mtLepNeuVV->Write();
}

if( process==-1 || process==Top ){
diMuonMassT ->Write();
diMuonQtT ->Write();
diMuGenQtT ->Write();
mtT ->Write();
leptonPtT->Write();
leptonEtaT->Write();
lepGenPtT->Write();
lepGenEtaT->Write();
neuGenPtT ->Write();
neuGenEtaT ->Write();
metT->Write();
metGenT->Write();
massWGenT ->Write();
dPhiLepMetT->Write();
dPhiGepGetT->Write();
dPhiGenMetT->Write();
dPhiGenLepT->Write();
mtLepNeuT ->Write();
}

if( process==-1 || process==QCD ){
diMuonMassQCD->Write();
diMuonQtQCD->Write();
diMuGenQtQCD->Write();
mtQCD->Write();
leptonPtQCD->Write();
leptonEtaQCD->Write();
lepGenPtQCD->Write();
lepGenEtaQCD->Write();
neuGenPtQCD->Write();
neuGenEtaQCD->Write();
metQCD->Write();
metGenQCD->Write();
massWGenQCD->Write();
dPhiLepMetQCD->Write();
dPhiGepGetQCD->Write();
dPhiGenMetQCD->Write();
dPhiGenLepQCD->Write();
mtLepNeuQCD->Write();
}

/*
jetPtAB->Write();
jetPtTT->Write();
jetPtWJ->Write();
jetPtZJ->Write();
jetPtVV->Write();
jetPtT->Write();
jetPtQCD->Write();
*/

out->Write();
out->Close();
}
