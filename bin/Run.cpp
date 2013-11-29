/*
 * Run.cc
 *
 *  Created on: Mar 11, 2010
 *      Author: lkreczko
 */
//#include "cms_bristol_ana_v3.hh"
#include "TSystem.h"
#include "TStopwatch.h"
#include "TROOT.h"
#include "Analysis.h"
#include <iostream>
#include <boost/scoped_ptr.hpp>

////#include "../Cert_198049-208686_8TeV_PromptReco_Collisions12_JSON.C"
//#include "../Cert_190456-203002_8TeV_PromptReco_Collisions12_JSON.C"
//#include "../Cert_190456-196531_8TeV_13Jul2012ReReco_Collisions12_JSON.C"

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/shm.h>
#include<getopt.h>
#include<getopt.h>

#define SIGNAL(s, handler)	{ \
	sa.sa_handler = handler; \
	if (sigaction(s, &sa, NULL) < 0) { \
	    fprintf(stderr, "Couldn't establish signal handler (%d)", s); \
	    exit(1); \
	} \
    }

Analysis *myAnalysis;
static void term(int qwe){
  printf("terminating with signal #%d\n",qwe); 
  if( myAnalysis ) delete myAnalysis;
  exit(2);
} 

using namespace ROOT;
using namespace std;
using namespace BAT;

void setUpOnce() {
    //needed to proper link vector<float> etc.
    gROOT->ProcessLine("#include <vector>");
    //prevent automatic ownership of ROOT objects
    TH1F::AddDirectory(false);
    //ignore ROOT errors (temporaly due to different nTuple content)
    gROOT->ProcessLine("gErrorIgnoreLevel = 3001;");
}

