#!/bin/bash

echo "Initializing the environment..."
cd /home/kkotov/CMSSW_5_3_8/src/OSUAnalysis/BEANsTools/
export VO_CMS_SW_DIR=/sharesoft/cmssw
source $VO_CMS_SW_DIR/cmsset_default.sh
source /sharesoft/osg/ce/setup.sh
eval `scram runtime -sh`
echo "Launching the job..."
../../../bin/slc5_amd64_gcc462/OATexpert $1 $2 $3 $4 $5
