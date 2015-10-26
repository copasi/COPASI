// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoReactionData.h
 *
 *  Created on: 15 Aug 2014
 *      Author: dada
 */

#ifndef UNDOREACTIONDATA_H_
#define UNDOREACTIONDATA_H_

#include "qtUtilities.h"
#include "UndoData.h"

class CReactionInterface;
class UndoSpeciesData;

class CReaction;

class UndoReactionData: public UndoData
{
public:
  UndoReactionData(const std::string &key = "",
                   const std::string &name = "",
                   const std::string &type = "");
  virtual ~UndoReactionData();

  CReaction* createReactionFromData(CModel* pModel);

  /**
   * when overidden in subclasses this function
   * will restore dependent objects.
   */
  virtual void restoreDependentObjects(CModel* pModel);


  CReactionInterface *getRi() const;
  void setRi(CReactionInterface *mpRi);

  QList<UndoSpeciesData*> *getSpeciesDependencyObjects() const;

private:
  /**
   * pointer to the reaction interface
   */
  CReactionInterface* mpRi;

  /**
   * Pointer to species dependency objects
   */
  QList<UndoSpeciesData*> *mSpeciesDependencyObjects;
};

#endif /* UNDOREACTIONDATA_H_ */
