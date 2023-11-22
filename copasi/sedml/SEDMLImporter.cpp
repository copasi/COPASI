// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * SEDMLImporter.cpp
 * $Rev:               $:  Revision of last commit
 * $Author:            $:  Author of last commit
 * $Date:              $:  Date of last commit
 * $HeadURL:       $
 * $Id:        $
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <limits>
#include <cmath>
#include <algorithm>

#include <sedml/SedTypes.h>
#include <sbml/math/FormulaFormatter.h>

#include "copasi/copasi.h"

#include "copasi/report/CKeyFactory.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CCompartment.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CEvent.h"
#include "copasi/function/CNodeK.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CEvaluationTree.h"
#include "copasi/function/CExpression.h"
#include "copasi/function/CFunctionParameters.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/utilities/CCopasiTree.h"
#include "copasi/utilities/CNodeIterator.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/MIRIAM/CRDFGraphConverter.h"
#include "copasi/compareExpressions/CEvaluationNodeNormalizer.h"
#include "copasi/commandline/CLocaleString.h"
#include "copasi/commandline/COptions.h"

#include "copasi/utilities/CProcessReport.h"
#include "copasi/utilities/CTaskFactory.h"
#include "copasi/commandline/CConfigurationFile.h"

#include "copasi/utilities/CCopasiMessage.h"

//TODO SEDML
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryProblem.h"
#include "copasi/sbml/SBMLImporter.h"
#include "copasi/utilities/CDirEntry.h"
#include "copasi/utilities/CCopasiException.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/plot/COutputDefinitionVector.h"
#include "copasi/plot/CPlotSpecification.h"

#include "copasi/report/CReportDefinitionVector.h"

#include <copasi/steadystate/CSteadyStateTask.h>
#include <copasi/scan/CScanTask.h>

#include "SEDMLImporter.h"
#include "SEDMLUtils.h"

// static
C_FLOAT64 SEDMLImporter::round(const C_FLOAT64 & x)
{
  return x < 0.0 ? -floor(-x + 0.5) : floor(x + 0.5);
}

void SEDMLImporter::setImportHandler(CProcessReport * pProcessReport)
{
  mpProcessReport = pProcessReport;
}

const CProcessReport * SEDMLImporter::getProcessReport() const
{
  return mpProcessReport;
}

void SEDMLImporter::setSEDMLDocument(SedDocument * pDocument)
{
  mpSEDMLDocument = pDocument;

  if (!mpSEDMLDocument)
    return;

  // sort elements according to their order
  mpSEDMLDocument->sortOrderedObjects();

  mOriginalLevel = mLevel = mpSEDMLDocument->getLevel();
  mVersion = mpSEDMLDocument->getVersion();
}

SedDocument * SEDMLImporter::getSEDMLDocument()
{
  return mpSEDMLDocument;
}

void SEDMLImporter::clearDocument()
{
  pdelete(mpSEDMLDocument);
}

void SEDMLImporter::setDataModel(CDataModel * pDataModel)
{
  mpDataModel = pDataModel;
}

CDataModel * SEDMLImporter::getDataModel()
{
  return mpDataModel;
}

void SEDMLImporter::setCopasiModel(CModel * pModel)
{
  mpCopasiModel = pModel;
}

void SEDMLImporter::clearCallBack()
{
  setImportHandler(NULL);
}

const std::string SEDMLImporter::getArchiveFileName()
{
  return mArchiveFileName;
}

/**
 * Creates and returns a COPASI CTrajectoryTask from the SEDML simulation
 * given as argument.
 */
void SEDMLImporter::updateCopasiTaskForSimulation(
  SedSimulation * sedmlsim,
  CDataVectorN< CCopasiTask > * pTaskList)
{
  if (sedmlsim == NULL)
    return;

  if (pTaskList == NULL)
    pTaskList = mContent.pTaskList;

  switch (sedmlsim->getTypeCode())
    {
      case SEDML_SIMULATION_UNIFORMTIMECOURSE:
      {
        if (pTaskList->getIndex("Time-Course") == C_INVALID_INDEX)
          CTaskFactory::create(CTaskEnum::Task::timeCourse, pTaskList);

        CTrajectoryTask * tTask = static_cast< CTrajectoryTask * >(&pTaskList->operator[]("Time-Course"));
        tTask->setScheduled(true);
        tTask->setMathContainer(&mpCopasiModel->getMathContainer());

        CTrajectoryProblem * tProblem = static_cast< CTrajectoryProblem * >(tTask->getProblem());
        SedUniformTimeCourse * tc = static_cast< SedUniformTimeCourse * >(sedmlsim);
        double outputStartTime = tc->getOutputStartTime();
        double outputEndTime = tc->getOutputEndTime();
        int numberOfPoints = tc->getNumberOfPoints();
        tProblem->setOutputStartTime(outputStartTime);

        // set the models initial time to the initial time of the simulation
        if (mpCopasiModel)
          {
            mpCopasiModel->setInitialTime(tc->getInitialTime());
            mpCopasiModel->updateInitialValues(mpCopasiModel->getInitialValueReference());
          }

        tProblem->setDuration(outputEndTime - outputStartTime);
        tProblem->setStepNumber(numberOfPoints);

        // TODO read kisao terms
        if (tc->isSetAlgorithm())
          {
            const SedAlgorithm * alg = tc->getAlgorithm();

            applyAlgorithm(tTask, alg);
          }

        break;
      }

      case SEDML_SIMULATION_ONESTEP:
      {
        if (pTaskList->getIndex("Time-Course") == C_INVALID_INDEX)
          CTaskFactory::create(CTaskEnum::Task::timeCourse, pTaskList);

        CTrajectoryTask * tTask = static_cast< CTrajectoryTask * >(&pTaskList->operator[]("Time-Course"));
        tTask->setScheduled(true);
        tTask->setMathContainer(&mpCopasiModel->getMathContainer());

        CTrajectoryProblem * tProblem = static_cast< CTrajectoryProblem * >(tTask->getProblem());
        SedOneStep * step = static_cast< SedOneStep * >(sedmlsim);
        tProblem->setOutputStartTime(0);
        tProblem->setDuration(step->getStep());
        tProblem->setStepNumber(1);

        // TODO read kisao terms

        break;
      }

      case SEDML_SIMULATION_STEADYSTATE:
      {
        if (pTaskList->getIndex("Steady-State") == C_INVALID_INDEX)
          CTaskFactory::create(CTaskEnum::Task::steadyState, pTaskList);

        // nothing to be done for this one
        CSteadyStateTask * tTask = static_cast< CSteadyStateTask * >(&pTaskList->operator[]("Steady-State"));
        tTask->setScheduled(true);
        tTask->setMathContainer(&mpCopasiModel->getMathContainer());

        // TODO read kisao terms
        //CCopasiProblem* tProblem = static_cast<CCopasiProblem*>(tTask->getProblem());
        //SedSteadyState* tc = static_cast<SedSteadyState*>(sedmlsim);

        break;
      }

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, "SEDMLImporter Error: encountered unknown simulation.");
        break;
    }
}