int main(int argc, char **argv) {
    // reassign interrupt signal
    struct sigaction sa;
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT); // finish the job on Ctrl-C
    sigaddset(&mask, SIGTERM); // condor_rm
    sa.sa_mask = mask;
    sa.sa_flags = 0;
    SIGNAL(SIGINT, term); // Terminate and call the cleanup function
    SIGNAL(SIGTERM, term); // Terminate and call the cleanup function
    myAnalysis = 0;

    // parse the options
    static struct option options[] = {
       {"help",         0, 0, 'h'},
       {"datatype",     1, 0, 'd'},
       {"selection",    1, 0, 's'},
       {"jecVariation", 1, 0, 'j'},
       {"input",        1, 0, 'i'},
       {"output",       1, 0, 'o'},
       {"resVariation", 1, 0, 'r'},
       {"bTagVariation",1, 0, 'b'},
       {0, 0, 0, 0}
    };

    cout<<"Running: ";
    for(int arg=0; arg<argc; arg++) cout<<argv[arg]<<" ";
    cout<<endl;

    const ToplikeSelectionSteps::Step *monotopSelection = monotopMetSelection;
    unsigned int monotopSelectionSize = monotopMetSelectionSize;
    const char *outputDirectory = "";
    const char *inputDirectory = 0;
    BAT::EventWeightProvider::SampleVersion variation = EventWeightProvider::central;

    enum {NONE=0, A=1, A1=2, A2=3, A3=4, A4=5, A5=6, A6=7, A7=8, A8=9, A9=10,
          B=100, B1=101, B2=102, B3=103, B4=104, B5=105, B6=106, B7=107, B8=108, B9=109, B10=110, B11=111, B12=112, B13=113, B14=114, B15=115, B16=116, B17=117, B18=118,
          B19=119, B20=120, B21=121,
          C=200, C1=201, C2=202, C3=203, C4=204, C5=205, C6=206, C7=207, C8=208, C9=209, C10=210, C11=211, C12=212, C13=213, C14=214, C15=215, C16=216, C17=217, C18=218,
          C19=219, C20=220, C21=221, C22=222, C23=223, C24=224, C25=225, C26=226, C27=227, C28=228, C29=229, C30=230, C31=231, C32=232, C33=233, C34=234, C35=235, C36=236,
          C37=237, C38=238, C39=239, C40=240,
          D=300, D1=301, D2=302, D3=303, D4=304, D5=305, D6=306, D7=307, D8=308, D9=309, D10=310, D11=311, D12=312, D13=313, D14=314, D15=315, D16=316, D17=317, D18=318, 
          D19=319, D20=320, D21=321, D22=322, D23=323, D24=324, D25=325, D26=326, D27=327, D28=328, D29=329, D30=330, D31=331, D32=332, D33=333, D34=334, D35=335, D36=336,
          D37=337,
          TT=1000, TT1=1001, TT2=1002, TT3=1003, TT4=1004, TT5=1005, TT6=1006, TT7=1007, TT8=1008, TT9=1009, TT10=1010, TT11=1011, TT12=1012, TT13=1013,
          TTll=1050, TTll1=1051, TTll2=1052, TTll3=1053, TTll4=1054, TTll5=1055, TTll6=1056, TTll7=1057, TTll8=1058, TTll9=1059,
          TThh=1060, TThh1=1061, TThh2=1062, TThh3=1063, TThh4=1064, TThh5=1065, TThh6=1066, TThh7=1067, TThh8=1069, TThh9=1069,
          TTlh=1070, TTlh1=1071, TTlh2=1072, TTlh3=1073, TTlh4=1074, TTlh5=1075, TTlh6=1076, TTlh7=1077, TTlh8=1078, TTlh9=1079,
          TTsu =1100, TTsd =1200, TTmu =1300, TTmd =1400,
          TTsu1=1101, TTsd1=1201, TTmu1=1301, TTmd1=1401,
          TTsu2=1102, TTsd2=1202, TTmu2=1302, TTmd2=1402,
          TTsu3=1103, TTsd3=1203, TTmu3=1303, TTmd3=1403,
          TTsu4=1104, TTsd4=1204, TTmu4=1304, TTmd4=1404,
          TTsu5=1105, TTsd5=1205, TTmu5=1305, TTmd5=1405,
          WJ=2000, WJ1=2001, WJ2=2002, WJ3=2003, WJ4=2004, WJ5=2005, WJ6=2006, WJ7=2007, WJ8=2008, WJ9=2009, WJ10=2010, WJ11=2011, WJ12=2012, WJ13=2013,
          WJ14=2014, WJ15=2015, WJ16=2016, WJ17=2017, WJ18=2018, WJ19=2019, WJ20=2020, WJ21=2021, WJ22=2022, WJ23=2023, WJ24=2024, WJ25=2025, WJ26=2026,
          WJ27=2027, WJ28=2028, WJ29=2029, WJ30=2030, WJ31=2031, WJ32=2032, WJ33=2033, WJ34=2034, WJ35=2035, WJ36=2036, WJ37=2037, WJ38=2038, WJ39=2039,
          WJsu=2100, WJsd=2200, WJmu=2300, WJmd=2400, 
          W1J  =3000, W1J1  =3001, W1J2  =3002, W1J3  =3003, W1J4  =3004, W1J5 =3005, 
          W1J6 =3006, W1J7  =3007, W1J8  =3008, W1J9  =3009, W1J10 =3010, W1J11=3011, 
          W1J12=3012, W1J13 =3013, W1J14 =3014, W1J15 =3015, W1J16 =3016, W1J17=3017, 
          W1J18=3018, W1J19 =3019, W1J20 =3020, W1J21 =3021, W1J22 =3022, W1J23=3023, 
          W1J24=3024, W1J25 =3025, W1J26 =3026, W1J27 =3027, W1J28 =3028, W1J29=3029, 
          W1J30=3030, W1J31 =3031, W1J32 =3032, W1J33 =3033, W1J34 =3034, W1J35=3035, 
          W1J36=3036, W1J37 =3037, W1J38 =3038, W1J39 =3039, W1J40 =3040, W1J41=3041, 
          W1Jsu=3100, W1Jsu1=3101, W1Jsu2=3102, W1Jsu3=3103, W1Jsu4=3104,
          W1Jsd=3200, W1Jsd1=3201, W1Jsd2=3202, W1Jsd3=3203, W1Jsd4=3204,
          W1Jmu=3300, W1Jmu1=3301, W1Jmu2=3302, W1Jmu3=3303, W1Jmu4=3304,
          W1Jmd=3400, W1Jmd1=3401, W1Jmd2=3402, W1Jmd3=3403, W1Jmd4=3404,
          W2J  =4000, W2J1  =4001, W2J2  =4002, W2J3  =4003, W2J4  =4004, W2J5=4005, 
          W2J6 =4006, W2J7  =4007, W2J8  =4008, W2J9  =4009, W2J10 =4010, W2J11=4011,
          W2J12=4012, W2J13 =4013, W2J14 =4014, W2J15 =4015, W2J16 =4016, W2J17=4017,
          W2J18=4018, W2J19 =4019, W2J20 =4020, W2J21 =4021, W2J22 =4022, W2J23=4023,
          W2J24=4024, W2J25 =4025, W2J26 =4026, W2J27 =4027, W2J28 =4028, W2J29=4029,
          W2J30=4030, W2J31 =4031, W2J32 =4032, W2J33 =4033, W2J34 =4034, W2J35=4035,
          W2J36=4036, W2J37 =4037, W2J38 =4038, W2J39 =4039, W2J40 =4040, W2J41=4041,
          W2J42=4042, W2J43 =4043, W2J44 =4044, W2J45 =4045, W2J46 =4046, W2J47=4047,
          W2J48=4048, W2J49 =4049, W2J50 =4050, W2J51 =4051, W2J52 =4052, W2J53=4053,
          W2J54=4054, W2J55 =4055, W2J56 =4056, W2J57 =4057, W2J58 =4058, W2J59=4059,
          W2Jsu=4100, W2Jsu1=4101, W2Jsu2=4102, W2Jsu3=4103, W2Jsu4=4104,
          W2Jsd=4200, W2Jsd1=4201, W2Jsd2=4202, W2Jsd3=4203, W2Jsd4=4204,
          W2Jmu=4300, W2Jmu1=4301, W2Jmu2=4302, W2Jmu3=4303, W2Jmu4=4304,
          W2Jmd=4400, W2Jmd1=4401, W2Jmd2=4402, W2Jmd3=4403, W2Jmd4=4404,
          W3J  =5000, W3J1  =5001, W3J2  =5002, W3J3  =5003, W3J4  =5004, W3J5 =5005, 
          W3J6 =5006, W3J7  =5007, W3J8  =5008, W3J9  =5009, W3J10 =5010, W3J11=5011, 
          W3J12=5012, W3J13 =5013, W3J14 =5014, W3J15 =5015, W3J16 =5016, W3J17=5017, 
          W3J18=5018, W3J19 =5019, W3J20 =5020, W3J21 =5021, W3J22 =5022, W3J23=5023, 
          W3J24=5024, W3J25 =5025, W3J26 =5026, W3J27 =5027, W3J28 =5028, W3J29=5029, 
          W3J30=5030, W3J31 =5031, W3J32 =5032, W3J33 =5033, W3J34 =5034, W3J35=5035, 
          W3J36=5036, W3J37 =5037, W3J38 =5038, W3J39 =5039, W3J40 =5040, W3J41=5041, 
          W3Jsu=5100, W3Jsu1=5101, W3Jsu2=5102, W3Jsu3=5103, W3Jsu4=5104, W3Jsu5=5105,
          W3Jsd=5200, W3Jsd1=5201, W3Jsd2=5202, W3Jsd3=5203, W3Jsd4=5204, W3Jsd5=5205,
          W3Jmu=5300, W3Jmu1=5301, W3Jmu2=5302, W3Jmu3=5303, W3Jmu4=5304, W3Jmu5=5305,
          W3Jmd=5400, W3Jmd1=5401, W3Jmd2=5402, W3Jmd3=5403, W3Jmd4=5404, W3Jmd5=5405,
          W4J  =6000, W4J1  =6001, W4J2  =6002, W4J3  =6003, W4J4  =6004, W4J5 =6005,
          W4J6 =6006, W4J7  =6007, W4J8  =6008, W4J9  =6009, W4J10 =6010, W4J11=6011,
          W4J12=6012, W4J13 =6013, W4J14 =6014, W4J15 =6015, W4J16 =6016, W4J17=6017,
          W4J18=6018, W4J19 =6019, W4J20 =6020, W4J21 =6021, W4J22 =6022, W4J23=6023,
          W4J24=6024, W4J25 =6025, W4J26 =6026, W4J27 =6027, W4J28 =6028, W4J29=6029,
          W4J30=6030, W4J31 =6031, W4J32 =6032, W4J33 =6033, W4J34 =6034, W4J35=6035,
          W4Jsu=6100, W4Jsu1=6101, W4Jsu2=6102, W4Jsu3=6103, W4Jsu4=6104, W4Jsu5=6105, W4Jsu6=6106,
          W4Jsd=6200, W4Jsd1=6201, W4Jsd2=6202, W4Jsd3=6203, W4Jsd4=6204, W4Jsd5=6205, W4Jsd6=6206,
          W4Jmu=6300, W4Jmu1=6301, W4Jmu2=6302, W4Jmu3=6303, W4Jmu4=6304, W4Jmu5=6305, W4Jmu6=6306,
          W4Jmd=6400, W4Jmd1=6401, W4Jmd2=6402, W4Jmd3=6403, W4Jmd4=6404, W4Jmd5=6405, W4Jmd6=6406,
          ZJ   =7000, ZJ1   =7001, ZJ2   =7002, ZJ3   =7003, ZJ4   =7004, ZJ5 =7005,
          ZJ6  =7006, ZJ7   =7007, ZJ8   =7008, ZJ9   =7009, ZJ10  =7010, ZJ11=7011,
          ZJ12 =7012, ZJ13  =7013, ZJ14  =7014, ZJ15  =7015, ZJ16  =7016, ZJ17=7017,
          ZJ18 =7018, ZJ19  =7019, ZJ20  =7020, ZJ21  =7021, ZJ22  =7022, ZJ23=7023,
          ZJ24 =7024, ZJ25  =7025, ZJ26  =7026, ZJ27  =7027, ZJ28  =7028, ZJ29=7029,
          ZJ30 =7030, ZJ31  =7031, ZJ32  =7032, ZJ33  =7033, ZJ34  =7034, ZJ35=7035,
          ZJ36 =7036, ZJ37  =7037, ZJ38  =7038, ZJ39  =7039, ZJ40  =7040, ZJ41=7041,
          ZJ42 =7042, ZJ43  =7043, ZJ44  =7044, ZJ45  =7045, ZJ46  =7046, ZJ47=7047,
          ZJ48 =7048, ZJ49  =7049, ZJ50  =7050, ZJ51  =7051, ZJ52  =7052, ZJ53=7053,
          ZJsu =7100, ZJsd  =7200, ZJmu  =7300, ZJmd  =7400,
          ZN   =8000, ZN1   =8001, ZN2   =8002, ZN3   =8003, ZN4   =8004,
          WW   =9000, WW1   =9001, WW2   =9002, WW3   =9003, WW4   =9004, WW5   =9005,
          WZ  =10000, WZ1  =10001, WZ2  =10002, WZ3  =10003, WZ4  =10004, WZ5  =10005,
          ZZ  =11000, ZZ1  =11001, ZZ2  =11002, ZZ3  =11003, ZZ4  =11004, ZZ5  =11005,
          T   =12000, T1   =12001, T2   =12002, T3   =12003, T4   =12004, T5   =12005, T6   =12006, T7   =12007, T8   =12008, T9   =12009,
          T10 =12010, T11  =12011, T12  =12012, T13  =12013, T14  =12014, T15  =12015, T16  =12016, T17  =12017, T18  =12018, T19  =12019,
          T20 =12020, T21  =12021, T22  =12022, T23  =12023, T24  =12024, T25  =12025, T26  =12026, T27  =12027, T28  =12028, T29  =12029,
          QCD_50_80  =13000, QCD_80_120 =14000, QCD_120_170 =15000, QCD_170_300  =16000, QCD_300_470=17000,
          QCD_470_600=18000, QCD_600_800=19000, QCD_800_1000=20000, QCD_1000_1400=21000, QCD_1400_1800=22000,
          signals=100000,
          s3m0=130000, s3m50=130050, s3m100=130100, s3m150=130150, s3m200=130200, s3m300=130300, s3m400=130400, s3m500=130500, s3m600=130600,
          s4m0=140000, s4m50=140050, s4m100=140100, s4m150=140150, s4m200=140200, s4m300=140300, s4m400=140400, s4m500=140500, s4m600=140600,
          s4m700=140700, s4m800=140800, s4m900=140900, s4m1000=141000,
          Signals=200000,
          S3m0=230000, S3m50=230050, S3m100=230100, S3m150=230150, S3m200=230200, S3m300=230300, S3m400=230400, S3m500=230500, S3m600=230600,
          S4m0=240000, S4m50=240050, S4m100=240100, S4m150=240150, S4m200=240200, S4m300=240300, S4m400=240400, S4m500=240500, S4m600=240600,
          S4m700=240700, S4m800=240800, S4m900=240900, S4m1000=241000,
          NUMBER_OF_TYPES};

    map<string,int> dataNames;
    dataNames[""]  =NONE;
    dataNames["A"] =A;  dataNames["A1"]=A1; dataNames["A2"]=A2; dataNames["A3"]=A3; dataNames["A4"]=A4;
    dataNames["A5"]=A5; dataNames["A6"]=A6; dataNames["A7"]=A7; dataNames["A8"]=A8; dataNames["A9"]=A9;

    dataNames["B"]  =B;   dataNames["B1"] =B1;  dataNames["B2"] =B2;  dataNames["B3"] =B3;  dataNames["B4"] =B4;
    dataNames["B5"] =B5;  dataNames["B6"] =B6;  dataNames["B7"] =B7;  dataNames["B8"] =B8;  dataNames["B9"] =B9;
    dataNames["B10"]=B10; dataNames["B11"]=B11; dataNames["B12"]=B12; dataNames["B13"]=B13; dataNames["B14"]=B14;
    dataNames["B15"]=B15; dataNames["B16"]=B16; dataNames["B17"]=B17; dataNames["B18"]=B18; dataNames["B19"]=B19;
    dataNames["B20"]=B20; dataNames["B21"]=B21;

    dataNames["C"]  =C;   dataNames["C1"] =C1;  dataNames["C2"] =C2;  dataNames["C3"] =C3;  dataNames["C4"] =C4;
    dataNames["C5"] =C5;  dataNames["C6"] =C6;  dataNames["C7"] =C7;  dataNames["C8"] =C8;  dataNames["C9"] =C9;
    dataNames["C10"]=C10; dataNames["C11"]=C11; dataNames["C12"]=C12; dataNames["C13"]=C13; dataNames["C14"]=C14;
    dataNames["C15"]=C15; dataNames["C16"]=C16; dataNames["C17"]=C17; dataNames["C18"]=C18; dataNames["C19"]=C19;
    dataNames["C20"]=C20; dataNames["C21"]=C21; dataNames["C22"]=C22; dataNames["C23"]=C23; dataNames["C24"]=C24;
    dataNames["C25"]=C25; dataNames["C26"]=C26; dataNames["C27"]=C27; dataNames["C28"]=C28; dataNames["C29"]=C29;
    dataNames["C30"]=C30; dataNames["C31"]=C31; dataNames["C32"]=C32; dataNames["C33"]=C33; dataNames["C34"]=C34;
    dataNames["C35"]=C35; dataNames["C36"]=C36; dataNames["C37"]=C37; dataNames["C38"]=C38; dataNames["C39"]=C39;
    dataNames["C40"]=C40;

    dataNames["D"]  =D;   dataNames["D1"] =D1;  dataNames["D2"] =D2;  dataNames["D3"] =D3;  dataNames["D4"] =D4;
    dataNames["D5"] =D5;  dataNames["D6"] =D6;  dataNames["D7"] =D7;  dataNames["D8"] =D8;  dataNames["D9"] =D9;
    dataNames["D10"]=D10; dataNames["D11"]=D11; dataNames["D12"]=D12; dataNames["D13"]=D13; dataNames["D14"]=D14;
    dataNames["D15"]=D15; dataNames["D16"]=D16; dataNames["D17"]=D17; dataNames["D18"]=D18; dataNames["D19"]=D19;
    dataNames["D20"]=D20; dataNames["D21"]=D21; dataNames["D22"]=D22; dataNames["D23"]=D23; dataNames["D24"]=D24;
    dataNames["D25"]=D25; dataNames["D26"]=D26; dataNames["D27"]=D27; dataNames["D28"]=D28; dataNames["D29"]=D29;
    dataNames["D30"]=D30; dataNames["D31"]=D31; dataNames["D32"]=D32; dataNames["D33"]=D33; dataNames["D34"]=D34;
    dataNames["D35"]=D35; dataNames["D36"]=D36; dataNames["D37"]=D37;

    dataNames["TT"]  =TT;  dataNames["TT1"]=TT1; dataNames["TT2"]=TT2; dataNames["TT3"]=TT3; dataNames["TT4"]=TT4;
    dataNames["TT5"] =TT5; dataNames["TT6"]=TT6; dataNames["TT7"]=TT7; dataNames["TT8"]=TT8; dataNames["TT9"]=TT9;
    dataNames["TT10"]=TT10;dataNames["TT11"]=TT11;dataNames["TT12"]=TT12; dataNames["TT13"]=TT13;

    dataNames["TTll"] =TTll;  dataNames["TTll1"]=TTll1; dataNames["TTll2"]=TTll2; dataNames["TTll3"]=TTll3; dataNames["TTll4"]=TTll4;
    dataNames["TTll5"]=TTll5; dataNames["TTll6"]=TTll6; dataNames["TTll7"]=TTll7; dataNames["TTll8"]=TTll8; dataNames["TTll9"]=TTll9;
    dataNames["TThh"] =TThh;  dataNames["TThh1"]=TThh1; dataNames["TThh2"]=TThh2; dataNames["TThh3"]=TThh3; dataNames["TThh4"]=TThh4;
    dataNames["TThh5"]=TThh5; dataNames["TThh6"]=TThh6; dataNames["TThh7"]=TThh7; dataNames["TThh8"]=TThh8; dataNames["TThh9"]=TThh9;
    dataNames["TTlh"] =TTlh;  dataNames["TTlh1"]=TTlh1; dataNames["TTlh2"]=TTlh2; dataNames["TTlh3"]=TTlh3; dataNames["TTlh4"]=TTlh4;
    dataNames["TTlh5"]=TTlh5; dataNames["TTlh6"]=TTlh6; dataNames["TTlh7"]=TTlh7; dataNames["TTlh8"]=TTlh8; dataNames["TTlh9"]=TTlh9;
    dataNames["TThh"]=TThh; dataNames["TTlh"]=TTlh; dataNames["TTll2"]=TTll2;
    dataNames["TTsu"] =TTsu;  dataNames["TTsd"] =TTsd;  dataNames["TTmu"] =TTmu;  dataNames["TTmd"] =TTmd;
    dataNames["TTsu1"]=TTsu1; dataNames["TTsd1"]=TTsd1; dataNames["TTmu1"]=TTmu1; dataNames["TTmd1"]=TTmd1;
    dataNames["TTsu2"]=TTsu2; dataNames["TTsd2"]=TTsd2; dataNames["TTmu2"]=TTmu2; dataNames["TTmd2"]=TTmd2;
    dataNames["TTsu3"]=TTsu3; dataNames["TTsd3"]=TTsd3; dataNames["TTmu3"]=TTmu3; dataNames["TTmd3"]=TTmd3;
    dataNames["TTsu4"]=TTsu4; dataNames["TTsd4"]=TTsd4; dataNames["TTmu4"]=TTmu4; dataNames["TTmd4"]=TTmd4;
    dataNames["TTsu5"]=TTsu5; dataNames["TTsd5"]=TTsd5; dataNames["TTmu5"]=TTmu5; dataNames["TTmd5"]=TTmd5;

    dataNames["WJ"]  =WJ;   dataNames["WJ1"] =WJ1;  dataNames["WJ2"] =WJ2;  dataNames["WJ3"] =WJ3;
    dataNames["WJ4"] =WJ4;  dataNames["WJ5"] =WJ5;  dataNames["WJ6"] =WJ6;  dataNames["WJ7"] =WJ7;
    dataNames["WJ8"] =WJ8;  dataNames["WJ9"] =WJ9;  dataNames["WJ10"]=WJ10; dataNames["WJ11"]=WJ11;
    dataNames["WJ12"]=WJ12; dataNames["WJ13"]=WJ13; dataNames["WJ14"]=WJ14; dataNames["WJ15"]=WJ15;
    dataNames["WJ16"]=WJ16; dataNames["WJ17"]=WJ17; dataNames["WJ18"]=WJ18; dataNames["WJ19"]=WJ19;
    dataNames["WJ20"]=WJ20; dataNames["WJ21"]=WJ21; dataNames["WJ22"]=WJ22; dataNames["WJ23"]=WJ23;
    dataNames["WJ24"]=WJ24; dataNames["WJ25"]=WJ25; dataNames["WJ26"]=WJ26; dataNames["WJ27"]=WJ27;
    dataNames["WJ28"]=WJ28; dataNames["WJ29"]=WJ29; dataNames["WJ30"]=WJ30; dataNames["WJ31"]=WJ31;
    dataNames["WJsu"]=WJsu; dataNames["WJsd"]=WJsd; dataNames["WJmu"]=WJmu; dataNames["WJmd"]=WJmd;

    dataNames["W1J"]  =W1J;   dataNames["W1J1"] =W1J1;  dataNames["W1J2"] =W1J2;  dataNames["W1J3"] =W1J3;  dataNames["W1J4"] =W1J4;  dataNames["W1J5"] =W1J5;
    dataNames["W1J6"] =W1J6;  dataNames["W1J7"] =W1J7;  dataNames["W1J8"] =W1J8;  dataNames["W1J9"] =W1J9;  dataNames["W1J10"]=W1J10; dataNames["W1J11"]=W1J11;
    dataNames["W1J12"]=W1J12; dataNames["W1J13"]=W1J13; dataNames["W1J14"]=W1J14; dataNames["W1J15"]=W1J15; dataNames["W1J16"]=W1J16; dataNames["W1J17"]=W1J17;
    dataNames["W1J18"]=W1J18; dataNames["W1J19"]=W1J19; dataNames["W1J20"]=W1J20; dataNames["W1J21"]=W1J21; dataNames["W1J22"]=W1J22; dataNames["W1J23"]=W1J23;
    dataNames["W1J24"]=W1J24; dataNames["W1J25"]=W1J25; dataNames["W1J26"]=W1J26; dataNames["W1J27"]=W1J27; dataNames["W1J28"]=W1J28; dataNames["W1J29"]=W1J29;
    dataNames["W1J30"]=W1J30; dataNames["W1J31"]=W1J31; dataNames["W1J32"]=W1J32; dataNames["W1J33"]=W1J33; dataNames["W1J34"]=W1J34; dataNames["W1J35"]=W1J35;
    dataNames["W1J36"]=W1J36; dataNames["W1J37"]=W1J37; dataNames["W1J38"]=W1J38; dataNames["W1J39"]=W1J39; dataNames["W1J40"]=W1J40; dataNames["W1J41"]=W1J41;
    dataNames["W1Jsu"]=W1Jsu; dataNames["W1Jsu1"]=W1Jsu1; dataNames["W1Jsu2"]=W1Jsu2; dataNames["W1Jsu3"]=W1Jsu3; dataNames["W1Jsu4"]=W1Jsu4;
    dataNames["W1Jsd"]=W1Jsd; dataNames["W1Jsd1"]=W1Jsd1; dataNames["W1Jsd2"]=W1Jsd2; dataNames["W1Jsd3"]=W1Jsd3; dataNames["W1Jsd4"]=W1Jsd4;
    dataNames["W1Jmu"]=W1Jmu; dataNames["W1Jmu1"]=W1Jmu1; dataNames["W1Jmu2"]=W1Jmu2; dataNames["W1Jmu3"]=W1Jmu3; dataNames["W1Jmu4"]=W1Jmu4;
    dataNames["W1Jmd"]=W1Jmd; dataNames["W1Jmd1"]=W1Jmd1; dataNames["W1Jmd2"]=W1Jmd2; dataNames["W1Jmd3"]=W1Jmd3; dataNames["W1Jmd4"]=W1Jmd4;

    dataNames["W2J"]  =W2J;   dataNames["W2J1"] =W2J1;  dataNames["W2J2"] =W2J2;  dataNames["W2J3"] =W2J3;  dataNames["W2J4"] =W2J4;  dataNames["W2J5"] =W2J5;
    dataNames["W2J6"] =W2J6;  dataNames["W2J7"] =W2J7;  dataNames["W2J8"] =W2J8;  dataNames["W2J9"] =W2J9;  dataNames["W2J10"]=W2J10; dataNames["W2J11"]=W2J11;
    dataNames["W2J12"]=W2J12; dataNames["W2J13"]=W2J13; dataNames["W2J14"]=W2J14; dataNames["W2J15"]=W2J15; dataNames["W2J16"]=W2J16; dataNames["W2J17"]=W2J17;
    dataNames["W2J18"]=W2J18; dataNames["W2J19"]=W2J19; dataNames["W2J20"]=W2J20; dataNames["W2J21"]=W2J21; dataNames["W2J22"]=W2J22; dataNames["W2J23"]=W2J23;
    dataNames["W2J24"]=W2J24; dataNames["W2J25"]=W2J25; dataNames["W2J26"]=W2J26; dataNames["W2J27"]=W2J27; dataNames["W2J28"]=W2J28; dataNames["W2J29"]=W2J29;
    dataNames["W2J30"]=W2J30; dataNames["W2J31"]=W2J31; dataNames["W2J32"]=W2J32; dataNames["W2J33"]=W2J33; dataNames["W2J34"]=W2J34; dataNames["W2J35"]=W2J35;
    dataNames["W2J36"]=W2J36; dataNames["W2J37"]=W2J37; dataNames["W2J38"]=W2J38; dataNames["W2J39"]=W2J39; dataNames["W2J40"]=W2J40; dataNames["W2J41"]=W2J41;
    dataNames["W2J42"]=W2J42; dataNames["W2J43"]=W2J43; dataNames["W2J44"]=W2J44; dataNames["W2J45"]=W2J45; dataNames["W2J46"]=W2J46; dataNames["W2J47"]=W2J47;
    dataNames["W2J48"]=W2J48; dataNames["W2J49"]=W2J49; dataNames["W2J50"]=W2J50; dataNames["W2J51"]=W2J51; dataNames["W2J52"]=W2J52; dataNames["W2J53"]=W2J53;
    dataNames["W2J54"]=W2J54; dataNames["W2J55"]=W2J55; dataNames["W2J56"]=W2J56; dataNames["W2J57"]=W2J57; dataNames["W2J58"]=W2J58; dataNames["W2J59"]=W2J59;
    dataNames["W2Jsu"]=W2Jsu; dataNames["W2Jsu1"]=W2Jsu1; dataNames["W2Jsu2"]=W2Jsu2; dataNames["W2Jsu3"]=W2Jsu3; dataNames["W2Jsu4"]=W2Jsu4;
    dataNames["W2Jsd"]=W2Jsd; dataNames["W2Jsd1"]=W2Jsd1; dataNames["W2Jsd2"]=W2Jsd2; dataNames["W2Jsd3"]=W2Jsd3; dataNames["W2Jsd4"]=W2Jsd4;
    dataNames["W2Jmu"]=W2Jmu; dataNames["W2Jmu1"]=W2Jmu1; dataNames["W2Jmu2"]=W2Jmu2; dataNames["W2Jmu3"]=W2Jmu3; dataNames["W2Jmu4"]=W2Jmu4;
    dataNames["W2Jmd"]=W2Jmd; dataNames["W2Jmd1"]=W2Jmd1; dataNames["W2Jmd2"]=W2Jmd2; dataNames["W2Jmd3"]=W2Jmd3; dataNames["W2Jmd4"]=W2Jmd4;

    dataNames["W3J"]  =W3J;   dataNames["W3J1"] =W3J1;  dataNames["W3J2"] =W3J2;  dataNames["W3J3"] =W3J3;  dataNames["W3J4"] =W3J4;  dataNames["W3J5"] =W3J5;
    dataNames["W3J6"] =W3J6;  dataNames["W3J7"] =W3J7;  dataNames["W3J8"] =W3J8;  dataNames["W3J9"] =W3J9;  dataNames["W3J10"]=W3J10; dataNames["W3J11"]=W3J11;
    dataNames["W3J12"]=W3J12; dataNames["W3J13"]=W3J13; dataNames["W3J14"]=W3J14; dataNames["W3J15"]=W3J15; dataNames["W3J16"]=W3J16; dataNames["W3J17"]=W3J17;
    dataNames["W3J18"]=W3J18; dataNames["W3J19"]=W3J19; dataNames["W3J20"]=W3J20; dataNames["W3J21"]=W3J21; dataNames["W3J22"]=W3J22; dataNames["W3J23"]=W3J23;
    dataNames["W3J24"]=W3J24; dataNames["W3J25"]=W3J25; dataNames["W3J26"]=W3J26; dataNames["W3J27"]=W3J27; dataNames["W3J28"]=W3J28; dataNames["W3J29"]=W3J29;
    dataNames["W3J30"]=W3J30; dataNames["W3J31"]=W3J31; dataNames["W3J32"]=W3J32; dataNames["W3J33"]=W3J33; dataNames["W3J34"]=W3J34; dataNames["W3J35"]=W3J35;
    dataNames["W3J36"]=W3J36; dataNames["W3J37"]=W3J37; dataNames["W3J38"]=W3J38; dataNames["W3J39"]=W3J39; dataNames["W3J40"]=W3J40; dataNames["W3J41"]=W3J41;
    dataNames["W3Jsu"]=W3Jsu; dataNames["W3Jsu1"]=W3Jsu1; dataNames["W3Jsu2"]=W3Jsu2; dataNames["W3Jsu3"]=W3Jsu3; dataNames["W3Jsu4"]=W3Jsu4; dataNames["W3Jsu5"]=W3Jsu5;
    dataNames["W3Jsd"]=W3Jsd; dataNames["W3Jsd1"]=W3Jsd1; dataNames["W3Jsd2"]=W3Jsd2; dataNames["W3Jsd3"]=W3Jsd3; dataNames["W3Jsd4"]=W3Jsd4; dataNames["W3Jsd5"]=W3Jsd5;
    dataNames["W3Jmu"]=W3Jmu; dataNames["W3Jmu1"]=W3Jmu1; dataNames["W3Jmu2"]=W3Jmu2; dataNames["W3Jmu3"]=W3Jmu3; dataNames["W3Jmu4"]=W3Jmu4; dataNames["W3Jmu5"]=W3Jmu5;
    dataNames["W3Jmd"]=W3Jmd; dataNames["W3Jmd1"]=W3Jmd1; dataNames["W3Jmd2"]=W3Jmd2; dataNames["W3Jmd3"]=W3Jmd3; dataNames["W3Jmd4"]=W3Jmd4; dataNames["W3Jmd5"]=W3Jmd5;

    dataNames["W4J"]  =W4J;   dataNames["W4J1"] =W4J1;  dataNames["W4J2"] =W4J2;  dataNames["W4J3"] =W4J3;  dataNames["W4J4"] =W4J4;  dataNames["W4J5"] =W4J5;
    dataNames["W4J6"] =W4J6;  dataNames["W4J7"] =W4J7;  dataNames["W4J8"] =W4J8;  dataNames["W4J9"] =W4J9;  dataNames["W4J10"]=W4J10; dataNames["W4J11"]=W4J11;
    dataNames["W4J12"]=W4J12; dataNames["W4J13"]=W4J13; dataNames["W4J14"]=W4J14; dataNames["W4J15"]=W4J15; dataNames["W4J16"]=W4J16; dataNames["W4J17"]=W4J17;
    dataNames["W4J18"]=W4J18; dataNames["W4J19"]=W4J19; dataNames["W4J20"]=W4J20; dataNames["W4J21"]=W4J21; dataNames["W4J22"]=W4J22; dataNames["W4J23"]=W4J23;
    dataNames["W4Jsu"]=W4Jsu; dataNames["W4Jsu1"]=W4Jsu1; dataNames["W4Jsu2"]=W4Jsu2; dataNames["W4Jsu3"]=W4Jsu3; dataNames["W4Jsu4"]=W4Jsu4; dataNames["W4Jsu5"]=W4Jsu5; dataNames["W4Jsu6"]=W4Jsu6;
    dataNames["W4Jsd"]=W4Jsd; dataNames["W4Jsd1"]=W4Jsd1; dataNames["W4Jsd2"]=W4Jsd2; dataNames["W4Jsd3"]=W4Jsd3; dataNames["W4Jsd4"]=W4Jsd4; dataNames["W4Jsd5"]=W4Jsd5; dataNames["W4Jsd6"]=W4Jsd6;
    dataNames["W4Jmu"]=W4Jmu; dataNames["W4Jmu1"]=W4Jmu1; dataNames["W4Jmu2"]=W4Jmu2; dataNames["W4Jmu3"]=W4Jmu3; dataNames["W4Jmu4"]=W4Jmu4; dataNames["W4Jmu5"]=W4Jmu5; dataNames["W4Jmu6"]=W4Jmu6;
    dataNames["W4Jmd"]=W4Jmd; dataNames["W4Jmd1"]=W4Jmd1; dataNames["W4Jmd2"]=W4Jmd2; dataNames["W4Jmd3"]=W4Jmd3; dataNames["W4Jmd4"]=W4Jmd4; dataNames["W4Jmd5"]=W4Jmd5; dataNames["W4Jmd6"]=W4Jmd6;

    dataNames["ZJ"]  =ZJ;   dataNames["ZJ1"] =ZJ1;  dataNames["ZJ2"] =ZJ2;  dataNames["ZJ3"] =ZJ3;  dataNames["ZJ4"] =ZJ4;  dataNames["ZJ5"] =ZJ5;
    dataNames["ZJ6"] =ZJ6;  dataNames["ZJ7"] =ZJ7;  dataNames["ZJ8"] =ZJ8;  dataNames["ZJ9"] =ZJ9;  dataNames["ZJ10"]=ZJ10; dataNames["ZJ11"]=ZJ11;
    dataNames["ZJ12"]=ZJ12; dataNames["ZJ13"]=ZJ13; dataNames["ZJ14"]=ZJ14; dataNames["ZJ15"]=ZJ15; dataNames["ZJ16"]=ZJ16; dataNames["ZJ17"]=ZJ17;
    dataNames["ZJ18"]=ZJ18; dataNames["ZJ19"]=ZJ19; dataNames["ZJ20"]=ZJ20; dataNames["ZJ21"]=ZJ21; dataNames["ZJ22"]=ZJ22; dataNames["ZJ23"]=ZJ23;
    dataNames["ZJ24"]=ZJ24; dataNames["ZJ25"]=ZJ25; dataNames["ZJ26"]=ZJ26; dataNames["ZJ27"]=ZJ27; dataNames["ZJ28"]=ZJ28; dataNames["ZJ29"]=ZJ29;
    dataNames["ZJ30"]=ZJ30; dataNames["ZJ31"]=ZJ31; dataNames["ZJ32"]=ZJ32; dataNames["ZJ33"]=ZJ33; dataNames["ZJ34"]=ZJ34; dataNames["ZJ35"]=ZJ35;
    dataNames["ZJ36"]=ZJ36; dataNames["ZJ37"]=ZJ37; dataNames["ZJ38"]=ZJ38; dataNames["ZJ39"]=ZJ39; dataNames["ZJ40"]=ZJ40; dataNames["ZJ41"]=ZJ41;
    dataNames["ZJ42"]=ZJ42; dataNames["ZJ43"]=ZJ43; dataNames["ZJ44"]=ZJ44; dataNames["ZJ45"]=ZJ45; dataNames["ZJ46"]=ZJ46; dataNames["ZJ47"]=ZJ47;
    dataNames["ZJ48"]=ZJ48; dataNames["ZJ49"]=ZJ49; dataNames["ZJ50"]=ZJ50; dataNames["ZJ51"]=ZJ51; dataNames["ZJ52"]=ZJ52; dataNames["ZJ53"]=ZJ53;

    dataNames["ZJsu"]=ZJsu; dataNames["ZJsd"]=ZJsd; dataNames["ZJmu"]=ZJmu; dataNames["ZJmd"]=ZJmd; 

    dataNames["ZN"]=ZN; dataNames["ZN1"]=ZN1; dataNames["ZN2"]=ZN2; dataNames["ZN3"]=ZN3; dataNames["ZN4"]=ZN4;
 
    dataNames["WW"]=WW; dataNames["WW1"]=WW1; dataNames["WW2"]=WW2; dataNames["WW3"]=WW3; dataNames["WW4"]=WW4; dataNames["WW5"]=WW5;
    dataNames["WZ"]=WZ; dataNames["WZ1"]=WZ1; dataNames["WZ2"]=WZ2; dataNames["WZ3"]=WZ3; dataNames["WZ4"]=WZ4; dataNames["WZ5"]=WZ5;
    dataNames["ZZ"]=ZZ; dataNames["ZZ1"]=WZ1; dataNames["ZZ2"]=WZ2; dataNames["ZZ3"]=WZ3; dataNames["ZZ4"]=WZ4; dataNames["ZZ5"]=WZ5;

    dataNames["T"]  =T;   dataNames["T1"] =T1;  dataNames["T2"] =T2;  dataNames["T3"] =T3;  dataNames["T4"] =T4;
    dataNames["T5"] =T5;  dataNames["T6"] =T6;  dataNames["T7"] =T7;  dataNames["T8"] =T8;  dataNames["T9"] =T9;
    dataNames["T10"]=T10; dataNames["T11"]=T11; dataNames["T12"]=T12; dataNames["T13"]=T13; dataNames["T14"]=T14;
    dataNames["T15"]=T15; dataNames["T16"]=T16; dataNames["T17"]=T17; dataNames["T18"]=T18; dataNames["T19"]=T19;
    dataNames["T20"]=T20; dataNames["T21"]=T21; dataNames["T22"]=T22; dataNames["T23"]=T23; dataNames["T24"]=T24;
    dataNames["T25"]=T25; dataNames["T26"]=T26; dataNames["T27"]=T27; dataNames["T28"]=T28; dataNames["T29"]=T29;


    dataNames["QCD_50_80"]  =QCD_50_80;   dataNames["QCD_80_120"]  =QCD_80_120;   dataNames["QCD_120_170"]=QCD_120_170;
    dataNames["QCD_170_300"]=QCD_170_300; dataNames["QCD_300_470"] =QCD_300_470;  dataNames["QCD_470_600"]=QCD_470_600;
    dataNames["QCD_600_800"]=QCD_600_800; dataNames["QCD_800_1000"]=QCD_800_1000; dataNames["QCD_1000_1400"]=QCD_1000_1400;

    dataNames["signals"]=signals;
    dataNames["s3m0"]  =s3m0;   dataNames["s3m50"] =s3m50;  dataNames["s3m100"]=s3m100;  dataNames["s3m150"]=s3m150;
    dataNames["s3m200"]=s3m200; dataNames["s3m300"]=s3m300; dataNames["s3m400"]=s3m400;  dataNames["s3m500"]=s3m500;
    dataNames["s3m600"]=s3m600;
    dataNames["s4m0"]  =s4m0;   dataNames["s4m50"] =s4m50;  dataNames["s4m100"]=s4m100;  dataNames["s4m150"]=s4m150;
    dataNames["s4m200"]=s4m200; dataNames["s4m300"]=s4m300; dataNames["s4m400"]=s4m400;  dataNames["s4m500"]=s4m500;
    dataNames["s4m600"]=s4m600; dataNames["s4m700"]=s4m700; dataNames["s4m800"]=s4m800;  dataNames["s4m900"]=s4m900;
    dataNames["s4m1000"]=s4m1000;

    dataNames["Signals"]=Signals;
    dataNames["S3m0"]   =S3m0;  dataNames["S3m50"] =S3m50;  dataNames["S3m100"]=S3m100;  dataNames["S3m150"]=S3m150;
    dataNames["S3m200"]=S3m200; dataNames["S3m300"]=S3m300; dataNames["S3m400"]=S3m400;  dataNames["S3m500"]=S3m500;

