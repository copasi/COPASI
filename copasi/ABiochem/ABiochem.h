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
  *  Create a gene network 
  *  @argument C_INT32 n the total number of genes
  *  @argument C_INT32 k the total number of links
  *  @argument C_FLOAT64 p the probability that a link is an activation
  *  @argument "CCopasiVector < CGene > &" gene the gene network
  *  @argument "char *" comments a character array to contain comments
  */
void MakeGeneNetwork(C_INT32 n, C_INT32 k, C_FLOAT64 p, CCopasiVector < CGene > &gene, char *comments);