CTaskEnum::Method getMethodType(const std::string & kisaoId)
{
  static std::map< std::string, CTaskEnum::Method > methodMap =
  {
    {"KISAO:0000560", CTaskEnum::Method::deterministic},
    {"KISAO:0000304", CTaskEnum::Method::RADAU5},
    {"KISAO:0000029", CTaskEnum::Method::directMethod},
    {"KISAO:0000027", CTaskEnum::Method::stochastic},
    {"KISAO:0000039", CTaskEnum::Method::tauLeap},
    {"KISAO:0000048", CTaskEnum::Method::adaptiveSA},
    {"KISAO:0000561", CTaskEnum::Method::hybrid},
    {"KISAO:0000562", CTaskEnum::Method::hybridLSODA},
    {"KISAO:0000563", CTaskEnum::Method::hybridODE45},
    {"KISAO:0000566", CTaskEnum::Method::stochasticRunkeKuttaRI5},
  };

  auto it = methodMap.find(kisaoId);

  if (it != methodMap.end())
    {
      return it->second;
    }

  // old behavior for stochastic
  if (kisaoId == SEDML_KISAO_STOCHASTIC)
    return CTaskEnum::Method::stochastic;

  // warn and default to LSODA
  CCopasiMessage(CCopasiMessage::WARNING,
                 "The requested Algorithm %s is not directly supported by COPASI, defaulting to LSODA.",
                 kisaoId.c_str());

  return CTaskEnum::Method::deterministic;
}

void SEDMLImporter::applyAlgorithm(CTrajectoryTask * tTask, const SedAlgorithm * alg)
{
  if (tTask == NULL || alg == NULL || !alg->isSetKisaoID())
    return;

  // set method type
  tTask->setMethodType(getMethodType(alg->getKisaoID()));

  CCopasiMethod * pMethod = tTask->getMethod();

  // apply parameters
  for (unsigned int i = 0; i < alg->getNumAlgorithmParameters(); ++i)
    {
      auto * param = alg->getAlgorithmParameter(i);

      if (param == NULL || !param->isSetKisaoID() || !param->isSetValue())
        continue;

      auto it = SEDMLUtils::PARAMETER_KISAO_MAP.find(param->getKisaoID());

      if (it == SEDMLUtils::PARAMETER_KISAO_MAP.end())
        continue;

      CCopasiParameter * pParameter = pMethod->getParameter(it->second);

      if (pParameter == NULL)
        continue;

      std::string paramValue = param->getValue();
      std::stringstream str(paramValue);

      switch (pParameter->getType())
        {
          case CCopasiParameter::Type::DOUBLE:
          case CCopasiParameter::Type::UDOUBLE:
          {
            C_FLOAT64 value;
            str >> value;
            pParameter->setValue< C_FLOAT64 >(value);
            break;
          }

          case CCopasiParameter::Type::INT:
          {
            C_INT32 value;
            str >> value;
            pParameter->setValue< C_INT32 >(value);
            break;
          }

          case CCopasiParameter::Type::UINT:
          {
            unsigned C_INT32 value;
            str >> value;
            pParameter->setValue< unsigned C_INT32 >(value);
            break;
          }

          case CCopasiParameter::Type::BOOL:
          {
            pParameter->setValue< bool >(
              paramValue == "1" || paramValue == "true" || paramValue == "yes");
            break;
          }

          case CCopasiParameter::Type::STRING:
          case CCopasiParameter::Type::CN:
            pParameter->setValue< std::string >(paramValue);
            break;

          default:
            break;
        }
    }
}

bool isTC(const SedTask * task)
{
  if (task == NULL || task->getSedDocument() == NULL)
    return false;

  const SedDocument * doc = task->getSedDocument();

  if (task->isSetSimulationReference())
    {
      const SedSimulation * sim = doc->getSimulation(task->getSimulationReference());

      if (sim != NULL && (sim->getTypeCode() == SEDML_SIMULATION_UNIFORMTIMECOURSE))
        return true;
    }

  return false;
}

bool isScan(const SedTask * task)
{

  if (task == NULL || task->getSedDocument() == NULL)
    return false;

  const SedDocument * doc = task->getSedDocument();

  if (task->isSetSimulationReference())
    {
      const SedSimulation * sim = doc->getSimulation(task->getSimulationReference());

      if (sim != NULL && (sim->getTypeCode() == SEDML_SIMULATION_STEADYSTATE || sim->getTypeCode() == SEDML_SIMULATION_ONESTEP || sim->getTypeCode() == SEDML_SIMULATION_UNIFORMTIMECOURSE))
        return true;
    }

  return false;
}

bool isScan(const SedRepeatedTask * task)
{
  if (task == NULL || task->getSedDocument() == NULL)
    return false;

  const SedDocument * doc = task->getSedDocument();

  for (unsigned int i = 0; i < task->getNumSubTasks(); ++i)
    {
      const SedSubTask * subTask = task->getSubTask(i);
      const SedTask * t = dynamic_cast< const SedTask * >(doc->getTask(subTask->getTask()));

      if (isScan(t))
        return true;
    }

  return false;
}

