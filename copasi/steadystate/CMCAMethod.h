/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CMCAMethod.h,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/06/20 13:19:55 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CMCAMethod_H__
#define COPASI_CMCAMethod_H__

#include <vector>
#include "utilities/CMatrix.h"
#include "utilities/CCopasiMethod.h"
#include "utilities/CAnnotatedMatrix.h"
#include "CSteadyStateMethod.h"

#define MCA_OK 0
#define MCA_SINGULAR 1

class CModel;

class CMCAMethod: public CCopasiMethod
  {
  private:

    CModel * mpModel;

    /**
     * MCA Matrices
     */
    CMatrix<C_FLOAT64> mUnscaledElasticities;
    CArrayAnnotation* mUnscaledElasticitiesAnn;

    CMatrix<C_FLOAT64> mUnscaledConcCC;
    CArrayAnnotation* mUnscaledConcCCAnn;

    CMatrix<C_FLOAT64> mUnscaledFluxCC;
    CArrayAnnotation* mUnscaledFluxCCAnn;

    CMatrix<C_FLOAT64> mScaledElasticities;
    CArrayAnnotation* mScaledElasticitiesAnn;

    CMatrix<C_FLOAT64> mScaledConcCC;
    CArrayAnnotation* mScaledConcCCAnn;

    CMatrix<C_FLOAT64> mScaledFluxCC;
    CArrayAnnotation* mScaledFluxCCAnn;

    /**
     * 1 if MCA coeffs are to be unscaled
     */
    C_INT16 mSSReder;

    /**
     * If need to evaluate the elasticites, ss_x
     * will be assigned in calculateTimeMCA()
     */
    std::vector <C_FLOAT64> mSsx;

    /**
     * Modulation factor for finite differences derivation
     */
    C_FLOAT64 mFactor;

    C_FLOAT64 mSteadyStateResolution;

    CSteadyStateMethod::ReturnCode mSSStatus;

    void initObjects();

  public:
    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (Defailt: NULL)
     */
    CMCAMethod(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CMCAMethod & src
     * @param const CCopasiContainer * pParent (Defailt: NULL)
     */
    CMCAMethod(const CMCAMethod & src,
               const CCopasiContainer * pParent = NULL);

    /**
     * User defined constructor
     * @param refer to Model and factor
     */
    //    CMCAMethod(CModel & model, C_FLOAT64 factor, const CCopasiContainer* pParent);

    /**
     * Deconstructor
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

    int calculateUnscaledConcentrationCC();

    const CMatrix<C_FLOAT64> & getUnscaledFluxCC() const
      {return mUnscaledFluxCC;}

    void calculateUnscaledFluxCC(int condition);

    const CMatrix<C_FLOAT64> & getScaledElasticities() const
      {return mScaledElasticities;}

    const CMatrix<C_FLOAT64> & getScaledConcentrationCC() const
      {return mScaledConcCC;}

    const CMatrix<C_FLOAT64> & getScaledFluxCC() const
      {return mScaledFluxCC;}

    const CArrayAnnotation* getUnscaledElasticitiesAnn() const
      {return mUnscaledElasticitiesAnn;}
    const CArrayAnnotation* getScaledElasticitiesAnn() const
      {return mScaledElasticitiesAnn;}
    const CArrayAnnotation* getUnscaledConcentrationCCAnn() const
      {return mUnscaledConcCCAnn;}
    const CArrayAnnotation* getScaledConcentrationCCAnn() const
      {return mScaledConcCCAnn;}
    const CArrayAnnotation* getUnscaledFluxCCAnn() const
      {return mUnscaledFluxCCAnn;}
    const CArrayAnnotation* getScaledFluxCCAnn() const
      {return mScaledFluxCCAnn;}

    /**
     * Scales the coefficients (i.e. Kacser format, rather than Reder)
     */
    void scaleMCA(int condition, C_FLOAT64 res);

    /**
     * Set the Model
     */
    void setModel(CModel* model);

    /**
     * Get the Model
     */
    const CModel* getModel() const;

    /**
     * the steady state MCA entry point
     * @param ss_solution refer to steady-state solution
     * @param refer to the resolution
     */
    int CalculateMCA(CSteadyStateMethod::ReturnCode status, C_FLOAT64 res);

    /**
     *
     */
    virtual bool process();

    /**
     * Read SSMCAUnscaled from configuration file
     */
    C_INT32 load(CReadConfig & configBuffer);

    void setSteadyStateStatus(CSteadyStateMethod::ReturnCode SSStatus);

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
    /**
     * Intialize the method parameter
     */
    void initializeParameter();
  };
#endif // COPASI_CMca
