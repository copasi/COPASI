/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReportDefinition.h,v $
   $Revision: 1.25 $
   $Name:  $
   $Author: mkulkarn $ 
   $Date: 2003/12/11 21:43:29 $
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

#include "CCopasiObject.h"
#include "CCopasiObjectName.h"
#include "CCopasiStaticString.h"
#include <string>
#include <vector>

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
    std::vector<CCopasiObjectName> mHeaderVector;
    std::vector<CCopasiObjectName> mFooterVector;

    std::vector<CCopasiObjectName> mBodyVector;

    CReportBody *mpBody;
    CCopasiStaticString mSeperator;
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
    cleanup
    */
    void cleanup();

    /**
    Returns the comments in the report tag
    */
    std::string & getComment()
    {
      return mComment;
    }

    /**
    sets the comments in the report tag
    */
    void setComment(const std::string & comment)
    {
      mComment = comment;
    }

    /**
    gets the body in the report tag
    */
    std::vector<CCopasiObjectName>* getBodyAddr();

    /**
    gets the header in the report tag
    */
    std::vector<CCopasiObjectName>* getHeaderAddr();

    /**
    gets the footer in the report tag
    */
    std::vector<CCopasiObjectName>* getFooterAddr();

    /**
    gets the Body in the report tag
    */
    CReportBody* getReportBody();

    /**
    sets the Body in the report tag
    */
    void setReportBody(CReportBody *pNewBody);

    void setSeperator(const CCopasiStaticString& Seperator)
    {
      mSeperator = Seperator;
    }

    CCopasiStaticString& getSeperator()
    {
      return mSeperator;
    }

    bool getTitle()
    {
      return mbTitle;
    }

    void setTitle(bool mTitle)
    {
      mbTitle = mTitle;
    }

    inline std::string & getKey()
    {
      return mKey;
    }
  };

#endif
