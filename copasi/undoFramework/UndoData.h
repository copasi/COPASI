// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoData.h
 *
 *  Created on: 15 Aug 2014
 *      Author: dada
 */

#ifndef UNDODATA_H_
#define UNDODATA_H_

#include <QObject>
#include <string>

class CModel;
class CCopasiObject;
class UndoGlobalQuantityData;
class UndoReactionData;
class UndoEventData;
class UndoSpeciesData;
class UndoCompartmentData;
class UndoDependentData;

/**
 * Base class for all COPASI undo data
 */
class UndoData : public QObject
{
  Q_OBJECT

public:
  UndoData(const std::string &key = "",
           const std::string &name = "",
           const std::string &type = "");

  virtual ~UndoData();

  virtual CCopasiObject* createObjectIn(CModel* pModel);

  virtual CCopasiObject* restoreObjectIn(CModel* pModel);

  virtual void fillObject(CModel* pModel);

  /**
   * when overidden in subclasses this function
   * will restore dependent objects.
   *
   * This function both creates the dependent objects
   * and sets all their values.
   */
  virtual void restoreDependentObjects(CModel* pModel);

  /**
   * Creates all dependent objects, but does not set their values
   */
  virtual void createDependentObjects(CModel* pModel);

  /**
   * Fills the dependent object with their values.
   */
  virtual void fillDependentObjects(CModel* pModel);


  /**
   * @return the key of the object
   */
  const std::string &getKey() const;

  /**
   * sets the key for the object
   * @param key the key
   */
  void setKey(const std::string &key);

  /**
   * @return true if key is set, false otherwise.
   */
  bool hasKey() const;

  /**
   * @return the name of the object
   */
  const std::string &getName() const;

  /**
   * sets the name
   * @param name the name
   */
  void setName(const std::string & name);

  /**
   * @return trye if name is set, false otherwise
   */
  bool hasName() const;

  /**
   * @return the type of the object
   */
  const std::string &getType() const;

  /**
   * @param type the type
   */
  void setType(const std::string &type);

protected:
  UndoDependentData *mpData;
  std::string mKey;
  std::string mName;
  std::string mType;
};

#endif /* UNDODATA_H_ */
