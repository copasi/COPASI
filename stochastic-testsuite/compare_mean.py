#!/usr/bin/python

import sys
import math
import string

MEAN_FILE=sys.argv[1]
REFERENCE_MEAN_FILE=sys.argv[2]
REFERENCE_SD_FILE=sys.argv[3]
REPEATS=float(sys.argv[4])
OUTFILE=sys.argv[5]

MEAN=file(MEAN_FILE,"r").readlines()
REFERENCE_MEAN=file(REFERENCE_MEAN_FILE,"r").readlines()
REFERENCE_SD=file(REFERENCE_SD_FILE,"r").readlines()

EXIT_STATUS=0

if(len(REFERENCE_MEAN)!=len(REFERENCE_SD) or len(MEAN) != len(REFERENCE_MEAN)):
    print "ERROR: The input files don't have the same number of lines."
    sys.exit(1)

NUMCOLUMNS=len(string.split(MEAN[1],","))
OUT=file(OUTFILE,"w")
OUT.write(MEAN[0])
for X in range(2,len(MEAN)):
    REF_MEAN_COLS=string.split(REFERENCE_MEAN[X],",")[1:]
    REF_SD_COLS=string.split(REFERENCE_SD[X],",")[1:]
    MEAN_COLS=string.split(MEAN[X],",")[1:]
    if(len(REF_MEAN_COLS)!=len(REF_SD_COLS) or len(MEAN_COLS) != len(REF_MEAN_COLS)):
        print "ERROR: Number of columns differs between files at line",Y
        OUT.close()
        sys.exit(1)
    RESULT=str(X-1)+","
    for Y in range(0,NUMCOLUMNS-1):
       v=0.0
       if(REF_SD_COLS[Y]!=0.0):
         try:
           v=((float(MEAN_COLS[Y])-float(REF_MEAN_COLS[Y]))/float(REF_SD_COLS[Y]))*math.sqrt(REPEATS) 
         except:
           print "EXCEPTION: MEAN_COLS[Y]=%f REF_MEAN_COLS[Y]=%f REF_SD_COLS[Y]=%f REPEATS=%d"%(MEAN_COLS[Y],REF_MEAN_COLS[Y],REF_SD_COLS[Y],REPEATS)
       if(math.fabs(v)>=3.0):
          print "ERROR: Value of %f to high at %s line %d."%(v,MEAN_FILE,X) 
          EXIT_STATUS=1
       RESULT=string.join([RESULT,str(v)],",")
    RESULT=RESULT+"\n"
    OUT.write(RESULT)   
OUT.close()    
sys.exit(EXIT_STATUS)
