#! /usr/bin/env python



# NumDiff, a python script for writing numerical differences between two files

# Author: willy
# Date: 25.02.2008

import os, sys, string, difflib
import re

# --- Failure Message Function ---

def fail(msg):
    out = sys.stderr.write
    out('\nERROR MESSAGE: ' + msg + "\n\n")
    return 0

# --- From Integer to String ---

def itos(integer):
  return str(integer)

# --- Open File Function ---

# Open a file & return the file object; 
# gripe and return 0 if it couldn't be opened
def fopen(fname):
  try:
    return open(fname, 'r')
  except (IOError) as detail:
    return fail("Couldn't open " + fname + ": " + str(detail))

# --- Get Index Line ---

def getIdxLine(filename, str):
  file = fopen(filename)
  a = file.readlines(); file.close()
  idxLine = 0
  for f in a:
    # as the first character is either '-' or '+'
    if f.find(str) > -1:
      return idxLine
    idxLine = idxLine + 1    
  return -1

# --- Modify CmpResult Function obtained by ndiff python ---

def takeImportantThings_python(ename, aname, dname):

  file = fopen(ename)
  file2 = fopen(aname)
  if not file and not file2:
    return 0

  a = file.readlines(); file.close()
  b = file2.readlines(); file2.close()

  dataFile1 = [] 
  dataFile2 = [] 
  for line in difflib.unified_diff(a, b):
    #print line
    if line.find('-') == 0:
      dataFile1.append(line)
    
    # '+' at the first character represents the line coming from the second file
    if line.find('+') == 0:
      dataFile2.append(line)

  #print '\n\nData from file 1 = ', dataFile1
  #print '\n\nData from file 2 = ', dataFile2

  expData = []
  actData = []

  # find the closest match of each data on dataFile1 from dataFile1
  for data in dataFile1:
    match = difflib.get_close_matches(data, dataFile2)

    for data2 in match:

      # '-' represents the data coming from the first file
      if re.match('-', data):
        txt = data.replace('-', '', 1)
      else:
        txt = data              

      expData.append(txt)

      newData = ''

      # if match to more than one item, select the most proper one
      if len(match) > 1:
        for entry in match:
          if len(entry.split()) == len(data.split()):
            newData = entry
            break
      else:
        newData = data2

      # '+' represents the data coming from the second file
      if re.match('\+', newData):
        txt = newData.replace('+', '', 1)
      else:
        txt = newData

      actData.append(txt)              

  # catch integer, decimal, and scientific-formatted number (eg. 0.1234e-5) ...

  # formulate the need using modularized regular expression
  real_in = r"-?\d+"						# integer notation
  real_dn = r"-?\d+\.\d*|\d*\.\d+"		# decimal notation
  real_sn = r"-?\d\.?\d*[Ee][+\-]?\d+"	# scientific notation
  real = real_sn + "|" + real_dn + "|" + real_in

  value = []
  idxAux = 0

  absErrorUB = 1e-09
  if 'ABSOLUTE_ERROR' in os.environ:
    absErrorUB = float(os.environ['ABSOLUTE_ERROR'])
  relErrorUB = 1e-05
  if 'RELATIVE_ERROR' in os.environ:
    relErrorUB = float(os.environ['RELATIVE_ERROR'])

  file3 = open(dname, 'w')

  for idx in range(0, len(expData)):
    idxNumStr = 0
    for txt in expData[idx], actData[idx]:

      # find all items satisfying the regular expression.
      numStr = re.findall(real, txt)

      # do something if at least one item exists:
      if len(numStr) > 0:

        # do something correlated to data from the first file:
        if idxNumStr%2 == 0:
          setExpData = set(expData[idx].split())

          # check whether the obtained item exists really on the file.
          for numItem in numStr:
            if numItem not in setExpData:
              delItem = numItem
              numStr.remove(delItem)

        # do something correlated to data from the second file:
        else:
          setActData = set(actData[idx].split())
        
          # check whether the obtained item exists really on the file.
          for numItem in numStr:
            if numItem not in setActData:
              delItem = numItem
              numStr.remove(delItem)

        # add all obtained, checked items.
        value.append(numStr)

      # increment the index
      idxNumStr = idxNumStr + 1
       
    # calculate the difference between two values and write it into a file
    if len(value) > 0:
      ref = expData[idx]

      if len(value[idxAux]) != len(value[idxAux+1]):
        print ('len(value[idxAux]) = ', len(value[idxAux]), ' -vs- len(value[idxAux+1]) = ', len(value[idxAux+1]) )
        exit()

      absErr, relErr, idxField = calcError( value[idxAux], value[idxAux+1], ref )
      #print '-'*100

      diffExists = False

      error = ''	  
      if relErr > relErrorUB:
        diffExists = True
        error = 'relative Error = ' + itos(relErr)
      elif absErr > absErrorUB:
        diffExists = True
        error = 'absolute Error = ' + itos(absErr)

      if diffExists:
        indexLineFromFile = getIdxLine(ename, expData[idx])

        # write into file.
        strLine = itos(indexLineFromFile)      
        file3.write('\nLine ' + strLine + ':\n')
        file3.write('+ ' + expData[idx])
        file3.write('- ' + actData[idx])
        textErr = 'at Field ' + itos(idxField) + ': ' + itos(error) + '\n'
        file3.write('* ' + textErr)
        
      idxAux = idxAux + 2

  file3.close()

