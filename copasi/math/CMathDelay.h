// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CMathDelay
#define COPASI_CMathDelay

#include <map>
#include <string>

#include "copasi/math/CMathObject.h"
#include "copasi/utilities/CVector.h"

class CMathContainer;

class CMathDelay
{
public:
  /**
   * Default Constructor
   */
  CMathDelay();

  /**
   * Destructor
   */
  virtual ~CMathDelay();

  /**
   * Create and compile the delay
   * @param CMath::DelayData::iterator & itDelayData
   * @param const size_t & delayValueCount
   * @param CMathContainer & container
   * @param CMathObject * pLagObject
   */
  void create(CMath::DelayData::iterator & itDelayData,
              const size_t & delayValueCount,
              CMathContainer & container,
              CMathObject * pLagObject);

  /**
   * Add a value object to the delay
   * @param CMath::DelayValueData::iterator & itValueData
   * @param const size_t & index
   * @param CMathObject * pValueObject
   */
  void addValueObject(CMath::DelayValueData::iterator & itValueData,
                      const size_t & index,
                      CMathObject * pValueObject);

  /**
   * Update the expression containing the delay
   * @param CMath::DelayValueData::iterator & itValueData
   * @param const size_t & index
   */
  void modifyMathObject(CMath::DelayValueData::iterator & itValueData,
                        const size_t & index);

  /**
   * Copy an existing object
   * @param const CMathDelay & src
   * @param CMathContainer & container
   * @param const size_t & valueOffset
   * @param const size_t & objectOffset
   */
  void copy(const CMathDelay & src, CMathContainer & container, const size_t & valueOffset, const size_t & objectOffset);

  /**
   * Create the update sequences required for event processing.
   */
  void createUpdateSequences();

  /**
   * Calculate the delay values.
   * @param const bool & useMoieties
   */
  void calculateDelayValues(const bool & useMoieties);

private:
  /**
   * A pointer to the container the delay belongs to
   */
  CMathContainer * mpContainer;

  /**
   * The object the lag of the delay
   */
  CMathObject * mpLagObject;

  /**
   * The object for the delayed value
   */
  CVector< CMathObject * > mValueObjects;

  /**
   * The sequence of calculations required to determine the delayed value
   */
  CObjectInterface::UpdateSequence mValueSequence;

  /**
   * The sequence of calculations required to determine the delayed value based on the reduced
   * state
   */
  CObjectInterface::UpdateSequence mValueSequenceReduced;
};

#endif // COPASI_CMathDelay
