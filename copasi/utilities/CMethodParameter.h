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

class CReadConfig;
class CWriteConfig;

class CMethodParameter
  {
    // Attributes

  private:

    /**
     *  The name of the attribute
     */
    std::string mName;

    /**
     *  The value of the attribute
     */
    double mValue;

    // Operations

  public:

    /**
     * Default constructor
     * @param "const string &" name (Default = "")
     * @param "const double &" value (Default = 0.0)
     */
    CMethodParameter(const std::string & name = "",
                     const double & value = 0.0);

    /**
     * Copy constructor
     * @param "const CMethodParameter &" src
     */
    CMethodParameter(const CMethodParameter & src);

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
