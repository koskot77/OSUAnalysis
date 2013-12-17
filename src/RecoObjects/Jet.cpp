/*
 * Jet.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/Jet.h"
#include "../../interface/BTagSFUtil.h"

#include <iostream>


using namespace std;

namespace BAT {

// Set static member
JetCorrDirection::value Jet::correctDirection = JetCorrDirection::NONE;
JetBtagVariation::value Jet::bTagVariation = JetBtagVariation::NONE;
JetResVariation::value  Jet::resVariation  = JetResVariation::NONE;
	
Jet::Jet() :
    Particle(),
    DiffVec(diffVec),
    usedAlgorithm(JetAlgorithm::Calo_AntiKT_Cone05),
    electromagneticFraction(0.),
    numberOfRecHitsContaining90PercentOfTheJetEnergy(0.),
    fractionOfEnergyIntheHottestHPDReadout(0.),
    btag_discriminators(BtagAlgorithm::NUMBER_OF_BTAGALGORITHMS),
    numberOfDaughters(0),
    chargedEmEnergyFraction(1),
    neutralHadronEnergyFraction(1),
    neutralEmEnergyFraction(1),
    chargedHadronEnergyFraction(1),
    chargedMultiplicity(0),
    partonFlavr(0)
{
    for (unsigned int btag = 0; btag < btag_discriminators.size(); ++btag) {
        btag_discriminators[btag] = -9999;
    }
}

//Jet::Jet(const Particle& particle) :
//    Particle(particle),
//    usedAlgorithm(JetAlgorithm::Calo_AntiKT_Cone05),
//    electromagneticFraction(0.),
//    numberOfRecHitsContaining90PercentOfTheJetEnergy(0.),
//    fractionOfEnergyIntheHottestHPDReadout(0.),
//    btag_discriminators(BJetTagger::NUMBER_OF_BTAGALGORITHMS),
//    numberOfDaughters(0),
//    chargedEmEnergyFraction(1),
//    neutralHadronEnergyFraction(1),
//    neutralEmEnergyFraction(1),
//    chargedHadronEnergyFraction(1),
//    chargedMultiplicity(0) {
//
//}
Jet::Jet(float energy, float px, float py, float pz) :
    Particle(energy, px, py, pz),
    DiffVec(diffVec),
    usedAlgorithm(JetAlgorithm::Calo_AntiKT_Cone05),
    electromagneticFraction(0.),
    btag_discriminators(BtagAlgorithm::NUMBER_OF_BTAGALGORITHMS),
    numberOfDaughters(0),
    chargedEmEnergyFraction(1),
    neutralHadronEnergyFraction(1),
    neutralEmEnergyFraction(1),
    chargedHadronEnergyFraction(1),
    chargedMultiplicity(0),
    partonFlavr(0)
{
    for (unsigned int btag = 0; btag < btag_discriminators.size(); ++btag) {
        btag_discriminators[btag] = -9999;
    }

}

Jet::~Jet() {
}

JetAlgorithm::value Jet::getUsedAlgorithm() const {
    return usedAlgorithm;
}

float Jet::genJetPt() const {
    return matchedGenJetPt;
}

float Jet::emf() const {
    return electromagneticFraction;
}

float Jet::n90Hits() const {
    return numberOfRecHitsContaining90PercentOfTheJetEnergy;
}

float Jet::fHPD() const {
    return fractionOfEnergyIntheHottestHPDReadout;
}

float Jet::NOD() const {
    return numberOfDaughters;
}

float Jet::CEF() const {
    return chargedEmEnergyFraction;
}

float Jet::NHF() const {
    return neutralHadronEnergyFraction;
}

float Jet::NEF() const {
    return neutralEmEnergyFraction;
}

float Jet::CHF() const {
    return chargedHadronEnergyFraction;
}

float Jet::NCH() const {
    return chargedMultiplicity;
}

double Jet::JECUnc() const {
    return jecUncertainty ;
}

int Jet::partonFlavour() const {
	return (partonFlavr);
}

//void Jet::setBtagVariation(JetBtagVariation::value var){
//    bTagVariation = var;
//}
//void Jet::setJetVariation(JetResVariation::value var){
//    resVariation = var;
//}

void Jet::setUsedAlgorithm(JetAlgorithm::value algo) {
    usedAlgorithm = algo;
}

void Jet::setGenJetPt(float genJetPt){
    matchedGenJetPt = genJetPt;
}

void Jet::setEMF(float emf) {
    electromagneticFraction = emf;
}

void Jet::setN90Hits(int n90Hits) {
    numberOfRecHitsContaining90PercentOfTheJetEnergy = n90Hits;
}

void Jet::setPartonFlavour(int partonFlvr) {
    partonFlavr = partonFlvr;
}

void Jet::setFHPD(float fHPD) {
    fractionOfEnergyIntheHottestHPDReadout = fHPD;
}

void Jet::setDiscriminatorForBtagType(float discriminator, BtagAlgorithm::value type) {
    btag_discriminators[type] = discriminator;
}

float Jet::getDiscriminatorForBtagType(BtagAlgorithm::value type) const {
    return btag_discriminators[type];
}

void Jet::setNOD(int nod) {
    numberOfDaughters = nod;
}
void Jet::setCEF(float cef) {
    chargedEmEnergyFraction = cef;
}
void Jet::setNHF(float nhf) {
    neutralHadronEnergyFraction = nhf;
}
void Jet::setNEF(float nef) {
    neutralEmEnergyFraction = nef;
}
void Jet::setCHF(float chf) {
    chargedHadronEnergyFraction = chf;
}

void Jet::setNCH(float nch) {
    chargedMultiplicity = nch;
}

void Jet::setJECUnc(double jecUnc) {
    jecUncertainty = jecUnc;
}


//double BEANhelper::getJERfactor( int returnType, double jetAbsETA, double genjetPT, double recojetPT){
void Jet::adjForRes(){
    double factor = 1.;
    
    double scale_JER = 1., scale_JERup = 1., scale_JERdown = 1.;

    double diff_FullSim_FastSim = 0.;

    double jetAbsETA = eta();

    if( jetAbsETA<0.5 ){ 
        scale_JER = 1.052; scale_JERup = 1.052 + sqrt( 0.012*0.012 + 0.062*0.062 ); scale_JERdown = 1.052 - sqrt( 0.012*0.012 + 0.061*0.061 );
        diff_FullSim_FastSim = 1.35;
    } else if( jetAbsETA<1.1 ){ 
        scale_JER = 1.057; scale_JERup = 1.057 + sqrt( 0.012*0.012 + 0.056*0.056 ); scale_JERdown = 1.057 - sqrt( 0.012*0.012 + 0.055*0.055 );
        diff_FullSim_FastSim = 1.54;
    } else if( jetAbsETA<1.7 ){ 
        scale_JER = 1.096; scale_JERup = 1.096 + sqrt( 0.017*0.017 + 0.063*0.063 ); scale_JERdown = 1.096 - sqrt( 0.017*0.017 + 0.062*0.062 );
        diff_FullSim_FastSim = 1.97;
    } else if( jetAbsETA<2.3 ){ 
        scale_JER = 1.134; scale_JERup = 1.134 + sqrt( 0.035*0.035 + 0.087*0.087 ); scale_JERdown = 1.134 - sqrt( 0.035*0.035 + 0.085*0.085 );
        diff_FullSim_FastSim = 3.12;
    } else if( jetAbsETA<5.0 ){ 
        scale_JER = 1.288; scale_JERup = 1.288 + sqrt( 0.127*0.127 + 0.155*0.155 ); scale_JERdown = 1.288 - sqrt( 0.127*0.127 + 0.153*0.153 );
        diff_FullSim_FastSim = 3.12;
    }

    double jetPt_JER = pt();
    double jetPt_JERup = pt();
    double jetPt_JERdown = pt();

    double diff_recojet_genjet = pt() - genJetPt();
//    if ((era == "2011" && samplename == "ttH120") || (era == "2012_52x" && samplename == "ttH120_FastSim"))
//      diff_recojet_genjet += diff_FullSim_FastSim;

    if( genJetPt()>10. ){
        jetPt_JER = std::max( 0., genJetPt() + scale_JER * ( diff_recojet_genjet ) );
        jetPt_JERup = std::max( 0., genJetPt() + scale_JERup * ( diff_recojet_genjet ) );
        jetPt_JERdown = std::max( 0., genJetPt() + scale_JERdown * ( diff_recojet_genjet ) );
    }

    if( resVariation==JetResVariation::PLUS )      factor = jetPt_JERup/pt();
    else if( resVariation==JetResVariation::MINUS) factor = jetPt_JERdown/pt();
    else                                           factor = jetPt_JER/pt();

    if( genJetPt()<=10. ) factor = 1.;

        FourVector new4vec = getFourVector();
        new4vec *= factor;
	diffVec  = getFourVector() - new4vec;
        setFourVector(new4vec);
        if (particleMass != 0.0)
                particleMass *= factor;
        // cout << "oldmass corr newmass " << oldmass << " " << corrFactor;
        // cout << " " << mass() << endl;
}


void Jet::adjForUnc()
{
	double corrFactor = 1.0;
	switch (correctDirection) {
		case JetCorrDirection::NONE:
			return;
		case JetCorrDirection::PLUS:
			corrFactor += jecUncertainty;
			break;
		case JetCorrDirection::MINUS:
			corrFactor -= jecUncertainty;
			break;
		default:
			break;
	}
	if (corrFactor == 1.0 || corrFactor <= 0 || corrFactor > 5.0)
		return;	// Reject excess values
	// double nrg = energy(), currpx = px(), currpy = py(), currpz = pz();
	// nrg *= corrFactor;
	// currpx *= corrFactor;
	// currpy *= corrFactor;
	// currpz *= corrFactor;
	FourVector new4vec = getFourVector();
	// double oldmass = massFromEnergyAndMomentum();
	new4vec *= corrFactor;
	diffVec += getFourVector() - new4vec;
	setFourVector(new4vec);
	if (particleMass != 0.0)
		particleMass *= corrFactor;
	// cout << "oldmass corr newmass " << oldmass << " " << corrFactor;
	// cout << " " << mass() << endl;
}


bool Jet::isGood() const {
    // bool passesPt = pt() > 30; // Bristol original value
    bool passesPt = pt() > 35;  // 19.07.11 Chris's value
    bool passesEta = fabs(eta()) < 2.4;
    bool jetID = false;
    //if (usedAlgorithm == JetAlgorithm::ParticleFlow || usedAlgorithm == JetAlgorithm::PF2PAT) {
    if (usedAlgorithm == JetAlgorithm::CA08PF || usedAlgorithm == JetAlgorithm::PF2PAT) {
        bool passNOD = NOD() > 1;
        bool passCEF = CEF() < 0.99;
        bool passNHF = NHF() < 0.99;
        bool passNEF = NEF() < 0.99;
        bool passCHF = true;
        bool passNCH = true;
        if (fabs(eta()) < 2.4) {
            passCHF = CHF() > 0;
            passNCH = NCH() > 0;
        }
        jetID = passNOD && passCEF && passNHF && passNEF && passCHF && passNCH;
    }
    else{
        bool passesEMF = emf() > 0.01;
        bool passesN90Hits = n90Hits() > 1;
        bool passesFHPD = fHPD() < 0.98;
        jetID = passesEMF && passesN90Hits && passesFHPD;
    }
    return passesPt && passesEta && jetID;
}

/* Values taken from
 * https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideBTagPerformance
 */
