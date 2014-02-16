#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <list>

#include "TH1.h"
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"

#include "RooRealVar.h"
#include "RooArgSet.h"
#include "RooAddPdf.h"
#include "RooRandom.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"

#include "RooStats/ModelConfig.h"
#include "RooStats/HybridCalculator.h"
#include "RooStats/FrequentistCalculator.h"
#include "RooStats/ToyMCSampler.h"
#include "RooStats/NumEventsTestStat.h"
#include "RooStats/ProfileLikelihoodTestStat.h"
#include "RooStats/SamplingDistPlot.h"

#include "RooStats/HypoTestInverter.h"
#include "RooStats/HypoTestInverterResult.h"
#include "RooStats/HypoTestInverterPlot.h"

#include "../../../tdrstyle.C"

using namespace RooFit;
using namespace RooStats;
using namespace std;

const bool debug   = false;//true;
const bool verbose = false;//true;

// POI name
const char *inverterName = "result_signalXsec;1";

// directories with results, make sure you have a set, corresponding to the choise of the type above 
const int   nPoints = 5;
//const double mass  [nPoints] = {200., 300., 400., 500., 600.};
//const char *results[nPoints] = {"S3m200", "S3m300", "S3m400", "S3m500", "S3m600"};
const double mass  [nPoints] = {500., 600., 700., 800., 900.};
const char *results[nPoints] = {"S4m500", "S4m600", "S4m700", "S4m800", "S4m800"};

double findCrossing(double massA, double massB, double limitA, double limitB, TF1 *func);

