/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodLevenbergMarquardt.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/03 18:51:14 $
   End CVS Header */

/**
  * COptMethodLevenbergMarquardt class
  */

#ifndef COPASI_COptMethodLevenbergMarquardt
 #define COPASI_COptMethodLevenbergMarquardt

#include "COptMethod.h"

class CRandom;

class COptMethodLevenbergMarquardt : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  public:
    /**
     * Copy Constructor
     * @param const COptMethodLevenbergMarquardt & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptMethodLevenbergMarquardt(const COptMethodLevenbergMarquardt & src,
                                 const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COptMethodLevenbergMarquardt();

    /**
     * Execute the optimization algorithm calling simulation routine 
     * when needed. It is noted that this procedure can give feedback 
     * of its progress by the callback function set with SetCallback.
     * @ return success;
     */
    virtual bool optimise();

  private:
    /**
     * Default Constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptMethodLevenbergMarquardt(const CCopasiContainer * pParent = NULL);

    /**
     * Initialize contained objects.
     */
    void initObjects();

    // Attributes
  private:
  };

#endif  // COPASI_COptMethodLevenbergMarquardt
