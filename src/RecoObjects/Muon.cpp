/*
 * Muon.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/Muon.h"

namespace BAT {

Muon::Muon() :
	Lepton(), is_Global(false), is_Tracker(false), is_PFMuon(false), ecal_Isolation(0.), hcal_Isolation(0), tracker_Isolation(0), effectiveArea(0),
        normalizedChi2(0), numberOfValidMuonHits(0),  numberOfMatchedStations(0), numberOfValidPixelHits(0), trackerLayersWithMeasurement(0)
{

}

Muon::Muon(float energy, float px, float py, float pz) :
	Lepton(energy, px, py, pz), is_Global(false), is_Tracker(false), is_PFMuon(false), ecal_Isolation(0.), hcal_Isolation(0), tracker_Isolation(0), effectiveArea(0),
        normalizedChi2(0), numberOfValidMuonHits(0),  numberOfMatchedStations(0), numberOfValidPixelHits(0), trackerLayersWithMeasurement(0)
{

}

Muon::~Muon() {
}

bool Muon::isGlobal() const {
	return is_Global;
}

bool Muon::isPFMuon() const {
	return is_PFMuon;
}

bool Muon::isTracker() const {
	return is_Tracker;
}

void Muon::makeGlobal(bool global) {
	is_Global = global;
}

void Muon::makePFMuon(bool pf) {
	is_PFMuon = pf;
}

void Muon::makeTracker(bool tracker) {
	is_Tracker = tracker;
}

float Muon::ecalIsolation() const {
	return ecal_Isolation;
}

void Muon::setEcalIsolation(float isolation) {
	ecal_Isolation = isolation;
}

float Muon::hcalIsolation() const {
	return hcal_Isolation;
}

void Muon::setHcalIsolation(float isolation) {
	hcal_Isolation = isolation;
}

float Muon::trackerIsolation() const {
	return tracker_Isolation;
}

void Muon::setTrackerIsolation(float isolation) {
	tracker_Isolation = isolation;
}

void Muon::setNormalizedChi2(double chi2){
        normalizedChi2 = chi2;
}
void Muon::setNumberOfValidMuonHits(int nHits){
        numberOfValidMuonHits = nHits;
}
void Muon::setNumberOfMatchedStations(int nStations){
        numberOfMatchedStations = nStations;
}
void Muon::setNumberOfValidPixelHits(int nPixelHits){
        numberOfValidPixelHits = nPixelHits;
}
void Muon::setNtrackerLayersWithMeasurement(int trkLayers){
        trackerLayersWithMeasurement = trkLayers;
}
void Muon::setEffectiveArea(float effArea){
        effectiveArea = effArea;
}
float Muon::Aeff() const {
        return effectiveArea;
}
float Muon::relativeIsolation() const {
	return (ecal_Isolation + hcal_Isolation + tracker_Isolation) / pt();
}

bool Muon::isTrackerIsolated() const{
	return trackerIsolation() < 0.05;
}

bool Muon::isPFIsolated() const{
	return pfIsolationDeltaBeta() < 0.12;
}

// https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Accessing_PF_Isolation_from_reco
//float Muon::pfIsolationDeltaBeta() const {
//    return (PFChargedHadron_Isolation + std::max(0.0, PFGamma_Isolation + PFNeutralHadron_Isolation - 0.5*PFsumPUPt) ) / pt();
//}
float Muon::pfIsolationDeltaBeta() const {
    return (tracker_Isolation + std::max(float(0.0), ecal_Isolation + hcal_Isolation - float(0.5)*PFsumPUPt) ) / pt();
}

// https://twiki.cern.ch/twiki/bin/view/CMS/EgammaEARhoCorrection#Isolation_cone_R_0_4
float Muon::pfIsolationAeff() const {
    return (PFChargedHadron_Isolation + std::max(float(0), PFGamma_Isolation + PFNeutralHadron_Isolation - PFrho * effectiveArea) ) / pt();
}

bool Muon::isGood() const{
	// bool passesPt = pt() > 35;
//	bool passesPt = pt() > 42;	// For use wth HLT_Mu40...
	bool passesPt = pt() > 20;	// For use wth HLT_Mu40...
	bool passesEta = fabs(eta()) < 2.1;

	bool passesD0 = fabs(d0()) < 0.02; //cm

	bool passesDistanceToPV = fabs(zDistanceToPrimaryVertex) < 1.0;
	return passesPt && passesEta && passesD0 && passesDistanceToPV && is_Global;
}

bool Muon::isTight() const{
// https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Basline_muon_selections_for_2012
        bool passesChi2              = normalizedChi2 < 10;
        bool passesD0                = fabs(d0()) < 0.2;
        bool passesDZ                = fabs(ZDistanceToPrimaryVertex()) < 0.5;
        bool passesMuonHits          = numberOfValidMuonHits > 0;
        bool passesMatchedStations   = numberOfMatchedStations > 1;
        bool passesPixelHits         = numberOfValidPixelHits > 0;
        bool passesLayers            = trackerLayersWithMeasurement > 5;
        return is_Global && is_PFMuon && passesChi2 && passesD0 && passesDZ &&
               passesMuonHits && passesMatchedStations && passesPixelHits && passesLayers;
}

bool Muon::isLoose() const {
    bool passesPt = pt() > 10;
    bool passesEta = fabs(eta()) < 2.5;
    bool looseisolated = pfIsolationDeltaBeta() < 0.2;
//    bool looseisolated = trackerIsolation() < 0.1;
    return passesPt && passesEta && looseisolated && (is_Global || is_Tracker);

}

}
