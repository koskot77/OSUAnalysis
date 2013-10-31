{
gROOT->ProcessLine(".L ../../../../tdrstyle.C");
setTDRStyle();

TChain *micro = new TChain("micro");
//micro->AddFile("/data/users/kkotov/2013.07.07/micro_WJ_muSel.root");
//micro->AddFile("/data/users/kkotov/2013.07.07/micro_ZZ_muSel.root");
micro->AddFile("/data/users/kkotov/2013.09.18/micro_W1J_muSel.root");
micro->AddFile("/data/users/kkotov/2013.09.18/micro_W2J_muSel.root");
micro->AddFile("/data/users/kkotov/2013.09.18/micro_W3J_muSel.root");
micro->AddFile("/data/users/kkotov/2013.09.18/micro_W4J_muSel.root");

TCanvas *cnv = new TCanvas();

   TH1F *hMet = new TH1F("hMet","",2,0,2);
   micro->Draw("(((otherTRIGs&256)==256) + 0.5)>>hMet","metPtRec>250");

   TH1F *hMu = new TH1F("hMu","",2,0,2);
   micro->Draw("(((muTRIGs&0x80000000)==0x80000000) + 0.5)>>hMu","lepton1PtRec>40 && abs(lepton1EtaRec)<2.1 && lepton1PFiso<0.1");

   TH1F *hMuMet = new TH1F("hMuMet","",2,0,2);
   micro->Draw("((((muTRIGs&0x80000000)==0x80000000 && (otherTRIGs&256)==256)) + 0.5)>>hMuMet","metPtRec>250 && lepton1PtRec>40 && abs(lepton1EtaRec)<2.1 && lepton1PFiso<0.1  &&  ( abs(metPhiRec-lepton1PhiRec)<3.1415927 ? abs(metPhiRec-lepton1PhiRec)<2.5 : (2.*3.1415927 - abs(metPhiRec-lepton1PhiRec))<2.5 )");

   int metTotal   = hMet->Integral();
   int metPass    = hMet->GetBinContent(2);
   if( !metTotal ) continue;
   double  effMet = metPass/(double)metTotal;
   double deffMet = sqrt(effMet*(1-effMet)/metTotal);
   delete hMet;
   cout<<"effMet = "<<effMet<<" +- "<<deffMet<<endl;

   int muTotal   = hMu->Integral();
   int muPass    = hMu->GetBinContent(2);
   if( !muTotal ) continue;
   double  effMu = muPass/(double)muTotal;
   double deffMu = sqrt(effMu*(1-effMu)/muTotal);
   delete hMu;
   cout<<"effMu = "<<effMu<<" +- "<<deffMu<<endl;

   int muMetTotal = hMuMet->Integral();
   int muMetPass  = hMuMet->GetBinContent(2);
   if( !muMetTotal ) continue;
   double  effMuMet = muMetPass/(double)muMetTotal;
   double deffMuMet = sqrt(effMuMet*(1-effMuMet)/muMetTotal);
   delete hMuMet;
   cout<<"effMuMet = "<<effMuMet<<" +- "<<deffMuMet<<endl;

   cout<<" effMuMet / effMet / effMu = "<< effMuMet/effMet/effMu <<endl;
}

