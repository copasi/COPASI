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
    (const std::string & name,
     const CFunctionParameter::DataType & type,
     const std::string & usage);

    /**
     *  Remove a parameter from the parameter list
     *  @param "const CFunctionParameter &" parameter
     */
    void remove
    (const std::string & name);

    /**
     *  Retrieves the vector of function parameters
     *  @return "CCopasiVectorNS < CFunctionParameter >" & parameter
     */ 
    // CCopasiVectorNS < CFunctionParameter > & getParameters();

    /**
     *
     */
    CFunctionParameter * operator[](unsigned C_INT32 index);

    /**
     *
     */
    const CFunctionParameter * operator[](unsigned C_INT32 index) const;

    /**
     *
     */
    CFunctionParameter * operator[](const std::string &name);

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
     *  In a normal situation pos is set to 0 for the first call. 
     *  It is increment by the method to allow subsequent searches to start
     *  after the last found item. This is usefull if several parameters 
     *  with the same usage exist.
     *  @param "const string &" usage
     *  @param "unsigned C_INT32 &" pos (first call should be with 0)
     *  @return "CFunctionParameter &" usageRange
     */
    CFunctionParameter & getParameterByUsage(const std::string & usage,
        unsigned C_INT32 & pos);

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CFunctionParameters & d)
    {
      os << "++++CFunctionParameters: " << std::endl;
      os << "    CFunctionParameters.mParameters " << std::endl << d.mParameters;
      os << "    CFunctionParameters.mUsageRanges " << std::endl << d.mUsageRanges;
      os << "----CFunctionParameters " << std::endl;

      return os;
    }

  private:
    /**
     *  WHAT DOES THIS DO ??????
     */
    void updateUsageRanges();
  };

#endif // COPASI_CFunctionParameters
