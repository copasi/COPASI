/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/Attic/CMethodParameterList.h,v $
   $Revision: 1.21 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:35:34 $
   End CVS Header */

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

enum Type {SD_UNIFORM = 0, SD_GAUSS, SD_BOLTZ, SD_REGULAR};

class CMethodParameterList : public CCopasiContainer
  {
    // Attributes
  private:
    /**
     *  The type of the Method
     */
    std::string mType;

    /**
     * The list of method parameters for this method
     */
    CCopasiVectorNS < CParameter > mMethodParameters;

    // Operations
  public:

    /**
     * Default constructor
     * @param "const string &" name (Default = "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & type (default: "Method Parameter List")
     */
    CMethodParameterList(const std::string & name = "NoName",
                         const CCopasiContainer * pParent = NULL,
                         const std::string & type = "Method Parameter List");

    /**
     * Copy constructor
     * @param "const CParameter &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMethodParameterList(const CMethodParameterList & src,
                         const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~CMethodParameterList();

    /**
     * cleanup
     */
    void cleanup();

    /**
     * Get the size of the parameter list
     * @return "unsigned C_INT32 &" size
     */
    unsigned C_INT32 size() const;

    /**
     * Retrieve the index given a name
     * @return index for the variable
     */
    const unsigned int CMethodParameterList::getIndex(const std::string & name);

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
     * Retrieve the type of the given method
     * @return " const string &" type
     */
    const CParameter::Type & getType(const unsigned C_INT32 & index);

    /**
     * Retrieve the type of the given method
     * @return " const string &" type
     */
    const CParameter::Type & getType(const std::string & name);

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
    const std::string & getName(const unsigned C_INT32 & index) const;

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
    void setValue(const std::string & name,
                  const double & value);

    /**
     * Set the value of the indexed parameter
     * @param "const string &" name
     * @param "const C_INT32 &" value
     */
    void setValue(const std::string & name,
                  const C_INT32 & value);

    /**
     * Set the value of the indexed parameter
     * @param "const string &" name
     * @param "const unsigned C_INT32 &" value
     */
    void setValue(const std::string & name,
                  const unsigned C_INT32 & value);

    /**
     * Set the value of the indexed parameter
     * @param "const string &" name
     * @param "const bool &" value
     */
    void setValue(const std::string & name,
                  const bool & value);

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
    const double & getValue(const std::string & name) const;

    /**
     * Add a parameter to the list
     * @param "const string &" name 
     * @param "const double &" value (Default = 0.0)
     */
    void add(const std::string & name,
             const double & value = 0.0,
             const CParameter::Type & type = CParameter::DOUBLE);

    /**
    * Delete a parameter in the list
    */
    void remove(const std::string & name);

    /**
    * Delete a parameter in the list
    */
    void swap(unsigned C_INT32 indexFrom, unsigned C_INT32 indexTo);

    /**
     * Load a list of parameters
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode" mode Default(CReadConfig::SEARCH)
     */
    virtual void load(CReadConfig & configBuffer,
                      CReadConfig::Mode mode = CReadConfig::SEARCH);

    /**
     * Load a list of parameters with specific name and type
     * this replaces the search() method
     * @param "CReadConfig &" configBuffer
     * @param "std::string" name
     * @param "std::string" type
     * @param "CReadConfig::Mode" mode Default(CReadConfig::SEARCH)
     */
    virtual void loadSpecific(CReadConfig & configBuffer,
                              const std::string & name,
                              const std::string & type,
                              CReadConfig::Mode mode = CReadConfig::SEARCH);

    /**
     * Save a list of parameters
     * @param "CWriteConfig &" configBuffer
     */
    virtual void save(CWriteConfig & configBuffer);

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
                                         const std::string & name,
                                         const std::string & type);
  };

#endif // COPASI_CMethodParameterList
