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
    CCopasiStaticString mComment;
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
    CReportDefinition();

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
    const CCopasiStaticString& getComment()
    {
      return mComment;
    }

    /**
    sets the comments in the report tag
    */
    void setComment(const CCopasiStaticString comment)
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

    void setSeperator(const CCopasiStaticString Seperator)
    {
      mSeperator = Seperator;
    }

    const CCopasiStaticString getSeperator()
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
