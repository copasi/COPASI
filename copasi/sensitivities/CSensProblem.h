/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensProblem.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/06/23 10:42:33 $
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

class CSensProblem: public CCopasiProblem
  {
  public:
    enum SubTaskType {
      unset = 0,
      SteadyState,
      TimeSeries,
      LyapunovExp
    };

    static const std::string SubTaskName[];

    static const char * XMLSubTask[];

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
     * Set the model of the problem
     * @param CModel * pModel
     * @result bool succes
     */
    //virtual bool setModel(CModel * pModel);

    /**
     * Retrieve the model the problem is dealing with.
     * @return "CModel *" pModel
     */
    //CModel * getModel() const;

    void setSubTaskType(const CSensProblem::SubTaskType & type);

    const CSensProblem::SubTaskType & getSubTaskType() const;

  private:
    CSensProblem::SubTaskType mSubTaskType;
  };

#endif // COPASI_CSensProblem
