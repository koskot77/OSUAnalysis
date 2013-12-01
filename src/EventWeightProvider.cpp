/*
 * CrossSections.cpp
 *
 *  Created on: 13 Aug 2010
 *      Author: kreczko
 */

#include "../interface/EventWeightProvider.h"
#include "TFile.h"
#include <boost/scoped_ptr.hpp>
#include <iostream>

namespace BAT {

const char* EventWeightProvider::truePUdistfile = "pileup_JSON_PromptReco_190456-208686.root";
const char *const observedPUdistfile = "Cert_160404-180252_7TeV_Collisions11_AllJSON_73p5mb_observed.root";

using namespace reweight;

boost::array<float, DataType::NUMBER_OF_DATA_TYPES> getXSections() {
    boost::array<float, DataType::NUMBER_OF_DATA_TYPES> xsection;
    xsection[DataType::DATA]   = 0;
    xsection[DataType::TTJets] = 245.8;
    xsection[DataType::ZJets]  = 3503.71;

    xsection[DataType::TTJets_HadronicMGDecays] = 111.4;
    xsection[DataType::TTJets_SemiLeptMGDecays] = 107.61;
    xsection[DataType::TTJets_FullLeptMGDecays] = 25.99;
    xsection[DataType::BN_TTJets_FullLeptMGDecays] = 25.99;

    xsection[DataType::ZJetsHT50to100]  = 381.2;
    xsection[DataType::ZJetsHT100to200] = 160.3;
    xsection[DataType::ZJetsHT200to400] = 41.49;
    xsection[DataType::ZJetsHT400toInf] = 5.274;

    xsection[DataType::WJets]  = 37509.0; // https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat8TeV
    xsection[DataType::W1Jets] = 5400;
    xsection[DataType::W2Jets] = 1750;
    xsection[DataType::W3Jets] =  519;
    xsection[DataType::W4Jets] =  214;
    xsection[DataType::QCD_Pt15to3000] = 29981599700;
//    xsection[DataType::QCD_Pt120to170] = 156293.3;
    xsection[DataType::QCD_Pt170to300] = 34138.15;
    xsection[DataType::QCD_Pt300to470] = 1759.549;
    xsection[DataType::QCD_Pt470to600] = 113.8791;
    xsection[DataType::QCD_Pt600to800] = 26.9921;
    xsection[DataType::QCD_Pt800to1000] = 3.550036;
    xsection[DataType::QCD_Pt1000to1400] = 0.737844;
    xsection[DataType::QCD_Pt1400to1800] = 0.03352235;

    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat8TeV
    xsection[DataType::WWtoAnything] = 54.838;
    xsection[DataType::WZtoAnything] = 32.3161;
    xsection[DataType::ZZtoAnything] = 8.059;

    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat8TeV
    xsection[DataType::singleTop_And_W] = 11.1;
    xsection[DataType::singleTbar_And_W] = 11.1;
    xsection[DataType::singleTopTChannel] = 56.4;
    xsection[DataType::singleTbarTChannel] = 30.7;
    xsection[DataType::singleTopSChannel] = 3.79;
    xsection[DataType::singleTbarSChannel] = 1.76;

    // private MadGraph cross-sections
    xsection[DataType::WHadr] = 32220.;
    xsection[DataType::WJetsHadr] = 2088.;

    xsection[DataType::S4_0  ] = 93.26;
    xsection[DataType::S4_50 ] = 110.0;
    xsection[DataType::S4_100] = 36.37;
    xsection[DataType::S4_150] = 17.46;
    xsection[DataType::S4_200] = 9.357;
    xsection[DataType::S4_300] = 3.216;
    xsection[DataType::S4_400] = 1.304;
    xsection[DataType::S4_500] = 0.607;
    xsection[DataType::S4_600] = 0.298;
    xsection[DataType::S4_700] = 0.1578;
    xsection[DataType::S4_800] = 0.08733;
    xsection[DataType::S4_900] = 0.05012;
    xsection[DataType::S4_1000]= 0.02969;

    xsection[DataType::S4_0_jets  ] = 100.0;
    xsection[DataType::S4_50_jets ] = 133.8;
    xsection[DataType::S4_100_jets] = 41.67;
    xsection[DataType::S4_150_jets] = 18.46;
    xsection[DataType::S4_200_jets] = 9.687;
    xsection[DataType::S4_300_jets] = 3.289;
    xsection[DataType::S4_500_jets] = .6325;

    xsection[DataType::S3_0  ] = 6.314;
    xsection[DataType::S3_50 ] = 5.072;
    xsection[DataType::S3_100] = 3.406;
    xsection[DataType::S3_150] = 2.227;
    xsection[DataType::S3_200] = 1.447;
    xsection[DataType::S3_300] = .6242;
    xsection[DataType::S3_400] = .2903;
    xsection[DataType::S3_500] = .1490;
    xsection[DataType::S3_600] = .07878;

    xsection[DataType::S3_0_jets  ] = 8.307;
    xsection[DataType::S3_50_jets ] = 6.705;
    xsection[DataType::S3_100_jets] = 4.159;
    xsection[DataType::S3_150_jets] = 2.299;
    xsection[DataType::S3_200_jets] = 1.412; // 0.694
    xsection[DataType::S3_300_jets] = .6048;
    xsection[DataType::S3_500_jets] = .1463;

    return xsection;
}

EventWeightProvider::EventWeightProvider(float lumiInInversePb, SampleVersion version) :
    lumiInInversePb(lumiInInversePb),
    sampleVersion(version),
    useSkimEff(true),
    xsection(),
    pileUpWeights(),
    numberOfEventsWithTooHighPileUp(0),
    numberOfProcessedEvents(),
    numberOfPattplSkimEvents(),
    numberOfNtplSkimEvents(),
    numberOfElectronSkimEvents(),
    numberOfMuonSkimEvents()
{
    currentReweightingModel = 0;
    generate_flat10_weights(); // use "Flat10+tail" as default
    //generate_observedPileUp2011_weights();

    xsection = getXSections();
    defineNumberOfProducedEvents();
//    defineNumberOfSkimmedEvents();
}

void EventWeightProvider::defineNumberOfProducedEvents() {
    numberOfProcessedEvents[DataType::DATA] = 0;

    numberOfProcessedEvents   [DataType::TTJets_HadronicMGDecays] = 31171004;
    numberOfPattplSkimEvents  [DataType::TTJets_HadronicMGDecays] = 0;
    numberOfNtplSkimEvents    [DataType::TTJets_HadronicMGDecays] = 31171004;
    numberOfElectronSkimEvents[DataType::TTJets_HadronicMGDecays] = 0;
    numberOfMuonSkimEvents    [DataType::TTJets_HadronicMGDecays] = 0;

    numberOfProcessedEvents   [DataType::TTJets_SemiLeptMGDecays] = 25323365;
    numberOfPattplSkimEvents  [DataType::TTJets_SemiLeptMGDecays] = 0;
    numberOfNtplSkimEvents    [DataType::TTJets_SemiLeptMGDecays] = 25323365;
    numberOfElectronSkimEvents[DataType::TTJets_SemiLeptMGDecays] = 0;
    numberOfMuonSkimEvents    [DataType::TTJets_SemiLeptMGDecays] = 0;

    numberOfProcessedEvents   [DataType::TTJets_FullLeptMGDecays] = 12100452;
    numberOfPattplSkimEvents  [DataType::TTJets_FullLeptMGDecays] = 0;
    numberOfNtplSkimEvents    [DataType::TTJets_FullLeptMGDecays] = 12100452;
    numberOfElectronSkimEvents[DataType::TTJets_FullLeptMGDecays] = 0;
    numberOfMuonSkimEvents    [DataType::TTJets_FullLeptMGDecays] = 0;

    numberOfProcessedEvents   [DataType::BN_TTJets_FullLeptMGDecays] = 12100452;
    numberOfPattplSkimEvents  [DataType::BN_TTJets_FullLeptMGDecays] = 0;
    numberOfNtplSkimEvents    [DataType::BN_TTJets_FullLeptMGDecays] = 12100452;
    numberOfElectronSkimEvents[DataType::BN_TTJets_FullLeptMGDecays] = 0;
    numberOfMuonSkimEvents    [DataType::BN_TTJets_FullLeptMGDecays] = 0;

// BEANs:
    // center, su, sd, mu, md

    int nTTJets[] = {6912438, 5001657, 5377915, 5406179, 5467705}; //5423781 with corrupted 34_4 md file
    numberOfProcessedEvents   [DataType::TTJets] = nTTJets[sampleVersion];
    numberOfPattplSkimEvents  [DataType::TTJets] = 0;
    numberOfNtplSkimEvents    [DataType::TTJets] = nTTJets[sampleVersion];
    numberOfElectronSkimEvents[DataType::TTJets] = 0;
    numberOfMuonSkimEvents    [DataType::TTJets] = 0;

    int nZJets[] = {30451975, 2169768, 1925599, 1985034, 2111846};
    numberOfProcessedEvents   [DataType::ZJets] = nZJets[sampleVersion];
    numberOfPattplSkimEvents  [DataType::ZJets] = 0;
    numberOfNtplSkimEvents    [DataType::ZJets] = nZJets[sampleVersion];
    numberOfElectronSkimEvents[DataType::ZJets] = 0;
    numberOfMuonSkimEvents    [DataType::ZJets] = 0;
//
    numberOfProcessedEvents   [DataType::ZJetsHT50to100] = 4039920;
    numberOfPattplSkimEvents  [DataType::ZJetsHT50to100] = 0;
    numberOfNtplSkimEvents    [DataType::ZJetsHT50to100] = 4039920;
    numberOfElectronSkimEvents[DataType::ZJetsHT50to100] = 0;
    numberOfMuonSkimEvents    [DataType::ZJetsHT50to100] = 0;

    numberOfProcessedEvents   [DataType::ZJetsHT100to200] = 4414132;
    numberOfPattplSkimEvents  [DataType::ZJetsHT100to200] = 0;
    numberOfNtplSkimEvents    [DataType::ZJetsHT100to200] = 4414132;
    numberOfElectronSkimEvents[DataType::ZJetsHT100to200] = 0;
    numberOfMuonSkimEvents    [DataType::ZJetsHT100to200] = 0;

    numberOfProcessedEvents   [DataType::ZJetsHT200to400] = 5047844;
    numberOfPattplSkimEvents  [DataType::ZJetsHT200to400] = 0;
    numberOfNtplSkimEvents    [DataType::ZJetsHT200to400] = 5047844;
    numberOfElectronSkimEvents[DataType::ZJetsHT200to400] = 0;
    numberOfMuonSkimEvents    [DataType::ZJetsHT200to400] = 0;

    numberOfProcessedEvents   [DataType::ZJetsHT400toInf] = 1001970;
    numberOfPattplSkimEvents  [DataType::ZJetsHT400toInf] = 0;
    numberOfNtplSkimEvents    [DataType::ZJetsHT400toInf] = 1001970;
    numberOfElectronSkimEvents[DataType::ZJetsHT400toInf] = 0;
    numberOfMuonSkimEvents    [DataType::ZJetsHT400toInf] = 0;

// BEANs:
    int nWJets[] = {57698420, 20780944, 20375387, 20971769, 21360516};
    numberOfProcessedEvents   [DataType::WJets] = nWJets[sampleVersion];
    numberOfPattplSkimEvents  [DataType::WJets] = 0;
    numberOfNtplSkimEvents    [DataType::WJets] = nWJets[sampleVersion];
    numberOfElectronSkimEvents[DataType::WJets] = 0;
    numberOfMuonSkimEvents    [DataType::WJets] = 0;

    numberOfProcessedEvents   [DataType::W1Jets] = 23136036;
    numberOfPattplSkimEvents  [DataType::W1Jets] = 0;
    numberOfNtplSkimEvents    [DataType::W1Jets] = 23136036;
    numberOfElectronSkimEvents[DataType::W1Jets] = 0;
    numberOfMuonSkimEvents    [DataType::W1Jets] = 0;

    numberOfProcessedEvents   [DataType::W2Jets] = 33945555;
    numberOfPattplSkimEvents  [DataType::W2Jets] = 0;
    numberOfNtplSkimEvents    [DataType::W2Jets] = 33945555;
    numberOfElectronSkimEvents[DataType::W2Jets] = 0;
    numberOfMuonSkimEvents    [DataType::W2Jets] = 0;

    int nW3J[] = {15528557, 14218240, 14700262, 15181537, 15264626};
    numberOfProcessedEvents   [DataType::W3Jets] = nW3J[sampleVersion];
    numberOfPattplSkimEvents  [DataType::W3Jets] = 0;
    numberOfNtplSkimEvents    [DataType::W3Jets] = nW3J[sampleVersion];
    numberOfElectronSkimEvents[DataType::W3Jets] = 0;
    numberOfMuonSkimEvents    [DataType::W3Jets] = 0;

    int nW4J[] = {13341409, 10475270,  8510718, 12123649, 13880166};
    numberOfProcessedEvents   [DataType::W4Jets] = nW4J[sampleVersion];
    numberOfPattplSkimEvents  [DataType::W4Jets] = 0;
    numberOfNtplSkimEvents    [DataType::W4Jets] = nW4J[sampleVersion];
    numberOfElectronSkimEvents[DataType::W4Jets] = 0;
    numberOfMuonSkimEvents    [DataType::W4Jets] = 0;

    numberOfProcessedEvents   [DataType::QCD_Pt15to3000] = 1021830; //7226188; //?
    numberOfPattplSkimEvents  [DataType::QCD_Pt15to3000] = 0;  //7226188; //?
    numberOfNtplSkimEvents    [DataType::QCD_Pt15to3000] = 1021830; //7226188; //?
    numberOfElectronSkimEvents[DataType::QCD_Pt15to3000] = 0;
    numberOfMuonSkimEvents    [DataType::QCD_Pt15to3000] = 0;

    numberOfProcessedEvents   [DataType::QCD_Pt170to300] = 19874076; //5789546;
    numberOfPattplSkimEvents  [DataType::QCD_Pt170to300] = 0;
    numberOfNtplSkimEvents    [DataType::QCD_Pt170to300] = 19874076; //5789546;
    numberOfElectronSkimEvents[DataType::QCD_Pt170to300] = 0;
    numberOfMuonSkimEvents    [DataType::QCD_Pt170to300] = 0;

    numberOfProcessedEvents   [DataType::QCD_Pt300to470] = 19714327; //5874224;
    numberOfPattplSkimEvents  [DataType::QCD_Pt300to470] = 0;
    numberOfNtplSkimEvents    [DataType::QCD_Pt300to470] = 19714327; //5874224;
    numberOfElectronSkimEvents[DataType::QCD_Pt300to470] = 0;
    numberOfMuonSkimEvents    [DataType::QCD_Pt300to470] = 0;

    numberOfProcessedEvents   [DataType::QCD_Pt470to600] = 3942508; //3940513;
    numberOfPattplSkimEvents  [DataType::QCD_Pt470to600] = 0;
    numberOfNtplSkimEvents    [DataType::QCD_Pt470to600] = 3942508; //3940513;
    numberOfElectronSkimEvents[DataType::QCD_Pt470to600] = 0;
    numberOfMuonSkimEvents    [DataType::QCD_Pt470to600] = 0;

    numberOfProcessedEvents   [DataType::QCD_Pt600to800] = 3932576; //3940513;
    numberOfPattplSkimEvents  [DataType::QCD_Pt600to800] = 0;
    numberOfNtplSkimEvents    [DataType::QCD_Pt600to800] = 3932576; //3940513;
    numberOfElectronSkimEvents[DataType::QCD_Pt600to800] = 0;
    numberOfMuonSkimEvents    [DataType::QCD_Pt600to800] = 0;

    numberOfProcessedEvents   [DataType::QCD_Pt800to1000] = 3928429; //3921086;
    numberOfPattplSkimEvents  [DataType::QCD_Pt800to1000] = 0;
    numberOfNtplSkimEvents    [DataType::QCD_Pt800to1000] = 3928429; //3921086;
    numberOfElectronSkimEvents[DataType::QCD_Pt800to1000] = 0;
    numberOfMuonSkimEvents    [DataType::QCD_Pt800to1000] = 0;

    numberOfProcessedEvents   [DataType::QCD_Pt1000to1400] = 1919722; //1926436;
    numberOfPattplSkimEvents  [DataType::QCD_Pt1000to1400] = 0;
    numberOfNtplSkimEvents    [DataType::QCD_Pt1000to1400] = 1919722; //1926436;
    numberOfElectronSkimEvents[DataType::QCD_Pt1000to1400] = 0;
    numberOfMuonSkimEvents    [DataType::QCD_Pt1000to1400] = 0;

    numberOfProcessedEvents   [DataType::QCD_Pt1400to1800] = 1957657;
    numberOfPattplSkimEvents  [DataType::QCD_Pt1400to1800] = 0;
    numberOfNtplSkimEvents    [DataType::QCD_Pt1400to1800] = 1957657;
    numberOfElectronSkimEvents[DataType::QCD_Pt1400to1800] = 0;
    numberOfMuonSkimEvents    [DataType::QCD_Pt1400to1800] = 0;
//
    numberOfProcessedEvents   [DataType::WHadr] = 9517;
    numberOfPattplSkimEvents  [DataType::WHadr] = 0;
    numberOfNtplSkimEvents    [DataType::WHadr] = 9516;
    numberOfElectronSkimEvents[DataType::WHadr] = 0;
    numberOfMuonSkimEvents    [DataType::WHadr] = 0;

    numberOfProcessedEvents   [DataType::WJetsHadr] = 9996;
    numberOfPattplSkimEvents  [DataType::WJetsHadr] = 0;
    numberOfNtplSkimEvents    [DataType::WJetsHadr] = 9988;
    numberOfElectronSkimEvents[DataType::WJetsHadr] = 0;
    numberOfMuonSkimEvents    [DataType::WJetsHadr] = 0;
// BEANs:
    numberOfProcessedEvents   [DataType::WWtoAnything] = 8942842; //8965049; // 9992188;
    numberOfPattplSkimEvents  [DataType::WWtoAnything] = 0;
    numberOfNtplSkimEvents    [DataType::WWtoAnything] = 8942842; //8965049; // 9992188;
    numberOfElectronSkimEvents[DataType::WWtoAnything] = 0;
    numberOfMuonSkimEvents    [DataType::WWtoAnything] = 0;

    numberOfProcessedEvents   [DataType::WZtoAnything] = 9732437; //9821291; // 9987975;
    numberOfPattplSkimEvents  [DataType::WZtoAnything] = 0;
    numberOfNtplSkimEvents    [DataType::WZtoAnything] = 9732437; //9821291; // 9987975;
    numberOfElectronSkimEvents[DataType::WZtoAnything] = 0;
    numberOfMuonSkimEvents    [DataType::WZtoAnything] = 0;

    numberOfProcessedEvents   [DataType::ZZtoAnything] = 9481492; //9568511; // 9791166;
    numberOfPattplSkimEvents  [DataType::ZZtoAnything] = 0;
    numberOfNtplSkimEvents    [DataType::ZZtoAnything] = 9481492; //9568511; // 9791166;
    numberOfElectronSkimEvents[DataType::ZZtoAnything] = 0;
    numberOfMuonSkimEvents    [DataType::ZZtoAnything] = 0;

    numberOfProcessedEvents   [DataType::singleTopSChannel] = 259657; // 259592;
    numberOfPattplSkimEvents  [DataType::singleTopSChannel] = 0;
    numberOfNtplSkimEvents    [DataType::singleTopSChannel] = 259657; // 259592;
    numberOfElectronSkimEvents[DataType::singleTopSChannel] = 0;
    numberOfMuonSkimEvents    [DataType::singleTopSChannel] = 0;

    numberOfProcessedEvents   [DataType::singleTbarSChannel] = 139835; // 139808;
    numberOfPattplSkimEvents  [DataType::singleTbarSChannel] = 0;
    numberOfNtplSkimEvents    [DataType::singleTbarSChannel] = 139835; // 139808;
    numberOfElectronSkimEvents[DataType::singleTbarSChannel] = 0;
    numberOfMuonSkimEvents    [DataType::singleTbarSChannel] = 0;

    numberOfProcessedEvents   [DataType::singleTopTChannel] = 3754544; // 23753;
    numberOfPattplSkimEvents  [DataType::singleTopTChannel] = 0;
    numberOfNtplSkimEvents    [DataType::singleTopTChannel] = 3754544; // 23753;
    numberOfElectronSkimEvents[DataType::singleTopTChannel] = 0;
    numberOfMuonSkimEvents    [DataType::singleTopTChannel] = 0;

    numberOfProcessedEvents   [DataType::singleTbarTChannel] = 1933504; // 1933075;
    numberOfPattplSkimEvents  [DataType::singleTbarTChannel] = 0;
    numberOfNtplSkimEvents    [DataType::singleTbarTChannel] = 1933504; // 1933075;
    numberOfElectronSkimEvents[DataType::singleTbarTChannel] = 0;
    numberOfMuonSkimEvents    [DataType::singleTbarTChannel] = 0;

    numberOfProcessedEvents   [DataType::singleTop_And_W] = 496918; // 496859;
    numberOfPattplSkimEvents  [DataType::singleTop_And_W] = 0;
    numberOfNtplSkimEvents    [DataType::singleTop_And_W] = 496918; // 496859;
    numberOfElectronSkimEvents[DataType::singleTop_And_W] = 0;
    numberOfMuonSkimEvents    [DataType::singleTop_And_W] = 0;

    numberOfProcessedEvents   [DataType::singleTbar_And_W] = 492779; // 492640;
    numberOfPattplSkimEvents  [DataType::singleTbar_And_W] = 0;
    numberOfNtplSkimEvents    [DataType::singleTbar_And_W] = 492779; // 492640;
    numberOfElectronSkimEvents[DataType::singleTbar_And_W] = 0;
    numberOfMuonSkimEvents    [DataType::singleTbar_And_W] = 0;
//
    numberOfProcessedEvents   [DataType::S4_0] = 49944;
    numberOfPattplSkimEvents  [DataType::S4_0] = 0;
    numberOfNtplSkimEvents    [DataType::S4_0] = 49944;
    numberOfElectronSkimEvents[DataType::S4_0] = 0;
    numberOfMuonSkimEvents    [DataType::S4_0] = 0;

    numberOfProcessedEvents   [DataType::S4_50] = 49957;
    numberOfPattplSkimEvents  [DataType::S4_50] = 0;
    numberOfNtplSkimEvents    [DataType::S4_50] = 49957;
    numberOfElectronSkimEvents[DataType::S4_50] = 0;
    numberOfMuonSkimEvents    [DataType::S4_50] = 0;

    numberOfProcessedEvents   [DataType::S4_100] = 49951;
    numberOfPattplSkimEvents  [DataType::S4_100] = 0;
    numberOfNtplSkimEvents    [DataType::S4_100] = 49951;
    numberOfElectronSkimEvents[DataType::S4_100] = 0;
    numberOfMuonSkimEvents    [DataType::S4_100] = 0;

    numberOfProcessedEvents   [DataType::S4_150] = 41552;
    numberOfPattplSkimEvents  [DataType::S4_150] = 0;
    numberOfNtplSkimEvents    [DataType::S4_150] = 41552;
    numberOfElectronSkimEvents[DataType::S4_150] = 0;
    numberOfMuonSkimEvents    [DataType::S4_150] = 0;

    numberOfProcessedEvents   [DataType::S4_200] = 49930;
    numberOfPattplSkimEvents  [DataType::S4_200] = 0;
    numberOfNtplSkimEvents    [DataType::S4_200] = 49930;
    numberOfElectronSkimEvents[DataType::S4_200] = 0;
    numberOfMuonSkimEvents    [DataType::S4_200] = 0;

    numberOfProcessedEvents   [DataType::S4_300] = 49909;
    numberOfPattplSkimEvents  [DataType::S4_300] = 0;
    numberOfNtplSkimEvents    [DataType::S4_300] = 49909;
    numberOfElectronSkimEvents[DataType::S4_300] = 0;
    numberOfMuonSkimEvents    [DataType::S4_300] = 0;

    numberOfProcessedEvents   [DataType::S4_400] = 47930;
    numberOfPattplSkimEvents  [DataType::S4_400] = 0;
    numberOfNtplSkimEvents    [DataType::S4_400] = 47930;
    numberOfElectronSkimEvents[DataType::S4_400] = 0;
    numberOfMuonSkimEvents    [DataType::S4_400] = 0;

    numberOfProcessedEvents   [DataType::S4_500] = 49906;
    numberOfPattplSkimEvents  [DataType::S4_500] = 0;
    numberOfNtplSkimEvents    [DataType::S4_500] = 49906;
    numberOfElectronSkimEvents[DataType::S4_500] = 0;
    numberOfMuonSkimEvents    [DataType::S4_500] = 0;

    numberOfProcessedEvents   [DataType::S4_600] = 44011;
    numberOfPattplSkimEvents  [DataType::S4_600] = 0;
    numberOfNtplSkimEvents    [DataType::S4_600] = 44011;
    numberOfElectronSkimEvents[DataType::S4_600] = 0;
    numberOfMuonSkimEvents    [DataType::S4_600] = 0;

    numberOfProcessedEvents   [DataType::S4_700] = 44885;
    numberOfPattplSkimEvents  [DataType::S4_700] = 0;
    numberOfNtplSkimEvents    [DataType::S4_700] = 44885;
    numberOfElectronSkimEvents[DataType::S4_700] = 0;
    numberOfMuonSkimEvents    [DataType::S4_700] = 0;

    numberOfProcessedEvents   [DataType::S4_800] = 47873;
    numberOfPattplSkimEvents  [DataType::S4_800] = 0;
    numberOfNtplSkimEvents    [DataType::S4_800] = 47873;
    numberOfElectronSkimEvents[DataType::S4_800] = 0;
    numberOfMuonSkimEvents    [DataType::S4_800] = 0;

    numberOfProcessedEvents   [DataType::S4_900] = 47868;
    numberOfPattplSkimEvents  [DataType::S4_900] = 0;
    numberOfNtplSkimEvents    [DataType::S4_900] = 47868;
    numberOfElectronSkimEvents[DataType::S4_900] = 0;
    numberOfMuonSkimEvents    [DataType::S4_900] = 0;

    numberOfProcessedEvents   [DataType::S4_1000] = 42882;
    numberOfPattplSkimEvents  [DataType::S4_1000] = 0;
    numberOfNtplSkimEvents    [DataType::S4_1000] = 42882;
    numberOfElectronSkimEvents[DataType::S4_1000] = 0;
    numberOfMuonSkimEvents    [DataType::S4_1000] = 0;

    numberOfProcessedEvents   [DataType::S4_0_jets] = 19850;
    numberOfPattplSkimEvents  [DataType::S4_0_jets] = 0;
    numberOfNtplSkimEvents    [DataType::S4_0_jets] = 19850;
    numberOfElectronSkimEvents[DataType::S4_0_jets] = 0;
    numberOfMuonSkimEvents    [DataType::S4_0_jets] = 0;

    numberOfProcessedEvents   [DataType::S4_50_jets] = 21489;
    numberOfPattplSkimEvents  [DataType::S4_50_jets] = 0;
    numberOfNtplSkimEvents    [DataType::S4_50_jets] = 21489;
    numberOfElectronSkimEvents[DataType::S4_50_jets] = 0;
    numberOfMuonSkimEvents    [DataType::S4_50_jets] = 0;

    numberOfProcessedEvents   [DataType::S4_100_jets] = 20845;
    numberOfPattplSkimEvents  [DataType::S4_100_jets] = 0;
    numberOfNtplSkimEvents    [DataType::S4_100_jets] = 20845;
    numberOfElectronSkimEvents[DataType::S4_100_jets] = 0;
    numberOfMuonSkimEvents    [DataType::S4_100_jets] = 0;

    numberOfProcessedEvents   [DataType::S4_150_jets] = 30471;
    numberOfPattplSkimEvents  [DataType::S4_150_jets] = 0;
    numberOfNtplSkimEvents    [DataType::S4_150_jets] = 30471;
    numberOfElectronSkimEvents[DataType::S4_150_jets] = 0;
    numberOfMuonSkimEvents    [DataType::S4_150_jets] = 0;

    numberOfProcessedEvents   [DataType::S4_200_jets] = 31644;
    numberOfPattplSkimEvents  [DataType::S4_200_jets] = 0;
    numberOfNtplSkimEvents    [DataType::S4_200_jets] = 31644;
    numberOfElectronSkimEvents[DataType::S4_200_jets] = 0;
    numberOfMuonSkimEvents    [DataType::S4_200_jets] = 0;

    numberOfProcessedEvents   [DataType::S4_300_jets] = 31400;
    numberOfPattplSkimEvents  [DataType::S4_300_jets] = 0;
    numberOfNtplSkimEvents    [DataType::S4_300_jets] = 31400;
    numberOfElectronSkimEvents[DataType::S4_300_jets] = 0;
    numberOfMuonSkimEvents    [DataType::S4_300_jets] = 0;

    numberOfProcessedEvents   [DataType::S4_500_jets] = 31130;
    numberOfPattplSkimEvents  [DataType::S4_500_jets] = 0;
    numberOfNtplSkimEvents    [DataType::S4_500_jets] = 31130;
    numberOfElectronSkimEvents[DataType::S4_500_jets] = 0;
    numberOfMuonSkimEvents    [DataType::S4_500_jets] = 0;


    numberOfProcessedEvents   [DataType::S3_0] = 49957;
    numberOfPattplSkimEvents  [DataType::S3_0] = 0;
    numberOfNtplSkimEvents    [DataType::S3_0] = 49957;
    numberOfElectronSkimEvents[DataType::S3_0] = 0;
    numberOfMuonSkimEvents    [DataType::S3_0] = 0;

    numberOfProcessedEvents   [DataType::S3_50] = 49956;
    numberOfPattplSkimEvents  [DataType::S3_50] = 0;
    numberOfNtplSkimEvents    [DataType::S3_50] = 49956;
    numberOfElectronSkimEvents[DataType::S3_50] = 0;
    numberOfMuonSkimEvents    [DataType::S3_50] = 0;

    numberOfProcessedEvents   [DataType::S3_100] = 49956;
    numberOfPattplSkimEvents  [DataType::S3_100] = 0;
    numberOfNtplSkimEvents    [DataType::S3_100] = 49956;
    numberOfElectronSkimEvents[DataType::S3_100] = 0;
    numberOfMuonSkimEvents    [DataType::S3_100] = 0;

    numberOfProcessedEvents   [DataType::S3_150] = 49946;
    numberOfPattplSkimEvents  [DataType::S3_150] = 0;
    numberOfNtplSkimEvents    [DataType::S3_150] = 49946;
    numberOfElectronSkimEvents[DataType::S3_150] = 0;
    numberOfMuonSkimEvents    [DataType::S3_150] = 0;

    numberOfProcessedEvents   [DataType::S3_200] = 49941;
    numberOfPattplSkimEvents  [DataType::S3_200] = 0;
    numberOfNtplSkimEvents    [DataType::S3_200] = 49941;
    numberOfElectronSkimEvents[DataType::S3_200] = 0;
    numberOfMuonSkimEvents    [DataType::S3_200] = 0;

    numberOfProcessedEvents   [DataType::S3_300] = 49936;
    numberOfPattplSkimEvents  [DataType::S3_300] = 0;
    numberOfNtplSkimEvents    [DataType::S3_300] = 49936;
    numberOfElectronSkimEvents[DataType::S3_300] = 0;
    numberOfMuonSkimEvents    [DataType::S3_300] = 0;

    numberOfProcessedEvents   [DataType::S3_400] = 39953;
    numberOfPattplSkimEvents  [DataType::S3_400] = 0;
    numberOfNtplSkimEvents    [DataType::S3_400] = 39953;
    numberOfElectronSkimEvents[DataType::S3_400] = 0;
    numberOfMuonSkimEvents    [DataType::S3_400] = 0;

    numberOfProcessedEvents   [DataType::S3_500] = 49911;
    numberOfPattplSkimEvents  [DataType::S3_500] = 0;
    numberOfNtplSkimEvents    [DataType::S3_500] = 49911;
    numberOfElectronSkimEvents[DataType::S3_500] = 0;
    numberOfMuonSkimEvents    [DataType::S3_500] = 0;

    numberOfProcessedEvents   [DataType::S3_600] = 47920;
    numberOfPattplSkimEvents  [DataType::S3_600] = 0;
    numberOfNtplSkimEvents    [DataType::S3_600] = 47920;
    numberOfElectronSkimEvents[DataType::S3_600] = 0;
    numberOfMuonSkimEvents    [DataType::S3_600] = 0;

    numberOfProcessedEvents   [DataType::S3_0_jets] = 21507;
    numberOfPattplSkimEvents  [DataType::S3_0_jets] = 0;
    numberOfNtplSkimEvents    [DataType::S3_0_jets] = 21507;
    numberOfElectronSkimEvents[DataType::S3_0_jets] = 0;
    numberOfMuonSkimEvents    [DataType::S3_0_jets] = 0;

    numberOfProcessedEvents   [DataType::S3_50_jets] = 22058;
    numberOfPattplSkimEvents  [DataType::S3_50_jets] = 0;
    numberOfNtplSkimEvents    [DataType::S3_50_jets] = 22058;
    numberOfElectronSkimEvents[DataType::S3_50_jets] = 0;
    numberOfMuonSkimEvents    [DataType::S3_50_jets] = 0;

    numberOfProcessedEvents   [DataType::S3_100_jets] = 21920;
    numberOfPattplSkimEvents  [DataType::S3_100_jets] = 0;
    numberOfNtplSkimEvents    [DataType::S3_100_jets] = 21920;
    numberOfElectronSkimEvents[DataType::S3_100_jets] = 0;
    numberOfMuonSkimEvents    [DataType::S3_100_jets] = 0;

    numberOfProcessedEvents   [DataType::S3_150_jets] = 27789;
    numberOfPattplSkimEvents  [DataType::S3_150_jets] = 0;
    numberOfNtplSkimEvents    [DataType::S3_150_jets] = 27789;
    numberOfElectronSkimEvents[DataType::S3_150_jets] = 0;
    numberOfMuonSkimEvents    [DataType::S3_150_jets] = 0;

    numberOfProcessedEvents   [DataType::S3_200_jets] = 30845; //15880
    numberOfPattplSkimEvents  [DataType::S3_200_jets] = 0;
    numberOfNtplSkimEvents    [DataType::S3_200_jets] = 30845; //15880
    numberOfElectronSkimEvents[DataType::S3_200_jets] = 0;
    numberOfMuonSkimEvents    [DataType::S3_200_jets] = 0;

    numberOfProcessedEvents   [DataType::S3_300_jets] = 31745;
    numberOfPattplSkimEvents  [DataType::S3_300_jets] = 0;
    numberOfNtplSkimEvents    [DataType::S3_300_jets] = 31745;
    numberOfElectronSkimEvents[DataType::S3_300_jets] = 0;
    numberOfMuonSkimEvents    [DataType::S3_300_jets] = 0;

    numberOfProcessedEvents   [DataType::S3_500_jets] = 30831;
    numberOfPattplSkimEvents  [DataType::S3_500_jets] = 0;
    numberOfNtplSkimEvents    [DataType::S3_500_jets] = 30831;
    numberOfElectronSkimEvents[DataType::S3_500_jets] = 0;
    numberOfMuonSkimEvents    [DataType::S3_500_jets] = 0;

}

EventWeightProvider::~EventWeightProvider() {

}

double EventWeightProvider::getWeight(DataType::value type) {
    if (type == DataType::DATA)
        return 1.;
    else
        return xsection[type] * lumiInInversePb / numberOfProcessedEvents[type];
}

float EventWeightProvider::reweightPileUpOfficial(unsigned int numberOfVertices){
    if( currentReweightingModel != truePileUp2012 ) return -1; // not available
    return officialReWighter.weight( int(numberOfVertices) );
//    if( numberOfVertices>=60 ) numberOfVertices = 59;
//    return pileUpWeights.at(numberOfVertices);
}

float EventWeightProvider::reweightPileUp(unsigned int numberOfVertices){
    if(numberOfVertices >= pileUpWeights.size()){
        ++numberOfEventsWithTooHighPileUp;
        return 0.;
    }

    return pileUpWeights.at(numberOfVertices);
}
boost::shared_ptr<TH1D> EventWeightProvider::getPileUpHistogram(std::string pileUpEstimationFile){
    std::cout << "Using pile-up estimation file " << pileUpEstimationFile << std::endl;
    boost::scoped_ptr<TFile> file(TFile::Open(pileUpEstimationFile.c_str()));
    boost::shared_ptr<TH1D> pileUp((TH1D*) file->Get("pileup")->Clone());
    file->Close();
    return pileUp;
}

void EventWeightProvider::generate_truePileUp2012_weights(PileUp mcScheme){

    if( mcScheme==S6 ){
       generate_truePileUp2011_weights();
       return;
    }

    if( currentReweightingModel == truePileUp2012 && currentMCscheme == mcScheme ) return;

    boost::shared_ptr<TH1D> estimatedPileUp = getPileUpHistogram(truePUdistfile);

    // https://twiki.cern.ch/twiki/bin/view/CMS/Pileup_MC_Gen_Scenarios
    //   (also in SimGeneral/MixingModule/python/mix_2012_Startup_50ns_PoissonOOTPU_cfi.py):
    const boost::array<double, 60> npu_probs_S7 = {{
      2.344E-05, 2.344E-05, 2.344E-05, 2.344E-05, 4.687E-04, 4.687E-04, 7.032E-04, 9.414E-04, 1.234E-03, 1.603E-03,
      2.464E-03, 3.250E-03, 5.021E-03, 6.644E-03, 8.502E-03, 1.121E-02, 1.518E-02, 2.033E-02, 2.608E-02, 3.171E-02,
      3.667E-02, 4.060E-02, 4.338E-02, 4.520E-02, 4.641E-02, 4.735E-02, 4.816E-02, 4.881E-02, 4.917E-02, 4.909E-02,
      4.842E-02, 4.707E-02, 4.501E-02, 4.228E-02, 3.896E-02, 3.521E-02, 3.118E-02, 2.702E-02, 2.287E-02, 1.885E-02,
      1.508E-02, 1.166E-02, 8.673E-03, 6.190E-03, 4.222E-03, 2.746E-03, 1.698E-03, 9.971E-04, 5.549E-04, 2.924E-04,
      1.457E-04, 6.864E-05, 3.054E-05, 1.282E-05, 5.081E-06, 1.898E-06, 6.688E-07, 2.221E-07, 6.947E-08, 2.047E-08
    }};

    const boost::array<double, 60> npu_probs_S10 = {{
      2.560E-06, 5.239E-06, 1.420E-05, 5.005E-05, 1.001E-04, 2.705E-04, 1.999E-03, 6.097E-03, 1.046E-02, 1.383E-02,
      1.685E-02, 2.055E-02, 2.572E-02, 3.262E-02, 4.121E-02, 4.977E-02, 5.539E-02, 5.725E-02, 5.607E-02, 5.312E-02,
      5.008E-02, 4.763E-02, 4.558E-02, 4.363E-02, 4.159E-02, 3.933E-02, 3.681E-02, 3.406E-02, 3.116E-02, 2.818E-02,
      2.519E-02, 2.226E-02, 1.946E-02, 1.682E-02, 1.437E-02, 1.215E-02, 1.016E-02, 8.400E-03, 6.873E-03, 5.564E-03,
      4.457E-03, 3.533E-03, 2.772E-03, 2.154E-03, 1.656E-03, 1.261E-03, 9.513E-04, 7.107E-04, 5.259E-04, 3.856E-04,
      2.801E-04, 2.017E-04, 1.439E-04, 1.017E-04, 7.126E-05, 4.948E-05, 3.405E-05, 2.322E-05, 1.570E-05, 5.005E-06
    }};

/*
    const boost::array<double, 60> npu_probs_S10 = {{
      2.11029e-05, 2.2761e-05, 2.53235e-05, 1.97463e-05, 0.000474665, 0.000467128, 0.00071765, 0.000938176, 0.00125547, 0.00160623, 
      0.0024401,   0.00321955, 0.00499129,  0.00667998,  0.00852815,  0.0111852,   0.0151593,  0.0203526,   0.026081,   0.0317188, 
      0.0367575,   0.0407324,  0.043382,    0.0451772,   0.0463779,   0.0473098,   0.0481136,  0.0488575,   0.0491213,  0.0490972, 
      0.0484994,   0.0470894,  0.0450395,   0.0421573,   0.038939,    0.0351953,   0.0312174,  0.0271105,   0.022755,   0.0188087, 
      0.0150805,   0.011646,   0.008692,    0.00618798,  0.00420566,  0.00272574,  0.00168823, 0.00102364,  0.000548073,0.000294687, 
      0.000145309, 6.6022e-05, 3.09007e-05, 1.50735e-05, 5.87867e-06, 1.50735e-06, 4.52206e-07, 4.52206e-07,0,          0
    }};
*/
    std::vector< float > mcPileUp(60), dataPileUp(60);

    for(int i=0; i<60; i++) {
      switch( mcScheme ){
         case S7 :  mcPileUp[i] = npu_probs_S7 [i]; break;
         case S10:  mcPileUp[i] = npu_probs_S10[i]; break;
         default : std::cout<<"Wrong PileUp MC scheme"<<std::endl; exit(0); break;
      }
      dataPileUp[i] = estimatedPileUp->GetBinContent(i+1);
    }

    officialReWighter = LumiReWeighting(mcPileUp, dataPileUp);

/*
// ugly quickfix:
    double s = 0.0;
    for (unsigned int npu = 0; npu < npu_probs_S10.size(); ++npu) {
        double npu_estimated = estimatedPileUp->GetBinContent(estimatedPileUp->GetXaxis()->FindBin(npu));
        pileUpWeights[npu] = npu_estimated / npu_probs_S10[npu];
        s += npu_estimated;
    }
    // normalize weights such that the total sum of weights over thw whole sample is 1.0, i.e., sum_i  result[i] * npu_probs[i] should be 1.0 (!)
    for (unsigned int npu = 0; npu < pileUpWeights.size(); ++npu) {
        pileUpWeights[npu] /= s;
    }
    currentReweightingModel = flat10;
/////////////////
*/
    currentReweightingModel = truePileUp2012;
    currentMCscheme = mcScheme;
}


// for signal Fall11 MC samples
void EventWeightProvider::generate_truePileUp2011_weights(void){

    if( currentReweightingModel == truePileUp2011 ) return;

    boost::shared_ptr<TH1D> estimatedPileUp = getPileUpHistogram(truePUdistfile);

    const boost::array<double, 50> npu_probs = {{ 0.003388501, 0.010357558, 0.024724258, 0.042348605, 0.058279812,
      0.068851751, 0.072914824, 0.071579609, 0.066811668, 0.060672356, 0.054528356, 0.04919354, 0.044886042,
      0.041341896, 0.0384679,   0.035871463, 0.03341952,  0.030915649, 0.028395374, 0.025798107, 0.023237445,
      0.020602754, 0.0180688,   0.015559693, 0.013211063, 0.010964293, 0.008920993, 0.007080504, 0.005499239,
      0.004187022, 0.003096474, 0.002237361, 0.001566428, 0.001074149, 0.000721755, 0.000470838, 0.00030268,
      0.000184665, 0.000112883, 6.74043E-05, 3.82178E-05, 2.22847E-05, 1.20933E-05, 6.96173E-06, 3.4689E-06,
      1.96172E-06, 8.49283E-07, 5.02393E-07, 2.15311E-07, 9.56938E-08
    }}; 

    double s = 0.0;
    for (unsigned int npu = 0; npu < npu_probs.size(); ++npu) {
        double npu_estimated = estimatedPileUp->GetBinContent(estimatedPileUp->GetXaxis()->FindBin(npu));
        pileUpWeights[npu] = npu_estimated / npu_probs[npu];
        s += npu_estimated;
    }
    // normalize weights such that the total sum of weights over thw whole sample is 1.0, i.e., sum_i  result[i] * npu_probs[i] should be 1.0 (!)
    for (unsigned int npu = 0; npu < pileUpWeights.size(); ++npu) {
        pileUpWeights[npu] /= s;
    }

    currentReweightingModel = truePileUp2011;
}

// for background Summer11 MC samples
void EventWeightProvider::generate_observedPileUp2011_weights(void){

    if( currentReweightingModel == observedPileUp2011 ) return;

    boost::shared_ptr<TH1D> estimatedPileUp = getPileUpHistogram(observedPUdistfile);

    const boost::array<double, 35> npu_probs = {{     1.45346E-01,    6.42802E-02,    6.95255E-02,    6.96747E-02,
      6.92955E-02,    6.84997E-02,    6.69528E-02,    6.45515E-02,    6.09865E-02,    5.63323E-02,    5.07322E-02,
      4.44681E-02,    3.79205E-02,    3.15131E-02,    2.54220E-02,    2.00184E-02,    1.53776E-02,    1.15387E-02,
      8.47608E-03,    6.08715E-03,    4.28255E-03,    2.97185E-03,    2.01918E-03,    1.34490E-03,    8.81587E-04,
      5.69954E-04,    3.61493E-04,    2.28692E-04,    1.40791E-04,    8.44606E-05,    5.10204E-05,    3.07802E-05,
      1.81401E-05,    1.00201E-05,    5.80004E-06
    }};

    double s = 0.0;
    for (unsigned int npu = 0; npu < npu_probs.size(); ++npu) {
        double npu_estimated = estimatedPileUp->GetBinContent(estimatedPileUp->GetXaxis()->FindBin(npu));
        pileUpWeights[npu] = npu_estimated / npu_probs[npu];
        s += npu_estimated;
    }
    // normalize weights such that the total sum of weights over thw whole sample is 1.0, i.e., sum_i  result[i] * npu_probs[i] should be 1.0 (!)
    for (unsigned int npu = 0; npu < pileUpWeights.size(); ++npu) {
        pileUpWeights[npu] /= s;
    }

    currentReweightingModel = observedPileUp2011;
} 

// for signal private fast sim samples
void EventWeightProvider::generate_flat10_weights(){

    if( currentReweightingModel == flat10 ) return;

    //boost::shared_ptr<TH1D> estimatedPileUp = getPileUpHistogram("pileup_160404-165970.root");
    boost::shared_ptr<TH1D> estimatedPileUp = getPileUpHistogram(truePUdistfile);

    // see SimGeneral/MixingModule/python/mix_E7TeV_FlatDist10_2011EarlyData_inTimeOnly_cfi.py; copy and paste from there:
    const boost::array<double, 25> npu_probs = {{0.0698146584, 0.0698146584, 0.0698146584,0.0698146584,0.0698146584,0.0698146584,0.0698146584,0.0698146584,0.0698146584,0.0698146584,0.0698146584 /* <-- 10*/,
           0.0630151648,0.0526654164,0.0402754482,0.0292988928,0.0194384503,0.0122016783,0.007207042,0.004003637,0.0020278322,
           0.0010739954,0.0004595759,0.0002229748,0.0001028162,4.58337152809607E-05 /* <-- 24 */}};
    double s = 0.0;
    for (unsigned int npu = 0; npu < npu_probs.size(); ++npu) {
        double npu_estimated = estimatedPileUp->GetBinContent(estimatedPileUp->GetXaxis()->FindBin(npu));
        pileUpWeights[npu] = npu_estimated / npu_probs[npu];
        s += npu_estimated;
    }
    // normalize weights such that the total sum of weights over thw whole sample is 1.0, i.e., sum_i  result[i] * npu_probs[i] should be 1.0 (!)
    for (unsigned int npu = 0; npu < pileUpWeights.size(); ++npu) {
        pileUpWeights[npu] /= s;
    }

    currentReweightingModel = flat10;
}

unsigned long EventWeightProvider::getNumberOfEventsWithTooHighPileUp() const{
    return numberOfEventsWithTooHighPileUp;
}

} // namespace BAT
