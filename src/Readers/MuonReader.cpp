/*
 * MuonReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */
 
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
 
#include "ProductArea/BNcollections/interface/BNmuon.h"

#include "../../interface/Readers/MuonReader.h"

namespace BAT {

MuonReader::MuonReader() :
//	numberOfMuonsReader(),
	energyReader(),
	pxReader(),
	pyReader(),
	pzReader(),
	chargeReader(),
	ecalIsolationReader(),
	hcalIsolationReader(),
	trackerIsolationReader(),
	vertex_dist_xy(),
	vertex_dist_z(),
	PFGammaIsolationReader(),
	PFChargedHadronIsolationReader(),
	PFNeutralHadronIsolationReader(),
	d0_PV_Reader(),
	isGlobalReader() {

}

MuonReader::MuonReader(TChainPointer input, MuonAlgorithm::value algo) :
	energyReader(input, MuonAlgorithm::prefixes.at(algo) + ".Energy"),
	pxReader(input, MuonAlgorithm::prefixes.at(algo) + ".Px"),
	pyReader(input, MuonAlgorithm::prefixes.at(algo) + ".Py"),
	pzReader(input, MuonAlgorithm::prefixes.at(algo) + ".Pz"),
	chargeReader(input, MuonAlgorithm::prefixes.at(algo) + ".Charge"),
	ecalIsolationReader(input, MuonAlgorithm::prefixes.at(algo) + ".EcalIso03"),
	hcalIsolationReader(input, MuonAlgorithm::prefixes.at(algo) + ".HcalIso03"),
	trackerIsolationReader(input, MuonAlgorithm::prefixes.at(algo) + ".TrkIso03"),
	vertex_dist_xy(input, MuonAlgorithm::prefixes.at(algo) + ".VtxDistXY"),
	vertex_dist_z(input, MuonAlgorithm::prefixes.at(algo) + ".VtxDistZ"),
	PFGammaIsolationReader(input,MuonAlgorithm::prefixes.at(algo) + ".PFGammaIso"),
	PFChargedHadronIsolationReader(input,MuonAlgorithm::prefixes.at(algo) + ".PfChargedHadronIso"),
	PFNeutralHadronIsolationReader(input,MuonAlgorithm::prefixes.at(algo) + ".PfNeutralHadronIso"),
	d0_PV_Reader(input, MuonAlgorithm::prefixes.at(algo) + ".dB"),
	isGlobalReader(input, MuonAlgorithm::prefixes.at(algo) + ".isGoodGlobalMuon") {

}

void MuonReader::initialise() {
	/*
    energyReader.initialise();
    pxReader.initialise();
    pyReader.initialise();
    pzReader.initialise();
    chargeReader.initialise();

    ecalIsolationReader.initialise();
    hcalIsolationReader.initialise();
    trackerIsolationReader.initialise();

    isGlobalReader.initialise();
    d0_PV_Reader.initialise();
		PFGammaIsolationReader.initialise();
		PFChargedHadronIsolationReader.initialise();
		PFNeutralHadronIsolationReader.initialise();
    vertex_dist_xy.initialise();
    vertex_dist_z.initialise();
    */
}

const MuonCollection& MuonReader::getMuons(
	const fwlite::ChainEvent *const evtchain) {
    if (muons.empty() == false)
        muons.clear();
    readMuons(evtchain);
    return muons;
}

void MuonReader::readMuons(const fwlite::ChainEvent *const evtchain) {
		fwlite::Handle<BNmuonCollection> h_muons;
///		h_muons.getByLabel(*evtchain, "BNproducer", "selectedPatMuonsPFlow");
		h_muons.getByLabel(*evtchain, "BNproducer", "selectedPatMuonsLoosePFlow");
    for (unsigned int index = 0; index < h_muons->size(); index++) {
    		const BNmuon *const mustruc = &h_muons->at(index);
        float energy = mustruc->energy;
        float px = mustruc->px;
        float py = mustruc->py;
        float pz = mustruc->pz;
        MuonPointer muon(new Muon(energy, px, py, pz));
        muon->setCharge(mustruc->charge);
        muon->setEcalIsolation(mustruc->ecalIso);
        muon->setHcalIsolation(mustruc->hcalIso);
        muon->setTrackerIsolation(mustruc->trackIso);

        // new PU corrected isolation components
        muon->setEcalIsolation(mustruc->pfIsoR04SumPhotonEt);
        muon->setHcalIsolation(mustruc->pfIsoR04SumNeutralHadronEt);
        muon->setTrackerIsolation(mustruc->pfIsoR04SumChargedHadronPt);
        muon->setPFChargedPUinIsoCone(mustruc->pfIsoR04SumPUPt);
        muon->setPFEventEnergyDensity(mustruc->rhoPrime);
        muon->setEffectiveArea(mustruc->AEffDr04);

        muon->makeGlobal(mustruc->isGlobalMuon);
        muon->makePFMuon(mustruc->isPFMuon);
        muon->makeTracker(mustruc->isTrackerMuon);
        muon->setD0(mustruc->correctedD0Vertex);
        //muon->setXyDistanceToPrimaryVertex(vertex_dist_xy.getVariableAt(index));
        muon->setZDistanceToPrimaryVertex(mustruc->correctedDZ);
				muon->setPFGammaIsolation(mustruc->photonIso);
				muon->setPFChargedHadronIsolation(mustruc->chargedHadronIso);
				muon->setPFNeutralHadronIsolation(mustruc->neutralHadronIso);
        muon->setNormalizedChi2(mustruc->normalizedChi2);
        muon->setNumberOfValidMuonHits(mustruc->numberOfValidMuonHits);
        muon->setNumberOfMatchedStations(mustruc->numberOfMatchedStations);
        muon->setNumberOfValidPixelHits(mustruc->numberOfValidPixelHits);
        muon->setNtrackerLayersWithMeasurement(mustruc->numberOfLayersWithMeasurement);

        muons.push_back(muon);
    }
}
MuonReader::~MuonReader() {
}

}
