/**
 * CFunctionParameters
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CFunctionParameters
#define COPASI_CFunctionParameters

#include "utilities/utilities.h"
#include "CFunctionParameter.h"
#include "CUsageRange.h"

class CFunctionParameters
  {
    // Attributes

  private:
    /**
     *  A vector of parameters
     *  @supplierCardinality 0..*
     *  @associates <{CFunctionParameter}>
     */
    CCopasiVectorNS < CFunctionParameter > mParameters;

    /**
     *  A vector describing the ranges of numbers of parameters for
     *  a specific usage
     * @supplierCardinality 0..*
     */
    CCopasiVectorNS < CUsageRange > mUsageRanges;

    // Operations

  public:
    /**
     *  Default constructor
     */
    CFunctionParameters();

    /**
     *  Copy constructor
     *  @param "const CFunctionParameters &" src
     */
    CFunctionParameters(const CFunctionParameters & src);

    /**
     *  Destructor
     */
    ~CFunctionParameters();

    /**
     *  Cleanup
     */
    void cleanup();

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param "CReadConfig &" configBuffer,
     *  @param "CReadConfig::Mode" mode (Default: CReadConfig::NEXT)
     *  @return Fail
     */
    void load(CReadConfig & configBuffer,
              CReadConfig::Mode mode = CReadConfig::NEXT);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param "CWriteConfig &" configBuffer
     *  @return Fail
     */
    void save(CWriteConfig & configBuffer);

    /**
     *  Add a parameter to the parameter list
     *  @param "const CFunctionParameter &" parameter
     */

    void add
      (const CFunctionParameter & parameter);

    /**
     *  Add a parameter to the parameter list
     *  @param "CFunctionParameter *" parameter
     */
    void add
      (CFunctionParameter * parameter);

    /**
     *  Add a parameter to the parameter list
     *  @param "const string & name
     *  @param "const CFunctionParameter::DataType &" type
     *  @param "const string &" usage
     */
    void add
      (const string & name,
       const CFunctionParameter::DataType & type,
       const string & usage);

    /**
     *  Remove a parameter from the parameter list
     *  @param "const CFunctionParameter &" parameter
     */
    void remove
      (const string & name);

    /**
     *  Retrieves the vector of function parameters
     *  @return "CCopasiVectorNS < CFunctionParameter >" & parameter
     */ 
    // CCopasiVectorNS < CFunctionParameter > & getParameters();

    /**
     *
     */
    CFunctionParameter * & operator[](unsigned C_INT32 index);

    /**
     *
     */
    const CFunctionParameter * & operator[](unsigned C_INT32 index) const;

    /**
     *
     */
    CFunctionParameter * operator[](const string &name);

    /**
     *
     */
    unsigned C_INT32 size() const;

    /**
     *  Retreives the vector of usage ranges for the parameters
     *  @return "vector < CUsageRange * > & usageRanges
     */
    CCopasiVectorNS < CUsageRange > & getUsageRanges();

    /**
     *  Retrieves the first parameter with the specified usage after pos
     *  @param "const string &" usage
     *  @param "unsigned C_INT32 &" pos (first call should be with 0)
     *  @return "CFunctionParameter &" usageRange
     */
    CFunctionParameter & getParameterByUsage(const string & usage,
        unsigned C_INT32 & pos);

  private:
    /**
     *  Update usage ranges
     */
    void updateUsageRanges();

    /**
     * insert operator
     */
    friend ostream & operator<<(ostream &os, const CFunctionParameters & d);
  };

#endif // COPASI_CFunctionParameters
