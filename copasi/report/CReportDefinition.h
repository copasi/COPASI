/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReportDefinition.h,v $
   $Revision: 1.34 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/15 12:55:31 $
   End CVS Header */

/****************************************************************************
 * 
 * Created: Tue Aug 11 2003
 *      by: Liang Xu
 *
 *  Created for Copasi by Liang Xu
 ****************************************************************************/

#ifndef COPASI_CReport_Definition
#define COPASI_CReport_Definition

#include <string>
#include <vector>

#include "CCopasiObject.h"
#include "CCopasiObjectName.h"
#include "CCopasiStaticString.h"
#include "utilities/CCopasiTask.h"

class CReportDefinition;
class CComment;
class CHeaderFooter;
class CReportBody;
class CReportObject;
class CReport;
class CReportTable;

class CReportDefinition : public CCopasiObject
  {
    // Operations
  private:
    std::string mKey;
    std::string mComment;
    CCopasiTask::Type mTaskType;

    std::vector<CRegisteredObjectName> mHeaderVector;
    std::vector<CRegisteredObjectName> mBodyVector;
    std::vector<CRegisteredObjectName> mFooterVector;

    CCopasiStaticString mSeparator;
    bool mTable;
    bool mbTitle;

  public:
    /**
     *  Default constructor.
     */
    CReportDefinition(const std::string & name = "NoName",
                      const CCopasiContainer * pParent = NULL);

    /**
     *  Copy constructor.
     */
    CReportDefinition(const CReportDefinition & src,
                      const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CReportDefinition();

    /**
     *cleanup
     */
    void cleanup();

    /**
     *Returns the comments in the report tag
     */
    const std::string & getComment() const
      {
        return mComment;
      }

    /**
     *sets the comments in the report tag
     */
    void setComment(const std::string & comment)
    {
      mComment = comment;
    }

    /**
     *gets the body in the report tag
     */
    std::vector<CRegisteredObjectName>* getBodyAddr();

    /**
     *gets the header in the report tag
     */
    std::vector<CRegisteredObjectName>* getHeaderAddr();

    /**
     *gets the footer in the report tag
     */
    std::vector<CRegisteredObjectName>* getFooterAddr();

    /**
     * This adds header and body entries for one table element 
     * (including separator if necessary)
     * @param const std::string & cn
     */
    void addTableElement(const std::string & cn);

    /**
     * This adds header and body entries for one table element 
     * (including separator if necessary)
     * @param const CCopasiObject * pObject
     */
    void addTableElement(const CCopasiObject * pObject);

    /**
     *
     */
    bool setTaskType(const CCopasiTask::Type & taskType);

    /**
     *
     */
    const CCopasiTask::Type & getTaskType() const;

    /**
     *
     */
    void setSeparator(const CCopasiStaticString& Separator);

    /**
     *
     */
    const CCopasiStaticString& getSeparator() const;

    /**
     *
     */
    bool getTitle() const;

    /**
     *
     */
    void setTitle(bool title);

    /**
     *
     */
    bool isTable() const;

    /**
     *
     */
    void setIsTable(bool table);

    /**
     *
     */
    virtual const std::string & getKey() const;
  };

#endif
