/*
 * TrackReader.h
 *
 *  Created on: 20 Sep 2010
 *      Author: kreczko
 */

#ifndef TRACKREADER_H_
#define TRACKREADER_H_

#include "DataFormats/FWLite/interface/ChainEvent.h"

#include "../RecoObjects/Track.h"
#include "VariableReader.h"

namespace BAT {

class TrackReader {
private:
    VariableReader<MultiDoublePointer> phiReader;
    VariableReader<MultiDoublePointer> etaReader;
    VariableReader<MultiDoublePointer> ptReader;
    VariableReader<MultiDoublePointer> thetaReader;
    VariableReader<MultiIntPointer> chargeReader;
    VariableReader<MultiDoublePointer> d0Reader;
    VariableReader<MultiBoolPointer> highPurityReader;

    TrackCollection tracks;
    void readTracks(const fwlite::ChainEvent *const evtchain);
public:
    TrackReader();
    TrackReader(TChainPointer input);
    virtual ~TrackReader();
    const TrackCollection& getTracks(const fwlite::ChainEvent *const evtchain);
    void initialise();
};

}

#endif /* TRACKREADER_H_ */
