/*
 * CrossSections.h
 *
 *  Created on: 29 Jul 2010
 *      Author: kreczko
 */

#ifndef EVENTWEIGHTPROVIDER_H_
#define EVENTWEIGHTPROVIDER_H_
//https://twiki.cern.ch/twiki/bin/view/CMS/CrossSections_3XSeries#crosssections

#include "DataTypes.h"
#include <vector>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include "TH1D.h"

//#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "../LumiReweightingStandAlone.h"

namespace BAT {
extern boost::array<float, DataType::NUMBER_OF_DATA_TYPES> getXSections();


class EventWeightProvider{
public:
    enum SampleVersion { central=0, scaleUp=1, scaleDown=2, matchingUp=3, matchingDown=4};
    static const char* truePUdistfile;

private:
    float lumiInInversePb;
    SampleVersion sampleVersion;
    bool useSkimEff;
    boost::array<double, DataType::NUMBER_OF_DATA_TYPES> xsection;
    boost::array<double, 60> pileUpWeights;
    unsigned long numberOfEventsWithTooHighPileUp;
//    void defineNumberOfSkimmedEvents();
    void defineNumberOfProducedEvents();

    int currentMCscheme;
    int currentReweightingModel;
    enum {flat10=1, truePileUp2011=2, observedPileUp2011=3, truePileUp2012=4};

//    edm::LumiReWeighting officialReWighter;
    reweight::LumiReWeighting officialReWighter;

public:
    // event weight, given initialization is done
    float reweightPileUp(unsigned int numberOfVertices);
    float reweightPileUpOfficial(unsigned int numberOfVertices);

    // initialization, choose one of 3 at any time:
    void generate_flat10_weights            (void); // for signal fast sim samples
    void generate_truePileUp2011_weights    (void); // for signal Fall11 MC samples
    void generate_observedPileUp2011_weights(void); // for background Summer11 MC samples
    enum PileUp {S6=6, S7=7, S10=10};
    void generate_truePileUp2012_weights    (PileUp mcScheme); //


//    void useSkimEfficiency(bool use);

//    float getExpectedNumberOfEvents(DataType::value type);
    double getWeight(DataType::value type);
    boost::shared_ptr<TH1D> getPileUpHistogram(std::string pileUpEstimationFile);
    unsigned long getNumberOfEventsWithTooHighPileUp() const;
    boost::array<unsigned long, DataType::NUMBER_OF_DATA_TYPES> numberOfProcessedEvents;
    boost::array<unsigned long, DataType::NUMBER_OF_DATA_TYPES> numberOfPattplSkimEvents;
    boost::array<unsigned long, DataType::NUMBER_OF_DATA_TYPES> numberOfNtplSkimEvents;
    boost::array<unsigned long, DataType::NUMBER_OF_DATA_TYPES> numberOfElectronSkimEvents;
    boost::array<unsigned long, DataType::NUMBER_OF_DATA_TYPES> numberOfMuonSkimEvents;

    EventWeightProvider(float lumiInInversePb, SampleVersion version = central );
    ~EventWeightProvider();
};
}

#endif /* EVENTWEIGHTPROVIDER_H_ */
