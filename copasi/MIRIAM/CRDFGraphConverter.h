// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFGraphConverter.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/04 14:17:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CRDFGraphConverter
#define COPASI_CRDFGraphConverter

#include <string>

#include "copasi/MIRIAM/CRDFPredicate.h"
#include "copasi/MIRIAM/CRDFGraph.h"

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
                        const CRDFGraph::CTriplet & triplet,
                        const CRDFPredicate::Path & newPath);
  };

#endif // COPASI_CRDFGraphConverter
