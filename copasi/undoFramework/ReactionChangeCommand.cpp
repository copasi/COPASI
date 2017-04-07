// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * ReactionLineEditChangedCommand.cpp
 *
 *  Created on: 25 Jul 2014
 *      Author: dada
 */

#include "copasi.h"

#include "model/CReaction.h"
#include "model/CModel.h"

#include "report/CCopasiRootContainer.h"

#include "UI/ReactionsWidget1.h"
#include "UI/qtUtilities.h"
#include "UI/CQCopasiApplication.h"
#include "UI/copasiui3window.h"
#include "UI/DataModelGUI.h"

#include "ReactionChangeCommand.h"

ReactionChangeCommand::ReactionChangeCommand(
  CCopasiUndoCommand::Type type,
  const QVariant& oldValue,
  const QVariant& newValue,
  ReactionsWidget1 *pReactionWidget,
  CReaction* pReaction,
  const QVariant& oldSecondValue /* = ""*/,
  const QVariant& newSecondValue /*= ""*/)
  : CCopasiUndoCommand("Reaction", type, "Change", "Reaction",
                       TO_UTF8(newValue.toString()),
                       TO_UTF8(oldValue.toString()),
                       pReaction->getObjectName())
  , mpReactionWidget(pReactionWidget)
  , mKey(pReaction->getKey())
  , mOldValue(oldValue)
  , mNewValue(newValue)
  , mOldSecondValue(oldSecondValue)
  , mNewSecondValue(newSecondValue)
  , mCreatedObjects()
{

  switch (type)
    {
      case REACTION_SCHEME_CHANGE:
        setText(": Changed reaction scheme");
        setProperty("Reaction Scheme");
        break;

      case REACTION_FAST_CHANGE:
        setText(": Changed reaction fast flag");
        setProperty("Fast Flag");
        break;

      case REACTION_REVERSIBLE_CHANGE:
        setText(": Changed reaction reversibility");
        setProperty("Reversible Flag");
        break;

      case REACTION_FUNCTION_CHANGE:
        setText(": Changed kinetic law");
        setProperty("Function");
        break;

      case REACTION_LOCAL_PARAMETER_VALUE_CHANGE:
        setText(": Changed local parameter value");
        setProperty("Function");
        break;

      case REACTION_MAPPING_VOLUME_CHANGE:
        setText(": Changed volume mapping");
        setProperty("Function");
        break;

      case REACTION_MAPPING_SPECIES_CHANGE:
        setText(": Changed species mapping");
        setProperty("Function");
        break;

      case REACTION_MAPPING_PARAMETER_CHANGE:
        setText(": Changed parameter mapping");
        setProperty("Function");
        break;

      case REACTION_ADD_NOISE_CHANGE:
        setText(": Changed adding noise");
        setProperty("Add Noise");
        break;

      case REACTION_NOISE_EXPRESSION_CHANGE:
        setText(": Changed noise expression");
        setProperty("Noise Expression");
        break;

      default:
        break;
    }
}

void
ReactionChangeCommand::redo()
{
  mpReactionWidget->changeReaction(mKey, mType, mNewValue, mNewSecondValue, this);
}

void
ReactionChangeCommand::undo()
{
  mpReactionWidget->changeReaction(mKey, mType, mOldValue, mOldSecondValue, this);
}

void
ReactionChangeCommand::removeCreatedObjects(const std::vector< std::string > & createdObjects)
{
  std::vector<std::string>::const_iterator it = createdObjects.begin();

  for (; it != createdObjects.end(); ++it)
    {
      const std::string& key = *it;
      CCopasiObject* pObject = CCopasiRootContainer::getKeyFactory()->get(key);

      if (pObject == NULL) continue;

      const std::string& objectType = pObject->getObjectType();

      if (objectType == "Compartment")
        {
          static_cast< CModel * >(pObject->getObjectAncestor("Model"))->removeCompartment(key, true);
        }
      else if (objectType == "Metabolite")
        {
          static_cast< CModel * >(pObject->getObjectAncestor("Model"))->removeMetabolite(key, true);
        }
      else
        {
          pObject->getObjectParent()->remove(pObject);
        }
    }
}

void
ReactionChangeCommand::setCreatedObjects(
  const std::vector<std::string> &createdObjects)
{
  mCreatedObjects = createdObjects;
}

const std::vector<std::string>&
ReactionChangeCommand::getCreatedObjects() const
{
  return mCreatedObjects;
}

ReactionChangeCommand::~ReactionChangeCommand()
{
}
