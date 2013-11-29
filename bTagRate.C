{
gROOT->ProcessLine(".L ../../../../tdrstyle.C");
setTDRStyle();

TChain *micro  = new TChain("micro");
//micro->AddFile("micro_HT_Run2012A_metSel.root");
//micro->AddFile("micro_JetHT_Run2012B-13Jul2012-v1_AOD_metSel.root");
//micro->AddFile("micro_BN_QCD_Pt-120to170_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3_AODSIM_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_QCD_170_300_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_QCD_300_470_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_QCD_470_600_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_QCD_600_800_metSel.root");
micro->AddFile("/data/users/kkotov/2013.11.15/micro_QCD_800_1000_metSel.root");

TH1F *probB_pT  = new TH1F("probB_pT", "",100,0,500);
TH1F *probB_eta = new TH1F("probB_eta","",100,-2.1,2.1);
TH2F *probB_2d  = new TH2F("probB_2d","",10,-2.1,2.1,10,0,500);

char buff[128];
/*
sprintf(buff,"(otherTRIGs&8) && (selection&31)==31 && thirdJetPtRec>40 && forthJetPtRec<35 && numberOfBJets>0 && metPtRec>0");

micro->Draw("firstBJetPtRec>>probB_pT",buff);
micro->Draw("firstBJetEtaRec>>probB_eta",buff);
micro->Draw("firstBJetPtRec:firstBJetEtaRec>>probB_2d",buff);
*/
TH1F *norm = new TH1F("norm","",100,0,100);

sprintf(buff,"(otherTRIGs&8192) && ((selection&31)==31 && thirdJetPtRec>40 && forthJetPtRec<35 && metPtRec>150)*weight");
//sprintf(buff,"(otherTRIGs&1024) && ((selection&31)==31 && thirdJetPtRec>40 && forthJetPtRec>40 && numberOfJets==4 && metPtRec>0)*weight");
micro->Draw("numberOfBJets>>norm",buff);
cout<<norm->GetEntries()<<endl;

TFile *out = new TFile("bTagRateHists4jetsHT250_150.root","RECREATE");
//probB_pT->Write();
//probB_eta->Write();
//probB_2d->Write();
norm->Write();
out->Write();
out->Close();
}
