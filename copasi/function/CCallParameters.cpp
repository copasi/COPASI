#include "CCallParameters.h"
#include "CFunction.h"

//TODO: modify the constructors so that CFunctionParameterMap behaves like a CCopasiObject

CFunctionParameterMap::CFunctionParameterMap():
    mPointers(),
    mObjects(),
    mFunctionParameters()
{};

CFunctionParameterMap::CFunctionParameterMap(const CFunctionParameterMap & src):
    mPointers(src.mPointers),
    mObjects(src.mObjects),
    mFunctionParameters(src.mFunctionParameters)
{};

CFunctionParameterMap::~CFunctionParameterMap() {};

void CFunctionParameterMap::initializeFromFunctionParameters(const CFunctionParameters & src)
{
  clearCallParameters();

  mFunctionParameters = src;
  /* TODO: may be we should copy the function parameters here. the call parameters can only be
     destroyed if we have the type information. So the CCallparameter object is save when the 
     function changes. But what about the reaction? Should it copy the function? (Then CCallParams
     would not need to copy CFunctionParameters) */

  initCallParameters();
}

void CFunctionParameterMap::clearCallParameters()
{
  unsigned C_INT32 i, imax = mFunctionParameters.size();

  for (i = 0; i < imax; i++)
    {
      if (mFunctionParameters[i]->getType() >= CFunctionParameter::VINT32)
        {
          if (mObjects[i])
            delete (std::vector< CCopasiObject * > *) mObjects[i];

          if (mPointers[i])
            delete (std::vector< void * > *) mPointers[i];
        }
    }
  mPointers.clear();
  mObjects.clear();
}

void CFunctionParameterMap::initCallParameters()
{
  unsigned C_INT32 i, imax = mFunctionParameters.size();

  mPointers.resize(imax);
  mObjects.resize(imax);

  for (i = 0; i < imax; i++)
    {
      if (mFunctionParameters[i]->getType() >= CFunctionParameter::VINT32)
        {
          if (mObjects[i])
            delete (std::vector< CCopasiObject * > *) mObjects[i];
          mObjects[i] = NULL;
          mObjects[i] = new std::vector< CCopasiObject * >;

          if (mPointers[i])
            delete (std::vector< void * > *) mPointers[i];
          mPointers[i] = NULL;

          switch (mFunctionParameters[i]->getType())
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
    unsigned C_INT32 i, imax = mFunctionParameters.size();
    unsigned C_INT32 j, jmax;
    const std::vector< const void * > * pVector;

    for (i = 0; i < imax; i++)
      {
        if (mPointers[i] == NULL)
          fatalError();
        if (mObjects[i] == NULL)
          fatalError();

        if (mFunctionParameters[i]->getType() < CFunctionParameter::VINT32)
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

  mPointers[index] = obj->getObjectValueAddress();
}

void CFunctionParameterMap::addCallParameter(const std::string paramName, const CCopasiObject* obj)
{
  CFunctionParameter::DataType type;
  C_INT32 index = findParameterByName(paramName, type);

  if (type < CFunctionParameter::VINT32) fatalError(); // is not a vector

  // TODO: check type of object
  ((std::vector<const CCopasiObject*> *)mObjects[index])->push_back(obj);

  ((std::vector<const C_FLOAT64*> *)mPointers[index])->push_back((const C_FLOAT64*)obj->getObjectValueAddress());
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
    return mFunctionParameters.findParameterByName(name, dataType);
  }

CCallParameterPointers & CFunctionParameterMap::getPointers()
{return mPointers;};

std::vector< const CCopasiObject * > CFunctionParameterMap::getObjects(const unsigned C_INT32 & index) const
  {
    std::vector< const CCopasiObject * > Objects;

    if (index != C_INVALID_INDEX)
      {
        if (mFunctionParameters[index]->getType() < CFunctionParameter::VINT32)
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
  {return mFunctionParameters;};
