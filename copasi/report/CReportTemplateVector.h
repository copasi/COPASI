// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// ReportTemplateVector.h: interface for the CReportTemplateVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined REPORT_DEFINITION_VECTOR
#define REPORT_DEFINITION_VECTOR

#include <iostream>
#include <vector>
#include <string>
#include "utilities/CCopasiVector.h"
#include "report/CReportTemplate.h"

class CReportTemplateVector: public CCopasiVectorN< CReportTemplate >
{
private:
  std::string mKey;

public:
  CReportTemplateVector(const std::string & name = "ReportTemplates",
                          const CCopasiContainer* pParent = NULL);

  ~CReportTemplateVector();

  //    const std::vector< CReportTemplate*>* getReportTemplatesAddr();

  CReportTemplate* createReportTemplate(const std::string & name, const std::string & comment);
  bool removeReportTemplate(const std::string & key);

  void cleanup();

  virtual const std::string & getKey() const;
};

#endif // !defined(AFX_REPORTDEFINITIONVECTOR_H__172081F2_7BF6_49FA_8FC7_C890F2CB1974__INCLUDED_)
