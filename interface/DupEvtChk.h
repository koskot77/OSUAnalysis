#ifndef GUARD_DupEvtChk_h
#define GUARD_DupEvtChk_h

#include <vector>
#include <set>
#include <map>
#include <algorithm>

class DupEvtChk
{
  public:
    DupEvtChk ();
    ~DupEvtChk ();

    bool IsDuplicate(unsigned int, unsigned long);

  private:
    std::set< std::pair<unsigned int, unsigned long> > fSet;
};


#endif
