/*
 * HighLevelTriggers.h
 *
 *  Created on: 17 Mar 2011
 *      Author: kreczko
 */

#ifndef HIGHLEVELTRIGGERS_H_
#define HIGHLEVELTRIGGERS_H_
#include <string>
#include <boost/array.hpp>

namespace HLTriggers{
enum value{
//5e33v4.16 triggers (Run2012A):

   HLT_IsoMu20_eta2p1=0,  //_v4	200	200	200	200	120	80	8	8	0		L1_SingleMu16er
   HLT_IsoMu24_eta2p1,  //_v12	1	1	1	1	1	1	1	1	0		L1_SingleMu16er
   HLT_IsoMu30_eta2p1,  //_v12	1	1	1	1	1	1	1	1	0		L1_SingleMu16er
   HLT_IsoMu34_eta2p1,  //_v10  1	1	1	1	1	1	1	1	0		L1_SingleMu16er
   HLT_IsoMu40_eta2p1,  //_v7	1	1	1	1	1	1	1	1	0		L1_SingleMu16er
   HLT_L1SingleMu12,    //_v1	60000	30000	30000	60000	72000	480000	150	50	0		L1_SingleMu12
   HLT_L2Mu10_NoVertex_NoBPTX3BX_NoHalo, //_v1	100	100	100	100	60	40	4	4	0		L1_SingleMu6_NotBptxOR
   HLT_L2Mu20_NoVertex_NoBPTX3BX_NoHalo, //_v1	1	1	1	1	1	1	10	1	0		L1_SingleMu6_NotBptxOR
   HLT_L2Mu20_eta2p1_NoVertex, //_v1	100	100	100	100	100	100	100	100	0		L1_SingleMu16er
   HLT_L2Mu30_NoVertex_NoBPTX3BX_NoHalo, //_v1	1	1	1	1	1	1	10	1	0		L1_SingleMu6_NotBptxOR
   HLT_L2Mu70_eta2p1_PFMET65, //_v4	1	1	1	1	1	1	1	1	0		L1_SingleMu16er
   HLT_L2Mu80_eta2p1_PFMET70, //_v4	1	1	1	1	1	1	1	1	0		L1_SingleMu16er
   HLT_Mu12, //_v16	30	30	30	30	72	96	600	600	0		L1_SingleMu7
   HLT_Mu15_eta2p1, //_v3	50	25	25	50	120	160	800	800	1		L1_SingleMu7
   HLT_Mu24_eta2p1, //_v3	200	200	200	200	120	80	8	8	0		L1_SingleMu16er
   HLT_Mu30_eta2p1, //_v3	200	200	200	200	120	80	8	8	0		L1_SingleMu16er
   HLT_Mu40_eta2p1_Track50_dEdx3p6, //_v3	1	1	1	1	1	1	1	1	0		L1_SingleMu16er
   HLT_Mu40_eta2p1_Track60_dEdx3p7, //_v3	1	1	1	1	1	1	1	1	0		L1_SingleMu16er
   HLT_Mu40_eta2p1, //_v9	1	1	1	1	1	1	1	1	0		L1_SingleMu16er
   HLT_Mu50_eta2p1, //_v6	1	1	1	1	1	1	1	1	0		L1_SingleMu16er
   HLT_Mu5, //_v18	30000	30000	30000	30000	72000	48000	24000	24000	0		L1_SingleMu3
   HLT_RelIso1p0Mu17, //_v3	0	0	0	0	0	0	0	0	0		L1_SingleMu12
   HLT_RelIso1p0Mu5,  //_v3	0	0	0	

//Additional 7e33v2.5 triggers (Run2012B):
HLT_IsoMu17_eta2p1_CentralPFNoPUJet30_BTagIPIter=23, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleMu14er
HLT_IsoMu17_eta2p1_CentralPFNoPUJet30, //_v1	20	20	20	20	20	20	1	1	0	0		L1_SingleMu14er
HLT_IsoMu17_eta2p1_TriCentralPFNoPUJet30_30_20, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleMu14er
HLT_IsoMu20_WCandPt80, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleMu16
HLT_IsoMu20_eta2p1_CentralPFJet80, //_v6	1	1	1	1	1	1	1	1	0	0		L1_SingleMu16er
HLT_IsoMu24_CentralPFJet30_CentralPFJet25_PFMET20, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleMu16
HLT_IsoMu24_CentralPFJet30_CentralPFJet25, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleMu16
HLT_IsoMu24_PFJet30_PFJet25_Deta3_CentralPFJet25, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleMu16
HLT_IsoMu24, //_v15	1	1	1	1	1	1	1	1	0	0		L1_SingleMu16
HLT_IsoMu30, //_v9	1	1	1	1	1	1	1	1	0	0		L1_SingleMu16
HLT_L2Mu70_eta2p1_PFMET55, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleMu16er
HLT_L2Mu70_eta2p1_PFMET60, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleMu16er
HLT_Mu12_eta2p1_DiCentral_20, //_v3	1050	1050	1050	870	870	870	870	870	0	0		L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_20_12 OR L1_Mu10er_JetC32 OR L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_32_12
HLT_Mu12_eta2p1_DiCentral_40_20_BTagIP3D1stTrack, //_v3	160	160	160	130	130	130	130	130	0	0		L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_20_12 OR L1_Mu10er_JetC32 OR L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_32_12
HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack, //_v3	1	1	1	1	1	1	1	1	0	0		L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_20_12 OR L1_Mu10er_JetC32 OR L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_32_12
HLT_Mu12_eta2p1_DiCentral_40_20, //_v3	570	570	570	470	470	470	470	470	0	0		L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_20_12 OR L1_Mu10er_JetC32 OR L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_32_12
HLT_Mu12_eta2p1_L1Mu10erJetC12WdEtaPhi1DiJetsC, //_v3	1000	1000	1000	1000	1000	1000	40	40	0	0		L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_20_12 OR L1_Mu10er_JetC32 OR L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_32_12
HLT_Mu15_eta2p1_TriCentral_40_20_20_BTagIP3D1stTrack, //_v3	70	70	70	60	60	60	60	60	0	0		L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_20_12 OR L1_Mu10er_JetC32 OR L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_32_12
HLT_Mu15_eta2p1_TriCentral_40_20_20_DiBTagIP3D1stTrack, //_v3	1	1	1	1	1	1	1	1	0	0		L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_20_12 OR L1_Mu10er_JetC32 OR L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_32_12
HLT_Mu15_eta2p1_TriCentral_40_20_20, //_v3	180	180	180	150	150	150	10	10	0	0		L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_20_12 OR L1_Mu10er_JetC32 OR L1_Mu10er_JetC12_WdEtaPhi1_DoubleJetC_32_12
HLT_Mu17_eta2p1_CentralPFNoPUJet30_BTagIPIter, //_v1	96	96	96	96	96	96	1	1	0	0		L1_SingleMu14er
HLT_Mu17_eta2p1_TriCentralPFNoPUJet30_30_20, //_v1	64	64	64	64	64	64	1	1	0	0		L1_SingleMu14er
HLT_Mu24_CentralPFJet30_CentralPFJet25, //_v1	15	15	10	10	10	10	1	1	0	0		L1_SingleMu16
HLT_Mu24_PFJet30_PFJet25_Deta3_CentralPFJet25, //_v1	15	15	10	10	10	10	1	1	0	0		L1_SingleMu16
HLT_Mu24, //_v14	200	200	200	200	200	200	8	8	0	0		L1_SingleMu16
HLT_Mu30, //_v14	200	200	200	200	200	200	8	8	0	0		L1_SingleMu16
HLT_Mu40, //_v12	1	1	1	1	1	1	1	1	0	0		L1_SingleMu16
HLT_RelIso1p0Mu20, //_v1	550	550	500	300	300	300	1	1	0	0		L1_SingleMu16er

ELECTRON_TRIGGERS=51,

HLT_Ele100_CaloIdVT_TrkIdT, //_v10	1	1	1	1	1	1	1	1	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele22_CaloIdL_CaloIsoVL, //_v5	0	0	0	0	0	0	0	0	1		L1_SingleEG12
HLT_Ele27_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL, //_v10	300	300	300	300	180	120	50	50	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele27_WP80_PFMET_MT50, //_v4	1	1	1	1	1	1	1	1	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele27_WP80, //_v10	1	1	1	1	1	1	1	1	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele30_CaloIdVT_TrkIdT, //_v5	225	225	225	225	140	90	10	10	0		L1_SingleEG22
HLT_Ele32_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL, //_v10	0	0	0	0	0	0	0	0	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele65_CaloIdVT_TrkIdT, //_v13	30	30	30	30	20	10	1	1	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele80_CaloIdVT_TrkIdT, //_v10	1	1	1	1	1	1	1	1	0		L1_SingleEG20 OR L1_Sing

HLT_Ele25_CaloIdVL_CaloIsoT_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet30_30_20, //_v1	40	40	40	40	40	40	1	1	0	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFNoPUJet30_BTagIPIter, //_v6	1	1	1	1	1	1	1	1	0	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFNoPUJet30, //_v5	125	125	100	75	50	25	8	8	0	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFNoPUJet30_30_20, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele25_CaloIdVT_CaloIsoVL_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet30, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele25_CaloIdVT_CaloIsoVL_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet50_40_30, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele25_CaloIdVT_TrkIdT_TriCentralPFNoPUJet30_30_20, //_v1	160	160	160	160	160	160	6	6	0	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele27_WP80_CentralPFJet80, //_v6	1	1	1	1	1	1	1	1	0	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele27_WP80_WCandPt80, //_v6	1	1	1	1	1	1	1	1	0	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele32_WP80_CentralPFJet35_CentralPFJet25_PFMET20, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele32_WP80_CentralPFJet35_CentralPFJet25, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele32_WP80_PFJet30_PFJet25_Deta3_CentralPFJet30, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele32_WP80_PFJet30_PFJet25_Deta3, //_v1	10	10	10	10	10	10	1	1	0	0		L1_SingleEG20 OR L1_SingleEG22
HLT_Ele90_CaloIdVT_GsfTrkIdT, //_v1	1	1	1	1	1	1	1	1	0	0		L1_SingleEG20 OR L1_SingleEG22

OTHER_TRIGGERS,
    HLT_MET120_HBHENoiseCleaned,
    HLT_MET120,
    HLT_MET200_HBHENoiseCleaned,
    HLT_MET200,
    HLT_MET300_HBHENoiseCleaned,
    HLT_MET300,
    HLT_MET400_HBHENoiseCleaned,
    HLT_MET400,
    HLT_PFMET150,
    HLT_PFMET180,
    HLT_DiCentralPFJet30_PFMET80,
    HLT_DiJet80Eta2p6_BTagIP3DFastPVLoose,

