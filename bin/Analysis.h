/*
 * Analysis.h
 *
 *  Created on: 12 Jul 2010
 *      Author: kreczko
 */

#ifndef ANALYSIS_H_
#define ANALYSIS_H_
#include <assert.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/unordered_map.hpp>
#include "../interface/Readers/NTupleEventReader.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TDirectory.h"
#include "../interface/Event.h"
#include "../interface/TopPairEventCandidate.h"
#include "../interface/ToplikeCandidate.h"
#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include "../interface/HistHelpers/HistogramManager.h"
#include "../interface/EventCounter.h"
#include "../interface/DupEvtChk.h"
#include "../interface/RecoObjects/Particle.h"
#include "../interface/EventWeightProvider.h"
#include "TFile.h"
#include "TTree.h"

struct InterestingEvent {
    InterestingEvent(unsigned long run, unsigned long event, std::string file) :
        candidate(), runNumber(run), eventNumber(event), fileName(file) {

    }

    InterestingEvent(BAT::TopPairEventCandidate cand, std::string file) :
        candidate(cand), runNumber(cand.runnumber()), eventNumber(cand.eventnumber()), fileName(file) {

    }
    ~InterestingEvent() {

    }
    BAT::TopPairEventCandidate candidate;
    unsigned long runNumber, eventNumber;
    std::string fileName;

    void print() {
        std::cout << "run " << candidate.runnumber() << ", event " << candidate.eventnumber() << " (Mttbar: "
                << candidate.mttbar() << ")" << std::endl;
        std::cout << "located in: " << fileName << std::endl << std::endl;
    }
};
typedef boost::array<unsigned long, BAT::TTbarEPlusJetsSelection::NUMBER_OF_SELECTION_STEPS> cutarray;
typedef boost::unordered_map<std::string, cutarray> cutmap;

class Analysis {
private:
    const std::vector<BAT::ToplikeSelectionSteps::Step>& monotopStudySelection;

    boost::scoped_ptr<BAT::NTupleEventReader> eventReader;
    BAT::Event currentEvent;
    BAT::TopPairEventCandidate ttbarCandidate;
    BAT::TopPlusXCandidates tPlusXCandidates;
    BAT::TwoNonResTops twoTopsNonRes;
    BAT::TwoNonResTops goodTopBadTop;
    BAT::TopNoMassConstraint loneTopsNoMassConstr;
    BAT::LeptoTopNoMassConstraint leptoTopNoMassConstr;
    DupEvtChk dupEvtChecker;
    cutarray cutflow;
    cutarray singleCuts;
    cutmap cutflowPerFile;
    cutmap singleCutsPerFile;
    cutarray mucutflow;
    cutarray musingleCuts;
    cutmap mucutflowPerFile;
    cutmap musingleCutsPerFile;
    std::vector<double> pdfWtAll, pdfWtSel;
    double q2upWtAll, q2downWtAll, q2upWtSel, q2downWtSel;
    std::vector<InterestingEvent> interestingEvents, brokenEvents;
    std::map<unsigned long, std::vector<unsigned long> > eventCheck;
    BAT::EventWeightProvider weights;
    double weight;
    BAT::Counter cutflowPerSample;
    BAT::Counter mucutflowPerSample;

    unsigned int wpTopPos, wpTopNeg, specTopPos, specTopNeg;

    TFile *outputFile;
    TTree *microTuple;

    // general event information: 
    int    type, run, lumi, event, numberOfJets, numberOfBJets, eSEL, muSEL, leptoCharge, nVerts;
    char   fileName[32];
    double pdfWeights[45];
    double q2WeightUp, q2WeightDown;
    double elecWt, muWt;
    ULong64_t eTRIGs, muTRIGs, metTRIGs, otherTRIGs; // fired tirggers from interface/HighLevelTriggers.h
    double Chi2, HT, ST, sumPt, cleanJetEff;

    int selection, metSel, muSel, eSel;

    int    whPdgId,    whIndGen;
    double whPtGen,    whEtaGen,    whPhiGen,  whMgen;
    double whPtRec,    whEtaRec,    whPhiRec,  whMrec;
    int    t1PdgId,    t1IndGen;
    double t1PtGen,    t1EtaGen,    t1PhiGen,  t1Mgen;
    int    t2PdgId,    t2IndGen;
    double t2PtGen,    t2EtaGen,    t2PhiGen,  t2Mgen;
    double thPtRec,    thEtaRec,    thPhiRec,  thMrec;

