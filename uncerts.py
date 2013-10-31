import os
import sys
import re
import subprocess

groups = {}
groups['TT']  = ['tt']
groups['WJ']  = ['wj']
groups['ZN']  = ['zn200', 'zn400']
groups['Top'] = ['tW', 'tbarW', 't', 'tbar', 'tS', 'tbarS']
groups['VV']  = ['ww', 'wz', 'zz']

process = sys.argv[1]

if not groups.has_key(process) :
  print 'First argument should be one of the following: TT WJ ZN Top VV'
  exit(0)

MET = sys.argv[2]

if not MET.isdigit() :
  print 'Second argument should be a number'
  exit(0)

pdf0_log = {}
pdf1_log = {}
sca0_log = {}
sca1_log = {}

main_log = subprocess.Popen(['root.exe', '-b', '-q', 'processLine.C("jesFlowTmp('+process+','+MET+')","jesFlowTmp_C.so")'], shell=False, stdout=subprocess.PIPE)

for sample in groups[process]:
   pdf0_log[sample] = subprocess.Popen(['root.exe', '-b', '-q', 'processLine.C("calcPDF('+sample+',0,'+MET+')","calcPDF_C.so")'], shell=False, stdout=subprocess.PIPE)
   pdf1_log[sample] = subprocess.Popen(['root.exe', '-b', '-q', 'processLine.C("calcPDF('+sample+',1,'+MET+')","calcPDF_C.so")'], shell=False, stdout=subprocess.PIPE)
#   sca0_log[sample] = subprocess.Popen(['root.exe', '-b', '-q', 'processLine.C("calcQ2('+sample+',0,'+MET+')","calcQ2_C.so")'], shell=False, stdout=subprocess.PIPE)
#   sca1_log[sample] = subprocess.Popen(['root.exe', '-b', '-q', 'processLine.C("calcQ2('+sample+',1,'+MET+')","calcQ2_C.so")'], shell=False, stdout=subprocess.PIPE)

pdf0bPlus  = {}
pdf0bMinus = {}
pdf1bPlus  = {}
pdf1bMinus = {}
#sca0bPlus  = {}
#sca0bMinus = {}
#sca1bPlus  = {}
#sca1bMinus = {}

for sample in groups[process]:
   for line in re.split('\n',pdf0_log[sample].communicate()[0]) :
#      print 'pdf0_log['+sample+']:'+line
      if re.search('PDF uncertainty:',line) != None :
         items = re.split('\s*',line)
         pdf0bPlus [sample] = float( items[2] )
         pdf0bMinus[sample] = float( items[3] )
      if re.search('No events processed',line) != None :
         pdf0bPlus [sample] = float(0)
         pdf0bMinus[sample] = float(0)

   for line in re.split('\n',pdf1_log[sample].communicate()[0]) :
#      print 'pdf1_log['+sample+']:'+line
      if re.search('PDF uncertainty:',line) != None :
         items = re.split('\s*',line)
         pdf1bPlus [sample] = float( items[2] )
         pdf1bMinus[sample] = float( items[3] )
      if re.search('No events processed',line) != None :
         pdf1bPlus [sample] = float(0)
         pdf1bMinus[sample] = float(0)

#   for line in re.split('\n',sca0_log[sample].communicate()[0]) :
##      print 'sca0_log:'+line
#      if re.search('Q2 scale variation:',line) != None :
#         items = re.split('\s*',line)
#         sca0bPlus [sample] = float( items[3] )
#         sca0bMinus[sample] = float( items[4] )
#
#   for line in re.split('\n',sca1_log[sample].communicate()[0]) :
##      print 'sca1_log:'+line
#      if re.search('Q2 scale variation:',line) != None :
#         items = re.split('\s*',line)
#         sca1bPlus [sample] = float( items[3] )
#         sca1bMinus[sample] = float( items[4] )
#
##print 'pdf0bPlus=',pdf0bPlus,' pdf0bMinus=',pdf0bMinus,' pdf1bPlus=',pdf1bPlus,' pdf1bMinus=',pdf1bMinus
##print 'sca0bPlus=',sca0bPlus,' sca0bMinus=',sca0bMinus,' sca1bPlus=',sca1bPlus,' sca1bMinus=',sca1bMinus

for line in re.split('\n',main_log.communicate()[0]) :
   for sample in groups[process]:
      if re.search('\+PDF0',line) != None :
         line = re.sub(r'\+PDF0'+sample+'\)','+'+str(pdf0bPlus[sample])+')',line)
      if re.search('\-PDF0',line) != None :
         line = re.sub(r'\-PDF0'+sample+'\)',str(pdf0bMinus[sample])+')',line)
      if re.search('\+PDF1',line) != None :
         line = re.sub(r'\+PDF1'+sample+'\)','+'+str(pdf1bPlus[sample])+')',line)
      if re.search('\-PDF1',line) != None :
         line = re.sub(r'\-PDF1'+sample+'\)',str(pdf1bMinus[sample])+')',line)
#      if re.search('\+SCALE0',line) != None :
#         line = re.sub(r'\+SCALE0'+sample+'\)','+'+str(sca0bPlus[sample])+')',line)
#      if re.search('\-SCALE0',line) != None :
#         line = re.sub(r'\-SCALE0'+sample+'\)',str(sca0bPlus[sample])+')',line)
#      if re.search('\+SCALE1',line) != None :
#         line = re.sub(r'\+SCALE1'+sample+'\)','+'+str(sca1bPlus[sample])+')',line)
#      if re.search('\-SCALE1',line) != None :
#         line = re.sub(r'\-SCALE1'+sample+'\)',str(sca1bPlus[sample])+')',line)
   print line;

#output.write(code);
#output.close();
#input.close()
