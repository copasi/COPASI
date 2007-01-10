// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "report/CReport.h"

%}

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
     *  Destructor.
     */
    ~CReport();

    /**
     * returns the reference of the Report Tag
     */
    CReportDefinition* getReportDefinition();

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

  };



