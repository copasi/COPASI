# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/Tools/NumDiff.py,v $ 
#   $Revision: 1.3 $ 
#   $Name:  $ 
#   $Author: pwilly $ 
#   $Date: 2008/10/29 15:27:43 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

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
    return open(fname, 'U')
  except IOError, detail:
    return fail("Couldn't open " + fname + ": " + str(detail))

# --- Get Index Line ---

def getIdxLine(filename, str):
  file = fopen(filename)
  a = file.readlines(); file.close()
  idxLine = 0
  for f in a:
    # as the first character is either '-' or '+'
    if f.find(str) > -1:
#      print '-> Line: ', idxLine, ' - string = ', str, ' - ', f
      return idxLine
    idxLine = idxLine + 1    
  return -1

# --- Modify CmpResult Function obtained by ndiff python ---

def takeImportantThings_python(ename, aname, dname):

  print 'ename = ', ename
  print 'aname = ', aname

  file = fopen(ename)
#  file2 = open(ename, 'w')
  file2 = fopen(aname)
  if not file and not file2:
    return 0

#  a = file.read().split('\n')
#  b = file2.read().split('\n')
  a = file.readlines(); file.close()
  b = file2.readlines(); file2.close()
  print a
  print b

  dataFile1 = [] 
  dataFile2 = [] 
  for line in difflib.unified_diff(a, b):
#if string.find(str, '|') > -1:
    # '-' at the first character represents the line coming from the first file
    if string.find(line, '-') == 0:
      dataFile1.append(line)
    
    # '+' at the first character represents the line coming from the second file
    if string.find(line, '+') == 0:
      dataFile2.append(line)
#    print line
#  for aLine in a:
#    print '--> aLine = ', aLine
#    for bCand in difflib.get_close_matches(aLine, b, 3, 0.75):
#      print '====> bLine = ', bCand

#    print difflib.get_close_matches(aLine, b, 3, 0.7)
#    print 

  print '\n\nData from file 1 = ', dataFile1
  print '\n\nData from file 2 = ', dataFile2

  expData = []
  actData = []

  # find the closest match of each data on dataFile1 from dataFile1
  for data in dataFile1:
    match = difflib.get_close_matches(data, dataFile2)
    print 'match = ', len(match)

    for data2 in match:
#      print 'data2** = ', data2, ' -> ', len(data)

      # '-' represents the data coming from the first file
      if re.match('-', data):
        txt = string.replace(data, '-', '', 1)
      else:
        txt = data              

      expData.append(txt)

      newData = ''

      # if match to more than one item, select the most proper one
      if len(match) > 1:
        for entry in match:
          if len(entry.split()) == len(data.split()):
            newData = entry
            print 'entry = ', entry
            break
      else:
        newData = data2
        print 'data2 = ', data2

      # '+' represents the data coming from the second file
      if re.match('\+', newData):
        txt = string.replace(newData, '+', '', 1)
      else:
        txt = newData

      actData.append(txt)              

#     print 'data2 = ', data2, ' -> ', len(data)

#      for data2 in match:
#        print 'data2 = ', data2, ' -> ', len(data)

#    matchNew = match
#    if len(match) > 1:
#      matchNew = match
#      for entry in match:
#        entrySplit = entry.split()
#        dataSplit = data.split()
#        if len(entrySplit) == len(dataSplit):
#          matchNew = entry
#          break

#      match = matchNew
#    match = matchNew
#    print '-> data : ', data, 'match = ', match, '\n'

  print '\nexpData = ', expData
  print '\nactData = ', actData


#  allData = []
#  allData.append(actData)
#  allData.append(expData

#  print getIdxLine(tname, actData[2][1:])

#        print entrySplit, ' -> ', len(entrySplit)
#        print dataSplit, ' -> ', len(dataSplit)
#        print 'len(', entry, ') = ', len(entry), ' -vs- ', len(data)
#        print '-> data : ', data, 'match = ', entry, '\n'
#    print '-> data : ', data, 'match = ', '\n'

  # collect any data from dataFile1 containing numeric values