void SEDMLImporter::importOutputs()
{
  COutputDefinitionVector * pLotList = mContent.pPlotDefinitionList;
  CModel * pModel = mpCopasiModel;
  SedDocument * pSEDMLDocument = mpSEDMLDocument;

  if (pLotList == NULL || pModel == NULL || pSEDMLDocument == NULL)
    return;

  unsigned int i, numOutput = pSEDMLDocument->getNumOutputs();

  std::map< const CDataObject *, SBase * > & copasiMap = pModel->getObjectDataModel()->getCopasi2SBMLMap();

  CReportDefinitionVector * pReports = mpDataModel->getReportDefinitionList();

  for (i = 0; i < numOutput; ++i)
    {
      SedOutput * current = pSEDMLDocument->getOutput(i);

      if (mpOptions != NULL && mpOptions->ignoreOutput(current->getId()))
        continue;

      switch (current->getTypeCode())
        {
          case SEDML_OUTPUT_REPORT:
          {
            importReport(dynamic_cast< SedReport * >(current));
            break;
          }

          case SEDML_OUTPUT_PLOT2D: //get the curves data
          {
            SedPlot2D * p = static_cast< SedPlot2D * >(current);
            std::string name = current->isSetName() ? current->getName() : current->getId();
            CPlotSpecification * pPl = pLotList->createPlotSpec(
                                         name, CPlotItem::plot2d);

            if (p->isSetXAxis())
              pPl->setLogX(p->getXAxis()->getType() == SEDML_AXISTYPE_LOG10);

            if (p->isSetYAxis())
              pPl->setLogY(p->getYAxis()->getType() == SEDML_AXISTYPE_LOG10);

            int count = 0;

            while (pPl == NULL)
              {
                // creation fails on duplicated name!
                pPl = pLotList->createPlotSpec(
                        SEDMLUtils::getNextId(name + " ", ++count), CPlotItem::plot2d);
              }

            bool logX = false;
            bool logY = false;

            for (unsigned int ic = 0; ic < p->getNumCurves(); ++ic)
              {
                auto * pCurve = p->getCurve(ic);
                addCurveToCopasiPlot(pCurve, pPl);
              }

            break;
          }

          case SEDML_OUTPUT_PLOT3D:
          {
            SedPlot3D * p = static_cast< SedPlot3D * >(current);
            std::string name = current->isSetName() ? current->getName() : current->getId();
            CPlotSpecification * pPl = pLotList->createPlotSpec(
                                         name, CPlotItem::plot2d);

            if (p->isSetXAxis())
              pPl->setLogX(p->getXAxis()->getType() == SEDML_AXISTYPE_LOG10);

            if (p->isSetYAxis())
              pPl->setLogY(p->getYAxis()->getType() == SEDML_AXISTYPE_LOG10);

            int count = 0;

            while (pPl == NULL)
              {
                // creation fails on duplicated name!
                pPl = pLotList->createPlotSpec(
                        SEDMLUtils::getNextId(name + " ", ++count), CPlotItem::plot2d);
              }

            bool logX = false;
            bool logY = false;

            for (unsigned int ic = 0; ic < p->getNumSurfaces(); ++ic)
              {
                auto * pCurve = p->getSurface(ic);
                addSurfaceToCopasiPlot(pCurve, pPl);
              }

            break;
          }

          default:
            CCopasiMessage(CCopasiMessage::WARNING, "SEDMLImporter Error: No support for this plot: %s", SedTypeCode_toString(current->getTypeCode()));
            break;
        }
    }
}

void SEDMLImporter::addCurveToCopasiPlot(
  LIBSEDML_CPP_NAMESPACE_QUALIFIER SedAbstractCurve * pCurve,
  CPlotSpecification * pPl)
{
  if (!mpSEDMLDocument || !mpCopasiModel)
    return;

  switch (pCurve->getTypeCode())
    {
      case SEDML_OUTPUT_CURVE:
      {

        SedCurve * curve = dynamic_cast< SedCurve * >(pCurve);

        if (!curve)
          return;

        std::string xDataReference = curve->getXDataReference();
        std::string yDataReference = curve->getYDataReference();

        const SedDataGenerator * xGenerator = mpSEDMLDocument->getDataGenerator(xDataReference);
        const SedDataGenerator * yGenerator = mpSEDMLDocument->getDataGenerator(yDataReference);

        //create the curves
        const CDataObject * tmpX = SEDMLUtils::resolveDatagenerator(mpCopasiModel, xGenerator);
        const CDataObject * tmpY = SEDMLUtils::resolveDatagenerator(mpCopasiModel, yGenerator);

        if (tmpX != NULL && tmpY != NULL)
          {
            std::string itemTitle;

            if (curve->isSetName())
              itemTitle = curve->getName();
            else if (yGenerator != NULL && yGenerator->isSetName())
              itemTitle = yGenerator->getName();
            else
              itemTitle = tmpY->getObjectDisplayName();

            // actually we can't have more than one plot item with the same name
            // so lets add a couple of blanks
            int count = 0;

            while (pPl->hasItem(itemTitle))
              itemTitle += std::string(" ") + std::to_string(++count);

            CPlotItem * plItem = pPl->createItem(itemTitle, CPlotItem::curve2d);
            plItem->setValue("Line width", 2.0);
            plItem->addChannel(tmpX->getCN());
            plItem->addChannel(tmpY->getCN());

            applyStyleToCopasiItem(mpSEDMLDocument->getStyle(curve->getStyle()), plItem);

            if (curve->isSetLogX() && curve->getLogX())
              pPl->setLogX(true);

            if (curve->isSetLogY() && curve->getLogY())
              pPl->setLogY(true);
          }

        break;
      }

      case SEDML_SHADEDAREA:
      {
        SedShadedArea * curve = dynamic_cast< SedShadedArea * >(pCurve);

        if (!curve)
          return;

        std::string xDataReference = curve->getXDataReference();
        std::string yDataReference = curve->getYDataReferenceFrom();
        std::string zDataReference = curve->getYDataReferenceTo();

        const SedDataGenerator * xGenerator = mpSEDMLDocument->getDataGenerator(xDataReference);
        const SedDataGenerator * yGenerator = mpSEDMLDocument->getDataGenerator(yDataReference);
        const SedDataGenerator * zGenerator = mpSEDMLDocument->getDataGenerator(zDataReference);

        //create the curves
        const CDataObject * tmpX = SEDMLUtils::resolveDatagenerator(mpCopasiModel, xGenerator);
        const CDataObject * tmpY = SEDMLUtils::resolveDatagenerator(mpCopasiModel, yGenerator);
        const CDataObject * tmpZ = SEDMLUtils::resolveDatagenerator(mpCopasiModel, zGenerator);

        if (tmpX != NULL && tmpY != NULL && tmpZ != NULL)
          {
            std::string itemTitle;

            if (curve->isSetName())
              itemTitle = curve->getName();
            else if (yGenerator != NULL && yGenerator->isSetName())
              itemTitle = yGenerator->getName();
            else
              itemTitle = tmpY->getObjectDisplayName();

            // actually we can't have more than one plot item with the same name
            // so lets add a couple of blanks
            int count = 0;

            while (pPl->hasItem(itemTitle))
              itemTitle += std::string(" ") + std::to_string(++count);

            CPlotItem * plItem = pPl->createItem(itemTitle, CPlotItem::bandedGraph);
            plItem->setValue("Line width", 2.0);
            plItem->addChannel(tmpX->getCN());
            plItem->addChannel(tmpY->getCN());
            plItem->addChannel(tmpZ->getCN());

            applyStyleToCopasiItem(mpSEDMLDocument->getStyle(curve->getStyle()), plItem);

            if (curve->isSetLogX() && curve->getLogX())
              pPl->setLogX(true);
          }

        break;
      }

      default:
        CCopasiMessage(CCopasiMessage::WARNING, "SEDMLImporter Error: No support for this curve: %s", SedTypeCode_toString(pCurve->getTypeCode()));
        break;
    }
}

