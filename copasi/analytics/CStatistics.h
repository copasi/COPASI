// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CSTATISTICS_H
#define CSTATISTICS_H

#include "copasi/model/CModelValue.h"
#include "copasi/report/CCopasiObjectReference.h"
#include "copasi/report/CCopasiObject.h"

class CStatistics : public CModelEntity
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

  //virtual std::string getObjectDisplayName() const;

  /**
  * Retrieves the value of the statistics
  * @return const C_FLOAT64 & mStatValue
  */
  const C_FLOAT64 & getStatValue() const;

  /**
  * Retrieve object referencing the concentration
  * @return CConcentrationReference * concentrationReference
  */
  CCopasiObjectReference <C_FLOAT64> * getStatValueReference() const;

// Attributes
private:

  /**
   *  Value of the statistics.
   */
  C_FLOAT64 mStatValue;
  CCopasiObjectReference <C_FLOAT64> *mpStatValueReference;

  /**
  * Initialize the contained CCopasiObjects
  */
  void initObjects();
};

#endif // CSTATISTICS_H
