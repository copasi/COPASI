// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <cmath>

#include "copasi.h"

#include "DataModelGUI.h"
#include "DataModel.txt.h"
#include "CQThread.h"
#include "qtUtilities.h"
#include "utilities/CVector.h"
#include "CProgressBar.h"
#include "listviews.h"
#include "CQMessageBox.h"
#include "CQBrowserPaneDM.h"

#include "function/CFunctionDB.h"
#include "model/CModel.h"
#include "model/CModelValue.h"
#include "model/CMetabNameInterface.h"
#include "plotUI/COutputHandlerPlot.h"
#include "plot/COutputDefinitionVector.h"
#include "report/CReportDefinitionVector.h"
#include "scan/CScanTask.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CMCATask.h"
#include "lna/CLNATask.h"
#include "trajectory/CTrajectoryTask.h"
#include "tssanalysis/CTSSATask.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "utilities/CCopasiException.h"
#include "commandline/CConfigurationFile.h"
#include "utilities/CCopasiTree.h"

//#include "model/CModelMerging.h"
#include "model/CModelExpansion.h"

#define USE_LAYOUT 1
#define USE_RENDER 1

#include <sbml/SBMLDocument.h>
#include <sbml/packages/render/sbml/RenderPoint.h>
#include <sbml/packages/render/sbml/Text.h>
#include <sbml/packages/layout/sbml/LineSegment.h>

#include "layout/CLayout.h"
#include "layout/CListOfLayouts.h"
#include "layout/SBMLDocumentLoader.h"
#include "sbml/CCellDesignerImporter.h"
#include "sbml/SBMLUtils.h"

#if LIBSBML_VERSION >= 50400
#include <sbml/packages/layout/extension/LayoutModelPlugin.h>
#endif

//*****************************************************************************

DataModelGUI::DataModelGUI(QObject * parent):
  QObject(parent),
  mpApp(NULL),
  mOutputHandlerPlot(),
  mListViews(),
  mFramework(0),
  mUpdateVector(),
  mChangedObjects(),
  mpThread(NULL),
  mpProgressBar(NULL),
  mSuccess(false),
  mSBMLImportString(),
  mpSBMLExportString(NULL),
  mFileName(),
  mOverWrite(false),
  mSBMLLevel(2),
  mSBMLVersion(4),
  mSBMLExportIncomplete(true),
  mSBMLExportCOPASIMIRIAM(true),
  mExportFormat()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  (*CCopasiRootContainer::getDatamodelList())[0]->addInterface(&mOutputHandlerPlot);

  //mpMathModel = NULL;
  //mMathModelUpdateScheduled = false;
}

DataModelGUI::~DataModelGUI()
{}

//************************************************************

void DataModelGUI::linkDataModelToGUI()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  std::set< ListViews * >::iterator it = mListViews.begin();
  std::set< ListViews * >::iterator end = mListViews.end();

  for (; it != end; ++it)
    {
      (*it)->setDataModel(this);
    }

  pDataModel->deleteOldData();
}

//*****************************************************************

//*****************************************************************
#ifdef WITH_MERGEMODEL

void DataModelGUI::addModel(const std::string & fileName)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;

  mpThread = new CQThread(this, &DataModelGUI::addModelRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(addModelFinished()));
  mpThread->start();
}

void DataModelGUI::addModelRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mSuccess = CCopasiRootContainer::addDatamodel()->loadModel(mFileName, mpProgressBar, false);
    }

  catch (...)
    {
      mSuccess = false;
    }

  CModel *pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();
  CModel *pMergeModel = (*CCopasiRootContainer::getDatamodelList())[1]->getModel();

  //CModelAdd add(pModel, mModel);
  //add.simpleCall();

  if (mSuccess && pModel && pMergeModel)
    {
      CModelExpansion expand(pModel);
      (*CCopasiRootContainer::getDatamodelList())[0]->mLastAddedObjects = expand.copyCompleteModel(pMergeModel);
    }
}

void DataModelGUI::addModelFinished()
{
  if (mSuccess)
    {
      //notify(ListViews::MODEL, ListViews::CHANGE, "");

      CCopasiRootContainer::getConfiguration()->getRecentFiles().addFile(mFileName);
      //linkDataModelToGUI();
    }

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(addModelFinished()));

  threadFinished();
}

