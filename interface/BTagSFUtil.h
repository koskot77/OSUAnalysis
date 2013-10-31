/*************************************************************

Class Usage:

This class should only be used for upgrading and downgrading 
if a single operating point is used in an analysis. 

bool isBTagged = b-tag flag for jet
int pdgIdPart = parton id
float Btag_SF = MC/data scale factor for b/c-tagging efficiency
float Btag_eff = b/c-tagging efficiency in data
float Bmistag_SF = MC/data scale factor for mistag efficiency
float Bmistag_eff = mistag efficiency in data

Author: Michael Segala
Contact: michael.segala@gmail.com
Updated: Ulrich Heintz 12/23/2011

v 1.1

*************************************************************/


#ifndef BTagSFUtil_lite_h
#define BTagSFUtil_lite_h

#include <Riostream.h>
#include "TRandom3.h"
#include "TMath.h"


class BTagSFUtil{

 public:
    
  BTagSFUtil( int seed=0 );
  ~BTagSFUtil();

  enum {LOOSE=1, MEDIUM=2, TIGHT=3};    

  void modifyBTagsWithSF( bool& isBTagged, int pdgIdPart, float Btag_SF = 0.98, float Btag_eff = 1.0, float Bmistag_SF = 1.0, float  Bmistag_eff = 1.0);
  float GetLightJeteff (float pt = 40, float eta = 1.3, int meanminmax = 0, int workingPoint = MEDIUM);
  float GetBTagSF (float pt = 40, float eta = 1.3, int meanminmax=0, int workingPoint = MEDIUM);
  float GetBTageff (int workingPoint = MEDIUM);
  float GetLightJetSF (float pt = 40, float eta = 1.3, int meanminmax = 0, int workingPoint = MEDIUM);


 private:
  
  bool applySF(bool& isBTagged, float Btag_SF = 0.98, float Btag_eff = 1.0);
  
  TRandom3* rand_;

};


BTagSFUtil::BTagSFUtil( int seed ) {

  rand_ = new TRandom3(seed);

}

BTagSFUtil::~BTagSFUtil() {

  delete rand_;

}


void BTagSFUtil::modifyBTagsWithSF(bool& isBTagged, int pdgIdPart, float Btag_SF, float Btag_eff, float Bmistag_SF, float Bmistag_eff){

  bool newBTag = isBTagged;

  // b quarks and c quarks:
  if( abs( pdgIdPart ) == 5 ||  abs( pdgIdPart ) == 4) { 

    double bctag_eff = Btag_eff;
    if ( abs(pdgIdPart)==4 )  bctag_eff = Btag_eff/5.0; // take ctag eff as one 5th of Btag eff
    newBTag = applySF(isBTagged, Btag_SF, bctag_eff);

    // light quarks:
  } else if( abs( pdgIdPart )>0 ) { //in data it is 0 (save computing time)

    newBTag = applySF(isBTagged, Bmistag_SF, Bmistag_eff);
    
  }

  isBTagged = newBTag;

}


