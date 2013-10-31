#ifndef TOPLIKECANDIDATE_H_
#define TOPLIKECANDIDATE_H_


#include <map>

#include "RecoObjects/MCParticle.h"
#include "TopPairEventCandidate.h"

// using namespace BAT;
using namespace std;

namespace BAT {


const int DQ_ID = 1, BQ_ID = 5, TOP_ID = 6, W_ID = 24, ELECTRON_ID = 11;
const int TAU_ID = 15, NU_E_ID = 12, MU_ID = 13, NU_MU_ID = 14;
const int WPRIME_ID = 4000023;

namespace ToplikeSelectionSteps {  // Note the name space!
enum Step {
// Any new constant must be added to selStepArr below or
// or get a new selection function coded for it.
// Note this order not important.  See selection arrays below.
    FilterOutScraping,
    GoodPrimaryvertex,
    HighLevelTrigger,
    OneIsolatedElectron,
    OneIsolatedMuon,
    IsolatedElectron,
    IsolatedMuon,
    LooseMuonVeto,
    LooseElectronVeto,
    TightMuonVeto,
    TightElectronVeto,
    SecondMuonVeto,
    SecondElectronVeto,
    ConversionRejection,
    ConversionFinder,
    MissingTransverseEnergy65,
    MissingTransverseEnergy80,
    MissingTransverseEnergy100,
    MissingTransverseEnergy150,
    MissingTransverseEnergy200,
    MissingTransverseEnergy250,
    MissingTransverseEnergy350,
    HT700GeV,
    AtLeastOneGoodJet,
    AtLeastTwoGoodJets,
    AtLeastThreeGoodJets,
    AtLeastFourGoodJets,
    AtLeastFiveGoodJets,
    FortyfiveGeVElectron,
    AtLeastOneBtag,
    AtLeastTwoBtags,
    BaseHLT
};

const std::string StringSteps[] = {
        "Scraping Filter",
        "Good primary vertex",
        "High Level Trigger",
        "Only one iso. electron",
        "Only one iso. muon",
        "Iso. electron",
        "Iso. muon",
        "Loose muon veto",
        "Loose electron veto",
        "Tight muon veto",
        "Tight electron veto",
        "Second-muon veto",
        "Second-electron veto",
        "Conv. veto (missing hits)",
        "Conv. finder (extra track)",
        "$E_T^{Miss} >$ 65 GeV/c",
        "$E_T^{Miss} >$ 80 GeV/c",
        "$E_T^{Miss} >$ 100 GeV/c",
        "$E_T^{Miss} >$ 150 GeV/c",
        "$E_T^{Miss} >$ 200 GeV/c",
        "$E_T^{Miss} >$ 250 GeV/c",
        "$E_T^{Miss} >$ 350 GeV/c",
        "$HT (\\Sigma p_T) <$ 700 GeV/c",
//        "$\\geq$ 1 jet $>$ 80 GeV/c",
        "$\\geq$ 1 jet $>$ 60 GeV/c",
        "$\\geq$ 2 jets $>$ 60 GeV/c",
        "$\\geq$ 3 jets $>$ 40 GeV/c",
//        "$\\geq$ 3 jets $>$ 30 GeV/c",
        "$\\geq$ 4 jets $>$ 20 GeV/c",
        "$\\geq$ 5 jets",
        "$>$45 GeV/c electron $p_T$",
        "$\\geq$ 1 SSV $b$-tag",
        "$\\geq$ 2 SSV $b$-tags",
        "Base HLT"
};
}

typedef struct {
	ToplikeSelectionSteps::Step key;
	TTbarEPlusJetsSelection::Step value;
} selPair;
	
const selPair selStepArr[] = {
	{ToplikeSelectionSteps::FilterOutScraping, TTbarEPlusJetsSelection::FilterOutScraping},	
	{ToplikeSelectionSteps::HighLevelTrigger, TTbarEPlusJetsSelection::HighLevelTrigger},	
	{ToplikeSelectionSteps::GoodPrimaryvertex, TTbarEPlusJetsSelection::GoodPrimaryvertex},	
	{ToplikeSelectionSteps::OneIsolatedElectron, TTbarEPlusJetsSelection::OneIsolatedElectron},	
	{ToplikeSelectionSteps::LooseMuonVeto, TTbarEPlusJetsSelection::LooseMuonVeto},	
	{ToplikeSelectionSteps::ConversionRejection, TTbarEPlusJetsSelection::ConversionRejection},	
	{ToplikeSelectionSteps::ConversionFinder, TTbarEPlusJetsSelection::ConversionFinder},	
	{ToplikeSelectionSteps::AtLeastOneGoodJet, TTbarEPlusJetsSelection::AtLeastOneGoodJets},	
	{ToplikeSelectionSteps::AtLeastTwoGoodJets, TTbarEPlusJetsSelection::AtLeastTwoGoodJets},	
	{ToplikeSelectionSteps::AtLeastThreeGoodJets, TTbarEPlusJetsSelection::AtLeastThreeGoodJets},	
	{ToplikeSelectionSteps::AtLeastFourGoodJets, TTbarEPlusJetsSelection::AtLeastFourGoodJets},	
	{ToplikeSelectionSteps::AtLeastOneBtag, TTbarEPlusJetsSelection::AtLeastOneBtag},	
	{ToplikeSelectionSteps::AtLeastTwoBtags, TTbarEPlusJetsSelection::AtLeastTwoBtags}
};


const ToplikeSelectionSteps::Step toplikeElectronSelection[] = {
	ToplikeSelectionSteps::HighLevelTrigger,
	ToplikeSelectionSteps::OneIsolatedElectron,
	ToplikeSelectionSteps::SecondElectronVeto,
	ToplikeSelectionSteps::LooseMuonVeto,
	ToplikeSelectionSteps::ConversionRejection,
	ToplikeSelectionSteps::ConversionFinder,
	ToplikeSelectionSteps::MissingTransverseEnergy80,
	ToplikeSelectionSteps::HT700GeV,
	ToplikeSelectionSteps::AtLeastOneGoodJet,
	ToplikeSelectionSteps::AtLeastTwoGoodJets,
	ToplikeSelectionSteps::AtLeastOneBtag,
	ToplikeSelectionSteps::AtLeastThreeGoodJets,
	ToplikeSelectionSteps::AtLeastFourGoodJets,
	ToplikeSelectionSteps::AtLeastFiveGoodJets
  // ToplikeSelectionSteps::AtLeastTwoBtags
};

const unsigned int toplikeElectronSelSize =
sizeof(toplikeElectronSelection)/sizeof(ToplikeSelectionSteps::AtLeastOneGoodJet);

const ToplikeSelectionSteps::Step toplikeMuonSelection[] = {
	ToplikeSelectionSteps::HighLevelTrigger,
	ToplikeSelectionSteps::OneIsolatedMuon,
	ToplikeSelectionSteps::SecondMuonVeto,
	ToplikeSelectionSteps::LooseElectronVeto,
	ToplikeSelectionSteps::MissingTransverseEnergy80,
	ToplikeSelectionSteps::HT700GeV,
	ToplikeSelectionSteps::AtLeastOneGoodJet,
	ToplikeSelectionSteps::AtLeastTwoGoodJets,
	ToplikeSelectionSteps::AtLeastOneBtag,
	ToplikeSelectionSteps::AtLeastThreeGoodJets,
	ToplikeSelectionSteps::AtLeastFourGoodJets,
	ToplikeSelectionSteps::AtLeastFiveGoodJets
  // ToplikeSelectionSteps::AtLeastTwoBtags
};

const unsigned int toplikeMuonSelSize =
	sizeof(toplikeMuonSelection)/sizeof(ToplikeSelectionSteps::AtLeastOneGoodJet);


const ToplikeSelectionSteps::Step eTrigStudySelection[] = {
	ToplikeSelectionSteps::BaseHLT,
	ToplikeSelectionSteps::OneIsolatedElectron,
	ToplikeSelectionSteps::SecondElectronVeto,
	ToplikeSelectionSteps::LooseMuonVeto,
	ToplikeSelectionSteps::ConversionRejection,
	ToplikeSelectionSteps::ConversionFinder,
	ToplikeSelectionSteps::MissingTransverseEnergy80,
	ToplikeSelectionSteps::HT700GeV,
	ToplikeSelectionSteps::AtLeastOneGoodJet,
	ToplikeSelectionSteps::AtLeastTwoGoodJets,
	ToplikeSelectionSteps::AtLeastOneBtag,
	ToplikeSelectionSteps::AtLeastThreeGoodJets,
	ToplikeSelectionSteps::AtLeastFourGoodJets,
	ToplikeSelectionSteps::AtLeastFiveGoodJets
};

const unsigned int eTrigStudySelSize =
sizeof(eTrigStudySelection)/sizeof(ToplikeSelectionSteps::AtLeastOneGoodJet);


const ToplikeSelectionSteps::Step monotopJetSelection[] = {
	ToplikeSelectionSteps::LooseElectronVeto,
	ToplikeSelectionSteps::LooseMuonVeto,
	ToplikeSelectionSteps::AtLeastOneGoodJet,
	ToplikeSelectionSteps::AtLeastTwoGoodJets,
	ToplikeSelectionSteps::AtLeastThreeGoodJets,
	ToplikeSelectionSteps::AtLeastFourGoodJets,
	ToplikeSelectionSteps::AtLeastOneBtag,

    ToplikeSelectionSteps::MissingTransverseEnergy80,
    ToplikeSelectionSteps::MissingTransverseEnergy150,
    ToplikeSelectionSteps::MissingTransverseEnergy250

};

const unsigned int monotopJetSelectionSize =
       sizeof(monotopJetSelection)/sizeof(ToplikeSelectionSteps::AtLeastOneGoodJet);

const ToplikeSelectionSteps::Step monotopMetSelection[] = {
	ToplikeSelectionSteps::LooseElectronVeto,
	ToplikeSelectionSteps::LooseMuonVeto,
	ToplikeSelectionSteps::AtLeastOneGoodJet,
	ToplikeSelectionSteps::AtLeastTwoGoodJets,
//	ToplikeSelectionSteps::MissingTransverseEnergy80,
	ToplikeSelectionSteps::AtLeastThreeGoodJets,
	ToplikeSelectionSteps::AtLeastOneBtag,
    ToplikeSelectionSteps::MissingTransverseEnergy150,
    ToplikeSelectionSteps::MissingTransverseEnergy250,
    ToplikeSelectionSteps::MissingTransverseEnergy350 ,
ToplikeSelectionSteps::BaseHLT,
};

const unsigned int monotopMetSelectionSize =
       sizeof(monotopMetSelection)/sizeof(ToplikeSelectionSteps::AtLeastOneGoodJet);

const ToplikeSelectionSteps::Step monotopMuonSelection[] = {
	ToplikeSelectionSteps::IsolatedMuon,
	ToplikeSelectionSteps::LooseElectronVeto,
	ToplikeSelectionSteps::AtLeastOneGoodJet,
	ToplikeSelectionSteps::AtLeastTwoGoodJets,
	ToplikeSelectionSteps::AtLeastThreeGoodJets,
	ToplikeSelectionSteps::AtLeastOneBtag,
    ToplikeSelectionSteps::MissingTransverseEnergy150,
    ToplikeSelectionSteps::MissingTransverseEnergy250,
    ToplikeSelectionSteps::MissingTransverseEnergy350 //,
//ToplikeSelectionSteps::BaseHLT,
};

const unsigned int monotopMuonSelectionSize =
       sizeof(monotopMuonSelection)/sizeof(ToplikeSelectionSteps::AtLeastOneGoodJet);

const ToplikeSelectionSteps::Step monotopElectronSelection[] = {
        ToplikeSelectionSteps::IsolatedElectron,
        ToplikeSelectionSteps::LooseMuonVeto,
        ToplikeSelectionSteps::ConversionRejection,
        ToplikeSelectionSteps::ConversionFinder,
	ToplikeSelectionSteps::AtLeastOneGoodJet,
	ToplikeSelectionSteps::AtLeastTwoGoodJets,
	ToplikeSelectionSteps::AtLeastThreeGoodJets,
	ToplikeSelectionSteps::AtLeastOneBtag,
    ToplikeSelectionSteps::MissingTransverseEnergy150,
    ToplikeSelectionSteps::MissingTransverseEnergy250,
    ToplikeSelectionSteps::MissingTransverseEnergy350 //,
//ToplikeSelectionSteps::BaseHLT,
};

const unsigned int monotopElectronSelectionSize =
       sizeof(monotopElectronSelection)/sizeof(ToplikeSelectionSteps::AtLeastOneGoodJet);


typedef struct {
	float deltaR;
	bool leptonic, hadronic;
} topTruth;

typedef struct {
	float deltaR;
	int gpInd;
	MCParticlePointer ptr;
} mcObj;


typedef std::vector< mcObj > mcList;


class ToplikeCandidate : public TopPairEventCandidate {

protected:
    // ElectronPointer electronFromW;
    // JetPointer leptonicBJet, hadronicBJet, jet1FromW, jet2FromW;
    JetPointer jet3FromW, jet4FromW;
    ParticlePointer hadronicWtPrime, tPrime;
    // ParticlePointer neutrino1, neutrino2, leptonicW1, leptonicW2, hadronicW,
    // leptonicTop1, leptonicTop2, hadronicTop, ttbarResonance;
    // unsigned short selectedNeutrino, currentSelectedNeutrino, hadronicBIndex,
    // leptonicBIndex, jet1FromWIndex, jet2FromWIndex;
    unsigned short jet3FromWIndex, jet4FromWIndex;
		double ptTprimeSystem, htSystem;
    bool doneReconstructiontop;
		mcList getMCList(const Particle *const recoObject) const;
		mcList getMCListForJets(const Jet *const recoObject) const;
		bool chkBW(const int ind1, const int ind2, const int ind3) const;
    bool chkIfChild(int gpInd, int motherGpInd) const;
    int chkMCMatch(const Particle *const recoObject, int motherInd, 
    	const int pdgId, int antiId = 0) const;
    int chkForQuark(const JetPointer recoObject, const int motherInd,
    	const int badInd = -1) const;
    int getNumMCMatchesForTop(const ParticlePointer &recoTop, 
    	bool hadronic = true) const;
    int getNumMCPermutsForTop(const ParticlePointer &recoTop, 
			bool hadronic = true) const;
		// int lTopDauMatching(const mcObj &topTru) const;
		// int hTopDauMatching(const mcObj &topTru) const;
    int strictHTopMatching(const mcObj &topTru) const;
    int strictLTopMatching(const mcObj &topTru) const;
    
public:
    ToplikeCandidate();
    ToplikeCandidate(const Event& event);
    virtual ~ToplikeCandidate();

