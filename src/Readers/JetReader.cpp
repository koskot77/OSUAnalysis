/*
 * JetReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */
 
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
 
#include "ProductArea/BNcollections/interface/BNjet.h"

#include "../../interface/Readers/JetReader.h"

namespace BAT {

JetReader::JetReader() :
    energyReader(),
    pxReader(),
    pyReader(),
    pzReader(),
    massReader(),
    chargeReader(),
    emfReader(),
    n90HitsReader(),
    partonFlavourReader(),
    fHPDReader(),
    NODReader(),
    CEFReader(),
    NHFReader(),
    NEFReader(),
    CHFReader(),
    NCHReader(),
    JECUncReader(),
    btagSimpleSecondaryVertexReader(),
    btagTrackCountingHighPurityReader(),
    btagTrackCountingHighEfficiencyReader(),
    btagCombinedSecondaryVertexReader(),
//    genEnergyReader(),
//    genPxReader(),
//    genPyReader(),
//    genPzReader(),
//    genMassReader(),
//    genChargeReader(),
//    genEmfReader(),
    jets(),
//    genJets(),
    usedAlgorithm(JetAlgorithm::Calo_AntiKT_Cone05) {

}
JetReader::JetReader(TChainPointer input, JetAlgorithm::value algo) :
    energyReader(input, JetAlgorithm::prefixes.at(algo) + ".Energy"),
    pxReader(input, JetAlgorithm::prefixes.at(algo) + ".Px"),
    pyReader(input, JetAlgorithm::prefixes.at(algo) + ".Py"),
    pzReader(input, JetAlgorithm::prefixes.at(algo) + ".Pz"),
    massReader(input, JetAlgorithm::prefixes.at(algo) + ".Mass"),
    chargeReader(input, JetAlgorithm::prefixes.at(algo) + ".Charge"),
    emfReader(input, JetAlgorithm::prefixes.at(algo) + ".EMF"),
    n90HitsReader(input, JetAlgorithm::prefixes.at(algo) + ".n90Hits"),
    partonFlavourReader(input, JetAlgorithm::prefixes.at(algo) + ".PartonFlavour"),
    fHPDReader(input, JetAlgorithm::prefixes.at(algo) + ".fHPD"),
    NODReader(input, JetAlgorithm::prefixes.at(algo) + ".NConstituents"),
    CEFReader(input, JetAlgorithm::prefixes.at(algo) + ".ChargedEmEnergyFraction"),
    NHFReader(input, JetAlgorithm::prefixes.at(algo) + ".NeutralHadronEnergyFraction"),
    NEFReader(input, JetAlgorithm::prefixes.at(algo) + ".NeutralEmEnergyFraction"),
    CHFReader(input, JetAlgorithm::prefixes.at(algo) + ".ChargedHadronEnergyFraction"),
    NCHReader(input, JetAlgorithm::prefixes.at(algo) + ".ChargedMultiplicity"),
    JECUncReader(input, JetAlgorithm::prefixes.at(algo) + ".JECUnc"),
    btagSimpleSecondaryVertexReader(input, JetAlgorithm::prefixes.at(algo) + ".SimpleSecondaryVertexHighEffBTag"),
    btagTrackCountingHighPurityReader(input, JetAlgorithm::prefixes.at(algo) + ".TrackCountingHighPurBTag"),
    btagTrackCountingHighEfficiencyReader(input, JetAlgorithm::prefixes.at(algo) + ".TrackCountingHighEffBTag"),
    btagCombinedSecondaryVertexReader(input, JetAlgorithm::prefixes.at(algo) + ".CombinedSecondaryVertexBJetTags"),
//    genEnergyReader(input, "GenJet.Energy"),
//    genPxReader(input, "GenJet.Px"),
//    genPyReader(input, "GenJet.Py"),
//    genPzReader(input, "GenJet.Pz"),
//    genMassReader(input, "GenJet.Mass"),
//    genChargeReader(input, "GenJet.Charge"),
//    genEmfReader(input, "GenJet.EMF"),
    jets(),
//    genJets(),
    usedAlgorithm(algo) {

}
JetReader::~JetReader() {
}

const JetCollection& JetReader::getJets(const fwlite::ChainEvent *const evtchain) {
	if (jets.empty() == false)
		jets.clear();
	readJets(evtchain);
	return jets;
}

//const JetCollection& JetReader::getGenJets() {
//	if (genJets.empty() == false)
//		genJets.clear();
//	readGenJets();
//	return genJets;
//}

void JetReader::readJets(const fwlite::ChainEvent *const evtchain) {
	fwlite::Handle<BNjetCollection> h_pfjets;
//	h_pfjets.getByLabel(*evtchain,"BNproducer","selectedPatJetsAK5PF");
	h_pfjets.getByLabel(*evtchain,"BNproducer","selectedPatJetsPFlow");
	for (unsigned int jetIndex = 0; jetIndex < h_pfjets->size(); jetIndex++) {
		const BNjet *const jetstruc = &h_pfjets->at(jetIndex);
		float energy = jetstruc->energy;
		float px = jetstruc->px;
		float py = jetstruc->py;
		float pz = jetstruc->pz;
		JetPointer jet(new Jet(energy, px, py, pz));
		jet->setUsedAlgorithm(usedAlgorithm);
		jet->setMass(jetstruc->mass);
		jet->setCharge(jetstruc->charge);
		jet->setGenJetPt(jetstruc->genJetPT);

		jet->setEMF(0);
		jet->setN90Hits(0);
		jet->setFHPD(0);

		jet->setDiscriminatorForBtagType(
				jetstruc->btagSecVertexHighEff,
				BtagAlgorithm::SimpleSecondaryVertexHighEffBTag);
		jet->setDiscriminatorForBtagType(
				jetstruc->btagTChighPur,
				BtagAlgorithm::TrackCountingHighPurBTag);
		jet->setDiscriminatorForBtagType(
				jetstruc->btagTChighEff,
				BtagAlgorithm::TrackCountingHighEffBTag);
                jet->setDiscriminatorForBtagType(
                                jetstruc->btagCombinedSecVertex,
                                BtagAlgorithm::CombinedSecondaryVertexBTag);

		if (usedAlgorithm == JetAlgorithm::PF2PAT) {
			jet->setNOD(jetstruc->nconstituents);
			jet->setCEF(jetstruc->chargedEmEnergyFraction);
			jet->setNHF(jetstruc->neutralHadronEnergyFraction);
			jet->setNEF(jetstruc->neutralEmEnergyFraction);
			jet->setCHF(jetstruc->chargedHadronEnergyFraction);
			jet->setNCH(jetstruc->chargedMultiplicity);
			jet->setPartonFlavour(jetstruc->flavour);
			jet->setJECUnc(jetstruc->JESunc);
                        // perform adjustment only for MC:
                        if( jetstruc->flavour!=0 ){
				jet->adjForRes();
				jet->adjForUnc();
                        }
		}
		jets.push_back(jet);
	}
}

//void JetReader::readGenJets() {
//	for (unsigned int jetIndex = 0; jetIndex < genEnergyReader.size(); jetIndex++) {
//		float energy = genEnergyReader.getVariableAt(jetIndex);
//		float px = genPxReader.getVariableAt(jetIndex);
//		float py = genPyReader.getVariableAt(jetIndex);
//		float pz = genPzReader.getVariableAt(jetIndex);
//		JetPointer jet(new Jet(energy, px, py, pz));
//
//		jet->setUsedAlgorithm(usedAlgorithm);
//		jet->setMass(genMassReader.getVariableAt(jetIndex));
//		jet->setCharge(genChargeReader.getVariableAt(jetIndex));
//		jet->setEMF(genEmfReader.getVariableAt(jetIndex));
//
//		genJets.push_back(jet);
//	}
//}

void JetReader::initialise() {
	/*
	energyReader.initialise();
	pxReader.initialise();
	pyReader.initialise();
	pzReader.initialise();
	massReader.initialise();
	chargeReader.initialise();
	partonFlavourReader.initialise();
	if (usedAlgorithm == JetAlgorithm::Calo_AntiKT_Cone05 ) {
		emfReader.initialise();
		n90HitsReader.initialise();
		fHPDReader.initialise();
	}
	btagSimpleSecondaryVertexReader.initialise();
	btagTrackCountingHighPurityReader.initialise();
	btagTrackCountingHighEfficiencyReader.initialise();
        btagCombinedSecondaryVertexReader.initialise();
	if (usedAlgorithm == JetAlgorithm::CA08PF || usedAlgorithm
			== JetAlgorithm::PF2PAT) {
		NODReader.initialise();
		CEFReader.initialise();
		NHFReader.initialise();
		NEFReader.initialise();
		CHFReader.initialise();
		NCHReader.initialise();
		JECUncReader.initialise();
	}
	*/

//	genEnergyReader.initialiseBlindly();
//	genPxReader.initialiseBlindly();
//	genPyReader.initialiseBlindly();
//	genPzReader.initialiseBlindly();
//	genMassReader.initialiseBlindly();
//	genEmfReader.initialiseBlindly();
//	genChargeReader.initialiseBlindly();
}
}
