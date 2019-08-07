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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// ReportDefinitionVector.h: interface for the CReportDefinitionVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined REPORT_DEFINITION_VECTOR
#define REPORT_DEFINITION_VECTOR

#include "copasi/report/CReportDefinition.h"
#include "copasi/core/CDataVector.h"

class CReportDefinitionVector: public CDataVectorN< CReportDefinition >
{
private:
  std::string mKey;

public:
  CReportDefinitionVector(const std::string & name = "ReportDefinitions",
                          const CDataContainer* pParent = NULL);

  virtual ~CReportDefinitionVector();

  CReportDefinition* createReportDefinition(const std::string & name, const std::string & comment);

  bool removeReportDefinition(const std::string & key);

  void cleanup();

  virtual const std::string & getKey() const;
};

#endif // !defined(AFX_REPORTDEFINITIONVECTOR_H__172081F2_7BF6_49FA_8FC7_C890F2CB1974__INCLUDED_)
