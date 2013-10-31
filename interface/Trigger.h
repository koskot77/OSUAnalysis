#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "HighLevelTriggers.h"

#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace BAT {

class Trigger {
protected:
    boost::shared_ptr< std::vector<int> > hltBits;
    boost::shared_ptr< std::vector<int> > prescales;
    std::map<std::string,int>       hltName2Bit;  // dictionary: hltName2Bit ["trigName"]       = menu::bit
    std::map<HLTriggers::value,int> hltIndex2Bit; // aliases:    hltIndex2Bit[HLTriggers:value] = menu::bit

public:
    Trigger();
    virtual ~Trigger();
    void setHLTs( const boost::shared_ptr<std::vector<int> > triggers); // set for every event

    void resynch( const boost::shared_ptr<std::vector<std::string> >  trigNames, // invoked once per run 
                  const boost::shared_ptr<std::vector<int> >          scales  ); // rebuilds dictionary and aliases

    int  prescale(const std::string& trigName) const;
    int  prescale(int bit) const;
    int  prescale(HLTriggers::value trigger) const;

    bool isFired(const std::string& trigName) const;
    bool isFired(int bit) const;
    bool isFired(HLTriggers::value trigger) const;

    const std::map<std::string,int>&       hltDictionary(void) const; // name -> bit association
    const std::map<HLTriggers::value,int>& hltAliases(void) const;    // local index from HighLevelTriggers.h -> bit
};

}

#endif /* TRIGGER_H_ */
