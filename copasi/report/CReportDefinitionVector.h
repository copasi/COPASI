/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReportDefinitionVector.h,v $
  $Revision: 1.15 $
  $Name:  $
  $Author: gauges $
  $Date: 2009/02/18 20:55:33 $
  End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// ReportDefinitionVector.h: interface for the CReportDefinitionVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined REPORT_DEFINITION_VECTOR
#define REPORT_DEFINITION_VECTOR

#include <iostream>
#include <vector>
#include <string>
#include "utilities/CCopasiVector.h"
#include "report/CReportDefinition.h"

class CReportDefinitionVector: public CCopasiVectorN< CReportDefinition >
  {
  private:
    std::string mKey;

  public:
    CReportDefinitionVector(const std::string & name = "ReportDefinitions",
                            const CCopasiContainer* pParent = NULL);

    ~CReportDefinitionVector();

    //    const std::vector< CReportDefinition*>* getReportDefinitionsAddr();

    CReportDefinition* createReportDefinition(const std::string & name, const std::string & comment);
    bool removeReportDefinition(const std::string & key);

    void cleanup();

    const std::string& getKey();
  };

#endif // !defined(AFX_REPORTDEFINITIONVECTOR_H__172081F2_7BF6_49FA_8FC7_C890F2CB1974__INCLUDED_)
