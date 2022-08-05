// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/utilities/CCopasiTask.h"

class CFluxMode;
class CMetab;

class CEFMTask : public CCopasiTask
{
private:
  /**
   * Default constructor
   */
  CEFMTask();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   */
  CEFMTask(const CDataContainer * pParent,
           const CTaskEnum::Task & type = CTaskEnum::Task::fluxMode);

  /**
   * Copy constructor
   * @param const COptTask & src
   */
  //-COptTask(const CEFMTask & src);
  CEFMTask(const CEFMTask & src,
           const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CEFMTask();

  /**
   * Set the call back of the task
   * @param CProcessReport * pCallBack
   * @result bool success
   */
  virtual bool setCallBack(CProcessReportLevel callBack);

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

#ifndef SWIG

  /**
   * Retrieve the list of valid methods
   * @return const CTaskEnum::Method * pValidMethods
   */
  virtual const CTaskEnum::Method * getValidMethods() const;
#endif

  /**
   * Retrieve the Flux Modes
   * @return const std::vector< CFluxMode > &
   */
  const std::vector< CFluxMode > & getFluxModes() const;

  /**
   * Retrieve the description of the flux mode
   * @param const CFluxMode & fluxMode
   * @return std::string fluxModeDescription
   */
  std::string getFluxModeDescription(const CFluxMode & fluxMode) const;

  /**
   * Retrieve the reaction equation of the part of the flux mode pointed at by itReaction
   * @param const std::map< size_t, C_FLOAT64 >::const_iterator & itReaction
   * @return std::string reactionEquation
   */
  std::string getReactionEquation(const std::map< size_t, C_FLOAT64 >::const_iterator & itReaction) const;

  /**
   * Retrieve the species changes for the given flux mode and species
   * @param const CFluxMode & fluxMode
   * @param const CMetab & pMetab
   * @return std::pair< C_FLOAT64, C_FLOAT64 > changes
   */
  std::pair< C_FLOAT64, C_FLOAT64 > getSpeciesChanges(const CFluxMode & fluxMode,
      const CMetab & metab) const;

  /**
   * Retrieve the net reaction for the given flux mode.
   * @param const CFluxMode & fluxMode
   * @return std::string netReaction
   */
  std::string getNetReaction(const CFluxMode & fluxMode) const;

  /**
   * Retrieve the internal species for the given flux mode.
   * @param const CFluxMode & fluxMode
   * @return std::string species
   */
  std::string getInternalSpecies(const CFluxMode & fluxMode) const;

private:
  /**
   * Retrieve the net reaction data for the given flux mode.
   * @param const CFluxMode & fluxMode
   * @return std::map< const CMetab *, C_FLOAT64 >g netReactionData
   */
  std::map< const CMetab *, C_FLOAT64 > getNetReactionData(const CFluxMode & fluxMode) const;

#ifdef COPASI_SSA
  std::string getReactionEquationForward(unsigned C_INT32 index1,
                                         unsigned C_INT32 index2) const;
  std::string getReactionEquationBackward(unsigned C_INT32 index1,
                                          unsigned C_INT32 index2) const;
#endif // COPASI_SSA
};

#endif // COPASI_CEFMTask
