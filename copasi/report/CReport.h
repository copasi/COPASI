/****************************************************************************
 * 
 * Created: Tue Aug 11 2003
 *      by: Liang Xu
 *
 *  Created for Copasi by Liang Xu
 ****************************************************************************/

#ifndef COPASI_CReport
#define COPASI_CReport

#include "CCopasiObject.h"
#include <string>
#include <vector>
#include <iostream>

class CReportDefinition;
class CBody;
class CReportTable;

class CReport : public CCopasiObject
  {
  private:
    std::ostream* outputTarget;
    std::vector<CCopasiObject*> footerObjectList;
    std::vector<CCopasiObject*> bodyObjectList;
    std::vector<CCopasiObject*> headerObjectList;

    CReportDefinition *mpReportDef;
    std::string mTarget;
    bool mAppend;
    //    std::string mKey;

  public:
    /**
        *  Default constructor.
        */
    CReport();

    /**
    cleanup
    */
    void cleanup();

    /**
       *  Destructor.
       */
    ~CReport();

    /**
    returns the reference of the Report Tag
    */
    CReportDefinition* getReportDefinition();

    /**
    compile the object list from name vector
    */
    void compile(const std::vector< CCopasiContainer * > * pListOfContainer = NULL);

    /**
    transfer every individual object list from name vector
    */
    void generateObjectFromName(
      const std::vector< CCopasiContainer * > * pListOfContainer,
      std::vector<CCopasiObject*> & objectList,
      std::vector<CCopasiObjectName>* nameVector);

    /**
    sets the reference to the report
    */
    void setReportDefinition(CReportDefinition *reportDef);

    /**
    returns the target of the Report Tag
    */
    const std::string& getTarget();

    /**
    sets the reference to the report
    */
    void setTarget(std::string target);

    /**
    Returns whether the Report Tag is appended or not
    */
    bool append();

    /**
       sets the append attribute if the report tag
    */
    void setAppend(bool append);

    /**
    to print header
    */
    void printHeader();

    /**
    to print body
    */
    void printBody();

    /**
       to print footer
       */
    void printFooter();

    /**
    to print body
    */
    static void printBody(CReport * pReport);
  };

#endif
