// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*!
 \file CCopasiXML.cpp
 \brief Implementation file of class CCopasiXML.
 */

/**
 * CCopasiXML class.
 * This class implements a CCopasiXMLInterface to the COPASI XML specified in
 * http://www.copasi.org/schema/copasi.xsd
 *
 * Created for COPASI by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */
#include <iostream>
#include <map>
#include <locale>

#include "copasi/copasi.h"

#include "CCopasiXML.h"
#include "parser/CXMLParser.h"

#include "CFixLocalReactionParameters.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/core/CDataVector.h"
#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/utilities/CUnitDefinitionDB.h"
#include "copasi/utilities/CSlider.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CState.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CEvaluationTree.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/utilities/CDirEntry.h"
#include "copasi/utilities/utility.h"
#include "copasi/plot/COutputDefinitionVector.h"
#include "copasi/plot/CPlotItem.h"
#include "copasi/layout/CListOfLayouts.h"
#include "copasi/parameterFitting/CFitTask.h"
#include "copasi/scan/CScanTask.h"
#include "copasi/utilities/CUnitDefinition.h"

#include "copasi/layout/CLLocalRenderInformation.h"
#include "copasi/layout/CLGlobalRenderInformation.h"
#include "copasi/layout/CLRenderInformationBase.h"
#include "copasi/layout/CLLocalStyle.h"
#include "copasi/layout/CLGlobalStyle.h"
#include "copasi/layout/CLColorDefinition.h"
#include "copasi/layout/CLGradientBase.h"
#include "copasi/layout/CLLinearGradient.h"
#include "copasi/layout/CLRadialGradient.h"
#include "copasi/layout/CLLineEnding.h"
#include "copasi/layout/CLRenderPoint.h"
#include "copasi/layout/CLRenderCubicBezier.h"
#include "copasi/layout/CLGroup.h"
#include "copasi/layout/CLTransformation2D.h"
#include "copasi/layout/CLImage.h"
#include "copasi/layout/CLGraphicalPrimitive1D.h"
#include "copasi/layout/CLText.h"
#include "copasi/layout/CLRenderCurve.h"
#include "copasi/layout/CLGraphicalPrimitive2D.h"
#include "copasi/layout/CLRectangle.h"
#include "copasi/layout/CLEllipse.h"
#include "copasi/layout/CLPolygon.h"
#include "copasi/layout/CLGradientStop.h"
#include "copasi/layout/CLLineEnding.h"

// class CCopasiTask;
// class CCopasiReport;

// static
CCopasiXML::CCopasiXML():
  CCopasiXMLInterface(),
  mpModel(NULL),
  mpFunctionList(NULL),
  mpTaskList(NULL),
  mpReportList(NULL),
  mpPlotList(NULL),
  mpGUI(NULL),
  mpLayoutList(NULL),
  mpDataModel(NULL),
  mMCXML21Issued(false)
{}

CCopasiXML::~CCopasiXML() {}

bool CCopasiXML::save(std::ostream & os,
                      const std::string & relativeTo)
{
  mPWD = relativeTo;

  os.imbue(std::locale::classic());
  os.precision(std::numeric_limits<double>::digits10 + 2);

  mpOstream = &os;
  bool success = true;

  *mpOstream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
             << std::endl;

  *mpOstream << "<!-- generated with COPASI "
             << CVersion::VERSION.getVersion()
             << " (http://www.copasi.org) at "
             << UTCTimeStamp()
             << " -->"
             << std::endl;

  *mpOstream << "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>" << std::endl;

  CXMLAttributeList Attributes;
  Attributes.add("xmlns", "http://www.copasi.org/static/schema");
  Attributes.add("versionMajor", CVersion::VERSION.getVersionMajor());
  Attributes.add("versionMinor", CVersion::VERSION.getVersionMinor());
  Attributes.add("versionDevel", CVersion::VERSION.getVersionDevel());
  Attributes.add("copasiSourcesModified", CVersion::VERSION.isSourceModified());

  /*
  Attributes.add("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
  Attributes.add("xsi:noNamespaceSchemaLocation",
                 "http://www.copasi.org/static/schema/CopasiML.rng");
  */

  startSaveElement("COPASI", Attributes);

  if (haveModel() && !haveFunctionList())
    {
      success &= buildFunctionList();
      success &= saveFunctionList();
      success &= freeFunctionList();
    }
  else
    {
      success &= saveFunctionList();
    }

  success &= saveModel();
  success &= saveTaskList();
  success &= saveReportList();
  success &= savePlotList();
  success &= saveGUI();
  success &= saveLayoutList();
  success &= saveSBMLReference();

  // moved to the end, so that older version of COPASI can still read the model.
  success &= saveUnitDefinitionList();

  endSaveElement("COPASI");

  return success;
}

bool CCopasiXML::saveModelParameterSets(std::ostream & os, const std::string & relativeTo)
{
  mPWD = relativeTo;

  os.imbue(std::locale::classic());
  os.precision(std::numeric_limits<double>::digits10 + 2);

  mpOstream = &os;
  bool success = true;

  *mpOstream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
             << std::endl;

  *mpOstream << "<!-- generated with COPASI "
             << CVersion::VERSION.getVersion()
             << " (http://www.copasi.org) at "
             << UTCTimeStamp()
             << " -->"
             << std::endl;

  *mpOstream << "<?oxygen RNGSchema=\"http://www.copasi.org/static/schema/CopasiML.rng\" type=\"xml\"?>" << std::endl;

  CXMLAttributeList Attributes;
  Attributes.add("xmlns", "http://www.copasi.org/static/schema");
  Attributes.add("versionMajor", CVersion::VERSION.getVersionMajor());
  Attributes.add("versionMinor", CVersion::VERSION.getVersionMinor());
  Attributes.add("versionDevel", CVersion::VERSION.getVersionDevel());
  Attributes.add("copasiSourcesModified", CVersion::VERSION.isSourceModified());

  startSaveElement("COPASI", Attributes);

  if (haveModel())
    {
      CXMLAttributeList Attributes;
      Attributes.add("key", mpModel->getKey());
      Attributes.add("name", mpModel->getObjectName());
      Attributes.add("simulationType", CModelEntity::XMLStatus[mpModel->getStatus()]);
      Attributes.add("timeUnit", mpModel->getTimeUnitName());
      Attributes.add("volumeUnit", mpModel->getVolumeUnitName());
      Attributes.add("areaUnit", mpModel->getAreaUnitName());
      Attributes.add("lengthUnit", mpModel->getLengthUnitName());
      Attributes.add("quantityUnit", mpModel->getQuantityUnitName());
      Attributes.add("type", CModel::ModelTypeNames[mpModel->getModelType()]);
      Attributes.add("avogadroConstant", mpModel->getAvogadro());

      // This is now optional
      // Attributes.add("stateVariable",
      //                mpModel->getStateTemplate().getKey(mpModel->getKey()));

      startSaveElement("Model", Attributes);
      saveModelParameterSets();
      endSaveElement("Model");
    }

  endSaveElement("COPASI");

  return success;
}

bool CCopasiXML::load(std::istream & is,
                      const std::string & relativeTo)
{
  mPWD = relativeTo;

  is.imbue(std::locale::classic());
  is.precision(std::numeric_limits<double>::digits10 + 2);

  mpIstream = &is;
  bool success = true;
  bool done = false;

  CVersion FileVersion;
  CXMLParser Parser(FileVersion);

  Parser.setFunctionList(mpFunctionList);
  Parser.setGUI(mpGUI);
  Parser.setLayoutList(mpLayoutList);
  Parser.setDatamodel(this->mpDataModel);

#define BUFFER_SIZE 0xfffe
  char * pBuffer = new char[BUFFER_SIZE + 1];

  try
    {
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
    }

  catch (...)
    {
      success = false;
    }

  delete [] pBuffer;
#undef BUFFER_SIZE

  mpModel = Parser.getModel();
  mpReportList = Parser.getReportList();
  mpTaskList = Parser.getTaskList();
  mpPlotList = Parser.getPlotList();
  mpLayoutList = Parser.getLayoutList();
  CUnitDefinitionDB * pUnitDefinitionImportList = Parser.getUnitDefinitionImportList();

  if (!success)
    {
      pdelete(mpModel);
      pdelete(mpReportList);
      pdelete(mpTaskList);
      pdelete(mpPlotList);
      pdelete(mpLayoutList);
    }
  else
    mergeUnitDefinitions(pUnitDefinitionImportList);

  if (FileVersion.getVersionDevel() <= 18)
    {
      fixBuild18();
    }

  // The range in which the fix needs to be applied
  if (36 <= FileVersion.getVersionDevel() && FileVersion.getVersionDevel() <= 58)
    {
      fixBuild55();
    }

  if (FileVersion.getVersionDevel() <= 81)
    {
      fixBuild81();
    }

  if (FileVersion.getVersionDevel() < 104)
    {
      fixBuildBefore104();
    }

  if (FileVersion.getVersionDevel() < 113)
    {
      fixBuild113();
    }

  if (FileVersion.getVersionDevel() < 171)
    {
      fixBuild171();
    }

  if (!CVersion::VERSION.isCompatible(FileVersion))
    CCopasiMessage(CCopasiMessage::WARNING, MCXML + 9, FileVersion.getVersion().c_str());

  return success;
}

