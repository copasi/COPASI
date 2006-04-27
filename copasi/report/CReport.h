/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReport.h,v $
   $Revision: 1.35 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:31:10 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/****************************************************************************
 *
 * Created: Tue Aug 11 2003
 *      by: Liang Xu
 *
 *  Created for Copasi by Liang Xu
 ****************************************************************************/

#ifndef COPASI_CReport
#define COPASI_CReport

#include <string>
#include <vector>
#include <iostream>

#include "CCopasiContainer.h"
#include "CCopasiObjectName.h"

#include "utilities/COutputHandler.h"

class CReportDefinition;
class CReportTable;

class CReport : public CCopasiContainer, public COutputInterface
  {
    /**
     * Enumeration of the report states.
     */
    enum State
    {
      Invalid = -1,
      Compiled = 0,
      HeaderHeader,
      HeaderBody,
      HeaderFooter,
      BodyHeader,
      BodyBody,
      BodyFooter,
      FooterHeader,
      FooterBody,
      FooterFooter,
    };

  private:
    std::ostream * mpOstream;
    bool mStreamOwner;

    CReportDefinition *mpReportDef;
    std::string mTarget;
    bool mAppend;

    std::vector< CCopasiObject * > mFooterObjectList;
    std::vector< CCopasiObject * > mBodyObjectList;
    std::vector< CCopasiObject * > mHeaderObjectList;

    CReport * mpHeader;
    CReport * mpBody;
    CReport * mpFooter;

    State mState;

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
     * compile the object list from name vector
     * @param std::vector< CCopasiContainer * > listOfContainer
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > listOfContainer);

    /**
     * Perform an output event for the current activity
     * @param const Activity & activity
     */
    virtual void output(const Activity & activity);

    /**
     * Introduce an additional seperator into the ouput
     * @param const Activity & activity
     */
    virtual void separate(const Activity & /* activity */);

    /**
     * Finsh the output
     */
    virtual void finish();

    /**
     * returns the reference of the Report Tag
     */
    CReportDefinition* getReportDefinition();

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
     * sets the reference to the report
     */
    void setReportDefinition(CReportDefinition *reportDef);

    /**
     * returns the target of the Report Tag
     */
    const std::string& getTarget() const;

    /**
     * sets the reference to the report
     */
    void setTarget(std::string target);

    /**
     * Returns whether the Report Tag is appended or not
     */
    bool append() const;

    /**
     * sets the append attribute if the report tag
     */
    void setAppend(bool append);

  private:
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
     * transfer every individual object list from name vector
     */
    void generateObjectsFromName(
      const std::vector< CCopasiContainer * > * pListOfContainer,
      std::vector< CCopasiObject * > & objectList,
      CReport *& pReport,
      const std::vector<CRegisteredObjectName>* nameVector);

    /**
     * Compile the child report
     * @param CReport * pReport
     * @param std::vector< CCopasiContainer * > listOfContainer
     * @return bool success
     */
    bool compileChildReport(CReport * pReport, std::vector< CCopasiContainer * > listOfContainer);
  };

#endif
