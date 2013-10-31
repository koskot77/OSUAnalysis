#include "../interface/DupEvtChk.h"

DupEvtChk::DupEvtChk ()
{
}


DupEvtChk::~DupEvtChk ()
{
}


bool DupEvtChk::IsDuplicate(unsigned int run, unsigned long event)
{
  static std::pair<unsigned int, unsigned long> pair;
  pair = std::pair<unsigned int, unsigned long>(run, event);
  if (fSet.count(pair)) {
    return true;
  }

  fSet.insert(pair);
  return false;
}