    // leading jets:
    int    leadingJetPdgId, leadingJetIndGen;
    double leadingJetPtGen, leadingJetEtaGen, leadingJetPhiGen;
    double leadingJetPtRec, leadingJetEtaRec, leadingJetPhiRec;
    double leadingJetTCHE,  leadingJetTCHP,   leadingJetCSV;
    int    subleadJetPdgId, subleadJetIndGen;
    double subleadJetPtGen, subleadJetEtaGen, subleadJetPhiGen;
    double subleadJetPtRec, subleadJetEtaRec, subleadJetPhiRec;
    double subleadJetTCHE,  subleadJetTCHP,   subleadJetCSV;
//    int    thirdJetPdgId, thirdJetIndGen;
//    double thirdJetPtGen, thirdJetEtaGen, thirdJetPhiGen;
    double thirdJetPtRec, thirdJetEtaRec, thirdJetPhiRec;
    double thirdJetTCHE,  thirdJetTCHP,   thirdJetCSV;
//    int    forthJetPdgId, forthJetIndGen;
//    double forthJetPtGen, forthJetEtaGen, forthJetPhiGen;
    double forthJetPtRec, forthJetEtaRec, forthJetPhiRec;
    double forthJetTCHE,  forthJetTCHP,   forthJetCSV;
    double m3jets, m3masslessJets;


    // all (<=3) b-jets (pT ordered):
    int    firstBJetPdgId, firstBJetIndGen;
    double firstBJetPtGen, firstBJetEtaGen, firstBJetPhiGen;
    double firstBJetPtRec, firstBJetEtaRec, firstBJetPhiRec;
    int    secondBJetPdgId, secondBJetIndGen;
    double secondBJetPtGen, secondBJetEtaGen, secondBJetPhiGen;
    double secondBJetPtRec, secondBJetEtaRec, secondBJetPhiRec;
    int    thirdBJetPdgId, thirdBJetIndGen;
    double thirdBJetPtGen, thirdBJetEtaGen, thirdBJetPhiGen;
    double thirdBJetPtRec, thirdBJetEtaRec, thirdBJetPhiRec;

    // highest pT leftover jet (gen-level: radiation for the background and d-jet in signals)
    int    freeJetPdgId,    freeJetIndGen;
    double freeJetPtGen,    freeJetEtaGen,    freeJetPhiGen;
    double freeJetPtRec,    freeJetEtaRec,    freeJetPhiRec;
    // a candidate b-jet from the hadronic top:
    int    bJetPdgId, bJetIndGen;
    double bJetPtGen, bJetEtaGen, bJetPhiGen;
    double bJetPtRec, bJetEtaRec, bJetPhiRec;
    // first and second (ordered in pT) jets from the hadronic W
    int    jet1WhPdgId, jet2WhPdgId,  jet1WhIndGen, jet2WhIndGen;
    double jet1WhPtGen, jet1WhEtaGen, jet1WhPhiGen;
    double jet1WhPtRec, jet1WhEtaRec, jet1WhPhiRec;
    double jet2WhPtGen, jet2WhEtaGen, jet2WhPhiGen;
    double jet2WhPtRec, jet2WhEtaRec, jet2WhPhiRec;
    // dark matter particle and associated missing ET
    int     dmPdgId,    dmIndGen;
    double  dmPtGen,    dmPhiGen,    dmEtaGen;
    double metPtRec,   metPhiRec,   metEtaRec;
    double metPtGen,   metPhiGen,   metEtaGen;

    // Leptons for the data-driven backgrounds
    int    lepton1PdgId, lepton1IsTight;
    double lepton1PtGen, lepton1EtaGen, lepton1PhiGen;
    double lepton1PtRec, lepton1EtaRec, lepton1PhiRec;
    double lepton1PFiso;
    int    lepton2PdgId, lepton2IsTight;
    double lepton2PtGen, lepton2EtaGen, lepton2PhiGen;
    double lepton2PtRec, lepton2EtaRec, lepton2PhiRec;
    double lepton2PFiso;
    int    lepton3PdgId, lepton3IsTight;
    double lepton3PtGen, lepton3EtaGen, lepton3PhiGen;
    double lepton3PtRec, lepton3EtaRec, lepton3PhiRec;
    double lepton3PFiso;
    int    neutrino1PdgId, neutrino2PdgId;
    double neutrino1PtGen, neutrino1EtaGen, neutrino1PhiGen;
    double neutrino2PtGen, neutrino2EtaGen, neutrino2PhiGen;

