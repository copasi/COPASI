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
#include "model/model.h"
#include "CElementaryFluxModes.h"
#include "CEFMAlgorithm.h"
CElementaryFluxModes::CElementaryFluxModes(){CONSTRUCTOR_TRACE; mModel = NULL;}
CElementaryFluxModes::~CElementaryFluxModes(){DESTRUCTOR_TRACE;}

void CElementaryFluxModes::calculate(const CModel * model)
{
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

bool
CElementaryFluxModes::isFluxModeReversible(const unsigned C_INT32 & index) const
{return mFluxModes[index].isReversible();}

std::string
CElementaryFluxModes::getFluxModeDescription(const unsigned C_INT32 & index) const
  {
    std::stringstream tmp;
    unsigned C_INT32 j, jmax = mFluxModes[index].size();
    const CCopasiVectorNS < CReaction > & Reaction = mModel->getReactions();

    for (j = 0; j < jmax; j++)
      {
        if (j) tmp << ", ";
        tmp << mFluxModes[index].getMultiplier(j) << " * "
        << Reaction[mIndex[mFluxModes[index].getReaction(j)]]->getName();
      }

    return tmp.str();
  }

unsigned C_INT32 CElementaryFluxModes::getFluxModeSize() const
{return mFluxModes.size();}