void SEDMLImporter::addSurfaceToCopasiPlot(
  LIBSEDML_CPP_NAMESPACE_QUALIFIER SedSurface * pSurface,
  CPlotSpecification * pPlot)
{
  if (!pSurface)
    return;

  switch (pSurface->getType())
    {
      case SEDML_SURFACETYPE_CONTOUR:
      case SEDML_SURFACETYPE_HEATMAP:
      {
        std::string xDataReference = pSurface->getXDataReference();
        std::string yDataReference = pSurface->getYDataReference();
        std::string zDataReference = pSurface->getZDataReference();

        const SedDataGenerator * xGenerator = mpSEDMLDocument->getDataGenerator(xDataReference);
        const SedDataGenerator * yGenerator = mpSEDMLDocument->getDataGenerator(yDataReference);
        const SedDataGenerator * zGenerator = mpSEDMLDocument->getDataGenerator(zDataReference);

        //create the curves
        const CDataObject * tmpX = SEDMLUtils::resolveDatagenerator(mpCopasiModel, xGenerator);
        const CDataObject * tmpY = SEDMLUtils::resolveDatagenerator(mpCopasiModel, yGenerator);
        const CDataObject * tmpZ = SEDMLUtils::resolveDatagenerator(mpCopasiModel, zGenerator);

        if (tmpX != NULL && tmpY != NULL && tmpZ != NULL)
          {
            std::string itemTitle;

            if (pSurface->isSetName())
              itemTitle = pSurface->getName();
            else if (yGenerator != NULL && yGenerator->isSetName())
              itemTitle = yGenerator->getName();
            else
              itemTitle = tmpY->getObjectDisplayName();

            // actually we can't have more than one plot item with the same name
            // so lets add a couple of blanks
            int count = 0;

            while (pPlot->hasItem(itemTitle))
              itemTitle += std::string(" ") + std::to_string(++count);

            CPlotItem * plItem = pPlot->createItem(itemTitle, CPlotItem::spectogram);
            plItem->setValue("Line width", 2.0);
            plItem->addChannel(tmpX->getCN());
            plItem->addChannel(tmpY->getCN());
            plItem->addChannel(tmpZ->getCN());

            //assertParameter("maxZ", CCopasiParameter::Type::STRING, std::string(""));
            plItem->setValue< bool >("logZ", pSurface->getLogZ());

            if (pSurface->getType() == SEDML_SURFACETYPE_CONTOUR)
              plItem->setValue< std::string >("contours", "10");

            applyStyleToCopasiItem(mpSEDMLDocument->getStyle(pSurface->getStyle()), plItem);

            if (pSurface->isSetLogX() && pSurface->getLogX())
              pPlot->setLogX(true);

            if (pSurface->isSetLogY() && pSurface->getLogY())
              pPlot->setLogY(true);
          }

        break;
      }

      default:
        CCopasiMessage(CCopasiMessage::WARNING, "SEDMLImporter Error: No support for this surface: %s", SedTypeCode_toString(pSurface->getTypeCode()));
        break;
    }
}

void SEDMLImporter::applyStyleToCopasiItem(
  LIBSEDML_CPP_NAMESPACE_QUALIFIER SedStyle * pStyle,
  CPlotItem * plItem)
{
  if (!pStyle)
    return;

  // apply base styling first
  applyStyleToCopasiItem(mpSEDMLDocument->getStyle(pStyle->getBaseStyle()), plItem);

  // apply line styles
  auto * line = pStyle->getLineStyle();

  bool hasLine = line && line->getType() != SEDML_LINETYPE_NONE;

  if (line)
    {
      if (line->isSetColor())
        {
          auto color = SEDMLUtils::rgbaToArgb(line->getColor());
          plItem->setValue< std::string >("Color", color);
        }

      if (line->isSetThickness())
        {
          plItem->setValue< C_FLOAT64 >("Line width", line->getThickness());
        }

      if (line->isSetType())
        {
          plItem->setValue< unsigned C_INT32 >(
            "Line subtype",
            SEDMLUtils::lineTypeFromSed(line->getType()));
        }

      if (hasLine)
        plItem->setValue< unsigned C_INT32 >("Line type", (int) CPlotItem::LineType::Lines);
    }

  // apply markers
  auto * marker = pStyle->getMarkerStyle();

  if (marker)
    {
      if (marker->isSetType() && marker->getType() != SEDML_MARKERTYPE_NONE)
        {
          auto type = SEDMLUtils::symbolFromSed(marker->getType());
          plItem->setValue< unsigned C_INT32 >(
            "Symbol subtype",
            SEDMLUtils::symbolFromSed(type));

          if (hasLine)
            plItem->setValue< unsigned C_INT32 >("Line type", (int) CPlotItem::LineType::LinesAndSymbols);
          else
            plItem->setValue< unsigned C_INT32 >("Line type", (int) CPlotItem::LineType::Symbols);
        }
    }

  // apply fill
  auto * fill = pStyle->getFillStyle();

  if (fill)
    {
      if (fill->isSetColor())
        {
          auto color = SEDMLUtils::rgbaToArgb(fill->getColor());
          plItem->setValue< std::string >("Color", color);

          plItem->assertParameter("alpha", CCopasiParameter::Type::INT,
                                  64);
          plItem->setValue("alpha", SEDMLUtils::getAlphaFromRgba(fill->getColor()));
        }
    }
}