//    dataNames["S4"]=S4;
    dataNames["S4m0"]=S4m0;     dataNames["S4m50"]=S4m50;   dataNames["S4m100"]=S4m100;  dataNames["S4m150"]=S4m150;
    dataNames["S4m200"]=S4m200; dataNames["S4m300"]=S4m300; dataNames["S4m500"]=S4m500;

    map<int, vector<const char*> > MET;//[NUMBER_OF_TYPES+1];
    map<int, vector<const char*> > sMuon;//[NUMBER_OF_TYPES+1];
    map<int, vector<const char*> > sElectron;//[NUMBER_OF_TYPES+1];
    map<int, vector<const char*> > MC;//[NUMBER_OF_TYPES+1];
#include "paths.h"

    int dataType=NONE;
    string dataName;
    Analysis::useJetResVariation(JetResVariation::NONE);
    Analysis::useBtagVariation(JetBtagVariation::NONE);

    while( 1 ){
       int index=0;
       int c = getopt_long(argc, argv, "hd:s:j:v:i:o:r:b:",options, &index);
       if( c == -1 ) break;
       switch( tolower(c) ) {
           case 'h':
              printf("Usage:\n");
              printf("-h     ,   --help              show this message\n");
              printf("-dTYPE ,   --datatype=TYPE     dataset to run on (TYPE=\n\
                A,A[1-5(e),6(mu)]\n\
                B,B[1-15(e),20(mu)],\n\
                C,C[1-24(e),34(mu)],\n\
                D,D[1-30(e),29(mu)],\n\
                T,TT[1-12],\n\
                WJ,WJ[1-29]\n\
                ZJ,ZJ[1-16],\n\
                ZN,ZN[1-4],\n\
                WW,WW[1-5],WZ,WZ[1-5],ZZ,ZZ[1-5],\n\
                W1J,W1J[1-12],\n\
                W2J,W2J[1-17],\n\
                W3J,W3J[1-8],\n\
                W4J,W4J[1-7],\n\
                TTll,TThh,TTlh,TTll2,\n\
                W3Jsu,W3Jsu1,W3Jsu2,W3Jsu3,W3Jsu4,\n\
                W3Jsd,W3Jsd1,W3Jsd2,W3Jsd3,W3Jsd4,\n\
                W4Jsu,W4Jsu1,W4Jsu2,W4Jsu3,W4Jsu4,\n\
                W4Jsd,W4Jsd1,W4Jsd2,W4Jsd3,W4Jsd4,\n\
                W3Jmu,W3Jmu1,W3Jmu2,W3Jmu3,W3Jmu4,\n\
                W3Jmd,W3Jmd1,W3Jmd2,W3Jmd3,W3Jmd4,\n\
                W4Jmu,W4Jmu1,W4Jmu2,W4Jmu3,W4Jmu4,\n\
                W4Jmd,W4Jmd1,W4Jmd2,W4Jmd3,W4Jmd4)\n\
                signals,\n\
                s3,s3m0,s3m50,s3m100,s3m150,s3m200,s3m300,s3m500,\n\
                s4,s4m0,s4m50,s4m100,s4m150,s4m200,s4m300,s4m500,\n\
                WJsu,WJsd,WJmu,WJmd,ZJsu,ZJsd,ZJmu,ZJmd,TTsu,TTsd,TTmu,TTmd,\n\
                Signals,\n\
                S3,S3m0,S3m50,S3m100,S3m150,S3m200,S3m300,S3m500,\n\
                S4,S4m0,S4m50,S4m100,S4m150,S4m200,S4m300,S4m500,\n");
              printf("-sS    ,   --selection=S       run with selection S ('d' - MET/default, 'm' - muon, 'e' - electron)\n");
              printf("-jV    ,   --jecVariation=V    vaiation V of jet energy correction ('n' - none/default 'p' - plus, 'm' - minus)\n");
              printf("-iPATH ,   --input=PATH        alternative to the -d option - path with input ntuples\n");
              printf("-oPATH ,   --output=PATH       store output in PATH directory\n");
              printf("-rV    ,   --resVariation=V    varying jet resolution ('n' - none/default 'p' - plus, 'm' - minus)\n");
              printf("-bV    ,   --bTagVariation=V   varying b-tag/mistag rate ('n' - none/default 'p' - plus, 'm' - minus)\n");
              return 0;
           break;
           case 'd': {
                     std::map<string,int>::const_iterator tp = dataNames.find(optarg);
                     if( tp != dataNames.end() ){
                        dataType = tp->second;
                        dataName = tp->first;
                     }
                  switch( dataType ){
                     case WJsu: variation = EventWeightProvider::scaleUp;      break;
                     case WJsd: variation = EventWeightProvider::scaleDown;    break;
                     case WJmu: variation = EventWeightProvider::matchingUp;   break;
                     case WJmd: variation = EventWeightProvider::matchingDown; break;
                     case ZJsu: variation = EventWeightProvider::scaleUp;      break;
                     case ZJsd: variation = EventWeightProvider::scaleDown;    break;
                     case ZJmu: variation = EventWeightProvider::matchingUp;   break;
                     case ZJmd: variation = EventWeightProvider::matchingDown; break;
                     case TTsu: variation = EventWeightProvider::scaleUp;      break;
                     case TTsd: variation = EventWeightProvider::scaleDown;    break;
                     case TTmu: variation = EventWeightProvider::matchingUp;   break;
                     case TTmd: variation = EventWeightProvider::matchingDown; break;
                     case TTsu1: variation = EventWeightProvider::scaleUp;      break;
                     case TTsd1: variation = EventWeightProvider::scaleDown;    break;
                     case TTmu1: variation = EventWeightProvider::matchingUp;   break;
                     case TTmd1: variation = EventWeightProvider::matchingDown; break;
                     case TTsu2: variation = EventWeightProvider::scaleUp;      break;
                     case TTsd2: variation = EventWeightProvider::scaleDown;    break;
                     case TTmu2: variation = EventWeightProvider::matchingUp;   break;
                     case TTmd2: variation = EventWeightProvider::matchingDown; break;
                     case TTsu3: variation = EventWeightProvider::scaleUp;      break;
                     case TTsd3: variation = EventWeightProvider::scaleDown;    break;
                     case TTmu3: variation = EventWeightProvider::matchingUp;   break;
                     case TTmd3: variation = EventWeightProvider::matchingDown; break;
                     case TTsu4: variation = EventWeightProvider::scaleUp;      break;
                     case TTsd4: variation = EventWeightProvider::scaleDown;    break;
                     case TTmu4: variation = EventWeightProvider::matchingUp;   break;
                     case TTmd4: variation = EventWeightProvider::matchingDown; break;
                     case TTsu5: variation = EventWeightProvider::scaleUp;      break;
                     case TTsd5: variation = EventWeightProvider::scaleDown;    break;
                     case TTmu5: variation = EventWeightProvider::matchingUp;   break;
                     case TTmd5: variation = EventWeightProvider::matchingDown; break;
                     case W3Jsu:variation = EventWeightProvider::scaleUp;      break;
                     case W3Jsd:variation = EventWeightProvider::scaleDown;    break;
                     case W4Jsu:variation = EventWeightProvider::scaleUp;      break;
                     case W4Jsd:variation = EventWeightProvider::scaleDown;    break;
                     case W3Jmu:variation = EventWeightProvider::matchingUp;   break;
                     case W3Jmd:variation = EventWeightProvider::matchingDown; break;
                     case W4Jmu:variation = EventWeightProvider::matchingUp;   break;
                     case W4Jmd:variation = EventWeightProvider::matchingDown; break;
                     default  : variation = EventWeightProvider::central;      break;
                  }
                  }
           break;
           case 's':
              switch( optarg[0] ){
                  case 'd': monotopSelection = monotopMetSelection;      break;
                  case 'm': monotopSelection = monotopMuonSelection;     break;
                  case 'e': monotopSelection = monotopElectronSelection; break;
                  default: printf("Type -h for help\n"); return 0;
              }
           break;
           case 'j':
              switch( optarg[0] ){
                  case 'n': Jet::correctDirection = JetCorrDirection::NONE;  break;
                  case 'p': Jet::correctDirection = JetCorrDirection::PLUS;  break;
                  case 'm': Jet::correctDirection = JetCorrDirection::MINUS; break;
                  default: printf("Type -h for help\n"); return 0;
              }
           break;
           case 'i': inputDirectory  = optarg; break;
           case 'o': outputDirectory = optarg; break;
           case 'r':
              switch( optarg[0] ){
                  case 'n': Analysis::useJetResVariation(JetResVariation::NONE); break;
                  case 'p': Analysis::useJetResVariation(JetResVariation::PLUS); break;
                  case 'm': Analysis::useJetResVariation(JetResVariation::MINUS); break;
                  default: printf("Type -h for help\n"); return 0;
              }
           break;
           case 'b':
              switch( optarg[0] ){
                  case 'n': Analysis::useBtagVariation(JetBtagVariation::NONE); break;
                  case 'p': Analysis::useBtagVariation(JetBtagVariation::PLUS); break;
                  case 'm': Analysis::useBtagVariation(JetBtagVariation::MINUS); break;
                  default: printf("Type -h for help\n"); return 0;
              }
           break;
           default : printf("Type -h for help\n"); return 0;
       }
    }

    if( dataType==NONE && inputDirectory==0 ){ printf("Missed input, type -h for help\n"); return 0; }
    if( dataType!=NONE && inputDirectory!=0 ){ printf("Ambiguous input, type -h for help\n"); return 0; }
