/*
 * Electron.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/Electron.h"
#include <assert.h>
#include <iostream>

using namespace std;

namespace BAT {

static const float initialBigValue = 123456789;
Electron::Electron() :
    Lepton(),
    usedAlgorithm(ElectronAlgorithm::Calo),
		electronIDUsed(eIDMethod::VBTF),
    robustLooseId(false),
    robustTightId(false),
    superCluser_Eta(initialBigValue),
    effectiveArea(initialBigValue),
    ecal_Isolation(initialBigValue),
    hcal_Isolation(initialBigValue),
    tracker_Isolation(initialBigValue),
    innerLayerMissingHits_(initialBigValue),
    sigma_IEtaIEta(0),
    dPhi_In(0),
    dEta_In(0),
    hadOverEm(0),
    gsfTrack(),
    closesTrackID(-1),
    cicEID(0),
    mvaTrigV0(0),
    mvaNonTrigV0(0),
    sharedFractionInnerHits(0),
    dCotThetaToNextTrack(0),
    distToNextTrack(0)
    {
}

Electron::Electron(float energy, float px, float py, float pz) :
    Lepton(energy, px, py, pz),
    usedAlgorithm(ElectronAlgorithm::Calo),
		electronIDUsed(eIDMethod::VBTF),
    robustLooseId(false),
    robustTightId(false),
    superCluser_Eta(initialBigValue),
    effectiveArea(initialBigValue),
    ecal_Isolation(initialBigValue),
    hcal_Isolation(initialBigValue),
    tracker_Isolation(initialBigValue),
    innerLayerMissingHits_(initialBigValue),
    sigma_IEtaIEta(0),
    dPhi_In(0),
    dEta_In(0),
    hadOverEm(0),
    gsfTrack(),
    closesTrackID(-1),
    cicEID(0),
    mvaTrigV0(0),
    mvaNonTrigV0(0),
    sharedFractionInnerHits(0),
    dCotThetaToNextTrack(0),
    distToNextTrack(0)
    {
}

Electron::~Electron() {
}

float Electron::superClusterEta() const {
    return superCluser_Eta;
}
float Electron::Aeff() const {
    return effectiveArea;
}
float Electron::ecalIsolation() const {
    return ecal_Isolation;
}

float Electron::hcalIsolation() const {
    return hcal_Isolation;
}

float Electron::trackerIsolation() const {
    return tracker_Isolation;
}

float Electron::relativeIsolation() const {
    return (ecal_Isolation + hcal_Isolation + tracker_Isolation) / this->et();
}

// https://twiki.cern.ch/twiki/bin/view/CMS/EgammaEARhoCorrection#Isolation_cone_R_0_4
float Electron::pfIsolationAeff() const {
//    const double EA04eta[] = {0,    1,    1.479, 2,    2.2,  2.3,  2.4};
 //   const double EA04lut[] = {0.21, 0.21, 0.11,  0.14, 0.18, 0.18, 0.26};
    return (PFChargedHadron_Isolation + std::max(float(0), PFGamma_Isolation + PFNeutralHadron_Isolation - PFrho * effectiveArea) ) / pt();
}

bool Electron::isHEEPIsolated() const {
    if (isInBarrelRegion())
        return (ecal_Isolation + hcal_Isolation) < 2 + 0.03 * et();
    else if (isInEndCapRegion() && et() < 50)
        return (ecal_Isolation + hcal_Isolation) < 2.5;
    else if (isInEndCapRegion() && et() >= 50)
        return (ecal_Isolation + hcal_Isolation) < 2.5 + 0.03 * (et() - 50);
    else
        return false;
}

ElectronAlgorithm::value Electron::getUsedAlgorithm() const {
    return usedAlgorithm;
}

void Electron::setEcalIsolation(float isolation) {
    ecal_Isolation = isolation;
}

void Electron::setHcalIsolation(float isolation) {
    hcal_Isolation = isolation;
}

void Electron::setTrackerIsolation(float isolation) {
    tracker_Isolation = isolation;
}

void Electron::setSuperClusterEta(float eta) {
    superCluser_Eta = eta;
}

void Electron::setEffectiveArea(float effArea) {
    effectiveArea = effArea;
}

void Electron::setRobustLooseID(bool id) {
    robustLooseId = id;
}

void Electron::setRobustTightID(bool id) {
    robustTightId = id;
}

void Electron::setSigmaIEtaIEta(float sigma) {
    sigma_IEtaIEta = sigma;
}

void Electron::setDPhiIn(float dphi) {
    dPhi_In = dphi;
}

void Electron::setDEtaIn(float deta) {
    dEta_In = deta;
}

void Electron::setHadOverEm(float HoverE) {
    hadOverEm = HoverE;
}

void Electron::setCICeID(int cicElID) {
    cicEID = cicElID;
}

void Electron::setMvaTrigV0eID(float mvaID) {
    mvaTrigV0 = mvaID;
}

void Electron::setMvaNonTrigV0eID(float mvaID) {
    mvaNonTrigV0 = mvaID;
}

bool Electron::isLoose() const {
    bool passesEt = et() > 20;
    bool passesEta = fabs(eta()) < 2.5;
		bool isolated = pfIsolationAeff() < 0.2;
		bool notInCrack = isInCrack() == false;
    bool passesID = false;
    if (electronIDUsed == eIDMethod::CIC)
       passesID = CIC_ElectronID(1);	// bitnum == 1 is LooseMC
    if (electronIDUsed == eIDMethod::MVA)
       passesID = mvaNonTrigV0eID() > 0;   // 
    else passesID = VBTF_W95_ElectronID();
    return passesEt && passesEta && isolated && notInCrack && passesID;

}

bool Electron::isGood(const float unused) const {
//    bool passesPt = pt() > 45.0;
    bool passesPt = pt() > 20.0;
    bool passesEta = fabs(eta()) < 2.5 && !isInCrack();

    bool passesD0 = false;
    if (usedAlgorithm == ElectronAlgorithm::Calo)
        passesD0 = fabs(d0_wrtBeamSpot()) < 0.02;//cm
    else
        // use d0 wrt primary vertex for
        passesD0 = fabs(d0()) < 0.02; //cm

    bool passesDistanceToPV = fabs(zDistanceToPrimaryVertex) < 0.1;
    bool passesID = false;
    if (electronIDUsed == eIDMethod::CIC)
         passesID = CIC_ElectronID();
    if (electronIDUsed == eIDMethod::MVA)
         passesID = mvaNonTrigV0eID() > 0;
    if( electronIDUsed == eIDMethod::VBTF )
         passesID = VBTF_W70_ElectronID();
    return passesPt && passesEta && passesD0 && passesID && passesDistanceToPV;
}

bool Electron::isQCDElectron(const float minEt) const {
    bool passesEt = et() > minEt;
    bool passesEta = fabs(eta()) < 2.5 && !isInCrack();

    bool passesD0 = false;
    if (usedAlgorithm == ElectronAlgorithm::Calo)
        passesD0 = fabs(d0_wrtBeamSpot()) < 0.02;//cm
    else
        passesD0 = fabs(d0()) < 0.02;//cm

    bool passesDistanceToPV = fabs(zDistanceToPrimaryVertex) < 0.1;
    bool passesID = QCD_AntiID_W70();
    return passesEt && passesEta && passesD0 && passesID && passesDistanceToPV;
}

bool Electron::isInBarrelRegion() const {
    return fabs(superClusterEta()) < 1.4442;
}

bool Electron::isInCrack() const {
    return !isInBarrelRegion() && !isInEndCapRegion();
}

bool Electron::isInEndCapRegion() const {
    return fabs(superClusterEta()) > 1.5660;
}

bool Electron::isFromConversion() const {
    return innerLayerMissingHits_ > 0;
}

bool Electron::isTaggedAsConversion(float maxDist, float maxDCotTheta) const {
    return fabs(distToNextTrack) < maxDist && fabs(dCotThetaToNextTrack) < maxDCotTheta;
}

float Electron::mvaTrigV0eID(void) const {
    return mvaTrigV0;
}

float Electron::mvaNonTrigV0eID(void) const {
    return mvaNonTrigV0;
}

bool Electron::CIC_ElectronID(unsigned short bitnum) const {
	int eidMask = 1 << bitnum;
	// We use "eidSuperTightMC", which is the 5th bit,
	// bitnum = 4, by default.  bitnum == 1 is LooseMC.

  // if ((cicEID & eidMask) == 0 && cicEID > eidMask)
		// cout << "mask eID " << eidMask << " " << cicEID << endl;

	return (cicEID & eidMask);
}

/* Electron ID cuts (without isolation) from:
 * https://twiki.cern.ch/twiki/bin/view/CMS/SimpleCutBasedEleID#Cuts_for_use_on_2010_data
 */