bool Jet::isTaggedAsBJet(BtagAlgorithm::value type, BtagAlgorithm::workingPoint wp) const {
    float cut(-9998);
    switch (type) {
    case BtagAlgorithm::GenPartonFlavour:
        return abs(partonFlavour()) == 5;

    case BtagAlgorithm::SimpleSecondaryVertexHighEffBTag:
        if (wp == BtagAlgorithm::LOOSE)
            cut = -9998;//no input found
        else if (wp == BtagAlgorithm::MEDIUM)
            cut = 1.74;
        else if (wp == BtagAlgorithm::TIGHT)
            cut = 3.05;
        break;

    case BtagAlgorithm::SimpleSecondaryVertexHighPurBTag:
        if (wp == BtagAlgorithm::LOOSE)
            cut = -9998;//no input found
        else if (wp == BtagAlgorithm::MEDIUM)
            cut = -9998;//no input found
        else if (wp == BtagAlgorithm::TIGHT)
            cut = 2.;
        break;

    case BtagAlgorithm::TrackCountingHighEffBTag:
        if (wp == BtagAlgorithm::LOOSE)
            cut = 1.7;
        else if (wp == BtagAlgorithm::MEDIUM)
            cut = 3.3;
        else if (wp == BtagAlgorithm::TIGHT)
            cut = 10.2;
        break;

    case BtagAlgorithm::TrackCountingHighPurBTag:
        if (wp == BtagAlgorithm::LOOSE)
            cut = 1.19;
        else if (wp == BtagAlgorithm::MEDIUM)
            cut = 1.93;
        else if (wp == BtagAlgorithm::TIGHT)
            cut = 3.41;
        break;

    case BtagAlgorithm::JetProbabilityBTag:
        if (wp == BtagAlgorithm::LOOSE)
            cut = 0.215;
        else if (wp == BtagAlgorithm::MEDIUM)
            cut = 0.459;
        else if (wp == BtagAlgorithm::TIGHT)
            cut = 0.669;
        break;

    case BtagAlgorithm::JetBProbabilityBTag:
        if (wp == BtagAlgorithm::LOOSE)
            cut = 0.988;
        else if (wp == BtagAlgorithm::MEDIUM)
            cut = 1.83;
        else if (wp == BtagAlgorithm::TIGHT)
            cut = 1.95;
        break;

    // WPs are taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagPerformanceOP
    case BtagAlgorithm::CombinedSecondaryVertexBTag:
        if (wp == BtagAlgorithm::LOOSE)
            cut = 0.244;
        else if (wp == BtagAlgorithm::MEDIUM)
            cut = 0.679;
        else if (wp == BtagAlgorithm::TIGHT)
            cut = 0.898;
        break;

    default:
        return false;

    }
    return btag_discriminators[type] > cut;
}


