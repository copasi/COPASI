/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiMethod.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/23 19:43:01 $
   End CVS Header */

/**
 *  CCopasiMethod class.
 *  This class is used to describe a task in COPASI. This class is 
 *  intended to be used as the parent class for all tasks whithin COPASI.
 *  
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiMethod
#define COPASI_CCopasiMethod

#include <string>

#include "CCopasiContainer.h"

class CCopasiProblem;
class CMethodParameterList;
class CReport;

class CCopasiMethod : public CCopasiParameterGroup
  {
  public:
    /**
     * Enumeration of the types of tasks known to COPASI.
     */
    enum Type
    {
      steadyState = 0,
      timeCourse,
      scan,
      fluxMode,
      optimization,
      parameterFitting,
    };

    /**
     * String literals for the GUI to display type names of tasks known
     * to COPASI.
     */
    const static string TypeName[];

    /**
     * XML type names of tasks known to COPASI.
     */
    const static char* XMLType[];

    // Attributes
  private:
    /**
     * The type of the task
     */
    std::string mType;

    // Operations
  protected:
    /**
     * Default constructor
     */
    CCopasiMethod();

  public:

    /**
     * Specific constructor
     * @param const string & name (Default = "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & type (default: "Method")
     */
    CCopasiMethod(const CCopasiMethod::Type & type,
                  const CCopasiContainer * pParent = NULL,
                  const std::string & type = "Method");

    /**
     * Copy constructor
     * @param const CCopasiMethodr & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiMethod(const CCopasiMethod & src,
                  const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~CCopasiMethod();

    /**
     * Retrieve the type of the method
     * @return  const string & type
     */
    const std::string & getType() const;

    /**
     * Set the type of the method
     * @param const string & type
     */
    void setType(const std::string & type);
  };

#endif // COPASI_CCopasiMethod
