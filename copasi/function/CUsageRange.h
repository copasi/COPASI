/**
 * CUsageRange
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CUsageRange
#define COPASI_CUsageRange

#include <string>
#include <iostream>

#include "CRange.h"

/** @dia:pos -24.0564,25.0674 */
/** @dia:route CRange; v,-18.6548,19.2872,21.8489,-11.3836,25.0674 */
class CUsageRange : public CRange
  {
  private:

  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & type (default: "Range")
     */
    CUsageRange(const std::string & name = "NoName",
                const CCopasiContainer * pParent = NULL,
                const std::string & type = "Usage Range");

    /**
     * Copy constructor
     * @param "const CUsageRange" & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CUsageRange(const CUsageRange & src,
                const CCopasiContainer * pParent = NULL);

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
    const std::string & getUsage() const;

    /**
     *  Retrieves the name in this case the usage the range
     *  @return "const string &" name
     */
    const std::string & getName() const;

    /**
     *  Set the usage of the range
     *  @param "const string &" usage
     */
    bool setUsage(const std::string & usage);

    /**
    * insert operator
    */
    friend std::ostream & operator<<(std::ostream &os, const CUsageRange & d)
    {
      os << "CUsageRange: "
      << " mLow " << d.getLow()
      << " mHigh " << d.getHigh()
      << " mUsage " << d.getObjectName() << std::endl;

      return os;
    }
  };

#endif // COPASI_CUsageRange