//    if( monotopSelection == monotopElectronSelection ) { printf("Electron selection is dismissed\n"); return 0; }

    map<int, vector<const char*> > *BEANtuples = 0;
    if( dataType<TT // first MC sample
    ){
             if( monotopSelection == monotopMetSelection      ) BEANtuples = &MET;
             if( monotopSelection == monotopMuonSelection     ) BEANtuples = &sMuon;
             if( monotopSelection == monotopElectronSelection ) BEANtuples = &sElectron;
    } else BEANtuples = &MC;

    setUpOnce();
    TStopwatch watch;
    watch.Start();

    Analysis::useJetAlgorithm(JetAlgorithm::PF2PAT);
    Analysis::useElectronIDMethod(eIDMethod::MVA);
    Analysis::useElectronAlgorithm(ElectronAlgorithm::ParticleFlow);
    // Analysis::useElectronAlgorithm(ElectronAlgorithm::Calo);

    Analysis::useMuonAlgorithm(MuonAlgorithm::ParticleFlow);
    // Analysis::useMuonAlgorithm(MuonAlgorithm::Default);

    //Analysis::useMETAlgorithm(METAlgorithm::PFMETType1);
    Analysis::useMETAlgorithm(METAlgorithm::ParticleFlowMET);
    Analysis::luminosity = 5000.; //luminosity();
    cout<<"Luminosity: "<<Analysis::luminosity<<" pb"<<endl;

    EventWeightProvider::truePUdistfile = "pileup_JSON_PromptReco_190456-208686.root";

    Analysis::useCustomConversionTagger(false);
    Analysis::usePFIsolation(true);
    // Analysis::usePFIsolation(false);	// For Calo electrons

