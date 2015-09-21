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

class UndoReactionData: public UndoData
{
public:
  UndoReactionData(const std::string &key = "",
                   const std::string &name = "",
                   const std::string &type = "");
  virtual ~UndoReactionData();

  CReactionInterface *getRi() const;
  void setRi(CReactionInterface *mpRi);

  QList<UndoSpeciesData*> *getSpeciesDependencyObjects() const;
  void setSpeciesDependencyObjects(
    QList<UndoSpeciesData*> *speciesDependencyObjects);

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
