{
gROOT->ProcessLine(".L ../../../../tdrstyle.C");
setTDRStyle();
TChain micro("micro");
micro.AddFile("/data/users/kkotov/2013.07.07/micro_W1J_muSel.root");
micro.AddFile("/data/users/kkotov/2013.07.07/micro_W2J_muSel.root");
micro.AddFile("/data/users/kkotov/2013.07.07/micro_W3J_muSel.root");
micro.AddFile("/data/users/kkotov/2013.07.07/micro_W4J_muSel.root");

TH1F lepton1PtGen250 ("lepton1PtGen250", "",100,-2,98);
TH1F lepton1EtaGen250("lepton1EtaGen250","",100,-5,5);
TH1F lepton1PtGen300 ("lepton1PtGen300", "",100,-2,98);
TH1F lepton1EtaGen300("lepton1EtaGen300","",100,-5,5);
TH1F lepton1PtGen350 ("lepton1PtGen350", "",100,-2,98);
TH1F lepton1EtaGen350("lepton1EtaGen350","",100,-5,5);
TH1F lepton1PtGen400 ("lepton1PtGen400", "",100,-2,98);
TH1F lepton1EtaGen400("lepton1EtaGen400","",100,-5,5);
micro.Draw("lepton1PtGen>>lepton1PtGen250",  "metPtRec>250 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250");
micro.Draw("lepton1EtaGen>>lepton1EtaGen250","metPtRec>250 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && lepton1PtGen>0");
micro.Draw("lepton1PtGen>>lepton1PtGen300",  "metPtRec>300 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250");
micro.Draw("lepton1EtaGen>>lepton1EtaGen300","metPtRec>300 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && lepton1PtGen>0");
micro.Draw("lepton1PtGen>>lepton1PtGen350",  "metPtRec>350 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250");
micro.Draw("lepton1EtaGen>>lepton1EtaGen350","metPtRec>350 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && lepton1PtGen>0");
micro.Draw("lepton1PtGen>>lepton1PtGen400",  "metPtRec>400 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250");
micro.Draw("lepton1EtaGen>>lepton1EtaGen400","metPtRec>400 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && lepton1PtGen>0");

TH2F lepton1PtEtaGen250("lepton1PtEtaGen250", "",100,-2,98,100,-5,5);
TH2F lepton1PtEtaGen300("lepton1PtEtaGen300", "",100,-2,98,100,-5,5);
TH2F lepton1PtEtaGen350("lepton1PtEtaGen350", "",100,-2,98,100,-5,5);
TH2F lepton1PtEtaGen400("lepton1PtEtaGen400", "",100,-2,98,100,-5,5);
micro.Draw("lepton1EtaGen:lepton1PtGen>>lepton1PtEtaGen250", "metPtRec>250 && (selection&28)==28 && m3jets<250 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250");
micro.Draw("lepton1EtaGen:lepton1PtGen>>lepton1PtEtaGen300", "metPtRec>300 && (selection&28)==28 && m3jets<250 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250");
micro.Draw("lepton1EtaGen:lepton1PtGen>>lepton1PtEtaGen350", "metPtRec>350 && (selection&28)==28 && m3jets<250 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250");
micro.Draw("lepton1EtaGen:lepton1PtGen>>lepton1PtEtaGen400", "metPtRec>400 && (selection&28)==28 && m3jets<250 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250");

TH1F leptonTauPtGen250("leptonTauPtGen250", "", 100, -2, 98);
TH1F leptonTauPtGen300("leptonTauPtGen300", "", 100, -2, 98);
TH1F leptonTauPtGen350("leptonTauPtGen350", "", 100, -2, 98);
TH1F leptonTauPtGen400("leptonTauPtGen400", "", 100, -2, 98);
micro.Draw("lepton1PtGen>>leptonTauPtGen250", "metPtRec>250 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && nTausGen>0 && m3jets<250");
micro.Draw("lepton1PtGen>>leptonTauPtGen300", "metPtRec>300 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && nTausGen>0 && m3jets<250");
micro.Draw("lepton1PtGen>>leptonTauPtGen350", "metPtRec>350 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && nTausGen>0 && m3jets<250");
micro.Draw("lepton1PtGen>>leptonTauPtGen400", "metPtRec>400 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && nTausGen>0 && m3jets<250");

TH1F lepton1PtRec250 ("lepton1PtRec250", "",100, -2, 98);
TH1F lepton1PFiso250 ("lepton1PFiso250", "", 100, -2, 8);
TH1F lepton1PtRec300 ("lepton1PtRec300", "",100, -2, 98);
TH1F lepton1PFiso300 ("lepton1PFiso300", "", 100, -2, 8);
TH1F lepton1PtRec350 ("lepton1PtRec350", "",100, -2, 98);
TH1F lepton1PFiso350 ("lepton1PFiso350", "", 100, -2, 8);
TH1F lepton1PtRec400 ("lepton1PtRec400", "",100, -2, 98);
TH1F lepton1PFiso400 ("lepton1PFiso400", "", 100, -2, 8);
micro.Draw("lepton1PtRec>>lepton1PtRec250", "metPtRec>250 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && lepton1PtGen>10 && abs(lepton1EtaGen)<2.4");
micro.Draw("lepton1PFiso>>lepton1PFiso250", "metPtRec>250 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && lepton1PtGen>10 && abs(lepton1EtaGen)<2.4 && lepton1PtRec>0");
micro.Draw("lepton1PtRec>>lepton1PtRec300", "metPtRec>300 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && lepton1PtGen>10 && abs(lepton1EtaGen)<2.4");
micro.Draw("lepton1PFiso>>lepton1PFiso300", "metPtRec>300 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && lepton1PtGen>10 && abs(lepton1EtaGen)<2.4 && lepton1PtRec>0");
micro.Draw("lepton1PtRec>>lepton1PtRec350", "metPtRec>350 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && lepton1PtGen>10 && abs(lepton1EtaGen)<2.4");
micro.Draw("lepton1PFiso>>lepton1PFiso350", "metPtRec>350 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && lepton1PtGen>10 && abs(lepton1EtaGen)<2.4 && lepton1PtRec>0");
micro.Draw("lepton1PtRec>>lepton1PtRec400", "metPtRec>400 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && lepton1PtGen>10 && abs(lepton1EtaGen)<2.4");
micro.Draw("lepton1PFiso>>lepton1PFiso400", "metPtRec>400 && (selection&28)==28 && thirdJetPtRec>40 && forthJetPtRec<35 && m3jets<250 && lepton1PtGen>10 && abs(lepton1EtaGen)<2.4 && lepton1PtRec>0");

TFile f("ineffMuWnJm3j.root","RECREATE");
lepton1PtGen250.Write();
lepton1EtaGen250.Write();
lepton1PtGen300.Write();
lepton1EtaGen300.Write();
lepton1PtGen350.Write();
lepton1EtaGen350.Write();
lepton1PtGen400.Write();
lepton1EtaGen400.Write();

lepton1PtEtaGen250.Write();
lepton1PtEtaGen300.Write();
lepton1PtEtaGen350.Write();
lepton1PtEtaGen400.Write();

leptonTauPtGen250.Write();
leptonTauPtGen300.Write();
leptonTauPtGen350.Write();
leptonTauPtGen400.Write();

lepton1PtRec250.Write();
lepton1PFiso250.Write();
lepton1PtRec300.Write();
lepton1PFiso300.Write();
lepton1PtRec350.Write();
lepton1PFiso350.Write();
lepton1PtRec400.Write();
lepton1PFiso400.Write();

f.Write();
f.Close();

}