    virtual bool isTopReconstructed(void) const {
			return doneReconstructiontop; 
    }

    /*
    const JetPointer getJet3FromHadronicW2() const;
    const JetPointer getJet4FromHadronicW2() const;
    const ParticlePointer getHadronicW2() const;
    const ParticlePointer getTprimeResonance() const;
    */

    void recoTprimeUsingChi2(ElectronPointer electron);
		virtual void recoBestSingleTop(LeptonPointer lepton);
		double TPrimeHTSystem() const;
		double PtTPrimeSystem() const;

    // Overload the following
		// virtual const ParticlePointer getResonance() const;
		bool hasAtLeastFiveGoodJets() const;
		double tpmass() const;
    virtual double getGlobalChi2() const;
		virtual double getLeptonicChi2(double topMass, double unused) const;
		virtual double getHadronicChi2() const;
    double getWChi2() const;
		double sumPt() const;
		double PtTtbarSystem() const;
		double PtTtbarSystem(unsigned short neutrinoSolution) const;
		virtual double getLoneHadChi2() const;
		topTruth getMCMatches(const ParticlePointer &recoObject) const;
    int getNumMCMatchesHTop() const;
    int getNumMCMatchesLTop() const;
		int getNumCorrectIDLTop() const;
		int getNumCorrectIDHTop() const;
		int goodLTopMatching() const;
		int goodHTopMatching() const;
		int getTausInJets() const;
		int numTaus() const;
		int missRecoJetsForGenJets() const;
		int missGenJetsForRecoJets() const;
		int sameMCCharge(const ParticlePointer &lepton, const int lepID) const;
};


class TopNoMassConstraint : public ToplikeCandidate {
public:
	TopNoMassConstraint();
	TopNoMassConstraint(const Event& event);
	virtual ~TopNoMassConstraint();
	
