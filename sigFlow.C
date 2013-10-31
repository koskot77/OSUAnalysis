#include<iomanip>

void sigFlow(void){
TChain *sig  = new TChain("micro");
sig->AddFile("/data/users/kkotov/2013.05.12/micro_signals_metSel.root");
sig->AddFile("/data/users/kkotov/2013.05.12/micro_signalsMore_metSel.root");

const char *cut[] = {
"Stage -1: Number generated          ",
"Stage  0: Loose muon veto           ",
"Stage  1: Loose electron veto       ",
"Stage  2: $\\geq$ 1 jet $>$60~\\GeVc ",
"Stage  3: $\\geq$ 2 jets $>$60~\\GeVc",
"Stage  4: $\\geq$ 3 jets $>$40~\\GeVc",
"Stage  5: 4$^{th}$ jet \\pt$<$35~\\GeVc",
"Stage  6: $M(3 jets)<$250~\\GeVcc",

"Stage  7: $E_T^{Miss} >$250~\\Ge/c  ",
"Stage  8:    veto  CSVl $b$-tag      ",
"Stage  8:        0 CSVm $b$-tag      ",
"Stage  8:        1 CSVm $b$-tag      ",
"Stage  8:        2 CSVm $b$-tag      ",

"Stage  8: $E_T^{Miss} >$300~\\GeVc  ",
"Stage  9:    veto  CSVl $b$-tag      ",
"Stage  9:        0 CSVm $b$-tag      ",
"Stage  9:        1 CSVm $b$-tag      ",
"Stage  9:        2 CSVm $b$-tag      ",

"Stage  9: $E_T^{Miss} >$350~\\GeVc   ",
"Stage 10:    veto  CSVl $b$-tag      ",
"Stage 10:        0 CSVm $b$-tag      ",
"Stage 10:        1 CSVm $b$-tag      ",
"Stage 10:        2 CSVm $b$-tag      ",

"Stage 10: $E_T^{Miss} >$400~\\GeVc  ",
"Stage 11:    veto  CSVl $b$-tag      ",
"Stage 11:        0 CSVm $b$-tag      ",
"Stage 11:        1 CSVm $b$-tag      ",
"Stage 11:        2 CSVm $b$-tag      "
};

TH1F *tmp = new TH1F("tmp","",-100,0,10000);

enum {S3m0=47, S3m50=50, S3m100=52, S3m150=53, S3m200=54, S3m300=55, S3m400=67, S3m500=56, S3m600=68,
      S4m0=27, S4m50=30, S4m100=32, S4m150=33, S4m200=34, S4m300=35, S4m400=69, S4m500=36, S4m600=70, S4m700=71, S4m800=72, S4m900=73, S4m1000=74};

//double lumiScale = (0.802 + 4.403 + 6.388 + 7.248)/5.;
double lumiScale = ( 19.6 )/5.;

cout<<"Cut                               &  0  &  50  &  100  &  150  &  200  &  300  &  400  &  500  &  600  \\\\ \\hline "<<endl;
for(int sel=-1; sel<27; sel++){
  char buff[512];
  switch( sel ){
    case -1 : sprintf(buff,"(1)*weight"); break;
    case  0 : sprintf(buff,"((selection&1)==1)*weight"); break;
    case  1 : sprintf(buff,"((selection&3)==3)*weight"); break;
    case  2 : sprintf(buff,"((selection&7)==7)*weight"); break;
    case  3 : sprintf(buff,"((selection&15)==15)*weight"); break;
    case  4 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40)*weight"); break;

    case  5 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35)*weight"); break;
    case  6 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250)*weight"); break;
    case  7 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>250)*weight"); break;

    case  8 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>250 && numberOfBJets==0 && "
                           "leadingJetCSV<0.244 && subleadJetCSV<0.244 && thirdJetCSV<0.244 && forthJetCSV<0.244)*weight"); break;
    case  9 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>250 && numberOfBJets==0)*weight"); break;
    case 10 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>250 && numberOfBJets==1)*weight"); break;
    case 11 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>250 && numberOfBJets==2)*weight"); break;

    case 12 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>300)*weight"); break;
    case 13 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>300 && numberOfBJets==0 && "
                           "leadingJetCSV<0.244 && subleadJetCSV<0.244 && thirdJetCSV<0.244 && forthJetCSV<0.244)*weight"); break;
    case 14 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>300 && numberOfBJets==0)*weight"); break;
    case 15 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>300 && numberOfBJets==1)*weight"); break;
    case 16 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>300 && numberOfBJets==2)*weight"); break;

    case 17 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>350)*weight"); break;
    case 18 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>350 && numberOfBJets==0 && "
                           "leadingJetCSV<0.244 && subleadJetCSV<0.244 && thirdJetCSV<0.244 && forthJetCSV<0.244)*weight"); break;
    case 19 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>350 && numberOfBJets==0)*weight"); break;
    case 20 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>350 && numberOfBJets==1)*weight"); break;
    case 21 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>350 && numberOfBJets==2)*weight"); break;

    case 22 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>400)*weight"); break;
    case 23 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>400 && numberOfBJets==0 && "
                           "leadingJetCSV<0.244 && subleadJetCSV<0.244 && thirdJetCSV<0.244 && forthJetCSV<0.244)*weight"); break;
    case 24 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>400 && numberOfBJets==0)*weight"); break;
    case 25 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>400 && numberOfBJets==1)*weight"); break;
    case 26 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && thMrec<250 && metPtRec>400 && numberOfBJets==2)*weight"); break;

    default : exit(0); break;
  }

  char buff2[1024];
  sprintf(buff2,"%s*(type==%d)",buff,S3m0); 
  sig->Draw("type>>tmp",buff2);
  double sig0yield = tmp->Integral() * lumiScale;
  sprintf(buff2,"%s*(type==%d)",buff,S3m50); 
  sig->Draw("type>>tmp",buff2);
  double sig50yield = tmp->Integral() * lumiScale;
  sprintf(buff2,"%s*(type==%d)",buff,S3m100); 
  sig->Draw("type>>tmp",buff2);
  double sig100yield  = tmp->Integral() * lumiScale;
  sprintf(buff2,"%s*(type==%d)",buff,S3m150);
  sig->Draw("type>>tmp",buff2);
  double sig150yield = tmp->Integral() * lumiScale;
  sprintf(buff2,"%s*(type==%d)",buff,S3m200); 
  sig->Draw("type>>tmp",buff2);
  double sig200yield  = tmp->Integral() * lumiScale;
  sprintf(buff2,"%s*(type==%d)",buff,S3m300); 
  sig->Draw("type>>tmp",buff2);
  double sig300yield  = tmp->Integral() * lumiScale;
  sprintf(buff2,"%s*(type==%d)",buff,S3m400); 
  sig->Draw("type>>tmp",buff2);
  double sig400yield  = tmp->Integral() * lumiScale;
  sprintf(buff2,"%s*(type==%d)",buff,S3m500); 
  sig->Draw("type>>tmp",buff2);
  double sig500yield  = tmp->Integral() * lumiScale;
  sprintf(buff2,"%s*(type==%d)",buff,S3m600); 
  sig->Draw("type>>tmp",buff2);
  double sig600yield  = tmp->Integral() * lumiScale;


  cout<<cut[sel+1]<<" & "<<setw(7)<<int(sig0yield+0.5)<<" & "<<setw(7)<<int(sig50yield+0.5)<<" & "<<setw(7)<<int(sig100yield+0.5)<<" & "<<setw(7)<<int(sig150yield+0.5)<<" & "<<setw(7)<<int(sig200yield+0.5)<<" & "<<setw(7)<<int(sig300yield+0.5)<<" & "<<setw(7)<<int(sig400yield+0.5)<<" & "<<setw(7)<<int(sig500yield+0.5)<<" & "<<setw(7)<<int(sig600yield+0.5)<<" \\\\ "<<endl;
}

}
