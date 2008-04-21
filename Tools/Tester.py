# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/Tools/Tester.py,v $ 
#   $Revision: 1.1.2.1 $ 
#   $Name:  $ 
#   $Author: pwilly $ 
#   $Date: 2008/02/26 10:17:36 $ 
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
#import shutil

# --- Usage Function ---

def usage():
  print '''
===================================================================================================
PURPOSE: The script is for testing the given model(s) automatically through command line CopasiSE.
It enables one to test the model(s) saved in more than one directories.
--------------------------------------------------------------------------------------------------- 
USAGE: python Tester.py <DIR_OF_CopasiSE> <DIR_OF_TEST | DIR_OF_TestInfo> <DIR_OF_RESULT> 
where:
DIR_OF_CopasiSE : Directory containing CopasiSE binary file
DIR_OF_TEST     : Directory containing test file(s) -> only one directory is able to test
DIR_OF_TestInfo : Directory containing TestInfo.txt -> at least one directory is able to test
DIR_OF_RESULT   : Directory containing result(s) of testing
===================================================================================================
'''

# --- Read Info File Function ---

def readInfoFile(infoFile):

# Open the info file

  file = open(infoFile, 'r')
  global testName, modelName, listInputFiles, listOutputFiles

# ----------
# testName : the name of the test indicating the name of the directory containing the test or the result
# modelName : the name of the used model
# listInputFiles : the list of input files name (just the name without any paths, eq. test1.cps)
# listOutputFiles : the list of output files name (just the name without any paths, eq. test1.txt)
# ----------

  listLine = file.read().split('\n')  # list of lines without \n at the end. 
#  print listLine

  testName = listLine[0]
#  descOfModel = listLine[2]
#  descOfExpectedResult = listLine[4]
  modelName = listLine[6]  # the name of the used model

# Create the listInputFiles and fill it

  listInputFiles = []
  for line in listLine[8:]:
    if line != '':
      listInputFiles.append(line)
    else:
      break
 
# Create the listOutputFiles and fill it

  listOutputFiles = []
  indexOutput = 8+len(listInputFiles)+1  # '+1' for \n

  for line in listLine[indexOutput:]:
    if line != '':
      listOutputFiles.append(line)
    else:
      break
 
#  print listInputFiles
#  print listOutputFiles

  if len(listInputFiles) != len(listOutputFiles):
    print 'Fatal Error: Number of output files (= %d) != number of input files (= %d)' % (int(len(listInputFiles)), int(len(listOutputFiles)))
    exit()

#  print testName
#  print descOfModel
#  print descOfExpectedResult
#  print modelName

  file.close()

# --- Checking Function ---

def check(args):

# Check the existence of CopasiSE binary file

  binFile = args[0]+'/CopasiSE'
  if os.path.exists(binFile) is False:
    print 'Fatal Error: %s does not exist.' % (binFile)
    exit()

# Create and fill listInputDirs by taking information from TestInfo.txt

  infoTFile = args[1] + '/TestInfo.txt'  # Check the existence of TestInfo.txt
  
  global listInputDirs, listOutputDirs

# ----------
# listInputDirs : the list of input directories name including path, eq. ../COPASI_TestSuite/Tests/TEST_000001
# listOutputDirs : the list of output directories name including path, eq. ../COPASI_TestSuite/Results/Build25Mac/TEST_000001
# ----------

  listInputDirs = []
  listOutputDirs = []
  
  if os.path.exists(infoTFile) is True:  # still on ../Tests 
    file = open(infoTFile, 'r')
    listLine = file.read().split('\n')  # list of lines without \n at the end. 
    file.close()

#    print listLine[2:]

    for line in listLine[2:]:
      listInputDirs.append(args[1] + '/' + line + '/')
 
  else:                                    # already on ../Test/<TESTDIR>
    listInputDirs.append(args[1])
 