void CCopasiXML::mergeUnitDefinitions(CUnitDefinitionDB * pUnitDefImportList)
{
  size_t Size = CCopasiMessage::size();

  CUnitDefinitionDB * pCopasiUnitDefinitionList = CRootContainer::getUnitList();

  if (pUnitDefImportList == NULL ||
      pCopasiUnitDefinitionList == NULL)
    return;

  std::ostringstream name, symbol;
  CUnitDefinition * pUnitDefToAdd, * pUnitDefInRootContainer;
  std::set<CUnitDefinition *> unitDefsToAdd;

  // Add them if they don't already exist. First change name and/or
  // symbol if there are collisions.
  CDataVectorN< CUnitDefinition >::iterator itIL = pUnitDefImportList->begin();
  CDataVectorN< CUnitDefinition >::iterator endIL = pUnitDefImportList->end();

  for (; itIL != endIL; ++itIL) //For all of the Unit Defintions to potentially import . . .
    {
      name.str("");
      name << itIL->getObjectName();

      symbol.str("");
      symbol << itIL->getSymbol();

      // If an object of this name already exists, we'll want more information.
      if (pCopasiUnitDefinitionList->getIndex(name.str()) != C_INVALID_INDEX)
        pUnitDefInRootContainer = &pCopasiUnitDefinitionList->operator [](name.str());
      else
        pUnitDefInRootContainer = NULL;

      if (pUnitDefInRootContainer != NULL && //implies name conflict
          pUnitDefInRootContainer->getSymbol() == symbol.str() &&
          pUnitDefInRootContainer->getExpression() == itIL->getExpression())
        continue; // No need to add an identical unit

      // If necessary, generate, then set, a non-conflicting name.
      int i = 0;

      while (pCopasiUnitDefinitionList->getIndex(name.str()) != C_INVALID_INDEX)
        {
          name.str("");
          name << itIL->getObjectName() << "_" << ++i;
        }

      // By now we know we will add a copy of this one.
      pUnitDefToAdd = new CUnitDefinition(name.str(), NULL); // name should now not conflict
      pUnitDefToAdd->setExpression(itIL->getExpression());

      // If necessary, generate, then set, a non-conflicting symbol.
      if (pCopasiUnitDefinitionList->containsSymbol(symbol.str()))
        {
          i = 0;

          while (pCopasiUnitDefinitionList->containsSymbol(symbol.str()) ||
                 pUnitDefImportList->containsSymbol(symbol.str()))
            {
              symbol.str("");
              symbol << itIL->getSymbol() << "_" << ++i;
            }

          // for all the ones aready chosen to add (includes current one)
          std::set< CUnitDefinition * >::iterator itChosen = unitDefsToAdd.begin();
          std::set< CUnitDefinition * >::iterator endChosen = unitDefsToAdd.end();

          for (; itChosen != endChosen; ++itChosen)
            {
              (*itChosen)->setExpression(CUnit::replaceSymbol((*itChosen)->getExpression(), itIL->getSymbol(), pUnitDefToAdd->getSymbol()));
            }

          // for all the ones remaining in the Import List
          CDataVectorN< CUnitDefinition >::iterator itILrem = itIL;

          for (; itILrem != endIL; ++itILrem)
            {
              itILrem->setExpression(CUnit::replaceSymbol(itILrem->getExpression(), itIL->getSymbol(), pUnitDefToAdd->getSymbol()));
            }

          // for any units used in the model
          mpModel->changeUnitExpressionSymbols(itIL->getSymbol(), pUnitDefToAdd->getSymbol());
        }

      pUnitDefToAdd->setSymbol(symbol.str());

      // Finally we can add, and allow the Copasi Unit Definition List to adopt, it.
      pCopasiUnitDefinitionList->add(pUnitDefToAdd, true);
      unitDefsToAdd.insert(pUnitDefToAdd); // keep track of this, in-case need symbol update
    }

  // Remove error messages created while merging
  while (CCopasiMessage::size() > Size)
    CCopasiMessage::getLastMessage();
}

bool CCopasiXML::setModel(CModel * pModel)
{
  mpModel = pModel;
  return true;
}

CModel * CCopasiXML::getModel() const {return mpModel;}

bool CCopasiXML::haveModel() const {return mpModel != NULL;}

bool CCopasiXML::freeModel()
{
  pdelete(mpModel);
  return true;
}

bool CCopasiXML::setFunctionList(CDataVectorN< CFunction > *pFunctionList)
{
  mpFunctionList = pFunctionList;
  return true;
}

CDataVectorN< CFunction > * CCopasiXML::getFunctionList() const
{return mpFunctionList;}

bool CCopasiXML::haveFunctionList() const
{return mpFunctionList != NULL;}

bool CCopasiXML::freeFunctionList()
{
  pdelete(mpFunctionList);
  return true;
}

bool CCopasiXML::setTaskList(CDataVectorN< CCopasiTask > * pTaskList)
{
  mpTaskList = pTaskList;
  return true;
}

/**
 * Set the datamodel.
 * @param CDataModel* pDataModel
 * @return bool success
 */
bool CCopasiXML::setDatamodel(CDataModel* pDataModel)
{
  this->mpDataModel = pDataModel;
  return true;
}

CDataVectorN< CCopasiTask > * CCopasiXML::getTaskList() const
{return mpTaskList;}

bool CCopasiXML::haveTaskList() const
{return mpTaskList != NULL;}

bool CCopasiXML::freeTaskList()
{
  pdelete(mpTaskList);
  return true;
}

//************

bool CCopasiXML::setPlotList(COutputDefinitionVector * pPlotList)
{
  mpPlotList = pPlotList;
  return true;
}

COutputDefinitionVector * CCopasiXML::getPlotList() const
{return mpPlotList;}

bool CCopasiXML::havePlotList() const
{return mpPlotList != NULL;}

bool CCopasiXML::freePlotList()
{
  pdelete(mpPlotList);
  return true;
}

//************

bool CCopasiXML::setReportList(CReportDefinitionVector * pReportList)
{
  mpReportList = pReportList;
  return true;
}

CReportDefinitionVector * CCopasiXML::getReportList() const
{return mpReportList;}

bool CCopasiXML::haveReportList() const
{return mpReportList != NULL;}

bool CCopasiXML::freeReportList()
{
  pdelete(mpReportList);
  return true;
}

//************

bool CCopasiXML::setGUI(SCopasiXMLGUI * pGUI)
{
  mpGUI = pGUI;
  return true;
}

SCopasiXMLGUI * CCopasiXML::getGUI() const {return mpGUI;}

bool CCopasiXML::haveGUI() const {return mpGUI != NULL;}

bool CCopasiXML::freeGUI()
{
  pdelete(mpGUI);
  return true;
}

//************

bool CCopasiXML::setLayoutList(const CListOfLayouts & layoutList)
{
  mpLayoutList = const_cast<CListOfLayouts *>(&layoutList);
  return true;
}

CListOfLayouts * CCopasiXML::getLayoutList() const
{return mpLayoutList;}

bool CCopasiXML::haveLayoutList() const
{return mpLayoutList != NULL;}

bool CCopasiXML::freeLayoutList()
{
  pdelete(mpLayoutList);
  return true;
}