#endif

bool DataModelGUI::createModel()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);

  if (!(*CCopasiRootContainer::getDatamodelList())[0]->newModel(NULL, false)) return false;

  mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList());

  linkDataModelToGUI();
  return true;
}

void DataModelGUI::loadModel(const std::string & fileName)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;

  mpThread = new CQThread(this, &DataModelGUI::loadModelRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(loadModelFinished()));
  mpThread->start();
}

void DataModelGUI::loadModelRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mSuccess = (*CCopasiRootContainer::getDatamodelList())[0]->loadModel(mFileName, mpProgressBar, false);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::loadModelFinished()
{
  if (mSuccess)
    {
      CCopasiRootContainer::getConfiguration()->getRecentFiles().addFile(mFileName);

      mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList());
      linkDataModelToGUI();
    }

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(loadModelFinished()));

  threadFinished();
}

void DataModelGUI::saveModel(const std::string & fileName, bool overwriteFile)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;
  mOverWrite = overwriteFile;

  mpThread = new CQThread(this, &DataModelGUI::saveModelRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(saveModelFinished()));
  mpThread->start();
}

void DataModelGUI::saveModelRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mSuccess = (*CCopasiRootContainer::getDatamodelList())[0]->saveModel(mFileName, mpProgressBar, mOverWrite);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::saveModelFinished()
{
  if (mSuccess)
    CCopasiRootContainer::getConfiguration()->getRecentFiles().addFile(mFileName);

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(saveModelFinished()));

  threadFinished();
}

void DataModelGUI::importSBMLFromString(const std::string & sbmlDocumentText)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mSBMLImportString = sbmlDocumentText;

  mpThread = new CQThread(this, &DataModelGUI::importSBMLFromStringRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(importSBMLFromStringFinished()));
  mpThread->start();
}

void DataModelGUI::importSBMLFromStringRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mSuccess = (*CCopasiRootContainer::getDatamodelList())[0]->importSBMLFromString(mSBMLImportString, mpProgressBar, false);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::importSBMLFromStringFinished()
{
  mSBMLImportString = "";

  if (mSuccess)
    {
      // can't run this in a separate thread because it uses GUI routines
      // TODO maybe put the main part of this routine in a separate thread after
      // TODO asking the user
      this->importCellDesigner();
      mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList());
      linkDataModelToGUI();
    }

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(importSBMLFromStringFinished()));

  threadFinished();
}

void DataModelGUI::importSBML(const std::string & fileName)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;
  mpThread = new CQThread(this, &DataModelGUI::importSBMLRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(importSBMLFinished()));
  mpThread->start();
}

void DataModelGUI::importSBMLRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mSuccess = (*CCopasiRootContainer::getDatamodelList())[0]->importSBML(mFileName, mpProgressBar, false);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::importSBMLFinished()
{
  if (mSuccess)
    {
      this->importCellDesigner();
      CCopasiRootContainer::getConfiguration()->getRecentSBMLFiles().addFile(mFileName);

      mOutputHandlerPlot.setOutputDefinitionVector((*CCopasiRootContainer::getDatamodelList())[0]->getPlotDefinitionList());
      linkDataModelToGUI();
    }

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(importSBMLFinished()));

  threadFinished();
}

void DataModelGUI::exportSBMLToString(std::string & sbmlDocumentText)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mpSBMLExportString = & sbmlDocumentText;

  mpThread = new CQThread(this, &DataModelGUI::exportSBMLToStringRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(exportSBMLToStringFinished()));
  mpThread->start();
}

void DataModelGUI::exportSBMLToStringRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      *mpSBMLExportString = (*CCopasiRootContainer::getDatamodelList())[0]->exportSBMLToString(mpProgressBar, 2, 4);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::exportSBMLToStringFinished()
{
  disconnect(mpThread, SIGNAL(finished()), this, SLOT(exportSBMLToStringFinished()));

  threadFinished();
}

void DataModelGUI::threadFinished()
{
  if (mpThread != NULL)
    {
      mpThread->deleteLater();
      mpThread = NULL;
    }

  if (mpProgressBar != NULL)
    {
      mpProgressBar->finish();
      mpProgressBar->deleteLater();
      mpProgressBar = NULL;
    }

  emit finished(mSuccess);
}

