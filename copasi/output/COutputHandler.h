// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef OUTPUT_HANDLER
#define OUTPUT_HANDLER

#include <vector>
#include <set>

#include "copasi/core/CObjectInterface.h"
#include "copasi/math/CMathUpdateSequence.h"

class CMathContainer;
class CDataContainer;
class CCopasiTask;
class Refresh;
class CDataModel;

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
    AFTER = 0x04,
    MONITORING = 0x08
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

  /**
   * compile the object list from name vector
   * @param CObjectInterface::ContainerList listOfContainer
   * @return bool success
   */
  virtual bool compile(CObjectInterface::ContainerList /* listOfContainer */) = 0;

  /**
   * Perform an output event for the current activity
   * @param const Activity & activity
   */
  virtual void output(const Activity & /* activity */) = 0;

  /**
   * Introduce an additional separator into the output
   * @param const Activity & activity
   */
  virtual void separate(const Activity & /* activity */) = 0;

  /**
   * Finish the output
   */
  virtual void finish() = 0;

  /**
   * Close the stream if applicable
   */
  virtual void close();

  /**
   * Retrieve the list of objects handled by the interface
   * @return const CObjectInterface::ObjectSet & objects
   */
  virtual const CObjectInterface::ObjectSet & getObjects() const;

  // Attributes
protected:
  /**
   * All the objects which are output.
   */
  CObjectInterface::ObjectSet mObjects;
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
   * @param CObjectInterface::ContainerList listOfContainer
   * @param  const CDataModel* pDataModel
   * @return bool success
   */
  virtual bool compile(CObjectInterface::ContainerList listOfContainer);

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

  std::set<COutputInterface *> getInterfaces() const;

protected:
  /**
   * Refresh all objects
   */
  void applyUpdateSequence();

  /**
   * Compile the object refresh list
   * @param const CObjectInterface::ContainerList & listOfContainer
   * @return bool success
   */
  bool compileUpdateSequence(const CObjectInterface::ContainerList & listOfContainer);

  // Attributes
protected:
  /**
   * A list of all active output interfaces.
   */
  std::set< COutputInterface * > mInterfaces;

  /**
   * Points to the master handler. The master handler is responsible for the
   * and object updates and all the output.
   */
  COutputHandler * mpMaster;

  /**
   * An ordered list of refresh methods needed by the master
   */
  CCore::CUpdateSequence mUpdateSequence;

  /**
   * A pointer to the math container
   */
  const CMathContainer * mpContainer;
};
#endif
