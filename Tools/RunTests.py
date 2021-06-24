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
import NumDiff
import shutil


# ----------
# listInputDirs : the list of input directories name including path, eq. ../COPASI_TestSuite/Tests/TEST_000001
# listOutputDirs : the list of output directories name including path, eq. ../COPASI_TestSuite/Results/Build25Mac/TEST_000001
# ----------


global listInputDirs, listOutputDirs
listInputDirs = []
listOutputDirs = []


# --- Checking Function ---

def getInputDirs(source_dir):
    result = []
    
    infoTFile = os.path.join( source_dir, 'TestInfo.txt')  # Check the existence of TestInfo.txt
    
    if os.path.exists(infoTFile):  # still on ../Tests 
      file = open(infoTFile, 'r')
      listLine = file.read().split('\n')  # list of lines without \n at the end. 
      file.close()
    
      for line in listLine[2:]:
        if line.strip().startswith('#'):
          continue;

        result.append(os.path.join(source_dir, line))
    
    else:                                    # already on ../Test/<TESTDIR>
      result.append(source_dir)

    return result

def check(args):



  listOutputDirs = []
  # Create and fill listOutputDirs by replacing the directory of inputDir with more proper one   
  for dir in listInputDirs:
    listOutputDirs.append( os.path.join( dir.replace('Tests', os.path.join('Results', args[1])) ))

  # Check the existence of output directory; create it if necessary
  for outputDir in listOutputDirs:
    if not os.path.exists(outputDir):
      os.makedirs(outputDir)
 
# --- Main Function ---
def main(args):
  """
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
"""  
# DIR_OF_RESULT   : Directory containing result(s) of testing
  try:
    opts,args = getopt.getopt(args, 'f:', ['font-size='])
  except getopt.GetoptError:
    print (__doc__)
    sys.exit(1)

  if len(args) < 3:
    print (__doc__)
    exit()

  # Check the given arguments

  # Check the existence of CopasiSE binary file
  binFile = args[0]
  out_dir = args[1]
  source_dir = args[2]

  if os.path.exists(binFile) is False:
    print ('Fatal Error: %s does not exist.' % (binFile))
    exit()  

  # Create and fill listInputDirs by taking information from TestInfo.txt
  listInputDirs = getInputDirs(source_dir)

  for dir in listInputDirs:
      testDir(dir, binFile, source_dir, out_dir)

def getCopasiFile(dir):
  try: 
    return glob.glob(dir + '/*.cps')[0];
  except:
    print ('\n-> %s contains no cps file <-\n'% (dir))
    sys.exit(1)

def testDir(dir, binFile, source_dir, outDir):
  
  testName = os.path.basename(dir)
  if not os.path.exists(outDir):
   os.makedirs(outDir)

  print ('testing {0}'.format(testName))
  
  # execute copasise
  par = [binFile, '--nologo', getCopasiFile(dir)]
  subprocess.Popen(par[0:3]).wait()  # wait until CopasiSE finish

  # Move the output file from the input directory to the output one
  computedResults = []
  for name in glob.glob(dir + '/*_result*.txt'):
    target = os.path.join(outDir, os.path.basename(name))
    if os.path.exists(target):
        os.remove(target)
    shutil.copy(name, target)
    os.remove(name)
    computedResults.append(target)

  if len(computedResults) == 0: 
      print ('... no result produced, please verify that the test produces a report file "*_result*.txt"')
      sys.exit(1)

  # Prepare report file; delete it if it exists already
  report =  os.path.join(outDir, 'report.txt')

  for name in computedResults:
    basename = os.path.basename(name)
    refDir = ''
    if testName not in source_dir:
      refDir = source_dir.replace('Tests', os.path.join('References', testName ))
    else:
      refDir = source_dir.replace('Tests', 'References')
    if not os.path.exists(refDir): 
        print ("... no reference data for test! missing dir: {0}".format(refDir))
        sys.exit(1)

    # between 'results' and 'result'
    if basename.find('results') != -1:
      cmpFile = name.replace('_results.txt', '_diff.txt')
    else:
      cmpFile = name.replace('_result.txt', '_diff.txt')

    for refName in glob.glob(refDir + '/*.txt'):
      different = NumDiff.runTest(refName, name, cmpFile, report, testName)
      if different: 
        print(" ... Different ")
      else:
        print (" ... OK")


# --- Run as main ---

if __name__ == '__main__':
  args = sys.argv[1:]
  main(args)  
