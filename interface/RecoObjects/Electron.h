/*
 * Electron.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef ELECTRON_H_
#define ELECTRON_H_
#include "Lepton.h"
#include <vector>
#include <string>
#include <boost/static_assert.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include "Jet.h"
#include "Track.h"

namespace BAT {

namespace ElectronAlgorithm {
enum value {
    Calo,
    ParticleFlow,
    LoosePF,
    PFElectronBEAN,
    NUMBER_OF_ELECTRONALGORITHMS
};

const boost::array<std::string, ElectronAlgorithm::NUMBER_OF_ELECTRONALGORITHMS> prefixes = { {
        "selectedPatElectrons",
        "selectedPatElectronsPFlow",  
        "selectedPatElectronsLoosePFlow",
        "selectedPatElectronsPFlow"
} };


const boost::array<std::string, ElectronAlgorithm::NUMBER_OF_ELECTRONALGORITHMS> names = { {
        "LooseElectron",
        "PFElectron",
        "LoosePFElectron",
        "PFElectronBEAN"
} };
}


namespace eIDMethod {
enum value {
	CIC, VBTF, MVA
};
}


namespace ElectronIsolation{
enum value {
    RelativeIsolation,
    ParticleFlowIsolation,
    NUMBER_OF_ELECTRONISOLATIONS
};
}

class Electron: public Lepton {
public:

    Electron();
    Electron(float energy, float px, float py, float pz);
    virtual ~Electron();
    bool isGood(const float minEt = 30) const;
    bool isTrackerIsolated() const;
    bool isTrackerNonIsolated() const;
    bool isPFIsolated() const;
    bool isPFNonIsolated() const;
    bool isHEEPIsolated() const;
    bool isTaggedAsConversion(float maxDist, float maxDCotTheta) const;
    bool CIC_ElectronID(unsigned short bitnum = 4) const;
    bool isFromConversion() const;
    bool isLoose() const;
    bool isQCDElectron(const float minEt = 30) const;

    ElectronAlgorithm::value algorithm() const;
    float mvaTrigV0eID(void) const;
    float mvaNonTrigV0eID(void) const;
    float ecalIsolation() const;
    float hcalIsolation() const;
    float trackerIsolation() const;
    float pfIsolationAeff() const;
    float superClusterEta() const;
    float Aeff() const;
    float sigmaIEtaIEta() const;
    float dPhiIn() const;
    float dEtaIn() const;
    float HadOverEm() const;
    float HEEPet() const;
    float innerLayerMissingHits() const;
    float dCotThetaToClosestTrack() const;
    float distToClosestTrack() const;
    bool VBTF_W70_ElectronID() const;
    bool VBTF_W95_ElectronID() const;
    bool QCD_AntiID_W70() const;
    bool QCD_AntiID_W70_Barrel() const;
    bool QCD_AntiID_W70_Endcap() const;
    bool RobustLooseID() const;
    bool RobustTightID() const;
    unsigned short getClosestJetIndex(const JetCollection& jets) const;
    ElectronAlgorithm::value getUsedAlgorithm() const;
    const TrackPointer GSFTrack() const;
    int closestCTFTrackID() const;
    float shFracInnerLayer() const;

    void setRobustLooseID(bool id);
    void setRobustTightID(bool id);

    void setSuperClusterEta(float eta);
    void setEffectiveArea(float effArea);
    void setEcalIsolation(float isolation);
    void setHcalIsolation(float isolation);
    void setTrackerIsolation(float isolation);
    void setNumberOfMissingInnerLayerHits(float missingHits);
    void setUsedAlgorithm(ElectronAlgorithm::value algo);
    void setEIDMethod(eIDMethod::value algo);
    void setSigmaIEtaIEta(float sigma);
    void setDPhiIn(float dphi);
    void setDEtaIn(float deta);
    void setHadOverEm(float HoverE);
    void setCICeID(int cicElID);
    void setMvaTrigV0eID(float mvaID);
    void setMvaNonTrigV0eID(float mvaID);
    void setGSFTrack(const TrackPointer track);
    void setClosestTrackID(const int trackID);
    void setSharedFractionInnerHits(float hits);
//    void setElectronVertexZPosition(float z);
    void setDistToNextTrack(float dist);
    void setDCotThetaToNextTrack(float dCotTheta);

    float relativeIsolation() const;

    bool isInBarrelRegion() const;
    bool isInCrack() const;
    bool isInEndCapRegion() const;

//    float vz() const;

protected:
    ElectronAlgorithm::value usedAlgorithm;
    eIDMethod::value electronIDUsed;

    bool robustLooseId, robustTightId;
    float superCluser_Eta, effectiveArea;
    float ecal_Isolation, hcal_Isolation, tracker_Isolation;
    float innerLayerMissingHits_;
    //used for HEEP
    float sigma_IEtaIEta, dPhi_In, dEta_In, hadOverEm;
    TrackPointer gsfTrack;
    int closesTrackID, cicEID;
    float mvaTrigV0, mvaNonTrigV0;
    float sharedFractionInnerHits;
    float dCotThetaToNextTrack, distToNextTrack;

    bool getVBTF_W70_ElectronID_Barrel() const;
    bool getVBTF_W70_ElectronID_Endcap() const;
    bool getVBTF_W95_ElectronID_Barrel() const;
    bool getVBTF_W95_ElectronID_Endcap() const;

};

typedef boost::shared_ptr<Electron> ElectronPointer;
typedef std::vector<ElectronPointer> ElectronCollection;

}

#endif /* ELECTRON_H_ */
