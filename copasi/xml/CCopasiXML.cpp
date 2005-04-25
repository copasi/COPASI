/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CCopasiXML.cpp,v $
   $Revision: 1.50 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/25 18:37:00 $
   End CVS Header */

/**
 * CCopasiXML class.
 * This class implements a CCopasiXMLInterface to the COPASI XML specified in
 * http://www.copasi.org/schema/copasi.xsd
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */
#include <iostream>
#include "copasi.h"
#include <map>

#include "CCopasiXML.h"
#include "CCopasiXMLParser.h"
#include "CCopasiXMLVersion.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiVector.h"
#include "utilities/CSlider.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "function/CFunction.h"
#include "report/CReportDefinitionVector.h"
#include "utilities/CCopasiTask.h"
#include "utilities/CCopasiMethod.h"
#include "utilities/CCopasiProblem.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotItem.h"

// class CCopasiTask;
// class CCopasiReport;

CCopasiXML::CCopasiXML():
    CCopasiXMLInterface()
{
  mVersion.setVersion(COPASI_XML_VERSION_MAJOR,
                      COPASI_XML_VERSION_MINOR,
                      COPASI_XML_VERSION_BUILD);
}

CCopasiXML::~CCopasiXML() {}

bool CCopasiXML::save(std::ostream & os)
{
  mpOstream = &os;
  bool success = true;

  *mpOstream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
  << std::endl;

  *mpOstream << "<!-- generated with COPASI "
  << CCopasiDataModel::Global->getVersion()->getVersion()
  << " (http://www.copasi.org) -->"
  << std::endl;

  CXMLAttributeList Attributes;
  Attributes.add("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
  Attributes.add("xsi:noNamespaceSchemaLocation",
                 "http://calvin.bioinformatics.vt.edu/copasi/schema/copasi.xsd");
  Attributes.add("versionMajor", mVersion.getVersionMajor());
  Attributes.add("versionMinor", mVersion.getVersionMinor());

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
  if (!savePlotList()) success = false;
  if (!saveGUI()) success = false;

  endSaveElement("COPASI");

  return success;
}

bool CCopasiXML::load(std::istream & is)
{
  mpIstream = &is;
  bool success = true;
  bool done = false;

  CCopasiXMLParser Parser(mVersion);

  Parser.setFunctionList(mpFunctionList);
  Parser.setModel(mpModel);
  Parser.setReportList(mpReportList);
  Parser.setTaskList(mpTaskList);
  Parser.setPlotList(mpPlotList);
  Parser.setGUI(mpGUI);

#define BUFFER_SIZE 0xfffe
  char * pBuffer = new char[BUFFER_SIZE + 1];

  while (!done)
    {
      mpIstream->get(pBuffer, BUFFER_SIZE, 0);

      if (mpIstream->eof()) done = true;
      if (mpIstream->fail() && !done) fatalError();

      if (!Parser.parse(pBuffer, -1, done))
        {
          CCopasiMessage Message(CCopasiMessage::RAW, MCXML + 2,
                                 Parser.getCurrentLineNumber(),
                                 Parser.getCurrentColumnNumber(),
                                 Parser.getErrorString());
          done = true;
          success = false;
        }
    }
  delete [] pBuffer;
#undef BUFFER_SIZE

  if (success)
    {
      mpFunctionList = Parser.getFunctionList();
      mpModel = Parser.getModel();
      mpReportList = Parser.getReportList();
      mpTaskList = Parser.getTaskList();
      mpPlotList = Parser.getPlotList();
      if (mpPlotList)
        {
          //std::cout << "Number of Plots: " << mpPlotList->size() << std::endl;
          unsigned int count;
          for (count = 0; count < mpPlotList->size(); count++)
            {
              //std::cout << "Number of PlotItems for plot @" << (*mpPlotList)[count] << ": " << (*mpPlotList)[count]->getItems().size() << std::endl;
            }
        }
    }

  return success;
}

const CVersion & CCopasiXML::getVersion() const
  {return mVersion;}

bool CCopasiXML::saveModel()
{
  bool success = true;
  if (!haveModel()) return success;

  CXMLAttributeList Attributes;
  Attributes.add("key", mpModel->getKey());
  Attributes.add("name", mpModel->getObjectName());
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
          Attributes.setValue(1, pComp->getObjectName());
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
      Attributes.add("status", "");
      Attributes.add("stateVariable", "");

      for (i = 0; i < imax; i++)
        {
          CMetab * pMetab = mpModel->getMetabolites()[i];

          Attributes.setValue(0, pMetab->getKey());
          Attributes.setValue(1, pMetab->getObjectName());
          Attributes.setValue(2, pMetab->getCompartment()->getKey());
          Attributes.setValue(3, CMetab::XMLStatus[pMetab->getStatus()]);
          Attributes.setValue(4,
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
          Attributes.setValue(1, pReaction->getObjectName());
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

          if (&pReaction->getFunction() !=
              dynamic_cast<CFunction *>(GlobalKeys.get("UndefinedFunction")))
            {
              Attr.erase();
              Attr.add("function", pReaction->getFunction().getKey());
              startSaveElement("KineticLaw", Attr);
              if ((jmax = pReaction->getFunctionParameters().size()))
                {
                  startSaveElement("ListOfCallParameters");
                  const CFunctionParameterMap * pMap =
                    &pReaction->getFunctionParameterMap();

                  for (j = 0; j < jmax; j++)
                    {
                      Attr.erase();
                      Attr.add("functionParameter",
                               pReaction->
                               getFunction().getParameters()[j]->getKey());

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
                }
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
  Attributes.add("type", "initialState");
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
  unsigned C_INT32 i, imax = mpFunctionList->size();

  if (!imax) return success;

  CXMLAttributeList Attributes;
  CFunction * pFunction = NULL;

  startSaveElement("ListOfFunctions");

  for (i = 0; i < imax; i++)
    {
      pFunction = (*mpFunctionList)[i];

      Attributes.erase();
      Attributes.add("key", pFunction->getKey());
      Attributes.add("name", pFunction->getObjectName());
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
          Attributes.setValue(1, pParameter->getObjectName());
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

bool CCopasiXML::savePlotList()
{
  std::cerr << "Saving plot list. " << std::endl;
  bool success = true;
  if (!havePlotList())
    {
      std::cerr << "No plot list defined." << std::endl;
      return success;
    }

  unsigned C_INT32 i, imax = mpPlotList->size();
  std::cerr << "Saving " << imax << " plots." << std::endl;
  if (!imax) return success;

  CXMLAttributeList Attributes;

  startSaveElement("ListOfPlots");

  for (i = 0; i < imax; i++)
    {
      const CPlotSpecification* pPlot = (*mpPlotList)[i];

      Attributes.erase();
      Attributes.add("name", pPlot->getObjectName());
      Attributes.add("type", CPlotSpecification::XMLType[pPlot->getType()]);
      Attributes.add("active", CPlotSpecification::XMLType[pPlot->isActive()]);
      startSaveElement("PlotSpecification", Attributes);
      saveParameterGroup(* (CCopasiParameterGroup::parameterGroup *)pPlot->CCopasiParameter::getValue());
      startSaveElement("ListOfPlotItems");
      unsigned C_INT32 j, jmax = pPlot->getItems().size();
      std::cerr << "Saving " << jmax << "PlotItems." << std::endl;
      for (j = 0; j < jmax; j++)
        {
          const CPlotItem* pPlotItem = pPlot->getItems()[j];
          Attributes.erase();
          Attributes.add("name", pPlotItem->getObjectName());
          Attributes.add("type", CPlotItem::XMLType[pPlotItem->getType()]);
          startSaveElement("PlotItem", Attributes);
          saveParameterGroup(* (CCopasiParameterGroup::parameterGroup *)pPlotItem->CCopasiParameter::getValue());
          startSaveElement("ListOfChannels");
          unsigned C_INT32 k, kmax = pPlotItem->getNumChannels();
          std::cerr << "Saving " << kmax << " Channels." << std::endl;
          for (k = 0; k < kmax; k++)
            {
              const CPlotDataChannelSpec pDataChannelSpec = pPlotItem->getChannels()[k];
              Attributes.erase();
              Attributes.add("cn", pDataChannelSpec);
              if (!pDataChannelSpec.minAutoscale)
                {
                  Attributes.add("min", pDataChannelSpec.min);
                }
              if (!pDataChannelSpec.maxAutoscale)
                {
                  Attributes.add("max", pDataChannelSpec.max);
                }
              saveElement("ChannelSpec", Attributes);
            }
          endSaveElement("ListOfChannels");
          endSaveElement("PlotItem");
        }
      endSaveElement("ListOfPlotItems");
      endSaveElement("PlotSpecification");
    }
  endSaveElement("ListOfPlots");
  return success;
}

//Mrinmayee
bool CCopasiXML::saveTaskList()
{
  bool success = true;
  if (!haveTaskList()) return success;

  unsigned C_INT32 i, imax = mpTaskList->size();

  if (!imax) return success;

  CXMLAttributeList Attributes;
  CCopasiTask * pTask = NULL;

  startSaveElement("ListOfTasks");

  for (i = 0; i < imax; i++)
    {
      pTask = (*mpTaskList)[i];

      Attributes.erase();
      Attributes.add("key", pTask->getKey());
      Attributes.add("name", pTask->getObjectName());
      Attributes.add("type", CCopasiTask::XMLType[pTask->getType()]);
      Attributes.add("scheduled", pTask->isScheduled() ? "true" : "false");

      startSaveElement("Task", Attributes);

      // Report Element
      CReport & tReport = pTask->getReport();
      if (tReport.getReportDefinition())
        {
          Attributes.erase();
          Attributes.add("reference", tReport.getReportDefinition()->getKey());
          Attributes.add("target", tReport.getTarget());
          Attributes.add("append", tReport.append());
          saveElement("Report", Attributes);
        }

      //Problem Element
      CCopasiProblem *tProblem = pTask->getProblem();

      Attributes.erase();
      startSaveElement("Problem");
      saveParameterGroup(* (std::vector<CCopasiParameter *> *) tProblem->CCopasiParameter::getValue());
      endSaveElement("Problem");

      // Method Element
      CCopasiMethod *tMethod = pTask->getMethod();

      Attributes.erase();
      Attributes.add("name", tMethod->CCopasiParameter::getObjectName());
      Attributes.add("type", CCopasiMethod::XMLSubType[tMethod->getSubType()]);
      startSaveElement("Method", Attributes);
      saveParameterGroup(* (std::vector<CCopasiParameter *> *) tMethod->CCopasiParameter::getValue());
      endSaveElement("Method");

      endSaveElement("Task");
    }

  endSaveElement("ListOfTasks");

  return success;
}

bool CCopasiXML::saveParameter(const CCopasiParameter & parameter)
{
  bool success = true;

  CXMLAttributeList Attributes;

  Attributes.add("name", parameter.getObjectName());

  CCopasiParameter::Type Type = parameter.getType();
  Attributes.add("type", CCopasiParameter::XMLType[Type]);

  switch (parameter.getType())
    {
    case CCopasiParameter::DOUBLE:
    case CCopasiParameter::UDOUBLE:
      Attributes.add("value", * (C_FLOAT64 *) parameter.getValue());
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::INT:
      Attributes.add("value", * (C_INT32 *) parameter.getValue());
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::UINT:
      Attributes.add("value", * (unsigned C_INT32 *) parameter.getValue());
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::BOOL:
      Attributes.add("value", * (bool *) parameter.getValue());
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::STRING:
      Attributes.add("value", * (std::string *) parameter.getValue());
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::CN:
      Attributes.add("value", * (std::string *) parameter.getValue());
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::GROUP:
      if (!startSaveElement("ParameterGroup", Attributes)) success = false;
      if (!saveParameterGroup(* (CCopasiParameterGroup::parameterGroup *) parameter.getValue())) success = false;
      if (!endSaveElement("ParameterGroup")) success = false;
      break;

    case CCopasiParameter::INVALID:
    default:
      success = false;
      break;
    }

  return success;
}

bool CCopasiXML::saveParameterGroup(const std::vector< CCopasiParameter * > & group)
{
  bool success = true;

  std::vector< CCopasiParameter * >::const_iterator it = group.begin();
  std::vector< CCopasiParameter * >::const_iterator end = group.end();

  for (; it != end; ++it)
    if (!saveParameter(**it)) success = false;

  return success;
}

//Mrinmayee
bool CCopasiXML::saveReportSection(const std::string & name,
                                   const std::vector <CRegisteredObjectName> & section)
{
  CXMLAttributeList Attributes;
  Attributes.add("NoName", "");

  unsigned C_INT32 j, jmax = section.size();

  if (jmax)
    {
      startSaveElement(name);
      for (j = 0; j < jmax; j++)
        {
          if (section[j].getObjectType() == "html")
            {
              //Write in Text
              startSaveElement("html");
              Attributes.set(0, "xmlns", "http://www.w3.org/1999/xhtml");
              startSaveElement("body", Attributes);
              saveData(section[j].getObjectName()); //TODO check
              endSaveElement("body");
              endSaveElement("html");
            }
          else
            {
              //Write in Object
              Attributes.set(0, "cn", section[j]);
              saveElement("Object", Attributes);
            }
        }
      endSaveElement(name);
    }

  return true;
}

bool CCopasiXML::saveReportList()
{
  bool success = true;
  if (!haveReportList()) return success;

  unsigned C_INT32 i, imax = mpReportList->size();
  if (!imax) return success;

  CXMLAttributeList Attributes;
  CReportDefinition * pReport = NULL;

  startSaveElement("ListOfReports");

  for (i = 0; i < imax; i++)
    {
      pReport = (*mpReportList)[i];

      Attributes.erase();
      Attributes.add("key", pReport->getKey());
      Attributes.add("name", pReport->getObjectName());
      Attributes.add("taskType", pReport->getTaskType());
      startSaveElement("Report", Attributes);

      startSaveElement("Comment");
      Attributes.erase();
      Attributes.add("xmlns", "http://www.w3.org/1999/xhtml");
      startSaveElement("body", Attributes);
      saveData(pReport->getComment());
      endSaveElement("body");
      endSaveElement("Comment");

      if (pReport->isTable())
        {
          Attributes.erase();
          Attributes.add("separator", pReport->getSeparator().getStaticString());
          Attributes.add("printTitle", pReport->getTitle());
          startSaveElement("Table", Attributes);

          const std::vector <CRegisteredObjectName> & Table = * pReport->getBodyAddr();
          unsigned C_INT32 j, jmax = Table.size();

          Attributes.erase();
          Attributes.add("cn", "");

          for (j = 0; j < jmax; j += 2) // We skip the separator
            {
              Attributes.setValue(0, Table[j]);
              saveElement("Object", Attributes);
            }

          endSaveElement("Table");
        }
      else
        {
          saveReportSection("Header", * pReport->getHeaderAddr());
          saveReportSection("Body", * pReport->getBodyAddr());
          saveReportSection("Footer", * pReport->getFooterAddr());
        }

      endSaveElement("Report");
    }

  endSaveElement("ListOfReports");

  return success;
}

bool CCopasiXML::saveGUI()
{
  bool success = true;
  if (!haveGUI()) return success;

  startSaveElement("GUI");

  if (mpGUI->pSliderList && mpGUI->pSliderList->size())
    {
      startSaveElement("ListOfSliders");

      CSlider * pSlider;
      CXMLAttributeList Attributes;

      Attributes.add("key", "");
      Attributes.add("associatedEntityKey", "");
      Attributes.add("objectCN", "");
      Attributes.add("objectType", "");
      Attributes.add("objectValue", "");
      Attributes.add("minValue", "");
      Attributes.add("maxValue", "");
      Attributes.add("tickNumber", "");
      Attributes.add("tickFactor", "");
      Attributes.add("scaling", "");

      unsigned C_INT32 i, imax = mpGUI->pSliderList->size();
      for (i = 0; i < imax; i++)
        {
          pSlider = (*mpGUI->pSliderList)[i];
          Attributes.setValue(0, pSlider->getKey());
          Attributes.setValue(1, pSlider->getAssociatedEntityKey());
          Attributes.setValue(2, pSlider->getSliderObjectCN());
          Attributes.setValue(3, CSlider::TypeName[pSlider->getSliderType()]);
          Attributes.setValue(4, pSlider->getSliderValue());
          Attributes.setValue(5, pSlider->getMinValue());
          Attributes.setValue(6, pSlider->getMaxValue());
          Attributes.setValue(7, pSlider->getTickNumber());
          Attributes.setValue(8, pSlider->getTickFactor());
          Attributes.setValue(9, pSlider->convertScaleToScaleName(pSlider->getScaling()));
          saveElement("Slider", Attributes);
        }

      endSaveElement("ListOfSliders");
    }

  endSaveElement("GUI");

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
      if (pFunction &&
          pFunction != GlobalKeys.get("UndefinedFunction"))
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