bool BTagSFUtil::applySF(bool& isBTagged, float Btag_SF, float Btag_eff){
  
  bool newBTag = isBTagged;

  if (Btag_SF == 1) return newBTag; //no correction needed 

  //throw die
  float coin = rand_->Uniform(1.);    

  if(Btag_SF > 1){  // use this if SF>1

    if( !isBTagged ) {

      //fraction of jets that need to be upgraded
      float mistagPercent = (1.0 - Btag_SF) / (1.0 - (Btag_SF/Btag_eff) );

      //upgrade to tagged
      if( coin < mistagPercent ) {newBTag = true;}
    }

  }else{  // use this if SF<1
      
    //downgrade tagged to untagged
    if( isBTagged && coin > Btag_SF ) {newBTag = false;}

  }

  return newBTag;
}
float BTagSFUtil::GetBTagSF (float pt, float eta, int meanminmax, int workingPoint){
  float x=pt;
// old SSV:
//  float SFb = 0.896462*((1.+(0.00957275*x))/(1.+(0.00837582*x)));
// new tagger: CSVM within 20 < pt < 800 GeV, abs(eta) < 2.4, x = pt
// from https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFb-pt_payload_Moriond13.txt

//  float ptmin[] = {20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600};
//  float ptmax[] = {30, 40, 50, 60, 70, 80,100, 120, 160, 210, 260, 320, 400, 500, 600, 800};
// above is equivalent to:
  int bin = -1;
  if( pt<20 ) bin = 0;
  if( pt>=20  && pt<80  ) bin = (pt-20)/10;
  if( pt>=80  && pt<120 ) bin = (pt-80)/20 + 6;
  if( pt>=120 && pt<160 ) bin = 8;
  if( pt>=160 && pt<210 ) bin = 9;
  if( pt>=210 && pt<260 ) bin = 10;
  if( pt>=260 && pt<320 ) bin = 11;
  if( pt>=320 && pt<400 ) bin = 12;
  if( pt>=400 && pt<500 ) bin = 13;
  if( pt>=500 && pt<600 ) bin = 14;
  if( pt>=600 && pt<800 ) bin = 15;
  if( pt>800 ) bin = 15;

  float SFb_errorLoose[] = {0.0484285, 0.0126178, 0.0120027, 0.0141137, 0.0145441, 0.0131145, 0.0168479, 0.0160836,
                            0.0126209, 0.0136017, 0.019182,  0.0198805, 0.0386531, 0.0392831, 0.0481008, 0.0474291 };
  float SFb_errorMedium[]= {0.0554504, 0.0209663, 0.0207019, 0.0230073, 0.0208719, 0.0200453, 0.0264232, 0.0240102,
                            0.0229375, 0.0184615, 0.0216242, 0.0248119, 0.0465748, 0.0474666, 0.0718173, 0.0717567 };
  float SFb_errorTight[] = {0.0567059, 0.0266907, 0.0263491, 0.0342831, 0.0303327, 0.024608,  0.0333786, 0.0317642,
                            0.031102,  0.0295603, 0.0474663, 0.0503182, 0.0580424, 0.0575776, 0.0769779, 0.0898199 };
  float SFb = 1;
  switch( workingPoint ){
     case LOOSE  : SFb = 0.981149*((1.+(-0.000713295*x))/(1.+(-0.000703264*x)));
        if( meanminmax == 1 ) SFb += SFb_errorLoose[bin];
        if( meanminmax ==-1 ) SFb -= SFb_errorLoose[bin];
     break;
     case MEDIUM : SFb = 0.726981*((1.+(0.253238*x))/(1.+(0.188389*x)));
        if( meanminmax == 1 ) SFb += SFb_errorMedium[bin];
        if( meanminmax ==-1 ) SFb -= SFb_errorMedium[bin];
     break;
     case TIGHT  : SFb = 0.869965*((1.+(0.0335062*x))/(1.+(0.0304598*x)));
        if( meanminmax == 1 ) SFb += SFb_errorTight[bin];
        if( meanminmax ==-1 ) SFb -= SFb_errorTight[bin];
     break;
     default : break;
  }
// those are always <1 -> we won't need to promote random jets to b-jets
  return SFb;
}

float BTagSFUtil::GetBTageff (int workingPoint){
//  float x=1.74;
  float effb=1;

// this function is not important if SFb<1
//  effb =  -0.00592795459517*x*x*x*x +  0.100276502585*x*x*x +  -0.562858452018*x*x +  1.02676379935*x +  0.0810613917651;
  
  return effb;
}