	virtual double getLoneHadChi2() const;
  virtual double getLepBAngle() const;
};


class TopPlusXCandidates : public ToplikeCandidate {
public:
	
	static const JetPointer nulljet;
	
	TopPlusXCandidates();
	TopPlusXCandidates(const Event& event);
	virtual ~TopPlusXCandidates();

	virtual double recoBestHadroTop(
		const JetPointer jet = nulljet, const JetPointer wJet1 = nulljet,
		const JetPointer wJet2 = nulljet);

	virtual void recoBestLeptoTop(LeptonPointer lepton,
		const JetPointer jet = nulljet, const JetPointer wJet1 = nulljet,
		const JetPointer wJet2 = nulljet);
	virtual void recoHadronicTop(LeptonPointer lepton,
		const JetPointer jet = nulljet);
	virtual void findDJet(const JetPointer topJet = nulljet);
	virtual bool passesSelectionStep(enum
		ToplikeSelectionSteps::Step step);
	virtual bool passesSelectionStepUpTo(unsigned int step,
		const ToplikeSelectionSteps::Step steps[]);
	virtual bool passesSelectionStepUpTo(unsigned int step,
		const std::vector<ToplikeSelectionSteps::Step>& steps);
	virtual bool passesFullEPlusJetSelection();
	virtual bool passesFullEPlusJetSelectionKK();
	virtual bool passesFullMuPlusJetSelection();
	virtual bool passesMETCut(double metCut=20) const;
	virtual bool passesHTCut(double htCut=700) const;
	virtual bool passesExtraElectronCut() const;
	virtual bool hasOnlyOneGoodIsolatedMuon();
	virtual bool hasGoodIsolatedMuon();
	virtual bool hasGoodIsolatedElectron();
	virtual bool hasNoIsolatedElectron() const;
	virtual bool hasNoGoodIsolatedElectron() const;
	virtual bool hasNoGoodIsolatedMuon() const;
	virtual bool hasNoSecondIsolatedElectron() const;
	virtual bool hasNoSecondIsolatedMuon() const;
	virtual bool hasAtLeastOneGoodJet() const;
	virtual bool hasAtLeastTwoGoodJets() const;
	virtual bool hasAtLeastThreeGoodJets() const;
	virtual bool hasAtLeastFourGoodJets() const;
	virtual bool passesHLTbase() const;

