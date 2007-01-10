// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "report/CReportDefinition.h"

%}


class CReportDefinition : public CCopasiObject
{
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
     *Returns the comments in the report tag
     */
    const std::string & getComment() const;

    /**
     *sets the comments in the report tag
     */
    void setComment(const std::string & comment);

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
     *gets the footer in the report tag
     */
    std::vector<CRegisteredObjectName>* getTableAddr();

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
    void setSeparator(const CCopasiReportSeparator & Separator);

    /**
     *
     */
    const CCopasiReportSeparator & getSeparator() const;

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
     * Set the precsion for floating point numbers;
     * @param const unsigned C_INT32 & precision
     */
    void setPrecision(const unsigned C_INT32 & precision);

    /**
     * Retrieve the precsion for floating point numbers;
     * @return const unsigned C_INT32 & precision
     */
    const unsigned C_INT32 & getPrecision() const;

    /**
     *
     */
    virtual const std::string & getKey() const;


};


