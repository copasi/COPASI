/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReportDefinitionVector.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:01 $
   End CVS Header */

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

class CReportDefinitionVector: public CCopasiVectorN< CReportDefinition >
  {
  private:
    std::string mKey;

  public:
    CReportDefinitionVector(const std::string & name = "ReportDefinitions",
                            const CCopasiContainer* pParent = &RootContainer);

    ~CReportDefinitionVector();

    //    const std::vector< CReportDefinition*>* getReportDefinitionsAddr();

    CReportDefinition* createReportDefinition(const std::string & name, const std::string & comment);
    bool removeReportDefinition(const std::string & key);

    void cleanup();

    const std::string& getKey();
  };

#endif // !defined(AFX_REPORTDEFINITIONVECTOR_H__172081F2_7BF6_49FA_8FC7_C890F2CB1974__INCLUDED_)
