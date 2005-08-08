/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiTimer.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/08/08 17:20:30 $
   End CVS Header */

#ifndef COPASI_CCopasiTimer
#define COPASI_CCopasiTimer

#include "CCopasiObject.h"
#include "utilities/CopasiTime.h"

class CCopasiTimer: public CCopasiObject
  {
  public:
    /**
     * Enumeration of timer types
     */
    enum Type
    {
      WALL = 0,
      CPU
    };

    // Operations
    /**
     * Default constructor
     * @param const Type & type (default: WALL)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiTimer(const Type & type = WALL,
                 const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CCopasiTimer & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiTimer(const CCopasiTimer & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CCopasiTimer();

    /**
     * Start or restart the timer.
     * @return bool success
     */
    bool start();

    /**
     * Actualizes the timer.
     * @return bool success
     */
    bool actualize();

    /**
     * Retrieve the elapsed time.
     * @return const CCopasiTimeVariable & elapsedTime
     */
    const CCopasiTimeVariable & getElapsedTime();

    /**
     * This is the output method for any object. The default implementation
     * provided with CCopasiObject uses the ostream operator<< of the object
     * to print the object.To overide this default behaviour one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;

  private:
    // Attributes
    /**
     * The timer type
     */
    Type mType;

    /**
     * The start time of the timer.
     */
    CCopasiTimeVariable mStartTime;

    /**
     * The elapsed time of the timer.
     */
    CCopasiTimeVariable mElapsedTime;

    /**
     * The elapsed time as a double used for reporting.
     */
    C_FLOAT64 mElapsedTimeSeconds;
  };

#endif // COPASI_CCopasiTimer
