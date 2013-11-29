import os, sys, shutil, re
from stat import *

jobs = {}

def check_files(arg,dirname,files):

    for file in files:
       file = dirname+'/'+file

       if not os.path.isdir(file):
          basename = os.path.basename(file)
          parts = re.split('_',basename)
          if len(parts) > 2:
             jobNum = int(re.split('_',basename)[3])
             if not jobs.has_key(jobNum) :
                jobs[jobNum] = [];

             jobs[jobNum].append(file)

if __name__ == '__main__':

    arg = "";

    os.path.walk(sys.argv[1], check_files, arg)

    for jobNum in jobs:
          largestFile = ''
          largestFileSize = 0
          for file in jobs[jobNum]:
             if os.path.islink(file):
                physical = os.readlink(file)
             else :
                physical = file

             if largestFileSize < os.path.getsize(physical):
                largestFileSize = os.path.getsize(physical)
                largestFile     = file

          print largestFile

