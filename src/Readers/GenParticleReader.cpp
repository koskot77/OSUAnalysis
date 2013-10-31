/*
 * GenParticleReader.cpp
 *
 *  Created on: Feb 23, 2011
 *      Author: phzss
 */

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
 
#include "ProductArea/BNcollections/interface/BNmcparticle.h"

#include "../../interface/Readers/GenParticleReader.h"
namespace BAT {

GenParticleReader::GenParticleReader() :
    energyReader(),
	pxReader(),
	pyReader(),
	pzReader(),
	pdgIdReader(),
	statusReader(),
	motherIndexReader() {

}

GenParticleReader::GenParticleReader(TChainPointer input) :
    energyReader(input, "GenParticle.Energy"),
    pxReader(input, "GenParticle.Px"),
    pyReader(input, "GenParticle.Py"),
    pzReader(input, "GenParticle.Pz"),
    pdgIdReader(input, "GenParticle.PdgId"),
    statusReader(input, "GenParticle.Status"),
    motherIndexReader(input, "GenParticle.MotherIndex") {

}


GenParticleReader::~GenParticleReader() {
}

const MCParticleCollection& GenParticleReader::getGenParticles(
	const fwlite::ChainEvent *const evtchain) {
    if (genParticles.empty() == false)
        genParticles.clear();
    readGenParticles(evtchain);
    return genParticles;
}

void GenParticleReader::readGenParticles(
	const fwlite::ChainEvent *const evtchain) {
	fwlite::Handle<BNmcparticleCollection> h_mcparticles;
	h_mcparticles.getByLabel(*evtchain,"BNproducer","MCstatus3");
	for (unsigned int index = 0; index < h_mcparticles->size(); index++) {
		const BNmcparticle *const genpstruc = &h_mcparticles->at(index);
		float energy = genpstruc->energy;
		float px = genpstruc->px;
		float py = genpstruc->py;
		float pz = genpstruc->pz;


		int pdgId = genpstruc->id;
		int status = genpstruc->status;
		int motherId = genpstruc->motherId;
		int grandMotherId = genpstruc->grandMotherId;

		MCParticlePointer genParticle(new MCParticle(energy, px, py, pz));
		genParticle->setPdgId(pdgId);
		genParticle->setStatus(status);
		genParticle->setMotherId(motherId);
		genParticle->setGrandMotherId(grandMotherId);

		genParticles.push_back(genParticle);
	}
}


void GenParticleReader::initialise() {
	/*
    energyReader.initialiseBlindly();
	pxReader.initialiseBlindly();
    pyReader.initialiseBlindly();
    pzReader.initialiseBlindly();

    pdgIdReader.initialiseBlindly();
    statusReader.initialiseBlindly();
    motherIndexReader.initialiseBlindly();
    */
}

}
