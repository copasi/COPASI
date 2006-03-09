/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CKinFunction.cpp,v $
   $Revision: 1.59 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2006/03/09 12:54:46 $
   End CVS Header */

/**
 * CKinFunction
 *
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2002
 */

#undef yyFlexLexer
#define yyFlexLexer CKinFunctionFlexLexer

#include <sstream>

#include "copasi.h"
#include "mathematics.h"

#include "CKinFunctionFlexLexer.h"
#include "CKinFunction.h"
#include "utilities/CCopasiException.h"
#include "report/CCopasiContainer.h"
#include "report/CCopasiObject.h"
#include "utilities/utility.h"

CKinFunction::CKinFunction(const std::string & name,
                           const CCopasiContainer * pParent):
    CFunction(name, pParent, CFunction::UserDefined)
{
  CONSTRUCTOR_TRACE;
}

CKinFunction::CKinFunction(const CFunction & src,
                           CReadConfig * configBuffer,
                           const CCopasiContainer * pParent):
    CFunction(src, pParent)
{
  CONSTRUCTOR_TRACE;

  if (configBuffer)
    {
      unsigned C_INT32 i, Size;
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
                           const CCopasiContainer * pParent):
    CFunction(src, pParent)
{
  CONSTRUCTOR_TRACE;
  compile();
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

// This is used when reading Gepasi Files
void CKinFunction::createParameters()
{
  CCopasiVectorN < CFunctionParameter > Substrates;
  CCopasiVectorN < CFunctionParameter > Products;
  CCopasiVectorN < CFunctionParameter > Modifiers;
  CCopasiVectorN < CFunctionParameter > Parameters;
  CCopasiVectorN < CFunctionParameter > Volumes;

  unsigned C_INT32 i, imax = mNodes.size();

  CFunctionParameter *pParameter;

  for (i = 0; i < imax; i++)
    {
      if (mNodes[i]->getType() == N_IDENTIFIER)
        {
          pParameter = new CFunctionParameter(mNodes[i]->getName());
          //          Parameter.setName(mNodes[i]->getObjectName());
          pParameter->setType(CFunctionParameter::FLOAT64);

          switch (mNodes[i]->getSubtype())
            {
            case N_SUBSTRATE:
              pParameter->setUsage(CFunctionParameter::SUBSTRATE);
              if (Substrates.getIndex(pParameter->getObjectName()) == C_INVALID_INDEX)
                Substrates.add(pParameter, false);
              else
                pdelete(pParameter);
              break;

            case N_PRODUCT:
              pParameter->setUsage(CFunctionParameter::PRODUCT);
              if (Products.getIndex(pParameter->getObjectName()) == C_INVALID_INDEX)
                Products.add(pParameter, false);
              else
                pdelete(pParameter);
              break;

            case N_MODIFIER:
              pParameter->setUsage(CFunctionParameter::MODIFIER);
              if (Modifiers.getIndex(pParameter->getObjectName()) == C_INVALID_INDEX)
                Modifiers.add(pParameter, false);
              else
                pdelete(pParameter);
              break;

            case N_KCONSTANT:
            case N_NOP:
              pParameter->setUsage(CFunctionParameter::PARAMETER);
              if (Parameters.getIndex(pParameter->getObjectName()) == C_INVALID_INDEX)
                Parameters.add(pParameter, false);
              else
                pdelete(pParameter);
              break;

            case N_VOLUME:
              pParameter->setUsage(CFunctionParameter::VOLUME);
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
    getVariables().add(Substrates[i], true);
  Substrates.cleanup();

  imax = Products.size();
  for (i = 0; i < imax; i++)
    getVariables().add(Products[i], true);
  Products.cleanup();

  imax = Modifiers.size();
  for (i = 0; i < imax; i++)
    getVariables().add(Modifiers[i], true);
  Modifiers.cleanup();

  imax = Parameters.size();
  for (i = 0; i < imax; i++)
    getVariables().add(Parameters[i], true);
  Parameters.cleanup();

  imax = Volumes.size();
  for (i = 0; i < imax; i++)
    getVariables().add(Volumes[i], true);
  Volumes.cleanup();
}

std::vector< CNodeK * > & CKinFunction::getNodes() {return mNodes;}

void CKinFunction::cleanupNodes()
{
  unsigned C_INT32 i, imax = mNodes.size();

  for (i = 0; i < imax; i++)
    if (mNodes[i]) delete mNodes[i];

  mNodes.clear();
  return;
}

/*void CKinFunction::writeMathML(std::ostream & out) const
  {
    //if (!mNodes[0]->isLeftValid()) return;
 
    out << "<math>" << std::endl;
    //mNodes[0]->getLeft().writeMathML(out, 0);
    out << "</math>" << std::endl;
  }*/
