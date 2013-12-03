{
TChain *tt  = new TChain("micro");
TChain *top = new TChain("micro");
TChain *wj  = new TChain("micro");
TChain *zj  = new TChain("micro");
TChain *ww  = new TChain("micro");
TChain *wz  = new TChain("micro");
TChain *zz  = new TChain("micro");
TChain *data  = new TChain("micro");

/*
tt ->AddFile("/data/users/kkotov/2013.07.07/micro_TT_metSel.root");
top->AddFile("/data/users/kkotov/2013.07.07/micro_T_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.07.07/micro_W1J_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.07.07/micro_W2J_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.07.07/micro_W3J_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.07.07/micro_W4J_metSel.root");
zj ->AddFile("/data/users/kkotov/2013.07.07/micro_ZN_metSel.root");
ww ->AddFile("/data/users/kkotov/2013.07.07/micro_WW_metSel.root");
wz ->AddFile("/data/users/kkotov/2013.07.07/micro_WZ_metSel.root");
zz ->AddFile("/data/users/kkotov/2013.07.07/micro_ZZ_metSel.root");
data->AddFile("/data/users/kkotov/2013.07.07/micro_MET2012A_metSel.root");
data->AddFile("/data/users/kkotov/2013.07.07/micro_MET2012B_metSel.root");
data->AddFile("/data/users/kkotov/2013.07.07/micro_MET2012C_metSel.root");
data->AddFile("/data/users/kkotov/2013.07.07/micro_MET2012D_metSel.root");
data->AddFile("/data/users/kkotov/2013.07.07/micro_MET2012E_metSel.root");
*/
/*
tt ->AddFile("/data_tmp/users/kkotov/2013.10.30/micro_TT1_metSel.root");
tt ->AddFile("/data_tmp/users/kkotov/2013.10.30/micro_TT2_metSel.root");
tt ->AddFile("/data_tmp/users/kkotov/2013.10.30/micro_TT3_metSel.root");
tt ->AddFile("/data_tmp/users/kkotov/2013.10.30/micro_TT4_metSel.root");
tt ->AddFile("/data_tmp/users/kkotov/2013.10.30/micro_TT5_metSel.root");
tt ->AddFile("/data_tmp/users/kkotov/2013.10.30/micro_TT6_metSel.root");
tt ->AddFile("/data_tmp/users/kkotov/2013.10.30/micro_TT7_metSel.root");
tt ->AddFile("/data_tmp/users/kkotov/2013.10.30/micro_TT8_metSel.root");
tt ->AddFile("/data_tmp/users/kkotov/2013.10.30/micro_TT9_metSel.root");
tt ->AddFile("/data_tmp/users/kkotov/2013.10.30/micro_TT10_metSel.root");
tt ->AddFile("/data_tmp/users/kkotov/2013.10.30/micro_TT11_metSel.root");
tt ->AddFile("/data_tmp/users/kkotov/2013.10.30/micro_TT12_metSel.root");
*/

tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TThh1_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TThh2_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TThh3_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TThh4_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TThh5_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TThh6_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TThh7_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TThh8_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TTlh1_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TTlh2_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TTlh3_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TTlh4_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TTlh5_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TTlh6_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TTlh7_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TTll1_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TTll2_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TTll3_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TTll4_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TTll5_metSel.root");
tt ->AddFile("/data/users/kkotov/2013.11.15/micro_TTll6_metSel.root");
top->AddFile("/data/users/kkotov/2013.11.15/micro_T1_metSel.root");
top->AddFile("/data/users/kkotov/2013.11.15/micro_T2_metSel.root");
top->AddFile("/data/users/kkotov/2013.11.15/micro_T3_metSel.root");
top->AddFile("/data/users/kkotov/2013.11.15/micro_T4_metSel.root");
top->AddFile("/data/users/kkotov/2013.11.15/micro_T5_metSel.root");
top->AddFile("/data/users/kkotov/2013.11.15/micro_T6_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W1J1_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W1J2_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W1J3_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W1J4_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W1J5_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W1J6_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W1J7_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W1J8_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W1J9_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W1J10_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W1J11_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W1J12_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W2J1_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W2J2_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W2J3_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W2J4_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W2J5_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W2J6_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W2J7_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W2J8_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W2J9_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W3J1_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W3J2_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W3J3_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W3J4_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W3J5_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W3J6_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W3J7_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W3J8_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W4J1_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W4J2_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W4J3_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W4J4_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W4J5_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W4J6_metSel.root");
wj ->AddFile("/data/users/kkotov/2013.11.15/micro_W4J7_metSel.root");
zj ->AddFile("/data/users/kkotov/2013.11.15/micro_ZN1_metSel.root");
zj ->AddFile("/data/users/kkotov/2013.11.15/micro_ZN2_metSel.root");
zj ->AddFile("/data/users/kkotov/2013.11.15/micro_ZN3_metSel.root");
zj ->AddFile("/data/users/kkotov/2013.11.15/micro_ZN4_metSel.root");
ww ->AddFile("/data/users/kkotov/2013.11.15/micro_WW1_metSel.root");
ww ->AddFile("/data/users/kkotov/2013.11.15/micro_WW2_metSel.root");
ww ->AddFile("/data/users/kkotov/2013.11.15/micro_WW3_metSel.root");
ww ->AddFile("/data/users/kkotov/2013.11.15/micro_WW4_metSel.root");
ww ->AddFile("/data/users/kkotov/2013.11.15/micro_WW5_metSel.root");
wz ->AddFile("/data/users/kkotov/2013.11.15/micro_WZ1_metSel.root");
wz ->AddFile("/data/users/kkotov/2013.11.15/micro_WZ2_metSel.root");
wz ->AddFile("/data/users/kkotov/2013.11.15/micro_WZ3_metSel.root");
wz ->AddFile("/data/users/kkotov/2013.11.15/micro_WZ4_metSel.root");
wz ->AddFile("/data/users/kkotov/2013.11.15/micro_WZ5_metSel.root");
zz ->AddFile("/data/users/kkotov/2013.11.15/micro_ZZ1_metSel.root");
zz ->AddFile("/data/users/kkotov/2013.11.15/micro_ZZ2_metSel.root");
zz ->AddFile("/data/users/kkotov/2013.11.15/micro_ZZ3_metSel.root");
zz ->AddFile("/data/users/kkotov/2013.11.15/micro_ZZ4_metSel.root");
zz ->AddFile("/data/users/kkotov/2013.11.15/micro_ZZ5_metSel.root");

data->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012A_metSel.root");
data->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012B_metSel.root");
data->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012C_metSel.root");
data->AddFile("/data/users/kkotov/2013.11.15/micro_MET2012D_metSel.root");

const char *cut[] = {
"Stage -1: Total expected             ",
"Stage  0: Loose electon veto         ",
"Stage  1: Loose muon veto            ",
"Stage  2: $\\geq$ 1 jet $>$60~\\GeVc   ",
"Stage  3: $\\geq$ 2 jets $>$60~\\GeVc  ",
"Stage  4: $\\geq$ 3 jets $>$40~\\GeVc  ",
"Stage  5: 4$^{th}$ jet \\pt$<$35~\\GeVc",
"Stage  6: $M(3 jets)<$250~\\GeVcc     ",

"Stage  7: $E_T^{Miss} >$250~\\GeV     ",
"\%Stage  7:    Veto  CSVl  b tags      ",
"~~~Stage  7: With   0 CSVm b tags    ",
"~~~Stage  7: With   1 CSVm b tag     ",
"\%~~~Stage  7: With   2 CSVm b tags    ",

"Stage  8: $E_T^{Miss} >$300~\\GeVc    ",
"\%Stage  8:    Veto  CSVl  b tags      ",
"~~~Stage  8: With   0 CSVm b tags    ",
"~~~Stage  8: With   1 CSVm b tag     ",
"\%~~~Stage  8: With   2 CSVm b tags    ",

"Stage  9: $E_T^{Miss} >$350~\\GeV     ",
"\%~~~Stage  9:    Veto  CSVl b tags    ",
"~~~Stage  9: With   0 CSVm b tags    ",
"~~~Stage  9: With   1 CSVm b tag     ",
"\%~~~Stage  9: With   2 CSVm b tags    ",

"Stage 10: $E_T^{Miss} >$400~\\GeVc    ",
"\%~~~Stage 10:    Veto  CSVl b tags    ",
"~~~Stage 10: With   0 CSVm b tags    ",
"~~~Stage 10: With   1 CSVm b tag     ",
"\%~~~Stage 10: With   2 CSVm b tags    "
};



TH1F *tmp = new TH1F("tmp","",10000,0,10000);

//double lumiScale = (0.802 + 4.403 + 6.388 + 7.248)/5.;
double lumiScale = ( 19.7 )/5.;

cout<<"Cut                               &   TTJets   & ZJetsToNuNu & WJetsToLNu &  Top  &   VV   &   Total  & MET "<<endl;
for(int sel=-1; sel<27; sel++){ //22
  char buff[512];
  switch( sel ){
    case -1 : sprintf(buff,"weight"); break;
    case  0 : sprintf(buff,"((selection&1)==1)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case  1 : sprintf(buff,"((selection&3)==3)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case  2 : sprintf(buff,"((selection&7)==7)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case  3 : sprintf(buff,"((selection&15)==15)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case  4 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;

    case  5 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case  6 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case  7 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>250)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;

    case  8 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>250 && numberOfBJets==0 && "
                           "leadingJetCSV<0.244 && subleadJetCSV<0.244 && thirdJetCSV<0.244 && forthJetCSV<0.244)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case  9 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>250 && numberOfBJets==0)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case 10 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>250 && numberOfBJets==1)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case 11 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>250 && numberOfBJets==2)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;

    case 12 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>300)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case 13 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>300 && numberOfBJets==0 && "
                           "leadingJetCSV<0.244 && subleadJetCSV<0.244 && thirdJetCSV<0.244 && forthJetCSV<0.244)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case 14 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>300 && numberOfBJets==0)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case 15 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>300 && numberOfBJets==1)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case 16 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>300 && numberOfBJets==2)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;

    case 17 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>350)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case 18 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>350 && numberOfBJets==0 && "
                           "leadingJetCSV<0.244 && subleadJetCSV<0.244 && thirdJetCSV<0.244 && forthJetCSV<0.244)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case 19 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>350 && numberOfBJets==0)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case 20 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>350 && numberOfBJets==1)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case 21 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>350 && numberOfBJets==2)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;

    case 22 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>400)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case 23 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>400 && numberOfBJets==0 && "
                           "leadingJetCSV<0.244 && subleadJetCSV<0.244 && thirdJetCSV<0.244 && forthJetCSV<0.244)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case 24 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>400 && numberOfBJets==0)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case 25 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>400 && numberOfBJets==1)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;
    case 26 : sprintf(buff,"((selection&15)==15 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && metPtRec>400 && numberOfBJets==2)*weight*sqrt(exp(0*(0.156-0.00137*t1PtGen))*exp(0*(0.156-0.00137*t2PtGen)))"); break;

    default : exit(0); break;
  }

  tt->Draw("type>>tmp",buff);
  double ttYield  = tmp->Integral() * lumiScale;
  zj->Draw("type>>tmp",buff);
  double zjYield = tmp->Integral() * lumiScale;
  wj->Draw("type>>tmp",buff);
  double wjYield  = tmp->Integral() * lumiScale * 1.23;
  top->Draw("type>>tmp",buff);
  double topYield = tmp->Integral() * lumiScale;
  ww->Draw("type>>tmp",buff);
  double wwYield  = tmp->Integral() * lumiScale;
  wz->Draw("type>>tmp",buff);
  double wzYield  = tmp->Integral() * lumiScale;
  zz->Draw("type>>tmp",buff);
  double zzYield  = tmp->Integral() * lumiScale;
  double vvYield  = wwYield + wzYield + zzYield;
  data->Draw("type>>tmp",buff);
  double dataYield  = tmp->Integral();

  cout<<cut[sel+1]<<" & "<<long(ttYield+0.5)<<" & "<<long(zjYield+0.5)<<" & "<<long(wjYield+0.5)<<" & "<<long(topYield+0.5)<<" & "<<long(vvYield+0.5)<<" & "<<long(ttYield+zjYield+wjYield+topYield+vvYield+0.5)<<"  \\\\ "<<dataYield<<endl;
}

}
