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
  };

#endif
