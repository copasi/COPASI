#include "CCallParameters.h"

void CCallParameters::initializeFromFunctionParameters(const CFunctionParameters & src)
{
  clearCallParameters();

  mpFunctionParameters = &src;
  /* TODO: may be we should copy the function parameters here. the call parameters can only be
     destroyed if we have the type information. So the CCallparameter object is save when the 
     function changes. But what about the reaction? Should it copy the function? (Then CCallParams
     would not need to copy CFunctionParameters) */

  initCallParameters();
}

void CCallParameters::clearCallParameters()
{
  if (!mpFunctionParameters) return;

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
  mPointer.clear();
  mObjects.clear();
}

void CCallParameters::initCallParameters()
{
  if (!mpFunctionParameters) fatalError();

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

          switch (*mpFunctionParameters)[i]->getType())
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

void CCallParameters::checkCallParameters() const
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

void CCallParameters::setCallParameter(const std::string paramName, const CCopasiObject* obj)
{
  CFunctionParameter::DataType type;
  C_INT32 index = findParameterByName(paramName, type);

  if (type >= CFunctionParameter::VINT32) fatal(); // is a vector

  // TODO: check type of object
  mObjects[index] = obj;

  // TODO: that does not work yet. CCopasiObject does not provide value
  mPointers[index] = obj->getValueAddr();
}

C_INT32 CCallParameters::findParameterByName(const std::string & name,
    CFunctionParameter::DataType & dataType) const
  {
    std::string VectorName = name.substr(0, name.find_last_of('_'));
    std::string Name;
    unsigned C_INT32 i, imax = mpFunctionParameters->size();

    for (i = 0; i < imax; i++)
      {
        Name = (*mpFunctionParameters)[i]->getName();

        if (Name == name || Name == VectorName)
          {
            dataType = (*mpFunctionParameters)[i]->getType();
            return i;
          }
      }

    fatalError()
    return - 1;
  }
