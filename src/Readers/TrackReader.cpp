/*
 * TrackReader.cpp
 *
 *  Created on: 20 Sep 2010
 *      Author: kreczko
 */

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
 
#include "ProductArea/BNcollections/interface/BNtrack.h"


#include "../../interface/Readers/TrackReader.h"

namespace BAT {

TrackReader::TrackReader() :
    phiReader(),
    etaReader(),
    ptReader(),
    thetaReader(),
    chargeReader(),
    d0Reader(),
    highPurityReader() {

}

TrackReader::TrackReader(TChainPointer input) :
    phiReader(input, "Track.Phi"),
    etaReader(input, "Track.Eta"),
    ptReader(input, "Track.Pt"),
    thetaReader(input, "Track.Theta"),
    chargeReader(input, "Track.Charge"),
    d0Reader(input, "Track.D0"),
    highPurityReader(input, "Track.isHighPurity") {

}

TrackReader::~TrackReader() {
}

const TrackCollection& TrackReader::getTracks(
	const fwlite::ChainEvent *const evtchain) {
    if (tracks.empty() == false)
        tracks.clear();
    readTracks(evtchain);
    return tracks;
}

void TrackReader::readTracks(const fwlite::ChainEvent *const evtchain) {
	fwlite::Handle<BNtrackCollection> h_tracks;
	h_tracks.getByLabel(*evtchain,"BNproducer","generalTracks");
	for (unsigned int index = 0; index < h_tracks->size(); index++) {
		const BNtrack *const trackstruc = &h_tracks->at(index);
		float phi = trackstruc->phi;
		float eta = trackstruc->eta;
		float pt = trackstruc->pt;
		float theta = trackstruc->theta;
		TrackPointer track(new Track(phi, eta, pt, theta));
		track->setCharge(trackstruc->charge);
		track->setD0(trackstruc->d0);
		// track ->setHighPurity(highPurityReader.getBoolVariableAt(index) > 0);
		// BEAN creation applies scraping filter of high-purity tracks

		tracks.push_back(track);
	}
}

void TrackReader::initialise() {
	/*
    phiReader.initialise();
    etaReader.initialise();
    ptReader.initialise();
    thetaReader.initialise();
    chargeReader.initialise();
    d0Reader.initialise();
    highPurityReader.initialise();
    */
}

}