void SEDMLImporter::importReport(
  LIBSEDML_CPP_NAMESPACE_QUALIFIER SedReport * report)
{
  if (!report)
    return;

  std::string name = report->isSetName() ? report->getName() : report->getId();
  CReportDefinition * def = new CReportDefinition(name);
  int count = 0;

  // creation fails on duplicated name!
  while (def == NULL)
    {
      def = new CReportDefinition(SEDMLUtils::getNextId(name + " ", ++count));
    }

  def->setComment("Import from SED-ML");
  def->setIsTable(false);
  def->setSeparator(", ");

  std::vector< CRegisteredCommonName > * pHeader = def->getHeaderAddr();
  std::vector< CRegisteredCommonName > * pBody = def->getBodyAddr();

  bool isTimeCourse = false;
  bool isScanTask = false;

  for (unsigned int i = 0; i < report->getNumDataSets(); ++i)
    {
      SedDataSet * ds = report->getDataSet(i);
      const SedDataGenerator * generator = mpSEDMLDocument->getDataGenerator(ds->getDataReference());
      const CDataObject * tmp = SEDMLUtils::resolveDatagenerator(mpCopasiModel, generator);

      if (generator == NULL || tmp == NULL)
        continue;

      std::string title = ds->isSetLabel() ? ds->getLabel() : generator->isSetName() ? generator->getName()
                          : ds->getId();

      pHeader->push_back(CDataString(title).getCN());
      pHeader->push_back(def->getSeparator().getCN());

      pBody->push_back(tmp->getCN());
      pBody->push_back(def->getSeparator().getCN());

      if (!isTimeCourse && !isScanTask)
        for (unsigned int j = 0; j < generator->getNumVariables(); ++j)
          {
            const auto * t = mpSEDMLDocument->getTask(generator->getVariable(j)->getTaskReference());

            if (t == NULL)
              continue;

            isScanTask = t->getTypeCode() == SEDML_TASK_REPEATEDTASK && isScan((const SedRepeatedTask *) t);
            isTimeCourse = isTC(dynamic_cast< const SedTask * >(t));
          }
    }

  // assign report to scan task
  if (isScanTask)
    {
      mReportMap[def] = std::make_pair("Scan",
                                       mpOptions != NULL && !mpOptions->getReportFile().empty() ? mpOptions->getReportFile() :
                                       "Scan.txt"
                                      );
    }

  // assign report to Timecourse task
  if (isTimeCourse)
    {
      mReportMap[def] = std::make_pair(
                          "Time-Course",
                          mpOptions != NULL && !mpOptions->getReportFile().empty() ? mpOptions->getReportFile() :
                          "Time-Course.txt");
    }
}

/**
 * Function reads an SEDML file with libsedml and converts it to a Copasi CModel
 */
CModel * SEDMLImporter::readSEDML(std::string filename,
                                  CDataModel * pDataModel,
                                  const SedmlImportOptions * pOptions)
{
  // convert filename to the locale encoding
  std::ifstream file(CLocaleString::fromUtf8(filename).c_str());

  if (!file)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSEDML + 5, filename.c_str());
    }

  std::ostringstream stringStream;
  char c;

  while (file.get(c))
    {
      stringStream << c;
    }

  file.clear();
  file.close();

  pDataModel->setSEDMLFileName(filename);

  return parseSEDML(stringStream.str(), pDataModel, pOptions);
}
/**
 * Function parses an SEDML document with libsedml and converts it to a COPASI CModel
 * object which is returned. Deletion of the returned pointer is up to the
 * caller.
 */
CModel *
SEDMLImporter::parseSEDML(const std::string & sedmlDocumentText,
                          CDataModel * pDataModel,
                          const SedmlImportOptions * pOptions)
{
  mReportMap.clear();
  mUsedSEDMLIdsPopulated = false;

  mpDataModel = pDataModel;
  assert(mpDataModel != NULL);

  mpCopasiModel = NULL;

  mpOptions = pOptions;

  SedReader reader;

  mImportStep = 0;

  if (mpProcessReport != NULL)
    {
      mpProcessReport->setName("Importing SED-ML file...");
      mTotalSteps = 11;
      mhImportStep = mpProcessReport->addItem("Step", mImportStep,
                                              &mTotalSteps);
    }

  unsigned C_INT32 step = 0, totalSteps = 0;
  size_t hStep = C_INVALID_INDEX;

  if (mpProcessReport != NULL)
    {
      step = 0;
      totalSteps = 1;
      hStep = mpProcessReport->addItem("Reading SED-ML file...", step,
                                       &totalSteps);
    }

  auto * pSEDMLDocument = reader.readSedMLFromString(sedmlDocumentText);

  assert(pSEDMLDocument != NULL);

  if (mpProcessReport != NULL)
    mpProcessReport->finishItem(hStep);

  if (mpProcessReport != NULL)
    {
      step = 0;
      totalSteps = 1;
      hStep = mpProcessReport->addItem("Checking consistency...", step,
                                       &totalSteps);
    }

  if (mpProcessReport != NULL)
    mpProcessReport->finishItem(hStep);

  bool fatal = false;
  unsigned int i, iMax = pSEDMLDocument->getNumErrors();

  for (i = 0; (i < iMax) && (!fatal); ++i)
    {
      const SedError * pSEDMLError = pSEDMLDocument->getError(i);

      CCopasiMessage::Type messageType = CCopasiMessage::RAW;

      switch (pSEDMLError->getSeverity())
        {

          case LIBSEDML_SEV_WARNING:

            // if issued as warning, this message is to be disregarded,
            // it was a bug in earlier versions of libSEDML
#if LIBSEDML_VERSION < 1
            if (pSEDMLError->getErrorId() == SedInvalidNamespaceOnSed)
              continue;

#endif

            if (mIgnoredSEDMLMessages.find(pSEDMLError->getErrorId())
                != mIgnoredSEDMLMessages.end())
              {
                messageType = CCopasiMessage::WARNING_FILTERED;
              }
            else
              {
                messageType = CCopasiMessage::WARNING;
              }

            CCopasiMessage(messageType, MCSEDML + 6, "WARNING",
                           pSEDMLError->getErrorId(), pSEDMLError->getLine(),
                           pSEDMLError->getColumn(),
                           pSEDMLError->getMessage().c_str());
            break;

          case LIBSEDML_SEV_ERROR:

            if (mIgnoredSEDMLMessages.find(pSEDMLError->getErrorId())
                != mIgnoredSEDMLMessages.end())
              {
                messageType = CCopasiMessage::ERROR_FILTERED;
              }

            CCopasiMessage(messageType, MCSEDML + 6, "ERROR",
                           pSEDMLError->getErrorId(), pSEDMLError->getLine(),
                           pSEDMLError->getColumn(),
                           pSEDMLError->getMessage().c_str());
            break;

          case LIBSEDML_SEV_FATAL:

            // treat unknown as fatal
          default:

            if (pSEDMLError->getErrorId() == 10804)
              {
                // this error indicates a problem with a notes element
                // although libsedml flags this as fatal, we would still
                // like to read the model
                CCopasiMessage(messageType, MCSEDML + 6, "ERROR",
                               pSEDMLError->getErrorId(), pSEDMLError->getLine(),
                               pSEDMLError->getColumn(),
                               pSEDMLError->getMessage().c_str());
              }
            else
              {
                fatal = true;
              }

            break;
        }
    }

  if (fatal)
    {
      if (mpProcessReport != NULL)
        mpProcessReport->finishItem(mhImportStep);

      const XMLError * pSEDMLError = pSEDMLDocument->getError(fatal);
      std::stringstream str;
      str << "SED-ML (2): SED-ML error (line: "
          << pSEDMLError->getLine()
          << "', column: '"
          << pSEDMLError->getColumn()
          << "'): '"
          << pSEDMLError->getMessage()
          << "'.";

      pdelete(pSEDMLDocument);

      // this will throw
      CCopasiMessage Message(CCopasiMessage::EXCEPTION, str.str().c_str());

      // this will not be reached
      return NULL;
    }

  if (pSEDMLDocument->getListOfModels() == NULL)
    {
      CCopasiMessage Message(CCopasiMessage::ERROR, MCSEDML + 2);

      if (mpProcessReport != NULL)
        mpProcessReport->finishItem(mhImportStep);

      return NULL;
    }

  // initialize data:
  initializeContent();

  setSEDMLDocument(pSEDMLDocument);

  // merge subtasks if needed
  mergeNestedSubtasks();

  if (pOptions == NULL || pOptions->skipModelImport() == false)
    {
      if (pOptions != NULL && !pOptions->getModelId().empty())
        importModel(pOptions->getModelId());
      else
        importFirstSBMLModel();
    }
  else
    {
      mpCopasiModel = pDataModel->getModel();
    }

  if (pOptions != NULL && !pOptions->getTaskId().empty())
    importTask(mpSEDMLDocument->getTask(pOptions->getTaskId()), false);
  else
    importTasks();

  importOutputs();

  assignReportDefinitions();

  if (mpProcessReport != NULL)
    mpProcessReport->finishItem(mhImportStep);

  return mpCopasiModel;
}

