/*
 * Analysis.cpp
 *
 *  Created on: 12 Jul 2010
 *      Author: kreczko
 */

#include "Analysis.h"
#include "TROOT.h"
#include <iostream>
#include <boost/scoped_ptr.hpp>
#include <boost/array.hpp>
#include "../interface/EventCounter.h"
#include <cmath>
#include <math.h>
#include "../interface/Printers/EventTablePrinter.h"
#include "TTree.h"

using namespace BAT;
using namespace std;
float Analysis::luminosity = 5000.;

//void Analysis::analyze(const char *outputFileName, int stage, int nb, double met, double mTop) {
void Analysis::analyze(const char *outputFileName) {
    finalized = false;

    outputFile = TFile::Open(outputFileName,"RECREATE");
    microTuple = new TTree("micro","micro");

    initMicroNtuple();
    cout << "detected samples:" << endl;
    for (unsigned int sample = 0; sample < DataType::NUMBER_OF_DATA_TYPES; ++sample) {
        if (eventReader->getSeenDatatypes()[sample])
            cout << DataType::names[sample] << endl;
    }

    for(unsigned int index = 0; index < 45; ++index) {
        pdfWtSel.push_back(0.0);
        pdfWtAll.push_back(0.0);
    }
    q2upWtAll = 0; q2downWtAll = 0; q2upWtSel = 0; q2downWtSel = 0;

    while (eventReader->hasNextEvent() ) {
        if( !initiateEvent() ) continue;
        printNumberOfProccessedEventsEvery(100000);

        tPlusXCandidates = TopPlusXCandidates(currentEvent);

        doCutFlow(singleCuts, singleCutsPerFile,
                  cutflow, cutflowPerFile, cutflowPerSample,
                  monotopStudySelection);

        sumQ2Weights();
if( BAT::NTupleEventReader::useLHAPDF )
        sumPDFWeights();
        doMicroNtuple();
    }
    finalize();
}

void Analysis::finalize(void){
  if( !finalized ){
    checkForDuplicatedEvents();
    outputFile->cd();
    microTuple->Write();
    outputFile->Write();
    outputFile->Close();
    printSummary();
    doQ2SystemStudy();
if( BAT::NTupleEventReader::useLHAPDF )
    doPDfSystemStudy();
//    delete outputFile;
//    delete microTuple;
    finalized = true;
  }
}

void Analysis::printNumberOfProccessedEventsEvery(unsigned long printEvery) {
    unsigned long eventIndex = eventReader->getNumberOfProccessedEvents();
    if (eventIndex % printEvery == 0 || eventIndex == 1) {
        cout << "Analysing event no " << eventIndex << ", sample: " << DataType::names[currentEvent.getDataType()]
                << endl;
        cout << "File: " << eventReader->getCurrentFile() << endl;
    } else {
    	/*
    	static TString prevFile;
    	const char *currFile = eventReader->getCurrentFile();
    	if (prevFile != currFile) {
        cout << "File: " << currFile << endl;
        prevFile = currFile;
    	}
    	*/
    }

}

//extern bool isGood(int,int); 
//extern bool isGoodPrompt(int,int); 

bool Analysis::initiateEvent() {
    currentEvent = eventReader->getNextEvent();
    string filename( eventReader->getCurrentFile() );

		if (currentEvent.isRealData() && dupEvtChecker.IsDuplicate(currentEvent.runnumber(), currentEvent.eventnumber()))
			return (false);

 // The code below apply 3 different JSON files
 // Keep in mind that luminosity is likely compatible with only 1 of them may not be accurate after such selection
/*
    if( currentEvent.isRealData() && (
         (filename.find("PromptReco") == string::npos && (filename.find("13Jul2012")  == string::npos )) ||
         (filename.find("PromptReco") != string::npos && !isGoodPrompt(currentEvent.runnumber(), currentEvent.lumiblock())) ||
         (filename.find("13Jul2012")  != string::npos && !isGood      (currentEvent.runnumber(), currentEvent.lumiblock()))
                                     )
    ) return false;
*/
    ttbarCandidate = TopPairEventCandidate(currentEvent);
    weight = weights.getWeight(currentEvent.getDataType());
    if( !currentEvent.isRealData() ){
       weights.generate_truePileUp2012_weights(EventWeightProvider::S10);
       weight *= weights.reweightPileUpOfficial( currentEvent.numberOfTruePileUpVertices() );
///       if( currentEvent.getDataType() != DataType::TTJets ){
///          weights.generate_truePileUp2012_weights(EventWeightProvider::S7);
///          weight *= weights.reweightPileUpOfficial( currentEvent.numberOfTruePileUpVertices() );
///       } else {
///          weights.generate_truePileUp2012_weights(EventWeightProvider::S6);
///          weight *= weights.reweightPileUp( currentEvent.numberOfTruePileUpVertices() );
///       }
    }
    currentEvent.correctedWeight = weight;

    return true;
}

void Analysis::inspectEvents() {
    std::vector<InterestingEvent> eventsToInspect;

    for (unsigned int index = 0; index < eventsToInspect.size(); ++index) {
        if ((ttbarCandidate.runnumber() == eventsToInspect.at(index).runNumber && ttbarCandidate.eventnumber()
                == eventsToInspect.at(index).eventNumber)) {
            cout << "file: " << eventReader->getCurrentFile() << endl;
            ttbarCandidate.inspect();
        }
    }

}


void Analysis::doSynchExercise() {
    if (ttbarCandidate.passesSelectionStepUpTo(TTbarEPlusJetsSelection::ConversionFinder)) {
        cout << ttbarCandidate.runnumber() << ":" << ttbarCandidate.eventnumber() << ":" << endl;//electron->et() << endl;
        if (ttbarCandidate.eventnumber() == 450622) {
            ttbarCandidate.inspect();
        }
    }
}


void Analysis::doCutFlow(cutarray &singleCuts, cutmap &singleCutsPerFile,
		cutarray &cutflow, cutmap &cutflowPerFile, BAT::Counter &cutflowPerSample,
		const std::vector<BAT::ToplikeSelectionSteps::Step>& cutList)
{
	unsigned int njet = tPlusXCandidates.GoodJets().size();
	if (njet >= JetBin::NUMBER_OF_JET_BINS)
			njet = JetBin::NUMBER_OF_JET_BINS - 1;
	// Last element is for original # of events
	cutflowPerSample.increase(tPlusXCandidates.getDataType(), cutList.size(), njet, weight);
	for (unsigned int cut = 0; cut < cutList.size(); ++cut) {
		if (tPlusXCandidates.passesSelectionStep(cutList[cut])) {
				++singleCuts[cut];
				singleCutsPerFile[eventReader->getCurrentFile()][cut]++;
		}
		if (tPlusXCandidates.passesSelectionStepUpTo(cut, cutList)) {
				cutflow[cut] += 1;
				cutflowPerFile[eventReader->getCurrentFile()][cut]++;
				cutflowPerSample.increase(tPlusXCandidates.getDataType(), cut, njet,
					tPlusXCandidates.correctedWeight);
		}
	}
	// Reset back to base weight after going through cut flow
	tPlusXCandidates.correctedWeight.reset();
}


