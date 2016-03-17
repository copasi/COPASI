// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

#include "report/CCopasiObject.h"
#include "report/CCopasiObjectName.h"
#include "report/CCopasiStaticString.h"
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
  CTaskEnum::Task mTaskType;

  std::vector<CRegisteredObjectName> mHeaderVector;
  std::vector<CRegisteredObjectName> mBodyVector;
  std::vector<CRegisteredObjectName> mFooterVector;
  std::vector<CRegisteredObjectName> mTableVector;

  CCopasiReportSeparator mSeparator;
  bool mTable;
  bool mbTitle;
  unsigned C_INT32 mPrecision;

protected:
  CReportDefinition(const CReportDefinition & src);

public:
  /**
   *  Default constructor.
   */
  CReportDefinition(const std::string & name = "NoName",
                    const CCopasiContainer * pParent = NO_PARENT);

  /**
   *  Copy constructor.
   */
  CReportDefinition(const CReportDefinition & src,
                    const CCopasiContainer * pParent);

  /**
   *  Destructor.
   */
  ~CReportDefinition();

  /**
   *cleanup
   */
  void cleanup();

  /**
   * Convert the table list into a header and body list.
   * @param const CObjectInterface::ContainerList & listOfContainer
   * (default: CCopasiContainer::EmptyList)
   * @return bool success
   */
  bool preCompileTable(const CObjectInterface::ContainerList & listOfContainer);

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
   *gets the body in the report tag
   */
  const std::vector<CRegisteredObjectName>* getBodyAddr() const;

  /**
   *gets the header in the report tag
   */
  std::vector<CRegisteredObjectName>* getHeaderAddr();

  /**
   *gets the header in the report tag
   */
  const std::vector<CRegisteredObjectName>* getHeaderAddr() const;

  /**
   *gets the footer in the report tag
   */
  std::vector<CRegisteredObjectName>* getFooterAddr();

  /**
   *gets the footer in the report tag
   */
  const std::vector<CRegisteredObjectName>* getFooterAddr() const;

  /**
   *gets the footer in the report tag
   */
  std::vector<CRegisteredObjectName>* getTableAddr();

  /**
   *gets the footer in the report tag
   */
  const std::vector<CRegisteredObjectName>* getTableAddr() const;

  /**
   *
   */
  bool setTaskType(const CTaskEnum::Task & taskType);

  /**
   *
   */
  const CTaskEnum::Task & getTaskType() const;

  /**
   *
   */
  void setSeparator(const std::string & separator);

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

private:
  /**
   * This adds header and body entries for one table element
   * (including separator if necessary)
   * @param const CCopasiObject * pObject
   */
  void addTableElement(const CCopasiObject * pObject);
};

#endif
