/**
 *  CEFMAlgorithm class.
 *  Used to calculate elementary flux modes
 *
 *  Created for Copasi by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#include "copasi.h"
#include "CEFMAlgorithm.h"

CEFMAlgorithm::CEFMAlgorithm()
{
  mCurrentTableau = NULL;
  mNextTableau = NULL;
}
  
CEFMAlgorithm::~CEFMAlgorithm()
{
  pdelete(mCurrentTableau);
  pdelete(mNextTableau);
}


bool CEFMAlgorithm::calculate(const vector < vector < C_FLOAT64 > > & stoi,
                              const unsigned C_INT32 &reversibleNumber,
                              vector < vector < unsigned C_INT32 > > & fluxModes)
{
  bool Success = TRUE;
  unsigned C_INT32 Step, MaxSteps = stoi[0].size();
  
  /* initialize the current tableu matrix */
  mCurrentTableau = new CTableauMatrix(stoi, reversibleNumber);
  
  /* Do the iteration */
  for (Step = 0; Step < MaxSteps; Step++) calculateNextTableau(Step);

  /* Build the elementary flux modes to be returned */
  buildFluxModes(fluxModes,stoi.size());

  /* Delete the current / final tableu matrix */
  pdelete(mCurrentTableau);
  
  return Success;
}

void CEFMAlgorithm::calculateNextTableau(const unsigned C_INT32 & step)
{
  list < const CTableauLine * >::iterator a;
  list < const CTableauLine * >::iterator b;
  C_FLOAT64 m;
  
  mNextTableau = new CTableauMatrix();
  
  /* Move all lines with zeros in the step column to the new tableu matrix */
  /* and remove them from the current tableau matrix */
  a = mCurrentTableau->getFirst();
  while (a != mCurrentTableau->getEnd())
    if ((*a)->getReaction(step) == 0.0)
      {
        /* We have to make sure that "a" points to the next element in the */
        /* list after the remember the previous element so that a++ points to */
        /* past the removed one */
        if (a == mCurrentTableau->getFirst())
          {
            mNextTableau->addLine(*a);
            mCurrentTableau->removeLine(a);
            a == mCurrentTableau->getFirst();
          }
        else
          {
            /* We have to remember the previous element so that a++ points to */
            /* past the removed one */
            b = a--;
            mNextTableau->addLine(*a);
            mCurrentTableau->removeLine(a);
            a = b++;
          }
      }

  /* Now we create all linear combinations of the remaining lines in the */
  /* current tableau */
  a = mCurrentTableau->getFirst();
  while (a != mCurrentTableau->getEnd())
    {
      b = a;
      b++;
      
      while (b != mCurrentTableau->getEnd())
        {
          m = - (*b)->getReaction(step) / (*a)->getReaction(step);

          /* The multiplier "m" for irreversible reactions must be positive */
          if ((*a)->isReversible() || m > 0.0)
            mNextTableau->addLine(new CTableauLine(m, **a, **b));
          
          b++;
        }
      a++;
    }
  
  /* Assigne the next tableau to the current tableau and cleanup */
  pdelete(mCurrentTableau);
  mCurrentTableau = mNextTableau;
  mNextTableau = NULL;
}

void CEFMAlgorithm::buildFluxModes(vector < vector < unsigned C_INT32 > > & fluxModes,
                                   const unsigned C_INT32 reactionNumber)
{
  unsigned C_INT32 i, imax = fluxModes.size();

  /* Clear the fluxModes */
  for (i=0; i<imax; i++) fluxModes[i].clear();
  fluxModes.clear();

  list < const CTableauLine * >::iterator a = mCurrentTableau->getFirst();
  list < const CTableauLine * >::iterator end = mCurrentTableau->getEnd();

  vector < unsigned C_INT32 > FluxMode;
  
  while (a != end)
    {
      FluxMode.clear();
      
      for (i=0; i<reactionNumber; i++)
        if ((*a)->getFluxMode(i)) FluxMode.push_back(i);
      
      fluxModes.push_back(FluxMode);
      a++;
    }
}

