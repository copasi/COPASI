// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CSTATISTICS_H
#define CSTATISTICS_H

#include "copasi/model/CModelValue.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/core/CDataObject.h"
#include "copasi/core/CDataContainer.h"

class CStatistics : public CDataContainer // CModelEntity //
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
              const CDataContainer * pParent,
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
  CDataObject * getStatValueReference() const;

// Attributes
private:

  /**
   *  Value of the statistics.
   */
  C_FLOAT64 mStatValue;

protected:
  CDataObject * mpStatValueReference;

  /**
  * Initialize the contained CDataObjects
  */
  void initObjects();
};

#endif // CSTATISTICS_H