	virtual double jetsHTNoTop(unsigned int numJets = 3) const;
	virtual double ST() const;
	virtual double getTopMetAngle() const;
	virtual JetPointer leadnontopjet() const;
	virtual double mass2jets(unsigned int jet1, unsigned int jet2) const;
	virtual double mass4jets() const;

	// The templates below are no longer necessary because there is now a
	// LeptonPointer, but they still work, so leave them as-is.
	
	// Template functions must be defined here to be instantiated in other files.
	template <class PartPtr> double transMass4j(const PartPtr leptonPtr) const {
		double px = leptonPtr->px() + met->px();
		double py = leptonPtr->py() + met->py();
		double pz = 0.0;
		double et =  leptonPtr->et() + met->et();
		for (unsigned short jetIndex = 0; jetIndex < 4 && jetIndex < goodJets.size(); ++jetIndex) {
			px += goodJets.at(jetIndex)->px();
			py += goodJets.at(jetIndex)->py();
			et += goodJets.at(jetIndex)->et();
		}
		Particle mt(et, px, py, pz);
		return (mt.mass());
	}

	template <class PartPtr> double transMass2j(const PartPtr leptonPtr) const {
		double px = leptonPtr->px() + met->px();
		double py = leptonPtr->py() + met->py();
		double pz = 0.0;
		double et =  leptonPtr->et() + met->et();
		if (goodBJets.size() > 0) {
			px += goodBJets.front()->px();
			py += goodBJets.front()->py();
			et += goodBJets.front()->et();
		}
		for (unsigned short jetIndex = 0;  jetIndex < 2 && jetIndex < goodJets.size(); ++jetIndex) {
			if (goodBJets.size() <= 0 || goodJets.at(jetIndex) !=  goodBJets.front()) {
				px += goodJets.at(jetIndex)->px();
				py += goodJets.at(jetIndex)->py();
				et += goodJets.at(jetIndex)->et();
				jetIndex = 2; // Terminate loop.
			}
		}
		Particle mt(et, px, py, pz);
		return (mt.mass());
	}