// plot scans and limits
void limits(void){
   // style
   setTDRStyle();

///   const char **results = 0;
//   const char *fileNamePattern = "Freq_CLs_grid_ts3_seed";
   const char *fileNamePattern = "_MET2.root";
   const char *outputFileName  = "output";

   // limits
   double expectedLimit[nPoints], observedLimit[nPoints];
   double expectedMinus1SigmaLimit[nPoints], expectedPlus1SigmaLimit[nPoints];
   double expectedMinus2SigmaLimit[nPoints], expectedPlus2SigmaLimit[nPoints];

   int nNonEmptyPoints = 0; 
   // loop over all of the mass points
   for(int point=0; point<nPoints; point++){
      // collects all of the parts with subsets of pseudo experiments
      list<string> parts;
      DIR *dp;
      if((dp = opendir(results[point])) == NULL) {
         cout<<"Error while opening the folder"<<endl;
         return;
      }
      struct dirent *dirp;
      while((dirp = readdir(dp)) != NULL) {
         if( strstr(dirp->d_name,fileNamePattern) == NULL || strstr(dirp->d_name,"Freq_") == NULL ) continue; 
         char buff[128];
         sprintf(buff,"%s/%s",results[point],dirp->d_name);
         parts.push_back(buff);
      }
      closedir(dp);
      // find a file with result
      list<string>::const_iterator fileIter = parts.begin();
      if( fileIter == parts.end() ){
         cout<<"Warning: no suitable results found in "<<results[point]<<", skipping to the next point ..."<<endl;
         expectedLimit[point] = -1;
         observedLimit[point] = -1;
         continue;
      }
      // construct the result
      TFile *file = new TFile( fileIter->c_str() );
      HypoTestInverterResult *r = (HypoTestInverterResult*) file->Get(inverterName); 
      fileIter++;
      // add up the rest of the results to get a descent statistics of the pseudo experiemnts
      while( fileIter != parts.end() ){
         TFile *f = new TFile( fileIter->c_str() );
         HypoTestInverterResult *r2 = dynamic_cast<HypoTestInverterResult*>( f->Get(inverterName) );
         r->Add(*r2);
         delete r2;
         fileIter++;
      }
      // compute the limits
      expectedLimit[point] = r->GetExpectedUpperLimit(0);
      observedLimit[point] = r->UpperLimit();
      expectedMinus1SigmaLimit[point] = r->GetExpectedUpperLimit(-1);
      expectedPlus1SigmaLimit [point] = r->GetExpectedUpperLimit(1);
      expectedMinus2SigmaLimit[point] = r->GetExpectedUpperLimit(-2);
      expectedPlus2SigmaLimit [point] = r->GetExpectedUpperLimit(2);
      // print the limits
      cout<<"The computed upper limit is: "<< observedLimit[point] <<" +/- "<< r->UpperLimitEstimatedError() <<endl;
      cout<< " expected limit (median) "  <<  expectedLimit[point] <<endl;
      cout<< " expected limit (-1 sig) "  <<  expectedMinus1SigmaLimit[point] <<endl;
      cout<< " expected limit (+1 sig) "  <<  expectedPlus1SigmaLimit [point] <<endl;
      cout<< " expected limit (-2 sig) "  <<  expectedMinus2SigmaLimit[point] <<endl;
      cout<< " expected limit (+2 sig) "  <<  expectedPlus2SigmaLimit [point] <<endl;
      // and plot the scan
      char buff[128];
      sprintf(buff,"c%s",results[point]);
      TCanvas *cnv = new TCanvas(buff,buff);
      sprintf(buff,"HTI_Result_Plot_%s",results[point]);
      HypoTestInverterPlot *plot = new HypoTestInverterPlot(buff,"CL Scan",reinterpret_cast<HypoTestInverterResult*>(r));
      plot->Draw("");  // use "CLb 2CL" options to plot CLs, CLs+b and Clb
      for(int i=0; i<cnv->GetListOfPrimitives()->GetSize(); i++)
         cout<<"Object ["<<i<<"]"<<cnv->GetListOfPrimitives()->At(i)->GetName()<<endl;
      TLegend *leg = (TLegend*) cnv->GetListOfPrimitives()->FindObject("TPave");
      if( leg ){
         leg->SetShadowColor(0);
         leg->SetLineColor(0);
         leg->SetFillColor(0);
         leg->SetX1NDC(0.35);
         leg->SetY1NDC(0.35);
      }
      TGraphErrors *ge = (TGraphErrors*) cnv->GetListOfPrimitives()->FindObject("CLs_observed");
      if( ge ){
         ge->SetMarkerColor(2);
         ge->GetXaxis()->SetTitle("#sigma_{signal} #times Br (pb)");
         ge->GetYaxis()->SetTitle("#it{p}-value");
      }
      // if needed, plot test statistics distributions for the two hypothesis 
      if(debug){ 
         const int nEntries = r->ArraySize();
         cout<<"# of pseudo experiments: "<<nEntries<<endl;
         for(int i=0; i<nEntries; i++){
            //char buff[128];
            sprintf(buff,"cYield%s_%d",results[point],i);
            TCanvas *c = new TCanvas(buff,buff);
            SamplingDistPlot * pl = plot->MakeTestStatPlot(i);
            if( !pl ) continue;
            TH1F *hist = pl->GetTH1F(NULL);
            sprintf(buff,"%s%d",hist->GetName(),i);
            hist->SetName( buff );
            if(verbose){
               cout<<"Point="<<i<<endl;
               const vector<Double_t>& bg  = r->GetBackgroundTestStatDist(i)->GetSamplingDistribution();
               const vector<Double_t>& bgw = r->GetBackgroundTestStatDist(i)->GetSampleWeights();
               const vector<Double_t>& alt = r->GetSignalAndBackgroundTestStatDist(i)->GetSamplingDistribution();
               const vector<Double_t>& altw= r->GetSignalAndBackgroundTestStatDist(i)->GetSampleWeights();
               cout<<"bg: ";  for(unsigned int j=0;j<bg.size();j++)  cout<<bg[j] <<", "; cout<<endl; //"/"<<bgw[j]<<", "; cout<<endl;
               cout<<"alt: "; for(unsigned int j=0;j<alt.size();j++) cout<<alt[j]<<", "; cout<<endl; //"/"<<altw[j]<<", "; cout<<endl;
               const Double_t xlow = *(std::min_element(bg.begin(), bg.end()));
               const Double_t xup = *(std::max_element(bg.begin(), bg.end()));
               cout<<"xlow= "<<xlow<<" xup="<<xup<<endl;
            }
            c->Divide(1,2);
            c->cd(1);
            pl->SetLogYaxis(true);
            pl->Draw();
            SamplingDistribution * s = r->GetExpectedPValueDist(i);
            SamplingDistPlot *p = new SamplingDistPlot();
            p->AddSamplingDistribution(s);
//            const vector<Double_t>& pVals = s->GetSamplingDistribution();
//            cout<<"p-values: "; for(int j=0;j<pVals.size();j++) cout<<pVals[j]<<", "; cout<<endl;
            c->cd(2);
            p->Draw();
         }
      }
      nNonEmptyPoints++;
   }

   // visual representation of the results
   TGraph *expectedLimitPlot = new TGraph(nNonEmptyPoints); expectedLimitPlot->SetName("expectedLimitPlot");
   TGraph *observedLimitPlot = new TGraph(nNonEmptyPoints); observedLimitPlot->SetName("observedLimitPlot");
   TGraphAsymmErrors *expected1SigmaLimitPlot = new TGraphAsymmErrors(nNonEmptyPoints); expected1SigmaLimitPlot->SetName("expected1SigmaLimitPlot");
   TGraphAsymmErrors *expected2SigmaLimitPlot = new TGraphAsymmErrors(nNonEmptyPoints); expected2SigmaLimitPlot->SetName("expected2SigmaLimitPlot");
 
   for(int point=0, n=0; point<nPoints; point++){
      if( expectedLimit[point]<0 ) continue;
      observedLimitPlot->SetPoint(n, mass[point], observedLimit[point]);
      expectedLimitPlot->SetPoint(n, mass[point], expectedLimit[point]);
      expected1SigmaLimitPlot->SetPoint(n, mass[point], expectedLimit[point]);
      expected2SigmaLimitPlot->SetPoint(n, mass[point], expectedLimit[point]);
      expected1SigmaLimitPlot->SetPointError(n, 0,0, expectedLimit[point]-expectedMinus1SigmaLimit[point], expectedPlus1SigmaLimit[point]-expectedLimit[point]);
      expected2SigmaLimitPlot->SetPointError(n, 0,0, expectedLimit[point]-expectedMinus2SigmaLimit[point], expectedPlus2SigmaLimit[point]-expectedLimit[point]);
      n++;
   }

   observedLimitPlot->SetMarkerColor(4);
   observedLimitPlot->SetLineStyle(1);

   expectedLimitPlot->SetMarkerStyle(1);
   expectedLimitPlot->SetMarkerColor(1);
   expectedLimitPlot->SetLineStyle(2);

   expected1SigmaLimitPlot->SetLineWidth(1);
   expected1SigmaLimitPlot->SetLineColor(1);
   expected1SigmaLimitPlot->SetFillColor(3);
   expected1SigmaLimitPlot->SetMarkerStyle(0);
   expected1SigmaLimitPlot->SetMarkerColor(3);

   expected2SigmaLimitPlot->SetLineWidth(1);
   expected2SigmaLimitPlot->SetLineColor(1);
   expected2SigmaLimitPlot->SetFillColor(5);
   expected2SigmaLimitPlot->SetMarkerStyle(0);
   expected2SigmaLimitPlot->SetMarkerColor(5);
//   expected2SigmaLimitPlot->SetMaximum(2.0);
   expected2SigmaLimitPlot->SetMaximum(1.1);
   expected2SigmaLimitPlot->SetMinimum(0);
   expected2SigmaLimitPlot->GetXaxis()->SetTitle("M (GeV/#it{c}^{2})");
   expected2SigmaLimitPlot->GetYaxis()->SetTitle("95\% C.L. limit on #sigma #times Br (pb)");

//expected2SigmaLimitPlot->SetTitle("Vector DM");//, E^{miss}_{T}>350 GeV");
expected2SigmaLimitPlot->SetTitle("Scalar DM");//, E^{miss}_{T}>350 GeV");

//   const double MonotopS3CrossSectionPoints[7][2] = { {0,8.307}, {50, 6.705}, {100, 4.159}, {150, 2.299}, {200, 1.412}, {300, .6048}, {500, .1463} };
//   const double MonotopS4CrossSectionPoints[7][2] = { {0,100.0}, {50, 133.8}, {100, 41.67}, {150, 18.46}, {200, 9.687}, {300, 3.289}, {500, .6325} };

   const double MonotopS3CrossSectionPoints[9][2]  = { {0,6.314}, {50, 5.072}, {100, 3.406}, {150, 2.227}, {200, 1.447}, {300, .6242}, {400, .2903}, {500, .1490}, {600, .07878} };
   const double MonotopS4CrossSectionPoints[13][2] = { {0,93.26}, {50, 110.0}, {100, 36.37}, {150, 17.46}, {200, 9.357}, {300, 3.216}, {400, 1.304}, {500, 0.607},
                                                  {600, 0.298}, {700, 0.1578}, {800, 0.08733}, {900, 0.05012}, {1000, 0.02969} };

   TGraph *s3Xsec = new TGraph(9); s3Xsec->SetName("s3Xsec");
   for(unsigned int point=0; point<sizeof(MonotopS3CrossSectionPoints)/2/sizeof(double); point++)
     s3Xsec->SetPoint(point, MonotopS3CrossSectionPoints[point][0], MonotopS3CrossSectionPoints[point][1]);

   TGraph *s4Xsec = new TGraph(9); s4Xsec->SetName("s4Xsec");
   for(unsigned int point=0; point<sizeof(MonotopS4CrossSectionPoints)/2/sizeof(double); point++)
     s4Xsec->SetPoint(point, MonotopS4CrossSectionPoints[point][0], MonotopS4CrossSectionPoints[point][1]);


//   TF1 *func = new TF1("func","[0]*exp(-[1]*pow(x,[2]))",200,600);
   TF1 *func = new TF1("func","[0]*exp(-[1]*pow(x,[2]))",500,900);
   func->SetParameter(0,100); func->SetParameter(1,0.01); func->SetParameter(2,1);
//   s3Xsec->Fit("func","R"); s3Xsec->Fit("func","R");
   s4Xsec->Fit("func","R"); s4Xsec->Fit("func","R");
   func->SetLineWidth(2);
   func->SetLineColor(2);
   TCanvas *cnv = new TCanvas();
   cnv->SetGridx();
   cnv->SetGridy();

   expected2SigmaLimitPlot->Draw("APF3");
   expected1SigmaLimitPlot->Draw("PF3");
   observedLimitPlot->SetLineWidth(2);
   observedLimitPlot->SetLineColor(4);
   observedLimitPlot->Draw("PL");
   expectedLimitPlot->Draw("PL");

   func->Draw("same");
   s3Xsec->SetLineWidth(2);
   s3Xsec->SetLineColor(2);
   s4Xsec->SetLineWidth(2);
   s4Xsec->SetLineColor(2);
//   s3Xsec->Draw("L");
//   s4Xsec->Draw("L");

   TLegend *leg = new TLegend(0.45,0.5,0.9,0.9); leg->SetShadowColor(0); leg->SetFillColor(0); leg->SetLineColor(0);
//   leg->AddEntry(func,"theory cross section","l");
   leg->AddEntry(s3Xsec,"Scalar DM theory #sigma#times Br","l");
//   leg->AddEntry(s4Xsec,"Vector DM theory #sigma#times Br","l");
   leg->AddEntry(expectedLimitPlot,"expected limit","l");
   leg->AddEntry(observedLimitPlot,"observed limit","pl");
   leg->AddEntry(expected1SigmaLimitPlot,"expected #pm 1 #sigma limit","f");
   leg->AddEntry(expected2SigmaLimitPlot,"expected #pm 2 #sigma limit","f");
   leg->Draw();

//   TLatex *cmsPrelim = new TLatex(277.6, 2.04, "CMS Preliminary 19.7 pb^{-1} at #sqrt{s}=8 TeV");
   TLatex *cmsPrelim = new TLatex(580.1, 1.13, "CMS Preliminary 19.7 pb^{-1} at #sqrt{s}=8 TeV");
   cmsPrelim->Draw();

   ////////////////////////////////////////
   int pointObs=0;
   while( pointObs<nPoints && observedLimit[pointObs]<func->Eval(mass[pointObs]) ) pointObs++;

   int pointExp=0;
   while( pointExp<nPoints && expectedLimit[pointExp]<func->Eval(mass[pointExp]) ) pointExp++;

   int pointPlus1Sigma=0;
   while( pointPlus1Sigma<nPoints && expectedPlus1SigmaLimit[pointPlus1Sigma]<func->Eval(mass[pointPlus1Sigma]) ) pointPlus1Sigma++;

   int pointMinus1Sigma=0;
   while( pointMinus1Sigma<nPoints && expectedMinus1SigmaLimit[pointMinus1Sigma]<func->Eval(mass[pointMinus1Sigma]) ) pointMinus1Sigma++;

   int pointPlus2Sigma=0;
   while( pointPlus2Sigma<nPoints && expectedPlus2SigmaLimit[pointPlus2Sigma]<func->Eval(mass[pointPlus2Sigma]) ) pointPlus2Sigma++;

   int pointMinus2Sigma=0;
   while( pointMinus2Sigma<nPoints && expectedMinus2SigmaLimit[pointMinus2Sigma]<func->Eval(mass[pointMinus2Sigma]) ) pointMinus2Sigma++;

   cout<<endl<<" Observed limit on mass = "<<
   findCrossing(mass[pointObs-1], mass[pointObs], observedLimit[pointObs-1], observedLimit[pointObs], func);
   cout<<endl<<endl;

   cout<<endl<<" Expected limit on mass = "<<
   findCrossing(mass[pointExp-1], mass[pointExp], expectedLimit[pointExp-1], expectedLimit[pointExp], func);
   cout<<endl<<endl;

   double right=findCrossing(mass[pointMinus1Sigma-1], mass[pointMinus1Sigma], expectedMinus1SigmaLimit[pointMinus1Sigma-1], expectedMinus1SigmaLimit[pointMinus1Sigma], func);
   double left =findCrossing(mass[pointPlus1Sigma -1], mass[pointPlus1Sigma],  expectedPlus1SigmaLimit [pointPlus1Sigma -1], expectedPlus1SigmaLimit [pointPlus1Sigma],  func);
   cout<<endl<<" 1-sigma band: ["<<left<<"-"<<right<<"]"<<endl<<endl;

   right = findCrossing(mass[pointMinus2Sigma-1], mass[pointMinus2Sigma], expectedMinus2SigmaLimit[pointMinus2Sigma-1], expectedMinus2SigmaLimit[pointMinus2Sigma], func);
   left  = findCrossing(mass[pointPlus2Sigma -1], mass[pointPlus2Sigma],  expectedPlus2SigmaLimit [pointPlus2Sigma -1], expectedPlus2SigmaLimit [pointPlus2Sigma],  func);
   cout<<endl<<" 2-sigma band: ["<<left<<"-"<<right<<"]"<<endl<<endl;

return;

   char buff[128];
   sprintf(buff,"%s.pdf",outputFileName);
   cnv->Print(buff);
   sprintf(buff,"%s.root",outputFileName);
   TFile *f = new TFile(buff,"UPDATE");
   cnv->Write();
   f->Write();
   f->Close();
}

double findCrossing(double massA, double massB, double limitA, double limitB, TF1 *func){
   double xsecA = func->Eval(massA);
   double xsecB = func->Eval(massB);
   double crossingRough =  massA + (massB-massA) * (limitA - xsecA) / (xsecB - xsecA - (limitB - limitA));

//   cout<<"Linear approximation for the crossing: "<<crossingRough<<endl;

   int    nIter = 0;
   double delta = 100;
   double crossingFine = crossingRough;
   while( fabs(delta)>0.001 && nIter<10000 ){
      delta = func->Eval( crossingFine ) - (limitB-limitA) * (crossingFine-massA)/(massB-massA) - limitA;
      if( delta<0 ) crossingFine -= 0.01;
      if( delta>0 ) crossingFine += 0.01;
      nIter++;
   }

//   cout<<"crossingFine= "<<crossingFine<<" sigma_level= "<<func->Eval( crossingFine )<<" (after "<<nIter<<" iterations)"<<endl;

   return crossingFine;
}

