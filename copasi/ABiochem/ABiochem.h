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

/*
 *  Create a gene network 
 *
 *  @param C_INT32 n the total number of genes
 *  @param C_INT32 k the total number of links
 *  @param C_FLOAT64 p the probability that a link is positive
 *  @param C_FLOAT64 r the probability of rewiring a gene
 *  @param "CCopasiVector < CGene > &" gene a vector of genes (the network)
 *  @param "char *" comments a string to write comments on the network
 */

void MakeGeneNetwork(C_INT32 n,
                      C_INT32 k,
                      C_FLOAT64 p,
                      C_FLOAT64 r,
                      CCopasiVector < CGene > &gene,
                      char *comments);