	template <class PartPtr> const ParticlePointer transMasslm1b(const PartPtr leptonPtr) const {
		double px = leptonPtr->px() + met->px();
		double py = leptonPtr->py() + met->py();
		double pz = 0.0;
		double et =  leptonPtr->et() + met->et();
		if (goodBJets.size() > 0) {
			px += goodBJets.front()->px();
			py += goodBJets.front()->py();
			et += goodBJets.front()->et();
		}
		return (ParticlePointer(new Particle(et, px, py, pz)));
	}


	template <class PartPtr> const ParticlePointer massl1b(const PartPtr leptonPtr) const {
		double px = leptonPtr->px();
		double py = leptonPtr->py();
		double pz = 0.0;
		double et =  leptonPtr->et();
		if (goodBJets.size() > 0) {
			px += goodBJets.front()->px();
			py += goodBJets.front()->py();
			et += goodBJets.front()->et();
		}
		return (ParticlePointer(new Particle(et, px, py, pz)));
	}


	template <class PartPtr> double deltaPhiTops(const PartPtr leptonPtr) const {
		double px = 0.0, py = 0.0, pz = 0.0, et = 0.0;
		for (unsigned short jetIndex = 1; jetIndex < 4 && jetIndex < goodJets.size(); ++jetIndex) {
			px += goodJets.at(jetIndex)->px();
			py += goodJets.at(jetIndex)->py();
			et += goodJets.at(jetIndex)->et();
		}
		ParticlePointer mt = ParticlePointer(new Particle(et, px, py, pz));
		return (transMasslm1b(leptonPtr)->deltaPhi(mt));
	}


