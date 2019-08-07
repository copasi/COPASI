// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CMCAMethod_H__
#define COPASI_CMCAMethod_H__

#include <vector>
#include "copasi/utilities/CLinkMatrix.h"
#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/core/CDataArray.h"
#include "copasi/steadystate/CSteadyStateMethod.h"

class CModel;
class CSteadyStateTask;

class CMCAMethod: public CCopasiMethod
{
private:
  /**
   * Default constructor.
   */
  CMCAMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: mcaMethodReder)
   * @param const CTaskEnum::Task & taskType (default: mca)
   */
  CMCAMethod(const CDataContainer * pParent,
             const CTaskEnum::Method & methodType = CTaskEnum::Method::mcaMethodReder,
             const CTaskEnum::Task & taskType = CTaskEnum::Task::mca);
  /**
   * Copy constructor
   * @param const CMCAMethod & src
   * @param const CDataContainer * pParent (Default: NULL)
   */
  CMCAMethod(const CMCAMethod & src,
             const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CMCAMethod();

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  const CMatrix<C_FLOAT64> & getUnscaledElasticities() const
  {return mUnscaledElasticities;}

  void calculateUnscaledElasticities(C_FLOAT64 res);

  const CMatrix<C_FLOAT64> & getUnscaledConcentrationCC() const
  {return mUnscaledConcCC;}

  bool calculateUnscaledConcentrationCC();

  const CMatrix<C_FLOAT64> & getUnscaledFluxCC() const
  {return mUnscaledFluxCC;}

  bool calculateUnscaledFluxCC(const bool & status);

  const CMatrix<C_FLOAT64> & getScaledElasticities() const
  {return mScaledElasticities;}

  const CMatrix<C_FLOAT64> & getScaledConcentrationCC() const
  {return mScaledConcCC;}

  const CMatrix<C_FLOAT64> & getScaledFluxCC() const
  {return mScaledFluxCC;}

  const CDataArray* getUnscaledElasticitiesAnn() const
  {return mUnscaledElasticitiesAnn;}
  const CDataArray* getScaledElasticitiesAnn() const
  {return mScaledElasticitiesAnn;}
  const CDataArray* getUnscaledConcentrationCCAnn() const
  {return mUnscaledConcCCAnn;}
  const CDataArray* getScaledConcentrationCCAnn() const
  {return mScaledConcCCAnn;}
  const CDataArray* getUnscaledFluxCCAnn() const
  {return mUnscaledFluxCCAnn;}
  const CDataArray* getScaledFluxCCAnn() const
  {return mScaledFluxCCAnn;}

  /**
   * Resizes all result matrices and updates the corresponding array annotations.
   * This needs to be called before output initialization (in case the output references
   * parts of the matrix) from the task initialization, but it also needs to be called
   * before selecting elements of the matrices in the object selection dialog.
   * The model needs to be set before calling this.
   */
  virtual void resizeAllMatrices();

  /**
   * Scales the coefficients (i.e. Kacser format, rather than Reder)
   */
  bool scaleMCA(const bool & status, C_FLOAT64 res);

  /**
   * Check whether the summation theorems hold.
   */
  bool checkSummationTheorems(const C_FLOAT64 & resolution);

  /**
   * Get the Model
   */
  const CModel* getModel() const;

  /**
   * the steady state MCA entry point
   * @param ss_solution refer to steady-state solution
   * @param refer to the resolution
   */
  bool CalculateMCA(C_FLOAT64 res);

  /**
   *
   */
  virtual bool process();

  /**
   * Read SSMCAUnscaled from configuration file
   */
  C_INT32 load(CReadConfig & configBuffer);

  void setSteadyStateTask(CSteadyStateTask * pSteadyStateTask);

  const CSteadyStateMethod::ReturnCode & getSteadyStateStatus() const
  {return mSSStatus;}

  void setFactor(C_FLOAT64 factor);

  void setSteadyStateResolution(C_FLOAT64 factor);

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

private:
  void initObjects();

  /**
   * Initialize the method parameter
   */
  void initializeParameter();

  bool createLinkMatrix(const bool & useSmallbone = false);

private:
  bool * mpUseReder;

  bool * mpUseSmallbone;

  /**
   * MCA Matrices
   */
  CMatrix<C_FLOAT64> mUnscaledElasticities;
  CDataArray* mUnscaledElasticitiesAnn;

  CMatrix<C_FLOAT64> mUnscaledConcCC;
  CDataArray* mUnscaledConcCCAnn;

  CMatrix<C_FLOAT64> mUnscaledFluxCC;
  CDataArray* mUnscaledFluxCCAnn;

  CMatrix<C_FLOAT64> mScaledElasticities;
  CDataArray* mScaledElasticitiesAnn;

  CMatrix<C_FLOAT64> mScaledConcCC;
  CDataArray* mScaledConcCCAnn;

  CMatrix<C_FLOAT64> mScaledFluxCC;
  CDataArray* mScaledFluxCCAnn;

  /**
   * 1 if MCA coeffs are to be unscaled
   */
  C_INT16 mSSReder;

  /**
   * If need to evaluate the elasticities, ss_x
   * will be assigned in calculateTimeMCA()
   */
  std::vector <C_FLOAT64> mSsx;

  /**
   * Modulation factor for finite differences derivation
   */
  C_FLOAT64 mFactor;

  C_FLOAT64 mSteadyStateResolution;

  CSteadyStateMethod::ReturnCode mSSStatus;

  CSteadyStateTask * mpSteadyStateTask;

  CLinkMatrix mLinkZero;

  CMatrix< C_FLOAT64 > mReducedStoichiometry;

  CMatrix< C_INT32 > mElasticityDependencies;
};
#endif // COPASI_CMca
