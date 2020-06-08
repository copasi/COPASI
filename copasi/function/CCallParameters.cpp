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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"
#include "CCallParameters.h"
#include "CFunction.h"

#include "copasi/utilities/CCopasiParameter.h"
#include "copasi/model/CModel.h"

// static
CDataObject * CFunctionParameterMap::pUnmappedObject = NULL;

//TODO: modify the constructors so that CFunctionParameterMap behaves like a CDataObject

CFunctionParameterMap::CFunctionParameterMap():
  mPointers(),
  mObjects(),
  mpFunctionParameters(NULL)
{
  if (pUnmappedObject == NULL)
    {
      C_FLOAT64 InvalidValue = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

      pUnmappedObject =
        new CCopasiParameter("unknown", CCopasiParameter::Type::DOUBLE, & InvalidValue);
    }
};

CFunctionParameterMap::CFunctionParameterMap(const CFunctionParameterMap & src):
  mPointers(src.mPointers),
  mObjects(src.mObjects),
  mpFunctionParameters(new CFunctionParameters(*src.mpFunctionParameters, NO_PARENT))
{
  size_t i, imax = mpFunctionParameters->size();

  for (i = 0; i < imax; ++i)
    if ((*mpFunctionParameters)[i]->getType() >= CFunctionParameter::DataType::VINT32)
      {
        mPointers[i].vector = new CCallParameters<C_FLOAT64>(*src.mPointers[i].vector);
        mObjects[i].vector = new CCallParameters<CDataObject>(*src.mObjects[i].vector);
      }
}

CFunctionParameterMap::~CFunctionParameterMap()
{
  clearCallParameters();
  pdelete(mpFunctionParameters)
};

void CFunctionParameterMap::initializeFromFunctionParameters(const CFunctionParameters & src)
{
  clearCallParameters();

  pdelete(mpFunctionParameters)
  mpFunctionParameters = new CFunctionParameters(src, NO_PARENT);

  initCallParameters();
}

void CFunctionParameterMap::clearCallParameters()
{
  if (mpFunctionParameters)
    {
      size_t i, imax = mpFunctionParameters->size();

      for (i = 0; i < imax; i++)
        {
          if ((*mpFunctionParameters)[i]->getType() >= CFunctionParameter::DataType::VINT32)
            {
              if (mObjects[i].vector)
                delete mObjects[i].vector;

              if (mPointers[i].vector)
                delete mPointers[i].vector;
            }
        }
    }

  mPointers.clear();
  mObjects.clear();
}

void CFunctionParameterMap::initCallParameters()
{
  size_t i, imax = mpFunctionParameters->size();

  // Resizing call the CCallParameters clear() method and initializes
  // all values to NULL.
  mPointers.resize(imax);
  mObjects.resize(imax);

  for (i = 0; i < imax; i++)
    {
      if ((*mpFunctionParameters)[i]->getType() >= CFunctionParameter::DataType::VINT32)
        {
          mObjects[i].vector = new CCallParameters<CDataObject>;
          mPointers[i].vector = new CCallParameters<C_FLOAT64>;
        }
    }
}

void CFunctionParameterMap::checkCallParameters() const
{
  size_t i, imax = mpFunctionParameters->size();
  size_t j, jmax;

  for (i = 0; i < imax; i++)
    {
      if (mPointers[i].vector == NULL)
        fatalError();

      if (mObjects[i].vector == NULL)
        fatalError();

      if ((*mpFunctionParameters)[i]->getType() < CFunctionParameter::DataType::VINT32)
        continue;

      jmax = mPointers[i].vector->size();

      for (j = 0; j < jmax; j++)
        if ((*mPointers[i].vector)[j].value == NULL)
          fatalError();

      if (jmax != mObjects[i].vector->size()) fatalError();

      for (j = 0; j < jmax; j++)
        if ((*mObjects[i].vector)[j].value == NULL)
          fatalError();
    }
}

