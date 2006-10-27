%{

#include "report/CReportDefinitionVector.h"

%}

#ifndef COPASI_DEBUG

%nodefaultctor
%nodefaultdtor

#endif /* !COPASI_DEBUG */



class CReportDefinitionVector: public CCopasiVectorN< CReportDefinition >
{
  public:
#ifdef COPASI_DEBUG  
    CReportDefinitionVector(const std::string & name = "ReportDefinitions",
                            const CCopasiContainer* pParent = &RootContainer);

    ~CReportDefinitionVector();
#endif /* COPASI_DEBUG */
    CReportDefinition* createReportDefinition(const std::string & name, const std::string & comment);
    
    bool removeReportDefinition(const std::string & key);

    const std::string& getKey();

};

#ifndef COPASI_DEBUG

%clearnodefaultctor
%clearnodefaultdtor

#endif /* !COPASI_DEBUG */


