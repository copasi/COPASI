/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/ABiochem/ABiochem.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:43 $
   End CVS Header */

/**
 *  ABiochem
 *
 *  A system to construct random biochemical networks 
 *  with various topologies and kinetics
 *
 *  writen by Pedro Mendes, September 2002
 *  Biochemical Networks Modeling Group
 *  Virginia Bioinformatics Institute
 */

#include "copasi.h"
#include <stdio.h>
#include "model/model.h"
#include "ABiochem/CGene.h"

/**
 *  Creates a gene network using a ring topology
 *
 *  @param C_INT32 n the total number of genes
 *  @param C_INT32 k the total number of links
 *  @param C_FLOAT64 p the probability that a link is positive
 *  @param C_FLOAT64 r the probability of rewiring a gene
 *  @param C_FLOAT64 coopval the value for Hill coefficients
 *  @param C_FLOAT64 rateval the value for rate constants
 *  @param C_FLOAT64 constval the value for inh/act constants
 *  @param "CCopasiVector < CGene > &" gene a vector of genes (the network)
 *  @param "char *" comments a string to write comments on the network
 */

void MakeGeneNetwork(C_INT32 n,
                     C_INT32 k,
                     C_FLOAT64 p,
                     C_FLOAT64 r,
                     C_FLOAT64 coopval,
                     C_FLOAT64 rateval,
                     C_FLOAT64 constval,
                     CCopasiVector < CGene > &gene,
                     char *comments);