void SEDMLImporter::initializeContent()
{
  mContent.mCopasi2SBMLMap.clear();
  mContent.mCopasi2SEDMLMap.clear();
  mContent.pTaskList = new CDataVectorN< CCopasiTask >("TaskList", NO_PARENT);
  mContent.pReportDefinitionList = new CReportDefinitionVector("ReportDefinitions", NO_PARENT);
  mContent.pPlotDefinitionList = new COutputDefinitionVector("OutputDefinitions", NO_PARENT);
}

void SEDMLImporter::updateContent(CDataModel::CContent & data, CDataModel & dm)
{
  data.pModel = mpCopasiModel;

  if (data.pModel)
    dm.add(data.pModel, true);

  data.pListOfLayouts = mContent.pListOfLayouts;
  data.pPlotDefinitionList = mContent.pPlotDefinitionList;

  if (data.pPlotDefinitionList)
    dm.add(data.pPlotDefinitionList, true);

  data.pReportDefinitionList = mContent.pReportDefinitionList;

  if (data.pReportDefinitionList)
    dm.add(data.pReportDefinitionList, true);

  data.pTaskList = mContent.pTaskList;

  if (data.pTaskList)
    dm.add(data.pTaskList, true);

  data.pCurrentSBMLDocument = mContent.pCurrentSBMLDocument;
  data.mCopasi2SBMLMap = mContent.mCopasi2SBMLMap;

  data.pCurrentSEDMLDocument = mpSEDMLDocument;
  data.mCopasi2SEDMLMap = mContent.mCopasi2SEDMLMap;
  data.mContentType = CDataModel::ContentType::SEDML;
}

void SEDMLImporter::importTasks(CDataVectorN< CCopasiTask > * pTaskList)
{

  if (mpSEDMLDocument == NULL)
    return;

  if (pTaskList == NULL)
    pTaskList = mContent.pTaskList;

  for (unsigned int i = 0; i < mpSEDMLDocument->getNumTasks(); ++i)
    {
      auto * task = mpSEDMLDocument->getTask(i);

      importTask(task, pTaskList);
    }
}

void SEDMLImporter::assignReportDefinitions(CDataVectorN< CCopasiTask > * pTaskList)
{

  if (pTaskList == NULL)
    pTaskList = mContent.pTaskList;

  if (pTaskList->empty())
    return;

  auto it = mReportMap.begin();

  for (; it != mReportMap.end(); ++it)
    {
      // skip if the task is not in the task list
      if (pTaskList->getIndex(it->second.first) == C_INVALID_INDEX)
        continue;

      CReport * report = &pTaskList->operator[](it->second.first).getReport();
      report->setReportDefinition(it->first);
      report->setTarget(it->second.second);
      report->setConfirmOverwrite(false);
      report->setAppend(false);

      if (mContent.pReportDefinitionList)
        mContent.pReportDefinitionList->add(it->first, true);
    }
}

