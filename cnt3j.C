#include <iostream>
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooArgSet.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooRandom.h"
#include "RooMsgService.h"
#include "RooStats/ModelConfig.h"

#include "TFile.h"

using namespace RooFit;
using namespace RooStats;
using namespace std;

#include "inputs3j.h"

void doPulls(RooAbsPdf *model, RooAbsPdf *prior, double signalCrossSection);

enum {s3m0=57, s3m50=60, s3m100=62, s3m150=63, s3m200=64, s3m300=65, s3m500=66,
      s4m0=37, s4m50=40, s4m100=42, s4m150=43, s4m200=44, s4m300=45, s4m500=46,
      S3m0=47, S3m50=50, S3m100=52, S3m150=53, S3m200=54, S3m300=55, S3m400=67, S3m500=56, S3m600=68,
      S4m0=27, S4m50=30, S4m100=32, S4m150=33, S4m200=34, S4m300=35, S4m400=69, S4m500=36, S4m600=70, S4m700=71, S4m800=72, S4m900=73, S4m1000=74}; 

void cnt3j(int model=S3m100, int MET_CUT=0){ // 0 - 250 GeV, 1 - 300 GeV, 2 - 350 GeV, 3 - 400 GeV, 4 - 450 GeV

  if( MET_CUT > 3){ cout<<"MET index is out of range: "<<MET_CUT<<endl; return; }

  double *sigEff0b, *sigEff1b, *sigJec0b, *sigJec1b, *sigPdf0b, *sigPdf1b;

  switch( model ){
    case S3m0:   sigEff0b =   S3m0Eff0b; sigEff1b =   S3m0Eff1b; sigJec0b =   S3m0Jec0b; sigJec1b =   S3m0Jec1b; sigPdf0b =   S3m0Pdf0b; sigPdf1b =   S3m0Pdf1b; break;
    case S3m50:  sigEff0b =  S3m50Eff0b; sigEff1b =  S3m50Eff1b; sigJec0b =  S3m50Jec0b; sigJec1b =  S3m50Jec1b; sigPdf0b =  S3m50Pdf0b; sigPdf1b =  S3m50Pdf1b; break;
    case S3m100: sigEff0b = S3m100Eff0b; sigEff1b = S3m100Eff1b; sigJec0b = S3m100Jec0b; sigJec1b = S3m100Jec1b; sigPdf0b = S3m100Pdf0b; sigPdf1b = S3m100Pdf1b; break;
    case S3m150: sigEff0b = S3m150Eff0b; sigEff1b = S3m150Eff1b; sigJec0b = S3m150Jec0b; sigJec1b = S3m150Jec1b; sigPdf0b = S3m150Pdf0b; sigPdf1b = S3m150Pdf1b; break;
    case S3m200: sigEff0b = S3m200Eff0b; sigEff1b = S3m200Eff1b; sigJec0b = S3m200Jec0b; sigJec1b = S3m200Jec1b; sigPdf0b = S3m200Pdf0b; sigPdf1b = S3m200Pdf1b; break;
    case S3m300: sigEff0b = S3m300Eff0b; sigEff1b = S3m300Eff1b; sigJec0b = S3m300Jec0b; sigJec1b = S3m300Jec1b; sigPdf0b = S3m300Pdf0b; sigPdf1b = S3m300Pdf1b; break;
    case S3m400: sigEff0b = S3m400Eff0b; sigEff1b = S3m400Eff1b; sigJec0b = S3m400Jec0b; sigJec1b = S3m400Jec1b; sigPdf0b = S3m400Pdf0b; sigPdf1b = S3m400Pdf1b; break;
    case S3m500: sigEff0b = S3m500Eff0b; sigEff1b = S3m500Eff1b; sigJec0b = S3m500Jec0b; sigJec1b = S3m500Jec1b; sigPdf0b = S3m500Pdf0b; sigPdf1b = S3m500Pdf1b; break;
    case S3m600: sigEff0b = S3m600Eff0b; sigEff1b = S3m600Eff1b; sigJec0b = S3m600Jec0b; sigJec1b = S3m600Jec1b; sigPdf0b = S3m600Pdf0b; sigPdf1b = S3m600Pdf1b; break;
    case S4m0:   sigEff0b =   S4m0Eff0b; sigEff1b =   S4m0Eff1b; sigJec0b =   S4m0Jec0b; sigJec1b =   S4m0Jec1b; sigPdf0b =   S4m0Pdf0b; sigPdf1b =   S4m0Pdf1b; break;
    case S4m50:  sigEff0b =  S4m50Eff0b; sigEff1b =  S4m50Eff1b; sigJec0b =  S4m50Jec0b; sigJec1b =  S4m50Jec1b; sigPdf0b =  S4m50Pdf0b; sigPdf1b =  S4m50Pdf1b; break;
    case S4m100: sigEff0b = S4m100Eff0b; sigEff1b = S4m100Eff1b; sigJec0b = S4m100Jec0b; sigJec1b = S4m100Jec1b; sigPdf0b = S4m100Pdf0b; sigPdf1b = S4m100Pdf1b; break;
    case S4m150: sigEff0b = S4m150Eff0b; sigEff1b = S4m150Eff1b; sigJec0b = S4m150Jec0b; sigJec1b = S4m150Jec1b; sigPdf0b = S4m150Pdf0b; sigPdf1b = S4m150Pdf1b; break;
    case S4m200: sigEff0b = S4m200Eff0b; sigEff1b = S4m200Eff1b; sigJec0b = S4m200Jec0b; sigJec1b = S4m200Jec1b; sigPdf0b = S4m200Pdf0b; sigPdf1b = S4m200Pdf1b; break;
    case S4m300: sigEff0b = S4m300Eff0b; sigEff1b = S4m300Eff1b; sigJec0b = S4m300Jec0b; sigJec1b = S4m300Jec1b; sigPdf0b = S4m300Pdf0b; sigPdf1b = S4m300Pdf1b; break;
    case S4m400: sigEff0b = S4m400Eff0b; sigEff1b = S4m400Eff1b; sigJec0b = S4m400Jec0b; sigJec1b = S4m400Jec1b; sigPdf0b = S4m400Pdf0b; sigPdf1b = S4m400Pdf1b; break;
    case S4m500: sigEff0b = S4m500Eff0b; sigEff1b = S4m500Eff1b; sigJec0b = S4m500Jec0b; sigJec1b = S4m500Jec1b; sigPdf0b = S4m500Pdf0b; sigPdf1b = S4m500Pdf1b; break;
    case S4m600: sigEff0b = S4m600Eff0b; sigEff1b = S4m600Eff1b; sigJec0b = S4m600Jec0b; sigJec1b = S4m600Jec1b; sigPdf0b = S4m600Pdf0b; sigPdf1b = S4m600Pdf1b; break;
    case S4m700: sigEff0b = S4m700Eff0b; sigEff1b = S4m700Eff1b; sigJec0b = S4m700Jec0b; sigJec1b = S4m700Jec1b; sigPdf0b = S4m700Pdf0b; sigPdf1b = S4m700Pdf1b; break;
    case S4m800: sigEff0b = S4m800Eff0b; sigEff1b = S4m800Eff1b; sigJec0b = S4m800Jec0b; sigJec1b = S4m800Jec1b; sigPdf0b = S4m800Pdf0b; sigPdf1b = S4m800Pdf1b; break;
    case S4m900: sigEff0b = S4m900Eff0b; sigEff1b = S4m900Eff1b; sigJec0b = S4m900Jec0b; sigJec1b = S4m900Jec1b; sigPdf0b = S4m900Pdf0b; sigPdf1b = S4m900Pdf1b; break;
    case S4m1000:sigEff0b = S4m1000Eff0b;sigEff1b = S4m1000Eff1b;sigJec0b = S4m1000Jec0b;sigJec1b = S4m1000Jec1b;sigPdf0b = S4m1000Pdf0b;sigPdf1b = S4m1000Pdf1b; break;
    default : cout<<"Unsupported model "<<model<<endl; return;
  }

  map<int, const char*> names;

  names[S3m0]   = "S3m0";
  names[S3m50]  = "S3m50";
  names[S3m100] = "S3m100";
  names[S3m150] = "S3m150";
  names[S3m200] = "S3m200";
  names[S3m300] = "S3m300";
  names[S3m400] = "S3m400";
  names[S3m500] = "S3m500";
  names[S3m600] = "S3m600";
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

///////////////////////////////////////////////////

  RooWorkspace *wspace = new RooWorkspace("myWS"); 

///////// lumi block //////////
  // integrated luminosity with log-normal systematics
  wspace->factory( "lumi_nom[18840.]" );
  wspace->factory( "lumi_kappa[1.044]" );
  wspace->factory( "cexpr::alpha_lumi('pow(lumi_kappa,beta_lumi)',lumi_kappa,beta_lumi[0,-5,5])" );
  wspace->factory( "prod::luminosity(lumi_nom,alpha_lumi)" );
  wspace->factory( "Gaussian::pLumi(beta_lumi,glob_lumi[0,-5,5],1)" );

  RooRealVar* lumi_nom = wspace->var("lumi_nom");
  lumi_nom->setVal( luminosity );
  RooRealVar* lumi_kappa = wspace->var("lumi_kappa");
  lumi_kappa->setVal( 1. + lumiError );
////// end of lumi block //////


  // List of main nuissance parameters: JEC, PDF, ren/reg Q2 scales, matching (some are 100% correlated or common between bgs)
  wspace->factory( "Gaussian::pJEC(     beta_JEC[     0,-5,5],glob_JEC[     0,-5,5],1)" );  // common for all
  wspace->factory( "Gaussian::pJER(     beta_JER[     0,-5,5],glob_JER[     0,-5,5],1)" );  // common for all
  wspace->factory( "Gaussian::pTRG(     beta_TRG[     0,-5,5],glob_TRG[     0,-5,5],1)" );  // common for all
  wspace->factory( "Gaussian::pTAG(     beta_TAG[     0,-5,5],glob_TAG[     0,-5,5],1)" );  // common for all
  wspace->factory( "Gaussian::pPDFtt(   beta_PDFtt[   0,-5,5],glob_PDFtt[   0,-5,5],1)" );
  wspace->factory( "Gaussian::pQ2tt(    beta_Q2tt[    0,-5,5],glob_Q2tt[    0,-5,5],1)" );
  wspace->factory( "Gaussian::pMATCHtt( beta_MATCHtt[ 0,-5,5],glob_MATCHtt[ 0,-5,5],1)" );
  wspace->factory( "Gaussian::pREWtt  ( beta_REWtt[   0,-5,5],glob_REWtt[   0,-5,5],1)" );
  wspace->factory( "Gaussian::pPDFt(    beta_PDFt[    0,-5,5],glob_PDFt[    0,-5,5],1)" );
  wspace->factory( "Gaussian::pPDFewk(  beta_PDFewk[  0,-5,5],glob_PDFewk[  0,-5,5],1)" );  // common for WJ, ZJ, VV
  wspace->factory( "Gaussian::pPDFsig(  beta_PDFsig[  0,-5,5],glob_PDFsig[  0,-5,5],1)" );
  wspace->factory( "Gaussian::pWJ(      beta_WJ[      0,-5,5],glob_WJ[      0,-5,5],1)" );
  wspace->factory( "Gaussian::pZN(      beta_ZN[      0,-5,5],glob_ZN[      0,-5,5],1)" );

//////// signal block /////////
  // POI: signal cross sections (pb)
  wspace->factory("signalXsec[0,0,100]"); // -35
  // define Bayesian prior PDF for POI
  wspace->factory( "Uniform::prior(signalXsec)" );

  // Efficiencies for signal at cut of MET>250,300,350,400,450:
  wspace->factory( "efficiency0b_nominal[0.00882]" );
  wspace->factory( "efficiency1b_nominal[0.01364]" );
  wspace->factory( "efficiency0b_kappaJEC[1.076]" );
  wspace->factory( "efficiency1b_kappaJEC[1.128]" );
  wspace->factory( "efficiency0b_kappaPDF[1.040]" );
  wspace->factory( "efficiency1b_kappaPDF[1.040]" );
  wspace->factory( "efficiency_kappaTRG[1.014]" );
//  wspace->factory( "efficiency0b_kappaQ2[1.000]" );
//  wspace->factory( "efficiency1b_kappaQ2[1.000]" );
  wspace->factory( "cexpr::alphaJEC_efficiency0b('pow(efficiency0b_kappaJEC,beta_JEC)',efficiency0b_kappaJEC,beta_JEC)" );
  wspace->factory( "cexpr::alphaJEC_efficiency1b('pow(efficiency1b_kappaJEC,beta_JEC)',efficiency1b_kappaJEC,beta_JEC)" );
  wspace->factory( "cexpr::alphaPDF_efficiency0b('pow(efficiency0b_kappaPDF,beta_PDFsig)',efficiency0b_kappaPDF,beta_PDFsig)" );
  wspace->factory( "cexpr::alphaPDF_efficiency1b('pow(efficiency1b_kappaPDF,beta_PDFsig)',efficiency1b_kappaPDF,beta_PDFsig)" );
  wspace->factory( "cexpr::alphaTRG_efficiency('pow(efficiency_kappaTRG,beta_TRG)',efficiency_kappaTRG,beta_TRG)" );
//  wspace->factory( "cexpr::alphaQ2_efficiency0b('pow(efficiency0b_kappaQ2,beta_Q2)',efficiency0b_kappaQ2,beta_Q2)" );
//  wspace->factory( "cexpr::alphaQ2_efficiency1b('pow(efficiency1b_kappaQ2,beta_Q2)',efficiency1b_kappaQ2,beta_Q2)" );
  wspace->factory( "prod::signalEff0b(efficiency0b_nominal,alphaJEC_efficiency0b,alphaPDF_efficiency0b,alphaTRG_efficiency)" ); //,alphaQ2_efficiency0b)" );
  wspace->factory( "prod::signalEff1b(efficiency1b_nominal,alphaJEC_efficiency1b,alphaPDF_efficiency1b,alphaTRG_efficiency)" ); //,alphaQ2_efficiency1b)" );

  RooRealVar* efficiency0b_nominal = wspace->var("efficiency0b_nominal");
  RooRealVar* efficiency1b_nominal = wspace->var("efficiency1b_nominal");
  efficiency0b_nominal->setVal( sigEff0b[MET_CUT] );
  efficiency1b_nominal->setVal( sigEff1b[MET_CUT] );
  RooRealVar* efficiency0b_kappaJEC = wspace->var("efficiency0b_kappaJEC");
  RooRealVar* efficiency1b_kappaJEC = wspace->var("efficiency1b_kappaJEC");
  efficiency0b_kappaJEC->setVal( 1. + sigJec0b[MET_CUT] );
  efficiency1b_kappaJEC->setVal( 1. + sigJec1b[MET_CUT] );
  RooRealVar* efficiency0b_kappaPDF = wspace->var("efficiency0b_kappaPDF");
  RooRealVar* efficiency1b_kappaPDF = wspace->var("efficiency1b_kappaPDF");
  efficiency0b_kappaPDF->setVal( 1.+sigPdf0b[MET_CUT] );
  efficiency1b_kappaPDF->setVal( 1.+sigPdf1b[MET_CUT] );

  // signal yield
  wspace->factory("prod::signalYield0b(luminosity, signalXsec, signalEff0b)");
  wspace->factory("prod::signalYield1b(luminosity, signalXsec, signalEff1b)");
///// end of signal block /////


//// TTbar background block ///
  // cross sections for the background (pb)
  wspace->factory("ttXsec[248.0]");

  // product of efficiencies and acceptances for the background + their log-normal constraints
  wspace->factory( "ttEff0b_nominal[.0003227]" );
  wspace->factory( "ttEff1b_nominal[.0006758]" );
  wspace->factory( "ttEff0b_kappaJEC[1.067]" );
  wspace->factory( "ttEff1b_kappaJEC[1.078]" );
  wspace->factory( "ttEff0b_kappaJER[1.0]" );
  wspace->factory( "ttEff1b_kappaJER[1.0]" );
  wspace->factory( "ttEff0b_kappaTAG[1.0]" );
  wspace->factory( "ttEff1b_kappaTAG[1.0]" );
  wspace->factory( "ttEff0b_kappaPDF[1.113]" );
  wspace->factory( "ttEff1b_kappaPDF[1.116]" );
  wspace->factory( "ttEff0b_kappaQ2[1.027]" );
  wspace->factory( "ttEff1b_kappaQ2[1.015]" );
  wspace->factory( "ttEff0b_kappaMATCH[1.060]" );
  wspace->factory( "ttEff1b_kappaMATCH[1.072]" );
  wspace->factory( "ttEff_kappaREW[1.072]" );
  wspace->factory( "ttEff_kappaTRG[1.014]" );
  wspace->factory( "cexpr::alphaJEC_ttEff0b('pow(ttEff0b_kappaJEC,beta_JEC)',ttEff0b_kappaJEC,beta_JEC)" );
  wspace->factory( "cexpr::alphaJEC_ttEff1b('pow(ttEff1b_kappaJEC,beta_JEC)',ttEff1b_kappaJEC,beta_JEC)" );
  wspace->factory( "cexpr::alphaJER_ttEff0b('pow(ttEff0b_kappaJER,beta_JER)',ttEff0b_kappaJER,beta_JER)" );
  wspace->factory( "cexpr::alphaJER_ttEff1b('pow(ttEff1b_kappaJER,beta_JER)',ttEff1b_kappaJER,beta_JER)" );
  wspace->factory( "cexpr::alphaTAG_ttEff0b('pow(ttEff0b_kappaTAG,beta_TAG)',ttEff0b_kappaTAG,beta_TAG)" );
  wspace->factory( "cexpr::alphaTAG_ttEff1b('pow(ttEff1b_kappaTAG,beta_TAG)',ttEff1b_kappaTAG,beta_TAG)" );
  wspace->factory( "cexpr::alphaPDF_ttEff0b('pow(ttEff0b_kappaPDF,beta_PDFtt)',ttEff0b_kappaPDF,beta_PDFtt)" );
  wspace->factory( "cexpr::alphaPDF_ttEff1b('pow(ttEff1b_kappaPDF,beta_PDFtt)',ttEff1b_kappaPDF,beta_PDFtt)" );
  wspace->factory( "cexpr::alphaQ2_ttEff0b('pow(ttEff0b_kappaQ2,beta_Q2tt)',ttEff0b_kappaQ2,beta_Q2tt)" );
  wspace->factory( "cexpr::alphaQ2_ttEff1b('pow(ttEff1b_kappaQ2,beta_Q2tt)',ttEff1b_kappaQ2,beta_Q2tt)" );
  wspace->factory( "cexpr::alphaMATCH_ttEff0b('pow(ttEff0b_kappaMATCH,beta_MATCHtt)',ttEff0b_kappaMATCH,beta_MATCHtt)" );
  wspace->factory( "cexpr::alphaMATCH_ttEff1b('pow(ttEff1b_kappaMATCH,beta_MATCHtt)',ttEff1b_kappaMATCH,beta_MATCHtt)" );
  wspace->factory( "cexpr::alphaREW_ttEff('pow(ttEff_kappaREW,beta_REWtt)',ttEff_kappaREW,beta_REWtt)" );
  wspace->factory( "cexpr::alphaTRG_ttEff('pow(ttEff_kappaTRG,beta_TRG)',ttEff_kappaTRG,beta_TRG)" );
  wspace->factory( "prod::ttEff0b(ttEff0b_nominal,alphaJEC_ttEff0b,alphaJER_ttEff0b,alphaTAG_ttEff0b,alphaPDF_ttEff0b,alphaQ2_ttEff0b,alphaMATCH_ttEff0b,alphaREW_ttEff,alphaTRG_ttEff)" );
  wspace->factory( "prod::ttEff1b(ttEff1b_nominal,alphaJEC_ttEff1b,alphaJER_ttEff1b,alphaTAG_ttEff1b,alphaPDF_ttEff1b,alphaQ2_ttEff1b,alphaMATCH_ttEff1b,alphaREW_ttEff,alphaTRG_ttEff)" );

  RooRealVar* ttEff0b_nominal = wspace->var("ttEff0b_nominal");
  RooRealVar* ttEff1b_nominal = wspace->var("ttEff1b_nominal");
  ttEff0b_nominal->setVal( ttEff0b[MET_CUT] );
  ttEff1b_nominal->setVal( ttEff1b[MET_CUT] );
  RooRealVar* ttEff0b_kappaJEC = wspace->var("ttEff0b_kappaJEC");
  RooRealVar* ttEff1b_kappaJEC = wspace->var("ttEff1b_kappaJEC");
  ttEff0b_kappaJEC->setVal( 1.+ttJec0b[MET_CUT] );
  ttEff1b_kappaJEC->setVal( 1.+ttJec1b[MET_CUT] );
  RooRealVar* ttEff0b_kappaJER = wspace->var("ttEff0b_kappaJER");
  RooRealVar* ttEff1b_kappaJER = wspace->var("ttEff1b_kappaJER");
  ttEff0b_kappaJER->setVal( 1.+ttJer0b[MET_CUT] );
  ttEff1b_kappaJER->setVal( 1.+ttJer1b[MET_CUT] );
  RooRealVar* ttEff0b_kappaTAG = wspace->var("ttEff0b_kappaTAG");
  RooRealVar* ttEff1b_kappaTAG = wspace->var("ttEff1b_kappaTAG");
  ttEff0b_kappaTAG->setVal( 1.+ttTag0b[MET_CUT] );
  ttEff1b_kappaTAG->setVal( 1.+ttTag1b[MET_CUT] );
  RooRealVar* ttEff0b_kappaPDF = wspace->var("ttEff0b_kappaPDF");
  RooRealVar* ttEff1b_kappaPDF = wspace->var("ttEff1b_kappaPDF");
  ttEff0b_kappaPDF->setVal( 1.+ttPdf0b[MET_CUT] );
  ttEff1b_kappaPDF->setVal( 1.+ttPdf1b[MET_CUT] );
  RooRealVar* ttEff0b_kappaQ2= wspace->var("ttEff0b_kappaQ2");
  RooRealVar* ttEff1b_kappaQ2= wspace->var("ttEff1b_kappaQ2");
  ttEff0b_kappaQ2->setVal( 1.+ttScale0b[MET_CUT] );
  ttEff1b_kappaQ2->setVal( 1.+ttScale1b[MET_CUT] );
  RooRealVar* ttEff0b_kappaMATCH= wspace->var("ttEff0b_kappaMATCH");
  RooRealVar* ttEff1b_kappaMATCH= wspace->var("ttEff1b_kappaMATCH");
  ttEff0b_kappaMATCH->setVal( 1.+ttMatch0b[MET_CUT] );
  ttEff1b_kappaMATCH->setVal( 1.+ttMatch1b[MET_CUT] );
  RooRealVar* ttEff_kappaREW = wspace->var("ttEff_kappaREW");
  ttEff_kappaREW->setVal( 1.+ttRew[MET_CUT] );

  wspace->factory("prod::ttYield0b(luminosity, ttXsec, ttEff0b)");
  wspace->factory("prod::ttYield1b(luminosity, ttXsec, ttEff1b)");
// end of the TTbar bg block //


// Data-driven yield for the invisible Z background + log-normal constraints
  wspace->factory( "znYield0b_nominal[590.]" );
  wspace->factory( "znYield1b_nominal[111.]" );
  wspace->factory( "znYield0b_kappa[1.139]" );
  wspace->factory( "znYield1b_kappa[1.316]" );
  wspace->factory( "cexpr::alpha_znYield0b('pow(znYield0b_kappa,beta_ZN)',znYield0b_kappa,beta_ZN)" );
  wspace->factory( "cexpr::alpha_znYield1b('pow(znYield1b_kappa,beta_ZN)',znYield1b_kappa,beta_ZN)" );
  wspace->factory( "prod::znYield0b(znYield0b_nominal,alpha_znYield0b)" );
  wspace->factory( "prod::znYield1b(znYield1b_nominal,alpha_znYield1b)" );

  RooRealVar* znYield0b_nominal = wspace->var("znYield0b_nominal");
  RooRealVar* znYield1b_nominal = wspace->var("znYield1b_nominal");
  znYield0b_nominal->setVal( znYield0b[MET_CUT] );
  znYield1b_nominal->setVal( znYield1b[MET_CUT] );
  RooRealVar* znYield0b_kappa = wspace->var("znYield0b_kappa");
  RooRealVar* znYield1b_kappa = wspace->var("znYield1b_kappa");
  znYield0b_kappa->setVal( 1. + znUncert0b[MET_CUT] );
  znYield1b_kappa->setVal( 1. + znUncert1b[MET_CUT] );
// end of the invisible Z bg. block //


// Data-driven yield for the WJets background + log-normal constraints
  wspace->factory( "wjYield0b_nominal[590.]" );
  wspace->factory( "wjYield1b_nominal[111.]" );
  wspace->factory( "wjYield0b_kappa[1.139]" );
  wspace->factory( "wjYield1b_kappa[1.316]" );
  wspace->factory( "cexpr::alpha_wjYield0b('pow(wjYield0b_kappa,beta_WJ)',wjYield0b_kappa,beta_WJ)" );
  wspace->factory( "cexpr::alpha_wjYield1b('pow(wjYield1b_kappa,beta_WJ)',wjYield1b_kappa,beta_WJ)" );
  wspace->factory( "prod::wjYield0b(wjYield0b_nominal,alpha_wjYield0b)" );
  wspace->factory( "prod::wjYield1b(wjYield1b_nominal,alpha_wjYield1b)" );

  RooRealVar* wjYield0b_nominal = wspace->var("wjYield0b_nominal");
  RooRealVar* wjYield1b_nominal = wspace->var("wjYield1b_nominal");
  wjYield0b_nominal->setVal( wjYield0b[MET_CUT] );
  wjYield1b_nominal->setVal( wjYield1b[MET_CUT] );
  RooRealVar* wjYield0b_kappa = wspace->var("wjYield0b_kappa");
  RooRealVar* wjYield1b_kappa = wspace->var("wjYield1b_kappa");
  wjYield0b_kappa->setVal( 1. + wjUncert0b[MET_CUT] );
  wjYield1b_kappa->setVal( 1. + wjUncert1b[MET_CUT] );
// end of the WJets bg. block //


///// Single top bg block /////
  // don't split up single top production mechanisms, work with yields instead
  wspace->factory( "tYield0b_nominal[179.]" );
  wspace->factory( "tYield1b_nominal[319.]" );
  wspace->factory( "tYield0b_kappaJEC[1.064]" );
  wspace->factory( "tYield1b_kappaJEC[1.076]" );
  wspace->factory( "tYield0b_kappaJER[1.]" );
  wspace->factory( "tYield1b_kappaJER[1.]" );
  wspace->factory( "tYield0b_kappaTAG[1.]" );
  wspace->factory( "tYield1b_kappaTAG[1.]" );
  wspace->factory( "tYield0b_kappaPDF[1.19]" );
  wspace->factory( "tYield1b_kappaPDF[1.17]" );
  wspace->factory( "tYield_kappaTRG[1.014]" );
  wspace->factory( "cexpr::alphaJEC_tYield0b('pow(tYield0b_kappaJEC,beta_JEC)',tYield0b_kappaJEC,beta_JEC)" );
  wspace->factory( "cexpr::alphaJEC_tYield1b('pow(tYield1b_kappaJEC,beta_JEC)',tYield1b_kappaJEC,beta_JEC)" );
  wspace->factory( "cexpr::alphaJER_tYield0b('pow(tYield0b_kappaJER,beta_JER)',tYield0b_kappaJER,beta_JER)" );
  wspace->factory( "cexpr::alphaJER_tYield1b('pow(tYield1b_kappaJER,beta_JER)',tYield1b_kappaJER,beta_JER)" );
  wspace->factory( "cexpr::alphaTAG_tYield0b('pow(tYield0b_kappaTAG,beta_TAG)',tYield0b_kappaTAG,beta_TAG)" );
  wspace->factory( "cexpr::alphaTAG_tYield1b('pow(tYield1b_kappaTAG,beta_TAG)',tYield1b_kappaTAG,beta_TAG)" );
  wspace->factory( "cexpr::alphaPDF_tYield0b('pow(tYield0b_kappaPDF,beta_PDFt)',tYield0b_kappaPDF,beta_PDFt)" );
  wspace->factory( "cexpr::alphaPDF_tYield1b('pow(tYield1b_kappaPDF,beta_PDFt)',tYield1b_kappaPDF,beta_PDFt)" );
  wspace->factory( "cexpr::alphaTRG_tYield('pow(tYield_kappaTRG,beta_TRG)',tYield_kappaTRG,beta_TRG)" );
  wspace->factory( "prod::tYield0b(tYield0b_nominal,alphaJEC_tYield0b,alphaJER_tYield0b,alphaTAG_tYield0b,alphaPDF_tYield0b,alpha_lumi,alphaTRG_tYield)" );
  wspace->factory( "prod::tYield1b(tYield1b_nominal,alphaJEC_tYield1b,alphaJER_tYield1b,alphaTAG_tYield1b,alphaPDF_tYield1b,alpha_lumi,alphaTRG_tYield)" );

  RooRealVar* tYield0b_nominal = wspace->var("tYield0b_nominal");
  RooRealVar* tYield1b_nominal = wspace->var("tYield1b_nominal");
  tYield0b_nominal->setVal( tYield0b[MET_CUT] );
  tYield1b_nominal->setVal( tYield1b[MET_CUT] );
  RooRealVar* tYield0b_kappaJEC = wspace->var("tYield0b_kappaJEC");
  RooRealVar* tYield1b_kappaJEC = wspace->var("tYield1b_kappaJEC");
  tYield0b_kappaJEC->setVal( 1. + tJec0b[MET_CUT] );
  tYield1b_kappaJEC->setVal( 1. + tJec1b[MET_CUT] );
  RooRealVar* tYield0b_kappaJER = wspace->var("tYield0b_kappaJER");
  RooRealVar* tYield1b_kappaJER = wspace->var("tYield1b_kappaJER");
  tYield0b_kappaJER->setVal( 1. + tJer0b[MET_CUT] );
  tYield1b_kappaJER->setVal( 1. + tJer1b[MET_CUT] );
  RooRealVar* tYield0b_kappaTAG = wspace->var("tYield0b_kappaTAG");
  RooRealVar* tYield1b_kappaTAG = wspace->var("tYield1b_kappaTAG");
  tYield0b_kappaTAG->setVal( 1. + tTag0b[MET_CUT] );
  tYield1b_kappaTAG->setVal( 1. + tTag1b[MET_CUT] );
  RooRealVar* tYield0b_kappaPDF = wspace->var("tYield0b_kappaPDF");
  RooRealVar* tYield1b_kappaPDF = wspace->var("tYield1b_kappaPDF");
  tYield0b_kappaPDF->setVal( 1. + tPdf0b[MET_CUT] );
  tYield1b_kappaPDF->setVal( 1. + tPdf1b[MET_CUT] );
// end of the Single t block //

///// VV background block /////
  // don't split up single top production mechanisms, work with yields instead
  wspace->factory( "vvYield0b_nominal[340.]" );
  wspace->factory( "vvYield1b_nominal[66.]" );
  wspace->factory( "vvYield0b_kappaJEC[1.092]" );
  wspace->factory( "vvYield1b_kappaJEC[1.082]" );
  wspace->factory( "vvYield0b_kappaJER[1.]" );
  wspace->factory( "vvYield1b_kappaJER[1.]" );
  wspace->factory( "vvYield0b_kappaTAG[1.]" );
  wspace->factory( "vvYield1b_kappaTAG[1.]" );
  wspace->factory( "vvYield0b_kappaPDF[1.05]" );
  wspace->factory( "vvYield1b_kappaPDF[1.05]" );
  wspace->factory( "vvYield_kappaTRG[1.014]" );
  wspace->factory( "cexpr::alphaJEC_vvYield0b('pow(vvYield0b_kappaJEC,beta_JEC)',vvYield0b_kappaJEC,beta_JEC)" );
  wspace->factory( "cexpr::alphaJEC_vvYield1b('pow(vvYield1b_kappaJEC,beta_JEC)',vvYield1b_kappaJEC,beta_JEC)" );
  wspace->factory( "cexpr::alphaJER_vvYield0b('pow(vvYield0b_kappaJER,beta_JER)',vvYield0b_kappaJER,beta_JER)" );
  wspace->factory( "cexpr::alphaJER_vvYield1b('pow(vvYield1b_kappaJER,beta_JER)',vvYield1b_kappaJER,beta_JER)" );
  wspace->factory( "cexpr::alphaTAG_vvYield0b('pow(vvYield0b_kappaTAG,beta_TAG)',vvYield0b_kappaTAG,beta_TAG)" );
  wspace->factory( "cexpr::alphaTAG_vvYield1b('pow(vvYield1b_kappaTAG,beta_TAG)',vvYield1b_kappaTAG,beta_TAG)" );
  wspace->factory( "cexpr::alphaPDF_vvYield0b('pow(vvYield0b_kappaPDF,beta_PDFewk)',vvYield0b_kappaPDF,beta_PDFewk)" );
  wspace->factory( "cexpr::alphaPDF_vvYield1b('pow(vvYield1b_kappaPDF,beta_PDFewk)',vvYield1b_kappaPDF,beta_PDFewk)" );
  wspace->factory( "cexpr::alphaTRG_vvYield('pow(vvYield_kappaTRG,beta_TRG)',vvYield_kappaTRG,beta_TRG)" );
  wspace->factory( "prod::vvYield0b(vvYield0b_nominal,alphaJEC_vvYield0b,alphaJER_vvYield0b,alphaTAG_vvYield0b,alphaPDF_vvYield0b,alpha_lumi,alphaTRG_vvYield)" );
  wspace->factory( "prod::vvYield1b(vvYield1b_nominal,alphaJEC_vvYield1b,alphaJER_vvYield1b,alphaTAG_vvYield1b,alphaPDF_vvYield1b,alpha_lumi,alphaTRG_vvYield)" );

  RooRealVar* vvYield0b_nominal = wspace->var("vvYield0b_nominal");
  RooRealVar* vvYield1b_nominal = wspace->var("vvYield1b_nominal");
  vvYield0b_nominal->setVal( vvYield0b[MET_CUT] );
  vvYield1b_nominal->setVal( vvYield1b[MET_CUT] );
  RooRealVar* vvYield0b_kappaJEC = wspace->var("vvYield0b_kappaJEC");
  RooRealVar* vvYield1b_kappaJEC = wspace->var("vvYield1b_kappaJEC");
  vvYield0b_kappaJEC->setVal( 1. + vvJec0b[MET_CUT] );
  vvYield1b_kappaJEC->setVal( 1. + vvJec1b[MET_CUT] );
  RooRealVar* vvYield0b_kappaJER = wspace->var("vvYield0b_kappaJER");
  RooRealVar* vvYield1b_kappaJER = wspace->var("vvYield1b_kappaJER");
  vvYield0b_kappaJER->setVal( 1. + vvJer0b[MET_CUT] );
  vvYield1b_kappaJER->setVal( 1. + vvJer1b[MET_CUT] );
  RooRealVar* vvYield0b_kappaTAG = wspace->var("vvYield0b_kappaTAG");
  RooRealVar* vvYield1b_kappaTAG = wspace->var("vvYield1b_kappaTAG");
  vvYield0b_kappaTAG->setVal( 1. + vvTag0b[MET_CUT] );
  vvYield1b_kappaTAG->setVal( 1. + vvTag1b[MET_CUT] );
  RooRealVar* vvYield0b_kappaPDF = wspace->var("vvYield0b_kappaPDF");
  RooRealVar* vvYield1b_kappaPDF = wspace->var("vvYield1b_kappaPDF");
  vvYield0b_kappaPDF->setVal( 1. + vvPdf0b[MET_CUT] );
  vvYield1b_kappaPDF->setVal( 1. + vvPdf1b[MET_CUT] );
// end of the Single t block //


//// QCD background block /////
  wspace->factory( "qcdYield[0,0,1000]" ); // -1000
  wspace->factory( "Uniform::priorQCD(qcdYield)" );
  wspace->factory( "probQCD1b_nominal[0.15]" );
  wspace->factory( "probQCD1b_kappa[1.05]" );
  wspace->factory( "cexpr::alpha_probQCD1b('pow(probQCD1b_kappa,beta_probQCD1b)',probQCD1b_kappa,beta_probQCD1b[0,-5,5])" );
  wspace->factory( "prod::probQCD1b(probQCD1b_nominal,alpha_probQCD1b)" );
  wspace->factory( "Gaussian::pQCD1b(beta_probQCD1b,glob_probQCD1b[0,-5,5],1)" );
  wspace->factory( "cexpr::probQCD0b('1.-0.02-probQCD1b',probQCD1b)" );
  wspace->factory( "prod::qcdYield0b(probQCD0b,qcdYield)" );
  wspace->factory( "prod::qcdYield1b(probQCD1b,qcdYield)" );

  RooRealVar* probQCD1b_nominal = wspace->var("probQCD1b_nominal");
  RooRealVar* probQCD1b_kappa   = wspace->var("probQCD1b_kappa");
  probQCD1b_nominal->setVal( probQCD1b  [MET_CUT] );
  probQCD1b_kappa  ->setVal( 1 + uncertQCD1b[MET_CUT] );

/// end of the QCD bg block ///


// sum of all of the background yields
  wspace->factory("sum::bgYield0b(ttYield0b,znYield0b,wjYield0b,tYield0b,vvYield0b,qcdYield0b)");
  wspace->factory("sum::bgYield1b(ttYield1b,znYield1b,wjYield1b,tYield1b,vvYield1b,qcdYield1b)");

  // total observed yield
  wspace->factory("observed0b[0,0,50000]"); // will be set later
  wspace->factory("observed1b[0,0,50000]"); // will be set later
  RooRealVar* observed0b = wspace->var("observed0b");   // get the observable
  RooRealVar* observed1b = wspace->var("observed1b");   // get the observable
  observed0b->setVal( obs0b[MET_CUT] );
  observed1b->setVal( obs1b[MET_CUT] );
  observed0b->setConstant();
  observed1b->setConstant();

  RooDataSet* data = new RooDataSet("observed_data", "0 and 1 b-tag counts", RooArgSet(*observed0b,*observed1b));
  data->add( RooArgSet(*observed0b,*observed1b) );
  data->Print("v");
  wspace->import(*data);

  wspace->factory("Poisson::countSB0b(observed0b, sum(signalYield0b,bgYield0b))");
  wspace->factory("Poisson::countSB1b(observed1b, sum(signalYield1b,bgYield1b))");
  //  background-only model
  wspace->factory("Poisson::countB0b(observed0b, bgYield0b)");
  wspace->factory("Poisson::countB1b(observed1b, bgYield1b)");
  // full models
  wspace->factory("PROD::fullSBmodel(countSB0b, countSB1b, pLumi, pJEC, pJER, pTAG, pPDFtt, pQ2tt, pMATCHtt, pREWtt, pPDFsig, pPDFewk, pPDFt, pZN, pWJ, priorQCD, pQCD1b, pTRG, prior)");
  wspace->factory("PROD::fullBmodel( countB0b,  countB1b,  pLumi, pJEC, pJER, pTAG, pPDFtt, pQ2tt, pMATCHtt, pREWtt, pPDFsig, pPDFewk, pPDFt, pZN, pWJ, priorQCD, pQCD1b, pTRG, prior)");
  wspace->factory("PROD::combinedPrior(                    pLumi, pJEC, pJER, pTAG, pPDFtt, pQ2tt, pMATCHtt, pREWtt, pPDFsig, pPDFewk, pPDFt, pZN, pWJ, priorQCD, pQCD1b, pTRG, prior)");

  wspace->Print();

  // arrange the parameters of the models to sets of global observables, nuisance parameters and the parameter of iterest
  RooArgList observables( *observed0b, *observed1b );
  RooRealVar* signalXsec = wspace->var("signalXsec"); // get the signal we care about
  RooArgSet POI( *signalXsec );
  // global observables (external knowledge)
  RooRealVar* glob_lumi   = wspace->var("glob_lumi");
  RooRealVar* glob_JEC    = wspace->var("glob_JEC");
  RooRealVar* glob_JER    = wspace->var("glob_JER");
  RooRealVar* glob_TAG    = wspace->var("glob_TAG");
  RooRealVar* glob_TRG    = wspace->var("glob_TRG");
  RooRealVar* glob_PDFtt  = wspace->var("glob_PDFtt");
  RooRealVar* glob_Q2tt   = wspace->var("glob_Q2tt");
  RooRealVar* glob_MATCHtt= wspace->var("glob_MATCHtt");
  RooRealVar* glob_REWtt  = wspace->var("glob_REWtt");
  RooRealVar* glob_PDFsig = wspace->var("glob_PDFsig");
  RooRealVar* glob_PDFewk = wspace->var("glob_PDFewk");
  RooRealVar* glob_PDFt   = wspace->var("glob_PDFt");
  RooRealVar* glob_ZN     = wspace->var("glob_ZN");
  RooRealVar* glob_WJ     = wspace->var("glob_WJ");
  RooRealVar* glob_probQCD1b = wspace->var("glob_probQCD1b");
  glob_lumi  ->setConstant(true);
  glob_JEC   ->setConstant(true);
  glob_JER   ->setConstant(true);
  glob_TAG   ->setConstant(true);
  glob_TRG   ->setConstant(true);
  glob_PDFtt ->setConstant(true);
  glob_Q2tt  ->setConstant(true);
  glob_MATCHtt ->setConstant(true);
  glob_REWtt ->setConstant(true);
  glob_PDFsig->setConstant(true);
  glob_PDFewk->setConstant(true);
  glob_PDFt  ->setConstant(true);
  glob_ZN    ->setConstant(true);
  glob_WJ    ->setConstant(true);
  glob_probQCD1b->setConstant(true);
  RooArgSet globalObs("global_obs");
  globalObs.add( *glob_lumi  );
  globalObs.add( *glob_JEC   );
  globalObs.add( *glob_JER   );
  globalObs.add( *glob_TAG   );
  globalObs.add( *glob_TRG   );
  globalObs.add( *glob_PDFtt );
  globalObs.add( *glob_Q2tt  );
  globalObs.add( *glob_MATCHtt );
  globalObs.add( *glob_REWtt );
  globalObs.add( *glob_PDFsig);
  globalObs.add( *glob_PDFewk);
  globalObs.add( *glob_PDFt  );
  globalObs.add( *glob_ZN    );
  globalObs.add( *glob_WJ    );
  globalObs.add( *glob_probQCD1b );
  // nuisance parameters
  RooRealVar* beta_lumi   = wspace->var("beta_lumi");
  RooRealVar* beta_JEC    = wspace->var("beta_JEC");
  RooRealVar* beta_JER    = wspace->var("beta_JER");
  RooRealVar* beta_TAG    = wspace->var("beta_TAG");
  RooRealVar* beta_TRG    = wspace->var("beta_TRG");
  RooRealVar* beta_PDFtt  = wspace->var("beta_PDFtt");
  RooRealVar* beta_Q2tt   = wspace->var("beta_Q2tt");
  RooRealVar* beta_MATCHtt= wspace->var("beta_MATCHtt");
  RooRealVar* beta_REWtt  = wspace->var("beta_REWtt");
  RooRealVar* beta_PDFsig = wspace->var("beta_PDFsig");
  RooRealVar* beta_PDFewk = wspace->var("beta_PDFewk");
  RooRealVar* beta_PDFt   = wspace->var("beta_PDFt");
  RooRealVar* beta_ZN     = wspace->var("beta_ZN");
  RooRealVar* beta_WJ     = wspace->var("beta_WJ");
  RooRealVar* beta_probQCD1b = wspace->var("beta_probQCD1b");
  RooRealVar* qcdYield    = wspace->var("qcdYield");

//beta_lumi  ->setConstant(true);
//beta_JEC   ->setConstant(true);
//beta_JER   ->setConstant(true);
//beta_TAG   ->setConstant(true);
//beta_PDFtt ->setConstant(true);
//beta_Q2tt  ->setConstant(true);
//beta_MATCHtt->setConstant(true);
//beta_REWtt ->setConstant(true);
//beta_PDFsig->setConstant(true);
//beta_PDFewk->setConstant(true);
//beta_PDFt  ->setConstant(true);
//beta_ZN    ->setConstant(true);
//beta_WJ    ->setConstant(true);
//beta_probQCD1b->setConstant(true);
//qcdYield   ->setConstant(true);
//signalXsec ->setConstant(true);

  RooArgSet NUI;
  NUI.add( *beta_lumi   );
  NUI.add( *beta_JEC    );
  NUI.add( *beta_JER    );
  NUI.add( *beta_TAG    );
  NUI.add( *beta_TRG    );
  NUI.add( *beta_PDFtt  );
  NUI.add( *beta_Q2tt   );
  NUI.add( *beta_MATCHtt);
  NUI.add( *beta_REWtt  );
  NUI.add( *beta_PDFsig );
  NUI.add( *beta_PDFewk );
  NUI.add( *beta_PDFt   );
  NUI.add( *beta_ZN     );
  NUI.add( *beta_WJ     );
  NUI.add( *beta_probQCD1b );
  NUI.add( *qcdYield    );

 // configure S+B model:
  ModelConfig sbModelConfig( "sbModelConfig", wspace );
  sbModelConfig.SetPdf( *(wspace->pdf("fullSBmodel")) );
  sbModelConfig.SetObservables( observables );
  sbModelConfig.SetParametersOfInterest( POI );
  sbModelConfig.SetNuisanceParameters( NUI );
  sbModelConfig.SetPriorPdf( *(wspace->pdf("combinedPrior")) );
  sbModelConfig.SetGlobalObservables( globalObs );

  // create a container for all of the parameters of the S+B model
  RooArgSet * pPoiAndNuisance = new RooArgSet("poiAndNuisance");
  pPoiAndNuisance->add( *sbModelConfig.GetParametersOfInterest() );
  if( sbModelConfig.GetNuisanceParameters() )
      pPoiAndNuisance->add( *sbModelConfig.GetNuisanceParameters() );

  // fit S+B model to the data
  RooAbsReal * pNll = sbModelConfig.GetPdf()->createNLL( *data );
  RooAbsReal * pProfile = pNll->createProfile( RooArgSet() );
  pProfile->getVal(); // this will do fit and set POI and nuisance parameters to fitted values

  // save a snapshot in the model (that'll be used for tossing S+B pseudo experiments)
  cout<<"\nWill save these parameter points that correspond to the fit to data"<<endl;
  pPoiAndNuisance->Print("v");
  sbModelConfig.SetSnapshot( *pPoiAndNuisance );

  // configure B-only model (recycle the S+B model config)
  ModelConfig bModelConfig( sbModelConfig );
  bModelConfig.SetName( "bModelConfig" );
  bModelConfig.SetWorkspace( *wspace );
  bModelConfig.SetPdf( *(wspace->pdf("fullBmodel")) );

  // import the model configs, has to be after all snapshots are saved
  wspace->import(sbModelConfig);
  wspace->import( bModelConfig);

  char fileName[1024];
  sprintf(fileName,"myWS_%s_MET%d.root",names[model],MET_CUT);

  TFile *file = new TFile(fileName,"RECREATE");
  wspace->Write();
  file->Write();
  file->Close();

//beta_WJ->setVal(-0.1);
//RooArgSet q(*beta_WJ);
//cout << "wjYield0b:" << wspace->function("wjYield0b")->getVal(&q) << endl;
//cout << "qcdYield: "<< wspace->var("qcdYield")->getVal() << " +- " << wspace->var("qcdYield")->getError() << endl;
//  doPulls(wspace->pdf("fullSBmodel"),wspace->pdf("combinedPrior"),0);
}

