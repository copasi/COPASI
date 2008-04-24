# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/unittests/scripts/rewriteXML.py,v $ 
#   $Revision: 1.1 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2008/01/28 14:33:50 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

#!/usr/bin/env python

import sys
import pdb
from xml.dom.ext.reader import Sax2
from xml.dom.ext import Print

if(len(sys.argv)!=3):
   print "Usage: rewriteXML SBMLFILE OUTFILE"
   sys.exit(1)
FILENAME=sys.argv[1]
OUTFILE=sys.argv[2]
reader=Sax2.Reader()
doc=reader.fromStream(open(FILENAME))
outfile=open(OUTFILE,"w")
Print(doc,outfile)



