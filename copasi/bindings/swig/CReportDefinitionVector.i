// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "report/CReportDefinitionVector.h"

%}


class CReportDefinitionVector: public CCopasiVectorN< CReportDefinition >
{
  public:
    CReportDefinitionVector(const std::string & name = "ReportDefinitions",
                            const CCopasiContainer* pParent = &RootContainer);

    ~CReportDefinitionVector();
    CReportDefinition* createReportDefinition(const std::string & name, const std::string & comment);
    
    bool removeReportDefinition(const std::string & key);

    const std::string& getKey();

};