# --- Calculate error ---

def calcError(listValue0, listValue1, ref):

  # calculate the numerical differences.
  # number[0] = number[1] by the list constructor.
  diff = []
  numList = []

  # absError = |A - B|
  absErrorUB = 1e-09
  # relError = absError / min (|A|, |B|)
  relErrorUB = 1e-05

  absErr = []; relErr = []

  #print 'listValue0 = ', listValue0
  #print 'listValue1 = ', listValue1

  # len(listValue0) = len(listValue1)
  for ij in range(0, len(listValue1)):

    value0 = float(listValue0[ij])
    value1 = float(listValue1[ij])

    if max(abs(value0), abs(value1)) == 0.0:
      absolute = 0.0; relative = 0.0
    else:
      absolute = abs(value0 - value1)
      #print 'val0 = ', value0, ' - val1 = ', value1 
      relative = absolute / max(abs(value0), abs(value1))

    relErr.append(relative)
    absErr.append(absolute)

  relErrMax = max(relErr)
  absErrMax = max(absErr)
  idxRelErr = relErr.index(relErrMax)
  idxAbsErr = absErr.index(absErrMax)
  refSplit = ref.split()
  setRef = set(refSplit)

  #print 'absErr = ', absErr, ' -> max ', absErrMax, ' -> idx = ', idxAbsErr
  #print 'relErr = ', relErr, ' -> max ', relErrMax, ' -> idx = ', idxRelErr
  #print 'corr. listValue0 = ', listValue0[idxAbsErr] 

  if listValue0[idxAbsErr] in setRef:
    idxField = -1
    while idxField < idxAbsErr:
#      print listValue0[idxAbsErr]
      idxField = refSplit.index( listValue0[idxAbsErr], idxField+1, len(refSplit) )

#    print idxField, ' -> ', refSplit[idxField]

  return absErrMax, relErrMax, idxField

# --- Main Function ---

def runTest(expResult, actResult, tmpResult, report, testName):

  takeImportantThings_python(expResult, actResult, tmpResult)

  endResult = tmpResult
  size = os.path.getsize(endResult)

  # create Report File
  repFile = open(report, 'a') 

  # there exists difference value(s)
  differenceFound = size > 0;

  if differenceFound:

    # take info
    file = open(endResult, 'r')
    lines = file.readlines()
    file.close()

    # insert head
    newLine = "Legends:\n"
    newLineAct = "+ : " + actResult + "\n"
    newLineExp = "- : " + expResult + "\n" 
    newLineDif = "* : absolute/relative error\n"
    maxLength = max(len(newLineAct), len(newLineExp), len(newLineDif))
    newLineSep = "-" * maxLength + "\n"

    head = newLine + newLineAct + newLineExp + newLineDif + newLineSep

    lines[0:0] = [head]

    # re-write
    file = open(endResult, 'w')
    file.writelines( lines )
    file.close()

    repFile.write(testName + '\t...\tDifferent\n')
  else:  
    repFile.write(testName + '\t...\tOK\n')

  repFile.close()
  
  return differenceFound

def main(args):  

  if len(args) < 5:
    return fail("Need 5 args: <exp_result> <actual_result> <cmp_result> <report> <testName>")

  expResult, actResult, tmpResult, report, testName = args
  runTest(expResult, actResult, tmpResult, report, testName)
#  print '\nexp: ', expResult, '\nact: ', actResult, '\ntmpResult: ', tmpResult, '\nreport: ', report, '\ntestName', testName


if __name__ == '__main__':
  print ('--- Running NumDiff.py ---')
  args = sys.argv[1:]
  main(args)  
