/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CCallParameters.cpp,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/14 22:15:26 $
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
  std::vector<const void*> * pDummy;

  C_INT32 i, imax = mpFunctionParameters->size();
  for (i = 0; i < imax; ++i)
    if ((*mpFunctionParameters)[i]->getType() >= CFunctionParameter::VINT32)
      {
        pDummy = new std::vector<const void*>(*(std::vector<const void*>*)(mPointers[i]));
        mPointers[i] = pDummy;
        pDummy = new std::vector<const void*>(*(std::vector<const void*>*)(mObjects[i]));
        mObjects[i] = pDummy;
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
              if (mObjects[i])
                delete (std::vector< CCopasiObject * > *) mObjects[i];

              if (mPointers[i])
                delete (std::vector< void * > *) mPointers[i];
            }
        }
    }
  mPointers.clear();
  mObjects.clear();
}

void CFunctionParameterMap::initCallParameters()
{
  unsigned C_INT32 i, imax = mpFunctionParameters->size();

  mPointers.resize(imax);
  mObjects.resize(imax);

  for (i = 0; i < imax; i++)
    {
      if ((*mpFunctionParameters)[i]->getType() >= CFunctionParameter::VINT32)
        {
          if (mObjects[i])
            delete (std::vector< CCopasiObject * > *) mObjects[i];
          mObjects[i] = NULL;
          mObjects[i] = new std::vector< CCopasiObject * >;

          if (mPointers[i])
            delete (std::vector< void * > *) mPointers[i];
          mPointers[i] = NULL;

          switch ((*mpFunctionParameters)[i]->getType())
            {
            case CFunctionParameter::VINT32:
              mPointers[i] = new std::vector< C_INT32 * >;
              break;

            case CFunctionParameter::VFLOAT64:
              mPointers[i] = new std::vector< C_FLOAT64 * >;
              break;

            default:
              fatalError();
              break;
            }
        }
      else
        {
          mPointers[i] = NULL;
          mObjects[i] = NULL;
        }
    }
}

void CFunctionParameterMap::checkCallParameters() const
  {
    unsigned C_INT32 i, imax = mpFunctionParameters->size();
    unsigned C_INT32 j, jmax;
    const std::vector< const void * > * pVector;

    for (i = 0; i < imax; i++)
      {
        if (mPointers[i] == NULL)
          fatalError();
        if (mObjects[i] == NULL)
          fatalError();

        if ((*mpFunctionParameters)[i]->getType() < CFunctionParameter::VINT32)
          continue;

        pVector = (const std::vector<const void * > *) mPointers[i];
        jmax = pVector->size();

        for (j = 0; j < jmax; j++)
          if ((*pVector)[j] == NULL)
            fatalError();

        pVector = (const std::vector<const void * > *) mObjects[i];
        if (jmax != pVector->size()) fatalError();

        for (j = 0; j < jmax; j++)
          if ((*pVector)[j] == NULL)
            fatalError();
      }
  }

void CFunctionParameterMap::setCallParameter(const std::string paramName, const CCopasiObject* obj)
{
  CFunctionParameter::DataType type;
  C_INT32 index = findParameterByName(paramName, type);

  if (type >= CFunctionParameter::VINT32) fatalError(); // is a vector

  // TODO: check type of object
  mObjects[index] = obj;

  mPointers[index] = obj->getReference();
}

void CFunctionParameterMap::addCallParameter(const std::string paramName, const CCopasiObject* obj)
{
  CFunctionParameter::DataType type;
  C_INT32 index = findParameterByName(paramName, type);

  if (type < CFunctionParameter::VINT32) fatalError(); // is not a vector

  // TODO: check type of object
  ((std::vector<const CCopasiObject*> *)mObjects[index])->push_back(obj);

  ((std::vector<const C_FLOAT64*> *)mPointers[index])->push_back((const C_FLOAT64*)obj->getReference());
}

void CFunctionParameterMap::clearCallParameter(const std::string paramName)
{
  CFunctionParameter::DataType type;
  C_INT32 index = findParameterByName(paramName, type);

  if (type < CFunctionParameter::VINT32) fatalError(); // is not a vector

  // TODO: check type of object
  ((std::vector<const CCopasiObject*> *)mObjects[index])->clear();

  ((std::vector<const C_FLOAT64*> *)mPointers[index])->clear();
}

unsigned C_INT32 CFunctionParameterMap::findParameterByName(const std::string & name,
    CFunctionParameter::DataType & dataType) const
  {
    return mpFunctionParameters->findParameterByName(name, dataType);
  }

CCallParameterPointers & CFunctionParameterMap::getPointers()
{return mPointers;};

std::vector< const CCopasiObject * > CFunctionParameterMap::getObjects(const unsigned C_INT32 & index) const
  {
    std::vector< const CCopasiObject * > Objects;

    if (index != C_INVALID_INDEX)
      {
        if ((*mpFunctionParameters)[index]->getType() < CFunctionParameter::VINT32)
          Objects.push_back((const CCopasiObject *) mObjects[index]);
        else
          {
            std::vector< void * > * tmp =
              (std::vector< void * > *) mObjects[index];
            unsigned C_INT32 i, imax = tmp->size();

            for (i = 0; i < imax; i++)
              Objects.push_back((const CCopasiObject *) (*tmp)[i]);
          }
      }

    return Objects;
  }

CCallParameterPointers & CFunctionParameterMap::getObjects() {return mObjects;};

const CCallParameterPointers & CFunctionParameterMap::getObjects() const
  {return mObjects;};

const CFunctionParameters & CFunctionParameterMap::getFunctionParameters() const
  {return * mpFunctionParameters;};