CIssue CFunctionParameterMap::setCallParameter(const std::string paramName, const CDataObject* obj)
{
  const CFunctionParameter * pFunctionParameter;
  size_t index = findParameterByName(paramName, &pFunctionParameter);

  if (index == C_INVALID_INDEX ||
      pFunctionParameter == NULL ||
      pFunctionParameter->getType() >= CFunctionParameter::DataType::VINT32) fatalError(); // is a vector

  assert(obj->getValuePointer());
  assert(obj->hasFlag(CDataObject::ValueDbl));

  mObjects[index].value = obj;
  mPointers[index].value = (const C_FLOAT64*) obj->getValuePointer();

  bool success = true;

  switch (pFunctionParameter->getUsage())
    {
      case CFunctionParameter::Role::SUBSTRATE:
      case CFunctionParameter::Role::PRODUCT:
      case CFunctionParameter::Role::MODIFIER:
        success = dynamic_cast< const CMetab * >(obj) != NULL;
        break;

      case CFunctionParameter::Role::PARAMETER:
        success = dynamic_cast< const CCopasiParameter * >(obj) != NULL ||
                  dynamic_cast< const CModelValue * >(obj) != NULL;
        break;

      case CFunctionParameter::Role::VOLUME:
        success = dynamic_cast< const CCompartment * >(obj) != NULL;
        break;

      case CFunctionParameter::Role::TIME:
        success = dynamic_cast< const CModel * >(obj) != NULL;
        break;

      case CFunctionParameter::Role::VARIABLE:
      case CFunctionParameter::Role::TEMPORARY:
        break;
    }

  return success ? CIssue() : CIssue(CIssue::eSeverity::Error, CIssue::eKind::VariablesMismatch);
}

CIssue CFunctionParameterMap::addCallParameter(const std::string paramName, const CDataObject* obj)
{
  const CFunctionParameter * pFunctionParameter;
  size_t index = findParameterByName(paramName, &pFunctionParameter);

  if (index == C_INVALID_INDEX ||
      pFunctionParameter == NULL ||
      pFunctionParameter->getType() < CFunctionParameter::DataType::VINT32) fatalError(); // is not a vector

  assert(obj->getValuePointer());
  assert(obj->hasFlag(CDataObject::ValueDbl));

  mObjects[index].vector->push_back(obj);
  mPointers[index].vector->push_back((const C_FLOAT64*) obj->getValuePointer());

  bool success = true;

  switch (pFunctionParameter->getUsage())
    {
      case CFunctionParameter::Role::SUBSTRATE:
      case CFunctionParameter::Role::PRODUCT:
      case CFunctionParameter::Role::MODIFIER:
        success = dynamic_cast< const CMetab * >(obj) != NULL;
        break;

      case CFunctionParameter::Role::PARAMETER:
        success = dynamic_cast< const CCopasiParameter * >(obj) != NULL ||
                  dynamic_cast< const CModelValue * >(obj) != NULL;
        break;

      case CFunctionParameter::Role::VOLUME:
        success = dynamic_cast< const CCompartment * >(obj) != NULL;
        break;

      case CFunctionParameter::Role::TIME:
        success = dynamic_cast< const CModel * >(obj) != NULL;
        break;

      case CFunctionParameter::Role::VARIABLE:
      case CFunctionParameter::Role::TEMPORARY:
        break;
    }

  return success ? CIssue() : CIssue(CIssue::eSeverity::Error, CIssue::eKind::VariablesMismatch);
}

void CFunctionParameterMap::clearCallParameter(const std::string paramName)
{
  const CFunctionParameter * pFunctionParameter;
  size_t index = findParameterByName(paramName, &pFunctionParameter);

  if (index == C_INVALID_INDEX ||
      pFunctionParameter == NULL ||
      pFunctionParameter->getType() < CFunctionParameter::DataType::VINT32)
    fatalError(); // is not a vector

  // TODO: check type of object
  mObjects[index].vector->clear();
  mPointers[index].vector->clear();
}

size_t CFunctionParameterMap::findParameterByName(const std::string & name,
    const CFunctionParameter ** ppFunctionParameter) const
{
  return mpFunctionParameters->findParameterByName(name, ppFunctionParameter);
}

CCallParameters<C_FLOAT64> & CFunctionParameterMap::getPointers()
{
  return mPointers;
}

const CCallParameters<C_FLOAT64> & CFunctionParameterMap::getPointers() const
{
  return mPointers;
}

std::vector< const CDataObject * > CFunctionParameterMap::getObjects(const size_t & index) const
{
  std::vector< const CDataObject * > Objects;

  if (index != C_INVALID_INDEX)
    {
      if ((*mpFunctionParameters)[index]->getType() < CFunctionParameter::DataType::VINT32)
        Objects.push_back(mObjects[index].value);
      else
        {
          size_t i, imax = mObjects[index].vector->size();

          for (i = 0; i < imax; i++)
            Objects.push_back((*mObjects[index].vector)[i].value);
        }
    }

  return Objects;
}

// CCallParameters<CDataObject> & CFunctionParameterMap::getObjects() {return mObjects;};

const CCallParameters<CDataObject> & CFunctionParameterMap::getObjects() const
{return mObjects;};

const CFunctionParameters & CFunctionParameterMap::getFunctionParameters() const
{return * mpFunctionParameters;};