void SEDMLImporter::importTask(
  SedAbstractTask * task,
  bool importModel,
  CDataVectorN< CCopasiTask > * pTaskList)
{
  if (task == NULL)
    return;

  if (mpSEDMLDocument == NULL)
    return;

  if (pTaskList == NULL)
    pTaskList = mContent.pTaskList;

  switch (task->getTypeCode())
    {
      case SEDML_TASK:
      {
        auto * current = static_cast< SedTask * >(task);

        // skip tasks for models we did not import
        if (current->isSetModelReference() && current->getModelReference() != this->mImportedModel)
          return;

        SedSimulation * sedmlsim =
          mpSEDMLDocument->getSimulation(current->getSimulationReference());
        updateCopasiTaskForSimulation(sedmlsim);
        break;
      }

      case SEDML_TASK_REPEATEDTASK:
      {
        SedRepeatedTask * repeat = static_cast< SedRepeatedTask * >(task);
        SedRange * range = repeat->getRange(repeat->getRangeId());

        if (range != NULL && range->getTypeCode() == SEDML_RANGE_FUNCTIONALRANGE)
          {
            // try to replace simple functional range
            range = convertSimpleFunctionalRange(dynamic_cast< SedFunctionalRange * >(range), repeat);
          }

        if (range != NULL && range->getTypeCode() != SEDML_RANGE_UNIFORMRANGE && range->getTypeCode() != SEDML_RANGE_VECTORRANGE)
          {
            CCopasiMessage(CCopasiMessage::WARNING, "This version of COPASI only supports uniform ranges and value ranges.");
            return;
          }

        SedUniformRange * urange = dynamic_cast< SedUniformRange * >(range);
        SedVectorRange * vrange = dynamic_cast< SedVectorRange * >(range);

        if (pTaskList->getIndex("Scan") == C_INVALID_INDEX)
          CTaskFactory::create(CTaskEnum::Task::scan, pTaskList);

        CScanTask * tTask = static_cast< CScanTask * >(&pTaskList->operator[]("Scan"));
        tTask->setScheduled(true);
        tTask->setMathContainer(NULL);

        CScanProblem * pProblem = static_cast< CScanProblem * >(tTask->getProblem());
        // in case there are existing scan items, these need to be removed
        pProblem->clearScanItems();

        if (urange != NULL && repeat->getNumTaskChanges() == 0)
          {
            pProblem->addScanItem(CScanProblem::SCAN_REPEAT, urange->getNumberOfPoints());
          }
        else
          {
            for (unsigned int j = 0; j < repeat->getNumTaskChanges(); ++j)
              {
                SedSetValue * sv = repeat->getTaskChange(j);

                if (sv->isSetRange())
                  {
                    range = repeat->getRange(sv->getRange());
                    urange = dynamic_cast< SedUniformRange * >(range);
                    vrange = dynamic_cast< SedVectorRange * >(range);

                    auto * frange = dynamic_cast< SedFunctionalRange * >(range);

                    // try to replace simple functional ranges
                    if (frange)
                      vrange = convertSimpleFunctionalRange(frange, repeat);
                  }

                if (SBML_formulaToString(sv->getMath()) != sv->getRange())
                  {
                    CCopasiMessage(CCopasiMessage::WARNING,
                                   "This version of COPASI only supports setValue elements that apply range values.");
                  }

                std::string target = sv->getTarget();
                const CDataObject * obj = SEDMLUtils::resolveXPath(mpCopasiModel, target, true);

                if (obj == NULL)
                  {
                    CCopasiMessage(CCopasiMessage::WARNING, "This version of COPASI only supports modifications of initial values.");
                    continue;
                  }

                int numPoints = 0;

                if (vrange != NULL)
                  numPoints = vrange->getNumValues();
                else if (urange != NULL)
                  numPoints = urange->getNumberOfPoints();

                CCopasiParameterGroup * group = pProblem->addScanItem(CScanProblem::SCAN_LINEAR, numPoints, obj);

                if (urange != NULL)
                  {
                    group->setValue< C_FLOAT64 >("Minimum", urange->getStart());
                    group->setValue< C_FLOAT64 >("Maximum", urange->getEnd());
                    group->setValue< bool >("Use Values", false);
                    group->setValue< bool >("log", (!urange->isSetType() || urange->getType().empty() || urange->getType() == "linear") ? false : true);
                  }

                if (vrange != NULL)
                  {
                    group->setValue< bool >("Use Values", true);
                    std::stringstream str;
                    std::vector< double > vals = vrange->getValues();

for (double val : vals)
                      str << val << " ";

                    group->setValue< std::string >("Values", str.str());
                  }
              }
          }

        if (repeat->getNumSubTasks() != 1)
          {
            CCopasiMessage(CCopasiMessage::WARNING, "This version of COPASI only supports repeatedTasks with one subtask.");
            return;
          }

        pProblem->setContinueFromCurrentState(!repeat->getResetModel());

        SedSubTask * subTask = repeat->getSubTask(0);

        if (!subTask->isSetTask())
          {
            CCopasiMessage(CCopasiMessage::WARNING, "This version of COPASI only supports repeatedTasks with one subtask that has a valid task reference.");
            return;
          }

        SedTask * actualSubTask = dynamic_cast< SedTask * >(mpSEDMLDocument->getTask(subTask->getTask()));

        if (actualSubTask == NULL || !actualSubTask->isSetSimulationReference())
          {
            CCopasiMessage(CCopasiMessage::WARNING, "This version of COPASI only supports repeatedTasks with one subtask that itself is a task with simulation reference.");
            return;
          }

        int code = mpSEDMLDocument->getSimulation(actualSubTask->getSimulationReference())->getTypeCode();

        if (code == SEDML_SIMULATION_STEADYSTATE)
          {
            pProblem->setSubtask(CTaskEnum::Task::steadyState);
            pProblem->setOutputInSubtask(false);
          }
        else if (code == SEDML_SIMULATION_ONESTEP || code == SEDML_SIMULATION_UNIFORMTIMECOURSE)
          {
            pProblem->setSubtask(CTaskEnum::Task::timeCourse);
          }

        break;
      }

      default:
      {
        const char * name = SedTypeCode_toString(task->getTypeCode());
        CCopasiMessage(CCopasiMessage::WARNING,
                       "Encountered unsupported Task type '%s'. This task cannot be imported in COPASI",
                       name != NULL ? name : "unknown");
      }
    }
}

void SEDMLImporter::mergeNestedSubtasks()
{
  if (!mpSEDMLDocument)
    return;

  bool keepRunning = true;

  while (keepRunning)
    {
      keepRunning = false;

      for (unsigned int i = 0; i < mpSEDMLDocument->getNumTasks(); ++i)
        {
          auto * task = dynamic_cast< SedRepeatedTask * >(mpSEDMLDocument->getTask(i));

          if (task == NULL)
            continue;

          if (task->getNumSubTasks() != 1)
            continue; // can't handle these in any way

          std::string subTaskId = task->getSubTask(0)->getTask();
          auto * subTask = dynamic_cast< SedRepeatedTask * >(mpSEDMLDocument->getTask(subTaskId));

          if (subTask == NULL)
            continue; // not a nested subtask, so nothing to be done here

          // ok so we have a nested repeated task, so move all things from sub task here
          auto * subTaskRanges = subTask->getListOfRanges();

          while (subTaskRanges->size() > 0)
            {
              task->getListOfRanges()->appendAndOwn(subTaskRanges->remove(0));
            }

          // changes
          auto * subTaskChanges = subTask->getListOfTaskChanges();

          while (subTaskChanges->size() > 0)
            {
              task->getListOfTaskChanges()->appendAndOwn(subTaskChanges->remove(0));
            }

          // finally set subTaskId to the one from the subTask and repeat
          task->getSubTask(0)->setTask(subTask->getSubTask(0)->getTask());

          // and delete the subTask
          mpSEDMLDocument->removeTask(subTaskId);
          keepRunning = true;
          break;
        }
    }
}

SedVectorRange *
SEDMLImporter::convertSimpleFunctionalRange(SedFunctionalRange * frange, SedRepeatedTask * repeat)
{
  if (frange && frange->getNumVariables() == 0)
    {
      auto * insideRange = repeat->getRange(frange->getRange());
      auto * insideVRange = dynamic_cast< SedVectorRange * >(insideRange);

      if (insideVRange)
        {
          // remove old range
          repeat->removeRange(frange->getId());

          // it is a simple range and can be replaced by another range.
          auto * newRange = repeat->createVectorRange();
          auto & oldValues = insideVRange->getValues();
          std::vector< double > newValues;
          std::map< std::string, double > knownValues;

          for (unsigned int k = 0; k < frange->getNumParameters(); ++k)
            {
              auto * p = frange->getParameter(k);
              knownValues[p->getId()] = p->getValue();
            }

for (auto value : oldValues)
            {
              knownValues[insideVRange->getId()] = value;
              newValues.push_back(SBMLTransforms::evaluateASTNode(frange->getMath(), knownValues));
            }

          newRange->setValues(newValues);
          newRange->setId(frange->getId());

          pdelete(frange);
          return newRange;
        }
    }

  CCopasiMessage(CCopasiMessage::WARNING,
                 "The repeated task uses a functional range, that cannot yet be supported.");
  return NULL;
}