void DataModelGUI::exportSBML(const std::string & fileName, bool overwriteFile, int sbmlLevel, int sbmlVersion, bool exportIncomplete, bool exportCOPASIMIRIAM)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;
  mOverWrite = overwriteFile;
  mSBMLLevel = sbmlLevel;
  mSBMLVersion = sbmlVersion;
  mSBMLExportIncomplete = exportIncomplete;
  mSBMLExportCOPASIMIRIAM = exportCOPASIMIRIAM;

  mpThread = new CQThread(this, &DataModelGUI::exportSBMLRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(exportSBMLFinished()));
  mpThread->start();
}

void DataModelGUI::exportSBMLRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mSuccess = (*CCopasiRootContainer::getDatamodelList())[0]->exportSBML(mFileName, mOverWrite, mSBMLLevel, mSBMLVersion, mSBMLExportIncomplete, mSBMLExportCOPASIMIRIAM, mpProgressBar);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::exportSBMLFinished()
{
  if (mSuccess)
    CCopasiRootContainer::getConfiguration()->getRecentSBMLFiles().addFile(mFileName);

  disconnect(mpThread, SIGNAL(finished()), this, SLOT(exportSBMLFinished()));

  threadFinished();
}

void DataModelGUI::exportMathModel(const std::string & fileName, const std::string & filter, bool overwriteFile)
{
  mpProgressBar = CProgressBar::create();

  mSuccess = true;
  mFileName = fileName;
  mOverWrite = overwriteFile;
  mExportFormat = filter;

  mpThread = new CQThread(this, &DataModelGUI::exportMathModelRun);
  connect(mpThread, SIGNAL(finished()), this, SLOT(exportMathModelFinished()));
  mpThread->start();
}

void DataModelGUI::exportMathModelRun()
{
  try
    {
      assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
      mSuccess = (*CCopasiRootContainer::getDatamodelList())[0]->exportMathModel(mFileName, mpProgressBar, mExportFormat, mOverWrite);
    }

  catch (...)
    {
      mSuccess = false;
    }
}

void DataModelGUI::exportMathModelFinished()
{
  disconnect(mpThread, SIGNAL(finished()), this, SLOT(exportMathModelFinished()));

  threadFinished();
}

bool DataModelGUI::updateMIRIAM(CMIRIAMResources & miriamResources)
{
  bool success = true;
  CProgressBar* pProgressBar = CProgressBar::create();
  //try
  //{
  success = miriamResources.updateMIRIAMResources(pProgressBar);
  //}
  //catch (...)
  //{
  //success = false;
  //}

  pdelete(pProgressBar);
  return success;
}

//************** QApplication ***********************************************

//************Model-View Architecture*****************************************

bool DataModelGUI::notify(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  // The GUI is inactive whenever a progress bar exist. We wait with updates
  // until then.
  if (mpProgressBar != NULL) return false;

  // update all initial value
  if (action != ListViews::RENAME)
    refreshInitialValues();

  emit notifyView(objectType, action, key);

  return true;
}

void DataModelGUI::registerListView(ListViews * pListView)
{
  pListView->setDataModel(this);
  mListViews.insert(pListView);
}

void DataModelGUI::deregisterListView(ListViews * pListView)
{
  pListView->setDataModel(NULL);
  mListViews.erase(pListView);
}

