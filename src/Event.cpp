/*
 * Event.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../interface/Event.h"
#include <iostream>
using namespace std;

namespace BAT {

AdjWeight::AdjWeight() :
	baseWt(1),
	adjustedWt(1),
	afCount(0)
{}


AdjWeight::~AdjWeight() 
{}


AdjWeight& AdjWeight::operator=(double weight)
{
	baseWt = adjustedWt = weight;
	afCount = 0;
	return (*this);
}


AdjWeight::operator double() const
{
	return (adjustedWt);
}


void AdjWeight::adjWt(double scaleFac, const char *const key)
{
	for (unsigned int index = 0; index < afCount; ++index) {
		if (strcmp(appliedFactors[index], key) == 0)
			return;
	}
	adjustedWt *= scaleFac;
	(void) strcpy(appliedFactors[afCount], key);
	afCount++;
	if (afCount > 10)
		afCount = 10;		// Should never happen
}


void AdjWeight::reset()
{
  adjustedWt = baseWt;
	afCount = 0;
}


// Event class ********************

bool Event::useCustomConversionTagger = false;
bool Event::usePFIsolation = false;
Event::Event() :
    trigger(new Trigger()),
    vertices(),
    goodVertices(),
    tracks(),
    allElectrons(),
    goodElectrons(),
    goodIsolatedElectrons(),
    goodPFIsolatedElectrons(),
    looseElectrons(),
    qcdElectrons(),
    loosePFElectrons(),
    allJets(),
    genJets(),
    goodJets(),
    goodBJets(),
    allMuons(),
    goodMuons(),
    goodIsolatedMuons(),
    looseMuons(),
    tightMuons(),
    genParticles(),
    met(),
    dataType(DataType::DATA),
    runNumber(0),
    eventNumber(0),
    localEventNumber(0),
    lumiBlock(0),
    eventWeight(1.),
    jetCleaningEfficiency(1.),
    numberOfHighPurityTracks(0),
    isBeamScraping(true),
    genNumberOfPileUpVertices(0),
    trueNumberOfPileUpVertices(0),
    Q2ScaleUpWgt(1), Q2ScaleDownWgt(1){
}

Event::~Event() {
}

bool Event::isRealData() const {
    return dataType == DataType::DATA;
}

const DataType::value Event::getDataType() const {
    return dataType;
}

void Event::setDataType(DataType::value type) {
    dataType = type;
}

void Event::setVertices(VertexCollection vertices) {
    this->vertices.clear();
    this->vertices = vertices;

	selectVerticesByQuality();
}

void Event::selectVerticesByQuality() {
    goodVertices.clear();

    for (unsigned int i = 0; i < vertices.size(); ++i) {
        if (vertices.at(i)->isGood())
            goodVertices.push_back(vertices.at(i));
    }
}

void Event::setTracks(TrackCollection tracks) {
    this->tracks.clear();
    this->tracks = tracks;
    numberOfHighPurityTracks = 0;
    for (unsigned int index = 0; index < tracks.size(); ++index) {
        if (tracks.at(index)->isHighPurity())
            numberOfHighPurityTracks++;
    }
}

void Event::setGenParticles(MCParticleCollection genParticles) {
	this->genParticles = genParticles;
}

void Event::setElectrons(ElectronCollection electrons) {
    allElectrons.clear();
    allElectrons = electrons;
    selectElectronsByQuality();
}


void Event::setLoosePFElectrons(ElectronCollection electrons) {
    loosePFElectrons.clear();
    loosePFElectrons = electrons;
}


void Event::selectElectronsByQuality() {
    goodElectrons.clear();
    goodIsolatedElectrons.clear();
    goodPFIsolatedElectrons.clear();
    for (unsigned int index = 0; index < allElectrons.size(); ++index) {
        ElectronPointer electron = allElectrons.at(index);

        if (electron->isGood())
            goodElectrons.push_back(electron);

        if(electron->isQCDElectron(20) && (usePFIsolation ? electron->isPFNonIsolated() : electron->isTrackerNonIsolated()) )
            qcdElectrons.push_back(electron);

        if (electron->isGood() && (usePFIsolation ? electron->isPFIsolated() : electron->isTrackerIsolated()) )
            goodIsolatedElectrons.push_back(electron);

        if(electron->algorithm() == ElectronAlgorithm::ParticleFlow){
            if(electron->isGood() && (usePFIsolation ? electron->isPFIsolated() : electron->isTrackerIsolated()) )
                goodPFIsolatedElectrons.push_back(electron);
        }
        if (electron->isLoose())
            looseElectrons.push_back(electron);
    }
}

void Event::setJets(JetCollection jets) {
    allJets.clear();
    allJets = jets;
    selectGoodJets();
    cleanAllJets();
}

void Event::setGenJets(JetCollection jets) {
    genJets.clear();
    genJets = jets;
}


void Event::selectGoodJets() {
    goodJets.clear();
    for (unsigned int index = 0; index < allJets.size(); ++index) {
        const JetPointer jet = allJets.at(index);
        if (jet->isGood()) {
            goodJets.push_back(jet);
        }
    }
    cleanGoodJets();
    for (unsigned int index = 0; index < goodJets.size(); ++index) {
        const JetPointer jet = goodJets.at(index);
        if (jet->isBJet(BtagAlgorithm::CombinedSecondaryVertexBTag))
            goodBJets.push_back(jet);
    }
}

void Event::cleanGoodJets() {
    if (goodJets.size() > 0) {
			if (goodPFIsolatedElectrons.size() > 0)
					cleanGoodJetsAgainstIsolatedLeptons(goodPFIsolatedElectrons);
			if (goodIsolatedMuons.size() > 0)
				cleanGoodJetsAgainstIsolatedLeptons(goodIsolatedMuons);
		}
}

void Event::cleanAllJets() {
    if (allJets.size() > 0) {
			if (goodPFIsolatedElectrons.size() > 0)
					cleanAllJetsAgainstIsolatedLeptons(goodPFIsolatedElectrons);
			if (goodIsolatedMuons.size() > 0)
				cleanAllJetsAgainstIsolatedLeptons(goodIsolatedMuons);
		}
}

float Event::getJetCleaningEfficiency(void) const { return jetCleaningEfficiency; }

template <class PartColl> void Event::cleanGoodJetsAgainstIsolatedLeptons(const PartColl &leptonColl) {
    unsigned int initialGoodJets = goodJets.size();
    for (unsigned int jetIndex = 0; jetIndex < goodJets.size(); ++jetIndex) {
        for (unsigned int leptonIndex = 0; leptonIndex < leptonColl.size(); ++leptonIndex) {
            if (goodJets.at(jetIndex)->isWithinDeltaR(0.3, leptonColl.at(leptonIndex))) {
                goodJets.erase(goodJets.begin() + jetIndex);
                --jetIndex;
                break;
            }
        }
    }
    jetCleaningEfficiency = goodJets.size() / initialGoodJets;
}

void Event::cleanGoodJetsAgainstMostIsolatedElectron() {
    const ElectronPointer mostIsolatedElectron = MostIsolatedElectron(Event::usePFIsolation);
    unsigned int initialGoodJets = goodJets.size();
    for (unsigned int jetIndex = 0; jetIndex < goodJets.size(); ++jetIndex) {
        if (goodJets.at(jetIndex)->isWithinDeltaR(0.3, mostIsolatedElectron)) {
            goodJets.erase(goodJets.begin() + jetIndex);
            --jetIndex;
        }
    }
    jetCleaningEfficiency = goodJets.size() / initialGoodJets;
}

template <class PartColl> void Event::cleanAllJetsAgainstIsolatedLeptons(const PartColl &leptonColl) {
    unsigned int initialAllJets = allJets.size();
    for (unsigned int jetIndex = 0; jetIndex < allJets.size(); ++jetIndex) {
        for (unsigned int leptonIndex = 0; leptonIndex < leptonColl.size(); ++leptonIndex) {
            if (allJets.at(jetIndex)->isWithinDeltaR(0.3, leptonColl.at(leptonIndex))) {
                allJets.erase(allJets.begin() + jetIndex);
                --jetIndex;
                break;
            }
        }
    }
    jetCleaningEfficiency = allJets.size() / initialAllJets;
}

void Event::cleanAllJetsAgainstMostIsolatedElectron() {
    const ElectronPointer mostIsolatedElectron = MostIsolatedElectron(Event::usePFIsolation);
    unsigned int initialAllJets = allJets.size();
    for (unsigned int jetIndex = 0; jetIndex < allJets.size(); ++jetIndex) {
        if (allJets.at(jetIndex)->isWithinDeltaR(0.3, mostIsolatedElectron)) {
            allJets.erase(allJets.begin() + jetIndex);
            --jetIndex;
        }
    }
    jetCleaningEfficiency = allJets.size() / initialAllJets;
}



const ElectronPointer Event::MostIsolatedElectron(bool usePFIso) const {
    float bestIsolation = 999999999;
    unsigned int bestIsolatedElectron = 990;
    for (unsigned int index = 0; index < allElectrons.size(); ++index) {
        float currentIsolation = 999999999;
        if(usePFIso)
            currentIsolation = allElectrons.at(index)->pfIsolationAeff();
        else
            currentIsolation = allElectrons.at(index)->relativeIsolation();

        if (currentIsolation < bestIsolation) {
            bestIsolation = currentIsolation;
            bestIsolatedElectron = index;
        }
    }
    return allElectrons.at(bestIsolatedElectron);
}

const ElectronPointer Event::MostIsolatedElectron() const{
    return MostIsolatedElectron(false);
}

const ElectronPointer Event::MostPFIsolatedElectron() const{
    return MostIsolatedElectron(true);
}


void Event::setMuons(MuonCollection muons) {
    allMuons.clear();
    allMuons = muons;
    selectMuonsByQuality();
}

void Event::selectMuonsByQuality() {
    goodMuons.clear();
    goodIsolatedMuons.clear();
    for (unsigned int index = 0; index < allMuons.size(); ++index) {
        MuonPointer muon = allMuons.at(index);

        if (muon->isGood())
            goodMuons.push_back(muon);

        if (muon->isGood() && (usePFIsolation ? muon->isPFIsolated() : muon->isTrackerIsolated()) )
            goodIsolatedMuons.push_back(muon);

        if (muon->isLoose())
            looseMuons.push_back(muon);

        if (muon->isTight() && (usePFIsolation ? muon->isPFIsolated() : muon->isTrackerIsolated()) )
            tightMuons.push_back(muon);
    }
}

void Event::setHLT(const boost::shared_ptr<Trigger> trig){
    trigger = trig;
}

void Event::setPDFWts(const boost::shared_ptr<std::vector<double> > pdfWts){
    pdfWeights = pdfWts;
}


void Event::setMET(const METPointer met) {
    this->met = met;
    this->met->adjForUnc(allJets);
}

void Event::setRunNumber(unsigned long number) {
    runNumber = number;
}

void Event::setEventNumber(unsigned long number) {
    eventNumber = number;
}

void Event::setLocalEventNumber(unsigned long number) {
    localEventNumber = number;
}

void Event::setLumiBlock(unsigned long block) {
    lumiBlock = block;
}

void Event::setEventWeight(float weight) {
    eventWeight = weight;
}

void Event::setBeamScrapingVeto(bool isScraping){
    isBeamScraping = isScraping;
}

const VertexPointer Event::PrimaryVertex() const {
    return goodVertices.front();
}

const VertexCollection& Event::Vertices() const {
    return vertices;
}

const VertexCollection& Event::GoodVertices() const {
    return goodVertices;
}

const TrackCollection& Event::Tracks() const {
    return tracks;
}

const ElectronCollection& Event::Electrons() const {
    return allElectrons;
}

const ElectronCollection& Event::GoodElectrons() const {
    return goodElectrons;
}

const ElectronCollection& Event::GoodIsolatedElectrons() const {
    return goodIsolatedElectrons;
}

const ElectronCollection& Event::GoodPFIsolatedElectrons() const {
    return goodPFIsolatedElectrons;
}

const ElectronCollection& Event::QCDElectrons() const{
    return qcdElectrons;
}

const ElectronCollection& Event::LoosePFElectrons() const{
    return loosePFElectrons;
}

const ElectronCollection& Event::LooseElectrons() const{
    return looseElectrons;
}

const JetCollection& Event::Jets() const {
    return allJets;
}

const JetCollection& Event::GenJets() const {
    return genJets;
}


const JetCollection& Event::GoodJets() const {
    return goodJets;
}

const JetCollection& Event::GoodBJets() const {
    return goodBJets;
}

const MuonCollection& Event::Muons() const {
    return allMuons;
}

const MuonCollection& Event::GoodMuons() const {
    return goodMuons;
}

const MuonCollection& Event::TightMuons() const {
    return tightMuons;
}

const MuonCollection& Event::LooseMuons() const {
    return looseMuons;
}

const MuonCollection& Event::GoodIsolatedMuons() const {
    return goodIsolatedMuons;
}

const MCParticleCollection& Event::GenParticles() const {
	return genParticles;
}

const METPointer Event::MET() const {
    return met;
}

unsigned long Event::runnumber() const {
    return runNumber;
}

unsigned long Event::eventnumber() const {
    return eventNumber;
}

unsigned long Event::localnumber() const {
    return localEventNumber;
}

unsigned long Event::lumiblock() const {
    return lumiBlock;
}

float Event::weight() const {
    return eventWeight;
}

void Event::inspect() const {
    cout << "run " << runNumber << ", event number " << eventNumber << ", lumi section " << lumiBlock << endl;

    cout << "number of tracks: " << tracks.size() << endl;
    cout << "number of high purity tracks: " << numberOfHighPurityTracks << endl;

    cout << "number of jets: " << allJets.size() << endl;
    EventContentPrinter::printJets(allJets);
    cout << "number of good jets: " << goodJets.size() << endl;
    EventContentPrinter::printJets(goodJets);

    cout << "number of good isolated electrons: " << goodIsolatedElectrons.size() << endl;
    EventContentPrinter::printElectrons(goodIsolatedElectrons);

    cout << "number of good electrons: " << goodElectrons.size() << endl;
    EventContentPrinter::printElectrons(goodElectrons);

    cout << "number of electrons: " << allElectrons.size() << endl;
    EventContentPrinter::printElectrons(allElectrons);
}

const boost::shared_ptr<Trigger> Event::HLT(void) const { return trigger; }

double Event::pdfWt(unsigned int index) const {
		if (index >= pdfWeights->size()) {
				static bool showMsg = true;
				if (showMsg) {
					cout << "Seeking PDF weight # " << index << " but only ";
					cout << pdfWeights->size() << " weights in event\n";
					showMsg = false;
				}
				return 1.0;
		}
    return (pdfWeights->at(index));
}


void Event::setGenNumberOfPileUpVertices(unsigned int pileup){
    genNumberOfPileUpVertices = pileup;
}

float Event::numberOfGeneratedPileUpVertices() const{
    return genNumberOfPileUpVertices;
}


void Event::setTrueNumberOfPileUpVertices(unsigned int pileup){
    trueNumberOfPileUpVertices = pileup;
}

float Event::numberOfTruePileUpVertices() const{
    return trueNumberOfPileUpVertices;
}

void Event::setQ2Scales(double up, double down){
     Q2ScaleUpWgt   = up;
     Q2ScaleDownWgt = down;
}

double Event::getWeightQ2ScaleUp  (void) const { return Q2ScaleUpWgt;   }
double Event::getWeightQ2ScaleDown(void) const { return Q2ScaleDownWgt; }

}