//    if( variation == EventWeightProvider::central && Jet::correctDirection == JetCorrDirection::NONE && dataType>D8 )
//       Analysis::useLHAPDF(true);
//    else
       Analysis::useLHAPDF(false);

    std::vector<ToplikeSelectionSteps::Step> selection(0);
    for(unsigned int step=0; step<monotopSelectionSize; step++)
       selection.push_back( monotopSelection[step] );

    myAnalysis = new Analysis(selection,variation);
 
    string outputFileName(outputDirectory);
    outputFileName.append("micro_");

    cout << "Starting to read ntuples\n";

    if( dataType!=NONE ){

       for(vector<const char*>::const_iterator tuple = (*BEANtuples)[dataType].begin(); tuple != (*BEANtuples)[dataType].end(); tuple++)
          myAnalysis->addInputFile(*tuple);

       if( dataType<TT ){
          if( monotopSelection == monotopMetSelection  ) outputFileName.append("MET2012");
          if( monotopSelection == monotopMuonSelection ) outputFileName.append("SingleMu2012");
          if( monotopSelection == monotopElectronSelection ) outputFileName.append("SingleElectron2012");
       }
       outputFileName.append( dataName );

    } else {
          string ntuples(inputDirectory);
          ntuples.append("/*.root");
          myAnalysis->addInputFile(ntuples.c_str());

          string sampleName(inputDirectory);
          size_t length = sampleName.length();
          size_t startPos = sampleName.rfind('/');
          if( startPos != string::npos ){ // found a '/' symbol
             if( startPos+1 == length ){ // it is a trailing '/' symbol(s)
               // remove all trailing '/' symbols w/o using regular expressions
               for(size_t previous = startPos;
                   startPos != 0 && startPos != string::npos && (previous-startPos) <= 1;
                   previous = startPos, startPos = sampleName.rfind('/',startPos-1) )
                   sampleName.resize(startPos);
             }
          }

          if( startPos == string::npos )
             outputFileName.append(sampleName);
          else
             outputFileName.append(sampleName.substr(startPos+1));
    }

    if( monotopSelection == monotopMetSelection      ) outputFileName.append("_metSel");
    if( monotopSelection == monotopMuonSelection     ) outputFileName.append("_muSel");
    if( monotopSelection == monotopElectronSelection ) outputFileName.append("_eSel");
    switch( Jet::correctDirection ){
       case JetCorrDirection::NONE:  break;
       case JetCorrDirection::PLUS:  outputFileName.append("_jecUp");   break;
       case JetCorrDirection::MINUS: outputFileName.append("_jecDown"); break;
       default: cout<<"unknown jec variation"<<endl; return 0; break;
    }
    outputFileName.append(".root");

    cout << "starting analysis" << endl;
    myAnalysis->analyze(outputFileName.c_str());

    delete myAnalysis;

    watch.Stop();
    watch.Print();

    return 0;
}