void Analysis::initMicroNtuple() {
    microTuple->Branch("type",   &type,   "type/I");
    microTuple->Branch("weight", &weight, "weight/D");
    microTuple->Branch("run",    &run,    "run/I");
    microTuple->Branch("lumi",   &lumi,   "lumi/I");
    microTuple->Branch("event",  &event,  "event/I");
///    microTuple->Branch("fileName", fileName, "fileName[32]/C");
    microTuple->Branch("numberOfJets",  &numberOfJets,  "numberOfJets/I");
    microTuple->Branch("numberOfBJets", &numberOfBJets, "numberOfBJets/I");
    microTuple->Branch("nVerts",        &nVerts,        "nVerts/I");
    microTuple->Branch("selection",     &selection,     "selection/I");
    microTuple->Branch("metSel",        &metSel,        "metSel/I");
    microTuple->Branch("muSel",         &muSel,         "muSel/I");
    microTuple->Branch("eSel",          &eSel,          "eSel/I");
    microTuple->Branch("eTRIGs",        &eTRIGs,        "eTRIGs/l");
    microTuple->Branch("muTRIGs",       &muTRIGs,       "muTRIGs/l");
    microTuple->Branch("metTRIGs",      &metTRIGs,      "metTRIGs/l");
    microTuple->Branch("otherTRIGs",    &otherTRIGs,    "otherTRIGs/l");
    microTuple->Branch("Chi2",          &Chi2,          "Chi2/D");
    microTuple->Branch("cleanJetEff",   &cleanJetEff,   "cleanJetEff/D");
///    microTuple->Branch("HT",            &HT,            "HT/D");
///    microTuple->Branch("ST",            &ST,            "ST/D");
///    microTuple->Branch("sumPt",         &sumPt,         "sumPt/D");
    microTuple->Branch("q2WeightUp",    &q2WeightUp,    "q2WeightUp/D");
    microTuple->Branch("q2WeightDown",  &q2WeightDown,  "q2WeightDown/D");
if( BAT::NTupleEventReader::useLHAPDF )
    microTuple->Branch("pdfWeights",     pdfWeights,    "pdfWeights[45]/D");

///    microTuple->Branch("leadingJetPdgId", &leadingJetPdgId, "leadingJetPdgId/I");
///    microTuple->Branch("leadingJetIndGen",&leadingJetIndGen,"leadingJetIndGen/I");
///    microTuple->Branch("leadingJetPtGen", &leadingJetPtGen, "leadingJetPtGen/D");
///    microTuple->Branch("leadingJetEtaGen",&leadingJetEtaGen,"leadingJetEtaGen/D");
///    microTuple->Branch("leadingJetPhiGen",&leadingJetPhiGen,"leadingJetPhiGen/D");
    microTuple->Branch("leadingJetPtRec", &leadingJetPtRec, "leadingJetPtRec/D");
    microTuple->Branch("leadingJetEtaRec",&leadingJetEtaRec,"leadingJetEtaRec/D");
    microTuple->Branch("leadingJetPhiRec",&leadingJetPhiRec,"leadingJetPhiRec/D");
    microTuple->Branch("leadingJetTCHE",  &leadingJetTCHE,  "leadingJetTCHE/D");
    microTuple->Branch("leadingJetTCHP",  &leadingJetTCHP,  "leadingJetTCHP/D");
    microTuple->Branch("leadingJetCSV",   &leadingJetCSV,   "leadingJetCSV/D");
    microTuple->Branch("leadingJetFlavor",&leadingJetFlavor,"leadingJetFlavor/I");

///    microTuple->Branch("subleadJetPdgId", &subleadJetPdgId, "subleadJetPdgId/I");
///    microTuple->Branch("subleadJetIndGen",&subleadJetIndGen,"subleadJetIndGen/I");
///    microTuple->Branch("subleadJetPtGen", &subleadJetPtGen, "subleadJetPtGen/D");
///    microTuple->Branch("subleadJetEtaGen",&subleadJetEtaGen,"subleadJetEtaGen/D");
///    microTuple->Branch("subleadJetPhiGen",&subleadJetPhiGen,"subleadJetPhiGen/D");
    microTuple->Branch("subleadJetPtRec", &subleadJetPtRec, "subleadJetPtRec/D");
    microTuple->Branch("subleadJetEtaRec",&subleadJetEtaRec,"subleadJetEtaRec/D");
    microTuple->Branch("subleadJetPhiRec",&subleadJetPhiRec,"subleadJetPhiRec/D");
    microTuple->Branch("subleadJetTCHE",  &subleadJetTCHE,  "subleadJetTCHE/D");
    microTuple->Branch("subleadJetTCHP",  &subleadJetTCHP,  "subleadJetTCHP/D");
    microTuple->Branch("subleadJetCSV",   &subleadJetCSV,   "subleadJetCSV/D");
    microTuple->Branch("subleadJetFlavor",&subleadJetFlavor,"subleadJetFlavor/I");

    microTuple->Branch("thirdJetPtRec",   &thirdJetPtRec,   "thirdJetPtRec/D");
    microTuple->Branch("thirdJetEtaRec",  &thirdJetEtaRec,  "thirdJetEtaRec/D");
    microTuple->Branch("thirdJetPhiRec",  &thirdJetPhiRec,  "thirdJetPhiRec/D");
    microTuple->Branch("thirdJetTCHE",    &thirdJetTCHE,    "thirdJetTCHE/D");
    microTuple->Branch("thirdJetTCHP",    &thirdJetTCHP,    "thirdJetTCHP/D");
    microTuple->Branch("thirdJetCSV",     &thirdJetCSV,     "thirdJetCSV/D");
    microTuple->Branch("thirdJetFlavor",  &thirdJetFlavor,  "thirdJetFlavor/I");

    microTuple->Branch("forthJetPtRec",   &forthJetPtRec,   "forthJetPtRec/D");
    microTuple->Branch("forthJetEtaRec",  &forthJetEtaRec,  "forthJetEtaRec/D");
    microTuple->Branch("forthJetPhiRec",  &forthJetPhiRec,  "forthJetPhiRec/D");
    microTuple->Branch("forthJetTCHE",    &forthJetTCHE,    "forthJetTCHE/D");
    microTuple->Branch("forthJetTCHP",    &forthJetTCHP,    "forthJetTCHP/D");
    microTuple->Branch("forthJetCSV",     &forthJetCSV,     "forthJetCSV/D");
    microTuple->Branch("forthJetFlavor",  &forthJetFlavor,  "forthJetFlavor/I");

    microTuple->Branch("m3jets",         &m3jets,         "m3jets/D");
    microTuple->Branch("m3masslessJets", &m3masslessJets, "m3masslessJets/D");

    microTuple->Branch("firstBJetPtRec",   &firstBJetPtRec,   "firstBJetPtRec/D");
    microTuple->Branch("firstBJetEtaRec",  &firstBJetEtaRec,  "firstBJetEtaRec/D");
    microTuple->Branch("firstBJetPhiRec",  &firstBJetPhiRec,  "firstBJetPhiRec/D");
    microTuple->Branch("secondBJetPtRec",  &secondBJetPtRec,  "secondBJetPtRec/D");
    microTuple->Branch("secondBJetEtaRec", &secondBJetEtaRec, "secondBJetEtaRec/D");
    microTuple->Branch("secondBJetPhiRec", &secondBJetPhiRec, "secondBJetPhiRec/D");
    microTuple->Branch("thirdBJetPtRec",   &thirdBJetPtRec,   "thirdBJetPtRec/D");
    microTuple->Branch("thirdBJetEtaRec",  &thirdBJetEtaRec,  "thirdBJetEtaRec/D");
    microTuple->Branch("thirdBJetPhiRec",  &thirdBJetPhiRec,  "thirdBJetPhiRec/D");

    microTuple->Branch("firstBJetPtGen",   &firstBJetPtGen,   "firstBJetPtGen/D");
    microTuple->Branch("firstBJetEtaGen",  &firstBJetEtaGen,  "firstBJetEtaGen/D");
    microTuple->Branch("firstBJetPhiGen",  &firstBJetPhiGen,  "firstBJetPhiGen/D");
    microTuple->Branch("secondBJetPtGen",  &secondBJetPtGen,  "secondBJetPtGen/D");
    microTuple->Branch("secondBJetEtaGen", &secondBJetEtaGen, "secondBJetEtaGen/D");
    microTuple->Branch("secondBJetPhiGen", &secondBJetPhiGen, "secondBJetPhiGen/D");
    microTuple->Branch("thirdBJetPtGen",   &thirdBJetPtGen,   "thirdBJetPtGen/D");
    microTuple->Branch("thirdBJetEtaGen",  &thirdBJetEtaGen,  "thirdBJetEtaGen/D");
    microTuple->Branch("thirdBJetPhiGen",  &thirdBJetPhiGen,  "thirdBJetPhiGen/D");

///    microTuple->Branch("freeJetPdgId",    &freeJetPdgId,   "freeJetPdgId/I");
///    microTuple->Branch("freeJetIndGen",   &freeJetIndGen,  "freeJetIndGen/I");
///    microTuple->Branch("freeJetPtGen",    &freeJetPtGen,   "freeJetPtGen/D");
///    microTuple->Branch("freeJetEtaGen",   &freeJetEtaGen,  "freeJetEtaGen/D");
///    microTuple->Branch("freeJetPhiGen",   &freeJetPhiGen,  "freeJetPhiGen/D");
///    microTuple->Branch("freeJetPtRec",    &freeJetPtRec,   "freeJetPtRec/D");
///    microTuple->Branch("freeJetEtaRec",   &freeJetEtaRec,  "freeJetEtaRec/D");
///    microTuple->Branch("freeJetPhiRec",   &freeJetPhiRec,  "freeJetPhiRec/D");

    microTuple->Branch("bJetPtGen",    &bJetPtGen,  "bJetPtGen/D");
    microTuple->Branch("bJetEtaGen",   &bJetEtaGen, "bJetEtaGen/D");
    microTuple->Branch("bJetPhiGen",   &bJetPhiGen, "bJetPhiGen/D");
    microTuple->Branch("bJetPtRec",    &bJetPtRec,  "bJetPtRec/D");
    microTuple->Branch("bJetEtaRec",   &bJetEtaRec, "bJetEtaRec/D");
    microTuple->Branch("bJetPhiRec",   &bJetPhiRec, "bJetPhiRec/D");

    microTuple->Branch("jet1WhPdgId",    &jet1WhPdgId,  "jet1WhPdgId/I");
    microTuple->Branch("jet2WhPdgId",    &jet2WhPdgId,  "jet2WhPdgId/I");
    microTuple->Branch("jet1WhIndGen",   &jet1WhIndGen, "jet1WhIndGen/I");
    microTuple->Branch("jet2WhIndGen",   &jet2WhIndGen, "jet2WhIndGen/I");
    microTuple->Branch("jet1WhPtGen",    &jet1WhPtGen,  "jet1WhPtGen/D");
    microTuple->Branch("jet1WhEtaGen",   &jet1WhEtaGen, "jet1WhEtaGen/D");
    microTuple->Branch("jet1WhPhiGen",   &jet1WhPhiGen, "jet1WhPhiGen/D");
    microTuple->Branch("jet1WhPtRec",    &jet1WhPtRec,  "jet1WhPtRec/D");
    microTuple->Branch("jet1WhEtaRec",   &jet1WhEtaRec, "jet1WhEtaRec/D");
    microTuple->Branch("jet1WhPhiRec",   &jet1WhPhiRec, "jet1WhPhiRec/D");
    microTuple->Branch("jet2WhPtGen",    &jet2WhPtGen,  "jet2WhPtGen/D");
    microTuple->Branch("jet2WhEtaGen",   &jet2WhEtaGen, "jet2WhEtaGen/D");
    microTuple->Branch("jet2WhPhiGen",   &jet2WhPhiGen, "jet2WhPhiGen/D");
    microTuple->Branch("jet2WhPtRec",    &jet2WhPtRec,  "jet2WhPtRec/D");
    microTuple->Branch("jet2WhEtaRec",   &jet2WhEtaRec, "jet2WhEtaRec/D");
    microTuple->Branch("jet2WhPhiRec",   &jet2WhPhiRec, "jet2WhPhiRec/D");

    microTuple->Branch("dmIndGen",       &dmIndGen,     "dmIndGen/I");
    microTuple->Branch("dmPdgId",        &dmPdgId,      "dmPdgId/I");
    microTuple->Branch("dmPtGen",        &dmPtGen,      "dmPtGen/D");
    microTuple->Branch("dmPhiGen",       &dmPhiGen,     "dmPhiGen/D");
    microTuple->Branch("dmEtaGen",       &dmEtaGen,     "dmEtaGen/D");
    microTuple->Branch("metPtRec",       &metPtRec,     "metPtRec/D");
    microTuple->Branch("metPhiRec",      &metPhiRec,    "metPhiRec/D");
    microTuple->Branch("metEtaRec",      &metEtaRec,    "metEtaRec/D");
    microTuple->Branch("metPtGen",       &metPtGen,     "metPtGen/D");
    microTuple->Branch("metPhiGen",      &metPhiGen,    "metPhiGen/D");
    microTuple->Branch("metEtaGen",      &metEtaGen,    "metEtaGen/D");

    microTuple->Branch("whIndGen",       &whIndGen,     "whIndGen/I");
    microTuple->Branch("whPdgId",        &whPdgId,      "whPdgId/I");
    microTuple->Branch("whPtGen",        &whPtGen,      "whPtGen/D");
    microTuple->Branch("whEtaGen",       &whEtaGen,     "whEtaGen/D");
    microTuple->Branch("whPhiGen",       &whPhiGen,     "whPhiGen/D");
    microTuple->Branch("whMgen",         &whMgen,       "whMgen/D");
    microTuple->Branch("whPtRec",        &whPtRec,      "whPtRec/D");
    microTuple->Branch("whEtaRec",       &whEtaRec,     "whEtaRec/D");
    microTuple->Branch("whPhiRec",       &whPhiRec,     "whPhiRec/D");
    microTuple->Branch("whMrec",         &whMrec,       "whMrec/D");

    microTuple->Branch("t1IndGen",       &t1IndGen,     "t1IndGen/I");
    microTuple->Branch("t1PdgId",        &t1PdgId,      "t1PdgId/I");
    microTuple->Branch("t1PtGen",        &t1PtGen,      "t1PtGen/D");
    microTuple->Branch("t1EtaGen",       &t1EtaGen,     "t1EtaGen/D");
    microTuple->Branch("t1PhiGen",       &t1PhiGen,     "t1PhiGen/D");
    microTuple->Branch("t1Mgen",         &t1Mgen,       "t1Mgen/D");
    microTuple->Branch("t2IndGen",       &t2IndGen,     "t2IndGen/I");
    microTuple->Branch("t2PdgId",        &t2PdgId,      "t2PdgId/I");
    microTuple->Branch("t2PtGen",        &t2PtGen,      "t2PtGen/D");
    microTuple->Branch("t2EtaGen",       &t2EtaGen,     "t2EtaGen/D");
    microTuple->Branch("t2PhiGen",       &t2PhiGen,     "t2PhiGen/D");
    microTuple->Branch("t2Mgen",         &t2Mgen,       "t2Mgen/D");
    microTuple->Branch("thPtRec",        &thPtRec,      "thPtRec/D");
    microTuple->Branch("thEtaRec",       &thEtaRec,     "thEtaRec/D");
    microTuple->Branch("thPhiRec",       &thPhiRec,     "thPhiRec/D");
    microTuple->Branch("thMrec",         &thMrec,       "thMrec/D");

    microTuple->Branch("lepton1PdgId",   &lepton1PdgId, "lepton1PdgId/I");
    microTuple->Branch("lepton1IsTight", &lepton1IsTight,"lepton1IsTight/I");
    microTuple->Branch("lepton1PtGen",   &lepton1PtGen, "lepton1PtGen/D");
    microTuple->Branch("lepton1EtaGen",  &lepton1EtaGen,"lepton1EtaGen/D");
    microTuple->Branch("lepton1PhiGen",  &lepton1PhiGen,"lepton1PhiGen/D");
    microTuple->Branch("lepton1PtRec",   &lepton1PtRec, "lepton1PtRec/D");
    microTuple->Branch("lepton1EtaRec",  &lepton1EtaRec,"lepton1EtaRec/D");
    microTuple->Branch("lepton1PhiRec",  &lepton1PhiRec,"lepton1PhiRec/D");
    microTuple->Branch("lepton1PFiso",   &lepton1PFiso, "lepton1PFiso/D"); ///
    microTuple->Branch("lepton1mvaTrigV0eID",    &lepton1mvaTrigV0eID,    "lepton1mvaTrigV0eID/D");
    microTuple->Branch("lepton1mvaNonTrigV0eID", &lepton1mvaNonTrigV0eID, "lepton1mvaNonTrigV0eID/D");

    microTuple->Branch("lepton2PdgId",   &lepton2PdgId, "lepton2PdgId/I");
    microTuple->Branch("lepton2IsTight", &lepton2IsTight,"lepton2IsTight/I");
    microTuple->Branch("lepton2PtGen",   &lepton2PtGen, "lepton2PtGen/D");
    microTuple->Branch("lepton2EtaGen",  &lepton2EtaGen,"lepton2EtaGen/D");
    microTuple->Branch("lepton2PhiGen",  &lepton2PhiGen,"lepton2PhiGen/D");
    microTuple->Branch("lepton2PtRec",   &lepton2PtRec, "lepton2PtRec/D");
    microTuple->Branch("lepton2EtaRec",  &lepton2EtaRec,"lepton2EtaRec/D");
    microTuple->Branch("lepton2PhiRec",  &lepton2PhiRec,"lepton2PhiRec/D");
    microTuple->Branch("lepton2PFiso",   &lepton2PFiso, "lepton2PFiso/D"); ///
    microTuple->Branch("lepton2mvaTrigV0eID",    &lepton2mvaTrigV0eID,    "lepton2mvaTrigV0eID/D");
    microTuple->Branch("lepton2mvaNonTrigV0eID", &lepton2mvaNonTrigV0eID, "lepton2mvaNonTrigV0eID/D");

    microTuple->Branch("lepton3PdgId",   &lepton3PdgId, "lepton3PdgId/I");
    microTuple->Branch("lepton3IsTight", &lepton3IsTight,"lepton3IsTight/I");
    microTuple->Branch("lepton3PtGen",   &lepton3PtGen, "lepton3PtGen/D");
    microTuple->Branch("lepton3EtaGen",  &lepton3EtaGen,"lepton3EtaGen/D");
    microTuple->Branch("lepton3PhiGen",  &lepton3PhiGen,"lepton3PhiGen/D");
    microTuple->Branch("lepton3PtRec",   &lepton3PtRec, "lepton3PtRec/D");
    microTuple->Branch("lepton3EtaRec",  &lepton3EtaRec,"lepton3EtaRec/D");
    microTuple->Branch("lepton3PhiRec",  &lepton3PhiRec,"lepton3PhiRec/D");
    microTuple->Branch("lepton3PFiso",   &lepton3PFiso, "lepton3PFiso/D"); ///
    microTuple->Branch("lepton3mvaTrigV0eID",    &lepton3mvaTrigV0eID,    "lepton3mvaTrigV0eID/D");
    microTuple->Branch("lepton3mvaNonTrigV0eID", &lepton3mvaNonTrigV0eID, "lepton3mvaNonTrigV0eID/D");

    microTuple->Branch("neutrino1PdgId",  &neutrino1PdgId,  "neutrino1PdgId/I");
    microTuple->Branch("neutrino1PtGen",  &neutrino1PtGen,  "neutrino1PtGen/D");
    microTuple->Branch("neutrino1EtaGen", &neutrino1EtaGen, "neutrino1EtaGen/D");
    microTuple->Branch("neutrino1PhiGen", &neutrino1PhiGen, "neutrino1PhiGen/D");

    microTuple->Branch("neutrino2PdgId",  &neutrino2PdgId,  "neutrino2PdgId/I");
    microTuple->Branch("neutrino2PtGen",  &neutrino2PtGen,  "neutrino2PtGen/D");
    microTuple->Branch("neutrino2EtaGen", &neutrino2EtaGen, "neutrino2EtaGen/D");
    microTuple->Branch("neutrino2PhiGen", &neutrino2PhiGen, "neutrino2PhiGen/D");

    microTuple->Branch("nTausGen",     &nTausGen,     "nTausGen/I");
    microTuple->Branch("tauPdgId",     &tauPdgId,     "tauPdgId/I");
    microTuple->Branch("tauPtGen",     &tauPtGen,     "tauPtGen/D");
    microTuple->Branch("tauEtaGen",    &tauEtaGen,    "tauEtaGen/D");
    microTuple->Branch("tauPhiGen",    &tauPhiGen,    "tauPhiGen/D");
    microTuple->Branch("tauElePdgId",  &tauElePdgId,  "tauElePdgId/I");
    microTuple->Branch("tauElePtGen",  &tauElePtGen,  "tauElePtGen/D");
    microTuple->Branch("tauEleEtaGen", &tauEleEtaGen, "tauEleEtaGen/D");
    microTuple->Branch("tauElePhiGen", &tauElePhiGen, "tauElePhiGen/D");
    microTuple->Branch("tauMuPdgId",   &tauMuPdgId,   "tauMuPdgId/I");
    microTuple->Branch("tauMuPtGen",   &tauMuPtGen,   "tauMuPtGen/D");
    microTuple->Branch("tauMuEtaGen",  &tauMuEtaGen,  "tauMuEtaGen/D");
    microTuple->Branch("tauMuPhiGen",  &tauMuPhiGen,  "tauMuPhiGen/D");
    microTuple->Branch("tauNuPdgId",   &tauNuPdgId,   "tauNuPdgId/I");
    microTuple->Branch("tauNuPtGen",   &tauNuPtGen,   "tauNuPtGen/D");
    microTuple->Branch("tauNuEtaGen",  &tauNuEtaGen,  "tauNuEtaGen/D");
    microTuple->Branch("tauNuPhiGen",  &tauNuPhiGen,  "tauNuPhiGen/D");
    microTuple->Branch("tauJetPtRec",  &tauJetPtRec,  "tauJetPtRec/D");
    microTuple->Branch("tauJetEtaRec", &tauJetEtaRec, "tauJetEtaRec/D");
    microTuple->Branch("tauJetPhiRec", &tauJetPhiRec, "tauJetPhiRec/D");
    microTuple->Branch("tauJetDR",     &tauJetDR,     "tauJetDR/D");

}

