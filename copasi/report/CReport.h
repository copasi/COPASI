/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReport.h,v $
   $Revision: 1.20 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/19 20:11:45 $
   End CVS Header */

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
  public:
    static const std::vector< CCopasiContainer * > EmptyList;

  private:
    std::ostream * mpOstream;
    bool mStreamOwner;

    CReportDefinition *mpReportDef;
    std::string mTarget;
    bool mAppend;

    std::vector<CCopasiObject*> footerObjectList;
    std::vector<CCopasiObject*> bodyObjectList;
    std::vector<CCopasiObject*> headerObjectList;

  public:
    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CReport(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor.
     * @param const CReport & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CReport(const CReport & src,
            const CCopasiContainer * pParent);
    /**
     * cleanup
     */
    void cleanup();

    /**
     *  Destructor.
     */
    ~CReport();

    /**
     * returns the reference of the Report Tag
     */
    CReportDefinition* getReportDefinition();

    /**
     * compile the object list from name vector
     * @param const std::vector< CCopasiContainer * > listOfContainer
     * @return bool success
     */
    bool compile(const std::vector< CCopasiContainer * > listOfContainer =
                   EmptyList);

    /**
     * Open the defined target stream or use the given argument
     * @param std::ostream * pOstream (default: NULL)
     * @return std::ostream * mpOstream
     */
    std::ostream * open(std::ostream * pOstream = NULL);

    /**
     * Retrieve a pointer to the ostream
     * @return std::ostream * pOstream
     */
    std::ostream * CReport::getStream() const;

    /**
     * transfer every individual object list from name vector
     */
    void generateObjectsFromName(
      const std::vector< CCopasiContainer * > * pListOfContainer,
      std::vector<CCopasiObject*> & objectList,
      std::vector<CCopasiObjectName>* nameVector);

    /**
     * sets the reference to the report
     */
    void setReportDefinition(CReportDefinition *reportDef);

    /**
     * returns the target of the Report Tag
     */
    const std::string& getTarget();

    /**
     * sets the reference to the report
     */
    void setTarget(std::string target);

    /**
     * Returns whether the Report Tag is appended or not
     */
    bool append();

    /**
     * sets the append attribute if the report tag
     */
    void setAppend(bool append);

    /**
     * to print header
     */
    void printHeader();

    /**
     * to print body
     */
    void printBody();

    /**
     * to print footer
     */
    void printFooter();

    /**
     *  to print body
     */
    static void printBody(CReport * pReport);
  };

#endif
