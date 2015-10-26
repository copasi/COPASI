// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoReactionData.cpp
 *
 *  Created on: 15 Aug 2014
 *      Author: dada
 */

#include <QtCore/QList>

#include <copasi/model/CModel.h>
#include <copasi/model/CMetab.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CReactionInterface.h>
#include <copasi/model/CChemEqInterface.h>

#include <copasi/undoFramework/UndoSpeciesData.h>
#include <copasi/undoFramework/UndoReactionData.h>


UndoReactionData::UndoReactionData(const std::string &key  /*= ""*/,
                                   const std::string &name /*= ""*/,
                                   const std::string &type /*= ""*/)
  : UndoData(key, name, type)
  , mpRi(NULL)
  , mSpeciesDependencyObjects(new QList <UndoSpeciesData*>())
{
}

UndoReactionData::~UndoReactionData()
{
  pdelete(mSpeciesDependencyObjects);
}

CReaction *UndoReactionData::createReactionFromData(CModel *pModel)
{
  if (pModel == NULL) return NULL;

  CReaction* pRea = pModel->createReaction(getName());

  if (pRea == NULL) return NULL;

  CChemEqInterface *chem = new CChemEqInterface(pModel);
  chem->setChemEqString(getRi()->getChemEqString());
  chem->writeToChemEq(pRea->getChemEq());
  getRi()->createMetabolites();
  getRi()->createOtherObjects();
  getRi()->writeBackToReaction(pRea);

  return pRea;

}

void UndoReactionData::restoreDependentObjects(CModel *pModel)
{
  if (pModel == NULL) return;

  UndoData::restoreDependentObjects(pModel, getSpeciesDependencyObjects());
}

CReactionInterface *UndoReactionData::getRi() const
{
  return mpRi;
}

void UndoReactionData::setRi(CReactionInterface *pRi)
{
  mpRi = pRi;
}

QList<UndoSpeciesData*> *UndoReactionData::getSpeciesDependencyObjects() const
{
  return mSpeciesDependencyObjects;
}
