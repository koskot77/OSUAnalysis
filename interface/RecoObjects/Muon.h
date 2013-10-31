/*
 * Muon.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef MUON_H_
#define MUON_H_
#include "Lepton.h"
#include <vector>
#include <string>
#include <boost/array.hpp>

namespace BAT {

namespace MuonAlgorithm {
enum value {
    Default,
    ParticleFlow,
    PFBEANMuon,
    NUMBER_OF_MUONALGORITHMS
};

const boost::array<std::string, MuonAlgorithm::NUMBER_OF_MUONALGORITHMS> prefixes = { {
        "selectedPatMuonsLoosePFlow",
        "selectedPatMuonsPFlow",
        "selectedPatMuonsPF"
				} };

const boost::array<std::string, MuonAlgorithm::NUMBER_OF_MUONALGORITHMS> names = { {
        "Muon",
        "PFMuon",
        "PFBEANMuon"
				} };
}


class Muon: public Lepton {
public:
	Muon();
	Muon(float energy, float px, float py, float pz);
	virtual ~Muon();
	bool isGood() const;
	bool isPFIsolated() const;
	bool isTrackerIsolated() const;
	bool isTracker() const;
	bool isGlobal() const;
	bool isPFMuon() const;
	bool isLoose() const;
	bool isTight() const;
	float ecalIsolation() const;
	float hcalIsolation() const;
	float trackerIsolation() const;
	float relativeIsolation() const;
        float pfIsolationDeltaBeta() const;
        float pfIsolationAeff() const;
        float Aeff() const;

	void makeGlobal(bool global);
	void makePFMuon(bool pf);
	void makeTracker(bool itracker);
	void setEcalIsolation(float isolation);
	void setHcalIsolation(float isolation);
	void setTrackerIsolation(float isolation);
        void setEffectiveArea(float effArea);

        void setNormalizedChi2(double chi2);
        void setNumberOfValidMuonHits(int nHits);
        void setNumberOfMatchedStations(int nStations);
        void setNumberOfValidPixelHits(int nPixelHits);
        void setNtrackerLayersWithMeasurement(int trkLayers);
private:
	bool is_Global, is_Tracker, is_PFMuon;
	float ecal_Isolation, hcal_Isolation, tracker_Isolation, effectiveArea;

        // for the tight selection:
        double normalizedChi2;
        int numberOfValidMuonHits,  numberOfMatchedStations;
        int numberOfValidPixelHits, trackerLayersWithMeasurement;
};

typedef boost::shared_ptr<Muon> MuonPointer;
typedef std::vector<MuonPointer> MuonCollection;
}

#endif /* MUON_H_ */
