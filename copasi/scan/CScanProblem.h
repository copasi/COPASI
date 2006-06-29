/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanProblem.h,v $
   $Revision: 1.28 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/06/29 09:01:19 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CScanProblem class.
 */

#ifndef COPASI_CScanProblem
#define COPASI_CScanProblem

#include <string>

#include "utilities/CCopasiProblem.h"
#include "utilities/CReadConfig.h"
//#include "model/CState.h"

//class CModel;

class CScanProblem : public CCopasiProblem
  {
  public:
    enum Type
    {
      SCAN_REPEAT = 0,
      SCAN_LINEAR,
      SCAN_RANDOM,
      SCAN_BREAK,
      SD_UNIFORM,
      SD_GAUSS,
      SD_BOLTZ,
      SD_REGULAR
    };

  private:

    /**
     *  This holds the scan items
     */
    CCopasiParameterGroup * mpScanItems;

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
     *  Set the type of the subtask.
     */
    void setSubtask(CCopasiTask::Type type);

    /**
     *  Get the type of the subtask.
     */
    CCopasiTask::Type getSubtask() const;

    /**
     *  Set if output should be done after every step of the subtask.
     */
    void setOutputInSubtask(bool ois);

    /**
     *  Ask if output should be done after every step of the subtask.
     */
    const bool & getOutputInSubtask() const;

    /**
     *  Set if initial conditions should be set to the result of the previous run.
     */
    void setAdjustInitialConditions(bool aic);

    /**
     *  Ask if initial conditions should be set to the result of the previous run.
     */
    const bool & getAdjustInitialConditions() const;

    unsigned C_INT32 getNumberOfScanItems() const;

    const CCopasiParameterGroup* getScanItem(unsigned C_INT32 index) const;
    CCopasiParameterGroup* getScanItem(unsigned C_INT32 index);

    CScanProblem::Type getScanItemType(unsigned C_INT32 index);

    CCopasiParameterGroup* createScanItem(CScanProblem::Type type, unsigned C_INT32 steps = 5, const CCopasiObject* obj = NULL);

    void clearScanItems();

    //void createDebugScan(CModel* model);

    /**
     * Load a scan problem
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
     */
    void load(CReadConfig & configBuffer,
              CReadConfig::Mode mode = CReadConfig::NEXT);
  };

#endif