/*
const Particle operator +(const Particle &that, const Particle &other) {
    Particle result = that;
    FourVector vector = result.getFourVector() + other.getFourVector();
cout<<" part 1: pt="<<result.getFourVector().Pt()<<" eta="<<result.getFourVector().Eta()<<" phi="<<result.getFourVector().Phi()<<" m="<<result.getFourVector().M()<<" E="<<result.getFourVector().E()<<" pz="<<result.getFourVector().Pz()<<endl;
cout<<" part 2: pt="<< other.getFourVector().Pt()<<" eta="<< other.getFourVector().Eta()<<" phi="<< other.getFourVector().Phi()<<" m="<< other.getFourVector().M()<<" E="<< other.getFourVector().E()<<" pz="<< other.getFourVector().Pz()<<endl;
    result.setFourVector(vector);
    result.setMass(0);
    result.setCharge(result.charge() + other.charge());
    return result;
}
           ParticlePointer  hadronicW   = ParticlePointer(new Particle(::operator+(*(tPlusXCandidates.getJet1FromHadronicW()),*(tPlusXCandidates.getJet2FromHadronicW()))));
           ParticlePointer  hadronicTop = ParticlePointer(new Particle(::operator+(*(tPlusXCandidates.getHadronicBJet()),*hadronicW)));
TLorentzVector v0,v1,v2;
v0.SetPtEtaPhiM(bJetPtRec,bJetEtaRec,bJetPhiRec,0);
v1.SetPtEtaPhiM(jet1WhPtRec,jet1WhEtaRec,jet1WhPhiRec,0);
v2.SetPtEtaPhiM(jet2WhPtRec,jet2WhEtaRec,jet2WhPhiRec,0);
           cout<<"Wmass = "<<hadronicW->mass()<<" vs. "<<(v1+v2).M()<<" topMass="<<hadronicTop->mass()<<" vs. "<<(v0+v1+v2).M()<<endl;
*/