bool CCopasiXML::saveModel()
{
  bool success = true;

  if (!haveModel()) return success;

  CXMLAttributeList Attributes;
  Attributes.add("key", mpModel->getKey());
  Attributes.add("name", mpModel->getObjectName());
  Attributes.add("simulationType", CModelEntity::XMLStatus[mpModel->getStatus()]);
  Attributes.add("timeUnit", mpModel->getTimeUnitName());
  Attributes.add("volumeUnit", mpModel->getVolumeUnitName());
  Attributes.add("areaUnit", mpModel->getAreaUnitName());
  Attributes.add("lengthUnit", mpModel->getLengthUnitName());
  Attributes.add("quantityUnit", mpModel->getQuantityUnitName());
  Attributes.add("type", CModel::ModelTypeNames[mpModel->getModelType()]);
  Attributes.add("avogadroConstant", mpModel->getAvogadro());

  // This is now optional
  // Attributes.add("stateVariable",
  //                mpModel->getStateTemplate().getKey(mpModel->getKey()));

  startSaveElement("Model", Attributes);

  saveAnnotation(mpModel);

  if (mpModel->getInitialExpression() != "")
    {
      startSaveElement("InitialExpression");
      saveData(mpModel->getInitialExpression());
      endSaveElement("InitialExpression");
    }

  size_t i, imax;

  // Compartment
  if ((imax = mpModel->getCompartments().size()) > 0)
    {
      startSaveElement("ListOfCompartments");

      Attributes.erase();
      Attributes.add("key", "");
      Attributes.add("name", "");
      Attributes.add("simulationType", "");
      Attributes.add("dimensionality", "");
      Attributes.add("addNoise", "");

      size_t i, imax = mpModel->getCompartments().size();

      for (i = 0; i < imax; i++)
        {
          const CCompartment * pComp = &mpModel->getCompartments()[i];

          Attributes.setValue(0, pComp->getKey());
          Attributes.setValue(1, pComp->getObjectName());
          CModelEntity::Status SimulationType = pComp->getStatus();
          Attributes.setValue(2, CModelEntity::XMLStatus[SimulationType]);
          Attributes.setValue(3, pComp->getDimensionality());
          Attributes.setValue(4, pComp->hasNoise() ? "true" : "false");

          startSaveElement("Compartment", Attributes);

          saveAnnotation(pComp);

          if (SimulationType != CModelEntity::Status::FIXED &&
              pComp->getExpression() != "")
            {
              startSaveElement("Expression");
              saveData(pComp->getExpression());
              endSaveElement("Expression");
            }

          if (pComp->getInitialExpression() != "")
            {
              startSaveElement("InitialExpression");
              saveData(pComp->getInitialExpression());
              endSaveElement("InitialExpression");
            }

          // We save the noise expression even if it is not used
          if (pComp->getNoiseExpression() != "")
            {
              startSaveElement("NoiseExpression");
              saveData(pComp->getNoiseExpression());
              endSaveElement("NoiseExpression");
            }

          endSaveElement("Compartment");

          if (pComp->getSBMLId() != "")
            mSBMLReference[pComp->getSBMLId()] = pComp->getKey();
        }

      endSaveElement("ListOfCompartments");
    }

  // Metabolites (aka. Species)
  if ((imax = mpModel->getMetabolites().size()) > 0)
    {
      startSaveElement("ListOfMetabolites");

      Attributes.erase();
      Attributes.add("key", "");
      Attributes.add("name", "");
      Attributes.add("simulationType", "");
      Attributes.add("compartment", "");
      Attributes.add("addNoise", "");

      for (i = 0; i < imax; i++)
        {
          const CMetab * pMetab = &mpModel->getMetabolites()[i];

          Attributes.setValue(0, pMetab->getKey());
          Attributes.setValue(1, pMetab->getObjectName());
          CModelEntity::Status SimulationType = pMetab->getStatus();
          Attributes.setValue(2, CModelEntity::XMLStatus[SimulationType]);
          Attributes.setValue(3, pMetab->getCompartment()->getKey());
          Attributes.setValue(4, pMetab->hasNoise() ? "true" : "false");

          startSaveElement("Metabolite", Attributes);

          saveAnnotation(pMetab);

          if (SimulationType != CModelEntity::Status::FIXED &&
              SimulationType != CModelEntity::Status::REACTIONS &&
              pMetab->getExpression() != "")
            {
              startSaveElement("Expression");
              saveData(pMetab->getExpression());
              endSaveElement("Expression");
            }

          if (pMetab->getInitialExpression() != "")
            {
              startSaveElement("InitialExpression");
              saveData(pMetab->getInitialExpression());
              endSaveElement("InitialExpression");
            }

          // We save the noise expression even if it is not used
          if (pMetab->getNoiseExpression() != "")
            {
              startSaveElement("NoiseExpression");
              saveData(pMetab->getNoiseExpression());
              endSaveElement("NoiseExpression");
            }

          endSaveElement("Metabolite");

          if (pMetab->getSBMLId() != "")
            mSBMLReference[pMetab->getSBMLId()] = pMetab->getKey();
        }

      endSaveElement("ListOfMetabolites");
    }

  // Model Values (aka. Global Quantities)
  if ((imax = mpModel->getModelValues().size()) > 0)
    {
      startSaveElement("ListOfModelValues");

      Attributes.erase();
      Attributes.add("key", "");
      Attributes.add("name", "");
      Attributes.add("simulationType", "");
      Attributes.add("addNoise", "");

      for (i = 0; i < imax; i++)
        {
          const CModelValue * pMV = &mpModel->getModelValues()[i];

          Attributes.setValue(0, pMV->getKey());
          Attributes.setValue(1, pMV->getObjectName());
          CModelEntity::Status SimulationType = pMV->getStatus();
          Attributes.setValue(2, CModelEntity::XMLStatus[SimulationType]);
          Attributes.setValue(3, pMV->hasNoise() ? "true" : "false");

          startSaveElement("ModelValue", Attributes);

          saveAnnotation(pMV);

          if (SimulationType != CModelEntity::Status::FIXED &&
              pMV->getExpression() != "")
            {
              startSaveElement("Expression");
              saveData(pMV->getExpression());
              endSaveElement("Expression");
            }

          if (pMV->getInitialExpression() != "")
            {
              startSaveElement("InitialExpression");
              saveData(pMV->getInitialExpression());
              endSaveElement("InitialExpression");
            }

          // We save the noise expression even if it is not used
          if (pMV->getNoiseExpression() != "")
            {
              startSaveElement("NoiseExpression");
              saveData(pMV->getNoiseExpression());
              endSaveElement("NoiseExpression");
            }

          if (pMV->getUnitExpression() != "")
            {
              startSaveElement("Unit");
              saveData(pMV->getUnitExpression());
              endSaveElement("Unit");
            }

          endSaveElement("ModelValue");

          if (pMV->getSBMLId() != "")
            mSBMLReference[pMV->getSBMLId()] = pMV->getKey();
        }

      endSaveElement("ListOfModelValues");
    }

  // Reactions
  if ((imax = mpModel->getReactions().size()) > 0)
    {
      startSaveElement("ListOfReactions");

      CXMLAttributeList Attr;
      const CDataVector< CChemEqElement > * pReactantList;
      size_t j, jmax;

      std::vector< const CDataObject * > ObjectList;
      size_t k, kmax;

      Attributes.erase();
      Attributes.add("key", "");
      Attributes.add("name", "");
      Attributes.add("reversible", "");
      Attributes.add("fast", "");
      Attributes.add("addNoise", "");

      for (i = 0; i < imax; i++)
        {
          const CReaction * pReaction = &mpModel->getReactions()[i];

          Attributes.setValue(0, pReaction->getKey());
          Attributes.setValue(1, pReaction->getObjectName());
          Attributes.setValue(2, pReaction->isReversible() ? "true" : "false");
          Attributes.setValue(3, pReaction->isFast() ? "true" : "false");
          Attributes.setValue(4, pReaction->hasNoise() ? "true" : "false");

          if (pReaction->getSBMLId() != "")
            mSBMLReference[pReaction->getSBMLId()] = pReaction->getKey();

          startSaveElement("Reaction", Attributes);

          saveAnnotation(pReaction);

          Attr.erase();
          Attr.add("metabolite", "");
          Attr.add("stoichiometry", "");

          pReactantList = & pReaction->getChemEq().getSubstrates();

          if ((jmax = pReactantList->size()) > 0)
            {
              startSaveElement("ListOfSubstrates");

              for (j = 0; j < jmax; j++)
                {
                  Attr.setValue(0, (*pReactantList)[j].getMetaboliteKey());
                  Attr.setValue(1, (*pReactantList)[j].getMultiplicity());

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
                  Attr.setValue(0, (*pReactantList)[j].getMetaboliteKey());
                  Attr.setValue(1, (*pReactantList)[j].getMultiplicity());

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
                  Attr.setValue(0, (*pReactantList)[j].getMetaboliteKey());
                  Attr.setValue(1, (*pReactantList)[j].getMultiplicity());

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
                  Attr.setValue(2, pParamList->getValue< C_FLOAT64 >(j));

                  saveElement("Constant", Attr);
                }

              endSaveElement("ListOfConstants");
            }

          if (pReaction->getFunction() != CRootContainer::getUndefinedFunction())
            {
              Attr.erase();
              Attr.add("function", pReaction->getFunction()->getKey());
              Attr.add("unitType", CReaction::KineticLawUnitTypeName[pReaction->getKineticLawUnitType()]);

              if (pReaction->getScalingCompartment() != NULL)
                {
                  Attr.add("scalingCompartment", pReaction->getScalingCompartment()->getCN());
                }

              startSaveElement("KineticLaw", Attr);

              if ((jmax = pReaction->getFunctionParameters().size()))
                {
                  startSaveElement("ListOfCallParameters");
                  const std::vector< std::vector< const CDataObject * > > & rMap =
                    pReaction->getParameterObjects();

                  for (j = 0; j < jmax; j++)
                    {
                      Attr.erase();
                      Attr.add("functionParameter",
                               pReaction->getFunction()->getVariables()[j]->getKey());

                      startSaveElement("CallParameter", Attr);

                      Attr.erase();
                      Attr.add("reference", "");

                      for (k = 0, kmax = rMap[j].size(); k < kmax; k++)
                        {
                          Attr.setValue(0, rMap[j][k]->getKey());
                          saveElement("SourceParameter", Attr);
                        }

                      endSaveElement("CallParameter");
                    }

                  endSaveElement("ListOfCallParameters");
                }

              endSaveElement("KineticLaw");
            }

          // We save the noise expression even if it is not used
          if (pReaction->getNoiseExpression() != "")
            {
              startSaveElement("NoiseExpression");
              saveData(pReaction->getNoiseExpression());
              endSaveElement("NoiseExpression");
            }

          endSaveElement("Reaction");
        }

      endSaveElement("ListOfReactions");
    }

  // Events (added 07.04.08)
  if ((imax = mpModel->getEvents().size()) > 0)
    {
      startSaveElement("ListOfEvents");

      Attributes.erase();
      Attributes.add("key", "");
      Attributes.add("name", "");
      Attributes.add("delayAssignment", "");
      Attributes.add("fireAtInitialTime", "");
      Attributes.add("persistentTrigger", "");

      for (i = 0; i < imax; i++)
        {
          const CEvent * pEvent = &mpModel->getEvents()[i];

          Attributes.setValue(0, pEvent->getKey());
          Attributes.setValue(1, pEvent->getObjectName());

          if (pEvent->getDelayExpression() != "")
            {
              Attributes.setValue(2, pEvent->getDelayAssignment() ? "true" : "false");
            }
          else
            {
              Attributes.skip(2);
            }

          Attributes.setValue(3, pEvent->getFireAtInitialTime());
          Attributes.setValue(4, pEvent->getPersistentTrigger());

          startSaveElement("Event", Attributes);

          saveAnnotation(pEvent);

          if (pEvent->getTriggerExpression() != "")
            {
              startSaveElement("TriggerExpression");
              saveData(pEvent->getTriggerExpression());
              endSaveElement("TriggerExpression");
            }

          if (pEvent->getDelayExpression() != "")
            {
              startSaveElement("DelayExpression");
              saveData(pEvent->getDelayExpression());
              endSaveElement("DelayExpression");
            }

          if (pEvent->getPriorityExpression() != "")
            {
              startSaveElement("PriorityExpression");
              saveData(pEvent->getPriorityExpression());
              endSaveElement("PriorityExpression");
            }

          const CDataVectorN< CEventAssignment > & Assignments = pEvent->getAssignments();

          if (Assignments.size() > 0)
            {
              CDataModel * pDataModel = Assignments.getObjectDataModel();

              startSaveElement("ListOfAssignments");

              CXMLAttributeList Attr;
              Attr.add("target", "");

              CDataVectorN< CEventAssignment >::const_iterator it = Assignments.begin();
              CDataVectorN< CEventAssignment >::const_iterator end = Assignments.end();

              for (; it != end; ++it)
                {
                  Attr.setValue(0, it->getXmlTargetCN());

                  startSaveElement("Assignment", Attr);

                  startSaveElement("Expression");
                  saveData(it->getExpression());
                  endSaveElement("Expression");

                  endSaveElement("Assignment");
                }

              endSaveElement("ListOfAssignments");
            }

          endSaveElement("Event");

          if (pEvent->getSBMLId() != "")
            mSBMLReference[pEvent->getSBMLId()] = pEvent->getKey();
        }

      endSaveElement("ListOfEvents");
    }

  // Save the model parameter sets
  saveModelParameterSets();

  // The State an state Template is only save for backwards compatibility
  startSaveElement("StateTemplate");

  Attributes.erase();
  // This is now optional.
  // Attributes.add("key", "");
  Attributes.add("objectReference", "");
  std::pair< std::string, std::string > Variable;

  const CModelEntity *const* ppEntity = mpModel->getStateTemplate().getEntities().array();
  const CModelEntity *const* ppEntityEnd = ppEntity + mpModel->getStateTemplate().size();

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    {
      Attributes.setValue(0, (*ppEntity)->getKey());

      saveElement("StateTemplateVariable", Attributes);
    }

  endSaveElement("StateTemplate");

  Attributes.erase();
  Attributes.add("type", "initialState");
  startSaveElement("InitialState", Attributes);
  *mpOstream << mIndent;
  ppEntity = mpModel->getStateTemplate().getEntities().array();

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    {
      *mpOstream << (DBL)(*ppEntity)->getInitialValue() << " ";
    }

  *mpOstream << std::endl;

  endSaveElement("InitialState");

  endSaveElement("Model");

  return success;
}

void CCopasiXML::saveModelParameterSets()
{
  CXMLAttributeList Attributes;
  size_t imax = 0, i = 0;
  Attributes.erase();
  const CModelParameterSet * pSet = &mpModel->getActiveModelParameterSet();
  Attributes.add("activeSet", pSet->getKey());

  startSaveElement("ListOfModelParameterSets", Attributes);

  Attributes.erase();
  Attributes.add("key", "");
  Attributes.add("name", "");

  pSet = &mpModel->getActiveModelParameterSet();

  Attributes.setValue(0, pSet->getKey());
  Attributes.setValue(1, pSet->getObjectName());

  startSaveElement("ModelParameterSet", Attributes);

  saveAnnotation(pSet);

  CModelParameterGroup::const_iterator itSet = pSet->begin();
  CModelParameterGroup::const_iterator endSet = pSet->end();

  for (; itSet != endSet; ++itSet)
    {
      saveModelParameter(*itSet);
    }

  endSaveElement("ModelParameterSet");

  imax = mpModel->getModelParameterSets().size();

  for (i = 0; i < imax; i++)
    {
      pSet = &mpModel->getModelParameterSets()[i];

      Attributes.setValue(0, pSet->getKey());
      Attributes.setValue(1, pSet->getObjectName());

      startSaveElement("ModelParameterSet", Attributes);

      saveAnnotation(pSet);

      itSet = pSet->begin();
      endSet = pSet->end();

      for (; itSet != endSet; ++itSet)
        {
          saveModelParameter(*itSet);
        }

      endSaveElement("ModelParameterSet");
    }

  endSaveElement("ListOfModelParameterSets");
}

