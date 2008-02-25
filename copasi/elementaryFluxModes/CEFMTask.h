// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMTask.h,v $
//   $Revision: 1.1.18.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/25 21:15:22 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CEFMTask class.
 *  This class is used to describe a task in COPASI. This class is
 *  intended to be used as the parent class for all tasks whithin COPASI.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CEFMTask
#define COPASI_CEFMTask

#include <string>

#include "utilities/CCopasiTask.h"

class CEFMTask : public CCopasiTask
  {
  public:
    /**
     * The methods which can be selected for performing this task.
     */
    static const unsigned C_INT32 ValidMethods[];

    /**
     * Check whether the given method is in the list of valid methods
     * This list must end with CCopasiMethod::unset
     * @param const unsigned C_INT32 & method
     * @param const unsigned C_INT32 * validMethods
     * @return bool isValid
     */
    static bool isValidMethod(const unsigned C_INT32 & method,
                              const unsigned C_INT32 * validMethods);

    /**
     * default constructor
     * @param const CCopasiContainer * pParent (default: RootContainer)
     */
    CEFMTask(const CCopasiContainer * pParent = & RootContainer);

    /**
     * Copy constructor
     * @param const COptTask & src
     */
    //-COptTask(const CEFMTask & src);
    CEFMTask(const CEFMTask & src, const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CEFMTask();

    /**
     * Set the call back of the task
     * @param CProcessReport * pCallBack
     * @result bool succes
     */
    virtual bool setCallBack(CProcessReport * pCallBack);

    /**
     * Initialize the task. If an ostream is given this ostream is used
     * instead of the target specified in the report. This allows nested
     * tasks to share the same output device.
     * @param const OutputFlag & of
     * @param COutputHandler * pOutputHandler
     * @param std::ostream * pOstream (default: NULL)
     * @return bool success
     */
    virtual bool initialize(const OutputFlag & of,
                            COutputHandler * pOutputHandler,
                            std::ostream * pOstream);

    /**
     * Process the task with or without initializing to the initial state.
     * @param const bool & useInitialValues
     * @return bool success
     */
    virtual bool process(const bool & useInitialValues);

    /**
     * Set the method type applied to solve the task
     * @param const CCopasiMethod::SubType & type
     * @return bool success
     */
    virtual bool setMethodType(const int & type);

    /**
     * Check the reversibility of the indexed Flux Mode
     * @param unsigned C_INT32 index
     * @return bool
     */ // should not be used
    bool isFluxModeReversible(unsigned C_INT32 index) const;

    /**
     * Retrieve the number of Flux Modes
     * @return unsigned C_INT32 size
     */
    unsigned C_INT32 getFluxModeSize() const;

    /**
     * Retrieve the description of the indexed Flux Mode
     * @param unsigned C_INT32 index
     * @return std::string description
     */
    std::string getFluxModeDescription(unsigned C_INT32 index) const;

    unsigned C_INT32 getFluxModeSize(unsigned C_INT32 index) const;

    std::string getReactionEquation(unsigned C_INT32 index1,
                                    unsigned C_INT32 index2) const;
  };

#endif // COPASI_CEFMTask
