/*
 * ElectronReader.cpp
 *
 */
 
#include <iostream>

#include "ProductArea/BNcollections/interface/BNelectron.h"

#include "../../interface/Readers/ElectronReader.h"
#include "../../interface/Readers/NTupleEventReader.h"

using namespace std;

namespace BAT {

//const std::string ElectronReader::algorithmPrefixes[Electron::NUMBER_OF_ELECTRONALGORITHMS] = { "els", "PFElsAll" };

ElectronReader::ElectronReader() :
//    numberOfElectronsReader(),
    energyReader(),
    pxReader(),
    pyReader(),
    pzReader(),
    chargeReader(),
    superClusterEtaReader(),
    d0_BS_Reader(),
    d0_PV_Reader(),
    numberOfInnerLayerMissingHitsReader(),
    ecalIsolationReader(),
    hcalIsolationReader(),
    trackerIsolationReader(),
    PFGammaIsolationReader(),
    PFChargedHadronIsolationReader(),
    PFNeutralHadronIsolationReader(),
//    robustLooseIDReader(),
//    robustTightIDReader(),
    sigmaIEtaIEtaReader(),
    dPhiInReader(),
    dEtaInReader(),
    hadOverEmReader(),
    sharedFractionInnerHits(),
    trackIDReader(),
    track_phi(),
    track_eta(),
    track_pt(),
    track_theta(),
    track_charge(),
    vertex_dist_xy(),
    vertex_dist_z(),
    dist(),
    dCotTheta(),
    cicEID(),
    mvaTrigV0(),
    mvaNonTrigV0(),
    algorithm(ElectronAlgorithm::Calo),
    electrons() {

}

ElectronReader::ElectronReader(TChainPointer input, ElectronAlgorithm::value algo) :
//    numberOfElectronsReader(input, "N" + ElectronAlgorithm::prefixes.at(algo)),
    energyReader(input, ElectronAlgorithm::prefixes.at(algo) + ".Energy"),
    pxReader(input, ElectronAlgorithm::prefixes.at(algo) + ".Px"),
    pyReader(input, ElectronAlgorithm::prefixes.at(algo) + ".Py"),
    pzReader(input, ElectronAlgorithm::prefixes.at(algo) + ".Pz"),
    chargeReader(input, ElectronAlgorithm::prefixes.at(algo) + ".Charge"),
    superClusterEtaReader(input, ElectronAlgorithm::prefixes.at(algo) + ".SCEta"),
    d0_BS_Reader(input, ElectronAlgorithm::prefixes.at(algo) + ".dBBS"),
    d0_PV_Reader(input, ElectronAlgorithm::prefixes.at(algo) + ".dB"),
    numberOfInnerLayerMissingHitsReader(input, ElectronAlgorithm::prefixes.at(algo) + ".MissingHits"),
    ecalIsolationReader(input, ElectronAlgorithm::prefixes.at(algo) + ".EcalIso03"),
    hcalIsolationReader(input, ElectronAlgorithm::prefixes.at(algo) + ".HcalIso03"),
    trackerIsolationReader(input,ElectronAlgorithm::prefixes.at(algo) + ".TrkIso03"),
    PFGammaIsolationReader(input,ElectronAlgorithm::prefixes.at(algo) + ".PFGammaIso"),
    PFChargedHadronIsolationReader(input,ElectronAlgorithm::prefixes.at(algo) + ".PfChargedHadronIso"),
    PFNeutralHadronIsolationReader(input,ElectronAlgorithm::prefixes.at(algo) + ".PfNeutralHadronIso"),
//    robustLooseIDReader(input, ElectronAlgorithm::prefixes.at(algo) + ".robustLooseId"),
//    robustTightIDReader(input, ElectronAlgorithm::prefixes.at(algo) + ".robustTightId"),
    sigmaIEtaIEtaReader(input, ElectronAlgorithm::prefixes.at(algo) + ".SigmaIEtaIEta"),
    dPhiInReader(input, ElectronAlgorithm::prefixes.at(algo) + ".DeltaPhiTrkSC"),
    dEtaInReader(input, ElectronAlgorithm::prefixes.at(algo) + ".DeltaEtaTrkSC"),
    hadOverEmReader(input, ElectronAlgorithm::prefixes.at(algo) + ".HoE"),
    sharedFractionInnerHits(input, ElectronAlgorithm::prefixes.at(algo) + ".shFracInnerHits"),
    trackIDReader(input, ElectronAlgorithm::prefixes.at(algo) + ".closestCtfTrackRef"),
    track_phi(input, ElectronAlgorithm::prefixes.at(algo) + ".GSFTrack.Phi"),
    track_eta(input, ElectronAlgorithm::prefixes.at(algo) + ".GSFTrack.Eta"),
    track_pt(input, ElectronAlgorithm::prefixes.at(algo) + ".GSFTrack.Pt"),
    track_theta(input, ElectronAlgorithm::prefixes.at(algo) + ".GSFTrack.Theta"),
    track_charge(input, ElectronAlgorithm::prefixes.at(algo) + ".GSFTrack.Charge"),
    vertex_dist_xy(input, ElectronAlgorithm::prefixes.at(algo) + ".VtxDistXY"),
    vertex_dist_z(input, ElectronAlgorithm::prefixes.at(algo) + ".VtxDistZ"),
    dist(input, ElectronAlgorithm::prefixes.at(algo) + ".Dist"),
    dCotTheta(input, ElectronAlgorithm::prefixes.at(algo) + ".DCotTheta"),
    cicEID(input, ElectronAlgorithm::prefixes.at(algo) + ".CICeID"),
    mvaTrigV0(input, ElectronAlgorithm::prefixes.at(algo) + ".MvaTrigV0"),
    mvaNonTrigV0(input, ElectronAlgorithm::prefixes.at(algo) + ".MvaNonTrigV0"),
    algorithm(algo),
    electrons() {

}

ElectronReader::~ElectronReader() {
}

const ElectronCollection& ElectronReader::getElectrons(const fwlite::ChainEvent *const evtchain) {
    if (electrons.empty() == false)
        electrons.clear();
    readElectrons(evtchain);
    return electrons;
}

void ElectronReader::readElectrons(const fwlite::ChainEvent *const evtchain) {
		fwlite::Handle<BNelectronCollection> h_electrons;
///		h_electrons.getByLabel(*evtchain, "BNproducer", "selectedPatElectronsPFlow");
		h_electrons.getByLabel(*evtchain, "BNproducer", "selectedPatElectronsLoosePFlow");
    for (unsigned int index = 0; index < h_electrons->size(); index++) {
    		const BNelectron *const elecstruc = &h_electrons->at(index);
        float energy = elecstruc->energy;
        float px = elecstruc->px;
        float py = elecstruc->py;
        float pz = elecstruc->pz;
//elecstruc->numberOfLostHits
        ElectronPointer electron(new Electron(energy, px, py, pz));
        electron->setUsedAlgorithm(algorithm);
        electron->setEIDMethod(NTupleEventReader::electronIDUsed);
        electron->setCharge(elecstruc->charge);
        electron->setD0(elecstruc->correctedD0Vertex);
        //electron->setXyDistanceToPrimaryVertex(vertex_dist_xy.getVariableAt(index));
        electron->setZDistanceToPrimaryVertex(elecstruc->correctedDZ);     
        electron->setNumberOfMissingInnerLayerHits(elecstruc->numberOfExpectedInnerHits);

        electron->setEcalIsolation(elecstruc->ecalIsoDR03);
        electron->setHcalIsolation(elecstruc->hcalIsoDR03);
        electron->setTrackerIsolation(elecstruc->trackIsoDR03);
//      new PF PileUp isolation components:
        electron->setEcalIsolation(elecstruc->photonIsoDR03);
        electron->setHcalIsolation(elecstruc->neutralHadronIsoDR03);
        electron->setTrackerIsolation(elecstruc->chargedHadronIsoDR03);
        electron->setPFChargedPUinIsoCone(elecstruc->puChargedHadronIsoDR03);
        electron->setPFEventEnergyDensity(elecstruc->rhoPrime);
        electron->setEffectiveArea(elecstruc->AEffDr03);

        electron->setSuperClusterEta(elecstruc->scEta);
        //electron->setSigmaIEtaIEta(sigmaIEtaIEtaReader.getVariableAt(index));
        // iEtaiEta used only for obsolete VTBF electron ID
        electron->setDPhiIn(elecstruc->delPhiIn);
        electron->setDEtaIn(elecstruc->delEtaIn);
        electron->setHadOverEm(elecstruc->hadOverEm);
        electron->setDistToNextTrack(elecstruc->dist);
        electron->setDCotThetaToNextTrack(elecstruc->dcot);
        // electron->setCICeID(cicEID.getIntVariableAt(index));
        // CIC is obsolete for 2012
        electron->setMvaTrigV0eID(elecstruc->mvaTrigV0);
        electron->setMvaNonTrigV0eID(elecstruc->mvaNonTrigV0);

        //electron->setSharedFractionInnerHits(sharedFractionInnerHits.getVariableAt(index));
        // not used
        //electron->setClosestTrackID(trackIDReader.getIntVariableAt(index));
        // Needed for conversion tagging, which is not used
        float trackPhi = elecstruc->tkPhi;
        float trackEta = elecstruc->tkEta;
        float trackPt = elecstruc->tkPT;
        // float trackTheta = elecstruc->tkPhi;
        // Not available in BEAN, not really necessary
        float trackCharge = elecstruc->gsfCharge;
        TrackPointer track = TrackPointer(new Track(trackPhi, trackEta,
        	trackPt, 0.0)); // trackTheta was last param, but not needed
        track->setCharge(trackCharge);
        track->setD0(electron->d0());
        if(algorithm != ElectronAlgorithm::Calo){
            electron->setPFGammaIsolation(elecstruc->photonIso);
            electron->setPFChargedHadronIsolation(elecstruc->chargedHadronIso);
            electron->setPFNeutralHadronIsolation(elecstruc->neutralHadronIso);
        }
        electron->setGSFTrack(track);
        electrons.push_back(electron);
    }
}

void ElectronReader::initialise() {
    /*
		energyReader.initialise();
    pxReader.initialise();
    pyReader.initialise();
    pzReader.initialise();
    chargeReader.initialise();
    superClusterEtaReader.initialise();

    if(d0_BS_Reader.doesVariableExist() && algorithm == ElectronAlgorithm::Calo)
        d0_BS_Reader.initialise();
    d0_PV_Reader.initialise();
    numberOfInnerLayerMissingHitsReader.initialise();

    ecalIsolationReader.initialise();
    hcalIsolationReader.initialise();
    trackerIsolationReader.initialise();

//    robustLooseIDReader.initialise();
//    robustTightIDReader.initialise();
    sigmaIEtaIEtaReader.initialise();
    dPhiInReader.initialise();
    dEtaInReader.initialise();
    hadOverEmReader.initialise();

    sharedFractionInnerHits.initialise();
    trackIDReader.initialise();
    track_phi.initialise();
    track_eta.initialise();
    track_pt.initialise();
    track_theta.initialise();
    track_charge.initialise();
    vertex_dist_xy.initialise();
    vertex_dist_z.initialise();
    dist.initialise();
    dCotTheta.initialise();
    cicEID.initialise();
    mvaTrigV0.initialise();
    mvaNonTrigV0.initialise();
    if(algorithm != ElectronAlgorithm::Calo){
        PFGammaIsolationReader.initialise();
        PFChargedHadronIsolationReader.initialise();
        PFNeutralHadronIsolationReader.initialise();
    }
    */
}

}