#  for data in dataFile1:
#    numData = re.findall("-?\d+\.?\d*e?-?\+?\d*", data)
#    print 'data = ', data, ' - numData of the first file = ', numData

#  for data in actData:
#  for idx in range(0, len(actData)):
#    numData = re.findall("-?\d+\.?\d*e?-?\+?\d*", data[idx])
#    if len(numData) > 0:
      
#    print 'data = ', data, ' - numData of the first file = ', numData

#  exit()
#  a1 = a.splitlines(1)
#  b1 = b.splitlines(1)
#  print a1
#  print b1
#  a1 = file.readlines(); file.close()
#  b1 = file2.readlines(); file2.close()

#  print difflib.ndiff(a1, b1)
#  print '---zzzzzzzzzzzz---'

#  diff = difflib.ndiff(a1, b1)
#  print ''.join(diff),
#  exit()
#  for line in difflib.unified_diff(a1, b1):
#  for line in difflib.context_diff(a, b):
#    print line

#  exit()

#  a = file.readlines(); file.close()
#  b = file2.readlines(); file2.close()
#  print a
#  print b
#  print '---XXXXXXXXXXXXX---'

#  for line in difflib.ndiff(a, b):
#  for line in difflib.unified_diff(a, b):
#  for line in difflib.context_diff(a, b):
#    print line,

#  all = file.readlines();
#  print all
#  print all[4]

#  file.close(), file2.close()

  # catch integer, decimal, and scientific-formatted number (eg. 0.1234e-5) ...

  # formulate the need using modularized regular expression
  real_in = r"-?\d+"						# integer notation
  real_dn = r"-?\d+\.\d*|\d*\.\d+"		# decimal notation
  real_sn = r"-?\d\.?\d*[Ee][+\-]?\d+"	# scientific notation
#  real = "-?(" + real_sn + "|" + real_dn + "|" + real_in + ")"
  real = real_sn + "|" + real_dn + "|" + real_in
  print 'real regexp = ', real

  value = []
  idxAux = 0

  absErrorUB = 1e-09
  relErrorUB = 1e-05

  rname = string.replace(dname, 'diff.txt', 'onlyDiffs.txt')
  print 'ename = ', ename
  print 'aname = ', aname
  print 'dname = ', dname
#  print 'rname = ', rname
#  exit()
  file3 = open(dname, 'w')

  for idx in range(0, len(expData)):
    idxNumStr = 0
    for txt in expData[idx], actData[idx]:
#      print '\ntxt = ', txt

      # find all items satisfying the regular expression.

#      numStr = re.findall("-?\d+\.?\d*e?-?\+?\d*", txt)
#      numStr = re.findall("-?\d+\.?\d*e?[- | \+]*\d*", txt)
      numStr = re.findall(real, txt)
#      numStr = re.findall("-?\d\.?\d*[Ee][+\-]?\d+|-?\d+\.\d*|\d*\.\d+|-?\d+", txt)

#      print 'numStr = ', numStr, ' - len(numStr) = ', len(numStr), '%2 = ', idxNumStr%2

      # do something if at least one item exists:
      if len(numStr) > 0:

        # do something correlated to data from the first file:
        if idxNumStr%2 == 0:
          setExpData = set(expData[idx].split())
#          print 'original: ', expData[idx]
#          print 'set: ', setExpData

          # check whether the obtained item exists really on the file.
          for numItem in numStr:
            if numItem not in setExpData:
              delItem = numItem
              print '---> delete Item = ', delItem
              numStr.remove(delItem)

        # do something correlated to data from the second file:
        else:
          setActData = set(actData[idx].split())
#          print 'original: ', actData[idx]
#          print 'set: ', setActData
        
          # check whether the obtained item exists really on the file.
          for numItem in numStr:
            if numItem not in setActData:
              delItem = numItem
              print 'delete Item = ', delItem
              numStr.remove(delItem)

        # add all obtained, checked items.
#        print 'numStr = ', numStr
        value.append(numStr)

      # increment the index
      idxNumStr = idxNumStr + 1
       
##    if len(value) > 0:
##      print 'value = ', value
#      exit()

    # calculate the difference between two values and write it into a file
    if len(value) > 0:
