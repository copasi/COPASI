/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CopasiTime.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/13 20:09:46 $
   End CVS Header */

#ifndef COPASI_time
#define COPASI_time

#include "copasi.h"

/**
 * This class is for handling execution time related values. 
 * static methods for retreiving wall clock and CPU time are
 * provided.
 */
class CCopasiTimeVariable
  {
  public:
    /**
     * Default constructor.
     */
    CCopasiTimeVariable();

    /**
     * Copy constructor.
     * @param const CCopasiTimeVariable & src
     */
    CCopasiTimeVariable(const CCopasiTimeVariable & src);

    /**
     * Specific constructor from a C_INT64 value.
     * @param const C_INT64 & value
     */
    CCopasiTimeVariable(const C_INT64 & value);

    /**
     * Destructor.
     */
    ~CCopasiTimeVariable();

    /**
     * Operator + for adding CCopasiTimeVariables
     * @param const CCopasiTimeVariable & value
     * @return CCopasiTimeVariable sum
     */
    CCopasiTimeVariable operator + (const CCopasiTimeVariable & value);

    /**
     * Operator - for subtracting CCopasiTimeVariables
     * @param const CCopasiTimeVariable & value
     * @return CCopasiTimeVariable difference
     */
    CCopasiTimeVariable operator - (const CCopasiTimeVariable & value);

    /**
     * Assignement operator
     * @param const CCopasiTimeVariable & rhs
     * @return CCopasiTimeVariable & this
     */
    CCopasiTimeVariable & operator = (const CCopasiTimeVariable & rhs);

    /**
     * Assignement operator assigning a C_INT64 value to a CCopasiTimeVariable
     * @param const CCopasiTimeVariable & rhs
     * @return CCopasiTimeVariable & this
     */
    CCopasiTimeVariable & operator = (const C_INT64 & value);

    /**
     * Coparison operator <
     * @param const CCopasiTimeVariable & value
     * @return bool isLess
     */
    bool operator < (const CCopasiTimeVariable & value);

    /**
     * Create a iso formated string (D:HH:MM:SS.ssssss)
     * @return std::string
     */
    std::string isoFormat() const;

    /**
     * Retrieve the time in micro seconds. If bounded is true  
     * 0 <= microSeconds  < 1000
     * @param const bool & bounded (default: false)
     * @return C_INT64 microSeconds
     */
    C_INT64 getMicroSeconds(const bool & bounded = false) const;

    /**
     * Retrieve the time in milli seconds. If bounded is true  
     * 0 <= milliSeconds  < 1000
     * @param const bool & bounded (default: false)
     * @return C_INT64 milliSeconds
     */
    C_INT64 getMilliSeconds(const bool & bounded = false) const;

    /**
     * Retrieve the time in seconds. If bounded is true  
     * 0 <= seconds  < 60
     * @param const bool & bounded (default: false)
     * @return C_INT64 seconds
     */
    C_INT64 getSeconds(const bool & bounded = false) const;

    /**
     * Retrieve the time in minutes. If bounded is true  
     * 0 <= minutes  < 60
     * @param const bool & bounded (default: false)
     * @return C_INT64 minutes
     */
    C_INT64 getMinutes(const bool & bounded = false) const;

    /**
     * Retrieve the time in hours. If bounded is true  
     * 0 <= hours  < 24
     * @param const bool & bounded (default: false)
     * @return C_INT64 hours
     */
    C_INT64 getHours(const bool & bounded = false) const;

    /**
     * Retrieve the time in days.
     * @param const bool & bounded (default: false)
     * @return C_INT64 days
     */
    C_INT64 getDays() const;

    /**
     * Retrieve the current wall clock time in micro seconds
     * since 1970-01-01:00:00:00.0
     * @return CCopasiTimeVariable time
     */
    static CCopasiTimeVariable getCurrentWallTime();

    /**
     * Retrieve the current cpu time used since the start of the process.
     * @return CCopasiTimeVariable time
     */
    static CCopasiTimeVariable getCPUTime();

    /**
     * Helper function to convert a C_INT32 to a std::string.
     * If the number of digits is non zero the value is padded with 
     * zeros.
     * @param const C_INT64 & value
     * @param const C_INT32 & digits (default: 0)
     * @return std::string
     */
    static std::string LL2String(const C_INT64 & value,
                                 const C_INT32 & digits = 0);

  private:
    /**
     * Value containing the time in micro seconds.
     */
    C_INT64 mTime;
  };

#endif