float BTagSFUtil::GetLightJetSF (float pt, float eta, int meanminmax, int workingPoint){
  float x=pt; 
  float tmpSFl=1;
// old SSV:
/*
  if(fabs(eta)>=0.0 &&  fabs(eta) <=0.8)
      {
	if( meanminmax == 0 ) tmpSFl = ((0.86318+(0.000801639*x))+(-1.64119e-06*(x*x)))+(2.59121e-10*(x*(x*x)));
	if( meanminmax == -1 ) tmpSFl = ((0.790364+(0.000463086*x))+(-4.35934e-07*(x*x)))+(-9.08296e-10*(x*(x*x)));
	if( meanminmax == 1 ) tmpSFl = ((0.935969+(0.0011402*x))+(-2.84645e-06*(x*x)))+(1.42654e-09*(x*(x*x)));
      }
  if(fabs(eta)>0.8 &&  fabs(eta) <=1.6)
    {
      if( meanminmax == 0 ) tmpSFl = ((0.958973+(-0.000269555*x))+(1.381e-06*(x*x)))+(-1.87744e-09*(x*(x*x)));
      if( meanminmax == -1 ) tmpSFl = ((0.865771+(-0.000279908*x))+(1.34144e-06*(x*x)))+(-1.75588e-09*(x*(x*x)));
      if( meanminmax == 1 ) tmpSFl = ((1.0522+(-0.000259296*x))+(1.42056e-06*(x*x)))+(-1.999e-09*(x*(x*x)));
    }
  if(fabs(eta)>1.6 &&  fabs(eta) <=2.4)
    {
      if( meanminmax == 0 ) tmpSFl = ((0.923033+(-0.000898227*x))+(4.74565e-06*(x*x)))+(-6.11053e-09*(x*(x*x)));
      if( meanminmax == -1 ) tmpSFl =((0.828021+(-0.000731926*x))+(4.19613e-06*(x*x)))+(-5.81379e-09*(x*(x*x)));
      if( meanminmax == 1 ) tmpSFl =((1.01812+(-0.00106483*x))+(5.29518e-06*(x*x)))+(-6.40728e-09*(x*(x*x)));
    }
*/

  // using https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFlightFuncs_Moriond2013.C and
  // assuming we are running on the whole A+B+C+D 2012 dataset, the SFs are:
switch( workingPoint ){
case LOOSE:
    if( fabs(eta)>= 0.0 && fabs(eta)<0.5 )
      {
	if( meanminmax == 0  ) tmpSFl = ((1.04901+(0.00152181*x))+(-3.43568e-06*(x*x)))+(2.17219e-09*(x*(x*x)));
	if( meanminmax == -1 ) tmpSFl = ((0.973773+(0.00103049*x))+(-2.2277e-06*(x*x)))+(1.37208e-09*(x*(x*x)));
	if( meanminmax == 1  ) tmpSFl = ((1.12424+(0.00201136*x))+(-4.64021e-06*(x*x)))+(2.97219e-09*(x*(x*x)));
      }
    if( fabs(eta)>=0.5 && fabs(eta)<1.0 )
      {
	if( meanminmax == 0  ) tmpSFl = ((0.991915+(0.00172552*x))+(-3.92652e-06*(x*x)))+(2.56816e-09*(x*(x*x)));
	if( meanminmax == -1 ) tmpSFl = ((0.921518+(0.00129098*x))+(-2.86488e-06*(x*x)))+(1.86022e-09*(x*(x*x)));
	if( meanminmax == 1  ) tmpSFl = ((1.06231+(0.00215815*x))+(-4.9844e-06*(x*x)))+(3.27623e-09*(x*(x*x)));
      }
    if( fabs(eta)>=1.0 && fabs(eta)<1.5 )
      {
	if( meanminmax == 0  ) tmpSFl = ((0.962127+(0.00192796*x))+(-4.53385e-06*(x*x)))+(3.0605e-09*(x*(x*x)));
	if( meanminmax == -1 ) tmpSFl = ((0.895419+(0.00153387*x))+(-3.48409e-06*(x*x)))+(2.30899e-09*(x*(x*x)));
	if( meanminmax == 1  ) tmpSFl = ((1.02883+(0.00231985*x))+(-5.57924e-06*(x*x)))+(3.81235e-09*(x*(x*x)));
      }
    if( fabs(eta)>=1.5 && fabs(eta)<2.4 )
      {
	if( meanminmax == 0  ) tmpSFl = ((1.06121+(0.000332747*x))+(-8.81201e-07*(x*x)))+(7.43896e-10*(x*(x*x)));
	if( meanminmax == -1 ) tmpSFl = ((0.983607+(0.000196747*x))+(-3.98327e-07*(x*x)))+(2.95764e-10*(x*(x*x)));
	if( meanminmax == 1  ) tmpSFl = ((1.1388+(0.000468418*x))+(-1.36341e-06*(x*x)))+(1.19256e-09*(x*(x*x)));
      }
break;
case MEDIUM:
  if(fabs(eta)>=0.0 &&  fabs(eta) <=0.8)
      {
	if( meanminmax == 0  ) tmpSFl = ((1.06238+(0.00198635*x))+(-4.89082e-06*(x*x)))+(3.29312e-09*(x*(x*x)));
	if( meanminmax == -1 ) tmpSFl = ((0.972746+(0.00104424*x))+(-2.36081e-06*(x*x)))+(1.53438e-09*(x*(x*x)));
	if( meanminmax == 1  ) tmpSFl = ((1.15201+(0.00292575*x))+(-7.41497e-06*(x*x)))+(5.0512e-09*(x*(x*x)));
      }
  if(fabs(eta)>0.8 &&  fabs(eta) <=1.6)
    {
      if( meanminmax == 0  ) tmpSFl = ((1.08048+(0.00110831*x))+(-2.96189e-06*(x*x)))+(2.16266e-09*(x*(x*x)));
      if( meanminmax == -1 ) tmpSFl = ((0.9836+(0.000649761*x))+(-1.59773e-06*(x*x)))+(1.14324e-09*(x*(x*x)));
      if( meanminmax == 1  ) tmpSFl = ((1.17735+(0.00156533*x))+(-4.32257e-06*(x*x)))+(3.18197e-09*(x*(x*x)));
    }
  if(fabs(eta)>1.6 &&  fabs(eta) <=2.4)
    {
      if( meanminmax == 0  ) tmpSFl = ((1.09145+(0.000687171*x))+(-2.45054e-06*(x*x)))+(1.7844e-09*(x*(x*x)));
      if( meanminmax == -1 ) tmpSFl = ((1.00616+(0.000358884*x))+(-1.23768e-06*(x*x)))+(6.86678e-10*(x*(x*x)));
      if( meanminmax == 1  ) tmpSFl = ((1.17671+(0.0010147*x))+(-3.66269e-06*(x*x)))+(2.88425e-09*(x*(x*x)));
    }
break;
case TIGHT:
    if( fabs(eta)>=0.0 && fabs(eta)<2.4 )
      {
	if( meanminmax == 0  ) tmpSFl = ((1.01739+(0.00283619*x))+(-7.93013e-06*(x*x)))+(5.97491e-09*(x*(x*x)));
	if( meanminmax == -1 ) tmpSFl = ((0.953587+(0.00124872*x))+(-3.97277e-06*(x*x)))+(3.23466e-09*(x*(x*x)));
	if( meanminmax == 1  ) tmpSFl = ((1.08119+(0.00441909*x))+(-1.18764e-05*(x*x)))+(8.71372e-09*(x*(x*x)));
      }
break;
default: break;
}
    return tmpSFl;

}

