# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/Tools/Tester.py,v $ 
#   $Revision: 1.3 $ 
#   $Name:  $ 
#   $Author: pwilly $ 
#   $Date: 2008/10/29 15:29:04 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

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

#  exit() 
# Create and fill listOutputDirs by replacing the directory of inputDir with more proper one   

  for dir in listInputDirs:
    listOutputDirs.append( string.replace(dir, 'Tests', 'Results/' + args[1]) )

#  print 'Input Dirs:'
#  print listInputDirs
#  print '\nOutput Dirs:'
#  print listOutputDirs

#  exit()

# Check the existence of output directory; create it if necessary

#  print '--', listOutputDirs

  for outputDir in listOutputDirs:
    splitName = string.split(outputDir, '/')
    outDir = ''
    for name in splitName:
#      print '----', name
      if outDir == '':
        outDir = name
      else:
        outDir = outDir + '/' + name
		
#      print outDir

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

#  OS = string.split( sys.platform, ' ' )[0]
#  print OS
#  print sys.platform, sys.version
#  exit()
  
# Check the given arguments
  
  check(args)

  print
  print 'Input Dirs:'
  print listInputDirs
  print '\nOutput Dirs:'
  print listOutputDirs
  
#  exit()

# Create a list containing any required parameters to run CopasiSE

  parInputs = []  # input parameters including filename and its path
#  parOutputs = [] # output parameters including filename and its path

  for dir in listInputDirs:
#    idx = 0
    
    for name in glob.glob(dir + '/*.cps'):
      parInputs.append(name)
#      idx = idx + 1
	  
#    if idx == 0:
    if len(parInputs) == 0:
      print '\n-> %s contains no cps file <-\n'% (dir)
#      exit()
  

#  print '\n--------'
#  for par in parInputs:
#	print par
#  print '--------\n'

  print '\nInput File(s): '
  print parInputs

  # output filename is taken from input one with different extension

#  print '\nOutput File(s): '
#  print parOutputs

  listPars = []  # containing any required parameters to run CopasiSE

  idx = 0
  while idx < len(parInputs):
    par = [args[0] + '/CopasiSE', parInputs[idx]]
    listPars.append(par)
    idx = idx + 1

  print '--------'
  for par in listPars:
    print par
  print '--------'

#  exit()

# Run CopasiSE

#  subprocess.Popen(pars[0:2]).wait()  # wait until CopasiSE finish
  print '\n--------'
  for par in listPars:
    print '\n', par, '\n'
    subprocess.Popen(par[0:2]).wait()  # wait until CopasiSE finish
    print '--------'

#  exit()

# Move the output file from the input directory to the output one

  print '\n'

  print 'listInputDirs = ', listInputDirs, ' in removing process'

  idx = 0
  for inDir in listInputDirs:
    outDir = listOutputDirs[idx]
    for name in glob.glob(inDir + '/*_result*.txt'):
      outName = string.replace(name, inDir, outDir)
      if os.path.exists(outName) is True:
        print 'Remove %s to %s ... SUCCESS' % (name, outDir) 
      os.system('mv ' + name + ' ' + outDir)    
    idx = idx + 1
	
#  exit()

# Make a comparison between expected and real results

##  resultsPath, sName = os.path.split(args[2])
##  refPath = os.path.join(resultsPath, 'References')
##  refFile = refPath + '/' + modelName + '.txt'
##  print '\nReference Name: %s' % refFile

##  for dir in listOutputDirs:
##    for output in listOutputFiles:
#      os.system('sdiff ' + dir + '/' + output + ' ' + refFile + ' > ' + dir + '/sdiff_' + output)
##      resultFile = dir + '/' + output
##      cmpFile = dir + '/diff_' + output
#      print resultFile, ' --', cmpFile
##      os.system('python NumDiff.py ' + resultFile + ' ' + refFile + ' ' + cmpFile )

  print 'listOutputDirs = ', listOutputDirs, ' in comparing process'

  dirSplit = listOutputDirs[0].split('/')
  
  # since the last character of 'dir' may be a '/' then :
#  testName = ''
#  while testName == '':
#    testName = dirSplit.pop()
#  dirSplit.pop()
  while dirSplit.pop() == '':
    continue 

  report = '/'.join(dirSplit) + '/report.txt'
  print dirSplit
  print report

#  exit()
  if os.path.exists(report) is True:
    os.remove(report)
  
  for dir in listOutputDirs:
    print 'dir = ', dir

    dirSplit = dir.split('/')
  
    # since the last character of 'dir' may be a '/' then :
    testName = ''
    while testName == '':
      testName = dirSplit.pop()

    print testName

    for name in glob.glob(dir + '/*_result*.txt'):
      print os.path.basename(name)
      refFile = string.replace(name, os.path.dirname(name), string.replace(args[2], 'Tests', 'Results/References'))

      # between 'results' and 'result'
      if os.path.basename(name).find('results') != -1:
        cmpFile = string.replace(name, '_results.txt', '_diff.txt')
      else:
       cmpFile = string.replace(name, '_result.txt', '_diff.txt')

      print refFile, ' -vs- ', name, ' -> ', cmpFile
#      resultFile = args[2] + '/Results/References/' + name
#      cmpFile = dir + '/diff_' + output
#      print resultFile, ' --', cmpFile
#      os.system('python NumDiffE.py ' + refFile + ' ' + name + ' ' + cmpFile )
      os.system('python NumDiffE.py ' + refFile + ' ' + name + ' ' + cmpFile + ' ' + report + ' ' + testName )
#      os.system('sdiff ' + refFile + ' ' + name + ' > ' + cmpFile)
#      os.system('python ndiff.py ' + refFile + ' ' + name + ' > ' + cmpFile)

  print '\n>>> End of Tester.py <<<\n'

# --- Run as main ---

#if __name__ == '__main__':
main()

