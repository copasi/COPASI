/**
 *  Erdos
 *
 *  Program to generate random gene networks following an 
 *  Erdos Renyi topology
 *  
 */

#include "copasi.h"
#include <stdio.h>
#include "model/model.h"
#include "ABiochem/CGene.h"

extern "C" void r250_init(int seed);
extern "C" unsigned int r250n(unsigned n);
extern "C" double dr250();

using namespace std;

void Erdos(C_INT32 n, C_INT32 k, C_FLOAT64 p, CCopasiVector < CGene > &gene, char *comments)
{
  C_INT32 i, j, l, m, modf;
  char gn[1024];

  // create and name genes
  gene.resize(n);
  for (i = 0; i < n; i++)
    {
      sprintf(gn, "G%ld", i + 1);
      gene[i]->setName(gn);
    }
  for (i = 0; i < n; i++)
    {
      for (j = 0; j < k; j++)
        {
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
          if (dr250() < p)
            modf = 1;
          else
            modf = 0;
          // gene[i]->addModifier(gene[l], r250n(2), dr250()*100.0 + 1e-5, dr250()*6.0 + 0.1);
          gene[i]->addModifier(gene[l], modf, 1.0, 1.0);
        }
      // gene[i]->setRate(dr250()*9.99 + 1e-2);
      // gene[i]->setDegradationRate(gene[i]->getRate()*(dr250()*5.83 + 0.17));
      gene[i]->setRate(1.0);
      gene[i]->setDegradationRate(1.0);
    }
  sprintf(comments, "Model of a random gene network following a Erdos-Renyi topology\nwith %ld genes and %ld input connections each.\n\nCreated automatically by the A-Biochem system", n, k);
}
