/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/COutputDefinitionVector.h,v $
  $Revision: 1.5 $
  $Name:  $
  $Author: shoops $
  $Date: 2011/09/16 12:10:08 $
  End CVS Header */

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#if !defined OUTPUTSPECIFICATION_VECTOR
#define OUTPUTSPECIFICATION_VECTOR

#include "plot/CPlotSpecification.h"
#include "utilities/CCopasiVector.h"

class COutputDefinitionVector : public CCopasiVectorN<CPlotSpecification>
{
private:
  std::string mKey;

public:
  COutputDefinitionVector(const std::string & name = "OutputDefinitions",
                          const CCopasiContainer* pParent = NULL);

  ~COutputDefinitionVector();

  CPlotSpecification* createPlotSpec(const std::string & name,
                                     CPlotItem::Type type = CPlotItem::plot2d);
  bool removePlotSpec(const std::string & key);

  void cleanup();

  const std::string& getKey() const;
};

#endif
