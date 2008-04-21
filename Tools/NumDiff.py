# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/Tools/NumDiff.py,v $ 
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

# NumDiff, a python script for writing numerical differences between two files

# Author: willy
# Date: 25.02.2008

import os, sys, string, difflib

# --- Failure Message Function ---

def fail(msg):    out = sys.stderr.write    out('\nERROR MESSAGE: ' + msg + "\n\n")    return 0

# --- Open File Function ---

# Open a file & return the file object; 
# gripe and return 0 if it couldn't be openeddef fopen(fname):  try:    return open(fname, 'U')  except IOError, detail:    return fail("Couldn't open " + fname + ": " + str(detail))

# --- Modify CmpResult Function ---
def fModCmpResult(fname):
  file = fopen(fname)  if not file:    return 0

  modResult = []
#  a = file.readlines(); file.close()
  a = file.read().split(); file.close()
  print a
#  for ch in a:
  idx = 0
#  global listIdxXYcXY, listIdxXcX, listIdxGreater, listIdxSmaller, listIdxLines
  listIdxXYcXY = []
  listIdxXcX = []
  listIdxGreater = []
  listIdxSmaller = []
  listIdxLines = []

  while idx < len(a):
    ch = a[idx]
    if ch.find('c') == 3:    # eq. 2,4c2,4 means line 2-4 of one file differs from line 2-4 of another
      print 'index of x1,y1cx2,y2 -> ', idx
      listIdxXYcXY.append(idx)

#      lineNumber = string.atoi(ch[2]) - string.atoi(ch[0]) + 1
      
#      idx2 = 0
#      for idx2 in range (0, lineNumber): 
#        modResult.append( str(string.atoi(ch[0]) + idx2) + 'c' + str(string.atoi(ch[4]) + idx2) )
#        idx = idx + 1
#        ch2 = a[idx]
#        if ( ch2.find         
#        modResult.append(ch2) 
#      print modResult

#      print ch[0], ch[2]
#      lineNumber = string.atoi(ch[2]) - string.atoi(ch[0]) + 1
#      print lineNumber
#      idx
#      ch = a[idx]
#      while ch.find('c') != -1:
#       print '-- ', ch 
#        break
#      print '## ', ch
#      idxStart = idx+2  # '+2' for 'xcx' and '<'      
      
#      idxFinish = idxStart + 

#      print a[idx+2:lineNumber]  
#      for i in range[a[], lineNumber]:
#        print i
    elif ch.find('c') == 1:  # eq. 7c7
      print 'index of xcx -> ', idx
      listIdxXcX.append(idx)

    elif ch.find('>') != -1:  # eq. 7c7
      print 'index of < -> ', idx
      listIdxGreater.append(idx)

    elif ch.find('<') != -1:  # eq. 7c7
      print 'index of > -> ', idx
      listIdxSmaller.append(idx)

    elif ch.find('---') != -1:  # eq. 7c7
      print 'index of --- -> ', idx
      listIdxLines.append(idx)