void DataModelGUI::buildChangedObjects()
{
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();
  pModel->compileIfNecessary(NULL);

  mChangedObjects.clear();

  CModelEntity ** ppEntity = pModel->getStateTemplate().getEntities();
  CModelEntity ** ppEntityEnd = pModel->getStateTemplate().endFixed();

  CMetab * pMetab;
  std::set< const CCopasiObject * > Objects;

  // The objects which are changed are all initial values of of all model entities including
  // fixed and unused once. Additionally, all kinetic parameters are possibly changed.
  // This is basically all the parameters in the parameter overview whose value is editable.

  // :TODO: Theoretically, it is possible that also task parameters influence the initial
  // state of a model but that is currently not handled.

  for (; ppEntity != ppEntityEnd; ++ppEntity)
    {
      // If we have an initial expression we have no initial values
      if ((*ppEntity)->getInitialExpression() != "" ||
          (*ppEntity)->getStatus() == CModelEntity::ASSIGNMENT)
        continue;

      // Metabolites have two initial values
      if (mFramework == 0 &&
          (pMetab = dynamic_cast< CMetab * >(*ppEntity)) != NULL)
        {
          // The concentration is assumed to be fix accept when this would lead to circular dependencies,
          // for the parent's compartment's initial volume.
          if (pMetab->isInitialConcentrationChangeAllowed() &&
              !isnan(pMetab->getInitialConcentration()))
            mChangedObjects.insert(pMetab->getInitialConcentrationReference());
          else
            mChangedObjects.insert(pMetab->getInitialValueReference());
        }
      else
        mChangedObjects.insert((*ppEntity)->getInitialValueReference());
    }

  // The reaction parameters
  CCopasiVector< CReaction >::const_iterator itReaction = pModel->getReactions().begin();
  CCopasiVector< CReaction >::const_iterator endReaction = pModel->getReactions().end();
  size_t i, imax;

  for (; itReaction != endReaction; ++itReaction)
    {
      const CCopasiParameterGroup & Group = (*itReaction)->getParameters();

      for (i = 0, imax = Group.size(); i < imax; i++)
        mChangedObjects.insert(static_cast< const CCopasiObject * >(Group.getParameter(i)->getObject(CCopasiObjectName("Reference=Value"))));
    }

  // Fix for Issue 1170: We need to add elements of the stoichiometry, reduced stoichiometry,
  // and link matrices.
  const CArrayAnnotation * pMatrix = NULL;
  pMatrix = dynamic_cast<const CArrayAnnotation *>(pModel->getObject(std::string("Array=Stoichiometry(ann)")));

  if (pMatrix != NULL)
    pMatrix->appendElementReferences(mChangedObjects);

  pMatrix = dynamic_cast<const CArrayAnnotation *>(pModel->getObject(std::string("Array=Reduced stoichiometry(ann)")));

  if (pMatrix != NULL)
    pMatrix->appendElementReferences(mChangedObjects);

  pMatrix = dynamic_cast<const CArrayAnnotation *>(pModel->getObject(std::string("Array=Link matrix(ann)")));

  if (pMatrix != NULL)
    pMatrix->appendElementReferences(mChangedObjects);

  try
    {
      mUpdateVector = pModel->buildInitialRefreshSequence(mChangedObjects);
    }

  catch (...)
    {
      QString Message = "Error while updating the initial values!\n\n";
      Message += FROM_UTF8(CCopasiMessage::getLastMessage().getText());

      CQMessageBox::critical(NULL, QString("COPASI Error"), Message,
                             QMessageBox::Ok, QMessageBox::Ok);
      CCopasiMessage::clearDeque();

      mUpdateVector.clear();
      return;
    }
}

void DataModelGUI::refreshInitialValues()
{
  buildChangedObjects();

  std::vector< Refresh * >::iterator it = mUpdateVector.begin();
  std::vector< Refresh * >::iterator end = mUpdateVector.end();

  for (; it != end; ++it)
    (**it)();

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CModel * pModel = (*CCopasiRootContainer::getDatamodelList())[0]->getModel();

  pModel->refreshActiveParameterSet();
}

void DataModelGUI::setFramework(int framework)
{
  mFramework = framework;

  std::set< ListViews * >::iterator it = mListViews.begin();
  std::set< ListViews * >::iterator end = mListViews.end();

  for (; it != end; ++it)
    {
      (*it)->setFramework(mFramework);
    }
}

void DataModelGUI::updateMIRIAMResourceContents()
{
  std::set< ListViews * >::iterator it = mListViews.begin();
  std::set< ListViews * >::iterator end = mListViews.end();

  for (; it != end; ++it)
    {
      (*it)->updateMIRIAMResourceContents();
    }
}

void DataModelGUI::commit()
{
  std::set< ListViews * >::iterator it = mListViews.begin();
  std::set< ListViews * >::iterator end = mListViews.end();

  for (; it != end; ++it)
    {
      (*it)->commit();
    }
}

/**
 * This method tries to import CellDesigner annotations.
 */
