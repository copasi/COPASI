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
 *  Creates a gene network using a small-world (watts-strogatz) topology
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
  C_INT32 i, j, l, l2, m, modf, links, links2;
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
          gene[i]->addModifier(gene[l], modf, 1.0, 1.0);
          if (dr250() < p)
            modf = 1;
          else
            modf = 0;
          gene[i]->addModifier(gene[l2], modf, 1.0, 1.0);
        }
      gene[i]->setRate(1.0);
      gene[i]->setDegradationRate(1.0);
    }
  // now rewire the grid
  for (i = 1; i <= links2; i++) // each link (one link each side)
    {
      for (j = 0; j < n; j++) // each gene
        {
          l = j + i;
          if (l >= n)
            l %= n;
          l2 = j - i;
          if (l2 < 0)
            l2 = n + l2;
          // check if we rewire the l link
          if (dr250() < r)
            {
              // store the modifier type
              modf = 0;
              for (m = 0; m < gene[i]->getModifierNumber(); m++)
                if (gene[l] == gene[i]->getModifier(m))
                  modf = gene[i]->getModifierType(m);
              // remove the previous link
              gene[i]->removeModifier(gene[l]);
              // find a new link (that is not yet there)
              for (l = -1; l < 0; )
                {
                  l = r250n(n);
                  for (m = 0; m < gene[i]->getModifierNumber(); m++)
                    if (gene[l] == gene[i]->getModifier(m))
                      {
                        l = -1;
                        break;
                      }
                }
              // add the new link
              gene[i]->addModifier(gene[l], modf, 1.0, 1.0);
            }
          // check if we rewire the l2 link
          if (dr250() < r)
            {
              // store the modifier type
              modf = 0;
              for (m = 0; m < gene[i]->getModifierNumber(); m++)
                if (gene[l2] == gene[i]->getModifier(m))
                  modf = gene[i]->getModifierType(m);
              // remove the previous link
              gene[i]->removeModifier(gene[l2]);
              // find a new link (that is not yet there)
              for (l2 = -1; l2 < 0; )
                {
                  l2 = r250n(n);
                  for (m = 0; m < gene[i]->getModifierNumber(); m++)
                    if (gene[l2] == gene[i]->getModifier(m))
                      {
                        l2 = -1;
                        break;
                      }
                }
              // add the new link
              gene[i]->addModifier(gene[l2], modf, 1.0, 1.0);
            }
        }
    }
  sprintf(comments, "Model of a small-worls gene network using the Watts-Strogatz algorithm\nwith %ld genes and %ld input connections each\nand %lg probability of rewiring.\n\nCreated automatically by the A-Biochem system", n, 2*links2, r);
}
