// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CFixLocalReactionParameters.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 00:34:41 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CFixLocalReactionParameters.h"

#include "model/CModel.h"
#include "model/CReaction.h"
#include "utilities/CCopasiParameterGroup.h"
#include "function/CExpression.h"

CFixLocalReactionParameters::CFixLocalReactionParameters():
    mpModel(NULL),
    mChanges()
{}

CFixLocalReactionParameters::~CFixLocalReactionParameters()
{}

void CFixLocalReactionParameters::fixModel(CModel * pModel)
{
  if (pModel == NULL) return;

  mpModel = pModel;
  checkModel();

  if (mChanges.size() == 0) return;

  changeModel();
}

void CFixLocalReactionParameters::checkModel()
{
  // Clear recorded changes
  mChanges.clear();

  // Check for all reactions
  CCopasiVector< CReaction >::const_iterator itReaction = mpModel->getReactions().begin();
  CCopasiVector< CReaction >::const_iterator endReaction = mpModel->getReactions().end();

  for (; itReaction != endReaction; ++itReaction)
    {
      // Check for all local parameters
      CCopasiParameterGroup::index_iterator itParameter = (*itReaction)->getParameters().beginIndex();
      CCopasiParameterGroup::index_iterator endParameter = (*itReaction)->getParameters().endIndex();

      for (; itParameter != endParameter; ++itParameter)
        {
          // Check for all entities' expressions and inititial expressions
          // whether the CN of the parameter appears in the infix.
          // Note '>' is already properly escaped in the CN
          std::string CN = "<" + (*itParameter)->getCN() + ",Reference=Value>";

          CModelEntity **ppEntity = mpModel->getStateTemplate().getEntities();
          CModelEntity **ppEntityEnd = ppEntity + mpModel->getStateTemplate().size();
          for (; ppEntity != ppEntityEnd; ++ppEntity)
            {
              if ((*ppEntity)->getExpression().find(CN) != std::string::npos)
                mChanges.insert
                (std::pair< CCopasiParameter *, CExpression * >(*itParameter, (*ppEntity)->getExpressionPtr()));

              if ((*ppEntity)->getInitialExpression().find(CN) != std::string::npos)
                mChanges.insert
                (std::pair< CCopasiParameter *, CExpression * >(*itParameter, (*ppEntity)->getInitialExpressionPtr()));
            }
        }
    }
}

void CFixLocalReactionParameters::changeModel()
{
  CCopasiParameter * pParameter = NULL;
  CModelValue * pModelValue = NULL;
  CReaction * pReaction = NULL;

  std::stringstream NameStream;
  std::stringstream Message;

  std::string OldCN;
  std::string NewCNBase;
  std::string NewCN;
  std::string Infix;

  std::string::size_type Start;

  // Loop through all changes.
  std::multimap< CCopasiParameter *, CExpression * >::const_iterator itChanges = mChanges.begin();
  std::multimap< CCopasiParameter *, CExpression * >::const_iterator endChanges = mChanges.end();

  for (; itChanges != endChanges; ++itChanges)
    {
      if (pParameter != itChanges->first)
        {
          // We have a new parameter
          pParameter = itChanges->first;
          OldCN = "<" + pParameter->getCN() + ",Reference=";

          // Create a global quantity of type FIXED.
          std::string Name = pParameter->getObjectName();
          pReaction = static_cast< CReaction * >(pParameter->getObjectAncestor("Reaction"));
          Name += "{" + pReaction->getObjectName() + "}";

          pModelValue = mpModel->createModelValue(Name,
                                                  *pParameter->getValue().pDOUBLE);

          // In case the created name is not unique we append _n with increasing n
          // until we succeed;
          C_INT32 index = 0;
          while (pModelValue == NULL)
            {
              NameStream.str("");
              NameStream << Name << "_" << index++;
              pModelValue = mpModel->createModelValue(NameStream.str(),
                                                      *pParameter->getValue().pDOUBLE);
            }
          NewCNBase = "<" + pModelValue->getCN() + ",Reference=";

          // If the parameter is actually used in the reaction
          // it is changed to the global quantity.
          if (pReaction->isLocalParameter(pParameter->getObjectName()))
            pReaction->setParameterMapping(pParameter->getObjectName(), pModelValue->getKey());

          Message << "  " << pParameter->getObjectName() << " in " << pReaction->getObjectName()
          << " is replaced by " << pModelValue->getObjectName() << std::endl;
        }

      // We need to destinguish between initial and other expressions.
      if (itChanges->second->getObjectName().compare(0, 7, "Initial") == 0)
        NewCN = NewCNBase + "Initial";
      else
        NewCN = NewCNBase;

      // Replace the OldCN of the parameter with the NewCN of global quantity in all expressions.
      Infix = itChanges->second->getInfix();

      // There may be more than one occurance.
      Start = 0;
      while ((Start = Infix.find(OldCN), Start) != std::string::npos)
        Infix.replace(Start, OldCN.length(), NewCN);

      itChanges->second->setInfix(Infix);
    }

  CCopasiMessage(CCopasiMessage::WARNING, MCXML + 14, Message.str().c_str());
}