bool applyValueToParameterSet(CModelParameterSet & set, CDataObject * obj, double newValue)
{
  const CModelParameter * pParameter = set.getModelParameter(obj->getCN());

  if (pParameter != NULL)
    {
      const_cast< CModelParameter * >(pParameter)->setValue(newValue, CCore::Framework::Concentration);
      return true;
    }

  return false;
}

bool applyAttributeChange(CModel * pCopasiModel, CModelParameterSet & set, const std::string & target, const std::string & newValue)
{
  CDataObject * obj = const_cast< CDataObject * >(SEDMLUtils::resolveXPath(pCopasiModel, target, true));

  if (obj == NULL)
    return false;

  // convert the string to double
  std::stringstream str;
  str << newValue;
  double result;
  str >> result;

  // set the value
  applyValueToParameterSet(set, obj->getObjectParent(), result);
  return true;
}

CModel * SEDMLImporter::importFirstSBMLModel()
{
  if (mpSEDMLDocument == NULL)
    return NULL;

  unsigned int numModels = mpSEDMLDocument->getNumModels();

  if (numModels < 1)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSEDML + 2);
    }

  if (numModels > 1)
    {
      CCopasiMessage(CCopasiMessage::WARNING, "COPASI currently only supports the import of SED-ML models, that involve one model only. Only the simulations for the first model will be imported");
    }

  return importModel(mpSEDMLDocument->getModel(0)->getId());
}

CModel * SEDMLImporter::importModel(const std::string & modelId)
{
  SedModel * sedmlModel = mpSEDMLDocument->getModel(modelId);

  if (sedmlModel == NULL)
    CCopasiMessage(CCopasiMessage::EXCEPTION,
                   "No model with id: %s ", modelId.c_str());

  // need to also allow for the specific urns like
  // urn:sedml:language:sbml.level-3.version-1
  if (sedmlModel->getLanguage().find("urn:sedml:language:sbml") == std::string::npos)
    CCopasiMessage(CCopasiMessage::EXCEPTION,
                   "Sorry currently, only SBML models are supported.");

  std::string modelSource = sedmlModel->getSource();

  if (modelSource.find("urn:") == 0 || modelSource.find("http://") == 0 || modelSource.find("https://") == 0)
    CCopasiMessage(CCopasiMessage::EXCEPTION,
                   "Currently, only local files are supported. Please resolve the remote source '%s' first before importing the SED-ML document.",
                   modelSource.c_str()
                  );


  SedModel * referencedModel = mpSEDMLDocument->getModel(modelSource);

  if (!referencedModel && modelSource[0] == '#')
    referencedModel = mpSEDMLDocument->getModel(modelSource.substr(1));

  if ((sedmlModel->getListOfChanges()->size()) > 0)
    CCopasiMessage(CCopasiMessage::WARNING, "Currently there is only limited support for "
                   "changing model entities. Only value changes are imported into the model.");

  if (referencedModel != NULL)
    {
      // need to import other model first
      importModel(referencedModel->getId());
    }
  else
    {
      auto FileName = resolveModelFile(modelSource);

      if (!CDirEntry::exist(FileName))
        {
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCSEDML + 4,
                         FileName.c_str());
        }

      //set the SBML file name for later use
      mpDataModel->setSBMLFileName(FileName);

      SBMLImporter importer;
      // Right now we always import the COPASI MIRIAM annotation if it is there.
      // Later this will be settable by the user in the preferences dialog
      importer.setImportCOPASIMIRIAM(true);
      importer.setImportHandler(mpProcessReport);

      mpCopasiModel = NULL;

      try
        {
          mpCopasiModel = importer.readSBML(FileName,
                                            mContent.pCurrentSBMLDocument,
                                            mContent.mCopasi2SBMLMap, mContent.pListOfLayouts, mpDataModel);
        }

      catch (CCopasiException & except)
        {
          importer.restoreFunctionDB();
          importer.deleteCopasiModel();

          throw except;
        }

      if (mpCopasiModel == NULL)
        {
          importer.restoreFunctionDB();
          importer.deleteCopasiModel();
          return NULL;
        }
    }

  mImportedModel = modelId;

  // apply possible changes to the model
  if (sedmlModel != NULL && sedmlModel->getNumChanges() > 0)
    {
      CModelParameterSet & set = mpCopasiModel->getActiveModelParameterSet();
      bool valueChanged = false;

      for (unsigned int i = 0; i < sedmlModel->getNumChanges(); ++i)
        {
          SedChangeAttribute * change = dynamic_cast< SedChangeAttribute * >(sedmlModel->getChange(i));

          if (change == NULL)
            continue;

          const std::string & target = change->getTarget();
          const std::string & newValue = change->getNewValue();

          if (!applyAttributeChange(mpCopasiModel, set, target, newValue))
            {
              CCopasiMessage(CCopasiMessage::WARNING, "Could not apply change for target: '%s'", target.c_str());
            }
          else
            {
              valueChanged = true;
            }
        }

      if (valueChanged)
        {
          set.updateModel();
        }
    }

  return mpCopasiModel;
}

std::string SEDMLImporter::resolveModelFile(const std::string & modelSource)
{
  std::string FileName;

  if (CDirEntry::exist(modelSource))
    FileName = modelSource;
  else if (!mpDataModel->getSEDMLFileName().empty())
    FileName = CDirEntry::dirName(mpDataModel->getSEDMLFileName()) + CDirEntry::Separator + modelSource;
  else if (!mpDataModel->getReferenceDirectory().empty())
    FileName = mpDataModel->getReferenceDirectory() + CDirEntry::Separator + modelSource;
  else
    FileName = modelSource;

  return FileName;
}

/**
 * Constructor that initializes speciesMap and the FunctionDB object
 */
SEDMLImporter::SEDMLImporter()
  : mIgnoredSEDMLMessages()
  , mIncompleteModel(false)
  , mLevel(0)
  , mOriginalLevel(0)
  , mVersion(0)
  , mpDataModel(NULL)
  , mpCopasiModel(NULL)
  , mpSEDMLDocument(NULL)
  , mpProcessReport(NULL)
  , mImportStep(0)
  , mhImportStep(C_INVALID_INDEX)
  , mTotalSteps(0)
  , mUsedSEDMLIds()
  , mUsedSEDMLIdsPopulated(false)
  , mImportedModel()
  , mReportMap()
{

  this->mIgnoredSEDMLMessages.insert(10501);
}

void SEDMLImporter::restoreFunctionDB()
{
}

/**
 * Destructor that does nothing.
 */
SEDMLImporter::~SEDMLImporter()
{
  mReportMap.clear();
}

void SEDMLImporter::deleteCopasiModel()
{
  pdelete(mpCopasiModel);
}