    HLT_HT200,
    HLT_HT250,
    HLT_HT300,
    HLT_HT350,
    HLT_HT400,
    HLT_HT450,
    HLT_HT500,
    HLT_HT550,

    NUMBER_OF_TRIGGERS
};

//const char *name[] = {
const boost::array<std::string, HLTriggers::NUMBER_OF_TRIGGERS> names = { {
   "HLT_IsoMu20_eta2p1_v",
   "HLT_IsoMu24_eta2p1_v",
   "HLT_IsoMu30_eta2p1_v",
   "HLT_IsoMu34_eta2p1_v",
   "HLT_IsoMu40_eta2p1_v",
   "HLT_L1SingleMu12_v",
   "HLT_L2Mu10_NoVertex_NoBPTX3BX_NoHalo_v",
   "HLT_L2Mu20_NoVertex_NoBPTX3BX_NoHalo_v",
   "HLT_L2Mu20_eta2p1_NoVertex_v",
   "HLT_L2Mu30_NoVertex_NoBPTX3BX_NoHalo_v",
   "HLT_L2Mu70_eta2p1_PFMET65_v",
   "HLT_L2Mu80_eta2p1_PFMET70_v",
   "HLT_Mu12_v",
   "HLT_Mu15_eta2p1_v",
   "HLT_Mu24_eta2p1_v",
   "HLT_Mu30_eta2p1_v",
   "HLT_Mu40_eta2p1_Track50_dEdx3p6_v",
   "HLT_Mu40_eta2p1_Track60_dEdx3p7_v",
   "HLT_Mu40_eta2p1_v",
   "HLT_Mu50_eta2p1_v",
   "HLT_Mu5_v",
   "HLT_RelIso1p0Mu17_v",
   "HLT_RelIso1p0Mu5_v",
"HLT_IsoMu17_eta2p1_CentralPFNoPUJet30_BTagIPIter_v",
"HLT_IsoMu17_eta2p1_CentralPFNoPUJet30_v",
"HLT_IsoMu17_eta2p1_TriCentralPFNoPUJet30_30_20_v",
"HLT_IsoMu20_WCandPt80_v",
"HLT_IsoMu20_eta2p1_CentralPFJet80_v",
"HLT_IsoMu24_CentralPFJet30_CentralPFJet25_PFMET20_v",
"HLT_IsoMu24_CentralPFJet30_CentralPFJet25_v",
"HLT_IsoMu24_PFJet30_PFJet25_Deta3_CentralPFJet25_v",
"HLT_IsoMu24_v",
"HLT_IsoMu30_v",
"HLT_L2Mu70_eta2p1_PFMET55_v",
"HLT_L2Mu70_eta2p1_PFMET60_v",
"HLT_Mu12_eta2p1_DiCentral_20_v",
"HLT_Mu12_eta2p1_DiCentral_40_20_BTagIP3D1stTrack_v",
"HLT_Mu12_eta2p1_DiCentral_40_20_DiBTagIP3D1stTrack_v",
"HLT_Mu12_eta2p1_DiCentral_40_20_v",
"HLT_Mu12_eta2p1_L1Mu10erJetC12WdEtaPhi1DiJetsC_v",
"HLT_Mu15_eta2p1_TriCentral_40_20_20_BTagIP3D1stTrack_v",
"HLT_Mu15_eta2p1_TriCentral_40_20_20_DiBTagIP3D1stTrack_v",
"HLT_Mu15_eta2p1_TriCentral_40_20_20_v",
"HLT_Mu17_eta2p1_CentralPFNoPUJet30_BTagIPIter_v",
"HLT_Mu17_eta2p1_TriCentralPFNoPUJet30_30_20_v",
"HLT_Mu24_CentralPFJet30_CentralPFJet25_v",
"HLT_Mu24_PFJet30_PFJet25_Deta3_CentralPFJet25_v",
"HLT_Mu24_v",
"HLT_Mu30_v",
"HLT_Mu40_v",
"HLT_RelIso1p0Mu20_v",

"ELECTRON_TRIGGERS",

"HLT_Ele100_CaloIdVT_TrkIdT_v",
"HLT_Ele22_CaloIdL_CaloIsoVL_v",
"HLT_Ele27_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v",
"HLT_Ele27_WP80_PFMET_MT50_v",
"HLT_Ele27_WP80_v",
"HLT_Ele30_CaloIdVT_TrkIdT_v",
"HLT_Ele32_CaloIdL_CaloIsoVL_TrkIdVL_TrkIsoVL_v",
"HLT_Ele65_CaloIdVT_TrkIdT_v",
"HLT_Ele80_CaloIdVT_TrkIdT_v",

"HLT_Ele25_CaloIdVL_CaloIsoT_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet30_30_20_v",
"HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFNoPUJet30_BTagIPIter_v",
"HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFNoPUJet30_v",
"HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFNoPUJet30_30_20_v",
"HLT_Ele25_CaloIdVT_CaloIsoVL_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet30_v",
"HLT_Ele25_CaloIdVT_CaloIsoVL_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet50_40_30_v",
"HLT_Ele25_CaloIdVT_TrkIdT_TriCentralPFNoPUJet30_30_20_v",
"HLT_Ele27_WP80_CentralPFJet80_v",
"HLT_Ele27_WP80_WCandPt80_v",
"HLT_Ele32_WP80_CentralPFJet35_CentralPFJet25_PFMET20_v",
"HLT_Ele32_WP80_CentralPFJet35_CentralPFJet25_v",
"HLT_Ele32_WP80_PFJet30_PFJet25_Deta3_CentralPFJet30_v",
"HLT_Ele32_WP80_PFJet30_PFJet25_Deta3_v",
"HLT_Ele90_CaloIdVT_GsfTrkIdT_v",

"OTHER_TRIGGERS",
   "HLT_MET120_HBHENoiseCleaned_v",
   "HLT_MET120_v",
   "HLT_MET200_HBHENoiseCleaned_v",
   "HLT_MET200_v",
   "HLT_MET300_HBHENoiseCleaned_v",
   "HLT_MET300_v",
   "HLT_MET400_HBHENoiseCleaned_v",
   "HLT_MET400_v",
   "HLT_PFMET150_v",
   "HLT_PFMET180_v",
   "HLT_DiCentralPFJet30_PFMET80_v",
   "HLT_DiJet80Eta2p6_BTagIP3DFastPVLoose_v",
   "HLT_HT200_v",
   "HLT_HT250_v",
   "HLT_HT300_v",
   "HLT_HT350_v",
   "HLT_HT400_v",
   "HLT_HT450_v",
   "HLT_HT500_v",
   "HLT_HT550_v"
} };

}
#endif /* HIGHLEVELTRIGGERS_H_ */
