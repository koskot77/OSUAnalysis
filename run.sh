#!/bin/bash

echo "Initializing the environment..."
cd /home/kkotov/CMSSW_5_3_8/src/OSUAnalysis/BEANsTools/
export VO_CMS_SW_DIR=/sharesoft/cmssw
source $VO_CMS_SW_DIR/cmsset_default.sh
source /sharesoft/osg/ce/setup.sh
eval `scram runtime -sh`
echo "Launching the job..."
root.exe -b -q "processLine.C(\"tPeakMu($1,$2,$3,$4,$5)\",\"tPeakMu_C.so\")" 2>&1 