bool Electron::VBTF_W70_ElectronID() const {
    if (isInBarrelRegion())
        return getVBTF_W70_ElectronID_Barrel();
    else if (isInEndCapRegion())
        return getVBTF_W70_ElectronID_Endcap();
    else
        // in crack
        return false;
}
// Numbers in slide #7 of https://indico.cern.ch/getFile.py/access?subContId=0&contribId=0&resId=0&materialId=slides&confId=193787
//  or https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaCutBasedIdentification
bool Electron::getVBTF_W70_ElectronID_Barrel() const {
    bool passesSigmaIEta = sigma_IEtaIEta < 0.01;
    bool passesDPhiIn = fabs(dPhi_In) < 0.03;
    bool passesDEtaIn = fabs(dEta_In) < 0.004;
    bool passesHadOverEm = hadOverEm < 0.12;
    return passesSigmaIEta && passesDPhiIn && passesDEtaIn && passesHadOverEm;
}

bool Electron::getVBTF_W70_ElectronID_Endcap() const {
    bool passesSigmaIEta = sigma_IEtaIEta < 0.03;
    bool passesDPhiIn = fabs(dPhi_In) < 0.02;
    bool passesDEtaIn = fabs(dEta_In) < 0.005;
    // bool passesHadOverEm = hadOverEm < 0.025;
    bool passesHadOverEm = hadOverEm < 0.10; // Changed to .015 for 2011
    return passesSigmaIEta && passesDPhiIn && passesDEtaIn && passesHadOverEm;
}