#      print 'len(value) = ', len(value)
#      print 'idx = ', idx, 'idxAux = ', idxAux 
#      print value[idxAux], ' -> ', value[idxAux+1]

      ref = expData[idx]
#      print 'ref = ', ref, ' - refSplit = ', ref.split()

      if len(value[idxAux]) != len(value[idxAux+1]):
        print 'len(value[idxAux]) = ', len(value[idxAux]), ' -vs- len(value[idxAux+1]) = ', len(value[idxAux+1]) 
        exit()

 #     absErr, relErr = calcError( value[idxAux], value[idxAux+1], expData[idx] )
      absErr, relErr, idxField = calcError( value[idxAux], value[idxAux+1], ref )
      print '-'*100
#      print absErr
#      print relErr

      diffExists = False

      error = ''	  
      if relErr > relErrorUB:
        diffExists = True
        error = 'relative Error = ' + itos(relErr)
      elif absErr > absErrorUB:
        diffExists = True
        error = 'absolute Error = ' + itos(absErr)

      if diffExists:
        print 'at Field ', idxField, ': ', absErr, ' (abs)', relErr, ' (rel)\n'

        indexLineFromFile = getIdxLine(ename, expData[idx])
        print expData[idx],
        print actData[idx]

        # write into file.
        strLine = itos(indexLineFromFile)      
        print 'strLine = ', strLine
        file3.write('\nLine ' + strLine + ':\n')
        file3.write('+ ' + expData[idx])
        file3.write('- ' + actData[idx])
        textErr = 'at Field ' + itos(idxField) + ': ' + itos(error) + '\n'
        print 'textErr = ', textErr
        file3.write('* ' + textErr)
        
#        file3.write('at Field ', idxField, ': ', absErr, ' (abs)', relErr, ' (rel)\n')

      idxAux = idxAux + 2

#      print numStr
##  for idx in range(0, len(value), 2):
##    print value[idx], ' -> ', value[idx+1]
#    calcError( value[idx], value[idx+1] )
#    absErr, relErr = calcError( value[idx], value[idx+1], expData )
#    print absErr
#    print relErr

##    exit()

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

  # len(listValue1) = len(listValue2)
  for ij in range(0, len(listValue1)):

    value0 = string.atof(listValue0[ij])
    value1 = string.atof(listValue1[ij])
    #print 'val0 = ', value0, ' - val1 = ', value1  

    absolute = abs(value0 - value1)
    relative = absolute / max(abs(value0), abs(value1))

    #print 'abs = ', absolute, ' - rel = ', relative

#    if relative > relErrorUB:
#      print '-> RELATIVE ERROR = ', relative
#      relErr.append(relative)
#    else:
#      relErr.append(relErrorUB)

    relErr.append(relative)
    absErr.append(absolute)
	
#    if absolute > absErrorUB:
#      print '-> ABSOLUT ERROR = ', absolute
#      absErr.append(absolute)
#    else:
#      absErr.append(absErrorUB)

  relErrMax = max(relErr)
  absErrMax = max(absErr)
#  setRelErr = set(relErr)
  idxRelErr = relErr.index(relErrMax)
  idxAbsErr = absErr.index(absErrMax)
#  print 'ref = ', ref
  refSplit = ref.split()
#  print 'refSplit = ', refSplit
  setRef = set(refSplit)

  print 'absErr = ', absErr, ' -> max ', absErrMax, ' -> idx = ', idxAbsErr
  print 'relErr = ', relErr, ' -> max ', relErrMax, ' -> idx = ', idxRelErr
  print 'corr. listValue0 = ', listValue0[idxAbsErr] 

  if listValue0[idxAbsErr] in setRef:
#    print 'XXX'
    idxField = -1
    while idxField < idxAbsErr:
      print listValue0[idxAbsErr]
#      print idxField, ' 1 - ', idxAbsErr
      idxField = refSplit.index( listValue0[idxAbsErr], idxField+1, len(refSplit) )
#      print idxField, ' 2 - ', idxAbsErr
#      if idxField == 2 and idxAbsErr == 3: exit()

    print idxField, ' -> ', refSplit[idxField]

