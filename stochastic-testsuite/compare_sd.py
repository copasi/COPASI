import sys
import math
import string

SD_FILE=sys.argv[1]
REFERENCE_SD_FILE=sys.argv[2]
REPEATS=sys.argv[3]
OUTFILE=sys.argv[4]

SD=file(SD,"r").readlines()
REFERENCE_SD=file(REFERENCE_SD_FILE,"r").readlines()

if(len(SD) != len(REFERENCE_SD)):
    print "Error. The input files don't have the same number of lines."
    sys.exit(1)

NUMCOLUMNS=len(string.split(SD[1],","))
OUT=file(OUTFILE,"w")
OUT.write(SD[0])
for X in range(1,len(SD)):
    REF_SD_COLS=string.split(REFERENCE_SD,",")[1:]
    SD_COLS=string.split(SD,",")[1:]
    if(len(SD_COLS) != len(REF_SD_COLS)):
        print "Error. Number of columns differs between files at line %d"%(X)
        OUT.close()
        sys.exit(1)
    RESULT=str(X-1)+","
    for Y in range(1,NUMCOLUMNS):
       v=(math.power(float(SD_COLS[Y]),2)/math.power(float(REF_SD_COLS[Y]),2)-1.0)*math.sqrt(REPEATS/2.0)
       if(math.abs(v)>=5.0):
          print "Warning. Value to hight at %s line %d."%(MEAN_FILE,X) 
       RESULT=string.join([RESULT,str(v)],",")
    RESULT=RESULT+"\n"
    OUT.write(RESULT)   
OUT.close()    
