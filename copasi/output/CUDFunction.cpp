/*****************************************************************************
* PROGRAM NAME: CUDFunction.cpp
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: Implement the user defined function object
*****************************************************************************/

#define COPASI_TRACE_CONSTRUCTION
#include <iostream>
#include "copasi.h"
#include "utilities/CGlobals.h"
#include "CNodeO.h"
#include "CUDFunction.h"

/**
 *  Default constructor
 */
CUDFunction::CUDFunction() : CKinFunction()
{
  CONSTRUCTOR_TRACE;
  setType(CFunction::Output);
}

CUDFunction::CUDFunction(const CFunction & src) : CKinFunction(src)
{CONSTRUCTOR_TRACE;}

CUDFunction::CUDFunction(const CUDFunction & src) : CKinFunction(src)
{CONSTRUCTOR_TRACE;}

/**
 *  This creates a user defined function with a name an description
 *  @param "const string" &name
 *  @param "const string" &description
 */
CUDFunction::CUDFunction(const string & name,
                         const string & description) : CKinFunction()
{
  CONSTRUCTOR_TRACE;
  setType(CFunction::Output);
  setName(name);
  setDescription(description);
}

/**
 *  Destructor
 */
CUDFunction::~CUDFunction() {cleanup(); DESTRUCTOR_TRACE;}

/**
 *  Delete
 */
void CUDFunction::cleanup()
{
  mNodes.cleanup();
  CFunction::cleanup();
}

#ifdef XXXX
/**
 *  Copy
 */
void CUDFunction::copy(const CUDFunction & in)
{
  CBaseFunction::copy(in);

  mNodes = CCopasiVectorS < CNodeO > (in.mNodes);

  mNidx = in.mNidx;

  connectNodes();
}
#endif // XXXX

/**
 *  Loads an object with data coming from a CReadConfig object.
 *  (CReadConfig object reads an input stream)
 *  @param pconfigbuffer reference to a CReadConfig object.
 *  @return Fail
 */
void CUDFunction::load(CReadConfig & configbuffer,
                       CReadConfig::Mode mode)
{
  C_INT32 Size = 0;
  string Name, Description;

  if (configbuffer.getVersion() < "4")
    {
      configbuffer.getVariable("Name", "string", &Name, mode);
      setName(Name);
  
      configbuffer.getVariable("Description", "string", &Description);
      setDescription(Description);

      setType(CFunction::Output);
    }
  else
    CFunction::load(configbuffer, mode);

  parse();
  
  if (configbuffer.getVersion() < "4")
    {
      configbuffer.getVariable("Nodes", "C_INT32", &Size);

      mNodes.load(configbuffer,Size);
      createParameters();
      mNodes.cleanup();
    }
  
  compile();
  return;
}

void CUDFunction::createParameters()
{
  CCopasiVectorN < CFunctionParameter > Data;

  unsigned C_INT32 i, imax = mNodes.size();
  
  CFunctionParameter Parameter;
  Parameter.setType(CFunctionParameter::FLOAT64);
  
  for (i=0; i<imax; i++)
    {
      if (mNodes[i]->getType() == N_IDENTIFIER)
        {
          try
            {
              Parameter.setName(getNodes()[i]->getName());
              Parameter.setUsage(mNodes[i]->getDatum().getObject());
              Data.add(Parameter);
            }

          catch (CCopasiException Exception)
            {
              if ((MCCopasiVector + 2) != Exception.getMessage().getNumber())
                throw Exception;
            }
        }
    }

  imax = Data.size();
  for (i=0; i<imax; i++)
      getParameters().add(Data[i]);
}
