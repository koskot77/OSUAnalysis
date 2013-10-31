/*
 * METReader.cpp
 *
 *  Created on: 4 Aug 2010
 *      Author: kreczko
 */

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
 
#include "ProductArea/BNcollections/interface/BNmet.h"


#include "../../interface/Readers/METReader.h"

namespace BAT {
//const std::string METReader::algorithmPrefixes[METAlgorithm::NUMBER_OF_METALGORITHMS] = {
//        "mets",
//        "tcmets",
//        "PFMets" };

METReader::METReader() :
    exReader(), eyReader(), met() {

}

METReader::METReader(TChainPointer input, METAlgorithm::value algo) :
    exReader(input, METAlgorithm::prefixes.at(algo) + ".Ex"),
    eyReader(input, METAlgorithm::prefixes.at(algo) + ".Ey") {

}

METReader::~METReader() {
}

void METReader::initialise() {
	/*
    exReader.initialise();
    eyReader.initialise();
    */
}

const METPointer METReader::getMET(const fwlite::ChainEvent *const evtchain) {
    readMET(evtchain);
    return met;
}

void METReader::readMET(const fwlite::ChainEvent *const evtchain) {
	fwlite::Handle<BNmetCollection> h_pfmet;
//	h_pfmet.getByLabel(*evtchain,"BNproducer","patMETsTypeIPF");
//	h_pfmet.getByLabel(*evtchain,"BNproducer","patMETsPFlow");
	h_pfmet.getByLabel(*evtchain,"BNproducer","pfType1CorrectedMetBN");
	const BNmet *const metstruc = &h_pfmet->at(0);
	met = METPointer(new MET(metstruc->px, metstruc->py));
}
}
