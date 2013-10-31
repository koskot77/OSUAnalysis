/*
 * MET.h
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#ifndef MET_H_
#define MET_H_

#include <boost/shared_ptr.hpp>
#include <string>
#include <boost/array.hpp>

#include "Jet.h"

namespace BAT {

namespace METAlgorithm {
enum value {
    Calo,
    tcMET,
    ParticleFlowMET,
    PFBEANMET,
    NUMBER_OF_METALGORITHMS
};

const boost::array<std::string, METAlgorithm::NUMBER_OF_METALGORITHMS> prefixes = { {
        "patMETs",
        "TCMET",
        "patMETsPFlow",
        "patMETsTypeIPF"
				} };

const boost::array<std::string, METAlgorithm::NUMBER_OF_METALGORITHMS> names = { {
        "CaloMET",
        "TCMET",
        "PFMET",
        "PFBEANMET"
				} };
}

class MET: public Particle {
public:
	MET();
	MET(float ex, float ey);
	virtual ~MET();
	bool isGood() const;
	void setUsedAlgorithm(METAlgorithm::value algo);
	METAlgorithm::value getUsedAlgorithm() const;
	void adjForUnc(const JetCollection &jets);

private:
	METAlgorithm::value usedAlgorithm;
};

typedef boost::shared_ptr<MET> METPointer;

}

#endif /* MET_H_ */
