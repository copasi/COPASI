/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiProblem.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/21 20:32:46 $
   End CVS Header */

/**
 *  CCopasiProblem class.
 *  This class is used to describe a task in COPASI. This class is 
 *  intended to be used as the parent class for all tasks whithin COPASI.
 *  
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiProblem
#define COPASI_CCopasiProblem

#include <string>

#include "CCopasiContainer.h"

class CCCopasiTask;
class MethodParameterList;

class CCopasiProblem : public CCopasiContainer
  {
  public:
    // Attributes

  private:

    // Operations
  protected:
    /**
     * Default constructor
     */
    CCopasiProblem();

  public:

    /**
     * Specific constructor
     * @param "const string &" name (Default = "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & type (default: "Task")
     */
    CCopasiProblem(const CCopasiProblem::Type & type,
                   const CCopasiContainer * pParent = NULL,
                   const std::string & type = "Task");

    /**
     * Copy constructor
     * @param "const CCopasiProblemr &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiProblem(const CCopasiProblem & src,
                   const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~CCopasiProblem();

    /**
     * Retrieve the name of the method
     * @return " const string &" name
     */
    const std::string & getName() const;

    /**
     * Set the name of the method
     * @param "const string &" name
     */
    bool setName(const std::string & name);

    /**
     * Retrieve the type of the method
     * @return " const string &" type
     */
    const std::string & getType() const;

    /**
     * Set the type of the method
     * @param "const string &" type
     */
    void setType(const std::string & type);

    /**
     * Retrieve the name of the indexed parameter
     * @param "const unsigned C_INT32 &" index
     * @return "const string &" mName
     */
  };

#endif // COPASI_CCopasiProblem