void Analysis::doMicroNtuple() {
        // general information about this event:
        type          = currentEvent.getDataType();
        run           = currentEvent.runnumber();
        lumi          = currentEvent.lumiblock();
        event         = currentEvent.eventnumber();
        numberOfJets  = currentEvent.GoodJets().size();
        numberOfBJets = currentEvent.GoodBJets().size();
        nVerts        = currentEvent.numberOfTruePileUpVertices();
        HT            = tPlusXCandidates.fullHT();
        ST            = tPlusXCandidates.ST();
        cleanJetEff   = currentEvent.getJetCleaningEfficiency();

        const char *file = basename( eventReader->getCurrentFile() );
        strncpy(fileName,file, (32>strlen(file)?strlen(file)+1:32));
        fileName[31] = '\0';

        eTRIGs = 0; muTRIGs = 0; metTRIGs = 0; otherTRIGs = 0;
        for(int trigger=0; trigger<HLTriggers::NUMBER_OF_TRIGGERS; trigger++)
            if( currentEvent.HLT()->isFired(HLTriggers::value(trigger)) ){
               if( trigger< HLTriggers::ELECTRON_TRIGGERS )
                    muTRIGs += (1L<<trigger);
               if( trigger> HLTriggers::ELECTRON_TRIGGERS && trigger< HLTriggers::OTHER_TRIGGERS )
                    eTRIGs  += (1L<<(trigger-HLTriggers::ELECTRON_TRIGGERS-1));
               if( trigger> HLTriggers::OTHER_TRIGGERS )
                    otherTRIGs  += (1L<<(trigger-HLTriggers::OTHER_TRIGGERS-1));
               //std::cout<<" fired "<<HLTriggers::names.at(trigger)<<std::endl;
            }

        q2WeightUp    = currentEvent.getWeightQ2ScaleUp();
        q2WeightDown  = currentEvent.getWeightQ2ScaleDown();

        leadingJetTCHE=-1; leadingJetTCHP=-1; leadingJetCSV=-1;
        subleadJetTCHE=-1; subleadJetTCHP=-1; subleadJetCSV=-1;
        thirdJetTCHE=-1;   thirdJetTCHP=-1;   thirdJetCSV=-1;
        forthJetTCHE=-1;   forthJetTCHP=-1;   forthJetCSV=-1;

        //  leading jet parameters and highest pT leftover jet (may not be the same jet):
        leadingJetPtRec = -1; leadingJetEtaRec = 0; leadingJetPhiRec = 0;
        subleadJetPtRec = -1; subleadJetEtaRec = 0; subleadJetPhiRec = 0;
        thirdJetPtRec   = -1; thirdJetEtaRec   = 0; thirdJetPhiRec   = 0;
        forthJetPtRec   = -1; forthJetEtaRec   = 0; forthJetPhiRec   = 0;
        firstBJetPtRec  = -1; secondBJetPtRec  =-1; thirdBJetPtRec   =-1;
        JetPointer leadingJetPointer, subleadJetPointer, thirdJetPointer;
        m3jets          = -1; m3masslessJets   =-1;
        for( JetCollection::const_iterator jet  = tPlusXCandidates.GoodJets().begin();
                                           jet != tPlusXCandidates.GoodJets().end();
                                           jet ++ ){
           if( leadingJetPtRec  < (*jet)->pt() ){
               forthJetPtRec    = thirdJetPtRec;
               forthJetEtaRec   = thirdJetEtaRec;
               forthJetPhiRec   = thirdJetPhiRec;
               forthJetTCHE     = thirdJetTCHE;
               forthJetTCHP     = thirdJetTCHP;
               forthJetCSV      = thirdJetCSV;
               forthJetFlavor   = thirdJetFlavor;
               thirdJetPtRec    = subleadJetPtRec;
               thirdJetEtaRec   = subleadJetEtaRec;
               thirdJetPhiRec   = subleadJetPhiRec;
               thirdJetTCHE     = subleadJetTCHE;
               thirdJetTCHP     = subleadJetTCHP;
               thirdJetCSV      = subleadJetCSV;
               thirdJetPointer  = subleadJetPointer;
               thirdJetFlavor   = subleadJetFlavor;
               subleadJetPtRec  = leadingJetPtRec;
               subleadJetEtaRec = leadingJetEtaRec;
               subleadJetPhiRec = leadingJetPhiRec;
               subleadJetTCHE   = leadingJetTCHE;
               subleadJetTCHP   = leadingJetTCHP;
               subleadJetCSV    = leadingJetCSV;
               subleadJetPointer= leadingJetPointer;
               subleadJetFlavor = leadingJetFlavor;
               leadingJetPtRec  = (*jet)->pt();
               leadingJetEtaRec = (*jet)->eta();
               leadingJetPhiRec = (*jet)->phi();
               leadingJetTCHE   = (*jet)->getDiscriminatorForBtagType(BtagAlgorithm::TrackCountingHighEffBTag);
               leadingJetTCHP   = (*jet)->getDiscriminatorForBtagType(BtagAlgorithm::TrackCountingHighPurBTag);
               leadingJetCSV    = (*jet)->getDiscriminatorForBtagType(BtagAlgorithm::CombinedSecondaryVertexBTag);
               leadingJetFlavor = (*jet)->partonFlavour();
               leadingJetPointer= (*jet);
           } else {
               if( subleadJetPtRec  < (*jet)->pt() ){
                   forthJetPtRec    = thirdJetPtRec;
                   forthJetEtaRec   = thirdJetEtaRec;
                   forthJetPhiRec   = thirdJetPhiRec;
                   forthJetTCHE     = thirdJetTCHE;
                   forthJetTCHP     = thirdJetTCHP;
                   forthJetCSV      = thirdJetCSV;
                   forthJetFlavor   = thirdJetFlavor;
                   thirdJetPtRec    = subleadJetPtRec;
                   thirdJetEtaRec   = subleadJetEtaRec;
                   thirdJetPhiRec   = subleadJetPhiRec;
                   thirdJetTCHE     = subleadJetTCHE;
                   thirdJetTCHP     = subleadJetTCHP;
                   thirdJetCSV      = subleadJetCSV;
                   thirdJetPointer  = subleadJetPointer;
                   thirdJetFlavor   = subleadJetFlavor;
                   subleadJetPtRec  = (*jet)->pt();
                   subleadJetEtaRec = (*jet)->eta();
                   subleadJetPhiRec = (*jet)->phi();
                   subleadJetTCHE   = (*jet)->getDiscriminatorForBtagType(BtagAlgorithm::TrackCountingHighEffBTag);
                   subleadJetTCHP   = (*jet)->getDiscriminatorForBtagType(BtagAlgorithm::TrackCountingHighPurBTag);
                   subleadJetCSV    = (*jet)->getDiscriminatorForBtagType(BtagAlgorithm::CombinedSecondaryVertexBTag);
                   subleadJetFlavor = (*jet)->partonFlavour();
                   subleadJetPointer= (*jet);
               } else {
                   if( thirdJetPtRec  < (*jet)->pt() ){
                       forthJetPtRec  = thirdJetPtRec;
                       forthJetEtaRec = thirdJetEtaRec;
                       forthJetPhiRec = thirdJetPhiRec;
                       forthJetTCHE   = thirdJetTCHE;
                       forthJetTCHP   = thirdJetTCHP;
                       forthJetCSV    = thirdJetCSV;
                       forthJetFlavor = thirdJetFlavor;
                       thirdJetPtRec  = (*jet)->pt();
                       thirdJetEtaRec = (*jet)->eta();
                       thirdJetPhiRec = (*jet)->phi();
                       thirdJetTCHE   = (*jet)->getDiscriminatorForBtagType(BtagAlgorithm::TrackCountingHighEffBTag);
                       thirdJetTCHP   = (*jet)->getDiscriminatorForBtagType(BtagAlgorithm::TrackCountingHighPurBTag);
                       thirdJetCSV    = (*jet)->getDiscriminatorForBtagType(BtagAlgorithm::CombinedSecondaryVertexBTag);
                       thirdJetFlavor = (*jet)->partonFlavour();
                       thirdJetPointer= (*jet);
                   } else {
                       if( forthJetPtRec  < (*jet)->pt() ){
                           forthJetPtRec  = (*jet)->pt();
                           forthJetEtaRec = (*jet)->eta();
                           forthJetPhiRec = (*jet)->phi();
                           forthJetTCHE   = (*jet)->getDiscriminatorForBtagType(BtagAlgorithm::TrackCountingHighEffBTag);
                           forthJetTCHP   = (*jet)->getDiscriminatorForBtagType(BtagAlgorithm::TrackCountingHighPurBTag);
                           forthJetCSV    = (*jet)->getDiscriminatorForBtagType(BtagAlgorithm::CombinedSecondaryVertexBTag);
                           forthJetFlavor = (*jet)->partonFlavour();
                       }
                   }
               }
           }

           if( (*jet)->isBJet() ){
              if( firstBJetPtRec   < (*jet)->pt() ){
                  secondBJetPtRec  = firstBJetPtRec;
                  secondBJetEtaRec = firstBJetEtaRec;
                  secondBJetPhiRec = firstBJetPhiRec;
                  firstBJetPtRec   = (*jet)->pt();
                  firstBJetEtaRec  = (*jet)->eta();
                  firstBJetPhiRec  = (*jet)->phi();
              } else {
                if( secondBJetPtRec  < (*jet)->pt() ){
                    thirdBJetPtRec   = secondBJetPtRec;
                    thirdBJetEtaRec  = secondBJetEtaRec;
                    thirdBJetPhiRec  = secondBJetPhiRec;
                    secondBJetPtRec  = (*jet)->pt();
                    secondBJetEtaRec = (*jet)->eta();
                    secondBJetPhiRec = (*jet)->phi();
                 } else {
                    if( thirdBJetPtRec  < (*jet)->pt() ){
                        thirdBJetPtRec  = (*jet)->pt();
                        thirdBJetEtaRec = (*jet)->eta();
                        thirdBJetPhiRec = (*jet)->phi();
                    }
                 }
              }
           }
      }

      if( thirdJetPtRec>0 ){
          Particle sum3jets = *leadingJetPointer + *subleadJetPointer + *thirdJetPointer;
          m3jets            = sum3jets.mass();
          TLorentzVector jet1, jet2, jet3;
          jet1.SetPtEtaPhiM(leadingJetPtRec, leadingJetEtaRec, leadingJetPhiRec, 0.);
          jet2.SetPtEtaPhiM(subleadJetPtRec, subleadJetEtaRec, subleadJetPhiRec, 0.);
          jet3.SetPtEtaPhiM(  thirdJetPtRec,   thirdJetEtaRec,   thirdJetPhiRec, 0.);
          TLorentzVector sum( jet1 + jet2 + jet3 );
          m3masslessJets    = sum.M();
      }

        lepton1PtRec = -1; lepton2PtRec = -1; lepton3PtRec = -1;
        lepton1PFiso = -1; lepton2PFiso = -1; lepton3PFiso = -1;
///        ElectronCollection electrons = tPlusXCandidates.GoodPFIsolatedElectrons();
///        ElectronCollection electrons = tPlusXCandidates.QCDElectrons();
///        ElectronCollection electrons = tPlusXCandidates.LooseElectrons();
///        MuonCollection     muons     = tPlusXCandidates.TightMuons();
        MuonCollection     muons     = tPlusXCandidates.LooseMuons();
///        for(unsigned int index = 0; index < electrons.size(); ++index) {
        for(unsigned int index = 0; index < muons.size(); ++index) {
///              const ElectronPointer lepton = electrons.at(index);
              const MuonPointer lepton = muons.at(index);
              if( lepton1PtRec  < lepton->pt() ){
                  lepton2PtRec  = lepton1PtRec;
                  lepton2EtaRec = lepton1EtaRec;
                  lepton2PhiRec = lepton1PhiRec;
                  lepton2PFiso  = lepton1PFiso;
                  lepton2IsTight= lepton1IsTight;
                  lepton1PtRec  = lepton->pt();
                  lepton1EtaRec = lepton->eta();
                  lepton1PhiRec = lepton->phi();
                  lepton1PFiso  = lepton->pfIsolationDeltaBeta();
///                  lepton1PFiso  = lepton->pfIsolationAeff();
                  lepton1IsTight = ( lepton->isTight() && lepton->isPFIsolated() ); 
///                  lepton1IsTight = ( lepton->isGood() && lepton->isPFIsolated() ); 
              } else {
                if( lepton2PtRec  < lepton->pt() ){
                    lepton3PtRec  = lepton2PtRec;
                    lepton3EtaRec = lepton2EtaRec;
                    lepton3PhiRec = lepton2PhiRec;
                    lepton3PFiso  = lepton2PFiso;
                    lepton3IsTight= lepton2IsTight;
                    lepton2PtRec  = lepton->pt();
                    lepton2EtaRec = lepton->eta();
                    lepton2PhiRec = lepton->phi();
                    lepton2PFiso  = lepton->pfIsolationDeltaBeta();
///                    lepton2PFiso  = lepton->pfIsolationAeff();
                    lepton2IsTight = ( lepton->isTight() && lepton->isPFIsolated() ); 
///                    lepton2IsTight = ( lepton->isGood() && lepton->isPFIsolated() ); 
                 } else {
                    if( lepton3PtRec  < lepton->pt() ){
                        lepton3PtRec  = lepton->pt();
                        lepton3EtaRec = lepton->eta();
                        lepton3PhiRec = lepton->phi();
                        lepton3PFiso  = lepton->pfIsolationDeltaBeta();
///                        lepton3PFiso  = lepton->pfIsolationAeff();
                        lepton3IsTight = ( lepton->isTight() && lepton->isPFIsolated() ); 
///                        lepton3IsTight = ( lepton->isGood() && lepton->isPFIsolated() ); 
                    }
                 }
              }
        }

        lepton1mvaTrigV0eID = -10;  lepton1mvaNonTrigV0eID = -10;
        lepton2mvaTrigV0eID = -10;  lepton2mvaNonTrigV0eID = -10;
        lepton3mvaTrigV0eID = -10;  lepton3mvaNonTrigV0eID = -10;
///        ElectronCollection electrons = tPlusXCandidates.GoodPFIsolatedElectrons();
///        ElectronCollection electrons = tPlusXCandidates.QCDElectrons();
///        ElectronCollection electrons = tPlusXCandidates.Electrons();
        ElectronCollection electrons = tPlusXCandidates.LooseElectrons();
///        MuonCollection     muons     = tPlusXCandidates.TightMuons();
///        MuonCollection     muons     = tPlusXCandidates.LooseMuons();
        for(unsigned int index = 0; index < electrons.size(); ++index) {
///        for(unsigned int index = 0; index < muons.size(); ++index) {
              const ElectronPointer lepton = electrons.at(index);
///              const MuonPointer lepton = muons.at(index);
              if( lepton1PtRec  < lepton->pt() ){
                  lepton2PtRec  = lepton1PtRec;
                  lepton2EtaRec = lepton1EtaRec;
                  lepton2PhiRec = lepton1PhiRec;
                  lepton2PFiso  = lepton1PFiso;
                  lepton2IsTight= lepton1IsTight;

                  lepton2mvaTrigV0eID    = lepton1mvaTrigV0eID;
                  lepton2mvaNonTrigV0eID = lepton1mvaNonTrigV0eID;

                  lepton1PtRec  = lepton->pt();
                  lepton1EtaRec = lepton->eta();
                  lepton1PhiRec = lepton->phi();
///                  lepton1PFiso  = lepton->pfIsolationDeltaBeta();
                  lepton1PFiso  = lepton->pfIsolationAeff();
///                  lepton1IsTight = ( lepton->isTight() && lepton->isPFIsolated() ); 
                  lepton1IsTight = ( lepton->isGood() && lepton->isPFIsolated() ); 

                  lepton1mvaTrigV0eID    = lepton->mvaTrigV0eID();
                  lepton1mvaNonTrigV0eID = lepton->mvaNonTrigV0eID();
              } else {
                if( lepton2PtRec  < lepton->pt() ){
                    lepton3PtRec  = lepton2PtRec;
                    lepton3EtaRec = lepton2EtaRec;
                    lepton3PhiRec = lepton2PhiRec;
                    lepton3PFiso  = lepton2PFiso;
                    lepton3IsTight= lepton2IsTight;

                    lepton3mvaTrigV0eID    = lepton2mvaTrigV0eID;
                    lepton3mvaNonTrigV0eID = lepton2mvaNonTrigV0eID;

                    lepton2PtRec  = lepton->pt();
                    lepton2EtaRec = lepton->eta();
                    lepton2PhiRec = lepton->phi();
///                    lepton2PFiso  = lepton->pfIsolationDeltaBeta();
                    lepton2PFiso  = lepton->pfIsolationAeff();
///                    lepton2IsTight = ( lepton->isTight() && lepton->isPFIsolated() ); 
                    lepton2IsTight = ( lepton->isGood() && lepton->isPFIsolated() ); 

                    lepton2mvaTrigV0eID    = lepton->mvaTrigV0eID();
                    lepton2mvaNonTrigV0eID = lepton->mvaNonTrigV0eID();
                 } else {
                    if( lepton3PtRec  < lepton->pt() ){
                        lepton3PtRec  = lepton->pt();
                        lepton3EtaRec = lepton->eta();
                        lepton3PhiRec = lepton->phi();
///                        lepton3PFiso  = lepton->pfIsolationDeltaBeta();
                        lepton3PFiso  = lepton->pfIsolationAeff();
///                        lepton3IsTight = ( lepton->isTight() && lepton->isPFIsolated() ); 
                        lepton3IsTight = ( lepton->isGood() && lepton->isPFIsolated() ); 

                        lepton3mvaTrigV0eID    = lepton->mvaTrigV0eID();
                        lepton3mvaNonTrigV0eID = lepton->mvaNonTrigV0eID();
                    }
                 }
              }
        }


      jet1WhPtRec=-1; 
      jet2WhPtRec=-1; 
      freeJetPtRec=-1; 

      metPtRec  = tPlusXCandidates.MET()->pt();
      metPhiRec = tPlusXCandidates.MET()->phi();
      metEtaRec = -1;


     bJetPtRec   = -1; bJetEtaRec   = 0; bJetPhiRec   = 0;
     jet1WhPtRec = -1; jet1WhEtaRec = 0; jet1WhPhiRec = 0;
     jet2WhPtRec = -1; jet2WhEtaRec = 0; jet2WhPhiRec = 0;
     whMrec      = -1; whPtRec      = -1; whEtaRec    = 0; whPhiRec = 0;
     thMrec      = -1; thPtRec      = -1; thEtaRec    = 0; thPhiRec = 0;

     if( tPlusXCandidates.passesSelectionStepUpTo(4,monotopStudySelection) ){

        if( tPlusXCandidates.recoBestHadroTop() < 0 ){
//           cout<<"Bad selection?"<<endl;
//           cout<<"type="<<type<<" run="<<run<<" lumi="<<lumi<<" event="<<event<<" numberOfJets="<<numberOfJets<<" numberOfBJets="<<numberOfBJets<<endl;
           Chi2 = -1;
        } else {

           Chi2          = tPlusXCandidates.getHadronicChi2();
           sumPt         = tPlusXCandidates.sumPt();

           if( tPlusXCandidates.dJetFromWpIndex>=0 ){
             freeJetPtRec  = tPlusXCandidates.dJetFromWp->pt();
             freeJetEtaRec = tPlusXCandidates.dJetFromWp->eta();
             freeJetPhiRec = tPlusXCandidates.dJetFromWp->phi();
           } else {
             freeJetPtRec  = -1;
             freeJetEtaRec = -1;
             freeJetPhiRec = -1;
           }

           bJetPtRec  = tPlusXCandidates.getHadronicBJet()->pt();
           bJetEtaRec = tPlusXCandidates.getHadronicBJet()->eta();
           bJetPhiRec = tPlusXCandidates.getHadronicBJet()->phi();

           jet1WhPtRec  = tPlusXCandidates.getJet1FromHadronicW()->pt();
           jet1WhEtaRec = tPlusXCandidates.getJet1FromHadronicW()->eta();
           jet1WhPhiRec = tPlusXCandidates.getJet1FromHadronicW()->phi();
           jet2WhPtRec  = tPlusXCandidates.getJet2FromHadronicW()->pt();
           jet2WhEtaRec = tPlusXCandidates.getJet2FromHadronicW()->eta();
           jet2WhPhiRec = tPlusXCandidates.getJet2FromHadronicW()->phi();

           whMrec   = tPlusXCandidates.getHadronicW()->mass();
           whPtRec  = tPlusXCandidates.getHadronicW()->pt();
           whEtaRec = tPlusXCandidates.getHadronicW()->eta();
           whPhiRec = tPlusXCandidates.getHadronicW()->phi();

           thMrec   = tPlusXCandidates.getHadronicTop()->mass();
           thPtRec  = tPlusXCandidates.getHadronicTop()->pt();
           thEtaRec = tPlusXCandidates.getHadronicTop()->eta();
           thPhiRec = tPlusXCandidates.getHadronicTop()->phi();
        }
     }


     selection = 0;
     for(int sel = monotopStudySelection.size()-1; sel >= 0; sel--)
        if( tPlusXCandidates.passesSelectionStep(monotopStudySelection[sel]) ){
           selection |= (1<<sel);
        }

     metSel = 0;
     for(int sel = monotopMetSelectionSize-1; sel >= 0; sel--)
        if( tPlusXCandidates.passesSelectionStep(monotopMetSelection[sel]) ){
           metSel |= (1<<sel);
        }

     muSel = 0;
     for(int sel = monotopMuonSelectionSize-1; sel >= 0; sel--)
        if( tPlusXCandidates.passesSelectionStep(monotopMuonSelection[sel]) ){
           muSel |= (1<<sel);
        }

     eSel = 0;
     for(int sel = monotopElectronSelectionSize-1; sel >= 0; sel--)
        if( tPlusXCandidates.passesSelectionStep(monotopElectronSelection[sel]) ){
           eSel |= (1<<sel);
        }

     if( !currentEvent.isRealData() ) {

            MCParticleCollection genParticles = tPlusXCandidates.GenParticles();

            // initialization
            dmPtGen = -1;      // DM
            t1PtGen = -1;      // top
            t2PtGen = -1;      // anti-top
            whPtGen = -1;      // W
            jet1WhPtGen = -1;  // jet1
            jet2WhPtGen = -1;  // jet2
            bJetPtGen = -1;    // b
            firstBJetPtGen = -1;
            secondBJetPtGen = -1;
            thirdBJetPtGen = -1;
            freeJetPtGen = -1; // radiation
            leadingJetPtGen = -1; // 
            nTausGen = 0;

            int quark1index = -1, quark2index = -1; // W hadronic decay indexies
            dmIndGen = -1;
            t1IndGen = -1;
            t2IndGen = -1;
            whIndGen = -1;
            bJetIndGen = -1;
            freeJetIndGen = -1;
            jet1WhIndGen  = -1;
            jet2WhIndGen  = -1;
 
            lepton1PtGen = -1;
            lepton2PtGen = -1;
            lepton3PtGen = -1;
            neutrino1PtGen = -1;
            neutrino2PtGen = -1;
            neutrino1PdgId =  0;
            neutrino2PdgId =  0;
            metPtGen = 0;

            tauPdgId = 0;       tauElePdgId = 0;    tauMuPdgId = 0;  tauNuPdgId = 0;
            tauPtGen = -1;      tauEtaGen   = 0;    tauPhiGen  = 0;
            tauElePtGen = -1;   tauEleEtaGen = 0;   tauElePhiGen = 0;
            tauMuPtGen  = -1;   tauMuEtaGen  = 0;   tauMuPhiGen  = 0;
            tauNuPtGen  = -1;   tauNuEtaGen  = 0;   tauNuPhiGen  = 0;

//if( metPtRec>250 && m3masslessJets<250 && (selection&31)==31 && thirdJetPtRec>40 && forthJetPtRec<35 && lepton1PtRec>40 && lepton1IsTight && lepton2PtRec<10 && fabs(lepton1EtaRec)<2.1 && (muTRIGs&0x80000000)==0x80000000 ){ //&& (eTRIGs&0x10)!=0x10 ){
//double MT = sqrt(2*lepton1PtRec*metPtRec*(1-cos(metPhiRec-lepton1PhiRec)));
//cout<<"Event: "<<event<<" MT="<<MT<<" lepton1PtRec="<<lepton1PtRec<<" lepton1PhiRec="<<lepton1PhiRec<<" metPtRec="<<metPtRec<<" metPhiRec="<<metPhiRec<<endl;
//}

            // loop over the generator-level particles and find prompt electron and b quarks
            for(MCParticleCollection::const_iterator pIter=genParticles.begin(); pIter!=genParticles.end(); pIter++){
                MCParticlePointer particle = *pIter;

//if( metPtRec>250 && m3masslessJets<250 && (selection&31)==31 && thirdJetPtRec>40 && forthJetPtRec<35 && lepton1PtRec>40 && lepton1IsTight && lepton2PtRec<10 && fabs(lepton1EtaRec)<2.1 && (muTRIGs&0x80000000)==0x80000000 ){ //&&(eTRIGs&0x10)!=0x10 ){ 
//cout<<" i="<<distance(MCParticleCollection::const_iterator(genParticles.begin()),pIter)<<" pdgId="<<particle->pdgId()<<" pt="<<particle->pt()<<" eta="<<particle->eta()<<" phi="<<particle->phi()<<" mother ind:"<<particle->motherId()<<" grandmother id:"<<particle->grandMotherId()<<" status: "<<particle->status()<<endl;
//}
                // dark matter
                if( abs(particle->pdgId())>=9000000 && dmPtGen<0 ){
                   dmPtGen  = particle->pt();
                   dmEtaGen = particle->eta();
                   dmPhiGen = particle->phi();
                   dmPdgId  = particle->pdgId();
                   dmIndGen = distance(MCParticleCollection::const_iterator(genParticles.begin()),pIter);
                }

                // W
                if( abs(particle->pdgId())==24 ){
                   whPtGen  = particle->pt();
                   whEtaGen = particle->eta();
                   whPhiGen = particle->phi();
                   whMgen   = particle->mass();
                   whPdgId  = particle->pdgId();
                   whIndGen = distance(MCParticleCollection::const_iterator(genParticles.begin()),pIter); 
                }

                // top
                if( particle->pdgId()==6 ){
                   t1PtGen  = particle->pt();
                   t1EtaGen = particle->eta();
                   t1PhiGen = particle->phi();
                   t1Mgen   = particle->mass();
                   t1PdgId  = particle->pdgId();
                   t1IndGen = distance(MCParticleCollection::const_iterator(genParticles.begin()),pIter); 
                }
                if( particle->pdgId()==-6 ){
                   t2PtGen  = particle->pt();
                   t2EtaGen = particle->eta();
                   t2PhiGen = particle->phi();
                   t2Mgen   = particle->mass();
                   t2PdgId  = particle->pdgId();
                   t2IndGen = distance(MCParticleCollection::const_iterator(genParticles.begin()),pIter); 
                }


                // look for the b-quark
                if( abs(particle->pdgId())==5 ){
                   int ancestor = particle->motherIndex();
                   unsigned int nJumps = 0;

                   // look only for b's from the tops
                   for(;ancestor>=0 && ancestor<100 && ancestor<int(genParticles.size()) &&
                      abs(genParticles[ancestor]->pdgId())!=5 &&
                      abs(genParticles[ancestor]->pdgId())!=6 &&
                      nJumps < genParticles.size();
                      nJumps++, ancestor = genParticles[ancestor]->motherIndex() );

                   if( ancestor>=0 && ancestor<100 && ancestor<int(genParticles.size()) && abs(genParticles[ancestor]->pdgId())==5 ) continue; // skip radiating b

                   bJetPtGen  = particle->pt();
                   bJetEtaGen = particle->eta();
                   bJetPhiGen = particle->phi();
                   bJetPdgId  = particle->pdgId();
                   bJetIndGen = distance(MCParticleCollection::const_iterator(genParticles.begin()),pIter); 

                   if( firstBJetPtGen < bJetPtGen ){
                      thirdBJetPtGen   = secondBJetPtGen;
                      thirdBJetEtaGen  = secondBJetEtaGen;
                      thirdBJetPhiGen  = secondBJetPhiGen;
                      thirdBJetPdgId   = secondBJetPdgId;
                      secondBJetPtGen  = firstBJetPtGen;
                      secondBJetEtaGen = firstBJetEtaGen;
                      secondBJetPhiGen = firstBJetPhiGen;
                      secondBJetPdgId  = firstBJetPdgId;
                      firstBJetPtGen   = bJetPtGen;
                      firstBJetEtaGen  = bJetEtaGen;
                      firstBJetPhiGen  = bJetPhiGen;
                      firstBJetPdgId   = bJetPdgId;
                   } else {
                      if( secondBJetPtGen < bJetPtGen ){
                         thirdBJetPtGen   = secondBJetPtGen;
                         thirdBJetEtaGen  = secondBJetEtaGen;
                         thirdBJetPhiGen  = secondBJetPhiGen;
                         thirdBJetPdgId   = secondBJetPdgId;
                         secondBJetPtGen  = bJetPtGen;
                         secondBJetEtaGen = bJetEtaGen;
                         secondBJetPhiGen = bJetPhiGen;
                         secondBJetPdgId  = bJetPdgId;
                      } else {
                         if( thirdBJetPtGen < bJetPtGen ){
                            thirdBJetPtGen   = bJetPtGen;
                            thirdBJetEtaGen  = bJetEtaGen;
                            thirdBJetPhiGen  = bJetPhiGen;
                            thirdBJetPdgId   = bJetPdgId;
                         }
                      }
                   }

                }

                // W hadronic decay products
                if( abs(particle->pdgId())<5 ){
                    int ancestor = particle->motherIndex();
                    unsigned int nJumps = 0;

                    for(; ancestor>=0 && ancestor<100 && ancestor<int(genParticles.size()) &&
                          abs(genParticles[ancestor]->pdgId())!=24 && // is W the parent?
                          nJumps < genParticles.size();
                          nJumps++, ancestor = genParticles[ancestor]->motherIndex() );

                    if( ancestor<0 || ancestor>=100 || ancestor>=int(genParticles.size()) || nJumps>=1 ) continue; // this is not a light quark from the hadronic W decay

                    if( quark1index < 0 )
                        quark1index = distance(MCParticleCollection::const_iterator(genParticles.begin()),pIter);
                    else {
                        if( quark2index<0 ) quark2index = distance(MCParticleCollection::const_iterator(genParticles.begin()),pIter); 
                        else {
                           quark1index = quark2index;
                           quark2index = distance(MCParticleCollection::const_iterator(genParticles.begin()),pIter); 
                        }
                    }
                }

                // possible radiation
                if( //currentEvent.getDataType() < 10                     && // only for the ttbar
                    (abs(particle->pdgId())<5 || particle->pdgId()==21) && // light flavor quark or a gluon
                    particle->pt()>30                                   && // high enough pT
                    distance(MCParticleCollection::const_iterator(genParticles.begin()),pIter)<20 // somewhere where ISR or FSR appears in the decay chain
                ){
                    int ancestor = particle->motherIndex();
                    unsigned int nJumps = 0;

                    // rewind back decay chain to see if this parton is the ISR or FSR
                    for(;ancestor>=0 && ancestor<100 && ancestor<int(genParticles.size()) &&
                        abs(genParticles[ancestor]->pdgId())!=2212 && // is ISR from proton?
                        abs(genParticles[ancestor]->pdgId())!=6    && // is FSR from top?
                        abs(genParticles[ancestor]->pdgId())!=24   && // is FSR from W?
                        nJumps < genParticles.size();
                        nJumps++, ancestor = genParticles[ancestor]->motherIndex() );

                    if( ancestor<0 || ancestor>=100 || ancestor>=int(genParticles.size()) || nJumps==genParticles.size() || nJumps>=2 || // why do I allow so many radiating steps here?
                        abs(genParticles[ancestor]->pdgId())==6 || abs(genParticles[ancestor]->pdgId())==24 ) continue; // remove FSR

                    if( freeJetPtGen>particle->pt() ) continue;

                    freeJetPtGen  = particle->pt();
                    freeJetEtaGen = particle->eta();
                    freeJetPhiGen = particle->phi();
                    freeJetPdgId  = particle->pdgId();
                    freeJetIndGen = distance(MCParticleCollection::const_iterator(genParticles.begin()),pIter); 
                }

                if( abs(particle->pdgId())==15 && (abs(particle->motherId())==24 || abs(particle->motherId())==23) ) nTausGen++;

                if( abs(particle->pdgId())==11 && abs(particle->motherId())==15 ){
                    tauElePdgId  = particle->pdgId();
                    tauElePtGen  = particle->pt();
                    tauEleEtaGen = particle->eta();
                    tauElePhiGen = particle->phi();
                }
                if( abs(particle->pdgId())==13 && abs(particle->motherId())==15 ){
                    tauMuPdgId  = particle->pdgId();
                    tauMuPtGen  = particle->pt();
                    tauMuEtaGen = particle->eta();
                    tauMuPhiGen = particle->phi();
                }
                if( abs(particle->pdgId())==16 && abs(particle->motherId())==15 ){
                    tauNuPdgId  = particle->pdgId();
                    tauNuPtGen  = particle->pt();
                    tauNuEtaGen = particle->eta();
                    tauNuPhiGen = particle->phi();
                }
                if( ( abs(particle->pdgId())==15 ) //&& particle->status()==3
 && (abs(particle->motherId())==24 || //abs(particle->grandMotherId())==24 ||
     abs(particle->motherId())==23  //abs(particle->grandMotherId())==23 || 
    )
                  ){
                    tauPdgId  = particle->pdgId();
                    tauPtGen  = particle->pt();
                    tauEtaGen = particle->eta();
                    tauPhiGen = particle->phi();
                   }


                // stable electron or muons
                if( ( abs(particle->pdgId())==11 || abs(particle->pdgId())==13 ) //&& particle->status()==3
 && (abs(particle->motherId())==24 || //abs(particle->grandMotherId())==24 ||
     abs(particle->motherId())==23 || //abs(particle->grandMotherId())==23 || 
     abs(particle->motherId())==15 //|| abs(particle->grandMotherId())==15 
    )
                  ){
//cout<<"gen lepton: pt="<<particle->pt()<<" eta="<<particle->eta()<<" phi="<<particle->phi()<<endl;
//                    int ancestor = particle->motherIndex();
//                    unsigned int nJumps = 0; // particle can radiate before it becomes stable, allow few intermediate steps in the decay chain
//                    // rewind back the decay chain to make sure this lepton is from the W or Z decay
//                    for(;ancestor>=0 && ancestor<100 && //ancestor<int(genParticles.size()) &&
//                        abs(genParticles[ancestor]->pdgId())!=24 &&  // W
//                        abs(genParticles[ancestor]->pdgId())!=23 &&  // Z
//                        nJumps < genParticles.size();
//                        nJumps++, ancestor = genParticles[ancestor]->motherIndex() );

///                    if( (particle->motherId()!=24 && particle->grandMotherId()!=24 ) ||
///                        (particle->motherId()!=23 && particle->grandMotherId()!=23 ) ) continue;
//                    if( ancestor<0 || ancestor>=100 || ancestor>=int(genParticles.size()) || nJumps==genParticles.size() || nJumps>=5 ) continue; // this is not a leptonfrom the W or Z decay
                    if( lepton1PtGen < particle->pt() ){
                       lepton2PtGen  = lepton1PtGen;
                       lepton2EtaGen = lepton1EtaGen;
                       lepton2PhiGen = lepton1PhiGen;
                       lepton2PdgId  = lepton1PdgId; 
                       lepton1PtGen  = particle->pt();
                       lepton1EtaGen = particle->eta();
                       lepton1PhiGen = particle->phi();
                       lepton1PdgId  = particle->pdgId();
                    } else {
                       if( lepton2PtGen  < particle->pt() ){
                           lepton3PtGen  = lepton2PtGen;
                           lepton3EtaGen = lepton2EtaGen;
                           lepton3PhiGen = lepton2PhiGen;
                           lepton3PdgId  = lepton2PdgId; 
                           lepton2PtGen  = particle->pt();
                           lepton2EtaGen = particle->eta();
                           lepton2PhiGen = particle->phi();
                           lepton2PdgId  = particle->pdgId();
                       } else {
                           if( lepton3PtGen  < particle->pt() ){
                               lepton3PtGen  = particle->pt();
                               lepton3EtaGen = particle->eta();
                               lepton3PhiGen = particle->phi();
                               lepton3PdgId  = particle->pdgId();
                           }
                       }
                    }
                }

                // electron or muon neutrino
                if( ( abs(particle->pdgId())==12 /*|| abs(particle->pdgId())==14*/ ) && particle->status()==3
&& ( abs(particle->motherId())==24 || abs(particle->grandMotherId())==23 )
/*noBEANs: && particle->status()==1*/ ){
///                    int ancestor = particle->motherIndex();
//                    unsigned int nJumps = 0; // can neutrino really radiate anything? anyway ...
//                    // rewind back decay chain to make sure this neutrino is from the W decay
//                    for(;ancestor>=0 && ancestor<100 && ancestor<int(genParticles.size()) &&
//                        abs(genParticles[ancestor]->pdgId())!=24 &&
//                        abs(genParticles[ancestor]->pdgId())!=15 &&
//                        nJumps < genParticles.size();
//                        nJumps++, ancestor = genParticles[ancestor]->motherIndex() );
//                    if( ancestor<0 || ancestor>=100 || ancestor>=int(genParticles.size()) || nJumps==genParticles.size() || nJumps>=5 ) continue; // this is not a neutrino from the W decay
                    if( neutrino1PtGen<particle->pt() && particle->pdgId()>0 ){
                        neutrino1PdgId  = particle->pdgId();
                        neutrino1PtGen  = particle->pt();
                        neutrino1EtaGen = particle->eta();
                        neutrino1PhiGen = particle->phi();
                    }
                    if( neutrino2PtGen<particle->pt() && particle->pdgId()<0 ){
                        neutrino2PdgId  = particle->pdgId();
                        neutrino2PtGen  = particle->pt();
                        neutrino2EtaGen = particle->eta();
                        neutrino2PhiGen = particle->phi();
                    }
                }

                if( ( abs(particle->pdgId())==12 || abs(particle->pdgId())==14 || abs(particle->pdgId())==16 ) && particle->status()==1 ){
                    TLorentzVector met, neu;
                    met.SetPtEtaPhiM( metPtGen, metEtaGen, metPhiGen, 0 );
                    neu.SetPtEtaPhiM( particle->pt(), particle->eta(), particle->phi(), 0);
                    met += neu;
                    metPtGen  = met.Pt();
                    metEtaGen = met.Eta();
                    metPhiGen = met.Phi();
                }

            }

            // reorder neutrinos in pT
            if( neutrino1PtGen<neutrino2PtGen && neutrino1PdgId!=0 ){
                int    tmpPdgId = neutrino2PdgId;
                double tmpPtGen = neutrino2PtGen;
                double tmpEtaGen= neutrino2EtaGen;
                double tmpPhiGen= neutrino2PhiGen;
                neutrino2PdgId  = neutrino1PdgId;
                neutrino2PtGen  = neutrino1PtGen;
                neutrino2EtaGen = neutrino1EtaGen;
                neutrino2PhiGen = neutrino1PhiGen;
                neutrino1PdgId  = tmpPdgId;
                neutrino1PtGen  = tmpPtGen;
                neutrino1EtaGen = tmpEtaGen;
                neutrino1PhiGen = tmpPhiGen;
            }

            // fill in the fields for the hadronic W decay jets
            if( quark1index>=0 && quark2index>=0 ){
                if( genParticles[quark1index]->pt() > genParticles[quark2index]->pt() ){
                    jet1WhPtGen  = genParticles[quark1index]->pt();
                    jet1WhEtaGen = genParticles[quark1index]->eta();
                    jet1WhPhiGen = genParticles[quark1index]->phi();
                    jet1WhPdgId  = genParticles[quark1index]->pdgId();
                    jet2WhPtGen  = genParticles[quark2index]->pt();
                    jet2WhEtaGen = genParticles[quark2index]->eta();
                    jet2WhPhiGen = genParticles[quark2index]->phi();
                    jet2WhPdgId  = genParticles[quark2index]->pdgId();
                    jet1WhIndGen = quark1index;
                    jet2WhIndGen = quark2index;
                } else {
                    jet1WhPtGen  = genParticles[quark2index]->pt();
                    jet1WhEtaGen = genParticles[quark2index]->eta();
                    jet1WhPhiGen = genParticles[quark2index]->phi();
                    jet1WhPdgId  = genParticles[quark2index]->pdgId();
                    jet2WhPtGen  = genParticles[quark1index]->pt();
                    jet2WhEtaGen = genParticles[quark1index]->eta();
                    jet2WhPhiGen = genParticles[quark1index]->phi();
                    jet2WhPdgId  = genParticles[quark1index]->pdgId();
                    jet1WhIndGen = quark2index;
                    jet2WhIndGen = quark1index;
                }
            } else {
                jet1WhPtGen  = -1;
                jet1WhEtaGen =  0;
                jet1WhPhiGen =  0;
                jet2WhPtGen  = -1;
                jet2WhEtaGen =  0;
                jet2WhPhiGen =  0;
                jet1WhPdgId  =  0;
                jet2WhPdgId  =  0;
                jet1WhIndGen = -1;
                jet2WhIndGen = -1;
            }

            // select the highest pT generator parton producing a single jet
            leadingJetPtGen  = -1;
            leadingJetEtaGen =  0;
            leadingJetPhiGen =  0;
            leadingJetIndGen = -1;
            leadingJetPdgId  =  0;
            if( jet1WhPtGen > bJetPtGen && jet1WhPtGen > freeJetPtGen ){
                leadingJetPtGen  = jet1WhPtGen;
                leadingJetEtaGen = jet1WhEtaGen;
                leadingJetPhiGen = jet1WhPhiGen;
                leadingJetIndGen = jet1WhIndGen;
                leadingJetPdgId  = jet1WhPdgId;
            }
            if( jet1WhPtGen > bJetPtGen && jet1WhPtGen < freeJetPtGen ){
                leadingJetPtGen  = freeJetPtGen;
                leadingJetEtaGen = freeJetEtaGen;
                leadingJetPhiGen = freeJetPhiGen;
                leadingJetIndGen = freeJetIndGen;
                leadingJetPdgId  = freeJetPdgId;
            }
            if( jet1WhPtGen < bJetPtGen && jet1WhPtGen > freeJetPtGen ){
                leadingJetPtGen  = bJetPtGen;
                leadingJetEtaGen = bJetEtaGen;
                leadingJetPhiGen = bJetPhiGen;
                leadingJetIndGen = bJetIndGen;
                leadingJetPdgId  = bJetPdgId;
            }

        if( tauPtGen >= 0){
        tauJetDR = 999;
        for( JetCollection::const_iterator jet  = tPlusXCandidates.GoodJets().begin();
                                           jet != tPlusXCandidates.GoodJets().end();
                                           jet ++ ){
           double newDist = sqrt(( tauEtaGen - (*jet)->eta()) * ( tauEtaGen - (*jet)->eta() ) + ( tauPhiGen - (*jet)->phi() ) * ( tauPhiGen - (*jet)->phi() ));
           if( tauJetDR > newDist ){
               tauJetDR = newDist;
               tauJetPtRec  = (*jet)->pt();
               tauJetEtaRec = (*jet)->eta();
               tauJetPhiRec = (*jet)->phi();
           }
        }
        } else {
               tauJetPtRec = -1;
               tauJetEtaRec = 0;
               tauJetPhiRec = 0;
               tauJetDR = -1;
        }


     }

//if( metPtRec>250 && m3masslessJets<250 && (selection&31)==31 && thirdJetPtRec>40 && forthJetPtRec<35 && lepton1PtRec>40 && lepton1IsTight && lepton2PtRec<10 && fabs(lepton1EtaRec)<2.1 && (muTRIGs&0x80000000)==0x80000000 ){ //&& (eTRIGs&0x10)!=0x10 ){ //
//double MT = sqrt(2*lepton1PtGen*metPtGen*(1-cos(metPhiGen-lepton1PhiGen)));
//cout<<"        MTgen="<<MT<<" lepton1PtGen="<<lepton1PtGen<<" lepton1PhiGen="<<lepton1PhiGen<<" metPtGen="<<metPtGen<<" metPhiGen="<<metPhiGen<<" nTausGen="<<nTausGen<<endl;
//}

     microTuple->Fill();
}

	
void Analysis::printSummary() {
/*
    EventTablePrinter::printWprimeCutFlow(cutflowPerSample, weights,
			toplikeElectronSelection, toplikeElectronSelSize, "Electron", luminosity);
    EventTablePrinter::printWprimeCutFlowUnwt(cutflowPerSample, weights,
			toplikeElectronSelection, toplikeElectronSelSize, "Electron");
    EventTablePrinter::printWprimeCutFlow(mucutflowPerSample, weights,
			toplikeMuonSelection, toplikeMuonSelSize, "Muon", luminosity);
    EventTablePrinter::printWprimeCutFlowUnwt(mucutflowPerSample, weights,
			toplikeMuonSelection, toplikeMuonSelSize, "Muon");
*/
    EventTablePrinter::printWprimeCutFlow(cutflowPerSample, weights,
			monotopStudySelection, "", luminosity);
    EventTablePrinter::printWprimeCutFlowUnwt(cutflowPerSample, weights,
			monotopStudySelection, "");

    // EventTablePrinter::printCutFlowLatexTable(cutflowPerSample);
    // EventTablePrinter::printUnweightedCutFlowLatexTable(cutflowPerSample);

    cout << "total number of processed events: " << eventReader->getNumberOfProccessedEvents() << endl;
    cout << endl;
    for (unsigned int cut = 0; cut < monotopStudySelection.size(); ++cut) {
        cout << "Selection step '" << ToplikeSelectionSteps::StringSteps[monotopStudySelection[cut]] << "'" << endl;
        cout << "passed events (single cut): " << singleCuts.at(cut) << endl;
        if (cut < monotopStudySelection.size()- 2)
            cout << "passed events (up to this cut):" << cutflow.at(cut) << endl;
        else
            cout << "passed events (full selection):" << cutflow.at(cut) << endl;
        cout << endl;
    }

    cout << "number of events without electrons: " << brokenEvents.size() << endl;
    cout << "\n\n Number of positive, negative W' tops: " << wpTopPos << ", " << wpTopNeg << endl;
    cout << "\n\n Number of positive, negative spectator tops: " << specTopPos << ", " << specTopNeg << endl;
}