#    elif ch in string.digits:
#      print ch, ' -> DIGITS'
    else:
      if ch not in ('<', '>'):  # numerical values
        print ch, ' -> DIGITS'

    print ch.find('c')
    idx = idx+1

  print listIdxXYcXY, listIdxXcX, listIdxSmaller, listIdxGreater, listIdxLines

  if len(listIdxSmaller) != len(listIdxGreater):
    fail('len(listIdxSmaller) (=' + str(len(listIdxSmaller)) + ') != len(listIdxGreater) (=' + len(listIdxGreater) + ')');

  print '*** ', len(a)

  for idx in range (0, len(a)):
    if idx in listIdxXYcXY:
      print 'A',
    elif idx in listIdxXcX:
      print 'B', 
    elif idx in listIdxSmaller:
      print 'C', 
    elif idx in listIdxGreater:
      print 'D',
    elif idx in listIdxLines:
      print 'E',
    else:
      print 'x',

  for idx in range (0, len(a)):
    if idx in listIdxXYcXY:
      ch = a[idx]
      print 'A idx: ', idx
      lineNumber = string.atoi(ch[2]) - string.atoi(ch[0]) + 1
      for idx2 in range (0, lineNumber):     
        modResult.append( str(string.atoi(ch[0]) + idx2) + 'c' + str(string.atoi(ch[4]) + idx2) )

        diffVals = []

        print '---'
        idx = listIdxSmaller[idx2]          # the first '<'

        print 'B idx: ', idx
        modResult.append( a[idx] )
        while idx+1 not in listIdxSmaller:  # do it again until the next '<'
          if idx+1 in listIdxLines: break   # or '---' as well
          idx = idx+1
          print 'C idx: ', idx
          modResult.append( a[idx] )
          if a[idx] not in ('<'):
            diffVals.append( 0 - string.atof(a[idx]) )
        
        modResult.append( '---' )           # it will be change later
        
        print '---'
        idx = listIdxGreater[idx2]

        print 'D idx: ', idx                # the first '>'
        modResult.append( a[idx] )
        idx3 = 0
        while idx+1 not in listIdxGreater:  # do it again until the next '>'
          if idx+1 in listIdxXcX: break     # or 'xcx',
          if idx+1 in listIdxXYcXY: break   # or 'xycxy',
          if idx+1 == len(a): break         # or end
          idx = idx+1
          print 'E idx: ', idx
          modResult.append( a[idx] )
          if a[idx] not in ('>'):
            diffVals[idx3] = diffVals[idx3] + string.atof(a[idx])
          idx3 = idx3 + 1

        values = ''
        for val in diffVals:
          values = values + '(' + str(val) + ')'
        print '\n', modResult
        modResult[modResult.index('---')] = values

        print 'idx2: ', idx2

      print lineNumber, idx
  
      print '\n', modResult  

    elif idx in listIdxXcX:
      print 'F idx: ', idx 
      idx2 = idx  
      diffVals = []             
      modResult.append( a[idx] )
      while idx+1 < len(a):
        if idx+1 in listIdxXYcXY: break  # neither 'xycxy'
        if idx+1 in listIdxXcX: break    # nor 'xcx'
        idx = idx+1
        print 'G idx: ', idx
        modResult.append( a[idx] )

      diffPos = listIdxSmaller[1] - listIdxSmaller[0]  # same for all, also in listIdxGreater
      for idx3 in range(0, diffPos-1):
        if idx2+2+idx3 in listIdxLines: break  # exclude '---'
        print idx2, idx3, idx2+2+idx3, idx2+7+idx3
        print a[idx2+2+idx3], a[idx2+7+idx3]
        diffVals.append( string.atof(a[idx2+2+idx3]) - string.atof(a[idx2+7+idx3]) )  # based on the data structure

      values = ''
      for val in diffVals:
        values = values + '(' + str(val) + ')'
      print '\n', modResult
      modResult[modResult.index('---')] = values

      print idx
      print '\n', modResult 
      
    else:
      pass

  print '\n\n', modResult

  print fname
  file = open(fname, 'w')#  if not file:#    return 0

  for valueStr in modResult:
    print valueStr
    if (valueStr.find('c') != -1): 
      file.write('\n---\n' + valueStr + ' \n')
    elif (valueStr.find('(') != -1):
      file.write('\n' + valueStr + ' \n')
    else:
      file.write(valueStr + ' ')

  file.close()
  exit()


# --- Compare Function ---

# Open two files & spray the diff to stdout; return false iff a problemdef fcompare(f1name, f2name):    f1 = fopen(f1name)    f2 = fopen(f2name)    if not f1 or not f2:      return 0

    a = f1.readlines(); f1.close()
    b = f2.readlines(); f2.close()
#    a = f1.read().split(); f1.close()
#    b = f2.read().split(); f2.close()
#    import string

#    idx = 0
#    while idx < len(a):
#      if string.lower(a[idx]) == string.upper(a[idx]):  # trick to avoid letters
#        aFloat = string.atof(a[idx])
#        bFloat = string.atof(b[idx])
#        print aFloat, bFloat, aFloat - bFloat
#      idx = idx+1

    lsplit_1 = lsplit_2 = lsplit_3 = []
    
    for line in difflib.ndiff(a, b):#    for line in difflib.Differ().compare(a, b):

      if line.find('-') != -1:    # belongs to the 1st file
        lsplit_1 = line.split()
        print lsplit_1
        lsplit_1.remove('-')
        print lsplit_1

      if line.find('+') != -1 and line.find('?') == -1:  # belongs to 2nd
        lsplit_2 = line.split()
        print lsplit_2
        lsplit_2.remove('+')
        print lsplit_2

    print len(lsplit_1), len(lsplit_2)

    idx = 0
    while idx < len(lsplit_1):
      print lsplit_1[idx], lsplit_2[idx]
      lsplit_3.append(string.atof(lsplit_1[idx]) - string.atof(lsplit_2[idx]))
      idx = idx+1
    print lsplit_3
    return 1

# --- Main Function ---

def main(args):  
#  import getopt#  try:#    opts, args = getopt.getopt(args, "qr:")#  except getopt.error, detail:#    return fail(str(detail))

  if len(args) < 3:    return fail("Need 3 args: exp_result actual_result cmp_result")

  print len(args), args

  expResult, actResult, cmpResult = args#  noisy = 1  
#  if noisy:#    print '-:', f1name#    print '+:', f2name

#  return fcompare(expResult, actResult)

  os.system('diff ' + actResult + ' ' + expResult + ' > ' + cmpResult)

  return fModCmpResult(cmpResult)

if __name__ == '__main__':
  print '--- Running NumDiff.py ---'
  args = sys.argv[1:]
  main(args)  
