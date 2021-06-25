// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CKinFunction
 *
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2002
 */

#undef yyFlexLexer
#define yyFlexLexer CKinFunctionFlexLexer

#include <sstream>

#include "copasi/copasi.h"

#include "CKinFunction.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/core/CDataObject.h"
#include "copasi/utilities/utility.h"

CKinFunction::CKinFunction(const std::string & name,
                           const CDataContainer * pParent):
  CFunction(name, pParent, CFunction::UserDefined),
  mNodes(),
  ObjList(),
  mNidx(0)

{
  CONSTRUCTOR_TRACE;
}

CKinFunction::CKinFunction(const CFunction & src,
                           const CDataContainer * pParent,
                           CReadConfig * configBuffer):
  CFunction(src, pParent),
  mNodes(),
  ObjList(),
  mNidx(0)
{
  CONSTRUCTOR_TRACE;

  if (configBuffer)
    {
      C_INT32 i, Size;
      configBuffer->getVariable("Nodes", "C_INT32", &Size);
      mNodes.resize(Size);

      for (i = 0; i < Size; i++)
        {
          mNodes[i] = new CNodeK;
          mNodes[i]->load(*configBuffer);
        }

      createParameters();

      cleanupNodes();
    }

  //  compile();
}

CKinFunction::CKinFunction(const CKinFunction & src,
                           const CDataContainer * pParent):
  CFunction(src, pParent),
  mNodes(src.mNodes),
  ObjList(src.ObjList),
  mNidx(src.mNidx)
{
  CONSTRUCTOR_TRACE;
  //compile();
}

CKinFunction::~CKinFunction()
{
  /*  int i;
    for (i=0; i<ObjList.size(); i++)
     ObjList[i] = NULL;
  */
  ObjList.clear();
  cleanup();
  DESTRUCTOR_TRACE;
}

void CKinFunction::cleanup()
{
  cleanupNodes();
}

// This is only used when reading Gepasi Files
void CKinFunction::createParameters()
{
  CDataVectorN < CFunctionParameter > Substrates;
  CDataVectorN < CFunctionParameter > Products;
  CDataVectorN < CFunctionParameter > Modifiers;
  CDataVectorN < CFunctionParameter > Parameters;
  CDataVectorN < CFunctionParameter > Volumes;

  size_t i, imax = mNodes.size();

  CFunctionParameter *pParameter;

  for (i = 0; i < imax; i++)
    {
      if (mNodes[i]->getType() == N_IDENTIFIER)
        {
          // We need to check that we have no reserved name.
          const char *Reserved[] =
          {
            "pi", "exponentiale", "true", "false", "infinity", "nan",
            "PI", "EXPONENTIALE", "TRUE", "FALSE", "INFINITY", "NAN"
          };

          std::string Name = mNodes[i]->getName();
          size_t j, jmax = 12;

          for (j = 0; j < jmax; j++)
            if (Name == Reserved[j]) break;

          if (j != jmax)
            {
              // It is save to prepend the identifyer with '_' since this is not allowed in
              // Gepasi but within COPASI.
              std::string OldName = Name;
              Name = "_" + Name;

              // We have to replace the corresponding CEvaluationNodes to reflect the change.
              std::vector< CEvaluationNode * >::iterator it = mpNodeList->begin();
              std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

              for (; it != end; ++it)
                if ((*it)->mainType() == CEvaluationNode::MainType::CONSTANT &&
                    (*it)->getData() == OldName)
                  (*it)->setData(Name);

              // The Infix has changed we need to update it.
              setInfix(getRoot()->buildInfix());
            }

          pParameter = new CFunctionParameter(Name);
          pParameter->setType(CFunctionParameter::DataType::FLOAT64);

          switch (mNodes[i]->getSubtype())
            {
              case N_SUBSTRATE:
                pParameter->setUsage(CFunctionParameter::Role::SUBSTRATE);

                if (Substrates.getIndex(pParameter->getObjectName()) == C_INVALID_INDEX)
                  Substrates.add(pParameter, false);
                else
                  pdelete(pParameter);

                break;

              case N_PRODUCT:
                pParameter->setUsage(CFunctionParameter::Role::PRODUCT);

                if (Products.getIndex(pParameter->getObjectName()) == C_INVALID_INDEX)
                  Products.add(pParameter, false);
                else
                  pdelete(pParameter);

                break;

              case N_MODIFIER:
                pParameter->setUsage(CFunctionParameter::Role::MODIFIER);

                if (Modifiers.getIndex(pParameter->getObjectName()) == C_INVALID_INDEX)
                  Modifiers.add(pParameter, false);
                else
                  pdelete(pParameter);

                break;

              case N_KCONSTANT:
              case N_NOP:
                pParameter->setUsage(CFunctionParameter::Role::PARAMETER);

                if (Parameters.getIndex(pParameter->getObjectName()) == C_INVALID_INDEX)
                  Parameters.add(pParameter, false);
                else
                  pdelete(pParameter);

                break;

              case N_VOLUME:
                pParameter->setUsage(CFunctionParameter::Role::VOLUME);

                if (Volumes.getIndex(pParameter->getObjectName()) == C_INVALID_INDEX)
                  Volumes.add(pParameter, false);
                else
                  pdelete(pParameter);

                break;

              default:
                pdelete(pParameter);
                fatalError();
            }
        }
    }

  getVariables().cleanup();

  imax = Substrates.size();

  for (i = 0; i < imax; i++)
    getVariables().add(&Substrates[i], true);

  Substrates.cleanup();

  imax = Products.size();

  for (i = 0; i < imax; i++)
    getVariables().add(&Products[i], true);

  Products.cleanup();

  imax = Modifiers.size();

  for (i = 0; i < imax; i++)
    getVariables().add(&Modifiers[i], true);

  Modifiers.cleanup();

  imax = Parameters.size();

  for (i = 0; i < imax; i++)
    getVariables().add(&Parameters[i], true);

  Parameters.cleanup();

  imax = Volumes.size();

  for (i = 0; i < imax; i++)
    getVariables().add(&Volumes[i], true);

  Volumes.cleanup();
}

std::vector< CNodeK * > & CKinFunction::getNodes() {return mNodes;}

void CKinFunction::cleanupNodes()
{
  size_t i, imax = mNodes.size();

  for (i = 0; i < imax; i++)
    if (mNodes[i]) delete mNodes[i];

  mNodes.clear();
  return;
}
