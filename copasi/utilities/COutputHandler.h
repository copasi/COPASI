/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/COutputHandler.h,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/16 21:05:31 $
   End CVS Header */

#ifndef OUTPUT_HANDLER
#define OUTPUT_HANDLER

#include <vector>
#include <set>

class CCopasiObject;
class CCopasiContainer;
class CCopasiTask;
class Refresh;

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
     * Destructor
     */
    virtual ~COutputInterface() {};

    /**
     * compile the object list from name vector
     * @param std::vector< CCopasiContainer * > listOfContainer (default: empty list)
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > /* listOfContainer */ =
                           std::vector< CCopasiContainer * >())
    {return false;};

    /**
     * Perform an output event for the current activity
     * @param const Activity & activity
     */
    virtual void output(const Activity & /* activity */) {};

    /**
     * Introduce an additional seperator into the ouput
     * @param const Activity & activity
     */
    virtual void separate(const Activity & /* activity */) {};

    /**
     * Finsh the output
     */
    virtual void finish() {};

    /**
     * Retreive the list of objects handled by the interface
     * @return const std::set< CCopasiObject * > & objects
     */
    virtual const std::set< CCopasiObject * > & getObjects() const
      {return mObjects;}

    // Attributes
  protected:
    /**
     * All the objects which are output.
     */
    std::set< CCopasiObject * > mObjects;
  };

/**
 *  This is the lass which drives all otuput of COPASI.
 */
class COutputHandler: public COutputInterface
  {
    // Operations

  public:
    /**
     * Default Constructor
     * @param CCopasiTask * pTask (default: NULL)
     */
    COutputHandler(CCopasiTask * pTask = NULL);

    /**
     * Destructor
     */
    virtual ~COutputHandler();

    /**
     * compile the object list from name vector
     * @param std::vector< CCopasiContainer * > listOfContainer (default: empty list)
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > listOfContainer =
                           std::vector< CCopasiContainer * >());

    /**
     * Perform an output event for the current activity
     * @param const Activity & activity
     */
    virtual void output(const Activity & activity);

    /**
     * Introduce an additional seperator into the ouput
     * @param const Activity & activity
     */
    virtual void separate(const Activity & activity);

    /**
     * Finsh the output
     */
    virtual void finish();

    /**
     * Add an interface
     * @param COutputInterface * pInterface;
     */
    virtual void addInterface(COutputInterface * pInterface);

    /**
     * Remove an interface
     * @param COutputInterface * pInterface;
     */
    virtual void removeInterface(COutputInterface * pInterface);

    /**
     * Set whether the handler is the master handler
     * @param const bool & isMaster
     */
    void setMaster(const bool & isMaster);

    /**
     * Check whether the handler is a master
     * @return const bool & isMaster
     */
    const bool & isMaster() const;

  protected:
    /**
     * Refresh all objects
     */
    void refresh();

    /**
     * Compile the object refresh list
     */
    bool compileRefresh();

    // Attributes
  protected:
    /**
     * The main operating task
     */
    CCopasiTask * mpTask;

    /**
     * A list of all active output interfaces.
     */
    std::set<COutputInterface *> mInterfaces;

    /**
     * Indicates whether the handler is the master handler. The master
     * handler is reponsible for the object updates.
     */
    bool mIsMaster;

    /**
     * An ordered list of refresh methods needed by the master
     */
    std::vector< Refresh * > mObjectRefreshes;
  };
#endif