void DataModelGUI::importCellDesigner()
{
  // add code to check for CellDesigner annotations
  // ask the user if the annotations should be imported
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);

  if (pDataModel != NULL)
    {
      SBMLDocument* pSBMLDocument = pDataModel->getCurrentSBMLDocument();

      if (pSBMLDocument != NULL &&
          pSBMLDocument->getModel() != NULL &&
          pSBMLDocument->getModel()->getAnnotation() != NULL)
        {
          // check for the CellDesigner namespace
          std::pair<bool, std::string> foundNamespace = CCellDesignerImporter::findCellDesignerNamespace(pSBMLDocument);

          if (foundNamespace.first == true)
            {
              const XMLNode* pAnno = CCellDesignerImporter::findCellDesignerAnnotation(pSBMLDocument, pSBMLDocument->getModel()->getAnnotation());

              // first we check if there are supported cell designer annotations
              if (pAnno != NULL)
                {
                  // check if the file contains the correct version
                  double version = CCellDesignerImporter::determineVersion(pAnno);

                  if (version < 4.0)
                    {
                      CCopasiMessage(CCopasiMessage::RAW, "CellDesigner annotation was found in the file, but the version is not supported.\nPlease open the file in the latest version of CellDesigner and save it again.");
                    }
                  else
                    {
                      bool importCD = false;
#if LIBSBML_VERSION >= 50400
                      // if we don't have a layout import it!
                      LayoutModelPlugin* mplugin = (LayoutModelPlugin*)pSBMLDocument->getModel()->getPlugin("layout");

                      if (mplugin == NULL || (mplugin != NULL && mplugin->getNumLayouts() == 0))
                        importCD = true;

#endif

                      // ask the user if the CellDesigner annotation should be imported
                      if (importCD || CQMessageBox::question(NULL, "CellDesigner import", "A CellDesigner diagram was found in this file.\nDo you want to import the diagram?" , QMessageBox::Yes | QMessageBox::No , QMessageBox::No) == QMessageBox::Yes)
                        {
                          // do the import
                          CCellDesignerImporter cd_importer(pSBMLDocument);

                          if (cd_importer.getLayout() == NULL)
                            {
                              CCopasiMessage(CCopasiMessage::WARNING, "Sorry, CellDesigner annotations could not be imported.");
                            }
                          else
                            {
                              // now we have to import the created layout
                              // create the model map
                              std::string s1, s2;
                              std::map<std::string, std::string> modelmap;
                              std::map<CCopasiObject*, SBase*>::const_iterator it;
                              std::map<CCopasiObject*, SBase*>::const_iterator itEnd = pDataModel->getCopasi2SBMLMap().end();

                              for (it = pDataModel->getCopasi2SBMLMap().begin(); it != itEnd; ++it)
                                {
                                  s1 = SBMLUtils::getIdFromSBase(it->second);

                                  if (it->first)
                                    {
                                      s2 = it->first->getKey();
                                    }
                                  else
                                    {
                                      s2 = "";
                                    }

                                  if ((s1 != "") && (s2 != ""))
                                    {
                                      modelmap[s1] = s2;
                                    }
                                }

                              // the layout map and the id to key map can be empty
                              std::map<std::string, std::string> layoutmap;
                              std::map<std::string, std::string> idToKeyMap;
#ifdef USE_CRENDER_EXTENSION
                              CLayout* pLayout = SBMLDocumentLoader::createLayout(*cd_importer.getLayout(), modelmap, layoutmap, idToKeyMap);
#else
                              CLayout* pLayout = SBMLDocumentLoader::createLayout(*cd_importer.getLayout(), modelmap, layoutmap);
#endif /* USE_CRENDER_EXTENSION */

                              // add the layout to the DataModel
                              if (pLayout != NULL && pDataModel->getListOfLayouts() != NULL)
                                {
                                  // the addLayout methods expects a map as the second argument which currently is
                                  // ignored, so we just pass an empty one
                                  // TODO maybe the methods actually expects one of the maps above (layoutmap or idToKeyMap), but
                                  // TODO this is not documented in CListOfLayouts
                                  std::map<std::string, std::string> tmp;
                                  pDataModel->getListOfLayouts()->addLayout(pLayout, tmp);
                                }
                              else
                                {
                                  CCopasiMessage(CCopasiMessage::WARNING, "Sorry, Layout from CellDesigner annotations could not be created.");
                                }
                            }
                        }
                    }
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::RAW, "CellDesigner annotation was found in the file, but the version is not supported.\nPlease open the file in the latest version of CellDesigner and save it again.");
                }
            }
        }
    }
}