#include "TTree.h"
#include "RooProfileLL.h"

void doPulls(RooAbsPdf *model, RooAbsPdf *prior, double signalCrossSection){
  int seed = 1;

  RooRandom::randomGenerator()->SetSeed(seed);
  char name[128];
  sprintf(name,"pull_%03.0f",signalCrossSection*10);

  TTree *results = new TTree(name,"");

  double signal=0, sigErr=0, nll=0;
  double qcdThrow=0, qcdFound=0, qcdError=0;
  results->Branch("signal",   &signal,   "signal/D");
  results->Branch("sigErr",   &sigErr,   "sigErr/D");
  results->Branch("nll",      &nll,      "nll/D");
//  results->Branch("lumi",     &_lumi,    "lumi/D");
  results->Branch("qcdThrow", &qcdThrow, "qcdThrow/D");
  results->Branch("qcdFound", &qcdFound, "qcdFound/D");
  results->Branch("qcdError", &qcdError, "qcdError/D");

  RooArgSet  *vars         = model->getVariables();
  RooRealVar *signalXsec   = (RooRealVar*) vars->find("signalXsec");
  RooRealVar *beta_lumi    = (RooRealVar*) vars->find("beta_lumi");
  RooRealVar *beta_JEC     = (RooRealVar*) vars->find("beta_JEC");
  RooRealVar *beta_TRG     = (RooRealVar*) vars->find("beta_TRG");
  RooRealVar *beta_REWtt   = (RooRealVar*) vars->find("beta_REWtt");
  RooRealVar *beta_PDFtt   = (RooRealVar*) vars->find("beta_PDFtt");
  RooRealVar *beta_Q2tt    = (RooRealVar*) vars->find("beta_Q2tt");
  RooRealVar *beta_MATCHtt = (RooRealVar*) vars->find("beta_MATCHtt");
  RooRealVar *beta_PDFsig  = (RooRealVar*) vars->find("beta_PDFsig");
  RooRealVar *beta_PDFewk  = (RooRealVar*) vars->find("beta_PDFewk");
  RooRealVar *beta_PDFt    = (RooRealVar*) vars->find("beta_PDFt");
  RooRealVar *beta_ZN      = (RooRealVar*) vars->find("beta_ZN");
  RooRealVar *beta_WJ      = (RooRealVar*) vars->find("beta_WJ");
  RooRealVar *beta_probQCD1b=(RooRealVar*) vars->find("beta_probQCD1b");
  RooRealVar *qcdYield     = (RooRealVar*) vars->find("qcdYield");
  RooRealVar *observed0b   = (RooRealVar*) vars->find("observed0b");
  RooRealVar *observed1b   = (RooRealVar*) vars->find("observed1b");

  for(int pseudoExperiment=0; pseudoExperiment<10000; pseudoExperiment++){
    // initialize all of the parameters, which are involved in generation
    signalXsec->setVal(signalCrossSection);

    RooDataSet *one = 0;
    if( !beta_lumi->isConstant() ){
       one = prior->generate(RooArgSet(*beta_lumi), 1);
       beta_lumi->setVal( one->get()->getRealValue("beta_lumi") );
       delete one;
    }
    if( !beta_JEC->isConstant() ){
       one = prior->generate(RooArgSet(*beta_JEC), 1);
       beta_JEC->setVal( one->get()->getRealValue("beta_JEC") );
       delete one;
    }
    if( !beta_PDFtt->isConstant() ){
       one = prior->generate(RooArgSet(*beta_PDFtt), 1);
       beta_PDFtt->setVal( one->get()->getRealValue("beta_PDFtt") );
       delete one;
    }
    if( !beta_REWtt->isConstant() ){
       one = prior->generate(RooArgSet(*beta_REWtt), 1);
       beta_REWtt->setVal( one->get()->getRealValue("beta_REWtt") );
       delete one;
    }
    if( !beta_TRG->isConstant() ){
       one = prior->generate(RooArgSet(*beta_TRG), 1);
       beta_TRG->setVal( one->get()->getRealValue("beta_TRG") );
       delete one;
    }
    if( !beta_Q2tt->isConstant() ){
       one = prior->generate(RooArgSet(*beta_Q2tt), 1);
       beta_Q2tt->setVal( one->get()->getRealValue("beta_Q2tt") );
       delete one;
    }
    if( !beta_MATCHtt->isConstant() ){
       one = prior->generate(RooArgSet(*beta_MATCHtt), 1);
       beta_MATCHtt->setVal( one->get()->getRealValue("beta_MATCHtt") );
       delete one;
    }
    if( !beta_PDFsig->isConstant() ){
       one = prior->generate(RooArgSet(*beta_PDFsig), 1);
       beta_PDFsig->setVal( one->get()->getRealValue("beta_PDFsig") );
       delete one;
    }
    if( !beta_PDFewk->isConstant() ){
       one = prior->generate(RooArgSet(*beta_PDFewk), 1);
       beta_PDFewk->setVal( one->get()->getRealValue("beta_PDFewk") );
       delete one;
    }
    if( !beta_PDFt->isConstant() ){
       one = prior->generate(RooArgSet(*beta_PDFt), 1);
       beta_PDFt->setVal( one->get()->getRealValue("beta_PDFt") );
       delete one;
    }
    if( !beta_ZN->isConstant() ){
       one = prior->generate(RooArgSet(*beta_ZN), 1);
       beta_ZN->setVal( one->get()->getRealValue("beta_ZN") );
       delete one;
    }
    if( !beta_WJ->isConstant() ){
       one = prior->generate(RooArgSet(*beta_WJ), 1);
       beta_WJ->setVal( one->get()->getRealValue("beta_WJ") );
       delete one;
    }
    if( !beta_probQCD1b->isConstant() ){
       one = prior->generate(RooArgSet(*beta_probQCD1b), 1);
       beta_probQCD1b->setVal( one->get()->getRealValue("beta_probQCD1b") );
       delete one;
    }
    if( !qcdYield->isConstant() ){
       one = prior->generate(RooArgSet(*qcdYield), 1);
       qcdYield->setVal( one->get()->getRealValue("qcdYield") );
       qcdThrow = qcdYield->getVal();
       delete one;
    }
//    vars->Print("v");

    RooDataSet *data = model->generate(RooArgSet(*observed0b,*observed1b),1);
//    data->Print("v");

//    RooAbsReal *lumi     = model->function("luminosity");
    RooAbsReal *pNll     = model->createNLL(*data);
    RooAbsReal *pProfile = pNll->createProfile(RooArgSet());
    pProfile->getVal();
    cout<<" S+B NLL="<<((RooProfileLL*)pProfile)->nll().getVal()<<endl;
    cout//<<"luminosity = "<<lumi->getVal()
        <<" signal = "   <<signalXsec->getVal()
        <<" qcdYield= "   <<qcdYield->getVal()
        <<" (qcdThrow= "   <<qcdThrow<<")"
        <<endl;

    signal   = signalXsec->getVal();
    sigErr   = signalXsec->getError();
    nll      = ((RooProfileLL*)pProfile)->nll().getVal();

//    _lumi     = lumi->getVal();
    qcdFound = qcdYield->getVal();
    qcdError = qcdYield->getError();

    results->Fill();

    delete pProfile;
    delete pNll;
    delete data;

cout<<"Pseudo experiment #"<<pseudoExperiment<<" is complete"<<endl;

}

sprintf(name,"pulls_%03.0f_%d.root",signalCrossSection*10,seed);
TFile *f = new TFile(name,"UPDATE");
results->Write();
f->Close();
delete f;
}
