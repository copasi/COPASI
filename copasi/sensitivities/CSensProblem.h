/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensProblem.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/06/29 09:02:21 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CSensProblem class.
 *  This class describes the steady state problem, i.e., it allows to specify
 *  for example initial conditions.
 *
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CSensProblem
#define COPASI_CSensProblem

#include <string>

#include "utilities/CCopasiProblem.h"
#include "model/CObjectLists.h"

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

  private:
    bool mIsSingleObject;
    CCopasiObjectName mSingleObjectCN;
    CObjectLists::ListType mListType;
  };

//****************************************************************

class CSensProblem: public CCopasiProblem
  {
  public:
    /**
     * this enumeration
     */

    enum SubTaskType {
      unset = 0,
      SteadyState,
      TimeSeries,
      LyapunovExp
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

    unsigned C_INT32 getNumberOfVariables() const;
    CSensItem getVariables(unsigned C_INT32 index) const;

    void addVariables(const CSensItem & item);

  private:

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
  };

#endif // COPASI_CSensProblem