# Create and fill listOutputDirs by taking information from Info.txt

  for dir in listInputDirs:
    infoFile = dir + '/Info.txt'
    if os.path.exists(infoFile) is False:
      print 'Fatal Error: %s does not exist.' % (infoFile)
      exit()
    else:
      readInfoFile(infoFile)
      listOutputDirs.append(args[2] + '/' + testName + '/')

#  print 'Input Dirs:'
#  print listInputDirs
#  print '\nOutput Dirs:'
#  print listOutputDirs

#  exit()

# Check the existence of input file (eg. cps, gps, sbml)
  
  print '\nChecking the existence of the following file(s)'

  for dir in listInputDirs:
    for inputName in listInputFiles:
      inputFile = dir + inputName
      if os.path.exists(inputFile) is False:
        print "%s ... NOT EXIST" % (inputFile)
        exit() 
      print '%s ... EXIST' % inputFile
    print '\n'

# Check the existence of output directory; create it if necessary

  for outputDir in listOutputDirs:
    if os.path.exists(outputDir) is False:
      print '%s does not exist.' % (outputDir)
      answer = 's'
      while answer[0] not in ('n', 'N', 'y', 'Y'):
        answer = raw_input('Create it (y/n) ? ')
#        print 'your answer is %s. It must be y/n' % (answer)
      if answer[0] in ('n', 'N'):
        print "Exit!"
        sys.exit(1)
      else:
#        print 'Create one!'
        os.system('mkdir ' + outputDir)
        if os.path.exists(outputDir) is False:
          print 'Create %s -> FAIL' % (outputDir)
          exit()
        else:
          print 'Create %s -> SUCCESS' % (outputDir)
  
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

  print 'Input Dirs:'
  print listInputDirs
  print '\nOutput Dirs:'
  print listOutputDirs

#  exit()

# Create a list containing any required parameters to run CopasiSE

  parInputs = []  # input parameters including filename and its path
  parOutputs = [] # output parameters including filename and its path

  for dir in listInputDirs:
    for input in listInputFiles:
      parInputs.append(dir + '/' + input)

  print '\n\nInput File(s): '
  print parInputs

  for dir in listOutputDirs:
    for output in listOutputFiles:
      parOutputs.append(dir + '/' + output)

  print '\nOutput File(s): '
  print parOutputs

  listPars = []  # containing any required parameters to run CopasiSE

  idx = 0
  while idx < len(parInputs):
    par = [args[0] + '/CopasiSE', parInputs[idx], parOutputs[idx]]
    listPars.append(par)
    idx = idx + 1

#  print '--------'
#  for par in listPars:
#    print par
#  print '--------'
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
  idx = 0
  for dir in listInputDirs:
    for output in listOutputFiles:
      os.system('mv ' + dir + '/' + output + ' ' + parOutputs[idx])
      print 'Move from %s to %s ... SUCCESS' % (dir+'/'+output, parOutputs[idx]) 
      idx = idx + 1

#  os.system('mv ' + args[1] + '/' + outputName + ' ' + args[2] + '/' + testName)
#  shutil.move(args[1] + '/' + outputName, args[2] + '/' + testName)

# Make a comparison between expected and real results

  resultsPath, sName = os.path.split(args[2])
  refPath = os.path.join(resultsPath, 'References')
  refFile = refPath + '/' + modelName + '.txt'
  print '\nReference Name: %s' % refFile

  for dir in listOutputDirs:
    for output in listOutputFiles:
#      os.system('sdiff ' + dir + '/' + output + ' ' + refFile + ' > ' + dir + '/sdiff_' + output)
      resultFile = dir + '/' + output
      cmpFile = dir + '/diff_' + output
#      print resultFile, ' --', cmpFile
      os.system('python NumDiff.py ' + resultFile + ' ' + refFile + ' ' + cmpFile )

  print '\n>>> End of Tester.py <<<\n'

# --- Run as main ---

#if __name__ == '__main__':
main()

