/**
 * CUsageRange
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CUsageRange
#define COPASI_CUsageRange

#include <string>
#include "CRange.h"

class CUsageRange : public CRange
  {
  private:

    /**
     * The usage or meaning of this range. This has no functional implication 
     * for CFunction but it might be used in derived classes. Possible
     * usages are SUBSTRATE, PRODUCT, MODIFIER, or PARAMETER 
     */
    string mUsage;

  public:
    /**
     *  Default constructor
     */
    CUsageRange();

    /**
     *  Copy constructor
     *  @param "const CUsageRange" & src
     */
    CUsageRange(const CUsageRange & src);

    /**
     *  Destructor
     */
    ~CUsageRange();

    /**
     *  Cleanup
     */
    void cleanup();

    /**
     *  Loads an object with data coming from a CReadConfig object. 
     *  (CReadConfig object reads an input stream)
     *  @param configBuffer reference to a CReadConfig object.
     *  @return Fail
     */
    virtual void load(CReadConfig & configBuffer,
                      CReadConfig::Mode mode = CReadConfig::NEXT);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     * (Which usually has a file attached but may also have socket)
     *  @param configBuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    virtual void save(CWriteConfig & configBuffer);

    /**
     *  Retrieves the usage of the range
     *  @return "const string &" usage
     */
    const string & getUsage() const;

    /**
     *  Retrieves the name in this case the usage the range
     *  @return "const string &" name
     */
    const string & getName() const;

    /**
     *  Set the usage of the range
     *  @param "const string &" usage
     */
    void setUsage(const string & usage);
  };

#endif // COPASI_CUsageRange
