/**
 * CCopasiXML class.
 * This class implements a CCopasiXMLInterface to the COPASI XML specified in
 * http://www.copasi.org/schema/copasi.xsd
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#include <map>

#include "copasi.h"
#include "CCopasiXML.h"

#include "utilities/CCopasiVector.h"
#include "model/CModel.h"
#include "function/CFunction.h"

// class CCopasiTask;
// class CCopasiReport;

CCopasiXML::CCopasiXML():
    CCopasiXMLInterface()
{}

CCopasiXML::~CCopasiXML() {}

bool CCopasiXML::save(std::ostream & os)
{
  mpOstream = &os;
  bool success = true;

  *mpOstream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  << std::endl;
  *mpOstream << "<!-- generated with COPASI (http://www.copasi.org) -->"
  << std::endl;

  CXMLAttributeList Attributes;
  Attributes.add("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
  Attributes.add("xsi:noNamespaceSchemaLocation",
                 "http://calvin.bioinformatics.vt.edu/copasi/schema/copasi.xsd");
  startSaveElement("COPASI", Attributes);

  if (haveModel() && !haveFunctionList())
    {
      if (!buildFunctionList()) success = false;
      if (!saveFunctionList()) success = false;
      if (!freeFunctionList()) success = false;
    }
  else
    if (!saveFunctionList()) success = false;

  if (!saveModel()) success = false;
  if (!saveTaskList()) success = false;
  if (!saveReportList()) success = false;

  endSaveElement("COPASI");

  return success;
}

bool CCopasiXML::load(std::istream & is)
{
  mpIstream = &is;

  return true;
}

bool CCopasiXML::saveModel()
{
  bool success = true;

  CXMLAttributeList Attributes;
  Attributes.add("key", mpModel->getKey());
  Attributes.add("name", mpModel->getTitle());
  Attributes.add("timeUnit", mpModel->getTimeUnit());
  Attributes.add("volumeUnit", mpModel->getVolumeUnit());
  Attributes.add("quantityUnit", mpModel->getQuantityUnit());
  Attributes.add("stateVariable", mpModel->getStateTemplate().getKey(mpModel->getKey()));

  return success;
}

bool CCopasiXML::saveFunctionList()
{
  bool success = true;

  if (!haveFunctionList()) return success;

  CXMLAttributeList Attributes;

  unsigned C_INT32 i, imax = mpFunctionList->size();
  CFunction * pFunction = NULL;

  Attributes.erase();
  startSaveElement("ListOfFunctions", Attributes);

  for (i = 0; i < imax; i++)
    {
      pFunction = (*mpFunctionList)[i];

      Attributes.erase();
      Attributes.add("key", pFunction->getKey());
      Attributes.add("name", pFunction->getName());
      Attributes.add("type", CFunction::TypeName[pFunction->getType()]);
      startSaveElement("Function", Attributes);

      Attributes.erase();
      startSaveElement("MathML", Attributes);

      startSaveElement("Text", Attributes);
      saveData(pFunction->getDescription());
      endSaveElement("Text");

      endSaveElement("MathML");

      startSaveElement("ListOfParameterDescriptions", Attributes);

      unsigned C_INT32 j, jmax = pFunction->getParameters().size();
      CFunctionParameter * pParameter;

      Attributes.add("key", "");
      Attributes.add("name", "");
      Attributes.add("order", "");
      Attributes.add("role", "");
      Attributes.add("minOccurs", "");
      Attributes.add("maxOccurs", "");

      std::string Usage;

      for (j = 0; j < jmax; j++)
        {
          pParameter = pFunction->getParameters()[j];
          Attributes.setValue(0, pParameter->getKey());
          Attributes.setValue(1, pParameter->getName());
          Attributes.setValue(2, j);
          Usage = pParameter->getUsage();
          if (Usage == "SUBSTRATE")
            Attributes.setValue(3, "substrate");
          else if (Usage == "PRODUCT")
            Attributes.setValue(3, "product");
          else if (Usage == "MODIFIER")
            Attributes.setValue(3, "modifier");
          else if (Usage == "PARAMETER")
            Attributes.setValue(3, "constant");
          else
            Attributes.setValue(3, "other");

          if (pParameter->getType() < CFunctionParameter::VINT32)
            {
              Attributes.setValue(4, 1);
              Attributes.setValue(5, 1);
            }
          else
            {
              CUsageRange * pUsageRange =
                pFunction->getParameters().getUsageRanges()[pParameter->getUsage()];
              Attributes.setValue(4, pUsageRange->getLow());
              if (pUsageRange->getHigh() == (unsigned C_INT32) CRange::Infinity)
                Attributes.setValue(5, "unbounded");
              else
                Attributes.setValue(5, pUsageRange->getHigh());
            }

          saveElement("ParameterDescription", Attributes);
        }

      endSaveElement("ListOfParameterDescriptions");

      endSaveElement("Function");
    }

  endSaveElement("ListOfFunctions");

  return success;
}

bool CCopasiXML::saveTaskList()
{
  bool success = true;

  return success;
}

bool CCopasiXML::saveReportList()
{
  bool success = true;

  return success;
}

bool CCopasiXML::buildFunctionList()
{
  bool success = true;

  std::map< std::string, CFunction * > FunctionMap;

  unsigned C_INT32 i, imax = mpModel->getReactions().size();

  for (i = 0; i < imax; i++)
    {
      CFunction * pFunction =
        const_cast< CFunction * >(&mpModel->getReactions()[i]->getFunction());
      FunctionMap[pFunction->getKey()] = pFunction;
    }

  CCopasiVectorN< CFunction > * pFunctionList = new CCopasiVectorN< CFunction >;
  pFunctionList->resize(FunctionMap.size(), false);

  std::map< std::string, CFunction * >::iterator it = FunctionMap.begin();
  std::map< std::string, CFunction * >::iterator End = FunctionMap.end();

  for (i = 0; it != End; ++it, i++)
    (*pFunctionList)[i] = it->second;

  if (!setFunctionList(*pFunctionList)) success = false;

  return success;
}
