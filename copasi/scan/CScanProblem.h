/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanProblem.h,v $
   $Revision: 1.21 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/12/30 15:31:54 $
   End CVS Header */

/**
 *  CScanProblem class.
 */

#ifndef COPASI_CScanProblem
#define COPASI_CScanProblem

#include <string>

#include "utilities/CCopasiProblem.h"
#include "utilities/CReadConfig.h"
#include "model/CState.h"

class CModel;

class CScanProblem : public CCopasiProblem
  {
  public:
    enum Type
    {
      SD_UNIFORM = 0,
      SD_GAUSS,
      SD_BOLTZ,
      SD_REGULAR
    };

  private:

    /**
     *  The initial state, i.e., the starting conditions of the trajectroy/SS.
     */
    CState mInitialState;

  public:

    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CScanProblem(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor.
     * @param const CTrajectoryProblem & src
     * @paramconst CCopasiContainer * pParent (default: NULL)
     */
    CScanProblem(const CScanProblem & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CScanProblem();

    /**
     * Set the moddel the problem is dealing with.
     * @param "CModel *" pModel
     */
    virtual bool setModel(CModel * pModel);

    /**
     * Set the number of time steps the trajectory method should integrate.
     * @param "const unsigned C_INT32 &" stepNumber
     */
    void setStepNumber(const unsigned C_INT32 & stepNumber);

    /**
     * Retrieve the number of time steps the trajectory method should integrate.
     * @return "const unsigned C_INT32 &" stepNumber
     */
    const unsigned C_INT32 & getStepNumber() const;

    /**
     * Set the initial state of the problem.
     * @param "const CState &" initialState
     */
    void setInitialState(const CState & initialState);

    /**
     * Set the initial state of the problem.
     * @param "const CStateX &" initialState
     */
    void setInitialState(const CStateX & initialState);

    /**
     * Retrieve the initial state of the problem.
     * @return "const CState &" pInitialState
     */
    const CState & getInitialState() const;

    /**
     * Load a scan problem
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
     */
    void load(CReadConfig & configBuffer,
              CReadConfig::Mode mode = CReadConfig::NEXT);
  };

#endif
