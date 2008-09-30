// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/COutputHandler.h,v $
//   $Revision: 1.18 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/09/30 18:14:08 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
     * Default constructor
     */
    COutputInterface():
        mObjects()
    {};

    /**
     * Copy constructor
     * @param const COutputInterface & src
     */
    COutputInterface(const COutputInterface & src):
        mObjects(src.mObjects)
    {};

    /**
     * Destructor
     */
    virtual ~COutputInterface() {};

    /**
     * compile the object list from name vector
     * @param std::vector< CCopasiContainer * > listOfContainer
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > /* listOfContainer */)
    {return false;};

    /**
     * Perform an output event for the current activity
     * @param const Activity & activity
     */
    virtual void output(const Activity & /* activity */) {};

    /**
     * Introduce an additional separator into the output
     * @param const Activity & activity
     */
    virtual void separate(const Activity & /* activity */) {};

    /**
     * Finish the output
     */
    virtual void finish() {};

    /**
     * Retrieve the list of objects handled by the interface
     * @return const std::set< const CCopasiObject * > & objects
     */
    virtual const std::set< const CCopasiObject * > & getObjects() const
      {return mObjects;}

    // Attributes
  protected:
    /**
     * All the objects which are output.
     */
    std::set< const CCopasiObject * > mObjects;
  };

/**
 *  This is the lass which drives all output of COPASI.
 */
class COutputHandler: public COutputInterface
  {
    // Operations

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

    /**
     * compile the object list from name vector
     * @param std::vector< CCopasiContainer * > listOfContainer
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > listOfContainer);

    /**
     * Perform an output event for the current activity
     * @param const Activity & activity
     */
    virtual void output(const Activity & activity);

    /**
     * Introduce an additional separator into the output
     * @param const Activity & activity
     */
    virtual void separate(const Activity & activity);

    /**
     * Finish the output
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
     * @param COutputHandler * pMaster
     */
    void setMaster(COutputHandler * pMaster);

    /**
     * Check whether the handler is a master
     * @return bool isMaster
     */
    bool isMaster() const;

  protected:
    /**
     * Refresh all objects
     */
    void refresh();

    /**
     * Compile the object refresh list
     * @param const std::vector< CCopasiContainer * > & listOfContainer
     * @return bool success
     */
    bool compileRefresh(const std::vector< CCopasiContainer * > & listOfContainer);

    // Attributes
  protected:
    /**
     * A list of all active output interfaces.
     */
    std::set<COutputInterface *> mInterfaces;

    /**
     * Points to the master handler. The master handler is responsible for the
     * and object updates and all the output.
     */
    COutputHandler * mpMaster;

    /**
     * An ordered list of refresh methods needed by the master
     */
    std::vector< Refresh * > mObjectRefreshes;
  };
#endif
