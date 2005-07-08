/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CCallParameters.cpp,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/07/08 12:32:45 $
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
        mPointers[i].vector = new std::vector<const C_FLOAT64 *>(*src.mPointers[i].vector);
        mObjects[i].vector = new std::vector<const CCopasiObject *>(*src.mObjects[i].vector);
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
          mObjects[i].vector = new std::vector<const CCopasiObject *>;
          mPointers[i].vector = new std::vector<const C_FLOAT64 *>;
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
          if ((*mPointers[i].vector)[j] == NULL)
            fatalError();

        if (jmax != mObjects[i].vector->size()) fatalError();

        for (j = 0; j < jmax; j++)
          if ((*mObjects[i].vector)[j] == NULL)
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
  mObjects[index].vector->push_back(obj);

  mPointers[index].vector->push_back((const C_FLOAT64*)obj->getReference());
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
              Objects.push_back((*mObjects[index].vector)[i]);
          }
      }

    return Objects;
  }

// CCallParameters<CCopasiObject> & CFunctionParameterMap::getObjects() {return mObjects;};

const CCallParameters<CCopasiObject> & CFunctionParameterMap::getObjects() const
{return mObjects;};

const CFunctionParameters & CFunctionParameterMap::getFunctionParameters() const
  {return * mpFunctionParameters;};
