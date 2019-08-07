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
 *  Created for COPASI by Liang Xu
 ****************************************************************************/

#ifndef COPASI_CReport
#define COPASI_CReport

#include <string>
#include <vector>
#include <iostream>

#include "copasi/core/CDataContainer.h"
#include "copasi/core/CRegisteredCommonName.h"

#include "copasi/output/COutputHandler.h"

class CReportDefinition;
class CReportTable;

class CReport : public COutputInterface
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
    FooterFooter
  };

private:
  const CDataModel * mpDataModel;
  std::ostream * mpOstream;
  bool mStreamOwner;

  const CReportDefinition *mpReportDef;
  std::string mTarget;
  bool mAppend;
  bool mConfirmOverwrite;

  std::vector< CObjectInterface * > mFooterObjectList;
  std::vector< CObjectInterface * > mBodyObjectList;
  std::vector< CObjectInterface * > mHeaderObjectList;

  CReport * mpHeader;
  CReport * mpBody;
  CReport * mpFooter;

  State mState;

public:
  /**
   * Default constructor.
   */
  CReport();

  /**
   * Copy constructor.
   * @param const CReport & src
   */
  CReport(const CReport & src);
  /**
   * cleanup
   */
  void cleanup();

  /**
   *  Destructor.
   */
  ~CReport();

  /**
   * compile the object list from name vector
   * @param CObjectInterface::ContainerList listOfContainer
   * @param  const CDataModel* pDataModel
   * @return bool success
   */
  virtual bool compile(CObjectInterface::ContainerList listOfContainer);

  /**
   * Perform an output event for the current activity
   * @param const Activity & activity
   */
  virtual void output(const Activity & activity);

  /**
   * Introduce an additional separator into the output
   * @param const Activity & activity
   */
  virtual void separate(const Activity & /* activity */);

  /**
   * Finish the output
   */
  virtual void finish();

  /**
   * Close the stream if applicable
   */
  virtual void close();

  /**
   * returns the reference of the Report Tag
   */

  /**
   * returns the reference of the Report Tag
   */
  const CReportDefinition* getReportDefinition() const;

  /**
   * Open the defined target stream or use the given argument
   * @param const CDataModel * pDataModel,
   * @param std::ostream * pOstream (default: NULL)
   * @return std::ostream * mpOstream
   */
  std::ostream * open(const CDataModel * pDataModel,
                      std::ostream * pOstream = NULL);

  /**
   * Retrieve a pointer to the ostream
   * @return std::ostream * pOstream
   */
  std::ostream * getStream() const;

  /**
   * sets the reference to the report
   * @param const CReportDefinition *reportDef
   */
  void setReportDefinition(const CReportDefinition *reportDef);

  /**
   * returns the target of the Report Tag
   */
  const std::string & getTarget() const;

  /**
   * sets the reference to the report
   * @param const std::string & target
   */
  void setTarget(const std::string & target);

  /**
   * Returns whether the Report Tag is appended or not
   * @return const bool & append
   */
  const bool & append() const;

  /**
   * sets the append attribute if the report tag
   * @param const bool & append
   */
  void setAppend(const bool & append);

  /**
   * Returns whether a confirmation should be issued when overwriting a report
   * @return const bool & confirmOverwite
   */
  const bool & confirmOverwrite() const;

  /**
   * sets the confirmOverwrite attribute if the report tag
   * @param const bool & confirmOverwrite
   */
  void setConfirmOverwrite(const bool & confirmOverwrite);

private:
  /**
   * to print header
   */
  void printHeader();

  /**
   * to print body
   */
  void printBody();

  /**
   * to print footer
   */
  void printFooter();

  /**
   * transfer every individual object list from name vector
   */
  void generateObjectsFromName(const CObjectInterface::ContainerList & listOfContainer,
                               std::vector< CObjectInterface * > & objectList,
                               CReport *& pReport,
                               const std::vector<CRegisteredCommonName>* nameVector);

  /**
   * Compile the child report
   * @param CReport * pReport
   * @param CObjectInterface::ContainerList listOfContainer
   * @return bool success
   */
  bool compileChildReport(CReport * pReport, CObjectInterface::ContainerList listOfContainer);
};

#endif
