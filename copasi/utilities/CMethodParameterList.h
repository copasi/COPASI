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

class CMethodParameter;

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
     * Retrieve the value of the indexed parameter.
     * @param "const unsigned C_INT32 &" index
     * @return "const double & value
     */
    const double & getValue(const unsigned C_INT32 & index) const;

    /**
     * Add a parameter to the list
     */

    void add
      (const CMethodParameter & parameter);

    /**
     * Load a list of parameters
     * @param "CReadConfig &" configBuffer
     */
    void load(CReadConfig & configBuffer);

    /**
     * Save a list of parameters
     * @param "CWriteConfig &" configBuffer
     */
    void save(CWriteConfig & configBuffer);
  };

#endif // COPASI_CMethodParameterList
