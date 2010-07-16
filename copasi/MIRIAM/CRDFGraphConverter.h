// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraphConverter.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/07/16 19:00:07 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CRDFGraphConverter
#define COPASI_CRDFGraphConverter

#include <string>

#include "copasi/MIRIAM/CRDFPredicate.h"

class CRDFGraph;
class CRDFTriplet;

class CRDFGraphConverter
{
public:
  static bool SBML2Copasi(std::string & XML);

private:
  struct sChange
  {
    CRDFPredicate::ePredicateType Source;
    CRDFPredicate::ePredicateType Target[4];
  };

  static sChange SBML2CopasiChanges[];

  static bool convert(CRDFGraph * pGraph, const sChange * changes);

  static bool convert(CRDFGraph * pGraph,
                      const CRDFTriplet & triplet,
                      const CRDFPredicate::Path & newPath);
};

#endif // COPASI_CRDFGraphConverter
