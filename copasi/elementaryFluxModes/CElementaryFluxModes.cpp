/**
 *  CElementaryFluxModes class.
 *  Main class to calculate elementary flux modes. This is the adapter to
 *  COPASI model.
 *
 *  Created for Copasi by Stefan Hoops 2002-05-09
 *  (C) Stefan Hoops 2002
 */

#include "copasi.h"
#include "CElementaryFluxModes.h"
#include "model/model.h"
#include "tnt/tnt.h"
#include "tnt/cmat.h"

CElementaryFluxModes::CElementaryFluxModes(){mModel = NULL;}

CElementaryFluxModes::~CElementaryFluxModes(){}

void CElementaryFluxModes::calculate(const CModel * model)
{
  mModel = model;
  
  /* ModelStoi is the transpose of the models stoichiometry matrix */
  const TNT::Transpose_View < TNT::Matrix < C_FLOAT64 > > & ModelStoi = 
    TNT::Transpose_View< TNT::Matrix < C_FLOAT64 > >(mModel->getStoi());

  unsigned C_INT32 row, numRows = ModelStoi.num_rows();
  unsigned C_INT32 col, numCols = ModelStoi.num_cols();
  
  /* Size the stoichiometry matrix passed to the algorithm */
  vector < vector < C_FLOAT64 > > Stoi;
  Stoi.resize(numRows);
  for (row=0; row<numRows; row++) Stoi[row].resize(numCols);
  
  /* Get the reactions from the model */
  /* Note: We have as many reactions as we have rows in ModelStoi */
  const CCopasiVectorS < CReaction > & Reaction = mModel->getReactions();
  
  /* Vector to keep track of the rearangements neccessary to put the */
  /* reversible reactions to the top of Stoi */
  mIndex.resize(numRows);
  
  /* Reversible reaction counter */
  mReversible = 0;
  
  unsigned C_INT32 Insert;
  unsigned C_INT32 InsertReversible = 0;
  unsigned C_INT32 InsertIrreversible = numRows - 1;
  
  /* Build the transpose of the stoichiometry matrix, */
  /* sort reversible reactions to the top, count them */
  /* and keep track of the rearrangement */
  for (row=0; row<numRows;)
    {
      if (Reaction[row]->isReversible())
        {
          Insert = InsertReversible++;
          mReversible++;
        }
      else
        Insert = InsertIrreversible--;

      mIndex[Insert] = row;
      row++; /* Since ModelStoi is accessed fortran style hereafter. */
      for (col=0; col<numCols; col++)
        Stoi[Insert][col] = ModelStoi(row,col+1);
    }

  /* Now do the calculation */
  CEFMAlgorithm Algorithm;
  Algorithm.calculate(Stoi, mReversible, mFluxModes);
}

void CElementaryFluxModes::write(ostream & output) const
{
  /* Get the reactions from the model */
  const CCopasiVectorS < CReaction > & Reaction = mModel->getReactions();

  string Reversible;
  unsigned C_INT32 i, imax = mFluxModes.size();
  unsigned C_INT32 j, jmax;

  output << "Elementary Flux Modes of Model \"" 
         << mModel->getTitle() << "\":" << endl;
  
  for (i=0; i<imax; i++)
    {
      output << i << ".\t";
      jmax = mFluxModes[i].size();
      Reversible = "reversible";
      
      for (j=0; j<jmax; j++)
        {
          if (!Reaction[mIndex[mFluxModes[i][j]]]->isReversible())
              Reversible = "irreversible";
              
          output << Reaction[mIndex[mFluxModes[i][j]]]->getName() << ", ";
        }
          
      output << "\t" << Reversible << endl;
    }
}
