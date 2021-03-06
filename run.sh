#!/bin/bash

echo "Initializing the environment..."
cd /home/kkotov/CMSSW_5_3_8/src/OSUAnalysis/BEANsTools/
export VO_CMS_SW_DIR=/sharesoft/cmssw
source $VO_CMS_SW_DIR/cmsset_default.sh
source /sharesoft/osg/ce/setup.sh
eval `scram runtime -sh`
export PATH=`echo $PATH | sed 's/\/sharesoft[^:]*//g'`
echo "Launching the job..."
root.exe -b -q "processLine.C(\"dataDriven($1,$2,$3,$4,$5,$6)\",\"dataDriven_C.so\")" 2>&1 