Analysis::Analysis(const std::vector<BAT::ToplikeSelectionSteps::Step> &selection, BAT::EventWeightProvider::SampleVersion sampleVersion) :
    monotopStudySelection(selection),
    eventReader(new NTupleEventReader()),
//    eventFilter(Filter::makeTopPairEPlusJetsFilter()),
    currentEvent(),
    ttbarCandidate(),
    cutflow(),
    singleCuts(),
    cutflowPerFile(),
    singleCutsPerFile(),
    mucutflow(),
    musingleCuts(),
    mucutflowPerFile(),
    musingleCutsPerFile(),
    interestingEvents(),
    brokenEvents(),
    eventCheck(),
    weights(Analysis::luminosity, sampleVersion),
    weight(0),
    cutflowPerSample(DataType::NUMBER_OF_DATA_TYPES, monotopStudySelection.size() + 1,
                    JetBin::NUMBER_OF_JET_BINS),
    mucutflowPerSample(DataType::NUMBER_OF_DATA_TYPES, monotopStudySelection.size() + 1,
                    JetBin::NUMBER_OF_JET_BINS),
			// Cut flows have extra element for original # of data events.
			// Bigger electron size used for muons to be safe

		wpTopPos(0),
		wpTopNeg(0),
		specTopPos(0),
		specTopNeg(0)
{
    //    outputfile->SetCompressionLevel(7);
    for (unsigned int cut = 0; cut < monotopStudySelection.size() ; ++cut) {
        cutflow[cut] = 0;
        singleCuts[cut] = 0;
    }
    for (unsigned int cut = 0; cut < monotopStudySelection.size(); ++cut) {
        mucutflow[cut] = 0;
        musingleCuts[cut] = 0;
    }
    finalized = false;
}

