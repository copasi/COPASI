// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#if !defined OUTPUTSPECIFICATION_VECTOR
#define OUTPUTSPECIFICATION_VECTOR

#include "copasi/plot/CPlotSpecification.h"
#include "copasi/core/CDataVector.h"

class COutputDefinitionVector : public CDataVectorN<CPlotSpecification>
{
private:
  std::string mKey;

public:
  COutputDefinitionVector(const std::string & name = "OutputDefinitions",
                          const CDataContainer* pParent = NULL);

  virtual ~COutputDefinitionVector();

  CPlotSpecification* createPlotSpec(const std::string & name,
                                     CPlotItem::Type type = CPlotItem::plot2d);

  bool removePlotSpec(const std::string & key);

  void cleanup();

  virtual const std::string& getKey() const;
};

#endif
