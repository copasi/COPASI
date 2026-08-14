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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_COutputAssistant
#define COPASI_COutputAssistant

#include <vector>
#include <string>
#include <map>
#include "copasi/copasi.h"

#include "copasi/utilities/CCopasiTask.h"

class CPlotSpecification;
class CReportDefinition;
class CDataObject;
class CDataModel;
class CDataArray;
class CFitProblem;
class CExperimentSet;

class COutputOption
{
public:

  std::string name;
  bool enabled;
  std::string description;
};

#ifndef SWIG
struct SFittingPlotOptions
{
  bool needMeasured;
  bool needFitted;
  bool needErrors;
  bool isValdation;
  std::string measuredLabel;
  std::string fittedLabel;
  std::string errorLabel;

  bool hasAny() const
  {
    return needMeasured || needFitted || needErrors;
  }

  void setExperimentLabels()
  {
    measuredLabel = "Measured Value";
    fittedLabel = "Fitted Value";
    errorLabel = "Weighted Error";
    isValdation = false;
  }

  void setValidationLabels()
  {
    measuredLabel = "Validation Value";
    fittedLabel = "Validation Fitted";
    errorLabel = "Validation Error";
    isValdation = true;
  }
};
#endif

class CDefaultOutputDescription
{
public:

  CDefaultOutputDescription():
    name(""),
    description(""),
    isPlot(true),
    mTaskType(CTaskEnum::Task::steadyState),
    mSecondaryTask(CTaskEnum::Task::UnsetTask),
    options()
  {}

  //C_INT32 id;
  std::string name;
  std::string description;
  bool isPlot;
  CTaskEnum::Task mTaskType;
  CTaskEnum::Task mSecondaryTask;
  std::vector<COutputOption> options;
};

class COutputAssistant
{
public:

  /**
   *  get a list of indices of output definitions that are
   *  suitable for the problem.
   *  If problem=NULL (default) all indices in the map are returned.
   */
  static
  std::vector<C_INT32> getListOfDefaultOutputDescriptions(const CCopasiTask * task = NULL);

  /**
   *  get an index of a default output report that is
   *  recommended  for the given problem.
   *  If no such report exists, -1 is returned
   */
  static
  C_INT32 getDefaultReportIndex(const CCopasiProblem * problem);

  /**
   *  get an index of a default plot that is
   *  recommended  for the given problem.
   *  If no such plot exists, -1 is returned
   */
  static
  C_INT32 getDefaultPlotIndex(const CCopasiProblem * problem);

  /**
   *  get title of output definition with index id.
   */
  static
  const std::string & getItemName(C_INT32 id);

  /**
   *  get complete description of output definition with index id.
   */
  static
  const CDefaultOutputDescription & getItem(C_INT32 id);

  /**
   * get the id of output definition with the given name
   *
   * @param name the name of the default output description to find
   * @param isPlot boolean indicating whether we are looking for a plot
   *        (true, default) or report.
   * @return the item id if found, or -1 if it is not
   */
  static
  C_INT32 findItemByName(const std::string& name, bool isPlot = true);

  /**
   *  create a plot or report from template with index id.
   *  returns a pointer to the plot or report definition (or NULL)
   *  if activate==true and the ouput is a report the report is set as
   *  the current report for the task (possibly replacing an already set report)
   */
  static
  CDataObject* createDefaultOutput(C_INT32 id, CCopasiTask * task, CDataModel* pDataModel, bool activate = true, const std::vector<COutputOption>* pOptions = NULL);

private:           //************************************

  typedef std::map<C_INT32, CDefaultOutputDescription> Map;

  static
  Map mMap;

  //this method creates the lists of output descriptions
  static
  bool initialize();

  /**
   * Check if an option is enabled.
   * 
   * @param pOptions pointer to the list of options (can be NULL)
   * @param name the name of the option to check
   * @param defaultValue the default value to return if the option is not found (default: true)
   * 
   * @return true if the option is enabled, false otherwise
   */
  static bool isOptionEnabled(const std::vector< COutputOption > * pOptions,
                              const std::string& name,
                              bool defaultValue = true);

  static
  CPlotSpecification* createPlot(const std::string & name,
                                 const CDataObject* x,
                                 bool logX,
                                 const std::vector<const CDataObject*> & y,
                                 bool logY,
                                 const CTaskEnum::Task & taskType,
                                 CDataModel* pDataModel,
                                 CCopasiTask *task = NULL);

  static
  CReportDefinition* createTable(const std::string & name,
                                 const std::vector<const CDataObject*> & d,
                                 const std::string & comment,
                                 const CTaskEnum::Task & taskType,
                                 CDataModel* pDataModel);

  static void add2DDataArrayToVector(std::vector<const CDataObject *> &pVector, const CDataArray* pArray);

  /**
   * @return a parameter estimation problem for the given data model, or NULL if no such problem exists
   */
  static CFitProblem* getParameterEstimationProblem(CDataModel* pDataModel);

#ifndef SWIG
  /**
   * @return the fitting plot options for the given list of options, 
   * or default options if the list is NULL or does not contain any fitting plot options
   */
  static SFittingPlotOptions getExperimentFittingPlotOptions(const std::vector<COutputOption>* pOptions);

  /**
   * @return the validation fitting plot options for the given list of options,
   * or default options if the list is NULL or does not contain any validation fitting plot options
   */
  static SFittingPlotOptions getValidationFittingPlotOptions(const std::vector<COutputOption>* pOptions);

  /**
   * @return a parameter estimation plot for the given data model and options, or NULL if no such plot can be created
   */
  static CPlotSpecification* createParameterEstimationPlot(C_INT32 id,
                                                           CDataModel* pDataModel,
                                                           const std::vector<COutputOption>* pOptions);

  /**
   * @return a fitting plot for the given data model, experiment set, and options, 
   * or NULL if no such plot can be created
   */
  static CPlotSpecification* createCombinedFittingPlot(C_INT32 id,
                                                       CDataModel* pDataModel,
                                                       const CExperimentSet& experimentSet,
                                                       const SFittingPlotOptions& options,
                                                       CPlotSpecification* pExistingPlot = NULL);

  /**
   * @return a fitting plot for each experiment in the given experiment set, with the given options, 
   * or NULL if no such plot can be created
   */
  static CPlotSpecification* createPerExperimentFittingPlot(C_INT32 id,
                                                            CDataModel* pDataModel,
                                                            const CExperimentSet& experimentSet,
                                                            const SFittingPlotOptions& options);

  /**
   * @return a fitting plot for each dependent value in the given experiment set, with the given options,
   * or NULL if no such plot can be created
   */
  static CPlotSpecification* createPerDependentValueFittingPlot(C_INT32 id,
                                                                CDataModel* pDataModel,
                                                                const CExperimentSet& experimentSet,
                                                                const SFittingPlotOptions& options,
                                                                std::map<const CDataObject*, CPlotSpecification*>* pPlotSpecMap = NULL);

  /**
   * @return a progress plot for the given data model and data objects, or NULL if no such plot can be created
   */
  static CPlotSpecification* createProgressPlot(C_INT32 id,
                                                CDataModel* pDataModel,
                                                const CDataObject* pXData,
                                                const CDataObject* pYData,
                                                const std::string& plotTitle,
                                                const std::string& itemTitle);

#endif // SWIG

  static const std::string emptyString;
  static const CDefaultOutputDescription emptyItem;
};

#endif