float BTagSFUtil::GetLightJeteff (float pt, float eta, int meanminmax, int workingPoint){
  float x=pt;
  float tmpMistag=1;
// old SSV:
/*
  if(fabs(eta)>=0.0 &&  fabs(eta) <=0.8)
    {
      if( meanminmax == 0 ) tmpMistag = (((0.000547883+(0.00023023*x))+(-7.31792e-07*(x*x)))+(1.15659e-09*(x*(x*x))))+(-7.00641e-13*(x*(x*(x*x))));
    }
  if(fabs(eta)>0.8 &&  fabs(eta) <=1.6)
    {
      if( meanminmax == 0 ) tmpMistag = (((0.000615562+(0.000240254*x))+(-7.00237e-07*(x*x)))+(1.2566e-09*(x*(x*x))))+(-8.59011e-13*(x*(x*(x*x))));
    }
  if(fabs(eta)>1.6 &&  fabs(eta) <=2.4)
      {
	if( meanminmax == 0 ) tmpMistag = (((0.000372388+(0.000309735*x))+(-4.35952e-07*(x*x)))+(3.63763e-10*(x*(x*x))))+(-2.11993e-13*(x*(x*(x*x))));
      }
*/
// official interpolations are nowhere to be found, using a homemade linear approximation of top plot in Fig.18 of
// http://cms.cern.ch/iCMS/jsp/openfile.jsp?tp=draft&files=AN2012_195_v2.pdf
// i.e. MC: pt=45, eff=1%, pt=775, eff=2.6%
//    tmpMistag = (0.026-0.01)*(x-45.)/(775.-45.) + 0.01;

// https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/MistagFuncs.C:
///if( x<20 || x>670 ) return tmpMistag;

meanminmax=0; 

switch( workingPoint ){
case LOOSE:
  if( fabs(eta)>=0.0 && fabs(eta)<0.5 )
    {
       if( meanminmax == 0 ) tmpMistag = 242534*(((1+(0.0182863*x))+(4.50105e-05*(x*x)))/(1+(108569*x)));
    }
  if( fabs(eta)>=0.5 && fabs(eta)<1.0 )
    {
       if( meanminmax == 0 ) tmpMistag = 129.938*(((1+(0.0197657*x))+(4.73472e-05*(x*x)))/(1+(55.2415*x)));
    }
  if( fabs(eta)>=1.0 && fabs(eta)<1.5 )
    {
       if( meanminmax == 0 ) tmpMistag = 592.214*(((1+(0.00671207*x))+(6.46109e-05*(x*x)))/(1+(134.318*x)));
    }
  if( fabs(eta)>=1.5 && fabs(eta)<2.4 )
    {
       if( meanminmax == 0 ) tmpMistag = 93329*(((1+(0.0219705*x))+(3.76566e-05*(x*x)))/(1+(18245.1*x)));
    }
//if( fabs(eta)>=0.0 && fabs(eta)<2.4 )
//{
//if( meanminmax == 0 ) tmpMistag = 18168.8*(((1+(0.020356*x))+(2.73475e-05*(x*x)))/(1+(5239.42*x)));
//}
break;
case MEDIUM:
  if( fabs(eta)>=0.0 &&  fabs(eta) <0.8 )
    {
      if( meanminmax == 0 ) tmpMistag = (0.00967751+(2.54564e-05*x))+(-6.92256e-10*(x*x));
    }
  if( fabs(eta)>=0.8 &&  fabs(eta) <1.6 )
    {
      if( meanminmax == 0 ) tmpMistag = (0.00974141+(5.09503e-05*x))+(2.0641e-08*(x*x));
    }
  if( fabs(eta)>=1.6 &&  fabs(eta) <2.4 )
    {
      if( meanminmax == 0 ) tmpMistag = (0.013595+(0.000104538*x))+(-1.36087e-08*(x*x));
    }
//  if( fabs(eta)>0.0 &&  fabs(eta) <=2.4 )
//      {
//	if( meanminmax == 0 ) tmpMistag = (0.0113428+(5.18983e-05*x))+(-2.59881e-08*(x*x));
//      }
break;
case TIGHT:
  if( fabs(eta)>=0.0 && fabs(eta) <2.4 )
    {
      if( meanminmax == 0 ) tmpMistag = 0.00315116*(((1+(-0.00769281*x))+(2.58066e-05*(x*x)))+(-2.02149e-08*(x*(x*x))));
    }
break;
default: break;
}
    return tmpMistag;

}

#endif

