/*
 * Event.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef EVENT_H_
#define EVENT_H_
#include "RecoObjects/Electron.h"
#include "RecoObjects/Jet.h"
#include "RecoObjects/Muon.h"
#include "RecoObjects/Vertex.h"
#include "RecoObjects/MET.h"
#include "RecoObjects/MCParticle.h"
#include "DataTypes.h"
#include "Printers/EventContentPrinter.h"
#include "Trigger.h"

#include <map>

namespace BAT {


class AdjWeight {
public:
	AdjWeight();
	virtual ~AdjWeight();
	AdjWeight& operator=(double weight);
	operator double() const;
	void adjWt(double scaleFac, const char *const key);
	void reset();

protected:
	double baseWt, adjustedWt;
	char appliedFactors[10][10];
	unsigned int afCount;
};


class Event {
protected:
    boost::shared_ptr<Trigger> trigger;

    VertexCollection vertices;
    VertexCollection goodVertices;
    TrackCollection tracks;
    ElectronCollection allElectrons;
    ElectronCollection goodElectrons;
    ElectronCollection goodIsolatedElectrons;
    ElectronCollection goodPFIsolatedElectrons;
    ElectronCollection looseElectrons;
    ElectronCollection qcdElectrons;
    ElectronCollection loosePFElectrons;

    JetCollection allJets;
    JetCollection genJets;
    JetCollection goodJets;
    JetCollection goodBJets;

    MuonCollection allMuons;
    MuonCollection goodMuons;
    MuonCollection goodIsolatedMuons;
    MuonCollection looseMuons;
    MuonCollection tightMuons;

    MCParticleCollection genParticles;

    METPointer met;

    DataType::value dataType;
    unsigned long runNumber;
    unsigned long eventNumber;
    unsigned long localEventNumber;
    unsigned long lumiBlock;
    float eventWeight;

    float jetCleaningEfficiency;
    unsigned int numberOfHighPurityTracks;
    bool isBeamScraping;

    unsigned int genNumberOfPileUpVertices;
    unsigned int trueNumberOfPileUpVertices;

    double Q2ScaleUpWgt, Q2ScaleDownWgt;

public:
    Event();
    virtual ~Event();
    bool isRealData() const;
    const DataType::value getDataType() const;
    void setDataType(DataType::value type);
    void setVertices(VertexCollection vertices);
    void setTracks(TrackCollection tracks);
    void setGenParticles(MCParticleCollection genParticles);
    void setElectrons(ElectronCollection electrons);
    void setLoosePFElectrons(ElectronCollection electrons);
    void setJets(JetCollection jets);
    void setGenJets(JetCollection genJets);
    void setMuons(MuonCollection muons);
    void setMET(const METPointer met);
    void setHLT(const boost::shared_ptr<Trigger> trig);
    void setPDFWts(const boost::shared_ptr<std::vector<double> >);
    void setRunNumber(unsigned long number);
    void setEventNumber(unsigned long number);
    void setLocalEventNumber(unsigned long number);
    void setLumiBlock(unsigned long block);
    void setEventWeight(float weight);
    void setBeamScrapingVeto(bool isScraping);
    void setGenNumberOfPileUpVertices(unsigned int pileup);
    void setTrueNumberOfPileUpVertices(unsigned int pileup);
    void setQ2Scales(double up, double down);

    const VertexPointer PrimaryVertex() const;
    const VertexCollection& Vertices() const;
    const VertexCollection& GoodVertices() const;
    const TrackCollection& Tracks() const;
    const MCParticleCollection& GenParticles() const;
    const ElectronCollection& Electrons() const;
    const ElectronCollection& GoodElectrons() const;
    const ElectronCollection& GoodIsolatedElectrons() const;
    const ElectronCollection& GoodPFIsolatedElectrons() const;
    const ElectronCollection& QCDElectrons() const;
    const ElectronCollection& LoosePFElectrons() const;
    const ElectronCollection& LooseElectrons() const;
    const JetCollection& Jets() const;
    const JetCollection& GenJets() const;
    const JetCollection& GoodJets() const;
    const JetCollection& GoodBJets() const;
    const MuonCollection& Muons() const;
    const MuonCollection& GoodMuons() const;
    const MuonCollection& GoodIsolatedMuons() const;
    const MuonCollection& TightMuons() const;
    const MuonCollection& LooseMuons() const;
    const METPointer MET() const;
    const ElectronPointer MostIsolatedElectron(bool usePFIso) const;
    const ElectronPointer MostIsolatedElectron() const;
    const ElectronPointer MostPFIsolatedElectron() const;
    unsigned long runnumber() const;
    unsigned long eventnumber() const;
    unsigned long localnumber() const;
    unsigned long lumiblock() const;
    float weight() const;
    void inspect() const;
    const boost::shared_ptr<Trigger> HLT(void) const;
    const std::map<std::string,int>& hltDictionary(void) const;
    double pdfWt(unsigned int index) const;
    static bool useCustomConversionTagger;
    static bool usePFIsolation;
    float getJetCleaningEfficiency(void) const ;

    float numberOfGeneratedPileUpVertices() const;
    float numberOfTruePileUpVertices() const;
    double getWeightQ2ScaleUp(void) const;
    double getWeightQ2ScaleDown(void) const;
    AdjWeight correctedWeight;
    boost::shared_ptr<std::vector<double> > pdfWeights;

private:
    void selectElectronsByQuality();
    void cleanGoodJets();
    void cleanAllJets();
    template <class PartColl> void cleanGoodJetsAgainstIsolatedLeptons(const PartColl &leptonColl);
    template <class PartColl> void cleanAllJetsAgainstIsolatedLeptons(const PartColl &leptonColl); 
    void cleanGoodJetsAgainstMostIsolatedElectron();
    void cleanAllJetsAgainstMostIsolatedElectron();
    void selectGoodJets();
    void selectMuonsByQuality();
    void selectVerticesByQuality();
};

}

#endif /* EVENT_H_ */