#  exit()

#  return absErr, relErr, idxField
  return absErrMax, relErrMax, idxField

    #diff.append( string.atof(number[0][ij]) - string.atof(number[1][ij]) )
    #numList.append(number[0][ij])

      # do something if at least one difference exists:
      #if len(diff) > 0:
      #  strDiffTmp = string.split(strSplit[0]) 
      #  setNumber = set(number[0])

        # create a line containing information about the differences:
      #  for id in range(0, len(strDiffTmp)):
      #    print 'id = ', strDiffTmp[id]

          # correlating to numeric value.
      #    if strDiffTmp[id] in setNumber:
      #      index = numList.index(strDiffTmp[id])
      #      print 'XXX - id = ', id, ' -> index: ', index
      #      diffVal = diff[index]
      #      print 'diffVal = ', diffVal

            # do something according to the type of difference values.
      #      if diffVal < 0:
      #        strDiffTmp[id] = '(' + itos(diff[index]) + ')'
      #      else:
      #        strDiffTmp[id] = itos(diff[index])

          # correlating to non-numeric value.
      #    else:
      #      print 'YYY'
      #      strDiffTmp[id] = '---'

      #  strDiff = "\t".join(strDiffTmp)
      #  print 'strDiff = ', strDiff

        # write into file.
      #  strLine = itos(idxLine)      
      #  file2.write('\nLine ' + strLine + ':\n')
      #  file2.write('+ ' + strMod[0] + '\n')
      #  file2.write('- ' + strMod[1])
      #  file2.write('d ' + strDiff + '\n')


# --- Modify CmpResult Function obtained by sdiff ---
#def takeImportantThings(aname, ename, tname):
def takeImportantThings_sdiff(tname, ename):

#  rname = string.replace(tname, 'diff.txt', 'onlyDiffs.txt')

  file = fopen(tname)
  file2 = open(ename, 'w')
  if not file and not file2:
    return 0

  all = file.readlines();
  print all
#  print all[4]

  idxLine = 0

  # check line per line whether the character indicating differences, '|', exists.
  # the character '|' separates line of the first file from that of the second one. 
  for str in all:
    print 'str ', str

	# do a work on the differences :
    if string.find(str, '|') > -1:

      # because of the structure, split the line into two new lines based on the character '|'.
      strSplit = string.split(str, '|')
      print 'strSplit: ', strSplit

      number = []
      strMod = []

      # remove the character '\t' coming as the first one.
      for i in range(0, len(strSplit)):
        print 'kkk = ', strSplit[i]
        if re.match("\t", strSplit[i]):
          txt = string.replace(strSplit[i], '\t', '', 1)
        else:
          txt = strSplit[i]
        strMod.append(txt)

      print 'strMod: ', strMod

      # do something for each line
      for txt in strMod:

        # catching integer, decimal, and scientific-formatted number (eg. 0.1234e-5) ...
        numStr = re.findall("-?\d+\.?\d*e?-?\+?\d*", txt)
        # ... and save them into a list.
        number.append(numStr)
        print '**', numStr, '***', number[0]

      # calculate the numerical differences.
      # number[0] = number[1] by the list constructor.
      diff = []
      numList = []
      # absError = |A - B|
      absError = 1e-09
      # relError = absError / min (|A|, |B|)
      relError = 1e-05

      for ij in range(0, len(number[0])):

        value0 = string.atof(number[0][ij])
        value1 = string.atof(number[1][ij])
        absolute = abs(value0 - value1)
        relative = absolute / min(abs(value0), abs(value1))

        print 'val0 = ', value0, ' - val1 = ', value1  
        print 'abs = ', absolute, ' - rel = ', relative

        if relative > relError:
          print '-> RELATIVE ERROR = ', relative

        if absolute > absError:
          print '-> ABSOLUT ERROR = ', absolute

        diff.append( string.atof(number[0][ij]) - string.atof(number[1][ij]) )
        numList.append(number[0][ij])

      # do something if at least one difference exists:
      if len(diff) > 0:
        strDiffTmp = string.split(strSplit[0]) 
        setNumber = set(number[0])

        # create a line containing information about the differences:
        for id in range(0, len(strDiffTmp)):
          print 'id = ', strDiffTmp[id]

          # correlating to numeric value.
          if strDiffTmp[id] in setNumber:
            index = numList.index(strDiffTmp[id])
            print 'XXX - id = ', id, ' -> index: ', index
            diffVal = diff[index]
            print 'diffVal = ', diffVal

            # do something according to the type of difference values.
            if diffVal < 0:
              strDiffTmp[id] = '(' + itos(diff[index]) + ')'
            else:
              strDiffTmp[id] = itos(diff[index])

          # correlating to non-numeric value.
          else:
            print 'YYY'
            strDiffTmp[id] = '---'

        strDiff = "\t".join(strDiffTmp)
        print 'strDiff = ', strDiff

        # write into file.
        strLine = itos(idxLine)      
        file2.write('\nLine ' + strLine + ':\n')
        file2.write('+ ' + strMod[0] + '\n')
        file2.write('- ' + strMod[1])
        file2.write('d ' + strDiff + '\n')

    # index of line
    idxLine = idxLine + 1

  file.close(), file2.close()
