/**
 *  ABiochem  -  Erdos
 *
 *  A program to generate random gene networks 
 *  following an Erdos-Renyi topology
 *  
 *  writen by Pedro Mendes, September 2002
 *  Biochemical Networks Modeling Group
 *  Virginia Bioinformatics Institute
 */

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include <stdio.h>
#include "utilities/CMethodParameter.h"
#include "model/model.h"
#include "ABiochem/CGene.h"

extern "C" void r250_init(int seed);
extern "C" unsigned int r250n(unsigned n);
extern "C" double dr250();

using namespace std;

/**
 *  Creates a gene network using a Erdos-Renyi topology
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
                     char *comments)
{
  C_INT32 i, j, l, m, modf;
  char gn[1024];
  C_INT32 ipg; // number of inputs per gene
  C_INT32 rem; // remainder of inputs extra (total%n)

  ipg = k / n;
  rem = k % n;
  // create and name genes
  gene.resize(n);
  for (i = 0; i < n; i++)
    {
      sprintf(gn, "G%ld", i + 1);
      gene[i]->setName(gn);
    }
  // add all the regular number of links
  for (i = 0; i < n; i++)
    {
      for (j = 0; j < ipg; j++)
        {
          for (l = -1; l < 0;)
            {
              l = r250n(n);
              for (m = 0; m < gene[i]->getModifierNumber(); m++)
                if (gene[l] == gene[i]->getModifier(m))
                  {
                    l = -1;
                    break;
                  }
            }
          if (dr250() < p)
            modf = 1;
          else
            modf = 0;
          // gene[i]->addModifier(gene[l], r250n(2), dr250()*100.0 + 1e-5, dr250()*6.0 + 0.1);
          gene[i]->addModifier(gene[l], l, modf, constval, coopval);
        }
      // gene[i]->setRate(dr250()*9.99 + 1e-2);
      // gene[i]->setDegradationRate(gene[i]->getRate()*(dr250()*5.83 + 0.17));
      gene[i]->setRate(rateval);
      gene[i]->setDegradationRate(rateval);
    }
  // add the remainder of links to make up k
  for (i = 0; i < rem; i++)
    {
      j = r250n(n);
      for (l = -1; l < 0;)
        {
          l = r250n(n);
          for (m = 0; m < gene[j]->getModifierNumber(); m++)
            if (gene[l] == gene[j]->getModifier(m))
              {
                l = -1;
                break;
              }
        }
      if (dr250() < p)
        modf = 1;
      else
        modf = 0;
      // gene[i]->addModifier(gene[l], r250n(2), dr250()*100.0 + 1e-5, dr250()*6.0 + 0.1);
      gene[j]->addModifier(gene[l], l, modf, constval, rateval);
    }
  sprintf(comments, "Model of a random gene network following a Erdos-Renyi topology\nwith %ld genes and %ld total input connections.\n\nCreated automatically by the A-Biochem system", n, k);
}
