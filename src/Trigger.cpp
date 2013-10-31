#include "../interface/Trigger.h"
#include <iostream>
using namespace std;

namespace BAT {

Trigger::Trigger() :
    hltBits(new std::vector<int>()),
    prescales(new std::vector<int>()),
    hltName2Bit(),
    hltIndex2Bit() {}

Trigger::~Trigger() {}

void Trigger::setHLTs(const boost::shared_ptr<std::vector<int> > triggers){
    hltBits = triggers;
}

void Trigger::resynch( const boost::shared_ptr<std::vector<std::string> >  trigNames,
                       const boost::shared_ptr<std::vector<int> >          scales  ){
    prescales = scales;
    hltName2Bit.clear();
    hltIndex2Bit.clear();
    for(unsigned int bit=0; bit<trigNames->size(); bit++){
       hltName2Bit.insert(std::pair<std::string,int>(trigNames->at(bit),bit));
//std::cout<<"trigbit: "<<bit<<" trigname: "<<trigNames->at(bit)<<std::endl;
       for(unsigned int trigIndex=0; trigIndex<HLTriggers::NUMBER_OF_TRIGGERS; trigIndex++){
//std::cout<<"   check against: "<<trigIndex<<" alias: "<<HLTriggers::names.at(trigIndex)<<std::endl;
          if( trigNames->at(bit).find( HLTriggers::names.at(trigIndex) ) != std::string::npos ){
              hltIndex2Bit.insert( std::pair<HLTriggers::value,int>(HLTriggers::value(trigIndex),bit) );
//std::cout<<"     match!"<<std::endl;
          }}
    }
}

bool Trigger::isFired(const std::string& trigName) const {
    std::map<std::string,int>::const_iterator trig = hltName2Bit.find(trigName);
    if( trig == hltName2Bit.end() ) return false;
    else return hltBits->at(trig->second)>0;
}

int Trigger::prescale(const std::string& trigName) const {
    std::map<std::string,int>::const_iterator trig = hltName2Bit.find(trigName);
    if( trig == hltName2Bit.end() ) return 0;
    else return prescales->at(trig->second);
}

bool Trigger::isFired(int bit) const{
    return hltBits->at(bit)>0;
}

int Trigger::prescale(int bit) const{
    return prescales->at(bit)>0;
}

bool Trigger::isFired(HLTriggers::value trigger) const { 
//std::cout<<"Looking for: "<<trigger<<" alias: "<<HLTriggers::names.at(trigger)<<std::endl;
    std::map<HLTriggers::value,int>::const_iterator trig = hltIndex2Bit.find(trigger);
    if( trig == hltIndex2Bit.end() ) return false;
    else {
//std::cout<<"   found bit: "<<trig->second<<std::endl;
 return hltBits->at(trig->second)>0;}
}

int Trigger::prescale(HLTriggers::value trigger) const { 
    std::map<HLTriggers::value,int>::const_iterator trig = hltIndex2Bit.find(trigger);
    if( trig == hltIndex2Bit.end() ) return false;
    else return prescales->at(trig->second)>0;
}

const std::map<std::string,int>& Trigger::hltDictionary(void) const { return hltName2Bit; }
const std::map<HLTriggers::value,int>& Trigger::hltAliases(void) const { return hltIndex2Bit; }

}
