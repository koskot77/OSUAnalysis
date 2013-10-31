/*
 * JetReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include <iostream>
 
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
 
#include "ProductArea/BNcollections/interface/BNgenjet.h"
 
#include "../../interface/Readers/GenJetReader.h"

using namespace std;

namespace BAT {

GenJetReader::GenJetReader() :
    genEnergyReader(),
    genPxReader(),
    genPyReader(),
    genPzReader(),
    genMassReader(),
    genChargeReader(),
    genEmfReader(),
    genJets() {

}
GenJetReader::GenJetReader(TChainPointer input) :
    genEnergyReader(input, "GenJet.Energy"),
    genPxReader(input, "GenJet.Px"),
    genPyReader(input, "GenJet.Py"),
    genPzReader(input, "GenJet.Pz"),
    genMassReader(input, "GenJet.Mass"),
    genChargeReader(input, "GenJet.Charge"),
    genEmfReader(input, "GenJet.EMF"),
    genJets() {

}
GenJetReader::~GenJetReader() {
}

const JetCollection& GenJetReader::getGenJets(
	const fwlite::ChainEvent *const evtchain) {
	if (genJets.empty() == false)
		genJets.clear();
	readGenJets(evtchain);
	return genJets;
}

void GenJetReader::readGenJets(const fwlite::ChainEvent *const evtchain) {
	fwlite::Handle<BNgenjetCollection> h_pfjets;
//	h_pfjets.getByLabel(*evtchain,"BNproducer","selectedPatJetsAK5PF");
	h_pfjets.getByLabel(*evtchain,"BNproducer","ak5GenJets");
	for (unsigned int jetIndex = 0; jetIndex < h_pfjets->size(); jetIndex++) {
		const BNgenjet *const jetstruc = &h_pfjets->at(jetIndex);
//		double energy = jetstruc->genJetET;
//		double pt = jetstruc->genJetPT;
//		double eta = jetstruc->genJetEta;
//		double phi = jetstruc->genJetPhi;
		double energy = jetstruc->et;
		double pt = jetstruc->pt;
		double eta = jetstruc->eta;
		double phi = jetstruc->phi;
		// float py = genPyReader.getVariableAt(jetIndex);
		// float pz = genPzReader.getVariableAt(jetIndex);
		if (energy > 0.0) {
			TLorentzVector jettmp;
			jettmp.SetPtEtaPhiE(pt, eta, phi, energy);
			// JetPointer jet(new Jet(energy, px, py, pz));
//			cout << "genjet vals e px py pz " << jettmp.Energy() << " ";
//			cout << jettmp.Px() << " " << jettmp.Py() << " ";
//			cout << jettmp.Pz() << endl;
			if (jettmp.Energy() > 0.0) {
				JetPointer jet(new Jet(jettmp.Energy(), jettmp.Px(), jettmp.Py(),
					jettmp.Pz()));
		
				jet->setUsedAlgorithm(JetAlgorithm::Calo_AntiKT_Cone05);
				// jet->setMass(genMassReader.getVariableAt(jetIndex));
				// jet->setCharge(genChargeReader.getVariableAt(jetIndex));
				// jet->setEMF(genEmfReader.getVariableAt(jetIndex));
		
				genJets.push_back(jet);
			}
		}
	}
}

void GenJetReader::initialise() {
	/*
	genEnergyReader.initialiseBlindly();
	genPxReader.initialiseBlindly();
	genPyReader.initialiseBlindly();
	genPzReader.initialiseBlindly();
	genMassReader.initialiseBlindly();
	genEmfReader.initialiseBlindly();
	genChargeReader.initialiseBlindly();
	*/
}
}
