/**
 *  CTrajectoryProblem class.
 *  This class describes the trajectory problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CTrajectoryProblem
#define COPASI_CTrajectoryProblem

#include <string>
#include "model/model.h"
#include "utilities/CMethodParameterList.h"
#include "utilities/CReadConfig.h"
#include "utilities/CWriteConfig.h"
#include "utilities/CCopasiVector.h"

class CScanProblem
  {
    // Attributes
  private:
    /**
     *  The model the problem is working on.
     */
    CModel * mpModel;

    //CMethodParameterList **scanItem;

    CCopasiVectorNS < CMethodParameterList > scanItem;

  public:
    // Operations

    /**
     *  Default constructor.
     */
    CScanProblem();

    /**
     *  Copy constructor.
     *  @param "const CScanProblem &" src
     */
    CScanProblem(const CScanProblem & src);

    /**
     *  Destructor.
     */
    ~CScanProblem();

    /**
     *  Size of the scanItem vector
     */
    C_INT32 scanItemSize();

    /**
     *  Add a Scan Item to the vector ScanItem
     */
    void addScanItem(CMethodParameterList * Item);

    /**
     *  Get a Scan Item from the vector ScanItem
     */
    CMethodParameterList * getScanItem(C_INT32 itemNumber);

    /**
     *  Add a parameter to a scan item
     * @param "const C_INT32" itemNumber
     * @param "const std::string &" name
     * @param "const double &" value
     */
    void addScanItemParameter(const C_INT32 itemNumber,
                              const std::string & name,
                              const double & value);

    /**
     *  Get a parameter from a scan item
     * @param "const C_INT32" itemNumber
     * @param "const std::string &" name
     */
    const double & getScanItemParameter(const C_INT32 itemNumber,
                                        const std::string & name);

    /**
     *  Set the value of a parameter in a scan item
     * @param "const C_INT32" itemNumber
     * @param "const std::string &" name
     * @param "const double &" value
     */
    void setScanItemParameter(const C_INT32 itemNumber,
                              const std::string & name,
                              const double & value);

    /**
     * Set the moddel the problem is dealing with.
     * @param "CModel *" pModel
     */
    void setModel(CModel * pModel);

    /**
     * Retrieve the model the problem is dealing with.
     * @return "CModel *" pModel
     */
    CModel * getModel() const;

    /**
     * Load a trajectory problem
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
     */

    /*
    void load(CReadConfig & configBuffer,
              CReadConfig::Mode mode = CReadConfig::NEXT);

    */

    /**
     * Save a trajectory problem
     * @param "CWriteConfig &" configBuffer
     */

    /*
    void save(CWriteConfig & configBuffer) const;
    */
  };

#endif // COPASI_CTrajectoryProblem
