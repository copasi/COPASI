/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiTask.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/30 17:59:22 $
   End CVS Header */

/**
 *  CCopasiTask class.
 *  This class is used to describe a task in COPASI. This class is 
 *  intended to be used as the parent class for all tasks whithin COPASI.
 *  
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiTask
#define COPASI_CCopasiTask

#include <string>

#include "report/CCopasiContainer.h"

class CCopasiProblem;
class CCopasiMethod;
class CReport;

class CCopasiTask : public CCopasiContainer
  {
  public:
    /**
     * Enumeration of the types of tasks known to COPASI.
     */
    enum Type
    {
      unset = 0,
      steadyState,
      timeCourse,
      scan,
      fluxMode,
      optimization,
      parameterFitting
    };

    /**
     * String literals for the GUI to display type names of tasks known
     * to COPASI.
     */
    static const std::string TypeName[];

    /**
     * XML type names of tasks known to COPASI.
     */
    static const char* XMLType[];

    // Attributes
  private:
    /**
     * The type of the task
     */
    std::string mType;

    /**
     * The problem of the task
     */
    CCopasiProblem * mpProblem;

    /**
     * The method used to solve the problem.
     */
    CCopasiMethod * mpMethod;

    /**
     * The report used to track results of the task.
     */
    CReport * mpReport;

    // Operations
  protected:
    /**
     * Default constructor
     */
    CCopasiTask();

  public:

    /**
     * Specific constructor
     * @param "const string &" name (Default = "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & type (default: "Task")
     */
    CCopasiTask(const CCopasiTask::Type & type,
                const CCopasiContainer * pParent = NULL,
                const std::string & type = "Task");

    /**
     * Copy constructor
     * @param "const CCopasiTaskr &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiTask(const CCopasiTask & src,
                const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~CCopasiTask();

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

#endif // COPASI_CCopasiTask
