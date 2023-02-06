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

#ifndef COPASI_CSensProblem
#define COPASI_CSensProblem

#include <string>

#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/model/CObjectLists.h"
#include "copasi/core/CDataArray.h"

/**
 * This class describes either one specific COPASI object (represented
 * by a registered object CN internally) or a list of objects (see CObjectLists
 * class).
 */
class CSensItem
{
public:
  CSensItem();
  CSensItem(const std::string & cn);
  CSensItem(CObjectLists::ListType type);

  bool isSingleObject() const;

  void setSingleObjectCN(const CCommonName & cn);
  const CCommonName & getSingleObjectCN() const;
  std::string getSingleObjectDisplayName(const CDataModel * pDataModel) const;

  void setListType(CObjectLists::ListType lt);
  const CObjectLists::ListType & getListType() const;
  std::string getListTypeDisplayName() const;

  std::vector< CDataObject * > getVariablesPointerList(CDataModel * pDataModel);

  //size_t dimensionality() const;

  bool operator==(const CSensItem & rhs) const;
  bool operator!=(const CSensItem & rhs) const;

  std::string print(const CDataModel * pDataModel) const;

private:
  CCommonName mSingleObjectCN;
  CObjectLists::ListType mListType;
};

//****************************************************************

/**
 *  CSensProblem class.
 */
class CSensProblem : public CCopasiProblem
{
public:
  /**
   * this enumeration
   */

  enum SubTaskType
  {
    Evaluation,
    SteadyState,
    TimeSeries,
    ParameterEstimation,
    Optimization,
    CrossSection,
    __SIZE
    //LyapunovExp
  };

  static const CEnumAnnotation< CTaskEnum::Task, SubTaskType > SubTaskTypeToTask;

  static const std::string SubTaskName[];

  static const char * XMLSubTask[];

  static std::vector< CObjectLists::ListType > getPossibleTargetFunctions(CSensProblem::SubTaskType);
  static std::vector< CObjectLists::ListType > getPossibleVariables(CSensProblem::SubTaskType);

  // Operations

  /**
   * Default constructor.
   * @param const CDataContainer * pParent (default: NULL)
   */
  CSensProblem(const CDataContainer * pParent = NO_PARENT);

  /**
   *  Copy constructor.
   *  @param "const CSensProblem &" src
   * @paramconst CDataContainer * pParent (default: NULL)
   */
  CSensProblem(const CSensProblem & src,
               const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  virtual ~CSensProblem();

  /**
   * Retrieve the optional sub task
   *
   * @return CCopasiTask* * pSubTask
   */
  virtual CCopasiTask * getSubTask() const override;

  /**
   *   set the problem's SubTaskType:
   */
  void setSubTaskType(const CSensProblem::SubTaskType & type);

  /**
   *   get the problem's SubTaskType:
   */
  CSensProblem::SubTaskType getSubTaskType() const;

  CSensItem getTargetFunctions() const;
  void setTargetFunctions(const CSensItem item);

  size_t getNumberOfVariables() const;
  CSensItem getVariables(size_t index) const;

  void addVariables(const CSensItem & item);

  bool changeVariables(size_t index, const CSensItem & item);

  bool removeVariables(size_t index);

  //remove all variables:
  bool removeVariables();

  CArray & getResult();
  const CArray & getResult() const;
  CDataArray * getResultAnnotated();
  const CDataArray * getResultAnnotated() const;

  CArray & getScaledResult();
  const CArray & getScaledResult() const;
  CDataArray * getScaledResultAnnotated();
  const CDataArray * getScaledResultAnnotated() const;

  CArray & getCollapsedResult();
  const CArray & getCollapsedResult() const;
  CDataArray * getCollapsedResultAnnotated();
  const CDataArray * getCollapsedResultAnnotated() const;

  bool collapsRequested() const;

  /**
   * This is the output method for any result of a problem. The default implementation
   * provided with CCopasiProblem. Does only print "Not implemented." To overide this
   * default behaviour one needs to reimplement the virtual printResult function.
   * @param std::ostream * ostream
   */
  virtual void printResult(std::ostream * ostream) const override;

  /**
   * Output stream operator. Prints description of the problem
   * @param ostream & os
   * @param const Problem & A
   * @return ostream & os
   */
  friend std::ostream & operator<<(std::ostream & os, const CSensProblem & o);

  /**
   * This is the output method for any object. It calls the insert operator<<
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const override;

private:
  /**
   * Initialize the method parameter
   */
  void initializeParameter();

  void initObjects();

  /**
   *  create the copasi parameters corresponding to the members of a CSensItem
   */
  static void createParametersInGroup(CCopasiParameterGroup * pg);

  static void copySensItemToParameterGroup(const CSensItem * si, CCopasiParameterGroup * pg);

  static void copyParameterGroupToSensItem(const CCopasiParameterGroup * pg, CSensItem * si);

  /**
   *  this sets up a problem for debugging purposes
   */
  void initDebugProblem();

  CSensProblem::SubTaskType * mpSubTaskType;

  CCopasiParameterGroup * mpTargetFunctions;

  /**
   *  This holds the variables items
   */
  CCopasiParameterGroup * mpVariablesGroup;

  /**
   *  This holds the result
   */
  CArray mResult;

  CDataArray * mpResultAnnotation;

  /**
   *  This holds the scaled result
   */
  CArray mScaledResult;

  CDataArray * mpScaledResultAnnotation;

  /**
   *  This holds the collapsed result
   */
  CArray mCollapsedResult;

  CDataArray * mpCollapsedResultAnnotation;
};

#endif // COPASI_CSensProblem
