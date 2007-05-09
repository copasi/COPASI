// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensProblem.h,v $
//   $Revision: 1.18.4.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/05/09 14:20:13 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CSensProblem
#define COPASI_CSensProblem

#include <string>

#include "utilities/CCopasiProblem.h"
#include "model/CObjectLists.h"
#include "utilities/CAnnotatedMatrix.h"

/**
 * This class describes either one specific copasi object (represented
 * by a registered object CN internally) or a list of objects (see CObjectLists
 * class).
 */
class CSensItem
  {
  public:
    bool isSingleObject() const;

    void setSingleObjectCN(const CCopasiObjectName & cn);
    const CCopasiObjectName & getSingleObjectCN() const;
    std::string getSingleObjectDisplayName() const;

    void setListType(CObjectLists::ListType lt);
    const CObjectLists::ListType & getListType() const;
    std::string getListTypeDisplayName() const;

    std::vector<CCopasiObject*> getVariablesPointerList(CModel* pModel);

    //unsigned C_INT32 dimensionality() const;

    bool operator==(const CSensItem & rhs) const;
    bool operator!=(const CSensItem & rhs) const;

  private:
    CCopasiObjectName mSingleObjectCN;
    CObjectLists::ListType mListType;
  };

//****************************************************************

/**
 *  CSensProblem class.
 */
class CSensProblem: public CCopasiProblem
  {
  public:
    /**
     * this enumeration
     */

    enum SubTaskType {
      Evaluation,
      SteadyState,
      TimeSeries //,
      //LyapunovExp
    };

    static const std::string SubTaskName[];

    static const char * XMLSubTask[];

    static std::vector<CObjectLists::ListType> getPossibleTargetFunctions(CSensProblem::SubTaskType);
    static std::vector<CObjectLists::ListType> getPossibleVariables(CSensProblem::SubTaskType);

    // Operations

    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSensProblem(const CCopasiContainer * pParent = NULL);

    /**
     *  Copy constructor.
     *  @param "const CSensProblem &" src
     * @paramconst CCopasiContainer * pParent (default: NULL)
     */
    CSensProblem(const CSensProblem & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    virtual ~CSensProblem();

    /**
     *   set the problem's SubTaskType:
     */
    void setSubTaskType(const CSensProblem::SubTaskType & type);

    /**
     *   get the problem's SubTaskType:
     */
    const CSensProblem::SubTaskType getSubTaskType() const;

    CSensItem getTargetFunctions() const;
    void changeTargetFunctions(const CSensItem item);

    unsigned C_INT32 getNumberOfVariables() const;
    CSensItem getVariables(unsigned C_INT32 index) const;

    void addVariables(const CSensItem & item);

    bool changeVariables(unsigned C_INT32 index, const CSensItem & item);

    bool removeVariables(unsigned C_INT32 index);

    //remove all variables:
    bool removeVariables();

    CCopasiArray & getResult();
    const CCopasiArray & getResult() const;
    CArrayAnnotation * getResultAnnotated();
    const CArrayAnnotation * getResultAnnotated() const;

    CCopasiArray & getScaledResult();
    const CCopasiArray & getScaledResult() const;
    CArrayAnnotation * getScaledResultAnnotated();
    const CArrayAnnotation * getScaledResultAnnotated() const;

    CCopasiArray & getCollapsedResult();
    const CCopasiArray & getCollapsedResult() const;
    CArrayAnnotation * getCollapsedResultAnnotated();
    const CArrayAnnotation * getCollapsedResultAnnotated() const;

    bool collapsRequested() const;

    /**
     * This is the output method for any result of a problem. The default implementation
     * provided with CCopasiProblem. Does only print "Not implemented." To overide this
     * default behaviour one needs to reimplement the virtual printResult function.
     * @param std::ostream * ostream
     */
    virtual void printResult(std::ostream * ostream) const;

    /**
     * Output stream operator. Prints description of the problem
     * @param ostream & os
     * @param const Problem & A
     * @return ostream & os
     */
    friend std::ostream &operator<<(std::ostream &os, const CSensProblem & o);

    /**
     * This is the output method for any object. It calls the insert operator<<
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;

  private:

    void initObjects();

    /**
     *  create the copasi parameters corresponding to the members of a CSensItem
     */
    static void createParametersInGroup(CCopasiParameterGroup *pg);

    static void copySensItemToParameterGroup(const CSensItem * si, CCopasiParameterGroup *pg);

    static void copyParameterGroupToSensItem(const CCopasiParameterGroup *pg, CSensItem * si);

    /**
     *  this sets up a problem for debugging purposes
     */
    void initDebugProblem();

    CSensProblem::SubTaskType * mpSubTaskType;

    CCopasiParameterGroup * mpTargetFunctions;

    //std::vector<CSensItem> mVariables;

    /**
     *  This holds the variables items
     */
    CCopasiParameterGroup * mpVariablesGroup;

    /**
     *  This holds the result
     */
    CCopasiArray mResult;

    CArrayAnnotation * mpResultAnnotation;

    /**
     *  This holds the scaled result
     */
    CCopasiArray mScaledResult;

    CArrayAnnotation * mpScaledResultAnnotation;

    /**
     *  This holds the collapsed result
     */
    CCopasiArray mCollapsedResult;

    CArrayAnnotation * mpCollapsedResultAnnotation;
  };

#endif // COPASI_CSensProblem
