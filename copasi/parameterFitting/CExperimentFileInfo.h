/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentFileInfo.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $
   $Date: 2011/03/07 19:32:04 $
   End CVS Header */

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CExperimentFileInfo
#define COPASI_CExperimentFileInfo

#include <string>
#include <vector>

class CExperimentSet;
class CExperiment;

/**
 *
 */
class CExperimentFileInfo
{
private:
  /**
   *
   */
  class CExperimentInfo
  {
    // Operations
  private:
    /**
     *
     */
    CExperimentInfo();

  public:
    /**
     *
     */
    CExperimentInfo(CExperiment & Experiment);

    /**
     *
     */
    ~CExperimentInfo();

    // Attributes
  public:
    /**
     *
     */
    CExperiment * pExperiment;

    /**
     *
     */
    size_t First;

    /**
     *
     */
    size_t Last;
  };

  // Operations
private:
  /**
   *
   */
  CExperimentFileInfo();

public:
  /**
   *
   */
  CExperimentFileInfo(CExperimentSet & set);

  /**
   *
   */
  ~CExperimentFileInfo();

  /**
   *
   */
  bool setFileName(const std::string & fileName);

  /**
   *
   */
  const std::string & getFileName() const;

  /**
   *
   */
  bool sync();

  /**
   *
   */
  bool validate() const;

  /**
   *
   */
  bool validateFirst(const size_t & index,
                     const size_t & value);

  /**
   *
   */
  bool validateLast(const size_t & index,
                    const size_t & value);

  /**
   *
   */
  bool validateHeader(const size_t & index,
                      const size_t & value);

  /**
   *
   */
  std::vector< std::string > getExperimentNames() const;

  /**
   *
   */
  CExperiment * getExperiment(const std::string & name);

  /**
   *
   */
  bool getFirstUnusedSection(size_t & First,
                             size_t & Last);

  /**
   *
   */
  bool getNextUnusedSection(size_t & First,
                            size_t & Last);

  /**
   *
   */
  bool adjustForEmptyLines(size_t & First,
                           size_t & Last);

  // Attributes
private:
  /**
   *
   */
  CExperimentSet * mpSet;

  /**
   *
   */
  std::string mFileName;

  /**
   *
   */
  std::vector< CExperimentInfo * > mList;

  /**
   *
   */
  size_t mLines;

  /**
   *
   */
  size_t mUsedEnd;

  /**
   *
   */
  std::vector< size_t > mEmptyLines;
};

#endif // COPASI_CExperimentFileInfo
