/**
 * CFunctionParameters
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CFunctionParameters
#define COPASI_CFunctionParameters

#include "utilities/readwrite.h"
#include "utilities/CCopasiVector.h"
#include "CFunctionParameter.h"
#include "CUsageRange.h"
#include "report/CCopasiContainer.h"

/** @dia:pos 10.7176,6.51973 */
class CFunctionParameters : public CCopasiContainer
  {
    // Attributes

  private:
    /**
     *  A vector of parameters
     *  @supplierCardinality 0..*
     *  @associates <{CFunctionParameter}>
     */
    /** @dia:route 0,3; h,15.1888,24.6765,8.71728,7.21973,10.7176 */
    CCopasiVectorNS < CFunctionParameter > mParameters;

    /**
     *  A vector describing the ranges of numbers of parameters for
     *  a specific usage
     * @supplierCardinality 0..*
     */
    /** @dia:route 0,2; h,10.7176,6.51973,7.07775,25.0674,1.28919 */
    CCopasiVectorNS < CUsageRange > mUsageRanges;

    // Operations

  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFunctionParameters(const std::string & name = "NoName",
                        const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CFunctionParameters &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFunctionParameters(const CFunctionParameters & src,
                        const CCopasiContainer * pParent = NULL);

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

    void add(const CFunctionParameter & parameter);

    /**
     *  Add a parameter to the parameter list
     *  @param "CFunctionParameter *" parameter
     *  @param const bool & adopt (Default: false)
     */
    void add(CFunctionParameter * parameter, const bool & adopt = false);

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
    const CFunctionParameter * operator[](unsigned C_INT32 index) const;

    /**
     *
     */
    CFunctionParameter * operator[](const std::string &name);
    const CFunctionParameter * operator[](const std::string &name) const;

    /**
     *
     */
    unsigned C_INT32 size() const;

    /**
     *  Retreives the vector of usage ranges for the parameters
     *  @return "vector < CUsageRange * > & usageRanges
     */
    const CCopasiVectorNS < CUsageRange > & getUsageRanges() const;

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
    const CFunctionParameter & getParameterByUsage(const std::string & usage,
        unsigned C_INT32 & pos) const;

    /**
     * gets the number of Parameters with a specific usage
     */
    unsigned C_INT32 getNumberOfParametersByUsage(const std::string & usage) const;

    /**
     * find a parameter by its name and return its index
     */
    unsigned C_INT32 findParameterByName(const std::string & name,
                                         CFunctionParameter::DataType & dataType) const;

    bool operator==(const CFunctionParameters & rhs) const;

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

    /**
     *  WHAT DOES THIS DO ??????
     */
    void updateUsageRanges();
  };

#endif // COPASI_CFunctionParameters
