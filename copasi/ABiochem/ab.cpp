/**
 *  ABiochem  -  ab
 *
 *  A program to generate random gene networks 
 *  following a Albert-Barabasi scale-free topology
 *  
 *  writen by Pedro Mendes, October 2002
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

void calculateProbabilities(CCopasiVector < CGene > &gene,
                             vector <C_FLOAT64> &prob,
                             C_INT32 n)
{
  C_INT32 i, tot, d;
  C_FLOAT64 acc, p;

  for (tot = i = 0; i < n; i++)
    {
      d = gene[i]->getOutDegree();
      prob[i] = (C_FLOAT64) d;
      tot += d;
    }
  for (acc = 0.0, i = 0; i < n; i++)
    {
      p = prob[i] / (C_FLOAT64) tot;
      prob[i] = p + acc;
      acc += p;
    }
}

/**
 *  Creates a gene network using a scale-free (Albert-Barabasi) topology
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
  C_INT32 i, j, l, m, modf, ancestors, links, ipg;
  char gn[1024];
  vector <C_FLOAT64> prob;
  C_FLOAT64 mp;

  // the number of ancestors in the network
  if (n > 3)
    ancestors = 3;
  else
    ancestors = 0;
  // the number of connections per gene in ancestor cluster
  if (2*ancestors < k)
    ipg = 2;
  else if (ancestors < k)
    ipg = 1;
  // the number of links added for each new gene
  links = (k - ipg * ancestors) / (n - ancestors);
  if (links > ancestors)
    links = ancestors;
  // create and name genes
  gene.resize(n);
  prob.reserve(n);
  for (i = 0; i < n; i++)
    {
      sprintf(gn, "G%ld", i + 1);
      gene[i]->setName(gn);
    }
  // create links between ancestors randomly
  // add all the regular number of links
  for (i = 0; i < ancestors; i++)
    {
      for (j = 0; j < ipg; j++)
        {
          for (l = -1; l < 0; )
            {
              l = r250n(ancestors);
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
          gene[i]->addModifier(gene[l], l, modf, 1.0e-3, 1.0);
        }
      gene[i]->setRate(1.0);
      gene[i]->setDegradationRate(1.0);
    }
  // grow the network one by one for the remainder of the genes
  for (i = ancestors; i < n; i++)
    {
      prob.push_back(0.0);
      for (j = 0; j < links; j++) // each link (one link each side)
        {
          // recalculate the probability table
          calculateProbabilities(gene, prob, i);
          // select sign of interaction
          if (dr250() < p)
            modf = 1;
          else
            modf = 0;
          // select modifier
          mp = dr250();
          for (l = -1; l < 0; )
            {
              for (l = 0; l < i; l++)
                if (mp < prob[l])
                  break;
              // chose which way the link goes
              if (dr250() < 0.5)
                {
                  for (m = 0; m < gene[l]->getModifierNumber(); m++)
                    if (gene[i] == gene[l]->getModifier(m))
                      {
                        l = -1;
                        break;
                      }
                  if (l == -1)
                    break;
                  gene[l]->addModifier(gene[i], i, modf, 1.0e-3, 1.0);
                }
              else
                {
                  for (m = 0; m < gene[i]->getModifierNumber(); m++)
                    if (gene[l] == gene[i]->getModifier(m))
                      {
                        l = -1;
                        break;
                      }
                  if (l == -1)
                    break;
                  gene[i]->addModifier(gene[l], l, modf, 1.0e-3, 1.0);
                }
            }
        }
      gene[i]->setRate(1.0);
      gene[i]->setDegradationRate(1.0);
    }
#ifdef XXXX
  // now rewire with probability r
  for (i = 0; i < k; i++) // each link (one link each side)
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
              gene[j]->removeModifier(gene[l]);
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
              gene[j]->addModifier(gene[l], l, modf, 1.0e-3, 1.0);
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
              gene[j]->removeModifier(gene[l2]);
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
              gene[j]->addModifier(gene[l2], l2, modf, 1.0e-3, 1.0);
            }
        }
    }
#endif
  sprintf(comments, "Model of a scale-free gene network using the Albert-Barabasi algorithm\nwith %ld genes (%ld seeds), %ld total input connections.\n\nCreated automatically by the A-Biochem system", n, ancestors, (ipg*ancestors + links*(n - ancestors)));
}
