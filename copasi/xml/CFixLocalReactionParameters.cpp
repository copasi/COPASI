// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "CFixLocalReactionParameters.h"

#include "copasi/model/CModel.h"
#include "copasi/model/CReaction.h"
#include "copasi/utilities/CCopasiParameterGroup.h"
#include "copasi/function/CExpression.h"

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
  CDataVector< CReaction >::const_iterator itReaction = mpModel->getReactions().begin();
  CDataVector< CReaction >::const_iterator endReaction = mpModel->getReactions().end();

  for (; itReaction != endReaction; ++itReaction)
    {
      // Check for all local parameters
      CCopasiParameterGroup::index_iterator itParameter = itReaction->getParameters().beginIndex();
      CCopasiParameterGroup::index_iterator endParameter = itReaction->getParameters().endIndex();

      for (; itParameter != endParameter; ++itParameter)
        {
          // Check for all entities' expressions and initial expressions
          // whether the CN of the parameter appears in the infix.
          // Note '>' is already properly escaped in the CN
          std::string CN = "<" + (*itParameter)->getCN() + ",Reference=Value>";

          const CModelEntity *const*ppEntity = mpModel->getStateTemplate().getEntities().array();
          const CModelEntity *const*ppEntityEnd = ppEntity + mpModel->getStateTemplate().size();

          for (; ppEntity != ppEntityEnd; ++ppEntity)
            {
              if ((*ppEntity)->getExpression().find(CN) != std::string::npos)
                mChanges.insert
                (std::pair< CCopasiParameter * const, const CExpression * >(*itParameter, (*ppEntity)->getExpressionPtr()));

              if ((*ppEntity)->getInitialExpression().find(CN) != std::string::npos)
                mChanges.insert
                (std::pair< CCopasiParameter * const, const CExpression * >(*itParameter, (*ppEntity)->getInitialExpressionPtr()));
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
  std::multimap< CCopasiParameter *, const CExpression * >::const_iterator itChanges = mChanges.begin();
  std::multimap< CCopasiParameter *, const CExpression * >::const_iterator endChanges = mChanges.end();

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

          pModelValue = mpModel->createModelValue(Name, pParameter->getValue< C_FLOAT64 >());

          // In case the created name is not unique we append _n with increasing n
          // until we succeed;
          C_INT32 index = 0;

          while (pModelValue == NULL)
            {
              NameStream.str("");
              NameStream << Name << "_" << index++;
              pModelValue = mpModel->createModelValue(NameStream.str(), pParameter->getValue< C_FLOAT64 >());
            }

          NewCNBase = "<" + pModelValue->getCN() + ",Reference=";

          // If the parameter is actually used in the reaction
          // it is changed to the global quantity.
          if (pReaction->isLocalParameter(pParameter->getObjectName()))
            {
              std::vector< const CDataObject * > Objects(1, pModelValue);
              pReaction->setParameterObjects(pParameter->getObjectName(), Objects);
            }

          Message << "  " << pParameter->getObjectName() << " in " << pReaction->getObjectName()
                  << " is replaced by " << pModelValue->getObjectName() << std::endl;
        }

      // We need to distinguish between initial and other expressions.
      if (itChanges->second->getObjectName().compare(0, 7, "Initial") == 0)
        NewCN = NewCNBase + "Initial";
      else
        NewCN = NewCNBase;

      // Replace the OldCN of the parameter with the NewCN of global quantity in all expressions.
      Infix = itChanges->second->getInfix();

      // There may be more than one occurrence.
      Start = 0;

      while ((Start = Infix.find(OldCN), Start) != std::string::npos)
        Infix.replace(Start, OldCN.length(), NewCN);

      const_cast< CExpression * >(itChanges->second)->setInfix(Infix);
    }

  CCopasiMessage(CCopasiMessage::WARNING, MCXML + 14, Message.str().c_str());
}
