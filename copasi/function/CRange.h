/**
 * CRange
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CRange
#define COPASI_CRange

#include "copasi.h"
#include "utilities/readwrite.h"
#include "report/CCopasiContainer.h"

/**
 *
 */ 
/** @dia:pos -40.594,3.88725 */
class CRange : public CCopasiContainer
  {
    //Attributes
  public:
    /**
     *  Constants which may be used specifying a Range
     */
    enum Constants
    {
      Infinity = -1,  // 0xFFFF
      NoRange = 0
    };

  private:
    /**
     *  Lower Bound
     */
    unsigned C_INT32 mLow;

    /**
     *  Upper Bound
     */
    unsigned C_INT32 mHigh;

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & type (default: "Range")
     */
    CRange(const std::string & name = "NoName",
           const CCopasiContainer * pParent = NULL,
           const std::string & type = "Range");

    /**
     * Copy Constructor
     * @param "const CRange" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CRange(const CRange & src,
           const CCopasiContainer * pParent = NULL);

    /**
     * Specific Constructor
     * @param "const unsigned C_INT32" low
     * @param "const unsigned C_INT32" high
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & type (default: "Range")
     */
    CRange(const unsigned C_INT32 & low,
           const unsigned C_INT32 & high = CRange::NoRange,
           const CCopasiContainer * pParent = NULL,
           const std::string & type = "Range");

    /**
     *  Destructor
     */
    virtual ~CRange();

    /**
     *  Cleanup
     */
    void cleanup();

    /**
     *  Loads an object with data coming from a CReadConfig object. 
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    virtual void load(CReadConfig & configbuffer,
                      CReadConfig::Mode mode = CReadConfig::NEXT);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     * (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    virtual void save(CWriteConfig & configbuffer);

    /**
     *  Set the lower Bound
     *  @param "const unsigned C_INT32" & low
     */
    virtual void setLow(const unsigned C_INT32& low);

    /**
     *  Set the upper Bound
     *  @param "const unsigned C_INT32" & high
     */
    virtual void setHigh(const unsigned C_INT32 & high);

    /**
     *  Set the range, i.e., lower and upper bound simultaniously
     *  @param "const unsigned C_INT32" & low
     *  @param "const unsigned C_INT32" & high = CRange::UNSPECIFIED
     */
    virtual void setRange(const unsigned C_INT32 & low,
                          const unsigned C_INT32 & high = CRange::NoRange);

    /**
     *  Retrieves the lower bound of the range
     *  @return "const unsigned C_INT32 &" low
     */
    virtual const unsigned C_INT32& getLow() const;

    /**
     *  Retrieves the upper bound of the range
     *  @return "const unsigned C_INT32 &" high
     */
    virtual const unsigned C_INT32 & getHigh() const;

    /**
     *  Checks whether we have a real range or just a low bound, i.e., a
     *  fixed number.
     */
    virtual const bool isRange() const;

    /**
     *  Checks whether the value is whithin the range
     *  @param "const unsigned C_INT32 &" value
     *  @return "const bool" isInRange
     */
    virtual const bool isInRange(const unsigned C_INT32 & value) const;

  private:
    /**
     *  Checks whether the values for low and high specify a valid range
     */
    virtual void checkRange() const;
  };

#endif // COPASI_CRange
