// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CSTATISTICS_H
#define CSTATISTICS_H

#include "copasi/model/CModelValue.h"
#include "copasi/report/CCopasiObjectReference.h"
#include "copasi/report/CCopasiObject.h"
#include "copasi/report/CCopasiContainer.h"

class CStatistics : public CCopasiContainer // CModelEntity //
{

// Operations
private:
  /**
  * Default constructor made unreachable.
  **/
  CStatistics();

public:
  /**
  * Public constructor.
  **/
  CStatistics(const std::string & name,
              const CCopasiContainer * pParent,
              const std::string & type,
              const unsigned C_INT32 & flag,
              C_FLOAT64 statValue);

  /**
  *  Destructor.
  */
  ~CStatistics();

  /**
  * Retrieves the value of the statistics
  * @return const C_FLOAT64 & mStatValue
  */
  const C_FLOAT64 & getStatValue() const;

  /**
  * Retrieve object referencing the concentration
  * @return CConcentrationReference * concentrationReference
  */
  CCopasiObject * getStatValueReference() const;

// Attributes
private:

  /**
   *  Value of the statistics.
   */
  C_FLOAT64 mStatValue;

protected:
  CCopasiObject * mpStatValueReference;

  /**
  * Initialize the contained CCopasiObjects
  */
  void initObjects();
};

#endif // CSTATISTICS_H
