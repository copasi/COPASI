/**
 *  ABiochem  -  wattstrog
 *
 *  A program to generate random gene networks 
 *  following an Watts-Stroganz small-world topology
 *  
 *  writen by Pedro Mendes, September 2002
 *  Biochemical Networks Modeling Group
 *  Virginia Bioinformatics Institute
 */

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include <stdio.h>
#include "model/model.h"
#include "ABiochem/CGene.h"

extern "C" void r250_init(int seed);
extern "C" unsigned int r250n(unsigned n);
extern "C" double dr250();

using namespace std;

/**
 *  Creates a gene network using a ring topology
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
                      char *comments)
{
  C_INT32 i, j, l, l2, modf, links, links2;
  char gn[1024];

  // links accounts for the number of links per gene
  links = k / n;
  links2 = links / 2;
  // create and name genes
  gene.resize(n);
  for (i = 0; i < n; i++)
    {
      sprintf(gn, "G%ld", i + 1);
      gene[i]->setName(gn);
    }
  // create a regular 1-dimensional grid
  for (i = 0; i < n; i++) // each gene
    {
      for (j = 1; j <= links2; j++) // each link (one link each side)
        {
          l = i + j;
          if (l >= n)
            l %= n;
          l2 = i - j;
          if (l2 < 0)
            l2 = n + l2;
          // add the two links, i->l i->l2
          if (dr250() < p)
            modf = 1;
          else
            modf = 0;
          gene[i]->addModifier(gene[l], l, modf, 1.0e-3, 1.0);
          if (dr250() < p)
            modf = 1;
          else
            modf = 0;
          gene[i]->addModifier(gene[l2], l2, modf, 1.0e-3, 1.0);
        }
      gene[i]->setRate(1.0);
      gene[i]->setDegradationRate(1.0);
    }
  sprintf(comments, "Model of a gene network on a regular 1D grid (ring)\nwith %ld genes and %ld input connections each.\n\nCreated automatically by the A-Biochem system", n, 2*links2);
}
