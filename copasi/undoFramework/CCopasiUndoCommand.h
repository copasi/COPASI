// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CCopasiUndoCommand.h
 *
 *  Created on: 3 Jul 2014
 *      Author: dada
 */

#include <QUndoCommand>
#include <QModelIndex>

#ifndef CCOPASIUNDOCOMMAND_H_
#define CCOPASIUNDOCOMMAND_H_

#include <set>

typedef QPair<int, int> PathItem;
typedef QList<PathItem> Path;

class CCopasiObject;
class UndoData;
class UndoSpecieData;
class UndoReactionData;
class UndoGlobalQuantityData;
class UndoEventData;

class CCopasiUndoCommand : public QUndoCommand
{
public:
  /**
   *  The valid command type for Undo History
   */
  enum Type
  {
    COMPARTMENTCREATE = 0 , //creation of single compartment
    EVENTCREATE, //creation of single event
    GLOBALQUANTITYCREATE, //creation of single global quantity
    REACTIONCREATE, //creation of single reaction
    SPECIECREATE, //creation of single species
    COMPARTMENTDELETE, //deletion of single compartment
    EVENTDELETE, //deletion of single event
    GLOBALQUANTITYDELETE, //deletion of single global quantity
    REACTIONDELETE, //deletion of single reaction
    SPECIEDELETE, //deletion of single species
    COMPARTMENTINSERT, //insert compartment
    EVENTINSERT, //insert event
    GLOBALQUANTITYINSERT, //insert global quantity
    REACTIONINSERT, //insert reaction
    SPECIEINSERT, //insert species
    COMPARTMENTREMOVE, //remove compartment
    EVENTREMOVE, //remove event
    GLOBALQUANTITYREMOVE, //remove global quantity
    REACTIONREMOVE, //remove reaction
    SPECIEREMOVE, //remove species
    COMPARTMENTREMOVEALL, //remove all compartment
    EVENTREMOVEALL, //remove all event
    GLOBALQUANTITYREMOVEALL, //remove all global quantity
    REACTIONREMOVEALL, //remove all reaction
    SPECIEREMOVEALL, //remove all species
    COMPARTMENTDATACHANGE, //change compartment data
    EVENTDATACHANGE, //change event data
    GLOBALQUANTITYDATACHANGE, //change global quantity data
    REACTIONDATACHANGE, //change reaction data
    SPECIEDATACHANGE, //change species data
    REACTIONLINEEDITCHANGE, //change reaction data
    SPECIESTYPECHANGE, //change reaction data
    SPECIESTYPECHANG
  };
  //change of species type
  /**
   * Retrieve the type of the command.
   * @return const CCopasiUndoCommand::Type & type
   */
  const CCopasiUndoCommand::Type & getType() const;
  /**
   * Set the type
   * @param const CCopasiUndoCommand::Type & type
   */
  virtual void setType(const CCopasiUndoCommand::Type & type);
  /**
   * Retrieve the Undo Data associated with this command.
   * @return UndoData *undoData
   */
  virtual UndoData *getUndoData() const;
  CCopasiUndoCommand();
  virtual ~CCopasiUndoCommand();
  virtual void undo() = 0;
  virtual void redo() = 0;
  Path pathFromIndex(const QModelIndex & index);
  QModelIndex pathToIndex(const Path & path, const QAbstractItemModel *model);
  void setDependentObjects(const std::set<const CCopasiObject*> & deletedObjects);
  QList<UndoReactionData*> *getReactionData() const;
  QList<UndoSpecieData*> *getSpecieData() const;
  void setReactionData(QList<UndoReactionData*> *reactionData);
  void setSpecieData(QList<UndoSpecieData*> *specieData);
  QList<UndoGlobalQuantityData*> *getGlobalQuantityData() const;
  void setGlobalQuantityData(QList<UndoGlobalQuantityData*> *globalQuantityData);
  QList<UndoEventData*> *getEventData() const;
  void setEventData(QList<UndoEventData*> *eventData);
  bool isUndoState() const;
  void setUndoState(bool undoState);
  std::string getEntityType() const;
  std::string getNewValue() const;
  std::string getOldValue() const;
  std::string getProperty() const;
  void setEntityType(std::string entityType);
  void setNewValue(std::string newValue);
  void setOldValue(std::string oldValue);
  void setProperty(std::string property);
  std::string getAction() const;
  void setAction(std::string action);
  std::string getName() const;
  void setName(std::string name);

protected:
  QList<UndoSpecieData*> *mpSpecieData;
  QList<UndoReactionData*> *mpReactionData;
  QList<UndoGlobalQuantityData*> *mpGlobalQuantityData;
  QList<UndoEventData*> *mpEventData;
  /**
   *  Type of the undo command.
   */
  CCopasiUndoCommand::Type mType;
private:
  bool undoState;
  std::string  mNewValue;
  std::string  mOldValue;
  std::string mProperty;
  std::string  mEntityType;
  std::string mAction;
  std::string mName;
};

#endif /* CCOPASIUNDOCOMMAND_H_ */
