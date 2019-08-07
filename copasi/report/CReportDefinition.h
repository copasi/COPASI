// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

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

#include "copasi/core/CDataObject.h"
#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/core/CDataString.h"
#include "copasi/utilities/CCopasiTask.h"

class CReportDefinition;
class CComment;
class CHeaderFooter;
class CReportBody;
class CReportObject;
class CReport;
class CReportTable;

class CReportDefinition : public CDataObject
{
  // Operations
private:
  std::string mKey;
  std::string mComment;
  CTaskEnum::Task mTaskType;

  std::vector<CRegisteredCommonName> mHeaderVector;
  std::vector<CRegisteredCommonName> mBodyVector;
  std::vector<CRegisteredCommonName> mFooterVector;
  std::vector<CRegisteredCommonName> mTableVector;

  CCopasiReportSeparator mSeparator;
  bool mTable;
  bool mbTitle;
  unsigned C_INT32 mPrecision;

protected:
  CReportDefinition(const CReportDefinition & src);

public:
  /**
   * Static method to create a CDataObject based on the provided data
   * @param const CData & data
   * @return CReportDefinition * pDataObject
   */
  static CReportDefinition * fromData(const CData & data, CUndoObjectInterface * pParent);

  /**
   * Retrieve the data describing the object
   * @return CData data
   */
  virtual CData toData() const;

  /**
   * Apply the provided data to the object
   * @param const CData & data
   * @return bool success
   */
  virtual bool applyData(const CData & data, CUndoData::CChangeSet & changes);

  /**
   * Create the undo data which represents the changes recording the
   * differences between the provided oldData and the current data.
   * @param CUndoData & undoData
   * @param const CUndoData::Type & type
   * @param const CData & oldData (default: empty data)
   * @param const CCore::Framework & framework (default: CCore::Framework::ParticleNumbers)
   * @return CUndoData undoData
   */
  virtual void createUndoData(CUndoData & undoData,
                              const CUndoData::Type & type,
                              const CData & oldData = CData(),
                              const CCore::Framework & framework = CCore::Framework::ParticleNumbers) const;

  /**
   *  Default constructor.
   */
  CReportDefinition(const std::string & name = "NoName",
                    const CDataContainer * pParent = NO_PARENT);

  /**
   *  Copy constructor.
   */
  CReportDefinition(const CReportDefinition & src,
                    const CDataContainer * pParent);

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
   * (default: CDataContainer::EmptyList)
   * @return bool success
   */
  bool preCompileTable(const CObjectInterface::ContainerList & listOfContainer);

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
  std::vector<CRegisteredCommonName>* getBodyAddr();

  /**
   *gets the body in the report tag
   */
  const std::vector<CRegisteredCommonName>* getBodyAddr() const;

  /**
   *gets the header in the report tag
   */
  std::vector<CRegisteredCommonName>* getHeaderAddr();

  /**
   *gets the header in the report tag
   */
  const std::vector<CRegisteredCommonName>* getHeaderAddr() const;

  /**
   *gets the footer in the report tag
   */
  std::vector<CRegisteredCommonName>* getFooterAddr();

  /**
   *gets the footer in the report tag
   */
  const std::vector<CRegisteredCommonName>* getFooterAddr() const;

  /**
   *gets the footer in the report tag
   */
  std::vector<CRegisteredCommonName>* getTableAddr();

  /**
   *gets the footer in the report tag
   */
  const std::vector<CRegisteredCommonName>* getTableAddr() const;

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
   * @param const CDataObject * pObject
   */
  void addTableElement(const CDataObject * pObject);
};

#endif