bool Electron::VBTF_W95_ElectronID() const {
    if (isInBarrelRegion())
        return getVBTF_W95_ElectronID_Barrel();
    else if (isInEndCapRegion())
        return getVBTF_W95_ElectronID_Endcap();
    else
        // in crack
        return false;
}

// following is left unchanged since not used
bool Electron::getVBTF_W95_ElectronID_Barrel() const {
    bool passesSigmaIEta = sigma_IEtaIEta < 0.01;
    bool passesDPhiIn = fabs(dPhi_In) < 0.8;
    bool passesDEtaIn = fabs(dEta_In) < 0.007;
    bool passesHadOverEm = hadOverEm < 0.15;
    return passesSigmaIEta && passesDPhiIn && passesDEtaIn && passesHadOverEm;
}

bool Electron::getVBTF_W95_ElectronID_Endcap() const {
    bool passesSigmaIEta = sigma_IEtaIEta < 0.03;
    bool passesDPhiIn = fabs(dPhi_In) < 0.7;
    bool passesDEtaIn = fabs(dEta_In) < 0.01;
    bool passesHadOverEm = hadOverEm < 0.07;
    return passesSigmaIEta && passesDPhiIn && passesDEtaIn && passesHadOverEm;
}

bool Electron::QCD_AntiID_W70() const {
    if (isInBarrelRegion())
        return QCD_AntiID_W70_Barrel();
    else if (isInEndCapRegion())
        return QCD_AntiID_W70_Endcap();
    else
        return false;
}

