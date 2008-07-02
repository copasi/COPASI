// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CSSAMethod.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: tjohann $
//   $Date: 2008/07/02 08:06:12 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_SSAMethod
#define COPASI_SSAMethod

#include <string>

#include "elementaryFluxModes/CEFMAlgorithm.h"
//#include "utilities/CMatrix.h"

#include "utilities/CAnnotatedMatrix.h"
#include "utilities/CCopasiVector.h"

class CSSAProblem;
class CFluxMode;

class CSSAMethod : public CEFMAlgorithm
  {
    friend CEFMMethod * CEFMMethod::createMethod(CCopasiMethod::SubType subType);

  public:
    CSSAMethod(const CSSAMethod & src,
               const CCopasiContainer * pParent = NULL);

    CSSAMethod(const CCopasiContainer * pParent = NULL);

    bool process(CProcessReport * handler);

    bool calculate();

    bool initialize();

    bool isReactionReversed(int index) const;

    TriLogic isMixingStable(int indexEC);

  protected:

    // attributes

    //
    CCopasiVectorNS< CReaction > mReactions;

    // the Stoichiometric Matrix in which we will have only irreversible reactions
    CMatrix<C_FLOAT64> mStoichiometry;

    // representation of mStoichiometry in vector<vector<>> form for the CEFMAlgorithm:
    std::vector< std::vector<C_FLOAT64> > mStoiRows;

    // bitfield telling which of the reactions are duplicated from a reversible reaction
    std::vector< bool > mIsBackwardReaction;

    // number of all reactions, including reversible -> size of mIsBackwardReaction.
    C_INT32 mNumReactions;

    // the rate constants corresponding to the reactions represented by the columns of mStoichiometry:
    // std::vector< std::string > mRateConstants;

    CMatrix<C_FLOAT64> mTransposedKineticMatrix;

    std::vector< CMatrix<C_FLOAT64> > mTransformedSubJacobians;

    std::vector< CVector<C_FLOAT64> > mExtremeCurrents;

    // vector holding the index of non-mixing stable ECs in mExtremeCurrents:
    // three states:
    //    -1 for "Not mixing stable"
    //     0 for "Unknown"
    //     1 for "Mixing stable"
    std::vector< TriLogic > mIsMixingStable;

    // gets the reactions to be duplicated in the matrix rows/columns
    //void buildBackwardReactionVector();

    // retrieves the jacobian from input:
    bool buildJacobian();
    // retrieves mExtremeFluxes via (positive) elementary modes:
    bool buildExtremeCurrents();
    // retrieves and expands the mStoichiometry:
    bool buildStoichiometry();

    // retrieves mTransposedKineticMatrix:
    bool buildKineticMatrix();

    // decompose jacobian in reaction coordinates
    bool decomposeJacobian();

    // test if there is a non-mixing stable EC
    // return true if all ECs are mixing stable,
    //        false otherwise.
    bool testForMixingStability();

    // build diagonal square matrices from vectors:
    template <class CType> CMatrix<CType> diag(CVector<CType> vector)
    {
      CMatrix<CType> matrix;

      matrix.resize(vector.size(), vector.size());
      memset(matrix.array(), 0, matrix.size()*sizeof(CType));

      for (unsigned int i = 0; i < vector.size(); ++i)
        matrix(i, i) = vector[i];

      return matrix;
    }
  };

#endif // COPASI_CSSAMethod
