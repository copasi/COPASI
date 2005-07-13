/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CCallParameters.cpp,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/13 17:24:16 $
   End CVS Header */

#include "copasi.h"
#include "CCallParameters.h"
#include "CFunction.h"

//TODO: modify the constructors so that CFunctionParameterMap behaves like a CCopasiObject

CFunctionParameterMap::CFunctionParameterMap():
    mPointers(),
    mObjects(),
    mpFunctionParameters(NULL)
{};

CFunctionParameterMap::CFunctionParameterMap(const CFunctionParameterMap & src):
    mPointers(src.mPointers),
    mObjects(src.mObjects),
    mpFunctionParameters(new CFunctionParameters(*src.mpFunctionParameters))
{
  C_INT32 i, imax = mpFunctionParameters->size();
  for (i = 0; i < imax; ++i)
    if ((*mpFunctionParameters)[i]->getType() >= CFunctionParameter::VINT32)
      {
        mPointers[i].vector = new std::vector< CCallParameters<C_FLOAT64>::UType >(*src.mPointers[i].vector);
        mObjects[i].vector = new std::vector< CCallParameters<CCopasiObject>::UType >(*src.mObjects[i].vector);
      }
}

CFunctionParameterMap::~CFunctionParameterMap()
{
  pdelete(mpFunctionParameters)
};

void CFunctionParameterMap::initializeFromFunctionParameters(const CFunctionParameters & src)
{
  clearCallParameters();

  pdelete(mpFunctionParameters)
  mpFunctionParameters = new CFunctionParameters(src);

  initCallParameters();
}

void CFunctionParameterMap::clearCallParameters()
{
  if (mpFunctionParameters)
    {
      unsigned C_INT32 i, imax = mpFunctionParameters->size();

      for (i = 0; i < imax; i++)
        {
          if ((*mpFunctionParameters)[i]->getType() >= CFunctionParameter::VINT32)
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
  unsigned C_INT32 i, imax = mpFunctionParameters->size();

  // Resizing call the CCallParameters clear() method and initializes
  // all values to NULL.
  mPointers.resize(imax);
  mObjects.resize(imax);

  for (i = 0; i < imax; i++)
    {
      if ((*mpFunctionParameters)[i]->getType() >= CFunctionParameter::VINT32)
        {
          mObjects[i].vector = new std::vector< CCallParameters<CCopasiObject>::UType >;
          mPointers[i].vector = new std::vector< CCallParameters<C_FLOAT64>::UType >;
        }
    }
}

void CFunctionParameterMap::checkCallParameters() const
  {
    unsigned C_INT32 i, imax = mpFunctionParameters->size();
    unsigned C_INT32 j, jmax;

    for (i = 0; i < imax; i++)
      {
        if (mPointers[i].vector == NULL)
          fatalError();
        if (mObjects[i].vector == NULL)
          fatalError();

        if ((*mpFunctionParameters)[i]->getType() < CFunctionParameter::VINT32)
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

void CFunctionParameterMap::setCallParameter(const std::string paramName, const CCopasiObject* obj)
{
  CFunctionParameter::DataType type;
  C_INT32 index = findParameterByName(paramName, type);

  if (type >= CFunctionParameter::VINT32) fatalError(); // is a vector

  // TODO: check type of object
  mObjects[index].value = obj;

  mPointers[index].value = (const C_FLOAT64*) obj->getReference();
}

void CFunctionParameterMap::addCallParameter(const std::string paramName, const CCopasiObject* obj)
{
  CFunctionParameter::DataType type;
  C_INT32 index = findParameterByName(paramName, type);

  if (type < CFunctionParameter::VINT32) fatalError(); // is not a vector

  // TODO: check type of object
  CCallParameters<CCopasiObject>::UType Object;
  Object.value = obj;
  mObjects[index].vector->push_back(Object);

  CCallParameters<C_FLOAT64>::UType Pointer;
  Pointer.value = (const C_FLOAT64*) obj->getReference();
  mPointers[index].vector->push_back(Pointer);
}

void CFunctionParameterMap::clearCallParameter(const std::string paramName)
{
  CFunctionParameter::DataType type;
  C_INT32 index = findParameterByName(paramName, type);

  if (type < CFunctionParameter::VINT32) fatalError(); // is not a vector

  // TODO: check type of object
  mObjects[index].vector->clear();

  mPointers[index].vector->clear();
}

unsigned C_INT32 CFunctionParameterMap::findParameterByName(const std::string & name,
    CFunctionParameter::DataType & dataType) const
  {
    return mpFunctionParameters->findParameterByName(name, dataType);
  }

CCallParameters<C_FLOAT64> & CFunctionParameterMap::getPointers()
{return mPointers;};

std::vector< const CCopasiObject * > CFunctionParameterMap::getObjects(const unsigned C_INT32 & index) const
  {
    std::vector< const CCopasiObject * > Objects;

    if (index != C_INVALID_INDEX)
      {
        if ((*mpFunctionParameters)[index]->getType() < CFunctionParameter::VINT32)
          Objects.push_back(mObjects[index].value);
        else
          {
            unsigned C_INT32 i, imax = mObjects[index].vector->size();

            for (i = 0; i < imax; i++)
              Objects.push_back((*mObjects[index].vector)[i].value);
          }
      }

    return Objects;
  }

// CCallParameters<CCopasiObject> & CFunctionParameterMap::getObjects() {return mObjects;};

const CCallParameters<CCopasiObject> & CFunctionParameterMap::getObjects() const
{return mObjects;};

const CFunctionParameters & CFunctionParameterMap::getFunctionParameters() const
  {return * mpFunctionParameters;};