bool Electron::QCD_AntiID_W70_Barrel() const {
    bool passesSigmaIEta = sigma_IEtaIEta < 0.01;
    bool passesDPhiIn = fabs(dPhi_In) > 0.03;
    bool passesDEtaIn = fabs(dEta_In) > 0.004;
    bool passesHadOverEm = hadOverEm < 0.25;
    return passesSigmaIEta && passesDPhiIn && passesDEtaIn && passesHadOverEm;
}

bool Electron::QCD_AntiID_W70_Endcap() const {
    bool passesSigmaIEta = sigma_IEtaIEta < 0.03;
    bool passesDPhiIn = fabs(dPhi_In) > 0.02;
    bool passesDEtaIn = fabs(dEta_In) > 0.005;
    bool passesHadOverEm = hadOverEm < 0.25;
    return passesSigmaIEta && passesDPhiIn && passesDEtaIn && passesHadOverEm;
}

float Electron::sigmaIEtaIEta() const {
    return sigma_IEtaIEta;
}

float Electron::dPhiIn() const {
    return dPhi_In;
}

float Electron::dEtaIn() const {
    return dEta_In;
}

float Electron::HadOverEm() const {
    return hadOverEm;
}

float Electron::HEEPet() const {
    return energy() * sin(fourvector.Theta());
}

bool Electron::RobustLooseID() const {
    return robustLooseId;
}

bool Electron::RobustTightID() const {
    return robustTightId;
}

void Electron::setNumberOfMissingInnerLayerHits(float missingHits) {
    innerLayerMissingHits_ = missingHits;
}

unsigned short Electron::getClosestJetIndex(const JetCollection& jets) const {
    unsigned short idOfClosest = 999;
    float closestDR = 999.;
    for (unsigned short index = 0; index < jets.size(); ++index) {
        float DR = deltaR(jets.at(index));
        if (DR < closestDR) {
            closestDR = DR;
            idOfClosest = index;
        }
    }
    return idOfClosest;
}

void Electron::setUsedAlgorithm(ElectronAlgorithm::value algo) {
    usedAlgorithm = algo;
}

void Electron::setEIDMethod(eIDMethod::value algo) {
    electronIDUsed= algo;
}

void Electron::setGSFTrack(const TrackPointer track) {
    gsfTrack = track;
}

const TrackPointer Electron::GSFTrack() const {
    return gsfTrack;
}

void Electron::setClosestTrackID(int trackID) {
    closesTrackID = trackID;
}

int Electron::closestCTFTrackID() const {
    return closesTrackID;
}

void Electron::setSharedFractionInnerHits(float hits) {
    sharedFractionInnerHits = hits;
}

float Electron::shFracInnerLayer() const {
    return sharedFractionInnerHits;
}

void Electron::setDistToNextTrack(float dist) {
    distToNextTrack = dist;
}

void Electron::setDCotThetaToNextTrack(float dCotTheta) {
    dCotThetaToNextTrack = dCotTheta;
}

bool Electron::isPFIsolated() const {
    return pfIsolationAeff() < 0.1;
}

bool Electron::isPFNonIsolated() const {
    return pfIsolationAeff() > 0.4;
}

bool Electron::isTrackerIsolated() const {
    return trackerIsolation() < 0.05;
}

bool Electron::isTrackerNonIsolated() const {
    return trackerIsolation() > 0.2;
}

ElectronAlgorithm::value Electron::algorithm() const {
    return usedAlgorithm;
}

float Electron::innerLayerMissingHits() const {
    return innerLayerMissingHits_;
}

float Electron::distToClosestTrack() const {
    return distToNextTrack;
}

float Electron::dCotThetaToClosestTrack() const {
    return dCotThetaToNextTrack;
}

}
