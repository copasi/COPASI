// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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
 * SEDMLImporter.h
 * $Rev:               $:  Revision of last commit
 * $Author:            $:  Author of last commit
 * $Date:              $:  Date of last commit
 * $HeadURL:       $
 * $Id::         $
 */

#ifndef SEDMLIMPORTER_H_
#define SEDMLIMPORTER_H_

#include <string>
#include <map>
#include <set>
#include <utility>

#include "copasi/function/CFunctionDB.h"
//#include "copasi/sbml/StdException.h"
#include "copasi/model/CModel.h"

#include <sedml/common/sedmlfwd.h>

LIBSBML_CPP_NAMESPACE_BEGIN
class Model;
LIBSBML_CPP_NAMESPACE_END

class CTrajectoryTask;
class CCompartment;
class CMetab;
class CProcessReport;
class CPlotSpecification;
class CReportDefinition;
class COutputDefinitionVector;
class CListOfLayouts;

class SEDMLImporter
{

protected:
  static
  C_FLOAT64 round(const C_FLOAT64 & x);

protected:
  std::string mArchiveFileName;
  std::set<unsigned int> mIgnoredSEDMLMessages;
  bool mIncompleteModel;
  unsigned int mLevel;
  unsigned int mOriginalLevel;
  unsigned int mVersion;

  CDataModel * mpDataModel;
  CModel* mpCopasiModel;

  SedDocument* mpSEDMLDocument;

  CProcessReport* mpImportHandler;
  unsigned C_INT32 mImportStep;
  size_t mhImportStep;
  unsigned C_INT32 mTotalSteps;

  std::set<std::string> mUsedSEDMLIds;
  bool mUsedSEDMLIdsPopulated;

  std::string mImportedModel;

  std::map<CReportDefinition*, std::string> mReportMap;

  // further symbols needed for updating content after import:
  CDataModel::CContent mContent;
public:
  SEDMLImporter();
  ~SEDMLImporter();

  const std::string getArchiveFileName();

  void readListOfPlotsFromSedMLOutput();

  /**
   * adds the given SED-ML curve to the COPASI plot, if supported
   *
   * prior to calling this function, please ensure to have the
   * the document and model set already.
   *
   * @param pCurve the SED-ML curve, that may include a style
   * @param pPlot the COPASI plot specification to add the curve to
   *
   */
  void addCurveToCopasiPlot(
    LIBSEDML_CPP_NAMESPACE_QUALIFIER SedAbstractCurve* pCurve,
    CPlotSpecification * pPlot);

  /**
  * adds the given SED-ML surface to the COPASI plot, if supported
  *
  * prior to calling this function, please ensure to have the
  * the document and model set already.
  *
  * @param pSurface the SED-ML surface, that may include a style
  * @param pPlot the COPASI plot specification to add the curve to
  *
  */
  void addSurfaceToCopasiPlot(
    LIBSEDML_CPP_NAMESPACE_QUALIFIER SedSurface * pSurface,
    CPlotSpecification * pPlot);


  /**
   * applies the given style to a plot item
   *
   * prior to calling this function, please ensure to have the
   * the document and model set already.
   *
   * @param pStyle the SED-ML Style to apply
   * @param plItem the copasi plot item
   *
   */
  void applyStyleToCopasiItem(
    LIBSEDML_CPP_NAMESPACE_QUALIFIER SedStyle* pStyle,
    CPlotItem* plItem);

  /**
   * imports the given report
   *
   * prior to calling this function, please ensure to have the
   * the document and model set already.
   *
   * @param report the SED-ML report to import
   */
  void importReport(LIBSEDML_CPP_NAMESPACE_QUALIFIER SedReport * report);

  /**
   * Updates COPASI tasks for a given SedML Simulation
   */
  void updateCopasiTaskForSimulation(SedSimulation* sedmlsim);

  /**
   * Updates the task / method settings from algorithm
   *
   * @param tTask, the time course task to update
   * @param alg the algorithm including algorithm parameters
   *
   */
  void applyAlgorithm(CTrajectoryTask * tTask, const SedAlgorithm * alg);

  /**
   * Imports the first viable SBML model
   */
  CModel* importFirstSBMLModel(CProcessReport* pImportHandler,
                               CDataModel* pDataModel);

  /**
   * Import all tasks for the imported SBML model
   */
  void importTasks();

  CModel* readSEDML(std::string filename, CProcessReport* pImportHandler,
                    CDataModel* pDataModel);

  CModel* parseSEDML(const std::string& sedmlDocumentText, CProcessReport* pImportHandler,
                     CDataModel * pDataModel);

  void updateContent(CDataModel::CContent & data, CDataModel& dm);

  /**
   * This call deletes an existing COPASI model.
   * The method can e.g. be called to clean up if an import fails.
   */
  void deleteCopasiModel();

  /**
   * sets a progress handler to inform about updates
   */
  void setImportHandler(CProcessReport* pHandler);

  /**
   * @return the progress handler set
   */
  CProcessReport* getImportHandlerAddr() const;

  /**
   * sets the sed-ml document that will be used by the importer
   *
   * (the document will not be automatically deleted) manually call
   * clearDocument to delete the existing document
   */
  void setSEDMLDocument(SedDocument *pDocument);

  /**
   * @return the current SED-ML document
   */
  SedDocument* getSEDMLDocument();

  /**
   * frees the current SED-ML document
   */
  void clearDocument();

  /**
   * sets the data model to be used by the importer
   */
  void setDataModel(CDataModel* pDataModel);

  /**
   * @return the current datamodel
   */
  CDataModel* getDataModel();

  /**
   * clears the currently set progress handler
   */
  virtual void clearCallBack();

  /**
   * not implemented
   */
  void restoreFunctionDB();
};

#endif /* SEDMLIMPORTER_H_ */
