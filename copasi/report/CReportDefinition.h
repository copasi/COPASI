/**
 *  CReportDefinition class.
 *  This class is the header file for the ReportDefinition.
 *
 *  Created for Copasi by Mudita Singhal
 */

#ifndef COPASI_CReportDefinition
#define COPASI_CReportDefinition

#include <string>
class CReportDefinition;
class CComment;
class CHeaderFooter;
class CBody;
class CObject;
class CReport;
class CTable;

class CReportDefinition
  {
    // Operations
  protected:
    /**
     *  Default constructor.
     */
    CReportDefinition();

  public:

    /**
    *  Destructor.
    */
    ~CReportDefinition();

    /**
    Returns the comments in the report tag
    */
    CComment getComment();

    /**
    sets the comments in the report tag
    */
    void setComment(CComment *comment);

    /**
    gets the header in the report tag
    */
    CHeaderFooter getHeader();

    /**
    sets the header in the report tag
    */
    void setHeader(CHeaderFooter *header);

    /**
    gets the footer in the report tag
    */
    CHeaderFooter getFooter();

    /**
    sets the footer in the report tag
    */
    void setFooter(CHeaderFooter *footer);

    /**
    gets the Body in the report tag
    */
    CBody getBody();

    /**
    sets the Body in the report tag
    */
    void setBody(CBody *body);
  };

class CComment
  {
  protected:
    /**
     *  Default constructor.
     */
    CComment();

  public:

    /**
    *  Destructor.
    */
    ~CComment();

    /**
    gets the text
    */
    CComment getText();

    /**
    sets the text 
    */
    void setText(CComment *text);
  };

class CHeaderFooter
  {
  protected:
    /**
     *  Default constructor.
     */
    CHeaderFooter();

  public:

    /**
    *  Destructor.
    */
    ~CHeaderFooter();

    /**
    gets the Object in the Header or Footer tag
    */
    CObject getObject();

    /**
    sets the Object in the Header or Footer tag
    */
    void setObject(CObject *object);

    /**
    gets the Text in the Header or Footer tag
    */
    CComment getText();

    /**
    sets the Text in the Header or Footer tag
    */
    void setText(CComment *text);

    /**
    gets the report in the Header or Footer tag
    */
    CReport getReport();

    /**
    sets the Report in the Header or Footer tag
    */
    void setReport(CReport *report);
  };

class CBody
  {
  protected:
    /**
     *  Default constructor.
     */
    CBody();

  public:

    /**
    *  Destructor.
    */
    ~CBody();

    /**
    gets the report in the Body Tag
    */
    CReport getReport();

    /**
    sets the Report in the Body tag
    */
    void setReport(CReport *report);

    /**
    gets the Table tag  in the Body Tag
    */
    CTable getTable();

    /**
    sets the Table tag in the Body tag
    */
    void setTable(CTable *table);
  };

class CObject
  {
  protected:
    /**
     *  Default constructor.
     */
    CObject();

  public:

    /**
    *  Destructor.
    */
    ~CObject();

    /**
    returns the name of the Object Tag
    */
    const std::string getName();

    /**
    sets the name of the Object tag
    */
    void setName(const std::string *name);
  };

class CReport
  {
  protected:
    /**
     *  Default constructor.
     */
    CReport();

  public:

    /**
    *  Destructor.
    */
    ~CReport();

    /**
    returns the reference of the Report Tag
    */
    CReport getReference();

    /**
    sets the reference to the report
    */
    void setReference(CReport *report);

    /**
    returns the target of the Report Tag
    */
    const std::string getTarget();

    /**
    sets the reference to the report
    */
    void setTarget(const std::string *target);

    /**
    Returns whether the Report Tag is appended or not
    */
    bool append();

    /**
       sets the append attribute if the report tag
    */
    void setAppend(bool append);
  };

class CTable
  {
  protected:
    /**
     *  Default constructor.
     */
    CTable();

  public:

    /**
    *  Destructor.
    */
    ~CTable();

    /**
    gets the Object tag of the Table tag
    */
    CObject getObject();

    /**
       sets the Object tag of the Table tag
    */
    void setObject(CObject *object);

    /**
    gets the Seperator attribute of the Table tag
    */
    const std::string getSeperator();

    /**
       sets the seperator attribute of the Table tag
    */
    void setSeperator(const std::string *seperator);

    /**
    gets the printTitle of the Table tag
    */
    bool printTitle();

    /**
       sets the print Title of the Table tag
    */
    void setPrintTitle(bool printTitle);
  };

#endif
