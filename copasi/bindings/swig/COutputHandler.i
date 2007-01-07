%{

#include "utilities/COutputHandler.h"

%}

/**
 *  This is just the interface that is used to all output provided by COPASI.
 */
class COutputInterface
  {
  public:
    /**
     * The output activity, indicating the status of the current operations
     * performed by a task.
     */
    enum Activity
    {
      BEFORE = 0x01,
      DURING = 0x02,
      AFTER = 0x04
    };

    /**
     * Default constructor
     */
    COutputInterface();

    /**
     * Copy constructor
     * @param const COutputInterface & src
     */
    COutputInterface(const COutputInterface & src);

    /**
     * Destructor
     */
    virtual ~COutputInterface();

  };

/**
 *  This is the lass which drives all otuput of COPASI.
 */
class COutputHandler: public COutputInterface
  {
  public:
    /**
     * Default Constructor
     */
    COutputHandler();

    /**
     * Copy constructor
     * @param const COutputInterface & src
     */
    COutputHandler(const COutputHandler & src);

    /**
     * Destructor
     */
    virtual ~COutputHandler();

  };


