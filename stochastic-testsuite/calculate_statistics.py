#!/usr/bin/python

import sys
import string
import math
import array

if(len(sys.argv)!=6):
    print "Wrong number of arguments."
    sys.exit(1)

# The separator for the input file.
SEPARATOR=","

INPUTFILE=sys.argv[1]

MEAN_OUTFILE=sys.argv[2]

SD_OUTFILE=sys.argv[3]

NUM_STEPS=int(sys.argv[4])

NUM_REPEATS=int(sys.argv[5])

INPUT=file(INPUTFILE,"r").readlines()

if(len(INPUT) != (NUM_REPEATS * (NUM_STEPS + 2) + 1)):
    print "Wrong number of data points."
    print "Found:     %d"%len(INPUT)
    print "Expecting: %d"%(NUM_REPEATS * (NUM_STEPS + 2) + 1)
    sys.exit(1)

NUMCOLUMNS=len(string.split(INPUT[1], SEPARATOR))
HEADER=string.join(string.split(INPUT[0], SEPARATOR), ",")

MEANOUT=file(MEAN_OUTFILE,"w")
MEANOUT.write(HEADER)

SDOUT=file(SD_OUTFILE,"w")   
SDOUT.write(HEADER)

# Allocate the memory mean and sd just for 1 row
MEAN=[0.0] * NUMCOLUMNS
SD=[0.0] * NUMCOLUMNS

# To save memory we process the data by rows
for X in range(0,NUM_STEPS+1):

    # Set Mean and SD to 0;
    for Y in range(0,NUMCOLUMNS - 1):
        MEAN[Y]=0
        SD[Y]=0

    for Z in range(0,NUM_REPEATS - 1):
        LINE=INPUT[X + 1 + Z * (NUM_STEPS + 2)]

        COLUMNS=string.split(LINE, SEPARATOR)
        if(len(COLUMNS)!=NUMCOLUMNS):
            print "Wrong number of elements on  line %d"%(X + 1 + Z * (NUM_STEPS + 3))
            sys.exit(1)

        for Y in range(0,len(COLUMNS)-1):
            v=float(COLUMNS[Y+1])
            DELTA=v-MEAN[Y]
            MEAN[Y]=MEAN[Y]+DELTA/(Z+1)

            # This uses the new mean, i.e., not DELTA * DELTA
            SD[Y]=SD[Y]+DELTA*(v-MEAN[Y])
    
    for Y in range(0,NUMCOLUMNS-1):
        COLUMNS[Y+1] = str(MEAN[Y])

    line = string.join(COLUMNS, ",") + "\n"
    MEANOUT.write(line)

    for Y in range(0,NUMCOLUMNS-1):
        COLUMNS[Y+1] = str(math.sqrt(SD[Y]/NUM_REPEATS))

    line = string.join(COLUMNS, ",") + "\n"
    SDOUT.write(line)

MEANOUT.close()    
SDOUT.close()
