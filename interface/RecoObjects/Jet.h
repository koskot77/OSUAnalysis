/*
 * Jet.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef JET_H_
#define JET_H_
#include "Particle.h"
#include <vector>
#include <string>
#include <boost/array.hpp>

namespace BAT {

namespace BtagAlgorithm {
enum value {
    GenPartonFlavour,
    JetBProbabilityBTag,
    JetProbabilityBTag,
    SimpleSecondaryVertexHighEffBTag,
    SimpleSecondaryVertexHighPurBTag,
    TrackCountingHighEffBTag,
    TrackCountingHighPurBTag,
    CombinedSecondaryVertexBTag,
    NUMBER_OF_BTAGALGORITHMS
};

enum workingPoint {
    LOOSE, MEDIUM, TIGHT
};
}

namespace JetAlgorithm {
//enum value {
//    Calo_AntiKT_Cone05, JPT_AntiKt_ConeDR05, ParticleFlow, PF2PAT, NUMBER_OF_JETALGORITHMS
//};
enum value {
    Calo_AntiKT_Cone05,
    CA08PF,
    PF2PAT,
    PF2PATBEAN,
    NUMBER_OF_JETALGORITHMS
};

//for nTuple branch names
const boost::array<std::string, JetAlgorithm::NUMBER_OF_JETALGORITHMS> prefixes = { {
        "goodPatJets",
        "goodPatJetsCA8PF",
        "goodPatJetsPFlow",
        "selectedPatJetsAK5PF"
				} };

const boost::array<std::string, JetAlgorithm::NUMBER_OF_JETALGORITHMS> names = { {
        "CaloJets",
        "CA08PFJets",
        "PF2PATJets",
        "PF2PATBEANJets"
				} };
//        "CaloJets",
//        "JPT",
//        "PFJets",
//        "PF2PATJets" } };
}


namespace JetCorrDirection {
   enum value { NONE, PLUS, MINUS };
}

namespace JetBtagVariation {
   enum value { NONE, PLUS, MINUS };
}

namespace JetResVariation {
   enum value { NONE, PLUS, MINUS };
}


class Jet: public Particle {
public:

    Jet();
    Jet(const Particle& particle);
    Jet(float energy, float px, float py, float pz);
    virtual ~Jet();
    bool isGood() const;
    bool isBJet(BtagAlgorithm::value type = BtagAlgorithm::CombinedSecondaryVertexBTag,
            BtagAlgorithm::workingPoint wp = BtagAlgorithm::MEDIUM) const;
    bool isTaggedAsBJet(BtagAlgorithm::value type = BtagAlgorithm::CombinedSecondaryVertexBTag,
            BtagAlgorithm::workingPoint wp = BtagAlgorithm::MEDIUM) const;
		JetAlgorithm::value getUsedAlgorithm() const;
    float genJetPt() const;
    float emf() const;
    float n90Hits() const;
    float fHPD() const;
    float NOD() const;
    float CEF() const;
    float NHF() const;
    float NEF() const;
    float CHF() const;
    float NCH() const;
		int partonFlavour() const;
    double JECUnc() const;
    const FourVector &DiffVec;

    void setUsedAlgorithm(JetAlgorithm::value algo);
//    void setBtagVariation(JetBtagVariation::value var);
//    void setResVariation(JetResVariation::value var);
    void setGenJetPt(float genJetPt);
    void setEMF(float emf);
    void setN90Hits(int n90Hits);
    void setPartonFlavour(int partonFlvr);
    void setFHPD(float fHPD);
    void setDiscriminatorForBtagType(float discriminator, BtagAlgorithm::value type);
    float getDiscriminatorForBtagType(BtagAlgorithm::value type) const ;
    //	void setBtagForData(float btag);
    void setNOD(int nod);
    void setCEF(float cef);
    void setNHF(float nhf);
    void setNEF(float nef);
    void setCHF(float chf);
    void setNCH(float nch);
    void setJECUnc(double jecUnc);

    static JetCorrDirection::value correctDirection;
    static JetBtagVariation::value bTagVariation;
    static JetResVariation::value  resVariation;

    void adjForUnc();
    void adjForRes();

protected:
    JetAlgorithm::value usedAlgorithm;
    float matchedGenJetPt;
    float electromagneticFraction;
    int numberOfRecHitsContaining90PercentOfTheJetEnergy;
    float fractionOfEnergyIntheHottestHPDReadout;
    std::vector<float> btag_discriminators;
    //	float btagInData;
    int numberOfDaughters;
    float chargedEmEnergyFraction, neutralHadronEnergyFraction, neutralEmEnergyFraction;
    float chargedHadronEnergyFraction, chargedMultiplicity;
		double jecUncertainty;
    int partonFlavr;
    FourVector diffVec;
};

typedef boost::shared_ptr<Jet> JetPointer;
typedef std::vector<JetPointer> JetCollection;
}

#endif /* JET_H_ */
