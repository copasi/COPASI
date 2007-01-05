/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/ssa/Attic/CSSAMethod.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: tjohann $
   $Date: 2006/09/12 15:16:20 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_SSAMethod
#define COPASI_SSAMethod

#include <string>

#include "utilities/CCopasiMethod.h"
//#include "utilities/CMatrix.h"

#include "utilities/CAnnotatedMatrix.h"

class CSSAProblem;
class CFluxMode;
#include "utilities/CCopasiException.h"

class CSSAMethod : public CCopasiMethod
  {
  protected:
    /**
     *  A pointer to the SSA problem.
     */
    const CSSAProblem * mpProblem;

    /**
     * A pointer to the progress bar handler
     */
    //CProcessReport * mpProgressHandler;

    // Operations
  private:
    /**
     * Default constructor.
     */
    CSSAMethod();

  protected:
    /**
     * Specific constructor.
     * @param CCopasiMethod::SubType subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    explicit CSSAMethod(CCopasiMethod::SubType subType,
                        const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Create a trajectory method.
     * Note: the returned object has to be released after use with delete
     */
    static CSSAMethod *
    createSSAMethod(CCopasiMethod::SubType subType
                    = CCopasiMethod::ssaMethod);

    /**
     * Copy constructor.
     * @param "const CTSSMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSSAMethod(const CSSAMethod & src,
               const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CSSAMethod();

    /**
     *  Set a pointer to the problem.
     *  This method is used by CSteadyState
     *  @param "CSteadyStateProblem *" problem
     */
    //void setProblem(CSteadyStateProblem * problem);

    /**
     */
    bool process(CProcessReport * handler);

    bool initialize(CSSAProblem* problem);

    bool calculate();
    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

  protected:

    // attributes

    // the Stoichiometric Matrix in which we will have only irreversible reactions
    CMatrix<C_FLOAT64> mStoichiometry;

    // representation of mStoichiometry in vector<vector<>> form for the CEFMAlgorithm:
    std::vector< std::vector<C_FLOAT64> > mStoiRows;

    // bitfield telling which of the reactions are duplicated from a reversible reaction
    std::vector< bool > mIsBackwardReaction;

    // number of all reactions, including reversible -> size of mIsBackwardReaction.
    C_INT32 mNumReactions;

    // the rate constants corresponding to the reactions represented by the columns of mStoichiometry:
    std::vector< std::string > mRateConstants;

    CMatrix<C_FLOAT64> mTransposedKineticMatrix;

    std::vector< CMatrix<C_FLOAT64> > mTransformedSubJacobians;

    std::vector< CVector<C_FLOAT64> > mExtremeCurrents;

    // vector holding the index of non-mixing stable ECs in mExtremeCurrents:
    std::vector< C_INT32 > mNonMixingStableECs;

    CSSATask * mpTask;
    CModel * mpModel;

    // gets the reactions to be duplicated in the matrix rows/columns
    void buildBackwardReactionVector();

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

    bool isMixingStable(CVector< C_FLOAT64 > &);

    // build diagonal square matrices from vectors:
    template <class CType> CMatrix<CType> diag(CVector<CType> vector)
    {
      CMatrix<CType> matrix;

      matrix.resize(vector.size(), vector.size());
      memset(matrix.array(), 0, matrix.size()*sizeof(CType));

      for (uint i = 0; i < vector.size(); ++i)
        matrix(i, i) = vector[i];

      return matrix;
    }
  };

#endif // COPASI_CSSAMethod