bool CCopasiXML::saveAnnotation(const CAnnotation * pAnnotation)
{
  if (pAnnotation->getMiriamAnnotation() != "")
    {
      startSaveElement("MiriamAnnotation");
      *mpOstream << pAnnotation->getMiriamAnnotation() << std::endl;
      endSaveElement("MiriamAnnotation");
    }

  if (pAnnotation->getNotes() != "")
    {
      startSaveElement("Comment");
      saveXhtml(pAnnotation->getNotes());
      endSaveElement("Comment");
    }

  if (pAnnotation->getUnsupportedAnnotations().size() > 0)
    {
      startSaveElement("ListOfUnsupportedAnnotations");

      CAnnotation::UnsupportedAnnotation::const_iterator it = pAnnotation->getUnsupportedAnnotations().begin();
      CAnnotation::UnsupportedAnnotation::const_iterator end = pAnnotation->getUnsupportedAnnotations().end();

      CXMLAttributeList Attributes;
      Attributes.add("name", "");

      for (; it != end; ++it)
        {
          Attributes.setValue(0, (*it).first);

          startSaveElement("UnsupportedAnnotation", Attributes);
          *mpOstream << (*it).second << std::endl;
          endSaveElement("UnsupportedAnnotation");
        }

      endSaveElement("ListOfUnsupportedAnnotations");
    }

  return true;
}

bool CCopasiXML::saveModelParameter(const CModelParameter * pModelParameter)
{
  // We do not save model parameters which are marked missing to preserve
  // their missing state.
  if (pModelParameter->getCompareResult() == CModelParameter::CompareResult::Missing)
    {
      return true;
    }

  bool success = true;

  CXMLAttributeList Attributes;

  if (pModelParameter->getType() != CModelParameter::Type::Reaction &&
      pModelParameter->getType() != CModelParameter::Type::Group)
    {
      Attributes.add("cn", pModelParameter->getCN());
      Attributes.add("value", pModelParameter->getValue(CCore::Framework::ParticleNumbers));
      Attributes.add("type", CModelParameter::TypeNames[pModelParameter->getType()]);
      Attributes.add("simulationType", CModelEntity::XMLStatus[pModelParameter->getSimulationType()]);

      if (pModelParameter->getInitialExpression() != "")
        {
          startSaveElement("ModelParameter", Attributes);
          startSaveElement("InitialExpression");
          saveData(pModelParameter->getInitialExpression());
          endSaveElement("InitialExpression");
          endSaveElement("ModelParameter");
        }
      else
        {
          saveElement("ModelParameter", Attributes);
        }
    }
  else
    {
      Attributes.add("cn", pModelParameter->getCN());
      Attributes.add("type", CModelParameter::TypeNames[pModelParameter->getType()]);

      startSaveElement("ModelParameterGroup", Attributes);

      CModelParameterGroup::const_iterator it = static_cast< const CModelParameterGroup * >(pModelParameter)->begin();
      CModelParameterGroup::const_iterator end = static_cast< const CModelParameterGroup * >(pModelParameter)->end();

      for (; it != end; ++it)
        {
          success &= saveModelParameter(*it);
        }

      endSaveElement("ModelParameterGroup");
    }

  return success;
}

bool CCopasiXML::saveFunctionList()
{
  bool success = true;

  if (!haveFunctionList()) return success;

  size_t i, imax = mpFunctionList->size();

  if (!imax) return success;

  CXMLAttributeList Attributes;
  const CFunction * pFunction = NULL;

  startSaveElement("ListOfFunctions");

  for (i = 0; i < imax; i++)
    {
      pFunction = &mpFunctionList->operator[](i);

      Attributes.erase();
      Attributes.add("key", pFunction->getKey());
      Attributes.add("name", pFunction->getObjectName());
      Attributes.add("type", CEvaluationTree::XMLType[pFunction->getType()]);

      if (pFunction)
        {
          switch (pFunction->isReversible())
            {
              case TriUnspecified:
                Attributes.add("reversible", "unspecified");
                break;

              case TriFalse:
                Attributes.add("reversible", "false");
                break;

              case TriTrue:
                Attributes.add("reversible", "true");
                break;
            }

          if (pFunction->getSBMLId() != "")
            mSBMLReference[pFunction->getSBMLId()] = pFunction->getKey();
        }

      startSaveElement("Function", Attributes);

      saveAnnotation(pFunction);

      startSaveElement("Expression");
      saveData(pFunction->getInfix());
      endSaveElement("Expression");

      if (pFunction)
        {
          startSaveElement("ListOfParameterDescriptions");

          size_t j, jmax = pFunction->getVariables().size();
          const CFunctionParameter * pParameter;

          Attributes.erase();
          Attributes.add("key", "");
          Attributes.add("name", "");
          Attributes.add("order", "");
          Attributes.add("role", "");

          for (j = 0; j < jmax; j++)
            {
              pParameter = pFunction->getVariables()[j];
              Attributes.setValue(0, pParameter->getKey());
              Attributes.setValue(1, pParameter->getObjectName());
              Attributes.setValue(2, j);
              Attributes.setValue(3, CFunctionParameter::RoleNameXML[pParameter->getUsage()]);

              saveElement("ParameterDescription", Attributes);
            }

          endSaveElement("ListOfParameterDescriptions");
        }

      endSaveElement("Function");
    }

  endSaveElement("ListOfFunctions");

  return success;
}

