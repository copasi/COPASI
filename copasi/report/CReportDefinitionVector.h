// ReportDefinitionVector.h: interface for the CReportDefinitionVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined REPORT_DEFINITION_VECTOR
#define REPORT_DEFINITION_VECTOR

#include <iostream>
#include <vector>
#include <string>
#include "utilities/CReadConfig.h"
#include "utilities/CWriteConfig.h"
#include "CCopasiContainer.h"
#include "CReportDefinition.h"

class CReportDefinitionVector: public CCopasiContainer
  {
  private:
    std::vector<CReportDefinition> mReportDefinitions;
    std::string mKey;

  public:
    CReportDefinitionVector(const std::string &, const CCopasiContainer*);
    ~CReportDefinitionVector();

    const std::vector< CReportDefinition >* getReportDefinitionsAddr();

    /**
     * Loads parameters for this solver with data coming from a
     * CReadConfig object. (CReadConfig object reads an input stream)
     * @param configbuffer reference to a CReadConfig object.
     */
    void load(CReadConfig & configBuffer);

    /**
     * Saves the parameters of the solver to a CWriteConfig object.
     * (Which usually has a file attached but may also have socket)
     * @param configbuffer reference to a CWriteConfig object.
     */
    void save(CWriteConfig & configBuffer);

    void cleanup();

    std::string getKey();
  };

#endif // !defined(AFX_REPORTDEFINITIONVECTOR_H__172081F2_7BF6_49FA_8FC7_C890F2CB1974__INCLUDED_)