	template <class PartPtr> double deltaPhiLepJet(const PartPtr leptonPtr) const {
		if (goodJets.size() > 0)
			return (leptonPtr->deltaPhi(goodJets.front()));
		return (0.0);
	}
	

	JetPointer dJetFromWp;
	short dJetFromWpIndex;
};


class TwoNonResTops : public TopPlusXCandidates {
public:
	TwoNonResTops();
	TwoNonResTops(const Event& event);
	virtual ~TwoNonResTops();
	
	void recoNonResTops(LeptonPointer lepton);
	void recoNonResTopsWdjet(LeptonPointer lepton);
	void recoWpFrom1Top(LeptonPointer lepton);
	virtual double getGlobalChi2() const;
	virtual const JetPointer getLtNonTopJet() const;
	virtual const ParticlePointer getWprime() const;
	virtual const ParticlePointer getBtBWprime() const;
	virtual const ParticlePointer getNegWprime() const;
	virtual const ParticlePointer getNegWprimeBad() const;
	virtual double getHadTopDAngle() const;
	virtual void getTrueWpChain();
	virtual MCParticlePointer getWpTru() const;
	virtual MCParticlePointer getWpTopTru() const;
	virtual MCParticlePointer getSpecTop() const;
	virtual MCParticlePointer getWpTopBTru() const;
	virtual MCParticlePointer getSpecTopB() const;
	virtual MCParticlePointer getWpDDauTru() const;
  virtual double getTotalChi2DJ(unsigned short neutrinoSolution) const;

	template <class PartPtr> double deltaPhiLepDJet(const PartPtr leptonPtr) const {
		if (goodJets.size() > 4)
			return (leptonPtr->deltaPhi(getLtNonTopJet()));
		return (0.0);
	}
	
	ParticlePointer wpFrom1Top, wpBadFrom1Top;

protected:
	MCParticlePointer wpTru, wpTopTru, specTopTru, wpDDauTru;
	MCParticlePointer wpTopBTru, specTopBTru;
	bool wpGenParticlesSet;
	ParticlePointer topFromWp;
};


class LeptoTopNoMassConstraint : public TopNoMassConstraint {
public:
	LeptoTopNoMassConstraint();
	LeptoTopNoMassConstraint(const Event& event);
	virtual ~LeptoTopNoMassConstraint();
	
	// virtual bool passesFullEPlusJetSelection() const;
	virtual void inspectReconstructedEvent() const;

};

}

#endif /* TOPLIKECANDIDATE_H_ */
