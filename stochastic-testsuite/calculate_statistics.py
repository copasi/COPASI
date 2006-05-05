#!/usr/bin/python

import sys
import string
import math

if(len(sys.argv)!=6):
    print "Wrong number of arguments."
    sys.exit(1)

INPUTFILE=sys.argv[1]

MEAN_OUTFILE=sys.argv[2]

SD_OUTFILE=sys.argv[3]

NUM_STEPS=int(sys.argv[4])

NUM_REPEATS=int(sys.argv[5])

INPUT=file(INPUTFILE,"r").readlines()

if(len(INPUT) != (NUM_REPEATS * (NUM_STEPS + 2) + 1)):
    print "Wrong number of data points."
    sys.exit(1)

DATA=[]
LINENUMBER=1
NUMCOLUMNS=len(string.split(INPUT[1]))
MEAN=[]

HEADER=INPUT[0]

for X in range(0,NUM_STEPS+1):
    MEAN.append([])
    for Y in range(0,NUMCOLUMNS - 1):
        MEAN[X].append(0)

for X in range(0,NUM_REPEATS):
   SET=[]
   for Y in range(0, NUM_STEPS+1):
     LINE=INPUT[LINENUMBER]
     COLUMNS=string.split(LINE)
     if(len(COLUMNS)!=NUMCOLUMNS):
        print "Wrong number of elements on  line %d"%(LINENUMBER)
        sys.exit(1)
     ROW=[]
     for Z in range(0,len(COLUMNS)-1):
        v=float(COLUMNS[Z+1])
        ROW.append(v)
        MEAN[Y][Z]=MEAN[Y][Z]+v
     SET.append(ROW)   
     LINENUMBER=LINENUMBER+1
   DATA.append(SET)  
   LINENUMBER=LINENUMBER+1  # skip the empty line

MEANOUT=file(MEAN_OUTFILE,"w")   
MEANOUT.write(HEADER)
for X in range(0,NUM_STEPS+1):
    line=string.join([str(X)],",")
    for Y in range(0,NUMCOLUMNS-1):
        MEAN[X][Y]=MEAN[X][Y]/NUM_REPEATS
        line=string.join([line,str(MEAN[X][Y])],",")
    line=line+"\n"
    MEANOUT.write(line)
MEANOUT.close()    

SD=[]
for X in range(0,NUM_STEPS+1):
    SD.append([])
    for Y in range(0,NUMCOLUMNS-1):
        SD[X].append(0)


for X in range(0,NUM_REPEATS):
    for Y in range(0,NUM_STEPS+1):
        for Z in range(0,NUMCOLUMNS-1):
            SD[Y][Z]=SD[Y][Z]+math.pow((DATA[X][Y][Z]-MEAN[Y][Z]),2)


SDOUT=file(SD_OUTFILE,"w")   
SDOUT.write(HEADER)
for X in range(0,NUM_STEPS+1):
    line=string.join([str(X)],",")
    for Y in range(0,NUMCOLUMNS-1):
        SD[X][Y]=math.sqrt(SD[X][Y]/NUM_REPEATS)
        line=string.join([line,str(SD[X][Y])],",")
    line=line+"\n"
    SDOUT.write(line)
SDOUT.close()    

    
