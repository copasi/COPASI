/**
 *  CMethodParameterList class.
 *  This class is used to describe a list method paramters. This class is 
 *  intended to be used with integration or optimization methods.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CMethodParameterList
#define COPASI_CMethodParameterList

#include <string>

#include "CCopasiVector.h"
#include "CMethodParameter.h"
#include "CReadConfig.h"

class CWriteConfig;

class CMethodParameterList : private CCopasiVectorNS < CMethodParameter >
  {
    // Attributes
  private:
    /**
     *  The name of the Method
     */
    string mName;

    /**
     *  The type of the Method
     */
    string mType;

    // Operations
  public:

    /**
     * Default constructor
     */
    CMethodParameterList();

    /**
     * Copy constructor
     * @param "const CMethodParameter &" src
     */
    CMethodParameterList(const CMethodParameterList & src);

    /**
     * Destructor
     */
    ~CMethodParameterList();

    /**
     * Get the size of the parameter list
     * @return "unsigned C_INT32 &" size
     */
    unsigned C_INT32 size() const;

    /**
     * Retrieve the name of the method
     * @return " const string &" name
     */
    const string & getName() const;

    /**
     * Set the name of the method
     * @param "const string &" name
     */
    void setName(const string & name);

    /**
     * Retrieve the type of the method
     * @return " const string &" type
     */
    const string & getType() const;

    /**
     * Set the type of the method
     * @param "const string &" type
     */
    void setType(const string & type);

    /**
     * Retrieve the name of the indexed parameter
     * @param "const unsigned C_INT32 &" index
     * @return "const string &" mName
     */
    const string & getName(const unsigned C_INT32 & index) const;

    /**
     * Set the value of the indexed parameter
     * @param "const unsigned C_INT32 &" index
     * @param "const double &" value
     */
    void setValue(const unsigned C_INT32 & index,
                  const double & value);

    /**
     * Set the value of the indexed parameter
     * @param "const string &" name
     * @param "const double &" value
     */
    void setValue(const string & name,
                  const double & value);

    /**
     * Retrieve the value of the indexed parameter.
     * @param "const unsigned C_INT32 &" index
     * @return "const double & value
     */
    const double & getValue(const unsigned C_INT32 & index) const;

    /**
     * Retrieve the value of the named parameter.
     * @param "const string &" index
     * @return "const double & value
     */
    const double & getValue(const string & name) const;

    /**
     * Add a parameter to the list
     * @param "const string &" name 
     * @param "const double &" value (Default = 0.0)
     */
    void add
    (const string & name,
     const double & value = 0.0);

    /**
     * Load a list of parameters
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode" mode Default(CReadConfig::SEARCH)
     */
    void load(CReadConfig & configBuffer,
              CReadConfig::Mode mode = CReadConfig::SEARCH);

    /**
     * Save a list of parameters
     * @param "CWriteConfig &" configBuffer
     */
    void save(CWriteConfig & configBuffer);

    /**
     * Search for method parameter list of a specified name and type 
     * in a congfig buffer. Note: the returned pointer has to be released
     * after use.
     * @param "CReadConfig &" configBuffer
     * @param "const string &" name
     * @param "const string &" type
     * @return "CMethodParameterList *" methodParameterList
     */
    static CMethodParameterList * search(CReadConfig & configBuffer,
                                         const string & name,
                                         const string & type);
  };

#endif // COPASI_CMethodParameterList
