/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CMassAction.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:54 $
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
     *  Retrieves the position of a parameter in the function call
     *  @param "const string &" name
     *  @return "const unsigned C_INT32" index
     */ 
    //virtual unsigned C_INT32 getParameterPosition(const std::string & name) const;

    /**
     *  Returns a string containing the explicit function in SBML format
     *  @param "vector < void * >" callParameters
    *  @param "const string &" r a suffix for parameter names (usually reaction number)
     */ 
    //    std::string getSBMLString(const std::vector< std::vector< std::string > > & callParameterNames, const std::string &r) const;

    /**
     *  Calculates the value of the function
     *  @param "vector < void * >" callParameters
     *  @return "C_FLOAT64" result
     */
    virtual C_FLOAT64
    calcValue(const CCallParameterPointers & callParameters) const;

    /**
     * Returns whether the function depends on the given parameter
     * &param const void * parameter
     * &param const CCallParameters & callParameters
     * &param bool dependsOn
     */
    virtual bool dependsOn(const void * parameter,
                           const CCallParameterPointers & callParameters) const;
  };

#endif // COPASI_CMassAction