bool CCopasiXML::savePlotList()
{
  //std::cerr << "Saving plot list. " << std::endl;
  bool success = true;

  if (!havePlotList())
    {
      //std::cerr << "No plot list defined." << std::endl;
      return success;
    }

  size_t i, imax = mpPlotList->size();

  //std::cerr << "Saving " << imax << " plots." << std::endl;
  if (!imax) return success;

  CXMLAttributeList Attributes;

  startSaveElement("ListOfPlots");

  for (i = 0; i < imax; i++)
    {
      const CPlotSpecification* pPlot = &mpPlotList->operator[](i);

      Attributes.erase();
      Attributes.add("name", pPlot->getObjectName());
      Attributes.add("type", CPlotSpecification::XMLType[pPlot->getType()]);
      Attributes.add("active", pPlot->isActive());
      Attributes.add("taskTypes", pPlot->getTaskTypes());
      startSaveElement("PlotSpecification", Attributes);
      saveParameterGroup(pPlot->CCopasiParameter::getValue< CCopasiParameterGroup::elements >());
      startSaveElement("ListOfPlotItems");
      size_t j, jmax = pPlot->getItems().size();

      //std::cerr << "Saving " << jmax << "PlotItems." << std::endl;
      for (j = 0; j < jmax; j++)
        {
          const CPlotItem* pPlotItem = &pPlot->getItems()[j];
          Attributes.erase();
          Attributes.add("name", pPlotItem->getObjectName());
          Attributes.add("type", CPlotItem::XMLType[pPlotItem->getType()]);
          startSaveElement("PlotItem", Attributes);
          saveParameterGroup(pPlotItem->CCopasiParameter::getValue< CCopasiParameterGroup::elements >());
          startSaveElement("ListOfChannels");
          size_t k, kmax = pPlotItem->getNumChannels();

          //std::cerr << "Saving " << kmax << " Channels." << std::endl;
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

  size_t i, imax = mpTaskList->size();

  if (!imax) return success;

  CXMLAttributeList Attributes;
  const CCopasiTask * pTask = NULL;

  startSaveElement("ListOfTasks");

  for (i = 0; i < imax; i++)
    {
      pTask = &mpTaskList->operator[](i);

      Attributes.erase();
      Attributes.add("key", pTask->getKey());
      Attributes.add("name", pTask->getObjectName());
      Attributes.add("type", CTaskEnum::TaskXML[pTask->getType()]);
      Attributes.add("scheduled", pTask->isScheduled() ? "true" : "false");
      Attributes.add("updateModel", pTask->isUpdateModel() ? "true" : "false");

      startSaveElement("Task", Attributes);

      // Report Element
      const CReport & tReport = pTask->getReport();

      if (tReport.getReportDefinition())
        {
          Attributes.erase();
          Attributes.add("reference", tReport.getReportDefinition()->getKey());

          std::string Target = tReport.getTarget();

          if (!CDirEntry::isRelativePath(Target) &&
              !CDirEntry::makePathRelative(Target, mPWD))
            {
              // leave absolute path instead of breaking it
              // Target = CDirEntry::fileName(Target);
              CCopasiMessage(CCopasiMessage::WARNING, "Couldn't create relative path for Report Target of Task '%s' for file '%s' to '%s', leaving the absolute path.", pTask->getObjectName().c_str(), Target.c_str(), mPWD.c_str());
            }

          Attributes.add("target", Target);
          Attributes.add("append", tReport.append());
          Attributes.add("confirmOverwrite", tReport.confirmOverwrite());
          saveElement("Report", Attributes);
        }

      //Problem Element
      const CCopasiProblem *tProblem = pTask->getProblem();

      Attributes.erase();
      startSaveElement("Problem");
      saveParameterGroup(tProblem->CCopasiParameter::getValue< CCopasiParameterGroup::elements >());
      endSaveElement("Problem");

      // Method Element
      const CCopasiMethod *tMethod = pTask->getMethod();

      Attributes.erase();
      Attributes.add("name", tMethod->CCopasiParameter::getObjectName());
      Attributes.add("type", CTaskEnum::MethodXML[tMethod->getSubType()]);
      startSaveElement("Method", Attributes);
      saveParameterGroup(tMethod->CCopasiParameter::getValue< CCopasiParameterGroup::elements >());
      endSaveElement("Method");

      endSaveElement("Task");
    }

  endSaveElement("ListOfTasks");

  return success;
}

//Mrinmayee
bool CCopasiXML::saveReportSection(const std::string & name,
                                   const std::vector <CRegisteredCommonName> & section)
{
  CXMLAttributeList Attributes;
  Attributes.add("NoName", "");

  size_t j, jmax = section.size();

  if (jmax)
    {
      startSaveElement(name);

      for (j = 0; j < jmax; j++)
        {
          if (section[j].getObjectType() == "html")
            {
              saveXhtml(section[j].getObjectName());
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

  size_t i, imax = mpReportList->size();

  if (!imax) return success;

  CXMLAttributeList Attributes;
  const CReportDefinition * pReport = NULL;

  startSaveElement("ListOfReports");

  for (i = 0; i < imax; i++)
    {
      pReport = &mpReportList->operator[](i);

      Attributes.erase();
      Attributes.add("key", pReport->getKey());
      Attributes.add("name", pReport->getObjectName());
      Attributes.add("taskType", CTaskEnum::TaskXML[pReport->getTaskType()]);
      Attributes.add("separator", pReport->getSeparator().getStaticString());
      Attributes.add("precision", pReport->getPrecision());

      startSaveElement("Report", Attributes);

      startSaveElement("Comment");
      saveXhtml(pReport->getComment());
      endSaveElement("Comment");

      if (pReport->isTable())
        {
          Attributes.erase();
          Attributes.add("printTitle", pReport->getTitle());
          startSaveElement("Table", Attributes);

          const std::vector <CRegisteredCommonName> & Table = * pReport->getTableAddr();
          size_t j, jmax = Table.size();

          Attributes.erase();
          Attributes.add("cn", "");

          for (j = 0; j < jmax; j++)
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

void CCopasiXML::savePosition(const CLPoint& p, const std::string & tag)
{
  CXMLAttributeList Attributes;
  Attributes.erase();
  Attributes.add("x", p.getX());
  Attributes.add("y", p.getY());
  saveElement(tag, Attributes);
}

void CCopasiXML::saveDimensions(const CLDimensions& d)
{
  CXMLAttributeList Attributes;
  Attributes.erase();
  Attributes.add("width", d.getWidth());
  Attributes.add("height", d.getHeight());
  saveElement("Dimensions", Attributes);
}

void CCopasiXML::saveBoundingBox(const CLBoundingBox& bb)
{
  startSaveElement("BoundingBox");
  savePosition(bb.getPosition());
  saveDimensions(bb.getDimensions());
  endSaveElement("BoundingBox");
}

void CCopasiXML::saveCurve(const CLCurve& c)
{
  CXMLAttributeList Attributes;
  startSaveElement("Curve");

  if (c.getNumCurveSegments() > 0)
    {
      startSaveElement("ListOfCurveSegments");
      size_t i, imax = c.getNumCurveSegments();

      for (i = 0; i < imax; ++i)
        {
          const CLLineSegment & cs = c.getCurveSegments()[i];

          Attributes.erase();

          if (cs.isBezier())
            Attributes.add("xsi:type", "CubicBezier");
          else
            Attributes.add("xsi:type", "LineSegment");

          startSaveElement("CurveSegment", Attributes);

          savePosition(cs.getStart(), "Start");
          savePosition(cs.getEnd(), "End");

          if (cs.isBezier())
            {
              savePosition(cs.getBase1(), "BasePoint1");
              savePosition(cs.getBase2(), "BasePoint2");
            }

          endSaveElement("CurveSegment");
        }

      endSaveElement("ListOfCurveSegments");
    }

  endSaveElement("Curve");
}

bool CCopasiXML::saveLayoutList()
{
  bool success = true;

  if (!haveLayoutList()) return success;

  size_t i, imax = mpLayoutList->size();

  if (!imax) return success;

  CXMLAttributeList Attributes;
  const CLayout * pLayout = NULL;
  Attributes.add("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
  startSaveElement("ListOfLayouts", Attributes);

  for (i = 0; i < imax; i++)
    {
      pLayout = &mpLayoutList->operator[](i);

      Attributes.erase();
      Attributes.add("key", pLayout->getKey());
      Attributes.add("name", pLayout->getObjectName());
      startSaveElement("Layout", Attributes);

      Attributes.erase();
      Attributes.add("width", pLayout->getDimensions().getWidth());
      Attributes.add("height", pLayout->getDimensions().getHeight());
      saveElement("Dimensions", Attributes);

      size_t j, jmax;

      //compartment glyphs
      if (pLayout->getListOfCompartmentGlyphs().size() > 0)
        {
          startSaveElement("ListOfCompartmentGlyphs");

          jmax = pLayout->getListOfCompartmentGlyphs().size();

          for (j = 0; j < jmax; ++j)
            {
              const CLCompartmentGlyph* cg = &pLayout->getListOfCompartmentGlyphs()[j];
              Attributes.erase();
              Attributes.add("key", cg->getKey());
              Attributes.add("name", cg->getObjectName());

              if (!cg->getModelObjectKey().empty() && cg->hasValidModelReference())
                {
                  Attributes.add("compartment", cg->getModelObjectKey());
                }
              else
                {
                  // we set the model reference to the empty string so that
                  // the warnings message only appears on the first save operation
                  const_cast< CLCompartmentGlyph * >(cg)->setModelObjectKey("");

                  if (!this->mMCXML21Issued)
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCXML + 21);
                      this->mMCXML21Issued = true;
                    }

                  // Bug 1973: we still write out the attribute, so that older
                  //           versions of COPASI do not refuse to read the model
                  Attributes.add("metabolite", "");
                }

              if (cg->getObjectRole().find_first_not_of(" \t\r\n") != std::string::npos)
                {
                  Attributes.add("objectRole", cg->getObjectRole());
                }

              startSaveElement("CompartmentGlyph", Attributes);

              saveBoundingBox(cg->getBoundingBox());

              endSaveElement("CompartmentGlyph");
            }

          endSaveElement("ListOfCompartmentGlyphs");
        }

      //species glyphs
      if (pLayout->getListOfMetaboliteGlyphs().size() > 0)
        {
          startSaveElement("ListOfMetabGlyphs");

          jmax = pLayout->getListOfMetaboliteGlyphs().size();

          for (j = 0; j < jmax; ++j)
            {
              const CLMetabGlyph* cg = &pLayout->getListOfMetaboliteGlyphs()[j];
              Attributes.erase();
              Attributes.add("key", cg->getKey());
              Attributes.add("name", cg->getObjectName());

              if (!cg->getModelObjectKey().empty() && cg->hasValidModelReference())
                {
                  Attributes.add("metabolite", cg->getModelObjectKey());
                }
              else if (cg->getObjectRole() != "invisible")
                {
                  // we set the model reference to the empty string so that
                  // the warnings message only appears on the first save operation
                  const_cast< CLMetabGlyph * >(cg)->setModelObjectKey("");

                  if (!this->mMCXML21Issued)
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCXML + 21);
                      this->mMCXML21Issued = true;
                    }

                  // Bug 1973: we still write out the attribute, so that older
                  //           versions of COPASI do not refuse to read the model
                  Attributes.add("metabolite", "");
                }

              if (cg->getObjectRole().find_first_not_of(" \t\r\n") != std::string::npos)
                {
                  Attributes.add("objectRole", cg->getObjectRole());
                }

              startSaveElement("MetaboliteGlyph", Attributes);

              saveBoundingBox(cg->getBoundingBox());

              endSaveElement("MetaboliteGlyph");
            }

          endSaveElement("ListOfMetabGlyphs");
        }

      //reaction glyphs
      if (pLayout->getListOfReactionGlyphs().size() > 0)
        {
          startSaveElement("ListOfReactionGlyphs");

          jmax = pLayout->getListOfReactionGlyphs().size();

          for (j = 0; j < jmax; ++j)
            {
              const CLReactionGlyph* cg = &pLayout->getListOfReactionGlyphs()[j];
              Attributes.erase();
              Attributes.add("key", cg->getKey());
              Attributes.add("name", cg->getObjectName());

              if (!cg->getModelObjectKey().empty() && cg->hasValidModelReference())
                {
                  Attributes.add("reaction", cg->getModelObjectKey());
                }
              else
                {
                  // we set the model reference to the empty string so that
                  // the warnings message only appears on the first save operation
                  const_cast< CLReactionGlyph * >(cg)->setModelObjectKey("");

                  if (!this->mMCXML21Issued)
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCXML + 21);
                      this->mMCXML21Issued = true;
                    }
                }

              if (cg->getObjectRole().find_first_not_of(" \t\r\n") != std::string::npos)
                {
                  Attributes.add("objectRole", cg->getObjectRole());
                }

              startSaveElement("ReactionGlyph", Attributes);

              if (!cg->getBoundingBox().isEmpty())
                saveBoundingBox(cg->getBoundingBox());

              if (cg->getCurve().getNumCurveSegments() >= 0)
                saveCurve(cg->getCurve());

              // metab reference glyphs
              startSaveElement("ListOfMetaboliteReferenceGlyphs");
              size_t k, kmax = cg->getListOfMetabReferenceGlyphs().size();

              for (k = 0; k < kmax; ++k)
                {
                  const CLMetabReferenceGlyph * mrg = &cg->getListOfMetabReferenceGlyphs()[k];
                  Attributes.erase();
                  Attributes.add("key", mrg->getKey());
                  Attributes.add("name", mrg->getObjectName());
                  Attributes.add("metaboliteGlyph", mrg->getMetabGlyphKey());
                  //Attributes.add("metaboliteReference", mrg->getXXX());
                  Attributes.add("role", CLMetabReferenceGlyph::XMLRole[mrg->getRole()]);

                  if (mrg->getObjectRole().find_first_not_of(" \t\r\n") != std::string::npos)
                    {
                      Attributes.add("objectRole", mrg->getObjectRole());
                    }

                  startSaveElement("MetaboliteReferenceGlyph", Attributes);

                  if (mrg->getCurve().getNumCurveSegments() == 0)
                    saveBoundingBox(mrg->getBoundingBox());
                  else
                    saveCurve(mrg->getCurve());

                  endSaveElement("MetaboliteReferenceGlyph");
                }

              endSaveElement("ListOfMetaboliteReferenceGlyphs");

              endSaveElement("ReactionGlyph");
            }

          endSaveElement("ListOfReactionGlyphs");
        }

      //text Glyphs
      if (pLayout->getListOfTextGlyphs().size() > 0)
        {
          startSaveElement("ListOfTextGlyphs");

          jmax = pLayout->getListOfTextGlyphs().size();

          for (j = 0; j < jmax; ++j)
            {
              const CLTextGlyph* cg = &pLayout->getListOfTextGlyphs()[j];
              // we only export the text glyph if it either has a text
              // or a valid originOfText
              std::string id = cg->getModelObjectKey();

              if (cg->isTextSet() || id.find_first_not_of(" \t\r\n") != std::string::npos)
                {
                  Attributes.erase();
                  Attributes.add("key", cg->getKey());
                  Attributes.add("name", cg->getObjectName());
                  Attributes.add("graphicalObject", cg->getGraphicalObjectKey());

                  if (cg->isTextSet())
                    {
                      Attributes.add("text", cg->getText());
                    }
                  else
                    {
                      // check if the object actually exists
                      if (cg->hasValidModelReference())
                        {
                          Attributes.add("originOfText", id);
                        }
                      else
                        {
                          // set the text to unset instead
                          Attributes.add("text", "unset");
                          // set the invalid key to the empty string
                          const_cast< CLTextGlyph * >(cg)->setModelObjectKey("");
                          const_cast< CLTextGlyph * >(cg)->setText("unset");

                          if (!this->mMCXML21Issued)
                            {
                              CCopasiMessage(CCopasiMessage::WARNING, MCXML + 21);
                              this->mMCXML21Issued = true;
                            }
                        }
                    }

                  if (cg->getObjectRole().find_first_not_of(" \t\r\n") != std::string::npos)
                    {
                      Attributes.add("objectRole", cg->getObjectRole());
                    }

                  startSaveElement("TextGlyph", Attributes);

                  saveBoundingBox(cg->getBoundingBox());

                  endSaveElement("TextGlyph");
                }
            }

          endSaveElement("ListOfTextGlyphs");
        }

      //additional graphical objects
      if (pLayout->getListOfGeneralGlyphs().size() > 0)
        {
          startSaveElement("ListOfAdditionalGraphicalObjects");

          jmax = pLayout->getListOfGeneralGlyphs().size();

          for (j = 0; j < jmax; ++j)
            {
              const CLGeneralGlyph* cg = &pLayout->getListOfGeneralGlyphs()[j];
              Attributes.erase();
              Attributes.add("key", cg->getKey());
              Attributes.add("name", cg->getObjectName());

              if (!cg->getModelObjectKey().empty() && cg->hasValidModelReference())
                {
                  Attributes.add("reference", cg->getModelObjectKey());
                }
              else
                {
                  // we set the model reference to the empty string so that
                  // the warnings message only appears on the first save operation
                  const_cast< CLGeneralGlyph * >(cg)->setModelObjectKey("");

                  //a general glyph does not necessarily have a model reference.
                  //so no warning is issued
                  /*if (!this->mMCXML21Issued)
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCXML + 21);
                      this->mMCXML21Issued = true;
                    }*/
                }

              if (cg->getObjectRole().find_first_not_of(" \t\r\n") != std::string::npos)
                {
                  Attributes.add("objectRole", cg->getObjectRole());
                }

              startSaveElement("AdditionalGraphicalObject", Attributes);

              //if (cg->getCurve().getNumCurveSegments() == 0)
              saveBoundingBox(cg->getBoundingBox());
              //else
              //  saveCurve(cg->getCurve());

              // reference glyphs

              endSaveElement("AdditionalGraphicalObject");
            }

          endSaveElement("ListOfAdditionalGraphicalObjects");
        }

      // save the local render information
      if (pLayout->getListOfLocalRenderInformationObjects().size() > 0)
        {
          saveListOfLocalRenderInformation(pLayout->getListOfLocalRenderInformationObjects());
        }

      endSaveElement("Layout");
    }

  // save the global render information list
  if (mpLayoutList->getListOfGlobalRenderInformationObjects().size() > 0)
    {
      saveListOfGlobalRenderInformation(mpLayoutList->getListOfGlobalRenderInformationObjects());
    }

  endSaveElement("ListOfLayouts");

  return success;
}

bool CCopasiXML::saveGUI()
{
  bool success = true;

  if (!haveGUI()) return success;

  startSaveElement("GUI");

  if (mpGUI->getSliderList() && mpGUI->getSliderList()->size())
    {
      startSaveElement("ListOfSliders");

      const CSlider * pSlider;
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

      size_t i, imax = mpGUI->getSliderList()->size();

      for (i = 0; i < imax; i++)
        {
          pSlider = &mpGUI->getSliderList()->operator[](i);
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

bool CCopasiXML::saveSBMLReference()
{
  // if there is no model, there are no SBML references to save,
  // so no reason to fail saving at this point
  if (!this->mpDataModel) return true;

  if (this->mpDataModel->getSBMLFileName() == "" ||
      mSBMLReference.size() == 0)
    return true;

  CXMLAttributeList Attributes;

  std::string SBMLFile = this->mpDataModel->getSBMLFileName();

  if (!CDirEntry::isRelativePath(SBMLFile) &&
      !CDirEntry::makePathRelative(SBMLFile, mPWD))
    SBMLFile = CDirEntry::fileName(SBMLFile);

  Attributes.add("file", SBMLFile);

  startSaveElement("SBMLReference", Attributes);
  Attributes.erase();
  Attributes.add("SBMLid", "");
  Attributes.add("COPASIkey", "");

  std::map<std::string, std::string>::const_iterator it = mSBMLReference.begin();
  std::map<std::string, std::string>::const_iterator end = mSBMLReference.end();

  for (; it != end; ++it)
    {
      Attributes.setValue(0, (*it).first);
      Attributes.setValue(1, (*it).second);

      saveElement("SBMLMap", Attributes);
    }

  endSaveElement("SBMLReference");

  return true;
}

bool CCopasiXML::buildFunctionList()
{
  bool success = true;

  CDataVectorN< CFunction > * pFunctionList
    = new CDataVectorN< CFunction >;

  std::vector< const CFunction * > FunctionList = CRootContainer::getFunctionList()->getUsedFunctions(this->mpDataModel->getModel());
  *pFunctionList = *reinterpret_cast< std::vector< CFunction * > * >(&FunctionList);

  if (!setFunctionList(pFunctionList)) success = false;

  return success;
}

void CCopasiXML::fixBuild18()
{
  if (mpModel == NULL) return;

  std::string quantityUnit = mpModel->getQuantityUnit();

  if (quantityUnit == "Mol")
    mpModel->setQuantityUnit("mol", CCore::Framework::ParticleNumbers);
  else if (quantityUnit == "mMol")
    mpModel->setQuantityUnit("mmol", CCore::Framework::ParticleNumbers);
  else if (quantityUnit == "\xc2\xb5Mol")
    mpModel->setQuantityUnit("\xc2\xb5mol", CCore::Framework::ParticleNumbers);
  else if (quantityUnit == "nMol")
    mpModel->setQuantityUnit("nmol", CCore::Framework::ParticleNumbers);
  else if (quantityUnit == "pMol")
    mpModel->setQuantityUnit("pmol", CCore::Framework::ParticleNumbers);
  else if (quantityUnit == "fMol")
    mpModel->setQuantityUnit("fmol", CCore::Framework::ParticleNumbers);

  return;
}

void CCopasiXML::fixBuild55()
{
  if (mpTaskList == NULL) return;

  size_t Index = mpTaskList->getIndex("Parameter Estimation");

  if (Index == C_INVALID_INDEX) return;

  CFitTask * pTask = dynamic_cast< CFitTask * >(&mpTaskList->operator[](Index));

  if (pTask == NULL) return;

  pTask->fixBuild55();

  return;
}

void CCopasiXML::fixBuild81()
{
  if (mpTaskList == NULL) return;

  size_t Index = mpTaskList->getIndex("Scan");

  if (Index == C_INVALID_INDEX) return;

  CScanTask * pTask = dynamic_cast< CScanTask * >(&mpTaskList->operator[](Index));

  if (pTask == NULL) return;

  pTask->fixBuild81();

  return;
}

void CCopasiXML::fixBuildBefore104()
{
  if (mpModel == NULL) return;

  if (mpModel->getTimeUnit() == "m")
    mpModel->setTimeUnit("min");
}

void CCopasiXML::fixBuild113()
{
  if (mpModel == NULL) return;

  CDataVector< CReaction >::iterator it = mpModel->getReactions().begin();
  CDataVector< CReaction >::iterator end = mpModel->getReactions().end();

  for (; it != end; ++it)
    {
      if (it->getCompartmentNumber() > 1)
        {
          const CCompartment * pCompartment = NULL;
          std::set< const CCompartment * > Compartments;

          CDataVector < CChemEqElement >::const_iterator itBalance = it->getChemEq().getBalances().begin();
          CDataVector < CChemEqElement >::const_iterator endBalance = it->getChemEq().getBalances().end();

          for (; itBalance != endBalance; ++itBalance)
            {
              if (itBalance->getMetabolite() != NULL &&
                  (pCompartment = itBalance->getMetabolite()->getCompartment()) != NULL)
                {
                  Compartments.insert(pCompartment);
                }
            }

          if (Compartments.size() == 1)
            {
              it->setKineticLawUnitType(CReaction::KineticLawUnit::ConcentrationPerTime);
            }
        }
    }
}

void CCopasiXML::fixBuild171()
{
  // We need to go through all registered object names and sanitize them.
  CRegisteredCommonName::sanitizeObjectNames();
}

/**
 * Saves the list of global render information objects.
 */
void CCopasiXML::saveListOfGlobalRenderInformation(const CDataVector< CLGlobalRenderInformation > & list)
{
  startSaveElement("ListOfGlobalRenderInformation");
  size_t i, iMax = list.size();

  for (i = 0; i < iMax; ++i)
    {
      saveGlobalRenderInformation(list[i]);
    }

  endSaveElement("ListOfGlobalRenderInformation");
}

/**
 * Saves the list of local render information objects.
 */
void CCopasiXML::saveListOfLocalRenderInformation(const CDataVector<CLLocalRenderInformation>& list)
{
  startSaveElement("ListOfRenderInformation");
  size_t i, iMax = list.size();

  for (i = 0; i < iMax; ++i)
    {
      saveLocalRenderInformation(list[i]);
    }

  endSaveElement("ListOfRenderInformation");
}

/**
 * Saves a single global render information object.
 */
void CCopasiXML::saveGlobalRenderInformation(const CLGlobalRenderInformation& renderInfo)
{
  // first we create the attributes that are common to all render information objects
  CXMLAttributeList attributes;
  saveRenderInformationAttributes(renderInfo, attributes);
  startSaveElement("RenderInformation", attributes);
  // now we save the definition that are the same for all render information objects
  saveRenderInformationDefinitionElements(renderInfo);
  // last we save the global styles
  size_t i, iMax = renderInfo.getNumStyles();

  if (iMax > 0)
    {
      startSaveElement("ListOfStyles");

      for (i = 0; i < iMax; ++i)
        {
          saveGlobalStyle(*(dynamic_cast<const CLGlobalStyle*>(renderInfo.getStyle(i))));
        }

      endSaveElement("ListOfStyles");
    }

  endSaveElement("RenderInformation");
}

/**
 * Saves a single local render information object.
 */
void CCopasiXML::saveLocalRenderInformation(const CLLocalRenderInformation& renderInfo)
{
  // first we create the attributes that are common to all render information objects
  CXMLAttributeList attributes;
  saveRenderInformationAttributes(renderInfo, attributes);
  startSaveElement("RenderInformation", attributes);
  // now we save the definition that are the same for all render information objects
  saveRenderInformationDefinitionElements(renderInfo);
  // last we save the global styles
  size_t i, iMax = renderInfo.getNumStyles();

  if (iMax > 0)
    {
      startSaveElement("ListOfStyles");

      for (i = 0; i < iMax; ++i)
        {
          saveLocalStyle(*(dynamic_cast<const CLLocalStyle*>(renderInfo.getStyle(i))));
        }

      endSaveElement("ListOfStyles");
    }

  endSaveElement("RenderInformation");
}

void CCopasiXML::saveRenderInformationAttributes(const CLRenderInformationBase& renderInfo, CXMLAttributeList& attributes)
{
  // save the key
  attributes.add("key", renderInfo.getKey());
  // save the name
  std::string s = renderInfo.getName();
  const char* ws = " \t\n\r";

  if (s.find_first_not_of(ws) != std::string::npos)
    {
      attributes.add("name", s);
    }

  // save the background color
  s = renderInfo.getBackgroundColor();

  if (s.find_first_not_of(ws) != std::string::npos)
    {
      // save the name
      attributes.add("backgroundColor", s);
    }

  // save the reference render information key
  s = renderInfo.getReferenceRenderInformationKey();

  if (s.find_first_not_of(ws) != std::string::npos)
    {
      // save the name
      attributes.add("referenceRenderInformation", s);
    }
}

/**
 * Saves color definitions , gradient definitions and line endings.
 */
void CCopasiXML::saveRenderInformationDefinitionElements(const CLRenderInformationBase& renderInfo)
{
  size_t i, iMax = renderInfo.getNumColorDefinitions();

  if (iMax > 0)
    {
      startSaveElement("ListOfColorDefinitions");

      for (i = 0; i < iMax; ++i)
        {
          saveColorDefinition(*(renderInfo.getColorDefinition(i)));
        }

      endSaveElement("ListOfColorDefinitions");
    }

  iMax = renderInfo.getNumGradientDefinitions();

  if (iMax > 0)
    {
      startSaveElement("ListOfGradientDefinitions");
      const CLGradientBase* pGradient = NULL;

      for (i = 0; i < iMax; ++i)
        {
          pGradient = renderInfo.getGradientDefinition(i);

          if (dynamic_cast<const CLRadialGradient*>(pGradient))
            {
              saveRadialGradient(*static_cast<const CLRadialGradient*>(pGradient));
            }
          else if (dynamic_cast<const CLLinearGradient*>(pGradient))
            {
              saveLinearGradient(*static_cast<const CLLinearGradient*>(pGradient));
            }
        }

      endSaveElement("ListOfGradientDefinitions");
    }

  iMax = renderInfo.getNumLineEndings();

  if (iMax > 0)
    {
      startSaveElement("ListOfLineEndings");

      for (i = 0; i < iMax; ++i)
        {
          saveLineEnding(*(renderInfo.getLineEnding(i)));
        }

      endSaveElement("ListOfLineEndings");
    }
}

/**
 * Save a single color definition element.
 */
void CCopasiXML::saveColorDefinition(const CLColorDefinition& color)
{
  CXMLAttributeList attributes;
  attributes.add("id", color.getId());
  attributes.add("value", color.createValueString());
  saveElement("ColorDefinition", attributes);
}

/**
 * Saves a single linear gradient definition.
 */
void CCopasiXML::saveLinearGradient(const CLLinearGradient& gradient)
{
  CXMLAttributeList attributes;
  // first we create the common attributes
  saveGradientAttributes(gradient, attributes);
  // now we add the attributes specific to the radial gradient
  attributes.add("x1", gradient.getXPoint1().toString());
  attributes.add("y1", gradient.getYPoint1().toString());

  if (gradient.getZPoint1() != CLRelAbsVector(0.0, 0.0))
    {
      attributes.add("z1", gradient.getZPoint1().toString());
    }

  attributes.add("x2", gradient.getXPoint2().toString());
  attributes.add("y2", gradient.getYPoint2().toString());

  if (gradient.getZPoint2() != CLRelAbsVector(0.0, 0.0))
    {
      attributes.add("z2", gradient.getZPoint2().toString());
    }

  startSaveElement("LinearGradient", attributes);
  // save the gradient stops
  saveGradientElements(gradient);
  endSaveElement("LinearGradient");
}

/**
 * Saves a single radial gradient definition.
 */
void CCopasiXML::saveRadialGradient(const CLRadialGradient& gradient)
{
  CXMLAttributeList attributes;
  // first we create the common attributes
  saveGradientAttributes(gradient, attributes);
  // now we add the attributes specific to the radial gradient
  attributes.add("cx", gradient.getCenterX().toString());
  attributes.add("cy", gradient.getCenterY().toString());
  attributes.add("cz", gradient.getCenterZ().toString());
  attributes.add("r", gradient.getRadius().toString());
  attributes.add("fx", gradient.getFocalPointX().toString());
  attributes.add("fy", gradient.getFocalPointY().toString());
  attributes.add("fz", gradient.getFocalPointZ().toString());
  startSaveElement("RadialGradient", attributes);
  // save the gradient stops
  saveGradientElements(gradient);
  endSaveElement("RadialGradient");
}

/**
 * Adds the attributes common to radial and linear gradient.
 */
void CCopasiXML::saveGradientAttributes(const CLGradientBase& gradient, CXMLAttributeList& attributes)
{
  attributes.add("id", gradient.getId());

  switch (gradient.getSpreadMethod())
    {
      case CLGradientBase::REPEAT:
        attributes.add("spreadMethod", "repeat");
        break;

      case CLGradientBase::REFLECT:
        attributes.add("spreadMethod", "reflect");
        break;

      case CLGradientBase::PAD:
      default:
        attributes.add("spreadMethod", "pad");
        break;
    }
}

/**
 * Saves the elements that are common to linear and radial gradients.
 */
void CCopasiXML::saveGradientElements(const CLGradientBase& gradient)
{
  size_t i, iMax = gradient.getNumGradientStops();

  if (iMax > 0)
    {
      for (i = 0; i < iMax; ++i)
        {
          saveGradientStop(*(gradient.getGradientStop(i)));
        }
    }
}

/**
 * Saves a single gradient stop element.
 */
void CCopasiXML::saveGradientStop(const CLGradientStop& stop)
{
  CXMLAttributeList attributes;
  attributes.add("offset", stop.getOffset().toString());
  attributes.add("stop-color", stop.getStopColor());
  saveElement("Stop", attributes);
}

void CCopasiXML::saveLineEnding(const CLLineEnding& lineEnding)
{
  // create the attributes
  CXMLAttributeList attributes;
  attributes.add("id", lineEnding.getId());
  attributes.add("enableRotationalMapping", lineEnding.getIsEnabledRotationalMapping() ? std::string("true") : std::string("false"));
  startSaveElement("LineEnding", attributes);
  // a line ending has a bounding box
  saveBoundingBox(*(lineEnding.getBoundingBox()));
  // and a group element
  assert(lineEnding.getGroup() != NULL);
  saveGroupElement(*lineEnding.getGroup());
  endSaveElement("LineEnding");
}

/**
 * Saves a single local style element.
 */
void CCopasiXML::saveLocalStyle(const CLLocalStyle& style)
{
  // first we create the attributes
  CXMLAttributeList attributes;
  saveStyleAttributes(style, attributes);

  // now we add the attributes that are specific to local styles
  if (style.getNumKeys() > 0)
    {
      attributes.add("keyList", CLStyle::createStringFromSet(style.getKeyList()));
    }

  startSaveElement("Style", attributes);
  saveStyleElements(style);
  endSaveElement("Style");
}

/**
 * Saves a single local style element.
 */
void CCopasiXML::saveGlobalStyle(const CLGlobalStyle& style)
{
  // first we create the attributes
  CXMLAttributeList attributes;
  saveStyleAttributes(style, attributes);
  startSaveElement("Style", attributes);
  saveStyleElements(style);
  endSaveElement("Style");
}

/**
 * Adds the attributes common to both style types.
 */
void CCopasiXML::saveStyleAttributes(const CLStyle& style, CXMLAttributeList& attributes)
{
  attributes.add("key", style.getKey());

  if (style.getNumRoles() > 0)
    {
      attributes.add("roleList", CLStyle::createStringFromSet(style.getRoleList()));
    }

  if (style.getNumTypes() > 0)
    {
      attributes.add("typeList", CLStyle::createStringFromSet(style.getTypeList()));
    }
}

/**
 * Saves the elements common to both style types.
 */
void CCopasiXML::saveStyleElements(const CLStyle& style)
{
  assert(style.getGroup() != NULL);
  saveGroupElement(*(style.getGroup()));
}

/**
 * Saves a group element.
 */
void CCopasiXML::saveGroupElement(const CLGroup& group)
{
  CXMLAttributeList attributes;
  save2DAttributes(group, attributes);
  saveTextAttributes<CLGroup>(group, attributes);
  saveArrowHeadAttributes<CLGroup>(group, attributes);
  startSaveElement("Group", attributes);
  size_t i, iMax = group.getNumElements();

  if (iMax > 0)
    {
      for (i = 0; i < iMax; ++i)
        {
          saveTransformation2D(*dynamic_cast<const CLTransformation2D*>(group.getElement(i)));
        }
    }

  endSaveElement("Group");
}

/**
 * Saves the attributes for a transformation.
 */
void CCopasiXML::saveTransformationAttributes(const CLTransformation2D& transformation, CXMLAttributeList& attributes)
{
  // transformation
  if (!transformation.isIdentityMatrix())
    {
      // check if it is a 2D or a 3D transformation
      if (transformation.is2DTransformation())
        {
          if (transformation.isSetMatrix())
            {
              attributes.add("transform", transformation.get2DTransformationString());
            }
        }
      else
        {
          if (transformation.isSetMatrix())
            {
              attributes.add("transform", transformation.get3DTransformationString());
            }
        }
    }
}

/**
 * Saves the attributes for a 1D element
 */
void CCopasiXML::save1DAttributes(const CLGraphicalPrimitive1D& primitive, CXMLAttributeList& attributes)
{
  // first we go and add the transformation attributes because each 1D element is automatically a transformation element.
  saveTransformationAttributes(primitive, attributes);

  // stroke
  if (primitive.isSetStroke())
    {
      attributes.add("stroke", primitive.getStroke());
    }

  // stroke size
  if (primitive.isSetStrokeWidth())
    {
      std::ostringstream os;
      os << primitive.getStrokeWidth();
      attributes.add("stroke-width", os.str());
    }

  // stroke dash array
  if (primitive.isSetDashArray())
    {
      std::ostringstream os;
      size_t i, iMax = primitive.getDashArray().size();
      os << primitive.getDashArray()[0];

      for (i = 1; i < iMax; ++i)
        {
          os << ", " << primitive.getDashArray()[i];
        }

      attributes.add("stroke-dasharray", os.str());
    }
}

/**
 * Saves the attributes for a 2D element
 */
void CCopasiXML::save2DAttributes(const CLGraphicalPrimitive2D& primitive, CXMLAttributeList& attributes)
{
  // first we go and add the 1D attributes because each 2D element is automatically a 1D element.
  save1DAttributes(primitive, attributes);

  // fill
  if (primitive.isSetFill())
    {
      attributes.add("fill", primitive.getFillColor());
    }

  // fill rule
  if (primitive.isSetFillRule())
    {
      switch (primitive.getFillRule())
        {
          case CLGraphicalPrimitive2D::EVENODD:
            attributes.add("fill-rule", "evenodd");
            break;

          case CLGraphicalPrimitive2D::NONZERO:
          default:
            attributes.add("fill-rule", "nonzero");
            break;
        }
    }
}

/**
 * Saves the attributes for a text element.
 * We make this a template so that we can use it for a group as well as a text element.
 */
template<typename TEXTELEMENT>
void CCopasiXML::saveTextAttributes(const TEXTELEMENT& text, CXMLAttributeList& attributes)
{
  // text size
  if (text.isSetFontSize())
    {
      attributes.add("font-size", text.getFontSize().toString());
    }

  // font family
  if (text.isSetFontFamily())
    {
      attributes.add("font-family", text.getFontFamily());
    }

  // font weight
  if (text.isSetFontWeight())
    {
      switch (text.getFontWeight())
        {
          case CLText::WEIGHT_BOLD:
            attributes.add("font-weight", "bold");
            break;

          default:
            break;
        }
    }

  // font style
  if (text.isSetFontStyle())
    {
      switch (text.getFontStyle())
        {
          case CLText::STYLE_ITALIC:
            attributes.add("font-style", "italic");
            break;

          default:
            break;
        }
    }

  // text anchor
  if (text.isSetTextAnchor())
    {
      switch (text.getTextAnchor())
        {
          case CLText::ANCHOR_MIDDLE:
            attributes.add("text-anchor", "middle");
            break;

          case CLText::ANCHOR_END:
            attributes.add("text-anchor", "end");
            break;

          case CLText::ANCHOR_START:
            attributes.add("text-anchor", "start");
            break;

          default:
            break;
        }
    }

  // vertical text anchor
  if (text.isSetVTextAnchor())
    {
      switch (text.getVTextAnchor())
        {
          case CLText::ANCHOR_MIDDLE:
            attributes.add("vtext-anchor", "middle");
            break;

          case CLText::ANCHOR_BOTTOM:
            attributes.add("vtext-anchor", "bottom");
            break;

          case CLText::ANCHOR_TOP:
            attributes.add("vtext-anchor", "top");
            break;

          default:
            break;
        }
    }
}

/**
 * Saves the startHead and endHead attribute as found in group and curves.
 * We write it as a template so that it can be used on curves and group elements.
 */
template<typename HEADELEMENT>
void CCopasiXML::saveArrowHeadAttributes(const HEADELEMENT& element, CXMLAttributeList& attributes)
{
  // start head
  if (element.isSetStartHead())
    {
      attributes.add("startHead", element.getStartHead());
    }

  // start head
  if (element.isSetEndHead())
    {
      attributes.add("endHead", element.getEndHead());
    }
}

/**
 * Saves a class that is subclasses from Transformation2D.
 * This covers images, curves, rectangles, ellipses, polygons, text elements and groups.
 */
void CCopasiXML::saveTransformation2D(const CLTransformation2D& transformation)
{
  if (dynamic_cast<const CLGraphicalPrimitive1D*>(&transformation))
    {
      if (dynamic_cast<const CLRenderCurve*>(&transformation))
        {
          saveRenderCurveElement(static_cast<const CLRenderCurve&>(transformation));
        }
      else if (dynamic_cast<const CLGraphicalPrimitive2D*>(&transformation))
        {
          if (dynamic_cast<const CLRectangle*>(&transformation))
            {
              saveRectangleElement(static_cast<const CLRectangle&>(transformation));
            }
          else if (dynamic_cast<const CLEllipse*>(&transformation))
            {
              saveEllipseElement(static_cast<const CLEllipse&>(transformation));
            }
          else if (dynamic_cast<const CLPolygon*>(&transformation))
            {
              savePolygonElement(static_cast<const CLPolygon&>(transformation));
            }
          else if (dynamic_cast<const CLGroup*>(&transformation))
            {
              saveGroupElement(static_cast<const CLGroup&>(transformation));
            }
          else
            {
              // we should never end up here.
              assert(false);
            }
        }
      else if (dynamic_cast<const CLText*>(&transformation))
        {
          saveRenderTextElement(static_cast<const CLText&>(transformation));
        }
      else
        {
          // we should never end up here.
          assert(false);
        }
    }
  else if (dynamic_cast<const CLImage*>(&transformation))
    {
      saveImageElement(static_cast<const CLImage&>(transformation));
    }
  else
    {
      // we should never end up here.
      assert(false);
    }
}

/**
 * saves a single image element.
 */
void CCopasiXML::saveImageElement(const CLImage& image)
{
  CXMLAttributeList attributes;
  // first we add the attributes for a transformation
  saveTransformationAttributes(image, attributes);
  // now we add the image specific attributes
  attributes.add("x", image.getX().toString());
  attributes.add("y", image.getY().toString());

  if (image.getZ() != CLRelAbsVector(0.0, 0.0))
    {
      attributes.add("z", image.getZ().toString());
    }

  attributes.add("width", image.getWidth().toString());
  attributes.add("height", image.getHeight().toString());
  attributes.add("href", image.getImageReference());
  saveElement("Image", attributes);
}

/**
 * saves a single rectangle element.
 */
void CCopasiXML::saveRectangleElement(const CLRectangle& rectangle)
{
  CXMLAttributeList attributes;
  // first we add the attributes for a 2D object
  save2DAttributes(rectangle, attributes);
  // now we add the rectangle specific attributes
  attributes.add("x", rectangle.getX().toString());
  attributes.add("y", rectangle.getY().toString());

  if (rectangle.getZ() != CLRelAbsVector(0.0, 0.0))
    {
      attributes.add("z", rectangle.getZ().toString());
    }

  attributes.add("width", rectangle.getWidth().toString());
  attributes.add("height", rectangle.getHeight().toString());

  if (rectangle.getRadiusX() != CLRelAbsVector(0.0, 0.0))
    {
      attributes.add("rx", rectangle.getRadiusX().toString());
    }

  if (rectangle.getRadiusY() != CLRelAbsVector(0.0, 0.0))
    {
      attributes.add("ry", rectangle.getRadiusY().toString());
    }

  saveElement("Rectangle", attributes);
}

/**
 * saves a single ellipse element.
 */
void CCopasiXML::saveEllipseElement(const CLEllipse& ellipse)
{
  CXMLAttributeList attributes;
  // first we add the attributes for a 2D object
  save2DAttributes(ellipse, attributes);
  // now we add the ellipse specific attributes
  attributes.add("cx", ellipse.getCX().toString());
  attributes.add("cy", ellipse.getCY().toString());

  if (ellipse.getCZ() != CLRelAbsVector(0.0, 0.0))
    {
      attributes.add("cz", ellipse.getCZ().toString());
    }

  if (ellipse.getRX() != CLRelAbsVector(0.0, 0.0))
    {
      attributes.add("rx", ellipse.getRX().toString());
    }

  if (ellipse.getRY() != CLRelAbsVector(0.0, 0.0))
    {
      attributes.add("ry", ellipse.getRY().toString());
    }

  saveElement("Ellipse", attributes);
}

/**
 * saves a single text element.
 */
void CCopasiXML::saveRenderTextElement(const CLText& text)
{
  CXMLAttributeList attributes;
  // first we add the attributes for a 1D object
  save1DAttributes(text, attributes);
  // save text attributes
  attributes.add("x", text.getX().toString());
  attributes.add("y", text.getY().toString());

  if (text.getZ() != CLRelAbsVector(0.0, 0.0))
    {
      attributes.add("z", text.getZ().toString());
    }

  // next we add the text specific attributes
  saveTextAttributes<CLText>(text, attributes);
  startSaveElement("Text", attributes);
  saveData(text.getText());
  endSaveElement("Text");
}

/**
 * saves a single image element.
 */
void CCopasiXML::savePolygonElement(const CLPolygon& polygon)
{
  CXMLAttributeList attributes;
  // first we add the attributes for a 2D object
  save2DAttributes(polygon, attributes);
  startSaveElement("Polygon", attributes);
  saveCurveElements(*polygon.getListOfElements());
  endSaveElement("Polygon");
}

/**
 * saves a single image element.
 */
void CCopasiXML::saveRenderCurveElement(const CLRenderCurve& curve)
{
  CXMLAttributeList attributes;
  // first we add the attributes for a 1D object
  save1DAttributes(curve, attributes);
  // next we add the arrow head attributes
  saveArrowHeadAttributes<CLRenderCurve>(curve, attributes);
  startSaveElement("Curve", attributes);
  saveCurveElements(*curve.getListOfCurveElements());
  endSaveElement("Curve");
}

/**
 * saves a vector of curve elements. This can be called from the polygon as well as the curve.
 */
void CCopasiXML::saveCurveElements(const std::vector<CLRenderPoint*>& curveElements)
{
  startSaveElement("ListOfElements");
  size_t i, iMax = curveElements.size();

  for (i = 0; i < iMax; ++i)
    {
      saveRenderPoint(*curveElements[i]);
    }

  endSaveElement("ListOfElements");
}

/**
 * saves a single render point element.
 */
void CCopasiXML::saveRenderPoint(const CLRenderPoint& point)
{
  CXMLAttributeList attributes;
  attributes.add("x", point.x().toString());
  attributes.add("y", point.y().toString());

  if (point.z() != CLRelAbsVector(0.0, 0.0))
    {
      attributes.add("z", point.z().toString());
    }

  const CLRenderCubicBezier* pCB = dynamic_cast<const CLRenderCubicBezier*>(&point);

  if (pCB != NULL)
    {
      attributes.add("basePoint1_x", pCB->basePoint1_X().toString());
      attributes.add("basePoint1_y", pCB->basePoint1_Y().toString());

      if (pCB->basePoint1_Z() != CLRelAbsVector(0.0, 0.0))
        {
          attributes.add("basePoint1_z", pCB->basePoint1_Z().toString());
        }

      attributes.add("basePoint2_x", pCB->basePoint2_X().toString());
      attributes.add("basePoint2_y", pCB->basePoint2_Y().toString());

      if (pCB->basePoint2_Z() != CLRelAbsVector(0.0, 0.0))
        {
          attributes.add("basePoint2_z", pCB->basePoint2_Z().toString());
        }
    }

  saveElement("Element", attributes);
}

bool CCopasiXML::saveUnitDefinitionList()
{
  bool success = true;

  CUnitDefinitionDB * pUnitDefList = CRootContainer::getUnitList();

  if (!pUnitDefList) return success;

  size_t i, imax = pUnitDefList->size();

  if (!imax) return success;

  // in case only the functionDB is exported, there will not be a model
  // and no units being used, so we don't have to export them here
  if (mpModel == NULL) return success;

  CXMLAttributeList Attributes;
  const CUnitDefinition * pUnitDef = NULL;

  startSaveElement("ListOfUnitDefinitions");

  for (i = 0; i < imax; i++)
    {
      pUnitDef = &pUnitDefList->operator[](i);

      // Don't save if the unit is not used in/for a model unit and
      // it's not a user-created unit (i.e. it is a built-in)
      if (mpModel->getUnitSymbolUsage(pUnitDef->getSymbol()).empty() &&
          pUnitDef->isReadOnly()) continue;

      Attributes.erase();
      Attributes.add("key", pUnitDef->getKey());
      Attributes.add("name", pUnitDef->getObjectName());
      Attributes.add("symbol", pUnitDef->getSymbol());

      startSaveElement("UnitDefinition", Attributes);

      saveAnnotation(pUnitDef);

      startSaveElement("Expression");

      saveData(pUnitDef->getExpression());

      endSaveElement("Expression");

      endSaveElement("UnitDefinition");
    }

  endSaveElement("ListOfUnitDefinitions");

  return success;
}