Analysis::~Analysis() {
   finalize();
}

void Analysis::addInputFile(const char* fileName) {
    eventReader->addInputFile(fileName);
}

void Analysis::setMaximalNumberOfEvents(long maxEvents) {
    if (maxEvents > 0) {
        eventReader->setMaximumNumberOfEvents(maxEvents);
    }
}

void Analysis::setUsedNeutrinoSelectionForTopPairReconstruction(NeutrinoSelectionCriterion::value selection) {
    TopPairEventCandidate::usedNeutrinoSelection = selection;
}

void Analysis::setUsedTTbarReconstructionCriterion(TTbarReconstructionCriterion::value selection) {
	TopPairEventCandidate::usedTTbarReconstruction = selection;
}

void Analysis::checkForDuplicatedEvents(){
    map<unsigned long, std::vector<unsigned long> >::const_iterator iter;
    std::vector<pair<unsigned long, unsigned long> > duplicateEvents;

    for(iter = eventCheck.begin(); iter != eventCheck.end(); ++iter){
        std::vector<unsigned long> events = (*iter).second;
        std::sort(events.begin(), events.end());
        for(unsigned long ev = 0; ev < events.size() -1; ++ev){
            if(events.at(ev) == events.at(ev +1)){
                duplicateEvents.push_back(make_pair((*iter).first, events.at(ev)));
            }
        }
    }

    if (duplicateEvents.size() > 0){
        cout << "found duplicate events" << endl;
        for(unsigned long ev = 0; ev < duplicateEvents.size() -1; ++ev){
            cout << "run: " << duplicateEvents.at(ev).first << " event: " << duplicateEvents.at(ev).second << endl;
        }
    }
}

