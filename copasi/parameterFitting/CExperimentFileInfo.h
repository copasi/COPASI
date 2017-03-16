// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
   * counts the lines in the file and initializes the empty lines
   */
  size_t countLines();

  /**
   * @return the filename
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
   * go through the experiments and remove all that don't match
   */
  void removeInvalidExperiments();

  /**
   * Removes the last experiments
   * @param start the start from where on all experiments will be deleted
   */
  void removeLastExperiments(size_t start);

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
   * @return object names of all experiments
   */
  std::vector< std::string > getExperimentNames() const;

  /**
   * @param name the object name of an experiment
   * @return the experiment if found or NULL
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

  /**
   * @return the first empty line within the given interval.
   */
  size_t getInterruption(size_t first, size_t last) const;

  // Attributes
private:
  /**
   * the experiment set
   */
  CExperimentSet * mpSet;

  /**
   * the filename
   */
  std::string mFileName;

  /**
   * vector of experiment info for each experiment
   */
  std::vector< CExperimentInfo * > mList;

  /**
   * number of lines in the file
   */
  size_t mLines;

  /**
   *
   */
  size_t mUsedEnd;

  /**
   * vector of empty lines
   */
  std::vector< size_t > mEmptyLines;
};

#endif // COPASI_CExperimentFileInfo
