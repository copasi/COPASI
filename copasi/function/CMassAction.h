/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CMassAction.h,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/09 16:31:49 $
   End CVS Header */

/**
 * CMassAction
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CMassAction
#define COPASI_CMassAction

#include "CFunction.h"

/** @dia:pos 62.0314,41.4407 */
/** @dia:route CFunction; v,58.2,35.55,39.4413,82.281,41.4407 */
class CMassAction : public CFunction
  {
    // Attributes
  private:

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMassAction(const std::string & name = "NoName",
                const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CFunction &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMassAction(const CFunction & src,
                const CCopasiContainer * pParent = NULL);

    /**
     * Specified constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMassAction(const TriLogic & reversible,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor
     */
    ~CMassAction();

    /**
     *  Calculates the value of the function
     *  @param const CCallParameters<C_FLOAT64> & callParameters
     *  @return "C_FLOAT64" result
     */
    virtual C_FLOAT64
    calcValue(const CCallParameters<C_FLOAT64> & callParameters) const;

    /**
     * Returns whether the function depends on the given parameter
     * &param const void * parameter
     * &param const CCallParameters<C_FLOAT64> & callParameters
     * &param bool dependsOn
     */
    virtual bool dependsOn(const void * parameter,
                           const CCallParameters<C_FLOAT64> & callParameters) const;
  };

#endif // COPASI_CMassAction