void Analysis::checkForBrokenEvents(){
    if(ttbarCandidate.Electrons().size() == 0){
        brokenEvents.push_back(InterestingEvent(ttbarCandidate, eventReader->getCurrentFile()));
    }

    if(ttbarCandidate.eventnumber() == 1019245){
        cout << "broken event" << endl;
        ttbarCandidate.inspect();
    }
}


void Analysis::sumPDFWeights(void) {
	if (currentEvent.isRealData() == false) {
		unsigned int numWts = currentEvent.pdfWeights->size();
if( numWts!=44 ){ cout<<"Non CTEQ PDF:"<<numWts<<endl; return; }
bzero(pdfWeights,44*sizeof(double));
		for (unsigned int index = 0; index <= numWts; ++index) {
			double wt = 1.0;
			if (index > 0)
				wt = currentEvent.pdfWt(index - 1);
pdfWeights[index] = wt;
			pdfWtAll[index] += wt;
                        if( tPlusXCandidates.passesSelectionStepUpTo(4,monotopStudySelection) &&
                            currentEvent.GoodBJets().size() == 1 &&
                            tPlusXCandidates.MET()->pt() > 250 //&&
//                            thMrec < 220 && thMrec>0 
                          )
				pdfWtSel[index] += wt;
		}
	}
}

