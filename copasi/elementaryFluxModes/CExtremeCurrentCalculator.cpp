/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/Attic/CExtremeCurrentCalculator.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: tjohann $
   $Date: 2006/09/12 12:23:44 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "model/CModel.h"

#include "CEFMAlgorithm.h"
#include "CEFMProblem.h"
#include "CEFMTask.h"
#include "CFluxMode.h"

#include "utilities/CProcessReport.h"
#include "elementaryFluxModes/CEFMAlgorithm.h"

#include "CExtremeCurrentCalculator.h"

CExtremeCurrentCalculator::CExtremeCurrentCalculator(const CCopasiContainer * pParent) :
    CEFMAlgorithm(CCopasiMethod::extremeCurrents, pParent)
{initObjects();}

bool
CExtremeCurrentCalculator::initialize()
{
  CCopasiTask * pTask = dynamic_cast< CCopasiTask * >(getObjectParent());
  if (pTask == NULL) return false;

  mpModel = pTask->getProblem()->getModel();
  if (mpModel == NULL) return false;

  mFluxModes.clear();

  /* ModelStoi is the transpose of the models stoichiometry matrix */
  const CMatrix< C_FLOAT64 > ModelStoi = mpModel->getStoi();

  unsigned C_INT32 row, numRows = ModelStoi.numRows();
  unsigned C_INT32 col, numCols = ModelStoi.numCols();

  /* Get the reactions from the model */
  /* Note: We have as many reactions as we have rows in ModelStoi */
  const CCopasiVectorNS < CReaction > & Reaction = mpModel->getReactions();

  /* Vector to keep track of the rearangements neccessary to put the */
  /* reversible reactions to the top of Stoi */
  mIndex.resize(numRows);

  /* Reversible reaction counter */
  mReversible = 0;

  /* Build the transpose of the stoichiometry matrix,   */
  /* expanding each reversible reaction's column (row). */
  std::vector< C_FLOAT64 > rowcache, revrowcache;
  std::vector< C_INT32 > index;
  rowcache.resize(numRows); revrowcache.resize(numRows);
  for (col = 0; col < numCols; col++)
    {
      for (row = 0; row < numRows; row++)
        {
          rowcache[row] = ModelStoi(row, col);
          revrowcache[row] = -1 * ModelStoi(row, col);
        }

      mStoi.push_back(rowcache);
      index.push_back(col);

      if (Reaction[col]->isReversible())
        {
          mStoi.push_back(revrowcache);
          index.push_back(col);
        }
    }

  mIndex.resize(mStoi.size());
  for (col = 0; col < mStoi.size(); ++col)
    mIndex[col] = index[col];

  std::cout << "new stoichiometric matrix" << std::endl;
  for (int i = 0; i < mStoi.size(); ++i)
    {
      for (int j = 0; j < numRows; ++j)
        std::cout << mStoi[i][j] << " ";
      std::cout << std::endl;
    }
  /* resetting reversible count, as we haven't any reversible */
  /* reactions in the stoichiometric matrix anymore           */

  /* resetting reversible count, as we haven't any reversible */
  /* reactions in the stoichiometric matrix anymore           */
  mReversible = 0;

  mStep = 0;
  mMaxStep = mStoi[0].size();

  if (mpCallBack)
    mhSteps =
      mpCallBack->addItem("Current Step",
                          CCopasiParameter::UINT,
                          & mStep,
                          & mMaxStep);

  return true;
}
