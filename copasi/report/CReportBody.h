/****************************************************************************
 * 
 * Created: Tue Aug 11 2003
 *      by: Liang Xu
 *
 *  Created for Copasi by Liang Xu
 ****************************************************************************/

#ifndef COPASI_CREPORT_BODY
#define COPASI_CREPORT_BODY

#include <string>
#include <vector>
#include "copasi.h"
#include "CCopasiObjectName.h"

class CReportTable;
class CCopasiObjectName;

class CReportBody
  {
  private:
    std::vector<CCopasiObjectName> mReportObjectName;
    CReportTable *mpReportTable;

  public:
    /**
        *  Default constructor.
        */
    CReportBody();

    /**
    cleanup
    */
    void cleanup();

    /**
    *  Destructor.
    */
    ~CReportBody();

    /**
    gets the Table tag  in the Body Tag
    */
    CReportTable* getTable();

    /**
    sets the Table tag in the Body tag
    */
    void setTable(CReportTable *table);
  };

class CReportTable
  {
  private:
    std::vector<CCopasiObjectName>* mpObjectNameVector;
    std::string mSeperator;
    bool mPrintTitle;

  public:
    /**
        *  Default constructor.
        */
    CReportTable();

    /**
    cleanup
    */
    void cleanup();

    /**
       *  Destructor.
       */
    ~CReportTable();

    /**
    gets the Object tag of the Table tag
    */
    inline std::vector<CCopasiObjectName>* getObjectNameVector()
    {
      return mpObjectNameVector;
    }

    /**
       sets the Object tag of the Table tag
    */
    inline void setObjectNameVector(std::vector<CCopasiObjectName> *objectVector)
    {
      mpObjectNameVector = objectVector;
    }

    /**
    gets the Seperator attribute of the Table tag
    */
    inline const std::string& getSeperator()
    {
      return mSeperator;
    }

    /**
       sets the seperator attribute of the Table tag
    */
    inline void setSeperator(const std::string seperator)
    {
      mSeperator = seperator;
    }

    /**
    gets the printTitle of the Table tag
    */
    bool printTitle()
    {
      return mPrintTitle;
    }

    /**
       sets the print Title of the Table tag
    */
    void setPrintTitle(bool printTitle)
    {
      mPrintTitle = printTitle;
    }
  };

#endif
