// ReportDefinitionVector.h: interface for the CReportDefinitionVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined REPORT_DEFINITION_VECTOR
#define REPORT_DEFINITION_VECTOR

#include <iostream>
#include <vector>
#include <string>
#include "utilities/CCopasiVector.h"
#include "CReportDefinition.h"

class CReportDefinitionVector: public CCopasiVector< CReportDefinition >
  {
  private:
    std::string mKey;

  public:
    CReportDefinitionVector(const std::string & name = "noname",
                            const CCopasiContainer* pParent = NULL);

    ~CReportDefinitionVector();

    const std::vector< CReportDefinition*>* getReportDefinitionsAddr();

    bool addReportDefinition(const std::string name, const std::string comment);

    void cleanup();

    const std::string& getKey();
  };

#endif // !defined(AFX_REPORTDEFINITIONVECTOR_H__172081F2_7BF6_49FA_8FC7_C890F2CB1974__INCLUDED_)