#  exit()

# --- Main Function ---

def main(args):  
#  import getopt
#  try:
#    opts, args = getopt.getopt(args, "qr:")
#  except getopt.error, detail:
#    return fail(str(detail))

  if len(args) < 5:
    return fail("Need 5 args: <exp_result> <actual_result> <cmp_result> <report> <testName>")

  print len(args), args

  expResult, actResult, tmpResult, report, testName = args
#  noisy = 1  
#  if noisy:
#    print '-:', f1name
#    print '+:', f2name

#  return fcompare(expResult, actResult)

  print '\nexp: ', expResult, '\nact: ', actResult, '\ntmpResult: ', tmpResult, '\nreport: ', report, '\ntestName', testName

#  result = string.replace( os.path.dirname(expResult), 'References', 'report.txt') 
#  print result
#  exit()
  takeImportantThings_python(expResult, actResult, tmpResult)
#  exit()

#  os.system('diff ' + actResult + ' ' + expResult + ' > ' + cmpResult)
##  os.system('sdiff ' + actResult + ' ' + expResult + ' > ' + tmpResult)
#  os.system('python ndiff.py ' + actResult + ' ' + expResult + ' > ' + tmpResult)

##  endResult = string.replace(tmpResult, 'diff.txt', 'onlyDiffs.txt')
##  print 'tmpResult = ', tmpResult, ' - endResult = ', endResult
##  exit()
#  return fModCmpResult(cmpResult)
#  return takeImportantThings(actResult, expResult, cmpResult)
##  takeImportantThings_sdiff(tmpResult, endResult)
#  takeImportantThings_python(tmpResult, endResult)

  endResult = tmpResult
  size = os.path.getsize(endResult)
#  print 'file size ', tmpResult, ' = ', size
#  print 'file size ', endResult, ' = ', size

  # create Report File
  repFile = open(report, 'a') 

  # there exists difference value(s)
  if size > 0:

    # take info
    file = open(endResult, 'r')
    lines = file.readlines()
    file.close()

    # insert head
    newLine = "Legends:\n"
    newLineAct = "+ : " + actResult + "\n"
    newLineExp = "- : " + expResult + "\n" 
#    newLineDif = "d : " + tmpResult + "\n"
    newLineDif = "* : absolute/relative error\n"
    maxLength = max(len(newLineAct), len(newLineExp), len(newLineDif))
    newLineSep = "-" * maxLength + "\n"

    head = newLine + newLineAct + newLineExp + newLineDif + newLineSep
#    print 'head:\n', head

    lines[0:0] = [head]

    # re-write
    file = open(endResult, 'w')
    file.writelines( lines )
    file.close()

    repFile.write(testName + '\t...\tDifferent\n')
  else:  
    repFile.write(testName + '\t...\tOK\n')

  repFile.close()

# Remove unneccessary files
#  os.remove(tmpResult)

  print 'ENDE'


if __name__ == '__main__':
  print '--- Running NumDiff.py ---'
  args = sys.argv[1:]
  main(args)  
