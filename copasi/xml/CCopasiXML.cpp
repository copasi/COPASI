/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CCopasiXML.cpp,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/18 16:53:09 $
   End CVS Header */

/**
 * CCopasiXML class.
 * This class implements a CCopasiXMLInterface to the COPASI XML specified in
 * http://www.copasi.org/schema/copasi.xsd
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#include "copasi.h"
#include <map>

#include "CCopasiXML.h"
#include "CCopasiXMLParser.h"

#include "utilities/CCopasiVector.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "function/CFunction.h"
#include "report/CReportDefinition.h"

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
  bool success = true;
  bool done = false;

  CCopasiXMLParser Parser;

#define BUFFER_SIZE 0xfffe
  char * pBuffer = new char[BUFFER_SIZE + 1];

  while (!done)
    {
      mpIstream->get(pBuffer, BUFFER_SIZE, 0);

      if (mpIstream->eof()) done = true;
      if (mpIstream->fail() && !done) fatalError();

      Parser.parse(pBuffer, -1, done);
    }
  delete [] pBuffer;
#undef BUFFER_SIZE

  mpFunctionList = Parser.getFunctionList();
  mpModel = Parser.getModel();

  return success;
}

bool CCopasiXML::saveModel()
{
  bool success = true;
  if (!haveModel()) return success;

  CXMLAttributeList Attributes;
  Attributes.add("key", mpModel->getKey());
  Attributes.add("name", mpModel->getTitle());
  Attributes.add("timeUnit", mpModel->getTimeUnit());
  Attributes.add("volumeUnit", mpModel->getVolumeUnit());
  Attributes.add("quantityUnit", mpModel->getQuantityUnit());
  Attributes.add("stateVariable",
                 mpModel->getStateTemplate().getKey(mpModel->getKey()));

  startSaveElement("Model", Attributes);

  startSaveElement("Comment");

  Attributes.erase();
  Attributes.add("xmlns", "http://www.w3.org/1999/xhtml");
  startSaveElement("body", Attributes);

  saveData(mpModel->getComments()); // :TODO: we need to have saveXHTML

  endSaveElement("body");

  endSaveElement("Comment");

  unsigned C_INT32 i, imax;

  if ((imax = mpModel->getCompartments().size()) > 0)
    {
      startSaveElement("ListOfCompartments");

      Attributes.erase();
      Attributes.add("key", "");
      Attributes.add("name", "");
      Attributes.add("stateVariable", "");

      unsigned C_INT32 i, imax = mpModel->getCompartments().size();
      for (i = 0; i < imax; i++)
        {
          CCompartment * pComp = mpModel->getCompartments()[i];

          Attributes.setValue(0, pComp->getKey());
          Attributes.setValue(1, pComp->getName());
          Attributes.setValue(2,
                              mpModel->getStateTemplate().getKey(pComp->getKey()));
          saveElement("Compartment", Attributes);
        }

      endSaveElement("ListOfCompartments");
    }

  if ((imax = mpModel->getMetabolites().size()) > 0)
    {
      startSaveElement("ListOfMetabolites");

      Attributes.erase();
      Attributes.add("key", "");
      Attributes.add("name", "");
      Attributes.add("compartment", "");
      Attributes.add("stateVariable", "");

      for (i = 0; i < imax; i++)
        {
          CMetab * pMetab = mpModel->getMetabolites()[i];

          Attributes.setValue(0, pMetab->getKey());
          Attributes.setValue(1, pMetab->getName());
          Attributes.setValue(2, pMetab->getCompartment()->getKey());
          Attributes.setValue(3,
                              mpModel->getStateTemplate().getKey(pMetab->getKey()));

          saveElement("Metabolite", Attributes);
        }

      endSaveElement("ListOfMetabolites");
    }

  if ((imax = mpModel->getReactions().size()) > 0)
    {
      startSaveElement("ListOfReactions");

      CXMLAttributeList Attr;
      const CCopasiVector< CChemEqElement > * pReactantList;
      unsigned C_INT32 j, jmax;

      std::vector< const CCopasiObject * > ObjectList;
      unsigned C_INT32 k, kmax;

      Attributes.erase();
      Attributes.add("key", "");
      Attributes.add("name", "");
      Attributes.add("compartment", "");
      Attributes.add("reversible", "");

      for (i = 0; i < imax; i++)
        {
          CReaction * pReaction = mpModel->getReactions()[i];

          Attributes.setValue(0, pReaction->getKey());
          Attributes.setValue(1, pReaction->getName());
          if (pReaction->getCompartment())
            Attributes.setValue(2, pReaction->getCompartment()->getKey());
          else
            Attributes.skip(2);
          Attributes.setValue(3, pReaction->isReversible() ? "true" : "false");

          startSaveElement("Reaction", Attributes);

          Attr.erase();
          Attr.add("metabolite", "");
          Attr.add("stoichiometry", "");

          pReactantList = & pReaction->getChemEq().getSubstrates();
          if ((jmax = pReactantList->size()) > 0)
            {
              startSaveElement("ListOfSubstrates");

              for (j = 0; j < jmax; j++)
                {
                  Attr.setValue(0,
                                (*pReactantList)[j]->getMetabolite().getKey());
                  Attr.setValue(1, (*pReactantList)[j]->getMultiplicity());

                  saveElement("Substrate", Attr);
                }

              endSaveElement("ListOfSubstrates");
            }
          //startSaveElement("ListOfProducts"); // this seems to belong further down

          pReactantList = & pReaction->getChemEq().getProducts();
          if ((jmax = pReactantList->size()) > 0)
            {
              startSaveElement("ListOfProducts"); //this seems to belong here

              for (j = 0; j < jmax; j++)
                {
                  Attr.setValue(0,
                                (*pReactantList)[j]->getMetabolite().getKey());
                  Attr.setValue(1,
                                (*pReactantList)[j]->getMultiplicity());

                  saveElement("Product", Attr);
                }

              endSaveElement("ListOfProducts");
            }

          pReactantList = & pReaction->getChemEq().getModifiers();
          if ((jmax = pReactantList->size()) > 0)
            {
              startSaveElement("ListOfModifiers");

              for (j = 0, jmax = pReactantList->size(); j < jmax; j++)
                {
                  Attr.setValue(0, (*pReactantList)[j]->getMetabolite().getKey());
                  Attr.setValue(1, (*pReactantList)[j]->getMultiplicity());

                  saveElement("Modifier", Attr);
                }

              endSaveElement("ListOfModifiers");
            }

          const CCopasiParameterGroup * pParamList;
          pParamList = & pReaction->getParameters();
          if ((jmax = pParamList->size()) > 0)
            {
              startSaveElement("ListOfConstants");

              Attr.erase();
              Attr.add("key", "");
              Attr.add("name", "");
              Attr.add("value", "");

              for (j = 0; j < jmax; j++)
                {
                  Attr.setValue(0, pParamList->getKey(j));
                  Attr.setValue(1, pParamList->getName(j));
                  Attr.setValue(2, * (C_FLOAT64 *) pParamList->getValue(j));

                  saveElement("Constant", Attr);
                }

              endSaveElement("ListOfConstants");
            }

          if (&pReaction->getFunction())
            {
              Attr.erase();
              Attr.add("function", pReaction->getFunction().getKey());
              startSaveElement("KineticLaw", Attr);

              startSaveElement("ListOfCallParameters");
              const CFunctionParameterMap * pMap =
                &pReaction->getFunctionParameterMap();

              for (j = 0, jmax = pReaction->getFunctionParameters().size(); j < jmax; j++)
                {
                  Attr.erase();
                  Attr.add("functionParameter",
                           pReaction->getFunctionParameters()[j]->getKey());

                  startSaveElement("CallParameter", Attr);

                  ObjectList = pMap->getObjects(j);

                  Attr.erase();
                  Attr.add("reference", "");

                  for (k = 0, kmax = ObjectList.size(); k < kmax; k++)
                    {
                      const CCopasiObject * pObject = ObjectList[k];

                      if (pObject->getObjectType() == "Parameter")
                        Attr.setValue(0,
                                      ((CCopasiParameter *)
                                       (CCopasiContainer *) pObject)->getKey());
                      else if (pObject->getObjectType() == "Metabolite")
                        Attr.setValue(0,
                                      ((CMetab *)
                                       (CCopasiContainer *) pObject)->getKey());
                      else
                        Attr.setValue(0, "NoKey");

                      saveElement("SourceParameter", Attr);
                    }

                  endSaveElement("CallParameter");
                }
              endSaveElement("ListOfCallParameters");

              endSaveElement("KineticLaw");
            }
          endSaveElement("Reaction");
        }
      endSaveElement("ListOfReactions");
    }
  startSaveElement("StateTemplate");

  Attributes.erase();
  Attributes.add("key", "");
  Attributes.add("objectReference", "");
  std::pair< std::string, std::string > Variable;

  for (i = 0, imax = mpModel->getStateTemplate().size(); i < imax; i++)
    {
      Variable = mpModel->getStateTemplate()[i];
      Attributes.setValue(0, Variable.first);
      Attributes.setValue(1, Variable.second);

      saveElement("StateTemplateVariable", Attributes);
    }

  endSaveElement("StateTemplate");

  Attributes.erase();
  Attributes.add("type", "initial");
  startSaveElement("InitialState", Attributes);
  CState InitialState = mpModel->getInitialState();

  std::stringstream data;
  data << InitialState.getTime();
  for (i = 0, imax = InitialState.getVolumeSize(); i < imax; i++)
    data << " " << InitialState.getVolume(i);

  for (i = 0, imax = InitialState.getVariableNumberSize(); i < imax; i++)
    data << " " << InitialState.getVariableNumber(i);

  for (i = 0, imax = InitialState.getFixedNumberSize(); i < imax; i++)
    data << " " << InitialState.getFixedNumber(i);

  saveData(data.str());
  endSaveElement("InitialState");

  endSaveElement("Model");

  return success;
}

bool CCopasiXML::saveFunctionList()
{
  bool success = true;

  if (!haveFunctionList()) return success;

  CXMLAttributeList Attributes;

  unsigned C_INT32 i, imax = mpFunctionList->size();
  CFunction * pFunction = NULL;

  startSaveElement("ListOfFunctions");

  for (i = 0; i < imax; i++)
    {
      pFunction = (*mpFunctionList)[i];

      Attributes.erase();
      Attributes.add("key", pFunction->getKey());
      Attributes.add("name", pFunction->getName());
      Attributes.add("type", CFunction::XMLType[pFunction->getType()]);
      Attributes.add("positive", pFunction->isReversible() ? "true" : "false");
      startSaveElement("Function", Attributes);

      startSaveElement("MathML");

      startSaveElement("Text");
      saveData(pFunction->getDescription());
      endSaveElement("Text");

      endSaveElement("MathML");

      startSaveElement("ListOfParameterDescriptions");

      unsigned C_INT32 j, jmax = pFunction->getParameters().size();
      CFunctionParameter * pParameter;

      Attributes.erase();
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
              Attributes.skip(4);
              Attributes.skip(5);
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
  // if (!haveTaskList()) return success;

  return success;
}

//Mrinmayee

bool CCopasiXML::saveReportList()
{
  bool success = true;
  if (!haveReportList()) return success;

  CXMLAttributeList Attributes;

  unsigned C_INT32 i, j, imax = mpReportList->size();
  CReportDefinition * pReport = NULL;

  startSaveElement("ListOfReports");

  for (i = 0; i < imax; i++)
    {
      pReport = (*mpReportList)[i];

      Attributes.erase();
      // *** fill in stuff here
      Attributes.add("key", pReport->getKey());
      Attributes.add("name", pReport->getObjectName());
      //Attributes.add("taskType", pReport->getTaskType());
      startSaveElement("Report", Attributes);

      startSaveElement("Comment");
      saveData(pReport->getComment().getStaticString());
      endSaveElement("Comment");

      startSaveElement("Header");
      std::vector <CCopasiObjectName> *header = pReport->getHeaderAddr();
      for (j = 0; j < header->size(); j++)
        {
          if ((*header)[j].getObjectType() == "string")
            {
              //Write in Text
              startSaveElement("Text");
              saveData((*header)[j]);
              endSaveElement("Text");
            }
          else
            {
              //Write in Object
              Attributes.erase();
              Attributes.add("cn", (*header)[j]);
              startSaveElement("Object", Attributes);
              endSaveElement("Object");
            }
        }

      //Report is not yet implemented
      /*startSaveElement("Report");

       endSaveElement("Report");*/

      endSaveElement("Header");

      startSaveElement("Body");
      std::vector <CCopasiObjectName> *body = pReport->getBodyAddr();
      for (j = 0; j < body->size(); j++)
        {
          startSaveElement("Complex");
          if ((*body)[j].getObjectType() == "string")
            {
              //Write in Text
              startSaveElement("Text");
              saveData((*body)[j]);
              endSaveElement("Text");
            }
          else
            {
              //Write in Object
              Attributes.erase();
              Attributes.add("cn", (*body)[j]);
              startSaveElement("Object", Attributes);
              endSaveElement("Object");
            }

          endSaveElement("Complex");
        }

      //Table is not yet implemented
      /*Attributes.erase();
      Attributes.add("seperator",);
      Attributes.add("printTitle",);
      startSaveElement("Table",Attributes);
      //*** Add stuff here
        Attributes.erase();
        Attributes.add("cn",);
           startSaveElement("Object",Attributes);
        endSaveElement("Object");
      endSaveElement("Table");*/

      endSaveElement("Body");

      //footer is not yet implented

      /*startSaveElement("Footer");
      //*** Add stuff here
       Attributes.erase();
       Attributes.add("cn",);
          startSaveElement("Object",Attributes);
       endSaveElement("Object");
          startSaveElement("Text");
        //*** Add here
       saveData();
       endSaveElement("Text");
          startSaveElement("Report");
            endSaveElement("Report")

      endSaveElement("Footer");*/

      endSaveElement("Report");
    }

  endSaveElement("ListOfReports");

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
