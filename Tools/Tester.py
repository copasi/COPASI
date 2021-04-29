#! /usr/bin/env python

# Tester, a python script for automatically testing CopasiSE

# Author: willy
# Date: 20.02.2008

import os          #  
import sys         # 
import getopt      # for getting user's arguments
import subprocess  # for running CopasiSE
import glob		   # for making file lists from directory
import string	   # for handling string
import time
#import shutil

# --- Usage Function ---

def usage():
  print '''
===================================================================================================
PURPOSE: The script aims at testing the given model(s) automatically through command line CopasiSE.
It enables one to test the model(s) saved in more than one directories.
--------------------------------------------------------------------------------------------------- 
USAGE: python Tester.py <DIR_OF_CopasiSE> <RELEASE_OS> <DIR_OF_TEST | DIR_OF_TestInfo>
where:
DIR_OF_CopasiSE : Directory containing CopasiSE binary file
RELEASE_OS      : Release-OS with format <relaease><OS> (eg. Build28Mac for Build28 under Mac OS)
DIR_OF_TEST     : Directory containing test file(s) -> only one directory is able to test
DIR_OF_TestInfo : Directory containing TestInfo.txt -> at least one directory is able to test
===================================================================================================
'''
# DIR_OF_RESULT   : Directory containing result(s) of testing

# --- Checking Function ---

def check(args):

# Check the existence of CopasiSE binary file

  binFile = args[0]+'/CopasiSE'
  if os.path.exists(binFile) is False:
    print 'Fatal Error: %s does not exist.' % (binFile)
    exit()

  global listInputDirs, listOutputDirs

# ----------
# listInputDirs : the list of input directories name including path, eq. ../COPASI_TestSuite/Tests/TEST_000001
# listOutputDirs : the list of output directories name including path, eq. ../COPASI_TestSuite/Results/Build25Mac/TEST_000001
# ----------

  listInputDirs = []
  listOutputDirs = []
  
# Create and fill listInputDirs by taking information from TestInfo.txt

  infoTFile = args[2] + '/TestInfo.txt'  # Check the existence of TestInfo.txt
  
  if os.path.exists(infoTFile) is True:  # still on ../Tests 
    file = open(infoTFile, 'r')
    listLine = file.read().split('\n')  # list of lines without \n at the end. 
    file.close()

    print listLine[2:]
	
    for line in listLine[2:]:
      listInputDirs.append(args[2] + '/' + line + '/')
 
  else:                                    # already on ../Test/<TESTDIR>
    listInputDirs.append(args[2])

# Create and fill listOutputDirs by replacing the directory of inputDir with more proper one   
  for dir in listInputDirs:
    listOutputDirs.append( string.replace(dir, 'Tests', 'Results/' + args[1]) )

# Check the existence of output directory; create it if necessary

  for outputDir in listOutputDirs:
    splitName = string.split(outputDir, '/')
    outDir = ''
    for name in splitName:
      if outDir == '':
        outDir = name
      else:
        outDir = outDir + '/' + name
		
      if os.path.exists(outDir) is False:
        print '%s does not exist.' % (outDir)
        os.system('mkdir ' + outDir)
        if os.path.exists(outDir) is True:
          print 'Create %s -> SUCCESS' % (outDir)
	  
# --- Main Function ---

def main():
  '''Parse font_size option, then convert each argument'''
  
  try:
    opts,args = getopt.getopt(sys.argv[1:], 'f:', ['font-size='])
  except getopt.GetoptError:
    usage()
    sys.exit(1)

  if len(args) < 3:
    usage()
    exit()

# Check the given arguments
  
  check(args)

  timeStart = time.time()
  print 'Time = ', timeStart

  print
  print 'Input Dirs:'
  print listInputDirs
  print '\nOutput Dirs:'
  print listOutputDirs
  
# Create a list containing any required parameters to run CopasiSE

  parInputs = []  # input parameters including filename and its path

  for dir in listInputDirs:    
    for name in glob.glob(dir + '/*.cps'):
      parInputs.append(name)
	  
    if len(parInputs) == 0:
      print '\n-> %s contains no cps file <-\n'% (dir)
  
#  print '\nInput File(s): '
#  print parInputs

  # output filename is taken from input one with different extension

  listPars = []  # containing any required parameters to run CopasiSE

  idx = 0
  while idx < len(parInputs):
    par = [args[0] + '/CopasiSE', parInputs[idx]]
    listPars.append(par)
    idx = idx + 1

#  print '--------'
#  for par in listPars:
#    print par
#  print '--------'

# Run CopasiSE

  print '\n--------'
  for par in listPars:
    print '\n', par, '\n'
    subprocess.Popen(par[0:2]).wait()  # wait until CopasiSE finish
    print '--------'

  timeInbetween = time.time()
  print '\nTimeStart = ', timeStart, ' - timeInbetween = ', timeInbetween
  print 'Duration = ', timeInbetween - timeStart, ' seconds\n'
#  exit()

# Move the output file from the input directory to the output one

  idx = 0
  for inDir in listInputDirs:
    outDir = listOutputDirs[idx]
    for name in glob.glob(inDir + '/*_result*.txt'):
      outName = string.replace(name, inDir, outDir)
      if os.path.exists(outName) is True:
        print 'Remove %s to %s directory ... SUCCESS' % (name, outDir) 
      os.system('mv ' + name + ' ' + outDir)    
    idx = idx + 1
  print ''
	
# Prepare report file; delete it if it exists already

  dirSplit = listOutputDirs[0].split('/')  
  # since the last character of 'dir' may be a '/' then :
  while dirSplit.pop() == '':
    continue 
  report = '/'.join(dirSplit) + '/report.txt'
#  print dirSplit
  print 'Report file: ', report, '\n'

  if os.path.exists(report) is True:
    os.remove(report)
  
# Make a comparison between expected and real results

  print 'listOutputDirs = ', listOutputDirs, ' in comparing process'

  for dir in listOutputDirs:
    print 'dir = ', dir

    dirSplit = dir.split('/')
  
    # since the last character of 'dir' may be a '/' then :
    testName = ''
    while testName == '':
      testName = dirSplit.pop()

    print testName

    for name in glob.glob(dir + '/*_result*.txt'):
      basename = os.path.basename(name)
      print 'name = ', name, ' -- basename = ', basename
      print 'dirname = ', os.path.dirname(name)
      print 'args[2] = ', args[2]
      refDir = string.replace(args[2], 'Tests', 'References/' + testName + '/')
      print 'refDir = ', refDir

      # between 'results' and 'result'
      if basename.find('results') != -1:
        cmpFile = string.replace(name, '_results.txt', '_diff.txt')
      else:
       cmpFile = string.replace(name, '_result.txt', '_diff.txt')

#      print refDir, ' -vs- ', name, ' -> ', cmpFile
#      os.system('python NumDiff.py ' + refFile + ' ' + name + ' ' + cmpFile + ' ' + report + ' ' + testName )

      for refName in glob.glob(refDir + '/*.txt'):
        print 'refName = ', refName
        os.system('python NumDiff.py ' + refName + ' ' + name + ' ' + cmpFile + ' ' + report + ' ' + testName )

  timeFinish = time.time()
  print '\nTimeStart = ', timeStart, ' - timeFinish = ', timeFinish
  print '\nDuration before running CopasiSE = ', timeInbetween - timeStart, ' seconds'
  print 'Duration after running CopasiSE = ', timeFinish - timeInbetween, ' seconds'
  print 'Total duration = ', timeFinish - timeStart, ' seconds'

  print '\n>>> End of Tester.py <<<\n'

# --- Run as main ---

#if __name__ == '__main__':
main()