//void Analysis::sumQ2Weights(int stage, int nb, double met, double mTop){
void Analysis::sumQ2Weights(void) {
    if (currentEvent.isRealData() == false) {
        q2upWtAll   += currentEvent.getWeightQ2ScaleUp();
        q2downWtAll += currentEvent.getWeightQ2ScaleDown();
        if( tPlusXCandidates.passesSelectionStepUpTo(4,monotopStudySelection) &&
            currentEvent.GoodBJets().size() == 1 &&
            tPlusXCandidates.MET()->pt() > 250 &&
            thMrec < 220 && thMrec>0 ){
           q2upWtSel   += currentEvent.getWeightQ2ScaleUp();
           q2downWtSel += currentEvent.getWeightQ2ScaleDown();
	}
    }
}

void Analysis::doQ2SystemStudy(void) const {
   cout<<"Q2 scale variation: up="<<q2upWtSel<<"/"<<q2upWtAll<<" down="<<q2downWtSel<<"/"<<q2downWtAll<<endl;
}

void Analysis::doPDfSystemStudy(void) const {
        std::vector<double> weights = pdfWtSel;
	double baseNumEvts = weights[0];
	if (baseNumEvts <= 0.0) {
		cout << "No events processed\n";
		return;
	}
	unsigned int numPairs = (weights.size() - 1) / 2;
	double wplus = 0.0, wminus = 0.0;
	for (unsigned int index = 0; index < numPairs; ++index) {
		double wa = (weights[(2 * index) + 1] / baseNumEvts) - 1.0;
		double wb = (weights[(2 * index) + 2] / baseNumEvts) - 1.0;
		if (wa < wb) {
			double tmp = wa;
			wa = wb;
			wb = tmp;
		}
		if (wa < 0.0)
			wa = 0.0;
		if (wb > 0.0)
			wb = 0.0;
		wplus += wa * wa;
		wminus += wb * wb;
	}
	if (wplus > 0)
		wplus = sqrt(wplus);
	if (wminus > 0)
		wminus = sqrt(wminus);
	cout << "PDF uncertainty: +" << wplus;
	cout << " -" << wminus << endl;
	cout << "Using " << numPairs << " eigenvectors\n";
}
