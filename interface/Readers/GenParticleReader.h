/*
 * GenParticleReader.h
 *
 *  Created on: Feb 23, 2011
 *      Author: phzss
 */

#ifndef GENPARTICLEREADER_H_
#define GENPARTICLEREADER_H_

#include "DataFormats/FWLite/interface/ChainEvent.h"

#include "../RecoObjects/MCParticle.h"
#include "VariableReader.h"

namespace BAT {

class GenParticleReader {
private:
    VariableReader<MultiDoublePointer> energyReader;
    VariableReader<MultiDoublePointer> pxReader;
    VariableReader<MultiDoublePointer> pyReader;
    VariableReader<MultiDoublePointer> pzReader;

    VariableReader<MultiIntPointer> pdgIdReader;
    VariableReader<MultiIntPointer> statusReader;
    VariableReader<MultiIntPointer> motherIndexReader;

    MCParticleCollection genParticles;
    void readGenParticles(const fwlite::ChainEvent *const evtchain);
public:
    GenParticleReader();
    GenParticleReader(TChainPointer input);
    virtual ~GenParticleReader();
    const MCParticleCollection& getGenParticles(
    	const fwlite::ChainEvent *const evtchain);
    void initialise();
};

}

#endif /* GENPARTICLEREADER_H_ */
