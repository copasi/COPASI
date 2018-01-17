// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CRDFGraphConverter
#define COPASI_CRDFGraphConverter

#include <string>

#include "copasi/MIRIAM/CRDFPredicate.h"
#include "copasi/utilities/CCallback.h"

class CRDFGraph;
class CRDFTriplet;

class CRDFGraphConverter
{
public:
  static bool SBML2Copasi(std::string & XML);

  static void deleteConverterData();

private:
  struct sChange
  {
    CRDFPredicate::ePredicateType Source;
    CRDFPredicate::ePredicateType Target[4];
    CCallbackInterface * pCheckTriplet;
  };

  static sChange SBML2CopasiChanges[];

  static bool convert(CRDFGraph * pGraph, const sChange * changes);

  static bool convert(CRDFGraph * pGraph,
                      const CRDFTriplet & triplet,
                      const CRDFPredicate::Path & newPath);
};

#endif // COPASI_CRDFGraphConverter
