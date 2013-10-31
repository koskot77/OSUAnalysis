/*
 * NTupleEventReader.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */
#include <iostream>
#include <string.h>
#include <dirent.h>
#include <fnmatch.h>
#include <libgen.h>
#include <boost/shared_ptr.hpp>

#include "TFile.h"
#include "TChainElement.h"
#include "TSystem.h"

#include <FWCore/FWLite/interface/AutoLibraryLoader.h> 

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"

#include "ProductArea/BNcollections/interface/BNevent.h"
#include "ProductArea/BNcollections/interface/BNtrigger.h"


#include "../../interface/Readers/NTupleEventReader.h"
/*
namespace LHAPDF {
        void initPDFSet(int nset, const std::string& filename, int member=0);
        int numberPDF(int nset);
        void usePDFMember(int nset, int member);
        double xfx(int nset, double x, double Q, int fl);
        double getXmin(int nset, int member);
        double getXmax(int nset, int member);
        double getQ2min(int nset, int member);
        double getQ2max(int nset, int member);
        void extrapolate(bool extrapolate=true);
}
*/
using namespace std;
namespace BAT {

const char * NTupleEventReader::EVENT_CHAIN = "rootTupleTree/tree";

JetAlgorithm::value NTupleEventReader::jetAlgorithm =
	JetAlgorithm::Calo_AntiKT_Cone05;
ElectronAlgorithm::value NTupleEventReader::electronAlgorithm =
	ElectronAlgorithm::Calo;
eIDMethod::value NTupleEventReader::electronIDUsed = eIDMethod::VBTF;
METAlgorithm::value NTupleEventReader::metAlgorithm = METAlgorithm::Calo;
MuonAlgorithm::value NTupleEventReader::muonAlgorithm = MuonAlgorithm::Default;
bool NTupleEventReader::loadTracks = false;
bool NTupleEventReader::useLHAPDF  = true;

NTupleEventReader::NTupleEventReader() :
    processedEvents(0),
    maximalNumberOfEvents(999999999),
    currentEventEntry(0),
    numberOfFiles(0),
    input(new TChain(NTupleEventReader::EVENT_CHAIN)),
    hltReader(new VariableReader<MultiIntPointer>(input, "Trigger.HLTResults")),
    pdfWtReader(new VariableReader<MultiDoublePointer>(input,
    	"Event.PDFWeights")),
    vertexReader(new VertexReader(input)),
    trackReader(new TrackReader(input)),
    electronReader(new ElectronReader(input, NTupleEventReader::electronAlgorithm)),
    loosePFelectronReader(new ElectronReader(input, ElectronAlgorithm::LoosePF)),
    genParticleReader(new GenParticleReader(input)),
    jetReader(new JetReader(input, NTupleEventReader::jetAlgorithm)),
    genJetReader(new GenJetReader(input)),
    muonReader(new MuonReader(input, NTupleEventReader::muonAlgorithm)),
    metReader(new METReader(input, NTupleEventReader::metAlgorithm)),
    runNumberReader(new VariableReader<unsigned int> (input, "Event.Run")),
    eventNumberReader(new VariableReader<unsigned int> (input, "Event.Number")),
    lumiBlockReader(new VariableReader<unsigned int> (input, "Event.LumiSection")),
//    beamScrapingReader(new VariableReader<bool> (input, "isBeamScraping")),
    PileupInfoReader(new VariableReader<unsigned int> (input,
    	"Event.PileUpInteractions")),
    TruePileupInfoReader(new VariableReader<unsigned int> (input,
    	"Event.TruePileUpInteractions")),
    Q2ScaleUpWgt  (new VariableReader<double>(input, "Event.Q2ScaleUpWgt")),
    Q2ScaleDownWgt(new VariableReader<double>(input, "Event.Q2ScaleDownWgt")),
    areReadersSet(false),
    areDatatypesKnown(false),
    currentRunNumber(-1),
    currentEvent(),
    currentTrigger(new Trigger()),
    seenDataTypes() {
///      if( useLHAPDF ) ///
///        LHAPDF::initPDFSet(1, "cteq66.LHgrid"); ///
}

NTupleEventReader::~NTupleEventReader() {
}

void NTupleEventReader::addInputFile(const char * fileName) {
	/*
    unsigned long filesAdded = input->Add(fileName, -1);
    	//-1 == number of events is not read!
    if (filesAdded <= 0)
        throw NoFileFoundException("No file found in '" + TString(fileName) +
        	"'");
    numberOfFiles += filesAdded;
    */
		// For BEANs
      char *path1 = strdup(fileName);
      char *path2 = strdup(fileName);

      const char *dir  = dirname(path1);
      const char *file = basename(path2);

      DIR *dp;
      if((dp = opendir(dir)) == NULL) {
         cout<<"Error while opening directory "<<dir<<endl;
         return;
      }
      struct dirent *dirp;
      while((dirp = readdir(dp)) != NULL) {
         if( fnmatch(file, dirp->d_name, 0) ) continue;
         samplefiles.push_back(string(dir)+"/"+dirp->d_name);
         numberOfFiles++;
      }
      closedir(dp);
      free(path1);
      free(path2);
}

void NTupleEventReader::addInputFileWithoutCheck(const char * fileName) {
    // numberOfFiles += input->Add(fileName);
    addInputFile(fileName);
}

const Event& NTupleEventReader::getNextEvent() {
    currentEvent = Event();
    selectNextNtupleEvent();
///    cout << "End of evtchain? " << evtchain->atEnd() << endl;

///    cout << "Opening BNevent\n";
    fwlite::Handle<BNeventCollection> h_event;
    h_event.getByLabel(*evtchain,"BNproducer");
    const BNevent *const evtstruc = &h_event->at(0);

    boost::shared_ptr<std::vector<int> > triggers(new std::vector<int>());
    boost::shared_ptr<std::vector<std::string> > trignames(new std::vector<std::string>());
    boost::shared_ptr<std::vector<int> > prescales(new std::vector<int>());

    fwlite::Handle<BNtriggerCollection> h_trig;
    h_trig.getByLabel(*evtchain,"BNproducer","HLT");

    for(unsigned int i = 0; i < h_trig->size(); i++){
       const BNtrigger *const trigstruc = &h_trig->at(i);
       triggers->push_back(trigstruc->pass);
       if( evtstruc->run != currentRunNumber ){ // menu can only change between runs 
           trignames->push_back(trigstruc->name);
           prescales->push_back(trigstruc->prescale);
       }
    }
    if( evtstruc->run != currentRunNumber ){ // menu can only change between runs 
       currentTrigger->resynch(trignames, prescales);
       currentRunNumber = evtstruc->run;
    }
    currentTrigger->setHLTs(triggers);
    currentEvent.setHLT(currentTrigger);

    currentEvent.setDataType(getDataType(getCurrentFile()));
    currentEvent.setVertices(vertexReader->getVertices(evtchain));

    if(NTupleEventReader::loadTracks)
        currentEvent.setTracks(trackReader->getTracks(evtchain));
    currentEvent.setElectrons(electronReader->getElectrons(evtchain));
    // currentEvent.setLoosePFElectrons(loosePFelectronReader->getElectrons());

    if(!currentEvent.isRealData()) {
    	currentEvent.setGenParticles(genParticleReader->getGenParticles(evtchain));
    	currentEvent.setGenJets(genJetReader->getGenJets(evtchain));
	currentEvent.setGenNumberOfPileUpVertices(evtstruc->numGenPV);
	currentEvent.setTrueNumberOfPileUpVertices(evtstruc->numTruePV);
			boost::shared_ptr<std::vector<double> > pdfWts(new std::vector<double>());
//			for(unsigned int i = 0; i < pdfWtReader->size(); i++)
//					pdfWts->push_back(pdfWtReader->getVariableAt(i));
/*
if( useLHAPDF ){
                        double w0 = 1.0;
                        for(int i=0; i <=44; ++i){
                            LHAPDF::usePDFMember(1,i);
                            double xpdf1 = LHAPDF::xfx(1, evtstruc->x1, evtstruc->qScale, evtstruc->id1);
                            double xpdf2 = LHAPDF::xfx(1, evtstruc->x2, evtstruc->qScale, evtstruc->id2);
                            double weight = 1.0;
                            if (i > 0) {
                                   weight = xpdf1 * xpdf2 / w0;
                                   pdfWts->push_back(weight);
                            } else w0 = xpdf1 * xpdf2;
//std::cout<<"x1="<<evtstruc->x1<<" x2="<<evtstruc->x2<<" qScale="<<evtstruc->qScale<<" id1="<<evtstruc->id1<<" id2="<<evtstruc->id2<<" PDF weight = "<<weight<<std::endl;
                        }

} else */ pdfWts->resize(44);
			currentEvent.setPDFWts(pdfWts);

    }
    currentEvent.setJets(jetReader->getJets(evtchain));
    currentEvent.setMuons(muonReader->getMuons(evtchain));
    currentEvent.setMET(metReader->getMET(evtchain));
    currentEvent.setRunNumber(evtstruc->run);
    currentEvent.setEventNumber(evtstruc->evt);
    currentEvent.setQ2Scales(evtstruc->Q2ScaleUpWgt,evtstruc->Q2ScaleDownWgt);
    currentEvent.setLocalEventNumber(currentEventEntry);
    currentEvent.setLumiBlock(evtstruc->lumi);
    currentEvent.setBeamScrapingVeto(false);

    return currentEvent;
}

void NTupleEventReader::selectNextNtupleEvent() {
    // if (hasNextEvent()) {
        // initiateReadersIfNotSet();
        // input->GetEntry(currentEventEntry);
   // } else cout << "End of events\n";
}

bool NTupleEventReader::hasNextEvent() {
    if (numberOfFiles == 0)
        throw NoFileFoundException("No input file found!");
    // bool hasNextInNTuple = input->LoadTree(currentEventEntry) >= 0;
    bool isWithinEventRange = currentEventEntry < maximalNumberOfEvents;
		if (currentEventEntry <= 0) {
			gSystem->Load("libFWCoreFWLite.so"); 
			AutoLibraryLoader::enable();
			gSystem->Load("libDataFormatsFWLite.so");
			gSystem->Load("libDataFormatsPatCandidates.so");
			evtchain = new fwlite::ChainEvent(samplefiles);
			cout << "Go to first event\n";
			evtchain->toBegin();
		} else ++(*evtchain);
		static TString prevFile;
		const char *currFile = getCurrentFile();
		if (prevFile != currFile) {
			cout << "Loaded file: " << currFile << endl;
			prevFile = currFile;
		}
		currentEventEntry++;
		processedEvents++;
		return (isWithinEventRange && (currentEventEntry <= 0 || 
			(evtchain != 0 && evtchain->atEnd() == false)));
    // return hasNextInNTuple && isWithinEventRange;
}

void NTupleEventReader::initiateReadersIfNotSet() {
		areReadersSet = true;
			// Readers are obsolete.
    if (areReadersSet == false) {
        input->SetBranchStatus("*", 0);
        hltReader->initialise();
        pdfWtReader->initialiseBlindly();
        vertexReader->initialise();
        if(NTupleEventReader::loadTracks)
            trackReader->initialise();
        electronReader->initialise();
        // loosePFelectronReader->initialise();
        genParticleReader->initialise();
        jetReader->initialise();
        genJetReader->initialise();
        muonReader->initialise();
        metReader->initialise();
        runNumberReader->initialise();
        eventNumberReader->initialise();
        lumiBlockReader->initialise();
        PileupInfoReader->initialiseBlindly();
        TruePileupInfoReader->initialiseBlindly();
//        beamScrapingReader->initialise();
        areReadersSet = true;
    }

}

DataType::value NTupleEventReader::getDataType(const std::string filename) {
    DataType::value filetype = DataType::DATA;

    for (unsigned int index = 0; index < DataType::names.size(); ++index) {
        const std::string searchString(DataType::names.at(index));

        if (filename.find(searchString) != std::string::npos) {
            filetype = (DataType::value) index;
        }
    }
    return filetype;
}

unsigned long NTupleEventReader::getNumberOfProccessedEvents() const {
    return processedEvents;
}

unsigned long NTupleEventReader::getCurrentLocalEventNumber() const {
    return currentEventEntry;
}

void NTupleEventReader::skipNumberOfEvents(unsigned long skipNextNEvents) {
    currentEventEntry += skipNextNEvents;
}

void NTupleEventReader::setMaximumNumberOfEvents(unsigned long maxNumberOfEvents) {
    maximalNumberOfEvents = maxNumberOfEvents;
}

const boost::array<bool, DataType::NUMBER_OF_DATA_TYPES>& NTupleEventReader::getSeenDatatypes() {
    if (areDatatypesKnown == false) {
        readDataTypes();
        areDatatypesKnown = true;
    }
    return seenDataTypes;
}

void NTupleEventReader::readDataTypes() {
	/*
    TIter nextFile(input->GetListOfFiles());
    TChainElement* file = 0;
    while ((file = (TChainElement*) nextFile()) != 0) {
        string fileName = file->GetTitle();
        DataType::value type = getDataType(fileName);
        seenDataTypes.at(type) = true;
    }
    */
	for (unsigned int index = 0; index < samplefiles.size(); ++index) {
        DataType::value type = getDataType(samplefiles.at(index));
        seenDataTypes.at(type) = true;
	}
}

const char* NTupleEventReader::getCurrentFile() const {
	/*
	if (input->GetCurrentFile() == 0)
		throw NoFileFoundException("Tried to access nonexistent file.");
    return input->GetCurrentFile()->GetName();
    */
	if (evtchain == 0 || evtchain->getTFile() == 0)
		throw NoFileFoundException("Tried to access nonexistent file.");
	return evtchain->getTFile()->GetName();
}
}
