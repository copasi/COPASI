/**
 *  CMethodParameter class.
 *  This class is used to describe method paramters. This class is intended
 *  to be used with integration or optimization methods.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CMethodParameter
#define COPASI_CMethodParameter

#include <string>

#include "report/CCopasiContainer.h"

class CReadConfig;
class CWriteConfig;

class CMethodParameter: public CCopasiContainer
  {
    // Attributes

  private:

    /**
     *  The name of the attribute
     */
    std::string & mName;

    /**
     *  The value of the attribute
     */
    double mValue;

    // Operations

  public:

    /**
     * Default constructor
     * @param "const string &" name (Default = "")
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & type (default: "Method Parameter")
     */
    CMethodParameter(const std::string & name = "NoName",
                     const CCopasiContainer * pParent = NULL,
                     const std::string & type = "Method Parameter");

    /**
     * Copy constructor
     * @param "const CMethodParameter &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMethodParameter(const CMethodParameter & src,
                     const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor
     * @param "const string &" name
     * @param "const double &" value
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & type (default: "Method Parameter")
     */
    CMethodParameter(const std::string & name,
                     const double & value,
                     const CCopasiContainer * pParent = NULL,
                     const std::string & type = "Method Parameter");

    /**
     * Destructor
     */
    ~CMethodParameter();

    /**
     * Set name of the parameter
     * @param "const string &" name
     */
    void setName(const std::string & name);

    /**
     * Retrieve the name of the parameter
     * @return "const string &" mName
     */
    const std::string & getName() const;

    /**
     * Set the value of the parameter
     * @param "const double &" value
     */
    void setValue(const double & value);

    /**
     * Retrieve the private value of the parameter.
     * @return "const double & value
     */
    const double & getValue() const;

    /**
     * Load a list of parameters
     * @param "CReadConfig &" configBuffer
     */
    void load(CReadConfig & configBuffer);

    /**
     * Save a list of parameters
     * @param "CWriteConfig &" configBuffer
     */
    void save(CWriteConfig & configBuffer) const;

    /**
     * Clean up
     */
    void cleanup();
  };

#endif // COPASI_CMethodParameter
