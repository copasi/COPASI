/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CMCAMethod.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/28 08:20:03 $
   End CVS Header */

#ifndef COPASI_CMCAMethod_H__
#define COPASI_CMCAMethod_H__

#include <vector>
#include "utilities/CMatrix.h"
#include "utilities/CCopasiMethod.h"

#define MCA_OK 0
#define MCA_SINGULAR 1

class CModel;

class CMCAMethod: public CCopasiMethod
  {
  private:

    /**
     * MCA Matrix
     */

    CMatrix <C_FLOAT64> mDxv;

    CMatrix <C_FLOAT64> mFcc;

    CMatrix <C_FLOAT64> mGamma;

    CModel * mpModel;

    /**
     * an n+1 integer vector of pivot indices.
     */
    C_INT32 * mSsipvt;

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

    bool mIsSteadyState;

  public:
    /**
     * Default constructor
     */
    CMCAMethod(const CCopasiContainer* pParent);

    /**
     * User defined constructor
     * @param refer to Model and factor
     */
    CMCAMethod(CModel & model, C_FLOAT64 factor, const CCopasiContainer* pParent);

    /**
     * Deconstructor
     */

    virtual ~CMCAMethod();

    /**
     * Set the Model
     */
    void setModel(CModel* model);

    /**
     * Get the Model
     */
    CModel* getModel();

    /**
     * return the mDxv matrix
     */
    CMatrix < C_FLOAT64 > getDxv();

    /**
     * return the mFCC matrix
     */
    CMatrix < C_FLOAT64 > getFcc();

    /**
     * return the mGamma matrix
     */
    CMatrix < C_FLOAT64 > getGamma();

    /**
     * Clear mDxv with zeros
     */
    void clearDxv();

    /**
     * Initialize mDxv with the unscaled elasticities
     * @param src is newtown variable, (is ss_x in Gespasi project)
     * @param res is the resolution of steady state
     */
    void initDxv(C_FLOAT64 res);

    /**
     * Calculates the flux-control coefficients
     *  @param refer to the condition
     */
    void CalcFCC(int condition);

    /**
     * Calculates the concentration-control coefficients
     */
    int CalcGamma();

    /**
     * Initialize ss_ipvt
     */
    void initSsipvt();

    /**
     * Delete ss_ipvt
     */
    void delSsipvt();
    /**
     * the steady state MCA entry point
     * @param ss_solution refer to steady-state solution
     * @param refer to the resolution
     */
    int CalculateMCA(int ss_solution, C_FLOAT64 res);

    /**
     * Initialize the MCA matrices: mDxv, mFcc, mGamma
     */
    void init();

    /**
     * 
     */
    virtual bool process();

    /**
     * Read SSMCAUnscaled from configuration file
     */
    C_INT32 load(CReadConfig & configBuffer);

    /**
     * Scales the coefficients (i.e. Kacser format, rather than Reder)
     * @param refer to the condition
     * @param refer to the resolution
     */
    void ScaleMCA(int condition, C_FLOAT64 res);

    /**
     * the time dependent MCA entry point
     * @param refer to the resolution
     */
    void CalculateTimeMCA(C_FLOAT64 res);

    /**
     * Return the mSSx vector for calculate time mca
     */
    std::vector <C_FLOAT64> getSsx();

    void setIsSteadyState(bool isSteadyState);

    bool isSteadyState() const;

    void setFactor(C_FLOAT64 factor);

    void setSteadyStateResolution(C_FLOAT64 factor);

    /**
     *  Saves the SSReder of the object to a CWriteConfig object.
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     *  @see mFail
     */ 
    //    C_INT32 save(CWriteConfig & configbuffer);
  };
#endif // COPASI_CMca
