/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/Attic/CElementaryFluxModes.cpp,v $
   $Revision: 1.22 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/16 16:20:18 $
   End CVS Header */

/**
 *  CElementaryFluxModes class.
 *  Main class to calculate elementary flux modes. This is the adapter to
 *  COPASI model.
 *
 *  Created for Copasi by Stefan Hoops 2002-05-09
 *  (C) Stefan Hoops 2002
 */

// #define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CElementaryFluxModes.h"
#include "CEFMAlgorithm.h"

CElementaryFluxModes::CElementaryFluxModes(){CONSTRUCTOR_TRACE; mModel = NULL;}
CElementaryFluxModes::~CElementaryFluxModes(){DESTRUCTOR_TRACE;}

void CElementaryFluxModes::calculate(const CModel * model)
{
  if (!model) return;

  mModel = model;

  /* ModelStoi is the transpose of the models stoichiometry matrix */
  const CTransposeView< CMatrix< C_FLOAT64 > > ModelStoi(mModel->getStoi());

  unsigned C_INT32 row, numRows = ModelStoi.numRows();
  unsigned C_INT32 col, numCols = ModelStoi.numCols();

  /* Size the stoichiometry matrix passed to the algorithm */
  std::vector< std::vector< C_FLOAT64 > > Stoi;
  Stoi.resize(numRows);

  for (row = 0; row < numRows; row++)
    Stoi[row].resize(numCols);

  /* Get the reactions from the model */
  /* Note: We have as many reactions as we have rows in ModelStoi */
  const CCopasiVectorNS < CReaction > & Reaction = mModel->getReactions();

  /* Vector to keep track of the rearangements neccessary to put the */
  /* reversible reactions to the top of Stoi */
  mIndex.resize(numRows);

  /* Reversible reaction counter */
  unsigned C_INT32 Reversible = 0;

  unsigned C_INT32 Insert;

  unsigned C_INT32 InsertReversible = 0;

  unsigned C_INT32 InsertIrreversible = numRows - 1;

  /* Build the transpose of the stoichiometry matrix, */
  /* sort reversible reactions to the top, count them */
  /* and keep track of the rearrangement */
  for (row = 0; row < numRows; row++)
    {
      if (Reaction[row]->isReversible())
        {
          Insert = InsertReversible++;
          Reversible++;
        }
      else
        Insert = InsertIrreversible--;

      mIndex[Insert] = row;

      for (col = 0; col < numCols; col++)
        Stoi[Insert][col] = ModelStoi(row, col);
    }

  /* Now do the calculation */
  CEFMAlgorithm Algorithm;

  Algorithm.calculate(Stoi, Reversible, mFluxModes);
}

bool CElementaryFluxModes::isFluxModeReversible(unsigned C_INT32 index) const
{return mFluxModes[index].isReversible();}

const CFluxMode & CElementaryFluxModes::getFluxMode(unsigned C_INT32 index) const
  {return mFluxModes[index];}

std::string
CElementaryFluxModes::getFluxModeDescription(unsigned C_INT32 index) const
  {
    std::stringstream tmp;
    unsigned C_INT32 j, jmax = mFluxModes[index].size();
    const CCopasiVectorNS < CReaction > & Reaction = mModel->getReactions();

    for (j = 0; j < jmax; j++)
      {
        if (j) tmp << ", ";
        tmp << mFluxModes[index].getMultiplier(j) << " * "
        << Reaction[mIndex[mFluxModes[index].getReactionIndex(j)]]->getObjectName();
      }

    return tmp.str();
  }

unsigned C_INT32 CElementaryFluxModes::getFluxModeSize() const
{return mFluxModes.size();}

std::ostream &operator<<(std::ostream &os, const CElementaryFluxModes &A)
{
  /* Get the reactions from the model */
  const CCopasiVectorNS < CReaction > & Reaction = A.mModel->getReactions();

  unsigned C_INT32 i, imax = A.mFluxModes.size();
  unsigned C_INT32 j, jmax;

  os << "Elementary Flux Modes of Model \""
  << A.mModel->getObjectName() << "\":" << std::endl;

  for (i = 0; i < imax; i++)
    {
      os << " Mode " << i + 1 << ":  ";

      if (A.mFluxModes[i].isReversible())
        os << "(reversible)";
      else
        os << "(irreversible)";

      os << std::endl;

      jmax = A.mFluxModes[i].size();

      for (j = 0; j < jmax; j++)
        {
          os << "   " << A.mFluxModes[i].getMultiplier(j) << " * "
          << Reaction[A.mIndex[A.mFluxModes[i].getReactionIndex(j)]]
          ->getObjectName()
          << std::endl;
        }

      os << std::endl;
    }

  return os;
}