    // special block for W+jets studies
    int    tauPdgId,      tauElePdgId,    tauMuPdgId, tauNuPdgId;
    double tauPtGen,      tauEtaGen,      tauPhiGen;
    double tauElePtGen,   tauEleEtaGen,   tauElePhiGen;
    double tauMuPtGen,    tauMuEtaGen,    tauMuPhiGen;
    double tauNuPtGen,    tauNuEtaGen,    tauNuPhiGen;
    double tauJetPtRec,   tauJetEtaRec,   tauJetPhiRec, tauJetDR;

    // technicalities
    int    nTausGen;
    double tche, tchp, ssv, csv;

    bool finalized;
public:
    static float luminosity;
    Analysis(const std::vector<BAT::ToplikeSelectionSteps::Step>& selection, BAT::EventWeightProvider::SampleVersion sampleVersion);
    virtual ~Analysis();
    void finalize();
    void analyze(const char *outputFileName);
//    void analyze(const char *outputFileName, int stage=4, int nb=1, double met=250, double mTop=220);
    void addInputFile(const char * fileName);
    void setMaximalNumberOfEvents(long maxEvents);
    void setUsedNeutrinoSelectionForTopPairReconstruction(BAT::NeutrinoSelectionCriterion::value selection);
    void setUsedTTbarReconstructionCriterion(BAT::TTbarReconstructionCriterion::value selection);
    static void useJetAlgorithm(BAT::JetAlgorithm::value algo) {
        BAT::NTupleEventReader::jetAlgorithm = algo;
    }
    static void useElectronAlgorithm(BAT::ElectronAlgorithm::value algo) {
        BAT::NTupleEventReader::electronAlgorithm = algo;
    }

    static void useElectronIDMethod(BAT::eIDMethod::value algo) {
        BAT::NTupleEventReader::electronIDUsed = algo;
    }
	
    static void useMETAlgorithm(BAT::METAlgorithm::value algo) {
        BAT::NTupleEventReader::metAlgorithm = algo;
    }
    static void useMuonAlgorithm(BAT::MuonAlgorithm::value algo){
        BAT::NTupleEventReader::muonAlgorithm = algo;
    }

    static void usePFIsolation(bool use){
        BAT::Event::usePFIsolation = use;
    }

    static void useBtagVariation(BAT::JetBtagVariation::value btag){
        BAT::Jet::bTagVariation = btag;
    }

    static void useJetResVariation(BAT::JetResVariation::value res){
        BAT::Jet::resVariation  = res;
    }

    static void useCustomConversionTagger(bool use){
        BAT::TopPairEventCandidate::useCustomConversionTagger = use;
        //custom conversion tagger needs track information
        BAT::NTupleEventReader::loadTracks = use;
    }

    static void useLHAPDF(bool use){
        BAT::NTupleEventReader::useLHAPDF = use;
    }

private:
    void printNumberOfProccessedEventsEvery(unsigned long printEvery);
//    void doEcalSpikeAnalysis();
    bool initiateEvent();
    void doSynchExercise();
    void printSummary();
    void inspectEvents();
    void doCutFlow(cutarray &singleCuts, cutmap &singleCutsPerFile,
                   cutarray &cutflow, cutmap &cutflowPerFile, BAT::Counter &cutflowPerSample,
                   const std::vector<BAT::ToplikeSelectionSteps::Step>& cutList);
    void initMicroNtuple();
    void doMicroNtuple();
    void sumPDFWeights();
//    void sumPDFWeights(int stage, int nb, double met, double mTop);
    void sumQ2Weights();
    void doPDfSystemStudy() const ;
    void doQ2SystemStudy() const ;
    void checkForDuplicatedEvents();
    void checkForBrokenEvents();
};

#endif /* ANALYSIS_H_ */