bool Jet::isBJet(BtagAlgorithm::value type, BtagAlgorithm::workingPoint wp) const {
	int jet_flavor = partonFlavour();
	float jet_pt = pt();
	float jet_phi = phi();
	float jet_eta = eta();
//	bool isTagged = isTaggedAsBJet(BtagAlgorithm::SimpleSecondaryVertexHighEffBTag);
//	bool isTagged = isTaggedAsBJet(BtagAlgorithm::CombinedSecondaryVertexBTag);//,BtagAlgorithm::LOOSE);
//	bool isTagged = isTaggedAsBJet(BtagAlgorithm::TrackCountingHighEffBTag);
        bool isTagged = isTaggedAsBJet(type,wp);

	//set a unique seed
	double sin_phi = sin((double) jet_phi * 1000000);
	double seed = abs(static_cast<int>(sin_phi * 100000));

	//Initialize class
	BTagSFUtil btsfutil(seed);

	//modify tags, make sure factors agree with the BtagAlgorithm above
        int workingPoint = BTagSFUtil::MEDIUM; 
        switch( wp ){
           case BtagAlgorithm::LOOSE : workingPoint = BTagSFUtil::LOOSE;  break;
           case BtagAlgorithm::MEDIUM: workingPoint = BTagSFUtil::MEDIUM; break;
           case BtagAlgorithm::TIGHT : workingPoint = BTagSFUtil::TIGHT;  break;
           default: break;
        }

        int var = 0;
        switch( bTagVariation ){
           case JetBtagVariation::NONE:  var = 0; break;
           case JetBtagVariation::PLUS:  var = 1; break;
           case JetBtagVariation::MINUS: var =-1; break;
           default: break;
        }

//if( var!=0 && abs(jet_flavor)!=5 && abs(jet_flavor)!=4 ) var = 0;

	double BTagSF =  btsfutil.GetBTagSF(jet_pt, jet_eta, var, workingPoint);
	double BTageff =  btsfutil.GetBTageff(workingPoint);
	double LightJetSF =  btsfutil.GetLightJetSF(jet_pt, jet_eta, var, workingPoint);
	double LightJeteff =  btsfutil.GetLightJeteff(jet_pt, jet_eta, var, workingPoint);
/*
cout
<<"BTagSF= "<<btsfutil.GetBTagSF(jet_pt, jet_eta, 0, workingPoint)<<" BTageff= "<<btsfutil.GetBTageff(workingPoint)<<" LightJetSF= "<<btsfutil.GetLightJetSF(jet_pt, jet_eta, 0, workingPoint)<<" LightJeteff= "<<btsfutil.GetLightJeteff(jet_pt, jet_eta, 0, workingPoint)
<<"+BTagSF= "<<btsfutil.GetBTagSF(jet_pt, jet_eta, 1, workingPoint)<<" BTageff= "<<btsfutil.GetBTageff(workingPoint)<<" +LightJetSF= "<<btsfutil.GetLightJetSF(jet_pt, jet_eta, 1, workingPoint)<<" +LightJeteff= "<<btsfutil.GetLightJeteff(jet_pt, jet_eta, 1, workingPoint)
<<"-BTagSF= "<<btsfutil.GetBTagSF(jet_pt, jet_eta,-1, workingPoint)<<" BTageff= "<<btsfutil.GetBTageff(workingPoint)<<" -LightJetSF= "<<btsfutil.GetLightJetSF(jet_pt, jet_eta,-1, workingPoint)<<" -LightJeteff= "<<btsfutil.GetLightJeteff(jet_pt, jet_eta,-1, workingPoint)
<<endl;
*/

// SFc = SFb with twice the quoted uncertainty:
if( var != 0 && abs(jet_flavor)==4 ){
   double delta = BTagSF - btsfutil.GetBTagSF(jet_pt, jet_eta, 0, workingPoint);
   BTagSF += delta;
}

	btsfutil.modifyBTagsWithSF(isTagged, jet_flavor, BTagSF, BTageff, LightJetSF, LightJeteff);
	return (isTagged);
}

}  // end namespace BAT
