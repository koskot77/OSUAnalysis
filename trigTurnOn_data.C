{
gROOT->ProcessLine(".L ../../../../tdrstyle.C");
setTDRStyle();

TChain *microABCD  = new TChain("micro");
TChain *microA = new TChain("micro");
TChain *microB = new TChain("micro");
TChain *microC = new TChain("micro");
TChain *microD = new TChain("micro");
TChain *microWJ= new TChain("micro");
//microABCD->AddFile("/data/users/kkotov/2013.07.07/micro_SingleMu2012A_muSel.root");
//microA->AddFile("/data/users/kkotov/2013.07.07/micro_SingleMu2012A_muSel.root");
//microB->AddFile("/data/users/kkotov/2013.07.07/micro_SingleMu2012A_muSel.root");
//microC->AddFile("/data/users/kkotov/2013.07.07/micro_SingleMu2012A_muSel.root");
//microD->AddFile("/data/users/kkotov/2013.07.07/micro_SingleMu2012A_muSel.root");

microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012A_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012A1_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012B1_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012B2_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012B3_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012B4_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012B5_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C1_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C2_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C3_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C4_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C5_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C6_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C7_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C8_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C9_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D1_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D2_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D3_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D4_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D5_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D6_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D7_muSel.root");
microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D8_muSel.root");
//microABCD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012E_muSel.root");
microA->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012A_muSel.root");
microA->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012A1_muSel.root");
microB->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012B1_muSel.root");
microB->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012B2_muSel.root");
microB->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012B3_muSel.root");
microB->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012B4_muSel.root");
microB->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012B5_muSel.root");
microC->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C1_muSel.root");
microC->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C2_muSel.root");
microC->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C3_muSel.root");
microC->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C4_muSel.root");
microC->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C5_muSel.root");
microC->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C6_muSel.root");
microC->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C7_muSel.root");
microC->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C8_muSel.root");
microC->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012C9_muSel.root");
microD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D1_muSel.root");
microD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D2_muSel.root");
microD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D3_muSel.root");
microD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D4_muSel.root");
microD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D5_muSel.root");
microD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D6_muSel.root");
microD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D7_muSel.root");
microD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012D8_muSel.root");
//microD->AddFile("/data/users/kkotov/2013.09.18/micro_SingleMu2012E_muSel.root");
microWJ->AddFile("/data/users/kkotov/2013.09.18/micro_W1J_muSel.root");
microWJ->AddFile("/data/users/kkotov/2013.09.18/micro_W2J_muSel.root");
microWJ->AddFile("/data/users/kkotov/2013.09.18/micro_W3J_muSel.root");
microWJ->AddFile("/data/users/kkotov/2013.09.18/micro_W4J_muSel.root");

TCanvas *cnv = new TCanvas();

int   dataType[] = {0,0,0,0,0,-1};
char *dataName[] = {"Run2012", "Run2012A", "Run2012B", "Run2012C", "Run2012D", "WJets"};
int   nTypes     = sizeof(dataType)/sizeof(int);
int markerColors[nTypes] = {1, 4, 590, 38, 824, 8};//, 8, 50, 42};
TChain *micro[nTypes] = {microABCD, microA, microB, microC, microD, microWJ};

TGraphErrors *turnOns[nTypes];

for(int type=0; type<nTypes; type++){
   cout<<"Type:"<<type<<endl;

int metThreshold[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 180, 200, 240, 280, 350, 500, 1000};
int nPoints = sizeof(metThreshold)/sizeof(int);

turnOns[type] = new TGraphErrors(nPoints-1);
char name[128];
sprintf(name,"turnOn%d",type);
turnOns[type]->SetName(name);

for(int point=0; point<nPoints-1; point++){
   cout<<"Point:"<<point<<endl;
   TH1F *htemp = new TH1F("htemp","",2,0,2);
   char selection[1024];
   sprintf(selection,"(metPtRec>%d && metPtRec<%d && lepton1PtRec>40 && ( abs(metPhiRec-lepton1PhiRec)<3.1415927 ? abs(metPhiRec-lepton1PhiRec)<2.5 : (2.*3.1415927 - abs(metPhiRec-lepton1PhiRec))<2.5 ) && (muTRIGs&0x80000000)==0x80000000 && leadingJetPtRec>35 && subleadJetPtRec>35 && thirdJetPtRec>35)*weight", //&& type==%d ",//&& leadingJetPtRec>150 && subleadJetPtRec>150",  (muTRIGs&0x2000000000000)==0x2000000000000
//                     " && abs(leadingJetEtaRec)<2 && abs(subleadJetEtaRec)<2",lepton1PtRec>100 && 
          metThreshold[point],metThreshold[point+1]);//,dataType[type]);
   micro[type]->Draw("(((otherTRIGs&256)==256) + 0.5)>>htemp", selection);
   int metTotal = htemp->Integral();
   int metPass  = htemp->GetBinContent(2);
   if( !metTotal ) continue;
//cout<<selection<<" : metTotal="<<metTotal<<" metPass="<<metPass<<endl;
   double eff = metPass/(double)metTotal;
   turnOns[type]->SetPoint(point,metThreshold[point],eff);
   turnOns[type]->SetPointError(point,0, sqrt(eff*(1-eff)/metTotal) );
   delete htemp;
}

}

TLegend *leg = new TLegend(0.5,0.15,0.9,0.6);
leg->SetShadowColor(0);
leg->SetFillColor(0);
leg->SetLineColor(0);
leg->SetLineWidth(0);

turnOns[0]->GetXaxis()->SetTitle("#slash{E}_{T} (GeV)");
turnOns[0]->GetYaxis()->SetTitle("Efficiency");
turnOns[0]->SetTitle("HLT_PFMET150 turn-on in Run2012");

cnv->SetGridx();
cnv->SetGridy();
cnv->Draw();

for(int type=0; type<nTypes; type++){
   turnOns[type]->SetMarkerColor(markerColors[type]);
   turnOns[type]->SetLineColor(markerColors[type]);
   turnOns[type]->SetMarkerStyle(1);
   if(type==0) turnOns[type]->Draw("APL");
   else        turnOns[type]->Draw("PL");
   leg->AddEntry(turnOns[type],dataName[type],"pl");
}

leg->Draw();

TArrow *arrow = new TArrow(120,0.8,120,0);
arrow->SetLineWidth(2);
arrow->SetLineColor(2);
arrow->Draw();
TLatex *text = new TLatex(35,0.83,"#slash{E}^{trig}_{T}>120 GeV");
text->SetTextSize(0.04);
text->Draw();

TFile f("turnOn.root","RECREATE");
cnv->Write();
f.Write();
f.Close();
}
